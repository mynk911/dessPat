///
/// \file ex3.c
/// \brief third exercise implementation
///
/// solution for third exercise.
///
/// \author Mayank Bansal
///

#include <stdio.h>
#include "lcthw.h"

///
/// print statements
///
/// \param out FILE pointer
///
/// \return 0 for success
///         otherwise any other number
///
int ex3(FILE* out)
{
    int age = 23;
    int height = 74;

    fprintf(out, "I am %d years old.\n", age);
    fprintf(out, "I am %d inches tall.\n", height);

    return 0;
}
