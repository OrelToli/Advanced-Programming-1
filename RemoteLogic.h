//
// Created by Orel on 02/12/2017.
//

#ifndef EX3NEW_REMOTELOGIC_H
#define EX3NEW_REMOTELOGIC_H

#include "GameLogic.h"

class RemoteLogic  : public GameLogic {
public:

    RemoteLogic(Board *board, Player &xPlayer, Player &oPlayer, Print *printStyle);

    void remoteMakeMove(Board &gameBoard, Player &player, Print *printStyle, int *remoteMove);
};


#endif //EX3NEW_REMOTELOGIC_H
