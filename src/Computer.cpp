#include <random>
#include <memory>

#include "Computer.h"
#include "Pos.h"

constexpr int FIELD_SIZE = 11;

std::vector<std::string> Computer::createRandomShip(int dim){
    Pos front=getRandomPosition();
    std::vector<Pos> direction {Pos(0,dim-1),Pos(0,-1*(dim-1)),Pos(dim-1,0),Pos(-1*(dim-1),0)};
    int i = randomNum(direction.size() - 1);
    Pos back=front+direction[i];
    return std::vector<std::string> {front.toString(),back.toString()};
}

std::string Computer::selectRandomShip(std::vector<std::shared_ptr<Ship>> s){
    int i = randomNum(s.size() - 1);
    return s[i] -> getMidPos().toString();
}

std::string Computer::randomAction() {
    return getRandomPosition().toString();
}

Pos getRandomPosition() {
    Pos randPos (randomNum(FIELD_SIZE),randomNum(FIELD_SIZE));
    return randPos;
}

int randomNum(int max) {
    std::random_device rd;
    std::mt19937 mt (rd());                             // Mersenne Twister 19937 random number generator
    std::uniform_int_distribution<int> dist (0, max); 

    return dist(rd);
}