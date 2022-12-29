#include <iostream>

#include "Player.h"
#include "AttackField.h"
#include "DefenceField.h"

Player::Player() {
    
}

AttackField Player::getAttackField() {
    return _af;
}

DefenceField& Player::getDefenceField() {
    return _df;
}

void Player::printFields() {
   
   std::vector<char> labels = {'A','B','C','D','E','F','G','H','I','L','M','N'};
    std::string line = "vaffanculolo";

    std::cout << "--+---+---+---+---+---+---+---+---+---+---+---+---+" << std::endl;
    for (int i = 0; i < 12; i++) {
        std::cout << labels[i];
        for (char c : line) {
            std::cout << " | " << c;
        }
        std::cout << " |" << std::endl;
        std::cout << "--+---+---+---+---+---+---+---+---+---+---+---+---+" << std::endl;
    }
    std::cout << "  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12|" << std::endl;
}