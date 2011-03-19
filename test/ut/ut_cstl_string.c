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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_less_cstr(pstr_string, ""));

    pstr_string->_vec_base._pby_start = NULL;
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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_less_equal_cstr(pstr_string, ""));

    pstr_string->_vec_base._pby_start = NULL;
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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_greater_cstr(pstr_string, ""));

    pstr_string->_vec_base._pby_start = NULL;
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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_greater_equal_cstr(pstr_string, ""));

    pstr_string->_vec_base._pby_start = NULL;
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
    pt_first->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_compare(pt_first, pt_second));

    pt_first->_vec_base._pby_finish = NULL;
    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare__non_inited_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init(pt_first);
    pt_second->_vec_base._pby_finish = (_byte_t*)0x73;
    expect_assert_failure(string_compare(pt_first, pt_second));

    pt_second->_vec_base._pby_finish = NULL;
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
    pt_first->_vec_base._pby_start = (_byte_t*)0x9999;
    expect_assert_failure(string_compare_substring_string(pt_first, 0, NPOS, pt_second));

    pt_first->_vec_base._pby_start = NULL;
    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_string__non_inited_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 100);
    pt_second->_vec_base._pby_start = (_byte_t*)0x9999;
    expect_assert_failure(string_compare_substring_string(pt_first, 0, NPOS, pt_second));

    pt_second->_vec_base._pby_start = NULL;
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
    pt_first->_vec_base._pby_start = (_byte_t*)0x9999;
    expect_assert_failure(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS));

    pt_first->_vec_base._pby_start = NULL;
    string_destroy(pt_first);
    string_destroy(pt_second);
}

void test_string_compare_substring_substring__non_inited_second(void** state)
{
    string_t* pt_first = create_string();
    string_t* pt_second = create_string();

    string_init_char(pt_first, 10, 100);
    pt_second->_vec_base._pby_start = (_byte_t*)0x9999;
    expect_assert_failure(string_compare_substring_substring(pt_first, 0, NPOS, pt_second, 0, NPOS));

    pt_second->_vec_base._pby_start = NULL;
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

    pt_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_compare_cstr(pt_string, elems));

    pt_string->_vec_base._pby_start = NULL;
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

    pt_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_compare_substring_cstr(pt_string, 0, NPOS, elems));

    pt_string->_vec_base._pby_start = NULL;
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

    pt_string->_vec_base._pby_start = (_byte_t*)0x3454;
    expect_assert_failure(string_compare_substring_subcstr(pt_string, 0, NPOS, elems, NPOS));

    pt_string->_vec_base._pby_start = NULL;
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

    assert_true(string_compare_substring_subcstr(pt_string, 5, 2, "", 3434) > 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_empty_non_empty(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 5, 0, "bcd", NPOS) < 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_sub_size_less(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 13, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 1, 3, "aaaaa", NPOS) < 0);

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

    assert_true(string_compare_substring_subcstr(pt_string, 4, 5, "aaaaa", NPOS) == 0);

    string_destroy(pt_string);
}

void test_string_compare_substring_subcstr__char_sub_size_greater(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 16, 'a');

    assert_true(string_compare_substring_subcstr(pt_string, 4, NPOS, "aaaaa", NPOS) > 0);

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

    assert_true(string_compare_substring_subcstr(pt_string, 0, NPOS, "bbbbb", 22222) < 0);

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

    assert_true(string_compare_substring_subcstr(pt_string, 0, NPOS, "ccccc", NPOS) == 0);

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

    pstr_string->_vec_base._pby_start = (_byte_t*)0x899;
    expect_assert_failure(string_substr(pstr_string, 0, NPOS));
    pstr_string->_vec_base._pby_start = NULL;

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
    pt_dest->_vec_base._pby_finish = (_byte_t*)0x888;
    expect_assert_failure(string_connect(pt_dest, pt_src));
    pt_dest->_vec_base._pby_finish = NULL;

    string_destroy(pt_dest);
    string_destroy(pt_src);
}

void test_string_connect__non_inited_src(void** state)
{
    string_t* pt_dest = create_string();
    string_t* pt_src = create_string();

    string_init(pt_dest);
    pt_src->_vec_base._pby_finish = (_byte_t*)0x888;
    expect_assert_failure(string_connect(pt_dest, pt_src));
    pt_src->_vec_base._pby_finish = NULL;

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

    pt_string->_vec_base._pby_start = (_byte_t*)0x999;
    expect_assert_failure(string_connect_cstr(pt_string, ""));
    pt_string->_vec_base._pby_start = NULL;

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

    pt_string->_vec_base._t_typeinfo._t_style = 23423;
    expect_assert_failure(string_connect_char(pt_string, 'a'));

    pt_string->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
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
    pt_string->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_find(pt_string, pt_find, 0));
    pt_string->_vec_base._pby_start = NULL;

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    pt_find->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_find(pt_string, pt_find, 0));
    pt_find->_vec_base._pby_start = NULL;

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_find__invalid_pos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init_char(pt_string, 10, 'a');
    string_init(pt_find);
    expect_assert_failure(string_find(pt_string, pt_find, 100));

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

    pt_string->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_find_cstr(pt_string, "abc", 0));
    pt_string->_vec_base._pby_start = NULL;

    string_destroy(pt_string);
}

void test_string_find_cstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    expect_assert_failure(string_find_cstr(pt_string, "abc", 100));

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
    expect_assert_failure(string_find_subcstr(NULL, "abc", 0, NPOS));
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

    pt_string->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_find_subcstr(pt_string, "abc", 0, NPOS));
    pt_string->_vec_base._pby_start = NULL;

    string_destroy(pt_string);
}

void test_string_find_subcstr__invalid_pos(void** state)
{
    string_t* pt_string = create_string();

    string_init_char(pt_string, 10, 'a');
    expect_assert_failure(string_find_subcstr(pt_string, "abc", 100, NPOS));

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
    assert_true(string_find_subcstr(pt_string, "", 0, NPOS) == 0);

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
    assert_true(string_find_subcstr(pt_string, "de", 0, NPOS) == 3);

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
    assert_true(string_find_subcstr(pt_string, "xy", 0, NPOS) == NPOS);

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
    assert_true(string_find_subcstr(pt_string, "", 5, NPOS) == 5);

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
    assert_true(string_find_subcstr(pt_string, "de", 2, NPOS) == 3);

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
    assert_true(string_find_subcstr(pt_string, "xy", 2, NPOS) == NPOS);

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
    assert_true(string_find_subcstr(pt_string, "de", 5, NPOS) == NPOS);

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

    pt_string->_vec_base._t_typeinfo._t_style = 23423;
    expect_assert_failure(string_find_char(pt_string, 'a', 111));

    pt_string->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
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
    pt_string->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_rfind(pt_string, pt_find, 0));
    pt_string->_vec_base._pby_start = NULL;

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__non_inited_find(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    pt_find->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_rfind(pt_string, pt_find, 0));
    pt_find->_vec_base._pby_start = NULL;

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
    assert_true(string_rfind(pt_string, pt_find, 0) == NPOS);

    string_destroy(pt_string);
    string_destroy(pt_find);
}

void test_string_rfind__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();
    string_t* pt_find = create_string();

    string_init(pt_string);
    string_init(pt_find);
    assert_true(string_rfind(pt_string, pt_find, NPOS) == NPOS);

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
    assert_true(string_rfind(pt_string, pt_find, NPOS) == 9);

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
    int elems[] = {0};
    expect_assert_failure(string_rfind_cstr(NULL, elems, 0));
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
    int elems[] = {0};

    pt_string->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_rfind_cstr(pt_string, elems, 0));
    pt_string->_vec_base._pby_start = NULL;

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_cstr(pt_string, "", 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_cstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_cstr(pt_string, "", NPOS) == NPOS);

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
    assert_true(string_rfind_cstr(pt_string, "", NPOS) == 9);

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
    int elems[] = {0};
    expect_assert_failure(string_rfind_subcstr(NULL, elems, 0, NPOS));
}

void test_string_rfind_subcstr__null_find(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    expect_assert_failure(string_rfind_subcstr(pt_string, NULL, 0, NPOS));

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__non_inited_string(void** state)
{
    string_t* pt_string = create_string();

    pt_string->_vec_base._pby_start = (_byte_t*)0x888;
    expect_assert_failure(string_rfind_subcstr(pt_string, "", 0, NPOS));
    pt_string->_vec_base._pby_start = NULL;

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "", 0, NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "", NPOS, NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_0_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", 0, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", NPOS, 0) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_0(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", 0, NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_non_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init(pt_string);
    assert_true(string_rfind_subcstr(pt_string, "abcd", NPOS, NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_empty_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "", NPOS, NPOS) == 9);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_non_empty_npos_length_0(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "abcdefghij", NPOS, 0) == 9);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "de", NPOS, 15676) == 3);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_not_find_npos(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "abcxy", NPOS, NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_empty(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "", 5, NPOS) == 5);

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
    assert_true(string_rfind_subcstr(pt_string, "de", 3, NPOS) == 3);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_not_find(void** state)
{
    string_t* pt_string = create_string();

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "xy", 5, NPOS) == NPOS);

    string_destroy(pt_string);
}

void test_string_rfind_subcstr__char_middle_not_find_pos(void** state)
{
    string_t* pt_string = create_string();
    size_t i = 0;

    string_init_cstr(pt_string, "abcdefghij");
    assert_true(string_rfind_subcstr(pt_string, "de", 2, NPOS) == NPOS);

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

    pt_string->_vec_base._t_typeinfo._t_style = 23423;
    expect_assert_failure(string_rfind_char(pt_string, 'a', 0));

    pt_string->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
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

