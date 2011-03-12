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

void test_string_init_cstr__cut_off_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "\0abc");
    assert_true(string_size(pstr_string) == 0);

    string_destroy(pstr_string);
}

void test_string_init_cstr__cut_off_non_empty(void** state)
{
    string_t* pstr_string = create_string();

    string_init_cstr(pstr_string, "abc\0xxxxx");
    assert_true(string_size(pstr_string) == 3);
    assert_true(strcmp(string_c_str(pstr_string), "abc") == 0);

    string_destroy(pstr_string);
}

