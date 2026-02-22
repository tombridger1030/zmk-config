/*
 * Custom OLED status screen for Lily58 Pro
 *
 * Central (left):  Animated owl (32x32) + layer name + BT profile
 * Peripheral (right): Animated crescent moon (32x32, centered)
 */

#include <zmk/display/status_screen.h>
#include <lvgl.h>

#include "widgets/owl.h"
#include "widgets/moon.h"

#if IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL) || !IS_ENABLED(CONFIG_ZMK_SPLIT)

/* --- Central half: Owl + status text --- */

#include <zmk/display/widgets/layer_status.h>
#include <zmk/display/widgets/output_status.h>

static struct zmk_widget_layer_status layer_status_widget;
static struct zmk_widget_output_status output_status_widget;

static const lv_img_dsc_t *owl_frames[5] = {
    &owl_frame_open,
    &owl_frame_open,    /* hold open longer */
    &owl_frame_half,
    &owl_frame_closed,
    &owl_frame_half,
};

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    /* Owl animation - left side */
    lv_obj_t *owl = lv_animimg_create(screen);
    lv_animimg_set_src(owl, (const void **)owl_frames, 5);
    lv_animimg_set_duration(owl, 4000); /* full blink cycle: 4s */
    lv_animimg_set_repeat_count(owl, LV_ANIM_REPEAT_INFINITE);
    lv_obj_align(owl, LV_ALIGN_LEFT_MID, 0, 0);
    lv_animimg_start(owl);

    /* Layer status - top right area */
    zmk_widget_layer_status_init(&layer_status_widget, screen);
    lv_obj_align(zmk_widget_layer_status_obj(&layer_status_widget),
                 LV_ALIGN_TOP_LEFT, 36, 2);

    /* Output/BT status - bottom right area */
    zmk_widget_output_status_init(&output_status_widget, screen);
    lv_obj_align(zmk_widget_output_status_obj(&output_status_widget),
                 LV_ALIGN_BOTTOM_LEFT, 36, -2);

    return screen;
}

#else

/* --- Peripheral half: Moon animation centered --- */

static const lv_img_dsc_t *moon_frames[3] = {
    &moon_frame_1,
    &moon_frame_2,
    &moon_frame_3,
};

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    lv_obj_t *moon = lv_animimg_create(screen);
    lv_animimg_set_src(moon, (const void **)moon_frames, 3);
    lv_animimg_set_duration(moon, 4500); /* 1.5s per frame */
    lv_animimg_set_repeat_count(moon, LV_ANIM_REPEAT_INFINITE);
    lv_obj_align(moon, LV_ALIGN_CENTER, 0, 0);
    lv_animimg_start(moon);

    return screen;
}

#endif
