#include "parser.h"

argv_t argv_parse(int argc, char *argv[]) {
    argv_t new_argv = {NULL, NULL};

    if (argc < 2)
        return new_argv;
    
    if (argc > 3) {
        fprintf(stderr, "Используйте: %s [option] [dir_path]\n", argv[0]);
        exit(1);
    }

    if (argv[1][0] == '-') {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-m") == 0) {
            new_argv.opt = argv[1];

            if (argc == 3) {
                fprintf(stderr, "Опции '%s' не допускают указание пути\n", argv[1]);
                exit(1);
            }
        } else if (strcmp(argv[1], "-a") == 0) {
            new_argv.opt = argv[1];

            if (argc == 3) {
                new_argv.dir = argv[2];
            }
        } else {
            fprintf(stderr, "Неизвестная опция: '%s'\n", argv[1]);
            exit(1);
        }
    } else {
        new_argv.dir = argv[1];
    }

    if (new_argv.dir != NULL) {
        struct stat st;
        if (stat(new_argv.dir, &st) != 0 || !S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Директория %s не существует или недоступна\n", new_argv.dir);
            exit(1);
        }
    }

    return new_argv;
}