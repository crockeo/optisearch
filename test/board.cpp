//////////
// Code //


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
