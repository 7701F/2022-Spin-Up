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
#include "autoncontrol.h"

#include <sstream>

lv_obj_t *scr = lv_obj_create(NULL, NULL);
lv_obj_t *display_title4 = lv_label_create(scr, NULL);
lv_obj_t *alabel = lv_label_create(scr, NULL);

static lv_res_t btn_click_action(lv_obj_t *btn)
{
	uint8_t id = lv_obj_get_free_num(btn);
	if (auton == true)
	{
		auton = false;
		lv_label_set_text(alabel, "Auton Selected: Game Auton");
	}
	else
	{
		auton = true;
		lv_label_set_text(alabel, "Auton Selected: Skills Auton");
	}

	/* The button is released.
	 * Make something here */
	return LV_RES_OK; /*Return OK if the button is not deleted*/
}

// Magic beyond my understanding of LVGL
void display()
{
	// Background Style
	static lv_style_t background_style;
	lv_style_copy(&background_style, &lv_style_plain);
	background_style.body.main_color = LV_COLOR_BLACK;
	background_style.body.grad_color = LV_COLOR_BLACK;

	lv_obj_set_style(scr, &background_style);
	lv_scr_load(scr);

	// styles
	static lv_style_t title_style;
	lv_style_copy(&title_style, &lv_style_plain);
	title_style.text.font = &lv_font_dejavu_20;
	title_style.text.color = LV_COLOR_GREEN;

	// junk
	lv_obj_set_style(display_title4, &title_style);
	lv_obj_align(display_title4, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 110);

	// text
	lv_obj_t *display_title = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title, &title_style);
	lv_label_set_text(display_title, "GREETINGS PROFESSOR FALKEN.");
	lv_obj_align(display_title, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

	lv_obj_t *display_title2 = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title2, &title_style);
	lv_label_set_text(display_title2, "SHALL WE PLAY A GAME?");
	lv_obj_align(display_title2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 35);

	// Button Junk

	/*Create a title label*/
	lv_label_set_text(alabel, "Auton Selected: Game Auton");
	lv_obj_align(alabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 135);

	/*Create a normal button*/
	lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
	lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_LEFT, 40, 160);
	lv_obj_set_free_num(btn1, 1);
	/*Set a unique number for the button*/
	lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);
	/*Add a label to the button*/
	lv_obj_t *ablabel = lv_label_create(btn1, NULL);
	lv_label_set_text(ablabel, "Auton Switch");

	lv_obj_set_style(btn1, &title_style);
	lv_obj_set_style(alabel, &title_style);
}

// IMU Status Shenanigans
void imuDisplay()
{
	// styles
	static lv_style_t title_style;
	lv_style_copy(&title_style, &lv_style_plain);
	title_style.text.font = &lv_font_dejavu_20;
	title_style.text.color = LV_COLOR_GREEN;
	lv_obj_t *display_title3 = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title3, &title_style);
	lv_label_set_text(display_title3, "IMU STATUS: UNINITIALIZED");
	lv_obj_align(display_title3, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 85);
	// should print about 2000 ms

	int time = pros::millis();
	int iter = 0;
	while (imu_sensor.is_calibrating())
	{
		// printf();
		std::ostringstream ss;
		ss << "IMU calibrating... (" << iter << " ms)";
		lv_label_set_text(display_title3, ss.str().c_str());
		iter += 10;
		pros::delay(10);
	}

	std::ostringstream ss;
	ss << "IMU calibrated: (" << iter - time << " ms)";
	lv_label_set_text(display_title3, ss.str().c_str());
}

void displayUpdate(void *param)
{
	std::ostringstream ss;
	ss << "Speed: " << param << " ";
	lv_label_set_text(display_title4, ss.str().c_str());
}
