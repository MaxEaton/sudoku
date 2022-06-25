#include <iostream>
#include <array>
#include <bitset>
#include <tuple>

#include "sudokuBacktracker.h"

#define z findBox(x, y)
#define side 3
#define length side*side

Board::Board(std::array<std::array<char, length>, length> state) {
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
    if (board == initial) {
        solve();
        if (board == initial) {
            
            return false;
        }
    }
    checkingMore = true;
    second = board;
    unsolve();
    solve();
    checkingMore = false;
    if (board == initial) {
        return true;
    }
    return false;
}

void Board::printBoard() {
    for (int x=0; x<length; x++) {
        std::cout << " ";
        for (int y=0; y<length; y++) {
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
    while (x < length) {
        if (board[x][y] == '0') {
            return {x, y};
        }
        y += 1;
        if (y == length) {
            y = 0;
            x += 1;
        }
    }
    return {length, length};
}

void Board::strip() {
    char num;
    for (int x=0; x<length; x++) {
        for (int y=0; y<length; y++) {
            num = board[x][y];
            if (num != '0') {
                row[x].set(num-'1');
                col[y].set(num-'1');
                box[z].set(num-'1');
            }
        }
    }
}

bool Board::backtracker(int x, int y) {
    std::tie(x, y) = findEmpty(x, y);
    if (x == length) {
        if (checkingMore && board == second) {
            return false;
        }
        return true;
    }
    std::bitset<length> const cell = row[x] | col[y] | box[z];
    if (cell.all()) {
        return false;
    }
    for (int n=0; n<length; n++) {
        if (!cell[n]) {
            board[x][y] = '1' + n;
            row[x].set(n);
            col[y].set(n);
            box[z].set(n);
            if (backtracker(x, y)) {
                return true;
            }
            row[x].reset(n);
            col[y].reset(n);
            box[z].reset(n);
        }
    }
    board[x][y] = '0';
    return false;
}

std::array<std::array<char, length>, length> strToMatrix(std::string str) {
    std::array<std::array<char, length>, length> matrix;
    for (int x=0; x<length; x++) {
        for (int y=0; y<length; y++) {
            matrix[x][y] = str[x*length+y];
        }
    }
    return matrix;
}