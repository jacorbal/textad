#include <stdio.h>
#include <parser.h>


/* Main entry */
int main(void)//int argc, char *argv[])
{
//    char sentence[80] = "gently give lock to her AND take silver Key and run";
//    char sentence[10] = "";
    char sentence[80] = " ask him about the 3 red birds  and run viciously ";

    parse(sentence);

    return 0;
}

