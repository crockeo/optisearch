//////////
// Code //

// Constructing a new Pair.
template <typename P, typename V>
Pair<P, V>::Pair(P&& priority, V&& value) {
    this->priority = priority;
    this->value = value;
}

// Comparing two integers.
int compare(const int n1, const int n2) {
    return n1 - n2;
}

// Comparing two pairs using the Priority value. Requires the P to have some
// implementation of the function 'compare' to compare two values in an analogue
// nature.
template <typename P, typename V>
int compare(const Pair<P, V>& pair1, const Pair<P, V>& pair2) {
    return compare(pair1.priority, pair2.priority);
}

// Comparing two pairs at given locations in the heap.
template <typename P, typename V>
int Heap<P, V>::compareAt(int idx1, int idx2) const {
    return compare(pairs.at(idx1), pairs.at(idx2));
}

// Getting the parent index of an index.
template <typename P, typename V>
int Heap<P, V>::getParent(int index) const {
    return (index - 1) / 2;
}

// Getting the left node of an index.
template <typename P, typename V>
int Heap<P, V>::getLeft(int index) const {
    return index * 2 + 1;
}

// Getting the right node of an index.
template <typename P, typename V>
int Heap<P, V>::getRight(int index) const {
    return index * 2 + 2;
}

// Bubbling a value all the way to the top.
template <typename P, typename V>
void Heap<P, V>::bubbleUp(int index) {
    if (index == 0)
        return;

    if (compareAt(index, getParent(index)) > 0) {
        swap(index, getParent(index));
        bubbleUp(getParent(index));
    }
}

// Bubbling a value all the way to the bottom.
template <typename P, typename V>
void Heap<P, V>::bubbleDown(int index) {
    // TODO: Implement
}

// Creating a new, empty heap.
template <typename P, typename V>
Heap<P, V>::Heap() { }

// Inserting a new value into the heap.
template <typename P, typename V>
void Heap<P, V>::insert(P priority, V value) {
    pairs.push_back(Pair(priority, value));
    bubbleUp(pairs.size() - 1);
    // TODO: Implement
}

// Peeking at the max value in the heap.
template <typename P, typename V>
V Heap<P, V>::peek() { return pairs.at(0).value; }

// Removing the max value in the heap & maintaining the heap property.
template <typename P, typename V>
V Heap<P, V>::remove() {
    // TODO: Implement
    return peek();
}

// Getting the current size of the heap.
template <typename P, typename V>
int Heap<P, V>::size() { return pairs.size(); }

// Checking if the heap is empty.
template <typename P, typename V>
bool Heap<P, V>::isEmpty() { return size() <= 0; }

// Returning this heap as a vector of Pairs.
template <typename P, typename V>
std::vector<Pair<P, V>> Heap<P, V>::asVector() { return pairs; }
