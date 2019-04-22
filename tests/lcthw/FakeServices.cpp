#include "Fixture.h"

extern "C" void* my_malloc(size_t size)
{
    return Fixture::_malloc->malloc(size);
}
