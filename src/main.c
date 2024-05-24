#include "global.h"

#include "dir.h"
#include "help.h"
#include "opt.h"
#include "output.h"
#include "parser.h"

int main(int argc, char* argv[])
{
    argv_t new_argv = argv_parse(argc, argv);
    
    selection_option(new_argv);

    Listdir* ldir = listdir_create(NULL);
    if (fill_listdir(ldir, 0)) {
        listdir_free(ldir);
        return EXIT_FAILURE;
    }
    display_listdir(ldir);
    listdir_free(ldir);

    return EXIT_SUCCESS;
}
