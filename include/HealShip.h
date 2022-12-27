#ifndef HEALSHIP_H
#define HEALSHIP_H

#include <string>
#include <vector>

#include "Ship.h"
#include "Pos.h"


class HealShip : public Ship {

    public:
        HealShip();
        HealShip(std::string front, std::string back);

        bool action(std::string input, Player p1, Player p2) override;
        void resetShield() override;

    private:
        bool move(std::string input, std::vector <Ship*> ship);
        void heal(std::vector<Ship*> ship);

};

#endif // HEALSHIP_H