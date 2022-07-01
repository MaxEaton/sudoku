#include <iostream>
#include <chrono>

#include "sudokuMisc.hpp"
#include "sudokuBoardClass.hpp"

int main() {
    auto timeAmount = std::chrono::high_resolution_clock::now();

    // std::string str;
    // std::array<std::array<char, sideSquared>, sideSquared> state;

    // while (!validInput(str)) {
    //     std::cout << "Enter state of board: ";
    //     std::cin >> str;

    // }
    // state = strToMatrix(str);

    // Board board(state);
    // board.printBoard();
    // board.solve();
    // board.printBoard();

    Board board;
    board.printBoard();
    board.solve();
    board.printBoard();
    
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timeAmount).count() / 1000 << " milliseconds\n";
    return 0;
}