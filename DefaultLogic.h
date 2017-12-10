/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#ifndef DEFAULTLOGIC_H
#define DEFAULTLOGIC_H

#include "GameLogic.h"
class DefaultLogic : public GameLogic {

public :
    /**
     * @name : GameLogic
     * @parameters : the board of the game, two players and the style of printing
     * @return : the function creates new game logic object
     **/
    DefaultLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle);
};
#endif //DEFAULTLOGIC_H