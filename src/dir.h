#ifndef PATH_H
#define PATH_H

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

int absolute_root_path(char** path);
int count_bytes_dir(Listdir* ldir);
int fill_listdir(Listdir* ldir, int flag_hidden_dir);
int fill_listnode(DIR* dir, Listdir* ldir, int flag_hidden_dir);
void swap(Listnode* node1, Listnode* node2);
void sort_items(Listnode* node, int dir_type);
void sort_items_listnode(Listdir* ldir);
char* change_path(char* path, char* name);

#endif
