/**
 * @file flag.c
 *
 * @brief Flag routines implementation
 */

/* System includes */
#include <stdbool.h> /* bool */
#include <stdlib.h>  /* malloc, free */
#include <string.h>  /* strncmp */

/* Local includes */
#include <flag.h>
#include <strops.h>


/* Initializes new flag */
flag_t *flag_init(const bool state, const char *yes, const char* no)
{
    flag_t *flag;

    if (!(flag = malloc(sizeof(flag_t)))) {
        return NULL;
    }

    flag->yes = malloc(sizeof(char) * (strlen(yes) + 1));
    flag->no = malloc(sizeof(char) * (strlen(no) + 1));
    str_cpy(flag->yes, yes);
    str_cpy(flag->no, no);
    flag->state = state;

    return flag;
}


/* Deallocates memory */
void flag_destroy(flag_t *flag)
{
    if (flag->yes) {
        free(flag->yes);
    }
    if (flag->no) {
        free(flag->no);
    }
    free(flag);
}


/* Compares two flags */
bool flag_cmp(const flag_t *f1, const flag_t *f2, bool statecmp)
{
    if (statecmp) {
        if (f1->state != f2->state) {
            return false;
        }
    }

    return !(strncmp(f1->yes, f2->yes, strlen(f1->yes)) &&
             strncmp(f1->no, f2->no, strlen(f1->no)));
}

