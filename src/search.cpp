#include "search.hpp"

//////////
// Code //

// Finding the heuristic for the board itself.
int heuristic(const Board& b) {
    int sum = 0;
    for (int row = 0; row < b.getHeight(); row++)
        for (int col = 0; col < b.getWidth(); col++)
            sum += b.distance(col, row);
    return sum;
}
