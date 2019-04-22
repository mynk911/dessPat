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
        _libc.reset(new ::testing::NiceMock<LibcService>());
    }

    ~Fixture()
    {
        _libc.reset();
    }
    static std::unique_ptr<LibcService> _libc;
};

#endif
