#include <random> 

#include "food.h"

Food::Food(int newWindowHeight, int newWindowWidth) {
    setWindowHeight(newWindowHeight);
    setWindowWidth(newWindowWidth);
}

int Food::getWindowHeight() { return windowHeight; }
int Food::getWindowWidth() { return windowWidth; }

void Food::setWindowHeight(int newWindowHeight) {
    if(newWindowHeight > 0) windowHeight = newWindowHeight;
}
void Food::setWindowWidth(int newWindowWidth) {
    if(newWindowWidth > 0) windowWidth = newWindowWidth;
}

int randint(int lowerBound, int upperBound) { 
    std::random_device rd;    
    std::mt19937 range(rd());
    std::uniform_int_distribution<int> uni(lowerBound, upperBound); 

    int randInteger = uni(range);

    return randInteger;
}

bool comparePlayerPoints(PlayerElement* playerEl, Point* newFoodPoint) {
    return playerEl->X() == newFoodPoint->x && playerEl->Y() == newFoodPoint->y;
}

bool compareFoodPoints(Point* foodPoint, Point* newFoodPoint) {
    return foodPoint->x == newFoodPoint->x && foodPoint->y == newFoodPoint->y;
}

bool Food::isPointInsideOfPlayerOrFoods(Point* newFoodPoint, std::deque<PlayerElement>* playerBody) {
    for(PlayerElement playerEl : *playerBody) {
        if(comparePlayerPoints(&playerEl, newFoodPoint)) return false;
    }

    for(Point foodPoint : foodsMap) {
        if(compareFoodPoints(&foodPoint, newFoodPoint)) return false;
    }

    return true;
}

// TODO: Solve isPointInsideOfPlayerOrFoods method
void Food::spawnFood(int number, std::deque<PlayerElement>* playerBody) {
    // get where's the player to avoid putting food over it
    for(int i=0; i < number; i++) {
        Point newFoodPoint;
        // do {
            newFoodPoint.x = randint(1, getWindowWidth());
            newFoodPoint.y = randint(1, getWindowHeight());
        // } while(isPointInsideOfPlayerOrFoods(&newFoodPoint, playerBody));

        foodsMap.push_back(newFoodPoint);
    }
}

void Food::clearFoodAndSpawn(int number, std::deque<PlayerElement>* playerBody) {
    foodsMap.clear();

    spawnFood(number, playerBody);
}
