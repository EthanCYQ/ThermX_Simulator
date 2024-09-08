#pragma once

#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include "lvgl.h"

#define PAGE_BACKGROUND_COLOR lv_color_hex(0xDEDEDE)
#define PAGE_FONT_COLOR       lv_color_hex(0x404040)
#define PAGE_THEME_COLOR      lv_color_hex(0xFFFFFF)

LV_FONT_DECLARE(OPPOSans_13px);
LV_FONT_DECLARE(OPPOSans_16px);
LV_FONT_DECLARE(OPPOSans_20px);
LV_FONT_DECLARE(OPPOSans_30px);

typedef enum {
    PAGE_STATE_IDLE = 0,
    PAGE_STATE_INITIALIZED,
    PAGE_STATE_ACTIVE,
    PAGE_STATE_SUSPENDED,
} page_state_t;

typedef struct Page_Base
{
    char *page_name;
    page_state_t page_state;

    void (*page_init)(void);
    void (*page_load)(void);
    void (*page_freeze)(void);
    void (*page_destroy)(void);
} page_base_t;

extern lv_obj_t *screen;

void page_style_init(void);
void page_status_bar_init(void);