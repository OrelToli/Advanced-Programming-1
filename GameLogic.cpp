/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */
#include <limits>
#include <sstream>
#include "GameLogic.h"



using namespace std;

GameLogic:: GameLogic(Board* board, Player& xPlayer, Player& oPlayer,Print* printStyle) :
        board(board), xPlayer(xPlayer), oPlayer(oPlayer) , printStyle(printStyle)
{
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


pair<int,int> GameLogic::valueOfDirection(Direction d) {
    switch(d)
    {
        case RIGHT : return make_pair(0, 1);
        case RIGHTDOWN : return make_pair(1, 1);
        case DOWN : return make_pair(1, 0);
        case LEFTDOWN : return make_pair(1,-1);
        case LEFT : return make_pair(0,-1);
        case LEFTUP : return make_pair(-1,-1);
        case UP : return make_pair(-1,0);
        case RIGHTUP : return make_pair(-1,1);
    }
};


bool GameLogic::isAnotherSquareOfPlayerInDirection(enum Type player, Direction direction, int i, int j){
    int dx = valueOfDirection(direction).first, dy = valueOfDirection(direction).second,
            currentX = i + dx, currentY = j + dy;
    while(this->board->isSquareInBoard(currentX,currentY)){
        if(this->board->getSquareType(currentX,currentY) == player)
            return true;
        else{
            currentX = currentX + dx;
            currentY = currentY + dy;
        }
    }
    return false;
}

void GameLogic::getMoveAndPlayIt(Board& gameBoard, Player& currentPlayer, vector<Square>& options) {
    int row, col;
    char dummy;
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
    makeMove(currentPlayer, gameBoard, row - 1, col - 1);
    lastRow = row;
    lastCol = col;
}



enum gameOverOrNot GameLogic::gameOver(){
    gameOverOrNot currentGame = gameContinues;
    //vector that suppose to contain all the possible moves of the player
    vector<Square> squares;
    vector<Square>&options = squares;
    //case 1 : the game ends because the board is full
    if(board->isBoardFull()) {
        currentGame = gameOverFullBoard;
        lastRow = END_GAME_FLAG;
        lastCol = END_GAME_FLAG;
    }
        //case 2: the game ends because both of the players has no options to move
    else if((isAvailableMove(*board, this->xPlayer).empty()) &&
       (isAvailableMove(*board, this->oPlayer).empty())) {
        currentGame = gameOverNoMoreMoves;
        lastRow = END_GAME_FLAG;
        lastCol = END_GAME_FLAG;
    }
    return currentGame;
}


vector<Square> GameLogic::isAvailableMove(Board& gameBoard, Player player){
    enum Type currentPlayer = player.getType();
    //vector that suppose to contain all the possible moves of the player
    vector<Square> squares , &options = squares;
    for(int i=0;i<gameBoard.getBoardSize() ;i++){
        for(int j=0;j<gameBoard.getBoardSize() ;j++){
            //when we found a square of the current player - we should check the squares around it
            if(gameBoard.getSquare(i,j)->getType() == currentPlayer){
                checkSquare(i, j, currentPlayer, options, gameBoard);
            }
        }
    }
    return options;
}

void GameLogic::humanMakeMove(Board& gameBoard, Player& player, Print* printStyle, int* arrayLocation) {
    //check what is the optional moves for the current player
    vector<Square> options = isAvailableMove(gameBoard, player);
    if (options.empty()) {
        printStyle->noPossibleOptionsToCurrentPlayer(player.getType());
        if(gameOver() == gameContinues) {
            lastRow = -1;
            lastCol = -1;

        } else {

            lastRow = -2;
            lastCol = -2;
        }

        arrayLocation[0] = lastRow;
        arrayLocation[1] = lastCol;


    } else {

    getMoveAndPlayIt(gameBoard, player, options);
    options.clear();
    arrayLocation[0] = lastRow;
    arrayLocation[1] = lastCol;
    printStyle->boardAfterUser(player, lastRow, lastCol);
    }
}


void GameLogic::checkSquare(int i, int j,enum Type player, vector<Square>& options, Board& gameBoard){
    //check what is the type of the enemy - 'X' or 'O'
    Type enemy;
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
                if ((gameBoard.getSquare(currentX,currentY)->getType() == typeEmpty) &&
                    (!(gameBoard.getSquare(currentX,currentY)->isSquareInVector(options)))){
                    //the square is on the board and it is free, so add this option to the options list
                    options.push_back(*(gameBoard.getSquare(currentX,currentY)));
                }
            }
        }
    }
}


void GameLogic::makeMove(Player& currentPlayer, Board& gameBoard, int row, int col) {
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


void GameLogic::changeSquares(Player& currentPlayer, Player& enemy, Direction direction, Board& gameBoard, int i, int j){
    int dx = valueOfDirection(direction).first, dy = valueOfDirection(direction).second,
            currentX = i + dx, currentY = j + valueOfDirection(direction).second;
    while((gameBoard.isSquareInBoard(currentX,currentY)) && (gameBoard.getSquareType(currentX,currentY) != currentPlayer.getType()))
    {
        if(gameBoard.getSquareType(currentX,currentY) == enemy.getType()) {
            //change the square of the enemy to the sign of the current player
            gameBoard.setSquare(currentX, currentY, currentPlayer.getType());
        }
        currentX = currentX + dx;
        currentY = currentY + dy;
    }
}


enum Type GameLogic::checkWhoWins(Board *gameBoard){
    int xCounter=0, oCounter=0;
    //count the number of 'X' squares and 'O' squares in the board
    for(int i=0;i<gameBoard->getBoardSize();i++){
        for(int j=0;j<gameBoard->getBoardSize();j++){
            if(gameBoard->getSquareType(i,j) == typeX)
                xCounter++;
            else if (gameBoard->getSquareType(i,j) == typeO)
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

