/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen(lv_ui *ui)
{
    //Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_volume
    ui->screen_volume = lv_slider_create(ui->screen);
    lv_slider_set_range(ui->screen_volume, 0, 100);
    lv_slider_set_mode(ui->screen_volume, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_volume, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_volume, 57, 198);
    lv_obj_set_size(ui->screen_volume, 225, 12);

    //Write style for screen_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_volume, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_volume, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_volume, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_volume, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_volume, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_volume, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_volume, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_volume, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_volume, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_volume, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_volume, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_volume, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_volume, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_volume, 8, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_pre_bt
    ui->screen_pre_bt = lv_btn_create(ui->screen);
    ui->screen_pre_bt_label = lv_label_create(ui->screen_pre_bt);
    lv_label_set_text(ui->screen_pre_bt_label, "上一首");
    lv_label_set_long_mode(ui->screen_pre_bt_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_pre_bt_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_pre_bt, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_pre_bt_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_pre_bt, 23, 123);
    lv_obj_set_size(ui->screen_pre_bt, 55, 30);
    lv_obj_add_flag(ui->screen_pre_bt, LV_OBJ_FLAG_CLICKABLE);

    //Write style for screen_pre_bt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_pre_bt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_pre_bt, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_pre_bt, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_pre_bt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_pre_bt, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_pre_bt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_pre_bt, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_pre_bt, &lv_font_sanjichip_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_pre_bt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_pre_bt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_next_bt
    ui->screen_next_bt = lv_btn_create(ui->screen);
    ui->screen_next_bt_label = lv_label_create(ui->screen_next_bt);
    lv_label_set_text(ui->screen_next_bt_label, "下一首");
    lv_label_set_long_mode(ui->screen_next_bt_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_next_bt_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_next_bt, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_next_bt_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_next_bt, 244, 123);
    lv_obj_set_size(ui->screen_next_bt, 57, 31);
    lv_obj_add_flag(ui->screen_next_bt, LV_OBJ_FLAG_CLICKABLE);

    //Write style for screen_next_bt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_next_bt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_next_bt, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_next_bt, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_next_bt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_next_bt, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_next_bt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_next_bt, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_next_bt, &lv_font_sanjichip_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_next_bt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_next_bt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_music_name
    ui->screen_music_name = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_music_name, "Scanning Files...");
    lv_label_set_long_mode(ui->screen_music_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_music_name, 78, 15);
    lv_obj_set_size(ui->screen_music_name, 183, 22);

    //Write style for screen_music_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_music_name, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_music_name, &lv_font_sanjichip_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_music_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_music_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_music_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_stop_bt
    ui->screen_stop_bt = lv_btn_create(ui->screen);
    ui->screen_stop_bt_label = lv_label_create(ui->screen_stop_bt);
    lv_label_set_text(ui->screen_stop_bt_label, "暂停");
    lv_label_set_long_mode(ui->screen_stop_bt_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_stop_bt_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_stop_bt, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_stop_bt_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_stop_bt, 132, 116);
    lv_obj_set_size(ui->screen_stop_bt, 71, 38);
    lv_obj_add_flag(ui->screen_stop_bt, LV_OBJ_FLAG_CHECKABLE);

    //Write style for screen_stop_bt, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_stop_bt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_stop_bt, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_stop_bt, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_stop_bt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_stop_bt, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_stop_bt, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_stop_bt, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_stop_bt, &lv_font_sanjichip_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_stop_bt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_stop_bt, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_music_list
    ui->screen_music_list = lv_dropdown_create(ui->screen);
    lv_dropdown_set_options(ui->screen_music_list, "我们之间的回忆");
    lv_obj_set_pos(ui->screen_music_list, 78, 55);
    lv_obj_set_size(ui->screen_music_list, 171, 30);

    //Write style for screen_music_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_music_list, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_music_list, &lv_font_sanjichip_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_music_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_music_list, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_music_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_music_list, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_music_list, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_music_list, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_music_list, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_music_list, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_music_list, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_music_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_music_list, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_music_list, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_screen_music_list_extra_list_selected_checked
    static lv_style_t style_screen_music_list_extra_list_selected_checked;
    ui_init_style(&style_screen_music_list_extra_list_selected_checked);

    lv_style_set_border_width(&style_screen_music_list_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_screen_music_list_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_screen_music_list_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_music_list_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_music_list_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_screen_music_list_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_screen_music_list_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_screen_music_list_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_music_list), &style_screen_music_list_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_screen_music_list_extra_list_main_default
    static lv_style_t style_screen_music_list_extra_list_main_default;
    ui_init_style(&style_screen_music_list_extra_list_main_default);

    lv_style_set_max_height(&style_screen_music_list_extra_list_main_default, 90);
    lv_style_set_text_color(&style_screen_music_list_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_music_list_extra_list_main_default, &lv_font_sanjichip_12);
    lv_style_set_text_opa(&style_screen_music_list_extra_list_main_default, 255);
    lv_style_set_border_width(&style_screen_music_list_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_screen_music_list_extra_list_main_default, 255);
    lv_style_set_border_color(&style_screen_music_list_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_music_list_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_music_list_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_screen_music_list_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_screen_music_list_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_music_list_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_music_list), &style_screen_music_list_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_music_list_extra_list_scrollbar_default
    static lv_style_t style_screen_music_list_extra_list_scrollbar_default;
    ui_init_style(&style_screen_music_list_extra_list_scrollbar_default);

    lv_style_set_radius(&style_screen_music_list_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_music_list_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_music_list_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_screen_music_list_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_music_list), &style_screen_music_list_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //The custom code of screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen);

    //Init events for screen.
    events_init_screen(ui);
}
