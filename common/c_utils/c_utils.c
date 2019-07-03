#include "c_utils.h"

void
swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int
cmp_char(const void* a, const void* b)
{
    return *(char *)a - *(char *)b;
}

void
swap_char(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void
reverse_string(char* a , char* b)
{
    while(a < b)
    {
        swap_char(a, b);
        a++; b--;
    }
}
