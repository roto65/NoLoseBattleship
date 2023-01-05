#include <array>

#include "AttackField.h"
#include "Pos.h"

AttackField::AttackField() {
    _attackfield = std::vector<std::string> (12,"            ");
}

bool AttackField::insertChar(char c, Pos p) {
    if (_attackfield[p.y][p.x] != ' '){
        return false;
    } else {
        _attackfield[p.y][p.x] = c;
        return true;
    }
}

void AttackField::clearSonar(){
    for (int i = 0; i < _attackfield.size(); i++){
        for (int j = 0; j < _attackfield[i].size(); j++){
            if (_attackfield[i][j] == 'Y'){
                _attackfield[i][j] == ' ';
            }
        }
    }
}

void AttackField::clearHit(){
    for (int i = 0; i < _attackfield.size(); i++){
        for (int j = 0; j < _attackfield[i].size(); j++){
            if (_attackfield[i][j] == 'X'){
                _attackfield[i][j] == ' ';
            }
        }
    }
}

void AttackField::clearMiss(){
    for (int i = 0; i < _attackfield.size(); i++){
        for (int j = 0; j < _attackfield[i].size(); j++){
            if (_attackfield[i][j] == 'O'){
                _attackfield[i][j] == ' ';
            }
        }
    }
}

std::vector<std::string> AttackField::getField() {
    return _attackfield;
}