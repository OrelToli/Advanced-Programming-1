/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#include "Player.h"

#ifndef EX3_AIPLAYER_H
#define EX3_AIPLAYER_H


using namespace std;

class AIPlayer : public Player {

public :

    /**
     * Constructor
     * @param type - the type of the player, X or O
     */
    AIPlayer(enum Type type);
};

#endif //EX3_AIPLAYER_H
