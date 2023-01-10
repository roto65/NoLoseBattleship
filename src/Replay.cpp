// Autore: Francesco Ariani (2041835)

#include <string>
#include <iostream>
#include <queue>
#include <memory>
#include <thread>
#include <chrono> 

#include "Replay.h"
#include "FilesIO.h"
#include "DummyPlayer.h"
#include "Ship.h"
#include "BattleShip.h"
#include "HealShip.h"
#include "Submarine.h"

std::queue<std::string> Vercingetorige;

constexpr int sleepTime = 1;

/*
    enum per poter fare lo switch sulle varie modalita' di replay:
    v = stampa a video
    f = stampa su file
*/
enum Arguments {
    invalidArgument, v, f
};

Arguments resolveArgument (std::string input) {
    if (input == "v") return v;
    if (input == "f") return f;

    return invalidArgument;
}

int main (int argc, char* argv[]) {

    if (argc < 2 ) {
        std::cout << "Non è stato inserito l'argomento che specifica la modalita' di replay!" << std::endl;
        return 0;
    }
    std::string argument = argv[1];

    if (argc < 3) {
        std::cout << "Inserire anche il nome del log di cui si vuole vedere il replay" << std::endl;
        return 0;
    }
    std::string inputPath = argv[2];

    if (argc < 4 && argument == "f") {
        std::cout << "Inserire anche il nome del file in cui si vuole salvare il replay" << std::endl;
        return 0;
    }
    std::string outputPath, XYTarget, XYOrigin;

    DummyPlayer p1 ("Giocatore 1"), p2 ("Giocatore 2");
    Vercingetorige = importLog(inputPath);

    insertShip(p1);
    insertShip(p2);
    
    std::vector<std::string> outputVector;
    
    int startPlayer = std::stoi(Vercingetorige.front());
    Vercingetorige.pop();

    std::string startPlayerLine = "Inizia il giocatore " + std::to_string(startPlayer + 1) + "\n";

    switch (resolveArgument(argument)) {
        case v:
            p1.printFields();

            std::this_thread::sleep_for(std::chrono::seconds(sleepTime));

            p2.printFields();

            std::this_thread::sleep_for(std::chrono::seconds(sleepTime));

            std::cout << startPlayerLine << std::endl;

            while (!Vercingetorige.empty()) {
                XYOrigin = nextElem(Vercingetorige);
                XYTarget = nextElem(Vercingetorige);

                if (startPlayer % 2 == 0) {
                    p1.action(XYOrigin, XYTarget, p2);
                    p1.printFields();
                } else {
                    p2.action(XYOrigin, XYTarget, p1);
                    p2.printFields();
                }
                std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
                startPlayer++;
            }
            break;
        case f:
            outputVector.push_back(p1.getFields());
            outputVector.push_back(p2.getFields());
            outputVector.push_back(startPlayerLine);

            while(!Vercingetorige.empty()) {
                XYOrigin = nextElem(Vercingetorige);
                XYTarget = nextElem(Vercingetorige);

                if (startPlayer % 2 == 0) {
                    p1.action(XYOrigin, XYTarget, p2);
                    outputVector.push_back(p1.getFields());
                } else {
                    p2.action(XYOrigin, XYTarget, p1);
                    outputVector.push_back(p2.getFields());
                }
                startPlayer++;                  
            }
            outputPath = argv[3];
            exportLog(outputVector, outputPath);
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
    for (int i = 0; i < 3; i++) {
        front = nextElem(Vercingetorige);
        back = nextElem(Vercingetorige);
        std::shared_ptr<Ship> u = std::make_shared<BattleShip>(front, back);
        p.getDefenceField().insertShip(u);
    }
    for (int i = 0; i < 3; i++) {
        front = nextElem(Vercingetorige);
        back = nextElem(Vercingetorige);
        std::shared_ptr<Ship> u = std::make_shared<HealShip>(front,back);
        p.getDefenceField().insertShip(u);
    }
    for (int i = 0; i < 2; i++) {
        point=nextElem(Vercingetorige);
        std::shared_ptr<Ship> u = std::make_shared<Submarine>(point);
        p.getDefenceField().insertShip(u);
    }
}

std::string nextElem(std::queue<std::string>& queue) {
    std::string elem = queue.front();
    queue.pop();
    return elem;
}