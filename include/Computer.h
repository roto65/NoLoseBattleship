#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "Pos.h"

/*
    classe per la gestione di un computer che gioca
    Eestende la classe Player.
    Implementa i metodi per generare i comandi in maniera casuale
*/
class Computer : public Player {
    public:

        /*
            metodo per creare in maniera casuale un nave, sapendone la lunghezza
        */
        std::vector<std::string> createRandomShip(int dim);

        /*
            metodo che restituisce le coordinate di una nave selezionata casualmente da un vettore
        */
        std::string selectRandomShip (std::vector<std::shared_ptr<Ship>> s);
        
        /*
            metodo per far eseguire un'azione randomica al computer 
        */
        void action (Player& p2, std::vector<std::string>& matchActions);       
};

/*
   metodo  restiruisce una coordinata randomica
*/
Pos getRandomPosition();

/*
    metodo genera un numero casuale compreso tra max e min inclusi
*/
int randomNum (int max, int min = 0);

#endif // COMPUTER_H