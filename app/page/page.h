
typedef enum {
    PAGE_STATE_IDLE = 0,
    PAGE_STATE_READY,
    PAGE_STATE_ACTIVITY,
    PAGE_STATE_SUSPEND,
} page_state_t;

typedef struct page
{
    char *page_name;
    page_state_t page_state;

    void (*page_create)(void);
    void (*page_load)(void);
    void (*page_unload)(void);
    void (*page_free)(void);
} page_t;

