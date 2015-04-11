#ifndef _HEAP_HPP_
#define _HEAP_HPP_

//////////////
// Includes //
#include <vector>

//////////
// Code //

// Pair explicitly represents a value inside of the 
template <typename P, typename V>
struct Pair {
    P priority;
    V value;

    // Constructing a new Pair.
    Pair(P&&, V&&);
};

// Comparing two pairs using the Priority value. Requires the P to have some
// implementation of the function 'compare' to compare two values in an analogue
// nature.
template <typename P, typename V>
int compare(const Pair<P, V>&, const Pair<P, V>&);

// A heap of values given a comparator.
template <typename P, typename V>
class Heap {
private:
    std::vector<Pair<P, V>> pairs;

    // Comparing two pairs at given locations in the heap.
    int compareAt(int, int) const;

    // Getting the parent index of an index.
    int getParent(int) const;

    // Getting the left node of an index.
    int getLeft(int) const;

    // Getting the right node of an index.
    int getRight(int) const;

    // Bubbling a value all the way to the top.
    void bubbleUp(int);

    // Bubbling a value all the way to the bottom.
    void bubbleDown(int);

public:
    // Creating a new, empty heap.
    Heap();

    // Inserting a new value into the heap.
    void insert(P, V);

    // Peeking at the max value in the heap.
    V peek();

    // Removing the max value in the heap & maintaining the heap property.
    V remove();

    // Getting the current size of the heap.
    int size();

    // Checking if the heap is empty.
    bool isEmpty();

    // Returning this heap as a vector of Pairs.
    std::vector<Pair<P, V>> asVector();
};

#include "heap.tpp"

#endif
