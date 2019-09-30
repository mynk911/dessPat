#ifndef CONCUR_CONCUR_H_
#define CONCUR_CONCUR_H_

#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <list>
#include <mutex>
#include <exception>
#include <memory>
#include <stack>

#include "concur_export.h"

namespace concur {
/// Basic thread demo
int CONCUR_EXPORT exec(std::ostream& out);

/// demo of dangling reference.
/// thread can outlive the parent and it accesses a member local to function.
/// @{
struct func {
    int& i;
    func(int&);
    void operator()();
};
int CONCUR_EXPORT oops();
/// @}
int CONCUR_EXPORT WaitForFinish();
int CONCUR_EXPORT WaitForFinishRAII();
void CONCUR_EXPORT edit_document(std::string const& filename);
int CONCUR_EXPORT std_thread_move();
int CONCUR_EXPORT threads_in_vector();

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

// a naive parallel implementation of std::accumulate. Makes use of hardware_concurrency
// to find threads supported by system.
template<typename Iterator,typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
	result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumualate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);
    if(!length)
	return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads =
	std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    unsigned long const block_size = length/num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    Iterator block_start = first;
    for(auto i = 0ul; i<(num_threads-1);i++)
    {
	Iterator block_end = block_start;
	std::advance(block_end, block_size);
	threads[i]=std::thread(accumulate_block<Iterator,T>(),
			       block_start, block_end, std::ref(results[i]));
	block_start=block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads-1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(), results.end(), init);
}

int CONCUR_EXPORT mutex_example();

class some_data
{
    int a;
    std::string b;
public:
    void do_something();
};

class data_wrapper
{
    some_data data;
    std::mutex m;
public:
    template < typename Function >
    void process_data(Function func)
    {
	std::lock_guard<std::mutex> l(m);
	func(data);
    }
};

void CONCUR_EXPORT unprotected_shared_data();

// identifying race conditions inherent in interface
// a thread safe stack

struct empty_stack : std::exception
{
public:
    virtual char const * what() const noexcept {
	return "stack empty";
    }
};

template < typename T>
class threadsafe_stack
{
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other)
    {
	std::lock_guard<std::mutex> lock(other.m);
	data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value)
    {
	std::lock_guard<std::mutex> lock(m);
	data.push(new_value);
    }
    std::shared_ptr<T> pop()
    {
	std::lock_guard<std::mutex> lock(m);
	if (data.empty()) throw empty_stack();
	auto res = std::make_shared<T>(data.top());
	data.pop();
	return res;
    }
    void pop(T& value)
    {
	std::lock_guard<std::mutex> lock(m);
	if (data.empty()) throw empty_stack();
	value = data.top();
	data.pop();
    }
    bool empty() const
    {
	std::lock_guard<std::mutex> lock(m);
	return data.empty();
    }
private:
    std::stack<T> data;
    mutable std::mutex m;
};

class CONCUR_EXPORT some_big_object
{
    int a;
public:
    int getA() { return a;}
    void setA(int x) { a=x; }
};

class safelock_swapper;

void CONCUR_EXPORT swap(safelock_swapper& lhs, safelock_swapper& rhs);

// demo of std::lock facility to lock two or mutex with deadlock
//    avoidance
class CONCUR_EXPORT  safelock_swapper
{
    some_big_object some_detail;
    mutable std::mutex m;
public:
    safelock_swapper(some_big_object const& sd) : some_detail(sd) {}
    friend void swap(safelock_swapper& lhs, safelock_swapper& rhs);
    bool operator==(safelock_swapper const& rhs) const;
};

// a mutex which can be obtained by a thread if the mutex held already has higher
// hierarchy value(implying a higher level code protection)
class CONCUR_EXPORT hierarchical_mutex
{
    struct hierarchical_mutex_impl;
    std::unique_ptr< hierarchical_mutex_impl> pimpl;
    void check_for_hierarchy_violation();
    void update_hierarchy_value();
public:
    virtual void lock();
    virtual void unlock();
    virtual bool try_lock();
    explicit hierarchical_mutex(unsigned long);
    ~hierarchical_mutex();
};

}
#endif
