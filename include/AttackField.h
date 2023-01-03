#ifndef ATTACK_FIELD_H
#define ATTACK_FIELD_H

#include <vector>
#include <string>

#include "Pos.h"

class AttackField {

    public: 
        AttackField();

        bool insertChar(char c, Pos p);
        void clearSonar();
        std::vector<std::string> getField();

    private:
        std::vector<std::string> _attackfield;
};

#endif // ATTACK_FIELD_H