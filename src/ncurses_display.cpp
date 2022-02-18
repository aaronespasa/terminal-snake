#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include "ncurses_display.h"

#define PLAYER_COLOR_PAIR 1
#define GRASS_COLOR_PAIR 2
#define FOOD_COLOR_PAIR 3
#define WHITE_BOX_COLOR_PAIR 4

void NCursesDisplay::updatePoints(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player) {
    // TODO: Modify points whenever the player eats a food
    std::string pointsStr = "Points: " + std::to_string(player.points);
    mvwprintw(window, 2, (int)(windowWidth / 5), pointsStr.c_str());
    wrefresh(window);
}

void NCursesDisplay::updateHighScore(WINDOW* window, WINDOW* gameWindow, int windowWidth, Player player) {
    if(player.points > player.highScore) player.highScore = player.points;

    std::string highScoreStr = "High Score: " + std::to_string(player.highScore);
        mvwprintw(window, 2, 2 * (int)(windowWidth / 3), highScoreStr.c_str());
        wrefresh(window);

        wmove(gameWindow, player.body.front().Y(), player.body.front().X());
        wrefresh(gameWindow);    
}

void NCursesDisplay::removeFoodIfEaten(WINDOW* gameWindow, Food& food, Player& player,
                                       int windowWidth, int windowHeight) {
    for(int i=0; i < food.foodsMap.size(); i++) {
            if(player.body.front().X() == food.foodsMap[i].x &&
               player.body.front().Y() == food.foodsMap[i].y) {
                   food.foodsMap.erase(food.foodsMap.begin() + i);

                   player.points += 1;
                   player.incrementSize(windowWidth, windowHeight);

                   food.spawnFood(1, &player.body);
                   displayFood(gameWindow, &food, &player.body.front());
            }
    }
}

void NCursesDisplay::displayGameOverWindow(WINDOW* gameWindow, int windowWidth, int windowHeight) {
    mvwprintw(gameWindow, windowHeight/2, windowWidth/2 - 10, "GAME OVER");
}

void NCursesDisplay::game(WINDOW* scoreWindow, WINDOW* gameWindow, int windowWidth,
                          int windowHeight, Player& player, Food& food) {
    nodelay(stdscr, TRUE);  // avoids waiting for the input
    int difficulty = 3;     // 1 (easy), 2 (medium), 3 (hard)
    
    while(player.alive) {
        removeFoodIfEaten(gameWindow, food, player, windowWidth, windowHeight);
        updatePoints(scoreWindow, gameWindow, windowWidth, player);
        displayPlayerElementInPosition(gameWindow, &player.body.front());
        wrefresh(gameWindow);
        
        clearPlayerTailFromDisplay(gameWindow, player.body.front(), player.body.back());

        int c = getch();

        player.move(c, windowWidth - 1, windowHeight);
        wmove(gameWindow, player.body.front().Y(), player.body.front().X());

        std::this_thread::sleep_for(std::chrono::milliseconds(300 / difficulty));
    }
    food.foodsMap.clear();

    updateHighScore(scoreWindow, gameWindow, windowWidth, player);

    nodelay(stdscr, FALSE);  // waits for the input

    displayGameOverWindow(gameWindow, windowWidth, windowHeight);
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
                                                    PlayerElement* head) {
    wattron(gameWindow, COLOR_PAIR(PLAYER_COLOR_PAIR));
    mvwprintw(gameWindow, head->Y(), head->X(), head->displayIcon.c_str());
    wattroff(gameWindow, COLOR_PAIR(PLAYER_COLOR_PAIR));
}

void NCursesDisplay::displayFood(WINDOW* gameWindow, Food* food, PlayerElement* head) {
    for(Point foodPoint : food->foodsMap) {
        wattron(gameWindow, COLOR_PAIR(FOOD_COLOR_PAIR));
        mvwprintw(gameWindow, foodPoint.y, foodPoint.x, food->displayIcon.c_str());
        wattroff(gameWindow, COLOR_PAIR(FOOD_COLOR_PAIR));
    }

    wmove(gameWindow, head->Y(), head->X());
}

void NCursesDisplay::clearGameWindow(WINDOW* gameWindow) {
    wclear(gameWindow);
    wbkgd(gameWindow, COLOR_PAIR(GRASS_COLOR_PAIR));
    
    wattron(gameWindow, COLOR_PAIR(WHITE_BOX_COLOR_PAIR));
    box(gameWindow, 0 , 0);
    wattroff(gameWindow, COLOR_PAIR(WHITE_BOX_COLOR_PAIR));

    wrefresh(gameWindow);
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
    keypad(stdscr, TRUE);   // gets the arrow input as a single int instead of 3
    curs_set(0);

    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support colors :(\n");
        exit(1);
    }
    start_color();          // enable color

    const int BASE_COLOR = COLOR_GREEN;
    init_pair(PLAYER_COLOR_PAIR, COLOR_MAGENTA, BASE_COLOR);
    init_pair(GRASS_COLOR_PAIR, BASE_COLOR, BASE_COLOR);
    init_pair(FOOD_COLOR_PAIR, COLOR_RED, BASE_COLOR);
    init_pair(WHITE_BOX_COLOR_PAIR, COLOR_WHITE, BASE_COLOR);

    // stdscr is the default window
    int width = getmaxx(stdscr);    
    int height = getmaxy(stdscr);
    int scoreWindowHeight = 5;
    const int gameWindowHeight = height - scoreWindowHeight - 2;
    int startX = 0, startY = 0;

    WINDOW* scoreWindow = newwin(scoreWindowHeight, width, startY, startX);
    WINDOW* gameWindow = newwin(height - scoreWindowHeight - 1, width, scoreWindowHeight + 1, startX);

    refresh();          // refreshes the whole screen

    // TODO: Add colors
    box(scoreWindow, 0, 0);
    wrefresh(scoreWindow); 
    
    updateHighScore(scoreWindow, gameWindow, width, player);
    updatePoints(scoreWindow, gameWindow, width, player);

    Food food(gameWindowHeight-1, width-1);
    bool userWantToContinuePlaying = true;

    while(userWantToContinuePlaying) {
        clearGameWindow(gameWindow);
        // move the player to the initial point and restart default values
        player.respawn(width, gameWindowHeight);

        displayPlayerElementInPosition(gameWindow, &player.body.front());
        player.direction = RIGHT;
        player.points = 0;
        player.alive = true;

        food.spawnFood(1, &player.body);
        displayFood(gameWindow, &food, &player.body.front());

        wrefresh(gameWindow);

        game(scoreWindow, gameWindow, width, gameWindowHeight, player, food);

        int c = getch();
        
        while(c != Y_KEY && c != N_KEY) {
            c = getch();
        }

        if(c == N_KEY) userWantToContinuePlaying = false;
    }    

    endwin();           // deallocates memory and ends ncurses
}