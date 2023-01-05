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
        void action(Player& p2, std::vector<std::string>& _matchActions); 

    protected:
        AttackField  _af;
        DefenceField _df;
};
/*
    Helper function per verificare se esiste la nave che dovrebbe compiere l'azione.
    In caso affermativo compie l'azione della nave selezionata
*/
bool activateShipAction(std::string XYOrigin, std::string XYTarget, Player& p1, Player& p2);

#endif // PLAYER_H