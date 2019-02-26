/*
 * Copyright (c) 2019, J. A. Corbal
 *
 * THIS MATERIAL IS PROVIDED "AS IS", WITH ABSOLUTELY NO WARRANTY
 * EXPRESSED OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting documentation.  No representations are made about the
 * suitability of this software for any purpose.
 */
/**
 * @file item.c
 *
 * @brief Item routines implementation
 */

/* System includes*/
#include <stdint.h> /* int32_t */
#include <stdlib.h> /* malloc, free */

/* Local includes */
#include <item.h>
#include <lingo.h>
#include <qltys.h>
#include <strops.h>


static uint32_t item_last_id = 0;   /**< Item unique identifier */


/* Allocates memory for a new item */
item_t *item_init(const char *name, const char *desc, float weight)
{
    item_t *item;

    /* Item name is a requirement */
    if (!name || str_is_empty(name)) {
        return NULL;
    }

    if (!(item = malloc(sizeof(item_t)))) {
        return NULL;
    }

    if (!(item->lingo = lingo_init_kdo(name, desc))) {
        return NULL;
    }

    if (!(item->qltys = qltys_init())) {
        return NULL;
    }
    
    item->weight = weight;
    item->id = item_next_id;

    return item;
}


/* Frees allocated memory */
void item_destroy(item_t *item)
{
    lingo_destroy_soft(item->lingo);
    qltys_destroy_hard(item->qltys);
    free(item);
}

