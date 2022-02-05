#include "player.h"
#include "ncurses_display.h"

int main(int argc, char const *argv[]) {
    Player player;
    NCursesDisplay::Display(player);
}