//
// Created by limor on 28/11/17.
//

#ifndef SQUARETESTS_H
#define SQUARETESTS_H



#include <gtest/gtest.h>
#include "../src/Board.h"

#define BIGBOARDSIZE 8
#define SMALLBOARDSIZE 3


class SquareTests : public testing::Test{
public:
    Board board;
    SquareTests(): board(BIGBOARDSIZE){}

};

#endif //SQUARETESTS_H
