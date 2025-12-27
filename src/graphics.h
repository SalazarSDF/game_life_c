#ifndef GRAPHICS_H
#define GRAPHICS_H

// Размеры игрового поля
#define WIDTH 80
#define HEIGHT 25

// Системные указатели
#define CURSOR_TO_TOP_LEFT "\033[H"
#define CLEAR_SCREEN "\033[2J"

// Символы для живых и мертвых клеток
#define LIVE 'O'
#define DEAD '.'

int create_field(char (*main_field)[WIDTH]);

#endif