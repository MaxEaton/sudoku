#ifndef SUDOKUMISC
#define SUDOKUMISC

#include <iostream>
#include <array>
#include <bitset>

#define z findBox(x, y)
#define side 3
#define sideSquared (side*side)

std::array<std::array<char, sideSquared>, sideSquared> strToMatrix(std::string str);

std::string matrixToStr(std::array<std::array<char, sideSquared>, sideSquared> matrix);

bool validInput(std::string str);

int randSideSquared();

#endif