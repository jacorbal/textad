/**
 * @file strops.h
 *
 * @brief String operations
 */

#ifndef STROPS_H
#define STROPS_H

#include <stdbool.h> /* bool */

/**
 */
typedef enum { LOWERCASE, UPPERCASE } lettercase_t;


/* Public interface */
/**
 * @brief Checks if a string is in an array of strings
 *
 * @param s       String to check
 * @param arr     Array where to check
 * @param arr_len Array length
 *
 * @return @c true if the string is in the array, @c false otherwise
 *
 * @todo Refactor, specially trying not to pass the @e arr_len
 */
bool str_in_array(const char *s, const char **arr, size_t arr_len);

/**
 * @brief Trims a string, removes leading and trailing white spaces
 *
 * @param s String to trim
 */
void str_trim(char * s);

/**
 * @brief Convert the string to lowercase
 *
 * @param s String to make lowercase
 * @param f Function to transform with signature `int f(int)`
 *
 * @note Recommended functions are @e tolower and @e toupper, or similar
 */
void str_transform(char *s, int (*f)(int));

/**
 * @brief Normalize a string
 *
 * Normalization in this context means to trime the string and transform
 * it by using a letter case.
 *
 * @param s          String to normalize
 * @param lettercase Uppercase or lowercase as normalization
 *
 * @see str_trim, str_tolower, lettercase_t
 */
void str_normalize(char **s, lettercase_t lettercase);

/**
 * @brief Macro that evaluates to `str_transform` using `tolower`
 */
#define str_tolower(s) str_transform(s, tolower)

/**
 * @brief Macro that evaluates to `str_transform` using `toupper`
 */
#define str_toupper(s) str_transform(s, toupper)

/**
 * @brief Macro that evaluates to `str_normalize` using `UPPERCASE`
 */
#define str_normalize_u(s) str_normalize(s, UPPERCASE)

/**
 * @brief Macro that evaluates to `str_normalize` using `LOWERCASE`
 */
#define str_normalize_l(s) str_normalize(s, LOWERCASE)

/**
 * @brief Macro that evaluates to the equality of two strings
 *
 * @see strncmp
 *
 * @note There are no length comparisons.  For safety reasons, `strncmp`
 *       is used, but always it's used the length of the first string.
 */
//#define streq(s1, s2) (strncmp(s1, s2, strlen(s1)) == 0)


#endif /* STROPS_H */

