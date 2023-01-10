// Autore: Francesco Ariani (2041835)

#ifndef REPLAY_H
#define REPLAY_H

#include <string>
#include <queue>

#include "DummyPlayer.h"

/*
    metodo per inserire le navi di un DummyPlayer
*/
void insertShip(DummyPlayer& p);

/*
    metodo che combina front() e pop() di std::queue
*/
std::string nextElem(std::queue<std::string>& queue);

#endif // REPLAY_H