///
/// \file ex18.c
/// \brief ex 18 function pointers
/// \author Mayank Bansal
///

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "lcthw.h"

void die2(const char* message)
{
    if (errno)
        perror(message);
    else
        printf("ERROR: %s\n", message);
    exit(1);
}

typedef int (*compare_cb) (int a, int b);
typedef int* (*sort_cb) (int* numbers, int count, compare_cb cmp);

int* bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0, i = 0, j = 0;
    
    int *target = malloc(count * sizeof(int));
    if (!target) die2("Memory Error!");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            if (cmp(target[j], target[j + 1]) > 0)
            {
                temp = target[j];
                target[j] = target[j + 1];
                target[j + 1] = temp;
            }
        }
    }
    return target;
} 

int* selection_sort(int* numbers, int count, compare_cb cmp)
{
    int temp = 0, i = 0, j = 0, mindex = 0;

    int* target = malloc(count * sizeof(int));
    if (!target) die2("Memory Error!");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count - 1; i++)
    {
        mindex = i;
        for (j = i + 1; j < count; j++)
        {
            if (cmp(target[mindex], target[j]) > 0)
                mindex = j;
        }
        temp = target[i];
        target[i] = target[mindex];
        target[mindex] = temp;
    }
    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reversed_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    else
        return a % b;
}

void test_sorted(int *numbers, int count, sort_cb sort, compare_cb cmp)
{
    int i = 0;
    int *sorted = sort(numbers, count, cmp);

    if (!sorted) die2("Failed to sort");
    for (i = 0; i < count; i++)
        printf("%d ", sorted[i]);
    printf("\n");
    free(sorted);
    unsigned char* data = (unsigned char*) cmp;
    for (int i = 0; i < 25; i++)
    {
        printf("%02x:", data[i]);
    }
    printf("\n");
}

int ex18(int argc, char** argv)
{
    if (argc < 2) die2("USAGE: dessPat 1 2 4 3 5 ..");
    int count = argc - 1;
    char** inputs = argv + 1;
    int* numbers = malloc(sizeof(int) * count);
    if (!numbers) die2("Memory Error");
    for (int i = 0; i < count; i++)
        numbers[i] = atoi(inputs[i]);
    printf("Bubble Sort:\n");
    test_sorted(numbers, count, bubble_sort, sorted_order);
    test_sorted(numbers, count, bubble_sort, reversed_order);
    test_sorted(numbers, count, bubble_sort, strange_order);
    printf("Selection Sort:\n");
    test_sorted(numbers, count, selection_sort, sorted_order);
    test_sorted(numbers, count, selection_sort, reversed_order);
    test_sorted(numbers, count, selection_sort, strange_order);
    free(numbers);
    return 0;
}