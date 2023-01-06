#ifndef MAIN_H
#define MAIN_H

#include "Player.h"
#include "Computer.h"

/*
    metodo per richiedere al giocatore le coordinate per inserire le navi 
*/
void insertPlayerShip(Player& p);

/*
    metodo che fa inserire casualmente le navi al computer
*/
void insertComputerShip(Computer& c);

/*
    metodo che gestisce le condizioni di terminazione di una partita;
    Decreta che giocatore ha vinto o se la partita e' finita in parita'
*/
bool endGame(Player p1, Player p2, int round);


/*
    metodo per gestire il loop dei turni 
*/
template <typename T, typename U>
void gameLoop(T& p1, U& p2);

#endif // MAIN_H