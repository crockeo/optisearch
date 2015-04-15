#include "search.hpp"

//////////////
// Includes //
#include <vector>
#include <tuple>

//////////
// Code //

// Finding the heuristic for the board itself.
int heuristic(const Board& b) {
    int sum = 0;
    for (int row = 0; row < b.getHeight(); row++)
        for (int col = 0; col < b.getWidth(); col++)
            sum += b.distance(col, row);
    return sum;
}

// Checking if a given board is the solution. For boards with more than one open
// space it will always return false.
bool isSolution(const Board& b) { return heuristic(b) == 0; }

// findSolution returns a vector of in-order moves to perform in order to reach
// a solution for a given board.
std::vector<BoardMove> findSolution(const Board b) {
    if (isSolution(b))
        return std::vector<BoardMove>();

    SearchHeap moveList([](float p1, float p2) -> float { return p2 - p1; });

    for (auto bm: b.validMoves()) {
        std::vector<BoardMove> moves { bm };
        Board temp = b.doMove(bm);

        int h = heuristic(temp);
        if (h == 0)
            return moves;

        moveList.insert(h / 2.f + 0.5f, std::make_tuple(temp, moves));
    }

    while (!moveList.isEmpty()) {
        auto pair      = moveList.removeTuple();
        auto board     = std::get<0>(pair.value);
        auto prevMoves = std::get<1>(pair.value);

        for (auto bm: board.validMoves()) {
            std::vector<BoardMove> moves = prevMoves;
            moves.push_back(bm);

            Board temp = board.doMove(bm);

            int h = heuristic(temp);
            if (h == 0)
                return moves;

            moveList.insert(pair.priority + (h / 2.f + 0.5f), std::make_tuple(temp, moves));
        }
    }

    return std::vector<BoardMove>();
}
