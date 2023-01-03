#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include "Pos.h"

class Computer : public Player {
    public:
        std::vector<std::string> createRandomShip(int dim);
        std::string selectRandomShip (std::vector<Ship*> s);  //forse da sostituire Pos con string per tenere traccia nei replay
        std::string randomAction ();        
};

Pos getRandomPosition();
int randomNum (int max);
#endif // COMPUTER_H