#include <iostream>

#include "mcpp_export.h"

class MCPP_EXPORT mcpp_test
{
	int t = 5;
public:
    void operator()()
	{
        std::cout<<t<<"\n";
	}
};
