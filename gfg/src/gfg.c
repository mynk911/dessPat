/// \file gfg.c
/// \brief this file contains implementations to some coding problems I am
/// working on.
///
/// I am putting together this file to keep track of problems I have solved as
/// well as a reference when I need a quick brush up of common topics. In this
/// file I include the underlying algorithms used to solve problems as well as
/// relevent references.

#include <limits.h>
#include "gfg.h"

///
/// find the maximum sum contiguous subarray in a given array using the kadane's
/// algorithm which is an O(n) solution to the problem with O(1) auxiliury space.
/// https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
///
int maximum_subarray(int A[], int n)
{
    int maxSoFar = INT_MIN, maxAtIndex = 0, temp = 0;
    for (int index = 0; index<n; index++) {
        //get max for subarray that ends at index
        temp = maxAtIndex + A[index];
        maxAtIndex = temp < A[index] ? A[index] : temp;
        //update global max
        if (maxSoFar < maxAtIndex) {
            maxSoFar = maxAtIndex;
        }
    }

    return maxSoFar;
}


/// uses property of XOR to find missing number.
int find_missing_number(int A[], int n)
{
    /// Calculate X = XOR of first n+1 natural numbers
    int X = 0;
    for(int i = 1; i <= n+1; i++)
        X ^= i;

    /// Calculate Y = XOR of all numbers in array
    int Y = 0;
    for(int i = 0;i < n; i++)
        Y ^= A[i];

    /// return X^Y = missing number
    return X^Y;
}
