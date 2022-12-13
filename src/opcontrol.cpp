/*
  Copyright (c) 2019-2022 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event will
  the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including commercial
  applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the
  original software. If you use this software in a product, an acknowledgment (see the following)
  in the product documentation is required.

  Portions Copyright (c) 2019-2022 7701F

  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
  being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/
#include <sstream>

#include "7701.h"

/* Honestly my stupidest moment, it stops the robot by driving the motor opposite direction of the current velocity */
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_RIGHT_X) == 0 && master.get_analog(ANALOG_LEFT_Y) == 0) {
			if (arms::chassis::leftMotors->get_actual_velocities() != std::vector<double>{0, 0, 0, 0} ||
			    arms::chassis::rightMotors->get_actual_velocities() != std::vector<double>{0, 0, 0, 0}) {
				// arms::chassis::leftMotors->move_velocity(arms::chassis::leftMotors->get_actual_velocities()[0] * -2);
				// arms::chassis::rightMotors->move_velocity(arms::chassis::rightMotors->get_actual_velocities()[0] * -2);
			}
		}
	}
}

/* Smart boy motor brake solution */
void prosBrake(bool brakeOn) {
	if (pbrake == true) {
		if (arms::chassis::rightMotors->get_brake_modes() != std::vector<pros::motor_brake_mode_e>(4, pros::E_MOTOR_BRAKE_HOLD)) {
			arms::chassis::leftMotors->set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
			arms::chassis::rightMotors->set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
		}
	} else if (pbrake == false) {
		if (arms::chassis::rightMotors->get_brake_modes() != std::vector<pros::motor_brake_mode_e>(4, pros::E_MOTOR_BRAKE_COAST)) {
			arms::chassis::leftMotors->set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
			arms::chassis::rightMotors->set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
		}
	}
}

/* Flywheel vars */
// Update inteval (in mS) for the flywheel control loop
#define FW_LOOP_SPEED 20

// Maximum power we want to send to the flywheel motors
#define FW_MAX_POWER 200

// Set the encoder ticks per revolution
float ticks_per_rev = 360;

// Encoder
long encoder_counts;      ///< current encoder count
long encoder_counts_last; ///< current encoder count

// velocity measurement
float motor_velocity; ///< current velocity in rpm
long millis_last;     ///< Time of last velocity calculation

// TBH control algorithm variables
long target_velocity; ///< target_velocity velocity
float current_error;  ///< error between actual and target_velocity velocities
float last_error;     ///< error last time update called
float gain;           ///< gain
float drive;          ///< final drive out of TBH (0.0 to 1.0)
float drive_at_zero;  ///< drive at last zero crossing
long first_cross;     ///< flag indicating first zero crossing
float drive_approx;   ///< estimated open loop drive

// final motor drive
long motor_drive; ///< final motor control value

int current_time;
float delta_ms;
int delta_enc;

namespace deFenestration::Flywheel {

/* Set motor voltage equal to desired velocity
 * value: motor control value
 */
void FwMotorSet(int value) {
	int x;
	x = (value * 12000) / 200;
	fw.move_voltage(x);
}

/* Set motor velocity
 * velocity: desired velocity
 * predicted_drive: estimated open loop motor drive
 */
void FwVelocitySet(int velocity, float predicted_drive) {
	// set target_velocity velocity (motor rpm)
	target_velocity = velocity;

	// Set error so zero crossing is correctly detected
	current_error = target_velocity - motor_velocity;
	last_error = current_error;

	// Set predicted open loop drive value
	drive_approx = predicted_drive;
	// Set flag to detect first zero crossing
	first_cross = 1;
	// clear tbh variable
	drive_at_zero = 0;
}

/* Calculate the current flywheel motor velocity */
void FwCalculateSpeed() {
	current_time = pros::millis();
	delta_ms = 1000.0 / (current_time - millis_last);

	encoder_counts = fw.get_position();

	// Calculate the change in encoder counts since the last time this function was called
	delta_enc = (encoder_counts - encoder_counts_last);

	// Calculate the motor velocity in RPM
	// motor_velocity = delta_ms * delta_enc * 60.0 / ticks_per_rev;
	// motor_velocity = delta_ms * delta_enc * 60.0 / ticks_per_rev;
	motor_velocity = (1000.0 / delta_ms) * delta_enc * 60.0 / ticks_per_rev;

	// (1000.0 / 60000) * 360 * 60.0 / 360 =
	// 1000.0 / 500 = 2

	encoder_counts_last = encoder_counts;
	millis_last = current_time;
}

/* Update the velocity tbh controller variables */
void FwControlUpdateVelocityTbh() {
	// calculate error in velocity
	// target_velocity is desired velocity
	// current is measured velocity
	current_error = target_velocity - motor_velocity;

	// Calculate new control value
	drive = drive + (current_error * gain);

	// Clip to the range 0 - 1.
	// We are only going forwards
	if (drive > 1)
		drive = 1;
	if (drive < 0)
		drive = 0;

	// Check for zero crossing
	if (current_error != last_error) {
		// First zero crossing after a new set velocity command
		if (first_cross) {
			// Set drive to the open loop approximation
			drive = drive_approx;
			first_cross = 0;
		} else
			drive = 0.5 * (drive + drive_at_zero);

		// Save this drive value in the "tbh" variable
		drive_at_zero = drive;
	}

	// Save last error
	last_error = current_error;
}

/* Task to control the velocity of the flywheel */
void FwControlTask() {
	// Set the gain
	gain = 0.0005;

	while (1) {
		// Calculate velocity
		deFenestration::Flywheel::FwCalculateSpeed();

		// Do the velocity TBH calculations
		deFenestration::Flywheel::FwControlUpdateVelocityTbh();

		// Scale drive into the range the motors need
		motor_drive = (drive * FW_MAX_POWER) + 0.5;

		// Final Limit of motor values - don't really need this
		if (motor_drive > 210)
			motor_drive = 210;
		if (motor_drive < -200)
			motor_drive = -200;

		// and finally set the motor control value
		deFenestration::Flywheel::FwMotorSet(motor_drive);

		// print fw speed
		printf("flywheel speed: %f current error: %f\r", motor_velocity, current_error);

		// Run at somewhere between 20 and 50mS
		pros::delay(FW_LOOP_SPEED);
	}
}

} // namespace deFenestration::Flywheel

/* Game System Controls */
bool flywheelState = false;
bool flywheelThirdPosState = false;
bool fwON = false;

bool pistonState = false;
bool prevPistonState = false;
bool indexState = false;

bool EpistonState = false;
bool EprevPistonState = false;
bool endgameState = false;

/* Exponential Drive Control
 * If bypass is set to true we switch to direct input,
 * bypassing the exponential curve
 */
std::int32_t exponentialDrive(std::int32_t joyVal) {
	if (bypass == true) {
		return joyVal;
	} else {
		return pow(joyVal, 3) / 10000;
	}
}

/*
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	prosBrake(true);

	deFenestration::Flywheel::FwVelocitySet(0, 0.0);

	// if (deFenestration::showScreen == true) {
	// 	arms::selector::destroy();
	// 	pros::Task displayTask(deFenestration::display);
	// }

	// Run Loop
	while (true) {
		/* Steering
		 * Handled by ARMS
		 */
		int leftJoyStick = master.get_analog(ANALOG_LEFT_Y);
		int rightJoyStick = master.get_analog(ANALOG_RIGHT_X);

		if (abs(leftJoyStick) < 3)
			leftJoyStick = 0;
		if (abs(rightJoyStick) < 3)
			rightJoyStick = 0;

		// clang-format off
		arms::chassis::arcade(
			exponentialDrive(leftJoyStick * (double)100 / 127),
			exponentialDrive(rightJoyStick * (double)100 / 127)
		);
		// clang-format on

		/* Exponential Bypass Toggle */
		if (master.get_digital_new_press(DIGITAL_LEFT))
			bypass = !bypass;

		/* Autonomous Manual Trigger
		 * If the robot is not connected to competition control
		 * and the button is pressed, the robot will begin the
		 * autonomous routine to allow for easy testing.
		 */
		if (master.get_digital_new_press(DIGITAL_X) && !pros::competition::is_connected())
			autonomous();

		/* Game Related Subsystems
		 * Controls for game specific functions
		 */
		// Frisbee Shooter Flywheel
		flywheelState = master.get_digital_new_press(DIGITAL_L2);
		flywheelThirdPosState = master.get_digital_new_press(DIGITAL_L1);

		if (flywheelState == true) {
			fwON = !fwON;
			deFenestration::Flywheel::FwVelocitySet(210, 1);
		}
		if (flywheelThirdPosState == true) {
			fwON = !fwON;
			deFenestration::Flywheel::FwVelocitySet(120, 0.5);
		}

		if (fwON == false) {
			deFenestration::Flywheel::FwVelocitySet(0, 0.0);
		}

		// Frisbee Conveyor / Intake
		if (master.get_digital(DIGITAL_R1)) {
			conveyor.move_velocity(200);
		} else if (master.get_digital(DIGITAL_Y)) {
			conveyor.move_velocity(-200);
		} else {
			conveyor.move_velocity(0);
		}

		// Indexer Piston Toggle
		// Might switch to a single press later
		// pistonState = master.get_digital(DIGITAL_R2);
		// if (pistonState == true && prevPistonState == false) {
		// 	indexState = !indexState;
		// 	indexer.set_value(indexState);
		// }
		// prevPistonState = pistonState;

		if (master.get_digital_new_press(DIGITAL_R2)) {
			indexState = !indexState;
			indexer.set_value(indexState);

			// delay 50 ms then retract
			pros::delay(50);
			indexState = !indexState;
			indexer.set_value(indexState);
		}

		// Endgame Piston
		EpistonState = master.get_digital_new_press(DIGITAL_RIGHT);
		if (EpistonState == true && EprevPistonState == false) {
			endgameState = !endgameState;
			endgame.set_value(endgameState);
		}
		EprevPistonState = EpistonState;

		/* Brake System
		 * The brake system is a safety feature that prevents the robot from being
		 * punished by other robots. Uses basic logic for toggle button
		 */
		if (master.get_digital_new_press(DIGITAL_B) == 1)
			pbrake = !pbrake;
		prosBrake(pbrake);

		// Lastly, delay
		pros::delay(2);
	}
}
