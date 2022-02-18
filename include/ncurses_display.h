#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include "player.h"
#include "food.h"
#include <ncurses.h>

const int Y_KEY = 121;
const int N_KEY = 110;

namespace NCursesDisplay {
    void display(Player player);
    void displayPlayerElementInPosition(WINDOW* gameWindow, PlayerElement* head);
    void displayFood(WINDOW* gameWindow, Food* food, PlayerElement* head);
    void displayGameOverWindow(WINDOW* gameWindow, int windowWidth, int windowHeight);
    void clearGameWindow(WINDOW* gameWindow);
    void removeFoodIfEaten(WINDOW* gameWindow, Food& food, Player& player, int windowWidth, int windowHeight);
    void clearPlayerTailFromDisplay(WINDOW* gameWindow, PlayerElement& head, PlayerElement& tail);
    void updatePoints(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
    void updateHighScore(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player);
    void game(WINDOW* scoreWindow, WINDOW* gameWindow, int windowWidth, int windowHeight,
              Player& player, Food& food);
}

#endif // !NCURSES_DISPLAY_H