#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_

//////////////
// Includes //
#include "board.hpp"

//////////
// Code //

// Finding the Manhattan distance between two points. The Manhattan distance is
// the distance between two points as though you're locked to a discrete grid.
int manhattanDistance(int, int, int, int);

// Finding the heuristic for the board itself.
int heuristic(const Board&);

#endif
