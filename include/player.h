#ifndef PLAYER_H
#define PLAYER_H

enum Direction {LEFT, TOP, RIGHT, BOTTOM};

class Player {
    public:
        Player(int highscore = 0) {}
        int points{0};
        int x = 1;
        int y = 1;
        int highScore{0};
        bool alive{true};
        Direction direction = LEFT;
};

#endif // !PLAYER_H