// Autore: Simone Pietrogrande (2032448)

#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include <exception>
#include <memory>

#include "Types.h" //Forward declarated classes
#include "Pos.h"
#include "Player.h"

/*
    classe madre che implementa la gestione delle navi.
    Viene ereditata da Battleship/HealShip/Submarine
*/
class Ship {

    public:
        Ship();

        /*
            metodi getter di tutti gli attributi di una nave
        */
        int getFacing();                //restiruisce il facing
        Pos getMidPos();                //restituisce la posizione centrale
        int getLength();                //restituisce la lunghezza della nave
        char getUpperChar();            //restituisce il carattere identificativo della nave in muiuscolo
        char getLowerChar();            //restituisce il carattere identificativo della nave in minuscolo
        std::vector<char>& getShield(); //restituisce il vettore dello scudo di una nave
        
        /*
            metodo per riportare la nave a "tutta integra" quando viene curata da una HealShip
        */
        void resetShield();
        
        /*
            metodo viruale puro per eseguire l'azione tipica di una nave.
            Definito bool per permettere il ciclo nel main 
            in caso di inserimento di dati non accettabili
        */
        virtual bool action(std::string XYTarget, Player& p1, Player& p2) = 0; 
        //p1 giocatore che esegue l'azione / p2 giocatore che subisce l'azione

        /*
            metodo che restituisce lo stato di una nave:
            true se la nave e affondata;
            false se la nave e' ancora in gioco 
        */
        bool isSunk();

        /*
            distruttore di default per tutti gli oggetti di tipo Ship
            dichiarato virtual in modo da richiamare anche i distruttori delle 
            classi che estendono Ship
        */
        virtual ~Ship() = default;

        /*
            eccezione lanciata se le coordinata inserite per creare una nave 
            non rispettano la sua lunghezza
        */
        class illegal_length_exception : public std::exception {
            public:
                const char* what() const noexcept {
                    return "La lunghezza inserita non e' valida!\n";
                }
        };
        
    protected:
        Pos _midPos;                // posizione centrale della nave. identifica la nave
        int _facing;                // 0 -> nave orizzontale / 1 -> nave verticale
        int _length;                // lunghezza della nave
        std::vector<char> _shield;  // corazza della nave / minuscole = segmento colpito / maiuscole = segmento intatto
        char _upperChar;            // carattere maiuscolo identificativo della nave 
        char _lowerChar;            // carattere minuscolo identificativo della nave
};


/*
    metodo che restituisce tutte le posizioni occupate da una nave
    a partire dalla sua posizione centrale
*/
std::vector<Pos> getSegments(std::shared_ptr<Ship> s);

#endif // SHIP_H