// Note to random developer,
//
// Hi Randev,
//   This is really cluttered. I understand. The whole testing suite for a
//  whole project ought not be in a single file. That being said, to my
//  understanding, Catch (the library I'm using for my testing framework)
//  assigns IDs to tests based on line number in their .cpp file. I tried having
//  them in a bunch of places, but if they had conflicting line numbers they
//  just would NOT compile.
//
//   In other words, sorry. I hope you'll forgive me one day. And if not, just
//  send all of your complaints nowhere.

//////////////////////
// Setting up Catch //
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//////////////
// Includes //
#include <vector>

#include "search.hpp"
#include "board.hpp"
#include "heap.hpp"

//////////
// Code //

////
// Search

// Testing manhattan distance.
TEST_CASE("Manhattan Distance") {
    REQUIRE(manhattanDistance( 0, 0,  1, 1) == 2);
    REQUIRE(manhattanDistance( 0, 0,  5, 1) == 6);
    REQUIRE(manhattanDistance( 4, 3,  1, 2) == 4);
    REQUIRE(manhattanDistance(10, 7, -3, 4) == 16);
    REQUIRE(manhattanDistance(31, 0, 31, 0) == 0);
}

////
// Board

// Testing board construction.
TEST_CASE("Board Construction") {
    Board empty(2, 2);
    for (int row = 0; row < empty.getHeight(); row++)
        for (int col = 0; col < empty.getWidth(); col++)
            REQUIRE(empty.getState(row, col) == 0);

    std::vector<int> states {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };
    Board filled(3, 3, states);

    for (int row = 0; row < filled.getHeight(); row++)
        for (int col = 0; col < filled.getWidth(); col++)
            REQUIRE(filled.getState(col, row) == row * filled.getWidth() + col);
}

// Testing the distance function on a board.
TEST_CASE("Board Distance") {
    std::vector<int> states {
        1, 3, 7,
        2, 4, 8,
        5, 0, 6
    };
    Board filled(3, 3, states);

    REQUIRE(filled.distance(0, 0) == 1);
    REQUIRE(filled.distance(1, 0) == 2);
    REQUIRE(filled.distance(2, 0) == 3);
    REQUIRE(filled.distance(0, 1) == 3);
    REQUIRE(filled.distance(1, 1) == 0);
    REQUIRE(filled.distance(2, 1) == 1);
    REQUIRE(filled.distance(0, 2) == 3);
    REQUIRE(filled.distance(1, 2) == 3);
    REQUIRE(filled.distance(2, 2) == 2);
}

////
// Heap

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