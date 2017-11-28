//
// Created by limor on 27/11/17.
//

#include <gtest/gtest.h>
#include "../src/Board.h"
#include "SquareTests.h"


#define BOARDSIZE 8


//test 1: check if comparing two equal squares returns true, and two different squares return false
TEST_F(SquareTests, checkEquation){
    Square s1(1,1,typeX),s2(2,2,typeO),s3(1,1,typeX),s4(1,1,typeO);
    EXPECT_FALSE(s1.equals(s2)) <<"incorrect location of O";
    EXPECT_FALSE(s1.equals(s4)) <<"incorrect location of X";
    EXPECT_TRUE(s1.equals(s3)) <<"incorrect location of O";
}


//test 2: check if specific square is
TEST_F(SquareTests, isSquareInVector) {
    Square s1(1,1,typeX),s2(2,2,typeO),s3(5,7,typeX),s4(3,2,typeO),squareToCheck(1,1,typeX);
    vector<Square> options ;
    options.push_back(s1);
    options.push_back(s2);
    options.push_back(s3);
    options.push_back(s4);
    EXPECT_TRUE(squareToCheck.isSquareInVector(options));
}


//test 3:
TEST_F(SquareTests, setSquareTypeWorks) {
    this->board.resetBoard();
    this->board.setSquare(4,4,typeO);
    this->board.getSquare(4,4)->setType(typeX);
    EXPECT_TRUE(this->board.getSquareType(4,4)==typeX);
}