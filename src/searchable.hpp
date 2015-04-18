#ifndef _SEARCHABLE_HPP_
#define _SEARCHABLE_HPP_

//////////////
// Includes //
#include <vector>
#include <set>

//////////
// Code //

// A type that represents a problem that can be searched.
template <typename T>
struct Searchable {
    // Getting the initial state of this search problem.
    virtual T getInitialState() = 0;

    // Checking if a given value is the goal state.
    virtual bool isGoal(T) = 0;

    // Getting the list of possible next states from a given state.
    virtual std::vector<T> nextStates(T) = 0;
};

// An interface to find a solution to a search problem.
template <typename T>
class Searcher {
protected:
    const Searchable<T>& searchProblem;
    std::vector<T> solution;
    std::set<T> visited;
    
public:
    // Creating a new searcher from a given search problem.
    Searcher(const Searchable<T>&&);
    Searcher(const Searchable<T>&);

    // Finding a series of states that go from the initial state to a goal
    // state.
    virtual std::vector<T> findSolution() = 0;

    // Checking if a given solution is actually a valid solution.
    bool isValidSolution(const std::vector<T>&);
};

#include "searchable.tpp"

#endif
