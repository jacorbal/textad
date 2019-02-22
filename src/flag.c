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
flag_t *flag_init(bool v, const char *yes, const char* no,
                  int (*print)(const char *))
{
    flag_t *flag;

    if ((flag = malloc(sizeof(flag_t))) == NULL) {
        return NULL;
    }

    flag->v = v;
    flag->yes = yes;
    flag->no = no;
    flag->print = print;

    return flag;
}


/* Deallocates memory */
void flag_destroy(flag_t *flag)
{
    free(flag);
}


/* Prints information depending on the status of the flag */
void flag_print(flag_t *flag)
{
    if (flag->v) {
        flag->print(flag->yes);
    } else {
        flag->print(flag->no);
    }
}

