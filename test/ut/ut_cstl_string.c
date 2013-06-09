#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cstl_basic_string_iterator.h"
#include "cstl/cstl_basic_string_private.h"
#include "cstl/cstl_basic_string.h"
#include "cstl/cstl_string_iterator.h"
#include "cstl/cstl_string_private.h"
#include "cstl/cstl_string.h"

#include "ut_def.h"
#include "ut_cstl_string.h"

UT_SUIT_DEFINATION(cstl_string, create_string)

/*
 * test create_string
 */
UT_CASE_DEFINATION(create_string)
void test_create_string__successfully(void** state)
{
    string_t* pstr_string = create_string();
    assert_true(pstr_string != NULL);
    string_destroy(pstr_string);
}

/*
 * test string_init
 */
UT_CASE_DEFINATION(string_init)
void test_string_init__null_string_container(void** state)
{
    expect_assert_failure(string_init(NULL));
}

void test_string_init__non_created(void** state)
{
    string_t str;
    expect_assert_failure(string_init(&str));
}

void test_string_init__successfully(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

/*
 * test string_init_char
 */
UT_CASE_DEFINATION(string_init_char)
void test_string_init_char__null(void** state)
{
    expect_assert_failure(string_init_char(NULL, 5, 'a'));
}

void test_string_init_char__non_created(void** state)
{
    string_t str;
    expect_assert_failure(string_init_char(&str, 5, 'a'));
}

void test_string_init_char__empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_char(pstr_string, 0, 'a');
    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_init_char__non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_char(pstr_string, 5, 'a');
    assert_true(string_size(pstr_string) == 5);
    assert_true(strcmp(string_c_str(pstr_string), "aaaaa") == 0);

    string_destroy(pstr_string);
}

/*
 * test string_init_cstr
 */
UT_CASE_DEFINATION(string_init_cstr)
void test_string_init_cstr__null(void** state)
{
    expect_assert_failure(string_init_cstr(NULL, "abc"));
}

void test_string_init_cstr__non_created(void** state)
{
    string_t str;
    expect_assert_failure(string_init_cstr(&str, "abc"));
}

void test_string_init_cstr__null_cstr(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_init_cstr(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_init_cstr__empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "");
    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_init_cstr__non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "abc");
    assert_true(string_size(pstr_string) == 3);
    assert_true(strcmp(string_c_str(pstr_string), "abc") == 0);

    string_destroy(pstr_string);
}

void test_string_init_cstr__truncate_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "\0abc");
    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_init_cstr__truncate_non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "abc\0xxxxx");
    assert_true(string_size(pstr_string) == 3);
    assert_true(strcmp(string_c_str(pstr_string), "abc") == 0);

    string_destroy(pstr_string);
}

/*
 * test string_init_subcstr
 */
UT_CASE_DEFINATION(string_init_subcstr)
void test_string_init_subcstr__null_container(void** state)
{
    expect_assert_failure(string_init_subcstr(NULL, "abcdef", 0));
}

void test_string_init_subcstr__non_created_container(void** state)
{
    string_t str;
    expect_assert_failure(string_init_subcstr(&str, "abcdefg", NPOS));
}

void test_string_init_subcstr__null_cstr(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_init_subcstr(pstr_string, NULL, NPOS));

    string_destroy(pstr_string);
}

void test_string_init_subcstr__cstr_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_subcstr(pstr_string, "", 0);
    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_init_subcstr__length_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_subcstr(pstr_string, "abc", 0);
    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_init_subcstr__non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_subcstr(pstr_string, "abc", 1);
    assert_true(string_size(pstr_string) == 1);
    assert_true(strcmp(string_c_str(pstr_string), "a") == 0);

    string_destroy(pstr_string);
}

void test_string_init_subcstr__all(void** state)
{
    string_t* pstr_string = create_string();

    string_init_subcstr(pstr_string, "abc", 3);
    assert_true(string_size(pstr_string) == 3);
    assert_true(strcmp(string_c_str(pstr_string), "abc") == 0);

    string_destroy(pstr_string);
}

void test_string_init_subcstr__truncate_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_subcstr(pstr_string, "\0abc", 4);
    assert_true(string_size(pstr_string) == 4);

    string_destroy(pstr_string);
}

void test_string_init_subcstr__truncate_non_empty(void** state)
{
    string_t* pstr_string = create_string();
    char elems[] = {'a', 'b', 'c', '\0', 'x', 'x', 'x', 'x', 'x'};

    string_init_subcstr(pstr_string, "abc\0xxxxx", 9);
    assert_true(string_size(pstr_string) == 9);
    assert_true(memcmp(string_c_str(pstr_string), elems, 9) == 0);

    string_destroy(pstr_string);
}

/*
 * test string_init_copy
 */
UT_CASE_DEFINATION(string_init_copy)
void test_string_init_copy__null_dest(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_init_copy(NULL, pstr_string));

    string_destroy(pstr_string);
}

void test_string_init_copy__null_src(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_init_copy(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_init_copy__non_create_dest(void** state)
{
    string_t str;
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_init_copy(&str, pstr_string));

    string_destroy(pstr_string);
}

void test_string_init_copy__non_inited_src(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();

    expect_assert_failure(string_init_copy(pstr_dest, pstr_src));

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy__empty(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init(pstr_src);

    string_init_copy(pstr_dest, pstr_src);
    assert_true(string_size(pstr_dest) == string_size(pstr_src));

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy__non_empty(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefg");

    string_init_copy(pstr_dest, pstr_src);
    assert_true(string_size(pstr_dest) == string_size(pstr_src));
    assert_true(strcmp(string_c_str(pstr_dest), "abcdefg") == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

/*
 * test string_init_copy_substring
 */
UT_CASE_DEFINATION(string_init_copy_substring)
void test_string_init_copy_substring__null_dest(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abc");

    expect_assert_failure(string_init_copy_substring(NULL, pstr_string, 0, NPOS));

    string_destroy(pstr_string);
}

void test_string_init_copy_substring__null_src(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_init_copy_substring(pstr_string, NULL, 0, NPOS));

    string_destroy(pstr_string);
}

void test_string_init_copy_substring__non_create_dest(void** state)
{
    string_t str;
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abc");

    expect_assert_failure(string_init_copy_substring(&str, pstr_string, 0, NPOS));

    string_destroy(pstr_string);
}

void test_string_init_copy_substring__non_inited_src(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();

    expect_assert_failure(string_init_copy_substring(pstr_dest, pstr_src, 0, NPOS));

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_begin_empty(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abc");

    string_init_copy_substring(pstr_dest, pstr_src, 0, 0);
    assert_true(string_size(pstr_dest) == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_begin_non_empty(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, 0, 3);
    assert_true(string_size(pstr_dest) == 3);
    assert_true(strcmp(string_c_str(pstr_dest), "abc") == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_begin_length(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, 0, string_length(pstr_src));
    assert_true(string_size(pstr_dest) == string_length(pstr_src));
    assert_true(strcmp(string_c_str(pstr_dest), "abcdefgh") == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_begin_npos(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, 0, NPOS);
    assert_true(string_size(pstr_dest) == string_length(pstr_src));
    assert_true(strcmp(string_c_str(pstr_dest), "abcdefgh") == 0);


    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_middle_empty(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, 3, 0);
    assert_true(string_size(pstr_dest) == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_middle_non_empty(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, 3, 4);
    assert_true(string_size(pstr_dest) == 4);
    assert_true(strcmp(string_c_str(pstr_dest), "defg") == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_middle_length(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, 3, string_length(pstr_src)-3);
    assert_true(string_size(pstr_dest) == 5);
    assert_true(strcmp(string_c_str(pstr_dest), "defgh") == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_middle_npos(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, 3, NPOS);
    assert_true(string_size(pstr_dest) == 5);
    assert_true(strcmp(string_c_str(pstr_dest), "defgh") == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_end(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    string_init_copy_substring(pstr_dest, pstr_src, string_length(pstr_src), NPOS);
    assert_true(string_size(pstr_dest) == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_substring__src_non_empty_npos(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_init_cstr(pstr_src, "abcdefgh");

    expect_assert_failure(string_init_copy_substring(pstr_dest, pstr_src, NPOS, NPOS));

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

/*
 * test string_init_copy_range
 */
UT_CASE_DEFINATION(string_init_copy_range)
void test_string_init_copy_range__null_dest(void** state)
{
    string_t* pstr = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pstr);
    it_begin = string_begin(pstr);
    it_end = string_end(pstr);

    expect_assert_failure(string_init_copy_range(NULL, it_begin, it_end));

    string_destroy(pstr);
}

void test_string_init_copy_range__invalid_begin_iterator(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pstr_src);
    it_begin = string_begin(pstr_src);
    it_end = string_end(pstr_src);

    it_begin._t_iteratortype = 23445;
    expect_assert_failure(string_init_copy_range(pstr_dest, it_begin, it_end));

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_range__invalid_end_iterator(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pstr_src);
    it_begin = string_begin(pstr_src);
    it_end = string_end(pstr_src);

    it_end._t_containertype = 9999;
    expect_assert_failure(string_init_copy_range(pstr_dest, it_begin, it_end));

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_range__invalid_range(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_cstr(pstr_src, "abcdefg");
    it_begin = string_begin(pstr_src);
    it_end = string_end(pstr_src);

    expect_assert_failure(string_init_copy_range(pstr_dest, it_end, it_begin));

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_range__empty_range(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_cstr(pstr_src, "abcdefg");
    it_begin = string_begin(pstr_src);
    it_end = string_end(pstr_src);

    string_init_copy_range(pstr_dest, it_begin, it_begin);
    assert_true(string_size(pstr_dest) == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

void test_string_init_copy_range__not_empty_range(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_cstr(pstr_src, "abcdefghijklmn");
    it_begin = iterator_next_n(string_begin(pstr_src), 3);
    it_end = iterator_next_n(it_begin, 5);

    string_init_copy_range(pstr_dest, it_begin, it_end);
    assert_true(string_size(pstr_dest) == iterator_distance(it_begin, it_end));
    assert_true(strcmp(string_c_str(pstr_dest), "defgh") == 0);

    string_destroy(pstr_dest);
    string_destroy(pstr_src);
}

/*
 * test string_destroy
 */
UT_CASE_DEFINATION(string_destroy)
void test_string_destroy__null_string_container(void** state)
{
    expect_assert_failure(string_destroy(NULL));
}

void test_string_destroy__non_created(void** state)
{
    string_t str;

    expect_assert_failure(string_destroy(&str));
}

void test_string_destroy__created_non_inited(void** state)
{
    string_t* pstr_string = create_string();

    string_destroy(pstr_string);
}

void test_string_destroy__inited_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    string_destroy(pstr_string);
}

void test_string_destroy__inited_non_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abcdefg");

    string_destroy(pstr_string);
}

/*
 * test string_c_str
 */
UT_CASE_DEFINATION(string_c_str)
void test_string_c_str__null_container(void** state)
{
    expect_assert_failure(string_c_str(NULL));
}

void test_string_c_str__non_inited_container(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_c_str(pstr_string));

    string_destroy(pstr_string);
}

void test_string_c_str__empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init(pstr_string);
    assert_true(strcmp(string_c_str(pstr_string), "") == 0);

    string_destroy(pstr_string);
}

void test_string_c_str__non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "abcdefg");
    assert_true(strcmp(string_c_str(pstr_string), "abcdefg") == 0);

    string_destroy(pstr_string);
}

/*
 * test string_data
 */
UT_CASE_DEFINATION(string_data)
void test_string_data__null_container(void** state)
{
    expect_assert_failure(string_data(NULL));
}

void test_string_data__non_inited_container(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_data(pstr_string));

    string_destroy(pstr_string);
}

void test_string_data__empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init(pstr_string);
    assert_true(strcmp(string_data(pstr_string), "") == 0);

    string_destroy(pstr_string);
}

void test_string_data__non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "abcdefg");
    assert_true(strcmp(string_data(pstr_string), "abcdefg") == 0);

    string_destroy(pstr_string);
}

/*
 * test string_copy
 */
UT_CASE_DEFINATION(string_copy)
void test_string_copy__null_container(void** state)
{
    char buffer[10];
    expect_assert_failure(string_copy(NULL, buffer, 0, 0));
}

void test_string_copy__non_inited_container(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[10];

    expect_assert_failure(string_copy(pstr_string, buffer, 0, 0));

    string_destroy(pstr_string);
}

void test_string_copy__null_buffer(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abcdefg");

    expect_assert_failure(string_copy(pstr_string, NULL, 0, 0));

    string_destroy(pstr_string);
}

void test_string_copy__invalid_position(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[10];
    string_init_cstr(pstr_string, "abcdefg");

    expect_assert_failure(string_copy(pstr_string, buffer, 0, 100));

    string_destroy(pstr_string);
}

void test_string_copy__begin_empty(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[10] = {'\0'};
    size_t t_size = 0;
    string_init_cstr(pstr_string, "abcdefg");

    t_size = string_copy(pstr_string, buffer, 0, 0);
    assert_true(t_size == 0);
    assert_true(strcmp(buffer, "") == 0);

    string_destroy(pstr_string);
}

void test_string_copy__begin_non_empty(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[10] = {'\0'};
    size_t t_size = 0;

    string_init_cstr(pstr_string, "abcdefg");
    t_size = string_copy(pstr_string, buffer, 4, 0);
    assert_true(t_size == 4);
    assert_true(strcmp(buffer, "abcd") == 0);

    string_destroy(pstr_string);
}

void test_string_copy__begin_length(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[20] = {'\0'};
    size_t t_size = 0;

    string_init_cstr(pstr_string, "abcdefg");

    t_size = string_copy(pstr_string, buffer, 10, 0);
    assert_true(t_size == 7);
    assert_true(strcmp(buffer, "abcdefg") == 0);

    string_destroy(pstr_string);
}

void test_string_copy__begin_npos(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[20] = "xxxxxxxxxx";
    size_t t_size = 0;
    string_init_cstr(pstr_string, "abcdefg");

    t_size = string_copy(pstr_string, buffer, NPOS, 0);
    assert_true(t_size == 7);
    assert_true(strcmp(buffer, "abcdefgxxx") == 0);

    string_destroy(pstr_string);
}

void test_string_copy__middle_empty(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[10] = {'\0'};
    size_t t_size = 0;
    string_init_cstr(pstr_string, "abcdefg");

    t_size = string_copy(pstr_string, buffer, 0, 5);
    assert_true(t_size == 0);

    string_destroy(pstr_string);
}

void test_string_copy__middle_non_empty(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[10] = {'\0'};
    size_t t_size = 0;
    string_init_cstr(pstr_string, "abcdefghijklmn");

    t_size = string_copy(pstr_string, buffer, 4, 5);
    assert_true(t_size == 4);
    assert_true(strcmp(buffer, "fghi") == 0);

    string_destroy(pstr_string);
}

void test_string_copy__middle_length(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[20] = "xxxxxxxxxx";
    size_t t_size = 0;
    string_init_cstr(pstr_string, "abcdefghij");

    t_size = string_copy(pstr_string, buffer, 5, 5);
    assert_true(t_size == 5);
    assert_true(strcmp(buffer, "fghijxxxxx") == 0);

    string_destroy(pstr_string);
}

void test_string_copy__middle_npos(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[20] = {'\0'};
    size_t t_size = 0;
    string_init_cstr(pstr_string, "abcdefg");

    t_size = string_copy(pstr_string, buffer, NPOS, 5);
    assert_true(t_size == 2);
    assert_true(strcmp(buffer, "fg") == 0);

    string_destroy(pstr_string);
}

void test_string_copy__end(void** state)
{
    string_t* pstr_string = create_string();
    size_t t_size = 0;
    char buffer[10];
    string_init_cstr(pstr_string, "abcdefghij");

    t_size = string_copy(pstr_string, buffer, 0, 10);
    assert_true(t_size == 0);

    string_destroy(pstr_string);
}

void test_string_copy__npos(void** state)
{
    string_t* pstr_string = create_string();
    char buffer[10];
    string_init_cstr(pstr_string, "abcdefg");

    expect_assert_failure(string_copy(pstr_string, buffer, 0, NPOS));

    string_destroy(pstr_string);
}

/*
 * test string_size
 */
UT_CASE_DEFINATION(string_size)
void test_string_size__null_string_container(void** state)
{
    expect_assert_failure(string_size(NULL));
}

void test_string_size__non_inited(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_size(pstr_string));

    string_destroy(pstr_string);
}

void test_string_size__successfully_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_size__successfully_non_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abcdefg");

    assert_true(string_size(pstr_string) == 7);

    string_destroy(pstr_string);
}

/*
 * test string_length
 */
UT_CASE_DEFINATION(string_length)
void test_string_length__null_string_container(void** state)
{
    expect_assert_failure(string_length(NULL));
}

void test_string_length__non_inited(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_length(pstr_string));

    string_destroy(pstr_string);
}

void test_string_length__successfully_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_true(string_length(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_length__successfully_non_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abcdefg");

    assert_true(string_length(pstr_string) == 7);

    string_destroy(pstr_string);
}

/*
 * test string_empty
 */
UT_CASE_DEFINATION(string_empty)
void test_string_empty__null_string_container(void** state)
{
    expect_assert_failure(string_empty(NULL));
}

void test_string_empty__non_inited(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_empty(pstr_string));

    string_destroy(pstr_string);
}

void test_string_empty__successfully_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_true(string_empty(pstr_string));

    string_destroy(pstr_string);
}

void test_string_empty__successfully_non_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abcdefg");

    assert_false(string_empty(pstr_string));

    string_destroy(pstr_string);
}

/*
 * test string_max_size
 */
UT_CASE_DEFINATION(string_max_size)
void test_string_max_size__null_string_container(void** state)
{
    expect_assert_failure(string_max_size(NULL));
}

void test_string_max_size__non_inited(void** state)
{
    string_t* pstr_string = create_string();

    assert_true(string_max_size(pstr_string) > 0);

    string_destroy(pstr_string);
}

void test_string_max_size__successfully(void** state)
{
    string_t* pstr_string = create_string();

    string_init(pstr_string);
    assert_true(string_max_size(pstr_string) != 0);

    string_destroy(pstr_string);
}

/*
 * test string_capacity
 */
UT_CASE_DEFINATION(string_capacity)
void test_string_capacity__null_string_container(void** state)
{
    expect_assert_failure(string_capacity(NULL));
}

void test_string_capacity__non_inited(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_capacity(pstr_string));

    string_destroy(pstr_string);
}

void test_string_capacity__successfully_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init(pstr_string);
    assert_true(string_capacity(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_capacity__successfully_little(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "abc");
    assert_true(string_capacity(pstr_string) == 3);

    string_destroy(pstr_string);
}

void test_string_capacity__successfully_huge(void** state)
{
    string_t* pstr_string = create_string();

    string_init_char(pstr_string, 3983, 'a');
    string_push_back(pstr_string, 'a');
    assert_true(string_capacity(pstr_string) == 7966);

    string_destroy(pstr_string);
}

/*
 * test string_at
 */
UT_CASE_DEFINATION(string_at)
void test_string_at__null_string_container(void** state)
{
    expect_assert_failure(string_at(NULL, 0));
}

void test_string_at__non_inited_string_container(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_at(pstr_string, 0));

    string_destroy(pstr_string);
}

void test_string_at__invalid_subscript_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_at(pstr_string, 0));

    string_destroy(pstr_string);
}

void test_string_at__invalid_subscript_end(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abcdefg");

    expect_assert_failure(string_at(pstr_string, string_size(pstr_string)));

    string_destroy(pstr_string);
}

void test_string_at__invalid_subscript(void** state)
{
    string_t* pstr_string = create_string();
    string_init_cstr(pstr_string, "abcdefg");

    expect_assert_failure(string_at(pstr_string, 132));

    string_destroy(pstr_string);
}

void test_string_at__successfully(void** state)
{
    size_t i = 0;
    string_t* pstr_string = create_string();
    string_init(pstr_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pstr_string, i + 'a');
    }

    for(i = 0; i < string_size(pstr_string); ++i)
    {
        assert_true(*(char*)string_at(pstr_string, i) == i + 'a');
    }

    string_destroy(pstr_string);
}

/*
 * test string_equal
 */
UT_CASE_DEFINATION(string_equal)
void test_string_equal__null_first(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_equal(NULL, pstr));

    string_destroy(pstr);
}

void test_string_equal__null_second(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_equal(pstr, NULL));

    string_destroy(pstr);
}

void test_string_equal__non_inited_first(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_second);
    expect_assert_failure(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    expect_assert_failure(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__same_string(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    assert_true(string_equal(pstr, pstr));

    string_destroy(pstr);
}

void test_string_equal__size_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init_cstr(pstr_second, "abcdefg");
    assert_false(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__size_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 233, 'a');
    string_init_char(pstr_second, 48, 'a');
    assert_false(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__size_equal_0(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init(pstr_second);
    assert_true(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__size_equal_elem_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'a');
    string_init_char(pstr_second, 10, 'z');
    assert_false(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__size_equal_elem_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'x');
    string_init_char(pstr_second, 10, 'n');
    assert_false(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__size_equal_elem_equal(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_cstr(pstr_first, "aaaaa");
    string_init_char(pstr_second, 5, 'a');
    assert_true(string_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test string_not_equal
 */
UT_CASE_DEFINATION(string_not_equal)
void test_string_not_equal__null_first(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_not_equal(NULL, pstr));

    string_destroy(pstr);
}

void test_string_not_equal__null_second(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_not_equal(pstr, NULL));

    string_destroy(pstr);
}

void test_string_not_equal__non_inited_first(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_second);
    expect_assert_failure(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    expect_assert_failure(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__same_string(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    assert_false(string_not_equal(pstr, pstr));

    string_destroy(pstr);
}

void test_string_not_equal__size_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init_char(pstr_second, 48, 'a');
    assert_true(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__size_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 233, 'a');
    string_init_char(pstr_second, 48, 'a');
    assert_true(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__size_equal_0(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init(pstr_second);
    assert_false(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'a');
    string_init_char(pstr_second, 10, 'v');
    assert_true(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'k');
    string_init_char(pstr_second, 10, 'c');
    assert_true(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__size_equal_elem_equal(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'l');
    string_init_char(pstr_second, 10, 'l');
    assert_false(string_not_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test string_less
 */
UT_CASE_DEFINATION(string_less)
void test_string_less__null_first(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_less(NULL, pstr));

    string_destroy(pstr);
}

void test_string_less__null_second(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_less(pstr, NULL));

    string_destroy(pstr);
}

void test_string_less__non_inited_first(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_second);
    expect_assert_failure(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    expect_assert_failure(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__same_string(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    assert_false(string_less(pstr, pstr));

    string_destroy(pstr);
}

void test_string_less__size_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init_char(pstr_second, 48, 'a');
    assert_true(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__size_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 233, 'a');
    string_init_char(pstr_second, 48, 'a');
    assert_false(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__size_equal_0(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init(pstr_second);
    assert_false(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__size_equal_elem_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'a');
    string_init_char(pstr_second, 10, 'f');
    assert_true(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__size_equal_elem_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'g');
    string_init_char(pstr_second, 10, 'a');
    assert_false(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__size_equal_elem_equal(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'd');
    string_init_char(pstr_second, 10, 'd');
    assert_false(string_less(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test string_less_equal
 */
UT_CASE_DEFINATION(string_less_equal)
void test_string_less_equal__null_first(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_less_equal(NULL, pstr));

    string_destroy(pstr);
}

void test_string_less_equal__null_second(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_less_equal(pstr, NULL));

    string_destroy(pstr);
}

void test_string_less_equal__non_inited_first(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_second);
    expect_assert_failure(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    expect_assert_failure(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__same_string(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    assert_true(string_less_equal(pstr, pstr));

    string_destroy(pstr);
}

void test_string_less_equal__size_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init_char(pstr_second, 48, 'a');
    assert_true(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__size_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 233, 'a');
    string_init_char(pstr_second, 48, 'a');
    assert_false(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__size_equal_0(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init(pstr_second);
    assert_true(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'w');
    assert_true(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'f');
    assert_false(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__size_equal_elem_equal(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'j');
    assert_true(string_less_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test string_greater
 */
UT_CASE_DEFINATION(string_greater)
void test_string_greater__null_first(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_greater(NULL, pstr));

    string_destroy(pstr);
}

void test_string_greater__null_second(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_greater(pstr, NULL));

    string_destroy(pstr);
}

void test_string_greater__non_inited_first(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_second);
    expect_assert_failure(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    expect_assert_failure(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__same_string(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    assert_false(string_greater(pstr, pstr));

    string_destroy(pstr);
}

void test_string_greater__size_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init_char(pstr_second, 48, 'a');
    assert_false(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__size_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 233, 'a');
    string_init_char(pstr_second, 48, 'a');
    assert_true(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__size_equal_0(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init(pstr_second);
    assert_false(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__size_equal_elem_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'w');
    assert_false(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__size_equal_elem_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'f');
    assert_true(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__size_equal_elem_equal(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'j');
    assert_false(string_greater(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test string_greater_equal
 */
UT_CASE_DEFINATION(string_greater_equal)
void test_string_greater_equal__null_first(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_greater_equal(NULL, pstr));

    string_destroy(pstr);
}

void test_string_greater_equal__null_second(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    expect_assert_failure(string_greater_equal(pstr, NULL));

    string_destroy(pstr);
}

void test_string_greater_equal__non_inited_first(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_second);
    expect_assert_failure(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    expect_assert_failure(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__same_string(void** state)
{
    string_t* pstr = create_string();
    string_init(pstr);

    assert_true(string_greater_equal(pstr, pstr));

    string_destroy(pstr);
}

void test_string_greater_equal__size_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init_char(pstr_second, 48, 'a');
    assert_false(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__size_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 233, 'a');
    string_init_char(pstr_second, 48, 'a');
    assert_true(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__size_equal_0(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    string_init(pstr_second);
    assert_true(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'w');
    assert_false(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'f');
    assert_true(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__size_equal_elem_equal(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init_char(pstr_first, 10, 'j');
    string_init_char(pstr_second, 10, 'j');
    assert_true(string_greater_equal(pstr_first, pstr_second));

    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test string_equal_cstr
 */
UT_CASE_DEFINATION(string_equal_cstr)
void test_string_equal_cstr__null_string(void** state)
{
    expect_assert_failure(string_equal_cstr(NULL, ""));
}

void test_string_equal_cstr__null_value_string(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_equal_cstr(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_equal_cstr__non_inited_string(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_equal_cstr__char_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_true(string_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_equal_cstr__char_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 3, 'a');

    assert_false(string_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_equal_cstr__char_equal(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_true(string_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_equal_cstr__char_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 6, 'a');

    assert_false(string_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_equal_cstr__char_size_equal_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_false(string_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

void test_string_equal_cstr__char_size_equal_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'c');

    assert_false(string_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

/*
 * test string_not_equal_cstr
 */
UT_CASE_DEFINATION(string_not_equal_cstr)
void test_string_not_equal_cstr__null_string(void** state)
{
    expect_assert_failure(string_not_equal_cstr(NULL, ""));
}

void test_string_not_equal_cstr__null_value_string(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_not_equal_cstr(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_not_equal_cstr__non_inited_string(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_not_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_not_equal_cstr__char_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_false(string_not_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_not_equal_cstr__char_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 3, 'a');

    assert_true(string_not_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_not_equal_cstr__char_equal(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_false(string_not_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_not_equal_cstr__char_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 6, 'a');

    assert_true(string_not_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_not_equal_cstr__char_size_equal_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_true(string_not_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

void test_string_not_equal_cstr__char_size_equal_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'c');

    assert_true(string_not_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

/*
 * test string_less_cstr
 */
UT_CASE_DEFINATION(string_less_cstr)
void test_string_less_cstr__null_string(void** state)
{
    expect_assert_failure(string_less_cstr(NULL, ""));
}

void test_string_less_cstr__null_value_string(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_less_cstr(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_less_cstr__non_inited_string(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_less_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_less_cstr__char_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_false(string_less_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_less_cstr__char_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 3, 'a');

    assert_true(string_less_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_less_cstr__char_equal(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_false(string_less_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_less_cstr__char_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 6, 'a');

    assert_false(string_less_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_less_cstr__char_size_equal_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_true(string_less_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

void test_string_less_cstr__char_size_equal_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'c');

    assert_false(string_less_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

/*
 * test string_less_equal_cstr
 */
UT_CASE_DEFINATION(string_less_equal_cstr)
void test_string_less_equal_cstr__null_string(void** state)
{
    expect_assert_failure(string_less_equal_cstr(NULL, ""));
}

void test_string_less_equal_cstr__null_value_string(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_less_equal_cstr(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_less_equal_cstr__non_inited_string(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_less_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_less_equal_cstr__char_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_true(string_less_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_less_equal_cstr__char_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 3, 'a');

    assert_true(string_less_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_less_equal_cstr__char_equal(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_true(string_less_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_less_equal_cstr__char_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 6, 'a');

    assert_false(string_less_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_less_equal_cstr__char_size_equal_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_true(string_less_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

void test_string_less_equal_cstr__char_size_equal_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'c');

    assert_false(string_less_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

/*
 * test string_greater_cstr
 */
UT_CASE_DEFINATION(string_greater_cstr)
void test_string_greater_cstr__null_string(void** state)
{
    expect_assert_failure(string_greater_cstr(NULL, ""));
}

void test_string_greater_cstr__null_value_string(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_greater_cstr(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_greater_cstr__non_inited_string(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_greater_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_greater_cstr__char_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_false(string_greater_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_greater_cstr__char_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 3, 'a');

    assert_false(string_greater_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_greater_cstr__char_equal(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_false(string_greater_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_greater_cstr__char_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 6, 'a');

    assert_true(string_greater_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_greater_cstr__char_size_equal_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_false(string_greater_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

void test_string_greater_cstr__char_size_equal_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'c');

    assert_true(string_greater_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

/*
 * test string_greater_equal_cstr
 */
UT_CASE_DEFINATION(string_greater_equal_cstr)
void test_string_greater_equal_cstr__null_string(void** state)
{
    expect_assert_failure(string_greater_equal_cstr(NULL, ""));
}

void test_string_greater_equal_cstr__null_value_string(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    expect_assert_failure(string_greater_equal_cstr(pstr_string, NULL));

    string_destroy(pstr_string);
}

void test_string_greater_equal_cstr__non_inited_string(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_greater_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_greater_equal_cstr__char_empty(void** state)
{
    string_t* pstr_string = create_string();
    string_init(pstr_string);

    assert_true(string_greater_equal_cstr(pstr_string, ""));

    string_destroy(pstr_string);
}

void test_string_greater_equal_cstr__char_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 3, 'a');

    assert_false(string_greater_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_greater_equal_cstr__char_equal(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_true(string_greater_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_greater_equal_cstr__char_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 6, 'a');

    assert_true(string_greater_equal_cstr(pstr_string, "aaaaa"));

    string_destroy(pstr_string);
}

void test_string_greater_equal_cstr__char_size_equal_less(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'a');

    assert_false(string_greater_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

void test_string_greater_equal_cstr__char_size_equal_greater(void** state)
{
    string_t* pstr_string = create_string();
    string_init_char(pstr_string, 5, 'c');

    assert_true(string_greater_equal_cstr(pstr_string, "bbbbb"));

    string_destroy(pstr_string);
}

/*
 * test string_compare
 */
UT_CASE_DEFINATION(string_compare)
void test_string_compare__null_first(void** state)
{
    string_t* pt = create_string();
    string_init(pt);

    expect_assert_failure(string_compare(NULL, pt));

    string_destroy(pt);
}

void test_string_compare__null_second(void** state)
{
    string_t* pt = create_string();
    string_init(pt);

    expect_assert_failure(string_compare(pt, NULL));

    string_destroy(pt);
}

void test_string_compare__non_inited_first(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_second);
    expect_assert_failure(string_compare(pt_first, pt_second));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__non_inited_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_first);
    expect_assert_failure(string_compare(pt_first, pt_second));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__same_string(void** state)
{
    string_t* pt = create_string();
    string_init(pt);

    assert_true(string_compare(pt, pt) == 0);

    string_destroy(pt);
}

void test_string_compare__char_size_first_less_than_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_first);
    string_init_char(pt_second, 48, 'a');
    assert_true(string_compare(pt_first, pt_second) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__char_size_first_greater_than_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 233, 'a');
    string_init_char(pt_second, 48, 'a');
    assert_true(string_compare(pt_first, pt_second) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__char_size_equal_0(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_first);
    string_init(pt_second);
    assert_true(string_compare(pt_first, pt_second) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__char_size_equal_elem_first_less_than_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'c');
    assert_true(string_compare(pt_first, pt_second) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__char_size_equal_elem_first_greater_than_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'g');
    string_init_char(pt_second, 10, 'c');
    assert_true(string_compare(pt_first, pt_second) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__char_size_equal_elem_equal(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'x');
    string_init_char(pt_second, 10, 'x');
    assert_true(string_compare(pt_first, pt_second) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

/*
 * test string_compare_substring_string
 */
UT_CASE_DEFINATION(string_compare_substring_string)
void test_string_compare_substring_string__null_first(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_compare_substring_string(NULL, 0, NPOS, pt_string));

    string_destroy(pt_string);
}

void test_string_compare_substring_string__null_second(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 100);
    expect_assert_failure(string_compare_substring_string(pt_string, 0, NPOS, NULL));

    string_destroy(pt_string);
}

void test_string_compare_substring_string__non_inited_first(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_second, 10, 100);
    expect_assert_failure(string_compare_substring_string(pt_first, 0, NPOS, pt_second));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__non_inited_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 100);
    expect_assert_failure(string_compare_substring_string(pt_first, 0, NPOS, pt_second));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__invalid_pos(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 100);
    string_init_char(pt_second, 10, 100);
    expect_assert_failure(string_compare_substring_string(pt_first, 100, NPOS, pt_second));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_sub_size_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, 3, pt_second) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_sub_content_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 3, 'c');
    assert_true(string_compare_substring_string(pt_first, 4, 3, pt_second) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_sub_equal(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 3, 'a');
    assert_true(string_compare_substring_string(pt_first, 7, 3, pt_second) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_sub_size_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 3, 'a');
    assert_true(string_compare_substring_string(pt_first, 5, NPOS, pt_second) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_sub_content_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'd');
    string_init_char(pt_second, 3, 'a');
    assert_true(string_compare_substring_string(pt_first, 7, NPOS, pt_second) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_all_size_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 30, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, NPOS, pt_second) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_all_content_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'd');
    assert_true(string_compare_substring_string(pt_first, 0, NPOS, pt_second) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_all_equal(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, NPOS, pt_second) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_all_size_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 20, 'a');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, NPOS, pt_second) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_all_content_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'e');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, NPOS, pt_second) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_empty_non_empty(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'b');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, 0, pt_second) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_non_empty_empty(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'b');
    string_init_char(pt_second, 0, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, NPOS, pt_second) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__char_empty_empty(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'b');
    string_init_char(pt_second, 0, 'a');
    assert_true(string_compare_substring_string(pt_first, 0, 0, pt_second) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}


/*
 * test string_compare_substring_substring
 */
UT_CASE_DEFINATION(string_compare_substring_substring)
void test_string_compare_substring_substring__null_first(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 0, 100);
    expect_assert_failure(string_compare_substring_substring(NULL, 0, NPOS, pt_string, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_compare_substring_substring__null_second(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 100);
    expect_assert_failure(string_compare_substring_substring(pt_string, 0, NPOS, NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_compare_substring_substring__non_inited_first(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_second, 10, 100);
    expect_assert_failure(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__non_inited_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 100);
    expect_assert_failure(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__invalid_first_pos(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 100);
    string_init_char(pt_second, 10, 100);
    expect_assert_failure(string_compare_substring_substring(pt_first, 100, NPOS, pt_second, 0, NPOS));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__invalid_second_pos(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 100);
    string_init_char(pt_second, 10, 100);
    expect_assert_failure(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 100, NPOS));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_sub_size_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, 3, pt_second, 3, 4444) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_sub_content_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 3, 'c');
    assert_true(string_compare_substring_substring(pt_first, 4, 3, pt_second, 0, NPOS) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_sub_equal(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 13, 'a');
    assert_true(string_compare_substring_substring(pt_first, 7, 3, pt_second, 3, 3) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_sub_size_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 13, 'a');
    assert_true(string_compare_substring_substring(pt_first, 5, NPOS, pt_second, 2, 4) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_sub_content_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'd');
    string_init_char(pt_second, 3, 'a');
    assert_true(string_compare_substring_substring(pt_first, 7, NPOS, pt_second, 0, NPOS) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_all_size_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 30, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_all_content_less(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'd');
    assert_true(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_all_equal(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_all_size_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 20, 'a');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_all_content_greater(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'e');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_empty_non_empty(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'b');
    string_init_char(pt_second, 10, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, 0, pt_second, 0, NPOS) < 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_non_empty_empty(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'b');
    string_init_char(pt_second, 5, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS) > 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__char_empty_empty(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 'b');
    string_init_char(pt_second, 3, 'a');
    assert_true(string_compare_substring_substring(pt_first, 0, 0, pt_second, 0, 0) == 0);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

/*
 * test string_compare_cstr
 */
UT_CASE_DEFINATION(string_compare_cstr)
void test_string_compare_cstr__null_string(void** state)
{
    char elems[] = {'\0'};
    expect_assert_failure(string_compare_cstr(NULL, elems));
}

void test_string_compare_cstr__null_value_string(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_compare_cstr(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_compare_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    char elems[] = {'\0'};

    expect_assert_failure(string_compare_cstr(pt_string, elems));

    string_destroy(pt_string);
}

void test_string_compare_cstr__char_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_compare_cstr(pt_string, "") == 0);

    string_destroy(pt_string);
}

void test_string_compare_cstr__char_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 3, 'a');

    assert_true(string_compare_cstr(pt_string, "aaaaa") < 0);

    string_destroy(pt_string);
}

void test_string_compare_cstr__char_equal(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'a');

    assert_true(string_compare_cstr(pt_string, "aaaaa") == 0);

    string_destroy(pt_string);
}

void test_string_compare_cstr__char_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 6, 'a');

    assert_true(string_compare_cstr(pt_string, "aaaaa") > 0);

    string_destroy(pt_string);
}

void test_string_compare_cstr__char_size_equal_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'a');

    assert_true(string_compare_cstr(pt_string, "bbbbb") < 0);

    string_destroy(pt_string);
}

void test_string_compare_cstr__char_size_equal_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'c');

    assert_true(string_compare_cstr(pt_string, "bbbbb") > 0);

    string_destroy(pt_string);
}

/*
 * test string_compare_substring_cstr
 */
UT_CASE_DEFINATION(string_compare_substring_cstr)
void test_string_compare_substring_cstr__null_string(void** state)
{
    char elems[] = {'\0'};
    expect_assert_failure(string_compare_substring_cstr(NULL, 0, NPOS, elems));
}

void test_string_compare_substring_cstr__null_value_string(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 100);

    expect_assert_failure(string_compare_substring_cstr(pt_string, 0, NPOS, NULL));

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    char elems[] = {'\0'};

    expect_assert_failure(string_compare_substring_cstr(pt_string, 0, NPOS, elems));

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    char elems[] = {'\0'};
    string_init_char(pt_string, 10, 100);

    expect_assert_failure(string_compare_substring_cstr(pt_string, 30, NPOS, elems));

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_empty_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_compare_substring_cstr(pt_string, 5, 0, "") == 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_non_empty_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_compare_substring_cstr(pt_string, 5, 2, "") > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_empty_non_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_compare_substring_cstr(pt_string, 5, 0, "bcd") < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_sub_size_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 13, 'a');

    assert_true(string_compare_substring_cstr(pt_string, 1, 3, "aaaaa") < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_sub_content_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 13, 'a');

    assert_true(string_compare_substring_cstr(pt_string, 1, 5, "bbbbb") < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_sub_equal(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 15, 'a');

    assert_true(string_compare_substring_cstr(pt_string, 4, 5, "aaaaa") == 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_sub_size_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 16, 'a');

    assert_true(string_compare_substring_cstr(pt_string, 4, NPOS, "aaaaa") > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_sub_content_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'c');

    assert_true(string_compare_substring_cstr(pt_string, 5, NPOS, "aaaaa") > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_all_size_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 3, 'b');

    assert_true(string_compare_substring_cstr(pt_string, 0, NPOS, "bbbbb") < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_all_content_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'b');

    assert_true(string_compare_substring_cstr(pt_string, 0, NPOS, "ttttt") < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_all_equal(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'c');

    assert_true(string_compare_substring_cstr(pt_string, 0, NPOS, "ccccc") == 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_all_size_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 6, 'c');

    assert_true(string_compare_substring_cstr(pt_string, 0, NPOS, "ccccc") > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_cstr__char_all_content_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'c');

    assert_true(string_compare_substring_cstr(pt_string, 0, NPOS, "aaaaa") > 0);

    string_destroy(pt_string);
}

/*
 * test string_compare_substring_subcstr
 */
UT_CASE_DEFINATION(string_compare_substring_subcstr)
void test_string_compare_substring_subcstr__null_string(void** state)
{
    char elems[] = {'\0'};
    expect_assert_failure(string_compare_substring_subcstr(NULL, 0, NPOS, elems, NPOS));
}

void test_string_compare_substring_subcstr__null_value_string(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 100);

    expect_assert_failure(string_compare_substring_subcstr(pt_string, 0, NPOS, NULL, NPOS));

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    char elems[] = {'\0'};

    expect_assert_failure(string_compare_substring_subcstr(pt_string, 0, NPOS, elems, NPOS));

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    char elems[] = {'\0'};
    string_init_char(pt_string, 10, 100);

    expect_assert_failure(string_compare_substring_subcstr(pt_string, 30, NPOS, elems, NPOS));

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_empty_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 5, 0, "aaaaaaa", 0) == 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_non_empty_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 5, 2, "", 0) > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_empty_non_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 5, 0, "bcd", 3) < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_sub_size_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 13, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 1, 3, "aaaaa", 5) < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_sub_content_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 13, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 1, 5, "bbbbb", 3) < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_sub_equal(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 15, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 4, 5, "aaaaa", 5) == 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_sub_size_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 16, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 4, NPOS, "aaaaa", 5) > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_sub_content_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'c');

    assert_true(string_compare_substring_subcstr(pt_string, 5, NPOS, "aaaaa", 1) > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_all_size_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 3, 'b');

    assert_true(string_compare_substring_subcstr(pt_string, 0, NPOS, "bbbbb", 5) < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_all_content_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'b');

    assert_true(string_compare_substring_subcstr(pt_string, 0, NPOS, "ttttt", 4) < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_all_equal(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'c');

    assert_true(string_compare_substring_subcstr(pt_string, 0, NPOS, "ccccc", 5) == 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_all_size_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 6, 'c');

    assert_true(string_compare_substring_subcstr(pt_string, 0, NPOS, "ccccc", 5) > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_all_content_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 5, 'c');

    assert_true(string_compare_substring_subcstr(pt_string, 0, NPOS, "aaaaa", 2) > 0);

    string_destroy(pt_string);
}

/*
 * test string_substr
 */
UT_CASE_DEFINATION(string_substr)
void test_string_substr__null_string(void** state)
{
    expect_assert_failure(string_substr(NULL, 0, NPOS));
}

void test_string_substr__non_inited_string(void** state)
{
    string_t* pstr_string = create_string();

    expect_assert_failure(string_substr(pstr_string, 0, NPOS));

    string_destroy(pstr_string);
}

void test_string_substr__invalid_pos(void** state)
{
    string_t* pstr_string = create_string();

    string_init_char(pstr_string, 10, 'a');
    expect_assert_failure(string_substr(pstr_string, 100, NPOS));

    string_destroy(pstr_string);
}

void test_string_substr__empty_substr(void** state)
{
    string_t* pstr_string = create_string();
    string_t* pt_substr = NULL;

    string_init_char(pstr_string, 10, 'a');
    pt_substr = string_substr(pstr_string, 0, 0);
    assert_true(pt_substr != NULL);
    assert_true(string_empty(pt_substr));

    string_destroy(pstr_string);
    string_destroy(pt_substr);
}

void test_string_substr__all(void** state)
{
    string_t* pstr_string = create_string();
    string_t* pt_substr = NULL;

    string_init_char(pstr_string, 10, 'a');
    pt_substr = string_substr(pstr_string, 0, NPOS);
    assert_true(string_equal(pstr_string, pt_substr));

    string_destroy(pstr_string);
    string_destroy(pt_substr);
}

void test_string_substr__begin(void** state)
{
    string_t* pstr_string = create_string();
    string_t* pt_substr = NULL;

    string_init_cstr(pstr_string, "abcdefgh");
    pt_substr = string_substr(pstr_string, 0, 3);
    assert_true(pt_substr != NULL);
    assert_true(string_size(pt_substr) == 3);
    assert_true(strcmp(string_c_str(pt_substr), "abc") == 0);

    string_destroy(pstr_string);
    string_destroy(pt_substr);
}

void test_string_substr__middle(void** state)
{
    string_t* pstr_string = create_string();
    string_t* pt_substr = NULL;

    string_init_cstr(pstr_string, "abcdefgh");
    pt_substr = string_substr(pstr_string, 3, 3);
    assert_true(pt_substr != NULL);
    assert_true(string_size(pt_substr) == 3);
    assert_true(strcmp(string_c_str(pt_substr), "def") == 0);

    string_destroy(pstr_string);
    string_destroy(pt_substr);
}

void test_string_substr__end(void** state)
{
    string_t* pstr_string = create_string();
    string_t* pt_substr = NULL;

    string_init_cstr(pstr_string, "abcdefgh");
    pt_substr = string_substr(pstr_string, 5, 344);
    assert_true(pt_substr != NULL);
    assert_true(string_size(pt_substr) == 3);
    assert_true(strcmp(string_c_str(pt_substr), "fgh") == 0);

    string_destroy(pstr_string);
    string_destroy(pt_substr);
}

/*
 * test string_connect
 */
UT_CASE_DEFINATION(string_connect)
void test_string_connect__null_dest(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_connect(NULL, pt_string));

    string_destroy(pt_string);
}

void test_string_connect__null_src(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_connect(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_connect__non_inited_dest(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_src);
    expect_assert_failure(string_connect(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_connect__non_inited_src(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    expect_assert_failure(string_connect(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_connect__empty_empty(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init(pt_src);
    string_connect(pt_dest, pt_src);
    assert_true(string_empty(pt_dest));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_connect__non_empty_empty(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 'a');
    string_init(pt_src);
    string_connect(pt_dest, pt_src);
    assert_true(string_size(pt_dest) == 10);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_connect__empty_non_empty(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_src, 10, 'a');
    string_init(pt_dest);
    string_connect(pt_dest, pt_src);
    assert_true(string_size(pt_dest) == 10);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_connect__same(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefg");

    string_connect(pt_string, pt_string);
    assert_true(string_size(pt_string) == 14);
    assert_true(strcmp(string_c_str(pt_string), "abcdefgabcdefg") == 0);

    string_destroy(pt_string);
}

void test_string_connect__char(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    size_t i = 0;

    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 4; ++i)
    {
        string_push_back(pt_dest, 'a');
        string_push_back(pt_src, 'd');
    }
    string_connect(pt_dest, pt_src);
    assert_true(string_size(pt_dest) == 8);
    assert_true(strcmp(string_c_str(pt_dest), "aaaadddd") == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

/*
 * test string_connect_cstr
 */
UT_CASE_DEFINATION(string_connect_cstr)
void test_string_connect_cstr__null_string(void** state)
{
    expect_assert_failure(string_connect_cstr(NULL, ""));
}

void test_string_connect_cstr__null_value_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_connect_cstr(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_connect_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_connect_cstr(pt_string, ""));

    string_destroy(pt_string);
}

void test_string_connect_cstr__empty_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_connect_cstr(pt_string, "");
    assert_true(string_empty(pt_string));

    string_destroy(pt_string);
}

void test_string_connect_cstr__non_empty_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 9, 'a');
    string_connect_cstr(pt_string, "");
    assert_true(string_size(pt_string) == 9);
    assert_true(strcmp(string_c_str(pt_string), "aaaaaaaaa") == 0);

    string_destroy(pt_string);
}

void test_string_connect_cstr__empty_non_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_connect_cstr(pt_string, "abcdefg");
    assert_true(string_size(pt_string) == 7);
    assert_true(strcmp(string_c_str(pt_string), "abcdefg") == 0);

    string_destroy(pt_string);
}

void test_string_connect_cstr__char(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "aaaaa");
    string_connect_cstr(pt_string, "bbbb");
    assert_true(string_size(pt_string) == 9);
    assert_true(strcmp(string_c_str(pt_string), "aaaaabbbb") == 0);

    string_destroy(pt_string);
}

/*
 * test string_connect_char
 */
UT_CASE_DEFINATION(string_connect_char)
void test_string_connect_char__null_string_container(void** state)
{
    expect_assert_failure(string_connect_char(NULL, 'a'));
}

void test_string_connect_char__non_inited_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_connect_char(pt_string, 'a'));

    string_destroy(pt_string);
}

void test_string_connect_char__empty_container(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_connect_char(pt_string, 'a');
    assert_true(string_size(pt_string) == 1);
    assert_true(strcmp(string_c_str(pt_string), "a") == 0);

    string_destroy(pt_string);
}

void test_string_connect_char__non_empty_container(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 3, 'a');
    string_connect_char(pt_string, 'b');
    assert_true(string_size(pt_string) == 4);
    assert_true(strcmp(string_c_str(pt_string), "aaab") == 0);

    string_destroy(pt_string);
}

/*
 * test string_find
 */
UT_CASE_DEFINATION(string_find)
void test_string_find__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find(NULL, pt_string, 0));

    string_destroy(pt_string);
}

void test_string_find__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_find);
    expect_assert_failure(string_find(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init_char(pt_string, 10, 'a');
    string_init(pt_find);
    assert_true(string_find(pt_string, pt_find, 100) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__same_begin(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find(pt_string, pt_string, 0) == 0);

    string_destroy(pt_string);
}

void test_string_find__same_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find(pt_string, pt_string, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find(pt_string, pt_find, 0) == 0);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_find(pt_string, pt_find, 0) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find(pt_string, pt_find, 5) == 5);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_find(pt_string, pt_find, 2) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find(pt_string, pt_find, 2) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_find(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

/*
 * test string_find_cstr
 */
UT_CASE_DEFINATION(string_find_cstr)
void test_string_find_cstr__null_string(void** state)
{
    expect_assert_failure(string_find_cstr(NULL, "abcd", 0));
}

void test_string_find_cstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_cstr(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_cstr(pt_string, "abc", 0));

    string_destroy(pt_string);
}

void test_string_find_cstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_cstr(pt_string, "abc", 100) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_cstr__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_cstr(pt_string, "", 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_cstr__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_cstr(pt_string, "de", 0) == 3);

    string_destroy(pt_string);
}

void test_string_find_cstr__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_cstr(pt_string, "xy", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_cstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_cstr(pt_string, "", 5) == 5);

    string_destroy(pt_string);
}

void test_string_find_cstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_cstr(pt_string, "de", 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_cstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_cstr(pt_string, "xy", 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_cstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_cstr(pt_string, "de", 5) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_subcstr
 */
UT_CASE_DEFINATION(string_find_subcstr)
void test_string_find_subcstr__null_string(void** state)
{
    expect_assert_failure(string_find_subcstr(NULL, "abc", 0, 3));
}

void test_string_find_subcstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_subcstr(pt_string, NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_find_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_subcstr(pt_string, "abc", 0, 3));

    string_destroy(pt_string);
}

void test_string_find_subcstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_subcstr(pt_string, "abc", 100, 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "", 0, 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_begin_length_0(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "de", 0, 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "de", 0, 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "xy", 0, 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "", 5, 0) == 5);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_middle_length_0(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "de", 2, 0) == 2);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "de", 2, 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "xy", 2, 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_subcstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_subcstr(pt_string, "de", 5, 2) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_char
 */
UT_CASE_DEFINATION(string_find_char)

void test_string_find_char__null_string_container(void** state)
{
    expect_assert_failure(string_find_char(NULL, 'a', 2323));
}

void test_string_find_char__non_init_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_char(pt_string, 'a', 111));

    string_destroy(pt_string);
}

void test_string_find_char__invalid_position(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_char(pt_string, 'b', 100) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_char__invalid_position_end(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_char(pt_string, 'b', string_size(pt_string)) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_char__invalid_position_NPOS(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_char(pt_string, 'b', NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_char__find_failure(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_char(pt_string, 'd', 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_char__find_failure_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 1, 'a');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    assert_true(string_find_char(pt_string, 'a', 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_char__find_successful(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    assert_true(string_find_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_char__find_successful_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_char(pt_string, 'a', 0) == 2);

    string_destroy(pt_string);
}

void test_string_find_char__find_successful_back(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'e');
    string_push_back(pt_string, 'a');
    assert_true(string_find_char(pt_string, 'a', 0) == 4);

    string_destroy(pt_string);
}

void test_string_find_char__find_successful_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_char(pt_string, 'a', 3) == 4);

    string_destroy(pt_string);
}

/*
 * test string_rfind
 */
UT_CASE_DEFINATION(string_rfind)
void test_string_rfind__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_rfind(NULL, pt_string, 0));

    string_destroy(pt_string);
}

void test_string_rfind__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_rfind(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_rfind__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_find);
    expect_assert_failure(string_rfind(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    expect_assert_failure(string_rfind(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__same_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_rfind(pt_string, pt_string, NPOS) == 0);

    string_destroy(pt_string);
}

void test_string_rfind__same_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_rfind(pt_string, pt_string, 4) == 0);

    string_destroy(pt_string);
}

void test_string_rfind__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init(pt_find);
    assert_true(string_rfind(pt_string, pt_find, 0) == 0);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init(pt_find);
    assert_true(string_rfind(pt_string, pt_find, NPOS) == string_size(pt_string));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init_char(pt_find, 10, 'a');
    assert_true(string_rfind(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init_char(pt_find, 10, 'a');
    assert_true(string_rfind(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_rfind(pt_string, pt_find, NPOS) == basic_string_size(pt_string));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_find_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_rfind(pt_string, pt_find, NPOS) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_rfind(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_rfind(pt_string, pt_find, 5) == 5);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_rfind(pt_string, pt_find, 3) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_rfind(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_rfind(pt_string, pt_find, 2) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

/*
 * test string_rfind_cstr
 */
UT_CASE_DEFINATION(string_rfind_cstr)
void test_string_rfind_cstr__null_string(void** state)
{
    expect_assert_failure(string_rfind_cstr(NULL, "abc", 0));
}

void test_string_rfind_cstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_rfind_cstr(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_rfind_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_rfind_cstr(pt_string, "abc", 0));

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_cstr(pt_string, "", 0) == 0);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_cstr(pt_string, "", NPOS) == 0);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_cstr(pt_string, "abcd", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_cstr(pt_string, "abcd", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_cstr(pt_string, "", NPOS) == string_size(pt_string));

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_find_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_cstr(pt_string, "de", NPOS) == 3);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_cstr(pt_string, "xy", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_cstr(pt_string, "", 5) == 5);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_cstr(pt_string, "de", 3) == 3);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_cstr(pt_string, "xy", 5) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_cstr(pt_string, "de", 2) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_rfind_subcstr
 */
UT_CASE_DEFINATION(string_rfind_subcstr)
void test_string_rfind_subcstr__null_string(void** state)
{
    expect_assert_failure(string_rfind_subcstr(NULL, "abc", 0, 3));
}

void test_string_rfind_subcstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_rfind_subcstr(pt_string, NULL, 0, 0));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_rfind_subcstr(pt_string, "", 0, 0));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "", 0, 0) == 0);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "", NPOS, 0) == string_size(pt_string));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_0_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", 0, 0) == string_size(pt_string));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", NPOS, 0) == string_size(pt_string));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", 0, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", NPOS, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "", NPOS, 0) == string_size(pt_string));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "abcdefghij", NPOS, 0) == string_size(pt_string));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "de", NPOS, 2) == 3);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "abcxy", NPOS, 5) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "", 5, 0) == 5);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_non_empty_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "defgh", 5, 0) == 5);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "de", 3, 2) == 3);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "xy", 5, 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "de", 2, 10) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_rfind_char
 */
UT_CASE_DEFINATION(string_rfind_char)

void test_string_rfind_char__null_string_container(void** state)
{
    expect_assert_failure(string_rfind_char(NULL, 'a', 0));
}

void test_string_rfind_char__non_init_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_rfind_char(pt_string, 'a', 0));

    string_destroy(pt_string);
}

void test_string_rfind_char__invalid_position(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_rfind_char(pt_string, 'a', 3445) == 9);

    string_destroy(pt_string);
}

void test_string_rfind_char__invalid_position_begin(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_rfind_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_rfind_char__invalid_position_NPOS(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_rfind_char(pt_string, 'a', NPOS) == 9);

    string_destroy(pt_string);
}

void test_string_rfind_char__find_failure(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_rfind_char(pt_string, 'b', NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_char__find_failure_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    assert_true(string_rfind_char(pt_string, 'b', 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_char__find_successful(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    assert_true(string_rfind_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_rfind_char__find_successful_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_rfind_char(pt_string, 'a', 3) == 2);

    string_destroy(pt_string);
}

void test_string_rfind_char__find_successful_back(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'e');
    string_push_back(pt_string, 'a');
    assert_true(string_rfind_char(pt_string, 'a', 100) == 4);

    string_destroy(pt_string);
}

void test_string_rfind_char__find_successful_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_rfind_char(pt_string, 'a', 4) == 4);

    string_destroy(pt_string);
}

/*
 * test string_find_first_of
 */
UT_CASE_DEFINATION(string_find_first_of)
void test_string_find_first_of__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_of(NULL, pt_string, 0));

    string_destroy(pt_string);
}

void test_string_find_first_of__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_of(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_first_of__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_find);
    expect_assert_failure(string_find_first_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init_char(pt_string, 10, 'a');
    string_init(pt_find);
    assert_true(string_find_first_of(pt_string, pt_find, 100) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__same_begin(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of(pt_string, pt_string, 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_first_of__same_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of(pt_string, pt_string, 4) == 4);

    string_destroy(pt_string);
}

void test_string_find_first_of__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_first_of(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 15);
    string_push_back(pt_find, 'a' + 3);
    assert_true(string_find_first_of(pt_string, pt_find, 0) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_first_of(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_first_of(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 4);
    string_push_back(pt_find, 'a' + 5);
    string_push_back(pt_find, 'a' + 3);
    assert_true(string_find_first_of(pt_string, pt_find, 2) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_first_of(pt_string, pt_find, 2) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_of__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_find_first_of(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

/*
 * test string_find_first_of_cstr
 */
UT_CASE_DEFINATION(string_find_first_of_cstr)
void test_string_find_first_of_cstr__null_string(void** state)
{
    expect_assert_failure(string_find_first_of_cstr(NULL, "abc", 0));
}

void test_string_find_first_of_cstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_of_cstr(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_first_of_cstr(pt_string, "abc", 0));

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of_cstr(pt_string, "abc", 100) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_cstr(pt_string, "", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_cstr(pt_string, "xydeh", 0) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_cstr(pt_string, "xy", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_cstr(pt_string, "", 5) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_cstr(pt_string, "fed", 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_cstr(pt_string, "xy", 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_cstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_cstr(pt_string, "de", 5) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_first_of_subcstr
 */
UT_CASE_DEFINATION(string_find_first_of_subcstr)
void test_string_find_first_of_subcstr__null_string(void** state)
{
    expect_assert_failure(string_find_first_of_subcstr(NULL, "abc", 0, 3));
}

void test_string_find_first_of_subcstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_of_subcstr(pt_string, NULL, 0, 0));

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_first_of_subcstr(pt_string, "abc", 0, 3));

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of_subcstr(pt_string, "abc", 100, 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "", 0, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_begin_length_0(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "de", 0, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "de", 0, 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "xy", 0, 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "", 5, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_middle_length_0(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "de", 2, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "de", 2, 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "xy", 2, 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_subcstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_of_subcstr(pt_string, "de", 5, 2) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_first_of_char
 */
UT_CASE_DEFINATION(string_find_first_of_char)

void test_string_find_first_of_char__null_string_container(void** state)
{
    expect_assert_failure(string_find_first_of_char(NULL, 'a', 2323));
}

void test_string_find_first_of_char__non_init_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_first_of_char(pt_string, 'a', 111));

    string_destroy(pt_string);
}

void test_string_find_first_of_char__invalid_position(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of_char(pt_string, 'b', 100) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__invalid_position_end(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of_char(pt_string, 'b', string_size(pt_string)) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__invalid_position_NPOS(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of_char(pt_string, 'b', NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__find_failure(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_of_char(pt_string, 'd', 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__find_failure_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 1, 'a');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    assert_true(string_find_first_of_char(pt_string, 'a', 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__find_successful(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    assert_true(string_find_first_of_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__find_successful_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_first_of_char(pt_string, 'a', 0) == 2);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__find_successful_back(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'e');
    string_push_back(pt_string, 'a');
    assert_true(string_find_first_of_char(pt_string, 'a', 0) == 4);

    string_destroy(pt_string);
}

void test_string_find_first_of_char__find_successful_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_first_of_char(pt_string, 'a', 3) == 4);

    string_destroy(pt_string);
}

/*
 * test string_find_first_not_of
 */
UT_CASE_DEFINATION(string_find_first_not_of)
void test_string_find_first_not_of__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_not_of(NULL, pt_string, 0));

    string_destroy(pt_string);
}

void test_string_find_first_not_of__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_not_of(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_first_not_of__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_find);
    expect_assert_failure(string_find_first_not_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_not_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init_char(pt_string, 10, 'a');
    string_init(pt_find);
    assert_true(string_find_first_not_of(pt_string, pt_find, 100) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__same_begin(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of(pt_string, pt_string, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of__same_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of(pt_string, pt_string, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_first_not_of(pt_string, pt_find, 0) == 0);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 1);
    string_push_back(pt_find, 'a' + 2);
    string_push_back(pt_find, 'a' + 0);
    string_push_back(pt_find, 'a' + 4);
    string_push_back(pt_find, 'a' + 5);
    assert_true(string_find_first_not_of(pt_string, pt_find, 0) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init_copy(pt_find, pt_string);
    assert_true(string_find_first_not_of(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_first_not_of(pt_string, pt_find, 5) == 5);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 4);
    string_push_back(pt_find, 'a' + 5);
    string_push_back(pt_find, 'a' + 2);
    assert_true(string_find_first_not_of(pt_string, pt_find, 2) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init_copy(pt_find, pt_string);
    assert_true(string_find_first_not_of(pt_string, pt_find, 2) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_first_not_of__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init_copy(pt_find, pt_string);
    assert_true(string_find_first_not_of(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

/*
 * test string_find_first_not_of_cstr
 */
UT_CASE_DEFINATION(string_find_first_not_of_cstr)
void test_string_find_first_not_of_cstr__null_string(void** state)
{
    expect_assert_failure(string_find_first_not_of_cstr(NULL, "abc", 0));
}

void test_string_find_first_not_of_cstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_not_of_cstr(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_first_not_of_cstr(pt_string, "abc", 0));

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of_cstr(pt_string, "abc", 100) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_cstr(pt_string, "", 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_cstr(pt_string, "abcefghijklmn", 0) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_cstr(pt_string, "jklmnxfghiyabcde", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_cstr(pt_string, "", 5) == 5);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_cstr(pt_string, "efghijklmnabc", 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_cstr(pt_string, "abcdxyeopfgqhijklmn", 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_cstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_cstr(pt_string, "fghijklmnopq", 5) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_first_not_of_subcstr
 */
UT_CASE_DEFINATION(string_find_first_not_of_subcstr)
void test_string_find_first_not_of_subcstr__null_string(void** state)
{
    expect_assert_failure(string_find_first_not_of_subcstr(NULL, "abc", 0, 3));
}

void test_string_find_first_not_of_subcstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_first_not_of_subcstr(pt_string, NULL, 0, 0));

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_first_not_of_subcstr(pt_string, "abc", 0, 3));

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of_subcstr(pt_string, "abcd", 100, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_begin_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "", 0, 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_begin_length_0(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "de", 0, 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_begin_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "abcefghijklmn", 0, 13) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_begin_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "xyabcdefghijklmn", 0, 13) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "", 5, 0) == 5);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_middle_length_0(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "de", 2, 0) == 2);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "abcefghijklmn", 2, 13) == 3);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "xyabcdefghijklmn", 2, 16) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_subcstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    assert_true(string_find_first_not_of_subcstr(pt_string, "fghijklmn", 5, 9) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_first_not_of_char
 */
UT_CASE_DEFINATION(string_find_first_not_of_char)

void test_string_find_first_not_of_char__null_string_container(void** state)
{
    expect_assert_failure(string_find_first_not_of_char(NULL, 'a', 0));
}

void test_string_find_first_not_of_char__non_init_string_container(
    void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_first_not_of_char(pt_string, 'a', 0));

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__invalid_position(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of_char(pt_string, 'a', 3445) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__invalid_position_end(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of_char(pt_string, 'a', string_size(pt_string)) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__invalid_position_NPOS(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of_char(pt_string, 'a', NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__find_first_not_of_failure(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_first_not_of_char(pt_string, 'a', 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__find_first_not_of_failure_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 1, 'b');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    assert_true(string_find_first_not_of_char(pt_string, 'a', 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__find_first_not_of_successful(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_first_not_of_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__find_first_not_of_successful_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_first_not_of_char(pt_string, 'a', 0) == 2);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__find_first_not_of_successful_back(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    assert_true(string_find_first_not_of_char(pt_string, 'a', 0) == 4);

    string_destroy(pt_string);
}

void test_string_find_first_not_of_char__find_first_not_of_successful_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'e');
    assert_true(string_find_first_not_of_char(pt_string, 'a', 3) == 4);

    string_destroy(pt_string);
}

/*
 * test string_find_last_of
 */
UT_CASE_DEFINATION(string_find_last_of)
void test_string_find_last_of__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_of(NULL, pt_string, 0));

    string_destroy(pt_string);
}

void test_string_find_last_of__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_of(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_last_of__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_find);
    expect_assert_failure(string_find_last_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__same_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 100);
    assert_true(string_find_last_of(pt_string, pt_string, NPOS) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_of__same_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 100);
    assert_true(string_find_last_of(pt_string, pt_string, 4) == 4);

    string_destroy(pt_string);
}

void test_string_find_last_of__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init(pt_find);
    assert_true(string_find_last_of(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init(pt_find);
    assert_true(string_find_last_of(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init_char(pt_find, 10, 'a');
    assert_true(string_find_last_of(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init_char(pt_find, 10, 'a');
    assert_true(string_find_last_of(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_last_of(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_find_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_of(pt_string, pt_find, NPOS) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_of(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_last_of(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_of(pt_string, pt_find, 3) == 3);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_of(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_of__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 4);
    assert_true(string_find_last_of(pt_string, pt_find, 2) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

/*
 * test string_find_last_of_cstr
 */
UT_CASE_DEFINATION(string_find_last_of_cstr)
void test_string_find_last_of_cstr__null_string(void** state)
{
    expect_assert_failure(string_find_last_of_cstr(NULL, "abc", 0));
}

void test_string_find_last_of_cstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_of_cstr(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_last_of_cstr(pt_string, "abc", 0));

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_cstr(pt_string, "", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_cstr(pt_string, "", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_cstr(pt_string, "abcd", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_cstr(pt_string, "abcd", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_cstr(pt_string, "", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_find_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_cstr(pt_string, "dxyz", NPOS) == 3);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_cstr(pt_string, "xy", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_cstr(pt_string, "", 5) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_cstr(pt_string, "de", 3) == 3);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_cstr(pt_string, "xy", 5) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_cstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_cstr(pt_string, "de", 2) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_last_of_subcstr
 */
UT_CASE_DEFINATION(string_find_last_of_subcstr)
void test_string_find_last_of_subcstr__null_string(void** state)
{
    expect_assert_failure(string_find_last_of_subcstr(NULL, "abc", 0, 3));
}

void test_string_find_last_of_subcstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_of_subcstr(pt_string, NULL, 0, 0));

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_last_of_subcstr(pt_string, "", 0, 0));

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_subcstr(pt_string, "", 0, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_subcstr(pt_string, "", NPOS, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_empty_non_empty_0_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_subcstr(pt_string, "abcd", 0, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_empty_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_subcstr(pt_string, "abcd", NPOS, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_subcstr(pt_string, "abcd", 0, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_of_subcstr(pt_string, "abcd", NPOS, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "", NPOS, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "abcdefghij", NPOS, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "de", NPOS, 2) == 4);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "wwwxy", NPOS, 5) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "", 5, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_middle_non_empty_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "defgh", 5, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "de", 3, 2) == 3);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "xy", 5, 2) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_subcstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_of_subcstr(pt_string, "de", 2, 2) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_last_of_char
 */
UT_CASE_DEFINATION(string_find_last_of_char)

void test_string_find_last_of_char__null_string_container(void** state)
{
    expect_assert_failure(string_find_last_of_char(NULL, 'a', 0));
}

void test_string_find_last_of_char__non_init_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_last_of_char(pt_string, 'b', 0));

    string_destroy(pt_string);
}

void test_string_find_last_of_char__invalid_position(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_of_char(pt_string, 'a', 34456) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__invalid_position_begin(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_of_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__invalid_position_NPOS(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_of_char(pt_string, 'a', NPOS) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__find_failure(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_of_char(pt_string, 'b', NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__find_failure_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    assert_true(string_find_last_of_char(pt_string, 'b', 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__find_successful(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_last_of_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__find_successful_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_last_of_char(pt_string, 'a', 3) == 2);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__find_successful_back(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'e');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'a');
    assert_true(string_find_last_of_char(pt_string, 'a', 100) == 4);

    string_destroy(pt_string);
}

void test_string_find_last_of_char__find_successful_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_last_of_char(pt_string, 'a', 4) == 4);

    string_destroy(pt_string);
}

/*
 * test string_find_last_not_of
 */
UT_CASE_DEFINATION(string_find_last_not_of)
void test_string_find_last_not_of__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_not_of(NULL, pt_string, 0));

    string_destroy(pt_string);
}

void test_string_find_last_not_of__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_not_of(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_last_not_of__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_find);
    expect_assert_failure(string_find_last_not_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_not_of(pt_string, pt_find, 0));

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__same_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_not_of(pt_string, pt_string, NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of__same_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_not_of(pt_string, pt_string, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init(pt_find);
    assert_true(string_find_last_not_of(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init(pt_find);
    assert_true(string_find_last_not_of(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init_char(pt_find, 10, 'a');
    assert_true(string_find_last_not_of(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init_char(pt_find, 10, 'a');
    assert_true(string_find_last_not_of(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_last_not_of(pt_string, pt_find, NPOS) == 9);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_find_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_not_of(pt_string, pt_find, NPOS) == 9);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init_copy(pt_find, pt_string);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_not_of(pt_string, pt_find, NPOS) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    assert_true(string_find_last_not_of(pt_string, pt_find, 5) == 5);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 3);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_not_of(pt_string, pt_find, 3) == 2);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init_copy(pt_find, pt_string);
    string_push_back(pt_find, 'a' + 13);
    string_push_back(pt_find, 'a' + 14);
    assert_true(string_find_last_not_of(pt_string, pt_find, 5) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find_last_not_of__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();
    size_t i = 0;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }
    string_init(pt_find);
    string_push_back(pt_find, 'a' + 0);
    string_push_back(pt_find, 'a' + 1);
    string_push_back(pt_find, 'a' + 2);
    assert_true(string_find_last_not_of(pt_string, pt_find, 2) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

/*
 * test string_find_last_not_of_cstr
 */
UT_CASE_DEFINATION(string_find_last_not_of_cstr)
void test_string_find_last_not_of_cstr__null_string(void** state)
{
    expect_assert_failure(string_find_last_not_of_cstr(NULL, "", 0));
}

void test_string_find_last_not_of_cstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_not_of_cstr(pt_string, NULL, 0));

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_last_not_of_cstr(pt_string, "", 0));

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_cstr(pt_string, "", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_cstr(pt_string, "", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_cstr(pt_string, "abcd", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_cstr(pt_string, "abcd", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_cstr(pt_string, "", NPOS) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_find_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_cstr(pt_string, "abcefghij", NPOS) == 3);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_cstr(pt_string, "abcdefghij", NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_cstr(pt_string, "", 5) == 5);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_cstr(pt_string, "abcef", 3) == 3);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_cstr(pt_string, "abcdefghij", 5) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_cstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_cstr(pt_string, "abc", 2) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_last_not_of_subcstr
 */
UT_CASE_DEFINATION(string_find_last_not_of_subcstr)
void test_string_find_last_not_of_subcstr__null_string(void** state)
{
    expect_assert_failure(string_find_last_not_of_subcstr(NULL, "", 0, 0));
}

void test_string_find_last_not_of_subcstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_find_last_not_of_subcstr(pt_string, NULL, 0, 0));

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_last_not_of_subcstr(pt_string, "", 0, 0));

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_subcstr(pt_string, "", 0, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_subcstr(pt_string, "", NPOS, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_empty_non_empty_0_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_subcstr(pt_string, "abcd", 0, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_empty_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_subcstr(pt_string, "abcd", NPOS, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_subcstr(pt_string, "abcd", 0, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_find_last_not_of_subcstr(pt_string, "abcd", NPOS, 4) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "", NPOS, 0) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "abcdefghij", NPOS, 0) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "fghijklmn", NPOS, 9) == 4);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "wabcdewfghijwklmxnoy", NPOS, 20) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "", 5, 0) == 5);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_middle_non_empty_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "defgh", 5, 0) == 5);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_middle_find(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "abcefg", 3, 6) == 3);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "xabcdefgy", 5, 9) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_subcstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_find_last_not_of_subcstr(pt_string, "abcde", 2, 5) == NPOS);

    string_destroy(pt_string);
}

/*
 * test string_find_last_not_of_char
 */
UT_CASE_DEFINATION(string_find_last_not_of_char)

void test_string_find_last_not_of_char__null_string_container(void** state)
{
    expect_assert_failure(string_find_last_not_of_char(NULL, 'a', 0));
}

void test_string_find_last_not_of_char__non_init_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_find_last_not_of_char(pt_string, 'a', 0));

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__invalid_position(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_not_of_char(pt_string, 'b', 34456) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__invalid_position_begin(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_not_of_char(pt_string, 'b', 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__invalid_position_NPOS(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_not_of_char(pt_string, 'b', NPOS) == 9);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__find_failure(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    assert_true(string_find_last_not_of_char(pt_string, 'a', NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__find_failure_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    assert_true(string_find_last_not_of_char(pt_string, 'b', 3) == NPOS);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__find_successful(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'e');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    assert_true(string_find_last_not_of_char(pt_string, 'a', 0) == 0);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__find_successful_middle(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'e');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'b');
    assert_true(string_find_last_not_of_char(pt_string, 'a', 3) == 2);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__find_successful_back(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'e');
    assert_true(string_find_last_not_of_char(pt_string, 'a', 100) == 4);

    string_destroy(pt_string);
}

void test_string_find_last_not_of_char__find_successful_middle_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'b');
    string_push_back(pt_string, 'c');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'a');
    string_push_back(pt_string, 'd');
    string_push_back(pt_string, 'e');
    assert_true(string_find_last_not_of_char(pt_string, 'a', 4) == 4);

    string_destroy(pt_string);
}

/*
 * test string_begin
 */
UT_CASE_DEFINATION(string_begin)
void test_string_begin__null_string_container(void** state)
{
    expect_assert_failure(string_begin(NULL));
}

void test_string_begin__non_inited_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_begin(pt_string));

    string_destroy(pt_string);
}

void test_string_begin__empty(void** state)
{
    string_iterator_t it_begin;
    string_t* pt_string = create_string();
    string_init(pt_string);

    it_begin = string_begin(pt_string);
    assert_true(iterator_equal(it_begin, string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_begin__non_empty(void** state)
{
    string_iterator_t it_begin;
    string_t* pt_string = create_string();
    string_init_cstr(pt_string, "abc");

    it_begin = string_begin(pt_string);
    assert_true(*(char*)iterator_get_pointer(it_begin) == 'a');

    string_destroy(pt_string);
}

/*
 * test string_end
 */
UT_CASE_DEFINATION(string_end)
void test_string_end__null_string_container(void** state)
{
    expect_assert_failure(string_end(NULL));
}

void test_string_end__non_inited_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_end(pt_string));

    string_destroy(pt_string);
}

void test_string_end__empty(void** state)
{
    string_iterator_t it_end;
    string_t* pt_string = create_string();
    string_init(pt_string);

    it_end = string_end(pt_string);
    assert_true(iterator_equal(it_end, string_begin(pt_string)));

    string_destroy(pt_string);
}

void test_string_end__non_empty(void** state)
{
    char c = '@';
    string_iterator_t it_end;
    string_t* pt_string = create_string();
    string_init_cstr(pt_string, "abc");

    it_end = string_end(pt_string);
    assert_true(*(char*)_BASIC_STRING_ITERATOR_COREPOS(it_end) == '\0');
    expect_assert_failure(iterator_next(it_end));
    expect_assert_failure(iterator_get_pointer(it_end));
    expect_assert_failure(iterator_set_value(it_end, &c));
    expect_assert_failure(iterator_get_value(it_end, &c));

    string_destroy(pt_string);
}

/*
 * test string_clear
 */
UT_CASE_DEFINATION(string_clear)
void test_string_clear__null_string_container(void** state)
{
    expect_assert_failure(string_clear(NULL));
}

void test_string_clear__non_inited_string_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_clear(pt_string));

    string_destroy(pt_string);
}

void test_string_clear__empty_string_container(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);

    string_clear(pt_string);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_clear__non_empty_string_container(void** state)
{
    size_t t_oldcapacity = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 198, 'a');

    string_clear(pt_string);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

/*
 * test string_swap
 */
UT_CASE_DEFINATION(string_swap)
void test_string_swap__null_first(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_swap(NULL, pt_string));

    string_destroy(pt_string);
}

void test_string_swap__null_second(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_swap(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_swap__non_inited_first(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_second);

    expect_assert_failure(string_swap(pt_first, pt_second));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_swap__non_inited_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_first);

    expect_assert_failure(string_swap(pt_first, pt_second));

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_swap__string_equal(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_first);
    string_init(pt_second);

    string_swap(pt_first, pt_second);

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_swap__0_swap_10(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    size_t i = 0;

    string_init(pt_first);
    string_init_char(pt_second, 10, 'a');

    t_firstsize = string_size(pt_first);
    t_secondsize = string_size(pt_second);
    string_swap(pt_first, pt_second);

    assert_true(string_size(pt_first) == t_secondsize);
    assert_true(string_size(pt_second) == t_firstsize);
    for(i = 0; i < string_size(pt_first); ++i)
    {
        assert_true(*(char*)string_at(pt_first, i) == 'a');
    }

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_swap__10_swap_0(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    size_t i = 0;

    string_init_char(pt_first, 10, 'a');
    string_init(pt_second);

    t_firstsize = string_size(pt_first);
    t_secondsize = string_size(pt_second);
    string_swap(pt_first, pt_second);

    assert_true(string_size(pt_first) == t_secondsize);
    assert_true(string_size(pt_second) == t_firstsize);
    for(i = 0; i < string_size(pt_second); ++i)
    {
        assert_true(*(char*)string_at(pt_second, i) == 'a');
    }

    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_swap__10_swap_10(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    size_t i = 0;

    string_init_char(pt_first, 10, 'a');
    string_init_char(pt_second, 10, 'b');

    t_firstsize = string_size(pt_first);
    t_secondsize = string_size(pt_second);
    string_swap(pt_first, pt_second);

    assert_true(string_size(pt_first) == t_secondsize);
    assert_true(string_size(pt_second) == t_firstsize);
    for(i = 0; i < string_size(pt_first); ++i)
    {
        assert_true(*(char*)string_at(pt_first, i) == 'b');
    }
    for(i = 0; i < string_size(pt_second); ++i)
    {
        assert_true(*(char*)string_at(pt_second, i) == 'a');
    }

    string_destroy(pt_first);
    string_destroy(pt_second);
}

/*
 * test string_reserve
 */
UT_CASE_DEFINATION(string_reserve)
void test_string_reserve__null_string_container(void** state)
{
    expect_assert_failure(string_reserve(NULL, 100));
}

void test_string_reserve__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_reserve(pt_string, 100));    

    string_destroy(pt_string);
}

void test_string_reserve__shrink(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 100, 'a');
    assert_true(string_capacity(pt_string) == 100);
    string_reserve(pt_string, 0);
    assert_true(string_capacity(pt_string) == 100);

    string_destroy(pt_string);
}

void test_string_reserve__not_change(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 100, 'a');
    assert_true(string_capacity(pt_string) == 100);
    string_reserve(pt_string, 100);
    assert_true(string_capacity(pt_string) == 100);

    string_destroy(pt_string);
}

void test_string_reserve__expand(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 100, 'a');
    assert_true(string_capacity(pt_string) == 100);
    string_reserve(pt_string, 850);
    assert_true(string_capacity(pt_string) == 850);

    string_destroy(pt_string);
}

/*
 * test string_assign
 */
UT_CASE_DEFINATION(string_assign)
void test_string_assign__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_assign(NULL, pt_string));

    string_destroy(pt_string);
}

void test_string_assign__null_src(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_assign(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_assign__non_inited_dest(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_src);

    expect_assert_failure(string_assign(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__non_inited_src(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);

    expect_assert_failure(string_assign(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__same_container(void** state)
{
    string_t* pvec = create_string();

    string_init(pvec);

    string_assign(pvec, pvec);
    assert_true(string_size(pvec) == 0);

    string_destroy(pvec);
}

void test_string_assign__0_assign_0(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init(pt_src);

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__0_assign_10(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init_char(pt_src, 10, 'a');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__0_assign_1000(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init_char(pt_src, 1000, 'a');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__10_assign_0(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 'a');
    string_init(pt_src);

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__10_assign_10_string_equal(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 'a');
    string_init_char(pt_src, 10, 'a');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__10_assign_10_string_not_equal(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 'a');
    string_init_char(pt_src, 10, 'b');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__10_assign_1000(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 'a');
    string_init_char(pt_src, 1000, 'b');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__1000_assign_0(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 1000, 'a');
    string_init(pt_src);

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__1000_assign_10(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 1000, 'a');
    string_init_char(pt_src, 10, 'b');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__1000_assign_1010(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 1000, 'a');
    string_init_char(pt_src, 1010, 'b');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign__1000_assign_1810(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 1000, 'a');
    string_init_char(pt_src, 1810, 'b');

    string_assign(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

/*
 * test string_assign_substring
 */
UT_CASE_DEFINATION(string_assign_substring)
void test_string_assign_substring__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_assign_substring(NULL, pt_string, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_assign_substring__null_src(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_assign_substring(pt_string, NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_assign_substring__non_inited_dest(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_src, 10, 100);
    expect_assert_failure(string_assign_substring(pt_dest, pt_src, 0, NPOS));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__non_inited_src(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 100);
    expect_assert_failure(string_assign_substring(pt_dest, pt_src, 0, NPOS));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_begin_empty(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init_char(pt_src, 10, 'a');

    string_assign_substring(pt_dest, pt_src, 0, 0);
    assert_true(string_size(pt_dest) == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_begin_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, 0, 3);
    assert_true(string_size(pt_dest) == 3);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_begin_length(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 2, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, 0, string_length(pt_src));
    assert_true(string_size(pt_dest) == string_length(pt_src));
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_begin_npos(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 87, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, 0, NPOS);
    assert_true(string_size(pt_dest) == string_length(pt_src));
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_middle_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 10, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, 3, 0);
    assert_true(string_size(pt_dest) == 0);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_middle_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 1, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, 3, 4);
    assert_true(string_size(pt_dest) == 4);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_middle_length(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, 3, string_length(pt_src)-3);
    assert_true(string_size(pt_dest) == 7);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_middle_npos(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 100, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, 3, NPOS);
    assert_true(string_size(pt_dest) == 7);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_end(void** state)
{
    int i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_assign_substring(pt_dest, pt_src, string_length(pt_src), NPOS);
    assert_true(string_size(pt_dest) == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_substring__successfully_src_non_empty_npos(void** state)
{
    int i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    expect_assert_failure(string_assign_substring(pt_dest, pt_src, NPOS, NPOS));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

/*
 * test string_assign_range
 */
UT_CASE_DEFINATION(string_assign_range)
void test_string_assign_range__null_dest(void** state)
{
    string_t* pt = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt);
    it_begin = string_begin(pt);
    it_end = string_end(pt);

    expect_assert_failure(string_assign_range(NULL, it_begin, it_end));

    string_destroy(pt);
}

void test_string_assign_range__non_inited_dest(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_src);
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    expect_assert_failure(string_assign_range(pt_dest, it_begin, it_end));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_range__invalid_begin_iterator(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init(pt_src);
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    it_begin._t_iteratortype = 23445;
    expect_assert_failure(string_assign_range(pt_dest, it_begin, it_end));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_range__invalid_end_iterator(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init(pt_src);
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    it_end._t_containertype = 9999;
    expect_assert_failure(string_assign_range(pt_dest, it_begin, it_end));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_range__invalid_range(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init_char(pt_src, 19, 'a');
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    expect_assert_failure(string_assign_range(pt_dest, it_end, it_begin));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_range__successfully_empty_range(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_dest, 22, 'a');
    string_init_char(pt_src, 19, 'b');
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    string_assign_range(pt_dest, it_begin, it_begin);
    assert_true(string_size(pt_dest) == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_assign_range__successfully(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }
    it_begin = iterator_next_n(string_begin(pt_src), 3);
    it_end = iterator_next_n(it_begin, 5);

    string_assign_range(pt_dest, it_begin, it_end);
    assert_true(string_size(pt_dest) == iterator_distance(it_begin, it_end));
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

/*
 * test string_assign_cstr
 */
UT_CASE_DEFINATION(string_assign_cstr)
void test_string_assign_cstr__null_container(void** state)
{
    expect_assert_failure(string_assign_cstr(NULL, "abcdef"));
}

void test_string_assign_cstr__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_assign_cstr(pt_string, "abcdefg"));

    string_destroy(pt_string);
}

void test_string_assign_cstr__null_valuestring(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_assign_cstr(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_assign_cstr__empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_assign_cstr(pt_string, "");
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_assign_cstr__non_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 30, 'a');
    string_assign_cstr(pt_string, "abc");
    assert_true(string_size(pt_string) == 3);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'b');
    assert_true(*(char*)string_at(pt_string, 2) == 'c');

    string_destroy(pt_string);
}

/*
 * test string_assign_subcstr
 */
UT_CASE_DEFINATION(string_assign_subcstr)
void test_string_assign_subcstr__null_container(void** state)
{
    expect_assert_failure(string_assign_subcstr(NULL, "abcdef", 0));
}

void test_string_assign_subcstr__non_created_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_assign_subcstr(pt_string, "abcdefg", NPOS));

    string_destroy(pt_string);
}

void test_string_assign_subcstr__null_valuestring(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_assign_subcstr(pt_string, NULL, NPOS));

    string_destroy(pt_string);
}

void test_string_assign_subcstr__empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_assign_subcstr(pt_string, "abcd", 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_assign_subcstr__non_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_assign_subcstr(pt_string, "abcd", 2);
    assert_true(string_size(pt_string) == 2);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'b');

    string_destroy(pt_string);
}

void test_string_assign_subcstr__total(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_assign_subcstr(pt_string, "abc", 3);
    assert_true(string_size(pt_string) == 3);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'b');
    assert_true(*(char*)string_at(pt_string, 2) == 'c');

    string_destroy(pt_string);
}

/*
 * test string_assign_char
 */
UT_CASE_DEFINATION(string_assign_char)
void test_string_assign_char__null_container(void** state)
{
    expect_assert_failure(string_assign_char(NULL, 10, 'a'));
}

void test_string_assign_char__non_inited_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_assign_char(pt_string, 111, 'a'));

    string_destroy(pt_string);
}

void test_string_assign_char__empty_container_assign_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_assign_char(pt_string, 0, 'a');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_assign_char__empty_container_assign_non_empty(void** state)
{
    int i = 0;
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_assign_char(pt_string, 3, 'a');
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < 3; ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_assign_char__non_empty_container_assign_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 4, 'a');
    string_assign_char(pt_string, 0, 'b');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_assign_char__non_empty_container_assign_less(void** state)
{
    int i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 4, 'a');
    string_assign_char(pt_string, 2, 'b');
    assert_true(string_size(pt_string) == 2);
    for(i = 0; i < 2; ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'b');
    }

    string_destroy(pt_string);
}

void test_string_assign_char__non_empty_container_assign_equal(void** state)
{
    int i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 4, 'a');
    string_assign_char(pt_string, 4, 'b');
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < 4; ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'b');
    }

    string_destroy(pt_string);
}

void test_string_assign_char__non_empty_container_assign_greater(void** state)
{
    int i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 4, 'a');
    string_assign_char(pt_string, 100, 'b');
    assert_true(string_size(pt_string) == 100);
    for(i = 0; i < 100; ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'b');
    }

    string_destroy(pt_string);
}

/*
 * test string_append
 */
UT_CASE_DEFINATION(string_append)
void test_string_append__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_append(NULL, pt_string));

    string_destroy(pt_string);
}

void test_string_append__null_src(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_append(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_append__non_inited_dest(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_src);

    expect_assert_failure(string_append(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append__non_inited_src(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);

    expect_assert_failure(string_append(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append__same_container(void** state)
{
    string_t* pvec = create_string();

    string_init_char(pvec, 10, 'a');

    string_append(pvec, pvec);
    assert_true(string_size(pvec) == 20);

    string_destroy(pvec);
}

void test_string_append__0_assign_0(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init(pt_src);

    string_append(pt_dest, pt_src);
    assert_true(string_size(pt_dest) == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append__0_assign_10(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init_char(pt_src, 10, 'a');

    string_append(pt_dest, pt_src);
    assert_true(string_equal(pt_dest, pt_src));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append__10_assign_0(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 'a');
    string_init(pt_src);

    string_append(pt_dest, pt_src);
    assert_true(string_size(pt_dest) == 10);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append__1000_assign_1810(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 1000, 'a');
    string_init_char(pt_src, 1810, 'b');

    string_append(pt_dest, pt_src);
    assert_true(string_size(pt_dest) == 2810);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'b');
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

/*
 * test string_append_substring
 */
UT_CASE_DEFINATION(string_append_substring)
void test_string_append_substring__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_append_substring(NULL, pt_string, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_append_substring__null_src(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_append_substring(pt_string, NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_append_substring__non_inited_dest(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_src, 10, 'a');
    expect_assert_failure(string_append_substring(pt_dest, pt_src, 0, NPOS));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__non_inited_src(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 10, 'a');
    expect_assert_failure(string_append_substring(pt_dest, pt_src, 0, NPOS));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_begin_empty(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init_char(pt_src, 10, 'a');

    string_append_substring(pt_dest, pt_src, 0, 0);
    assert_true(string_size(pt_dest) == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_begin_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, 0, 3);
    assert_true(string_size(pt_dest) == 3);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_begin_length(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 2, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, 0, string_length(pt_src));
    assert_true(string_size(pt_dest) == 12);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 2)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a' + i - 2);
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_begin_npos(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 87, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, 0, NPOS);
    assert_true(string_size(pt_dest) == 97);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 87)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a' + i - 87);
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_middle_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 10, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, 3, 0);
    assert_true(string_size(pt_dest) == 10);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'x');
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_middle_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 1, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, 3, 4);
    assert_true(string_size(pt_dest) == 5);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 1)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3 - 1);
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_middle_length(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, 3, string_length(pt_src)-3);
    assert_true(string_size(pt_dest) == 7);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_middle_npos(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init_char(pt_dest, 100, 'x');
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, 3, NPOS);
    assert_true(string_size(pt_dest) == 107);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 100)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3 - 100);
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_end(void** state)
{
    int i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    string_append_substring(pt_dest, pt_src, string_length(pt_src), NPOS);
    assert_true(string_size(pt_dest) == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_substring__successfully_src_non_empty_npos(void** state)
{
    int i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }

    expect_assert_failure(string_append_substring(pt_dest, pt_src, NPOS, NPOS));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

/*
 * test string_append_range
 */
UT_CASE_DEFINATION(string_append_range)
void test_string_append_range__null_dest(void** state)
{
    string_t* pt = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt);
    it_begin = string_begin(pt);
    it_end = string_end(pt);

    expect_assert_failure(string_append_range(NULL, it_begin, it_end));

    string_destroy(pt);
}

void test_string_append_range__non_inited_dest(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_src);
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    expect_assert_failure(string_append_range(pt_dest, it_begin, it_end));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_range__invalid_begin_iterator(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init(pt_src);
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    it_begin._t_iteratortype = 23445;
    expect_assert_failure(string_append_range(pt_dest, it_begin, it_end));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_range__invalid_end_iterator(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init(pt_src);
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    it_end._t_containertype = 9999;
    expect_assert_failure(string_append_range(pt_dest, it_begin, it_end));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_range__invalid_range(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init_char(pt_src, 19, 'a');
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    expect_assert_failure(string_append_range(pt_dest, it_end, it_begin));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_range__successfully_empty_range(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_dest, 22, 'x');
    string_init_char(pt_src, 19, 'z');
    it_begin = string_begin(pt_src);
    it_end = string_end(pt_src);

    string_append_range(pt_dest, it_begin, it_begin);
    assert_true(string_size(pt_dest) == 22);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'x');
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_range__successfully(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_src, 'a' + i);
    }
    it_begin = iterator_next_n(string_begin(pt_src), 3);
    it_end = iterator_next_n(it_begin, 5);

    string_append_range(pt_dest, it_begin, it_end);
    assert_true(string_size(pt_dest) == iterator_distance(it_begin, it_end));
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a' + i + 3);
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_append_range__same_container(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 22, 'a');
    it_begin = string_begin(pt_string);
    it_end = string_end(pt_string);

    string_append_range(pt_string, it_begin, it_end);
    assert_true(string_size(pt_string) == 44);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

/*
 * test string_append_cstr
 */
UT_CASE_DEFINATION(string_append_cstr)
void test_string_append_cstr__null_container(void** state)
{
    expect_assert_failure(string_append_cstr(NULL, "abcdef"));
}

void test_string_append_cstr__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_append_cstr(pt_string, "abcdefg"));

    string_destroy(pt_string);
}

void test_string_append_cstr__null_valuestring(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_append_cstr(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_append_cstr__empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_append_cstr(pt_string, "");
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_append_cstr__non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 30, 'x');
    string_append_cstr(pt_string, "aaa");
    assert_true(string_size(pt_string) == 33);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 30)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

/*
 * test string_append_subcstr
 */
UT_CASE_DEFINATION(string_append_subcstr)
void test_string_append_subcstr__null_container(void** state)
{
    expect_assert_failure(string_append_subcstr(NULL, "abcdef", 0));
}

void test_string_append_subcstr__non_created_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_append_subcstr(pt_string, "abcdefg", NPOS));

    string_destroy(pt_string);
}

void test_string_append_subcstr__null_valuestring(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_append_subcstr(pt_string, NULL, NPOS));

    string_destroy(pt_string);
}

void test_string_append_subcstr__empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_append_subcstr(pt_string, "abcde", 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_append_subcstr__non_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_append_subcstr(pt_string, "abcde", 2);
    assert_true(string_size(pt_string) == 2);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'b');

    string_destroy(pt_string);
}

void test_string_append_subcstr__total(void** state)
{
    string_t* pt_string = create_string();
    char elem[] = {'a', 'b', 'c', '\0', 'd', 'e'};

    string_init(pt_string);
    string_append_subcstr(pt_string, elem, 6);
    assert_true(string_size(pt_string) == 6);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'b');
    assert_true(*(char*)string_at(pt_string, 2) == 'c');
    assert_true(*(char*)string_at(pt_string, 3) == '\0');
    assert_true(*(char*)string_at(pt_string, 4) == 'd');
    assert_true(*(char*)string_at(pt_string, 5) == 'e');

    string_destroy(pt_string);
}

/*
 * test string_append_char
 */
UT_CASE_DEFINATION(string_append_char)
void test_string_append_char__null_container(void** state)
{
    expect_assert_failure(string_append_char(NULL, 1, 100));
}

void test_string_append_char__non_inited_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_append_char(pt_string, 0, 111));

    string_destroy(pt_string);
}

void test_string_append_char__empty_append_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_append_char(pt_string, 0, 'a');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_append_char__empty_append_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_append_char(pt_string, 10, 'a');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_append_char__non_empty_append_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    string_append_char(pt_string, 0, 'b');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_append_char__non_empty_append_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    string_append_char(pt_string, 10, 'b');
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'b');
        }
    }

    string_destroy(pt_string);
}

/*
 * test string_insert
 */
UT_CASE_DEFINATION(string_insert)
void test_string_insert__null_string_container(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_insert(NULL, string_begin(pt_string), 'a'));

    string_destroy(pt_string);
}

void test_string_insert__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_insert(pt_string, string_begin(pt_string), 'a'));

    string_destroy(pt_string);
}

void test_string_insert__invalid_position(void** state)
{
    string_iterator_t it_pos;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');
    it_pos = string_begin(pt_string);
    it_pos._t_pos._pby_corepos = NULL;

    expect_assert_failure(string_insert(pt_string, it_pos, 'a'));

    string_destroy(pt_string);
}

void test_string_insert__empty(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    it_pos = string_begin(pt_string);
    it_iter = string_insert(pt_string, it_pos, 'a');
    assert_true(iterator_equal(it_iter, string_begin(pt_string)));
    assert_true(string_size(pt_string) == 1);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');

    string_destroy(pt_string);
}

void test_string_insert__begin(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_begin(pt_string);
    it_iter = string_insert(pt_string, it_pos, 'x');
    assert_true(iterator_equal(it_iter, string_begin(pt_string)));
    assert_true(string_size(pt_string) == 1001);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 1)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert__middle(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = iterator_next_n(string_begin(pt_string), 300);
    it_iter = string_insert(pt_string, it_pos, 'x');
    assert_true(iterator_equal(it_iter, iterator_next_n(string_begin(pt_string), 300)));
    assert_true(string_size(pt_string) == 1001);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i == 300)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert__end(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_end(pt_string);
    it_iter = string_insert(pt_string, it_pos, 'x');
    assert_true(iterator_equal(it_iter, iterator_prev(string_end(pt_string))));
    assert_true(string_size(pt_string) == 1001);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

/*
 * test string_insert_n
 */
UT_CASE_DEFINATION(string_insert_n)
void test_string_insert_n__null_string_container(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_insert_n(NULL, string_begin(pt_string), 10, 'a'));

    string_destroy(pt_string);
}

void test_string_insert_n__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_insert_n(pt_string, string_begin(pt_string), 10, 'a'));

    string_destroy(pt_string);
}

void test_string_insert_n__invalid_position(void** state)
{
    string_iterator_t it_pos;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'x');
    it_pos = string_begin(pt_string);
    it_pos._t_pos._pby_corepos = NULL;

    expect_assert_failure(string_insert_n(pt_string, it_pos, 10, 'a'));

    string_destroy(pt_string);
}

void test_string_insert_n__empty_insert_0(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    it_pos = string_begin(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 0, 'x');
    assert_true(iterator_equal(it_iter, it_pos));
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_insert_n__empty_insert_10(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    it_pos = string_begin(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 10, 'x');
    assert_true(iterator_equal(it_iter, string_begin(pt_string)));
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
}

void test_string_insert_n__empty_insert_1000(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    it_pos = string_begin(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 1000, 'x');
    assert_true(iterator_equal(it_iter, string_begin(pt_string)));
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
}

void test_string_insert_n__begin_insert_0(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_begin(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 0, 'x');
    assert_true(iterator_equal(it_iter, string_begin(pt_string)));
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_n__begin_insert_10(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_begin(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 10, 'x');
    assert_true(iterator_equal(it_iter, string_begin(pt_string)));
    assert_true(string_size(pt_string) == 1010);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_n__begin_insert_1000(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_begin(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 1000, 'x');
    assert_true(iterator_equal(it_iter, string_begin(pt_string)));
    assert_true(string_size(pt_string) == 2000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_n__middle_insert_0(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = iterator_next_n(string_begin(pt_string), 300);
    it_iter = string_insert_n(pt_string, it_pos, 0, 'x');
    assert_true(iterator_equal(it_iter, iterator_next_n(string_begin(pt_string), 300)));
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_n__middle_insert_10(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = iterator_next_n(string_begin(pt_string), 300);
    it_iter = string_insert_n(pt_string, it_pos, 10, 'x');
    assert_true(iterator_equal(it_iter, iterator_next_n(string_begin(pt_string), 300)));
    assert_true(string_size(pt_string) == 1010);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 300 && i < 310)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_n__middle_insert_1000(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = iterator_next_n(string_begin(pt_string), 300);
    it_iter = string_insert_n(pt_string, it_pos, 1000, 'x');
    assert_true(iterator_equal(it_iter, iterator_next_n(string_begin(pt_string), 300)));
    assert_true(string_size(pt_string) == 2000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 300 && i < 1300)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_n__end_insert_0(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_end(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 0, 'x');
    assert_true(iterator_equal(it_iter, string_end(pt_string)));
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_n__end_insert_10(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_end(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 10, 'x');
    assert_true(iterator_equal(it_iter, iterator_next_n(string_begin(pt_string), 1000)));
    assert_true(string_size(pt_string) == 1010);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_n__end_insert_1000(void** state)
{
    string_iterator_t it_pos;
    string_iterator_t it_iter;
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    it_pos = string_end(pt_string);
    it_iter = string_insert_n(pt_string, it_pos, 1000, 'x');
    assert_true(iterator_equal(it_iter, iterator_next_n(string_begin(pt_string), 1000)));
    assert_true(string_size(pt_string) == 2000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

/*
 * test string_insert_string
 */
UT_CASE_DEFINATION(string_insert_string)
void test_string_insert_string__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_insert_string(NULL, 0, pt_string));

    string_destroy(pt_string);
}

void test_string_insert_string__null_insert(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_insert_string(pt_string, 0, NULL));

    string_destroy(pt_string);
}

void test_string_insert_string__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init(pt_insert);

    expect_assert_failure(string_insert_string(pt_string, 0, pt_insert));

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_string__non_inited_insert(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_insert_string(pt_string, 0, pt_insert));

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_string__same_container(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_insert_string(pt_string, 0, pt_string);
    assert_true(string_size(pt_string) == 20);

    string_destroy(pt_string);
}

void test_string_insert_string__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_insert);

    expect_assert_failure(string_insert_string(pt_string, 180, pt_insert));

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_string__char_middle_insert_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_insert);

    string_insert_string(pt_string, 4, pt_insert);
    assert_true(string_size(pt_string) == 10);

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_string__char_begin_insert_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_insert, 5, 'n');

    string_insert_string(pt_string, 0, pt_insert);
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'n');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

/*
 * test string_insert_substring
 */
UT_CASE_DEFINATION(string_insert_substring)
void test_string_insert_substring__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_insert_substring(NULL, 0, pt_string, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_insert_substring__null_insert(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_insert_substring(pt_string, 0, NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_insert_substring__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_insert, 10, 'a');

    expect_assert_failure(string_insert_substring(pt_string, 0, pt_insert, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_substring__non_inited_insert(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_insert_substring(pt_string, 0, pt_insert, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_substring__same_container(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_insert_substring(pt_string, 0, pt_string, 0, NPOS);
    assert_true(string_size(pt_string) == 20);

    string_destroy(pt_string);
}

void test_string_insert_substring__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_insert, 10, 'a');

    expect_assert_failure(string_insert_substring(pt_string, 180, pt_insert, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_substring__invalid_startpos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_insert, 10, 'a');

    expect_assert_failure(string_insert_substring(pt_string, 0, pt_insert, 120, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_substring__char_middle_insert_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_insert, 10, 'x');

    string_insert_substring(pt_string, 4, pt_insert, 0, 0);
    assert_true(string_size(pt_string) == 10);

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

void test_string_insert_substring__char_begin_insert_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_insert = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_insert, 15, 'n');

    string_insert_substring(pt_string, 0, pt_insert, 5, 5);
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'n');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_insert);
}

/*
 * test string_insert_cstr
 */
UT_CASE_DEFINATION(string_insert_cstr)
void test_string_insert_cstr__null_container(void** state)
{
    expect_assert_failure(string_insert_cstr(NULL, 0, "abcdef"));
}

void test_string_insert_cstr__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_insert_cstr(pt_string, 0, "abcdefg"));

    string_destroy(pt_string);
}

void test_string_insert_cstr__null_valuestring(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_insert_cstr(pt_string, 0, NULL));

    string_destroy(pt_string);
}

void test_string_insert_cstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abc");
    expect_assert_failure(string_insert_cstr(pt_string, 178, "abcdefg"));

    string_destroy(pt_string);
}

void test_string_insert_cstr__char_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefg");
    string_insert_cstr(pt_string, 3, "");
    assert_true(string_size(pt_string) == 7);

    string_destroy(pt_string);
}

void test_string_insert_cstr__char_non_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 2, 'x');
    string_insert_cstr(pt_string, 1, "abc");
    assert_true(string_size(pt_string) == 5);
    assert_true(*(char*)string_at(pt_string, 0) == 'x');
    assert_true(*(char*)string_at(pt_string, 1) == 'a');
    assert_true(*(char*)string_at(pt_string, 2) == 'b');
    assert_true(*(char*)string_at(pt_string, 3) == 'c');
    assert_true(*(char*)string_at(pt_string, 4) == 'x');

    string_destroy(pt_string);
}

/*
 * test string_insert_subcstr
 */
UT_CASE_DEFINATION(string_insert_subcstr)
void test_string_insert_subcstr__null_container(void** state)
{
    expect_assert_failure(string_insert_subcstr(NULL, 0, "abcdef", 0));
}

void test_string_insert_subcstr__non_created_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_insert_subcstr(pt_string, 0, "abcdefg", NPOS));

    string_destroy(pt_string);
}

void test_string_insert_subcstr__null_valuestring(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_insert_subcstr(pt_string, 0, NULL, NPOS));

    string_destroy(pt_string);
}

void test_string_insert_subcstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abc");
    expect_assert_failure(string_insert_subcstr(pt_string, 178, "abcdefg", NPOS));

    string_destroy(pt_string);
}

void test_string_insert_subcstr__char_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "xxxxxxxxxx");
    string_insert_subcstr(pt_string, 3, "abc", 0);
    assert_true(string_size(pt_string) == 10);
    assert_true(strncmp((char*)string_c_str(pt_string), "xxxxxxxxxx", 10) == 0);

    string_destroy(pt_string);
}

void test_string_insert_subcstr__char_non_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "xxxxxxxxxx");
    string_insert_subcstr(pt_string, 2, "abc", 1);
    assert_true(string_size(pt_string) == 11);
    assert_true(strncmp((char*)string_c_str(pt_string), "xxaxxxxxxxx", 11) == 0);

    string_destroy(pt_string);
}

void test_string_insert_subcstr__char_total(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "xxxxxxxxxx");
    string_insert_subcstr(pt_string, 5, "abc", 3);
    assert_true(string_size(pt_string) == 13);
    assert_true(strncmp((char*)string_c_str(pt_string), "xxxxxabcxxxxx", 13) == 0);

    string_destroy(pt_string);
}

/*
 * test string_insert_range
 */
UT_CASE_DEFINATION(string_insert_range)
void test_string_insert_range__null_string(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init(pt_src);
    expect_assert_failure(string_insert_range(NULL, string_begin(pt_dest),
        string_begin(pt_src), string_end(pt_src)));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__non_inited_string(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_src);
    expect_assert_failure(string_insert_range(pt_dest, string_begin(pt_dest),
        string_begin(pt_src), string_end(pt_src)));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__invalid_pos(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_pos;

    string_init(pt_dest);
    string_init(pt_src);
    it_pos._t_containertype = 3333;
    expect_assert_failure(string_insert_range(pt_dest, it_pos,
        string_begin(pt_src), string_end(pt_src)));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__invalid_begin(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_begin;

    string_init(pt_dest);
    string_init(pt_src);
    it_begin._t_iteratortype = 11111;
    expect_assert_failure(string_insert_range(pt_dest, string_begin(pt_dest),
        it_begin, string_end(pt_src)));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__invalid_end(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();
    string_iterator_t it_end;

    string_init(pt_dest);
    string_init(pt_src);
    it_end._t_iteratortype = 11111;
    expect_assert_failure(string_insert_range(pt_dest, string_begin(pt_dest),
        string_begin(pt_src), it_end));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__invalid_range(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init_char(pt_src, 10, 'a');
    expect_assert_failure(string_insert_range(pt_dest, string_begin(pt_dest),
        string_end(pt_src), string_begin(pt_src)));

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__range_belong_to_dest(void** state)
{
    string_t* pt_dest = create_string();

    string_init_char(pt_dest, 10, 'a');
    string_insert_range(pt_dest, string_begin(pt_dest),
        string_begin(pt_dest), string_end(pt_dest));
    assert_true(string_size(pt_dest) == 20);

    string_destroy(pt_dest);
}

void test_string_insert_range__empty_insert_empty(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init(pt_src);
    string_insert_range(pt_dest, string_begin(pt_dest), string_begin(pt_src), string_end(pt_src));
    assert_true(string_size(pt_dest) == 0);

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__empty_insert_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    string_init_char(pt_src, 10, 'a');
    string_insert_range(pt_dest, string_end(pt_dest), string_begin(pt_src), string_end(pt_src));
    assert_true(string_size(pt_dest) == 10);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a');
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__non_empty_insert_begin_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 5, 'a');
    string_init_char(pt_src, 10, 'x');
    string_insert_range(pt_dest, string_begin(pt_dest), string_end(pt_src), string_end(pt_src));
    assert_true(string_size(pt_dest) == 5);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a');
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__non_empty_insert_middle_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 5, 'a');
    string_init_char(pt_src, 10, 'x');
    string_insert_range(pt_dest, iterator_next(string_begin(pt_dest)),
        string_begin(pt_src), string_begin(pt_src));
    assert_true(string_size(pt_dest) == 5);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a');
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__non_empty_insert_end_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 5, 'a');
    string_init(pt_src);
    string_insert_range(pt_dest, string_end(pt_dest),
        string_begin(pt_src), string_end(pt_src));
    assert_true(string_size(pt_dest) == 5);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        assert_true(*(char*)string_at(pt_dest, i) == 'a');
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__non_empty_insert_begin_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 5, 'a');
    string_init_char(pt_src, 10, 'x');
    string_insert_range(pt_dest, string_begin(pt_dest),
        string_begin(pt_src), string_end(pt_src));
    assert_true(string_size(pt_dest) == 15);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a');
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__non_empty_insert_middle_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 5, 'a');
    string_init_char(pt_src, 10, 'x');
    string_insert_range(pt_dest, iterator_next(string_begin(pt_dest)),
        string_begin(pt_src), iterator_next_n(string_begin(pt_src), 5));
    assert_true(string_size(pt_dest) == 10);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 1 || i > 5)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'x');
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_insert_range__non_empty_insert_end_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init_char(pt_dest, 5, 'a');
    string_init_char(pt_src, 10, 'x');
    string_insert_range(pt_dest, string_end(pt_dest),
        iterator_prev_n(string_end(pt_src), 7), string_end(pt_src));
    assert_true(string_size(pt_dest) == 12);
    for(i = 0; i < string_size(pt_dest); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_dest, i) == 'x');
        }
    }

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

/*
 * test string_insert_char
 */
UT_CASE_DEFINATION(string_insert_char)
void test_string_insert_char__null_string_container(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_insert_char(NULL, 0, 10, 'a'));

    string_destroy(pt_string);
}

void test_string_insert_char__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_insert_char(pt_string, 0, 10, 'a'));

    string_destroy(pt_string);
}

void test_string_insert_char__invalid_position(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 0);

    expect_assert_failure(string_insert_char(pt_string, 100, 10, 'a'));

    string_destroy(pt_string);
}

void test_string_insert_char__empty_insert_0(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    string_insert_char(pt_string, 0, 0, 'a');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_insert_char__empty_insert_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    string_insert_char(pt_string, 0, 10, 'a');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_char__empty_insert_1000(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    string_insert_char(pt_string, 0, 1000, 'a');
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_char__begin_insert_0(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 0, 0, 'x');
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_char__begin_insert_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 0, 10, 'x');
    assert_true(string_size(pt_string) == 1010);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_char__begin_insert_1000(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 0, 1000, 'x');
    assert_true(string_size(pt_string) == 2000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_char__middle_insert_0(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 300, 0, 'x');
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_char__middle_insert_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 300, 10, 'x');
    assert_true(string_size(pt_string) == 1010);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 300 && i < 310)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_char__middle_insert_1000(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 300, 1000, 'x');
    assert_true(string_size(pt_string) == 2000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 300 && i < 1300)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_char__end_insert_0(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 1000, 0, 'x');
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_insert_char__end_insert_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 1000, 10, 'x');
    assert_true(string_size(pt_string) == 1010);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_insert_char__end_insert_1000(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_insert_char(pt_string, 1000, 1000, 'x');
    assert_true(string_size(pt_string) == 2000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

/*
 * test string_push_back
 */
UT_CASE_DEFINATION(string_push_back)
void test_string_push_back__null_container(void** state)
{
    expect_assert_failure(string_push_back(NULL, 23));
}

void test_string_push_back__non_inited_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_push_back(pt_string, 111));

    string_destroy(pt_string);
}

void test_string_push_back__empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_push_back(pt_string, 'a');
    assert_true(string_size(pt_string) == 1);
    assert_true(*(char*)iterator_get_pointer(iterator_prev(string_end(pt_string))) == 'a');

    string_destroy(pt_string);
}

void test_string_push_back__non_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 100, 'a');
    string_push_back(pt_string, 'x');
    assert_true(string_size(pt_string) == 101);
    assert_true(*(char*)iterator_get_pointer(iterator_prev(string_end(pt_string))) == 'x');

    string_destroy(pt_string);
}

/*
 * test string_resize_char
 */
UT_CASE_DEFINATION(string_resize_char)
void test_string_resize_char__null_string_container(void** state)
{
    expect_assert_failure(string_resize_char(NULL, 10, 'a'));
}

void test_string_resize_char__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_resize_char(pt_string, 10, 'a'));

    string_destroy(pt_string);
}

void test_string_resize_char__successfully_0_resize_0(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    string_resize_char(pt_string, 0, 'a');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_resize_char__successfully_0_resize_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    string_resize_char(pt_string, 10, 'a');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_resize_char__successfully_10_resize_0(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_size(pt_string) == 10);
    string_resize_char(pt_string, 0, 'x');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_resize_char__successfully_10_resize_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_size(pt_string) == 10);
    string_resize_char(pt_string, 10, 'x');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_resize_char__successfully_10_resize_1000(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_size(pt_string) == 10);
    string_resize_char(pt_string, 1000, 'x');
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_resize_char__successfully_1000_resize_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_resize_char(pt_string, 10, 'x');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

/*
 * test string_resize
 */
UT_CASE_DEFINATION(string_resize)
void test_string_resize__null_string_container(void** state)
{
    expect_assert_failure(string_resize(NULL, 10));
}

void test_string_resize__non_inited(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_resize(pt_string, 10));

    string_destroy(pt_string);
}

void test_string_resize__successfully_0_resize_0(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    string_resize(pt_string, 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_resize__successfully_0_resize_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init(pt_string);

    assert_true(string_size(pt_string) == 0);
    string_resize(pt_string, 10);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == '\0');
    }

    string_destroy(pt_string);
}

void test_string_resize__successfully_10_resize_0(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_size(pt_string) == 10);
    string_resize(pt_string, 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_resize__successfully_10_resize_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_size(pt_string) == 10);
    string_resize(pt_string, 10);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_resize__successfully_10_resize_1000(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_size(pt_string) == 10);
    string_resize(pt_string, 1000);
    assert_true(string_size(pt_string) == 1000);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == '\0');
        }
    }

    string_destroy(pt_string);
}

void test_string_resize__successfully_1000_resize_10(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 1000, 'a');

    assert_true(string_size(pt_string) == 1000);
    string_resize(pt_string, 10);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

/*
 * test string_erase
 */
UT_CASE_DEFINATION(string_erase)
void test_string_erase__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    expect_assert_failure(string_erase(NULL, string_begin(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase__non_inited_string(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_non_inited = create_string();

    string_init_char(pt_string, 10, 'a');
    expect_assert_failure(string_erase(pt_non_inited, string_begin(pt_string)));

    string_destroy(pt_string);
    string_destroy(pt_non_inited);
}

void test_string_erase__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_pos;

    string_init_char(pt_string, 10, 'a');
    it_pos = string_begin(pt_string);
    it_pos._t_containertype = 9999;
    expect_assert_failure(string_erase(pt_string, it_pos));

    string_destroy(pt_string);
}

void test_string_erase__empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_erase(pt_string, string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase__begin(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_pos;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }

    it_pos = string_erase(pt_string, string_begin(pt_string));
    assert_true(string_size(pt_string) == 9);
    assert_true(*(char*)iterator_get_pointer(it_pos) == 'a' + 1);

    string_destroy(pt_string);
}

void test_string_erase__middle(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_pos;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }

    it_pos = string_erase(pt_string, iterator_next(string_begin(pt_string)));
    assert_true(string_size(pt_string) == 9);
    assert_true(*(char*)iterator_get_pointer(it_pos) == 'a' + 2);

    string_destroy(pt_string);
}

void test_string_erase__last(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_pos;

    string_init(pt_string);
    for(i = 0; i < 10; ++i)
    {
        string_push_back(pt_string, 'a' + i);
    }

    it_pos = string_erase(pt_string, iterator_prev(string_end(pt_string)));
    assert_true(string_size(pt_string) == 9);
    assert_true(iterator_equal(it_pos, string_end(pt_string)));

    string_destroy(pt_string);
}

/*
 * test string_erase_range
 */
UT_CASE_DEFINATION(string_erase_range)
void test_string_erase_range__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 2, 'a');
    expect_assert_failure(string_erase_range(
        NULL, string_begin(pt_string), string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase_range__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_erase_range(
        pt_string, string_begin(pt_string), string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase_range__invalid_begin(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_begin;

    string_init_char(pt_string, 2, 'a');
    it_begin._t_containertype = 44444;
    expect_assert_failure(string_erase_range(pt_string, it_begin, string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase_range__invalid_end(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_end;

    string_init_char(pt_string, 2, 'a');
    it_end._t_iteratortype = 34455;
    expect_assert_failure(string_erase_range(pt_string, string_begin(pt_string), it_end));

    string_destroy(pt_string);
}

void test_string_erase_range__invalid_range(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 2, 'a');
    expect_assert_failure(string_erase_range(
        pt_string, string_end(pt_string), string_begin(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase_range__empty(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_pos;

    string_init(pt_string);
    it_pos = string_erase_range(
        pt_string, string_end(pt_string), string_begin(pt_string));
    assert_true(string_size(pt_string) == 0);
    assert_true(iterator_equal(it_pos, string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase_range__begin(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_pos;
    /*int elems[] = {4, 2, 6, 9, 1, 0};*/

    string_init_cstr(pt_string, "abcde");
    it_pos = string_erase_range(pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 2));
    assert_true(string_size(pt_string) == 3);
    assert_true(*(char*)iterator_get_pointer(it_pos) == 'c');

    string_destroy(pt_string);
}

void test_string_erase_range__middle(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_pos;
    /*int elems[] = {4, 2, 6, 9, 1, 5, 19, 45, 234, 11, 87, 0};*/

    string_init_cstr(pt_string, "abcdefghijk");
    it_pos = string_erase_range(pt_string, iterator_next(string_begin(pt_string)),
        iterator_next_n(string_begin(pt_string), 5));
    assert_true(string_size(pt_string) == 7);
    assert_true(*(char*)iterator_get_pointer(it_pos) == 'f');

    string_destroy(pt_string);
}

void test_string_erase_range__end(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_pos;
    /*int elems[] = {4, 2, 6, 9, 1, 5, 19, 45, 234, 11, 87, 0};*/

    string_init_cstr(pt_string, "abcdefghijk");
    it_pos = string_erase_range(pt_string, iterator_next_n(string_begin(pt_string), 5),
        string_end(pt_string));
    assert_true(string_size(pt_string) == 5);
    assert_true(iterator_equal(it_pos, string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase_range__all(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_pos;
    /*int elems[] = {4, 2, 6, 9, 1, 5, 19, 45, 234, 11, 87, 0};*/

    string_init_cstr(pt_string, "abcdefghijk");
    it_pos = string_erase_range(pt_string, string_begin(pt_string),
        string_end(pt_string));
    assert_true(string_size(pt_string) == 0);
    assert_true(iterator_equal(it_pos, string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_erase_range__erase_empty(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_pos;
    /*int elems[] = {4, 2, 6, 9, 1, 5, 19, 45, 234, 11, 87, 0};*/

    string_init_cstr(pt_string, "abcdefghijk");
    it_pos = string_erase_range(pt_string, string_begin(pt_string),
        string_begin(pt_string));
    assert_true(string_size(pt_string) == 11);
    assert_true(*(char*)iterator_get_pointer(it_pos) == 'a');

    string_destroy(pt_string);
}

/*
 * test string_erase_substring
 */
UT_CASE_DEFINATION(string_erase_substring)
void test_string_erase_substring__null_string(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_erase_substring(NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_erase_substring__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_erase_substring(pt_string, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_erase_substring__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 3, 'a');
    expect_assert_failure(string_erase_substring(pt_string, 8, NPOS));

    string_destroy(pt_string);
}

void test_string_erase_substring__begin(void** state)
{
    string_t* pt_string = create_string();
    /*int elems[] = {6, 3, 9, 1, 98, 4, 5, 0};*/

    string_init_cstr(pt_string, "abcdefg");
    string_erase_substring(pt_string, 0, 5);
    assert_true(string_size(pt_string) == 2);
    assert_true(*(char*)string_at(pt_string, 0) == 'f');
    assert_true(*(char*)string_at(pt_string, 1) == 'g');

    string_destroy(pt_string);
}

void test_string_erase_substring__middle(void** state)
{
    string_t* pt_string = create_string();
    /*int elems[] = {6, 3, 9, 1, 98, 4, 5, 0};*/

    string_init_cstr(pt_string, "abcdefg");
    string_erase_substring(pt_string, 1, 5);
    assert_true(string_size(pt_string) == 2);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'g');

    string_destroy(pt_string);
}

void test_string_erase_substring__end(void** state)
{
    string_t* pt_string = create_string();
    /*int elems[] = {6, 3, 9, 1, 98, 4, 5, 0};*/

    string_init_cstr(pt_string, "abcdefg");
    string_erase_substring(pt_string, 2, 5);
    assert_true(string_size(pt_string) == 2);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'b');

    string_destroy(pt_string);
}

void test_string_erase_substring__all(void** state)
{
    string_t* pt_string = create_string();
    /*int elems[] = {6, 3, 9, 1, 98, 4, 5, 0};*/

    string_init_cstr(pt_string, "abcdefg");
    string_erase_substring(pt_string, 0, 1234);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_erase_substring__erase_empty(void** state)
{
    string_t* pt_string = create_string();
    /*int elems[] = {6, 3, 9, 1, 98, 4, 5, 0};*/

    string_init_cstr(pt_string, "abcdefg");
    string_erase_substring(pt_string, 4, 0);
    assert_true(string_size(pt_string) == 7);
    assert_true(*(char*)string_at(pt_string, 0) == 'a');
    assert_true(*(char*)string_at(pt_string, 1) == 'b');
    assert_true(*(char*)string_at(pt_string, 2) == 'c');
    assert_true(*(char*)string_at(pt_string, 3) == 'd');
    assert_true(*(char*)string_at(pt_string, 4) == 'e');
    assert_true(*(char*)string_at(pt_string, 5) == 'f');
    assert_true(*(char*)string_at(pt_string, 6) == 'g');

    string_destroy(pt_string);
}

/*
 * test string_replace
 */
UT_CASE_DEFINATION(string_replace)
void test_string_replace__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_replace(NULL, 0, NPOS, pt_string));

    string_destroy(pt_string);
}

void test_string_replace__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_replace(pt_string, 0, NPOS, NULL));

    string_destroy(pt_string);
}

void test_string_replace__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init(pt_replace);

    expect_assert_failure(string_replace(pt_string, 0, NPOS, pt_replace));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__non_inited_replace(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace(pt_string, 0, NPOS, pt_replace));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__same_container(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace(pt_string, 0, NPOS, pt_string);
    assert_true(string_size(pt_string) == 10);

    string_destroy(pt_string);
}

void test_string_replace__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    expect_assert_failure(string_replace(pt_string, 180, NPOS, pt_replace));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_replace(pt_string, 0, 0, pt_replace);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 10, 'x');

    string_replace(pt_string, 0, 0, pt_replace);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_replace(pt_string, 0, 3, pt_replace);
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 10, 'x');

    string_replace(pt_string, 0, 3, pt_replace);
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_replace(pt_string, 3, 0, pt_replace);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 10, 'x');

    string_replace(pt_string, 5, 0, pt_replace);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_replace(pt_string, 3, 5, pt_replace);
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 2, 'x');

    string_replace(pt_string, 5, 3, pt_replace);
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_replace(pt_string, 3, NPOS, pt_replace);
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 5, 'x');

    string_replace(pt_string, 5, 150, pt_replace);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_replace(pt_string, 0, 150, pt_replace);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 4, 'x');

    string_replace(pt_string, 0, NPOS, pt_replace);
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

/*
 * test string_replace_substring
 */
UT_CASE_DEFINATION(string_replace_substring)
void test_string_replace_substring__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_substring(NULL, 0, NPOS, pt_string, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_replace_substring__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_substring(pt_string, 0, NPOS, NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_replace_substring__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_replace, 10, 'a');

    expect_assert_failure(string_replace_substring(pt_string, 0, NPOS, pt_replace, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__non_inited_replace(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_substring(pt_string, 0, NPOS, pt_replace, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__same_container(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_substring(pt_string, 0, NPOS, pt_string, 0, NPOS);
    assert_true(string_size(pt_string) == 10);

    string_destroy(pt_string);
}

void test_string_replace_substring__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'a');

    expect_assert_failure(string_replace_substring(pt_string, 180, NPOS, pt_replace, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__invalid_position(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_replace_substring(pt_string, 8, NPOS, pt_replace, 0, NPOS);
    assert_true(string_size(pt_string) == 8);

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 0, 0, pt_replace, 0, 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 0, 0, pt_replace, 0, 10);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 0, 3, pt_replace, 67, 0);
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 0, 3, pt_replace, 45, 10);
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 3, 0, pt_replace, 66, 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 5, 0, pt_replace, 90, 233);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 3, 5, pt_replace, 5, 0);
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 2, 'x');

    string_replace_substring(pt_string, 5, 3, pt_replace, 0, 55);
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 3, NPOS, pt_replace, 0, 0);
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 5, 'x');

    string_replace_substring(pt_string, 5, 150, pt_replace, 0, NPOS);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_substring(pt_string, 0, 150, pt_replace, 56, 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_substring__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 4, 'x');

    string_replace_substring(pt_string, 0, NPOS, pt_replace, 0, NPOS);
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

/*
 * test string_replace_cstr
 */
UT_CASE_DEFINATION(string_replace_cstr)
void test_string_replace_cstr__null_dest(void** state)
{
    expect_assert_failure(string_replace_cstr(NULL, 0, NPOS, "abcd"));
}

void test_string_replace_cstr__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_cstr(pt_string, 0, NPOS, NULL));

    string_destroy(pt_string);
}

void test_string_replace_cstr__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_replace_cstr(pt_string, 0, NPOS, "abc"));

    string_destroy(pt_string);
}

void test_string_replace_cstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_cstr(pt_string, 180, NPOS, "abc"));

    string_destroy(pt_string);
}

void test_string_replace_cstr__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 0, 0, "");
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 0, 0, "xxxxxxxxxx");
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 0, 3, "");
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 0, 3, "xxxxxxxxxx");
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 3, 0, "");
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 5, 0, "xxxxxxxxxx");
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 3, 5, "");
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 5, 3, "xx");
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 3, NPOS, "");
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 5, 150, "xxxxx");
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_cstr__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 0, 150, "");
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_replace_cstr__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_cstr(pt_string, 0, NPOS, "xxxx");
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
}

/*
 * test string_replace_subcstr
 */
UT_CASE_DEFINATION(string_replace_subcstr)
void test_string_replace_subcstr__null_dest(void** state)
{
    expect_assert_failure(string_replace_subcstr(NULL, 0, NPOS, "abcde", 5));
}

void test_string_replace_subcstr__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_subcstr(pt_string, 0, NPOS, NULL, 0));

    string_destroy(pt_string);
}

void test_string_replace_subcstr__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_replace_subcstr(pt_string, 0, NPOS, "abcd", 4));

    string_destroy(pt_string);
}

void test_string_replace_subcstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_subcstr(pt_string, 180, NPOS, "abc", 3));

    string_destroy(pt_string);
}

void test_string_replace_subcstr__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 0, 0, "abcd", 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 0, 0, "xxxxxx", 5);
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 0, 3, "", 0);
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 0, 3, "xxxxxxxxxxxxx", 10);
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 3, 0, "", 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 5, 0, "xxxxxxxxxx", 10);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 3, 5, "xx", 0);
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 5, 3, "xxxx", 2);
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 3, NPOS, "", 0);
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 5, 150, "xxxxx", 5);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_subcstr__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 0, 150, "", 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_replace_subcstr__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_subcstr(pt_string, 0, NPOS, "xxxx", 4);
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
}

/*
 * test string_replace_char
 */
UT_CASE_DEFINATION(string_replace_char)
void test_string_replace_char__null_container(void** state)
{
    expect_assert_failure(string_replace_char(NULL, 0, 0, 0, 'a'));
}

void test_string_replace_char__non_inited_container(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_replace_char(pt_string, 0, 0, 0, 'a'));

    string_destroy(pt_string);
}

void test_string_replace_char__empty_replace_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    string_replace_char(pt_string, 0, NPOS, 0, 'a');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_replace_char__empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init(pt_string);

    string_replace_char(pt_string, 0, NPOS, 10, 'a');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_replace_char__begin_replace_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 0, 3, 0, 'x');
    assert_true(string_size(pt_string) == 7);

    string_destroy(pt_string);
}

void test_string_replace_char__begin_replace_less(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 0, 3, 1, 'x');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i == 0)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__begin_replace_equal(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 0, 3, 3, 'x');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 3)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__begin_replace_greater(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 0, 3, 8, 'x');
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 8)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__middle_replace_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 1, 3, 0, 'a');
    assert_true(string_size(pt_string) == 7);

    string_destroy(pt_string);
}

void test_string_replace_char__middle_replace_less(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 1, 3, 1, 'x');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i == 1)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__middle_replace_equal(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 1, 3, 3, 'x');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 0 && i < 4)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__middle_replace_greater(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 1, 3, 8, 'x');
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 0 && i < 9)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__end_replace_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 7, 3, 0, 'a');
    assert_true(string_size(pt_string) == 7);

    string_destroy(pt_string);
}

void test_string_replace_char__end_replace_less(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 7, 100, 1, 'x');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i == 7)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__end_replace_equal(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 7, NPOS, 3, 'x');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__end_replace_greater(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 7, NPOS, 8, 'x');
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_replace_char__replace_all(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');

    string_replace_char(pt_string, 0, NPOS, 8, 'x');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
}

/*
 * test string_range_replace
 */
UT_CASE_DEFINATION(string_range_replace)
void test_string_range_replace__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_range_replace(
        NULL, string_begin(pt_string), string_end(pt_string), pt_string));

    string_destroy(pt_string);
}

void test_string_range_replace__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_range_replace(
        pt_string, string_begin(pt_string), string_end(pt_string), NULL));

    string_destroy(pt_string);
}

void test_string_range_replace__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init(pt_replace);

    expect_assert_failure(string_range_replace(
        pt_string, string_begin(pt_replace), string_end(pt_replace), pt_replace));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__non_inited_replace(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_replace));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__same_container(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_string);
    assert_true(string_size(pt_string) == 10);

    string_destroy(pt_string);
}

void test_string_range_replace__invalid_range(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    expect_assert_failure(string_range_replace(
        pt_string, string_end(pt_string), string_begin(pt_string), pt_replace));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_range_replace(
        pt_string, string_begin(pt_string), string_begin(pt_string), pt_replace);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 10, 'x');

    string_range_replace(
        pt_string, string_begin(pt_string), string_begin(pt_string), pt_replace);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_range_replace(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), pt_replace);
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 10, 'x');

    string_range_replace(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), pt_replace);
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_range_replace(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 3), pt_replace);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 10, 'x');

    string_range_replace(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 5), pt_replace);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_range_replace(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 8), pt_replace);
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 2, 'x');

    string_range_replace(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 8), pt_replace);
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_range_replace(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        string_end(pt_string), pt_replace);
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 5, 'x');

    string_range_replace(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        string_end(pt_string), pt_replace);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_range_replace(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_replace);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 4, 'x');

    string_range_replace(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_replace);
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

/*
 * test string_range_replace_substring
 */
UT_CASE_DEFINATION(string_range_replace_substring)
void test_string_range_replace_substring__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace_substring(
        NULL, string_begin(pt_string), string_end(pt_string), pt_string, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_range_replace_substring__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace_substring(
        pt_string, string_begin(pt_string), string_end(pt_string), NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_range_replace_substring__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_replace, 10, 'a');

    expect_assert_failure(string_range_replace_substring(
        pt_string, string_begin(pt_replace), string_end(pt_replace), pt_replace, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__non_inited_replace(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace_substring(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_replace, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__same_container(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_substring(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_string, 0, NPOS);
    assert_true(string_size(pt_string) == 10);

    string_destroy(pt_string);
}

void test_string_range_replace_substring__invalid_range(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'a');

    expect_assert_failure(string_range_replace_substring(
        pt_string, string_end(pt_string), string_begin(pt_string), pt_replace, 0, NPOS));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__invalid_position(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init(pt_replace);

    string_range_replace_substring(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_replace, 0, NPOS);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, string_begin(pt_string), string_begin(pt_string), pt_replace, 0, 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, string_begin(pt_string), string_begin(pt_string), pt_replace, 0, 10);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), pt_replace, 67, 0);
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), pt_replace, 45, 10);
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 3), pt_replace, 66, 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 5), pt_replace, 90, 233);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 8), pt_replace, 5, 0);
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 2, 'x');

    string_range_replace_substring(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 8), pt_replace, 0, 55);
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        string_end(pt_string), pt_replace, 0, 0);
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 5, 'x');

    string_range_replace_substring(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        string_end(pt_string), pt_replace, 0, NPOS);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_range_replace_substring(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_replace, 56, 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_substring__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 4, 'x');

    string_range_replace_substring(
        pt_string, string_begin(pt_string), string_end(pt_string), pt_replace, 0, NPOS);
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

/*
 * test string_range_replace_cstr
 */
UT_CASE_DEFINATION(string_range_replace_cstr)
void test_string_range_replace_cstr__null_dest(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_range_replace_cstr(
        NULL, string_begin(pt_string), string_end(pt_string), "abcd"));

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace_cstr(
        pt_string, string_begin(pt_string), string_end(pt_string), NULL));

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;
    string_init(pt_replace);

    it_begin = string_begin(pt_replace);
    it_end = string_end(pt_replace);
    expect_assert_failure(string_range_replace_cstr(
        pt_string, it_begin, it_end, "abc"));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_cstr__invalid_range(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace_cstr(
        pt_string, string_end(pt_string), string_begin(pt_string), "abc"));

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, string_begin(pt_string), string_begin(pt_string), "");
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, string_begin(pt_string), string_begin(pt_string), "xxxxxxxxxx");
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), "");
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), "xxxxxxxxxx");
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 3), "");
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 5), "xxxxxxxxxx");
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 8), "");
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 8), "xx");
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        string_end(pt_string), "");
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        string_end(pt_string), "xxxxx");
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, string_begin(pt_string), string_end(pt_string), "");
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_range_replace_cstr__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_cstr(
        pt_string, string_begin(pt_string), string_end(pt_string), "xxxx");
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
}

/*
 * test string_range_replace_subcstr
 */
UT_CASE_DEFINATION(string_range_replace_subcstr)
void test_string_range_replace_subcstr__null_dest(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_range_replace_subcstr(
        NULL, string_begin(pt_string), string_end(pt_string), "abcde", 5));

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__null_replace(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace_subcstr(
        pt_string, string_begin(pt_string), string_end(pt_string), NULL, 0));

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;
    string_init(pt_replace);

    it_begin = string_begin(pt_replace);
    it_end = string_end(pt_replace);
    expect_assert_failure(string_range_replace_subcstr(
        pt_string, it_begin, it_end, "abc", 3));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_subcstr__invalid_range(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_range_replace_subcstr(
        pt_string, string_end(pt_string), string_begin(pt_string), "abcd", 4));

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, string_begin(pt_string), string_begin(pt_string), "abcd", 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, string_begin(pt_string), string_begin(pt_string), "xxxxxx", 5);
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), "", 0);
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3), "xxxxxxxxxxxxx", 10);
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 3), "", 0);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 5), "xxxxxxxxxx", 10);
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 8), "xx", 0);
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 8), "xxxx", 2);
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        string_end(pt_string), "", 0);
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        string_end(pt_string), "xxxxx", 5);
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, string_begin(pt_string), string_end(pt_string), "", 0);
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_range_replace_subcstr__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_range_replace_subcstr(
        pt_string, string_begin(pt_string), string_end(pt_string), "xxxx", 4);
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
}

/*
 * test string_range_replace_char
 */
UT_CASE_DEFINATION(string_range_replace_char)
void test_string_range_replace_char__null_container(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_range_replace_char(
        NULL, string_begin(pt_string), string_end(pt_string), 10, 'a'));

    string_destroy(pt_string);
}

void test_string_range_replace_char__non_inited_container(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_replace);
    it_begin = string_begin(pt_replace);
    it_end = string_end(pt_replace);

    expect_assert_failure(string_range_replace_char(pt_string, it_begin, it_end, 10, 'a'));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_range_replace_char__invalid_range(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_end = string_end(pt_string);

    expect_assert_failure(string_range_replace_char(pt_string, it_end, it_begin, 0, 'a'));

    string_destroy(pt_string);
}

void test_string_range_replace_char__empty_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_string);
    it_begin = string_begin(pt_string);
    it_end = string_end(pt_string);

    string_range_replace_char(pt_string, it_begin, it_end, 0, 'a');
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
}

void test_string_range_replace_char__empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init(pt_string);
    it_begin = string_begin(pt_string);
    it_end = string_end(pt_string);

    string_range_replace_char(pt_string, it_begin, it_end, 10, 'a');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__begin_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 0, 'a');
    assert_true(string_size(pt_string) == 7);

    string_destroy(pt_string);
}

void test_string_range_replace_char__begin_replace_less(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 1, 'w');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i == 0)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__begin_replace_equal(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 3, 'w');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 3)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__begin_replace_greater(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 8, 'w');
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 8)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__middle_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_begin = iterator_next(it_begin);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 0, 'a');
    assert_true(string_size(pt_string) == 7);

    string_destroy(pt_string);
}

void test_string_range_replace_char__middle_replace_less(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_begin = iterator_next(it_begin);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 1, 'w');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i == 1)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__middle_replace_equal(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_begin = iterator_next(it_begin);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 3, 'w');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 0 && i < 4)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__middle_replace_greater(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_begin = iterator_next(it_begin);
    it_end = iterator_next_n(it_begin, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 8, 'w');
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 0 && i < 9)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__end_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_end = string_end(pt_string);
    it_begin = iterator_prev_n(it_end, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 0, 'a');
    assert_true(string_size(pt_string) == 7);

    string_destroy(pt_string);
}

void test_string_range_replace_char__end_replace_less(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_end = string_end(pt_string);
    it_begin = iterator_prev_n(it_end, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 1, 'w');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i == 7)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__end_replace_equal(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_end = string_end(pt_string);
    it_begin = iterator_prev_n(it_end, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 3, 'w');
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__end_replace_greater(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_end = string_end(pt_string);
    it_begin = iterator_prev_n(it_end, 3);

    string_range_replace_char(pt_string, it_begin, it_end, 8, 'w');
    assert_true(string_size(pt_string) == 15);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'w');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
}

void test_string_range_replace_char__replace_all(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_iterator_t it_begin;
    string_iterator_t it_end;

    string_init_char(pt_string, 10, 'a');
    it_begin = string_begin(pt_string);
    it_end = string_end(pt_string);

    string_range_replace_char(pt_string, it_begin, it_end, 8, 'w');
    assert_true(string_size(pt_string) == 8);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'w');
    }

    string_destroy(pt_string);
}

/*
 * test string_replace_range
 */
UT_CASE_DEFINATION(string_replace_range)
void test_string_replace_range__null_dest(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    expect_assert_failure(string_replace_range(
        NULL, string_begin(pt_string), string_end(pt_string),
        string_begin(pt_string), string_end(pt_string)));

    string_destroy(pt_string);
}

void test_string_replace_range__non_inited_dest(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_replace, 10, 'a');

    expect_assert_failure(string_replace_range(
        pt_string, string_begin(pt_replace), string_end(pt_replace),
        string_begin(pt_replace), string_end(pt_replace)));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__same_container(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    string_replace_range(
        pt_string, string_begin(pt_string), string_end(pt_string),
        string_begin(pt_string), string_end(pt_string));
    assert_true(string_size(pt_string) == 10);

    string_destroy(pt_string);
}

void test_string_replace_range__invalid_range(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'a');

    expect_assert_failure(string_replace_range(
        pt_string, string_end(pt_string), string_begin(pt_string),
        string_begin(pt_replace), string_end(pt_replace)));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__invalid_replace_range(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'a');

    expect_assert_failure(string_replace_range(
        pt_string, string_begin(pt_string), string_end(pt_string),
        string_end(pt_replace), string_begin(pt_replace)));

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__begin_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, string_begin(pt_string), string_begin(pt_string),
        string_begin(pt_replace), string_begin(pt_replace));
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__begin_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, string_begin(pt_string), string_begin(pt_string),
        string_begin(pt_replace), iterator_next_n(string_begin(pt_replace), 10));
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__begin_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_replace), 67), iterator_next_n(string_begin(pt_replace), 67));
    assert_true(string_size(pt_string) == 7);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__begin_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, string_begin(pt_string),
        iterator_next_n(string_begin(pt_string), 3),/* pt_replace, 45, 10);*/
        iterator_next_n(string_begin(pt_replace), 45), iterator_next_n(string_begin(pt_replace), 55));
    assert_true(string_size(pt_string) == 17);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 10)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__middle_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 3),/* pt_replace, 66, 0);*/
        iterator_next_n(string_begin(pt_replace), 66), iterator_next_n(string_begin(pt_replace), 66));
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__middle_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 5),/* pt_replace, 90, 233);*/
        iterator_next_n(string_begin(pt_replace), 90), string_end(pt_replace));
    assert_true(string_size(pt_string) == 20);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 14)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__middle_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        iterator_next_n(string_begin(pt_string), 8),/* pt_replace, 5, 0);*/
        iterator_next_n(string_begin(pt_replace), 5), iterator_next_n(string_begin(pt_replace), 5));
    assert_true(string_size(pt_string) == 5);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__middle_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 2, 'x');

    string_replace_range(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        iterator_next_n(string_begin(pt_string), 8),/* pt_replace, 0, 55);*/
        string_begin(pt_replace), string_end(pt_replace));
    assert_true(string_size(pt_string) == 9);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5 || i > 6)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__end_non_empty_replace_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, iterator_next_n(string_begin(pt_string), 3),
        string_end(pt_string), /*pt_replace, 0, 0);*/
        string_begin(pt_replace), string_begin(pt_replace));
    assert_true(string_size(pt_string) == 3);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'a');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__end_non_empty_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 5, 'x');

    string_replace_range(
        pt_string, iterator_next_n(string_begin(pt_string), 5),
        string_end(pt_string),/* pt_replace, 0, NPOS);*/
        string_begin(pt_replace), string_end(pt_replace));
    assert_true(string_size(pt_string) == 10);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        if(i < 5)
        {
            assert_true(*(char*)string_at(pt_string, i) == 'a');
        }
        else
        {
            assert_true(*(char*)string_at(pt_string, i) == 'x');
        }
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__all_replace_empty(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 100, 'x');

    string_replace_range(
        pt_string, string_begin(pt_string), string_end(pt_string),/* pt_replace, 56, 0);*/
        iterator_next_n(string_begin(pt_replace), 56), iterator_next_n(string_begin(pt_replace), 56));
    assert_true(string_size(pt_string) == 0);

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

void test_string_replace_range__all_replace_non_empty(void** state)
{
    size_t i = 0;
    string_t* pt_string = create_string();
    string_t* pt_replace = create_string();
    string_init_char(pt_string, 10, 'a');
    string_init_char(pt_replace, 4, 'x');

    string_replace_range(
        pt_string, string_begin(pt_string), string_end(pt_string),/* pt_replace, 0, NPOS);*/
        string_begin(pt_replace), string_end(pt_replace));
    assert_true(string_size(pt_string) == 4);
    for(i = 0; i < string_size(pt_string); ++i)
    {
        assert_true(*(char*)string_at(pt_string, i) == 'x');
    }

    string_destroy(pt_string);
    string_destroy(pt_replace);
}

/*
 * test string_output
 */
UT_CASE_DEFINATION(string_output)
void test_string_output__null_string(void** state)
{
    expect_assert_failure(string_output(NULL, stdout));
}

void test_string_output__null_stream(void** state)
{
    string_t* pt_string = create_string();
    string_init_cstr(pt_string, "abcdefg");

    expect_assert_failure(string_output(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_output__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_output(pt_string, stdout));

    string_destroy(pt_string);
}

void test_string_output__output_empty(void** state)
{
    string_t* pt_string = create_string();
    char buff[101] = {'\0'};
    FILE* fp_stream = NULL;
    string_init(pt_string);

    fp_stream = fopen("test_string_output__output_empty.utoutput", "w+");
    string_output(pt_string, fp_stream);
    rewind(fp_stream);
    fgets(buff, 100, fp_stream);
    assert_true(strcmp(buff, "") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}

void test_string_output__output_non_empty(void** state)
{
    string_t* pt_string = create_string();
    char buff[101] = {'\0'};
    FILE* fp_stream = NULL;
    string_init_cstr(pt_string, "abcdefg");

    fp_stream = fopen("test_string_output__output_non_empty.utoutput", "w+");
    string_output(pt_string, fp_stream);
    rewind(fp_stream);
    fgets(buff, 100, fp_stream);
    assert_true(strcmp(buff, "abcdefg") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}

/*
 * test string_input
 */
UT_CASE_DEFINATION(string_input)
void test_string_input__null_string(void** state)
{
    expect_assert_failure(string_input(NULL, stdin));
}

void test_string_input__null_stream(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_input(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_input__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_input(pt_string, stdin));

    string_destroy(pt_string);
}

void test_string_input__input_empty(void** state)
{
    string_t* pt_string = create_string();
    FILE* fp_stream = NULL;
    string_init(pt_string);

    fp_stream = fopen("test_string_input__input_empty.utoutput", "w+");
    string_input(pt_string, fp_stream);
    assert_true(strcmp(string_c_str(pt_string), "") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}

void test_string_input__input_non_empty(void** state)
{
    string_t* pt_string = create_string();
    FILE* fp_stream = NULL;
    string_init(pt_string);

    fp_stream = fopen("test_string_input__input_non_empty.utoutput", "w+");
    fputs("abcdefg", fp_stream);
    rewind(fp_stream);
    string_input(pt_string, fp_stream);
    assert_true(strcmp(string_c_str(pt_string), "abcdefg") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}

/*
 * test string_getline
 */
UT_CASE_DEFINATION(string_getline)
void test_string_getline__null_string(void** state)
{
    expect_assert_failure(string_getline(NULL, stdin));
}

void test_string_getline__null_stream(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_getline(pt_string, NULL));

    string_destroy(pt_string);
}

void test_string_getline__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_getline(pt_string, stdin));

    string_destroy(pt_string);
}

void test_string_getline__getline_empty(void** state)
{
    string_t* pt_string = create_string();
    FILE* fp_stream = NULL;
    string_init(pt_string);

    fp_stream = fopen("test_string_getline__getline_empty.utoutput", "w+");
    assert_true(string_getline(pt_string, fp_stream) == false);
    assert_true(strcmp(string_c_str(pt_string), "") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}

void test_string_getline__getline_non_empty(void** state)
{
    string_t* pt_string = create_string();
    FILE* fp_stream = NULL;
    string_init(pt_string);

    fp_stream = fopen("test_string_getline__getline_non_empty.utoutput", "w+");
    fputs("abcdefg\nxxxxxx\nooooooo", fp_stream);
    rewind(fp_stream);
    assert_true(string_getline(pt_string, fp_stream) == true);
    assert_true(strcmp(string_c_str(pt_string), "abcdefg") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}

/*
 * test string_getline_delimiter
 */
UT_CASE_DEFINATION(string_getline_delimiter)
void test_string_getline_delimiter__null_string(void** state)
{
    expect_assert_failure(string_getline_delimiter(NULL, stdin, 'x'));
}

void test_string_getline_delimiter__null_stream(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    expect_assert_failure(string_getline_delimiter(pt_string, NULL, 'x'));

    string_destroy(pt_string);
}

void test_string_getline_delimiter__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    expect_assert_failure(string_getline_delimiter(pt_string, stdin, 'x'));

    string_destroy(pt_string);
}

void test_string_getline_delimiter__getline_delimiter_empty(void** state)
{
    string_t* pt_string = create_string();
    FILE* fp_stream = NULL;
    string_init(pt_string);

    fp_stream = fopen("test_string_getline_delimiter__getline_delimiter_empty.utoutput", "w+");
    assert_true(string_getline_delimiter(pt_string, fp_stream, 'x') == false);
    assert_true(strcmp(string_c_str(pt_string), "") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}

void test_string_getline_delimiter__getline_delimiter_non_empty(void** state)
{
    string_t* pt_string = create_string();
    FILE* fp_stream = NULL;
    string_init(pt_string);

    fp_stream = fopen("test_string_getline_delimiter__getline_delimiter_non_empty.utoutput", "w+");
    fputs("abcdefg\naaaxtt\nooooooo", fp_stream);
    rewind(fp_stream);
    assert_true(string_getline_delimiter(pt_string, fp_stream, 'x') == true);
    assert_true(strcmp(string_c_str(pt_string), "abcdefg\naaa") == 0);
    fclose(fp_stream);

    string_destroy(pt_string);
}
