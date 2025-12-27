#include "graphics.h"
#include <ncurses.h>

int create_field(char (*main_field)[WIDTH]) {

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mvaddch(y, x, main_field[y][x]);
        }
    }
    
    return 0;
}
