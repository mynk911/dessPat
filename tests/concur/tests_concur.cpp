#include <sstream>
#include <chrono>
#include <numeric>

#include "util.hpp"
#include "gtest/gtest.h"
#include "concur.h"

TEST(concurtests, exec)
{
   std::stringstream s;
   concur::exec(s);
   EXPECT_STREQ(s.str().c_str(), "Hello concur World!");
}

TEST(concurtests, oops)
{
    EXPECT_EQ(concur::oops(), 0);
}

TEST(concurtests, WaitForFinish)
{
    EXPECT_EQ(concur::WaitForFinish(), 0);
}

TEST(concurtests, WaitForFinishRAII)
{
    EXPECT_EQ(concur::WaitForFinishRAII(), 0);
}

TEST(concurtests, detachThread)
{
    concur::edit_document("test.test");
}

TEST(concurtests, StdThreadMove)
{
    EXPECT_EQ(concur::std_thread_move(), 0);
}

TEST(concurtests, threadsinVector)
{
    EXPECT_EQ(concur::threads_in_vector(), 0);
}

TEST(concurtests, parallelAccumulate)
{
    std::vector<int> numbers;
    std::vector<int> dist(10, 0);
    std::generate_n(std::back_inserter(numbers), 10000000,
		RandomNumberBetween<std::mt19937,std::uniform_int_distribution<int>>(1, 10));
    auto serial_res = 0;
    auto start = std::chrono::steady_clock::now();
    serial_res = std::accumulate(std::begin(numbers), std::end(numbers), serial_res);
    auto end = std::chrono::steady_clock::now();
    auto serial_dur =
	std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    auto parallel_res = 0;
    start = std::chrono::steady_clock::now();
    parallel_res = concur::parallel_accumualate(std::begin(numbers), std::end(numbers), parallel_res);
    end = std::chrono::steady_clock::now();
    auto parallel_dur =
	std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    ASSERT_EQ(serial_res, parallel_res);
    EXPECT_GE(serial_dur, parallel_dur);
}

TEST(concurtests, mutexExample)
{
    auto ret = concur::mutex_example();
    std::cout << "45 in list : " << ret;
}

TEST(concurtests, unProtectedSharedData)
{
    concur::unprotected_shared_data();
}

TEST(concurtests, threadSafeStack)
{
    concur::threadsafe_stack<int> ts;
    std::thread th1([&ts](){
	 ts.push(5);
    });

    std::thread th2([&ts](){
	try {
	    ts.pop();
	} catch(const std::exception& e){
	    std::cout << e.what() << std::endl;
	}
    });
    if(th1.joinable()) th1.join();
    if(th2.joinable()) th2.join();
}

TEST(concurtests, safeLockWrapper)
{
    concur::some_big_object a,b;
    a.setA(1); b.setA(2);
    concur::safelock_swapper s1(a);
    concur::safelock_swapper s2(b);
    std::thread th1([&s1,&s2](){
	concur::swap(s1, s2);
    });

    std::thread th3([&s1, &s2]() {
	if (s1 == s2)
	    std::cout << "equal ";
	else
	    std::cout << "unequal ";
	});

    std::thread th2([&s1,&s2](){
	concur::swap(s2, s1);
    });

    if (th1.joinable()) th1.join();
    if (th2.joinable()) th2.join();
    if (th3.joinable()) th3.join();
}

concur::hierarchical_mutex hlm(1000);
concur::hierarchical_mutex llm(500);

TEST(concurtests, hierarchicalMutexUsage)
{
    {
	std::lock_guard<concur::hierarchical_mutex> a(hlm);
	std::lock_guard<concur::hierarchical_mutex> b(llm);
    }

    {
	std::lock_guard<concur::hierarchical_mutex> a(llm);
	ASSERT_THROW(std::lock_guard<concur::hierarchical_mutex> b(hlm),
		     std::logic_error);
    }
}
