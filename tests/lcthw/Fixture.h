#ifndef LCTHW_FIXTURE_H
#define LCTHW_FIXTURE_H

#include <memory>
#include "gtest/gtest.h"
#include "ServicesMocks.h"

class Fixture : public ::testing::Test
{
public:
    Fixture()
    {
        _malloc.reset(new ::testing::NiceMock<MallocService>());
    }

    ~Fixture()
    {
        _malloc.reset();
    }
    static std::unique_ptr<MallocService> _malloc;
};

#endif
