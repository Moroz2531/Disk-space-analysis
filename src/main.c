#include "dir.h"
#include "help.h"
#include "parser.h"

int main(int argc, char* argv[])
{
    argv_t new_argv = argv_parse(argc, argv);
    int ch;
    // опция '-h'
    if (new_argv.opt && strcmp(new_argv.opt, "-h") == 0) {
        help_draw();
        return 0;
    }

    initscr();
    curs_set(0);

    // создание нового окна размера 20x40
    // с координатами левого верхнего угла (5, 10)
    WINDOW* win = newwin(20, 40, 5, 10);
    box(win, 0, 0);
    wrefresh(win);

    while ((ch = getch()) != 'q') {
    }

    delwin(win);
    endwin();

    /* тестовый вывод приложения для наглядности проделанной работы */
    /* разрешено удаление данной части для дальнейшего решения */
    Listdir* ldir = listdir_create(NULL);
    if (fill_listdir(ldir)) {
        printf("Error fill listdir!\n");
        return 1;
    }
    for (; ldir != NULL; ldir = ldir->next) {
        printf("path_dir: %s\n", ldir->path_dir);
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            printf("name: %s | type: %d\n", ldir->node->name, ldir->node->type);
        }
    }

    return 0;
}
