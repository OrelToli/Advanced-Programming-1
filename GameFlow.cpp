/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#include "GameFlow.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "RemotePlayer.h"
#include "PrintConsole.h"
#include "DefaultLogic.h"
#include "AILogic.h"
#include "RemoteLogic.h"
#include "Client.h"


using namespace std;

GameFlow:: GameFlow(int boardSize) : xPlayer(xPlayer), oPlayer(oPlayer), gameLogic(gameLogic) {

    Board *gameBoard = new Board(boardSize);
    PrintConsole printConsole = PrintConsole();
    Print &printStyle = printConsole;
    Player player1 = HumanPlayer(typeX), player2 = Player(typeO);

    this->gameLogic = decideGameType();
    this->board = gameBoard;
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
        gameLogic.humanMakeMove(*this->board, currentPlayer,printStyle);

        //change the turn between the players
        changeTurn(currentPlayer, playerFlag);
        this->currentGame = this->gameLogic.gameOver();
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
            Square currentAIMove = gameLogic.makeMoveAI(gameBoard, currentPlayer);
            //Announce AI played move.
            printStyle->printPlayAI(currentAIMove.getX() + 1,currentAIMove.getY() + 1);
        } else {

            //check what is the optional moves for the current player
            gameLogic.humanMakeMove(*this->board, currentPlayer,printStyle);
        }
        //change the turn between the players
        changeTurn(currentPlayer, playerFlag);
        currentGame = this->gameLogic.gameOver();
    }

    printGameOverAndWinner(this->currentGame);
}


//Here is like the main of the client.
void GameFlow::handleRemoteGame() {

    int turn;
    Board& gameBoard = *this->board;


    Client client = Client("127.0.0.1", 8000);
    if (setupClientAndPlayerType(client) == 1) {
        Player localPlayer = HumanPlayer(typeX);
        Player remotePlayer = RemotePlayer(typeO);
        turn = 1;
    } else {
        Player localPlayer = HumanPlayer(typeO);
        Player remotePlayer = RemotePlayer(typeX);
        turn = 0;


        ///print board and say waiting for other player
    }

    //1 is turn of human, 0 is turn of remote
    while (currentGame == gameContinues) {

        if(turn) {
            gameLogic.humanMakeMove(gameBoard,localPlayer,printStyle);
            ///you need to get the move somehow, in order to send it.
            //turn of human logic
            ///update here the other player!

        } else {
            ///get a move from the second player!


            //turn of remote logic
        }

        turn = changeRemoteTurn(turn);
        currentGame = this->gameLogic.gameOver();
    }


    ///if game is over, send to them or receive that the game is over
    printGameOverAndWinner(this->currentGame);
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

    return (client.getPlayerType());

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
    enum Type winner = this->gameLogic.checkWhoWins(board);
    this->printStyle->announceWhoWins(winner);

}


GameLogic GameFlow::decideGameType() {
    int playType;
    Player player2(typeO);
    this->printStyle->chooseGameType();
    cin>>playType;
    switch(playType) {

            case (1):
                player2 = HumanPlayer(typeO);
                this->oPlayer = player2;
                GameLogic logic = DefaultLogic(this->board, this->xPlayer, this->oPlayer, this->&printStyle);
                this->type = Local;
                return logic;

            case (2):
                player2 = AIPlayer(typeO);
                this->oPlayer = player2;
                GameLogic logic2 = AILogic(this->board, this->xPlayer, this->oPlayer, this->&printStyle);
                this->type = AI;
                return logic2;

            case (3):
                player2 = RemotePlayer(typeO);
                this->oPlayer = player2;
                GameLogic logic3 = RemoteLogic(this->board, this->xPlayer, this->oPlayer, this->&printStyle);
                this->type = Remote;
                return logic3;

        default:
            break;
    }
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

