#include <iostream>

#include "lin_export.h"

class LIN_EXPORT lin
{
	int t = 6;
public:
    void operator()()
	{
        std::cout<<t<<"\n";
	}
};
