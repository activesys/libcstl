#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl_types_builtin.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_types_builtin.h"

UT_SUIT_DEFINATION(cstl_types_builtin, _type_init_char)

/*
 * test _type_init_char
 */
UT_CASE_DEFINATION(_type_init_char)
void test__type_init_char__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_init_char(NULL, &b_output));
}

void test__type_init_char__null_output(void** state)
{
    char c_input;
    expect_assert_failure(_type_init_char(&c_input, NULL));
}

void test__type_init_char__ok(void** state)
{
    char c_input = 'a';
    bool_t b_output = false;
    _type_init_char(&c_input, &b_output);
    assert_true(c_input == '\0');
    assert_true(b_output);
}

/*
 * test _type_copy_char
 */
UT_CASE_DEFINATION(_type_copy_char)
void test__type_copy_char__null_first(void** state)
{
    char c_second = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_copy_char(NULL, &c_second, &b_output));
}

void test__type_copy_char__null_second(void** state)
{
    char c_first = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_copy_char(&c_first, NULL, &b_output));
}

void test__type_copy_char__null_output(void** state)
{
    char c_first = 'a';
    char c_second = 'b';
    expect_assert_failure(_type_copy_char(&c_first, &c_second, NULL));
}

void test__type_copy_char__ok(void** state)
{
    char c_first = 'a';
    char c_second = 'b';
    bool_t b_output = false;
    _type_copy_char(&c_first, &c_second, &b_output);
    assert_true(c_first == 'b');
    assert_true(c_second == 'b');
    assert_true(b_output);
}

/*
 * test _type_less_char
 */
UT_CASE_DEFINATION(_type_less_char)
void test__type_less_char__null_first(void** state)
{
    char c_second = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_less_char(NULL, &c_second, &b_output));
}

void test__type_less_char__null_second(void** state)
{
    char c_first = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_less_char(&c_first, NULL, &b_output));
}

void test__type_less_char__null_output(void** state)
{
    char c_first = 'a';
    char c_second = 'b';
    expect_assert_failure(_type_less_char(&c_first, &c_second, NULL));
}

void test__type_less_char__less(void** state)
{
    char c_first = 'a';
    char c_second = 'b';
    bool_t b_output = false;
    _type_less_char(&c_first, &c_second, &b_output);
    assert_true(c_first == 'a');
    assert_true(c_second == 'b');
    assert_true(b_output);
}

void test__type_less_char__equal(void** state)
{
    char c_first = 'a';
    char c_second = 'a';
    bool_t b_output = true;
    _type_less_char(&c_first, &c_second, &b_output);
    assert_true(c_first == 'a');
    assert_true(c_second == 'a');
    assert_false(b_output);
}

void test__type_less_char__greater(void** state)
{
    char c_first = 'b';
    char c_second = 'a';
    bool_t b_output = true;
    _type_less_char(&c_first, &c_second, &b_output);
    assert_true(c_first == 'b');
    assert_true(c_second == 'a');
    assert_false(b_output);
}

/*
 * test _type_destroy_char
 */
UT_CASE_DEFINATION(_type_destroy_char)
void test__type_destroy_char__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_destroy_char(NULL, &b_output));
}

void test__type_destroy_char__null_output(void** state)
{
    char c_input;
    expect_assert_failure(_type_destroy_char(&c_input, NULL));
}

void test__type_destroy_char__ok(void** state)
{
    char c_input = 'a';
    bool_t b_output = false;
    _type_destroy_char(&c_input, &b_output);
    assert_true(c_input == 'a');
    assert_true(b_output);
}

/*
 * test _type_init_uchar
 */
UT_CASE_DEFINATION(_type_init_uchar)
void test__type_init_uchar__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_init_uchar(NULL, &b_output));
}

void test__type_init_uchar__null_output(void** state)
{
    unsigned char c_input;
    expect_assert_failure(_type_init_uchar(&c_input, NULL));
}

void test__type_init_uchar__ok(void** state)
{
    unsigned char c_input = 'a';
    bool_t b_output = false;
    _type_init_uchar(&c_input, &b_output);
    assert_true(c_input == '\0');
    assert_true(b_output);
}

/*
 * test _type_copy_uchar
 */
UT_CASE_DEFINATION(_type_copy_uchar)
void test__type_copy_uchar__null_first(void** state)
{
    unsigned char c_second = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_copy_uchar(NULL, &c_second, &b_output));
}

void test__type_copy_uchar__null_second(void** state)
{
    unsigned char c_first = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_copy_uchar(&c_first, NULL, &b_output));
}

void test__type_copy_uchar__null_output(void** state)
{
    unsigned char c_first = 'a';
    unsigned char c_second = 'b';
    expect_assert_failure(_type_copy_uchar(&c_first, &c_second, NULL));
}

void test__type_copy_uchar__ok(void** state)
{
    unsigned char c_first = 'a';
    unsigned char c_second = 'b';
    bool_t b_output = false;
    _type_copy_uchar(&c_first, &c_second, &b_output);
    assert_true(c_first == 'b');
    assert_true(c_second == 'b');
    assert_true(b_output);
}

/*
 * test _type_less_uchar
 */
UT_CASE_DEFINATION(_type_less_uchar)
void test__type_less_uchar__null_first(void** state)
{
    unsigned char c_second = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_less_uchar(NULL, &c_second, &b_output));
}

void test__type_less_uchar__null_second(void** state)
{
    unsigned char c_first = 'a';
    bool_t b_output = false;
    expect_assert_failure(_type_less_uchar(&c_first, NULL, &b_output));
}

void test__type_less_uchar__null_output(void** state)
{
    unsigned char c_first = 'a';
    unsigned char c_second = 'b';
    expect_assert_failure(_type_less_uchar(&c_first, &c_second, NULL));
}

void test__type_less_uchar__less(void** state)
{
    unsigned char c_first = 'a';
    unsigned char c_second = 'b';
    bool_t b_output = false;
    _type_less_uchar(&c_first, &c_second, &b_output);
    assert_true(c_first == 'a');
    assert_true(c_second == 'b');
    assert_true(b_output);
}

void test__type_less_uchar__equal(void** state)
{
    unsigned char c_first = 'a';
    unsigned char c_second = 'a';
    bool_t b_output = true;
    _type_less_uchar(&c_first, &c_second, &b_output);
    assert_true(c_first == 'a');
    assert_true(c_second == 'a');
    assert_false(b_output);
}

void test__type_less_uchar__greater(void** state)
{
    unsigned char c_first = 'b';
    unsigned char c_second = 'a';
    bool_t b_output = true;
    _type_less_uchar(&c_first, &c_second, &b_output);
    assert_true(c_first == 'b');
    assert_true(c_second == 'a');
    assert_false(b_output);
}

/*
 * test _type_destroy_uchar
 */
UT_CASE_DEFINATION(_type_destroy_uchar)
void test__type_destroy_uchar__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_destroy_uchar(NULL, &b_output));
}

void test__type_destroy_uchar__null_output(void** state)
{
    unsigned char c_input;
    expect_assert_failure(_type_destroy_uchar(&c_input, NULL));
}

void test__type_destroy_uchar__ok(void** state)
{
    unsigned char c_input = 'a';
    bool_t b_output = false;
    _type_destroy_uchar(&c_input, &b_output);
    assert_true(c_input == 'a');
    assert_true(b_output);
}

/*
 * test _type_init_short
 */
UT_CASE_DEFINATION(_type_init_short)
void test__type_init_short__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_init_short(NULL, &b_output));
}

void test__type_init_short__null_output(void** state)
{
    short h_input;
    expect_assert_failure(_type_init_short(&h_input, NULL));
}

void test__type_init_short__ok(void** state)
{
    short h_input = 10;
    bool_t b_output = false;
    _type_init_short(&h_input, &b_output);
    assert_true(h_input == 0);
    assert_true(b_output);
}

/*
 * test _type_copy_short
 */
UT_CASE_DEFINATION(_type_copy_short)
void test__type_copy_short__null_first(void** state)
{
    short h_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_short(NULL, &h_second, &b_output));
}

void test__type_copy_short__null_second(void** state)
{
    short h_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_short(&h_first, NULL, &b_output));
}

void test__type_copy_short__null_output(void** state)
{
    short h_first = 10;
    short h_second = 20;
    expect_assert_failure(_type_copy_short(&h_first, &h_second, NULL));
}

void test__type_copy_short__ok(void** state)
{
    short h_first = 10;
    short h_second = 20;
    bool_t b_output = false;
    _type_copy_short(&h_first, &h_second, &b_output);
    assert_true(h_first == 20);
    assert_true(h_second == 20);
    assert_true(b_output);
}

/*
 * test _type_less_short
 */
UT_CASE_DEFINATION(_type_less_short)
void test__type_less_short__null_first(void** state)
{
    short h_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_short(NULL, &h_second, &b_output));
}

void test__type_less_short__null_second(void** state)
{
    short h_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_short(&h_first, NULL, &b_output));
}

void test__type_less_short__null_output(void** state)
{
    short h_first = 10;
    short h_second = 20;
    expect_assert_failure(_type_less_short(&h_first, &h_second, NULL));
}

void test__type_less_short__less(void** state)
{
    short h_first = 10;
    short h_second = 20;
    bool_t b_output = false;
    _type_less_short(&h_first, &h_second, &b_output);
    assert_true(h_first == 10);
    assert_true(h_second == 20);
    assert_true(b_output);
}

void test__type_less_short__equal(void** state)
{
    short h_first = 10;
    short h_second = 10;
    bool_t b_output = true;
    _type_less_short(&h_first, &h_second, &b_output);
    assert_true(h_first == 10);
    assert_true(h_second == 10);
    assert_false(b_output);
}

void test__type_less_short__greater(void** state)
{
    short h_first = 20;
    short h_second = 10;
    bool_t b_output = true;
    _type_less_short(&h_first, &h_second, &b_output);
    assert_true(h_first == 20);
    assert_true(h_second == 10);
    assert_false(b_output);
}

/*
 * test _type_destroy_short
 */
UT_CASE_DEFINATION(_type_destroy_short)
void test__type_destroy_short__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_destroy_short(NULL, &b_output));
}

void test__type_destroy_short__null_output(void** state)
{
    short h_input;
    expect_assert_failure(_type_destroy_short(&h_input, NULL));
}

void test__type_destroy_short__ok(void** state)
{
    short h_input = 10;
    bool_t b_output = false;
    _type_destroy_short(&h_input, &b_output);
    assert_true(h_input == 10);
    assert_true(b_output);
}

/*
 * test _type_init_ushort
 */
UT_CASE_DEFINATION(_type_init_ushort)
void test__type_init_ushort__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_init_ushort(NULL, &b_output));
}

void test__type_init_ushort__null_output(void** state)
{
    unsigned short uh_input;
    expect_assert_failure(_type_init_ushort(&uh_input, NULL));
}

void test__type_init_ushort__ok(void** state)
{
    unsigned short uh_input = 10;
    bool_t b_output = false;
    _type_init_ushort(&uh_input, &b_output);
    assert_true(uh_input == 0);
    assert_true(b_output);
}

/*
 * test _type_copy_ushort
 */
UT_CASE_DEFINATION(_type_copy_ushort)
void test__type_copy_ushort__null_first(void** state)
{
    unsigned short uh_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_ushort(NULL, &uh_second, &b_output));
}

void test__type_copy_ushort__null_second(void** state)
{
    unsigned short uh_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_ushort(&uh_first, NULL, &b_output));
}

void test__type_copy_ushort__null_output(void** state)
{
    unsigned short uh_first = 10;
    unsigned short uh_second = 20;
    expect_assert_failure(_type_copy_ushort(&uh_first, &uh_second, NULL));
}

void test__type_copy_ushort__ok(void** state)
{
    unsigned short uh_first = 10;
    unsigned short uh_second = 20;
    bool_t b_output = false;
    _type_copy_ushort(&uh_first, &uh_second, &b_output);
    assert_true(uh_first == 20);
    assert_true(uh_second == 20);
    assert_true(b_output);
}

/*
 * test _type_less_ushort
 */
UT_CASE_DEFINATION(_type_less_ushort)
void test__type_less_ushort__null_first(void** state)
{
    unsigned short uh_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_ushort(NULL, &uh_second, &b_output));
}

void test__type_less_ushort__null_second(void** state)
{
    unsigned short uh_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_ushort(&uh_first, NULL, &b_output));
}

void test__type_less_ushort__null_output(void** state)
{
    unsigned short uh_first = 10;
    unsigned short uh_second = 20;
    expect_assert_failure(_type_less_ushort(&uh_first, &uh_second, NULL));
}

void test__type_less_ushort__less(void** state)
{
    unsigned short uh_first = 10;
    unsigned short uh_second = 20;
    bool_t b_output = false;
    _type_less_ushort(&uh_first, &uh_second, &b_output);
    assert_true(uh_first == 10);
    assert_true(uh_second == 20);
    assert_true(b_output);
}

void test__type_less_ushort__equal(void** state)
{
    unsigned short uh_first = 10;
    unsigned short uh_second = 10;
    bool_t b_output = true;
    _type_less_ushort(&uh_first, &uh_second, &b_output);
    assert_true(uh_first == 10);
    assert_true(uh_second == 10);
    assert_false(b_output);
}

void test__type_less_ushort__greater(void** state)
{
    unsigned short uh_first = 20;
    unsigned short uh_second = 10;
    bool_t b_output = true;
    _type_less_ushort(&uh_first, &uh_second, &b_output);
    assert_true(uh_first == 20);
    assert_true(uh_second == 10);
    assert_false(b_output);
}

/*
 * test _type_destroy_ushort
 */
UT_CASE_DEFINATION(_type_destroy_ushort)
void test__type_destroy_ushort__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_destroy_ushort(NULL, &b_output));
}

void test__type_destroy_ushort__null_output(void** state)
{
    unsigned short uh_input;
    expect_assert_failure(_type_destroy_ushort(&uh_input, NULL));
}

void test__type_destroy_ushort__ok(void** state)
{
    unsigned short uh_input = 10;
    bool_t b_output = false;
    _type_destroy_ushort(&uh_input, &b_output);
    assert_true(uh_input == 10);
    assert_true(b_output);
}

/*
 * test _type_init_int
 */
UT_CASE_DEFINATION(_type_init_int)
void test__type_init_int__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_init_int(NULL, &b_output));
}

void test__type_init_int__null_output(void** state)
{
    int n_input = 0;
    expect_assert_failure(_type_init_int(&n_input, NULL));
}

void test__type_init_int__ok(void** state)
{
    int n_input = 10;
    bool_t b_output = false;
    _type_init_int(&n_input, &b_output);
    assert_true(n_input == 0);
    assert_true(b_output);
}

/*
 * test _type_copy_int
 */
UT_CASE_DEFINATION(_type_copy_int)
void test__type_copy_int__null_first(void** state)
{
    int n_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_int(NULL, &n_second, &b_output));
}

void test__type_copy_int__null_second(void** state)
{
    int n_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_int(&n_first, NULL, &b_output));
}

void test__type_copy_int__null_output(void** state)
{
    int n_first = 10;
    int n_second = 20;
    expect_assert_failure(_type_copy_int(&n_first, &n_second, NULL));
}

void test__type_copy_int__ok(void** state)
{
    int n_first = 10;
    int n_second = 20;
    bool_t b_output = false;
    _type_copy_int(&n_first, &n_second, &b_output);
    assert_true(n_first == 20);
    assert_true(n_second == 20);
    assert_true(b_output);
}

/*
 * test _type_less_int
 */
UT_CASE_DEFINATION(_type_less_int)
void test__type_less_int__null_first(void** state)
{
    int n_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_int(NULL, &n_second, &b_output));
}

void test__type_less_int__null_second(void** state)
{
    int n_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_int(&n_first, NULL, &b_output));
}

void test__type_less_int__null_output(void** state)
{
    int n_first = 10;
    int n_second = 20;
    expect_assert_failure(_type_less_int(&n_first, &n_second, NULL));
}

void test__type_less_int__less(void** state)
{
    int n_first = 10;
    int n_second = 20;
    bool_t b_output = false;
    _type_less_int(&n_first, &n_second, &b_output);
    assert_true(n_first == 10);
    assert_true(n_second == 20);
    assert_true(b_output);
}

void test__type_less_int__equal(void** state)
{
    int n_first = 10;
    int n_second = 10;
    bool_t b_output = true;
    _type_less_int(&n_first, &n_second, &b_output);
    assert_true(n_first == 10);
    assert_true(n_second == 10);
    assert_false(b_output);
}

void test__type_less_int__greater(void** state)
{
    int n_first = 20;
    int n_second = 10;
    bool_t b_output = true;
    _type_less_int(&n_first, &n_second, &b_output);
    assert_true(n_first == 20);
    assert_true(n_second == 10);
    assert_false(b_output);
}

/*
 * test _type_destroy_int
 */
UT_CASE_DEFINATION(_type_destroy_int)
void test__type_destroy_int__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_destroy_int(NULL, &b_output));
}

void test__type_destroy_int__null_output(void** state)
{
    int n_input;
    expect_assert_failure(_type_destroy_int(&n_input, NULL));
}

void test__type_destroy_int__ok(void** state)
{
    int n_input = 10;
    bool_t b_output = false;
    _type_destroy_int(&n_input, &b_output);
    assert_true(n_input == 10);
    assert_true(b_output);
}

/*
 * test _type_init_uint
 */
UT_CASE_DEFINATION(_type_init_uint)
void test__type_init_uint__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_uint(NULL, &b_output));
}

void test__type_init_uint__null_output(void** state)
{
    unsigned int un_input = 10;
    expect_assert_failure(_type_init_uint(&un_input, NULL));
}

void test__type_init_uint__ok(void** state)
{
    unsigned int un_input = 10;
    bool_t b_output = false;
    _type_init_uint(&un_input, &b_output);
    assert_true(un_input == 0);
    assert_true(b_output);
}

/*
 * test _type_copy_uint
 */
UT_CASE_DEFINATION(_type_copy_uint)
void test__type_copy_uint__null_first(void** state)
{
    unsigned int un_second = 3;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_uint(NULL, &un_second, &b_output));
}

void test__type_copy_uint__null_second(void** state)
{
    unsigned int un_first = 3;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_uint(&un_first, NULL, &b_output));
}

void test__type_copy_uint__null_output(void** state)
{
    unsigned int un_first = 3;
    unsigned int un_second = 2;
    expect_assert_failure(_type_copy_uint(&un_first, &un_second, NULL));
}

void test__type_copy_uint__ok(void** state)
{
    unsigned int un_first = 5;
    unsigned int un_second = 2;
    bool_t b_output = false;
    _type_copy_uint(&un_first, &un_second, &b_output);
    assert_true(un_first == 2);
    assert_true(un_second == 2);
    assert_true(b_output);
}

/*
 * test _type_less_uint
 */
UT_CASE_DEFINATION(_type_less_uint)
void test__type_less_uint__null_first(void** state)
{
    unsigned int un_second = 4;
    bool_t b_output = false;
    expect_assert_failure(_type_less_uint(NULL, &un_second, &b_output));
}

void test__type_less_uint__null_second(void** state)
{
    unsigned int un_first = 4;
    bool_t b_output = false;
    expect_assert_failure(_type_less_uint(&un_first, NULL, &b_output));
}

void test__type_less_uint__null_output(void** state)
{
    unsigned int un_first = 4;
    unsigned int un_second = 3;
    expect_assert_failure(_type_less_uint(&un_first, &un_second, NULL));
}

void test__type_less_uint__less(void** state)
{
    unsigned int un_first = 4;
    unsigned int un_second = 9;
    bool_t b_output = false;
    _type_less_uint(&un_first, &un_second, &b_output);
    assert_true(un_first == 4);
    assert_true(un_second == 9);
    assert_true(b_output);
}

void test__type_less_uint__equal(void** state)
{
    unsigned int un_first = 4;
    unsigned int un_second = 4;
    bool_t b_output = false;
    _type_less_uint(&un_first, &un_second, &b_output);
    assert_true(un_first == 4);
    assert_true(un_second == 4);
    assert_false(b_output);
}

void test__type_less_uint__greater(void** state)
{
    unsigned int un_first = 5;
    unsigned int un_second = 2;
    bool_t b_output = false;
    _type_less_uint(&un_first, &un_second, &b_output);
    assert_true(un_first == 5);
    assert_true(un_second == 2);
    assert_false(b_output);
}

/*
 * test _type_destroy_uint
 */
UT_CASE_DEFINATION(_type_destroy_uint)
void test__type_destroy_uint__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_uint(NULL, &b_output));
}

void test__type_destroy_uint__null_output(void** state)
{
    unsigned int un_input = 3;
    expect_assert_failure(_type_destroy_uint(&un_input, NULL));
}

void test__type_destroy_uint__ok(void** state)
{
    unsigned int un_input = 3;
    bool_t b_output = false;
    _type_destroy_uint(&un_input, &b_output);
    assert_true(un_input == 3);
    assert_true(b_output);
}

/*
 * test _type_init_long
 */
UT_CASE_DEFINATION(_type_init_long)
void test__type_init_long__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_init_long(NULL, &b_output));
}

void test__type_init_long__null_output(void** state)
{
    long l_input = 0;
    expect_assert_failure(_type_init_long(&l_input, NULL));
}

void test__type_init_long__ok(void** state)
{
    long l_input = 10;
    bool_t b_output = false;
    _type_init_long(&l_input, &b_output);
    assert_true(l_input == 0);
    assert_true(b_output);
}

/*
 * test _type_copy_long
 */
UT_CASE_DEFINATION(_type_copy_long)
void test__type_copy_long__null_first(void** state)
{
    long l_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_long(NULL, &l_second, &b_output));
}

void test__type_copy_long__null_second(void** state)
{
    long l_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_long(&l_first, NULL, &b_output));
}

void test__type_copy_long__null_output(void** state)
{
    long l_first = 10;
    long l_second = 20;
    expect_assert_failure(_type_copy_long(&l_first, &l_second, NULL));
}

void test__type_copy_long__ok(void** state)
{
    long l_first = 10;
    long l_second = 20;
    bool_t b_output = false;
    _type_copy_long(&l_first, &l_second, &b_output);
    assert_true(l_first == 20);
    assert_true(l_second == 20);
    assert_true(b_output);
}

/*
 * test _type_less_long
 */
UT_CASE_DEFINATION(_type_less_long)
void test__type_less_long__null_first(void** state)
{
    long l_second = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_long(NULL, &l_second, &b_output));
}

void test__type_less_long__null_second(void** state)
{
    long l_first = 10;
    bool_t b_output = false;
    expect_assert_failure(_type_less_long(&l_first, NULL, &b_output));
}

void test__type_less_long__null_output(void** state)
{
    long l_first = 10;
    long l_second = 20;
    expect_assert_failure(_type_less_long(&l_first, &l_second, NULL));
}

void test__type_less_long__less(void** state)
{
    long l_first = 10;
    long l_second = 20;
    bool_t b_output = false;
    _type_less_long(&l_first, &l_second, &b_output);
    assert_true(l_first == 10);
    assert_true(l_second == 20);
    assert_true(b_output);
}

void test__type_less_long__equal(void** state)
{
    long l_first = 10;
    long l_second = 10;
    bool_t b_output = true;
    _type_less_long(&l_first, &l_second, &b_output);
    assert_true(l_first == 10);
    assert_true(l_second == 10);
    assert_false(b_output);
}

void test__type_less_long__greater(void** state)
{
    long l_first = 20;
    long l_second = 10;
    bool_t b_output = true;
    _type_less_long(&l_first, &l_second, &b_output);
    assert_true(l_first == 20);
    assert_true(l_second == 10);
    assert_false(b_output);
}

/*
 * test _type_destroy_long
 */
UT_CASE_DEFINATION(_type_destroy_long)
void test__type_destroy_long__null_input(void** state)
{
    bool_t b_output = false;

    expect_assert_failure(_type_destroy_long(NULL, &b_output));
}

void test__type_destroy_long__null_output(void** state)
{
    long l_input;
    expect_assert_failure(_type_destroy_long(&l_input, NULL));
}

void test__type_destroy_long__ok(void** state)
{
    long l_input = 10;
    bool_t b_output = false;
    _type_destroy_long(&l_input, &b_output);
    assert_true(l_input == 10);
    assert_true(b_output);
}

/*
 * test _type_init_ulong
 */
UT_CASE_DEFINATION(_type_init_ulong)
void test__type_init_ulong__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_ulong(NULL, &b_output));
}

void test__type_init_ulong__null_output(void** state)
{
    unsigned long ul_input = 10;
    expect_assert_failure(_type_init_ulong(&ul_input, NULL));
}

void test__type_init_ulong__ok(void** state)
{
    unsigned long ul_input = 10;
    bool_t b_output = false;
    _type_init_ulong(&ul_input, &b_output);
    assert_true(ul_input == 0);
    assert_true(b_output);
}

/*
 * test _type_copy_ulong
 */
UT_CASE_DEFINATION(_type_copy_ulong)
void test__type_copy_ulong__null_first(void** state)
{
    unsigned long ul_second = 3;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_ulong(NULL, &ul_second, &b_output));
}

void test__type_copy_ulong__null_second(void** state)
{
    unsigned long ul_first = 3;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_ulong(&ul_first, NULL, &b_output));
}

void test__type_copy_ulong__null_output(void** state)
{
    unsigned long ul_first = 3;
    unsigned long ul_second = 2;
    expect_assert_failure(_type_copy_ulong(&ul_first, &ul_second, NULL));
}

void test__type_copy_ulong__ok(void** state)
{
    unsigned long ul_first = 5;
    unsigned long ul_second = 2;
    bool_t b_output = false;
    _type_copy_ulong(&ul_first, &ul_second, &b_output);
    assert_true(ul_first == 2);
    assert_true(ul_second == 2);
    assert_true(b_output);
}

/*
 * test _type_less_ulong
 */
UT_CASE_DEFINATION(_type_less_ulong)
void test__type_less_ulong__null_first(void** state)
{
    unsigned long ul_second = 4;
    bool_t b_output = false;
    expect_assert_failure(_type_less_ulong(NULL, &ul_second, &b_output));
}

void test__type_less_ulong__null_second(void** state)
{
    unsigned long ul_first = 4;
    bool_t b_output = false;
    expect_assert_failure(_type_less_ulong(&ul_first, NULL, &b_output));
}

void test__type_less_ulong__null_output(void** state)
{
    unsigned long ul_first = 4;
    unsigned long ul_second = 3;
    expect_assert_failure(_type_less_ulong(&ul_first, &ul_second, NULL));
}

void test__type_less_ulong__less(void** state)
{
    unsigned long ul_first = 4;
    unsigned long ul_second = 9;
    bool_t b_output = false;
    _type_less_ulong(&ul_first, &ul_second, &b_output);
    assert_true(ul_first == 4);
    assert_true(ul_second == 9);
    assert_true(b_output);
}

void test__type_less_ulong__equal(void** state)
{
    unsigned long ul_first = 4;
    unsigned long ul_second = 4;
    bool_t b_output = false;
    _type_less_ulong(&ul_first, &ul_second, &b_output);
    assert_true(ul_first == 4);
    assert_true(ul_second == 4);
    assert_false(b_output);
}

void test__type_less_ulong__greater(void** state)
{
    unsigned long ul_first = 5;
    unsigned long ul_second = 2;
    bool_t b_output = false;
    _type_less_ulong(&ul_first, &ul_second, &b_output);
    assert_true(ul_first == 5);
    assert_true(ul_second == 2);
    assert_false(b_output);
}

/*
 * test _type_destroy_ulong
 */
UT_CASE_DEFINATION(_type_destroy_ulong)
void test__type_destroy_ulong__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_ulong(NULL, &b_output));
}

void test__type_destroy_ulong__null_output(void** state)
{
    unsigned long ul_input = 3;
    expect_assert_failure(_type_destroy_ulong(&ul_input, NULL));
}

void test__type_destroy_ulong__ok(void** state)
{
    unsigned long ul_input = 3;
    bool_t b_output = false;
    _type_destroy_ulong(&ul_input, &b_output);
    assert_true(ul_input == 3);
    assert_true(b_output);
}

/*
 * test _type_init_float
 */
UT_CASE_DEFINATION(_type_init_float)
void test__type_init_float__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_float(NULL, &b_output));
}

void test__type_init_float__null_output(void** state)
{
    float f_input = 10.34f;
    expect_assert_failure(_type_init_float(&f_input, NULL));
}

void test__type_init_float__ok(void** state)
{
    float f_input = 10.09054f;
    bool_t b_output = false;
    _type_init_float(&f_input, &b_output);
    assert_true(f_input == 0.0f);
    assert_true(b_output);
}

/*
 * test _type_copy_float
 */
UT_CASE_DEFINATION(_type_copy_float)
void test__type_copy_float__null_first(void** state)
{
    float f_second = -4.23f;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_float(NULL, &f_second, &b_output));
}

void test__type_copy_float__null_second(void** state)
{
    float f_first = 3.4f;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_float(&f_first, NULL, &b_output));
}

void test__type_copy_float__null_output(void** state)
{
    float f_first = 3.09f;
    float f_second = 2.22f;
    expect_assert_failure(_type_copy_float(&f_first, &f_second, NULL));
}

void test__type_copy_float__ok(void** state)
{
    float f_first = 5.23f;
    float f_second = 2.11f;
    bool_t b_output = false;
    _type_copy_float(&f_first, &f_second, &b_output);
    assert_true(f_first == 2.11f);
    assert_true(f_second == 2.11f);
    assert_true(b_output);
}

/*
 * test _type_less_float
 */
UT_CASE_DEFINATION(_type_less_float)
void test__type_less_float__null_first(void** state)
{
    float f_second = 4.0f;
    bool_t b_output = false;
    expect_assert_failure(_type_less_float(NULL, &f_second, &b_output));
}

void test__type_less_float__null_second(void** state)
{
    float f_first = 4.0f;
    bool_t b_output = false;
    expect_assert_failure(_type_less_float(&f_first, NULL, &b_output));
}

void test__type_less_float__null_output(void** state)
{
    float f_first = 4.0f;
    float f_second = 3.4f;
    expect_assert_failure(_type_less_float(&f_first, &f_second, NULL));
}

void test__type_less_float__less(void** state)
{
    float f_first = 4.9f;
    float f_second = 9.0f;
    bool_t b_output = false;
    _type_less_float(&f_first, &f_second, &b_output);
    assert_true(f_first == 4.9f);
    assert_true(f_second == 9.0f);
    assert_true(b_output);
}

void test__type_less_float__equal(void** state)
{
    float f_first = 4.0f;
    float f_second = 4.0f;
    bool_t b_output = false;
    _type_less_float(&f_first, &f_second, &b_output);
    assert_true(f_first == 4.0f);
    assert_true(f_second == 4.0f);
    assert_false(b_output);
}

void test__type_less_float__greater(void** state)
{
    float f_first = 5.00000001f;
    float f_second = 5.0f;
    bool_t b_output = false;
    _type_less_float(&f_first, &f_second, &b_output);
    assert_true(f_first == 5.00000001f);
    assert_true(f_second == 5.0f);
    assert_false(b_output);
}

/*
 * test _type_destroy_float
 */
UT_CASE_DEFINATION(_type_destroy_float)
void test__type_destroy_float__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_float(NULL, &b_output));
}

void test__type_destroy_float__null_output(void** state)
{
    float f_input = 4.3f;
    expect_assert_failure(_type_destroy_float(&f_input, NULL));
}

void test__type_destroy_float__ok(void** state)
{
    float f_input = 0.3f;
    bool_t b_output = false;
    _type_destroy_float(&f_input, &b_output);
    assert_true(f_input == 0.3f);
    assert_true(b_output);
}

/*
 * test _type_init_double
 */
UT_CASE_DEFINATION(_type_init_double)
void test__type_init_double__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_double(NULL, &b_output));
}

void test__type_init_double__null_output(void** state)
{
    double d_input = 10.34;
    expect_assert_failure(_type_init_double(&d_input, NULL));
}

void test__type_init_double__ok(void** state)
{
    double d_input = 10.09054;
    bool_t b_output = false;
    _type_init_double(&d_input, &b_output);
    assert_true(d_input == 0.0);
    assert_true(b_output);
}

/*
 * test _type_copy_double
 */
UT_CASE_DEFINATION(_type_copy_double)
void test__type_copy_double__null_first(void** state)
{
    double d_second = -4.23;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_double(NULL, &d_second, &b_output));
}

void test__type_copy_double__null_second(void** state)
{
    double d_first = 3.4;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_double(&d_first, NULL, &b_output));
}

void test__type_copy_double__null_output(void** state)
{
    double d_first = 3.09;
    double d_second = 2.22;
    expect_assert_failure(_type_copy_double(&d_first, &d_second, NULL));
}

void test__type_copy_double__ok(void** state)
{
    double d_first = 5.23;
    double d_second = 2.11;
    bool_t b_output = false;
    _type_copy_double(&d_first, &d_second, &b_output);
    assert_true(d_first == 2.11);
    assert_true(d_second == 2.11);
    assert_true(b_output);
}

/*
 * test _type_less_double
 */
UT_CASE_DEFINATION(_type_less_double)
void test__type_less_double__null_first(void** state)
{
    double d_second = 4.0;
    bool_t b_output = false;
    expect_assert_failure(_type_less_double(NULL, &d_second, &b_output));
}

void test__type_less_double__null_second(void** state)
{
    double d_first = 4.0;
    bool_t b_output = false;
    expect_assert_failure(_type_less_double(&d_first, NULL, &b_output));
}

void test__type_less_double__null_output(void** state)
{
    double d_first = 4.0;
    double d_second = 3.4;
    expect_assert_failure(_type_less_double(&d_first, &d_second, NULL));
}

void test__type_less_double__less(void** state)
{
    double d_first = 4.9;
    double d_second = 9.0;
    bool_t b_output = false;
    _type_less_double(&d_first, &d_second, &b_output);
    assert_true(d_first == 4.9);
    assert_true(d_second == 9.0);
    assert_true(b_output);
}

void test__type_less_double__equal(void** state)
{
    double d_first = 4.0;
    double d_second = 4.0;
    bool_t b_output = false;
    _type_less_double(&d_first, &d_second, &b_output);
    assert_true(d_first == 4.0);
    assert_true(d_second == 4.0);
    assert_false(b_output);
}

void test__type_less_double__greater(void** state)
{
    double d_first = 5.00000001;
    double d_second = 5.0;
    bool_t b_output = false;
    _type_less_double(&d_first, &d_second, &b_output);
    assert_true(d_first == 5.00000001);
    assert_true(d_second == 5.0);
    assert_false(b_output);
}

/*
 * test _type_destroy_double
 */
UT_CASE_DEFINATION(_type_destroy_double)
void test__type_destroy_double__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_double(NULL, &b_output));
}

void test__type_destroy_double__null_output(void** state)
{
    double d_input = 4.3;
    expect_assert_failure(_type_destroy_double(&d_input, NULL));
}

void test__type_destroy_double__ok(void** state)
{
    double d_input = 0.3;
    bool_t b_output = false;
    _type_destroy_double(&d_input, &b_output);
    assert_true(d_input == 0.3);
    assert_true(b_output);
}

/*
 * test _type_init_long_double
 */
UT_CASE_DEFINATION(_type_init_long_double)
void test__type_init_long_double__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_long_double(NULL, &b_output));
}

void test__type_init_long_double__null_output(void** state)
{
    long double ld_input = 10.34;
    expect_assert_failure(_type_init_long_double(&ld_input, NULL));
}

void test__type_init_long_double__ok(void** state)
{
    long double ld_input = 10.09054;
    bool_t b_output = false;
    _type_init_long_double(&ld_input, &b_output);
    assert_true(ld_input == 0.0);
    assert_true(b_output);
}

/*
 * test _type_copy_long_double
 */
UT_CASE_DEFINATION(_type_copy_long_double)
void test__type_copy_long_double__null_first(void** state)
{
    long double ld_second = -4.23;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_long_double(NULL, &ld_second, &b_output));
}

void test__type_copy_long_double__null_second(void** state)
{
    long double ld_first = 3.4;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_long_double(&ld_first, NULL, &b_output));
}

void test__type_copy_long_double__null_output(void** state)
{
    long double ld_first = 3.09;
    long double ld_second = 2.22;
    expect_assert_failure(_type_copy_long_double(&ld_first, &ld_second, NULL));
}

void test__type_copy_long_double__ok(void** state)
{
    long double ld_first = 5.23;
    long double ld_second = 2.11;
    bool_t b_output = false;
    _type_copy_long_double(&ld_first, &ld_second, &b_output);
    assert_true(ld_first == 2.11);
    assert_true(ld_second == 2.11);
    assert_true(b_output);
}

/*
 * test _type_less_long_double
 */
UT_CASE_DEFINATION(_type_less_long_double)
void test__type_less_long_double__null_first(void** state)
{
    long double ld_second = 4.0;
    bool_t b_output = false;
    expect_assert_failure(_type_less_long_double(NULL, &ld_second, &b_output));
}

void test__type_less_long_double__null_second(void** state)
{
    long double ld_first = 4.0;
    bool_t b_output = false;
    expect_assert_failure(_type_less_long_double(&ld_first, NULL, &b_output));
}

void test__type_less_long_double__null_output(void** state)
{
    long double ld_first = 4.0;
    long double ld_second = 3.4;
    expect_assert_failure(_type_less_long_double(&ld_first, &ld_second, NULL));
}

void test__type_less_long_double__less(void** state)
{
    long double ld_first = 4.9;
    long double ld_second = 9.0;
    bool_t b_output = false;
    _type_less_long_double(&ld_first, &ld_second, &b_output);
    assert_true(ld_first == 4.9);
    assert_true(ld_second == 9.0);
    assert_true(b_output);
}

void test__type_less_long_double__equal(void** state)
{
    long double ld_first = 4.0;
    long double ld_second = 4.0;
    bool_t b_output = false;
    _type_less_long_double(&ld_first, &ld_second, &b_output);
    assert_true(ld_first == 4.0);
    assert_true(ld_second == 4.0);
    assert_false(b_output);
}

void test__type_less_long_double__greater(void** state)
{
    long double ld_first = 5.00000001;
    long double ld_second = 5.0;
    bool_t b_output = false;
    _type_less_long_double(&ld_first, &ld_second, &b_output);
    assert_true(ld_first == 5.00000001);
    assert_true(ld_second == 5.0);
    assert_false(b_output);
}

/*
 * test _type_destroy_long_double
 */
UT_CASE_DEFINATION(_type_destroy_long_double)
void test__type_destroy_long_double__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_long_double(NULL, &b_output));
}

void test__type_destroy_long_double__null_output(void** state)
{
    long double ld_input = 4.3;
    expect_assert_failure(_type_destroy_long_double(&ld_input, NULL));
}

void test__type_destroy_long_double__ok(void** state)
{
    long double ld_input = 0.3;
    bool_t b_output = false;
    _type_destroy_long_double(&ld_input, &b_output);
    assert_true(ld_input == 0.3);
    assert_true(b_output);
}

/*
 * test _type_init_bool
 */
UT_CASE_DEFINATION(_type_init_bool)
void test__type_init_bool__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_bool(NULL, &b_output));
}

void test__type_init_bool__null_output(void** state)
{
    bool_t b_input = false;
    expect_assert_failure(_type_init_bool(&b_input, NULL));
}

void test__type_init_bool__ok(void** state)
{
    bool_t b_input = true;
    bool_t b_output = false;
    _type_init_bool(&b_input, &b_output);
    assert_false(b_input);
    assert_true(b_output);
}

/*
 * test _type_copy_bool
 */
UT_CASE_DEFINATION(_type_copy_bool)
void test__type_copy_bool__null_first(void** state)
{
    bool_t b_second = true;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_bool(NULL, &b_second, &b_output));
}

void test__type_copy_bool__null_second(void** state)
{
    bool_t b_first = true;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_bool(&b_first, NULL, &b_output));
}

void test__type_copy_bool__null_output(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    expect_assert_failure(_type_copy_bool(&b_first, &b_second, NULL));
}

void test__type_copy_bool__ok(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    bool_t b_output = false;
    _type_copy_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_false(b_second);
    assert_true(b_output);
}

/*
 * test _type_less_bool
 */
UT_CASE_DEFINATION(_type_less_bool)
void test__type_less_bool__null_first(void** state)
{
    bool_t b_second = true;
    bool_t b_output = false;
    expect_assert_failure(_type_less_bool(NULL, &b_second, &b_output));
}

void test__type_less_bool__null_second(void** state)
{
    bool_t b_first = true;
    bool_t b_output = false;
    expect_assert_failure(_type_less_bool(&b_first, NULL, &b_output));
}

void test__type_less_bool__null_output(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    expect_assert_failure(_type_less_bool(&b_first, &b_second, NULL));
}

void test__type_less_bool__less(void** state)
{
    bool_t b_first = false;
    bool_t b_second = true;
    bool_t b_output = false;
    _type_less_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_true(b_second);
    assert_true(b_output);
}

void test__type_less_bool__equal(void** state)
{
    bool_t b_first = false;
    bool_t b_second = false;
    bool_t b_output = false;
    _type_less_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_false(b_second);
    assert_false(b_output);
}

void test__type_less_bool__greater(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    bool_t b_output = false;
    _type_less_bool(&b_first, &b_second, &b_output);
    assert_true(b_first);
    assert_false(b_second);
    assert_false(b_output);
}

/*
 * test _type_destroy_bool
 */
UT_CASE_DEFINATION(_type_destroy_bool)
void test__type_destroy_bool__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_bool(NULL, &b_output));
}

void test__type_destroy_bool__null_output(void** state)
{
    bool_t b_input = false;
    expect_assert_failure(_type_destroy_bool(&b_input, NULL));
}

void test__type_destroy_bool__ok(void** state)
{
    bool_t b_input = false;
    bool_t b_output = false;
    _type_destroy_bool(&b_input, &b_output);
    assert_false(b_input);
    assert_true(b_output);
}

/*
 * test _type_init_cstr
 */
UT_CASE_DEFINATION(_type_init_cstr)
void test__type_init_cstr__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_cstr(NULL, &b_output));
}

void test__type_init_cstr__null_output(void** state)
{
    string_t* pstr_input = malloc(sizeof(string_t));
    if (pstr_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_cstr(pstr_input, NULL));
}

void test__type_init_cstr__ok(void** state)
{
    bool_t b_output = false;
    string_t* pstr_input = malloc(sizeof(string_t));
    if (pstr_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_cstr(pstr_input, &b_output);
    assert_true(b_output);
    string_destroy(pstr_input);
}

/*
 * test _type_copy_cstr
 */
UT_CASE_DEFINATION(_type_copy_cstr)
void test__type_copy_cstr__null_first(void** state)
{
    bool_t b_output = false;
    string_t* pstr_second = create_string();
    if (pstr_second == NULL) {
        assert_true(false);
        return;
    }

    string_init(pstr_second);
    expect_assert_failure(_type_copy_cstr(NULL, pstr_second, &b_output));
    string_destroy(pstr_second);
}

void test__type_copy_cstr__null_second(void** state)
{
    bool_t b_output = false;
    string_t* pstr_first = create_string();
    if (pstr_first == NULL) {
        assert_true(false);
        return;
    }

    string_init(pstr_first);
    expect_assert_failure(_type_copy_cstr(pstr_first, NULL, &b_output));
    string_destroy(pstr_first);
}

void test__type_copy_cstr__null_output(void** state)
{
    string_t* pstr_first = NULL;
    string_t* pstr_second = NULL;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        string_destroy(pstr_first);
        return;
    }
    string_init(pstr_first);
    string_init(pstr_second);
    expect_assert_failure(_type_copy_cstr(pstr_first, pstr_second, NULL));
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_copy_cstr__ok(void** state)
{
    string_t* pstr_first = NULL;
    string_t* pstr_second = NULL;
    bool_t b_output = false;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        string_destroy(pstr_first);
        return;
    }
    string_init(pstr_first);
    string_init_cstr(pstr_second, "abc");
    _type_copy_cstr(pstr_first, pstr_second, &b_output);
    assert_true(strcmp(string_c_str(pstr_first), "abc") == 0);
    assert_true(strcmp(string_c_str(pstr_second), "abc") == 0);
    assert_true(string_equal(pstr_first, pstr_second));
    assert_true(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test _type_less_cstr
 */
UT_CASE_DEFINATION(_type_less_cstr)
void test__type_less_cstr__null_first(void** state)
{
    bool_t b_output = false;
    string_t* pstr_second = create_string();
    if (pstr_second == NULL) {
        assert_true(false);
        return;
    }

    string_init(pstr_second);
    expect_assert_failure(_type_less_cstr(NULL, pstr_second, &b_output));
    string_destroy(pstr_second);
}

void test__type_less_cstr__null_second(void** state)
{
    bool_t b_output = false;
    string_t* pstr_first = create_string();
    if (pstr_first == NULL) {
        assert_true(false);
        return;
    }

    string_init(pstr_first);
    expect_assert_failure(_type_less_cstr(pstr_first, NULL, &b_output));
    string_destroy(pstr_first);
}

void test__type_less_cstr__null_output(void** state)
{
    string_t* pstr_first = NULL;
    string_t* pstr_second = NULL;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        string_destroy(pstr_first);
        return;
    }
    string_init(pstr_first);
    string_init(pstr_second);
    expect_assert_failure(_type_less_cstr(pstr_first, pstr_second, NULL));
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_less_cstr__less(void** state)
{
    string_t* pstr_first = NULL;
    string_t* pstr_second = NULL;
    bool_t b_output = false;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        string_destroy(pstr_first);
        return;
    }
    string_init(pstr_first);
    string_init_cstr(pstr_second, "abc");
    _type_less_cstr(pstr_first, pstr_second, &b_output);
    assert_true(string_empty(pstr_first));
    assert_true(strcmp(string_c_str(pstr_second), "abc") == 0);
    assert_true(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_less_cstr__equal(void** state)
{
    string_t* pstr_first = NULL;
    string_t* pstr_second = NULL;
    bool_t b_output = false;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        string_destroy(pstr_first);
        return;
    }
    string_init_cstr(pstr_first, "abc");
    string_init_cstr(pstr_second, "abc");
    _type_less_cstr(pstr_first, pstr_second, &b_output);
    assert_true(strcmp(string_c_str(pstr_first), "abc") == 0);
    assert_true(strcmp(string_c_str(pstr_second), "abc") == 0);
    assert_false(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_less_cstr__greater(void** state)
{
    string_t* pstr_first = NULL;
    string_t* pstr_second = NULL;
    bool_t b_output = false;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        string_destroy(pstr_first);
        return;
    }
    string_init_cstr(pstr_first, "abcd");
    string_init_cstr(pstr_second, "abc");
    _type_less_cstr(pstr_first, pstr_second, &b_output);
    assert_true(strcmp(string_c_str(pstr_first), "abcd") == 0);
    assert_true(strcmp(string_c_str(pstr_second), "abc") == 0);
    assert_false(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test _type_destroy_cstr
 */
UT_CASE_DEFINATION(_type_destroy_cstr)
void test__type_destroy_cstr__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_cstr(NULL, &b_output));
}

void test__type_destroy_cstr__null_output(void** state)
{
    string_t* pstr_input = create_string();
    if (pstr_input == NULL) {
        assert_true(false);
        return;
    }
    string_init(pstr_input);
    expect_assert_failure(_type_destroy_cstr(pstr_input, NULL));
    string_destroy(pstr_input);
}

void test__type_destroy_cstr__ok(void** state)
{
    string_t* pstr_input = NULL;
    bool_t b_output = false;

    if ((pstr_input = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    string_init_cstr(pstr_input, "abc");
    _type_destroy_cstr(pstr_input, &b_output);
    assert_true(b_output);
    free(pstr_input);
}

/*
 * test _type_init_vector
 */
UT_CASE_DEFINATION(_type_init_vector)
void test__type_init_vector__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_vector(NULL, &b_output));
}

void test__type_init_vector__null_output(void** state)
{
    vector_t* pvec_input = malloc(sizeof(vector_t));
    if (pvec_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_vector(pvec_input, NULL));
    free(pvec_input);
}

void test__type_init_vector__ok(void** state)
{
    vector_t* pvec_input = malloc(sizeof(vector_t));
    const char* b_output = "int";
    if (pvec_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_vector(pvec_input, b_output);
    assert_true(_vector_is_inited(pvec_input));
    vector_destroy(pvec_input);
}

/*
 * test _type_copy_vector
 */
UT_CASE_DEFINATION(_type_copy_vector)
void test__type_copy_vector__null_first(void** state)
{
    vector_t* pvec_second = NULL;
    bool_t b_output = false;
    
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    vector_init(pvec_second);
    expect_assert_failure(_type_copy_vector(NULL, pvec_second, &b_output));
    vector_destroy(pvec_second);
}

void test__type_copy_vector__null_second(void** state)
{
    vector_t* pvec_first = NULL;
    bool_t b_output = false;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(pvec_first);
        return;
    }
    vector_init(pvec_first);
    expect_assert_failure(_type_copy_vector(pvec_first, NULL, &b_output));
    vector_destroy(pvec_first);
}

void test__type_copy_vector__null_output(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        vector_destroy(pvec_first);
        return;
    }
    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(_type_copy_vector(pvec_first, pvec_second, NULL));
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__type_copy_vector__ok(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;
    bool_t b_output = false;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        vector_destroy(pvec_first);
        return;
    }
    vector_init(pvec_first);
    vector_init_n(pvec_second, 10);
    _type_copy_vector(pvec_first, pvec_second, &b_output);
    assert_true(vector_size(pvec_first) == 10);
    assert_true(vector_size(pvec_second) == 10);
    assert_true(vector_equal(pvec_first, pvec_second));
    assert_true(b_output);
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test _type_less_vector
 */
UT_CASE_DEFINATION(_type_less_vector)
void test__type_less_vector__null_first(void** state)
{
    vector_t* pvec_second = NULL;
    bool_t b_output = false;
    
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    vector_init(pvec_second);
    expect_assert_failure(_type_less_vector(NULL, pvec_second, &b_output));
    vector_destroy(pvec_second);
}

void test__type_less_vector__null_second(void** state)
{
    vector_t* pvec_first = NULL;
    bool_t b_output = false;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(pvec_first);
        return;
    }
    vector_init(pvec_first);
    expect_assert_failure(_type_less_vector(pvec_first, NULL, &b_output));
    vector_destroy(pvec_first);
}

void test__type_less_vector__null_output(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        vector_destroy(pvec_first);
        return;
    }
    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(_type_less_vector(pvec_first, pvec_second, NULL));
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__type_less_vector__less(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;
    bool_t b_output = false;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        vector_destroy(pvec_first);
        return;
    }
    vector_init(pvec_first);
    vector_init_n(pvec_second, 10);
    _type_less_vector(pvec_first, pvec_second, &b_output);
    assert_true(vector_empty(pvec_first));
    assert_true(vector_size(pvec_second) == 10);
    assert_true(b_output);
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__type_less_vector__equal(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;
    bool_t b_output = false;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        vector_destroy(pvec_first);
        return;
    }
    vector_init_n(pvec_first, 10);
    vector_init_n(pvec_second, 10);
    _type_less_vector(pvec_first, pvec_second, &b_output);
    assert_true(vector_size(pvec_first) == 10);
    assert_true(vector_size(pvec_second) == 10);
    assert_true(vector_equal(pvec_first, pvec_second));
    assert_false(b_output);
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__type_less_vector__greater(void** state)
{
    vector_t* pvec_first = NULL;
    vector_t* pvec_second = NULL;
    bool_t b_output = false;
    if ((pvec_first = create_vector(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pvec_second = create_vector(int)) == NULL) {
        assert_true(false);
        vector_destroy(pvec_first);
        return;
    }
    vector_init_n(pvec_first, 10);
    vector_init_n(pvec_second, 4);
    _type_less_vector(pvec_first, pvec_second, &b_output);
    assert_true(vector_size(pvec_first) == 10);
    assert_true(vector_size(pvec_second) == 4);
    assert_false(b_output);
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test _type_destroy_vector
 */
UT_CASE_DEFINATION(_type_destroy_vector)
void test__type_destroy_vector__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_vector(NULL, &b_output));
}

void test__type_destroy_vector__null_output(void** state)
{
    vector_t* pvec_input = create_vector(int);
    if (pvec_input == NULL) {
        assert_true(false);
        return;
    }
    vector_init(pvec_input);
    expect_assert_failure(_type_destroy_vector(pvec_input, NULL));
    vector_destroy(pvec_input);
}

void test__type_destroy_vector__ok(void** state)
{
    bool_t b_output = false;
    vector_t* pvec_input = create_vector(int);
    if (pvec_input == NULL) {
        assert_true(false);
        return;
    }
    vector_init_n(pvec_input, 10);
    _type_destroy_vector(pvec_input, &b_output);
    assert_true(b_output);
    vector_destroy(pvec_input);
}

