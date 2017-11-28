/**
 * name : Limor Levi
 * id number : 308142389
**/

#include "Square.h"

Square::Square(int x, int y, enum Type type){
    this->x = x;
    this->y = y;
    this->type = type;
}


int Square::getX(){
    return this->x;
}


int Square::getY(){
    return this->y;
}


enum Type Square::getType(){
    return this->type;
}


void Square::setType(enum Type type) {
    this->type = type;
}


bool Square::equals(Square& other){
    return ((this->getType() == other.getType()) &&
            (this->getX() == other.getX()) &&
            (this->getY() == other.getY()));
}

bool Square::isSameLocation(Square& other){
    return (((this->getX() == other.getX()) &&
            (this->getY() == other.getY())));
}

bool Square::isSquareInVector(vector<Square>& options){
    for( vector<Square>::iterator it=options.begin();it!=options.end();it++){
        if(this->equals(*it))
            return true;
    }
    return false;
}
