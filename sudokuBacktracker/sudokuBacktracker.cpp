#include <iostream>
#include <array>
#include <bitset>
#include <tuple>

#include "sudokuMisc.hpp"
#include "sudokuBoardClass.hpp"

#define z findBox(x, y)
#define side 3
#define sideSquared (side*side)

Board::Board(std::array<std::array<char, sideSquared>, sideSquared> state) {
    initial = state;
    board = state;
    row = {0};
    col = {0};
    box = {0};
    strip();
}

void Board::solve() {
    backtracker(0, 0);
}

void Board::unsolve() {
    board = initial;
    row = {0};
    col = {0};
    box = {0};
    strip();
}

bool Board::onlySol() {
    if (!generateBool) {
        if (board == initial) {
            solve();
            if (board == initial) {
                return false;
            }
        }
        solution = board;
    } 
    generateBool = false;
    onlySolBool = true;
    unsolve();
    solve();
    onlySolBool = false;
    generateBool = true;
    if (board == initial) {
        return true;
    }
    return false;
}

void Board::printBoard() {
    for (int x=0; x<sideSquared; x++) {
        std::cout << " ";
        for (int y=0; y<sideSquared; y++) {
            std::cout << board[x][y] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int Board::findBox(int x, int y) {
    return (x / side) * side + y / side;
}

std::pair<int, int> Board::findEmpty(int x, int y) {
    while (x < sideSquared) {
        if (board[x][y] == '0') {
            return {x, y};
        }
        y += 1;
        if (y == sideSquared) {
            y = 0;
            x += 1;
        }
    }
    return {sideSquared, sideSquared};
}

void Board::strip() {
    char numChar;
    for (int x=0; x<sideSquared; x++) {
        for (int y=0; y<sideSquared; y++) {
            numChar = board[x][y];
            if (numChar != '0') {
                row[x].set(numChar-'1');
                col[y].set(numChar-'1');
                box[z].set(numChar-'1');
            }
        }
    }
}

bool Board::backtracker(int x, int y) {
    std::tie(x, y) = findEmpty(x, y);
    if (x == sideSquared) {
        if (onlySolBool && board == solution) {
            return false;
        }
        return true;
    }
    std::bitset<sideSquared> const cell = row[x] | col[y] | box[z];
    if (cell.all()) {
        return false;
    }
    std::array<char, sideSquared> order;
    if (generateBool) {
        order = reorderNumber();
    } else {
        order = {{'1', '2', '3', '4', '5', '6', '7', '8', '9'}};
    }
    for (int n=0; n<sideSquared; n++) {
        if (!cell[order[n]-'1']) {
            board[x][y] = order[n];
            row[x].set(order[n]-'1');
            col[y].set(order[n]-'1');
            box[z].set(order[n]-'1');
            if (backtracker(x, y)) {
                return true;
            }
            row[x].reset(order[n]-'1');
            col[y].reset(order[n]-'1');
            box[z].reset(order[n]-'1');
        }
    }
    board[x][y] = '0';
    return false;
}

std::array<std::array<char, sideSquared>, sideSquared> strToMatrix(std::string str) {
    std::array<std::array<char, sideSquared>, sideSquared> matrix;
    for (int x=0; x<sideSquared; x++) {
        for (int y=0; y<sideSquared; y++) {
            matrix[x][y] = str[x*sideSquared+y];
        }
    }
    return matrix;
}

bool validInput(std::string str) {
    if (str.length() < sideSquared) {
        return false;
    }
    for (int i=0; i<sideSquared; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}