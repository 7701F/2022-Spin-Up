/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"
#include "opfunctions.h"

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
	// Brake
	// chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

	// Run Loop
	while (true) {
		// Move the steering motors
		arms::chassis::arcade(
			master.get_analog(ANALOG_LEFT_Y) * (double)100.0 / 127,
			master.get_analog(ANALOG_LEFT_X) * (double)100.0 / 127
		);
		// Comment out whichever drive type you don't want to use
		// tankDrive(speed);
		// arcadeDrive();

		// Brake System Selector
		// Uses basic logic for toggle and is able to use a custom homemade
		// brake or the PROS control for the built in motor breaks.
		if (master.get_digital_new_press(DIGITAL_A) == 1) {
			if (pbrake == true) {
				pbrake = false;
			} else {
				pbrake = true;
			}
		}

		// Winch Control
		if (master.get_digital(DIGITAL_UP) == 1) {
			winchM.move_velocity(100);
		} else if (master.get_digital(DIGITAL_DOWN) == 1) {
			winchM.move_velocity(-100);
		} else {
			winchM.move_velocity(0);
		}

		// Speed Control
		// if (master.get_digital(DIGITAL_Y) == 1) {
		// 	if (speed == 1.5) {
		// 		speed = 1;
		// 	} else {
		// 		speed = 1.5;
		// 	}
		// }

		if (master.get_digital_new_press(DIGITAL_X) == 1) {
			autonomous();
		}

		// Uncomment whichever brake/lift you want to use.
		// customBrake(pbrake);
		prosBrake(pbrake);

		// Lift Controls
		liftControls();

		// Lastly, delay
		pros::delay(1);
	}
}
