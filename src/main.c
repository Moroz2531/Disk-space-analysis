#include "converter.h"
#include "dir.h"
#include "help.h"
#include "parser.h"
#include "opt.h"

void test_output();

int main(int argc, char* argv[])
{
    argv_t new_argv = argv_parse(argc, argv);
    int ch;

    selection_option(new_argv);

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

    return EXIT_SUCCESS;
}

void test_output(WINDOW* win)
{
    Listdir* ldir = listdir_create(NULL);

    if (fill_listdir(ldir)) {
        delwin(win);
        endwin();
        fprintf(stderr, "Error filling listdir!\n");
        exit(EXIT_FAILURE);
    }

    converter(ldir);

    for (; ldir != NULL; ldir = ldir->next) {
        printw("path_dir: %s\n", ldir->path_dir);
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            printw("name: %s | size: %zu | %c | type: %d\n",
                   ldir->node->name,
                   ldir->node->byte,
                   ldir->size_type,
                   ldir->node->type);
            wrefresh(win);
        }
    }
    listdir_free(ldir);
}