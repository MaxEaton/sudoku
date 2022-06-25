#include <iostream>
#include <chrono>

#include "sudokuBacktracker.h"

int main() {
    auto timeAmount = std::chrono::high_resolution_clock::now();

    std::string str = "060000070010026000004000250900050003400080900080000407806400000040100008090038000";
    // std::string str = "000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    std::array<std::array<char, length>, length> state;

    state = strToMatrix(str);

    Board board(state);
    board.printBoard();
    board.solve();
    board.printBoard();
    
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timeAmount).count() / 1000 << " milliseconds\n";
    return 0;
}