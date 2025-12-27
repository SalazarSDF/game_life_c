#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>

// Размеры игрового поля
#define WIDTH 80
#define HEIGHT 25

// Символы для живых и мертвых клеток
#define LIVE 'O'
#define DEAD '.'

int create_field(char (*main_field)[WIDTH]);

#endif
