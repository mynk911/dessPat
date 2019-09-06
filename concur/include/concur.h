#ifndef CONCUR_CONCUR_H_
#define CONCUR_CONCUR_H_

#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>

#include "concur_export.h"

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
int CONCUR_EXPORT WaitForFinish();
int CONCUR_EXPORT WaitForFinishRAII();
void CONCUR_EXPORT edit_document(std::string const& filename);
int CONCUR_EXPORT StdThreadMove();
int CONCUR_EXPORT threadsinVector();

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
/// @}

#endif
