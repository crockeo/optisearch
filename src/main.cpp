//////////////
// Includes //
#include <exception>
#include <iostream>
#include <vector>

#include "search.hpp"
#include "board.hpp"

//////////
// Code //

// Printing out a whole board.
void printBoard(const Board& b) {
    for (int row = 0; row < b.getHeight(); row++) {
        std::cout << "  ";
        for (int col = 0; col < b.getWidth(); col++)
            std::cout << b.getState(col, row) << " ";
        std::cout << std::endl;
    }
}

// Printing out a board move.
void printBoardMove(const BoardMove& bm) {
    std::cout << "  {"  << bm.col1 << "," << bm.row1
              << "}->{" << bm.col2 << "," << bm.row2
              << "}"    << std::endl;
}

// The entry point.
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Proper usage: " << argv[0] << " <path/to/board/file>" << std::endl;
        return 1;
    }

    Board b;
    try {
        b = loadBoard(std::string(argv[1]));
    } catch (std::runtime_error e) {
        std::cout << "Failed to load board: " << e.what() << std::endl;
        return 1;
    }

    if (isSolution(b)) {
        std::cout << "That board is already solved." << std::endl;
        return 0;
    }

    std::vector<BoardMove> moves = findSolution(b);
    if (moves.size() == 0) {
        std::cout << "That board is unsolvable." << std::endl;
        return 0;
    }

    std::cout << "Board:" << std::endl;
    printBoard(b);
    std::cout << "Board solution:" << std::endl;
    for (auto bm: moves)
        printBoardMove(bm);
}
