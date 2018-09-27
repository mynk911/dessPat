/**
  \file gfg.h

  \brief this file contains interfaces to functions solvingproblems I am working
  on.

  I am putting together this file to keep track of problems I have solved as
  well as a reference when I need a quick brush up of common topics. In this
  file I try to explain the purpose and usage of each function.

  \author mayank bansal
  */

#ifndef GFG_GFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gfg_export.h"
/**
  \brief find the maximum sum contiguous subarray.

  find the maximum sum contiguous subarray in a given array with a
  O(n) time complexity and with O(1) auxiliury space.

  Usage : 

  \code
  int array[] = {1, 2, 3, -6, 8};
  int res = maximum_subarray(array, 5);
  printf("res : %d", res); // res : 8
  \endcode
 
  \param A array of integers.
  \param n size of the integer array.
  \return sum of the maximum sum contiguous subarray

*/
int GFG_EXPORT maximum_subarray(int A[], int n);

/*!
 * \brief find missing number in given array of natural numbers.
 *
 * O(n) time complexity with O(1) auxiliury space.
 *
 * \code
 * int array[] = {1,2,3,5,6};
 * int res = find_missing_number(array, 5);
 * printf("res : %d", res); // res : 4)
 * \endcode
 *
 * \param A array of integers in range (1,n+1) with one number missing
 * \param n size of array A
 * \return missing number in array
 */
int GFG_EXPORT find_missing_number(int A[], int n);

#ifdef __cplusplus
}
#endif 
#endif 
