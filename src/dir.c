#include "dir.h"

// определяет текущий рабочий каталог
int absolute_root_path(char** path)
{
    if (*path != NULL)
        return 1;
    *path = getcwd(*path, 0);
    return 0;
};

void fill_listnode(DIR* dir, Listdir* ldir)
{
    struct dirent* entry;
    struct stat file_stat;

    // проходим по каталогу и заполняем его содержимое в структуру
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;

        // получаем информацию о файле или каталоге
        char* full_path = change_path(ldir->path_dir, entry->d_name);
        if (stat(full_path, &file_stat) == 0) {
            ldir->node = listnode_add(ldir->node, entry->d_name, entry->d_type);
            ldir->node->byte = file_stat.st_size; // сохраняем размер объекта
        }
        free(full_path);
    }
};

// получаем пути других каталогов
char* change_path(char* path, char* name)
{
    char* mod_path = malloc(strlen(path) + strlen(name) + 2);
    if (mod_path == NULL)
        return NULL;
    memcpy(mod_path, path, strlen(path) + 1);
    mod_path[strlen(path)] = '/';
    memcpy(&mod_path[strlen(path) + 1], name, strlen(name) + 1);
    return mod_path;
};

// получение байтов каталога и запись в структуру
int count_bytes_dir(Listdir* ldir)
{
    // доходим до конца связного списка
    while (ldir->next != NULL)
        ldir = ldir->next;

    // с конца связного списка идем к началу списка
    // вместе с этим заполняем поле byte_dir
    while (ldir != NULL) {
        size_t count_byte = 0;
        // проходим по содержимому каталога и подсчитываем байты
        for (Listnode* node = ldir->node; node != NULL; node = node->next) {
            if (node->type == DT_DIR) {
                char* path_find_dir = change_path(ldir->path_dir, node->name);
                if (path_find_dir == NULL)
                    return 1;

                for (Listdir* t_ldir = ldir;; t_ldir = t_ldir->next) {
                    if (strcmp(t_ldir->path_dir, path_find_dir) == 0) {
                        node->byte = t_ldir->byte_dir;
                        count_byte += t_ldir->byte_dir;
                        break;
                    }
                }
                free(path_find_dir);
            } else
                count_byte += node->byte;
        }
        ldir->byte_dir = count_byte;
        ldir = ldir->prev;
    }
    return 0;
};

// заполнение списка каталогов. ldir должен быть инициализирован
int fill_listdir(Listdir* ldir)
{
    DIR* dir;
    char* path = NULL;

    if (absolute_root_path(&path))
        return 1;
    ldir->path_dir = path;

    // заполняем в структуру содержимое корневого пути
    dir = opendir(path);
    if (!dir)
        return 1;
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
                if (mod_path == NULL)
                    return 1;
                mod_ldir = listdir_create(mod_path);
                listdir_add(t_ldir, mod_ldir);

                dir = opendir(mod_ldir->path_dir);
                fill_listnode(dir, mod_ldir);
                closedir(dir);
            }
        }
    }
    if (count_bytes_dir(ldir))
        return 1;
    return 0;
};
