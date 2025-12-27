#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h> 
#include <fcntl.h> 

#include <sys/select.h>
#include <sys/time.h>

#include "game_logic.h"
#include "graphics.h"

// Структура для сохранения оригинальных настроек терминала
struct termios orig_termios;

// Функция для восстановления настроек терминала при выходе
void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios); }

// Функция включения неканонического (неблокирующего) режима
void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);  // Гарантируем восстановление настроек при выходе

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);  // Отключаем буферизацию строк и эхо-вывод
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    // Делаем stdin неблокирующим, чтобы getchar не ждал нажатия
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
}

int main(void) {
    char main_field[HEIGHT][WIDTH];
    char process_field[HEIGHT][WIDTH];
    int input;
    // Пауза на 0.5 секунды (500000 микросекунд)
    double speed = 500000;
    const double speed_step = 250000;

    const double min_speed = 10000;

    initial_distribution(main_field);
    enable_raw_mode();  // Включаем режим управления

    printf(CLEAR_SCREEN);
    
    while (1) {
        create_field(main_field);
        next_generation(main_field, process_field);
        matrix_transfer(main_field, process_field);
        printf("SPEED: %lf", speed);

        // Настройка таймера для select
        struct timeval tv;
        // Преобразуем микросекунды в секунды и микросекунды для struct timeval
        tv.tv_sec = (time_t)(speed / 1000000);
        tv.tv_usec = (suseconds_t)((long long)speed % 1000000);

        // Настраиваем отслеживание клавиатуры (stdin)
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        // Ждем ввода ИЛИ истечения времени
        // select возвращает количество готовых дескрипторов или 0 при таймауте
        int activity = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

        if(activity > 0){
            input = getchar();
            if (input != EOF) {
                if (input == ' ') {
                    break;
                } else if ((input == 'a') || (input == 'A')) {
                    speed += speed_step;
                } else if ((input == 'z') || (input == 'Z')) {
                    speed -= speed_step;
                    if (speed < min_speed) {
                        speed = min_speed;
                    }
                }
            }
    
    
            usleep(speed);
        }
    }

    return 0;
}
