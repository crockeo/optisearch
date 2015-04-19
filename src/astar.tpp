//////////////
// Includes //
#include "heap.hpp"

#include <iostream>

//////////
// Code //

// Creating a new searcher from a given search problem.
template <typename T>
AStarSearcher<T>::AStarSearcher(const Searchable<T>&& searchProblem)
        : Searcher<T>(searchProblem) { }

template <typename T>
AStarSearcher<T>::AStarSearcher(const Searchable<T>& searchProblem)
        : Searcher<T>(searchProblem) { }

#include <iostream>

// Finding a series of states that go from the initial state to a goal
// state.
template <typename T>
std::vector<T> AStarSearcher<T>::findSolution() {
    if (this->solution != nullptr)
        return *this->solution;

    T initial = this->searchProblem.getInitialState();
    if (this->searchProblem.isGoal(initial)) {
        std::vector<T> ret { initial };
        return ret;
    }

    Heap<float, std::vector<T>> searchHeap([](float p1, float p2) { return p1 - p2; });
    std::vector<T> initialVector { initial };
    searchHeap.insert(0.f, initialVector);
    this->visited.insert(initial);

    while (!searchHeap.isEmpty()) {
        auto pair = searchHeap.removeTuple();
        
        for (T t: this->searchProblem.nextStates(pair.value.at(pair.value.size() - 1))) {
            // TODO: There is a god damn segfault happening here and I need to
            //       find out why. I think it has something to do with
            //       inheriting values from superclasses? But some weird shit
            //       might be happening. I dunno.
            if (this->visited.find(t) == this->visited.end()) {
                std::vector<T> temp = pair.value;
                temp.push_back(t);

                if (this->searchProblem.isGoal(t)) {
                    this->solution = new std::vector<T>();
                    *this->solution = temp;

                    return temp;
                }

                this->visited.insert(t);

                searchHeap.insert(pair.priority + t.heuristic() / 2.f + 0.5f, temp);
            }
        }
    }

    return std::vector<T>();
}
