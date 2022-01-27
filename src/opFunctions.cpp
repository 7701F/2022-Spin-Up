/*
 * Copyright (c) 2019-2022, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "main.h"
#include "motors.h"
#include "pros/misc.h"
#include "pros/motors.h"

// Each stick controls a side of the wheels
void tankDrive(double speed) {
	// leftMtr.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_Y));
	// leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_Y));
	// rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
	// rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));

	// By default it multiples the anolog input by 1.5 to make it go slightly faster
	// Speed Control
	if (master.get_digital(DIGITAL_Y) == 1) {
		if (speed == 1.5) {
			speed = 1;
		} else {
			speed = 1.5;
		}
	}

	leftMtr.move(master.get_analog(ANALOG_LEFT_Y) * speed);
	leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) * speed);
	rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) * speed);
	rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) * speed);
}

// Right stick controls turning and left controls acceleration
void arcadeDrive() {
	int forward_backward = master.get_analog(ANALOG_LEFT_Y);
	int left_right = master.get_analog(ANALOG_RIGHT_X);

	leftMtr.move(forward_backward + left_right);
	leftMtrR.move(forward_backward + left_right);
	rightMtr.move(forward_backward - left_right);
	rightMtrR.move(forward_backward - left_right);
}

// Honestly my stupidest moment, it stops the robot by driving the motor opposite direction of the current velocity
void customBrake(bool pbrake) {
	if (pbrake == true) {
		if (master.get_analog(ANALOG_LEFT_Y) == 0 || master.get_analog(ANALOG_RIGHT_X) == 0) {
			if (leftMtr.get_actual_velocity() != 0 || rightMtr.get_actual_velocity() != 0 ||
					leftMtrR.get_actual_velocity() != 0 || rightMtrR.get_actual_velocity() != 0) {
				leftMtr.move_velocity(leftMtr.get_actual_velocity() * -2);
				rightMtr.move_velocity(rightMtr.get_actual_velocity() * -2);
				leftMtrR.move_velocity(leftMtrR.get_actual_velocity() * -2);
				rightMtrR.move_velocity(rightMtrR.get_actual_velocity() * -2);

				int count = 0;
				if (!(count % 25)) {
					// Only print every 50ms, the controller text update rate is slow
					master.rumble(".... .- .-. -.. . .-.");
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
		if (leftMtr.get_brake_mode() != pros::E_MOTOR_BRAKE_HOLD) {
			leftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			leftMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rightMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}
	} else if (pbrake == false) {
		if (leftMtr.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) {
			leftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			rightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			leftMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			rightMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		}
	}
}

// Combined Claw, Lift, and Winch control function
void gameSystemControls() {
	// Lift Controls
	if (master.get_digital(DIGITAL_L1) == 1) {
		rightLift.move_velocity(100);
		leftLift.move_velocity(100);
	} else if (master.get_digital(DIGITAL_L2) == 1) {
		rightLift.move_velocity(-100);
		leftLift.move_velocity(-100);
	} else {
		rightLift.move_velocity(0);
		leftLift.move_velocity(0);
	}

	// Claw Controls
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
