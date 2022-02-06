#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include "player.h"
#include <ncurses.h>

const int Y_KEY = 121;
const int N_KEY = 110;

namespace NCursesDisplay {
    void display(Player player);
    void updatePoints(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
    void updateHighScore(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
    void game(WINDOW* scoreWindow, WINDOW* gameWindow, int windowWidth, int windowHeight,
              Player player);
}

#endif // !NCURSES_DISPLAY_H