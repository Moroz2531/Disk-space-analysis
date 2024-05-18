#ifndef OPT_H
#define OPT_H

#include "global.h"

#include "converter.h"
#include "dir.h"
#include "help.h"
#include "parser.h"

void opt_only_dir(char* path);
void opt_m();
void opt_a(char* path);
void opt_a_no_dir();
void selection_option(argv_t new_argv);

#endif
