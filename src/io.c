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

