/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#define NUMDIRECTIONS 8
#define INT_MAX 10000000
#define INT_MIN -10000000
#define NO_MOVES "NoMove"
#define END_GAME "End"
#define NO_MOVES_FLAG -1
#define END_GAME_FLAG -2
#include <string>
#include <string.h>
#include <unistd.h>
enum gameOverOrNot {gameOverFullBoard, gameOverNoMoreMoves, gameContinues};
using namespace std;

#include <vector>
#include "Square.h"
#include "Player.h"
#include "Board.h"
#include "Print.h"


class GameLogic {

public :
    enum Direction {RIGHT, RIGHTDOWN,DOWN, LEFTDOWN, LEFT, LEFTUP, UP, RIGHTUP };

    /**
     * @name : GameLogic
     * @parameters : the board of the game, two players and the style of printing
     * @return : the function creates new game logic object
     **/
    GameLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle);

    /**
     * The function is responsible for getting the current board, checking the best move to play for the AI,
     * Playing it, and announcing it.
     * @param gameBoard - current gameboard
     * @param player - Our AI player.
     * @return - the AI move
     */
    virtual Square makeMoveAI(Board& gameBoard, Player player) {};


    /**
     * The MinMax function, for a given vector of possible moves for the AI, runs in a loop, checks for each
     * move which gets the minimum points of the X player, and returns the best move to the makeMoveAI function.
     * @param gameBoard - our current gameboard
     * @param options - A given vector of possible moves for the AI
     * @return The current AI best move to play.
     */
    virtual Square* minMaxMoveChosen(Board &gameBoard, vector<Square>& options) {};


    /**
     * Plays the given AI move, then runs in a loop, to create simulations of the possible next moves
     * of the X player. After each X player move, checks the differece in points and saves the move with the
     * MAX points that the X player can get. Return the max points that the X player can get from the
     * move that the O player did.
     * @param currentAIMove - the current move for the AI to play, to run the simulations on.
     * @param currentGameBoard - Our gameboard
     * @return The max points of the current X player possible moves.
     */
    virtual int moveWithMinimalHumanPlayerPoints(Square currentAIMove, Board &currentGameBoard) {};


    /**
     * Calculates the difference between the User-AI points on the board
     * @param gameBoard - the game board to check.
     * @return The difference in points
     */
    virtual int playerAIPointsAdvantage(Board& gameBoard) {} ;

    /**
     * @name : valueOfDirection
     * @parameters : direction
     * @return : the function returns a pair which represents the specific direction
     **/
    pair<int,int> valueOfDirection(Direction d);

    /**
     * @name : isAnotherSquareOfPlayerInDirection
     * @parameters : the square of the current player, the sign of the current player and direction to check
     * @return : the function returns true if there is another square of the player in the direction, or false otherwise
     **/
    bool isAnotherSquareOfPlayerInDirection(enum Type currentPlayer, Direction direction, int row, int col);

    /**
 * @name : gameOver
 * @parameters : no parameters
 * @return : true if the game should over or false otherwise
 **/
    enum gameOverOrNot gameOver();

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
   * Gets a vector of possible moves. The function is responsible for declaring the possible moves,
   * getting the move input from the user, and playing it.
   * @param gameBoard - The current gameboard
   * @param currentPlayer - The current player to play the game
   * @param options - Our vector of possible moves.
   */
    void getMoveAndPlayIt(Board& gameBoard, Player& currentPlayer, vector<Square>& options);

    void humanMakeMove(Board& gameBoard, Player& player, Print* printStyle, int* arrayLocation);

    virtual void remoteMakeMove(Board& gameBoard, Player& player, Print* printStyle, int* remoteMove) {};


    protected:
    Direction directions[NUMDIRECTIONS];
    Board* board;
    Player xPlayer;
    Player oPlayer;
    Print* printStyle;
    char lastMove[10];
    int lastRow;
    int lastCol;
};
#endif //GAMELOGIC_H