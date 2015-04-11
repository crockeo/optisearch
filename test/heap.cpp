//////////////
// Includes //
#include "../src/heap.hpp"

//////////
// Code //
TEST_CASE("Will compile") {
    Heap<int, int> intHeap;

    intHeap.insert(3, 3);
    intHeap.insert(1, 1);
    intHeap.insert(4, 4);
    intHeap.insert(2, 2);

    REQUIRE(intHeap.remove() == 4);
    REQUIRE(intHeap.remove() == 3);
    REQUIRE(intHeap.remove() == 2);
    REQUIRE(intHeap.remove() == 1);
}
