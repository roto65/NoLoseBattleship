// Autore: Francesco Ariani (2041835)

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

/*
    enum per poter fare lo switch sulle varie modalita' di gioco:
    pc = player vs computer
    cc = computer vs computer
    pp = player vs player
*/
enum Arguments {
    invalidArgument, pc, cc, pp
};

Arguments resolveArgument(std::string input) {
    if (input == "pc") return pc;
    if (input == "cc") return cc;
    if (input == "pp") return pp;

    return invalidArgument;
}

/*
    tiene conto delle azioni per il replay
*/
std::vector<std::string> matchActions;

int main(int argc, char* argv[]) {
    
    if (argc < 2) {                 //controllo che venga inserita la modaita' di gioco
        std::cout << "Non e' stata inserito l'argomento che specifica la modalita' di gioco!\n";
        return 0;
    }

    std::string argument = argv[1];
    
    Player p1 ("Giocatore 1"), p2 ("Giocatore 2");
    Computer c1 ("Computer 1"), c2 ("Computer 2");

    switch (resolveArgument(argument)) {
        case pc:                    //player vs computer
            insertPlayerShip(p1);
            insertComputerShip(c1);
            gameLoop(p1,c1);
            break;
        case cc:                    //computer vs computer
            insertComputerShip(c1);
            insertComputerShip(c2);
            gameLoop(c1,c2);
            break;
        case pp:                    //player vs player
            insertPlayerShip(p1);
            insertPlayerShip(p2);
            gameLoop(p1,p2);
            break;
        default:                    //viene inserita una modalita' di gioco non in elenco 
            std::cout << "Inserire:\n"
                << "- \"pc\" se si vuole eseguire una partita player vs computer\n" 
                << "- \"cc\" se si vuole eseguire una partita computer vs computer" << std::endl;
            return 0;
            break;
    }

    exportLog(matchActions);        //scrittura del log della partita
    return 0;
}
    
void insertPlayerShip(Player& p) {
    std::string front, back, point;
    for (int i = 0; i < 3;) {       //inserimento corazzate
        std::cout << "Inserire le coordinate della prua e della poppa della " << (i + 1) << " corazzata:" << std::endl;
        std::cin >> front >> back;
        try {
            std::shared_ptr<Ship> u = std::make_shared<BattleShip>(front, back);
            if (p.getDefenceField().insertShip(u)) { 
                matchActions.push_back(front + " " + back);
                i++;
            }
        } catch (const Ship::illegal_length_exception& e) {
            std::cout << e.what();
        } catch (const std::invalid_argument& e) {
            std::cout << "Inserire coordinate valide" << std::endl;
        } catch (const DefenceField::out_of_bound_exception& e) {
            std::cout << e.what();
        } catch (const DefenceField::overlap_exception& e) {
            std::cout << e.what();
        }
    }
    for (int i = 0; i < 3;) {       //inserimento navi di supporto
        std::cout << "Inserire le coordinate della prua e della poppa della " << (i + 1) << " nave di supporto:" << std::endl;
        std::cin >> front >> back;
        try {
            std::shared_ptr<Ship> u = std::make_shared<HealShip>(front,back);
            if (p.getDefenceField().insertShip(u)) {
                matchActions.push_back(front + " " + back);
                i++;
            }
        } catch(const Ship::illegal_length_exception& e) {
            std::cout << e.what();
        } catch(const std::invalid_argument& e) {
            std::cout << "Inserire coordinate valide" << std::endl;
        } catch(const DefenceField::out_of_bound_exception& e) {
            std::cout << e.what();
        } catch(const DefenceField::overlap_exception& e) {
            std::cout << e.what();
        }
    }
    for (int i = 0; i < 2;) {       //inserimento sottomarino
        std::cout << "Inserire le coordinate del " << (i + 1) << " sottomarino:" << std::endl;
        std::cin >> point;
        try {
            std::shared_ptr<Ship> u = std::make_shared<Submarine>(point);
            if (p.getDefenceField().insertShip(u)) {
                matchActions.push_back(point);
                i++;
            }
        } catch(const std::invalid_argument& e) {
            std::cout << "Inserire coordinate valide" << std::endl;
        } catch(const DefenceField::out_of_bound_exception& e) {
            std::cout << e.what();
        } catch(const DefenceField::overlap_exception& e) {
            std::cout << e.what();
        }
    }
}

void insertComputerShip(Computer& c) {
    for (int i = 0; i < 3;) {       //inserimento corazzate 
        std::vector<std::string> coordinates = c.createRandomShip(5);
        try {
            std::shared_ptr<BattleShip> u = std::make_shared<BattleShip>(coordinates[0],coordinates[1]);
            if (c.getDefenceField().insertShip(u)) {
                matchActions.push_back(coordinates[0] + " " + coordinates[1]);
                i++;
            }
        } catch (const DefenceField::out_of_bound_exception& e) {
        } catch (const DefenceField::overlap_exception& e) {
        }
    }
    for (int i = 0; i < 3;) {       //inserimento navi supporto
        std::vector<std::string> coordinates = c.createRandomShip(3);
        try {
            std::shared_ptr<HealShip> u = std::make_shared<HealShip>(coordinates[0], coordinates[1]);
            if (c.getDefenceField().insertShip(u)) {
                matchActions.push_back(coordinates[0] + " " + coordinates[1]);
                i++;
            }
        } catch (const DefenceField::out_of_bound_exception& e) {
        } catch (const DefenceField::overlap_exception& e) {
        } 
    }
    for (int i = 0; i < 2;) {       //inserimento sottomarino
        std::vector<std::string> coordinates = c.createRandomShip(1);
        try {
            std::shared_ptr<Submarine> u = std::make_shared<Submarine>(coordinates[0]);
            if (c.getDefenceField().insertShip(u)) {
                matchActions.push_back(coordinates[0]);
                i++;
            }
        } catch (const DefenceField::out_of_bound_exception& e) {
        } catch (const DefenceField::overlap_exception& e) {
        }
    }
}

bool endGame (Player p1, Player p2, int round) {
    const int MAX_TURN = 104;
    if (p1.getDefenceField().getShipCount() == 0 && p2.getDefenceField().getShipCount() == 0) {
        std::cout << "Partita terminata in pareggio" << std::endl;
        return false;
    }
    if (p1.getDefenceField().getShipCount() == 0) {
        std::cout << "Vittoria per il giocatore 2!" << std::endl;
        return false;
    }
    if (p2.getDefenceField().getShipCount() == 0) {
        std::cout << "Vittoria per il giocatore 1!" << std::endl;
        return false;
    }
    if (round > MAX_TURN) {
        std::cout << "Limite massimo di turni raggiunto: partita terminata in pareggio" << std::endl;
        return false;
    }
    return true;
}

template <typename T, typename U> 
void gameLoop (T& p1, U& p2) {

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
    } while(endGame(p1,p2,turnCounter));
}