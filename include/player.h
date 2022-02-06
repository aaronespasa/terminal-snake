#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>

enum Direction {LEFT, UP, RIGHT, DOWN};

const std::unordered_map<int, Direction> ARROW_KEYS {
    {258, DOWN},
    {259, UP},
    {260, LEFT},
    {261, RIGHT}
};

class Player {
    public:
        Player(int highscore = 0) {}

        int X();
        int Y();
        void X(int newX, int windowWidth);
        void Y(int newY, int windowHeight);

        void move(int keyNumber, int windowWidth, int windowHeight);     

        int points{0};
        int highScore{0};
        bool alive{true};
        Direction direction = RIGHT;
    private:
        int x = 1;
        int y = 1;
};

#endif // !PLAYER_H