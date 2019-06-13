#ifndef WIN_H_
#define WIN_H_

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

#endif // WIN_H_
