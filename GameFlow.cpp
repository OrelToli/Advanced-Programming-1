/**
 * name : Limor Levi
 * id number : 308142389
**/

#include "GameFlow.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include <limits>

using namespace std;

GameFlow:: GameFlow(GameLogic* gameLogic, Board* board, Player& xPlayer, Player& oPlayer, Print* printStyle) :
        gameLogic(gameLogic), board(board), xPlayer(xPlayer), oPlayer(oPlayer) , printStyle(printStyle) {
    this->gameLogic = gameLogic;
    this->board = board;
    this->xPlayer = xPlayer;
    this->oPlayer = oPlayer;
    this->printStyle = printStyle;
}


void GameFlow::runGame(){

    Player current=this->xPlayer;
    Player& currentPlayer = current;
    //player flag is used to change turns between the players
    bool flag = true,&playerFlag = flag ;
    Board& gameBoard = *this->board;
    int gameType = AIorUser();

    gameOverOrNot currentGame = this->gameLogic->gameOver();
    //run the game until the game is over
    while (currentGame == gameContinues) {

        //Checking game type. If AI is playing, run makeMoveAI.
        if (gameType && currentPlayer.getType() == typeO) {
            Square currentAIMove = gameLogic->makeMoveAI(gameBoard, currentPlayer);

            //Announce AI played move.
            printStyle->printPlayAI(currentAIMove.getX() + 1,currentAIMove.getY() + 1);

        }

        //Player X is user and always plays. If the game is User vs User & Player is 0, let him play as well.
        if(currentPlayer.getType() == typeX || (currentPlayer.getType() == typeO && !gameType)) {

            //check what is the optional moves for the current player
            vector<Square> options = gameLogic->isAvailableMove(*this->board, currentPlayer);
            if (options.empty()) {
                this->printStyle->noPossibleOptionsToCurrentPlayer(currentPlayer.getType());
                changeTurn(currentPlayer, playerFlag);
                continue;
            }
            getMoveAndPlayIt(gameBoard, currentPlayer, options);
            options.clear();

            if(gameType)
                printStyle->boardAfterUser();

            printStyle->printBoard(gameBoard);

        }
        //change the turn between the players
        changeTurn(currentPlayer, playerFlag);
        currentGame = this->gameLogic->gameOver();
    }
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


int GameFlow::AIorUser() {
    int playType;
    this->printStyle->chooseAIGameOrCoop();
    cin>>playType;
    if(playType) {
        Player player2 = AIPlayer(typeO);
        this->oPlayer = player2;

    } else {
        Player player2 = HumanPlayer(typeO);
        this->oPlayer = player2;
    }

    return playType;

}


void GameFlow::getMoveAndPlayIt(Board& gameBoard, Player& currentPlayer, vector<Square>& options) {
    int row, col;
    char dummy;
    //print the current state of the board and ask move from the player
    this->printStyle->printBoard(gameBoard);
    this->printStyle->announceTurn(currentPlayer);
    this->printStyle->printOptionsToPlayer(options);
    //wait to the user input and check correctness of it
    while (true) {
        this->printStyle->askMoveFromPlayer();
        cin >> row >> dummy >> col;
        //check if row and col are valid integers
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if ((!board->isSquareInBoard(row - 1, col - 1)) ||
            (!gameBoard.getSquare(row - 1, col - 1)->isSquareInVector(options))) {
            this->printStyle->wrongInput();
            continue;
        }
        break;
    }
    this->printStyle->createSpace();
    //make the current player's move
    gameLogic->makeMove(currentPlayer, gameBoard, row - 1, col - 1);
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