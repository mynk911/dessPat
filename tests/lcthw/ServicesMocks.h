#ifndef LCTHW_SERVICES_MOCKS_H_
#define LCTHW_SERVICES_MOCKS_H_

#include "gmock/gmock.h"

class MallocService
{
public:
    virtual ~MallocService() {}
    MOCK_METHOD1(malloc, void*(size_t));
};
#endif
