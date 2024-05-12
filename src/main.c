#include "dir.h"
#include "help.h"
#include "parser.h"

void test_output();

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
    noecho();

    WINDOW* win = newwin(20, 40, 5, 10);
    box(win, 0, 0);
    wrefresh(win);

    test_output(win);

    while ((ch = getch()) != 'q') {
    }

    delwin(win);
    endwin();

    return 0;
}

void test_output(WINDOW* win)
{
    Listdir* ldir = listdir_create(NULL);

    if (fill_listdir(ldir)) {
        delwin(win);
        endwin();
        fprintf(stderr, "Ошибка заполнения списка директории!\n");
        exit(1);
    }

    for (; ldir != NULL; ldir = ldir->next) {
        printw("path_dir: %s\n", ldir->path_dir);
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            printw("name: %s | size: %zu | type: %d\n",
                   ldir->node->name,
                   ldir->node->byte,
                   ldir->node->type);
            wrefresh(win);
        }
    }
    listdir_free(ldir);
}