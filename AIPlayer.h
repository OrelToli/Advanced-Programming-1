//
// Created by Orel on 18/11/2017.
//

#include "Player.h"

#ifndef EX3_AIPLAYER_H
#define EX3_AIPLAYER_H


using namespace std;

class AIPlayer : public Player {

public :

    /**
     * COnstructor
     * @param type - the type of the player, X or O
     */
    AIPlayer(enum Type type);
};

#endif //EX3_AIPLAYER_H
