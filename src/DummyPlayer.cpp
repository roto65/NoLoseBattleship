#include <array>
#include <vector>
#include <string>

#include "DummyPlayer.h"

DummyPlayer::DummyPlayer() {

}

DummyPlayer::DummyPlayer(std::string name) {
    _name = name;
}

std::string DummyPlayer::getFields() {
    std::string output ="";
    const int fieldSize = 12;

    const std::array<std::string, fieldSize> labels = {"A","B","C","D","E","F","G","H","I","L","M","N"};

    const std::string lineSeparator = "--+---+---+---+---+---+---+---+---+---+---+---+---+";
    const std::string numberRow     = "  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12|";

    std::vector<std::string> printableDefenceField = _df.getField();    

    std::vector<std::string> printableAttackField  = _af.getField();
    
    output += "Campi del " + _name + "\n";
    
    output += lineSeparator + "    " + lineSeparator + "\n";
    for (int i = 0; i < fieldSize; i++) {
        output += labels[i] + " | ";
        for (char c : printableDefenceField[i]) {
            output += c;
            output +=  " | ";
        }
        output += "    " + labels[i] + " | ";
        for (char c : printableAttackField[i]) {
            output += c;
            output +=  " | ";
        }
        output += "\n" + lineSeparator + "    " + lineSeparator + "\n";
    }
    output += numberRow + "    " + numberRow + "\n";
    return output;
}


void DummyPlayer::action(std::string XYOrigin, std::string XYTarget, Player& p2) {
    if (XYOrigin == "NN" && XYTarget == "NN") {
        _df.nukeShips();
        p2.getDefenceField().nukeShips();
    } else {
        activateShipAction(XYOrigin, XYTarget, *this, p2);
    }
}