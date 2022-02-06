#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include "ncurses_display.h"

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
    nodelay(stdscr, TRUE);  // avoids waiting for the input

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

    const int gameWindowHeight = height - scoreWindowHeight - 2;
    while(player.alive) {
        UpdatePoints(scoreWindow, gameWindow, width, player);
        wmove(gameWindow, player.Y(), player.X());
        wrefresh(gameWindow);

        int c = getch();

        player.move(c, width - 1, gameWindowHeight);
        wmove(gameWindow, player.Y(), player.X());

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // UpdateHighScore(scoreWindow, gameWindow, width, player);

    endwin();           // deallocates memory and ends ncurses
}