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

//////////////
// Includes //
#include "catch.hpp"
#include <vector>

#include "search.hpp"
#include "astar.hpp"
#include "board.hpp"
#include "heap.hpp"
#include "maze.hpp"

//////////
// Code //

// LONG_TESTING defines whether or not one ought to wait for the long-running
// tests to complete.
const bool LONG_TESTING = false;

////
// Search

// Testing the board heuristic.
TEST_CASE("Board Heuristic") {
    std::vector<int> states {
        1, 3, 7,
        2, 4, 8,
        5, 0, 6
    };
    Board filled(3, 3, states);

    REQUIRE(heuristic(filled) == 18);
}

// Testing isSolution.
TEST_CASE("Solution Checking") {
    std::vector<int> states {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };
    Board filled(3, 3, states);

    REQUIRE(isSolution(filled));
}

// Testing the search method.
TEST_CASE("Board Search") {
    // An already-solved board.
    Board solved = loadBoard("res/solved.txt");
    std::vector<BoardMove> solvedMoves = findSolution(solved);
    REQUIRE(solvedMoves.size() == 0);

    // An easy first-move solution.
    Board easy = loadBoard("res/easy.txt");
    std::vector<BoardMove> easyMoves = findSolution(easy);

    REQUIRE(easyMoves.size() == 1);
    REQUIRE(easyMoves.at(0) == BoardMove(0, 0, 1, 0));

    // Testing a move involved solution.
    Board complicated = loadBoard("res/complicated.txt");
    std::vector<BoardMove> complicatedMoves = findSolution(complicated);

    REQUIRE(complicatedMoves.size() == 3);
    REQUIRE(complicatedMoves.at(0) == BoardMove(2, 0, 2, 1));
    REQUIRE(complicatedMoves.at(1) == BoardMove(1, 0, 2, 0));
    REQUIRE(complicatedMoves.at(2) == BoardMove(0, 0, 1, 0));

    if (LONG_TESTING) {
        // Trying to find a solution on a board that has no solution.
        Board unsolvable = loadBoard("res/unsolvable.txt");
        std::vector<BoardMove> unsolvableMoves = findSolution(unsolvable);

        REQUIRE(unsolvableMoves.size() == 0);
    }
}

////
// A* Search

TEST_CASE("A* Search") {
    Maze maze(0, 0, 10, 0);
    SearchableMaze searchableMaze(maze);

    AStarSearcher<Maze> searcher(searchableMaze);

    std::vector<Maze> testSolution {
        Maze( 0, 0, 10, 0),
        Maze( 1, 0, 10, 0),
        Maze( 2, 0, 10, 0),
        Maze( 3, 0, 10, 0),
        Maze( 4, 0, 10, 0),
        Maze( 5, 0, 10, 0),
        Maze( 6, 0, 10, 0),
        Maze( 7, 0, 10, 0),
        Maze( 8, 0, 10, 0),
        Maze( 9, 0, 10, 0),
        Maze(10, 0, 10, 0),
    };

    std::vector<Maze> foundSolution = searcher.findSolution();

    for (int i = 0; i < testSolution.size(); i++)
        REQUIRE(testSolution.at(i) == foundSolution.at(i));
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

// Testing operator== for boards.
TEST_CASE("Equality") {
    std::vector<int> states {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    Board board1(3, 3, states);
    Board board2(3, 3, states);

    REQUIRE(board1 == board2);
}

// Testing isValidMove for a board.
TEST_CASE("Validating Moves") {
    std::vector<int> states {
        1, 3, 7,
        2, 4, 8,
        5, 0, 6
    };
    Board filled(3, 3, states);

    REQUIRE(filled.isValidMove(BoardMove(1, 1,
                                         1, 2)) == true);

    REQUIRE(filled.isValidMove(BoardMove(0, 0,
                                         0, 0)) == false);

    REQUIRE(filled.isValidMove(BoardMove(1, 3,
                                         1, 2)) == false);
}

// Testing doMove for a board.
TEST_CASE("doMove") {
    std::vector<int> vs0 {
        1, 3, 7,
        2, 0, 8,
        5, 4, 6
    };
    Board moved1(3, 3, vs0);

    std::vector<int> vs1 {
        1, 3, 7,
        2, 4, 8,
        0, 5, 6
    };
    Board moved2(3, 3, vs1);

    std::vector<int> vs2 {
        1, 3, 7,
        2, 4, 8,
        5, 6, 0
    };
    Board moved3(3, 3, vs2);

    // Setting up the real board.
    std::vector<int> states {
        1, 3, 7,
        2, 4, 8,
        5, 0, 6
    };
    Board filled(3, 3, states);

    REQUIRE(filled.doMove(BoardMove(1, 1, 1, 2)) == moved1);
    REQUIRE(filled.doMove(BoardMove(0, 2, 1, 2)) == moved2);
    REQUIRE(filled.doMove(BoardMove(2, 2, 1, 2)) == moved3);
    REQUIRE_THROWS(filled.doMove(BoardMove(-1, -1, 3, 3)));
}

// Testing getState & setState on the board.
TEST_CASE("Get & Set") {
    Board empty(3, 3);

    empty.setState(0, 0, 3);
    empty.setState(1, 0, 2);

    REQUIRE(empty.getState(0, 0) == 3);
    REQUIRE(empty.getState(1, 0) == 2);
    REQUIRE(empty.getState(2, 0) == 0);
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

// Testing loading a board from a file.
TEST_CASE("Load") {
    Board b = loadBoard("res/board01.txt");

    for (int row = 0; row < b.getHeight(); row++)
        for (int col = 0; col < b.getWidth(); col++)
            REQUIRE(b.getState(col, row) == row * b.getWidth() + col);

    REQUIRE_THROWS(loadBoard("res/doesnotexist.txt"));
    REQUIRE_THROWS(loadBoard("res/invalidsize.txt"));
    REQUIRE_THROWS(loadBoard("res/invalidboard.txt"));
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

////
// Maze

// Testing the maze constructor.
TEST_CASE("Maze Construction") {
    Maze maze(0, 0, 1, 1);

    REQUIRE(maze.px == 0);
    REQUIRE(maze.py == 0);
    REQUIRE(maze.tx == 1);
    REQUIRE(maze.ty == 1);
}

// Testing maze heuristic.
TEST_CASE("Maze Heuristic") {
    Maze maze1(0, 0, 1, 1);
    REQUIRE(maze1.heuristic() == 2);

    Maze maze2(0, 0, 10, 0);
    REQUIRE(maze2.heuristic() == 10);
}

// Testing maze equality.
TEST_CASE("Maze Equality") {
    Maze maze1(0, 0, 1, 1);
    Maze maze2(1, 1, 0, 0);
    Maze maze3(0, 0, 1, 1);

    REQUIRE(maze1 != maze2);
    REQUIRE(maze2 != maze3);
    REQUIRE(maze1 == maze3);
}

TEST_CASE("Maze Ordering") {
    Maze maze1(0, 0, 0, 0);
    Maze maze2(0, 0, 0, 1);
    Maze maze3(0, 0, 1, 0);
    Maze maze4(0, 1, 0, 0);
    Maze maze5(1, 0, 0, 0);

    REQUIRE(maze1 < maze2);
    REQUIRE(maze2 < maze3);
    REQUIRE(maze3 < maze4);
    REQUIRE(maze4 < maze5);
}
