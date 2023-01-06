#include <vector>

#include "AttackField.h"
#include "Pos.h"

AttackField::AttackField() {
    _attackfield = std::vector<std::string> (12,"            "); //vettore di 12 stringhe vuote
}

bool AttackField::insertChar(char c, Pos p) { 
    _attackfield[p.y][p.x] = c;
    return true;
}

void AttackField::clearSonar() {
    /*
        i campi vengono gestiti come matrici bidimensionali
        in quanto le stringhe possono essere considerate array di char
    */
    for (int i = 0; i < _attackfield.size(); i++) {
        for (int j = 0; j < _attackfield[i].size(); j++) {
            if (_attackfield[i][j] == 'Y') {
                _attackfield[i][j] = ' ';
            }
        }
    }
}

void AttackField::clearHit() {
    /*
        i campi vengono gestiti come matrici bidimensionali
        in quanto le stringhe possono essere considerate array di char
    */
    for (int i = 0; i < _attackfield.size(); i++) {
        for (int j = 0; j < _attackfield[i].size(); j++) {
            if (_attackfield[i][j] == 'X') {
                _attackfield[i][j] = ' ';
            }
        }
    }
}

void AttackField::clearMiss(){
    /*
        i campi vengono gestiti come matrici bidimensionali
        in quanto le stringhe possono essere considerate array di char
    */
    for (int i = 0; i < _attackfield.size(); i++) {
        for (int j = 0; j < _attackfield[i].size(); j++) {
            if (_attackfield[i][j] == 'O') {
                _attackfield[i][j] = ' ';
            }
        }
    }
}

std::vector<std::string>& AttackField::getField() {
    return _attackfield;
}