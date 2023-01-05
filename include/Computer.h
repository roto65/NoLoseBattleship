#ifndef COMPUTER_H
#define COMPUTER_H

#include <memory>

#include "Player.h"
#include "Pos.h"

class Computer : public Player {
    public:
        std::vector<std::string> createRandomShip(int dim);
        std::string selectRandomShip (std::vector<std::shared_ptr<Ship>> s);  //forse da sostituire Pos con string per tenere traccia nei replay
        void action (Player& p2, std::vector<std::string>& _matchActions);       
};

Pos getRandomPosition();
int randomNum (int max, int min = 0);
#endif // COMPUTER_H