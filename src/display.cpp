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
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = LV_COLOR_WHITE;
  background_style.body.grad_color = LV_COLOR_BLACK;

  lv_obj_t *scr = lv_obj_create(NULL, NULL);
  lv_obj_set_style(scr, &background_style);
  lv_scr_load(scr);

  lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(obj, 165, 165);
  lv_obj_set_style(obj, &lv_style_transp);
  lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, -20);

  Gif* gif = new Gif ("/usd/image.gif", obj);

  // styles
  static lv_style_t title_style;
  lv_style_copy(&title_style, &lv_style_plain);
  title_style.text.font = &lv_font_dejavu_20;
  title_style.text.color = LV_COLOR_WHITE;

  // text
  lv_obj_t *display_title = lv_label_create(scr, NULL);
  lv_obj_set_style(display_title, &title_style);
  lv_label_set_text(display_title, "SNEAKY SNAKES");
  lv_obj_align(display_title, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -15);
}

