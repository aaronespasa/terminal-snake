#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include "ncurses_display.h"

const int DOWN_ARROW = 258;
const int UP_ARROW = 259;
const int LEFT_ARROW = 260;
const int RIGHT_ARROW = 261;

void NCursesDisplay::UpdatePoints(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player) {
    std::string pointsStr = "Points: " + std::to_string(player.points);
    mvwprintw(window, 2, (int)(windowWidth / 5), pointsStr.c_str());

    wrefresh(window);
}

void NCursesDisplay::UpdateHighScore(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player) {
    int row, col;
    getyx(window, row, col);
    
    std::string highScoreStr = "High Score: " + std::to_string(player.highScore);
    mvwprintw(window, 2, 2 * (int)(windowWidth / 3), highScoreStr.c_str());
    
    wmove(gameWindow, row, col);
    
    wrefresh(window);
}

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Display the snake game on the terminal.
 * 
 */
void NCursesDisplay::Display(Player player) {
    initscr();              // start ncurses (sets up memory & clears the screen)
    noecho();               // do not print input values
    cbreak();               // terminate on CTRL + C
    start_color();          // enable color
    keypad(stdscr, TRUE);   // gets the arrow input as a single int instead of 3

    // stdscr is the default window
    int width = getmaxx(stdscr);    
    int height = getmaxy(stdscr);
    int scoreWindowHeight = 5;
    int startX = 0, startY = 0;

    WINDOW* scoreWindow = newwin(scoreWindowHeight, width, startY, startX);
    WINDOW* gameWindow = newwin(height - scoreWindowHeight - 1, width, scoreWindowHeight + 1, startX);

    refresh();          // refreshes the whole screen

    box(scoreWindow, 0, 0);
    wrefresh(scoreWindow); 

    box(gameWindow, 0 , 0);
    wrefresh(gameWindow); 
    
    UpdateHighScore(scoreWindow, gameWindow, width, player);
    UpdatePoints(scoreWindow, gameWindow, width, player);

    wmove(gameWindow, 1, 1);
    wrefresh(gameWindow);

    const int gameWindowHeight = height - scoreWindowHeight - 3;
    while(player.alive) {
        getyx(gameWindow, player.y, player.x);
        UpdatePoints(scoreWindow, gameWindow, width, player);
        wmove(gameWindow, player.y, player.x);
        wrefresh(gameWindow);

        if(kbhit()) {
            int c = getch();

            // TODO: Convert the controls into setters for the Player class
            if(c == DOWN_ARROW && player.y < gameWindowHeight) {
                player.y += 1;
            } else if (c == RIGHT_ARROW && player.x < width - 2) {
                player.x += 1;
            } else if (c == LEFT_ARROW && player.x > 1) {
                player.x -= 1;
            } else if (c == UP_ARROW && player.y > 1) {
                player.y -= 1;
            }
            wmove(gameWindow, player.y, player.x);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    // UpdateHighScore(scoreWindow, gameWindow, width, player);

    int c = getch();

    printw("%d ", c);

    getch();            // waits for user input, returns int value of that key

    endwin();           // deallocates memory and ends ncurses
}
