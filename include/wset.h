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
 * @file wset.h
 *
 * @brief Word set operations declaration
 */

#ifndef WSET_H
#define WSET_H

/* System includes */
#include <stdbool.h>    /* bool */


/**
 * @typedef wset_t
 *
 * @brief Set of words
 */
typedef struct {
    char **words;   /**< Array of strings */
    size_t len;     /**< Size of array */
    size_t bytes;   /**< Sum of all lengths of all words */
} wset_t;


/* Public interface */
/**
 * @brief Create an empty bag of words
 *
 * @return Pointer to newly created empty word set, or @c NULL otherwise
 */
wset_t *wset_init(void);

/**
 * @brief Frees allocated memory
 *
 * @param wset Word set to deallocate
 */
void wset_destroy(wset_t *wset, bool destroy_words);

/**
 * @brief Checks if a word is contained in the set of words
 *
 * @param wset Word set to search in
 * @param word Word to look up
 *
 * @return @c true if the word is on the set, or @c false otherwise
 */
bool wset_has_word(wset_t *wset, const char *word);

/**
 * @brief Adds a new word to the set of words
 *
 * @param wset Word set where to insert the new word
 * @param word Word to insert in the word set
 *
 * @return @c true if the word is successufuly inserted in the word set,
 *         or @c false otherwise
 *
 * @pre The new word cannot be already in the set
 * @pre The new word cannot be the empty string or be @c NULL
 *
 * @see wset_has_word
 */
bool wset_add(wset_t *wset, const char *word);

/**
 * @brief Removes a word from the set of words
 *
 * @param wset Word set where to insert the new word
 * @param word Word to insert in the word set
 *
 * @return @c true if the word is successufuly removed from the word
 *         set, or @c false otherwise
 *
 * @pre The word must be already in the set
 * @pre The word set mustn't be empty
 *
 * @see wset_has_word
 *
 * @bug Segfault when adding a new word after removing another.
 *      Check memory management in this function (@c realloc)
 */
bool wset_rem(wset_t *wset, const char *word);

/**
 * @brief Replaces a string with another
 *
 * @param wset Where to make the changes
 * @param old  Old string to replace
 * @param new  Replacement string
 *
 * @return @c true if the replacement was successful, or @c false
 *         otherwise
 *
 * @see wset_add, wset_rem
 */
bool wset_replace(wset_t *wset, const char *old, const char *new);

/**
 * @brief Applies a function to every string on the set
 *
 * @param wset Word set to operate to
 * @param f    Function to apply to each and every member of the set
 *
 * @note The signature of the function must be `void f(char *)`
 */
void wset_map(wset_t *wset, void (*f)(char *));

/**
 * @brief Macro that evaluates to a hard destroy of the object
 *
 * @see wset_destroy
 */
#define wset_destroy_all(w)  wset_destroy(w, true)

/**
 * @brief Macro that evaluates to the word set length (size)
 */
#define wset_len(w)  (w->len)

/**
 * @brief Macro that evaluates to the set size in bytes
 */
#define wset_bytes(w)  (w->bytes)


#endif /* WSET_H */

