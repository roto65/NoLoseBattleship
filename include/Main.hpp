// Autore: Francesco Ariani (2041835)

#ifndef MAIN_HPP
#define MAIN_HPP

/*
    header suddiviso in due blocchi per mantenere la separazione tra interfaccia e implementazione con i template
*/

#include <iostream>
#include <vector>
#include <string>

#include "Computer.h"

template <typename T, typename U> 
void gameLoop (T& p1, U& p2, std::vector<std::string>& matchActions) {

    //scelta casuale di chi inizia a giocare per primo / 0 : inizia p1 / 1 : inizia p2
    int turn = randomNum(1);

    int turnCounter = 1;
    matchActions.push_back(std::to_string(turn));
    do {
        std::cout << "Inizio del " << turnCounter << " turno" << std::endl;
        if (turn % 2 == 0) {
            p1.action(p2, matchActions);
            std::cout << "turno eseguito P1\n";
        } else {
            p2.action(p1, matchActions);
            std::cout << "turno eseguito P2\n";
        }
        turn++;
        turnCounter++;
    } while (endGame(p1,p2,turnCounter));
}

#endif // MAIN_HPP