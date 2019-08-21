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
    th.join();
    // thread is detached but uses local state,
    // can cause undefined behavior
    // th.detach();
    return 0;
}

int WaitForFinish()
{
    int sll = 0;
    func my_func(sll);
    std::thread t(my_func);
    try {
        //
    } catch (...) {
        t.join();
        throw;
    }
    t.join();
    return 0;
}

class ThreadGuard
{
    std::thread& _t;
public:
    explicit ThreadGuard(std::thread& t)
        :_t(t)
    {}

    ~ThreadGuard()
    {
        if(_t.joinable())
            _t.join();
    }

    ThreadGuard(const ThreadGuard& ) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

int WaitForFinishRAII()
{
    int sll = 0;
    func my_func(sll);
    std::thread th(my_func);
    ThreadGuard g(th);
    return 0;
}
