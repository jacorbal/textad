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
 * @file io.h
 *
 * @brief Input/Output routines declaration
 */

#ifndef IO_H
#define IO_H


/**
 * @typedef printer_t
 *
 * @brief Printer structure, with a pointer to a function to print
 *
 * Why bother with this?  In the future will be easier to use made
 * functions to format the output strings, using colors or identifying
 * keywords on the string, and point to that here.
 */
typedef struct {
//    const char *s;              /**< String to print */
    int (*print)(const char *); /**< Function to print with */
} printer_t;


/* Public interface */
/**
 * @brief Initializes printer "object"
 */
printer_t *printer_init(int (*print)(const char *));

/**
 * @brief Frees allocated memory
 *
 * @param printer Printer "object" to deallocate
 */
void printer_destroy(printer_t *printer);

/**
 * @brief Prints a flag string depending on the value of its state
 *
 * @param printer Printer structure
 *
 * @return Returns a non negative number on success, or 0 if there are
 *         no valid strings to print
 *
 * @see flag_t
 */
int printer_flag(printer_t *printer, flag_t *flag);

/**
 * @brief Macro that evaluates to the initialization of the printer
 *        "object" using the @e puts function
 */
//#define printer_init_puts()  printer_init(puts)

/**
 * @brief Macro that evaluates to the printing of a string (print string)
 */
#define ps(printer, string)  (printer->print(string))

/**
 * @brief Macro that evaluates to the printing of a flag (print flag)
 *
 * @see flag_t
 */
#define pf(printer, flag)  printer_flag(printer, flag)


#endif /* IO_H */

