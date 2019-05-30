#include "Fixture.h"

#ifdef C_SERVICE_MOCK_TESTS
std::unique_ptr<LibcService> Fixture::_libc;
#endif // C_SERVICE_MOCK_TESTS
