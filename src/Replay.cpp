#include <string>
#include <iostream>
#include <queue>
#include <thread>
#include <chrono> // per lo sleep

#include "Replay.h"
#include "FilesIO.h"
#include "DummyPlayer.h"
#include "Ship.h"
#include "BattleShip.h"
#include "HealShip.h"
#include "Submarine.h"

std::queue<std::string> match_actions;

enum Arguments {
    invalidArgument, v, f
};

Arguments resolveArgument (std::string input) {
    if (input == "v") return v;
    if (input == "f") return f;

    return invalidArgument;
}

// 0 comando ./replay
// 1 v f
// 2 input path
// 3 output path

int main (int argc, char* argv[]) {
    if (argc < 2 ) {
        std::cout<<"Non è stato inserito l'argomento che specifica la modalita' di replay!\n";
        return 0;
    }
    std::string argument = argv[1];

    if (argc < 3) {
        std::cout<<"Inserire anche il nome del log di cui si vuole vedere il replay\n";
        return 0;
    }
    std::string inputPath = argv[2];

    if (argc < 4 && argument == "f") {
        std::cout<<"Inserire anche il nome del file in cui si vuole salvare il replay\n";
        return 0;
    }
    std::string outputPath;

    DummyPlayer p1,p2;
    match_actions = importLog(inputPath);
    insertShip(p1);
    insertShip(p2);
    std::vector<std::string> Vercingetorige;

    switch (resolveArgument(argument)) {
    case v:
        while(!match_actions.empty()){
            //p1.action(match_actions.); da riscrivere action
            p1.printFields();
            std::cout<<std::endl<<std::endl; // a capi per staccare
            p2.printFields();
            std::cout<<std::endl<<std::endl; // a capi per staccare
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        break;
    case f: //riscrivere action
        while(!match_actions.empty()){
            Vercingetorige.push_back(p1.getFields());
            Vercingetorige.push_back(p2.getFields());       
        }
        outputPath = argv[3];
        exportLog(Vercingetorige, outputPath);
        break;
    
    default:
        std::cout << "Inserire:\n"
            << "- \"v\" se si vuole vedere il replay di una partita a terminale\n" 
            << "- \"f\" se si vuole vedere il replay di una partita in un file a parte" << std::endl;
        return 0;
        break;
    }
    return 0;
}

void insertShip(DummyPlayer& p) {
    std::string front, back, point;
    for (int i = 0; i < 3;) {
            front=match_actions.front();
            match_actions.pop();
            back=match_actions.front();
            match_actions.pop();
            std::shared_ptr<Ship> u = std::make_shared<BattleShip>(front, back);
            p.getDefenceField().insertShip(u);
    }
    for (int i = 0; i < 3;) {
            front=match_actions.front();
            match_actions.pop();
            back=match_actions.front();
            match_actions.pop();
            std::shared_ptr<Ship> u = std::make_shared<HealShip>(front,back);
            p.getDefenceField().insertShip(u);
    }
    for(int i = 0; i < 2;i++) {
            point=match_actions.front();
            match_actions.pop();
            std::shared_ptr<Ship> u = std::make_shared<Submarine>(point);
            p.getDefenceField().insertShip(u);
    }
}