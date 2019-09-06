#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <term.h>
#include <curses.h>

#include "lin.h"

static FILE* output_stream = (FILE*)0;

char* menu[] = {
    "a - add new record",
    "b - delete record",
    "q - quit",
    NULL
};

int getchoice(char *greet, char* choices[], FILE* in, FILE* out);
int char_to_terminal(int char_to_write);

int dev_tty()
{
    int choice = 0;
    FILE* input = NULL;
    FILE* output = NULL;
    struct termios initial_settings, new_settings;

    if(!isatty(fileno(stdout)))
       fprintf(stderr, "Not a terminal. OK\n");

    input = fopen("/dev/tty", "r");
    output = fopen("/dev/tty", "w");
    if(!input || !output)
    {
	fprintf(stderr, "unable to open /dev/tty\n");
	return -1;
    }

    tcgetattr(fileno(input), &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    if(tcsetattr(fileno(input), TCSANOW, &new_settings) != 0) {
	fprintf(stderr, "could not save attributes\n");
    }
    do {
	choice = getchoice("Please select an action", menu, input, output);
	printf("you have chosen: %c\n", choice);
	sleep(1);
    } while(choice != 'q');
    tcsetattr(fileno(input), TCSANOW, &initial_settings);
    return choice;
}

int getchoice(char *greet, char* choices[], FILE* in, FILE* out)
{
    int selected = 0;
    int chosen;
    int screenrow, screencol = 10;

    char **option;
    char *cursor, *clear;

    output_stream = out;

    setupterm(NULL, fileno(out), (int *)0);
    cursor = tigetstr("cup");
    clear = tigetstr("clear");

    screenrow = 4;
    tputs(clear, 1, char_to_terminal);
    tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
    fprintf(out, "choice: %s\n", greet);
    screenrow += 2;
    option = choices;
    while(*option){
	tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
	fprintf(out, "%s\n", *option);
	screenrow++;
	option++;
    }
    do {
	selected = fgetc(in);
	option = choices;
	while(*option) {
	    if(selected == *option[0]){
		chosen = 1;
		break;
	    }
	    option++;
	}
	if(!chosen){
	    tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
	    fprintf(out, "incorrect choice, select again");
	}
    } while(!chosen);
    tputs(clear, 1, char_to_terminal);
    return selected;
}

int char_to_terminal(int char_to_write)
{
    if(output_stream) putc(char_to_write, output_stream);
    return 0;
}

#define PASSWORD_LEN 8

int pass_word()
{
    struct termios initialrsettings, newrsettings;
    char password[PASSWORD_LEN + 1];
    tcgetattr(fileno(stdin), &initialrsettings);
    newrsettings = initialrsettings;
    newrsettings.c_lflag &= ~ECHO;
    printf("Enter Password: ");
    if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
	fprintf(stderr, "Could not set attributes\n");
    } else {
	fgets(password, PASSWORD_LEN + 1, stdin);
	tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
	fprintf(stdout, "\n You entered %s\n", password);
    }
    return 0;
}

static struct termios initial_settings, new_settings;
static int peek_character;
void init_keyboard();
void close_keyboard();
int kbhit();
int readch();

int kbhit_example()
{
    int ch = 0;
    init_keyboard();
    while(ch!='q') {
	printf("looping\n");
	sleep(1);
	if(kbhit()) {
	    ch = readch();
	    printf("You hit %c\n",ch);
	}
    }
    close_keyboard();
    return 0;
}

void init_keyboard()
{
    tcgetattr(0, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
    char ch;
    int nread;
    if(peek_character != -1)
	return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0, &ch, 1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);

    if(nread == 1)
    {
	peek_character = ch;
	return 1;
    }
    return 0;
}

int readch()
{
    char ch;
    if(peek_character!=-1)
    {
	ch = peek_character;
	peek_character = -1;
	return ch;
    }
    read(0, &ch, 1);
    return ch;
}

int curses_basic()
{
    initscr();
    move(5, 15);
    printw("%s","Hello World");
    refresh();
    sleep(2);
    endwin();
    return 0;
}

int curses_char_attr()
{
    const char witch_one[] = " First Witch ";
    const char witch_two[] = " Second Witch ";
    const char *scan_ptr;

    initscr();

    move(5, 15);
    attron(A_BOLD);
    printw("%s", "Macbeth");
    attroff(A_BOLD);
    refresh();
    sleep(1);

    move(8, 15);
    attron(A_DIM);
    printw("%s", "Thunder and Lightning");
    attroff(A_DIM);
    refresh();
    sleep(1);

    move(10, 10);
    printw("When shall we meet again");
    move(11, 23);
    printw("In thunder, lightning or in rain ?");
    move(13, 10);
    printw("When the hurlyburly's done, ");
    move(14, 23);
    printw("When the battle's lost and won.");
    refresh();
    sleep(5);

    attron(A_DIM);
    scan_ptr = witch_one + strlen(witch_one) - 1;
    while(scan_ptr != witch_one) {
	move(10, 10);
	insch(*scan_ptr--);
    }

    scan_ptr = witch_two + strlen(witch_two) - 1;
    while(scan_ptr != witch_two) {
	move(13, 10);
	insch(*scan_ptr--);
    }
    attroff(A_DIM);

    refresh();
    sleep(1);

    endwin();
    return 0;
}
