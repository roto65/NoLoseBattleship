#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <string>

#include "Ship.h"
#include "Pos.h"
#include "Player.h"

/*
    classe che gestisce la nave corazzata.
    Estende la classe Ship
*/

class BattleShip : public Ship {

    public:
        BattleShip();
        BattleShip(std::string front, std::string back);

        /*
            override del metodo action.
            La Battleship spara in una posizione data da input.
            Sul campo d'attacco viene visualizzato 'X' se colpito, 'O' se mancato
        */
        bool action(std::string XYTarget, Player& p1, Player& p2) override;

};

#endif // BATTLESHIP_H