/**
 * name : Limor Levi
 * id number : 308142389
**/

#ifndef PRINTCONSOLE_H
#define PRINTCONSOLE_H

#include "Print.h"
#include "Board.h"


class PrintConsole : public Print {

public :
    /**
     * @name : PrintConsole
     * @parameters : no parameters
     * @return : the function creates an instance of printing on the console
     **/
    PrintConsole();

    /**
     * @name : printBoard
     * @parameters : the board of the game
     * @return : the function prints the board
     **/
    void printBoard(Board &gameBoard);

    /**
     * @name : printOptionsToPlayer
     * @parameters : vector of optional squares
     * @return : the function prints all the options of the player
     **/
    void printOptionsToPlayer(vector<Square> &options);

    /**
     * @name : announceTurn
     * @parameters : the current player
     * @return : the function announce who the turn belongs to
     **/
    void announceTurn(Player &currentPlayer);

    /**
     * @name : askMoveFromPlayer
     * @parameters : row and col variables to save the input in
     * @return : the function asks from the player to choose move
     **/
    void askMoveFromPlayer();

    /**
     * @name : wrongInput
     * @parameters : no parameters
     * @return : the function ask from the player to choose another move
     **/
    void wrongInput();

    /**
     * @name : announceWhoWins
     * @parameters : the winner of the game
     * @return : the function announce who wins in the game
     **/
    void announceWhoWins(enum Type winner);

    /**
     * @name : noOptionsToBothPlayers
     * @parameters : no parameters
     * @return : the function announce that there are no possible options to both of the players
     **/
    void noOptionsToBothPlayers();

    /**
     * @name : fullBoard
     * @parameters : no parameters
     * @return : the function announce that the board is full
     **/
    void fullBoard();

    /**
     * @name : createSpace
     * @parameters : no parameters
     * @return : the function creates spaces between the the printed boards
     **/
    void createSpace() ;

    /**
     * @name : noPossibleOptionsToCurrentPlayer
     * @parameters : the sign of the current player
     * @return : the function announce that the current player doesn't have any option to do
     **/
    void noPossibleOptionsToCurrentPlayer(enum Type currentPlayer) ;

    /**
     * @name :
     * Asks the player whether he wants to play a CO-OP game or game vs AI
     */
    void chooseAIGameOrCoop() ;


    /**
     * @name : Prints the move that the AI played.
     * @param row - the row of the square that the AI played.
     * @param col - the col of the square that the AI played.
     */
    void printPlayAI(int row, int col);

    /**
     * Returns the char type of the enum Type
     * @param type - enum Type of the square
     * @return cahr type
     */
    char returnType(enum Type type);

    /**
     * @name : Prints on the screen that the User player played.
     */
    void boardAfterUser();

};
#endif //PRINTCONSOLE_H