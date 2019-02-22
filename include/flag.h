/**
 * @file flag.c
 *
 * @brief Flag routines
 */

#ifndef FLAG_H
#define FLAG_H

#include <stdbool.h>


/**
 * @typedef flag_t
 *
 * @brief Flag, defined with two (pointer to) functions (as methods) to
 *        toggle the flag and print it
 */
typedef struct {
    bool v;                     /**< Actual value of the flag */
    const char *yes;            /**< Text on positive case */
    const char *no;             /**< Text on negative case */
    int (*print)(const char *); /**< Pointer to print function */
} flag_t;


/* Public interface */
/**
 * @brief Initializes the flag
 *
 * @param v      Flag effective value
 * @param yes    Text on affirmative case
 * @param no     Text on negative case
 * @param print  Print function
 *
 * @return Pointer to new flag, or @c NULL otherwise
 */
flag_t *flag_init(bool v, const char *yes, const char *no,
                  int (*print)(const char *));

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
#define flag_v(f)  (f->v)

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
 * @brief Macro that evaluates to @e flag_init in a quick mode
 *
 * This macro is equivalent to use @e flag_init setting the print
 * function pointer to @e puts.
 */
#define flag_init_q(f,y,n)  flag_init(f, y, n, puts)


#endif /* FLAG_H */

