#include "page_manager.h"
#include "page_startup.h"

static page_base_t *page_startup = NULL;

static void page_startup_init(void)
{

}

static void page_startup_load(void)
{

}

static void page_startup_freeze(void)
{

}

static void page_startup_destroy(void)
{

}

bool page_startup_register(void)
{
    if (page_startup != NULL) {
        return false;
    }
    page_startup = (page_base_t *)malloc(sizeof(page_base_t));
    page_startup->page_name = "page_startup";
    page_startup->page_state = PAGE_STATE_IDLE;
    page_startup->page_init = page_startup_init;
    page_startup->page_load = page_startup_load;
    page_startup->page_freeze = page_startup_freeze;
    page_startup->page_destroy = page_startup_destroy;
    
    pm_register_page(page_startup);
    return true;
}

bool page_startup_unregister(void)
{
    if (page_startup == NULL) {
        return false;
    }
    pm_unregister_page(page_startup);
    free(page_startup);
    page_startup = NULL;
    return true;
}