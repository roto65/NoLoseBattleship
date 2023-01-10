#ifndef DUMMY_PLAYER_H
#define DUMMY_PLAYER_H

#include <string>

#include "Player.h"

class DummyPlayer : public Player{
    public:
        DummyPlayer();
        DummyPlayer(std::string name);
        
        std::string getFields();
        void action (std::string XYOrigin, std::string XYTarget, Player& p2);
    
};

#endif //DUMMY_ PLAYER_H