#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <string>

#include "Ship.h"
#include "Player.h"

class Submarine : public Ship {

    public:
        Submarine();
        Submarine(std::string point);

        /*
            override del metodo action.
        */
        bool action(std::string input, Player p1, Player p2) override;
        
        /*
            override del metodo resetShield().
        */
        void resetShield() override;

    private:
        /*
            metodo per spostare la nave in una posizione data da input
            controlla che la posizione inserita sia all'interno del campo di gioco 
            e che la nave non si sovrapponga ad altre presenti nel campo.

            Definito bool per permettere il ciclo nel main in caso si inserimento non corretto 
        */
        bool move(std::string input, std::vector<Ship*> ships);

        /*
            metodo per la scansione del campo avversario 
            per la ricerca di navi in un'area 5x5 dal sottomarino che sta effetuando l'azione
        */
        void scan(Player p, std::vector<Ship*> ships);

};

#endif // SUBMARINE_H