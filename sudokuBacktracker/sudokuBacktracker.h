#ifndef SUDOKUBACKTRACKER
#define SUDOKUBACKTRACKER

#include <iostream>
#include <array>
#include <bitset>
#include <tuple>

#define z findBox(x, y)
#define side 3
#define sideSquared side*side

struct Board {
    public:

    std::array<std::array<char, sideSquared>, sideSquared> initial;
    std::array<std::array<char, sideSquared>, sideSquared> board;
    std::array<std::bitset<sideSquared>, sideSquared> row;
    std::array<std::bitset<sideSquared>, sideSquared> col;
    std::array<std::bitset<sideSquared>, sideSquared> box;

    Board(std::array<std::array<char, sideSquared>, sideSquared> state);

    void solve();

    void unsolve();

    bool onlySol();

    void printBoard();
    
    private:

    bool checkingMore = false;
    std::array<std::array<char, sideSquared>, sideSquared> second;

    int findBox(int x, int y);

    std::pair<int, int> findEmpty(int x, int y);

    void strip();

    bool backtracker(int x, int y);
};

std::array<std::array<char, sideSquared>, sideSquared> strToMatrix(std::string str);

bool validInput(std::string str);

#endif