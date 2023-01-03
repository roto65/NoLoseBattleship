#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Main.h"
#include "Player.h"
#include "Computer.h"
#include "BattleShip.h"
#include "HealShip.h"
#include "Submarine.h"


int main (int argc, char* argv[]) { 
    if(argc==2&&argv[1]=="pc"){
        Player p1;
        Computer p2;
        std::string front, back, point;
        while(p1.getDefenceField().getShipCount() < 8){  //ciclo: chiede poppa e prua della nave --> richiama DefenceField::insertShip() --> passa alla prossima nave
            for (int i = 0; i < 3;){
                std::cout<< "Inserire le coordinate della prua e della poppa della "<< i+1 <<" corazzata:" << std::endl;
                std::cin >> front >> back;
                BattleShip* tempShip = new BattleShip(front, back);
                std::unique_ptr<BattleShip> u (new BattleShip(front, back));
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
        
    }
    else if(argc==2&&argv[1]=="cc"){

    }
    else{

    }

    return 0;
}

