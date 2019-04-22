///
/// \file ex16.c
/// \brief  exercise 16 structs and pointers
/// \author Mayank Bansal
///

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lcthw.h"

struct Person {
    char* name;
    int age;
    int height;
    int weight;
};

///
/// create a person with given information.
///
/// \param n name
/// \param a age
/// \param h height
/// \param w weight
///
/// \return person
///
struct Person* CreatePerson(const char* n, int a, int h, int w)
{
    struct Person* who = (struct Person*) malloc(sizeof(struct Person));
    assert(who != NULL);

    size_t length = strlen(n) + 1;
    who->name = (char *) malloc(length);
    strcpy(who->name, n);

    who->age = a;
    who->height = h;
    who->weight = w;

    return who;
}

///
/// destroys specified person.
///
/// \param p person
///
void DestroyPerson(struct Person** p)
{
    assert(*p != NULL);
    free((*p)->name);
    free(*p);
    *p = NULL;
}

///
/// prints a person's information.
///
/// \param p person
/// \param out FILE pointer
///
void PrintPerson(FILE* out, struct Person* p)
{
    fprintf(out, "Name : %s\n", p->name);
    fprintf(out, "Age : %d\n", p->age);
    fprintf(out, "Height : %d\n", p->height);
    fprintf(out, "Weight : %d\n", p->weight);
}

