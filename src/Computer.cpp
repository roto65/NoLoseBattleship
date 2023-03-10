// Autore: Alessandro Rotondo (2032447)

#include <vector>
#include <string>
#include <random>
#include <memory>

#include "Computer.h"
#include "Pos.h"
#include "Ship.h"
#include "BattleShip.h"
#include "HealShip.h"
#include "Submarine.h"

constexpr int FIELD_SIZE = 11;

Computer::Computer() {

}

Computer::Computer(std::string name) {
    _name = name;
}

std::vector<std::string> Computer::createRandomShip(int dim) {
    Pos front = getRandomPosition();
    std::vector<Pos> direction {Pos(0,dim-1), Pos(0,-1*(dim-1)), Pos(dim-1,0), Pos(-1*(dim-1),0)};
    int i = randomNum(direction.size() - 1,0);
    Pos back = front + direction[i];
    return std::vector<std::string> {front.toString(),back.toString()};
}

std::string Computer::selectRandomShip(std::vector<std::shared_ptr<Ship>> s) {
    int i = randomNum(s.size() - 1, 0);
    return s[i]->getMidPos().toString();
}

void Computer::action(Player& p2, std::vector<std::string>& matchActions) {
    if (_df.getShipCount() == 0) {      //se non ci sono piu' navi disponibili viene passato il turno
        return;
    }
    bool actionDone;                    //verifica se e' stata eseguita un azione / false azione non esguita /true azione eseguita
    do {
        actionDone = false;
        std::string XYOrigin = selectRandomShip(_df.getShipArray());
        std::string XYTarget = getRandomPosition().toString();
        if (activateShipAction(XYOrigin, XYTarget, *this, p2)) {
            matchActions.push_back(XYOrigin + " " + XYTarget);
            actionDone = true;
        }
    } while (!actionDone);
}

void Computer::insertAllShips(std::vector<std::string>& matchActions) {
    for (int i = 0; i < 3;) {       //inserimento corazzate 
        std::vector<std::string> coordinates = createRandomShip(5);
        try {
            std::shared_ptr<BattleShip> u = std::make_shared<BattleShip>(coordinates[0],coordinates[1]);
            if (getDefenceField().insertShip(u)) {
                matchActions.push_back(coordinates[0] + " " + coordinates[1]);
                i++;
            }
        } catch (const DefenceField::out_of_bound_exception& e) {
        } catch (const DefenceField::overlap_exception& e) {
        }
    }
    for (int i = 0; i < 3;) {       //inserimento navi supporto
        std::vector<std::string> coordinates = createRandomShip(3);
        try {
            std::shared_ptr<HealShip> u = std::make_shared<HealShip>(coordinates[0], coordinates[1]);
            if (getDefenceField().insertShip(u)) {
                matchActions.push_back(coordinates[0] + " " + coordinates[1]);
                i++;
            }
        } catch (const DefenceField::out_of_bound_exception& e) {
        } catch (const DefenceField::overlap_exception& e) {
        } 
    }
    for (int i = 0; i < 2;) {       //inserimento sottomarino
        std::vector<std::string> coordinates = createRandomShip(1);
        try {
            std::shared_ptr<Submarine> u = std::make_shared<Submarine>(coordinates[0]);
            if (getDefenceField().insertShip(u)) {
                matchActions.push_back(coordinates[0]);
                i++;
            }
        } catch (const DefenceField::out_of_bound_exception& e) {
        } catch (const DefenceField::overlap_exception& e) {
        }
    }
}

Pos getRandomPosition() {
    Pos randPos (randomNum(FIELD_SIZE,0),randomNum(FIELD_SIZE,0));
    return randPos;
}

int randomNum(int max, int min) {
    std::random_device rd;
    std::mt19937 mt (rd());             // Mersenne Twister 19937 random number generator
    std::uniform_int_distribution<int> dist (min, max);

    return dist(rd);
}
