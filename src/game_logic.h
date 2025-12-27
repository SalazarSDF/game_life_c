#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Размеры игрового поля
#define WIDTH 80
#define HEIGHT 25

int initial_distribution(char (*main_field)[WIDTH]);
int neighbor_count(int x, int y, char (*main_field)[WIDTH]);
int next_generation(char (*main_field)[WIDTH], char (*process_field)[WIDTH]);
int matrix_transfer(char (*main_field)[WIDTH], char (*process_field)[WIDTH]);

#endif