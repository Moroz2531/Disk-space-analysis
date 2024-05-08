#include "parser.h"
#include <ncurses.h>

int main(int argc, char *argv[]) {
    argv_t new_argv = argv_parse(argc, argv);

    // Инициализация библиотеки ncurses
    initscr();

    // Создание нового окна размера 20x40
    // с координатами левого верхнего угла (5, 10)
    WINDOW* win = newwin(20, 40, 5, 10);
    box(win, 0, 0);
    wrefresh(win);

    // Ожидание нажатия клавиши q для выхода
    int ch;
    while ((ch = getch()) != 'q')

    // Очистка и завершение работы библиотеки ncurses
    delwin(win);
    endwin();

    return 0;
}