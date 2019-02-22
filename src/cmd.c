/**
 * @file cmd.c
 *
 * @brief Command routines implementation
 */

/* System includes */
#include <stdlib.h>
#include <string.h>

/* Local includes */
#include <cmd.h>


/* Initializes an empty command */
cmd_t *cmd_init_empty(void)
{
    cmd_t *cmd;

    if ((cmd = malloc(sizeof(cmd_t))) == NULL) {
        return NULL;
    }

    cmd->action = NULL;
    cmd->mode = NULL;
    cmd->quantity = NULL;
    cmd->quality = NULL;
    cmd->dobj = NULL;
    cmd->iobj = NULL;

    return cmd;
}

/* Initializes a command indicating every chunck of the sentence */
cmd_t *cmd_init(char *action, char *mode, char *quantity, char *quality,
                char *dobj, char *iobj)
{
    cmd_t *cmd;

    if ((cmd = malloc(sizeof(cmd_t))) == NULL) {
        return NULL;
    }

    if (action == NULL) {
        return NULL;
    }

    cmd->action = action;
    cmd->mode = mode;
    cmd->quantity = quantity;
    cmd->quality = quality;
    cmd->dobj = dobj;
    cmd->iobj = iobj;

    return cmd;
}


/* Destroys a command */
void cmd_destroy(cmd_t *cmd)
{
    free(cmd);
}


