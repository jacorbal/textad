/**
 * @file parser.h
 *
 * @brief Parse sentences and evaluates its content
 *
 * Definitions in this context.
 *
 *    * _Simple sentence_.  A sentence that can be parse as one unit
 *
 *    * _Compound sentence_.  A sentence that has to be separated to
 *                            parse each unit individually.
 */

#ifndef PARSER_H
#define PARSER_H

#define DELIMITERS " .,;:!-'\"(){}[]<>" /**< Characters to ignore when parsing */
#define SEPARATOR  "and"

/* Local includes */
#include <cmd.h>


/**
 * @brief lexeme_t
 *
 * @brief Types of lexemes
 */
typedef enum { LEX_END=-1,  /**< End of sentence, could be an error */
               LEX_EMPTY=0, /**< Empty string */
               LEX_ADJ,     /**< Adjective */
               LEX_ADVERB,  /**< Verb */
               LEX_ART,     /**< Article */
               LEX_CONJ,    /**< Conjunction */
               LEX_NOUN,    /**< Noun */
               LEX_NUM,     /**< Number */
               LEX_PREP,    /**< Preposition */
               LEX_PRONOUN, /**< Pronoun */
               LEX_VERB,    /**< Verb */
               LEX_UNK=99,  /**< Extra / Unknown lexeme */
} lexeme_t;


/* Public interface */
/**
 * @brief Returns the type of a word checking with a "database"
 *
 * @param word Word to analyze
 *
 * @return Type of lexeme
 *
 * @see lexeme_t
 */
lexeme_t lexeme_type(const char *word);

/**
 * @brief Parse syntax of previously analyzed sentence chunks
 *
 * @param cmd Command to parse
 *
 * @return Returns 0 if no errors, or otherwise
 *
 * @see cmd_t
 */
int parse_cmd(cmd_t *cmd);

/**
 * @brief Parses a single sentence
 *
 * @param sentence Sentence to parse
 *
 * @return Returns 0 if transverses the whole sentence, or otherwise
 */
int parse_simple(char *sentence);

/**
 * @brief Parse several sentences connected by a copulative lexeme
 *
 * @param sentence Compound sentence to parse
 *
 * @return Returns 0 if parses all sentences successfully,
 *                -1 if the sentence is empty or @c NULL, or otherwise
 *
 * @todo Refactor: too many calls to `str_trim`, too many iterations and
 *                 too many pointers that may be unneeded
 */
int parse_compound(char *sentence);

/**
 * @brief Macro that evaluates to the size in bits of an array of strings,
 *         (@c char*)
 */
#define arr_len_bits(arr)  (sizeof(arr) / (sizeof(arr[0][0])))

/**
 * @brief Macro that evaluates to the size in bytes of an array of strings,
 *         (@c char*)
 */
#define arr_len_bytes(arr) (arr_len_bits(arr) / 8)

/**
 * @brief An alias for `parse_compound`
 */
#define parse(s) parse_compound(s)


#endif /* PARSER_H */

