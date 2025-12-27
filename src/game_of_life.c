#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game_logic.h"
#include "graphics.h"


int main(void) {

    char main_field[HEIGHT][WIDTH];
    char process_field[HEIGHT][WIDTH];
    int exit_status = 0, input;
    // Пауза на 0.5 секунды (500000 микросекунд)
    double speed = 500000;

    initial_distribution(main_field);

    while(exit_status == 0) {
        create_field(main_field);

        input = getchar();
        if ((input == 'a') || (input == 'A')) {
            speed = speed + 250000;
        } else if ((input == 'z') || (input == 'Z')) {
            speed = speed - 250000;
        } else if (input == ' ') {
            exit_status = 1;
        }

        next_generation(main_field, process_field);

        matrix_transfer(main_field, process_field);

        usleep(speed);
    }

    return 0;
}