#ifndef DEFENCE_FIELD_H
#define DEFENCE_FIELD_H

#include <ostream>
#include <vector>

#include "Ship.h"

class DefenceField {

    public:
        DefenceField();

        std::vector<Ship*> getShipArray(); //restituisce l'array delle navi
        int getShipCount();

        bool insertShip(Ship* s); //se va bene (fa i controlli del caso), inserisce la nave nell'array
        bool checkShip(Pos p);
        
    private:
        std::vector<Ship*> _field;
};

// getShield()[2] = 'c';

// metodo: restituisce se hai hittato o meno (bool) + 
// aggiorna se true lo shield della nave colpita (position aware)

std::ostream& operator<<(std::ostream& os, const DefenceField df);

#endif // DEFENCE_FILELD_H