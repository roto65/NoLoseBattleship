#include <string>
#include <memory>
#include <vector>

#include <stdlib.h>

#include "Submarine.h"
#include "Player.h"
#include "Pos.h"

Submarine::Submarine () {

}

Submarine::Submarine (std::string point) {
    Pos P (point);
    _midPos.x = P.x;
    _midPos.y = P.y;    
    _facing = 0;      // facing e' ereditato da ship ma in submarine non viene mai utilizzato (valore 0 come default)
    _length = 1;
    _upperChar = 'E';
    _lowerChar = 'e';
    _shield = std::vector<char> (_length, _upperChar);
}

bool Submarine::action(std::string XYTarget, Player& p1, Player& p2) {
    if (move(XYTarget,p1.getDefenceField().getShipArray())) {
        scan(p1, p2.getDefenceField().getShipArray());
        return true;
    } else {
        return false;
    }
}

bool Submarine::move(std::string XYTarget, std::vector<std::shared_ptr<Ship>> ships) {
    Pos targetPos (XYTarget);

    //controllo che la posizione sia nel campo da gioco
    if (_midPos.x < 0 || _midPos.x > 11 || _midPos.y < 0 || _midPos.y > 11) { 
        return false;
    } else if (_midPos == targetPos) {

        // controllo se la nave si sta muovendo sul posto (il sottomarino fa solo scan)
        return true;
    } else {

        //controllo che la nave non si sovrapponga ad altre presenti sul campo 
        for (std::shared_ptr<Ship> s : ships) {
            std::vector<Pos> segment = getSegments(s);
            for (Pos p : segment) {
                if (p == targetPos) {
                    return false;
                }
            }
        }
    }
    _midPos = targetPos;
    return true;
}

void Submarine::scan(Player& player, std::vector<std::shared_ptr<Ship>> ships) {  
    for (int i = (_midPos.x - 2); i <= (_midPos.x + 2); i++) {
        for (int j = (_midPos.y -2); j <= (_midPos.y + 2); j++) {
            if (0 <= i && i <= 11 && 0 <= j && j <= 11) {
                player.getAttackField().insertChar(' ', Pos(i,j));
            }
        }
    }
    for (std::shared_ptr<Ship> s : ships) {
        std::vector<Pos> segments = getSegments(s);
        int i = 0;
        for (Pos pos : segments) {
            /*
                il controllo che un segmento di una nave sia nell'area 
                scannerizzata viene effettuato guardando che la distanza da tale segmento 
                al sottomarino che sta effettuando l'azione sia <= 2 su entrami gli assi cartesiani 
            */
            if (std::abs(pos.x - _midPos.x) <= 2 && std::abs(pos.y - _midPos.y) <= 2) {
                if (s->getShield()[i] == s->getUpperChar()) {
                    player.getAttackField().insertChar('Y', pos);
                } else {
                    player.getAttackField().insertChar('X', pos);
                }
            }
            i++;
        }
    }
}