#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_

//////////////
// Includes //
#include "board.hpp"
#include "heap.hpp"

//////////
// Code //

// A type definition to make things easier to write down.
typedef Heap<float, std::tuple<Board, std::vector<BoardMove>>> SearchHeap;

// Finding the heuristic for the board itself.
int heuristic(const Board&);

// Checking if a given board is the solution. For boards with more than one open
// space it will always return false.
bool isSolution(const Board&);

// findSolution returns a vector of in-order moves to perform in order to reach
// a solution for a given board.
std::vector<BoardMove> findSolution(const Board);

#endif
