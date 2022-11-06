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
	lv_label_set_text(displayTitle, "GREETINGS PROFESSOR FALKEN.");
	lv_obj_align(displayTitle, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

	lv_obj_t* displayTitle2 = lv_label_create(scr, NULL);
	lv_obj_set_style(displayTitle2, &titleStyle);
	lv_label_set_text(displayTitle2, "SHALL WE PLAY A GAME?");
	lv_obj_align(displayTitle2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 35);

	// Flywheel Telemetry Display
	lv_obj_t* statsDisplay = lv_label_create(scr, NULL);
	lv_obj_set_style(statsDisplay, &titleStyle);
	lv_obj_align(statsDisplay, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 85);

	// lv_obj_t* odomDisplay = lv_label_create(scr, NULL);
	// lv_obj_set_style(odomDisplay, &titleStyle);
	// lv_obj_align(odomDisplay, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 160);

	// lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
	// lv_obj_set_size(obj, 480, 240);
	// lv_obj_set_style(obj, &lv_style_transp); // make the container invisible
	// lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);

	// Gif gif("/usd/mygif.gif", obj);

	// deFenestration Stats Display
	// Runs every 20ms
	while(true) {
		std::stringstream stats;
		stats << "Flywheel Info:\n" <<  "  Flywheel Temp: " << flywheel.getTemperature() << "\n  Flywheel MVel: " << (flywheel.getActualVelocity()) << "\n  Flywheel OVel: " << (flywheel.getActualVelocity() * 16.3333333334) << "\n  Flywheel Efficiency: " << flywheel.getEfficiency(); //<< " Flywheel CDraw: " << flywheel.getCurrentDraw();

		std::stringstream odomStats;
		// odomStats << "Odom X/Y:(" << arms::odom::getPosition().x << "," << arms::odom::getPosition().y << ") Odom Angle: " << arms::odom::getHeading();
		// odomStats << "Disabled.";

		// lv_label_set_text(odomDisplay, odomStats.str().c_str());
		lv_label_set_text(statsDisplay, stats.str().c_str());
		pros::delay(50);
	}
}
