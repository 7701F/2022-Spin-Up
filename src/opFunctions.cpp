/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"

// Honestly my stupidest moment, it stops the robot by driving the motor opposite
// direction of the current velocity.
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_LEFT_Y) == 0 && master.get_analog(ANALOG_RIGHT_X) == 0) {
			if (leftMtr.get_actual_velocity() != 0 || rightMtr.get_actual_velocity() != 0 ||
			    leftMtrR.get_actual_velocity() != 0 || rightMtrR.get_actual_velocity() != 0) {
				leftMtr.move_velocity(leftMtr.get_actual_velocity() * -.1);
				rightMtr.move_velocity(rightMtr.get_actual_velocity() * -.1);
				leftMtrR.move_velocity(leftMtrR.get_actual_velocity() * -.1);
				rightMtrR.move_velocity(rightMtrR.get_actual_velocity() * -.1);
			}
		}
	}
}

// Toggles the motor brake mode.
void motorBrake(bool pbrake) {
	if (pbrake == true) {
		if (arms::chassis::leftMotors->getBrakeMode() !=
		        okapi::AbstractMotor::brakeMode::hold ||
		    arms::chassis::rightMotors->getBrakeMode() !=
		        okapi::AbstractMotor::brakeMode::hold) {
			arms::chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
			printf("BRAKE TOGGLED: HOLD\n");
		}
	} else if (pbrake == false) {
		if (arms::chassis::leftMotors->getBrakeMode() !=
		        okapi::AbstractMotor::brakeMode::coast ||
		    arms::chassis::rightMotors->getBrakeMode() !=
		        okapi::AbstractMotor::brakeMode::coast) {
			arms::chassis::setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
			printf("BRAKE TOGGLED: COAST\n");
		}
	}
}

int liftSpeed;
bool pistonState = false;
bool prevPistonState = false;
bool mogoState = false;
bool ringState = false;
enum winchKey { startPos = 0, upPos = 1100, downPos = -2065 };
int winchState = 1;
// Combined Claw, Lift, Winch, and Ringlift control function
void gameSystemControls() {
	// Lift Controls
	if (master.get_digital(DIGITAL_L1) == 1) {
		liftSpeed = 127;
	} else if (master.get_digital(DIGITAL_L2) == 1) {
		liftSpeed = -127;
	} else {
		liftSpeed = 0;
	}

	if (fabs(liftSpeed) >= 50 && liftMotors.getPosition() > 0) {
		liftMotors.moveVelocity(liftSpeed * (double)100 / 127);
	} else if (liftSpeed == 0) {
		liftMotors.moveVelocity(0);
	} else if (liftMotors.getPosition() < 0) {
		liftMotors.moveAbsolute(11, 10);
	}

	// Claw Controls
	pistonState = master.get_digital(DIGITAL_R2);
	if (pistonState == true && prevPistonState == false) {
		mogoState = !mogoState;
		clawP.set_value(mogoState);
	}
	prevPistonState = pistonState;

	// Ring Lift Controls
	if (master.get_digital(DIGITAL_R1)) {
		ringState = !ringState;
	}

	if (ringState) {
		ringM.move_velocity(600);
	} else {
		ringM.move_velocity(0);
	}

	// Winch Automated Control
	if (master.get_digital(DIGITAL_RIGHT)) {
		winchState = winchState == 0 ? 2 : winchState == 1 ? 2 : winchState == 2 ? 1 : 0;
	}

	switch (winchState) {
		case 1:
			if (winchM.get_position() == winchKey::upPos) {
				NULL;
			} else if (winchM.get_position() == winchKey::downPos) {
				winchM.move_absolute(winchKey::upPos, 100);
			}
		case 2:
			if (winchM.get_position() == winchKey::downPos) {
				NULL;
			} else if (winchM.get_position() == winchKey::upPos) {
				winchM.move_absolute(winchKey::downPos, 100);
			}
	}
}
