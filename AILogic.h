//
// Created by Orel on 02/12/2017.
//

#ifndef EX3NEW_AILOGIC_H
#define EX3NEW_AILOGIC_H


#include "GameLogic.h"

class AILogic  : public GameLogic {

public:

    AILogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle);


    /**
     * The function is responsible for getting the current board, checking the best move to play for the AI,
     * Playing it, and announcing it.
     * @param gameBoard - current gameboard
     * @param player - Our AI player.
     */
    Square makeMoveAI(Board& gameBoard, Player player);

    /**
      * The MinMax function, for a given vector of possible moves for the AI, runs in a loop, checks for each
      * move which gets the minimum points of the X player, and returns the best move to the makeMoveAI function.
      * @param gameBoard - our current gameboard
      * @param options - A given vector of possible moves for the AI
      * @return The current AI best move to play.
      */
    Square* minMaxMoveChosen(Board &gameBoard, vector<Square>& options);

    /**
     * Plays the given AI move, then runs in a loop, to create simulations of the possible next moves
     * of the X player. After each X player move, checks the differece in points and saves the move with the
     * MAX points that the X player can get. Return the max points that the X player can get from the
     * move that the O player did.
     * @param currentAIMove - the current move for the AI to play, to run the simulations on.
     * @param currentGameBoard - Our gameboard
     * @return The max points of the current X player possible moves.
     */
    int moveWithMinimalHumanPlayerPoints(Square currentAIMove, Board &currentGameBoard);


    /**
     * Calculates the difference between the User-AI points on the board
     * @param gameBoard - the game board to check.
     * @return The difference in points
     */
    int playerAIPointsAdvantage(Board& gameBoard);

};


#endif //EX3NEW_AILOGIC_H
