//
// Created by limor on 28/11/17.
//

#ifndef GAMEFLOWTESTS_H
#define GAMEFLOWTESTS_H

#include <gtest/gtest.h>
#include "../src/Board.h"

#define BIGBOARDSIZE 8
#define SMALLBOARDSIZE 3


class GameFlowTests : public testing::Test{
public:
    Board bigBoard;
    Board smallBoard;
    GameFlowTests(): bigBoard(BIGBOARDSIZE), smallBoard(SMALLBOARDSIZE){}

};

#endif //GAMEFLOWTESTS_H
