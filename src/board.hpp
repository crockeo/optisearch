#ifndef _BOARD_HPP_
#define _BOARD_HPP_

//////////////
// Includes //
#include <vector>

//////////
// Code //

struct BoardMove {
    int col1, row1;
    int col2, row2;

    // Constructing a new BoardMove.
    BoardMove(int, int, int, int);
};

class Board {
private:
    int width, height;
    std::vector<int> states;

    // Converting a 2D coordinate into a 1D coordinate.
    int index(int, int) const;

public:
    // Creating a board with a default set of values. If the set of values do
    // not extend as far as the size of the board, the remaining values will
    // instead be filled with zeroes (empty spots).
    Board(int, int, std::vector<int>);

    // Creating an empty board (with everything at 0) at a given width & height.
    Board(int, int);

    // Checking if a move is valid.
    bool isValidMove(BoardMove) const;

    // Attempting to perform a move. If successful, it returns true, otherwise
    // it returns false.
    bool doMove(BoardMove);

    // Setting the state of a value at a given position in the Board.
    bool setState(int, int, int);

    // Getting the state of a value at a given postiion in the Board.
    int getState(int, int) const;

    // Getting the whole set of states as a vector.
    std::vector<int> asVector() const;

    // Getting the respective dimensions of this board.
    int getWidth() const;
    int getHeight() const;
};

#endif
