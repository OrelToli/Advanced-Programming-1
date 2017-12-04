/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#ifndef PRINT_H
#define PRINT_H
#include "Square.h"
#include "Player.h"
#include "Board.h"
#include <vector>

class Print {

public :
    /**
     * @name : printBoard
     * @parameters : the board of the game
     * @return : the function prints the board
     **/
    virtual void printBoard(Board& gameBoard) = 0;

    /**
     * @name : printOptionsToPlayer
     * @parameters : vector of optional squares
     * @return : the function prints all the options of the player
     **/
    virtual void printOptionsToPlayer(vector <Square> &options) = 0;

    /**
     * @name : announceTurn
     * @parameters : the current player
     * @return : the function announce who the turn belongs to
     **/
    virtual void announceTurn(Player& currentPlayer) = 0;

    /**
     * @name : askMoveFromPlayer
     * @parameters : no parameters
     * @return : the function asks from the player to choose move
     **/
    virtual void askMoveFromPlayer() = 0;

    /**
     * @name : wrongInput
     * @parameters : no parameters
     * @return : the function ask from the player to choose another move
     **/
    virtual void wrongInput() = 0;

    /**
     * @name : announceWhoWins
     * @parameters : the winner of the game
     * @return : the function announce who wins in the game
     **/
    virtual void announceWhoWins(enum Type winner) = 0;

    /**
     * @name : noOptionsToBothPlayers
     * @parameters : no parameters
     * @return : the function announce that there are no possible options to both of the players
     **/
    virtual void noOptionsToBothPlayers() = 0;

    /**
     * @name : fullBoard
     * @parameters : no parameters
     * @return : the function announce that the board is full
     **/
    virtual void fullBoard() = 0;

    /**
     * @name : createSpace
     * @parameters : no parameters
     * @return : the function creates spaces between the the printed boards
     **/
    virtual void createSpace() = 0;

    /**
     * @name : noPossibleOptionsToCurrentPlayer
     * @parameters : the sign of the current player
     * @return : the function announce that the current player doesn't have any option to do
     **/
    virtual void noPossibleOptionsToCurrentPlayer(enum Type currentPlayer) = 0 ;

    /**
     * @name :
     * Asks the player whether he wants to play a CO-OP game or game vs AI
     **/
    virtual void chooseGameType() = 0 ;

    /**
     * @name : Prints the move that the AI played.
     * @param row - the row of the square that the AI played.
     * @param col - the col of the square that the AI played.
     */
    virtual void printPlayAI(int row, int col) = 0;

    /**
     * Returns the char type of the enum Type
     * @param type - enum Type of the square
     * @return cahr type
     */
    virtual char returnType(enum Type type) = 0;

    /**
     * @name : Prints on the screen that the User player played.
     */
    virtual void boardAfterUser() = 0;

};
#endif //PRINT_H