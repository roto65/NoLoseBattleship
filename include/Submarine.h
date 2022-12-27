#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <string>

#include "Ship.h"
#include "Player.h"

class Submarine : public Ship {

    public:
        Submarine();
        Submarine(std::string front, std::string back);

        bool action(std::string input, Player p1, Player p2) override;
        void resetShield();

    private:
        void move(std::string input);
        void scan();

};

#endif // SUBMARINE_H