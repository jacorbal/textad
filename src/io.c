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
 * @file io.c
 */

/* System includes */
#include <stdlib.h>

/* Local includes */
#include <flag.h>
#include <io.h>


/*  */
printer_t *printer_init(int (*print)(const char *))
{
    printer_t *printer;

    if (!print) {
        return NULL;
    }

    if (!(printer = malloc(sizeof(printer_t)))) {
        return NULL;
    }

    printer->print = print;

    return printer;
}


void printer_destroy(printer_t *printer)
{
    free(printer);
}


/* Prints information depending on the status of the flag */
int printer_flag(printer_t *printer, flag_t *flag)
{
    if (!flag->yes || !flag->no) {
        return 0;
    }

    if (flag->state) {
        return printer->print(flag->yes);
    } else {
        return printer->print(flag->no);
    }
}

