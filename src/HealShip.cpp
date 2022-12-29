#include <string>

#include "HealShip.h"

HealShip::HealShip() {

}

HealShip::HealShip (std::string front, std::string back) {
    Pos F (front);
    Pos B (back);  
    //controllo se la nave inserita è orizzontale o verticale 
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
    if (move(input, p1.getDefenceField().getShipArray())) {
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
    switch(_facing){
        case 0: //nave orizzontale
            //controllo che la nave sia dentro il campo da gioco 
            if (_midPos.x<0 || _midPos.x > 10 || _midPos.y<0 || _midPos.y > 11){
                return false;
            }
            //controllo che la nave non si sovrapponga ad altre già presenti 
            for(Ship* s : ship){
                std::vector<Pos> segment = getSegments(s);
                for(Pos p : segment){
                    if (p == _midPos || p == (_midPos + Pos(-1,0)) || p == (_midPos + Pos(1,0))){
                        return false;
                    }
                }
            }
            break;
        case 1://nave verticale
            if (_midPos.x<0 || _midPos.x > 11 || _midPos.y<0 || _midPos.y > 10){
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
    for (Ship* s : ship){
        std::vector<Pos> segments = getSegments(s);
        for(Pos pos : segments){
            /*
                il controllo che un segmento di una nave sia dentro l'area di influenza della HealShip
                 è effetuato controllando che la distanza tra il segmento e il centro della HealShip sia <=1 
                 per entrambi gli assi cartesiani  
            */
            if(std::abs(pos.x - _midPos.x) <= 1 && std::abs(pos.y - _midPos.y) <= 1){
                s->resetShield();
            }
        }
    }
}