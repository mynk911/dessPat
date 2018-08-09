#include "gfg.h"
#include <limits.h>
int kadane(int A[], int n)
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
