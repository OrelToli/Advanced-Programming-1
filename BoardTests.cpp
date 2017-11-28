//
// Created by limor on 26/11/17.
//
using namespace std;
#include <gtest/gtest.h>
#include "../src/Board.h"
#include "../src/DefaultLogic.h"
#include "../src/PrintConsole.h"
#include "BoardTests.h"

//test 1: check the existence of 'X' and 'O' in the center of the board
TEST_F(BoardTests, isExistXOInCenter) {
    int location1 = BIGBOARDSIZE / 2 - 1, location2 = BIGBOARDSIZE / 2;
    EXPECT_TRUE(bigBoard.getSquareType(location1,location2) == typeX) <<"incorrect location of O";
    EXPECT_TRUE(bigBoard.getSquareType(location2,location1) == typeX) <<"incorrect location of O";
    EXPECT_TRUE(bigBoard.getSquareType(location1,location1) == typeO) <<"incorrect location of X";
    EXPECT_TRUE(bigBoard.getSquareType(location2,location2) == typeO) <<"incorrect location of X";
}


//test 2: check if points are in the limits of the board
TEST_F(BoardTests, isSquareInBoard) {
    this->bigBoard.resetBoard();
    int upperBound = BIGBOARDSIZE +1, downBound = 0;
    Square square1(upperBound,upperBound,typeX);
    Square square2(downBound+4, downBound+4,typeX);
    EXPECT_FALSE(bigBoard.isSquareInBoard(square1.getX(),square1.getY())) << "problem with isSquareInBoard function";
    EXPECT_TRUE(bigBoard.isSquareInBoard(square2.getX(),square2.getY())) << "problem with isSquareInBoard function";
}


//test 3:check setSquare function
TEST_F(BoardTests, setSquareCheck) {
    this->bigBoard.resetBoard();
    int index=1;
    bigBoard.setSquare(index,index,typeX);
    EXPECT_EQ(bigBoard.getSquareType(index,index), typeX) << "Incorrect allocation of square" ;
}


//test 4: check if copy-constructor works perfectly
TEST_F(BoardTests, isCopyBoardOK) {
    this->bigBoard.resetBoard();
    int index=1;
    bigBoard.setSquare(index,index,typeO);
    index++;
    bigBoard.setSquare(index,index,typeO);
    index++;
    bigBoard.setSquare(index,index,typeO);
    index++;
    bigBoard.setSquare(index,index,typeX);
    index++;
    bigBoard.setSquare(index,index,typeX);
    index++;
    bigBoard.setSquare(index,index,typeX);
    Board copyBoard(bigBoard);
    EXPECT_TRUE(bigBoard.equals(&copyBoard)) <<"copy constructor isn't correct - the boards aren't equal to each other";
}


//test 5:simulate specific situation on the board,and check that the vector of possible moves is full
TEST_F(BoardTests, isAvailableMovesCorrect) {
    this->bigBoard.resetBoard();
    PrintConsole printConsole = PrintConsole();
    Print &printStyle = printConsole;
    Player xPlayer = Player(typeX), oPlayer = Player(typeO);
    DefaultLogic dl(&bigBoard, xPlayer, oPlayer,&printStyle);
    bigBoard.setSquare(3,4,typeX);
    bigBoard.setSquare(4,4,typeX);
    bigBoard.setSquare(5,4,typeX);
    bigBoard.setSquare(4,5,typeX);
    bigBoard.setSquare(5,5,typeO);
    vector<Square> options = dl.isAvailableMove(bigBoard, oPlayer);
    EXPECT_TRUE(bigBoard.getSquare(5,3)->isSquareInVector(options)) <<"vector of possible options is not full";
    EXPECT_TRUE(bigBoard.getSquare(3,5)->isSquareInVector(options)) <<"vector of possible options is not full";
    EXPECT_FALSE(bigBoard.getSquare(6,6)->isSquareInVector(options)) <<"vector of possible contain wrong possibles";
    EXPECT_FALSE(bigBoard.getSquare(7,1)->isSquareInVector(options)) <<"vector of possible contain wrong possibles";
    EXPECT_FALSE(bigBoard.getSquare(5,4)->isSquareInVector(options)) <<"vector of possible contain wrong possibles";
}


