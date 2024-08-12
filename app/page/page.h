#include <string.h>
#include <stdbool.h>
#include <malloc.h>

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

