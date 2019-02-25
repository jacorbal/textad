/**
 * @file wset.c
 *
 * @brief Word set operations implementation
 */

/* System includes */
#include <stdbool.h>    /* bool, true, false */
#include <stdlib.h>     /* malloc, realloc, free */

/* Local includes */
#include <strops.h>
#include <wset.h>


/* Create an empty bag of words */
wset_t *wset_init(void)
{
    wset_t *wset;

    if (!(wset = malloc(sizeof(wset_t)))) {
        return NULL;
    }
    if (!(wset->words = malloc(sizeof(char **)))) {
        return NULL;
    }

    wset->len = 0;
    wset->bytes = 0;

    return wset;
}

/* Frees allocated memory */
void wset_destroy(wset_t *wset, bool destroy_words)
{
    if (wset->words) {
        if (destroy_words) {
            /* Free also the words when destroying the set */
            for (size_t i = 0; i < wset->len; ++i) {
                free(wset->words[i]);
            }
        }
        free(wset->words);
    }
    free(wset);
}


/* Checks if a word is contained in the set of words */
bool wset_has_word(wset_t *wset, const char *word)
{
    return str_in_array(word, (const char **) wset->words, wset->len);
}


/* Adds a new word to the set of words */
bool wset_add(wset_t *wset, const char *word)
{
    if (wset_has_word(wset, word)) {
        return false;
    }

    wset->words = realloc(wset->words, sizeof(char **) * (wset->len + 1));
    wset->words[wset->len] = realloc(wset->words[wset->len],
                                     sizeof(char *) * (strlen(word) + 1));

    if (!wset->words[wset->len]) {
        return false;
    }
    str_cpy(wset->words[wset->len], word);
    wset->bytes += strlen(word);
    wset->len++;

    return true;
}


/* Removes a word from the set of words */
bool wset_rem(wset_t *wset, const char *word)
{
    if (!wset_has_word(wset, word) || wset->len == 0) {
        return false;
    }

    for (size_t i = 0; i < wset->len; ++i) {
        if (streq(wset->words[i], word)) {
            for (size_t j = i; j < wset->len; ++j) {
                wset->words[j] = wset->words[j+1];
            }
            // FIXME: Segfault when adding after removing! -- check 'realloc'
/*
            wset->words[i] = realloc(wset->words[i],
                    sizeof(char *) * (wset->bytes - strlen(word)));
            if (!wset->words[i]) {
                return false;
            }

            wset->words = realloc(wset->words, sizeof(char **) * wset->len);
            if (!wset->words) {
                return false;
            }
*/
            wset->bytes -= strlen(word);
            wset->len--;
        }
    }

    return true;
}


/* Applies a function to every string on the set */
void wset_f(wset_t *wset, void (*f)(char *))
{
    for (size_t i = 0; i < wset->len; ++i) {
        f(wset->words[i]);
    }
}
