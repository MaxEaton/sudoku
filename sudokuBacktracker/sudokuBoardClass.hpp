#ifndef SUDOKUBOARDCLASS
#define SUDOKUBOARDCLASS

#include <iostream>
#include <array>
#include <bitset>

#define z findBox(x, y)
#define side 3
#define sideSquared (side*side)

struct Board {
    public:

    std::array<std::array<char, sideSquared>, sideSquared> initial;
    std::array<std::array<char, sideSquared>, sideSquared> board;
    std::array<std::bitset<sideSquared>, sideSquared> row;
    std::array<std::bitset<sideSquared>, sideSquared> col;
    std::array<std::bitset<sideSquared>, sideSquared> box;

    Board();

    Board(std::array<std::array<char, sideSquared>, sideSquared> state);

    void generate();

    void solve();

    void unsolve();

    bool onlySol();

    void printBoard();
    
    private:

    bool onlySolBool = false;
    bool generateBool = false;
    std::array<std::array<char, sideSquared>, sideSquared> solution;

    std::array<char, sideSquared> reorderNumber();

    int findBox(int x, int y);

    std::pair<int, int> findEmpty(int x, int y);

    void strip();

    void decompose();

    bool backtracker(int x, int y);
};

#endif