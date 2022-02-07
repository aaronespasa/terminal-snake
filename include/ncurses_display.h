#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include "player.h"
#include <ncurses.h>

const int Y_KEY = 121;
const int N_KEY = 110;

// TODO: Spawn foods randomly (avoiding the user position) and create a vector
// containing the multiple foods
struct Food {
    int x;
    int y;
};

// TODO: Display the created foods
namespace NCursesDisplay {
    void display(Player player);
    void displayPlayerElementInPosition(WINDOW* gameWindow, PlayerElement &head);
    void clearPlayerTailFromDisplay(WINDOW* gameWindow, PlayerElement &head, PlayerElement &tail);
    void updatePoints(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
    void updateHighScore(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
    void game(WINDOW* scoreWindow, WINDOW* gameWindow, int windowWidth, int windowHeight,
              Player player);
}

#endif // !NCURSES_DISPLAY_H