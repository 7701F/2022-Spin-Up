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

// Honestly my stupidest moment, it stops the robot by driving the motor
// opposite direction of the current velocity
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_LEFT_Y) == 0 &&
		    master.get_analog(ANALOG_RIGHT_X) == 0) {
			if (leftMtr.get_actual_velocity() != 0 ||
			    rightMtr.get_actual_velocity() != 0 ||
			    leftMtrR.get_actual_velocity() != 0 ||
			    rightMtrR.get_actual_velocity() != 0) {
				leftMtr.move_velocity(leftMtr.get_actual_velocity() * -.1);
				rightMtr.move_velocity(rightMtr.get_actual_velocity() * -.1);
				leftMtrR.move_velocity(leftMtrR.get_actual_velocity() * -.1);
				rightMtrR.move_velocity(rightMtrR.get_actual_velocity() * -.1);
			}
		}
	}
}

// Smart boy motor brake solution
void motorBrake(bool pbrake) {
	if (pbrake == true) {
		if (arms::chassis::leftMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::hold || arms::chassis::rightMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::hold) {
			arms::chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			printf("BRAKE TOGGLED: HOLD\n");
		}
	} else if (pbrake == false) {
		if (arms::chassis::leftMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::coast || arms::chassis::rightMotors->getBrakeMode() != okapi::AbstractMotor::brakeMode::coast) {
			arms::chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			printf("BRAKE TOGGLED: COAST\n");
		}
	}
}

int liftSpeed;
// Combined Claw, Lift, and Winch control function
void gameSystemControls() {
		// Lift Controls
		// Analog Lift Controls
		// liftSpeed = (fabs(master.get_analog(ANALOG_RIGHT_Y)) > 50 ? master.get_analog(ANALOG_RIGHT_Y) : 0);

		// Digital Lift Controls
		if (master.get_digital(DIGITAL_L1) == 1) {
			liftSpeed = 127;
		} else if (master.get_digital(DIGITAL_L2) == 1) {
			liftSpeed = -127;
		} else {
			liftSpeed = 0;
		}

		if(fabs(liftSpeed) >= 50 && liftMotors.getPosition() > 0) {
			liftMotors.moveVelocity(liftSpeed * (double)100 / 127);
		} else if(liftSpeed == 0){
			liftMotors.moveVelocity(0);
		} else if (liftMotors.getPosition() < 0) {
			liftMotors.moveAbsolute(11, 10);
		}

		// Claw
		if (master.get_digital(DIGITAL_R1) == 1) {
			clawM.move_velocity(50);
		} else if (master.get_digital(DIGITAL_R2) == 1) {
			clawM.move_velocity(-50);
		} else {
			clawM.move_velocity(0);
		}

		// Winch Control
		if (master.get_digital(DIGITAL_UP) == 1) {
			winchM.move_velocity(100);
		} else if (master.get_digital(DIGITAL_DOWN) == 1) {
			winchM.move_velocity(-100);
		} else {
			winchM.move_velocity(0);
		}
}
