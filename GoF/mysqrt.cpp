/*
 * mysqrt.cpp
 *
 *  Created on: 06-Aug-2018
 *      Author: mayank
 */

#include <math.h>
#include "gof.h"
#include "dessPatConfig.h"
double mysqrt(double x)
{
#if defined (HAVE_LOG) && defined (HAVE_EXP)
    return exp(log(x)*0.5);
#else
    return sqrt(x);
#endif
}



