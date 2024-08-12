#include "page.h"

bool pm_register_page(page_base_t *page);
bool pm_unregister_page(page_base_t *page);
void pm_switch_page(char *page_name);
