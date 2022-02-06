#ifndef PLAYER_H
#define PLAYER_H

class Player {
    public:
        Player(int highscore = 0) {}
        int points{0};
        int x = 1;
        int y = 1;
        int highScore{0};
        bool alive{true};
};

#endif // !PLAYER_H