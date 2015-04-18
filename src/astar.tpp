//////////////
// Includes //
#include "heap.hpp"

//////////
// Code //

// Finding a series of states that go from the initial state to a goal
// state.
template <typename T>
std::vector<T> AStarSearcher<T>::findSolution() {
    T initial = this->searchProblem.getInitialState();
    if (this->searchProblem.isGoal(initial)) {
        std::vector<T> ret { initial };
        return ret;
    }

    Heap<float, std::vector<T>> searchHeap([](float p1, float p2) { return p1 - p2; });
    searchHeap.insert(0.f, std::vector<T>(initial));
    this->visited.add(initial);

    while (!searchHeap.isEmpty()) {
        auto pair = searchHeap.removePair();
        
        for (T t: this->searchProblem.nextStates(pair.value.at(pair.value.size() - 1))) {
            if (this->visited.find(t) == this->visited.end()) {
                std::vector<T> temp = pair.value;
                temp.push_back(t);
                if (this->searchProblem.isGoal(t))
                    return temp;

                this->visited.add(t);

                searchHeap.insert(pair.priority + t.heuristic() / 2.f + 0.5f, temp);
            }
        }
    }

    return std::vector<T>();
}
