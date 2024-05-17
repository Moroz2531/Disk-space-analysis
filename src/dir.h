#ifndef PATH_H
#define PATH_H

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

int absolute_root_path(char** path);
int count_bytes_dir(Listdir* ldir);
int fill_listdir(Listdir* ldir);
void fill_listnode(DIR* dir, Listdir* ldir);
void all_fill_listnode(DIR* dir, Listdir* ldir);
int all_fill_listdir(Listdir* ldir);
char* change_path(char* path, char* name);

#endif
