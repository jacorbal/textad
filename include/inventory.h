/**
 * @file inventory.h
 *
 * @brief Inventory related routines declaration
 */

#ifndef INVENTORY_H
#define INVENTORY_H

/* System includes */
#include <stdbool.h>    /* bool */

/* Local includes */
#include <item.h>


/**
 * @typedef inv_t
 *
 * @brief Inventory structure as a dynamic array of pointer to items
 *
 * @note Instead of using a function to calcuate the weight by
 *       transversing all items in the dynamic array, the weight is
 *       stored as a variable only updated when modifying the contents
 *       of the inventory
 */
typedef struct {
    item_t **items; /**< Array of pointer to items */
    size_t len;     /**< Length of the array */
    float weight;   /**< Inventory weight in kg (sum of all contained items) */
} inv_t;


/* Public interface */
/**
 * @brief Initializes a new empty inventory
 *
 * @return Pointer to the newly created inventory, or @c NULL otherwise
 */
inv_t *inv_init(void);

/**
 * @brief Frees allocated memory
 *
 * @param inv           Inventory to deallocate
 * @param destroy_items If true, deallocates also items memory
 *
 * @note Items contained are not deallocated.  The inventory may
 *       disappear but the items should remain
 */
void inv_destroy(inv_t *inv, bool destroy_items);

/**
 * @brief Checks if an item is contained in a specific inventory
 *
 * @param inv  Inventory where to look
 * @param item Item to check
 *
 * @return @c true if the item is in the inventory, or @c false otherwise
 */
bool inv_has_item(inv_t *inv, item_t *item);

/**
 * @brief Adds an item to the inventory
 *
 * @param inv  Pointer to the inventory where to add
 * @param item Pointer to the item to add
 *
 * @return @c true if the insertion was successful, or @c false otherwise
 *
 * @pre The item shouldn't be contained in the inventory
 *
 * @see inv_has_item
 */
bool inv_add(inv_t *inv, item_t *item);

/**
 * @brief Removes an item from the inventory
 *
 * @param inv  Inventory where to remove the pointer to the item
 * @param item Pointer to the item to unlink from the inventory
 *
 * @return @c true if the item was successfully removed, or @c false
 *         otherwise
 *
 * @pre The item has to be contained in the inventory
 * @pre The inventory mustn't be empty
 *
 * @note To check where in the set (dynamic array) of items, i.e., the
 *       inventory, is the item to remove, this function checks if the
 *       item @e id matches
 *
 * @see inv_has_item
 *
 * @todo Refactor this function using @e memmove (@c string.h)
 */
bool inv_rem(inv_t *inv, item_t *item);

/**
 * @brief Moves an item from one inventory to another
 *
 * @param src  Pointer to source inventory, where the item is taken from
 * @param dest Pointer to destination inventory, where the item goes
 * @param item Pointer to the item to move
 *
 * @return @c true if the transfer is succesful, or @c false otherwise
 *
 * @pre The same preconditions as @e inv_add and @e inv_rem
 *
 * @note First removes the item from @e src, and if succeeds, the adds
 *       it to @e dest, in that order
 *
 * @see inv_add, inv_rem
 */
bool inv_transfer(inv_t *src, inv_t *dest, item_t *item);

/**
 * @brief Forces recaculation of weight to update the inventory weight
 *        "property"
 *
 * @param inv Inventory to calculate effective weight in kg
 *
 * @return Sum of all of weights (kg) of items contained in the inventory
 */
float inv_eval_weight(inv_t *inv);

/**
 * @brief Macro that evaluates to a soft memory deallocation without
 *        touching the contained items
 *
 * @see inv_destroy
 */
#define inv_destroy_soft(i)  inv_destroy(i, false)

/**
 * @brief Macro that evaluates to a hard memory deallocation destroying
 *        also the contained items
 *
 * @see inv_destroy
 */
#define inv_destroy_all(i)  inv_destroy(i, true)

/**
 * @brief Macro that evaluates to the inventory length (number of items
 *        that the inventory contains)
 */
#define inv_len(i)  (i->len)

/**
 * @brief Macro that evaluates to the inventory current weight
 */
#define inv_weight(i)  (i->weight)


#endif /* INVENTORY_H */

