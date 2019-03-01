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
 * @file parser.c
 *
 * @brief Parses string by analyzing the syntactic value of every token
 *
 * It identifies every token with a gramatic value after applying rules
 * (language dependant) to exclude plurals, conjugations, prefixation,
 * etc.  The function in charge of this is `str_in_array`, that compares
 * the token with a database of words classified by synxtax category.
 *
 * There's a priority order in case a word could have different
 * syntactic values.  Instead of checking the sourroundings, the value
 * of the word is assigned just as it goes the analysis in
 * `lexeme_type`.
 */

/* System includes */
#include <ctype.h>  /* tolower */
#include <stdlib.h> /* free, malloc */
#include <string.h> /* strlen, strndup, strsep, strstr */

/**/#include <stdio.h>

/* Local includes */
#include <cmd.h>
#include <strops.h>
#include <parser.h>


/* Arrays of valid words separated by lexeme type.
 * TODO: later, taken from data files or databases */
static const char *adverbs[] = { "gently", "softly", "viciously", };
static const char *adjectives[] = { "red", "blue", "green", "yellow", "white", "black", "silver", };
static const char *numbers[] = { "one", "two", "three", "four", "five", "1", "2", "3", };
static const char *articles[] = { "a", "an", "the", };
static const char *conjunctions[] = { "and", "then", };
static const char *nouns[] = { "dog", "cat", "birds", "mouse", "potion", "key", "lock", };
static const char *pronouns[] = { "him", "her", "his", "its", "self", };
static const char *prepositions[] = { "about", "to", "for", "at", "in", "on", "of", "with", };
static const char *verbs[] = { "ask", "give", "run", "fly", "put", "eat", "drink", "catch", "take", "drop", "open", };
//static const char *answers[] = { "fine", "good", "bad", "yes", "no", "okay", };
//static const char *directions[] = { "north", "east", "south", "west", "northeast", "nortwest", "southeast", "southwest", "up", "down", };
//static const char *commands[] = { "inventory", "help", "restart", "load", "save", "quit", };
/* Also add:
 *      *expelatives[]  = { "...", };
 *      *exclamations[] = {"hello", "bye", "damn", }
 *
 * Not sure if include this, or use key combinations, or both...:
 *      *commands[] = { "load",  "save", "restart", "quit" }; 
 *                    ^F4/C-l  ^F5/C-s    C-r      C-x
 */



/* Gets the lexeme */
lexeme_t lexeme_type(const char *word)
{
    if (!word || str_is_empty(word)) {
        return LEX_EMPTY;
    }

    /* Here the priority is set indirectly by the order how these
     * conditionals are processed.  For a S-V-O model, the pronoun
     * should go first, but in these kind of adventures it's used more
     * the imperative, more like V-O, where the pronouns are part of the
     * object, who also may have adjectives.  Numbers as adjectives are
     * parsed separately, so it'll be easier to disaggregate them and
     * convert them to proper integers.
     *
     *   - "OPEN  LOCK  WITH THE SILVER KEY"
     *      verb  noun  prep art adject noun
     *      ----  ----  --------------------
     *      Act.  O.D.  Adjunct C. ('C. C. instrumental')
     *
     *   - "CLOSE DOOR"
     *      verb  noun
     *      ---- -----
     *      Act.  O.D.
     *
     *   - "USE  NEW  OIL  IN THE OLD LANTERN"
     *      verb adj noun prep art adj  noun
     *      ---- -------- --------------------
     *      Act.    D.O.  Adverial C. ('C. C. de lugar')
     *
     *   - "GIVE REDHERRING TO  WOMAN"
     *      verb    noun   prep noun
     *      ---- ---------- ---------
     *      Act.   D.O.       I.O.
     */
    if (str_in_array(word, verbs, arr_len_bytes(verbs))) {
        return LEX_VERB;
    } else if (str_in_array(word, adverbs, arr_len_bytes(adverbs))) {
        return LEX_ADVERB;
    } else if (str_in_array(word, articles, arr_len_bytes(articles))) {
        return LEX_ART;
    } else if (str_in_array(word, adjectives, arr_len_bytes(adjectives))) {
        return LEX_ADJ;
    } else if (str_in_array(word, numbers, arr_len_bytes(numbers))) {
        return LEX_NUM;
    } else if (str_in_array(word, nouns, arr_len_bytes(nouns))) {
        return LEX_NOUN;
    } else if (str_in_array(word, prepositions, arr_len_bytes(prepositions))) {
        return LEX_PREP;
    } else if (str_in_array(word, pronouns, arr_len_bytes(pronouns))) {
        return LEX_PRONOUN;
    } else if (str_in_array(word, conjunctions, arr_len_bytes(conjunctions))) {
        return LEX_CONJ;
    }

    return LEX_END;
}


/* Parse syntax of previously analyzed sentence chunks */
int parse_cmd(cmd_t *cmd)
{
    if (!cmd_action) { /* no verb, no action, therefore nothing to do */
        return 1;
    }

    /* Command processing */
/**/
    printf("Action?....... %s\n", cmd_action);
    printf("Mode?......... %s\n", cmd_mode);
    printf("Quantity?..... %s\n", cmd_quantity);
    printf("Quality?...... %s\n", cmd_quality);
    printf("D.Object?..... %s\n", cmd_dobj);
    printf("I.Object?..... %s\n", cmd_iobj);
    puts("");
/**/

    return 0;
}


/* Parse sentence */
int parse_simple(char *sentence)
{
    lexeme_t token_type;
    char *token;
    cmd_t *cmd;

    if (!(cmd = cmd_init_empty())) {
        return 1;
    }

    while ((token = strsep(&sentence, DELIMITERS))) {
        token_type = lexeme_type(token);
            /* is_direction (n, nw...)?, is_special (look...)?,
             * is_system (load...)?, is_answer (yes, no...)?,
             * is_management (inventory...)? is_...*/

        switch (token_type) {
            case LEX_VERB:
                str_cpy(cmd_action, token);
                break;

            case LEX_ADVERB:
                str_cpy(cmd_mode, token);
                break;

            case LEX_PREP:
                break;

            case LEX_ART:
                break;

            case LEX_NUM:
                str_cpy(cmd_quantity, token);
                break;

            case LEX_ADJ:
                str_cpy(cmd_quality, token);
                break;

            case LEX_NOUN:
                str_cpy(cmd_dobj, token);
                break;

            case LEX_PRONOUN:
                str_cpy(cmd_iobj, token);
                break;

            case LEX_CONJ:
                break;

            case LEX_UNK:
            case LEX_EMPTY:
                break;

            case LEX_END:   /* This point is reached on error */
            default:
                cmd_destroy(cmd);
//                puts("END");
                return 2;
        }
    }

    parse_cmd(cmd);
    cmd_destroy(cmd);

    return 0;
}


/* Parse several sentences connected by a copulative lexeme */
/* FIXME: It has to be another method better for this -> refactor!
 * (may be that amount of pointers are not needed, also, not that many
 * calls to 'str_trim') */
int parse_compound(char *sentence)
{
    char *first;
    char *last;
    char *prev;
    char *next;
    int ret_val = 0;
    int it=0;

    if (!sentence || str_is_empty(sentence)) {
        return -1;
    }

    /* Iterate over all subsentences */
    str_normalize_l(&sentence);
    first = sentence;
    while ((next = strstr(first, SEPARATOR))) {
        prev = first;
        first = strndup(next + strlen(SEPARATOR),
                        strlen(next) - strlen(SEPARATOR));
        last = strndup(prev, strlen(prev) - strlen(next));
        str_trim(last);
        ret_val += parse_simple(last);
        it++;
    }

    /* Iterate over the last remaining sentence, or the only one if no
     * separator */
    if (it) {
        str_trim(first);
        ret_val += parse_simple(first);
        /* Those strings are created by 'strndup' and I think they may
         * be deallocated with 'free'. */
        free(first);
        free(last);
    } else {
        ret_val = parse_simple(sentence);
    }

    /* QUESTION:
     * Return instead the number of iterations, `it`, (menaning, the
     * number of successfully parsed sentences)? */
    return ret_val;
}

