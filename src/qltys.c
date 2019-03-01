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
 * @file qltys.c
 *
 *
 * @brief Flag array implementation
 */

/* System includes */
#include <stdbool.h>    /* bool, true, false */
#include <stdlib.h>     /* malloc, realloc, free */

/* Local includes */
#include <flag.h>
#include <qltys.h>


/* Allocates memory for the qualities array */
qltys_t *qltys_init(void)
{
    qltys_t *qltys;

    if (!(qltys = malloc(sizeof(qltys_t)))) {
        return NULL;
    }

    if (!(qltys->flags = malloc(sizeof(flag_t *)))) {
        return NULL;
    }

    qltys->len = 0;

    return qltys;
}


/* Frees allocated memory */
void qltys_destroy(qltys_t *qltys, bool destroy_flags)
{
    if (qltys->flags && destroy_flags) {
        for (size_t i = 0; i < qltys->len; ++i) {
            flag_destroy(qltys->flags[i]);
        }
    }
    free(qltys->flags);
    free(qltys);
}


/* Checks if the array contains a specific flag */
bool qltys_has_flag(qltys_t *qltys, flag_t *flag)
{
    if (!qltys || !flag) {
        return false;
    }

    for (size_t i = 0; i < qltys->len; ++i) {
        if (qltys->flags[i] == flag) {
            return true;
        }
    }

    return false;
}


/* Searches for and toggles a flag in the array */
bool qltys_toggle_flag(qltys_t *qltys, flag_t *flag)
{
    for (size_t i = 0; i < qltys->len; ++i) {
        if (qltys->flags[i] == flag) {
            flag_toggle(qltys->flags[i]);
            return true;
        }
    }

    return false;
}


/* Adds a new flag to the qualities array */
bool qltys_add(qltys_t *qltys, flag_t *flag)
{
    if (!flag || !qltys || qltys_has_flag(qltys, flag)) {
        return false;
    }

    qltys->flags = realloc(qltys->flags,
            sizeof(flag_t *) * (qltys->len + 1));
    if (!qltys->flags) {
        return false;
    }

    qltys->flags[qltys->len] = flag;
    qltys->len++;

    return true;
}


/* Removes a new flag to the qualities array */
bool qltys_rem(qltys_t *qltys, flag_t *flag)
{
    if (!flag || !qltys || !qltys_has_flag(qltys, flag) || qltys->len == 0) {
        return false;
    }

    for (size_t i = 0; i < qltys->len; ++i) {
        if (qltys->flags[i] == flag) {
            for (size_t j = i; j < qltys->len; ++j) {
                qltys->flags[j] = qltys->flags[j+1];
            }
            qltys->flags = realloc(qltys->flags,
                    sizeof(flag_t *) * qltys->len);
            if (!qltys->flags) {
                return false;
            }
            qltys->len--;
        }
    }

    return true;
}

