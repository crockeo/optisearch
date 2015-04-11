#ifndef _HEAP_HPP_
#define _HEAP_HPP_

//////////////
// Includes //
#include <functional>
#include <vector>

//////////
// Code //

// Pair explicitly represents a value inside of the 
template <typename P, typename V>
struct Pair {
    P priority;
    V value;

    // Constructing a new Pair.
    Pair(P, V);
};

// A heap of values given a comparator.
template <typename P, typename V>
class Heap {
private:
    std::function<int(const P, const P)> comparator;
    std::vector<Pair<P, V>> pairs;

    // Comparing two pairs at given locations in the heap.
    int compareAt(int, int) const;

    // Getting the parent index of an index.
    int getParent(int) const;

    // Getting the left node of an index.
    int getLeft(int) const;

    // Getting the right node of an index.
    int getRight(int) const;

    // Swapping the values at two indices.
    void swap(int, int);

    // Bubbling a value all the way to the top.
    void bubbleUp(int);

    // Bubbling a value all the way to the bottom.
    void bubbleDown(int);

public:
    // Creating a new, empty heap.
    Heap(std::function<int(const P, const P)>);

    // Inserting a new value into the heap.
    void insert(P, V);

    // Peeking at the max value in the heap.
    V peek() const;

    // Removing the max value in the heap & maintaining the heap property.
    V remove();

    // Getting the current size of the heap.
    int size() const;

    // Checking if the heap is empty.
    bool isEmpty() const;

    // Returning this heap as a vector of Pairs.
    std::vector<Pair<P, V>> asVector() const;
};

#include "heap.tpp"

#endif
