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
    erase();
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
    sleep(2);

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
    erase();
    endwin();
    return 0;
}

#define PW_LEN 25
#define NAME_LEN 256

int curses_keyboard()
{
    char name[NAME_LEN];
    char password[PW_LEN];
    char* real_password = "xyzzy";
    int i = 0;

    initscr();

    move(5,10);
    printw("%s", "Please Login:");

    move(7, 10);
    printw("%s", "Enter Name:");
    getstr(name);

    move(9, 10);
    printw("%s", "Enter Password:");
    refresh();

    cbreak();
    noecho();

    memset(password, '\0', sizeof(password));
    while(i < PW_LEN)
    {
	password[i] = getch();
	move(9, 30+i);
	addch('*');
	refresh();
	if(password[i] == '\n') break;
	if(strcmp(password, real_password) == 0) break;
	i++;
    }
    echo();
    nocbreak();

    move(11, 10);
    if(strcmp(password, real_password) == 0) printw("%s", "Correct");
    else printw("%s", "Wrong");
    refresh();
    sleep(1);
    erase();
    endwin();
    return 0;
}

int curses_multiple_windows()
{
    WINDOW *new_window_ptr;
    WINDOW *popup_window_ptr;
    int x_loop;
    int y_loop;
    char a_letter = 'a';

    initscr();

    // fill base screen with characters.
    move(5,5);
    printw("Testing multiple windows");
    refresh();
    sleep(1);

    for(y_loop = 0; y_loop < LINES - 1; y_loop++) {
	for(x_loop = 0; x_loop < COLS - 1; x_loop++) {
	    mvwaddch(stdscr, y_loop, x_loop, a_letter);
	    a_letter++;
	    if(a_letter > 'z') a_letter = 'a';
	}
    }
    refresh();
    sleep(2);

    // create a new window, add text and display
    new_window_ptr = newwin(10, 20, 5, 5);
    mvwprintw(new_window_ptr, 2, 2, "%s", "Hello World");
    mvwprintw(new_window_ptr, 5, 2, "%s", "Notice how very long lines wrap inside the box");
    wrefresh(new_window_ptr);
    sleep(4);

    // change content of background window, on refresh-screen background window is displayed.
    a_letter = '0';
    for(y_loop = 0; y_loop < LINES - 1; y_loop++) {
	for(x_loop = 0; x_loop < COLS - 1; x_loop++) {
	    mvwaddch(stdscr, y_loop, x_loop, a_letter);
	    a_letter++;
	    if(a_letter > '9') a_letter = '0';
	}
    }
    refresh();
    sleep(2);

    // refreshing new window has no effect as it has no changes
    wrefresh(new_window_ptr);
    sleep(2);

    // touch helps us by tricking curses to think that new window has changed
    touchwin(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);

    // add another overlapping window with a box around it.
    popup_window_ptr = newwin(10, 20, 8, 8);
    box(popup_window_ptr, '|', '-');
    mvwprintw(popup_window_ptr, 5, 2, "%s", "Pop Up Window");
    wrefresh(popup_window_ptr);
    sleep(2);

    touchwin(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);
    wclear(new_window_ptr);
    wrefresh(new_window_ptr);
    sleep(2);
    delwin(new_window_ptr);

    touchwin(popup_window_ptr);
    wrefresh(popup_window_ptr);
    sleep(2);
    delwin(popup_window_ptr);

    touchwin(stdscr);
    refresh();
    sleep(2);

    endwin();
    return 0;
}
