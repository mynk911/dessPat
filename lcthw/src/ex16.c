///
/// \file ex7.c
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

/*!
 * \brief create a person 
 *
 * \param n name
 * \param a age
 * \param h height
 * \param w weight
 *
 * \return person
 */
struct Person* CreatePerson(char* n, int a, int h, int w)
{
	struct Person* who = (struct Person*) malloc(sizeof(struct Person));
	assert(who != NULL);
	
	who->name = strdup(n);
	who->age = a;
	who->height = h;
	who->weight = w;

	return who;
}

/*!
 * \brief destroy a person
 *
 * \param p person
 */
void DestroyPerson(struct Person* p)
{
	assert(p != NULL);
	free(p->name);
	free(p);
}

/*!
* \brief print a person
*
* \param p person
*/
void PrintPerson(struct Person* p)
{
	printf("Name : %s\n", p->name);
	printf("Age : %d\n", p->age);
	printf("Height : %d\n", p->height);
	printf("Weight : %d\n", p->weight);
}

int ex16(int argc, char* argv[])
{
	struct Person *joe = CreatePerson("Joe Alex", 32, 64, 140);
	struct Person *frank = CreatePerson("Frank Blank", 20, 72, 180);
	printf("Joe is at memory location %p\n", joe);
	PrintPerson(joe);
	printf("Frank is at memory location %p\n", frank);
	PrintPerson(frank);
	DestroyPerson(joe);
	return 0;
}