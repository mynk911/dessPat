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

class AdjacencyMatrix : public GraphImp
{
public:
    friend class AdjacencyMatrixIterator;
    typedef std::vector<bool> Graph;
    AdjacencyMatrix(int n);
    ~AdjacencyMatrix() override;
    void add(int i,int j) override;
    void remove(int i, int j) override;
    bool edge(int i, int j) override;
    virtual std::shared_ptr<Iter> iter(int i) override;
private:
    Graph::size_type index(int i, int j)
    {
        return static_cast<Graph::size_type>(_verticesCount*i+j);
    }
    Graph _graph;
    int _verticesCount;
};

class AdjacencyMatrixIterator : public Iter
{
public:
    AdjacencyMatrixIterator(AdjacencyMatrix* m, int i)
        : Iter(), index(i), node(-1), graph(m) {
        next();
    }
    ~AdjacencyMatrixIterator() override {}
    bool next() override
    {
        if (node > graph->_verticesCount) return false;
        node++;
        while (graph->_graph[graph->index(index,node)] == false &&
            node < graph->_verticesCount) node++;
        if (node > graph->_verticesCount) return false;
        return true;
    }
    int eval() override
    {
        if (node < graph->_verticesCount)
            return node;
        return -1;
    }
private:
    int node;
    int index;
    AdjacencyMatrix* graph;
};

AdjacencyMatrix::AdjacencyMatrix(int n)
    :GraphImp (),
      _graph(static_cast<Graph::size_type>(n*n)),
      _verticesCount(n)
{}

AdjacencyMatrix::~AdjacencyMatrix() {}

void AdjacencyMatrix::add(int i, int j)
{
    if(i >= _verticesCount || j >= _verticesCount)
        throw std::logic_error("vertex out of bound");
    _graph[index(i,j)] = true;
}

void AdjacencyMatrix::remove(int i, int j)
{
    if(i >= _verticesCount || j >= _verticesCount)
        throw std::logic_error("vertex out of bound");
    _graph[index(i,j)] = false;
}

bool AdjacencyMatrix::edge(int i, int j)
{
    if(i >= _verticesCount || j >= _verticesCount)
        throw std::logic_error("vertex out of bound");
    return  _graph[index(i,j)];
}

std::shared_ptr<Iter> AdjacencyMatrix::iter(int i)
{
    return std::make_shared<AdjacencyMatrixIterator>(this, i);
}

class AdjacencyList : public GraphImp
{
public:
    friend class AdjacencyListIterator;
    typedef std::vector<std::list<int>> Graph;
    AdjacencyList(int n);
    ~AdjacencyList() override;
    void add(int i,int j) override;
    void remove(int i, int j) override;
    bool edge(int i, int j) override;
    virtual std::shared_ptr<Iter> iter(int i) override;
private:
    Graph _graph;
    int _verticesCount;
};

class AdjacencyListIterator : public Iter
{
public:
    AdjacencyListIterator(AdjacencyList* m, int i)
        : Iter(), itr(m->_graph[i].begin()), index(i), graph(m) {}
    ~AdjacencyListIterator() override {}
    bool next() override
    {
        if (itr == graph->_graph[index].end()) return false;
        itr++;
        if (itr == graph->_graph[index].end()) return false;
        return true;
    }
    int eval() override
    {
        if (itr != graph->_graph[index].end())
            return *itr;
        return -1;
    }
private:
    std::list<int>::iterator itr;
    int index;
    AdjacencyList* graph;
};

AdjacencyList::AdjacencyList(int n)
    : GraphImp(), _graph(n)
{
}

AdjacencyList::~AdjacencyList()
{}

void AdjacencyList::add(int i, int j)
{
    if (i >= _verticesCount || j >= _verticesCount)
        throw std::logic_error("vertex out of bound");
    if (std::find(_graph[i].begin(), _graph[i].end(), j) == _graph[i].end())
        _graph[i].push_back(j);
}
void AdjacencyList::remove(int i, int j)
{
    if (i >= _verticesCount || j >= _verticesCount)
        throw std::logic_error("vertex out of bound");
    _graph[i].erase(std::remove(_graph[i].begin(), _graph[i].end(), j),
        _graph[i].end());
}

bool AdjacencyList::edge(int i, int j)
{
    if (i >= _verticesCount || j >= _verticesCount)
        throw std::logic_error("vertex out of bound");
    if (std::find(_graph[i].begin(), _graph[i].end(), j) == _graph[i].end())
        return true;
    return false;
}

std::shared_ptr<Iter> AdjacencyList::iter(int i)
{
    return std::make_shared<AdjacencyListIterator>(this, i);
}

class DirectedGraph : public Graph
{
    // Graph interface
public:
    void addEdge(int, int) override;
    void removeEdge(int, int) override;
    bool IsEdge(int, int) override;
    std::shared_ptr<Iter> iter(int) override;
};

void DirectedGraph::addEdge(int i, int j)
{
    _imp.add(i, j);
}

void DirectedGraph::removeEdge(int i, int j)
{
    _imp.remove(i, j);
}

bool DirectedGraph::IsEdge(int i, int j)
{
    return _imp.edge(i, j);
}

std::shared_ptr<Iter> DirectedGraph::iter(int i)
{ 
    return _imp.iter(i);
}

class UnDirectedGraph : public Graph
{


    // Graph interface
public:
    void addEdge(int, int) override;
    void removeEdge(int, int) override;
    bool IsEdge(int, int) override;
    std::shared_ptr<Iter> iter(int) override;
};

void UnDirectedGraph::addEdge(int i, int j)
{
    _imp.add(i, j);
    _imp.add(j, i);
}

void UnDirectedGraph::removeEdge(int i, int j)
{
    _imp.remove(i, j);  
    _imp.remove(j, i);
}

bool UnDirectedGraph::IsEdge(int i, int j)
{ 
    return _imp.edge(i, j) && _imp.edge(j, i);
}

std::shared_ptr<Iter> UnDirectedGraph::iter(int i)
{
    return _imp.iter(i);
}

}
