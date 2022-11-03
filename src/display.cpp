/*
  Copyright (c) 2019-2022 7701F

  This software is provided 'as-is', without any express or implied warranty. In no event will
  the authors be held liable for any damages arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose, including commercial
  applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the
  original software. If you use this software in a product, an acknowledgment (see the following)
  in the product documentation is required.

  Portions Copyright (c) 2019-2022 7701F

  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
  being the original software.

  3. This notice may not be removed or altered from any source distribution.
*/

#include <sstream>

#include "7701.h"
#include "main.h"

lv_obj_t* scr = lv_obj_create(NULL, NULL);

// Magic beyond my understanding of LVGL
void display() {
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
	lv_obj_t* display_title = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title, &title_style);
	lv_label_set_text(display_title, "GREETINGS PROFESSOR FALKEN.");
	lv_obj_align(display_title, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

	lv_obj_t* display_title2 = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title2, &title_style);
	lv_label_set_text(display_title2, "SHALL WE PLAY A GAME?");
	lv_obj_align(display_title2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 35);

	std::stringstream stats;
	stats << "Flywheel Temp: " << flywheel.getTemperature() << "\n" << "Flywheel MVel: " << (flywheel.getActualVelocity()) << "\n" << "Flywheel OVel: " << (flywheel.getActualVelocity() * 16.3333) << "\n" << "Flywheel Efficiency: " << flywheel.getEfficiency() << "\n" << "Flywheel CDraw: " << flywheel.getCurrentDraw();

	lv_obj_t* statsdisplay = lv_label_create(scr, NULL);
	lv_obj_set_style(statsdisplay, &title_style);
	lv_label_set_text(statsdisplay, stats.str().c_str());
	lv_obj_align(statsdisplay, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 60);

	while(true) {
		std::stringstream stats;
		stats << "Flywheel Info:\n" <<  "Flywheel Temp: " << flywheel.getTemperature() << "\n" << "Flywheel MVel: " << (flywheel.getActualVelocity()) << "\n" << "Flywheel OVel: " << (flywheel.getActualVelocity() * 16.3333) << "\n" << "Flywheel Efficiency: " << flywheel.getEfficiency() << "\n" << "Flywheel CDraw: " << flywheel.getCurrentDraw();

		lv_label_set_text(statsdisplay, stats.str().c_str());
		pros::delay(20);
	}
}

// // IMU Status Shenanigans
// void imuDisplay() {
// 	// styles
// 	static lv_style_t title_style;
// 	lv_style_copy(&title_style, &lv_style_plain);
// 	title_style.text.font = &lv_font_dejavu_20;
// 	title_style.text.color = LV_COLOR_GREEN;
// 	lv_obj_t* display_title3 = lv_label_create(scr, NULL);
// 	lv_obj_set_style(display_title3, &title_style);
// 	lv_label_set_text(display_title3, "IMU STATUS: UNINITIALIZED");
// 	lv_obj_align(display_title3, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 85);

// 	int time = pros::millis();
// 	int iter = 0;
// 	while (imu_sensor.isCalibrating()) {
// 		// printf();
// 		std::ostringstream ss;
// 		ss << "IMU calibrating... (" << iter << " ms)";
// 		lv_label_set_text(display_title3, ss.str().c_str());
// 		iter += 10;
// 		pros::delay(1);
// 	}

// 	std::ostringstream ss;
// 	ss << "IMU calibrated: (" << iter - time << " ms)";
// 	lv_label_set_text(display_title3, ss.str().c_str());
// }
