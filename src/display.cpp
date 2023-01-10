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

lv_obj_t* scr = lv_obj_create(NULL, NULL);

// Magic beyond my understanding of LVGL
namespace deFenestration {
void display() {
	// Background Style
	static lv_style_t backgroundStyle;
	lv_style_copy(&backgroundStyle, &lv_style_plain);
	backgroundStyle.body.main_color = LV_COLOR_BLACK;
	backgroundStyle.body.grad_color = LV_COLOR_BLACK;

	lv_obj_set_style(scr, &backgroundStyle);
	lv_scr_load(scr);

	// styles
	static lv_style_t titleStyle;
	lv_style_copy(&titleStyle, &lv_style_plain);
	titleStyle.text.font = &lv_font_dejavu_20;
	titleStyle.text.color = LV_COLOR_GREEN;

	// Title
	lv_obj_t* displayTitle = lv_label_create(scr, NULL);
	lv_obj_set_style(displayTitle, &titleStyle);
	lv_label_set_text(displayTitle, "GREETINGS PROFESSOR FALKEN.\nSHALL WE PLAY A GAME?");
	lv_obj_align(displayTitle, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

	// Flywheel Telemetry Display
	lv_obj_t* statsDisplay = lv_label_create(scr, NULL);
	lv_obj_set_style(statsDisplay, &titleStyle);
	lv_obj_align(statsDisplay, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 85);

	// deFenestration Stats Display
	// Runs every 50ms
	// while (true) {
	// 	std::stringstream stats;
	// 	stats << "Flywheel Info:\n"
	// 	      << "  Flywheel Temp: " << fw.get_temperature()
	// 	      << "\n  Flywheel MVel: " << (motor_velocity)
	// 	      << "\n  Flywheel OVel: " << (motor_velocity * 16.3333333334)
	// 	      << "\n  Flywheel Efficiency: " << fw.get_efficiency();

	// 	lv_label_set_text(statsDisplay, stats.str().c_str());

	// 	// Lastly, delay
	// 	pros::delay(50);
	// }
}

void destroy() {
	lv_obj_del(scr);
}

} // namespace deFenestration
