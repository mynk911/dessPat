#include <thread>

#include "concur.h"
using namespace std;

void hello(std::ostream& out)
{
    out << "Hello concur World!";
}

int exec(std::ostream& out)
{
    thread t(hello, std::ref(out));
    t.join();
    return 0;
}

func::func(int& i_)
    :i(i_)
{}

void func::operator()()
{
    for(unsigned j = 0; j<1000000;++j)
	i++;
}

int oops()
{
    int sll = 0;
    func my_func(sll);
    std::thread th(my_func);
    th.detach();
    return 0;
}
