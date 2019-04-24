#ifndef TESTS_FAKE_SERVICES_H
#define TESTS_FAKE_SERVICES_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void* my_malloc(size_t size);
FILE* my_fopen(const char* filename, const char* modes);

#ifdef __cplusplus
}
#endif

#endif //TESTS_FAKE_SERVICES_H
