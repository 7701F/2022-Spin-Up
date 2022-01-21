/*
 * Copyright (c) 2019-2021, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"
#include <sstream>

lv_obj_t *scr = lv_obj_create(NULL, NULL);

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
		std::ostringstream ss;
		ss << "IMU calibrating... (" << iter << " ms)";
		// std::string("IMU calibrating... ").append(txt).append(std::string(" ms)"))
		lv_label_set_text(display_title3, ss.str().c_str());
		iter += 10;
		pros::delay(10);
	}

	if (imu_sensor.is_calibrating() == false)
	{
		std::ostringstream ss;
		ss << "IMU calibrated: (" << iter - time << " ms)";
		// std::string("IMU calibrated ").c_str() + txt.c_str() + std::string(" ms)").c_str()
		// std::string txt = std::to_string(iter - time);
		lv_label_set_text(display_title3, ss.str().c_str());
	}
}
