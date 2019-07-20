#include <iostream>

#include "concur_export.h"

/// Basic thread demo
int CONCUR_EXPORT exec(std::ostream& out);

/// demo of dangling reference.
/// thread can outlive the parent and it accesses a member local to function.
/// @{
struct func {
    int& i;
    func(int&);
    void operator()();
};
int CONCUR_EXPORT oops();
/// @}[O]
