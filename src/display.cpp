/*
 * Copyright (c) 2019-2021, Michael Gummere.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"

// #include "gif-pros/gifclass.hpp"

// extern Gif gif;

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

	lv_obj_t *obj = lv_obj_create(lv_scr_act(), NULL);
	// lv_obj_set_size(obj, 282, 209);
	lv_obj_set_size(obj, 50, 40);
	lv_obj_set_style(obj, &lv_style_transp);
	lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);

	// Gif *gif = new Gif("/usd/image.gif", obj);

	// styles
	static lv_style_t title_style;
	lv_style_copy(&title_style, &lv_style_plain);
	title_style.text.font = &lv_font_dejavu_20;
	title_style.text.color = LV_COLOR_GREEN;

	static lv_style_t char_block_style;
	lv_style_copy(&char_block_style, &lv_style_plain);
	char_block_style.text.font = &lv_font_dejavu_20;
	char_block_style.text.color = LV_COLOR_BLACK;

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
