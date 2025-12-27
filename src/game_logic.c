#include <stdlib.h>
#include <time.h>
#include "game_logic.h"
#include "graphics.h"

// Случайно распределяем изначальные значени
int initial_distribution(char (*main_field)[WIDTH]) {
    srand(time(NULL));
    int random_value;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            random_value = rand() % 2;
            if (random_value == 0) {
                main_field[y][x] = LIVE;
            } else {
                main_field[y][x] = DEAD;
            }
        }
    }
    return 0;
}

// Подсчет числа живых соседей
int neighbor_count(int x, int y, char (*main_field)[WIDTH]) {
    int count = 0, neighbor_x, neighbor_y;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            neighbor_x = (x + dx + WIDTH) % WIDTH;
            neighbor_y = (y + dy + HEIGHT) % HEIGHT;

            if (main_field[neighbor_y][neighbor_x] == LIVE) {
                count++;
            }
        }
    }
    return count;
}

int next_generation(char (*main_field)[WIDTH], char (*process_field)[WIDTH]) {
    int num_neighbors;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            num_neighbors = neighbor_count(x, y, main_field);

            if (main_field[y][x] == LIVE) {
                if (num_neighbors < 2 || num_neighbors > 3) {
                    process_field[y][x] = DEAD;
                } else {
                    process_field[y][x] = LIVE;
                }
            } else {
                if (num_neighbors == 3) {
                    process_field[y][x] = LIVE;
                } else {
                    process_field[y][x] = DEAD;
                }
            }
        }
    }
    return 0;
}


// Присваим измененную матрицу нашей основной
int matrix_transfer(char (*main_field)[WIDTH], char (*process_field)[WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            main_field[y][x] = process_field[y][x];
        }
    }
    return 0;
}
