#include "page.h"
#include "page_manager.h"

typedef struct page_pool_node {
    page_t *page_ptr;
    struct page_pool_node *next;
} page_pool_t;

static page_pool_t *page_pool = NULL;

void pm_init(void)
{    
}

static bool page_pool_add(page_t *page)
{
    page_pool_t *node = (page_pool_t *)malloc(sizeof(page_pool_t));
    if (node == NULL) {
        return false;
    }
    node->page_ptr = page;
    node->next = NULL;
    if (page_pool == NULL) {
        page_pool = node;
    } else {
        page_pool_t *ptr = page_pool;
        while (ptr->next != NULL) ptr = ptr->next;
        ptr->next = node;
    }
    return true;
}

static page_t *page_pool_get(char *name)
{
    page_pool_t *ptr = page_pool;
    while (ptr != NULL) {
        if (strcmp(ptr->page_ptr->page_name, name) == 0) {
            return ptr->page_ptr;
        } else {
            ptr = ptr->next;
        }
    }
    return NULL;
}

bool pm_register_page(page_t *page)
{
    return page_pool_add(page);
}

void pm_switch_page(char *page_name)
{

}
