#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include <exception>

#include "Types.h" //Forward declarated classes

#include "Pos.h"
#include "Player.h"

class Ship {

    public:
        Ship();
        int getFacing();
        Pos getMidPos();
        int getLength();
        std::vector<char> getShield();
        void setShield(std::vector<char> shield);

        /*
            metodo per riportare la nave a "tutta integra" quando viene curata da una HealShip
        */
        virtual void resetShield() = 0;
        
        /*
            metodo per eseguire l'azione tipica di una nave.
            Definito bool per permettere il ciclo nel main 
            in caso di inserimento di dati non accettabili
        */
        virtual bool action(std::string input, Player p1, Player p2) = 0; 
        //p1 giocatore che esegue l'azione / p2 giocatore che subisce l'azione
        
        class illegal_length : public std::exception {
            public:
                const char* what() {
                    return "Illegal Length";
                }
        };

    protected:
        Pos _midPos;                // posizione centrale della nave. identifica la nave
        int _facing;                // 0 -> nave orizzontale / 1 -> nave verticale
        int _length;                // lunghezza della nave
        std::vector<char> _shield;  // corazza della nave / minuscole = segmento colpito / maiuscole = segmento intatto
            
        bool isSunk();
};

std::vector<Pos> getSegments(Ship*);

#endif // SHIP_H