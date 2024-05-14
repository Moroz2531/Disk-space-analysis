#ifndef OPT_H
#define OPT_H

#include <pwd.h>
#include <unistd.h>

#include "parser.h"
#include "dir.h"
#include "converter.h"
#include "help.h"

void opt_only_dir(char* path);
void opt_m();
void opt_a_no_dir();
void selection_option(argv_t new_argv);

#endif