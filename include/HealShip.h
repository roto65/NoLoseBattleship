// Autore: Simone Pietrogrande (2032448)

#ifndef HEALSHIP_H
#define HEALSHIP_H

#include <vector>
#include <string>
#include <memory>

#include "Ship.h"
#include "Player.h"

/*
    classe che gestisce una nave di supporto.
    Estende la classe Ship
*/
class HealShip : public Ship {

    public:
        HealShip();
        HealShip(std::string front, std::string back);

        /*
            override del metodo action.
            La nave da supporto si sposta in una posizione data da input;
            cura tutte le navi che hanno almeno un segmento in un'area 3x3 dal centro della nave di supporto
        */
        bool action(std::string XYTarget, Player& p1, Player& p2) override;

    private:

        /*
            metodo per spostare la nave in una posizione data da input
            controlla che la posizione inserita sia all'interno del campo di gioco 
            e che la nave non si sovrapponga ad altre presenti nel campo.

            Definito bool per permettere il ciclo nel main in caso si inserimento non corretto 
        */
        bool move(std::string XYTarget, std::vector <std::shared_ptr<Ship>> ship);

        /*
            metodo per ripristinare lo shield di ogni nave 
            che abbia almento un segmento all'interno di un'area 3x3 
            dal centro della HealShip che sta effettuando l'azione
        */
        void heal(std::vector<std::shared_ptr<Ship>>& ship);

};

#endif // HEALSHIP_H