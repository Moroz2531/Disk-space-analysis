#include "list.h"

Listnode* listnode_create(char* name, int type)
{
    Listnode* p = malloc(sizeof(Listnode));
    char* name_cpy = malloc(strlen(name) + 1);
    memcpy(name_cpy, name, strlen(name) + 1);

    if (p != NULL) {
        p->name = name_cpy;
        p->type = type;
        p->state = '#';
        p->size_type = 'b';
        p->next = NULL;
        p->prev = NULL;
    }

    return p;
};

Listnode* listnode_add(Listnode* list, char* name, int type)
{
    Listnode* newnode = listnode_create(name, type);
    if (newnode == NULL)
        return list;
    newnode->next = list;

    if (list != NULL) {
        list->prev = newnode;
    }
    return newnode;
};

Listdir* listdir_create(char* path)
{
    Listdir* p = malloc(sizeof(Listdir));

    if (p != NULL) {
        p->path_dir = path;
        p->size_type = 'b';
        p->next = NULL;
        p->node = NULL;
        p->prev = NULL;
    }

    return p;
};

void listdir_add(Listdir* ldir, Listdir* newdir)
{
    while (ldir->next != NULL) {
        if (strcmp(ldir->path_dir, newdir->path_dir) == 0)
            return;
        ldir = ldir->next;
    }
    ldir->next = newdir;
    newdir->prev = ldir;
};

/* освобождение памяти для всей структуры listdir */
void listdir_free(Listdir* ldir)
{
    Listdir* p = NULL;
    Listnode* n = NULL;

    while (ldir->prev != NULL)
        ldir = ldir->prev;

    for (; ldir != NULL; ldir = ldir->next) {
        if (p != NULL) {
            free(p->path_dir);
            free(p);
        }

        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
            if (n != NULL) {
                free(n->name);
                free(n);
            }
            n = ldir->node;
        }
        p = ldir;
    }
    free(p);
};

Map* map_create(Listnode* node, char* path_dir)
{
    Map* map = malloc(sizeof(Map));

    if (map != NULL) {
        map->path_dir = path_dir;
        map->node = node;
        map->next = NULL;
        map->prev = NULL;
    }
    return map;
};

void map_add(Map* map, Map* new_map)
{
    while (map->next != NULL)
        map = map->next;
    map->next = new_map;
    new_map->prev = map;
};

// добавление элементов открытого каталога в карту
// map указывает на открытый каталог
int map_add_node(Map* map, Listnode* node, char* path_dir)
{
    Map* new_map = map_create(node, path_dir);

    if (new_map != NULL) {
        Map* map_cpy = map;
        while (strcmp(map->next->path_dir, map_cpy->path_dir) != 0
               && map->next != NULL)
            map = map->next;
        Map* end_map = map->next;

        if (end_map == NULL) {
            map->next = new_map;
            new_map->prev = map;
        } else {
            Map* end_map_prev = end_map->prev;
            end_map->prev = new_map;
            new_map->next = end_map;
            new_map->prev = end_map_prev;
            end_map_prev->next = new_map;
        }
        map = map_cpy;
        return 0;
    }
    return 1;
};

void map_delete_node(Map* map, char* path_dir)
{
    if (strcmp(map->path_dir, map->next->path_dir) == 0)
        return;
    Map* map_cpy = map->next;
    while (strcmp(map_cpy->path_dir, path_dir) == 0 && map_cpy != NULL) {
        Map* map_delete = map_cpy;
        map_cpy = map_cpy->next;
        free(map_delete);
    }

    if (map_cpy == NULL)
        map->next = map_cpy;
    else {
        map->next = map_cpy;
        map_cpy->prev = map;
    }
};
