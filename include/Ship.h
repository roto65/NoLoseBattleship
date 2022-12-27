#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>

#include "Pos.h"
#include "Player.h"

class Ship {

    public:
        Ship();
        int getFacing();
        Pos getMidPos();
        std::vector<char> getShield();
        void setShield(std::vector<char> shield);
        virtual void resetShield() = 0;
    protected:
        Pos _midPos;                // posizione centrale della nave. identifica la nave
        int _facing;                // 0 -> nave orizzontale / 1 -> nave verticale
        int _length;                // lunghezza della nave
        std::vector<char> _shield;  // corazza della nave / minuscole = segmento colpito / maiuscole = segmento intatto
            
        bool isSunk();
        virtual bool action(std::string input, Player p1, Player p2) = 0;
        

};
std::vector<Pos> getSegments(Ship*);
#endif // SHIP_H