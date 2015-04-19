#ifndef _MAZE_HPP_
#define _MAZE_HPP_

//////////////
// Includes //
#include "searchable.hpp"

//////////
// Code //

// This class represents a board with a player some distance away from a goal.
struct Maze {
    int px, py;
    int tx, ty;

    // Constructing a new Maze.
    Maze(int, int, int, int);

    // A heuristic for this board.
    float heuristic();

    // Checking equality between boards.
    bool operator==(const Maze&);
    bool operator!=(const Maze&);
};

// Ordering boards.
bool operator<(const Maze&, const Maze&);

// SearchableMaze is the Searchable instance for finding a solution to this
// board.
class SearchableMaze : public Searchable<Maze> {
private:
    Maze initialMaze;

public:
    // Constructing a new SearchableMaze from a given Maze as its initial
    // state.
    SearchableMaze(Maze);

    // Getting the initial state of this search problem.
    Maze getInitialState() const;

    // Checking if a given value is the goal state.
    bool isGoal(Maze) const;

    // Getting the list of possible next states from a given state.
    std::vector<Maze> nextStates(Maze) const;
};

#endif
