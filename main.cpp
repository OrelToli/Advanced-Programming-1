/**
 * name : Limor Levi
 * id number : 308142389
**/

#define BOARDSIZE 8

#include "Board.h"
#include "GameLogic.h"
#include "GameFlow.h"
#include "HumanPlayer.h"
#include "PrintConsole.h"
#include "DefaultLogic.h"

int main() {
    //in this assignment, the game runs on the console, so we use the PrintConsole style
    PrintConsole printConsole = PrintConsole();
    Print &printStyle = printConsole;
    //creation of the game board in size 8
    Board *gameBoard = new Board(BOARDSIZE);
    //in this assignment, only human players is involved in the game
    Player player1 = HumanPlayer(typeX), player2 = Player(typeO);
    Player &xPlayer = player1, oPlayer = player2;

    DefaultLogic defaultLogic = DefaultLogic(gameBoard, xPlayer, oPlayer, &printStyle);
    GameLogic &gameLogic = defaultLogic;

    GameFlow gameFlow(&gameLogic, gameBoard, xPlayer, oPlayer, &printStyle);
    gameFlow.runGame();
    delete gameBoard;
    return 0;
}