#include <string>

#include "Submarine.h"
#include "Player.h"

Submarine::Submarine () {

}

Submarine::Submarine (std::string front, std::string back) {
    
}

bool Submarine::action(std::string input, Player p1, Player p2) {
    return true;
}

void Submarine::resetShield() {
    _shield = {'S'};
}