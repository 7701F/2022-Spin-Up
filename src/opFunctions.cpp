/*
 * Copyright (c) 2019-2021, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

std::int32_t speed;

void tankDrive()
{
	// leftMtr.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_Y));
	// leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_Y));
	// rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
	// rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));

	if (master.get_digital(DIGITAL_R2) == true)
	{
		speed = 1;
	}
	else
		speed = 1.5;

	leftMtr.move(master.get_analog(ANALOG_LEFT_Y) * speed);
	leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) * speed);
	rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) * speed);
	rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) * speed);

	// Test Copied Code
	// float axis_4 = master.get_analog(ANALOG_LEFT_X); //left side
	// float axis_3 = master.get_analog(ANALOG_LEFT_Y); //left up
	// float axis_2 = master.get_analog(ANALOG_RIGHT_Y); //right up
	// float axis_1 = master.get_analog(ANALOG_RIGHT_X); //right side

	// //tank controls
	// //x axis controls strafing
	// float f_lb = (axis_3 + (axis_4))/(2*127);
	// float f_lf = (axis_3 + (-axis_4))/(2*127);
	// float f_rb = (axis_2 + (-axis_1))/(2*127);
	// float f_rf = (axis_2 + axis_1)/(2*127);

	// leftMtr.move(f_lf);
	// leftMtrR.move(f_lb);
	// rightMtr.move(f_rf);
	// rightMtrR.move(f_rb);
}

void arcadeDrive()
{
	int forward_backward = master.get_analog(ANALOG_LEFT_Y);
	int left_right = master.get_analog(ANALOG_RIGHT_X);

	leftMtr.move(forward_backward + left_right);
	rightMtr.move(forward_backward - left_right);
	leftMtrR.move(forward_backward + left_right);
	rightMtrR.move(forward_backward - left_right);
}

void customBrake(bool pbrake)
{
	if (pbrake == true)
	{
		if (leftMtr.get_actual_velocity() != 0)
		{
			leftMtr.move(leftMtr.get_actual_velocity() * -1);
			rightMtr.move(rightMtr.get_actual_velocity() * -1);
			leftMtrR.move(leftMtrR.get_actual_velocity() * -1);
			rightMtrR.move(rightMtrR.get_actual_velocity() * -1);
		}
	}
}

void prosBrake(bool pbrake)
{
	if (pbrake == true)
	{
		leftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		rightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		leftMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		rightMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	}
	if (pbrake == false)
	{
		leftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		rightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		leftMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		rightMtrR.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	}
}

void liftControls()
{
	if (master.get_digital(DIGITAL_L1) == 1)
	{
		// if (rightLift.get_position() > -216 || leftLift.get_position() < 217)
		// {
		rightLift.move_velocity(75);
		leftLift.move_velocity(75);
		// pros::delay(10);
		// rightLift.move_velocity(0);
		// leftLift.move_velocity(0);
		// }
		// rightLift.move_absolute(20, 200);
	}
	else if (master.get_digital(DIGITAL_L2) == 1)
	{
		// if (rightLift.get_position() > 0 || leftLift.get_position() < 0)
		// {
		rightLift.move_velocity(-75);
		leftLift.move_velocity(-75);
		// pros::delay(10);
		// rightLift.move_velocity(0);
		// leftLift.move_velocity(0);
		// }
		// rightLift.move_absolute(0, 200);
	}
	else
	{
		rightLift.move_velocity(0);
		leftLift.move_velocity(0);
	}
}
