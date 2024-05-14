#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include "dir.h"

#define KB 1024 // 2^10 byte
#define MB 1048576 // 2^20 byte
#define GB 1073741824 // 2^30 byte

size_t byte_converter(size_t byte);
char type_converter(size_t byte);
void converter(Listdir* ldir);

#endif