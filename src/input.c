/**
 * @file input.c
 */

#include <stdbool.h>    /* bool, true, false */
#include <stdio.h>      /* fflush, fprintf, fgets */
#include <string.h>     /* strlen */


/* Gets a line from 'stdin' */
int get_line(char *prmpt, char *buf, size_t size)
{
    int ch;
    bool extra; /* Are there extra characters after the stipulated size? */

    /* Get line */
    if (prmpt) {
        fprintf(stdout, "%s", prmpt);
        fflush(stdout);
    }

    /* If no input, return 1 */
    // TODO/FIXME: this should happen when `fgets == NULL`
    if (!fgets(buf, size, stdin)) {
        return 1;   /* no input */
    }

    /* If it was too long, there'll be no newline.  In that case, we
     * flush to end of line so that excess doesn't affect the next call */
    if (buf[strlen(buf) - 1] != '\n') {
        extra = false;
        while (((ch = getc(stdin)) != '\n') && (ch != EOF)) {
            extra = true;
        }
        return (extra) ? 2 /* too long */ : 0 /* okay */;
    }

    /* Otherwise remove newline and give string back to caller */
    buf[strlen(buf) - 1] = '\0';

    return 0;
}

