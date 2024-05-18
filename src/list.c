#include "list.h"

Listnode* listnode_create(char* name, int type)
{
    Listnode* p = malloc(sizeof(Listnode));
    char* name_cpy = malloc(strlen(name) + 1);
    memcpy(name_cpy, name, strlen(name) + 1);

    if (p != NULL) {
        p->name = name_cpy;
        p->type = type;
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
    while (ldir->next != NULL)
        ldir = ldir->next;
    ldir->next = newdir;
    newdir->prev = ldir;
};

/* освобождение памяти для всей структуры listdir */
void listdir_free(Listdir* ldir)
{
    Listdir* p = NULL;
    Listnode* n = NULL;

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
    free(n);
};
