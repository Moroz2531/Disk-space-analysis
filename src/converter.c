#include "converter.h"

size_t converter(size_t byte)
{
    // менее 1 кб - возвращаем число байт
    if (byte < KB)
        return byte;
    // меньше 1 мб - возвращаем число кб
    if (byte < MB)
        return byte / KB;
    // меньше 1 гб - возвращаем число мб
    if (byte < GB)
        return byte / MB;
    // больше или равен 1 гб - возвращаем число гб
    if (byte >= GB)
        return byte / GB;

    return -1;
}