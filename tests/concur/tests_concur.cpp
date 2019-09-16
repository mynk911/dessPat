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
    ASSERT_EQ(true, concur::mutex_example());
}

TEST(concurTests, unProtectedSharedData)
{
    concur::unprotected_shared_data();
}