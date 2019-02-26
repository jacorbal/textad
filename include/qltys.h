/**
 * @file qltys.h
 *
 * @brief Array of different flags to be used each one as a dynamic
 *       adjective
 */

#ifndef QLTYS_H
#define QLTYS_H

/* System includes */
#include <stdbool.h>    /* bool */

/* Local includes */
#include <flag.h>


/**
 * @typedef qltys_t
 *
 * @brief In short words, array of flags
 */
typedef struct {
    flag_t **flags;
    size_t len;
} qltys_t;


/* Public interface */
/**
 * @brief Allocates memory for qualities array
 *
 * @return Pointer to the newly created qualities array
 */
qltys_t *qltys_init(void);

/**
 * @brief Frees allocated memory
 *
 * @param qltys         Qualities array to free
 * @param destroy_flags If @c true, frees also the memory of used flags
 */
void qltys_destroy(qltys_t *qltys, bool destroy_flags);

/**
 * @brief Check if a flag is contained in the qualities array
 *
 * @param qltys Qualities array to search in
 * @param flag  Flag to search for
 *
 * @return @c true if the flag is on the array, or @c false otherwise
 */
bool qltys_has_flag(qltys_t *qltys, flag_t *flag);

/**
 * @brief Searches for and toggles a flag in the qualities array
 *
 * @param qltys Qualities array
 * @param flag  Flag to toggle
 *
 * @return @c true if the flag was succesfully toggled, or @c false
 *         otherwise
 *
 * @see flag_toggle
 */
bool qltys_toggle_flag(qltys_t *qltys, flag_t *flag);

/**
 * @brief Adds a new flag to the qualities array
 *
 * @param qltys Qualities array to add the flag to
 * @param flag  Flag to add
 *
 * @return @c true if the flag is succesfully added, or @c false
 *         otherwise
 */
bool qltys_add(qltys_t *qltys, flag_t *flag);

/**
 * @brief Removes a new flag from the qualities array
 *
 * @param qltys Qualities array to remove the flag from
 * @param flag  Flag to remove
 *
 * @return @c true if the flag is succesfully removed, or @c false
 *         otherwise
 */
bool qltys_rem(qltys_t *qltys, flag_t *flag);

/**
 * @brief Macro that evaluates to the deallocation of all the qualities,
 *        without deallocating any flag that contains
 *
 * @see qltys_destroy
 */
#define qltys_destroy_soft(q)  qltys_destroy(q, false)

/**
 * @brief Macro that evaluates to the deallocation of all the qualities,
 *        and also every flag that contains
 *
 * @see qltys_destroy
 */
#define qltys_destroy_hard(q)  qltys_destroy(q, true)


#endif /* QLTYS_H */

