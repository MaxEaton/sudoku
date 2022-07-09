#include <iostream>
#include <fstream>
#include <chrono>

#include "sudokuMisc.hpp"
#include "sudokuBoardClass.hpp"

#define trainingNumber 100000
#define testingNumber (trainingNumber/4)

int main() {
    auto timeAmount = std::chrono::high_resolution_clock::now(); 
    
    srand(time(0));
    Board board;
    board.generate();
    board.printBoard();
    board.solve();
    board.printBoard();
    

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timeAmount).count() / 1000 << " milliseconds\n";
    return 0;
}

void collectInput() {
    std::string str;
    std::array<std::array<char, sideSquared>, sideSquared> state;

    while (!validInput(str)) {
        std::cout << "Enter state of board: ";
        std::cin >> str;

    }
    state = strToMatrix(str);

    Board board(state);
    board.printBoard();
    board.solve();
    board.printBoard();
}

void collectStuff() {
    srand(time(0));
    Board board;
    std::ofstream stuff;
    stuff.open("stuff.txt", std::ofstream::out | std::ofstream::trunc);
    for (int i=0; i<trainingNumber; i++) {
        board.generate();
        stuff << matrixToStr(board.board) << "\n";
        board.solve();
        stuff << matrixToStr(board.board) << "\n";
    }
    stuff.close();
    
    std::ofstream stuff2;
    stuff2.open("stuff2.txt", std::ofstream::out | std::ofstream::trunc);
    for (int i=0; i<testingNumber; i++) {
        board.generate();
        stuff2 << matrixToStr(board.board) << "\n";
        board.solve();
        stuff2 << matrixToStr(board.board) << "\n";
    }
    stuff2.close();
}