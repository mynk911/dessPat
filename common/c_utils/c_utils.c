#include "c_utils.h"

void swap(int A[], size_t a, size_t b)
{
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}
