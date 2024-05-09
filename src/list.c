#include <stdlib.h>
#include <string.h>

#include "list.h"

Listnode* listnode_create(char name, int type)
{
    Listnode* p = malloc(sizeof(Listnode));
    if (p != NULL) {
        strcpy(p->name, name);
        p->type = type;
        p->next = NULL;
    }
    return p;
};

Listnode* listnode_add(Listnode* list, char name, int type)
{
    Listnode* newnode = listnode_createnode(name, type);
    if (newnode != NULL) {
        newnode->next = list;
        return newnode;
    }
    return list;
};

Listdir* listdir_create(char* path)
{
    Listdir* p = malloc(sizeof(Listdir));
    if (p != NULL) {
        p->path_dir = path;
        p->next = NULL;
        p->node = NULL;
    }
    return p;
};

Listdir* listdir_add(Listdir* ldir, char* path)
{
    Listdir* newdir = listdir_create(path);
    while (ldir->next != NULL)
        ldir = ldir->next;
    ldir->next = newdir;
    return newdir;
};

void listdir_init(Listdir* ldir, char* path)
{
    ldir->next = NULL;
    ldir->node = NULL;
    ldir->path_dir = path;
};

void listdir_free(Listdir* ldir)
{
    for (; ldir != NULL; ldir = ldir->next) {
        for (; ldir)
    }
};
