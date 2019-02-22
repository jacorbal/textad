/**
 * @file cmd.h
 *
 * @brief Command routines
 */

#ifndef CMD_H
#define CMD_H


/**
 * @typedef cmd_t
 *
 * @brief Command to be processed
 *
 * All sentences are imperative in the form:
 *
 *    <action> [<mode>] [<quality>] [<quantity>] [<d. object>] [<i. object>]
 *    -------- -------- ----------- ------------ ------------- -------------
 *       |        |         |            |            |              |
 *     VERB    ADVERB    ADJECTIVE    NUMBER     COMMON NOUN  PRONOUN or
 *      |                                                     PROPER NOUN
 *      |
 *    Mandatory
 *
 * Examples:
 *   * INVENTORY (verb -> special)
 *   * GET KEY (verb + noun)
 *   * GIVE KEY TO HIM (verb + noun + "to" + iobj)
 *   * ASK HER ABOUT MAGIC (verb + pronoun + "about" + dobj)
 *   * LOOK IN RED CLOSET (verb + "in" + adj + dobj)
 *   * TAKE SWORD AND KILL MONSTER FEROCEOSLY
 *          (verb + dobj) + "AND" + (verb + dobj + adv)
 *   * ASK HIM SOFTLY ABOUT THE THREE RED BIRDS
 *          (verb + iobj + adv + "about" + "the" + num + adj + noun)
 *
 * The <action> (verb) is always required.  It can be a tipical action,
 * but also an special command (such as "inventory"), an answer ("yes",
 * "no", "maybe"), a direction ("north", "east"), &c.
 *
 * When a special action is invoked, everything else is ignored:
 *   * LOAD QUICKLY (load + <ignored>)
 *   * SAVE GENTLY (save + <ignored>)
 *   * INVENTORY NOW (inventory + <ignored>)
 *
 * Prepositions, articles and conjunctions are ignored, except 'and' to
 * couple several actions into one, eg, "LOOK ROOM AND TAKE KEY".
 */
typedef struct {
    char *action;   /**< Action (verb) */
    char *mode;     /**< Way this action is performed (adverb) */
    char *quantity; /**< Number of the object (adjective in partitive sense) */
    char *quality;  /**< Quality of the object (adjective) */
    char *dobj;     /**< Direct object (common nouns) */
    char *iobj;     /**< Indirect object (proper nouns and pronouns) */
} cmd_t;


/* Public interface */
/**
 * @brief Initializes a command allocating needed memory
 *
 * @return Pointer to the newly created command, or @c NULL otherwise
 */
cmd_t *cmd_init_empty(void);

/**
 * @brief Initializes a command allocating needed memory
 *
 * @param action   Verb
 * @param mode     Adverb
 * @param quality  Adjective
 * @param quantity Number
 * @param dobj     Direct object
 * @param iobj     Indirect object
 *
 * @return Pointer to the newly created command, or @c NULL otherwise
 */
cmd_t *cmd_init(char *action, char *mode, char *quantity, char *quality,
                char *dobj, char *iobj);

/**
 * @brief Frees allocated memory for a previously allocated command
 *
 * @param cmd Command to deallocate from memory
 */
void cmd_destroy(cmd_t *cmd);

/**
 * @brief Macro that evaluates to the command @e action 'property'
 */
#define cmd_action (cmd->action)

/**
 * @brief Macro that evaluates to the command @e mode 'property'
 */
#define cmd_mode (cmd->mode)

/**
 * @brief Macro that evaluates to the command @e quantity 'property'
 */
#define cmd_quantity (cmd->quantity)

/**
 * @brief Macro that evaluates to the command @e quality 'property'
 */
#define cmd_quality (cmd->quality)

/**
 * @brief Macro that evaluates to the command @e dobj 'property'
 */
#define cmd_dobj (cmd->dobj)

/**
 * @brief Macro that evaluates to the command @e iobj 'property'
 */
#define cmd_iobj (cmd->iobj)


#endif /* CMD_H */
