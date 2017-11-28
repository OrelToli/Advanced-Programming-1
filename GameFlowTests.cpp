//
// Created by orel on 27/11/17.
//

using namespace std;
#include <gtest/gtest.h>
#include "../src/Board.h"
#include "../src/DefaultLogic.h"
#include "../src/PrintConsole.h"
#include "../src/GameFlow.h"
#include "GameFlowTests.h"


TEST_F(GameFlowTests, TurnsChangeCorrectly) {

    Board b(3);
    b.resetBoard();
    Player x = Player(typeX);
    Player o = Player(typeO);
    PrintConsole printConsole = PrintConsole();
    Print &p = printConsole;
    DefaultLogic d = DefaultLogic(&b,x,o,&p);
    GameFlow f = GameFlow(&d,&b,x,o,&p);
    bool flag = true;
    bool firstTurn = false;
    bool secondTurn = false;
    Player &current = x;
    f.changeTurn(current,flag);
    firstTurn = (current.getType() == o.getType());
    f.changeTurn(current,flag);
    secondTurn = (current.getType() == x.getType());

    EXPECT_EQ(firstTurn,secondTurn);


}


