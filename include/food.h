#ifndef FOOD_H
#define FOOD_H

#include <vector>

#include "player.h"

struct Point {
    int x;
    int y;
};

class Food {
    public:
        Food(int newWindowHeight, int newWindowWidth);

        int windowHeight();
        int windowWidth();
        void windowHeight(int newWindowHeight);
        void windowWidth(int newWindowWidth);

        void spawnFood(int number, std::deque<PlayerElement> &playerBody);
        bool isPointInsideOfPlayerOrFoods(Point& newFoodPoint, std::deque<PlayerElement>& playerBody);

        std::vector<Point> foodsMap;
    private:
        int windowHeight{1};
        int windowWidth{1};
};

#endif // !FOOD_H