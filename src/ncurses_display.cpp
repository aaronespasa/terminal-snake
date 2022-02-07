#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include "ncurses_display.h"

void NCursesDisplay::updatePoints(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player) {
    std::string pointsStr = "Points: " + std::to_string(player.points);
    mvwprintw(window, 2, (int)(windowWidth / 5), pointsStr.c_str());
    wrefresh(window);
}

void NCursesDisplay::updateHighScore(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player) {
    // updates the highscore
    std::string highScoreStr = "High Score: " + std::to_string(player.highScore);
    mvwprintw(window, 2, 2 * (int)(windowWidth / 3), highScoreStr.c_str());
    wrefresh(window);

    wmove(gameWindow, player.body.front().Y(), player.body.front().X());
    wrefresh(gameWindow);     
}

void NCursesDisplay::game(WINDOW* scoreWindow, WINDOW* gameWindow, int windowWidth,
                          int windowHeight, Player player) {
    nodelay(stdscr, TRUE);  // avoids waiting for the input
    int difficulty = 3;     // 1 (easy), 2 (medium), 3 (hard)
    
    while(player.alive) {
        updatePoints(scoreWindow, gameWindow, windowWidth, player);
        displayPlayerElementInPosition(gameWindow, player.body.front());
        wrefresh(gameWindow);
        
        clearPlayerTailFromDisplay(gameWindow, player.body.front(), player.body.back());

        int c = getch();

        player.move(c, windowWidth - 1, windowHeight);
        wmove(gameWindow, player.body.front().Y(), player.body.front().X());

        std::this_thread::sleep_for(std::chrono::milliseconds(300 / difficulty));
    }

    updateHighScore(scoreWindow, gameWindow, windowWidth, player);

    nodelay(stdscr, FALSE);  // waits for the input

    wprintw(gameWindow, "You have lost :(");
    wrefresh(gameWindow);
}

void NCursesDisplay::clearPlayerTailFromDisplay(WINDOW* gameWindow,
                                                PlayerElement &head,
                                                PlayerElement &tail) {
    wmove(gameWindow, tail.Y(), tail.X());
    wprintw(gameWindow, " ");
    wmove(gameWindow, head.Y(), head.X());
}

void NCursesDisplay::displayPlayerElementInPosition(WINDOW* gameWindow,
                                                    PlayerElement &head) {
    mvwprintw(gameWindow, head.Y(), head.X(), head.displayIcon.c_str());
}

/**
 * @brief Display the snake game on the terminal.
 * 
 */
void NCursesDisplay::display(Player player) {
    setlocale(LC_ALL, "");
    initscr();              // start ncurses (sets up memory & clears the screen)
    noecho();               // do not print input values
    cbreak();               // terminate on CTRL + C
    start_color();          // enable color
    keypad(stdscr, TRUE);   // gets the arrow input as a single int instead of 3
    curs_set(0);

    // stdscr is the default window
    int width = getmaxx(stdscr);    
    int height = getmaxy(stdscr);
    int scoreWindowHeight = 5;
    const int gameWindowHeight = height - scoreWindowHeight - 2;
    int startX = 0, startY = 0;

    WINDOW* scoreWindow = newwin(scoreWindowHeight, width, startY, startX);
    WINDOW* gameWindow = newwin(height - scoreWindowHeight - 1, width, scoreWindowHeight + 1, startX);

    refresh();          // refreshes the whole screen

    box(scoreWindow, 0, 0);
    wrefresh(scoreWindow); 

    box(gameWindow, 0 , 0);
    wrefresh(gameWindow); 
    
    updateHighScore(scoreWindow, gameWindow, width, player);
    updatePoints(scoreWindow, gameWindow, width, player);

    bool userWantToContinuePlaying = true;

    while(userWantToContinuePlaying) {
        // move the player to the initial point and restart default values
        player.respawn(width, gameWindowHeight);

        displayPlayerElementInPosition(gameWindow, player.body.front());
        player.direction = RIGHT;
        player.points = 0;
        player.alive = true;
        wrefresh(gameWindow);

        game(scoreWindow, gameWindow, width, gameWindowHeight, player);

        int c = getch();
        
        while(c != Y_KEY && c != N_KEY) {
            c = getch();
        }

        if(c == N_KEY) userWantToContinuePlaying = false;
    }    

    endwin();           // deallocates memory and ends ncurses
}