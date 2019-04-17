/**
  \file lcthw.h
  \brief LCTHW header

  header for lcthw solutions.

  \author Mayank Bansal
  */

#ifndef LCTHW_LCTHW_H_
#define LCTHW_LCTHW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lcthw_export.h"
#include <stdio.h>

/**
 * \brief first exercise
 */
int LCTHW_EXPORT ex1(FILE* out);

/*!
 * \brief second exercise prints and variables
 */
int LCTHW_EXPORT ex3(FILE* out);

/*!
 * \brief seventh exercise data types
 */
int LCTHW_EXPORT ex7(FILE* out);

/*!
 * \brief ex8 if else if in c
 */
int LCTHW_EXPORT ex8(int argc, const char *argv[], FILE* out);

/*!
 * \brief ex9 while loop and boolean expression
 */
int LCTHW_EXPORT ex9(FILE* out);

/*!
 * \brief ex10 switch statement
 */
int LCTHW_EXPORT ex10(int argc,const char *argv[], FILE* out);

/*!
 * \brief ex11 strings
 */
int LCTHW_EXPORT ex11(FILE* out);

/*!
 * \brief ex12 arrays and sizeof
 */
int LCTHW_EXPORT ex12(FILE* out);

/*!
 * \brief ex13 for loop
 */
int LCTHW_EXPORT ex13(int argc, const char *argv[], FILE* out);

/*!
 * \brief ex14 functions
 */
int LCTHW_EXPORT ex14(int argc,const char *argv[], FILE* out);

/*!
 * \brief ex15 pointers
 */
int LCTHW_EXPORT ex15(FILE* out);

/*!
 * \brief represents information of a person.
 */
struct Person;

/*!
 * \brief Create a Person. Ex 16 structs and pointers to them.
 */
LCTHW_EXPORT struct Person*
CreatePerson(const char* n, int a, int h, int w);

/*!
 * \brief Destroy a Person
 */
void LCTHW_EXPORT DestroyPerson(struct Person** p);

/*!
 * \brief Print a person.
 */
void LCTHW_EXPORT PrintPerson(FILE* out, struct Person* p);

/*!
 * \brief ex17 heap and stack memory.
 */
int LCTHW_EXPORT ex17(int argc, const char *argv[]);
int LCTHW_EXPORT ex18(int argc, char *argv[]);
int LCTHW_EXPORT ex19(int argc, char *argv[]);
int LCTHW_EXPORT ex22(int argc, char* argv[]);
int LCTHW_EXPORT ex23(int argc, char* argv[]);
int LCTHW_EXPORT ex24(int argc, char* argv[]);
int LCTHW_EXPORT ex25(int argc, char* argv[]);
#ifdef __cplusplus
}
#endif

#endif
