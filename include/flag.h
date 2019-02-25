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
 * @brief Flag, defined with two (pointer to) functions (as methods) to
 *        toggle the flag and print it
 */
typedef struct {
    bool state;                 /**< Actual value of the flag */
    const char *yes;            /**< Text on positive case */
    const char *no;             /**< Text on negative case */
    int (*print)(const char *); /**< Pointer to print function */
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
flag_t *flag_init(bool state, const char *yes, const char *no);

/**
 * @brief Frees allocated memory
 *
 * @param flag Flag to deallocate from memory
 */
void flag_destroy(flag_t *flag);

/**
 * @brief Prints information depending on the flag value
 */
void flag_print(flag_t *flag);

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
#define flag_toggle(f)  (f->v = !(f->v))

/**
 * @brief Macro that evaluates to @flag_init without status strings
 */
#define flag_init_q(f)  flag_init(f, NULL, NULL);

/** @brief Macro that evaluates to @flag_init without status strings and
 *         the status set to @c true
 */
#define flag_init_qt(f)  flag_init_qq(true)

/** @brief Macro that evaluates to @flag_init without status strings and
 *         the status set to @c false
 */
#define flag_init_qf(f)  flag_init_qq(false)


#endif /* FLAG_H */

