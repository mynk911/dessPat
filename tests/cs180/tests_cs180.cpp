#include <sstream>

#include "cs180.h"
#include "gtest/gtest.h"

TEST(cs180, stableMatchingBasic)
{
    std::stringstream in, out;

    in << "2 m1 m2 w1 w2 m1 w2 w1 m2 w1 w2 w1 m1 m2 w2 m1 m2\0";
    std::string s("w1 m2\n"
		  "w2 m1\n");
    cs180::StableMatching sm(in);
    sm(out);
    EXPECT_EQ(s, out.str());
}

TEST(cs180, stableMatchingBasicReversed)
{
    std::stringstream in, out;

    in << "2 m1 m2 w1 w2 m1 w2 w1 m2 w1 w2 w1 m1 m2 w2 m1 m2\0";
    std::string s("m1 w2\n"
		  "m2 w1\n");
    cs180::StableMatching sm(in);
    sm(out, false);
    EXPECT_EQ(s, out.str());
}

TEST(cs180, stableMatchingComplex)
{
    std::stringstream in, out;

    in << "7 "
    "adam brian deb charlie ethan fred greg "
    "susan lucy felicity debra katie mary jenny "
    "adam jenny katie felicity debra mary susan lucy "
    "brian mary katie felicity jenny lucy debra susan "
    "charlie mary jenny lucy susan felicity katie debra "
    "deb debra mary jenny felicity katie susan lucy "
    "ethan debra mary lucy jenny katie susan felicity "
    "fred debra susan jenny katie lucy mary felicity "
    "greg lucy mary felicity katie jenny susan debra "
    "lucy adam greg fred deb charlie ethan brian "
    "susan adam greg deb brian fred ethan charlie "
    "felicity ethan fred deb greg charlie brian adam "
    "debra deb ethan charlie greg brian fred adam "
    "jenny adam fred ethan deb charlie greg brian "
    "katie charlie ethan fred greg brian deb adam "
    "mary fred charlie greg ethan brian deb adam ";

    std::string s("debra deb\nfelicity brian\njenny adam\nkatie ethan\nlucy "
		  "greg\nmary charlie\nsusan fred\n");
    cs180::StableMatching sm(in);
    sm(out);
    
    EXPECT_EQ(s, out.str());
}

TEST(cs180, priorityQueueTest1)
{
    cs180::heap<int> pq(25);
    pq.insert(5, 1);
    pq.insert(4, 8);
    pq.insert(2, 2);
    pq.insert(1, 4);
    pq.insert(3, 3);
    pq.insert(7, 5);
    EXPECT_EQ(5, pq.extractmin());
    EXPECT_EQ(2, pq.extractmin());
    EXPECT_EQ(3, pq.extractmin());
    EXPECT_EQ(1, pq.extractmin());
    EXPECT_EQ(7, pq.extractmin());
    EXPECT_EQ(4, pq.extractmin());
}

TEST(cs180, priorityQueueTest2)
{
    cs180::heap<int> pq(25);
    pq.insert(5, 1);
    pq.insert(4, 8);
    pq.insert(2, 2);
    pq.insert(1, 4);
    pq.insert(3, 3);
    pq.insert(7, 5);
    pq.changeKey(0, 25);
    EXPECT_EQ(2, pq.extractmin());
    EXPECT_EQ(3, pq.extractmin());
    EXPECT_EQ(1, pq.extractmin());
    EXPECT_EQ(7, pq.extractmin());
    EXPECT_EQ(4, pq.extractmin());
    EXPECT_EQ(5, pq.extractmin());
}

void print(cs180::Graph& g, int n)
{
    std::cout << "=== graph print ===" << std::endl;
    for (int i = 0; i < n; i++)
    {
        auto itr = g.iter(i);
        std::cout << i  << " ";
        while (itr->next()) std::cout << itr->eval() << " ";
        std::cout << std::endl;
    }
    std::cout << "===================" << std::endl;
}

void graphAPITest(cs180::Graph& g, cs180::GraphType t)
{
    print(g, 5);
    g.addEdge(2, 3);
    ASSERT_EQ(g.IsEdge(2, 3), true);
    if(t == cs180::GraphType::UnDirected)
        ASSERT_EQ(g.IsEdge(3, 2), true);
    g.addEdge(4, 1);
    g.addEdge(2, 4);
    print(g, 5);
    g.removeEdge(2, 3);
    ASSERT_EQ(g.IsEdge(2, 3), false);
    ASSERT_EQ(g.IsEdge(3, 2), false);
    g.removeEdge(4, 1);
    g.removeEdge(2, 4);
    print(g, 5);
}

TEST(cs180, UnDirectedGraphAdjacencyMatrix)
{
    auto& graph = cs180::CreateGraph(
        cs180::GraphType::UnDirected,
        cs180::GraphImpType::AdjacencyMatrix,
        5);
    graphAPITest(graph, cs180::GraphType::UnDirected);
}
TEST(cs180, UnDirectedGraphAdjacencyList)
{
    auto& graph = cs180::CreateGraph(
        cs180::GraphType::UnDirected,
        cs180::GraphImpType::AdjacencyList,
        5);
    graphAPITest(graph, cs180::GraphType::UnDirected);
}

TEST(cs180, DirectedGraphAdjacencyMatrix)
{
    auto& graph = cs180::CreateGraph(
        cs180::GraphType::Directed,
        cs180::GraphImpType::AdjacencyMatrix,
        5);
    graphAPITest(graph, cs180::GraphType::Directed);
}
TEST(cs180, DirectedGraphAdjacencyList)
{
    auto& graph = cs180::CreateGraph(
        cs180::GraphType::Directed,
        cs180::GraphImpType::AdjacencyList,
        5);
    graphAPITest(graph, cs180::GraphType::Directed);
}

