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
 * @file lingo.c
 *
 * @brief Implementation of methods for storing linguistic chunks
 */

/* System includes */
#include <stdbool.h>    /* bool */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* strlen */

/* Local includes */
#include <lingo.h>
#include <strops.h>
#include <wset.h>


/* Initializes the structure */
lingo_t *lingo_init(const char *kname, const char *uname,
                    const char *desc, bool direct)
{
    lingo_t *lingo;

    if (!(lingo = malloc(sizeof(lingo_t)))) {
        return NULL;
    }

    lingo->kname = str_alloc_as(kname);
    lingo->uname = str_alloc_as(uname);
    lingo->desc = str_alloc_as(desc);

    if (uname) { str_cpy(lingo->uname, uname); }
    if (kname) { str_cpy(lingo->kname, kname); }
    if (desc) { str_cpy(lingo->desc, desc); }

    lingo->nouns = wset_init();
    lingo->adjs = wset_init();
    lingo->pronouns = wset_init();

    lingo->direct = direct;

    return lingo;
}


/* Frees allocated memory */
void lingo_destroy(lingo_t *lingo, bool destroy_sets)
{
    wset_destroy(lingo->nouns, destroy_sets);
    wset_destroy(lingo->adjs, destroy_sets);
    wset_destroy(lingo->pronouns, destroy_sets);

    free(lingo->desc);
    free(lingo->kname);
    free(lingo->uname);

    free(lingo);
}

