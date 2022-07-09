#include <iostream>
#include <fstream>
#include <array>
#include <bitset>
#include <chrono>

#define int1byte unsigned __int8
#define int2byte unsigned __int16
#define z findBox(x, y)
#define side 3
#define sideSquared 9
#define sideFourth 81

// #define trainingNumber 100000
#define trainingNumber 1
// #define testingNumber (trainingNumber/4)
#define population 100
#define survivePop 10
#define mutationRate 100 // read as 1 / mutationRate
#define generations 100

// note that crossBreed is only compatible with population 100 and survivalPop 10

int randMutate() {
    return rand() % mutationRate;
}

int randFourth() {
    return rand() % sideFourth;
}

int1byte rand1byte() {
    return rand() * rand();
}

int2byte rand2byte() {
    return rand() * rand();
}

int charToInt(char c) {
    return (int)(c-48);
}

std::array<int2byte, sideFourth> strToVector(std::string str) {
    std::array<int2byte, sideFourth> vector;
    for (int i=0; i<sideFourth; i++) {
        vector[i] = charToInt(str[i]);
    }
    return vector;
}

int findBox(int x, int y) {
    return (x / side) * side + y / side;
}

int fitnessScore (std::array<int2byte, sideFourth> prediction, std::array<int2byte, sideFourth> solution) {
    int score = 0;
    std::array<std::bitset<sideSquared>, sideSquared> row = {0};
    std::array<std::bitset<sideSquared>, sideSquared> col = {0};
    std::array<std::bitset<sideSquared>, sideSquared> box = {0};
    for (int x=0; x<sideSquared; x++) {
        for (int y=0; y<sideSquared; y++) {
            if (prediction[x*sideSquared+y] != solution[x*sideSquared+y]-1) {
                score += 1;
            }
            if (row[x][prediction[x*sideSquared+y]]) {
                score += 1;
            }
            if (col[y][prediction[x*sideSquared+y]]) {
                score += 1;
            }
            if (box[z][prediction[x*sideSquared+y]]) {
                score += 1;
            }
            row[x].set(prediction[x*sideSquared+y]);
            col[y].set(prediction[x*sideSquared+y]);
            box[z].set(prediction[x*sideSquared+y]);
        }
    }
    return score;
}

std::array<int2byte, sideFourth> transitioning(std::array<int2byte, sideFourth> initial, std::array<std::array<int1byte, sideFourth>, sideFourth> transitionMatrix, std::array<int1byte, sideFourth> shift) {
    std::array<int2byte, sideFourth> transitioned = {0};
    for (int a=0; a<sideFourth; a++) {
        for (int b=0; b<sideFourth; b++) {
            transitioned[a] += initial[b] * transitionMatrix[a][b];
        }
        transitioned[a] += shift[a];
    }
    return transitioned;
}

std::array<int2byte, sideFourth> modulated(std::array<int2byte, sideFourth> transitioned, std::array<int2byte, sideFourth> modulo) {
    // for (int a=0; a<sideFourth; a++) {
    //     if (modulo[a] == 0) {
    //         transitioned[a] = 0;
    //     }
    //     while (transitioned[a] >= sideSquared) {
    //         transitioned[a] %= modulo[a];
    //         if (transitioned[a] < sideSquared) {
    //             break;
    //         }
    //         modulo[a] %= transitioned[a];
    //         if (modulo[a] < sideSquared) {
    //             transitioned[a] = modulo[a];
    //             break;
    //         }
    //     }
    // }
    for (int a=0; a<sideFourth; a++) {
        transitioned[a] %= 9;
    }
    return transitioned;
}

void survival(std::array<int, population> fitness, std::array<std::array<std::array<int1byte, sideFourth>, sideFourth>, population> &transMatrices, std::array<std::array<int1byte, sideFourth>, population> &shifts, std::array<std::array<int2byte, sideFourth>, population> &modulos) {
    for (int i=0; i<population; i++) {
        for (int i2=0; i2<population; i2++) {
            if (fitness[i2] > fitness[i]) {
                int temp = fitness[i];
                fitness[i] = fitness[i2];
                fitness[i2] = temp;
                std::array<std::array<int1byte, sideFourth>, sideFourth> tempTransMatrix = transMatrices[i];
                transMatrices[i] = transMatrices[i2];
                transMatrices[i2] = tempTransMatrix;
                std::array<int1byte, sideFourth> tempShift = shifts[i];
                shifts[i] = shifts[i2];
                shifts[i2] = tempShift;
                std::array<int2byte, sideFourth> tempModulo = modulos[i];
                modulos[i] = modulos[i2];
                modulos[i2] = tempModulo;
            }
        }
    }
    return;
}

void crossBreed(std::array<std::array<std::array<int1byte, sideFourth>, sideFourth>, population> &transMatrices, std::array<std::array<int1byte, sideFourth>, population> &shifts, std::array<std::array<int2byte, sideFourth>, population> &modulos) {
    int index = survivePop;
    for (int k=0; k<survivePop; k++) {
        for (int k2=0; k2<survivePop; k2++) {
            if (k != k2) {
                int randCutOff = randFourth();
                for (int i=0; i<randCutOff; i++) {
                    if (i < randCutOff) {
                        transMatrices[index][i] = transMatrices[k][i];
                        shifts[index][i] = shifts[k][i];
                        modulos[index][i] = modulos[k][i];
                    } else {
                        transMatrices[index][i] = transMatrices[k2][i];
                        shifts[index][i] = shifts[k2][i];
                        modulos[index][i] = modulos[k2][i];
                    }
                    for (int i2=0; i2<randCutOff; i2++) {
                        if (!randMutate()) {
                            transMatrices[index][i][i2] = rand1byte();
                        }
                    }
                    if (!randMutate()) {
                        shifts[index][i] = rand1byte();
                    }
                    if (!randMutate()) {
                        modulos[index][i] = rand2byte();
                    }
                }
                index += 1;
            }
        }
    }
}

void accessStuff(std::array<std::array<int2byte, sideFourth>, trainingNumber> &initials, std::array<std::array<int2byte, sideFourth>, trainingNumber> &solutions) {
    std::ifstream stuff_txt;
    stuff_txt.open("stuff.txt");
    std::string initial;
    std::string solution;
    for (int j=0; j<trainingNumber; j++) {
        std::getline(stuff_txt, initial);
        std::getline(stuff_txt, solution);
        initials[j] = strToVector(initial);
        solutions[j] = strToVector(solution);
    }
    stuff_txt.close();
    return;
}

void accessParams(std::array<std::array<std::array<int1byte, sideFourth>, sideFourth>, population> &transMatrices, std::array<std::array<int1byte, sideFourth>, population> &shifts, std::array<std::array<int2byte, sideFourth>, population> &modulos) {
    for (int i=0; i<population; i++) {
        std::ifstream transMatrix_txt;
        transMatrix_txt.open("transMatrices/transMatrix" + std::to_string(i) + ".txt");
        std::string transInd;
        for (int a=0; a<sideFourth; a++) {
            for (int b=0; b<sideFourth; b++) {
                std::getline(transMatrix_txt, transInd, ',');
                transMatrices[i][a][b] = std::stoi(transInd);
            }
            transMatrix_txt.ignore(1);
        }
        transMatrix_txt.close();

        std::ifstream shift_txt;
        shift_txt.open("shifts/shift" + std::to_string(i) + ".txt");
        std::string shiftInd;
        for (int a=0; a<sideFourth; a++) {
            std::getline(shift_txt, shiftInd, ',');
            shifts[i][a] = std::stoi(shiftInd);
        }
        shift_txt.close();

        std::ifstream modulo_txt;
        modulo_txt.open("modulos/modulo" + std::to_string(i) + ".txt");
        std::string moduloInd;
        for (int a=0; a<sideFourth; a++) {
            std::getline(modulo_txt, moduloInd, ',');
            modulos[i][a] = std::stoi(moduloInd);
        }
        modulo_txt.close();
    }
    return;
}

void saveParams(std::array<std::array<std::array<int1byte, sideFourth>, sideFourth>, population> transMatrices, std::array<std::array<int1byte, sideFourth>, population> shifts, std::array<std::array<int2byte, sideFourth>, population> modulos) {
    for (int i=0; i<population; i++) {
        std::ofstream transMatrix_txt;
        transMatrix_txt.open("transMatrices/transMatrix" + std::to_string(i) + ".txt", std::ofstream::out | std::ofstream::trunc);
        for (int a=0; a<sideFourth; a++) {
            for (int b=0; b<sideFourth; b++) {
                transMatrix_txt << transMatrices[i][a][b]*1 << ",";
            }
            transMatrix_txt << "\n";
        }
        transMatrix_txt.close();
        
        std::ofstream shift_txt;
        shift_txt.open("shifts/shift" + std::to_string(i) + ".txt", std::ofstream::out | std::ofstream::trunc);
        for (int a=0; a<sideFourth; a++) {
            shift_txt << shifts[i][a]*1 << ",";
        }
        shift_txt << "\n";
        shift_txt.close();
        
        std::ofstream modulo_txt;
        modulo_txt.open("modulos/modulo" + std::to_string(i) + ".txt", std::ofstream::out | std::ofstream::trunc);
        for (int a=0; a<sideFourth; a++) {
            modulo_txt << modulos[i][a] << ",";
        }
        modulo_txt << "\n";
        modulo_txt.close();
    }
    return;
}

void randomizeParams(std::array<std::array<std::array<int1byte, sideFourth>, sideFourth>, population> &transMatrices, std::array<std::array<int1byte, sideFourth>, population> &shifts, std::array<std::array<int2byte, sideFourth>, population> &modulos) {
    for (int i=0; i<population; i++) {
        for (int a=0; a<sideFourth; a++) {
            for (int b=0; b<sideFourth; b++) {
                transMatrices[i][a][b] = rand1byte();
            }
            shifts[i][a] = rand1byte();
            modulos[i][a] = rand2byte();
        }
    }
    return;
}

void predicting() {
    std::array<std::array<int2byte, sideFourth>, trainingNumber>* initials = new std::array<std::array<int2byte, sideFourth>, trainingNumber>;
    std::array<std::array<int2byte, sideFourth>, trainingNumber>* solutions = new std::array<std::array<int2byte, sideFourth>, trainingNumber>;
    accessStuff(*initials, *solutions);

    std::array<std::array<std::array<int1byte, sideFourth>, sideFourth>, population>* transMatrices = new std::array<std::array<std::array<int1byte, sideFourth>, sideFourth>, population>;
    std::array<std::array<int1byte, sideFourth>, population>* shifts = new std::array<std::array<int1byte, sideFourth>, population>;
    std::array<std::array<int2byte, sideFourth>, population>* modulos = new std::array<std::array<int2byte, sideFourth>, population>;
    accessParams(*transMatrices, *shifts, *modulos);
    // randomizeParams(*transMatrices, *shifts, *modulos);
    
    for (int g=0; g<generations; g++) {
        std::array<int, population> fitness = {0};
        for (int i=0; i<population; i++) {
            for (int j=0; j<trainingNumber; j++) {
                fitness[i] += fitnessScore(modulated(transitioning((*initials)[j], (*transMatrices)[i], (*shifts)[i]), (*modulos)[i]), (*solutions)[j]);
            }
            if (g+1 == generations) {
                std::cout << i << ": " << fitness[i] << std::endl;
            }
        }
        survival(fitness, *transMatrices, *shifts, *modulos);
        crossBreed(*transMatrices, *shifts, *modulos);
        // std::cout << "Generation " << g << std::endl;
    }

    saveParams(*transMatrices, *shifts, *modulos);

    delete initials;
    delete solutions;
    delete transMatrices;
    delete shifts;
    delete modulos;
    return;
}

int main() {
    auto timeAmount = std::chrono::high_resolution_clock::now(); 
    
    srand(time(0));
    predicting();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timeAmount).count() / 1000 << " milliseconds\n";
    return 0;
}