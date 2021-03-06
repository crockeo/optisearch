#include "maze.hpp"

//////////////
// Includes //
#include <cstdlib>

//////////
// Code //

// Constructing a new Maze.
Maze::Maze(int px, int py, int tx, int ty) {
    this->px = px;
    this->py = py;
    this->tx = tx;
    this->ty = ty;
}

// A heuristic for this board.
float Maze::heuristic() {
    return std::abs(px - tx) + std::abs(py - ty);
}

// Checking equality between boards.
bool Maze::operator==(const Maze& b) {
    return this->px == b.px && this->py == b.py && this->tx == b.tx && this->ty == b.ty;
}

bool Maze::operator!=(const Maze& b) {
    return !(*this == b);
}

// Ordering boards.
bool operator<(const Maze& m1, const Maze& m2) {
    std::vector<int> t { m1.px, m1.py, m1.tx, m1.ty };
    std::vector<int> o { m2.px, m2.py, m2.tx, m2.ty };

    return t < o;
}

// Constructing a new SearchableMaze from a given Maze as its initial
// state.
SearchableMaze::SearchableMaze(Maze board) :
        initialMaze(board) { };

// Getting the initial state of this search problem.
Maze SearchableMaze::getInitialState() const { return initialMaze; }

// Checking if a given value is the goal state.
bool SearchableMaze::isGoal(Maze b) const {
    return b.px == b.tx && b.py == b.ty;
}

// Getting the list of possible next states from a given state.
std::vector<Maze> SearchableMaze::nextStates(Maze b) const {
    std::vector<Maze> next;

    next.push_back(Maze(b.px - 1, b.py    , b.tx, b.ty));
    next.push_back(Maze(b.px + 1, b.py    , b.tx, b.ty));
    next.push_back(Maze(b.px    , b.py - 1, b.tx, b.ty));
    next.push_back(Maze(b.px    , b.py + 1, b.tx, b.ty));

    return next;
}
