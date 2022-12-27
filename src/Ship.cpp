#include "Ship.h"

Ship::Ship() {

}

bool Ship::isSunk() {
    bool check = true; //verifica le condizioni della nave / true = affondata / false = ancora a galla
    for(int i = 0; i < _shield.size() && check; i++){
        if((int) _shield[i] >= 65 && (int) _shield[i] <= 90) check = false; // se almeno un segmento non è colpito segna la nave a galla
    }
    return check;
}

int Ship::getFacing(){
    return _facing;
}

Pos Ship::getMidPos(){
    return _midPos;
}

std::vector<char> Ship::getShield(){
    return _shield;
}

void Ship::setShield(std::vector<char> shield){
    _shield=shield;
}

std::vector<Pos> getSegments(Ship* s){
    std::vector <Pos> segments;
    switch(s->getFacing()){
        case 0:
            segments.push_back(s->getMidPos() + Pos(0,-1));
            segments.push_back(s->getMidPos());
            segments.push_back(s->getMidPos() + Pos(0,1));
        break;
        case 1:
            segments.push_back(s->getMidPos() + Pos(-1,0));
            segments.push_back(s->getMidPos());
            segments.push_back(s->getMidPos() + Pos(1,0));
    }
    return segments;
}