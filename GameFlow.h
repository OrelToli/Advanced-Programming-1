/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#ifndef GAMEFLOW_H
#define GAMEFLOW_H

using namespace std;

#include <vector>
#include "Square.h"
#include "Player.h"
#include "GameLogic.h"
#include "Board.h"
#include "Client.h"

enum gameType {Local, AI, Remote};

class GameFlow {

public:
    /**
     * @name : GameFlow
     * @parameters : game logic object , the game of the board and the players
     * @return : the function creates new instance of gameFlow object
     **/
    GameFlow(Board * gameBoard, GameLogic* gameLogic,Player player1, Player player2, Print* printStyle, gameType type);

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
     * Asks the user whether he wants a co-op game or User vs AI game or Remote Play.
     */
    GameLogic* decideGameType();


    void printGameOverAndWinner(gameOverOrNot currentGame);

    void handleHumanGame();


    void handleAIGame();


    void handleRemoteGame();

    int setupClientAndPlayerType(Client& client);

    int changeRemoteTurn(int turn);

    void getIPPort(string& ip, int& portNumber);


private:
    GameLogic* gameLogic;
    Board* board;
    Player xPlayer;
    Player oPlayer;
    Print* printStyle;
    enum gameType type;
    enum gameOverOrNot currentGame;
};
#endif //GAMEFLOW_H