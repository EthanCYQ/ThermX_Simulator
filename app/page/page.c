#include "page.h"

lv_obj_t *screen = NULL;

#define STYLE_SHADOW_HEIGHT    10
#define STYLE_SHADOW_OPA       LV_OPA_20
#define STYLE_SHADOW_OFS_X     0
#define STYLE_SHADOW_OFS_Y     6

static lv_style_t bg_style;
static lv_style_t cont_style;

void page_style_init(void)
{
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, PAGE_BACKGROUND_COLOR);
    lv_style_set_radius(&bg_style, 0);
    lv_style_set_pad_all(&bg_style, 0);
    lv_style_set_border_width(&bg_style, 0);

    lv_style_init(&cont_style);
    lv_style_set_bg_color(&cont_style, PAGE_THEME_COLOR);
    lv_style_set_radius(&cont_style, 0);
    lv_style_set_pad_all(&cont_style, 0);
    lv_style_set_border_width(&cont_style, 0);
    lv_style_set_shadow_width(&cont_style, STYLE_SHADOW_HEIGHT);
    lv_style_set_shadow_opa(&cont_style,   STYLE_SHADOW_OPA);
    lv_style_set_shadow_ofs_x(&cont_style, STYLE_SHADOW_OFS_X);
    lv_style_set_shadow_ofs_y(&cont_style, STYLE_SHADOW_OFS_Y);

    screen = lv_obj_create(lv_scr_act());
    lv_obj_set_size(screen, LV_HOR_RES, LV_VER_RES);
    lv_obj_add_style(screen, &bg_style, LV_STATE_DEFAULT);
}

#define STATUS_BAR_HEIGHT  20

static lv_obj_t *status_bar = NULL;
static lv_obj_t *sb_time_label = NULL;

void page_status_bar_init(void)
{
    status_bar = lv_obj_create(screen);
    lv_obj_set_size(status_bar, LV_HOR_RES, STATUS_BAR_HEIGHT);
    lv_obj_add_style(status_bar, &cont_style, LV_STATE_DEFAULT);
    lv_obj_set_align(status_bar, LV_ALIGN_TOP_MID);

    sb_time_label = lv_label_create(status_bar);
    lv_label_set_text(sb_time_label, "19:49");
    lv_obj_set_align(sb_time_label, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(sb_time_label, &OPPOSans_16px, 0);
}
