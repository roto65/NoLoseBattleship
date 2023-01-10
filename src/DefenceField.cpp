// Autore: Alessandro Rotondo (2032447)

#include <vector>
#include <string>
#include <memory>

#include "DefenceField.h"
#include "Ship.h"
#include "Pos.h"

DefenceField::DefenceField() {

}

std::vector<std::shared_ptr<Ship>>& DefenceField::getShipArray() {
    return _defenceField;
}

int DefenceField::getShipCount() {
    return _defenceField.size();
}

bool DefenceField::insertShip(std::shared_ptr<Ship> newShip) {
    int len = newShip->getLength();
    std::vector<Pos> temp = getSegments(newShip);               //variabile per tenere conto della posizione occupata dalla nave che sta venendo inserita
    for (int i = 0; i < len; i++) {
        if (temp[i].x < 0 || temp[i].x > 11 || temp[i].y < 0 || temp[i].y > 11) { 
            throw out_of_bound_exception();                     //se un pezzo della nave è fuori dal campo questa non viene inserita
        } else {
            for (std::shared_ptr<Ship> s : _defenceField) {
                std::vector<Pos> segments = getSegments(s);
                for (Pos p : segments) {
                    if (p == temp[i]) {
                        throw overlap_exception();              //la nave inserita collide con un pezzo di un altra
                    }
                }
            }
        }
    }
    _defenceField.push_back(newShip);                           //inserimento della nave se passa tutti i controlli
    return true;
}

void DefenceField::removeShips() {

    // omesso il tipo auto per it in modo da rendere il codice piu' esplicito
    for (std::vector<std::shared_ptr<Ship>>::iterator it = _defenceField.begin(); it != _defenceField.end(); it++) {
        std::shared_ptr<Ship> tempIt = *it;
        if (tempIt->isSunk()) {
            _defenceField.erase(it);
            return;
        }
    }
}

void DefenceField::nukeShips() {
    _defenceField.clear();
}

std::vector<std::string> DefenceField::getField() {
    std::vector<std::string> _fieldArray (12,"            ");   //stringa di 12 elementi vuoti
    for (std::shared_ptr<Ship> s : _defenceField) {             //scorre  tutte le navi 
        int i = 0;
        for (Pos p : getSegments(s)) {                          //scorre tutte le posizione occupate da una nave
            _fieldArray[p.y][p.x] = s->getShield()[i];
            i++;
        }
    }
    return _fieldArray;
}