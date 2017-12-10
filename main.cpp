/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#define BOARDSIZE 8
#include "Board.h"
#include "GameLogic.h"
#include "GameFlow.h"
#include "HumanPlayer.h"
#include "PrintConsole.h"
#include "DefaultLogic.h"
#include "AILogic.h"
#include "RemotePlayer.h"
#include "AIPlayer.h"
#include "RemoteLogic.h"

int main() {


    gameType type = NoGame;
    while(true) {
        Board *gameBoard = new Board(BOARDSIZE);
        Print *printStyle = new PrintConsole();
        Player player1 = HumanPlayer(typeX), player2 = Player(typeO);
        GameLogic *pLogic;
        int playType;

        if (type == NoGame) {
            printStyle->chooseGameType();
            cin >> playType;
        }

        switch (playType) {
            case (1): {
                player2 = HumanPlayer(typeO);
                DefaultLogic logic(gameBoard, player1, player2, printStyle);
                pLogic = &logic;
                type = Local;
                break;
            }
            case (2): {
                player2 = AIPlayer(typeO);
                AILogic logic(gameBoard, player1, player2, printStyle);
                pLogic = &logic;
                type = AI;
                break;
            }
            case (3): {
                player2 = RemotePlayer(typeO);
                RemoteLogic logic(gameBoard, player1, player2, printStyle);
                pLogic = &logic;
                type = Remote;
                break;
            }
            default:
                break;
        }


        GameFlow gameFlow(gameBoard, pLogic, player1, player2, printStyle, type);
        gameFlow.runGame();

        if(type!=Remote)
            break;
    }



    return 0;
}

