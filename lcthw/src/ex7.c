///
/// \file ex7.c
/// \brief seventh and later exercise implementation
///
/// solution for seventh and later exercises.
///
/// \author Mayank Bansal
///

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#include "lcthw.h"
///
/// exercise seven implementation
///
int ex7(int argc, char* argv[])
{
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";

    printf("You are %d miles away.\n", distance);
    printf("You have %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    printf("My whole name is %s %c %s.\n",
            first_name, initial, last_name);

    int bugs = 100;
    double bug_rate = 1.2;

    printf("You have %d bugs at the imaginary rate of %f.\n",
            bugs, bug_rate);

    unsigned long universe_of_defects = 1L * 1024L * 1024L * 1024L*1024L*1024L*1024L*2L;
    printf("The entire universe has %ld bugs.\n", universe_of_defects);

    double expected_bugs = bugs * bug_rate;
    printf("You are expected to have %f bugs.\n", expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    printf("That is only a %e portion of the universe.\n ",
                                                part_of_universe);

    //this makes no sense, just a demo of something weird
    char nul_byte = '\0';
    int care_percentage = bugs * nul_byte;
    printf("Which means you should care %d%%.\n", care_percentage);
    return 0;
}

/*!
 * \brief ex8 if else if in c
 *
 * \param argc
 * \param argv
 * \return
 */
int ex8(int argc, char *argv[])
{
    int i = 0;

    if (argc == 1) {
        printf("You only have one argument. You suck.\n");
    } else if (argc > 1 && argc < 4) {
        printf("Here's your arguments:\n");

        for (i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } else  {
        printf("You have too many arguments. You suck.\n");
    }

    return 0;
}

/*!
 * \brief ex9 switch;
 *
 * \param argc
 * \param argv
 *
 * \return
 */
int ex9(int argc, char *argv[])
{
    int i;
    while (i < 25) {
        printf("%d\n", i);
        i++;
    }
    return 0;
}

/*!
 * \brief ex10 switch statement
 *
 * \param argc
 * \param argv
 * \return
 */
int ex10(int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];

        switch (letter) {
        case 'a':
        case 'A':
            printf("%d: 'A'\n", i);
            break;

        case 'e':
        case 'E':
            printf("%d: 'E'\n", i);
            break;

        case 'i':
        case 'I':
            printf("%d: 'I'\n", i);
            break;

        case 'o':
        case 'O':
            printf("%d: 'O'\n", i);
            break;

        case 'u':
        case 'U':
            printf("%d: 'U'\n", i);
            break;

        case 'y':
        case 'Y':
            if (i > 2) {
                // it's only sometimes Y
                printf("%d: 'Y'\n", i);
            }
            break;

        default:
            printf("%d: %c is not a vowel\n", i, letter);
        }
    }

    return 0;
}

/*!
 * \brief ex11 strings
 * \param argc
 * \param argv
 * \return
 */
int ex11(int argc, char *argv[])
{
    int numbers[4] = { 0 };
    char name[4] = { 'a'};
    unsigned int x = (97 << 24) + (68 << 16) + (90 << 8) + 121;
    char y[4];
    memcpy(y,&x,4);
    // first, print them out raw
    printf("numbers: %d %d %d %d\n",
           numbers[0], numbers[1], numbers[2], numbers[3]);

    printf("name each: %d %d %d %d\n",
           name[0], name[1], name[2], name[3]);

    printf("name each: %c %c %c %c\n",
           y[0], y[1], y[2], y[3]);

    x = UINT_MAX;
    memcpy(y,&x,4);
    printf("name each: %c %c %c %c\n",
           y[0], y[1], y[2], y[3]);

    printf("name: %s\n", name);

    // setup the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    // setup the name
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    // then print them out initialized
    printf("numbers: %d %d %d %d\n",
           numbers[0], numbers[1], numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
           name[0], name[1], name[2], name[3]);

    // print the name like a string
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
           another[0], another[1], another[2], another[3]);

    return 0;
}

/*!
 * \brief ex12 arrays and sizeof
 * \param argc
 * \param argv
 * \return
 */
int ex12(int argc, char *argv[])
{
    char full_name[] = {
        'Z', 'e', 'd',
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w' , '\0'
    };
    int areas[] = { 10, 12, 13, 14, 20 };
    char name[] = "Zed";


    // WARNING: On some systems you may have to change the
    // %ld in this code to a %u since it will use unsigned ints
    printf("The size of an int: %ld\n", sizeof(int));
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf("The number of ints in areas: %ld\n",
            sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

    printf("The size of a char: %ld\n", sizeof(char));
    printf("The size of name (char[]): %ld\n", sizeof(name));
    printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

    printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
    printf("The number of chars: %ld\n",
            sizeof(full_name) / sizeof(char));

    //full_name[12] = 'X';

    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}

/*!
 * \brief ex13 for loop
 * \param argc
 * \param argv
 * \return
 */
int ex13(int argc, char *argv[])
{
    int i = 0;
    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    states[4] = argv[1];
    argv[2] = states[3];
    int num_states = 5;

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 0; i < argc+1; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }


    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}

//forward declarations
int can_print_it(char ch);
void print_letters(char arg[],int n);

void print_arguments(int argc, char *argv[])
{
    int i = 0;

    for (i = 0; i < argc; i++) {
        print_letters(argv[i],strlen(argv[i]));
    }
}

void print_letters(char arg[], int n)
{
    int i = 0;

    for (i = 0; i<n; i++) {
        char ch = arg[i];

        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int can_print_it(char ch)
{
    return isalpha(ch) || isblank(ch);
}

/*!
 * \brief ex14 functions
 *
 * \param argc
 * \param argv
 *
 * \return
 */
int ex14(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}

