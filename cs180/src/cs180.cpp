#include <iostream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <vector>
#include <string>
#include <list>
#include <memory>
#include <cassert>
#include "dbg.h"
#include "util.hpp"
#include "cs180.h"

namespace cs180 {

StableMatching::StableMatching(std::istream& in)
{
    in >> n;
    
    SortUniqueRange(in, n, group1);
    SortUniqueRange(in, n, group2);
    
#ifdef debugPrints
    std::cout << "men:" << std::endl;
    for(auto i : men)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "women:" << std::endl;
    for(auto i : women)
        std::cout << i << " ";
    std::cout << std::endl;
#endif
    
    preferences1 = std::shared_ptr<SizeType>(new SizeType[n*n], std::default_delete<SizeType[]>());
    preferences2 = std::shared_ptr<SizeType>(new SizeType[n*n], std::default_delete<SizeType[]>());
    rankings1 = std::shared_ptr<SizeType>(new SizeType[n*n], std::default_delete<SizeType[]>());
    rankings2 = std::shared_ptr<SizeType>(new SizeType[n*n], std::default_delete<SizeType[]>());

    populatePreferenceList(in, preferences1.get(), group1, group2);
    populatePreferenceList(in, preferences2.get(), group2, group1);

#ifdef debugPrints
    printPreferenceList(menPref, men , women);
    printPreferenceList(womenPref, women, men);
#endif

    calculateRankings(rankings1.get(), preferences2.get(), n);
    calculateRankings(rankings2.get(), preferences1.get(), n);
}

void printPreferenceList(std::vector<std::string>::size_type *pref,
        std::vector < std::string>& preferer,
        std::vector < std::string>& preferee)
{
    std::cout << "Preference list:" << std::endl;
    auto n = preferer.size();
    for(auto i = 0ul; i < n; i++)
    {
        std::cout << preferer.at(i) << " ";
        for(auto j = 0ul; j < n; j++)
        {
            std::cout << preferee.at(pref[i*n+j]) << " ";
        }
        std::cout << std::endl;
    }
}

StableMatching& StableMatching::operator()(std::ostream& out, bool proposerIsGroup1)
{
    std::list<SizeType> freeProposers(n);
    std::iota(freeProposers.begin(), freeProposers.end(), 0);
    std::vector<SizeType> next(n, 0);
    std::vector<SizeType> current(n , std::numeric_limits<SizeType>::max());

    SizeType* pref,*ranking;
    std::vector<std::string>* proposers, *proposees;
    
    if(proposerIsGroup1)
    {
        pref = preferences1.get();
        ranking = rankings1.get();
        proposees = &group2;
        proposers = &group1;
    }
    else
    {
    pref = preferences2.get();
    ranking = rankings2.get();
	proposees = &group1;
	proposers = &group2;
    }
    while (!freeProposers.empty())
    {
        auto proposer = freeProposers.front();
        assert(next[proposer] != n);
        auto proposee = pref[proposer*n + next[proposer]];
        if(current[proposee] == std::numeric_limits<SizeType>::max())
        {
            current[proposee] = proposer;
            freeProposers.pop_front();
        }
        else{
            auto current_choice = current[proposee];
            if(ranking[proposee*n + proposer] < ranking[proposee*n + current_choice])
            {
                current[proposee] = proposer;
                freeProposers.pop_front();
                freeProposers.push_back(current_choice);
            }
        }
        next[proposer]++;
    }

    for(SizeType i=0; i<n; i++)
    {
        out << (*proposees)[i] << " " << (*proposers)[current[i]] << std::endl;
    }
    return *this;
}

GraphImp::GraphImp() {}

GraphImp::~GraphImp() {}

Graph::Graph(GraphImp& imp)
    :_imp(imp)
{}

Graph::~Graph() {}

Iter::Iter() {}

Iter::~Iter() {}
#ifdef DEVEL
class AdjacencyMatrix : public GraphImp
{
public:
    typedef std::vector<bool> Graph;
    AdjacencyMatrix(int n);
    ~AdjacencyMatrix() override;
    bool add(int i,int j) override;
    bool remove(int i, int j) override;
    bool edge(int i, int j) override;
    virtual std::shared_ptr<Iter> iter(int i) override;
private:
    class AdjacencyMatrixIterator : public Iter
    {
    public:
        AdjacencyMatrixIterator(int);
        ~AdjacencyMatrixIterator() override;
        bool next() override;
        int eval() override;
    private:
        int node;
        int index;
    };
    Graph::size_type index(int i, int j)
    {
        return static_cast<Graph::size_type>(_verticesCount*i+j);
    }
    Graph _graph;
    int _verticesCount;
};

AdjacencyMatrix::AdjacencyMatrix(int n)
    :GraphImp (),
      _graph(static_cast<Graph::size_type>(n*n)),
      _verticesCount(n)
{}

AdjacencyMatrix::~AdjacencyMatrix() {}

bool AdjacencyMatrix::add(int i, int j)
{
    if(i >= _verticesCount || j >= _verticesCount)
        return false;
    return _graph[index(i,j)] = true;
}

bool AdjacencyMatrix::remove(int i, int j)
{
    if(i >= _verticesCount || j >= _verticesCount)
        return false;
    _graph[index(i,j)] = false;
    return true;
}

bool AdjacencyMatrix::edge(int i, int j)
{
    if(i >= _verticesCount || j >= _verticesCount)
        throw std::logic_error("vertex out of bound");
    return  _graph[index(i,j)];
}

std::shared_ptr<Iter> AdjacencyMatrix::iter(int i)
{
    return std::make_shared<AdjacencyMatrixIterator>(i);
}

class AdjacencyList : public GraphImp
{
public:
    typedef std::vector<std::list<int>> Graph;
    AdjacencyList(int n);
    ~AdjacencyList() override;
    bool add(int i,int j) override;
    bool remove(int i, int j) override;
    bool edge(int i, int j) override;
    virtual std::shared_ptr<Iter> iter(int i) override;
private:
    class AdjacencyMatrixIterator : public Iter
    {
    public:
        AdjacencyMatrixIterator(int);
        ~AdjacencyMatrixIterator() override;
        bool next() override;
        int eval() override;
    private:
        int node;
        int index;
    };
    Graph _graph;
};

AdjacencyList::~AdjacencyList()
{}


class DirectedGraph : public Graph
{
    // Graph interface
public:
    bool addEdge(int, int) override;
    bool removeEdge(int, int) override;
    bool IsEdge(int, int) override;
    std::shared_ptr<Iter> iter(int) override;
};

bool DirectedGraph::addEdge(int, int)
{
    return true;
}

bool DirectedGraph::removeEdge(int, int)
{ return true;
}

bool DirectedGraph::IsEdge(int, int)
{ return true;
}

std::shared_ptr<Iter> DirectedGraph::iter(int)
{ return nullptr;
}

class UnDirectedGraph : public Graph
{


    // Graph interface
public:
    bool addEdge(int, int) override;
    bool removeEdge(int, int) override;
    bool IsEdge(int, int) override;
    std::shared_ptr<Iter> iter(int) override;
};

bool UnDirectedGraph::addEdge(int, int)
{ return true;
}

bool UnDirectedGraph::removeEdge(int, int)
{ return true;
}

bool UnDirectedGraph::IsEdge(int, int)
{ return true;
}

std::shared_ptr<Iter> UnDirectedGraph::iter(int)
{ return nullptr;
}
#endif // DEVEL
}
