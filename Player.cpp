/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */
#include "Player.h"

Player::Player(enum Type type) {
    this->type = type;
}


enum Type Player::getType(){
    return this->type;
}