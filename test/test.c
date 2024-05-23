#include <ctest.h>

#include "../src/parser.h"
#include "../src/converter.h"

CTEST(argv_parse, no_argv)
{
    char* argv[] = {"./dse"};
    int argc = 1;
    argv_t result = argv_parse(argc, argv);
    ASSERT_NULL(result.opt);
    ASSERT_NULL(result.dir);
}

CTEST(argv_parse, only_option)
{
    char* argv[] = {"./dse", "-h"};
    int argc = 2;
    argv_t result = argv_parse(argc, argv);
    ASSERT_STR("-h", result.opt);
    ASSERT_NULL(result.dir);
}

CTEST(argv_parse, option_and_path)
{
    char* argv[] = {"./dse", "-a", "/home"};
    int argc = 3;
    argv_t result = argv_parse(argc, argv);
    ASSERT_STR("-a", result.opt);
    ASSERT_STR("/home", result.dir);
}

CTEST(argv_parse, only_path)
{
    char* argv[] = {"./dse", "/home"};
    int argc = 2;
    argv_t result = argv_parse(argc, argv);
    ASSERT_NULL(result.opt);
    ASSERT_STR("/home", result.dir);
}