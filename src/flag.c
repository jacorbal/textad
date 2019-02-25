/**
 * @file flag.c
 *
 * @brief Flag routines implementation
 */

/* System includes */
#include <stdbool.h> /* bool */
#include <stdlib.h>  /* malloc, free */

/* Local includes */
#include <flag.h>


/* Initializes new flag */
flag_t *flag_init(bool state, const char *yes, const char* no)
{
    flag_t *flag;

    if ((flag = malloc(sizeof(flag_t))) == NULL) {
        return NULL;
    }

    flag->state = state;
    flag->yes = yes;
    flag->no = no;

    return flag;
}


/* Deallocates memory */
void flag_destroy(flag_t *flag)
{
    free(flag);
}

