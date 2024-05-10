#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dir.h"

/* находим путь запускаемого приложения */
int absolute_root_path(char** path)
{
    if (*path != NULL)
        return 1;
    *path = getcwd(*path, 0);
    return 0;
};

/* заполняем содержимое каталога в структуру */
void fill_listnode(DIR* dir, Listdir* ldir)
{
    struct dirent* entry;

    /* проходим по каталогу и заполняем его содержимое в структуру */
    while ((entry = readdir(dir)) != NULL)
        ldir->node = listnode_add(ldir->node, entry->d_name, entry->d_type);
};

/* получаем пути других каталогов */
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

/* заполнение списка каталогов. ldir должен быть инициализирован */
int fill_listdir(Listdir* ldir)
{
    DIR* dir;
    char* path = NULL;

    if (absolute_root_path(&path))
        return 1;
    ldir->path_dir = path;

    /* заполняем в структуру содержимое корневого пути */
    dir = opendir(path);
    if (!dir)
        return 1;
    fill_listnode(dir, ldir);
    closedir(dir);

    /* увеличение связных списков и добавление каталогов с их содержимых */
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
    return 0;
};
