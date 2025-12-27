#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game_logic.h"
#include "graphics.h"

int main(void) {
    char main_field[HEIGHT][WIDTH];
    char process_field[HEIGHT][WIDTH];
    int input;

    double speed = 500;  // 500ms
    const int speed_step = 250;
    const int min_speed = 10;

    initial_distribution(main_field);

    // 1. Инициализация ncurses
    initscr();             // Инициализирует режим экрана
    cbreak();              // Отключает буферизацию ввода (чтение символа за символом)
    noecho();              // Не отображать вводимые символы
    curs_set(0);           // Скрыть курсор
    keypad(stdscr, TRUE);  // Включает поддержку функциональных клавиш (на всякий случай)

    // Очищаем экран в начале
    clear();

    while (1) {
        // 2. Логика игры
        next_generation(main_field, process_field);
        matrix_transfer(main_field, process_field);

        // 3. Отрисовка
        create_field(main_field);

        // Выводим статус скорости внизу (за пределами игрового поля)
        refresh();  // Выводим изменения на физический экран

        // 4. Управление скоростью и ввод
        // timeout(speed) заставляет getch() ждать 'speed' миллисекунд.
        // Если ничего не нажато, getch возвращает ERR.
        // Если нажато, возвращает код клавиши сразу!
        timeout(speed);

        input = getch();

        if (input != ERR) {
            if (input == ' ') {
                break;  // Выход
            } else if ((input == 'a') || (input == 'A')) {
                speed += speed_step;
            } else if ((input == 'z') || (input == 'Z')) {
                speed -= speed_step;
                if (speed < min_speed) {
                    speed = min_speed;
                }
            }
        }
    }
    endwin();
    return 0;
}
