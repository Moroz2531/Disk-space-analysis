#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    char* opt;
    char* dir;
} argv_t;

argv_t argv_parse(int argc, char* argv[]);

#endif
