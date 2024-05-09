#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "dir.h"
#include "list.h"

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
    mod_path[strlen(path)] = '\\';
    strcat(mod_path, name);
    return mod_path;
};

/* заполнение списка каталогов */
int fill_listdir(Listdir* ldir)
{
    DIR* dir;
    char* path = NULL;

    if (absolute_root_path(&path))
        return 1;
    listdir_init(ldir, path);

    /* заполняем в структуру содержимое корневого пути */
    dir = opendir(path);
    fill_listnode(dir, ldir);
    closedir(dir);

    /* увеличение связных списков и добавление каталогов с их содержимых */
    for (Listdir* mod_ldir = NULL; ldir != NULL; ldir = ldir->next) {
        Listnode* n = ldir->node;
        for (char* mod_path = NULL; n != NULL; n = n->next) {
            if (n->type == DT_DIR) {
                if (strcmp(n->name, ".") == 0 || strcmp(n->name, "..") == 0)
                    continue;

                mod_path = change_path(ldir->path_dir, n->name);
                if (mod_path == NULL) {
                    free(path);
                    return 1;
                }
                mod_ldir = listdir_add(ldir, mod_path);
                dir = opendir(mod_path);
                fill_listnode(dir, mod_ldir);
                closedir(dir);
            }
        }
    }
    free(path);
    return 0;
};
