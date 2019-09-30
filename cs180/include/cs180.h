#ifndef _CS180_CS180_H_
#define _CS180_CS180_H_

#include <vector>
#include <memory>
#include <limits>
#include "cs180_export.h"

/** Main namespace for cs180. 
 */
namespace cs180 {

/** Finds stable matching between two groups.
 *Given two groups and ordered list of their preferences for individuals in
 *other group, finds a stable matching - a matching where no two particular
 *matches can break to form new matches.
 */
class CS180_EXPORT StableMatching
{
public:
    /// size type
    using SizeType = std::vector<std::string>::size_type;
    /** constructor
     * @param in std::istream& streams the input data. Data :
        <ol>
        <li>n - an integer </li>
        <li> n unique strings representing n members in Group 1</li>
        <li> n unique strings representing n members in Group 2</li>
         <li> preference list for n Group 1 members in form 
              group1-member followed by n group 2 members</li>
         <li> preference list for n Group 2 members in form 
              group2-member followed by n group 1 members</li>
        </ol>
        The order of data should be maintained as above.
     */
    explicit StableMatching(std::istream& in);

    /** @name Default implementations
     * Once initilased the data in StableMatching object is never modified.
     * Hence default copying and moving strategy for shared pointers works fine.
     */
    ///@{
    StableMatching(const StableMatching& other) = default;
    StableMatching(StableMatching&& other) = default;
    StableMatching& operator=(const StableMatching& other) = default;
    StableMatching& operator=(StableMatching&& other) = default;
    ~StableMatching() = default;
    ///@}

    /// finds stable matching and streams output to out.
    StableMatching& operator()(std::ostream& out, bool proposerIsGroup1 = true);
private:
    SizeType n;
    std::vector< std::string > group1, group2;
    std::shared_ptr<SizeType> preferences1, preferences2, rankings1, rankings2;
};

/** Provides priority queue functionality using heap data structure.
 * @tparam T element type to be stored in queue
 */
template <typename T>
class heap
{
    struct node;
    std::vector<node> buf;
    using heap_size_type = typename std::vector<struct node>::size_type;
    std::vector<heap_size_type> pos;
    struct node {
        unsigned int key;
        heap_size_type id;
        std::unique_ptr<T> elem;
        template <typename... Args>
        node(unsigned k, heap_size_type i, Args... args)
            : key(k),
              id(i),
              elem(std::make_unique<T>(std::forward<Args>(args)...))
        {
        }
        node(const node& other)
            : key(other.key),
              id(other.id),
              elem(std::make_unique<T>(*other.elem))
        {}
        node& operator=(const node& other)
        {
            key = other.key;
            id = other.id;
            *elem = *other.elem;
        }
        node(node&& other) = default;
        node& operator=(node&& other) = default;
        void swap(node& other)
        {
            std::swap(key, other.key);
            std::swap(id, other.id);
            std::swap(elem, other.elem);
        }
    };
    static constexpr heap_size_type Size = 100;
    heap_size_type counter;
    void heapifyUp(heap_size_type i)
    {
        heap_size_type j = 0;
        while (i>0) {
            j = (i-1)/2;
            if(buf[i].key < buf[j].key)
            {
                buf[i].swap(buf[j]);
                pos[buf[i].id] = i;
                pos[buf[j].id] = j;
                i = j;
            }
            else break;
        }
    }
    void heapifyDown(heap_size_type i)
    {
        heap_size_type l =0,r =0,minindex = 0;
        unsigned int min = 0;
        while(2*i < buf.size())
        {
            l = 2*i+1;
            r = 2*i+2;
            min = buf[i].key;

            if(l < buf.size())
            {
                if(buf[l].key < min)
                {
                    min = buf[l].key;
                    minindex = l;
                }
            }
            if(r < buf.size())
            {
                if(buf[r].key < min)
                {
                    min = buf[r].key;
                    minindex = r;
                }
            }
            if(min == i) break;
            else {
                buf[i].swap(buf[minindex]);
                pos[buf[i].id] = i;
                pos[buf[minindex].id] = minindex;
                i = min;
            }
        }
    }
public:
    /// create a heap of given size
    explicit heap(heap_size_type size = Size)
        :counter(0)
    {
        buf.reserve(size);
        pos.reserve(size);
    }

    /** @name Default implementations
     */
    ///@{
    heap(const heap& other) = default;
    heap(heap&& other) = default;
    ~heap() = default;
    heap& operator=(const heap& other) = default;
    heap& operator=(heap&& other) = default;
    ///@}

    void swap(heap& other) noexcept
    {
        swap(buf, other.buf);
        swap(pos, other.pos);
    }

    /// insert an element with key k
    heap_size_type insert(T t, int k)
    {
        node n(k, counter++, t);
        buf.push_back(n);
        pos.push_back(counter-1);
        heapifyUp(buf.size()-1);
        return n.id;
    }

    T findmin()
    {
        return buf[0].elem;
    }

    /// remove an entry from queue and return it's element
    T remove(heap_size_type i)
    {
        buf[i].swap(buf[buf.size()-1]);
        node el = buf.back();
        buf.pop_back();
        heapifyDown(i);
        heapifyUp(i);
        pos[el.id] = std::numeric_limits<unsigned>::max();
        return *el.elem;
    }


    T extractmin()
    {
        return remove(0);
    }

    /// change key value for an entry.
    void changeKey(heap_size_type id, unsigned int val)
    {
        buf[pos[id]].key = val;
        heapifyDown(pos[id]);
        heapifyUp(pos[id]);
    }
};

template<typename T>
void swap(heap<T>& a, heap<T>& b) noexcept
{
    a.swap(b);
}

class GraphImp;
class Iter;

enum class GraphType {
    Directed,
    UnDirected
};

enum class GraphImpType {
    AdjacencyMatrix,
    AdjacencyList
};

/** base class for different graphs such asdirected, undirecte
 */
class CS180_EXPORT Graph
{
public:
    virtual void addEdge(int, int) = 0;
    virtual void removeEdge(int, int) = 0;
    virtual bool IsEdge(int, int) = 0;
    virtual std::shared_ptr<Iter> iter(int) = 0;
protected:
    Graph(GraphImp&);
    virtual ~Graph();
    GraphImp& _imp;
};

/** Iterator over all nodes that are connected a particular vertex
 */
class CS180_EXPORT Iter {
public:
    virtual bool next() = 0;
    virtual int eval() = 0;
protected:
    Iter();
    virtual ~Iter();
};

CS180_EXPORT Graph& CreateGraph(GraphType, GraphImpType, int);

CS180_EXPORT std::vector<int> bfs(Graph&, int, int);
CS180_EXPORT std::vector<int> dfs(Graph&, int, int);
}
#endif
