/**
 * @file input.h
 *
 * @brief Input routines declaration
 */

#ifndef INPUT_H
#define INPUT_H

#include <stddef.h> /* size_t */


/* Public interface */
/**
 * @brief Gets a line from @e stdin
 *
 * @param prmpt Prompt symbol before input, or @NULL to show nothing
 * @param buf   Buffer where to store the input string
 * @param size  Buffer size
 *
 * @return Returns 0 if the string is succesfully gotten,
 *                 1 if the input string is empty, or
 *                 2 if the input string is longer than the buffer,
 *                 where it will be truncated
 *
 * @bug The function does not return 1 on empty input.  The test is
 *      performed by using @e fgets, that returns "@c NULL on error or
 *      when the end of file (EOF) occurs while no characters have been
 *      read" (man fgetc(3))
 */
int get_line(const char *prmpt, char *buf, size_t size);


#endif /* ! INPUT_H */

