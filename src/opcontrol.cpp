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
#include "main.h"

/* Honestly my stupidest moment, it stops the robot by driving the motor opposite direction of the current velocity */
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_RIGHT_X) == 0 && master.get_analog(ANALOG_LEFT_X) == 0) {
			if (leftMotors.getActualVelocity() != 0 || rightMotors.getActualVelocity() != 0) {
				leftMotors.moveVelocity(leftMotors.getActualVelocity() * -2);
				rightMotors.moveVelocity(rightMotors.getActualVelocity() * -2);
				pros::delay(2);
			}
		}
	}
}

/* Smart boy motor brake solution */
void prosBrake(bool pbrake) {
	if (pbrake == true) {
		if (rightMotors.getBrakeMode() != okapi::AbstractMotor::brakeMode::hold) {
			leftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			rightMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
		}
	} else if (pbrake == false) {
		if (rightMotors.getBrakeMode() != okapi::AbstractMotor::brakeMode::coast) {
			leftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			rightMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
		}
	}
}

/* Flywheel vars */
// Update inteval (in mS) for the flywheel control loop
#define FW_LOOP_SPEED 20

// Maximum power we want to send to the flywheel motors
#define FW_MAX_POWER 210

// encoder tick per revolution
float ticks_per_rev; ///< encoder ticks per revolution

// Encoder
long encoder_counts;      ///< current encoder count
long encoder_counts_last; ///< current encoder count

// velocity measurement
float motor_velocity; ///< current velocity in rpm
long nSysTime_last;   ///< Time of last velocity calculation

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

namespace deFenestration::Flywheel {

/*-----------------------------------------------------------------------------*/
/** @brief      Set the flywheen motors                                        */
/** @param[in]  value motor control value                                      */
/*-----------------------------------------------------------------------------*/
void FwMotorSet(int value) {
	int x;
	x = (value * 12000) / 200;
	flywheel.moveVoltage(x);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Set the controller position                                    */
/** @param[in]  desired velocity                                               */
/** @param[in]  predicted_drive estimated open loop motor drive                */
/*-----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------*/
/** @brief      Calculate the current flywheel motor velocity                  */
/*-----------------------------------------------------------------------------*/
float FwCalculateSpeed() {
	encoder_counts = flywheel.getPosition();

	motor_velocity = (encoder_counts - encoder_counts_last) / 20.0;

	encoder_counts_last = encoder_counts;
	// motor_velocity = flywheel.getActualVelocity();

	return motor_velocity;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Update the velocity tbh controller variables                   */
/*-----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------*/
/** @brief     Task to control the velocity of the flywheel                    */
/*-----------------------------------------------------------------------------*/
void FwControlTask() {
	// Set the gain
	gain = 0.00025;

	// We are using Speed geared motors
	// Set the encoder ticks per revolution
	ticks_per_rev = 20;

	int count;
	while (1) {
		// Calculate velocity
		deFenestration::Flywheel::FwCalculateSpeed();
		// motor_velocity = flywheel.getActualVelocity();

		// Do the velocity TBH calculations
		deFenestration::Flywheel::FwControlUpdateVelocityTbh();

		// Scale drive into the range the motors need
		motor_drive = (drive * FW_MAX_POWER) + 0.5;

		// Final Limit of motor values - don't really need this
		if (motor_drive > 200)
			motor_drive = 200;
		if (motor_drive < -200)
			motor_drive = -200;

		// and finally set the motor control value
		deFenestration::Flywheel::FwMotorSet(motor_drive);

		// Run at somewhere between 20 and 50mS
		count++;
		count %= 150;
		pros::delay(FW_LOOP_SPEED);
	}
}

} // namespace deFenestration::Flywheel

/* Game System Controls */
bool flywheelState = false;
bool flywheelThirdPosState = false;
bool fwON = false;

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
int count;
void opcontrol() {
	arms::odom::reset({{0, 24}});
	leftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	rightMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

	deFenestration::Flywheel::FwVelocitySet(0, 0.0);

	if (deFenestration::config::showScreen == true) {
		arms::selector::destroy();
		pros::Task displayTask(display);
	}

	// Run Loop
	while (true) {
		/* Steering
		 * Handled by ARMS
		 */
		// clang-format off
		arms::chassis::arcade(
			master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		    master.get_analog(ANALOG_RIGHT_X) * (double)-100 / 127
		);
		// clang-format on

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
		// Disk Flywheel
		flywheelState = master.get_digital_new_press(DIGITAL_L2);
		if (flywheelState == true) {
			fwON = !fwON;
			deFenestration::Flywheel::FwVelocitySet(200, 1.55);
		}
		flywheelThirdPosState = master.get_digital_new_press(DIGITAL_L1);
		if (flywheelThirdPosState == true) {
			fwON = !fwON;
			deFenestration::Flywheel::FwVelocitySet(120, 0.5);
		}

		if (fwON == false) {
			deFenestration::Flywheel::FwVelocitySet(0, 0.0);
		}

		// Disk Conveyor
		if (master.get_digital(DIGITAL_R1)) {
			conveyor.moveVelocity(200);
		} else if (master.get_digital(DIGITAL_R2)) {
			conveyor.moveVelocity(-200);
		} else {
			conveyor.moveVelocity(0);
		}

		// Roller
		if (master.get_digital(DIGITAL_A)) {
			roller.moveVelocity(200);
		} else {
			roller.moveVelocity(0);
		}

		/* Brake System
		 * The brake system is a safety feature that prevents the robot from being
		 * punished by other robots. Uses basic logic for toggle button
		 */
		if (master.get_digital_new_press(DIGITAL_B) == 1)
			pbrake = !pbrake;
		prosBrake(pbrake);

		if (deFenestration::config::debug == true) {
			if (count % 500)
				printf("Flywheel on: %i\n", fwON);
			if (count % 1000)
				printf("Flywheel MVel: %f & Flywheel OVel: %f \n", flywheel.getActualVelocity(), flywheel.getActualVelocity() * 16.3333);
			if (count % 1500)
				printf("Commanded Velocity: %ld\n", motor_drive);
			if (count % 2000)
				printf("Flywheel CDraw: %d\n Flywheel Commanded Current: %f\n", flywheel.getCurrentDraw(),
				       (motor_velocity * 12000) / 200);
		}

		// Lastly, delay
		count++;
		pros::delay(2);
	}
}
