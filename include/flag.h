/**
 * @file flag.h
 *
 * @brief Flag routines
 */

#ifndef FLAG_H
#define FLAG_H

/* System includes */
#include <stdbool.h>    /* bool, true, false */


/**
 * @typedef flag_t
 *
 * @brief Flag, defined with a boolean state and two strings depending
 *        on the state value
 *
 * @todo The strings should be in a `union` allocating memory for the
 *       longest
 */
typedef struct {
    bool state;   /**< Actual value of the flag */
    char *yes;    /**< Text on positive case */
    char *no;     /**< Text on negative case */
} flag_t;


/* Public interface */
/**
 * @brief Initializes the flag
 *
 * @param state  Flag effective value
 * @param yes    Text on affirmative case
 * @param no     Text on negative case
 *
 * @return Pointer to new flag, or @c NULL otherwise
 */
flag_t *flag_init(const bool state, const char *yes, const char *no);

/**
 * @brief Frees allocated memory
 *
 * @param flag Flag to deallocate from memory
 */
void flag_destroy(flag_t *flag);

/**
 * @brief Compares two flags
 *
 * @param f1       First flag to compare
 * @param f2       Second flag to compare
 * @param statecmp Compare also the state of the flag
 *
 * @return @c true if both flags have the same @e yes and @e no strings
 *
 * @note The equality is based on string comparison, and it's always
 *       taken as a reference the length of the strings of @e f1
 */
bool flag_cmp(const flag_t *f1, const flag_t *f2, bool statecmp);

/**
 * @brief Macro that evaluates to the flag effective value
 */
#define flag_state(f)  (f->state)

/**
 * @brief Macro that evaluates to the flag affirmative answer
 */
#define flag_yes(f)  (f->yes)

/**
 * @brief Macro that evaluates to the flag negative answer
 */
#define flag_no(f)  (f->no)

/**
 * @brief Toggles flag value
 */
#define flag_toggle(f)  (f->state = !(f->state))

/**
 * @brief Macro that evaluates to @flag_init without status strings
 */
#define flag_init_q(f)  flag_init(f, NULL, NULL);

/** @brief Macro that evaluates to @flag_init without status strings and
 *         the status set to @c true
 */
#define flag_init_qt(f)  flag_init_q(true)

/** @brief Macro that evaluates to @flag_init without status strings and
 *         the status set to @c false
 */
#define flag_init_qf(f)  flag_init_q(false)


#endif /* FLAG_H */

