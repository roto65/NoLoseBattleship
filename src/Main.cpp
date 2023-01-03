#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

#include "Main.h"
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

std::vector<std::string> _matchActions;

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
        break;
    case cc:
        insertComputerShip(c1);
        insertComputerShip(c2);
        break;
    default:
        std::cout << "Inserire \"pc\" se si vuole eseguire una partita player vs computer o inserire \"cc\" se si vuole eseguire una partita computer vs computer";
        break;
    return 0;
    }
}
    
void insertPlayerShip (Player p1) {
    std::string front, back, point;
    for (int i = 0; i < 3;){
        std::cout<< "Inserire le coordinate della prua e della poppa della "<< i+1 <<" corazzata:" << std::endl;
        std::cin >> front >> back;
        try{
            std::shared_ptr<Ship> u = std::make_shared<BattleShip>(front, back);
            if (p1.getDefenceField().insertShip(u)) i++;
        }
        catch(const Ship::illegal_length& e){
            std::cout << e.what();
        }
        catch(const std::invalid_argument& e){
            std::cout<<"Inserire coordinate valide\n";
        }
    }
    for (int i = 0; i < 3;){
        std::cout<< "Inserire le coordinate della prua e della poppa della "<< i+1 <<" nave di supporto:" << std::endl;
        std::cin >> front >> back;
        try{
            std::shared_ptr<Ship> u = std::make_shared<HealShip>(front,back);
            if (p1.getDefenceField().insertShip(u)) i++;
        }
        catch(const Ship::illegal_length& e) {
            std::cout << e.what();
        }
        catch(const std::invalid_argument& e){
            std::cout<<"Inserire coordinate valide\n";
        }
    }
    for(int i = 0; i < 2;){
        std::cout<< "Inserire le coordinate del "<< i+1 <<" sottomarino:" << std::endl;
        std::cin >> point;
        try{
            std::cout<<"dentro try\n";
            std::shared_ptr<Ship> u = std::make_shared<Submarine>(point);
            std::cout<<"dopo costruttore\n";
            if (p1.getDefenceField().insertShip(u)) i++;
        }
        catch(const std::invalid_argument& e){
            std::cout<<"Inserire coordinate valide\n";
        }
    }
}

void insertComputerShip(Computer c){
    for (int i = 0; i < 3;){
        std::vector<std::string> coordinates = c.createRandomShip(5);
        std::shared_ptr<BattleShip> u = std::make_shared<BattleShip>(coordinates[0],coordinates[1]);
        if (c.getDefenceField().insertShip(u)) i++;
    }
    for (int i = 0; i < 3;){
        std::vector<std::string> coordinates = c.createRandomShip(3);
        std::shared_ptr<HealShip> u = std::make_shared<HealShip>(coordinates[0], coordinates[1]);
        if (c.getDefenceField().insertShip(u)) i++; 
    }
    for(int i = 0; i < 2;){
        std::vector<std::string> coordinates = c.createRandomShip(1);
        std::shared_ptr<Submarine> u = std::make_shared<Submarine>(coordinates[0]);
        if (c.getDefenceField().insertShip(u)) i++;
    }
}

bool endGame (Player p1, Player p2,int round){
    if(p1.getDefenceField().getShipCount()==0){
        std::cout << "Vittoria per il giocatore 2!\n";
        return true;
    }
    if(p2.getDefenceField().getShipCount()==0){
        std::cout << "Vittoria per il giocatore 1!\n";
        return true;
    }
    if(round>=104){
        std::cout << "Limite massimo di turni raggiunto: partita terminata in pareggio\n";
        return true;
    }
    return false;
}

void computerAction (Computer p1, Player p2){
    bool actionDone;    //verifica se è stata eseguita un azione / false azione non esguita /true azione eseguita
    do{
        actionDone=false;
        std::string XYOrigin = p1.selectRandomShip(p1.getDefenceField().getShipArray());
        std::string XYTarget = p1.randomAction();
        for(std::shared_ptr<Ship> s : p1.getDefenceField().getShipArray()){
            if(s->getMidPos()==Pos(XYOrigin)){
                if(s->action(XYTarget,p1,p2)){
                    p2.getDefenceField().removeShips();
                    actionDone=true;
                };
            }
        }
    }while(!actionDone);
}

void playerAction (Player p1, Player p2){
    bool actionDone;    //verifica se è stata eseguita un azione / false azione non esguita / true azione eseguita
    do{
        actionDone=false;
        std::cout<<"Inserire le coordinate del centro della nave che deve compiere l'azione e quelle in cui eseguire l'azione, oppure un comando speciale (HH HH per tutta la lista dei comandi)\n";
        std::string XYOrigin, XYTarget;
        std::cin>>XYOrigin>>XYTarget;
        if(XYOrigin=="AA" && XYTarget=="AA"){
            p1.getAttackField().clearSonar();
        }
        else if(XYOrigin=="BB" && XYTarget=="BB"){
            p1.getAttackField().clearHit();
        }
        else if(XYOrigin=="CC" && XYTarget=="CC"){
            p1.getAttackField().clearMiss();
        }
        else if(XYOrigin=="HH" && XYTarget=="HH"){
            std::cout<<"\n-AA AA: rimuove tutte le rilevazioni sonar dal campo di attacco";
            std::cout<<"\n-BB BB: rimuove tutti i colpi andati a segno dal campo di attacco";
            std::cout<<"\n-CC CC: rimuove tutti i colpi andati a vuoto dal campo di attacco";
            std::cout<<"\n-HH HH: fornisce la lista di tutte le azioni speciali compibili";
            std::cout<<"\n-XX XX: stampa le griglie di attacco e difesa del giocatore corrente";
        }
        else if(XYOrigin=="XX" && XYTarget=="XX"){
            p1.printFields();
        }
        else{ 
            try{
                for(std::shared_ptr<Ship> s : p1.getDefenceField().getShipArray()){
                    if(s->getMidPos()==Pos(XYOrigin)){
                        if(s->action(XYTarget,p1,p2)){
                            p2.getDefenceField().removeShips();
                            actionDone=true;
                        }
                    }
                }
            } catch(const std::invalid_argument& e){
                // TODO
            }

        }
    }while(!actionDone);
}
