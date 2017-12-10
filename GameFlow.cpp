/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#include <fstream>
#include <cstdlib>
#include "GameFlow.h"
#include "HumanPlayer.h"
#include "RemotePlayer.h"
using namespace std;

GameFlow:: GameFlow(Board * gameBoard, GameLogic* gameLogic,Player player1, Player player2, Print* printStyle, gameType type) : xPlayer(xPlayer), oPlayer(oPlayer), gameLogic(gameLogic) {

    this->type = type;
    this->printStyle = printStyle;
    this->board = gameBoard;
    this->gameLogic = gameLogic;
    this->xPlayer = player1;
    this->oPlayer = player2;
    this->currentGame = gameContinues;
}


void GameFlow::runGame(){

    switch(type) {
        case (Local) :
            handleHumanGame();
            break;

        case (AI) :
            handleAIGame();
            break;

        case (Remote) :
            handleRemoteGame();
            break;
    }
    delete this->board;
}




void GameFlow::handleHumanGame() {
    Player current=this->xPlayer;
    Player& currentPlayer = current;

    //player flag is used to change turns between the players
    bool flag = true,&playerFlag = flag ;
    Board& gameBoard = *this->board;

    //run the game until the game is over
    while (currentGame == gameContinues) {

        //check what is the optional moves for the current player
        this->printStyle->printBoard(gameBoard);
        gameLogic->humanMakeMove(*this->board, currentPlayer,printStyle, new int[2]);

        //change the turn between the players
        changeTurn(currentPlayer, playerFlag);
        this->currentGame = this->gameLogic->gameOver();
    }

    printGameOverAndWinner(this->currentGame);
}




void GameFlow::handleAIGame() {

    Player current=this->xPlayer;
    Player& currentPlayer = current;
    //player flag is used to change turns between the players
    bool flag = true,&playerFlag = flag ;
    Board& gameBoard = *this->board;

    //run the game until the game is over
    while (currentGame == gameContinues) {

        //Checking game type. If AI is playing, run makeMoveAI.
        if (currentPlayer.getType() == typeO) {
            Square currentAIMove = gameLogic->makeMoveAI(gameBoard, currentPlayer);
            //Announce AI played move.
            printStyle->printPlayAI(currentAIMove.getX() + 1,currentAIMove.getY() + 1);
        } else {
            //check what is the optional moves for the current player
            this->printStyle->printBoard(gameBoard);
            gameLogic->humanMakeMove(*this->board, currentPlayer,printStyle,new int[2]);
        }
        //change the turn between the players
        changeTurn(currentPlayer, playerFlag);
        currentGame = this->gameLogic->gameOver();
    }
    printGameOverAndWinner(this->currentGame);
}


void GameFlow::handleRemoteGame() {
    int portNumber;
    string ip;
    getIPPort(ip,portNumber);
    int turn;
    Player* localPlayer, *remotePlayer;
    Client client = Client(ip.c_str(), portNumber);
    int setup = setupClientAndPlayerType(client);
    if (setup == 1) {
        localPlayer = new HumanPlayer(typeX);
        remotePlayer = new RemotePlayer(typeO);
        turn = 1;

    } else {
        localPlayer = new HumanPlayer(typeO);
        remotePlayer = new RemotePlayer(typeX);
        turn = 0;
    }
    printStyle->printBoard(*this->board);
    int square[2];
    //1 is turn of human, 0 is turn of remote
    while (true) {

        if(turn) {
            gameLogic->humanMakeMove(*this->board,*localPlayer,printStyle,square);
            printStyle->printBoard(*this->board);
            client.sendMove(square);

        } else {
            client.getRemoteMove(square);
            if(square[0] == -2) // END GAME
                break;
            else if(square[0] == -1) {
                printStyle->noPossibleOptionsToCurrentPlayer(remotePlayer->getType());
            }
            else
                this->gameLogic->remoteMakeMove(*this->board,*remotePlayer,printStyle,square);

        }

        turn = changeRemoteTurn(turn);
        currentGame = this->gameLogic->gameOver();
        if(currentGame == gameOverFullBoard ||currentGame == gameOverNoMoreMoves) {
            break;
        }

    }
    ///if game is over, send to them or receive that the game is over
    printGameOverAndWinner(this->currentGame);
}

void GameFlow::getIPPort(string& ip, int& portNumber) {
    char ipAddress[20], port[4];
    ifstream myFile;

    myFile.open("settings.txt");
    if(myFile.is_open()){
        //read the ip address
        myFile>>ipAddress;
        ip = ipAddress;
        //read the port number
        myFile>>port;
        portNumber = atoi (port);
        myFile>>portNumber;
    }
    //close "settings.txt" file
    myFile.close();
}


int GameFlow::changeRemoteTurn(int turn){

    if(turn) {
        return 0;
    } else {
        return 1;
    }

}




//0 for x local, 1 for O local
int GameFlow::setupClientAndPlayerType(Client& client) {
    try {
        client.connectToServer();
    } catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
        exit(-1);
    }
    this->printStyle->waitingForOtherPlayer();
    int type = client.getPlayerType();
    this->printStyle->connectedToServer();
    return (type);
}


void GameFlow::printGameOverAndWinner(gameOverOrNot currentGame) {

    if(currentGame == gameOverFullBoard) {
        this->printStyle->printBoard(*board);
        this->printStyle->fullBoard();

    } else if (currentGame == gameOverNoMoreMoves) {
        this->printStyle->printBoard(*board);
        this->printStyle->noOptionsToBothPlayers();

    }
    //check who is the winner and announce it
    enum Type winner = this->gameLogic->checkWhoWins(board);
    this->printStyle->announceWhoWins(winner);

}


void GameFlow::changeTurn(Player& player, bool& playerFlag) {
    if(playerFlag){
        player = this->oPlayer;
        playerFlag = false;
    }
    else{
        player = this->xPlayer;
        playerFlag = true;
    }
}

