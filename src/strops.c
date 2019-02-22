/**
 * @file strops.c
 *
 * @brief String operations implementation
 */

/* System includes */
#include <ctype.h>   /* isspace, tolower */
#include <stdbool.h> /* bool, true, false */
#include <string.h>  /* memmove, strcmp, strlen */

/* Local includes */
#include <strops.h>


/* Checks if a string is in an array of strings */
bool str_in_array(const char *s, const char **arr, size_t arr_len)
{
    for (size_t i = 0; i < arr_len; ++i) {
        if (strcmp(s, arr[i]) == 0) {
            return true;
        }
    }

    return false;
}


/* Trims a string, removes leading and trailing white spaces */
void str_trim(char * s)
{
    char * p = s;
    int l = strlen(p);

    while (isspace(p[l - 1])) { p[--l] = 0; }
    while (*p && isspace(*p)) { ++p, --l; }

    memmove(s, p, l + 1);
}


/* Transform the string to lowercase */
void str_transform(char *s, int (*f)(int))
{
    for ( ; *s; ++s) { *s = f(*s); }
}


/* Normalize string */
void str_normalize(char **s, lettercase_t lettercase)
{
    switch (lettercase) {
        case UPPERCASE:
            str_toupper(*s);
            break;

        case LOWERCASE:
        default:
            str_tolower(*s);
    }
    str_trim(*s);
}

