#include <iostream>
#include <thread>

#include "concur.h"
using namespace std;

void hello()
{
    cout << "Hello concur World!" << endl;
}

struct func {
    int& i;
    static long x;
    func(int& i_) : i(i_) {}
    void operator()()
    {
        for(unsigned j = 0; j<1000000; ++j)
        {
            x+=i;
        }
    }
};
long func::x = 0;

void oops()
{
    int a = 5;
    func mfun(a);
    std::thread th(mfun);
    th.detach();
}
int execAll()
{
    thread t(hello);
    t.join();
    oops();
    return 0;
}
