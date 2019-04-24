#include "Fixture.h"
#include "FakeServices.h"

extern "C" void* my_malloc(size_t size)
{
    return Fixture::_libc->malloc(size);
}

extern "C" FILE* my_fopen(const char* filename, const char* modes)
{
    return Fixture::_libc->fopen(filename, modes);
}
