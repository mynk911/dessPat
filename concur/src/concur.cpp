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
