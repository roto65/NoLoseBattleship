#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

#include "Main.h"
#include "FilesIO.h"
#include "Player.h"
#include "Computer.h"
#include "Ship.h"
#include "BattleShip.h"
#include "HealShip.h"
#include "Submarine.h"

enum Arguments {
    invalidArgument, pc, cc
};

Arguments resolveArgument(std::string input) {
    if (input == "pc") return pc;
    if (input == "cc") return cc;

    return invalidArgument;
}

std::vector<std::string> _matchActions; //tiene conto delle azioni per il replay

int main (int argc, char* argv[]) {
    
    if (argc < 2) {
        std::cout << "Non e' stata inserito l'argomento che specifica la modalita' di gioco!\n"; // TODO
        return 0;
    }

    std::string argument = argv[1];
    
    Player p1;
    Computer c1, c2;

    switch (resolveArgument(argument)) {
    case pc:
        insertPlayerShip(p1);
        insertComputerShip(c1);
        gameLoop(p1,c1);
        break;
    case cc:
        insertComputerShip(c1);
        insertComputerShip(c2);
        gameLoop(c1,c2);
        break;
    default:
        std::cout << "Inserire \"pc\" se si vuole eseguire una partita player vs computer o inserire \"cc\" se si vuole eseguire una partita computer vs computer";
        return 0; //oppure a1 a5 b1 b5 c1 c5 d1 d3 e1 e3 f1 f3 h5 n3 XX XXaltro input
        break;
    }

    exportLog(_matchActions);

    return 0;
}
    
void insertPlayerShip (Player& p1) {
    std::string front, back, point;
    for (int i = 0; i < 3;){
        std::cout<< "Inserire le coordinate della prua e della poppa della "<< i+1 <<" corazzata:" << std::endl;
        std::cin >> front >> back;
        try{
            std::shared_ptr<Ship> u = std::make_shared<BattleShip>(front, back);
            if (p1.getDefenceField().insertShip(u)){ 
                _matchActions.push_back(front+" "+back);
                i++;
            }
        }
        catch(const Ship::illegal_length& e){
            std::cout << e.what();
        }
        catch(const std::invalid_argument& e){
            std::cout<<"Inserire coordinate valide\n";
        }
        catch(const DefenceField::out_of_bound& e){
            std::cout << e.what();
        }
        catch(const DefenceField::overlap& e){
            std::cout << e.what();
        }
    }
    for (int i = 0; i < 3;){
        std::cout<< "Inserire le coordinate della prua e della poppa della "<< i+1 <<" nave di supporto:" << std::endl;
        std::cin >> front >> back;
        try{
            std::shared_ptr<Ship> u = std::make_shared<HealShip>(front,back);
            if (p1.getDefenceField().insertShip(u)){
                _matchActions.push_back(front+" "+back);
                i++;
            }
        }
        catch(const Ship::illegal_length& e) {
            std::cout << e.what();
        }
        catch(const std::invalid_argument& e){
            std::cout<<"Inserire coordinate valide\n";
        }
        catch(const DefenceField::out_of_bound& e){
            std::cout << e.what();
        }
        catch(const DefenceField::overlap& e){
            std::cout << e.what();
        }
    }
    for(int i = 0; i < 2;){
        std::cout<< "Inserire le coordinate del "<< i+1 <<" sottomarino:" << std::endl;
        std::cin >> point;
        try{
            std::shared_ptr<Ship> u = std::make_shared<Submarine>(point);
            if (p1.getDefenceField().insertShip(u)){
                _matchActions.push_back(point);
                i++;
            }
        }
        catch(const std::invalid_argument& e){
            std::cout<<"Inserire coordinate valide\n";
        }
        catch(const DefenceField::out_of_bound& e){
            std::cout << e.what();
        }
        catch(const DefenceField::overlap& e){
            std::cout << e.what();
        }
    }
    //std::cout << p1.getDefenceField().getShipCount();
}

void insertComputerShip(Computer& c){
    for (int i = 0; i < 3;){
        std::vector<std::string> coordinates = c.createRandomShip(5);
        try{
            std::shared_ptr<BattleShip> u = std::make_shared<BattleShip>(coordinates[0],coordinates[1]);
            if (c.getDefenceField().insertShip(u)){
                _matchActions.push_back(coordinates[0]+" "+coordinates[1]);
                i++;
            }
        }
        catch(const DefenceField::out_of_bound& e){
        }
        catch(const DefenceField::overlap& e){
        }
    }
    for (int i = 0; i < 3;){
        std::vector<std::string> coordinates = c.createRandomShip(3);
        try{
            std::shared_ptr<HealShip> u = std::make_shared<HealShip>(coordinates[0], coordinates[1]);
            if (c.getDefenceField().insertShip(u)){
                _matchActions.push_back(coordinates[0]+" "+coordinates[1]);
                i++;
            }
        }
        catch(const DefenceField::out_of_bound& e){
        }
        catch(const DefenceField::overlap& e){
        } 
    }
    for(int i = 0; i < 2;){
        std::vector<std::string> coordinates = c.createRandomShip(1);
        try{
            std::shared_ptr<Submarine> u = std::make_shared<Submarine>(coordinates[0]);
            if (c.getDefenceField().insertShip(u)){
                _matchActions.push_back(coordinates[0]);
                i++;
            }
        }
        catch(const DefenceField::out_of_bound& e){
        }
        catch(const DefenceField::overlap& e){
        }
    }
}

bool endGame (Player p1, Player p2,int round){
    const int MAX_TURN = 104;
    if(p1.getDefenceField().getShipCount()==0 && p2.getDefenceField().getShipCount()==0){
        std::cout <<"Partita terminata in pareggio\n";
        return false;
    }
    if(p1.getDefenceField().getShipCount()==0){
        std::cout << "Vittoria per il giocatore 2!\n";
        return false;
    }
    if(p2.getDefenceField().getShipCount()==0){
        std::cout << "Vittoria per il giocatore 1!\n";
        return false;
    }
    if(round>=MAX_TURN){
        std::cout << "Limite massimo di turni raggiunto: partita terminata in pareggio\n";
        return false;
    }
    return true;
}

template <typename T> 
void gameLoop (T& p1, Computer& p2){
    int turn = randomNum(1); //da mettere il random
    do{
        if(turn % 2 != 0){
            p1.action(p2, _matchActions);  //spostare playerAction e computerAction nelle rispettive classi e chiamarli action(Computer p)
            std::cout<<"turno eseguito p1\n";
        }else{
            p2.action(p1, _matchActions);
            std::cout<<"turno eseguito p2\n";
        }
        turn++;
    }while(endGame(p1,p2,turn));
}