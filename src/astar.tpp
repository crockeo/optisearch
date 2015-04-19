//////////////
// Includes //
#include "heap.hpp"

//////////
// Code //

// Creating a new searcher from a given search problem.
template <typename T>
AStarSearcher<T>::AStarSearcher(const Searchable<T>&& searchProblem)
        : Searcher<T>(searchProblem) { }

template <typename T>
AStarSearcher<T>::AStarSearcher(const Searchable<T>& searchProblem)
        : Searcher<T>(searchProblem) { }

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

    Heap<float, std::vector<T>> searchHeap([](float p1, float p2) { return p2 - p1; });
    std::vector<T> initialVector { initial };
    searchHeap.insert(0.f, initialVector);
    this->visited.insert(initial);

    while (!searchHeap.isEmpty()) {
        auto pair = searchHeap.removeTuple();
        
        for (T t: this->searchProblem.nextStates(pair.value.at(pair.value.size() - 1))) {
            auto loc = this->visited.find(t);
            if (this->visited.find(t) == this->visited.end()) {
                std::vector<T> temp = pair.value;
                temp.push_back(t);

                if (this->searchProblem.isGoal(t)) {
                    this->solution = new std::vector<T>();
                    *this->solution = temp;

                    return temp;
                }

                this->visited.insert(t);

                searchHeap.insert(pair.priority + (t.heuristic() / 2.f) + 1.f, temp);
            }
        }
    }

    return std::vector<T>();
}
