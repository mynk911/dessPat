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
/// print examples of various data types.
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number
///
int ex7(FILE* out)
{
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";

    fprintf(out, "You are %d miles away.\n", distance);
    fprintf(out, "You have %f levels of power.\n", power);
    fprintf(out, "You have %f awesome super powers.\n", super_power);
    fprintf(out, "I have an initial %c.\n", initial);
    fprintf(out, "I have a first name %s.\n", first_name);
    fprintf(out, "I have a last name %s.\n", last_name);
    fprintf(out, "My whole name is %s %c %s.\n",
            first_name, initial, last_name);

    int bugs = 100;
    double bug_rate = 1.2;

    fprintf(out, "You have %d bugs at the imaginary rate of %f.\n",
            bugs, bug_rate);

    unsigned long universe_of_defects = 1UL * 1024L * 1024L * 1024L;
    fprintf(out, "The entire universe has %lu bugs.\n", universe_of_defects);

    double expected_bugs = bugs * bug_rate;
    fprintf(out, "You are expected to have %f bugs.\n", expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    fprintf(out, "That is only a %e portion of the universe.\n",
                                                part_of_universe);

    //this makes no sense, just a demo of something weird
    char nul_byte = '\0';
    int care_percentage = bugs * nul_byte;
    fprintf(out, "Which means you should care %d%%.\n", care_percentage);
    return 0;
}

///
/// a demonstration of if else and command line parameters.
///
/// \param argc c command line arguments count, from main()
/// \param argv c command line arguments from main()
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number.
///
int ex8(int argc, const char *argv[], FILE* out)
{
    int i = 0;

    // since executable is at index 0, argc > 1 if arguments given
    if (argc == 1) {
        fprintf(out, "You only have one argument. You suck.\n");
    } else if (argc > 1 && argc < 4) {
        fprintf(out, "Here's your arguments:\n");

        for (i = 0; i < argc; i++) {
            fprintf(out, "%s ", argv[i]);
        }
    } else  {
        fprintf(out, "You have too many arguments. You suck.\n");
    }

    return 0;
}

///
/// prints out in aloop
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number.
///
int ex9(FILE* out)
{
    int i = 0;
    while (i < 25) {
        fprintf(out, "%d ", i);
        i++;
    }
    fprintf(out, "\n");
    return 0;
}


///
/// switch statement example
///
/// \param argc argument count
/// \param argv arguments
/// \param out file pointer
///
/// \return 0 for success,
///         otherwise some other number
///
int ex10(int argc,const char *argv[], FILE* out)
{
    if (argc != 2) {
        fprintf(out, "ERROR: You need one argument.\n");
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];

        switch (letter) {
        case 'a':
        case 'A':
            fprintf(out, "%d: 'A'\n", i);
            break;

        case 'e':
        case 'E':
            fprintf(out, "%d: 'E'\n", i);
            break;

        case 'i':
        case 'I':
            fprintf(out, "%d: 'I'\n", i);
            break;

        case 'o':
        case 'O':
            fprintf(out, "%d: 'O'\n", i);
            break;

        case 'u':
        case 'U':
            fprintf(out, "%d: 'U'\n", i);
            break;

        case 'y':
        case 'Y':
            if (i > 2) {
                // it's only sometimes Y
                fprintf(out, "%d: 'Y'\n", i);
            }
            break;

        default:
            fprintf(out, "%d: %c is not a vowel\n", i, letter);
        }
    }

    return 0;
}

/*!
 * \brief ex11 strings
 *
 * \param FILE pointer
 *
 * \return 0 for success
 */
int ex11(FILE* out)
{
    int numbers[4] = { 0 };
    char name[4] = { 'a'};
    unsigned int x = (97 << 24) + (68 << 16) + (90 << 8) + 121;
    char y[4];
    memcpy(y,&x,4);
    // first, print them out raw
    fprintf(out, "numbers: %d %d %d %d\n",
           numbers[0], numbers[1], numbers[2], numbers[3]);

    fprintf(out, "name each: %d %d %d %d\n",
           name[0], name[1], name[2], name[3]);

    fprintf(out, "name each: %c %c %c %c\n",
           y[0], y[1], y[2], y[3]);

    x = UINT_MAX;
    memcpy(y,&x,4);
    fprintf(out, "name each: %c %c %c %c\n",
           y[0], y[1], y[2], y[3]);

    fprintf(out, "name: %s\n", name);

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
    fprintf(out, "numbers: %d %d %d %d\n",
           numbers[0], numbers[1], numbers[2], numbers[3]);

    fprintf(out, "name each: %c %c %c %c\n",
           name[0], name[1], name[2], name[3]);

    // print the name like a string
    fprintf(out, "name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    fprintf(out, "another: %s\n", another);

    fprintf(out, "another each: %c %c %c %c\n",
           another[0], another[1], another[2], another[3]);

    return 0;
}

///
/// \brief ex12 arrays and sizeof
///
/// \param out FILE pointer
///
/// \return 0 for success
///
int ex12(FILE *out)
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
    fprintf(out, "The size of an int: %u\n", sizeof(int));
    fprintf(out, "The size of areas (int[]): %u\n", sizeof(areas));
    fprintf(out, "The number of ints in areas: %u\n",
            sizeof(areas) / sizeof(int));
    fprintf(out, "The first area is %d, the 2nd %u.\n", areas[0], areas[1]);

    fprintf(out, "The size of a char: %u\n", sizeof(char));
    fprintf(out, "The size of name (char[]): %u\n", sizeof(name));
    fprintf(out,"The number of chars: %u\n", sizeof(name) / sizeof(char));

    fprintf(out,"The size of full_name (char[]): %u\n", sizeof(full_name));
    fprintf(out, "The number of chars: %u\n",
            sizeof(full_name) / sizeof(char));

    //full_name[12] = 'X';

    fprintf(out, "name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}

///
/// for loop demo in c
///
/// \param argc argument count
/// \param argv arguments
/// \param out FILE pointer
///
/// \return 0 for success
///
int ex13(int argc, const char *argv[], FILE* out)
{
    int i = 0;
    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1; i < argc; i++) {
        fprintf(out, "arg %d: %s\n", i, argv[i]);
    }


    for (i = 0; i < num_states; i++) {
        fprintf(out, "state %d: %s\n", i, states[i]);
    }

    return 0;
}

//forward declarations
int can_print_it(char ch);
void print_letters(const char arg[],size_t n, FILE* out);

void print_arguments(int argc,const char *argv[], FILE* out)
{
    int i = 0;

    for (i = 0; i < argc; i++) {
        print_letters(argv[i],strlen(argv[i]), out);
    }
}

void print_letters(const char arg[], size_t n, FILE* out)
{
    size_t i = 0;

    for (i = 0; i<n; i++) {
        char ch = arg[i];

        if (can_print_it(ch)) {
            fprintf(out, "%c", ch);
        }
    }
        fprintf(out, "\n");
}

int can_print_it(char ch)
{
    return isalpha((unsigned char)ch) ||
		   isblank((unsigned char)ch);
}

///
/// \brief functions demo
///
/// \param argc argument count
/// \param argv arguments
/// \param out FILE pointer
///
/// \return 0 for success
///
int ex14(int argc,const char *argv[], FILE* out)
{
    print_arguments(argc, argv, out);
    return 0;
}

///
/// demo on pointers and their relation to arrays
///
/// \param out FILE pointer
///
/// \return 0 for success
///
int ex15(FILE* out)
{
	    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
        fprintf(out, "%s has %d years alive.\n", names[i], ages[i]);
    }

    fprintf(out, "---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < count; i++) {
        fprintf(out, "%s has %d years alive.\n",
                *(cur_name + i), *(cur_age + i));
    }

    fprintf(out, "---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        fprintf(out, "%s has %d years alive.\n", cur_name[i], cur_age[i]);
    }

    fprintf(out, "---\n");

    // fourth way with pointers in a stupid complex way
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count; cur_name++, cur_age++) {
        fprintf(out, "%s has %d years alive.\n", *cur_name, *cur_age);
    }

    return 0;
}

