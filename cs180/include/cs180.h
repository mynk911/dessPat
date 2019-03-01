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

#include "cs180_export.h"

namespace cs180 {

int CS180_EXPORT stable_matching();
namespace pq {
class element;

class heap
{
    struct node {
        unsigned int key;
        unsigned int id;
        const element& e;
    };
    std::vector<struct node> vec;
    std::vector<unsigned int> pos;
    static constexpr int Size = 100;
    void heapifyUp(unsigned int i);
    void heapifyDown(unsigned int i);
public:
    heap(int size = Size);
    //impl
    heap(const heap& other);
    //default
    heap(heap&& other);
    ~heap();
    //impl
    heap& operator=(const heap& other);
    //default
    heap& operator=(heap&& other);
    void swap(heap& other);
    void insert(node& n);
    element& findmin();
    void remove(unsigned int i);
    element& extractmin();
    void changeKey(node& n, unsigned int val);

};

void swap(heap& a, heap& b);

}}
#endif
