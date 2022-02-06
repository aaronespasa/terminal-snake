#include "player.h"

int Player::X() { return x; }
int Player::Y() { return y; }

void Player::X(int newX, int windowWidth) {
    if(newX > 0 && newX < windowWidth) { x = newX; }
}

void Player::Y(int newY, int windowHeight) {
    if(newY > 0 && newY < windowHeight) { y = newY; }
}

void Player::move(int keyNumber, int windowWidth, int windowHeight) {
    Direction newDirection;

    std::unordered_map<int, Direction>::const_iterator keyPair = ARROW_KEYS.find(keyNumber);
    if(keyPair == ARROW_KEYS.end())
        newDirection = direction;       // move in the same direction (not an arrow key)
    else 
        newDirection = keyPair->second; // update the direction

    switch(newDirection) {
        case LEFT:
            X(X()-1, windowWidth);
            break;
        case RIGHT:
            X(X()+1, windowWidth);
            break;
        case UP:
            Y(Y()-1, windowHeight);
            break;
        case DOWN:
            Y(Y()+1, windowHeight);
            break;
    }

    // update the direction (or maintain the previous one)
    direction = newDirection;
}