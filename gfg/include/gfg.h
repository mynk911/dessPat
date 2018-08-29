/**
  \file gfg.h
  \author mayank bansal

  \brief this file contains solutions to some coding problems I am working on.

  I am putting together this file to keep track of problems I have solved as
  well as a reference when I need a quick brush up of common topics.
  */

#ifndef GFG_GFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gfg_export.h"
/**
  \brief find the maximum sum contiguous subarray.

  find the maximum sum contiguous subarray in a given array usig the kadane's algorithm
  which is an O(n) solution to the problem with O(1) auxiliury space.
  https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
  
  Usage : 

  \code
  int array[] = {1, 2, 3, -6, 8};
  int res = kadane(array, 5);
  printf("res : %d", res); // res : 8
  \endcode
 
  \param A array of integers.
  \param n size of the integer array.
  \return sum of the maximum sum contiguous subarray

*/
int GFG_EXPORT kadane(int[] A, int n);

#ifdef __cplusplus
}
#endif 
#endif 
