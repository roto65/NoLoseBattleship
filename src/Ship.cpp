#include <memory>

#include "Ship.h"

Ship::Ship() {

}

bool Ship::isSunk() {
    bool check = true; //verifica le condizioni della nave / true = affondata / false = ancora a galla
    for (int i = 0; i < _shield.size() && check; i++) {
        if ((int) _shield[i] >= 65 && (int) _shield[i] <= 90) check = false; // se almeno un segmento non è colpito segna la nave a galla
    }
    return check;
}

int Ship::getFacing() {
    return _facing;
}

Pos Ship::getMidPos() {
    return _midPos;
}

int Ship::getLength() {
    return _length;
}

char Ship::getUpperChar() {
    return _upperChar;
}

char Ship::getLowerChar() {
    return _lowerChar;
}

std::vector<char>& Ship::getShield() {
    return _shield;
}

void Ship::resetShield() {
    _shield = std::vector<char> (_length, _upperChar);
}

std::vector<Pos> getSegments(std::shared_ptr<Ship> s) {
    std::vector <Pos> segments;
    int halfLen = (s -> getLength()) / 2;
    switch (s -> getFacing()) {
        case 0:
            for (int i = -halfLen; i <= halfLen; i++) {
                segments.push_back(s -> getMidPos() + Pos (i, 0));
            }
            break;
        case 1:
            for (int i = -halfLen; i <= halfLen; i++) {
                segments.push_back(s -> getMidPos() + Pos (0, i));
            }
            break;
    }
    return segments;
}