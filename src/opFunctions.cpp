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

	if(master.get_digital(DIGITAL_R2)) {
		speed = 4;
	} else speed = 2.12;

	leftMtr.move_velocity(master.get_analog(ANALOG_LEFT_Y) * speed);
	leftMtrR.move_velocity(master.get_analog(ANALOG_LEFT_Y) * speed);
	rightMtr.move_velocity(master.get_analog(ANALOG_RIGHT_Y) * speed);
	rightMtrR.move_velocity(master.get_analog(ANALOG_RIGHT_Y) * speed);

	// static lv_style_t title_style;
	// lv_style_copy(&title_style, &lv_style_plain);
	// title_style.text.font = &lv_font_dejavu_20;
	// title_style.text.color = LV_COLOR_GREEN;

	// lv_obj_t *display_title3 = lv_label_create(scr, NULL);
	// lv_obj_set_style(display_title3, &title_style);
	// lv_label_set_text(display_title3, "SHALL WE PLAY A GAME?");
	// lv_obj_align(display_title3, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 60);
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
