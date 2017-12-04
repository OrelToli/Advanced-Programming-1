//
// Created by orel on 30/11/17.
//

#ifndef EX3NEW_REMOTEPLAYER_H
#define EX3NEW_REMOTEPLAYER_H


#include "Player.h"

class RemotePlayer : public Player {

public :

    /**
     * Constructor
     * @param type - the type of the player, X or O
     */
    RemotePlayer(enum Type type);
};


#endif //EX3NEW_REMOTEPLAYER_H
