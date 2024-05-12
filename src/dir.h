#ifndef PATH_H
#define PATH_H

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

int absolute_root_path(char** path);
void fill_listnode(DIR* dir, Listdir* ldir);
char* change_path(char* path, char* name);
int fill_listdir(Listdir* ldir);

#endif