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
 * @file lingo.h
 *
 * @brief Declaration of syntax chunks to then relate to objects
 */

#ifndef LINGO_H
#define LINGO_H

/* System includes */
#include <stdbool.h>    /* bool, true, false */
#include <stddef.h>     /* NULL */

/* Local includes */
#include <wset.h>


/**
 * @typedef lingo_t
 *
 * @brief Language atoms for any object that can be in the game world
 *
 * This structure is intended to be used as a lingual construction for
 * an game object to be refered to.  The adjectives @e adjs are only
 * "static" adjectives, i.e., those that are constant and cannot change
 * during the lifetime of the object, for they are not linked to any
 * state value.
 */
typedef struct {
    char *desc;         /**< Object description */
    char *kname;        /**< Object known name */
    char *uname;        /**< Object unknown name */

    wset_t *nouns;      /**< List of nouns to refer this object */
    wset_t *adjs;       /**< List of (static) adjectives for this object */
    wset_t *pronouns;   /**< List of pronouns related to this object */

    bool direct;        /**< Is this object usually indirect or direct */
} lingo_t;


/* Public interface */
/**
 * @brief Initializes the lingo "matrix" where everything is set to
 *        @c NULL except the name and description of the item
 *
 * @param kname  Known name (e.g., "")
 * @param ukname Unknown name (e.g., "")
 * @param desc   Description of the object
 * @param direct Is usually a direct object, or indirect?
 *
 * @return Pointer to the newly created lingo structure
 */
lingo_t *lingo_init(const char *kname, const char *uname,
                    const char *desc, bool direct);

/**
 * @brief Frees allocted memory
 *
 * @param lingo        Lingo structure to free
 * @param destroy_sets If @c true, destroy also the word sets
 */
void lingo_destroy(lingo_t *lingo, bool destroy_sets);

/**
 * @brief Macro that evaluates to the initialization of a lingo
 *        structure that usually is a direct object
 *
 * @see lingo_init
 */
#define lingo_init_do(k,u,d)  lingo_init(k, u, d, true)

/**
 * @brief Macro that evaluates to the initialization of a lingo
 *        structure that usually is an indirect object
 *
 * @see lingo_init
 */
#define lingo_init_io(k,u,d)  lingo_init(k, u, d, false)

/**
 * @brief Macro that evaluates to the initialization of a lingo
 *        structure that usually is an indirect object and it has no
 *        unknon name
 *
 * @see lingo_init
 */
#define lingo_init_kdo(k,d)  lingo_init(k, NULL, d, true)

/**
 * @brief Macro that evaluates to the initialization of a lingo
 *        structure that usually is an indirect object and it has no
 *        unknon name
 *
 * @see lingo_init
 */
#define lingo_init_kio(k,d)  lingo_init(k, NULL, d, false)

/**
 * @brief Macro that evaluates to the destruction of the object without
 *        deallocating the sets it contains
 *
 * @see lingo_destroy
 */
#define lingo_destroy_soft(l)  lingo_destroy(l, false)

/**
 * @brief Macro that evaluates to the destruction of the object and all
 *        the sets it contains
 *
 * @see lingo_destroy
 */
#define lingo_destroy_all(l)  lingo_destroy(l, true)


#endif /* LINGO_H */

