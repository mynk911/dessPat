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

    if(!isatty(fileno(stdout)))
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

int getchoice(char *greet, char* choices[], FILE* in, FILE* out)
{
    int selected;
    int chosen = 0;
    char **option;
    do {
	fprintf(out, "choice: %s\n", greet);
	option = choices;
	while(*option){
	    fprintf(out, "%s\n", *option);
	    option++;
	}
	do {
	    selected = fgetc(in);
	} while(selected == '\n');
	option = choices;
	while(*option) {
	    if(selected == *option[0]){
		chosen = 1;
		break;
	    }
	    option++;
	}
	if(!chosen){
	    fprintf(out, "incorrect choice, select again");
	}
    } while(!chosen);
    return selected;
}
