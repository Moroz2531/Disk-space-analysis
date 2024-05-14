#include <locale.h>
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "output.h"

#define SIZE_BUF 13

// отображение абсолютного корневого пути
void display_root_path(Listdir* ldir)
{
    int length_path = strlen(ldir->path_dir);
    wchar_t buf[length_path + 1];

    swprintf(buf, length_path + 1, L"%s", ldir->path_dir);
    mvaddstr(0, 0, "path: ");
    mvaddwstr(0, strlen("path: "), buf);
};

// отображение имен файлов
void display_listnode(Listdir* ldir)
{
    Listnode* node = ldir->node;
    for (int i = 2; node != NULL; node = node->next) {
        wchar_t buf[SIZE_BUF];
        swprintf(buf, SIZE_BUF, L"%12s", node->name);
        mvaddwstr(i++, 0, buf);
    }
};

// графика приложения: отображение разделителей и цветов
void display_delim()
{
    int cols, rows;
    getmaxyx(stdscr, rows, cols);

    for (int i = 0; i < cols; i++)
        mvaddch(1, i, '-');
};

// отображение процентного соотношения
void display_percentage(Listdir* ldir)
{
}

// отображение структуры listdir
int display_listdir(Listdir* ldir)
{
    wchar_t c;

    initscr();
    noecho();
    curs_set(0);

    setlocale(LC_ALL, "ru_RU.UTF-8");

    do {
        clear();

        display_root_path(ldir);
        display_listnode(ldir);
        display_delim();

        // перемещение курсора в начало
        move(2, 0);
        refresh();
    } while ((c = getch()) != 'q');

    endwin();
    return 0;
};
