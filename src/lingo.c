/**
 * @file lingo.c
 *
 * @brief Implementation of methods for storing linguistic chunks
 */

/* System includes */
#include <stdbool.h>    /* bool */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* strlen */

/* Local includes */
#include <lingo.h>
#include <strops.h>
#include <wset.h>


/* Initializes the structure */
lingo_t *lingo_init(const char *kname, const char *uname,
                    const char *desc, bool direct)
{
    lingo_t *lingo;

    if (!(lingo = malloc(sizeof(lingo_t)))) {
        return NULL;
    }

    lingo->kname = alloc_str_as(kname);
    lingo->uname = alloc_str_as(uname);
    lingo->desc = alloc_str_as(desc);

    if (uname) { str_cpy(lingo->uname, uname); }
    if (kname) { str_cpy(lingo->kname, kname); }
    if (desc) { str_cpy(lingo->desc, desc); }

    lingo->nouns = wset_init();
    lingo->adjs = wset_init();
    lingo->pronouns = wset_init();

    lingo->direct = direct;

    return lingo;
}


/* Frees allocated memory */
void lingo_destroy(lingo_t *lingo, bool destroy_sets)
{
    wset_destroy(lingo->nouns, destroy_sets);
    wset_destroy(lingo->adjs, destroy_sets);
    wset_destroy(lingo->pronouns, destroy_sets);

    free(lingo->desc);
    free(lingo->kname);
    free(lingo->uname);

    free(lingo);
}

