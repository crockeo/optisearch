#include "board.hpp"

//////////////
// Includes //
#include <cstdlib>

//////////
// Code //

// Constructing a new BoardMove.
BoardMove::BoardMove(int col1, int row1,
                     int col2, int row2) {
    this->col1 = col1;
    this->col1 = row1;

    this->col2 = col2;
    this->row2 = row2;
}

// Converting a 2D coordinate into a 1D coordinate.
int Board::index(int col, int row) const {
    if (col < 0 || col >= width || row < 0 || row >= height) return -1;
    return row * width + col;
}

// Creating a board with a default set of values. If the set of values do
// not extend as far as the size of the board, the remaining values will
// instead be filled with zeroes (empty spots).
Board::Board(int width, int height, std::vector<int> states) :
        states(width * height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < width * height; i++) {
        if (i < states.size())
            this->states[i] = states.at(i);
        else
            this->states[i] = 0;
    }
}

// Creating an empty board (with everything at 0) at a given width & height.
Board::Board(int width, int height) :
        states(width * height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < width * height; i++)
        states[i] = 0;
}

// Checking if a move is valid.
bool Board::isValidMove(BoardMove bm) const {
    // TODO: Implement.
    return false;
}

// Attempting to perform a move. If successful, it returns true, otherwise
// it returns false.
bool Board::doMove(BoardMove bm) {
    // TODO: Implement
    return false;
}

// Setting the state of a value at a given position in the Board.
bool Board::setState(int col, int row, int value) {
    int i = index(col, row);
    if (i < 0)
        return false;

    states[i] = value;
    return true;
}

// Getting the state of a value at a given postiion in the Board.
int Board::getState(int col, int row) const {
    int i = index(col, row);
    if (i < 0)
        return -1;

    return states.at(i);
}

// Getting the distance from a value at a given position and its target
// position.
int Board::distance(int col, int row) const {
    int state = getState(col, row);
    if (state == -1)
        return -1;

    int tcol = state % width,
        trow = state / width;

    return std::abs(col - tcol) + std::abs(row - trow);
}

// Getting the whole set of states as a vector.
std::vector<int> Board::asVector() const { return states; }

// Getting the respective dimensions of this board.
int Board::getWidth() const { return width; }
int Board::getHeight() const { return height; }
