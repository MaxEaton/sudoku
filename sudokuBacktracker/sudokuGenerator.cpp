#include <iostream>
#include <array>
#include <random>
#include <time.h>

#include "sudokuMisc.hpp"
#include "sudokuBoardClass.hpp"

#define z findBox(x, y)
#define side 3
#define sideSquared (side*side)

int randSideSquared() {
    return rand() % sideSquared;
}

Board::Board() {
    generate();
}

std::array<char, sideSquared> Board::reorderNumber() {
    std::array<char, sideSquared> order = {{'1', '2', '3', '4', '5', '6', '7', '8', '9'}};
    for (int i=0; i<sideSquared; i++) {
        int randNum = randSideSquared();
        char temp = order[i];
        order[i] = order[randNum];
        order[randNum] = temp;
    }
    return order;
}

void Board::generate() {
    row = {0};
    col = {0};
    box = {0};
    board = {{
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0'}
    }};
    generateBool = true;
    srand(time(0));
    backtracker(0, 0);
    solution = board;
    decompose();
    strip();
    generateBool = false;
}

void Board::decompose() {
    char temp;
    // int count = 0;
    for (int x=0; x<sideSquared; x++) {
        for (int y=0; y<sideSquared; y++) {
            if (rand() % 3 < 2) {
                temp = board[x][y];
                board[x][y] = '0';
                initial = board;
                if (!onlySol()) {
                    board = initial;
                    board[x][y] = temp;
                } else {
                    board = initial;
                    // count += 1;
                }
                initial = board;
                unsolve();
            }
        }
    }
    // std::cout << count << std::endl;
    return;
}