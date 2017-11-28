//
// Created by limor on 28/11/17.
//

#ifndef DEFAULTLOGICTESTS_H
#define DEFAULTLOGICTESTS_H


#include <gtest/gtest.h>
#include "../src/Board.h"
#include "../src/PrintConsole.h"

#define BIGBOARDSIZE 8
#define SMALLBOARDSIZE 3

class DefaultLogicTests : public testing::Test{
public:
    Board bigBoard;
    Board smallBoard;
    Player xPlayer;
    Player oPlayer;
    PrintConsole printConsole;
    DefaultLogic dBig;
    DefaultLogic dSmall;
    DefaultLogicTests(): bigBoard(BIGBOARDSIZE), smallBoard(SMALLBOARDSIZE), xPlayer(typeX), oPlayer(typeO),
                         printConsole(), dBig(&bigBoard,xPlayer,oPlayer,&printConsole),dSmall(&smallBoard,xPlayer,oPlayer,&printConsole){}



};

#endif //DEFAULTLOGICTESTS_H
