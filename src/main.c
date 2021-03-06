/* Command and parsing test */
#ifdef DEBUG
    #include <stdio.h>
    #include <mcheck.h>
    #include <malloc.h>
#endif

#include <input.h>
#include <parser.h>
#include <strops.h>

#define CMD_PROMPT   " > "
#define CMD_MAX_LEN  (80)


/* Main entry */
int main(void)
{
    char cmd[CMD_MAX_LEN];

#ifdef DEBUG
    puts(" *** DEBUG MODE ON ***");
    puts(" Type 'quit' to exit");
    mallopt(M_CHECK_ACTION, 2);
    mtrace();
#endif

    do {
        get_line(CMD_PROMPT, cmd, CMD_MAX_LEN);
        parse(cmd);
    } while (!streq(cmd, "quit"));

    return 0;
}

