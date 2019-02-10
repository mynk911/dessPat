///
/// \file ex24.c
/// \brief ex 24 input output and files
/// \author Mayank Bansal
///


#include <stdio.h>
#include "dbg.h"
#include "lcthw.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES, BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue","Green","Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int ex24(int argc, char* argv[])
{
    Person you;
    int i = 0;
    char* in = NULL; int rc;
    printf("fn");
    in = fgets(you.first_name, MAX_DATA - 1, stdin);
    //in = gets(you.first_name);
    check(in != NULL, "fn failed");
    //rc = fscanf(stdin, "%s", &you.first_name);
    //check(rc > 0, "fn failed : enter string");

    printf("ln");
    in = fgets(you.last_name, MAX_DATA - 1, stdin);
    check(in != NULL, "ln failed");
    //rc = fscanf(stdin, "%50s", &you.last_name);
    //check(rc > 0, "ln failed : enter string");

    printf("age");
    rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "age failed : enter number");

    printf("eye color");
    for (i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "eye colr failed : enter number");
    you.eyes = eyes - 1;
    check(you.eyes >= 0 && you.eyes <= OTHER_EYES, "eye color failed : invalid eye color");

    printf("income");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "income failed : enter floating point number");

    printf("you : %s %s %d %s %f\n", you.first_name, you.last_name, you.age, EYE_COLOR_NAMES[you.eyes], you.income);

    return 0;
error:
    return -1;
}