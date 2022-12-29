#include <string>
#include <iostream>
#include <vector>

#include "Main.h"
#include "Player.h"
#include "Computer.h"
#include "BattleShip.h"
#include "HealShip.h"
#include "Submarine.h"


int main (void) { 

    Player p1;
    Player p2;
    std::string front, back, point;
    while(p1.getDefenceField().getShipCount() < 8){
        for (int i = 0; i < 3;){
            std::cout<< "Inserire le coordinate della prua e della poppa della "<< i+1 <<" corazzata:" << std::endl;
            std::cin >> front >> back;
            BattleShip* tempShip = new BattleShip(front, back);
            if (p1.getDefenceField().insertShip(tempShip)) i++;
        }
        for (int i = 0; i < 3;){
            std::cout<< "Inserire le coordinate della prua e della poppa della "<< i+1 <<" nave di supporto:" << std::endl;
            std::cin >> front >> back;
            HealShip* tempShip = new HealShip(front, back);
            if (p1.getDefenceField().insertShip(tempShip)) i++; 
        }
        for(int i = 0; i < 2;){
            std::cout<< "Inserire le coordinate della prua e della poppa del "<< i+1 <<" sottomarino:" << std::endl;
            std::cin >> point;
            Submarine* tempShip = new Submarine(point);
            if (p1.getDefenceField().insertShip(tempShip)) i++;
        }
    }

    return 0;
}

//ciclo: chiede poppa e prua della nave --> richiama DefenceField::insertShip() --> passa alla prossima nave