#ifndef PLAYER_H
#define PLAYER_H

#include "Types.h" //Forward declarated classes

#include "AttackField.h"
#include "DefenceField.h"

class Player {

    public:
        Player();

        AttackField getAttackField();
        DefenceField& getDefenceField(); //richiama DefenceField::getShipArray() 

        void printFields();
    private:
        AttackField  _af;
        DefenceField _df;
};
bool activateShipAction(std::string XYOrigin, std::string XYTarget, Player p1, Player p2);

#endif // PLAYER_H