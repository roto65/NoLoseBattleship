#ifndef HEALSHIP_H
#define HEALSHIP_H

#include <string>
#include <vector>

#include "Ship.h"
#include "Pos.h"


class HealShip : public Ship {

    public:
        HealShip();
        HealShip(std::string front, std::string back);

        /*
            override del metodo action.
        */
        bool action(std::string XYTarget, Player p1, Player p2) override;

    private:
        /*
            metodo per spostare la nave in una posizione data da input
            controlla che la posizione inserita sia all'interno del campo di gioco 
            e che la nave non si sovrapponga ad altre presenti nel campo.

            Definito bool per permettere il ciclo nel main in caso si inserimento non corretto 
        */
        bool move(std::string input, std::vector <Ship*> ship);

        /*
            metodo per ripristinare lo shield di ogni nave 
            che abbia almento un segmento all'interno di un'area 3x3 
            dal centro della HealShip che sta effettuando l'azione
        */
        void heal(std::vector<Ship*> ship);

};

#endif // HEALSHIP_H