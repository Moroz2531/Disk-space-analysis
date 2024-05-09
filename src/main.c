#include "parser.h"
#include "help.h"

int main(int argc, char *argv[]) {
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
    
    while ((ch = getch()) != 'q') {}

    delwin(win);
    endwin();

    return 0;
}