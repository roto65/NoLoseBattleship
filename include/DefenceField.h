#ifndef DEFENCE_FIELD_H
#define DEFENCE_FIELD_H

#include <ostream>
#include <vector>

#include "Types.h" //Forward declarated classes
#include "Pos.h"


class DefenceField {

    public:
        DefenceField();

        std::vector<Ship*> getShipArray(); //restituisce l'array delle navi
        void setShipArray(std::vector<Ship*> arr);
        int getShipCount();

        bool insertShip(Ship* newShip); //se va bene (fa i controlli del caso), inserisce la nave nell'array
        std::vector<std::string> getField();
        
    private:
        std::vector<Ship*> _defenceField; 
};


#include "Ship.h"

#endif // DEFENCE_FILELD_H