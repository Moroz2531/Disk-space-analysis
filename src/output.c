#include "output.h"

#define SIZE_BUF 17

// отображение абсолютного корневого пути
void display_root_path(Listdir* ldir)
{
    const int length_path = strlen(ldir->path_dir);
    wchar_t buf[length_path + 1];

    swprintf(buf, length_path + 1, L"%s", ldir->path_dir);
    mvaddstr(0, 0, "path: ");
    mvaddwstr(0, strlen("path: "), buf);
};

// отображение процентного соотношения
int display_percentage(Listnode* n, int y, int x, Listdir* ldir)
{
    // сдвиг по x
    const int shift = x + 3;
    const float percentage = ((float)n->byte / ldir->byte_dir) * 100;

    mvprintw(y, shift, "%5.2f%c\t", percentage, '%');
    // обходим отображение процентного соотношения
    return shift + 6;
};

void display_size(Listnode* n, const int y, const int x)
{
    const int shift = x + 4;
    size_t byte = converter(n);

    mvprintw(y, shift, "%ld %c\t", byte, n->size_type);
}

// отображение содержимого каталога
void display_listnode(Listdir* ldir)
{
    Listnode* node = ldir->node;

    while (node->prev != NULL)
        node = node->prev;

    for (int i = 2; node != NULL; node = node->next, i++) {
        wchar_t buf[SIZE_BUF];

        swprintf(buf, SIZE_BUF, L"%16s", node->name);
        mvaddwstr(i, 0, buf);

        const int x = display_percentage(node, i, SIZE_BUF, ldir);

        display_size(node, i, x);
        if (node->type == DT_DIR)
            printw("#");
    }
};

// графика приложения: отображение разделителей, цветов и общей информации
void display_delim(Listdir* ldir)
{
    int cols, rows;
    getmaxyx(stdscr, rows, cols);

    for (int i = 0; i < cols; i++)
        mvaddch(1, i, '-');
};

// управление клавишами up, down, left, right
void movement(Listdir* ldir, wchar_t c)
{
    static int x = 0, y = 2;

    move(y, x);
    refresh();

    if (c == KEY_UP && ldir->node->prev != NULL) {
        y--;
        ldir->node = ldir->node->prev;
    } else if (c == KEY_DOWN && ldir->node->next != NULL) {
        y++;
        ldir->node = ldir->node->next;
    } else if (c == KEY_RIGHT) {
    }
    mvprintw(10, 50, "%s", ldir->node->name);
    move(y, x);
};

// отображение структуры listdir
int display_listdir(Listdir* ldir)
{
    wchar_t c = 0;

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);

    setlocale(LC_ALL, "ru_RU.UTF-8");

    do {
        clear();

        display_root_path(ldir);
        display_listnode(ldir);
        display_delim(ldir);
        movement(ldir, c);
        refresh();

    } while ((c = getch()) != 'q');

    endwin();
    return 0;
};
