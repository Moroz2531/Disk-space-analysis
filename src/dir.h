#ifndef PATH_H
#define PATH_H

int absolute_root_path(char** path);
void fill_listnode(DIR* dir, Listdir* ldir);
char* change_path(char* path, char* name);
int fill_listdir(Listdir* ldir);

#endif
