#include <ctest.h>

#include "../src/converter.h"
#include "../src/list.h"
#include "../src/parser.h"

CTEST(argv_parse, check_no_argv)
{
    char* argv[] = {"./dse"};
    int argc = 1;
    argv_t result = argv_parse(argc, argv);
    ASSERT_NULL(result.opt);
    ASSERT_NULL(result.dir);
}

CTEST(argv_parse, check_only_option)
{
    char* argv[] = {"./dse", "-h"};
    int argc = 2;
    argv_t result = argv_parse(argc, argv);
    ASSERT_STR("-h", result.opt);
    ASSERT_NULL(result.dir);
}

CTEST(argv_parse, check_option_and_path)
{
    char* argv[] = {"./dse", "-a", "/home"};
    int argc = 3;
    argv_t result = argv_parse(argc, argv);
    ASSERT_STR("-a", result.opt);
    ASSERT_STR("/home", result.dir);
}

CTEST(argv_parse, check_only_path)
{
    char* argv[] = {"./dse", "/home"};
    int argc = 2;
    argv_t result = argv_parse(argc, argv);
    ASSERT_NULL(result.opt);
    ASSERT_STR("/home", result.dir);
}

CTEST(byte_converter, check_convert_to_bytes)
{
    size_t byte = 0;
    for (size_t i = 0; i < KB; i++, byte++)
        ASSERT_EQUAL(i, byte_converter(byte));
}

CTEST(byte_converter, check_convert_to_KB)
{
    size_t kb1 = KB;
    size_t kb2 = MB - KB;
    ASSERT_EQUAL(1, byte_converter(kb1));
    ASSERT_EQUAL(1023, byte_converter(kb2));
}

CTEST(byte_converter, check_convert_to_MB)
{
    size_t mb1 = MB;
    size_t mb2 = GB - MB;
    ASSERT_EQUAL(1, byte_converter(mb1));
    ASSERT_EQUAL(1023, byte_converter(mb2));
}

CTEST(byte_converter, check_convert_to_GB)
{
    size_t gb1 = GB;
    size_t gb2 = GB * 5;
    const size_t expect_gb2 = gb2 / GB;
    ASSERT_EQUAL(1, byte_converter(gb1));
    ASSERT_EQUAL(expect_gb2, byte_converter(gb2));
}

CTEST(type_converter, check_convert_to_byte_type)
{
    const char expect_type = 'b';
    for (size_t byte; byte < KB; byte++)
        ASSERT_EQUAL(expect_type, type_converter(byte));
}

CTEST(type_converter, check_convert_to_kb_type)
{
    const char expect_type = 'K';
    size_t kb1 = KB;
    size_t kb2 = MB - KB;
    ASSERT_EQUAL(expect_type, type_converter(kb1));
    ASSERT_EQUAL(expect_type, type_converter(kb2));
}

CTEST(type_converter, check_convert_to_mb_type)
{
    const char expect_type = 'M';
    size_t mb1 = MB;
    size_t mb2 = GB - MB;
    ASSERT_EQUAL(expect_type, type_converter(mb1));
    ASSERT_EQUAL(expect_type, type_converter(mb2));
}

CTEST(type_converter, check_convert_to_GB_type)
{
    const char expect_type = 'G';
    size_t gb1 = GB;
    size_t gb2 = GB * 5;
    ASSERT_EQUAL(expect_type, type_converter(gb1));
    ASSERT_EQUAL(expect_type, type_converter(gb2));
}

CTEST(converter, check_converter)
{
    const size_t expect_size = 3;
    const char expect_type = 'K';

    Listnode* node = listnode_create("testnode", 8);
    node->byte = 3 * KB;

    size_t actual_byte = converter(node);

    ASSERT_EQUAL(expect_size, actual_byte);
    ASSERT_EQUAL(expect_type, node->size_type);
}

CTEST(listnode_create, check_listnode_create)
{
    Listnode* node = listnode_create("testnode", 8);

    const char* expect_name = "testnode";
    const char expect_type = 8;
    const char expect_size_type = 'b';

    ASSERT_EQUAL(*expect_name, *node->name);
    ASSERT_EQUAL(expect_type, node->type);
    ASSERT_EQUAL(expect_size_type, node->size_type);
    ASSERT_NULL(node->next);
    ASSERT_NULL(node->prev);
}

CTEST(listnode_add, check_listnode_add)
{
    Listnode* node = listnode_create("testnode", 8);
    Listnode* newnode = listnode_add(node, "testadd", 8);

    const char* expect_name = "testadd";
    const char expect_type = 8;
    const char expect_size_type = 'b';
    
    ASSERT_EQUAL(*expect_name, *newnode->next->name);
    ASSERT_EQUAL(expect_type, newnode->next->type);
    ASSERT_EQUAL(expect_size_type, newnode->next->size_type);
    ASSERT_NOT_NULL(newnode->next);
    ASSERT_NOT_NULL(newnode->next->prev);
}

CTEST(listdir_create, check_lisdir_create)
{
    char* path = "testpath";
    Listdir* ldir = listdir_create(path);

    const char* expect_dir_path = path;
    const char expect_size_type = 'b';
    
    ASSERT_EQUAL(expect_dir_path, ldir->path_dir);
    ASSERT_EQUAL(expect_size_type, ldir->size_type);
    ASSERT_NULL(ldir->node);
    ASSERT_NULL(ldir->next);
    ASSERT_NULL(ldir->prev);
}

CTEST(listdir_add, check_listdir_add)
{
    char* path1 = "testpath1";
    char* path2 = "testpath2";

    Listdir* ldir = listdir_create(path1);
    Listdir* newdir = listdir_create(path2);

    listdir_add(ldir, newdir);

    ASSERT_NOT_NULL(ldir->next);
    ASSERT_NOT_NULL(ldir->next->prev);
}