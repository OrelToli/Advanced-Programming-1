/**
 * name : Limor Levi
 * id number : 308142389
**/

#ifndef BOARD_H_
#define BOARD_H_

using namespace std;

#include "Square.h"
#include <iostream>
#include <stdlib.h>

class Board {

public :
    /**
     * @name : Board
     * @parameters : the size of the board
     * @return : the function creates new instance of Board object
     **/
    Board(int size);

    /**
     * Copies a board into a new board and allocates a new array for the board, usually for simulation.
     * @name: Copy constructor
     * @param oldBoardToCopy - The board to recreate.
     */
    Board(Board& oldBoardToCopy);


    /**
     * @name : getBoardSize
     * @parameters : no parameters
     * @return : the function returns the board size
     **/
    int getBoardSize();

    /**
     * @name : getSquare
     * @parameters : the row and the col of the square
     * @return : the function returns the square
     **/
    enum Type getSquareType(int i, int j) ;

    /**
     * @name : setSquare
     * @parameters : the location of the square and the new square
     * @return : the function changes the square
     **/
    void setSquare(int i,int j, enum Type newSquare);

    /**
     * @name : isBoardFull()
     * @parameters : no parameters
     * @return : true if the board is full or false otherwise
     **/
    bool isBoardFull();

    /**
     * @name : isSquareInBoard
     * @parameters : the square location
     * @return : true if the square is in the limits of the board or false otherwise
     **/
    bool isSquareInBoard(int row,int col);

    /**
      * @name : getSquare
      * @parameters : the square location
      * @return : the function returns the square in the specific location
      **/
    Square* getSquare(int i,int j) ;

    /**
    * @name : ~Board
    * @parameters : no parameters
    * @return : the function frees the allocated memory
    **/
    ~Board();

private :
    int boardSize ;
    Square*** board;
};
#endif /* BOARD_H_ */