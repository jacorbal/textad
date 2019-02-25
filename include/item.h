/**
 * @file item.h
 *
 * @brief Item related routines declaration
 */

#ifndef ITEM_H
#define ITEM_H

#include <stdint.h> /* uint32_t */


/**
 */
typedef struct {
    uint32_t id;    /**< Item unique identifier */
    char *name;     /**< Item name */
    char *desc;     /**< Item description */
    float weight;   /**< Item weight in kg */
} item_t;


/* Public interface */
/**
 * @brief Allocates memory for new item
 *
 * @param name   Iten name
 * @param desc   Item description
 * @param weight Item weight in kg
 *
 * @return Pointer to the newly created item
 */
item_t *item_init(const char *name, const char *desc, float weight);

/**
 * @brief Frees allocated memory
 *
 * @param item Item to deallocate
 */
void item_destroy(item_t *item);

/**
 * @brief Macro that evaluates to the item name
 */
#define item_name(i) (i->name)

/**
 * @brief Macro that evaluates to the item description
 */
#define item_desc(i) (i->desc)

/**
 * @brief Macro that evaluates to the item weight in kg
 */
#define item_weight(i) (i->weight)

/**
 * @brief Macro that evaluates to the item unique numeric identifier
 */
#define item_id(i) (i->id)

/**
 * @brief Macro that evaluates to the next identifier value
 */
#define item_next_id  (++item_last_id)


#endif /* ITEM_H */

