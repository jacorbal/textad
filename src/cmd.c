/**
 * @file cmd.c
 *
 * @brief Command routines implementation
 */

/* System includes */
#include <stdlib.h>

/* Local includes */
#include <cmd.h>
#include <strops.h>


/* Initializes a command indicating every chunck of the sentence */
cmd_t *cmd_init(char *action, char *mode, char *quantity, char *quality,
                char *dobj, char *iobj)
{
    cmd_t *cmd;

    if (!(cmd = malloc(sizeof(cmd_t)))) {
        return NULL;
    }

    if (!action) {
        return NULL;
    }

    cmd->action = str_alloc_as(action);
    cmd->mode = str_alloc_as(mode);
    cmd->quantity = str_alloc_as(quantity);
    cmd->quality = str_alloc_as(quality);
    cmd->dobj = str_alloc_as(dobj);
    cmd->iobj = str_alloc_as(iobj);

    str_cpy(cmd->action, action);
    str_cpy(cmd->mode, mode);
    str_cpy(cmd->quantity, quantity);
    str_cpy(cmd->quality, quality);
    str_cpy(cmd->dobj, dobj);
    str_cpy(cmd->iobj, iobj);

    return cmd;
}


/* Destroys a command */
void cmd_destroy(cmd_t *cmd)
{
    free(cmd->action);
    free(cmd->mode);
    free(cmd->quantity);
    free(cmd->quality);
    free(cmd->dobj);
    free(cmd->iobj);

    free(cmd);
}

