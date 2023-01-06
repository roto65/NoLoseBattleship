#ifndef DUMMY_PLAYER_H
#define DUMMY_PLAYER_H

#include "Player.h"

class DummyPlayer : public Player{
    public:
        DummyPlayer();
        
        std::string getFields();
    
};

#endif //DUMMY_ PLAYER_H