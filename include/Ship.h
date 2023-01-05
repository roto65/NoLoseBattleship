#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include <exception>
#include <memory>

#include "Types.h" //Forward declarated classes

#include "Pos.h"
#include "Player.h"

class Ship {

    public:
        Ship();
        int getFacing();
        Pos getMidPos();
        int getLength();
        char getUpperChar();
        char getLowerChar();

        std::vector<char>& getShield();
        void setShield(std::vector<char> shield);
        

        /*
            metodo per riportare la nave a "tutta integra" quando viene curata da una HealShip
        */
        void resetShield();
        
        /*
            metodo per eseguire l'azione tipica di una nave.
            Definito bool per permettere il ciclo nel main 
            in caso di inserimento di dati non accettabili
        */
        virtual bool action(std::string XYTarget, Player& p1, Player& p2) = 0; 
        //p1 giocatore che esegue l'azione / p2 giocatore che subisce l'azione
        
        class illegal_length : public std::exception {
            public:
                const char* what() const noexcept {
                    return "La lunghezza inserita non e' valida!\n";
                }
        };
        bool isSunk();

    protected:
        Pos _midPos;                // posizione centrale della nave. identifica la nave
        int _facing;                // 0 -> nave orizzontale / 1 -> nave verticale
        int _length;                // lunghezza della nave
        std::vector<char> _shield;  // corazza della nave / minuscole = segmento colpito / maiuscole = segmento intatto
        char _upperChar;
        char _lowerChar;
};

std::vector<Pos> getSegments(std::shared_ptr<Ship> s);

#endif // SHIP_H