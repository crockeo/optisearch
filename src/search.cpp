#include "search.hpp"

//////////
// Code //

// Getting the absolute value of an integer.
int abs(int n) { return n < 0 ? -n : n; }

// Finding the Manhattan distance between two points. The Manhattan distance is
// the distance between two points as though you're locked to a discrete grid.
int manhattanDistance(int x1, int y1,
                      int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Finding the heuristic for the board itself.
int heuristic(const Board&) {
    // TODO: Implement
    return -1;
}
