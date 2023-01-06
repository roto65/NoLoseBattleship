#include <array>
#include <vector>
#include "DummyPlayer.h"

DummyPlayer::DummyPlayer() {

}

std::string DummyPlayer::getFields(){
    std::string output ="";
    const int fieldSize = 12;

    const std::array<std::string, fieldSize> labels = {"A","B","C","D","E","F","G","H","I","L","M","N"};

    const std::string lineSeparator = "--+---+---+---+---+---+---+---+---+---+---+---+---+";
    const std::string numberRow     = "  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12|";

    std::vector<std::string> printableDefenceField = _df.getField();    

    std::vector<std::string> printableAttackField  = _af.getField();
    output += lineSeparator + "    " + lineSeparator + "\n";
    for(int i = 0; i < fieldSize; i++){
        output += labels[i]+" | ";
        for(char c : printableDefenceField[i]){
            output += c + " | ";
        }
        output += "    " + labels[i] + " | ";
        for (char c : printableAttackField[i]) {
            output += c + " | ";
        }
        output += "\n" + lineSeparator + "    " + lineSeparator + "\n";
    }
    output += numberRow + "    " + numberRow + "\n";
    return output;
}