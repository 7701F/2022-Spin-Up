/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

// Variables
int count = 0;

// Honestly my stupidest moment, it stops the robot by driving the motor opposite direction of the current
// velocity
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_LEFT_Y) == 0 || master.get_analog(ANALOG_RIGHT_X) == 0) {
			if (leftMtr.getActualVelocity() != 0 || rightMtr.getActualVelocity() != 0 ||
			    leftMtrR.getActualVelocity() != 0 || rightMtrR.getActualVelocity() != 0) {
				leftMtr.moveVelocity(leftMtr.getActualVelocity() * -2);
				rightMtr.moveVelocity(rightMtr.getActualVelocity() * -2);
				leftMtrR.moveVelocity(leftMtrR.getActualVelocity() * -2);
				rightMtrR.moveVelocity(rightMtrR.getActualVelocity() * -2);

				if (!(count % 25)) {
					// Only print every 50ms, the controller text update rate is slow
					// master.rumble(".");
				}

				count++;
				pros::delay(2);
			}
		}
	}
}

// Smart boy motor brake solution
void prosBrake(bool pbrake) {
	if (pbrake == true) {
		if (leftMtr.getBrakeMode() != okapi::AbstractMotor::brakeMode::hold) {
			leftMtr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			rightMtr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			leftMtrR.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			rightMtrR.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

			printf("BRAKE TOGGLED: HOLD\n");
		}
	} else if (pbrake == false) {
		if (leftMtr.getBrakeMode() != okapi::AbstractMotor::brakeMode::coast) {
			leftMtr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			rightMtr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			leftMtrR.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			rightMtrR.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

			printf("BRAKE TOGGLED: COAST\n");
		}
	}
}

// Combined Claw, Lift, and Winch control function
void gameSystemControls() {
	// Lift Controls
	if (master.get_digital(DIGITAL_Y) == 1) {
		// motor.move_velocity(100);
	} else if (master.get_digital(DIGITAL_A) == 1) {
		// motor.move_velocity(-100);
	} else {
		// motor.move_velocity(0);
	}
}
