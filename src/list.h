#ifndef LIST_H
#define LIST_H

typedef struct Listnode Listnode;
typedef struct Listdir Listdir;

typedef struct Listnode {
    char* name;
    int type;
    Listnode* next;
} Listnode;

typedef struct Listdir {
    char* path_dir;
    Listdir* next;
    Listnode* node;
} Listdir;

Listnode* listnode_create(char* name, int type);
Listnode* listnode_add(Listnode* list, char* name, int type);
Listdir* listdir_create(char* path);
void listdir_add(Listdir* ldir, Listdir* newdir);

#endif
