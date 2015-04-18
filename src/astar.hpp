#ifndef _ASTAR_HPP_
#define _ASTAR_HPP_

//////////////
// Includes //
#include <vector>

#include "searchable.hpp"

//////////
// Code //

// An implementation of an A* search algorithm.
template <typename T>
class AStarSearcher : public Searcher<T> {
    // Finding a series of states that go from the initial state to a goal
    // state.
    std::vector<T> findSolution();
};

#include "astar.tpp"

#endif
