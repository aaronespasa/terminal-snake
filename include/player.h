#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <string>
#include <deque>

enum Direction {LEFT, UP, RIGHT, DOWN};

const std::unordered_map<int, Direction> ARROW_KEYS {
    {258, DOWN},
    {259, UP},
    {260, LEFT},
    {261, RIGHT}
};

class PlayerElement {
    public:
        PlayerElement(int x, int y, int windowWidth, int windowHeight);
        int X();
        int Y();
        void X(int newX, int windowWidth);
        void Y(int newY, int windowHeight);

        std::string displayIcon{"#"};
        bool alive{true};
    private:
        int x{1};
        int y{1};
};

class Player {
    public:
        std::deque<PlayerElement> body;

        void respawn(int windowWidth, int windowHeight);
        void move(int keyNumber, int windowWidth, int windowHeight);     

        int points{0};
        int highScore{0};
        bool alive{true};
        Direction direction{RIGHT};
};

#endif // !PLAYER_H