//////////
// Code //

// Creating a new searcher from a given search problem.
template <typename T>
Searcher<T>::Searcher(const Searchable<T>&& searchProblem) :
        solution(),
        visited() {
    this->searchProblem = searchProblem;
}

template <typename T>
Searcher<T>::Searcher(const Searchable<T>& searchProblem) :
        Searcher(searchProblem) { }

// Checking if a given solution is actually a valid solution.
template <typename T>
bool Searcher<T>::isValidSolution(const std::vector<T>& states) {
    if (states.empty() || states.at(0) != searchProblem.getInitialState() || !isGoal(states.at(states.size() - 1)))
        return false;

    for (int i = 0; i < states.size() - 1; i++) {
        std::vector<T> next = searchProblem.nextStates(states.at(i));
        if (next.find(states.at(i + 1)) == next.end())
            return false;
    }

    return true;
}
