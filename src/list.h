#ifndef LIST_H
#define LIST_H

#define MAX_LENGTH 256

typedef struct Listnode Listnode;
typedef struct Listdir Listdir;

typedef struct Listnode {
    char name[MAX_LENGTH];
    int type;
    Listnode* next;
} Listnode;

typedef struct Listdir {
    char* path_dir;
    Listdir* next;
    Listnode* node;
} Listdir;

Listnode* listnode_create(char name, int type);
Listnode* listnode_add(Listnode* list, char name, int type);
Listdir* listdir_create(char* path);
Listdir* listdir_add(Listdir* dir, char* path);
void listdir_init(Listdir* ldir, char* path);

#endif
