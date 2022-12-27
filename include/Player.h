#ifndef PLAYER_H
#define PLAYER_H

#include "AttackField.h"
#include "DefenceField.h"

class Player {

    public:
        Player();

        AttackField getAttackField();
        DefenceField getDefenceField(); //richiama DefenceField::getShipArray() 

        void printFields();
    private:
        AttackField  _af;
        DefenceField _df;
};

#endif // PLAYER_H