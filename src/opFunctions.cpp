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

void tankDrive()
{
	leftMtr.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
	rightMtr.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
	leftMtrR.move(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
	rightMtrR.move(master.get_analog(ANALOG_RIGHT_Y) + master.get_analog(ANALOG_RIGHT_Y));
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
