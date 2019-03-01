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
 * @file strops.h
 *
 * @brief String operations
 */

#ifndef STROPS_H
#define STROPS_H

#include <stdbool.h> /* bool */
#include <stdlib.h>  /* malloc */
#include <string.h>  /* strcmp, strlen */


/**
 * @typedef lettercase_t
 */
typedef enum { LOWERCASE, UPPERCASE } lettercase_t;


/* Public interface */
/**
 * @brief Check if a string is in an array of strings
 *
 * @param s       String to check
 * @param arr     Array where to check
 * @param arr_len Array length
 *
 * @return @c true if the string is in the array, @c false otherwise
 *
 * @todo Refactor, specially trying not to pass the @e arr_len
 */
bool str_in_array(const char *s, const char **arr, size_t arr_len);

/**
 * @brief Trim a string, removes leading and trailing white spaces
 *
 * @param s String to trim
 */
void str_trim(char *s);

/**
 * @brief Convert the string to lowercase
 *
 * @param s String to make lowercase
 * @param f Function to transform with signature `int f(int)`
 *
 * @note Recommended functions are @e tolower and @e toupper, or similar
 */
void str_transform_case(char *s, int (*f)(int));

/**
 * @brief Normalize a string
 *
 * Normalization in this context means to trime the string and transform
 * it by using a letter case.
 *
 * @param s          String to normalize
 * @param lettercase Uppercase or lowercase as normalization
 *
 * @see str_trim, str_tolower, lettercase_t
 */
void str_normalize(char **s, lettercase_t lettercase);

/**
 * @brief String copying with safe boundaries
 *
 * @param dst Pointer to destination string
 * @param src Null-terminated string to copy from
 * @param len Length to be copied from @e src to @e dest
 *
 * @return Pointer to the destination string, or @c NULL if failure on
 *         memory allocation
 *
 * @note Copy up to @e n -1 bytes characters from @e src C-string, to
 *       @e dest, making sure the termination is @c NULL.
 *
 * @note This is a safer replacement for @e strncpy by guaranteeing a
 *       null-terminated result, inspired in @e strlcpy
 */
char *str_ncpy(char *dest, const char *src, size_t len);

/**
 * @brief Allocates as much memory for the destination string as the
 *        length of the source string, and then copies the source string
 *        into the destination
 *
 * @param dst Pointer to the destination string
 * @param src Source string
 *
 * @return Pointer to the destination string, or @c NULL if failure on
 *         memory allocation
 *
 * @see str_ncpy
 */
char *str_cpy_alloc(char **dst, const char *src);

/**
 * @brief Macro that evaluates to @e str_transform using @e tolower
 *
 * @see tolower
 */
#define str_tolower(s)  str_transform_case(s, tolower)

/**
 * @brief Macro that evaluates to @e str_transform using @e toupper
 *
 * @see toupper
 */
#define str_toupper(s)  str_transform_case(s, toupper)

/**
 * @brief Macro that evaluates to @e str_normalize using `UPPERCASE`
 */
#define str_normalize_u(s)  str_normalize(s, UPPERCASE)

/**
 * @brief Macro that evaluates to @e str_normalize using `LOWERCASE`
 */
#define str_normalize_l(s)  str_normalize(s, LOWERCASE)

/**
 * @brief Macro that evaluates to a special case of @e str_ncpy where
 *        the length to be copied is the same as @e src
 *
 * @see str_ncpy
 */
#define str_cpy(d, s)  str_ncpy(d, s, strlen(s) + 1)

/**
 * @brief Macro that evaluates to the equality of two strings
 *
 * @see strncmp
 *
 * @note There are no length comparisons.  For safety reasons, @e strncmp
 *       is used, but always it's used the length of the first string.
 */
#define streq(s1, s2)  (strncmp(s1, s2, strlen(s1)) == 0)

/**
 * @brief Macro that evaluates to the length of the string
 */
#define str_is_empty(s)  (strlen(s) == 0)

/**
 * @brief Macro that evaluates to the allocation of as much memory of
 *        another string, or it evaluates it to @c NULL
 */
#define str_alloc_as(s)  (s) ? malloc(sizeof(char) * (strlen(s)+1)) : NULL


#endif /* STROPS_H */

