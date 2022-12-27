#include <string>

#include "HealShip.h"

HealShip::HealShip() {

}

HealShip::HealShip (std::string front, std::string back) {
    Pos F (front);
    Pos B (back);    //conversione da stringa a pos
    if(F.x == B.x){
        _facing = 1;
    } else {
        _facing = 0;
    }
    _midPos.x = (F.x + B.x) / 2;
    _midPos.y = (F.y + B.y) / 2;
    _length = 3;
    resetShield();
}

bool HealShip::action(std::string input, Player p1, Player p2) {
    if (move(input,p1.getDefenceField().getShipArray())) {
        heal(p1.getDefenceField().getShipArray());
        return true;
    } else {
        return false;
    }
}

void HealShip::resetShield() {
    _shield = {'S','S','S'};
}

bool HealShip::move (std::string input, std::vector<Ship*> ship){
    //fai i cazzo di controlli per la posizione
    switch(_facing){
        case 0:
            if (_midPos.x > 10 || _midPos.y > 11){
                return false;
            }
            for(Ship* s : ship){
                std::vector<Pos> segment = getSegments(s);
                for(Pos p : segment){
                    if (p == _midPos || p == (_midPos + Pos(-1,0)) || p == (_midPos + Pos(1,0))){
                        return false;
                    }
                }
            }
            break;
        case 1:
            if (_midPos.x > 11 || _midPos.y > 10){
                return false;
            }
            for(Ship* s : ship){
                std::vector<Pos> segment = getSegments(s);
                for(Pos p : segment){
                    if (p == _midPos || p == (_midPos + Pos(0,-1)) || p == (_midPos + Pos(0,1))){
                        return false;
                    }
                }
            }
            break;
    }
    _midPos = Pos(input);
    return true;
}

void HealShip::heal(std::vector<Ship*> ship){
    // area 3x3 intorno al _midPos --> basta che ci sia un segmento della nave per curarla tutta
    for (Ship* s : ship){
        std::vector<Pos> segment = getSegments(s);
        for(Pos p : segment){
            switch(_facing){
                case 0:
                    if (p == (_midPos + Pos(-1,-1)) || p == (_midPos + Pos(0,-1)) || p == (_midPos + Pos(1,-1)) || p == (_midPos + Pos(-1,1)) || p == (_midPos + Pos(0,1)) || p == (_midPos + Pos(1,1))){
                        s->resetShield(); //metodo da scrivere
                    }
                    break;
                case 1:
                    break;
            }
        }
    }
}