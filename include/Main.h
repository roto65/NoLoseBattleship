// Autore: Francesco Ariani (2041835)

#ifndef MAIN_H
#define MAIN_H

#include "Player.h"
#include "Computer.h"

/*
    metodo che gestisce le condizioni di terminazione di una partita;
    decreta che giocatore ha vinto o se la partita e' finita in parita';
    il metodo ritorna false quando la partita finisce in modo che il while di gameLoop si interrompa

*/
bool endGame(Player p1, Player p2, int round);


/*
    metodo per gestire il loop dei turni 
*/
template <typename T, typename U>
void gameLoop(T& p1, U& p2);

/*
    definizioni di funzioni template 
*/
#include "Main.hpp"

#endif // MAIN_H