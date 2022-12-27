#ifndef ATTACK_FIELD_H
#define ATTACK_FIELD_H

#include <vector>
#include <string>
#include <ostream>

#include "Pos.h"

class AttackField {

    public: 
        AttackField();

        bool insertChar(char c, Pos p);
        void clearSonar();

    private:
        std::vector<std::string> _field;
};

std::ostream& operator<<(std::ostream& os, const AttackField af);

#endif // ATTACK_FIELD_H