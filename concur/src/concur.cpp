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

void open_document_and_display_gui(std::string const& filename)
{
    // brings the document matching filename in focus.
    // if no document matching filename is open, open it.
}

bool done_editing()
{
    // should return true until the doc is closed.
    static int x = 1;
    if(x == 1)
    {
	x++;
	return false;
    }
    return true;
}

enum class user_command {
    open_new_document,
	close_document,
	invalid
};

user_command get_user_input()
{
    return user_command::open_new_document;
}

std::string const get_filename_from_user()
{
    //prompts user to provide filename for new document
    return std::string("test.txt");
}

void process_user_input(user_command cmd)
{

}

void edit_document(std::string const& filename)
{
    open_document_and_display_gui(filename);
    while(!done_editing())
    {
	user_command cmd = get_user_input();
	if(cmd==user_command::open_new_document)
	{
	    std::string const new_name = get_filename_from_user();
	    std::thread t(edit_document, new_name);
	    t.detach();
	} else {
	    process_user_input(cmd);
	}
    }
}

class scoped_thread
{
    std::thread t;
public:
    explicit scoped_thread(std::thread t_):
	t(std::move(t_))
    {
	if(!t.joinable()) throw std::logic_error("No thread");
    }
    ~scoped_thread()
    {
	t.join();
    }
    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
};

int StdThreadMove()
{
    int sll = 3;
    func mfn(sll);
    std::thread th(mfn);
    scoped_thread t(std::move(th));
    return 0;
}

void do_work(unsigned int id)
{
    for(int i = 0; i < 10000000; i++);
}

int threadsinVector()
{
    std::vector<std::thread> threads;
    for(auto i = 0ul;i < 20; i++)
    {
	threads.push_back(std::thread(do_work, i));
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return 0;
}
