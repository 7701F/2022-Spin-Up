/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "main.h"

#include "gif-pros/gifclass.hpp"

extern Gif gif;

void display() {
	static lv_style_t background_style;
	lv_style_copy( & background_style, & lv_style_plain);
	background_style.body.main_color = LV_COLOR_WHITE;
	background_style.body.grad_color = LV_COLOR_WHITE;

	lv_obj_t * scr = lv_obj_create(NULL, NULL);
	lv_obj_set_style(scr, & background_style);
	lv_scr_load(scr);

	lv_obj_t * obj = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj, 400, 209);
	lv_obj_set_style(obj, & lv_style_transp);
	lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, -20);

	Gif * gif = new Gif("/usd/image.gif", obj);

	// styles
	static lv_style_t title_style;
	lv_style_copy( & title_style, & lv_style_plain);
	title_style.text.font = & lv_font_dejavu_20;
	title_style.text.color = LV_COLOR_BLACK;

	// text
	lv_obj_t * display_title = lv_label_create(scr, NULL);
	lv_obj_set_style(display_title, & title_style);
	lv_label_set_text(display_title, "Connection Pending...");
	lv_obj_align(display_title, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -15);

	/*Describe the color for the needles*/
	static lv_color_t needle_colors[1];
	needle_colors[0] = LV_COLOR_RED;

	/*Create a gauge*/
	lv_obj_t * gauge1 = lv_gauge_create(lv_scr_act(), NULL);
	lv_gauge_set_needle_count(gauge1, 1, needle_colors);
	lv_obj_set_size(gauge1, 200, 200);
	lv_obj_align(gauge1, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_gauge_set_range(gauge1, 0, 10);
	lv_gauge_set_critical_value(gauge1, 4.5);

	lv_gauge_set_value(gauge1, 0, leftMtr.get_voltage());

	// while (true) {
	// 	lv_label_set_text(display_title, "Connection Pending");
	// 	lv_label_set_text(display_title, "Connection Pending.");
	// 	lv_label_set_text(display_title, "Connection Pending..");
	// 	lv_label_set_text(display_title, "Connection Pending...");
	// 	pros::delay(20);
	// }
}
