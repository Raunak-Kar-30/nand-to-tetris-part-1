#include "assembler.h"
#include <errno.h>

// Throw an error at a particular line
void error(char *message, int line_number)
{
    printf("%s\nIn Line %d\n", message, line_number);
    die("Execution failed");
}


// Stop executing the program gracefully
void die(char *message)
{
    fprintf(stderr, "%s\nError : %d\n", message, errno);
    exit(1);
}