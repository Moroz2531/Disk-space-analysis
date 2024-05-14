#include "opt.h"

void selection_option(argv_t new_argv)
{
    if (new_argv.opt != NULL) {
        // опция '-h'
        if (strcmp(new_argv.opt, "-h") == 0) {
            help_draw();
            exit(EXIT_SUCCESS);
            // опция '-m'
        } else if (strcmp(new_argv.opt, "-m") == 0) {
            fprintf(stderr, "Will be available very soon!\n");
            exit(EXIT_SUCCESS);
            // опция '-a'
        } else if (strcmp(new_argv.opt, "-a") == 0) {
            // '-a' передан с dir_path
            if (new_argv.dir != NULL) {
                fprintf(stderr, "Will be available very soon!\n");
                printf("Path: %s\n", new_argv.dir);
                exit(EXIT_SUCCESS);
                // '-a' передан без dir_path
            } else {
                fprintf(stderr, "Will be available very soon!\n");
                exit(EXIT_SUCCESS);
            }
        }
        // указан только путь dir_path
    } else if (new_argv.dir != NULL) {
        fprintf(stderr, "Will be available very soon!\n");
        printf("Path: %s\n", new_argv.dir);
        exit(EXIT_SUCCESS);
        // иначе выходим из функции
    } else {
        return;
    }
}