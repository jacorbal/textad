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
 * @file flag.c
 *
 * @brief Flag routines implementation
 */

/* System includes */
#include <stdbool.h> /* bool */
#include <stdlib.h>  /* malloc, free */
#include <string.h>  /* strncmp */

/* Local includes */
#include <flag.h>
#include <strops.h>

/* Initializes new flag */
flag_t *flag_init(const bool state, const char *yes, const char* no)
{
    flag_t *flag;

    if (!(flag = malloc(sizeof(flag_t)))) {
        return NULL;
    }

    flag->state = state;
    flag->yes = str_alloc_cpy(yes);
    flag->no = str_alloc_cpy(no);

    return flag;
}


/* Deallocates memory */
void flag_destroy(flag_t *flag)
{
    free(flag->yes);
    free(flag->no);
    free(flag);
}


/* Compares two flags */
bool flag_cmp(const flag_t *f1, const flag_t *f2, bool statecmp)
{
    if (statecmp) {
        if (f1->state != f2->state) {
            return false;
        }
    }

    return (strncmp(f1->yes, f2->yes, strlen(f1->yes)) == 0) &&
           (strncmp(f1->no, f2->no, strlen(f1->no)) == 0);
}

