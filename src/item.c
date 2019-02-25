/**
 * @file item.c
 *
 * @brief Item routines implementation
 */

/* System includes*/
#include <stdint.h> /* int32_t */
#include <stdlib.h> /* malloc, free */

/* Local includes */
#include <strops.h>
#include <item.h>


/**
 */
static uint32_t item_last_id = 0;



/* Allocates memory for a new item */
item_t *item_init(const char *name, const char *desc, float weight)
{
    item_t *item;

    if (!name || str_is_empty(name)) {
        return NULL;
    }

    if (!(item = malloc(sizeof(item_t)))) {
        return NULL;
    }

    item->name = malloc(sizeof(char) * (strlen(name) + 1));
    item->desc = malloc(sizeof(char) * (strlen(desc) + 1));

    str_cpy(item->name, name);
    str_cpy(item->desc, desc);
    item->weight = weight;
    item->id = item_next_id;

    return item;
}


/* Frees allocated memory */
void item_destroy(item_t *item)
{
    free(item->name);
    free(item->desc);
    free(item);
}

