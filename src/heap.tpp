//////////
// Code //

// Constructing a new Pair.
template <typename P, typename V>
Pair<P, V>::Pair(P priority, V value) {
    this->priority = priority;
    this->value = value;
}

// Comparing two pairs at given locations in the heap.
template <typename P, typename V>
int Heap<P, V>::compareAt(int idx1, int idx2) const {
    return comparator(pairs.at(idx1).priority, pairs.at(idx2).priority);
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

// Swapping the values at two indices.
template <typename P, typename V>
void Heap<P, V>::swap(int idx1, int idx2) {
    auto temp = pairs[idx2];
    pairs[idx2] = pairs[idx1];
    pairs[idx1] = temp;
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
    int lComp = getLeft(index)  >= size() ? 0 : compareAt(index, getLeft(index)),
        rComp = getRight(index) >= size() ? 0 : compareAt(index, getRight(index));

    if (lComp < 0 || rComp < 0) {
        int idx;
        if (lComp <= rComp)
            idx = getLeft(index);
        else
            idx = getRight(index);

        swap(index, idx);
        bubbleDown(idx);
    }
}

// Creating a new, empty heap.
template <typename P, typename V>
Heap<P, V>::Heap(std::function<int(const P, const P)> comparator) {
    this->comparator = comparator;
}

// Inserting a new value into the heap.
template <typename P, typename V>
void Heap<P, V>::insert(P priority, V value) {
    pairs.push_back(Pair<P, V>(priority, value));
    bubbleUp(pairs.size() - 1);
}

// Peeking at the max value in the heap.
template <typename P, typename V>
V Heap<P, V>::peek() const { return pairs.at(0).value; }

// Removing the max value in the heap & maintaining the heap property.
template <typename P, typename V>
V Heap<P, V>::remove() {
    V value = pairs.at(0).value;
    pairs[0] = pairs.at(pairs.size() - 1);
    pairs.pop_back();

    if (pairs.size() > 1)
        bubbleDown(0);

    return value;
}

// Getting the current size of the heap.
template <typename P, typename V>
int Heap<P, V>::size() const { return pairs.size(); }

// Checking if the heap is empty.
template <typename P, typename V>
bool Heap<P, V>::isEmpty() const { return size() <= 0; }

// Returning this heap as a vector of Pairs.
template <typename P, typename V>
std::vector<Pair<P, V>> Heap<P, V>::asVector() const { return pairs; }
