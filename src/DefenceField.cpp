#include <array>
#include <vector>
#include <iostream>
#include <memory>

#include "DefenceField.h"
#include "Ship.h"

DefenceField::DefenceField() {

}

std::vector<std::shared_ptr<Ship>> DefenceField::getShipArray() {
    return _defenceField;
}

void DefenceField::setShipArray(std::vector<std::shared_ptr<Ship>> arr) {
    _defenceField = arr;
}

int DefenceField::getShipCount() {
    return _defenceField.size();
}

bool DefenceField::insertShip(std::shared_ptr<Ship> newShip) {
    int len = newShip -> getLength();
    std::vector<Pos> temp = getSegments(newShip); //variabile per tenere conto della posizione occupata dalla nave che sta venendo inserita
    for(int i = 0; i < len; i++){
        if(temp[i].x < 0 || temp[i].x > 11 || temp[i].y <0 || temp[i].y > 11){
            std::cout<<"Tentativo di inserire nave fuori dalla griglia\n";
            return false; //se un pezzo della nave è fuori dal campo questa non viene inserita
        }
        else {
            for(std::shared_ptr<Ship> s : _defenceField) {
                std::vector<Pos> segments = getSegments(s);
                for(Pos p : segments) {
                    if(p == temp[i]) {
                        std::cout<<"Tentativo di inserire nave in posizione occupata da un'altra nave\n";
                        return false; //la nave inserita collide con un pezzo di un altra
                    }
                }
            }
        }
    }
    _defenceField.push_back(newShip);
    return true;
}

bool DefenceField::removeShips() {
    for(std::vector<std::shared_ptr<Ship>>::iterator it = _defenceField.begin(); it != _defenceField.end(); it++) {
        std::shared_ptr<Ship> temp = *it;
        if (temp -> isSunk()) {
            _defenceField.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<std::string> DefenceField::getField(){
    std::vector<std::string> _fieldArray (12,"            "); //stringa di 12 elementi vuoti
    for (std::shared_ptr<Ship> s : _defenceField){
        int i = 0;
        for(Pos p : getSegments(s)){
            _fieldArray[p.y][p.x] = s->getShield()[i];
            i++;
        }
    }
    return _fieldArray;
}