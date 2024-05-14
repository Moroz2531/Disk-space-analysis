#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct Listnode Listnode;
typedef struct Listdir Listdir;

typedef struct Listnode {
    char* name;
    int type;
    size_t byte;
    Listnode* next;
} Listnode;

typedef struct Listdir {
    char* path_dir;
    size_t byte_dir;
    Listnode* node;
    Listdir* next;
    Listdir* prev;
} Listdir;

Listnode* listnode_create(char* name, int type);
Listnode* listnode_add(Listnode* list, char* name, int type);
Listdir* listdir_create(char* path);
void listdir_add(Listdir* ldir, Listdir* newdir);
void listdir_free(Listdir* ldir);

#endif
