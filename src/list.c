#include <stdlib.h>
#include <string.h>

#include "list.h"

Listnode* listnode_create(char* name, int type)
{
    Listnode* p = malloc(sizeof(Listnode));
    char* name_cpy = malloc(strlen(name) + 1);
    memcpy(name_cpy, name, strlen(name) + 1);
    if (p != NULL) {
        p->name = name_cpy;
        p->type = type;
        p->next = NULL;
    }
    return p;
};

Listnode* listnode_add(Listnode* list, char* name, int type)
{
    Listnode* newnode = listnode_create(name, type);
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

void listdir_add(Listdir* ldir, Listdir* newdir)
{
    while (ldir->next != NULL)
        ldir = ldir->next;
    ldir->next = newdir;
};

/*void listdir_free(Listdir* ldir)
{
    for (; ldir != NULL; ldir = ldir->next) {
        for (; ldir->node != NULL; ldir->node = ldir->node->next) {
        }
    }
};*/
