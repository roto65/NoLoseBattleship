#include <string>

#include "BattleShip.h"
#include "Pos.h"

BattleShip::BattleShip(){

}

BattleShip::BattleShip(std::string front, std::string back){
    Pos F (front);
    Pos B (back);    //conversione da stringa a pos
    if(F.x == B.x){
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
        char hit;
        
        p1.getAttackField().insertChar(hit, I);
    }
    return true;
}

void BattleShip::resetShield() {
    _shield = {'C','C','C','C','C'};
}
