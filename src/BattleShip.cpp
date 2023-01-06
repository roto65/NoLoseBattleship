#include <string>
#include <memory>

#include "BattleShip.h"
#include "Pos.h"

BattleShip::BattleShip(){

}

BattleShip::BattleShip(std::string front, std::string back){
    Pos F (front);      //conversione da stringa a Pos
    Pos B (back);    
    if (distance(F, B) != 4) {
        throw illegal_length_exception();
    }
    //assegnazione del facing della nave in base alle coordiante inserite
    if(F.x == B.x) {
        _facing = 1;
    } else {
        _facing = 0;
    }
    _midPos.x = (F.x + B.x) / 2;
    _midPos.y = (F.y + B.y) / 2;
    _length = 5;
    _upperChar = 'C';
    _lowerChar = 'c';
    _shield = std::vector<char> (_length, _upperChar);
}

bool BattleShip::action(std::string XYTarget, Player& p1, Player& p2){
    Pos I (XYTarget);
    //controllo che le coordiante XYTarget siano all'interno della griglia di gioco
    if((I.x > 12 || I.x < 0 || I.y < 0 || I.y > 12)){
        return false; //coordinate non valide
    }
    else{
        //scorre le navi nel vettore
        for(std::shared_ptr<Ship> s : p2.getDefenceField().getShipArray()){
            std::vector<Pos> segments = getSegments(s);
            int i = 0;
            //scorre le posizioni occupate da ogni singola nave
            for(Pos p : segments){
                if(p==I){
                    p1.getAttackField().insertChar('X', I); //aggiornamento campo di attacco se colpita
                    s->getShield()[i] = s->getLowerChar();  //aggiornamento shield della nave colpita
                    return true;
                }
                i++;
            }
        }
        p1.getAttackField().insertChar('O', I);             //aggiornamento campo di attacco se mancato
        return true;
    }
    
}
