/*
 * dessPat.cpp
 *
 *  Created on: 03-Aug-2018
 *      Author: mayank
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dessPatConfig.h"
#ifdef GOF
#include "gof.h"
#endif
#ifdef GFG
#include "gfg.h"
#endif
int main (int argc, char *argv[])
{
    if (argc < 2)
      {
      fprintf(stdout,"%s Version %d.%d\n",
              argv[0],
              dessPat_VERSION_MAJOR,
              dessPat_VERSION_MINOR);
      fprintf(stdout,"Usage: %s number\n",argv[0]);
      return 1;
      }
  double inputValue = atof(argv[1]);
#ifdef GOF
  double outputValue = mysqrt(inputValue);
#else
  double outputValue = sqrt(inputValue);
#endif
  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
#ifdef GFG
  //get number of test cases
  int t; scanf("%d", &t);
  int A[1010];
  while (t--) {
      //get the size of array
      int n; scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scanf("%d", &A[i]);
      printf("%d\n", kadane(A, n));
  }
#endif // GFG

  return 0;
}



