/*
 * Copyright (c) 2019-2021, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"

// Magic beyond my understanding of LVGL
void display()
{
	static lv_style_t background_style;
	lv_style_copy(&background_style, &lv_style_plain);
	background_style.body.main_color = LV_COLOR_BLACK;
	background_style.body.grad_color = LV_COLOR_BLACK;

	lv_obj_t *scr = lv_obj_create(NULL, NULL);
	lv_obj_set_style(scr, &background_style);
	lv_scr_load(scr);

	// styles
	static lv_style_t title_style;
	lv_style_copy(&title_style, &lv_style_plain);
	title_style.text.font = &lv_font_dejavu_20;
	title_style.text.color = LV_COLOR_GREEN;

	// text
	lv_obj_t *display_title = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title, &title_style);
	lv_label_set_text(display_title, "GREETINGS PROFESSOR FALKEN.");
	lv_obj_align(display_title, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

	lv_obj_t *display_title2 = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title2, &title_style);
	lv_label_set_text(display_title2, "SHALL WE PLAY A GAME?");
	lv_obj_align(display_title2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 35);
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
		auto txt = std::to_string(iter);
		lv_label_set_text(display_title3, std::string("IMU calibrating... ").append(txt).append(std::string(" ms)")));
		iter += 10;
		pros::delay(10);
	}

	if (imu_sensor.is_calibrating() == false)
	{
		std::string txt = std::to_string(iter - time);
		lv_label_set_text(display_title3, std::string("IMU calibrating... ").c_str() + txt.c_str() + std::string(" ms)").c_str());
	}
}

// Runs the display update code
void displayUpdate()
{
	/*Describe the color for the needles*/
	static lv_color_t needle_colors[1];
	needle_colors[0] = LV_COLOR_RED;

	/*Create a gauge*/
	lv_obj_t *gauge1 = lv_gauge_create(lv_scr_act(), NULL);
	lv_gauge_set_needle_count(gauge1, 1, needle_colors);
	lv_obj_set_size(gauge1, 200, 200);
	lv_obj_align(gauge1, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_gauge_set_range(gauge1, 0, 10);
	lv_gauge_set_critical_value(gauge1, 4.5);

	while (true)
	{
		pros::c::imu_accel_s_t accel = imu_sensor.get_accel();
		lv_gauge_set_value(gauge1, 0, accel.y);
	}
}
