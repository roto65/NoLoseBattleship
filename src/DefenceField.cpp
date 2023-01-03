#include <array>
#include <vector>
#include <iostream>

#include "DefenceField.h"
#include "Ship.h"

DefenceField::DefenceField() {

}

std::vector<Ship*> DefenceField::getShipArray() {
    return _defenceField;
}

void DefenceField::setShipArray(std::vector<Ship*> arr) {
    _defenceField = arr;
}

int DefenceField::getShipCount() {
    return _defenceField.size();
}

bool DefenceField::insertShip(Ship* newShip) {
    int len = newShip -> getLength();
    std::vector<Pos> temp = getSegments(newShip);                                      //variabile per tenere conto della posizione occupata dalla nave che sta venendo inserita
    for(int i=0; i < len; i++){
        if(temp[i].x < 0 || temp[i].x > 11 || temp[i].y <0 || temp[i].y > 11){
            return false; //se un pezzo della nave è fuori dal campo questa non viene inserita
        }
        else {
            for(Ship* s : _defenceField) {
                std::vector<Pos> segments = getSegments(s);
                for(Pos p : segments) {
                    if(p == temp[i]) {
                        return false; //la nave inserita collide con un pezzo di un altra
                    }
                }
            }
        }
    }
    _defenceField.push_back(newShip);
    return true;
}

std::vector<std::string> DefenceField::getField(){
    std::vector<std::string> _fieldArray (12,"            "); //stringa di 12 elementi vuoti
    for (Ship* s : _defenceField){
        int i = 0;
        for(Pos p : getSegments(s)){
            _fieldArray[p.y][p.x] = s->getShield()[i];
            i++;
        }
    }
    return _fieldArray;
}