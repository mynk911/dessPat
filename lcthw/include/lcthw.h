/**
  @file lcthw.h
  LCTHW header.
  header for lcthw solutions.
  */

#ifndef LCTHW_LCTHW_H_
#define LCTHW_LCTHW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lcthw_export.h"
#include <stdio.h>

/** first exercise.
 * prints a number.
 * @param out FILE pointer
 * @return 0 for success,
 *         otherwise any other number
 */
int LCTHW_EXPORT ex1(FILE* out);

/// second exercise prints and variables
/// print statements
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number
int LCTHW_EXPORT ex3(FILE* out);

/// seventh exercise data types
/// print examples of various data types.
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number
///
int LCTHW_EXPORT ex7(FILE* out);

/// ex8 if else if in c
/// a demonstration of if else and command line parameters.
///
/// \param argc c command line arguments count, from main()
/// \param argv c command line arguments from main()
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number.
int LCTHW_EXPORT ex8(int argc, const char *argv[], FILE* out);

/// ex9 while loop and boolean expression
/// prints out in aloop
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number.
///
int LCTHW_EXPORT ex9(FILE* out);

/// ex10 switch statement
/// switch statement example
///
/// \param argc argument count
/// \param argv arguments
/// \param out file pointer
///
/// \return 0 for success,
///         otherwise some other number
int LCTHW_EXPORT ex10(int argc,const char *argv[], FILE* out);

/// ex11 strings
///
/// \param FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex11(FILE* out);

/// ex12 arrays and sizeof
///
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex12(FILE* out);

/// for loop demo in c
///
/// \param argc argument count
/// \param argv arguments
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex13(int argc,const char *argv[], FILE* out);

/// functions demo
///
/// \param argc argument count
/// \param argv arguments
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex14(int argc,const char *argv[], FILE* out);

/// demo on pointers and their relation to arrays
///
/// \param out FILE pointer
///
/// \return 0 for success
int LCTHW_EXPORT ex15(FILE* out);

struct Person;

/// Ex 16 structs and pointers to them.
/// create a person with given information.
///
/// \param n name
/// \param a age
/// \param h height
/// \param w weight
///
/// \return person
LCTHW_EXPORT struct Person*
CreatePerson(const char* n, int a, int h, int w);

/// destroys specified person.
///
/// \param p person
void LCTHW_EXPORT DestroyPerson(struct Person** p);

/// prints a person's information.
///
/// \param p person
/// \param out FILE pointer
void LCTHW_EXPORT PrintPerson(FILE* out, struct Person* p);

/*! ex17 heap and stack memory.
 * \param argc argument count
 * \param argv an array of argc c string pointers
 * \param buf output buffer
 */
int LCTHW_EXPORT ex17(int argc, const char *argv[], char* buf);

/// compare and sort function typedefs
/// @{
typedef int (*compare_cb) (int a, int b);
typedef int* (*sort_cb) (int* numbers, int count, compare_cb cmp);
/// @}

LCTHW_EXPORT int sorted_order(int a, int b);
LCTHW_EXPORT int reversed_order(int a, int b);
LCTHW_EXPORT int strange_order(int a, int b);
LCTHW_EXPORT int* bubble_sort(int *numbers, int count, compare_cb cmp);
LCTHW_EXPORT int* selection_sort(int *numbers, int count, compare_cb cmp);

/// ex18 function pointers via sorting examples.
/// \param argc count of arguments
/// \param argv an array of argc c string pointers
/// \param buf output buffer
/// \param sort sorting function
/// \param cmp comparison function
/// \return 0 for success.
///
int LCTHW_EXPORT ex18(int argc,const char **argv,
		      char* buf, sort_cb sort, compare_cb cmp);

LCTHW_EXPORT int test_check(const char* file_name);
LCTHW_EXPORT int test_sentinel(int code);
LCTHW_EXPORT int test_check_mem();
LCTHW_EXPORT int test_check_debug();

extern int THE_SIZE;
LCTHW_EXPORT int get_age();
LCTHW_EXPORT int* age();
LCTHW_EXPORT void set_age(int age);
LCTHW_EXPORT double update_ratio(double ratio);
LCTHW_EXPORT int get_size();
LCTHW_EXPORT void scope_demo(int count);

LCTHW_EXPORT int normal_copy(char* from, char* to, int count);
LCTHW_EXPORT int duffs_device(char* from, char* to, int count);

LCTHW_EXPORT int ex24(FILE* in, FILE* out);
LCTHW_EXPORT int ex25(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif

#endif
