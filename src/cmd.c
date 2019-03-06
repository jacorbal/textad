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
 * @file cmd.c
 *
 * @brief Command routines implementation
 */

/* System includes */
#include <stdbool.h>    /* bool */
#include <stdlib.h>     /* malloc, free */

/* Local includes */
#include <cmd.h>
#include <strops.h>


/* Initializes a command indicating every chunck of the sentence */
cmd_t *cmd_init(const char *action, const char *mode,
                const char *quantity, const char *quality,
                const char *dobj, const char *iobj)
{
    cmd_t *cmd;

    if (!(cmd = malloc(sizeof(cmd_t)))) {
        return NULL;
    }

    str_cpy_alloc(&cmd->action, action);
    str_cpy_alloc(&cmd->mode, mode);
    str_cpy_alloc(&cmd->quantity, quantity);
    str_cpy_alloc(&cmd->quality, quality);
    str_cpy_alloc(&cmd->dobj, dobj);
    str_cpy_alloc(&cmd->iobj, iobj);

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

