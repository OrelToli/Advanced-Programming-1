/**
 * name : Limor Levi
 * id number : 308142389
**/

#define NUMDIRECTIONS 8
#include "DefaultLogic.h"

DefaultLogic::DefaultLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle) :
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


bool DefaultLogic::gameOver(){
    bool winFlag = false;
    //vector that suppose to contain all the possible moves of the player
    vector<Square> squares;
    vector<Square>&options = squares;
    //case 1 : the game ends because the board is full
    if(board->isBoardFull()){
        this->printStyle->printBoard(*board);
        this->printStyle->fullBoard();
        winFlag=true;
    }
    else{
        //case 2: the game ends because both of the players has no options to move
        if((isAvailableMove(*board, this->xPlayer).empty()) &&
           (isAvailableMove(*board, this->oPlayer).empty())) {
            this->printStyle->printBoard(*board);
            this->printStyle->noOptionsToBothPlayers();
            winFlag=true;
        }
    }
    if(winFlag){
        //check who is the winner and announce it
        enum Type winner = checkWhoWins(board);
        this->printStyle->announceWhoWins(winner);
    }
    return winFlag;
}


vector<Square> DefaultLogic::isAvailableMove(Board& gameBoard, Player player){
    enum Type currentPlayer = player.getType();
    //vector that suppose to contain all the possible moves of the player
    vector<Square> squares , &options = squares;
    for(int i=1;i<gameBoard.getBoardSize()+1 ;i++){
        for(int j=1;j<gameBoard.getBoardSize()+1 ;j++){
            //when we found a square of the current player - we should check the squares around it
            if(gameBoard.getSquare(i,j)->getType() == currentPlayer){
                checkSquare(i, j, currentPlayer, options, gameBoard);
            }
        }
    }
    return options;
}


void DefaultLogic::checkSquare(int i, int j,enum Type player, vector<Square>& options, Board& gameBoard){
    //check what is the type of the enemy - 'X' or 'O'
    char enemy;
    if (player == typeX)
        enemy = typeO;
    else
        enemy = typeX;
    //check each of the directions around the square
    for(int k=0;k<NUMDIRECTIONS;k++){
        if(isAnotherSquareOfPlayerInDirection(enemy,directions[k],i,j)){
            int dx = valueOfDirection(directions[k]).first, dy = valueOfDirection(directions[k]).second,
                    currentX = i + dx,currentY = j + dy;
            //while the square is on the board limits and equals to the enemy's sign - keep checking the direction
            while ((gameBoard.isSquareInBoard(currentX,currentY)) &&
                   (gameBoard.getSquareType(currentX,currentY) == enemy)){
                currentX = currentX + valueOfDirection(directions[k]).first;
                currentY = currentY + valueOfDirection(directions[k]).second;
            }
            //check what is the reason the while loop ends: the square is free or the square is not on the board
            if(!gameBoard.isSquareInBoard(currentX,currentY)) {
                continue;
            } else {
                if ((gameBoard.getSquare(currentX,currentY)->getType() == ' ') &&
                    (!(gameBoard.getSquare(currentX,currentY)->isSquareInVector(options)))){
                    //the square is on the board and it is free, so add this option to the options list
                    options.push_back(*(gameBoard.getSquare(currentX,currentY)));
                }
            }
        }
    }
}


void DefaultLogic::makeMove(Player& currentPlayer, Board& gameBoard, int row, int col) {
    Player temp = this->xPlayer;
    Player& enemy = temp;
    //check what is the type of the enemy - 'X' or 'O'
    if (currentPlayer.getType() == typeX){
        temp = this->oPlayer;
        enemy = temp;
    }
    //change the square that the player choose to the current player sign
    gameBoard.setSquare(row, col, currentPlayer.getType());
    //change the relevant squares around the square that the current player choose

    for (int k = 0; k < 8; k++) {
        if (isAnotherSquareOfPlayerInDirection(currentPlayer.getType(), directions[k],row, col)) {
            changeSquares(currentPlayer, enemy, directions[k], gameBoard, row, col);
        }
    }
}


void DefaultLogic::changeSquares(Player& currentPlayer, Player& enemy, Direction direction, Board& gameBoard, int i, int j){
    int dx = valueOfDirection(direction).first, dy = valueOfDirection(direction).second,
            currentX = i + dx, currentY = j + valueOfDirection(direction).second;
    while((gameBoard.isSquareInBoard(currentX,currentY)) && (gameBoard.getSquareType(currentX,currentY) != currentPlayer.getType()))
    {
        if(gameBoard.getSquareType(currentX,currentY) == enemy.getType()) {
            //change the square of the enemy to the sign of the current player
            makeMove(currentPlayer, gameBoard, currentX, currentY);
        }
        currentX = currentX + dx;
        currentY = currentY + dy;
    }
}


enum Type DefaultLogic::checkWhoWins(Board *gameBoard){
    int xCounter=0, oCounter=0;
    //count the number of 'X' squares and 'O' squares in the board
    for(int i=0;i<gameBoard->getBoardSize();i++){
        for(int j=0;j<gameBoard->getBoardSize();j++){
            if(gameBoard->getSquareType(i,j) == typeX)
                xCounter++;
            else
                oCounter++;
        }
    }
    if(xCounter>oCounter)
        return typeX;
    else if (oCounter>xCounter)
        return typeO;
    else
        return typeEmpty;
}

void DefaultLogic::makeMoveAI(Board &gameBoard, Player player) {

    //AI is given a vector of possible moves.
    vector<Square> options = isAvailableMove(*this->board, player);
    if (options.empty()) {
        this->printStyle->noPossibleOptionsToCurrentPlayer(player.getType());
    } else {
        //Send to Function minMaxMoveChosen a reference of the vector,
        // receive back a pointer to the best move to play.
        Square* currentMove = minMaxMoveChosen(gameBoard, options);

        //AI play currentMove Pointer
        this->makeMove(player,gameBoard,currentMove->getX(),currentMove->getY());

        //Announce AI played move.
        this->printStyle->printPlayAI(currentMove->getX() + 1,currentMove->getY() + 1);
    }

}

//(Chooses a move to play by checking each move of the O player, to get the minimal points of the X player)
Square* DefaultLogic::minMaxMoveChosen(Board &gameBoard, vector<Square>& options){

    int min = INT16_MAX;
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
int DefaultLogic::moveWithMinimalHumanPlayerPoints(Square currentAIMove, Board &currentGameBoard) {

    Board gameboard2 = currentGameBoard;

    //Send the play to "make move" function, along with the gameBoard2 reference
    makeMove(oPlayer,gameboard2,currentAIMove.getX(),currentAIMove.getY());

    //get all possible next moves for player X.
    vector<Square> options = isAvailableMove(gameboard2, xPlayer);
    int max = INT16_MIN;
    int temp;

    for( vector<Square>::iterator it=options.begin();it!=options.end();it++){

        Board gameboard3 = gameboard2;

        //printStyle->printBoard(gameboard3);

        //Send to "make move" function, the gameBoard3 reference + the current i move.
        makeMove(xPlayer,gameboard3,it->getX(),it->getY());

        temp = playerAIPointsAdvantage(gameboard3);

        if(temp > max)
            max = temp;
    }

    //The maximum points that the User can get from his moves, according to the current AI move
    return max;

}

int DefaultLogic::playerAIPointsAdvantage(Board& gameBoard) {

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