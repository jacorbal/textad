/**
 * @file inventory.c
 *
 * @brief Inventory related functions implementation
 */

/* System includes */
#include <stdbool.h>    /* bool, true, false */
#include <stdlib.h>     /* malloc, realloc, free */

/* Local includes */
#include <item.h>
#include <inventory.h>


/* Initializes a new empty inventory */
inv_t *inv_init(void)
{
    inv_t *inv;

    if (!(inv = malloc(sizeof(inv_t)))) {
        return NULL;
    }

    if (!(inv->items = malloc(sizeof(item_t *)))) {
        return NULL;
    }

    inv->len = 0;
    inv->weight = 0.0f;

    return inv;
}


/* Frees allocated memory */
void inv_destroy(inv_t *inv, bool destroy_items)
{
    if (inv->items) {
        if (destroy_items) {
            for (size_t i = 0; i < inv->len; ++i) {
//                free(inv->items[i]);
                item_destroy(inv->items[i]);
            }
        }
        free(inv->items);
    }
    free(inv);
}


/* Checks if an item is contained in a specific inventory */
bool inv_has_item(inv_t *inv, item_t *item)
{
    if (!item || !inv) {
        return false;
    }
    
    for (size_t i = 0; i < inv->len; ++i) {
        if (inv->items[i]->id == item->id) {
            return true;
        }
    }

    return false;
}


/* Adds an item to the inventory */
bool inv_add(inv_t *inv, item_t *item)
{
    if (!item || !inv || inv_has_item(inv, item)) {
        return false;
    }

    inv->items = realloc(inv->items, sizeof(item_t *) * (inv->len + 1));
    if (!inv->items) {
        return false;
    }

    inv->items[inv->len] = item;
    inv->len++;
    inv->weight += item->weight;

    return true;
}


/* Removes an item from the inventory */
bool inv_rem(inv_t *inv, item_t *item)
{
    if (!item || !inv || !inv_has_item(inv, item) || inv->len == 0) {
        return false;
    }

    for (size_t i = 0; i < inv->len; ++i) {
        if (inv->items[i]->id == item->id) {
            for (size_t j = i; j < inv->len; ++j) {
                inv->items[j] = inv->items[j + 1];
            }
            inv->items = realloc(inv->items, sizeof(item_t *) * inv->len);
            if (!inv->items) {
                return false;
            }
            inv->len--;
            inv->weight -= item->weight;
        }
    }

    return true;
}


/* Moves an item from one inventory to another */
bool inv_transfer(inv_t *src, inv_t *dest, item_t *item)
{
    return inv_rem(src, item) && inv_add(dest, item);
}


/* Calculates the effective weight of the inventory */
float inv_eval_weight(inv_t *inv)
{
    float total_weight = 0.0f;

    if (inv) {
        for (size_t i = 0; i < inv->len; ++i) {
            total_weight += inv->items[i]->weight;
        }
    }

    return total_weight;
}

