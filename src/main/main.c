#include <ncurses.h>

int main(int args, char* argv[]) {
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