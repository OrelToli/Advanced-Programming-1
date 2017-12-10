/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */


#include "DefaultLogic.h"


DefaultLogic::DefaultLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle) :
        GameLogic(board, xPlayer, oPlayer, printStyle) {
    //initialization the array of directions
    this->directions[0] = RIGHT;
    this->directions[1] = RIGHTDOWN;
    this->directions[2] = DOWN;
    this->directions[3] = LEFTDOWN;
    this->directions[4] = LEFT;
    this->directions[5] = LEFTUP;
    this->directions[6] = UP;
    this->directions[7] = RIGHTUP;
    this->board = board;
    this->xPlayer = xPlayer;
    this->oPlayer = oPlayer;
    this->printStyle = printStyle;
}





