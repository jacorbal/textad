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
 * @file item.h
 *
 * @brief Item related routines declaration
 *
 * The item is very entity of the game and, since it depends on a
 * parsing method, the words carried by the item structure are separated
 * in different categories.
 *
 * I struggled in where to include the qualities "object".  The item
 * has a pointer to a @e lingo structure with lists for nouns, pronouns
 * and adjectives (as well as a name and a description), but I thought
 * that the dynamic elements, thus being the "dynamic adjectives" that
 * are subjected to the value of a state variable, should belong to the
 * item and not to the @e lingo structure.
 *
 * From the user point of view, there's no difference thanks to the
 * macros below, to add or remove adjectives from one or another place,
 * for example, @e item_add_ajd for adding a new static adjective, or
 * @e item_add_qlty to add a new dynamic adjective.
 *
 * The main reason for keeping those adjective types in different
 * "classes" is because I don't consider the @e flags_t as something
 * purely linguistic, as it includes some logic behind states, and the
 * type @e lingo_t was conceived to carry only syntax data and not
 * states values.
 *
 * In the end, the parser will check both static and dynamic adjectives
 * taken from the references in the item, and treat them equally.
 */

#ifndef ITEM_H
#define ITEM_H

/* System includes */
#include <stdint.h> /* uint32_t */

/* Local includes */
#include <lingo.h>
#include <qltys.h>


/**
 * @typedef item_t
 *
 * @brief Item properties and syntax lexems sorted by kind
 *
 * The @e lingo chuncks contain the list of nouns, adjectives and
 * pronouns that refer to the item, and though they can be modified,
 * those tend to be constant.  In the case of a variable item, what
 * changes usually are the dynamic properties of it, thus, adjectives.
 * So there are in @e lingo nouns, pronouns and static adjectives (those
 * that are constant and never change) and @e qltys containing the
 * dynamic adjectives (or those that are linked to a state variable and,
 * depending on its value, the adjetive may change as well.
 *
 * @verbatim
 *
 *    item_t <------- lingo_t
 *      ^              | | |
 *      |              | | `------ nouns: (char *)
 *      |              | `-------- pronouns: (char *)
 *      |              `---------- adjs (static): (char*)
 *      |
 *      |
 *      `------------ qltys_t <- flag_t (dynamic adjs.)
 *                                 | |
 *                                 | `------ yes: (char*)
 *                                 `-------- no: (char*)
 * @endverbatim
 */
typedef struct {
    uint32_t id;        /**< Item unique identifier */
    float weight;       /**< Item weight in kg */
    lingo_t *lingo;     /**< Syntax related strings */
    qltys_t *qltys;     /**< List of qualities (flags/dyanmic adjs) */
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
#define item_name(i)  (i->name)

/**
 * @brief Macro that evaluates to the item description
 */
#define item_desc(i)  (i->desc)

/**
 * @brief Macro that evaluates to the item weight in kg
 */
#define item_weight(i)  (i->weight)

/**
 * @brief Macro that evaluates to the item unique numeric identifier
 */
#define item_id(i)  (i->id)

/**
 * @brief Macro that evaluates to the linguistic nouns for this item
 */
#define item_nouns(i)  (i->lingo->nouns)

/**
 * @brief Macro that evaluates to the linguistic adjectives for this item
 */
#define item_adjs(i)  (i->lingo->adjs)

/**
 * @brief Macro that evaluates to the linguistic pronouns for this item
 */
#define item_pronouns(i)  (i->lingo->pronouns)

/**
 * @brief Macro that evaluates to the adding of a noun
 *
 * @see wset_add
 */
#define item_add_noun(i,s)  wset_add(i->lingo->nouns, s)

/**
 * @brief Macro that evaluates to the removal of a noun
 *
 * @see wset_rem
 */
#define item_rem_noun(i,s)  wset_rem(i->lingo->nouns, s)

/**
 * @brief Macro that evaluates to the adding of an adjective
 *
 * @see wset_add
 */
#define item_add_adj(i,s)  wset_add(i->lingo->adjs, s)

/**
 * @brief Macro that evaluates to the removal of an adjective
 *
 * @see wset_rem
 */
#define item_rem_adj(i,s)  wset_rem(i->lingo->adjs, s)

/**
 * @brief Macro that evaluates to the adding of a pronoun
 *
 * @see wset_add
 */
#define item_add_pronoun(i,s)  wset_add(i->lingo->pronouns, s)

/**
 * @brief Macro that evaluates to the removal of a pronoun
 *
 * @see wset_rem
 */
#define item_rem_pronoun(i,s)  wset_rem(i->lingo->pronouns, s)

/**
 * @brief Macro that evaluates to the replacement of an old noun for a
 *        new one
 *
 * @see wset_replace
 */
#define item_replace_noun(i, os, ns)  wset_replace(i->lingo->nouns, os, ns)

/**
 * @brief Macro that evaluates to the replacement of an old adjective
 *        for a new one
 *
 * @see wset_replace
 */
#define item_replace_adj(i, os, ns)  wset_replace(i->lingo->adjs, os, ns)

/**
 * @brief Macro that evaluates to the replacement of an old pronoun
 *        for a new one
 *
 * @see wset_replace
 */
#define item_replace_pronoun(i, os, ns)  wset_replace(i->lingo->pronouns, os, ns)

/**
 * @brief Macro that evaluates to the adding of a new flag in the
 *        qualities array
 *
 * @see qltys_add
 */
#define item_add_qlty(i, f)  qltys_add(i->qltys, f)

/**
 * @brief Macro that evaluates to the removal of a new flag in the
 *        qualities array
 *
 * @see qltys_rem
 */
#define item_rem_qlty(i, f)  qltys_rem(i->qltys, f)

/**
 * @brief Macro that evaluates to the toggling of a flag
 *
 * @see qltys_toggle_flag, flag_toggle
 */
#define item_toggle_flag(i, f)  qltys_toggle_flag(i->qltys, f)

/**
 * @brief Macro that evaluates to the next identifier value
 */
#define item_next_id  (++item_last_id)


#endif /* ITEM_H */

