#include <iostream>
#include <string>

#include "BattleShip.h"
#include "Pos.h"

BattleShip::BattleShip(){

}

BattleShip::BattleShip(std::string front, std::string back){
    Pos F (front);
    Pos B (back);    //conversione da stringa a pos
    if (distance(F, B) != 4.0) {
        throw illegal_length();
    }
    if(F.x == B.x) {
        _facing = 1;
    } else {
        _facing = 0;
    }
    _midPos.x = (F.x + B.x) / 2;
    _midPos.y = (F.y + B.y) / 2;
    _length = 5;
    resetShield();
}

bool BattleShip::action(std::string input, Player p1, Player p2){
    Pos I (input);
    if((I.x<12&&I.x>=0)&&(I.y<12&&I.y>=0)){
        return false;
    }
    else{
        for(Ship* s : p2.getDefenceField().getShipArray()){
            std::vector<Pos> segments = getSegments(s);
            for(Pos p : segments){
                if(p==I){
                    p1.getAttackField().insertChar('X', I);
                    return true;
                }
            }
        }
        p1.getAttackField().insertChar('O', I);
        return true;
    }
    
}

void BattleShip::resetShield() {
    _shield = {'C','C','C','C','C'};
}
