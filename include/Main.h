#ifndef MAIN_H
#define MAIN_H

#include "Player.h"
#include "Computer.h"



void insertPlayerShip(Player& p);
void insertComputerShip(Computer& c);
bool endGame(Player p1, Player p2, int round);

template <typename T>
void gameLoop(T& p1, Computer& p2);

#endif // MAIN_H