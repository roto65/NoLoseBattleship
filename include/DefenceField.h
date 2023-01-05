#ifndef DEFENCE_FIELD_H
#define DEFENCE_FIELD_H

#include <ostream>
#include <vector>
#include <exception>
#include <memory>

#include "Types.h" //Forward declarated classes
#include "Pos.h"


class DefenceField {

    public:
        DefenceField();

        std::vector<std::shared_ptr<Ship>> getShipArray(); //restituisce l'array delle navi
        void setShipArray(std::vector<std::shared_ptr<Ship>> arr);
        int getShipCount();

        bool insertShip(std::shared_ptr<Ship> newShip); //se va bene (fa i controlli del caso), inserisce la nave nell'array
        bool removeShips();
        void nukeShips();
        std::vector<std::string> getField();

        class out_of_bound : public std::exception {
            public:
                const char* what() const noexcept {
                    return "Tentativo di inserire nave fuori dalla griglia\n";
                }
        };

        class overlap : public std::exception {
            public:
                const char* what() const noexcept {
                    return "Tentativo di inserire nave in posizione occupata da un'altra nave\n";
                }
        };
        
    private:
        std::vector<std::shared_ptr<Ship>> _defenceField; 
};


#include "Ship.h"

#endif // DEFENCE_FILELD_H