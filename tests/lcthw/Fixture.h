#ifndef LCTHW_FIXTURE_H
#define LCTHW_FIXTURE_H

#include <memory>
#include "gtest/gtest.h"
#include "dessPatConfig.h"

#ifdef C_SERVICE_MOCK_TESTS
#include "ServicesMocks.h"
#endif // C_SERVICE_MOCK_TESTS

class Fixture : public ::testing::Test
{
public:
    Fixture()
    {
#ifdef C_SERVICE_MOCK_TESTS
        _libc.reset(new ::testing::NiceMock<LibcService>());
#endif // C_SERVICE_MOCK_TESTS
    }

    ~Fixture()
    {
#ifdef C_SERVICE_MOCK_TESTS
        _libc.reset();
#endif // C_SERVICE_MOCK_TESTS
    }
#ifdef C_SERVICE_MOCK_TESTS
    static std::unique_ptr<LibcService> _libc;
#endif // C_SERVICE_MOCK_TESTS
};

#endif
