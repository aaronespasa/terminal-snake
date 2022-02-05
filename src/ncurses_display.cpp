#include "ncurses_display.h"

/**
 * @brief Display the snake game on the terminal.
 * 
 */
void NCursesDisplay::Display() {
    initscr();          // start ncurses (sets up memory & clears the screen)
    noecho();           // do not print input values
    cbreak();           // terminate on CTRL + C
    start_color();      // enable color

    // refreshes the screen to match what's in memory
    refresh();

    // waits for user input, returns int value of that key
    getch();

    endwin();   // deallocates memory and ends ncurses
}