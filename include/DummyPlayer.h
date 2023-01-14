// Autore: Francesco Ariani (2041835)

#ifndef DUMMY_PLAYER_H
#define DUMMY_PLAYER_H

#include <string>
#include <queue>
#include <string>

#include "Player.h"

/*
    classe che imita un Player durante l'esecuzione dei replay.
    Gestisce la lettura delle azioni di gioco e di stampa dei campi
*/
class DummyPlayer : public Player{
    public:
        DummyPlayer();
        DummyPlayer(std::string name);
        
        /*
            metodo che unisce il campo di difesa e di attacco di un DummyPlayer in un unica stringa.
            Utilizzato per la stampa dei campi nel replay su file
        */
        std::string getFields();

        /*
            metodo che gestisce l'azione di un DummyPlayer.
            Sovrascrive lo stesso metodo di Player per evitare che nei replay 
            venga richiesto di inserire un comando
        */
        void action (std::string XYOrigin, std::string XYTarget, Player& p2);

        /*
            metodo per inserire le navi di un DummyPlayer
        */
        void insertAllShips(std::queue<std::string>& Vercingetorige);
    
};

/*
    metodo che combina front() e pop() di std::queue
*/
std::string nextElem(std::queue<std::string>& queue);

#endif //DUMMY_ PLAYER_H