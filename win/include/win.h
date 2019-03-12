#include <iostream>

#include "win_export.h"

class WIN_EXPORT win
{
	int t = 7;
public:
    void operator()()
	{
        std::cout<<t<<"\n";
	}
};
