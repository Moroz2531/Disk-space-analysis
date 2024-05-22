#include <ctest.h>

#include "../src/parser.h"

CTEST(argv_parse, no_argv)
{
    const char* argv[] = {"./dse"};
    const int argc = 1;
    argv_t result = argv_parse(argc, argv);
    ASSERT_NULL(result.opt);
    ASSERT_NULL(result.dir);
}