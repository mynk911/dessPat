/**
 * \file cs180.h
 * \brief CS180 header file
 *
 * declarations for CS180
 *
 * \author Mayank Bansal
 */
#ifndef _CS180_CS180_H_
#define _CS180_CS180_H_

#include <vector>
#include <memory>
#include <limits>
#include "cs180_export.h"
#include "dbg.h"

namespace cs180 {

int CS180_EXPORT stable_matching();
namespace pq {
template <typename T>
class CS180_EXPORT heap
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
            debug("creating a node");
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
    static heap_size_type counter;
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
    explicit heap(heap_size_type size = Size)
    {
        buf.reserve(size);
        pos.reserve(size);
    }
    //impl
    heap(const heap& other) = default;
    //default
    heap(heap&& other) = default;
    ~heap() = default;
    //impl
    heap& operator=(const heap& other) = default;
    //default
    heap& operator=(heap&& other) = default;
    void swap(heap& other) noexcept
    {
        swap(buf, other.buf);
        swap(pos, other.pos);
    }
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

template <typename T> typename heap<T>::heap_size_type heap<T>::counter = 0;

}}

#endif
