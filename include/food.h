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

        int getWindowHeight();
        int getWindowWidth();
        void setWindowHeight(int newWindowHeight);
        void setWindowWidth(int newWindowWidth);

        void spawnFood(int number, std::deque<PlayerElement> &playerBody);
        void clearFoodAndSpawn(int number, std::deque<PlayerElement> &playerBody);
        bool isPointInsideOfPlayerOrFoods(Point& newFoodPoint, std::deque<PlayerElement>& playerBody);

        std::vector<Point> foodsMap;
        std::string displayIcon{"@"};
    private:
        int windowHeight{1};
        int windowWidth{1};
};

#endif // !FOOD_H