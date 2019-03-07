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
 * @file array.h
 *
 * @brief Array size calculations
 */

#ifndef ARRAY_H
#define ARRAY_H


/* Public interface */
/**
 * @brief Macro that evaluates to the number of elements in an array,
 *        (@c <type>*)
 */
#define arr_len(arr)  (sizeof(arr) / (sizeof(arr)[0]))

/**
 * @brief Macro that evaluates to the number of elementes in an array of
 *        arrays, (@c <type>**), ie, flattening it
 */
#define darr_len(arr)  (sizeof(arr) / (sizeof(arr)[0][0]))

/**
 * @brief Macro that evaluates to the effective number of bytes in an
 *        array of arrays, (@c char**), ie, flattening it
 */
#define darr_len_str(arr) (darr_len(arr) / 8)


#endif /* ARRAY_H */

