// Autore: Alessandro Rotondo (2032447)

#ifndef ATTACK_FIELD_H
#define ATTACK_FIELD_H

#include <vector>
#include <string>

#include "Pos.h"

/*
    classe che gestisce il campo d'attacco di un giocatore
*/
class AttackField {

    public: 
        /*
            costruttore di default
            crea un campo di 12 stringhe vuote 
        */
        AttackField();

        /*
            metodo per inserire un determinato carattere 
            in una posizione del campo di attacco
        */
        bool insertChar(char c, Pos p);

        /*
            metodo per rimuovere tutti i caratteri 'Y'
            Viene invocato dall'input "AA AA"
        */
        void clearSonar();

        /*
            metodo per rimuovere tutti i caratteri 'X'
            Viene invocato dall'input "BB BB"
        */
        void clearHit();

        /*
            metodo per rimuovere tutti i caratteri 'O'
            Viene invocato dall'input "CC CC"
        */
        void clearMiss();

        /*
            metodo per sparare in ogni cella del campo    
        */
        void nukeField();

        /*
            metodo per restituire il campo 
        */
        std::vector<std::string>& getField();

    private:
        std::vector<std::string> _attackfield;
};

#endif // ATTACK_FIELD_H