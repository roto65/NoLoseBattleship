#include <iostream>

#include "Player.h"
#include "AttackField.h"
#include "DefenceField.h"

Player::Player() {
    
}

AttackField Player::getAttackField() {
    return _af;
}

DefenceField& Player::getDefenceField() {
    return _df;
}

void Player::printFields() {
    std::vector<char> labels = {'A','B','C','D','E','F','G','H','I','L','M','N'};
    std::cout<<"--+---+---+---+---+---+---+---+---+---+---+---+---+" << "\t" << "--+---+---+---+---+---+---+---+---+---+---+---+---+" << std::endl;
    for(int i = 0; i < labels.size(); i++){
        std::cout << labels[i] << " | ";
        for(char c : _df.getField()[i]){
            std::cout << c << " | ";
        }
        std::cout << "\t";
        std::cout << labels[i];
        for (int i = 0; i < _af.getField().size(); i ++){
            for (char c : _af.getField()[i])
            std::cout << c << " | ";
        }
        std::cout << std::endl;
        std::cout << " 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| " << "\t" << " 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12|" << std::endl; 
   }
}
bool activateShipAction(std::string XYOrigin, std::string XYTarget, Player p1, Player p2){
    Pos p (XYOrigin);
    for (Ship* s : p1.getDefenceField().getShipArray()){
        if(s->getMidPos() == p){
            s->action(XYTarget, p1, p2);
            return true;
        }
    }
    return false;
 }