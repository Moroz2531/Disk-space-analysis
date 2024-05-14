#include "opt.h"

void opt_m()
{
    struct passwd pw, *pw_result;
    char buffer[4096];
    int status;

    // получаем начальный каталог пользователя
    status = getpwuid_r(getuid(), &pw, buffer, sizeof(buffer), &pw_result);
    if (status != 0 || pw_result == NULL) {
        fprintf(stderr, "Failed to get home directory\n");
        exit(EXIT_FAILURE);
    }

    printf("Home directory: %s\n", pw.pw_dir);
}

void selection_option(argv_t new_argv)
{
    if (new_argv.opt != NULL) {
        // опция '-h'
        if (strcmp(new_argv.opt, "-h") == 0) {
            help_draw();
            exit(EXIT_SUCCESS);
            // опция '-m'
        } else if (strcmp(new_argv.opt, "-m") == 0) {
            opt_m();
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