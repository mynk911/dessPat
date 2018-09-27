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
#ifdef LCTHW
#include "lcthw.h"
#endif
int main (int argc, char *argv[])
{
      fprintf(stdout,"%s Version %d.%d\n",
              argv[0],
              dessPat_VERSION_MAJOR,
              dessPat_VERSION_MINOR);

#ifdef GOF
#endif

#ifdef GFG
  //get number of test cases
  int t;
  int A[1010];
  printf("maximum_subarray : \n");
  scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scanf("%d", &A[i]);
      printf("%d\n", maximum_subarray(A, n));
  }
  printf("find_missing_number : \n");
  scanf("%d", &t);
  while (t--) {
      //get the size of array
      int n; scanf("%d", &n);
      //get array entries
      for (int i = 0; i < n; i++)
          scanf("%d", &A[i]);
      printf("%d\n", find_missing_number(A, n));
  }
#endif // GFG

#ifdef LCTHW
  //exercise 1
  ex1(argc,argv);
#endif
  return 0;
}



