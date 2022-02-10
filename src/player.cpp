#include <algorithm>

#include "player.h"

PlayerElement::PlayerElement(int x, int y, int windowWidth, int windowHeight) {
    X(1, windowWidth);
    Y(1, windowHeight);
}

int PlayerElement::X() { return x; }
int PlayerElement::Y() { return y; }

void PlayerElement::X(int newX, int windowWidth) {
    if(newX > 0 && newX < windowWidth) 
        x = newX;
    else
        alive = false;
}

void PlayerElement::Y(int newY, int windowHeight) {
    if(newY > 0 && newY < windowHeight) 
        y = newY;
    else
        alive = false;
}

void Player::incrementSize(int windowWidth, int windowHeight) {
    int tailX = body.back().X();
    int tailY = body.back().Y();

    switch(direction) {
        case LEFT:
            tailX += 1;
            break;
        case RIGHT:
            tailX -= 1;
            break;
        case UP:
            tailY += 1;
            break;
        case DOWN:
            tailY -= 1;
            break;
    }

    PlayerElement newBodyElement(tailX, tailY, windowWidth, windowHeight);
    
    body.push_back(newBodyElement);
}

void Player::respawn(int windowWidth, int windowHeight) {
    body.clear();   // remove all the elements from the deque

    // TODO: The player dies when some element of it coincides with another one
    PlayerElement playerElement1(1, 2, windowWidth, windowHeight);
    body.push_front(playerElement1);

    PlayerElement playerElement2(1, 1, windowWidth, windowHeight);
    body.push_front(playerElement2);
}

void Player::move(int keyNumber, int windowWidth, int windowHeight) {
    Direction newDirection;

    std::unordered_map<int, Direction>::const_iterator keyPair = ARROW_KEYS.find(keyNumber);
    if(keyPair == ARROW_KEYS.end())
        newDirection = direction;       // move in the same direction (not an arrow key)
    else 
        newDirection = keyPair->second; // update the direction

    // get the first element to take its coordinates
    PlayerElement head = body.front();

    // get and pop the last element of the deque
    PlayerElement tail = body.back();
    body.pop_back();

    switch(newDirection) {
        case LEFT:
            tail.X(head.X()-1, windowWidth);
            tail.Y(head.Y(), windowHeight);
            body.push_front(tail);
            break;
        case RIGHT:
            tail.X(head.X()+1, windowWidth);
            tail.Y(head.Y(), windowHeight);
            body.push_front(tail);
            break;
        case UP:
            tail.X(head.X(), windowWidth);
            tail.Y(head.Y()-1, windowHeight);
            body.push_front(tail);
            break;
        case DOWN:
            tail.X(head.X(), windowWidth);
            tail.Y(head.Y()+1, windowHeight);
            body.push_front(tail);
            break;
    }

    // TODO: If the head coindices with a food, push back a playerElement
    // and remove the food from the NCursesDisplay list of foods

    // if the head is dead, then the player is also dead
    if(!body.front().alive) { alive = false; }

    // update the direction (or maintain the previous one)
    direction = newDirection;
}