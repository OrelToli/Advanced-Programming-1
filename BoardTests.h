//
// Created by limor on 28/11/17.
//

#ifndef BOARDTESTS_H
#define BOARDTESTS_H

#include <gtest/gtest.h>
#include "../src/Board.h"

#define BIGBOARDSIZE 8
#define SMALLBOARDSIZE 3

class BoardTests : public testing::Test{
public:
    Board bigBoard;
    Board smallBoard;
    BoardTests(): bigBoard(BIGBOARDSIZE), smallBoard(SMALLBOARDSIZE){}

};

#endif //BOARDTESTS_H
