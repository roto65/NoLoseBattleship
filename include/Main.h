#ifndef MAIN_H
#define MAIN_H

#include "Player.h"
#include "Computer.h"

void insertPlayerShip(Player p);
void insertComputerShip(Computer c);
bool endGame(Player p1, Player p2, int round);
void computerAction(Computer p1, Player p2);
void playerAction(Player p1, Player p2);

#endif // MAIN_H