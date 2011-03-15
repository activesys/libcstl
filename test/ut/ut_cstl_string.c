#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
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
    str._vec_base._pby_start = (_byte_t*)0x887;
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
    str._vec_base._pby_start = (_byte_t*)0x887;
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
    str._vec_base._pby_start = (_byte_t*)0x887;
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
    str._vec_base._t_typeinfo._t_style = 24455656;
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

    string_init_subcstr(pstr_string, "", 5);
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

    string_init_subcstr(pstr_string, "abc", 100);
    assert_true(string_size(pstr_string) == 3);
    assert_true(strcmp(string_c_str(pstr_string), "abc") == 0);

    string_destroy(pstr_string);
}

void test_string_init_subcstr__truncate_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_subcstr(pstr_string, "\0abc", 100);
    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_init_subcstr__truncate_non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_subcstr(pstr_string, "abc\0xxxxx", 100);
    assert_true(string_size(pstr_string) == 3);
    assert_true(strcmp(string_c_str(pstr_string), "abc") == 0);

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

    str._vec_base._t_typeinfo._pt_type = NULL;
    expect_assert_failure(string_init_copy(&str, pstr_string));

    string_destroy(pstr_string);
}

void test_string_init_copy__non_inited_src(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();

    pstr_src->_vec_base._pby_finish = (_byte_t*)0x732;
    expect_assert_failure(string_init_copy(pstr_dest, pstr_src));

    pstr_src->_vec_base._pby_finish = NULL;
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

    str._vec_base._t_typeinfo._pt_type = NULL;
    expect_assert_failure(string_init_copy_substring(&str, pstr_string, 0, NPOS));

    string_destroy(pstr_string);
}

void test_string_init_copy_substring__non_inited_src(void** state)
{
    string_t* pstr_dest = create_string();
    string_t* pstr_src = create_string();

    pstr_src->_vec_base._pby_finish = (_byte_t*)0x732;
    expect_assert_failure(string_init_copy_substring(pstr_dest, pstr_src, 0, NPOS));

    pstr_src->_vec_base._pby_finish = NULL;
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

    expect_assert_failure(string_init_copy_substring(pstr_dest, pstr_src, string_length(pstr_src), NPOS));

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
    str._vec_base._pby_start = (_byte_t*)0x37;

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

    pstr_string->_vec_base._t_typeinfo._t_style = 4566;
    expect_assert_failure(string_c_str(pstr_string));

    pstr_string->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
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

    pstr_string->_vec_base._t_typeinfo._t_style = 4566;
    expect_assert_failure(string_data(pstr_string));

    pstr_string->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
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

    pstr_string->_vec_base._t_typeinfo._t_style = 4566;
    expect_assert_failure(string_copy(pstr_string, buffer, 0, 0));

    pstr_string->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
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
    char buffer[10];
    string_init_cstr(pstr_string, "abcdefghij");

    expect_assert_failure(string_copy(pstr_string, buffer, 0, 10));

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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x887;
    expect_assert_failure(string_size(pstr_string));

    pstr_string->_vec_base._pby_start = NULL;
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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x887;
    expect_assert_failure(string_length(pstr_string));

    pstr_string->_vec_base._pby_start = NULL;
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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x887;
    expect_assert_failure(string_empty(pstr_string));

    pstr_string->_vec_base._pby_start = NULL;
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

    pstr_string->_vec_base._pby_finish = (_byte_t*)0x783;
    expect_assert_failure(string_max_size(pstr_string));

    pstr_string->_vec_base._pby_finish = NULL;
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

    pstr_string->_vec_base._pby_endofstorage = (_byte_t*)0x623;
    expect_assert_failure(string_capacity(pstr_string));

    pstr_string->_vec_base._pby_endofstorage = NULL;
    string_destroy(pstr_string);
}

void test_string_capacity__successfully_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init(pstr_string);
    assert_true(string_capacity(pstr_string) == 16);

    string_destroy(pstr_string);
}

void test_string_capacity__successfully_little(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "abc");
    assert_true(string_capacity(pstr_string) == 18);

    string_destroy(pstr_string);
}

void test_string_capacity__successfully_huge(void** state)
{
    string_t* pstr_string = create_string();

    string_init_char(pstr_string, 3983, 'a');
    assert_true(string_capacity(pstr_string) == 5973);

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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x223;
    expect_assert_failure(string_at(pstr_string, 0));

    pstr_string->_vec_base._pby_start = NULL;
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
    pstr_first->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_equal(pstr_first, pstr_second));

    pstr_first->_vec_base._pby_finish = NULL;
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    pstr_second->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_equal(pstr_first, pstr_second));

    pstr_second->_vec_base._pby_finish = NULL;
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
    pstr_first->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_not_equal(pstr_first, pstr_second));

    pstr_first->_vec_base._pby_finish = NULL;
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_not_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    pstr_second->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_not_equal(pstr_first, pstr_second));

    pstr_second->_vec_base._pby_finish = NULL;
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
    pstr_first->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_less(pstr_first, pstr_second));

    pstr_first->_vec_base._pby_finish = NULL;
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    pstr_second->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_less(pstr_first, pstr_second));

    pstr_second->_vec_base._pby_finish = NULL;
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
    pstr_first->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_less_equal(pstr_first, pstr_second));

    pstr_first->_vec_base._pby_finish = NULL;
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_less_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    pstr_second->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_less_equal(pstr_first, pstr_second));

    pstr_second->_vec_base._pby_finish = NULL;
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
    pstr_first->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_greater(pstr_first, pstr_second));

    pstr_first->_vec_base._pby_finish = NULL;
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    pstr_second->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_greater(pstr_first, pstr_second));

    pstr_second->_vec_base._pby_finish = NULL;
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
    pstr_first->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_greater_equal(pstr_first, pstr_second));

    pstr_first->_vec_base._pby_finish = NULL;
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test_string_greater_equal__non_inited_second(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();

    string_init(pstr_first);
    pstr_second->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_greater_equal(pstr_first, pstr_second));

    pstr_second->_vec_base._pby_finish = NULL;
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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_equal_cstr(pstr_string, ""));

    pstr_string->_vec_base._pby_start = NULL;
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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_not_equal_cstr(pstr_string, ""));

    pstr_string->_vec_base._pby_start = NULL;
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
