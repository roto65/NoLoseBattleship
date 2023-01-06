#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <string>
#include <vector>
#include <memory>

#include "Ship.h"
#include "Player.h"

/*
    classe che gestisce un sottomarino.
    Estende la classe Ship
*/
class Submarine : public Ship {

    public:
        Submarine();
        Submarine(std::string point);

        /*
            override del metodo action.
            Il sottomarino si muove in una posizione data da input;
            scannerizza un'area 5x5 dalla posizione centrale 
        */
        bool action(std::string XYTarget, Player& p1, Player& p2) override;

    private:
        /*
            metodo per spostare la nave in una posizione data da input
            controlla che la posizione inserita sia all'interno del campo di gioco 
            e che la nave non si sovrapponga ad altre presenti nel campo.

            Definito bool per permettere il ciclo nel main in caso si inserimento non corretto 
        */
        bool move(std::string XYTarget, std::vector<std::shared_ptr<Ship>> ships);

        /*
            metodo per la scansione del campo avversario 
            per la ricerca di navi in un'area 5x5 dal sottomarino che sta effetuando l'azione
        */
        void scan(Player& p, std::vector<std::shared_ptr<Ship>> ships);

};

#endif // SUBMARINE_H