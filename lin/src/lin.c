#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lin.h"

char* menu[] = {
    "a - add new record",
    "b - delete record",
    "q - quit",
    NULL
};

int getchoice(char *greet, char* choices[], FILE* in, FILE* out);

int dev_tty()
{
    int choice = 0;
    FILE* input = NULL;
    FILE* output = NULL;
    
    if(isatty(fileno(stdout)))
       fprintf(stderr, "Not a terminal. OK\n");
    
    input = fopen("/dev/tty", "r");
    output = fopen("/dev/tty", "w");
    if(!input || !output)
    {
	fprintf(stderr, "unable to open /dev/tty\n");
        return -1;
    }
    
    do {
	choice = getchoice("Please select an action", menu, input, output);
	printf("you have chosen: %c\n", choice);
    } while(choice != 'q');
    return choice;
}

