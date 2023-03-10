// Autore: Alessandro Rotondo (2032447)

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include "Player.h"
#include "AttackField.h"
#include "DefenceField.h"
#include "Pos.h"
#include "Ship.h"
#include "BattleShip.h"
#include "HealShip.h"
#include "Submarine.h"

Player::Player() {
    
}

Player::Player(std::string name) {
    _name = name;
}

AttackField& Player::getAttackField() {
    return _af;
}

DefenceField& Player::getDefenceField() {
    return _df;
}

void Player::printFields() {
    const int fieldSize = 12;

    const std::array<std::string, fieldSize> labels = {"A","B","C","D","E","F","G","H","I","L","M","N"};

    const std::string lineSeparator = "--+---+---+---+---+---+---+---+---+---+---+---+---+";
    const std::string numberRow     = "  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12|";

    std::vector<std::string> printableDefenceField = _df.getField();    

    std::vector<std::string> printableAttackField  = _af.getField();

    std::cout << "Campi del " << _name << std::endl;

    std::cout << lineSeparator << "\t" << lineSeparator << std::endl;
    
    for (int i = 0; i < fieldSize; i++) {
        std::cout << labels[i] << " | ";
        for (char c : printableDefenceField[i]) {
            std::cout << c << " | ";
        }
        std::cout << "\t" << labels[i] << " | ";
        for (char c : printableAttackField[i]) {
            std::cout << c << " | ";
        }
        std::cout << std::endl << lineSeparator << "\t" << lineSeparator << std::endl;
   }
    std::cout << numberRow << "\t" << numberRow << std::endl << std::endl << std::endl; 
}

void Player::action (Player& p2, std::vector<std::string>& matchActions) {
    if (_df.getShipCount()==0) {    //se non ci sono piu' navi disponibili viene passato il turno
        return;
    }
    bool actionDone;                //verifica se e' stata eseguita un azione / false azione non esguita / true azione eseguita
    do {
        actionDone = false;
        std::cout << "Turno del " << _name << "\n"
            << "Inserire le coordinate del centro della nave che deve compiere l'azione e quelle in cui eseguire l'azione,\n"
            << "oppure un comando speciale (HH HH per stampare la lista dei comandi)" << std::endl;

        std::string XYOrigin, XYTarget;
        std::cin >> XYOrigin >> XYTarget;

        //trasforma XYOrigin e XYTarget in maiuscolo
        std::transform(XYOrigin.begin(), XYOrigin.end(), XYOrigin.begin(), ::toupper);
        std::transform(XYTarget.begin(), XYTarget.end(), XYTarget.begin(), ::toupper);

        //comandi speciali
        if (XYOrigin == "AA" && XYTarget == "AA") {
            _af.clearSonar();
        } else if (XYOrigin == "BB" && XYTarget == "BB") {
            _af.clearHit();
        } else if (XYOrigin == "CC" && XYTarget == "CC") {
            _af.clearMiss();
        } else if (XYOrigin == "HH" && XYTarget == "HH") {
            std::cout<< "-AA AA: rimuove tutte le rilevazioni sonar dal campo di attacco\n"
                << "-BB BB: rimuove tutti i colpi andati a segno dal campo di attacco\n"
                << "-CC CC: rimuove tutti i colpi andati a vuoto dal campo di attacco\n"
                << "-HH HH: fornisce la lista di tutte le azioni speciali compibili\n"
                << "-NN NN: finisce immediatamente la partita in pareggio\n"
                << "-XX XX: stampa le griglie di attacco e difesa del giocatore corrente\n" << std::endl;
        } else if (XYOrigin == "NN" && XYTarget == "NN") {
            _df.nukeShips();
            _af.nukeField();

            p2.getDefenceField().nukeShips();
            p2.getAttackField().nukeField();

            matchActions.push_back(XYOrigin + " " + XYTarget);
            actionDone = true;
        } else if (XYOrigin == "XX" && XYTarget == "XX") {
            printFields();
        } else { 
            try {
                if (activateShipAction(XYOrigin, XYTarget, *this, p2)) {
                    matchActions.push_back(XYOrigin + " " + XYTarget);
                    actionDone = true;
                } else {
                    std::cout << "Inserire un comando valido\n";
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Inserire un comando valido\n";
            }
        }
    } while (!actionDone);
}

void Player::insertAllShips(std::vector<std::string>& matchActions) {
    std::string front, back, point;
    for (int i = 0; i < 3;) {       //inserimento corazzate
        std::cout << "Inserire le coordinate della prua e della poppa della " << (i + 1) << " corazzata:" << std::endl;
        std::cin >> front >> back;
        if (front == "XX" && back == "XX") {
            printFields();
        } else {
            try {
                std::shared_ptr<Ship> u = std::make_shared<BattleShip>(front, back);
                if (getDefenceField().insertShip(u)) { 
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
    }
    for (int i = 0; i < 3;) {       //inserimento navi di supporto
        std::cout << "Inserire le coordinate della prua e della poppa della " << (i + 1) << " nave di supporto:" << std::endl;
        std::cin >> front >> back;
        if (front == "XX" && back == "XX") {
            printFields();
        } else {
            try {
                std::shared_ptr<Ship> u = std::make_shared<HealShip>(front,back);
                if (getDefenceField().insertShip(u)) {
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
    }
    for (int i = 0; i < 2;) {       //inserimento sottomarino
        std::cout << "Inserire le coordinate del " << (i + 1) << " sottomarino:" << std::endl;
        std::cin >> point;
        if (point == "XX") {
            std::string token2;
            std::cin >> token2;
            if (token2 == "XX") {
                printFields();
            }
        } else {
            try {
                std::shared_ptr<Ship> u = std::make_shared<Submarine>(point);
                if (getDefenceField().insertShip(u)) {
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
}

bool activateShipAction(std::string XYOrigin, std::string XYTarget, Player& p1, Player& p2) {
    Pos p (XYOrigin);
    for (std::shared_ptr<Ship> s : p1.getDefenceField().getShipArray()) {
        if (s->getMidPos() == p) {
            if (s->action(XYTarget, p1, p2)) {
                p2.getDefenceField().removeShips();
                return true;
            }
        }
    }
    return false;
 }