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
 * @file strops.c
 *
 * @brief String operations implementation
 */

/* System includes */
#include <ctype.h>   /* isspace, tolower */
#include <stdbool.h> /* bool, true, false */
#include <string.h>  /* memmove, strcmp, strlen */

/* Local includes */
#include <strops.h>


/* Check if a string is in an array of strings */
bool str_in_array(const char *s, const char **arr, size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i) {
        if (strcmp(s, arr[i]) == 0) {
            return true;
        }
    }

    return false;
}


/* Trim a string, removes leading and trailing white spaces */
void str_trim(char * s)
{
    char * p = s;
    int l = strlen(p);

    while (isspace(p[l - 1])) { p[--l] = 0; }
    while (*p && isspace(*p)) { ++p, --l; }

    memmove(s, p, l + 1);
}


/* Transform the string to lowercase */
void str_transform_case(char *s, int (*f)(int))
{
    for (; *s; ++s) {
        *s = f(*s);
    }
}


/* Normalize string */
void str_normalize(char **s, lettercase_t lettercase)
{
    switch (lettercase) {
        case UPPERCASE:
            /* str_toupper(*s); */
            str_transform_case(*s, toupper);
            break;

        case LOWERCASE:
        default:
            /* str_lower(*s); */
            str_transform_case(*s, tolower);
            break;
    }
    str_trim(*s);
}


/* Copy a string to another */
size_t str_ncpy(char *dst, const char *src, size_t len)
{
    char *d = dst;
    const char *s = src;
    size_t n = len;

    /* Copy as many bytes as will fit */
    if (n != 0) {
        while (--n != 0) {
            if ((*d++ = *s++) == '\0') {
                break;
            }
        }
    }

    /* Not enough room in dst, add NULL and traverse rest of 'src' */
    if (n == 0) {
        if (len != 0) { *d = '\0';  } /* null-terminate 'dst' */
        while (*s++);
    }

    return s - src - 1;     /* Count does not include 'NULL' */
}

