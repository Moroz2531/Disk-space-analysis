#include "opt.h"

void opt_only_dir(char* path)
{
    Listdir* ldir = listdir_create(NULL);
    DIR* dir;
    ldir->path_dir = path;

    // заполняем в структуру содержимое указаного пути
    dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "Failed to init home directory\n");
        exit(EXIT_FAILURE);
    }
    fill_listnode(dir, ldir);
    closedir(dir);

    // увеличение связных списков и добавление каталогов с их содержимых
    Listdir* t_ldir = ldir;
    for (Listdir* mod_ldir = NULL; t_ldir != NULL; t_ldir = t_ldir->next) {
        Listnode* n = t_ldir->node;
        for (char* mod_path = NULL; n != NULL; n = n->next) {
            if (n->type == DT_DIR) {
                if (strcmp(n->name, ".") == 0 || strcmp(n->name, "..") == 0)
                    continue;

                mod_path = change_path(t_ldir->path_dir, n->name);
                if (mod_path == NULL) {
                    fprintf(stderr, "Fatal change path error!\n");
                    exit(EXIT_FAILURE);
                }
                mod_ldir = listdir_create(mod_path);
                listdir_add(t_ldir, mod_ldir);

                dir = opendir(mod_ldir->path_dir);
                fill_listnode(dir, mod_ldir);
                closedir(dir);
            }
        }
    }

    converter(ldir);
    // сразу же выводим информацию
    for (; ldir != NULL; ldir = ldir->next) {
        printf("path_dir: %s\n", ldir->path_dir);
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            printf("name: %s | size: %zu | %c | type: %d\n",
                   ldir->node->name,
                   ldir->node->byte,
                   ldir->size_type,
                   ldir->node->type);
        }
    }
    listdir_free(ldir);
}

void opt_m()
{
    Listdir* ldir = listdir_create(NULL);
    DIR* dir;
    struct passwd pw, *pw_result;
    char buffer[4096];
    int status;

    // получаем начальный каталог пользователя
    status = getpwuid_r(getuid(), &pw, buffer, sizeof(buffer), &pw_result);
    if (status != 0 || pw_result == NULL) {
        fprintf(stderr, "Failed to get home directory\n");
        exit(EXIT_FAILURE);
    }

    ldir->path_dir = pw.pw_dir;

    // заполняем в структуру содержимое корневого пути
    dir = opendir(pw.pw_dir);
    if (!dir) {
        fprintf(stderr, "Failed to init home directory\n");
        exit(EXIT_FAILURE);
    }
    fill_listnode(dir, ldir);
    closedir(dir);

    // увеличение связных списков и добавление каталогов с их содержимых
    Listdir* t_ldir = ldir;
    for (Listdir* mod_ldir = NULL; t_ldir != NULL; t_ldir = t_ldir->next) {
        Listnode* n = t_ldir->node;
        for (char* mod_path = NULL; n != NULL; n = n->next) {
            if (n->type == DT_DIR) {
                if (strcmp(n->name, ".") == 0 || strcmp(n->name, "..") == 0)
                    continue;

                mod_path = change_path(t_ldir->path_dir, n->name);
                if (mod_path == NULL) {
                    fprintf(stderr, "Fatal change path error!\n");
                    exit(EXIT_FAILURE);
                }
                mod_ldir = listdir_create(mod_path);
                listdir_add(t_ldir, mod_ldir);

                dir = opendir(mod_ldir->path_dir);
                fill_listnode(dir, mod_ldir);
                closedir(dir);
            }
        }
    }

    if (count_bytes_dir(ldir)) {
        fprintf(stderr, "Size analitic failed!\n");
        exit(EXIT_FAILURE);
    }
    // конвертация размера и вывод происходит сразу в функции opt_m
    converter(ldir);

    for (; ldir != NULL; ldir = ldir->next) {
        printf("path_dir: %s\n", ldir->path_dir);
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            printf("name: %s | size: %zu | %c | type: %d\n",
                   ldir->node->name,
                   ldir->node->byte,
                   ldir->size_type,
                   ldir->node->type);
        }
    }
    listdir_free(ldir);
}

void opt_a(char* path)
{
    Listdir* ldir = listdir_create(NULL);
    DIR* dir;
    ldir->path_dir = path;

    // заполняем в структуру содержимое указаного пути
    dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "Failed to init home directory\n");
        exit(EXIT_FAILURE);
    }
    all_fill_listnode(dir, ldir);
    closedir(dir);
    
    // увеличение связных списков и добавление каталогов с их содержимых
    Listdir* t_ldir = ldir;
    for (Listdir* mod_ldir = NULL; t_ldir != NULL; t_ldir = t_ldir->next) {
        Listnode* n = t_ldir->node;
        for (char* mod_path = NULL; n != NULL; n = n->next) {
            if (n->type == DT_DIR) {
                if (strcmp(n->name, ".") == 0 || strcmp(n->name, "..") == 0)
                    continue;

                mod_path = change_path(t_ldir->path_dir, n->name);
                if (mod_path == NULL) {
                    fprintf(stderr, "Fatal change path error!\n");
                    exit(EXIT_FAILURE);
                }
                mod_ldir = listdir_create(mod_path);
                listdir_add(t_ldir, mod_ldir);

                dir = opendir(mod_ldir->path_dir);
                fill_listnode(dir, mod_ldir);
                closedir(dir);
            }
        }
    }

    converter(ldir);
    // сразу же выводим информацию
    for (; ldir != NULL; ldir = ldir->next) {
        printf("path_dir: %s\n", ldir->path_dir);
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            printf("name: %s | size: %zu | %c | type: %d\n",
                   ldir->node->name,
                   ldir->node->byte,
                   ldir->size_type,
                   ldir->node->type);
        }
    }
    listdir_free(ldir);
}

void opt_a_no_dir()
{
    Listdir* ldir = listdir_create(NULL);

    if (all_fill_listdir(ldir)) {
        fprintf(stderr, "Error filling all objects in listdir!\n");
        exit(EXIT_FAILURE);
    }
    // конвертация размера и вывод происходит сразу в функции opt_a_no_dir
    converter(ldir);

    for (; ldir != NULL; ldir = ldir->next) {
        printf("path_dir: %s\n", ldir->path_dir);
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            printf("name: %s | size: %zu | %c | type: %d\n",
                   ldir->node->name,
                   ldir->node->byte,
                   ldir->size_type,
                   ldir->node->type);
        }
    }
    listdir_free(ldir);
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
            // '-a' передана с dir_path
            if (new_argv.dir != NULL) {
                opt_a(new_argv.dir);
                exit(EXIT_SUCCESS);
                // '-a' передана без dir_path
            } else {
                opt_a_no_dir();
                exit(EXIT_SUCCESS);
            }
        }
        // указан только путь dir_path
    } else if (new_argv.dir != NULL) {
        opt_only_dir(new_argv.dir);
        exit(EXIT_SUCCESS);
        // иначе выходим из функции
    } else {
        return;
    }
}