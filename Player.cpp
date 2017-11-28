/**
 * name : Limor Levi
 * id number : 308142389
**/
#include "Player.h"

Player::Player(enum Type type) {
    this->type = type;
}


enum Type Player::getType(){
    return this->type;
}