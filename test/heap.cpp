//////////////
// Includes //
#include <vector>

#include "../src/heap.hpp"

//////////
// Code //

// Testing the .insert & .remove methods.
TEST_CASE("Insert & Remove") {
    Heap<int, int> intHeap([](const int n1, const int n2) -> int { return n1 - n2; });

    intHeap.insert(3, 3);
    intHeap.insert(1, 1);
    intHeap.insert(4, 4);
    intHeap.insert(2, 2);

    REQUIRE(intHeap.size() == 4);
    REQUIRE(intHeap.remove() == 4);

    REQUIRE(intHeap.size() == 3);
    REQUIRE(intHeap.remove() == 3);

    REQUIRE(intHeap.size() == 2);
    REQUIRE(intHeap.remove() == 2);

    REQUIRE(intHeap.size() == 1);
    REQUIRE(intHeap.remove() == 1);

    REQUIRE(intHeap.size() == 0);
}

// Testing the order of a vector returned from asVector.
TEST_CASE("AsVector") {
    Heap<int, int> intHeap([](const int n1, const int n2) -> int { return n1 - n2; });

    intHeap.insert(3, 3);
    intHeap.insert(1, 1);
    intHeap.insert(4, 4);
    intHeap.insert(2, 2);

    std::vector<Pair<int, int>> pairs = intHeap.asVector();
    
    REQUIRE(pairs.at(0).value == 4);
    REQUIRE(pairs.at(1).value == 2);
    REQUIRE(pairs.at(2).value == 3);
    REQUIRE(pairs.at(3).value == 1);
}
