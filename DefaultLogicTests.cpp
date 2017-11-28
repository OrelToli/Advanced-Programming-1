//
// Created by orel on 27/11/17.
//
using namespace std;
#include <gtest/gtest.h>
#include "../src/Board.h"
#include "../src/DefaultLogic.h"
#include "DefaultLogicTests.h"



//Creates a game that should end due to full board, checks if the gameOver function decides that the game is over.
TEST_F(DefaultLogicTests, GameOverWhenFullBoard) {
    this->bigBoard.resetBoard();

    bigBoard.setSquare(1,1,typeX);
    bigBoard.setSquare(1,2,typeX);
    bigBoard.setSquare(1,3,typeX);
    bigBoard.setSquare(2,1,typeX);
    bigBoard.setSquare(2,2,typeX);
    bigBoard.setSquare(2,3,typeX);
    bigBoard.setSquare(3,1,typeX);
    bigBoard.setSquare(3,2,typeX);
    bigBoard.setSquare(3,3,typeX);

    EXPECT_TRUE(dBig.gameOver()) << "GameOverWhenFullBoard Failed";

}

//
TEST_F(DefaultLogicTests, GameOverWhenNoMoreMoves) {
    this->smallBoard.resetBoard();

    smallBoard.setSquare(1,2,typeO);
    smallBoard.setSquare(2,1,typeX);
    smallBoard.setSquare(2,2,typeX);
    smallBoard.setSquare(2,3,typeO);
    smallBoard.setSquare(3,2,typeX);

    EXPECT_TRUE(dSmall.gameOver()) << "GameOverWhenNoMoreMoves Failed";

}


TEST_F(DefaultLogicTests, AvailableMovesAreAsExpected) {

    this->bigBoard.resetBoard();

    int movesCounter = 0;
    vector<Square> excpectedAvailableMoves;
    excpectedAvailableMoves.push_back(Square(1,3,typeX));
    excpectedAvailableMoves.push_back(Square(2,4,typeX));
    excpectedAvailableMoves.push_back(Square(3,1,typeX));
    excpectedAvailableMoves.push_back(Square(3,5,typeX));
    excpectedAvailableMoves.push_back(Square(5,1,typeX));
    excpectedAvailableMoves.push_back(Square(5,2,typeX));
    excpectedAvailableMoves.push_back(Square(5,3,typeX));

    bigBoard.setSquare(2,2,typeX);
    bigBoard.setSquare(2,3,typeO);
    bigBoard.setSquare(3,2,typeO);
    bigBoard.setSquare(3,3,typeX);
    bigBoard.setSquare(3,4,typeO);
    bigBoard.setSquare(4,2,typeO);
    bigBoard.setSquare(4,3,typeO);

    vector<Square> options = dBig.isAvailableMove(bigBoard, xPlayer);
    EXPECT_EQ(excpectedAvailableMoves.size(),options.size()) << "AvailableMovesAreAsExpected Failed - Vector Size";

    for( vector<Square>::iterator it=options.begin();it!=options.end();it++)
        for( vector<Square>::iterator it2=excpectedAvailableMoves.begin();it2!=excpectedAvailableMoves.end();it2++)
            if((*it).isSameLocation((*it2)))
                movesCounter++;


    EXPECT_EQ(movesCounter,options.size()) << "AvailableMovesAreAsExpected Failed - Not all the moves exist";
    options.clear();
    excpectedAvailableMoves.clear();
}



//
//TEST_F(DefaultLogicTests, PlayerMoveEatsOtherPlayerSquaresCorrectly) {
//
//    bool allCirclesFlipped = false;
//    this->smallBoard.resetBoard();
//
//    //Eating at 3,1
//    smallBoard.setSquare(0,0,typeX);
//    smallBoard.setSquare(1,0,typeO);
//    smallBoard.setSquare(1,1,typeO);
//    smallBoard.setSquare(2,1,typeO);
//    smallBoard.setSquare(0,2,typeX);
//    smallBoard.setSquare(2,2,typeX);
//
//    printConsole.printBoard(smallBoard);
//    dSmall.makeMove(xPlayer,smallBoard,2,0);
//    if(smallBoard.getSquareType(2,1) == typeX && smallBoard.getSquareType(2,2) == typeX && smallBoard.getSquareType(3,2) == typeX)
//        allCirclesFlipped = true;
//
//    EXPECT_TRUE(allCirclesFlipped) << "PlayerMoveEatsOtherPlayerSquaresCorrectly Failed";
//    printConsole.printBoard(smallBoard);
//}


TEST_F(DefaultLogicTests, NoPossibleMovesAvailable) {
    this->smallBoard.resetBoard();

    smallBoard.setSquare(1,1,typeO);
    smallBoard.setSquare(1,2,typeO);
    smallBoard.setSquare(2,1,typeX);
    smallBoard.setSquare(2,2,typeO);
    smallBoard.setSquare(2,3,typeX);
    smallBoard.setSquare(3,2,typeX);
    vector<Square> options = dSmall.isAvailableMove(smallBoard, xPlayer);


    EXPECT_TRUE(options.empty()) << "NoPossibleMovesAvailable Failed";

}



TEST_F(DefaultLogicTests, WhenGameOverTheRightPlayerWins) {

    this->smallBoard.resetBoard();

    Type expectedWinner = typeO;

    smallBoard.setSquare(1,2,typeO);
    smallBoard.setSquare(1,3,typeO);
    smallBoard.setSquare(2,2,typeX);
    smallBoard.setSquare(2,3,typeO);

    EXPECT_EQ(dSmall.checkWhoWins(&smallBoard),expectedWinner) << "WhenGameOverTheRightPlayerWins Failed";

}



TEST_F(DefaultLogicTests, AIChoosesTheBestMoveAvailable) {


    this->bigBoard.resetBoard();



    bigBoard.setSquare(4,4,typeX);
    bigBoard.setSquare(4,5,typeX);
    bigBoard.setSquare(5,4,typeX);
    bigBoard.setSquare(5,5,typeO);
    bigBoard.setSquare(3,4,typeX);

    dBig.makeMoveAI(bigBoard, oPlayer);

    Square bestOption1 = Square(3,3,typeO);
    Square bestOption2 = Square(5,3,typeO);

    bool excpectedMoveCompleted = (bigBoard.getSquareType(bestOption1.getX(),bestOption1.getY()) == bestOption1.getType()
        || bigBoard.getSquareType(bestOption2.getX(),bestOption2.getY()) == bestOption2.getType());
    EXPECT_TRUE(excpectedMoveCompleted) << "AIChoosesTheBestMoveAvailable Failed";

}


//
//TEST_F(DefaultLogicTests, AIAlgorithmCalculatesMaxPointsFromMovesOfUserPlayerCorrectly) {
//
//
//    this->bigBoard.resetBoard();
//
//    int maxPointsForAIMove = 0;
//    int expectedMaxPoints = 3;
//
//    bigBoard.setSquare(4,4,typeX);
//    bigBoard.setSquare(4,5,typeX);
//    bigBoard.setSquare(5,4,typeX);
//    bigBoard.setSquare(5,5,typeO);
//    bigBoard.setSquare(3,4,typeX);
//
//    Square currentAIMove = Square(3,3,typeO);
//    maxPointsForAIMove = dBig.moveWithMinimalHumanPlayerPoints(currentAIMove,bigBoard);
//    EXPECT_EQ(maxPointsForAIMove,expectedMaxPoints)
//                        << "AIAlgorithmCalculatesMaxPointsFromMovesOfUserPlayerCorrectly Failed";
//
//
//}


