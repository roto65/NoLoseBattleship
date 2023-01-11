// Autore: Alessandro Rotondo (2032447)

#ifndef DEFENCE_FIELD_H
#define DEFENCE_FIELD_H

#include <vector>
#include <string>
#include <exception>
#include <memory>

#include "Types.h" //Forward declarated classes

/*
    classe che gestisce il campo di difesa di un giocatore
*/
class DefenceField {

    public:
        DefenceField();

        /*
           metodo che restituisce il vettore delle navi  
        */
        std::vector<std::shared_ptr<Ship>>& getShipArray(); 

        /*
            metodo che restituisce il numero di navi ancora in gioco 
        */
        int getShipCount();

        /*
            metodo per inserire una nuova nave all'interno del vettore di navi
        */
        bool insertShip(std::shared_ptr<Ship> newShip);

        /*
            metodo che scorre tutto il vettore di navi;
            rimuove un'eventuale nave che ha lo shield completamente distrutto
        */
        void removeShips();

        /*
            metodo per distruggere tutte le navi
        */
        void nukeShips();

        /*
            metodo che trasforma il vettore di navi in un vettore di stringhe 
            per poter essere poi stampato a schermo 
        */
        std::vector<std::string> getField();

        /*
            eccezione lanciata in caso di tentato inserimento di una nave fuori dalla griglia di gioco 
        */
        class out_of_bound_exception : public std::exception {
            public:
                const char* what() const noexcept {
                    return "Tentativo di inserire nave fuori dalla griglia\n";
                }
        };

        /*
            eccezione lanciata nel caso si cerchi di posizionare una nave 
            che vada a sovrapporsi a una gia' esistente
        */
        class overlap_exception : public std::exception {
            public:
                const char* what() const noexcept {
                    return "Tentativo di inserire nave in posizione occupata da un'altra nave\n";
                }
        };
        
    private:
        std::vector<std::shared_ptr<Ship>> _defenceField; 
};

#include "Ship.h"

#endif // DEFENCE_FILELD_H