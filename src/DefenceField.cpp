#include <array>
#include <vector>
#include <iostream>

#include "DefenceField.h"
#include "Ship.h"

constexpr std::array<char, 12> labels = {'A','B','C','D','E','F','G','H','I','L','M','N'};

DefenceField::DefenceField() {

}

std::vector<Ship*> DefenceField::getShipArray() {
    return _field;
}

void DefenceField::setShipArray(std::vector<Ship*> arr) {
    _field = arr;
}

int DefenceField::getShipCount() {
    return _field.size();
}

bool DefenceField::insertShip(Ship* newShip) {
    int len = newShip -> getLength();
    std::vector<Pos> temp = getSegments(newShip);                                      //variabile per tenere conto della posizione occupata dalla nave che sta venendo inserita
    for(int i=0; i < len; i++){
        if(temp[i].x < 0 || temp[i].x > 11 || temp[i].y <0 || temp[i].y > 11){
            return false; //se un pezzo della nave è fuori dal campo questa non viene inserita
        }
        else {
            for(Ship* s : _field) {
                std::vector<Pos> segments = getSegments(s);
                for(Pos p : segments) {
                    if(p == temp[i]) {
                        return false; //la nave inserita collide con un pezzo di un altra
                    }
                }
            }
        }
    }
    _field.push_back(newShip);
    return true;
}