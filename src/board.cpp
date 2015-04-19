#include "board.hpp"

//////////////
// Includes //
#include <cstdlib>
#include <fstream>

//////////
// Code //

// Constructing a new BoardMove.
BoardMove::BoardMove(int col1, int row1,
                     int col2, int row2) {
    this->col1 = col1;
    this->row1 = row1;

    this->col2 = col2;
    this->row2 = row2;
}

// Checking equality between two BoardMoves.
bool BoardMove::operator==(const BoardMove& bm) const {
    return (col1 == bm.col1 && row1 == bm.row1 && col2 == bm.col2 && row2 == bm.row2) ||
           (col1 == bm.col2 && row1 == bm.row2 && col2 == bm.col1 && row2 == bm.row1);
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

// Creating a useless board - with size 0 on both width and height and no
// states.
Board::Board() {
    this->width = 0;
    this->height = 0;
}

// Checking equality between this and another board.
bool Board::operator==(const Board& b) const {
    if (width != b.width || height != b.height)
        return false;

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            if (getState(col, row) != b.getState(col, row))
                return false;

    return true;
}

// Ordering boards.
bool Board::operator<(const Board& b) const {
    return asVector() < b.asVector();
}

// Creating a heuristic.
int Board::heuristic() const {
    int sum = 0;
    for (int row = 0; row < getHeight(); row++)
        for (int col = 0; col < getWidth(); col++)
            sum += distance(col, row);
    return sum;
}

// Checking if a move is valid.
bool Board::isValidMove(BoardMove bm) const {
    return bm.col1 >= 0 && bm.col1 < width  &&
           bm.row1 >= 0 && bm.row1 < height &&
           bm.col2 >= 0 && bm.col2 < width  &&
           bm.row2 >= 0 && bm.row2 < height &&
          (getState(bm.col1, bm.row1) == 0 ||
           getState(bm.col2, bm.row2) == 0);
}

// Attempting to perform a move. If successful, it returns true, otherwise
// it returns false.
Board Board::doMove(BoardMove bm) const throw(std::logic_error) {
    if (!isValidMove(bm))
        throw std::logic_error("Invalid board move.");

    Board b(*this);

    int temp = b.getState(bm.col1, bm.row1);
    b.setState(bm.col1, bm.row1, b.getState(bm.col2, bm.row2));
    b.setState(bm.col2, bm.row2, temp);

    return b;
}

// Setting the state of a value at a given position in the Board.
bool Board::setState(int col, int row, int value) throw(std::logic_error) {
    int i = index(col, row);
    if (i < 0)
        throw std::logic_error("Column or row is outside of board bounds.");

    states[i] = value;
    return true;
}

// Getting the state of a value at a given postiion in the Board.
int Board::getState(int col, int row) const throw(std::logic_error) {
    int i = index(col, row);
    if (i < 0)
        throw std::logic_error("Column or row is outside of board bounds.");

    return states.at(i);
}

// Getting a list of valid moves at this given state.
std::vector<BoardMove> Board::validMoves() const {
    std::vector<BoardMove> moves;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (getState(col, row) == 0) {
                if (col - 1 >= 0)
                    moves.push_back(BoardMove(col - 1, row, col, row));
                if (col + 1 < width)
                    moves.push_back(BoardMove(col + 1, row, col, row));
                if (row - 1 >= 0)
                    moves.push_back(BoardMove(col, row - 1, col, row));
                if (row + 1 < height)
                    moves.push_back(BoardMove(col, row + 1, col, row));

                break;
            }
        }
    }

    return moves;
}

// Getting the distance from a value at a given position and its target
// position.
int Board::distance(int col, int row) const throw(std::logic_error) {
    int state;
    try {
        state = getState(col, row);
    } catch (std::logic_error e) {
        throw e;
    }

    int tcol = state % width,
        trow = state / width;

    return std::abs(col - tcol) + std::abs(row - trow);
}

// Getting the whole set of states as a vector.
std::vector<int> Board::asVector() const { return states; }

// Getting the respective dimensions of this board.
int Board::getWidth() const { return width; }
int Board::getHeight() const { return height; }

// Creating a new search problem from a board.
SearchableBoard::SearchableBoard(Board board) :
        initialBoard(board) { }

// Getting the initial state of this search problem.
Board SearchableBoard::getInitialState() const {
    return initialBoard;
}

// Checking if a given value is the goal state.
bool SearchableBoard::isGoal(Board board) const {
    for (int row = 0; row < board.getHeight(); row++)
        for (int col = 0; col < board.getWidth(); col++)
            if (board.getState(col, row) != row * board.getWidth() + col)
                return false;

    return true;
}

// Getting the list of possible next states from a given state.
std::vector<Board> SearchableBoard::nextStates(Board board) const {
    std::vector<Board> boards;
    std::vector<BoardMove> validMoves = board.validMoves();
    for (auto bm: validMoves) {
        Board temp(board);
        temp.doMove(bm);

        boards.push_back(temp);
    }

    return boards;
}

// Loading a board from an input stream.
Board loadBoard(std::istream&& in) throw(std::runtime_error) {
    if (!in.good())
        throw std::runtime_error("Input stream is not good.");

    int width,
        height;
    in >> width;
    in >> height;

    if (width < 0 || height < 0)
        throw std::runtime_error("Cannot have negative width / height.");

    std::vector<int> states;
    int state;
    for (int i = 0; i < width * height; i++) {
        if (in.eof())
            throw std::runtime_error("Unexpected end of stream.");

        in >> state;
        if (state < 0)
            throw std::runtime_error("Cannot have negative state.");

        states.push_back(state);
    }

    return Board(width, height, states);
}

// Loading a board from a file at a given location.
Board loadBoard(std::string path) throw(std::runtime_error) {
    return loadBoard(std::ifstream(path));
}
