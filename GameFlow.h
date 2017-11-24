/**
 * name : Limor Levi
 * id number : 308142389
**/

#ifndef GAMEFLOW_H
#define GAMEFLOW_H

using namespace std;

#include <vector>
#include "Square.h"
#include "Player.h"
#include "GameLogic.h"
#include "Board.h"

class GameFlow {

public:
    /**
     * @name : GameFlow
     * @parameters : game logic object , the game of the board and the players
     * @return : the function creates new instance of gameFlow object
     **/
    GameFlow(GameLogic* gameLogic, Board* board, Player& xPlayer, Player& oPlayer, Print* printStyle);

    /**
     * @name : runGame
     * @parameters : no parameters
     * @return : the function runs the whole game until it ends
     **/
    void runGame();

    /**
      * @name : changeTurn
      * @parameters : reference to the current player and player "flag"
      * @return : the function changes turn between the players
      **/
    void changeTurn(Player& player, bool& playerFlag);

    /**
     * Asks the user whether he wants a co-op game or User vs AI game.
     * @return - 1 for User vs AI, 0 for CO-OP
     */
    int AIorUser();

    /**
     * Gets a vector of possible moves. The function is responsible for declaring the possible moves,
     * getting the move input from the user, and playing it.
     * @param gameBoard - The current gameboard
     * @param currentPlayer - The current player to play the game
     * @param options - Our vector of possible moves.
     */
    void getMoveAndPlayIt(Board& gameBoard, Player& currentPlayer, vector<Square>& options);


private:
    GameLogic* gameLogic;
    Board* board;
    Player xPlayer;
    Player oPlayer;
    Print* printStyle;
};
#endif //GAMEFLOW_H