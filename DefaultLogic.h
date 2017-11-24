/**
 * name : Limor Levi
 * id number : 308142389
**/

#ifndef DEFAULTLOGIC_H
#define DEFAULTLOGIC_H

#include "GameLogic.h"

class DefaultLogic : public GameLogic {

public :
    /**
     * @name : GameLogic
     * @parameters : the board of the game, two players and the style of printing
     * @return : the function creates new game logic object
     **/
    DefaultLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle);

    /**
     * @name : gameOver
     * @parameters : no parameters
     * @return : true if the game should over or false otherwise
     **/
    bool gameOver();

    /**
      * @name : isAvailableMove
      * @parameters : the board of the game and the current player
      * @return : the function returns list of squares that optionally to the player's move
      **/
    vector<Square> isAvailableMove(Board& gameBoard, Player currentPlayer);

    /**
     * @name : makeMove
     * @parameters : the current player, board of the game and the location of the square
     * @return : the function makes one of the available moves of the current player
     **/
    void makeMove(Player& currentPlayer, Board& gameBoard, int row, int col);

    /**
     * @name : checkWhoWins
     * @parameters : no parameters
     * @return : the function returns the player who won the game
     **/
    enum Type checkWhoWins(Board *gameBoard);

    /**
     * @name : checkSquare
     * @parameters : the location of the square, vector of options and the board of the game
     * @return : the function adds optional moves to the vector of squares
     **/
    void checkSquare(int i, int j,enum Type player,vector<Square>& options, Board& gameBoard);

    /**
     * @name : changeSquares
     * @parameters : both of the players, direction, gameBoard and the location of the square
     * @return : the function changes the squares of the enemy to the squares of the player
     **/
    void changeSquares(Player& currentPlayer, Player& enemy, Direction direction, Board& gameBoard, int i, int j);

    /**
     * The function is responsible for getting the current board, checking the best move to play for the AI,
     * Playing it, and announcing it.
     * @param gameBoard - current gameboard
     * @param player - Our AI player.
     */
    void makeMoveAI(Board& gameBoard, Player player);

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
#endif //DEFAULTLOGIC_H