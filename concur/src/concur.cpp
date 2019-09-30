#include <limits>

#include "concur.h"

namespace concur {
void hello(std::ostream& out)
{
    out << "Hello concur World!";
}

int exec(std::ostream& out)
{
    std::thread t(hello, std::ref(out));
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

// demo of waiting for threads. We have to take care of all possible
// execution branches including the possiblility of exception
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

// RAII wait for finish demo. With RAII all execution branches are automatically taken care
// of
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

// an example of not waiting for thread to finish. edit_dociument opens new docs
// in a new thread and each thread individually handles document editing using common code.
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

// threads are move only objects. scoped_thread is an alternative to ThreadGuard
// which moves thread to an internal thread object instead of maintaining reference
// to external object.
int std_thread_move()
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

// an example of threads stored in container.
int threads_in_vector()
{
    std::vector<std::thread> threads;
    for(auto i = 0ul;i < 20; i++)
    {
	threads.push_back(std::thread(do_work, i));
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return 0;
}

// using mutex example
// Not working on ubuntu 16
std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int some_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(some_value);
}

void list_contains(int value_to_find, bool& ret)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    ret = std::find(some_list.begin(), some_list.end(), value_to_find)
	!= some_list.end();
}

// mutex are used for "mutually exclusive" access to shared data by running threads.
int  mutex_example()
{
    scoped_thread st(std::thread(add_to_list, 45));
    bool ret;
    scoped_thread st1(std::thread(list_contains, 45, std::ref(ret)));
    return ret?1:0;
}

void some_data::do_something()
{

}

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
    unprotected = &protected_data;
}

data_wrapper x;

// protection provided by mutex can become meaningless if reference to
// protected data is passed outside the scope of mutex. Here malicious function
// stores pointer to some_data object which is protected in data_wrapper in a
// global object. User then makes a call to unprotected->do_something() without
// mutex protection.
void unprotected_shared_data()
{
    x.process_data(malicious_function);
    unprotected->do_something();
}

void swap(some_big_object& lhs, some_big_object& rhs) noexcept
{
    std::cout << "moving" << lhs.getA() << "to" << rhs.getA() << " ";
    some_big_object t;
    t=lhs;
    lhs=rhs;
    rhs = t;
}

void swap(safelock_swapper& lhs, safelock_swapper& rhs)
{
    if(&lhs == &rhs) return;
    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> b(rhs.m, std::adopt_lock);
    //std::unique_lock<std::mutex> a(lhs.m, std::defer_lock);
    //std::unique_lock<std::mutex> b(rhs.m, std::defer_lock);
    //std::lock(a, b);
    swap(lhs.some_detail, rhs.some_detail);
}

bool safelock_swapper::operator==(safelock_swapper const& rhs) const
{
    if(this == &rhs) return true;
    std::unique_lock<std::mutex> a(this->m);
    some_big_object x = this->some_detail;
    // this is a buggy implementation. Since some_detail is obtained from
    // lhs and rhs at different points in time with different locks, the
    // values may change in between and operator == will give wrong results.
    // striving for minimum granularity should not change the operation 
    // functionality.
    a.unlock();
    std::unique_lock<std::mutex> b(rhs.m);
    some_big_object y = rhs.some_detail;
    b.unlock();
    return x.getA()==y.getA();
}

struct hierarchical_mutex::hierarchical_mutex_impl {
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_heirarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;
    hierarchical_mutex_impl(unsigned long value) : hierarchy_value(value) {}
};

thread_local unsigned long hierarchical_mutex::hierarchical_mutex_impl::this_thread_hierarchy_value
(std::numeric_limits<unsigned long>::max());

void hierarchical_mutex::check_for_hierarchy_violation()
{
    if(pimpl->this_thread_hierarchy_value <= pimpl->hierarchy_value)
	throw std::logic_error("mutex hierarchy violated");
}

void hierarchical_mutex::update_hierarchy_value()
{
    pimpl->previous_heirarchy_value= pimpl->this_thread_hierarchy_value;
    pimpl->this_thread_hierarchy_value= pimpl->hierarchy_value;
}

hierarchical_mutex::hierarchical_mutex(unsigned long value)
    : pimpl(std::make_unique<hierarchical_mutex::hierarchical_mutex_impl>(value))
{}

hierarchical_mutex::~hierarchical_mutex() = default;
void hierarchical_mutex::lock()
{
    check_for_hierarchy_violation();
    pimpl->internal_mutex.lock();
    update_hierarchy_value();
}

void hierarchical_mutex::unlock()
{
    pimpl->this_thread_hierarchy_value = pimpl->previous_heirarchy_value;
    pimpl->internal_mutex.unlock();
}

bool hierarchical_mutex::try_lock()
{
    check_for_hierarchy_violation();
    if(!pimpl->internal_mutex.try_lock())
	return false;
    update_hierarchy_value();
    return true;
}
}
