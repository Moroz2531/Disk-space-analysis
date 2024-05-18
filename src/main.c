#include "converter.h"
#include "dir.h"
#include "global.h"
#include "help.h"
#include "opt.h"
#include "output.h"
#include "parser.h"

int main(int argc, char* argv[])
{
    argv_t new_argv = argv_parse(argc, argv);
    /*// опция '-h'
    if (new_argv.opt && strcmp(new_argv.opt, "-h") == 0) {
        help_draw();
        return EXIT_SUCCESS;
    }*/

    Listdir* ldir = listdir_create(NULL);
    if (fill_listdir(ldir, 1)) {
        listdir_free(ldir);
        return EXIT_FAILURE;
    }
    converter(ldir);
    // display_listdir(ldir);
    listdir_free(ldir);

    return EXIT_SUCCESS;
}
