#include <array>
#include <vector>

#include "DefenceField.h"
#include "Ship.h"

constexpr std::array<char, 12> labels = {'A','B','C','D','E','F','G','H','I','L','M','N'};

DefenceField::DefenceField() {

}

std::vector<Ship*> DefenceField::getShipArray() {
    return _field;
}

int DefenceField::getShipCount() {
    return _field.size();
}

bool DefenceField::insertShip(Ship* s) {
    return false;
}