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
    Player _p1;
    Player _p2;
    std::string front, back, point;
    while(_p1.getDefenceField().getShipCount() < 8){
        for (int i = 0; i < 3;){
            std::cout<<"Inserire le coordinate della prua e della poppa della "<< i+1 <<" corazzata\n";
            std::cin >> front >> back;
            BattleShip _tempShip (front, back);
            if (_p1.getDefenceField().insertShip(&_tempShip)) i++;
            
        }
        for (int i = 0; i < 3;){
            std::cout<<"Inserire le coordinate della prua e della poppa della "<< i+1 <<" nave di supporto\n";
            std::cin >> front >> back;
            HealShip _tempShip (front, back);
            if (_p1.getDefenceField().insertShip(&_tempShip)) i++; 
        }
        for(int i = 0; i < 2;){
            std::cout<<"Inserire le coordinate della prua e della poppa del "<< i+1 <<" sottomarino\n";
            std::cin >> point;
            Submarine _tempShip (point);
            if (_p1.getDefenceField().insertShip(&_tempShip)) i++;
        }
    }



    return 0;
}

//ciclo: chiede poppa e prua della nave --> richiama DefenceField::insertShip() --> passa alla prossima nave