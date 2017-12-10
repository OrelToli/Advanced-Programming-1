/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include <iostream>
#include "Player.h"

using namespace std;

class HumanPlayer : public Player {

public :

    /**
     * Constructor
     * @param type - the type of the human player X or O
     */
    HumanPlayer(enum Type type);
};
#endif //HUMANPLAYER_H