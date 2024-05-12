#include "help.h"

void help_draw()
{
    initscr();
    curs_set(0);
    noecho();

    box(stdscr, 0, 0);

    mvprintw(2, 2, "Руководство по использованию приложения dse");
    mvprintw(4, 4, "Возможные опции:");
    mvprintw(5, 6, "-h\tОтображает руководство");
    mvprintw(
            6,
            6,
            "-m\tАнализ использования места на диске из начального каталога");
    mvprintw(
            7,
            6,
            "-a [dir_path]\tАнализ использования места на диске, включая "
            "скрытые объекты");
    mvprintw(9, 4, "Использование:");
    mvprintw(10, 6, "./dse [option] [dir_path]");
    mvprintw(12, 4, "Нажмите 'q' для выхода из справки");
    refresh();

    char ch;
    while ((ch = getch()) != 'q') {
    }

    endwin();
}