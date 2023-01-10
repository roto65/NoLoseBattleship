// Autore: Simone Pietrogrande (2032448)

#include <string>
#include <memory>
#include <vector>

#include <stdlib.h>

#include "HealShip.h"
#include "Pos.h"
#include "Player.h"

HealShip::HealShip() {

}

HealShip::HealShip (std::string front, std::string back) {
    Pos F (front);
    Pos B (back);

    if (distance(F, B) != 2) {
        throw illegal_length_exception();
    }

    //controllo se la nave inserita è orizzontale o verticale 
    if (F.x == B.x) {
        _facing = 1;
    } else {
        _facing = 0;
    }
    _midPos.x = (F.x + B.x) / 2;
    _midPos.y = (F.y + B.y) / 2;
    _length = 3;
    _upperChar = 'S';
    _lowerChar = 's';
    _shield = std::vector<char> (_length, _upperChar);
}

bool HealShip::action(std::string XYTarget, Player& p1, Player& p2) {
    if (move(XYTarget, p1.getDefenceField().getShipArray())) {
        heal(p1.getDefenceField().getShipArray());
        return true;
    } else {
        return false;
    }
}

bool HealShip::move (std::string XYTarget, std::vector<std::shared_ptr<Ship>> ship) {
    Pos targetPos (XYTarget);
    
    switch (_facing) {
        case 0:     //nave orizzontale

            //controllo che la nave sia dentro il campo da gioco 
            if (targetPos.x < 1 || targetPos.x > 10 || targetPos.y < 0 || targetPos.y > 11) {
                return false;
            }

            //controllo che la nave non si sovrapponga ad altre già presenti
            for (std::shared_ptr<Ship> s : ship) {          //scorre tutte le navi 
                if (s->getMidPos() == _midPos) continue;    //evita di fare controlli sulla nave che sta facendo l'azione
                std::vector<Pos> segment = getSegments(s);
                for (Pos p : segment) {                     //scorre tutte le posizioni occupate dalla nave
                    if (p == targetPos || p == (targetPos + Pos(-1,0)) || p == (targetPos + Pos(1,0))) {
                        return false;                       //la nave andrebbe a collidere con una già esistente
                    }
                }
                if ((targetPos.x -1) < 0 || (targetPos.x + 1) > 11) {
                    return false;                           //la nave avrebbe dei segmenti fuori dalla griglia di gioco 
                }
            }
            break;
        case 1:     //nave verticale
            if (targetPos.x < 0 || targetPos.x > 11 || targetPos.y < 1 || targetPos.y > 10) {
                return false;
            }
            for (std::shared_ptr<Ship> s : ship) {  
                if (s->getMidPos() == _midPos) continue;
                std::vector<Pos> segment = getSegments(s);
                for (Pos p : segment) {
                    if (p == targetPos || p == (targetPos + Pos(0,-1)) || p == (targetPos + Pos(0,1))) {
                        return false;
                    }
                }
                if ((targetPos.y -1) < 0 || (targetPos.y + 1) > 11) {
                    return false;
                }
            }
            break;
    }
    _midPos = targetPos;                                    //aggiornamento della posizione se la nave passa tutti i controlli
    return true;
}

void HealShip::heal(std::vector<std::shared_ptr<Ship>>& ship) {
    for (std::shared_ptr<Ship> s : ship) {                   //scorre tutte le navi
        if (s->getMidPos() == _midPos) continue;             //evita di fare controlli sulla nave che sta facendo l'azione
        std::vector<Pos> segments = getSegments(s);

        for (Pos pos : segments) {

            /*
                il controllo che un segmento di una nave sia dentro l'area di influenza della HealShip
                 è effetuato controllando che la distanza tra il segmento e il centro della HealShip sia <=1 
                 per entrambi gli assi cartesiani  
            */
            if (std::abs(pos.x - _midPos.x) <= 1 && std::abs(pos.y - _midPos.y) <= 1) {
                s->resetShield();
            }
        }
    }
}