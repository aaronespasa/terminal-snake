#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include "player.h"
#include <ncurses.h>

namespace NCursesDisplay {
    void Display(Player player);
    void UpdatePoints(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
    void UpdateHighScore(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
}

#endif // !NCURSES_DISPLAY_H