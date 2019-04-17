///
/// \file ex1.c
/// \brief first exercise implementation
///
/// solution for first exercise.
///
/// \author Mayank Bansal
///
#include <stdio.h>
#include "lcthw.h"

///
/// prints a number.
///
/// \param out FILE pointer
///
/// \return 0 for success,
///         otherwise any other number
///
int ex1(FILE* out)
{
    int distance = 100;

    fprintf(out, "You are %d miles away.\n", distance);

    return 0;
}
