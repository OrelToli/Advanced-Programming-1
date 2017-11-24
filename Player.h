/**
 * name : Limor Levi
 * id number : 308142389
**/

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Square.h"

using namespace std;

class Player {

public:
    /**
     * @name : Player
     * @parameters : type of the player
     * @return : the function creates new instance of Player
     **/
    Player(enum Type type);

    /**
     * @name : getType
     * @parameters : no parameters
     * @return : the type of the player (X or O)
     **/
    enum Type getType();

protected:
    enum Type type;
};
#endif //PLAYER_H