#include <array>
#include <vector>

#include "DefenceField.h"
#include "Ship.h"

constexpr std::array<char, 12> labels = {'A','B','C','D','E','F','G','H','I','L','M','N'};
const std::array<Pos, 5> orizontal = { Pos (0,0), Pos (1,0), Pos (-1,0), Pos (2,0), Pos (-2,0)};
const std::array<Pos, 5> vertical = { Pos (0,0), Pos (0,1), Pos (0,-1), Pos (0,2), Pos (0,-2)};

DefenceField::DefenceField() {

}

std::vector<Ship*> DefenceField::getShipArray() {
    return _field;
}

int DefenceField::getShipCount() {
    return _field.size();
}

bool DefenceField::insertShip(Ship* s) {

    int len = s -> getLength();
    std::vector<Pos> temp;                                      //variabile per tenere conto della posizione occupata dalla nave che sta venendo inserita
    for(int i = 0; i < len; i++){                               //mette dentro temp le posizioni delle celle occupate dalla nave
        if(s -> getFacing() == 0){                              //nel caso sia orizontale
            temp.push_back(s -> getMidPos() + orizontal[i]);
        } else {                                                   
            temp.push_back(s -> getMidPos() + vertical[i]);     //nel caso sia verticale
        }
    }
    for(int i=0; i < len; i++){
        if(temp[i].x < 0 || temp[i].x > 11 || temp[i].y <0 || temp[i].y > 11){
            return false; //se un pezzo della nave è fuori dal campo questa non viene inserita
        }
        else {
            for(Ship* s : _field) {
                std::vector<Pos> segment = getSegments(s);
                for(Pos p : segment) {
                    if(p == temp[i]) {
                        return false; //la nave inserita collide con un pezzo di un altra
                    }
                }
            }
        }
    }
    _field.push_back(s);
    return true;

}