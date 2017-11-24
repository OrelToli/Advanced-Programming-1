/**
 * name : Limor Levi
 * id number : 308142389
**/
#include "GameLogic.h"

using namespace std;

GameLogic:: GameLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle) :
        board(board), xPlayer(xPlayer), oPlayer(oPlayer) , printStyle(printStyle)
{
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


pair<int,int> GameLogic::valueOfDirection(Direction d) {
    switch(d)
    {
        case RIGHT : return make_pair(0, 1);
        case RIGHTDOWN : return make_pair(1, 1);
        case DOWN : return make_pair(1, 0);
        case LEFTDOWN : return make_pair(1,-1);
        case LEFT : return make_pair(0,-1);
        case LEFTUP : return make_pair(-1,-1);
        case UP : return make_pair(-1,0);
        case RIGHTUP : return make_pair(-1,1);
    }
};


bool GameLogic::isAnotherSquareOfPlayerInDirection(char player, Direction direction, int i, int j){
    int dx = valueOfDirection(direction).first, dy = valueOfDirection(direction).second,
            currentX = i + dx, currentY = j + valueOfDirection(direction).second;
    while(this->board->isSquareInBoard(currentX,currentY)){
        if(this->board->getSquareType(currentX,currentY) == player)
            return true;
        else{
            currentX = currentX + dx;
            currentY = currentY + dy;
        }
    }
    return false;
}
