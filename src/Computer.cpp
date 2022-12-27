#include <random>

#include "Computer.h"
#include "Pos.h"

constexpr int SIZE = 11;

Pos getRandomPosition() {
    std::random_device rd;
    std::mt19937 mt (rd());
    std::uniform_int_distribution<int> dist (0, SIZE);

    Pos randPos (dist(mt), dist(mt));
    return randPos;
}