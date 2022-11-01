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
#include "gif-pros/gifclass.hpp"

/* Flywheel */
// Update inteval (in mS) for the flywheel control loop
#define FW_LOOP_SPEED 20

// Maximum power we want to send to the flywheel motors
#define FW_MAX_POWER 200

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
/** @brief      Get the flywheen motor encoder count                           */
/*-----------------------------------------------------------------------------*/
double FwMotorEncoderGet() {
	return flywheel.getPosition();
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
void FwCalculateSpeed() {
	// int delta_ms;
	// int delta_enc;

	// // Get current encoder value
	// encoder_counts = FwMotorEncoderGet();

	// // This is just used so we don't need to know how often we are called
	// // how many mS since we were last here
	// delta_ms = pros::millis() - nSysTime_last;
	// nSysTime_last = pros::millis();

	// // Change in encoder count
	// delta_enc = (encoder_counts - encoder_counts_last);

	// // save last position
	// encoder_counts_last = encoder_counts;

	// Calculate velocity in rpm
	motor_velocity = flywheel.getActualVelocity();
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

	while (1) {
		// Calculate velocity
		FwCalculateSpeed();

		// Do the velocity TBH calculations
		FwControlUpdateVelocityTbh();

		// Scale drive into the range the motors need
		motor_drive = (drive * FW_MAX_POWER) + 0.5;

		// Final Limit of motor values - don't really need this
		if (motor_drive > 200)
			motor_drive = 200;
		if (motor_drive < -200)
			motor_drive = -200;

		// and finally set the motor control value
		FwMotorSet(motor_drive);

		// Run at somewhere between 20 and 50mS
		pros::delay(FW_LOOP_SPEED);
	}
}

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

/* Game System Controls */
bool flywheelState = false;

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
	leftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	rightMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

	pros::Task fwTask(FwControlTask);
	FwVelocitySet(0, 0.0);

	arms::selector::destroy();

	lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj, 480, 240);
	lv_obj_set_style(obj, &lv_style_transp); // make the container invisible
	lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);

	Gif gif("/usd/mygif.gif", obj);

	// Run Loop
	while (true) {
		/* Steering
		 * Handled by ARMS
		 * H-Drive is controlled by the X-axis on the left stick
		 */
		// clang-format off
		arms::chassis::arcade(
			master.get_analog(ANALOG_LEFT_Y) * (double)100 / 127,
		    master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127
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

		// Disk Launcher
		flywheelState = master.get_digital_new_press(DIGITAL_L2);
		flywheel.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

		if (flywheelState == true) {
			FwVelocitySet(96, 0.2);
		} else if (flywheelState == false) {
			FwVelocitySet(0, 0.0);
		}
		// if(flywheelState == true) {
		// 	flywheel.moveVelocity(290);
		// } else if(flywheelState == false) {
		// 	flywheel.moveVelocity(0);
		// }
		printf("Flywheel Velocity: %f\r\nFlywheel toggle: %d\r\n", flywheel.getActualVelocity(), flywheelState);

		// Disk Conveyor
		if (master.get_digital(DIGITAL_L1)) {
			conveyor.moveVelocity(200);
		} else {
			conveyor.moveVelocity(0);
		}

		/* Brake System
		 * The brake system is a safety feature that prevents the robot from being
		 * punished by other robots. Uses basic logic for toggle button
		 */
		if (master.get_digital_new_press(DIGITAL_B) == 1) {
			pbrake = !pbrake;
		}
		prosBrake(pbrake);

		// Lastly, delay
		pros::delay(2);
	}
}
