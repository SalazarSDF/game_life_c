#include <stdio.h>
#include "graphics.h"

int create_field(char (*main_field)[WIDTH]) {

    printf(CLEAR_SCREEN);
    printf(CURSOR_TO_TOP_LEFT);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            putchar(main_field[y][x]);
        }
        printf("\n");
    }
    
    return 0;
}