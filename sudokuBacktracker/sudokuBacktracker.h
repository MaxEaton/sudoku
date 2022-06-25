#ifndef SUDOKUBACKTRACKER
#define SUDOKUBACKTRACKER

#include <iostream>
#include <array>
#include <bitset>
#include <tuple>

#define z findBox(x, y)
#define side 3
#define length side*side

struct Board {
    public:

    std::array<std::array<char, length>, length> initial;
    std::array<std::array<char, length>, length> board;
    std::array<std::bitset<length>, length> row;
    std::array<std::bitset<length>, length> col;
    std::array<std::bitset<length>, length> box;

    Board(std::array<std::array<char, length>, length> state);

    void solve();

    void unsolve();

    bool onlySol();

    void printBoard();
    
    private:

    bool checkingMore = false;
    std::array<std::array<char, length>, length> second;

    int findBox(int x, int y);

    std::pair<int, int> findEmpty(int x, int y);

    void strip();

    bool backtracker(int x, int y);
};

std::array<std::array<char, length>, length> strToMatrix(std::string str);

#endif