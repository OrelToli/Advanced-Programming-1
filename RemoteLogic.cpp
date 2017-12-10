//
// Created by Orel on 02/12/2017.
//

#include <sstream>
#include "RemoteLogic.h"

RemoteLogic::RemoteLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle) :
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



void RemoteLogic::remoteMakeMove(Board& gameBoard, Player& player, Print* printStyle, int* remoteMove){
    //check what is the optional moves for the current player
    //const char *cstr = remoteMove.c_str();
    if(remoteMove[0] == END_GAME_FLAG) {
        //break the while?
    } else if(remoteMove[0] == NO_MOVES_FLAG) {
        printStyle->noPossibleOptionsToCurrentPlayer(player.getType());
    } else {
        int row = remoteMove[0], col = remoteMove[1];
        makeMove(player, gameBoard, row - 1, col - 1);
    }

    printStyle->boardAfterUser(player, remoteMove[0], remoteMove[1]);
    printStyle->printBoard(gameBoard);
}



