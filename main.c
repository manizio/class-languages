#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state_machine.h"

int main(int argc, char *argv[])
{
 
    if (argc == 2)
    {
        struct afd machine;
        initializeAFD(&machine);

        char *input = argv[1];
        int isMatch = match(input, &machine);

        if (isMatch)
        {
            printf("Valid string\n");
        } else
        {
            printf("Invalid string\n");
        }
        destroy_afd(&machine);
    } else {
        printf("Invalid use\n");
    }


    return 0;

}