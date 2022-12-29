#include <array>

#include "AttackField.h"
#include "Pos.h"

constexpr std::array<char, 12> labels  {'A','B','C','D','E','F','G','H','I','L','M','N'};

AttackField::AttackField() {

}

bool AttackField::insertChar(char c, Pos p) {
    return true;
}