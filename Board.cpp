/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */
#include "Board.h"

Board::Board(int size) {
    this->boardSize = size;
    //dynamic allocation of the board
    this->board = new Square **[size + 1];
    for (int i = 0; i < size + 1; i++) {
        this->board[i] = new Square *[size + 1];
    }
    for (int i = 0; i < size + 1; i++)
        for (int j = 0; j < size + 1; j++) {
            this->board[i][j] = new Square(i, j, typeX);
        }
    //associate specific squares to the players
    int location1 = size / 2 - 1, location2 = size / 2;
    setSquare(location1, location1, typeO);
    setSquare(location2, location2, typeO);
    setSquare(location1, location2, typeX);
    setSquare(location2, location1, typeX);
    setSquare(5, 4, typeEmpty);

}

Board::Board(Board& oldBoardToCopy) {

    this->boardSize = oldBoardToCopy.getBoardSize();
    //dynamic allocation of the board
    this->board = new Square **[this->boardSize + 1];
    for (int i = 0; i < this->boardSize + 1; i++) {
        this->board[i] = new Square *[this->boardSize + 1];
    }
    for (int i = 0; i < this->boardSize + 1; i++)
        for (int j = 0; j < this->boardSize + 1; j++) {
            this->board[i][j] = new Square(i, j, oldBoardToCopy.getSquareType(i,j));
        }

}


int Board::getBoardSize() {
    return this->boardSize;
}


void Board::setSquare(int i, int j, enum Type newSquare) {
    (*getSquare(i, j)).setType(newSquare);
}


enum Type Board::getSquareType(int i, int j) {
    return (this->board[i][j])->getType();
}


Square *Board::getSquare(int i, int j) {
    return this->board[i][j];
}


Board::~Board() {
    for (int i = 0; i < boardSize + 1; i++) {
        for (int j = 0; j < boardSize + 1; j++) {
            delete board[i][j];
        }
    }
    for (int i = 0; i < boardSize + 1; i++) {
        delete[] board[i];
    }
    delete[] board;
}


bool Board::isBoardFull() {
    for (int i = 0; i < boardSize + 1; i++) {
        for (int j = 0; j < boardSize + 1; j++) {
            if (board[i][j]->getType() == typeEmpty)
                return false;
        }
    }
    return true;
}


bool Board::isSquareInBoard(int row, int col) {
    if ((row >= this->boardSize) || (row < 0) || (col >= this->boardSize) || (col < 0)) {
        return false;
    }
    return true;
}

void Board::resetBoard(){
    for (int i = 0; i < this->boardSize + 1; i++)
        for (int j = 0; j < this->boardSize + 1; j++) {
            this->board[i][j] = new Square(i, j, typeEmpty);
        }
}


bool Board::equals(Board* otherBoard){
    for (int i = 0; i < this->boardSize + 1; i++)
        for (int j = 0; j < this->boardSize + 1; j++) {
            if(!this->board[i][j]->equals(*otherBoard->getSquare(i,j))){
                return false;
            }
        }
    return true;
}







