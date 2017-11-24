/**
 * name : Limor Levi
 * id number : 308142389
**/

#ifndef SQUARE_H_
#define SQUARE_H_
#include <iostream>
#include <vector>

//An enum that signifies the type of character that appears in the square, X/O or empty square.
enum Type { typeX, typeO, typeEmpty};

using namespace std;

class Square {

public :
    /**
     * @name : Square
     * @parameters : the location of the square and its type
     * @return : the function creates new instance of square
     **/
    Square(int x, int y, enum Type type);

    /**
     * @name : getX
     * @parameters : no parameters
     * @return : the x value of the location of the square
     **/
    int getX();

    /**
     * @name : getY
     * @parameters : no parameters
     * @return : the y value of the location of the square
     **/
    int getY();

    /**
     * @name : getType
     * @parameters : no parameters
     * @return : the type of the square
     **/
    enum Type getType();

    /**
     * @name : setType
     * @parameters : the new type of the square
     * @return : the function changes the type of the square
     **/
    void setType(enum Type type);

    /**
     * @name : equals
     * @parameters : other square
     * @return : true if the squares are equal or false otherwise
     **/
    bool equals(Square& other);

    /**
     * @name : isSquareInVector
     * @parameters : square and vector of squares
     * @return : the function returns true if the square exsist in the vector or false otherwise
     **/
    bool isSquareInVector(vector<Square>& options);

private :
    int x;
    int y;
    enum Type type;

};
#endif /* SQUARE_H_ */