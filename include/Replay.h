#ifndef REPLAY_H
#define REPLAY_H

#include <string>
#include <queue>

#include "DummyPlayer.h"

/*
    classe per la gestione dei replay
*/

/*
    metodo per inserire le navi di un dummy player 
*/
void insertShip(DummyPlayer& p);

/*
    metodo che combina front() e pop() di std::queue
*/
std::string nextElem(std::queue<std::string>& queue);

#endif // REPLAY_H