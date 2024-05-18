#include "converter.h"

size_t byte_converter(size_t byte)
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
};

char type_converter(size_t byte)
{
    // менее 1 кб - возвращаем тип байт
    if (byte < KB)
        return 'b';
    // меньше 1 мб - возвращаем тип кб
    if (byte < MB)
        return 'K';
    // меньше 1 гб - возвращаем тип мб
    if (byte < GB)
        return 'M';
    // больше или равен 1 гб - возвращаем тип гб
    if (byte >= GB)
        return 'G';

    return 'b';
};

void converter(Listdir* ldir)
{
    // идём в конец списка
    while (ldir->next != NULL)
        ldir = ldir->next;

    // проходимся от конца до самого начала
    while (ldir != NULL) {
        for (Listnode* node = ldir->node; node != NULL; node = node->next) {
            if (node->type == DT_DIR) {
                char* path_find_dir = change_path(ldir->path_dir, node->name);
                if (path_find_dir == NULL) {
                    fprintf(stderr, "Byte convertation failed!\n");
                    return;
                }

                for (Listdir* t_ldir = ldir;; t_ldir = t_ldir->next) {
                    if (strcmp(t_ldir->path_dir, path_find_dir) == 0) {
                        node->size_type = type_converter(t_ldir->byte_dir);
                        node->byte = byte_converter(t_ldir->byte_dir);
                        break;
                    }
                }
                free(path_find_dir);
            } else {
                node->size_type = type_converter(node->byte);
                node->byte = byte_converter(node->byte);
            }
        }
        ldir->size_type = type_converter(ldir->byte_dir);
        ldir->byte_dir = byte_converter(ldir->byte_dir);
        ldir = ldir->prev;
    }
};
