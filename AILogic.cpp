//
// Created by Orel on 02/12/2017.
//

#include "AILogic.h"


AILogic::AILogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle) :
        GameLogic(board, xPlayer, oPlayer, printStyle) {
    //initialization the array of directions
    this->directions[0] = RIGHT;
    this->directions[1] = RIGHTDOWN;
    this->directions[2] = DOWN;
    this->directions[3] = LEFTDOWN;
    this->directions[4] = LEFT;
    this->directions[5] = LEFTUP;
    this->directions[6] = UP;
    this->directions[7] = RIGHTUP;
    this->board = board;
    this->xPlayer = xPlayer;
    this->oPlayer = oPlayer;
    this->printStyle = printStyle;
}



Square AILogic::makeMoveAI(Board &gameBoard, Player player) {
    Square* currentMove;
    //AI is given a vector of possible moves.
    vector<Square> options = isAvailableMove(*this->board, player);
    if (options.empty()) {
        this->printStyle->noPossibleOptionsToCurrentPlayer(player.getType());
    } else {
        //Send to Function minMaxMoveChosen a reference of the vector,
        // receive back a pointer to the best move to play.
        currentMove = minMaxMoveChosen(gameBoard, options);

        //AI play currentMove Pointer
        this->makeMove(player,gameBoard,currentMove->getX(),currentMove->getY());

    }
    return *currentMove;
}

//(Chooses a move to play by checking each move of the O player, to get the minimal points of the X player)
Square* AILogic::minMaxMoveChosen(Board &gameBoard, vector<Square>& options){

    int min = INT_MAX;
    int temp;
    Square * bestMove = NULL;
    //Go over all possible given moves of the O player.
    for( vector<Square>::iterator it=options.begin();it!=options.end();it++){

        //getting the current point of the move, according to the best move of the X player
        temp = moveWithMinimalHumanPlayerPoints(*it, gameBoard);

        //checking if the current move is better than the rest of the moves. If so, saves it using a pointer.
        if(temp < min) {
            min = temp;
            bestMove = &(*it);
        }
    }
    return bestMove;
}


//(Gets each O player move, then checks each X player move to get the max points X could possibly get from his moves)
int AILogic::moveWithMinimalHumanPlayerPoints(Square currentAIMove, Board &currentGameBoard) {

    Board gameboard2 = currentGameBoard;
    //Send the play to "make move" function, along with the gameBoard2 reference
    makeMove(oPlayer,gameboard2,currentAIMove.getX(),currentAIMove.getY());

    //get all possible next moves for player X.
    vector<Square> options = isAvailableMove(gameboard2, xPlayer);
    int max = INT_MIN;
    int temp;

    for( vector<Square>::iterator it=options.begin();it!=options.end();it++){

        Board gameboard3 = gameboard2;
        //before player move, after AI

        //Send to "make move" function, the gameBoard3 reference + the current i move.
        makeMove(xPlayer,gameboard3,it->getX(),it->getY());
        temp = playerAIPointsAdvantage(gameboard3);
        //after AI move

        if(temp > max)
            max = temp;
    }

    //The maximum points that the User can get from his moves, according to the current AI move
    return max;

}

int AILogic::playerAIPointsAdvantage(Board& gameBoard) {

    int xCounter=0, oCounter=0;
    //count the number of 'X' squares and 'O' squares in the board
    for(int i=0;i<gameBoard.getBoardSize();i++){
        for(int j=0;j<gameBoard.getBoardSize();j++){
            if(gameBoard.getSquareType(i,j) == typeX)
                xCounter++;
            else if(gameBoard.getSquareType(i,j) == typeO)
                oCounter++;
        }
    }

    return (xCounter - oCounter);

}
