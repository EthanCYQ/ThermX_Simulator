#include "page_manager.h"

/*******************************************/
/* The following functions about page pool */
/*******************************************/

typedef struct page_pool_node {
    page_base_t *page_ptr;
    struct page_pool_node *next;
} page_pool_t;

static page_pool_t *page_pool = NULL;

/**
 * @brief Adds a page to the page pool
 * @param page Pointer to the page to be added
 * @return true if successful, false otherwise
 */
static bool page_pool_add(page_base_t *page)
{
    if (page_pool == NULL) {
        page_pool = (page_pool_t *)malloc(sizeof(page_pool_t));
        if (page_pool == NULL) {
            return false;
        } else {
            page_pool->next = NULL;
            page_pool->page_ptr = NULL;
        }
    }

    page_pool_t *node = (page_pool_t *)malloc(sizeof(page_pool_t));
    if (node == NULL) {
        return false;
    }
    node->page_ptr = page;
    node->next = NULL;

    page_pool_t *ptr = page_pool;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = node;

    return true;
}

/**
 * @brief Removes a page from the page pool
 * @param page Pointer to the page to be removed
 * @return true if successful, false otherwise
 */
static bool page_pool_remove(page_base_t *page)
{
    if (page_pool == NULL) {
        return false;
    }
    page_pool_t *ptr = page_pool;
    page_pool_t *next_ptr = NULL, *free_ptr = NULL;
    while (ptr->next != NULL) {
        if (strcmp(ptr->next->page_ptr->page_name, page->page_name) == 0) {
            next_ptr = ptr->next->next;
            free_ptr = ptr->next;
            break;
        } else {
            ptr = ptr->next;
        }
    }

    if ((next_ptr == NULL) && (free_ptr == NULL)) {
        return false;
    }
    ptr->next = next_ptr;
    free(free_ptr);

    return true;
}

/**
 * @brief Retrieves a page from the page pool by name
 * @param name Name of the page to retrieve
 * @return Pointer to the retrieved page, or NULL if not found
 */
static page_base_t *page_pool_get(char *name)
{
    if (page_pool == NULL) {
        return NULL;
    }
    page_pool_t *ptr = page_pool->next;
    while (ptr != NULL) {
        if (strcmp(ptr->page_ptr->page_name, name) == 0) {
            return ptr->page_ptr;
        } else {
            ptr = ptr->next;
        }
    }
    return NULL;
}

/**
 * @brief Registers a page in the page manager
 * @param page Pointer to the page to be registered
 * @return true if successful, false otherwise
 */
bool pm_register_page(page_base_t *page)
{
    return page_pool_add(page);
}

/**
 * @brief Unregisters a page from the page manager
 * @param page Pointer to the page to be unregistered
 * @return true if successful, false otherwise
 */
bool pm_unregister_page(page_base_t *page)
{
    return page_pool_remove(page);
}

/**********************************************/
/* The following functions about page switch */
/**********************************************/
/**
 * @brief Executes the appropriate action based on the current page state
 * @param page Pointer to the page to execute the action on
 */
static void page_execute_action(page_base_t *page)
{
    switch (page->page_state) {
        case PAGE_STATE_IDLE:
            page->page_init();
            page->page_state = PAGE_STATE_INITIALIZED;
            break;
        case PAGE_STATE_INITIALIZED:
            page->page_load();
            page->page_state = PAGE_STATE_ACTIVE;
            break;
        case PAGE_STATE_ACTIVE:
            page->page_freeze();
            page->page_state = PAGE_STATE_SUSPENDED;
            break;
        case PAGE_STATE_SUSPENDED:
            page->page_destroy();
            page->page_state = PAGE_STATE_IDLE;
            break;
        default:
            break;
    }   
}

/**
 * @brief Moves the page state forward
 * @param page Pointer to the page to move forward
 */
static void page_move_foward(page_base_t *page)
{
    switch (page->page_state) {
        case PAGE_STATE_IDLE:
        case PAGE_STATE_INITIALIZED:
            page_execute_action(page);
            page_move_foward(page);
        default:
            break;
    }
}

/**
 * @brief Moves the page state backward
 * @param page Pointer to the page to move backward
 */
static void page_move_backward(page_base_t *page)
{
    switch (page->page_state) {
        case PAGE_STATE_ACTIVE:
        case PAGE_STATE_SUSPENDED:
            page_execute_action(page);
            page_move_backward(page);
        default:
            break;
    }
}

static page_base_t *current_page = NULL;
static page_base_t *next_page = NULL;

/**
 * @brief Switches to a specified page
 * @param page_name Name of the page to switch to
 */
void pm_switch_page(char *page_name)
{
    if (current_page == NULL) {
        next_page = page_pool_get(page_name);
        if (next_page == NULL) {
            return;
        }
        current_page = next_page;
        page_move_foward(current_page);
        next_page = NULL;
    } else {
        if (strcmp(current_page->page_name, page_name) == 0) {
            return;
        }
        next_page = page_pool_get(page_name);
        if (next_page == NULL) {
            return;
        }
        page_move_foward(next_page);
        page_move_backward(current_page);
        current_page = next_page;
        next_page = NULL;
    }
}
