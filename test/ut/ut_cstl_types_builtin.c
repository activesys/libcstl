#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl/cslist.h"
#include "cstl/cdeque.h"
#include "cstl/cstack.h"
#include "cstl/cqueue.h"
#include "cstl/cset.h"
#include "cstl/cmap.h"
#include "cstl/chash_set.h"
#include "cstl/chash_map.h"
#include "cstl/cstring.h"
#include "cstl_types_builtin.h"
#include "cstl_vector_aux.h"
#include "cstl_list_aux.h"
#include "cstl_slist_aux.h"
#include "cstl_deque_aux.h"
#include "cstl_basic_string_aux.h"

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
 * test _type_init_cstl_bool
 */
UT_CASE_DEFINATION(_type_init_cstl_bool)
void test__type_init_cstl_bool__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_cstl_bool(NULL, &b_output));
}

void test__type_init_cstl_bool__null_output(void** state)
{
    bool_t b_input = false;
    expect_assert_failure(_type_init_cstl_bool(&b_input, NULL));
}

void test__type_init_cstl_bool__ok(void** state)
{
    bool_t b_input = true;
    bool_t b_output = false;
    _type_init_cstl_bool(&b_input, &b_output);
    assert_false(b_input);
    assert_true(b_output);
}

/*
 * test _type_copy_cstl_bool
 */
UT_CASE_DEFINATION(_type_copy_cstl_bool)
void test__type_copy_cstl_bool__null_first(void** state)
{
    bool_t b_second = true;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_cstl_bool(NULL, &b_second, &b_output));
}

void test__type_copy_cstl_bool__null_second(void** state)
{
    bool_t b_first = true;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_cstl_bool(&b_first, NULL, &b_output));
}

void test__type_copy_cstl_bool__null_output(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    expect_assert_failure(_type_copy_cstl_bool(&b_first, &b_second, NULL));
}

void test__type_copy_cstl_bool__ok(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    bool_t b_output = false;
    _type_copy_cstl_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_false(b_second);
    assert_true(b_output);
}

/*
 * test _type_less_cstl_bool
 */
UT_CASE_DEFINATION(_type_less_cstl_bool)
void test__type_less_cstl_bool__null_first(void** state)
{
    bool_t b_second = true;
    bool_t b_output = false;
    expect_assert_failure(_type_less_cstl_bool(NULL, &b_second, &b_output));
}

void test__type_less_cstl_bool__null_second(void** state)
{
    bool_t b_first = true;
    bool_t b_output = false;
    expect_assert_failure(_type_less_cstl_bool(&b_first, NULL, &b_output));
}

void test__type_less_cstl_bool__null_output(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    expect_assert_failure(_type_less_cstl_bool(&b_first, &b_second, NULL));
}

void test__type_less_cstl_bool__less(void** state)
{
    bool_t b_first = false;
    bool_t b_second = true;
    bool_t b_output = false;
    _type_less_cstl_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_true(b_second);
    assert_true(b_output);
}

void test__type_less_cstl_bool__equal(void** state)
{
    bool_t b_first = false;
    bool_t b_second = false;
    bool_t b_output = false;
    _type_less_cstl_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_false(b_second);
    assert_false(b_output);
}

void test__type_less_cstl_bool__greater(void** state)
{
    bool_t b_first = true;
    bool_t b_second = false;
    bool_t b_output = false;
    _type_less_cstl_bool(&b_first, &b_second, &b_output);
    assert_true(b_first);
    assert_false(b_second);
    assert_false(b_output);
}

/*
 * test _type_destroy_cstl_bool
 */
UT_CASE_DEFINATION(_type_destroy_cstl_bool)
void test__type_destroy_cstl_bool__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_cstl_bool(NULL, &b_output));
}

void test__type_destroy_cstl_bool__null_output(void** state)
{
    bool_t b_input = false;
    expect_assert_failure(_type_destroy_cstl_bool(&b_input, NULL));
}

void test__type_destroy_cstl_bool__ok(void** state)
{
    bool_t b_input = false;
    bool_t b_output = false;
    _type_destroy_cstl_bool(&b_input, &b_output);
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
    /*string_destroy(pstr_input);*/
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
    _type_init_vector(pvec_input, (void*)b_output);
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
    free(pvec_input);
}

/*
 * test _type_init_list
 */
UT_CASE_DEFINATION(_type_init_list)
void test__type_init_list__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_list(NULL, &b_output));
}

void test__type_init_list__null_output(void** state)
{
    list_t* plist_input = malloc(sizeof(list_t));
    if (plist_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_list(plist_input, NULL));
    free(plist_input);
}

void test__type_init_list__ok(void** state)
{
    list_t* plist_input = malloc(sizeof(list_t));
    const char* b_output = "int";
    if (plist_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_list(plist_input, (void*)b_output);
    assert_true(_list_is_inited(plist_input));
    list_destroy(plist_input);
}

/*
 * test _type_copy_list
 */
UT_CASE_DEFINATION(_type_copy_list)
void test__type_copy_list__null_first(void** state)
{
    list_t* plist_second = NULL;
    bool_t b_output = false;
    
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    list_init(plist_second);
    expect_assert_failure(_type_copy_list(NULL, plist_second, &b_output));
    list_destroy(plist_second);
}

void test__type_copy_list__null_second(void** state)
{
    list_t* plist_first = NULL;
    bool_t b_output = false;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(plist_first);
        return;
    }
    list_init(plist_first);
    expect_assert_failure(_type_copy_list(plist_first, NULL, &b_output));
    list_destroy(plist_first);
}

void test__type_copy_list__null_output(void** state)
{
    list_t* plist_first = NULL;
    list_t* plist_second = NULL;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        list_destroy(plist_first);
        return;
    }
    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(_type_copy_list(plist_first, plist_second, NULL));
    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__type_copy_list__ok(void** state)
{
    list_t* plist_first = NULL;
    list_t* plist_second = NULL;
    bool_t b_output = false;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        list_destroy(plist_first);
        return;
    }
    list_init(plist_first);
    list_init_n(plist_second, 10);
    _type_copy_list(plist_first, plist_second, &b_output);
    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 10);
    assert_true(list_equal(plist_first, plist_second));
    assert_true(b_output);
    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test _type_less_list
 */
UT_CASE_DEFINATION(_type_less_list)
void test__type_less_list__null_first(void** state)
{
    list_t* plist_second = NULL;
    bool_t b_output = false;
    
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    list_init(plist_second);
    expect_assert_failure(_type_less_list(NULL, plist_second, &b_output));
    list_destroy(plist_second);
}

void test__type_less_list__null_second(void** state)
{
    list_t* plist_first = NULL;
    bool_t b_output = false;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(plist_first);
        return;
    }
    list_init(plist_first);
    expect_assert_failure(_type_less_list(plist_first, NULL, &b_output));
    list_destroy(plist_first);
}

void test__type_less_list__null_output(void** state)
{
    list_t* plist_first = NULL;
    list_t* plist_second = NULL;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        list_destroy(plist_first);
        return;
    }
    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(_type_less_list(plist_first, plist_second, NULL));
    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__type_less_list__less(void** state)
{
    list_t* plist_first = NULL;
    list_t* plist_second = NULL;
    bool_t b_output = false;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        list_destroy(plist_first);
        return;
    }
    list_init(plist_first);
    list_init_n(plist_second, 10);
    _type_less_list(plist_first, plist_second, &b_output);
    assert_true(list_empty(plist_first));
    assert_true(list_size(plist_second) == 10);
    assert_true(b_output);
    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__type_less_list__equal(void** state)
{
    list_t* plist_first = NULL;
    list_t* plist_second = NULL;
    bool_t b_output = false;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        list_destroy(plist_first);
        return;
    }
    list_init_n(plist_first, 10);
    list_init_n(plist_second, 10);
    _type_less_list(plist_first, plist_second, &b_output);
    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 10);
    assert_true(list_equal(plist_first, plist_second));
    assert_false(b_output);
    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__type_less_list__greater(void** state)
{
    list_t* plist_first = NULL;
    list_t* plist_second = NULL;
    bool_t b_output = false;
    if ((plist_first = create_list(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((plist_second = create_list(int)) == NULL) {
        assert_true(false);
        list_destroy(plist_first);
        return;
    }
    list_init_n(plist_first, 10);
    list_init_n(plist_second, 4);
    _type_less_list(plist_first, plist_second, &b_output);
    assert_true(list_size(plist_first) == 10);
    assert_true(list_size(plist_second) == 4);
    assert_false(b_output);
    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test _type_destroy_list
 */
UT_CASE_DEFINATION(_type_destroy_list)
void test__type_destroy_list__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_list(NULL, &b_output));
}

void test__type_destroy_list__null_output(void** state)
{
    list_t* plist_input = create_list(int);
    if (plist_input == NULL) {
        assert_true(false);
        return;
    }
    list_init(plist_input);
    expect_assert_failure(_type_destroy_list(plist_input, NULL));
    list_destroy(plist_input);
}

void test__type_destroy_list__ok(void** state)
{
    bool_t b_output = false;
    list_t* plist_input = create_list(int);
    if (plist_input == NULL) {
        assert_true(false);
        return;
    }
    list_init_n(plist_input, 10);
    _type_destroy_list(plist_input, &b_output);
    assert_true(b_output);
    free(plist_input);
}

/*
 * test _type_init_slist
 */
UT_CASE_DEFINATION(_type_init_slist)
void test__type_init_slist__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_slist(NULL, &b_output));
}

void test__type_init_slist__null_output(void** state)
{
    slist_t* pslist_input = malloc(sizeof(slist_t));
    if (pslist_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_slist(pslist_input, NULL));
    free(pslist_input);
}

void test__type_init_slist__ok(void** state)
{
    slist_t* pslist_input = malloc(sizeof(slist_t));
    const char* b_output = "int";
    if (pslist_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_slist(pslist_input, (void*)b_output);
    assert_true(_slist_is_inited(pslist_input));
    slist_destroy(pslist_input);
}

/*
 * test _type_copy_slist
 */
UT_CASE_DEFINATION(_type_copy_slist)
void test__type_copy_slist__null_first(void** state)
{
    slist_t* pslist_second = NULL;
    bool_t b_output = false;
    
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    slist_init(pslist_second);
    expect_assert_failure(_type_copy_slist(NULL, pslist_second, &b_output));
    slist_destroy(pslist_second);
}

void test__type_copy_slist__null_second(void** state)
{
    slist_t* pslist_first = NULL;
    bool_t b_output = false;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(pslist_first);
        return;
    }
    slist_init(pslist_first);
    expect_assert_failure(_type_copy_slist(pslist_first, NULL, &b_output));
    slist_destroy(pslist_first);
}

void test__type_copy_slist__null_output(void** state)
{
    slist_t* pslist_first = NULL;
    slist_t* pslist_second = NULL;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        slist_destroy(pslist_first);
        return;
    }
    slist_init(pslist_first);
    slist_init(pslist_second);
    expect_assert_failure(_type_copy_slist(pslist_first, pslist_second, NULL));
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__type_copy_slist__ok(void** state)
{
    slist_t* pslist_first = NULL;
    slist_t* pslist_second = NULL;
    bool_t b_output = false;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        slist_destroy(pslist_first);
        return;
    }
    slist_init(pslist_first);
    slist_init_n(pslist_second, 10);
    _type_copy_slist(pslist_first, pslist_second, &b_output);
    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 10);
    assert_true(slist_equal(pslist_first, pslist_second));
    assert_true(b_output);
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test _type_less_slist
 */
UT_CASE_DEFINATION(_type_less_slist)
void test__type_less_slist__null_first(void** state)
{
    slist_t* pslist_second = NULL;
    bool_t b_output = false;
    
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    slist_init(pslist_second);
    expect_assert_failure(_type_less_slist(NULL, pslist_second, &b_output));
    slist_destroy(pslist_second);
}

void test__type_less_slist__null_second(void** state)
{
    slist_t* pslist_first = NULL;
    bool_t b_output = false;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(pslist_first);
        return;
    }
    slist_init(pslist_first);
    expect_assert_failure(_type_less_slist(pslist_first, NULL, &b_output));
    slist_destroy(pslist_first);
}

void test__type_less_slist__null_output(void** state)
{
    slist_t* pslist_first = NULL;
    slist_t* pslist_second = NULL;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        slist_destroy(pslist_first);
        return;
    }
    slist_init(pslist_first);
    slist_init(pslist_second);
    expect_assert_failure(_type_less_slist(pslist_first, pslist_second, NULL));
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__type_less_slist__less(void** state)
{
    slist_t* pslist_first = NULL;
    slist_t* pslist_second = NULL;
    bool_t b_output = false;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        slist_destroy(pslist_first);
        return;
    }
    slist_init(pslist_first);
    slist_init_n(pslist_second, 10);
    _type_less_slist(pslist_first, pslist_second, &b_output);
    assert_true(slist_empty(pslist_first));
    assert_true(slist_size(pslist_second) == 10);
    assert_true(b_output);
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__type_less_slist__equal(void** state)
{
    slist_t* pslist_first = NULL;
    slist_t* pslist_second = NULL;
    bool_t b_output = false;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        slist_destroy(pslist_first);
        return;
    }
    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 10);
    _type_less_slist(pslist_first, pslist_second, &b_output);
    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 10);
    assert_true(slist_equal(pslist_first, pslist_second));
    assert_false(b_output);
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__type_less_slist__greater(void** state)
{
    slist_t* pslist_first = NULL;
    slist_t* pslist_second = NULL;
    bool_t b_output = false;
    if ((pslist_first = create_slist(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pslist_second = create_slist(int)) == NULL) {
        assert_true(false);
        slist_destroy(pslist_first);
        return;
    }
    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 4);
    _type_less_slist(pslist_first, pslist_second, &b_output);
    assert_true(slist_size(pslist_first) == 10);
    assert_true(slist_size(pslist_second) == 4);
    assert_false(b_output);
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test _type_destroy_slist
 */
UT_CASE_DEFINATION(_type_destroy_slist)
void test__type_destroy_slist__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_slist(NULL, &b_output));
}

void test__type_destroy_slist__null_output(void** state)
{
    slist_t* pslist_input = create_slist(int);
    if (pslist_input == NULL) {
        assert_true(false);
        return;
    }
    slist_init(pslist_input);
    expect_assert_failure(_type_destroy_slist(pslist_input, NULL));
    slist_destroy(pslist_input);
}

void test__type_destroy_slist__ok(void** state)
{
    bool_t b_output = false;
    slist_t* pslist_input = create_slist(int);
    if (pslist_input == NULL) {
        assert_true(false);
        return;
    }
    slist_init_n(pslist_input, 10);
    _type_destroy_slist(pslist_input, &b_output);
    assert_true(b_output);
    free(pslist_input);
}

/*
 * test _type_init_deque
 */
UT_CASE_DEFINATION(_type_init_deque)
void test__type_init_deque__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_deque(NULL, &b_output));
}

void test__type_init_deque__null_output(void** state)
{
    deque_t* pdeq_input = malloc(sizeof(deque_t));
    if (pdeq_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_deque(pdeq_input, NULL));
    free(pdeq_input);
}

void test__type_init_deque__ok(void** state)
{
    deque_t* pdeq_input = malloc(sizeof(deque_t));
    const char* b_output = "int";
    if (pdeq_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_deque(pdeq_input, (void*)b_output);
    assert_true(_deque_is_inited(pdeq_input));
    deque_destroy(pdeq_input);
}

/*
 * test _type_copy_deque
 */
UT_CASE_DEFINATION(_type_copy_deque)
void test__type_copy_deque__null_first(void** state)
{
    deque_t* pdeq_second = NULL;
    bool_t b_output = false;
    
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    deque_init(pdeq_second);
    expect_assert_failure(_type_copy_deque(NULL, pdeq_second, &b_output));
    deque_destroy(pdeq_second);
}

void test__type_copy_deque__null_second(void** state)
{
    deque_t* pdeq_first = NULL;
    bool_t b_output = false;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(pdeq_first);
        return;
    }
    deque_init(pdeq_first);
    expect_assert_failure(_type_copy_deque(pdeq_first, NULL, &b_output));
    deque_destroy(pdeq_first);
}

void test__type_copy_deque__null_output(void** state)
{
    deque_t* pdeq_first = NULL;
    deque_t* pdeq_second = NULL;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        deque_destroy(pdeq_first);
        return;
    }
    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(_type_copy_deque(pdeq_first, pdeq_second, NULL));
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__type_copy_deque__ok(void** state)
{
    deque_t* pdeq_first = NULL;
    deque_t* pdeq_second = NULL;
    bool_t b_output = false;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        deque_destroy(pdeq_first);
        return;
    }
    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 10);
    _type_copy_deque(pdeq_first, pdeq_second, &b_output);
    assert_true(deque_size(pdeq_first) == 10);
    assert_true(deque_size(pdeq_second) == 10);
    assert_true(deque_equal(pdeq_first, pdeq_second));
    assert_true(b_output);
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test _type_less_deque
 */
UT_CASE_DEFINATION(_type_less_deque)
void test__type_less_deque__null_first(void** state)
{
    deque_t* pdeq_second = NULL;
    bool_t b_output = false;
    
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    deque_init(pdeq_second);
    expect_assert_failure(_type_less_deque(NULL, pdeq_second, &b_output));
    deque_destroy(pdeq_second);
}

void test__type_less_deque__null_second(void** state)
{
    deque_t* pdeq_first = NULL;
    bool_t b_output = false;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(pdeq_first);
        return;
    }
    deque_init(pdeq_first);
    expect_assert_failure(_type_less_deque(pdeq_first, NULL, &b_output));
    deque_destroy(pdeq_first);
}

void test__type_less_deque__null_output(void** state)
{
    deque_t* pdeq_first = NULL;
    deque_t* pdeq_second = NULL;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        deque_destroy(pdeq_first);
        return;
    }
    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(_type_less_deque(pdeq_first, pdeq_second, NULL));
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__type_less_deque__less(void** state)
{
    deque_t* pdeq_first = NULL;
    deque_t* pdeq_second = NULL;
    bool_t b_output = false;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        deque_destroy(pdeq_first);
        return;
    }
    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 10);
    _type_less_deque(pdeq_first, pdeq_second, &b_output);
    assert_true(deque_empty(pdeq_first));
    assert_true(deque_size(pdeq_second) == 10);
    assert_true(b_output);
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__type_less_deque__equal(void** state)
{
    deque_t* pdeq_first = NULL;
    deque_t* pdeq_second = NULL;
    bool_t b_output = false;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        deque_destroy(pdeq_first);
        return;
    }
    deque_init_n(pdeq_first, 10);
    deque_init_n(pdeq_second, 10);
    _type_less_deque(pdeq_first, pdeq_second, &b_output);
    assert_true(deque_size(pdeq_first) == 10);
    assert_true(deque_size(pdeq_second) == 10);
    assert_true(deque_equal(pdeq_first, pdeq_second));
    assert_false(b_output);
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test__type_less_deque__greater(void** state)
{
    deque_t* pdeq_first = NULL;
    deque_t* pdeq_second = NULL;
    bool_t b_output = false;
    if ((pdeq_first = create_deque(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pdeq_second = create_deque(int)) == NULL) {
        assert_true(false);
        deque_destroy(pdeq_first);
        return;
    }
    deque_init_n(pdeq_first, 10);
    deque_init_n(pdeq_second, 4);
    _type_less_deque(pdeq_first, pdeq_second, &b_output);
    assert_true(deque_size(pdeq_first) == 10);
    assert_true(deque_size(pdeq_second) == 4);
    assert_false(b_output);
    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test _type_destroy_deque
 */
UT_CASE_DEFINATION(_type_destroy_deque)
void test__type_destroy_deque__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_deque(NULL, &b_output));
}

void test__type_destroy_deque__null_output(void** state)
{
    deque_t* pdeq_input = create_deque(int);
    if (pdeq_input == NULL) {
        assert_true(false);
        return;
    }
    deque_init(pdeq_input);
    expect_assert_failure(_type_destroy_deque(pdeq_input, NULL));
    deque_destroy(pdeq_input);
}

void test__type_destroy_deque__ok(void** state)
{
    bool_t b_output = false;
    deque_t* pdeq_input = create_deque(int);
    if (pdeq_input == NULL) {
        assert_true(false);
        return;
    }
    deque_init_n(pdeq_input, 10);
    _type_destroy_deque(pdeq_input, &b_output);
    assert_true(b_output);
    free(pdeq_input);
}

/*
 * test _type_init_stack
 */
UT_CASE_DEFINATION(_type_init_stack)
void test__type_init_stack__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_stack(NULL, &b_output));
}

void test__type_init_stack__null_output(void** state)
{
    stack_t* pstack_input = malloc(sizeof(stack_t));
    if (pstack_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_stack(pstack_input, NULL));
    free(pstack_input);
}

void test__type_init_stack__ok(void** state)
{
    stack_t* pstack_input = malloc(sizeof(stack_t));
    const char* b_output = "int";
    if (pstack_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_stack(pstack_input, (void*)b_output);
    //assert_true(_stack_is_inited(pstack_input));
    stack_destroy(pstack_input);
}

/*
 * test _type_copy_stack
 */
UT_CASE_DEFINATION(_type_copy_stack)
void test__type_copy_stack__null_first(void** state)
{
    stack_t* pstack_second = NULL;
    bool_t b_output = false;
    
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    stack_init(pstack_second);
    expect_assert_failure(_type_copy_stack(NULL, pstack_second, &b_output));
    stack_destroy(pstack_second);
}

void test__type_copy_stack__null_second(void** state)
{
    stack_t* pstack_first = NULL;
    bool_t b_output = false;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(pstack_first);
        return;
    }
    stack_init(pstack_first);
    expect_assert_failure(_type_copy_stack(pstack_first, NULL, &b_output));
    stack_destroy(pstack_first);
}

void test__type_copy_stack__null_output(void** state)
{
    stack_t* pstack_first = NULL;
    stack_t* pstack_second = NULL;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        stack_destroy(pstack_first);
        return;
    }
    stack_init(pstack_first);
    stack_init(pstack_second);
    expect_assert_failure(_type_copy_stack(pstack_first, pstack_second, NULL));
    stack_destroy(pstack_first);
    stack_destroy(pstack_second);
}

void test__type_copy_stack__ok(void** state)
{
    stack_t* pstack_first = NULL;
    stack_t* pstack_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        stack_destroy(pstack_first);
        return;
    }
    stack_init(pstack_first);
    stack_init(pstack_second);
    for (i = 0; i < 10; ++i) {
        stack_push(pstack_second, i);
    }
    _type_copy_stack(pstack_first, pstack_second, &b_output);
    assert_true(stack_size(pstack_first) == 10);
    assert_true(stack_size(pstack_second) == 10);
    assert_true(stack_equal(pstack_first, pstack_second));
    assert_true(b_output);
    stack_destroy(pstack_first);
    stack_destroy(pstack_second);
}

/*
 * test _type_less_stack
 */
UT_CASE_DEFINATION(_type_less_stack)
void test__type_less_stack__null_first(void** state)
{
    stack_t* pstack_second = NULL;
    bool_t b_output = false;
    
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    stack_init(pstack_second);
    expect_assert_failure(_type_less_stack(NULL, pstack_second, &b_output));
    stack_destroy(pstack_second);
}

void test__type_less_stack__null_second(void** state)
{
    stack_t* pstack_first = NULL;
    bool_t b_output = false;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(pstack_first);
        return;
    }
    stack_init(pstack_first);
    expect_assert_failure(_type_less_stack(pstack_first, NULL, &b_output));
    stack_destroy(pstack_first);
}

void test__type_less_stack__null_output(void** state)
{
    stack_t* pstack_first = NULL;
    stack_t* pstack_second = NULL;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        stack_destroy(pstack_first);
        return;
    }
    stack_init(pstack_first);
    stack_init(pstack_second);
    expect_assert_failure(_type_less_stack(pstack_first, pstack_second, NULL));
    stack_destroy(pstack_first);
    stack_destroy(pstack_second);
}

void test__type_less_stack__less(void** state)
{
    stack_t* pstack_first = NULL;
    stack_t* pstack_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        stack_destroy(pstack_first);
        return;
    }
    stack_init(pstack_first);
    stack_init(pstack_second);
    for (i = 0; i < 10; ++i) {
        stack_push(pstack_second, i);
    }
    _type_less_stack(pstack_first, pstack_second, &b_output);
    assert_true(stack_empty(pstack_first));
    assert_true(stack_size(pstack_second) == 10);
    assert_true(b_output);
    stack_destroy(pstack_first);
    stack_destroy(pstack_second);
}

void test__type_less_stack__equal(void** state)
{
    stack_t* pstack_first = NULL;
    stack_t* pstack_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        stack_destroy(pstack_first);
        return;
    }
    stack_init(pstack_first);
    for (i = 0; i < 10; ++i) {
        stack_push(pstack_first, i);
    }
    stack_init(pstack_second);
    for (i = 0; i < 10; ++i) {
        stack_push(pstack_second, i);
    }
    _type_less_stack(pstack_first, pstack_second, &b_output);
    assert_true(stack_size(pstack_first) == 10);
    assert_true(stack_size(pstack_second) == 10);
    assert_true(stack_equal(pstack_first, pstack_second));
    assert_false(b_output);
    stack_destroy(pstack_first);
    stack_destroy(pstack_second);
}

void test__type_less_stack__greater(void** state)
{
    stack_t* pstack_first = NULL;
    stack_t* pstack_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pstack_first = create_stack(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pstack_second = create_stack(int)) == NULL) {
        assert_true(false);
        stack_destroy(pstack_first);
        return;
    }
    stack_init(pstack_first);
    for (i = 0; i < 10; ++i) {
        stack_push(pstack_first, i);
    }
    stack_init(pstack_second);
    for (i = 0; i < 4; ++i) {
        stack_push(pstack_second, i);
    }
    _type_less_stack(pstack_first, pstack_second, &b_output);
    assert_true(stack_size(pstack_first) == 10);
    assert_true(stack_size(pstack_second) == 4);
    assert_false(b_output);
    stack_destroy(pstack_first);
    stack_destroy(pstack_second);
}

/*
 * test _type_destroy_stack
 */
UT_CASE_DEFINATION(_type_destroy_stack)
void test__type_destroy_stack__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_stack(NULL, &b_output));
}

void test__type_destroy_stack__null_output(void** state)
{
    stack_t* pstack_input = create_stack(int);
    if (pstack_input == NULL) {
        assert_true(false);
        return;
    }
    stack_init(pstack_input);
    expect_assert_failure(_type_destroy_stack(pstack_input, NULL));
    stack_destroy(pstack_input);
}

void test__type_destroy_stack__ok(void** state)
{
    bool_t b_output = false;
    int i = 0;
    stack_t* pstack_input = create_stack(int);
    if (pstack_input == NULL) {
        assert_true(false);
        return;
    }
    stack_init(pstack_input);
    for (i = 0; i < 10; ++i) {
        stack_push(pstack_input, i);
    }
    _type_destroy_stack(pstack_input, &b_output);
    assert_true(b_output);
    free(pstack_input);
}

/*
 * test _type_init_queue
 */
UT_CASE_DEFINATION(_type_init_queue)
void test__type_init_queue__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_queue(NULL, &b_output));
}

void test__type_init_queue__null_output(void** state)
{
    queue_t* pque_input = malloc(sizeof(queue_t));
    if (pque_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_queue(pque_input, NULL));
    free(pque_input);
}

void test__type_init_queue__ok(void** state)
{
    queue_t* pque_input = malloc(sizeof(queue_t));
    const char* b_output = "int";
    if (pque_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_queue(pque_input, (void*)b_output);
    //assert_true(_queue_is_inited(pque_input));
    queue_destroy(pque_input);
}

/*
 * test _type_copy_queue
 */
UT_CASE_DEFINATION(_type_copy_queue)
void test__type_copy_queue__null_first(void** state)
{
    queue_t* pque_second = NULL;
    bool_t b_output = false;
    
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    queue_init(pque_second);
    expect_assert_failure(_type_copy_queue(NULL, pque_second, &b_output));
    queue_destroy(pque_second);
}

void test__type_copy_queue__null_second(void** state)
{
    queue_t* pque_first = NULL;
    bool_t b_output = false;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(pque_first);
        return;
    }
    queue_init(pque_first);
    expect_assert_failure(_type_copy_queue(pque_first, NULL, &b_output));
    queue_destroy(pque_first);
}

void test__type_copy_queue__null_output(void** state)
{
    queue_t* pque_first = NULL;
    queue_t* pque_second = NULL;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        queue_destroy(pque_first);
        return;
    }
    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(_type_copy_queue(pque_first, pque_second, NULL));
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test__type_copy_queue__ok(void** state)
{
    queue_t* pque_first = NULL;
    queue_t* pque_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        queue_destroy(pque_first);
        return;
    }
    queue_init(pque_first);
    queue_init(pque_second);
    for (i = 0; i < 10; ++i) {
        queue_push(pque_second, i);
    }
    _type_copy_queue(pque_first, pque_second, &b_output);
    assert_true(queue_size(pque_first) == 10);
    assert_true(queue_size(pque_second) == 10);
    assert_true(queue_equal(pque_first, pque_second));
    assert_true(b_output);
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test _type_less_queue
 */
UT_CASE_DEFINATION(_type_less_queue)
void test__type_less_queue__null_first(void** state)
{
    queue_t* pque_second = NULL;
    bool_t b_output = false;
    
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    queue_init(pque_second);
    expect_assert_failure(_type_less_queue(NULL, pque_second, &b_output));
    queue_destroy(pque_second);
}

void test__type_less_queue__null_second(void** state)
{
    queue_t* pque_first = NULL;
    bool_t b_output = false;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(pque_first);
        return;
    }
    queue_init(pque_first);
    expect_assert_failure(_type_less_queue(pque_first, NULL, &b_output));
    queue_destroy(pque_first);
}

void test__type_less_queue__null_output(void** state)
{
    queue_t* pque_first = NULL;
    queue_t* pque_second = NULL;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        queue_destroy(pque_first);
        return;
    }
    queue_init(pque_first);
    queue_init(pque_second);
    expect_assert_failure(_type_less_queue(pque_first, pque_second, NULL));
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test__type_less_queue__less(void** state)
{
    queue_t* pque_first = NULL;
    queue_t* pque_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        queue_destroy(pque_first);
        return;
    }
    queue_init(pque_first);
    queue_init(pque_second);
    for (i = 0; i < 10; ++i) {
        queue_push(pque_second, i);
    }
    _type_less_queue(pque_first, pque_second, &b_output);
    assert_true(queue_empty(pque_first));
    assert_true(queue_size(pque_second) == 10);
    assert_true(b_output);
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test__type_less_queue__equal(void** state)
{
    queue_t* pque_first = NULL;
    queue_t* pque_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        queue_destroy(pque_first);
        return;
    }
    queue_init(pque_first);
    for (i = 0; i < 10; ++i) {
        queue_push(pque_first, i);
    }
    queue_init(pque_second);
    for (i = 0; i < 10; ++i) {
        queue_push(pque_second, i);
    }
    _type_less_queue(pque_first, pque_second, &b_output);
    assert_true(queue_size(pque_first) == 10);
    assert_true(queue_size(pque_second) == 10);
    assert_true(queue_equal(pque_first, pque_second));
    assert_false(b_output);
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

void test__type_less_queue__greater(void** state)
{
    queue_t* pque_first = NULL;
    queue_t* pque_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pque_first = create_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pque_second = create_queue(int)) == NULL) {
        assert_true(false);
        queue_destroy(pque_first);
        return;
    }
    queue_init(pque_first);
    for (i = 0; i < 10; ++i) {
        queue_push(pque_first, i);
    }
    queue_init(pque_second);
    for (i = 0; i < 4; ++i) {
        queue_push(pque_second, i);
    }
    _type_less_queue(pque_first, pque_second, &b_output);
    assert_true(queue_size(pque_first) == 10);
    assert_true(queue_size(pque_second) == 4);
    assert_false(b_output);
    queue_destroy(pque_first);
    queue_destroy(pque_second);
}

/*
 * test _type_destroy_queue
 */
UT_CASE_DEFINATION(_type_destroy_queue)
void test__type_destroy_queue__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_queue(NULL, &b_output));
}

void test__type_destroy_queue__null_output(void** state)
{
    queue_t* pque_input = create_queue(int);
    if (pque_input == NULL) {
        assert_true(false);
        return;
    }
    queue_init(pque_input);
    expect_assert_failure(_type_destroy_queue(pque_input, NULL));
    queue_destroy(pque_input);
}

void test__type_destroy_queue__ok(void** state)
{
    bool_t b_output = false;
    int i = 0;
    queue_t* pque_input = create_queue(int);
    if (pque_input == NULL) {
        assert_true(false);
        return;
    }
    queue_init(pque_input);
    for (i = 0; i < 10; ++i) {
        queue_push(pque_input, i);
    }
    _type_destroy_queue(pque_input, &b_output);
    assert_true(b_output);
    free(pque_input);
}

/*
 * test _type_init_priority_queue
 */
UT_CASE_DEFINATION(_type_init_priority_queue)
void test__type_init_priority_queue__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_priority_queue(NULL, &b_output));
}

void test__type_init_priority_queue__null_output(void** state)
{
    priority_queue_t* ppq_input = malloc(sizeof(priority_queue_t));
    if (ppq_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_priority_queue(ppq_input, NULL));
    free(ppq_input);
}

void test__type_init_priority_queue__ok(void** state)
{
    priority_queue_t* ppq_input = malloc(sizeof(priority_queue_t));
    const char* b_output = "int";
    if (ppq_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_priority_queue(ppq_input, (void*)b_output);
    //assert_true(_priority_queue_is_inited(ppq_input));
    priority_queue_destroy(ppq_input);
}

/*
 * test _type_copy_priority_queue
 */
UT_CASE_DEFINATION(_type_copy_priority_queue)
void test__type_copy_priority_queue__null_first(void** state)
{
    priority_queue_t* ppq_second = NULL;
    bool_t b_output = false;
    
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    priority_queue_init(ppq_second);
    expect_assert_failure(_type_copy_priority_queue(NULL, ppq_second, &b_output));
    priority_queue_destroy(ppq_second);
}

void test__type_copy_priority_queue__null_second(void** state)
{
    priority_queue_t* ppq_first = NULL;
    bool_t b_output = false;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    expect_assert_failure(_type_copy_priority_queue(ppq_first, NULL, &b_output));
    priority_queue_destroy(ppq_first);
}

void test__type_copy_priority_queue__null_output(void** state)
{
    priority_queue_t* ppq_first = NULL;
    priority_queue_t* ppq_second = NULL;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        priority_queue_destroy(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    priority_queue_init(ppq_second);
    expect_assert_failure(_type_copy_priority_queue(ppq_first, ppq_second, NULL));
    priority_queue_destroy(ppq_first);
    priority_queue_destroy(ppq_second);
}

void test__type_copy_priority_queue__ok(void** state)
{
    priority_queue_t* ppq_first = NULL;
    priority_queue_t* ppq_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        priority_queue_destroy(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    priority_queue_init(ppq_second);
    for (i = 0; i < 10; ++i) {
        priority_queue_push(ppq_second, i);
    }
    _type_copy_priority_queue(ppq_first, ppq_second, &b_output);
    assert_true(priority_queue_size(ppq_first) == 10);
    assert_true(priority_queue_size(ppq_second) == 10);
    assert_true(b_output);
    priority_queue_destroy(ppq_first);
    priority_queue_destroy(ppq_second);
}

/*
 * test _type_less_priority_queue
 */
UT_CASE_DEFINATION(_type_less_priority_queue)
void test__type_less_priority_queue__null_first(void** state)
{
    priority_queue_t* ppq_second = NULL;
    bool_t b_output = false;
    
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    priority_queue_init(ppq_second);
    expect_assert_failure(_type_less_priority_queue(NULL, ppq_second, &b_output));
    priority_queue_destroy(ppq_second);
}

void test__type_less_priority_queue__null_second(void** state)
{
    priority_queue_t* ppq_first = NULL;
    bool_t b_output = false;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    expect_assert_failure(_type_less_priority_queue(ppq_first, NULL, &b_output));
    priority_queue_destroy(ppq_first);
}

void test__type_less_priority_queue__null_output(void** state)
{
    priority_queue_t* ppq_first = NULL;
    priority_queue_t* ppq_second = NULL;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        priority_queue_destroy(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    priority_queue_init(ppq_second);
    expect_assert_failure(_type_less_priority_queue(ppq_first, ppq_second, NULL));
    priority_queue_destroy(ppq_first);
    priority_queue_destroy(ppq_second);
}

void test__type_less_priority_queue__less(void** state)
{
    priority_queue_t* ppq_first = NULL;
    priority_queue_t* ppq_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        priority_queue_destroy(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    priority_queue_init(ppq_second);
    for (i = 0; i < 10; ++i) {
        priority_queue_push(ppq_second, i);
    }
    _type_less_priority_queue(ppq_first, ppq_second, &b_output);
    assert_true(priority_queue_empty(ppq_first));
    assert_true(priority_queue_size(ppq_second) == 10);
    assert_true(b_output);
    priority_queue_destroy(ppq_first);
    priority_queue_destroy(ppq_second);
}

void test__type_less_priority_queue__equal(void** state)
{
    priority_queue_t* ppq_first = NULL;
    priority_queue_t* ppq_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        priority_queue_destroy(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    for (i = 0; i < 10; ++i) {
        priority_queue_push(ppq_first, i);
    }
    priority_queue_init(ppq_second);
    for (i = 0; i < 10; ++i) {
        priority_queue_push(ppq_second, i);
    }
    _type_less_priority_queue(ppq_first, ppq_second, &b_output);
    assert_true(priority_queue_size(ppq_first) == 10);
    assert_true(priority_queue_size(ppq_second) == 10);
    assert_false(b_output);
    priority_queue_destroy(ppq_first);
    priority_queue_destroy(ppq_second);
}

void test__type_less_priority_queue__greater(void** state)
{
    priority_queue_t* ppq_first = NULL;
    priority_queue_t* ppq_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppq_first = create_priority_queue(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppq_second = create_priority_queue(int)) == NULL) {
        assert_true(false);
        priority_queue_destroy(ppq_first);
        return;
    }
    priority_queue_init(ppq_first);
    for (i = 0; i < 10; ++i) {
        priority_queue_push(ppq_first, i);
    }
    priority_queue_init(ppq_second);
    for (i = 0; i < 4; ++i) {
        priority_queue_push(ppq_second, i);
    }
    _type_less_priority_queue(ppq_first, ppq_second, &b_output);
    assert_true(priority_queue_size(ppq_first) == 10);
    assert_true(priority_queue_size(ppq_second) == 4);
    assert_false(b_output);
    priority_queue_destroy(ppq_first);
    priority_queue_destroy(ppq_second);
}

/*
 * test _type_destroy_priority_queue
 */
UT_CASE_DEFINATION(_type_destroy_priority_queue)
void test__type_destroy_priority_queue__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_priority_queue(NULL, &b_output));
}

void test__type_destroy_priority_queue__null_output(void** state)
{
    priority_queue_t* ppq_input = create_priority_queue(int);
    if (ppq_input == NULL) {
        assert_true(false);
        return;
    }
    priority_queue_init(ppq_input);
    expect_assert_failure(_type_destroy_priority_queue(ppq_input, NULL));
    priority_queue_destroy(ppq_input);
}

void test__type_destroy_priority_queue__ok(void** state)
{
    bool_t b_output = false;
    int i = 0;
    priority_queue_t* ppq_input = create_priority_queue(int);
    if (ppq_input == NULL) {
        assert_true(false);
        return;
    }
    priority_queue_init(ppq_input);
    for (i = 0; i < 10; ++i) {
        priority_queue_push(ppq_input, i);
    }
    _type_destroy_priority_queue(ppq_input, &b_output);
    assert_true(b_output);
    free(ppq_input);
}

/*
 * test _type_init_set
 */
UT_CASE_DEFINATION(_type_init_set)
void test__type_init_set__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_set(NULL, &b_output));
}

void test__type_init_set__null_output(void** state)
{
    set_t* pset_input = malloc(sizeof(set_t));
    if (pset_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_set(pset_input, NULL));
    free(pset_input);
}

void test__type_init_set__ok(void** state)
{
    set_t* pset_input = malloc(sizeof(set_t));
    const char* b_output = "int";
    if (pset_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_set(pset_input, (void*)b_output);
    //assert_true(_set_is_inited(pset_input));
    set_destroy(pset_input);
}

/*
 * test _type_copy_set
 */
UT_CASE_DEFINATION(_type_copy_set)
void test__type_copy_set__null_first(void** state)
{
    set_t* pset_second = NULL;
    bool_t b_output = false;
    
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    set_init(pset_second);
    expect_assert_failure(_type_copy_set(NULL, pset_second, &b_output));
    set_destroy(pset_second);
}

void test__type_copy_set__null_second(void** state)
{
    set_t* pset_first = NULL;
    bool_t b_output = false;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(pset_first);
        return;
    }
    set_init(pset_first);
    expect_assert_failure(_type_copy_set(pset_first, NULL, &b_output));
    set_destroy(pset_first);
}

void test__type_copy_set__null_output(void** state)
{
    set_t* pset_first = NULL;
    set_t* pset_second = NULL;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        set_destroy(pset_first);
        return;
    }
    set_init(pset_first);
    set_init(pset_second);
    expect_assert_failure(_type_copy_set(pset_first, pset_second, NULL));
    set_destroy(pset_first);
    set_destroy(pset_second);
}

void test__type_copy_set__ok(void** state)
{
    set_t* pset_first = NULL;
    set_t* pset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        set_destroy(pset_first);
        return;
    }
    set_init(pset_first);
    set_init(pset_second);
    for (i = 0; i < 10; ++i) {
        set_insert(pset_second, i);
    }
    _type_copy_set(pset_first, pset_second, &b_output);
    assert_true(set_size(pset_first) == 10);
    assert_true(set_size(pset_second) == 10);
    assert_true(b_output);
    set_destroy(pset_first);
    set_destroy(pset_second);
}

/*
 * test _type_less_set
 */
UT_CASE_DEFINATION(_type_less_set)
void test__type_less_set__null_first(void** state)
{
    set_t* pset_second = NULL;
    bool_t b_output = false;
    
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    set_init(pset_second);
    expect_assert_failure(_type_less_set(NULL, pset_second, &b_output));
    set_destroy(pset_second);
}

void test__type_less_set__null_second(void** state)
{
    set_t* pset_first = NULL;
    bool_t b_output = false;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(pset_first);
        return;
    }
    set_init(pset_first);
    expect_assert_failure(_type_less_set(pset_first, NULL, &b_output));
    set_destroy(pset_first);
}

void test__type_less_set__null_output(void** state)
{
    set_t* pset_first = NULL;
    set_t* pset_second = NULL;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        set_destroy(pset_first);
        return;
    }
    set_init(pset_first);
    set_init(pset_second);
    expect_assert_failure(_type_less_set(pset_first, pset_second, NULL));
    set_destroy(pset_first);
    set_destroy(pset_second);
}

void test__type_less_set__less(void** state)
{
    set_t* pset_first = NULL;
    set_t* pset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        set_destroy(pset_first);
        return;
    }
    set_init(pset_first);
    set_init(pset_second);
    for (i = 0; i < 10; ++i) {
        set_insert(pset_second, i);
    }
    _type_less_set(pset_first, pset_second, &b_output);
    assert_true(set_empty(pset_first));
    assert_true(set_size(pset_second) == 10);
    assert_true(b_output);
    set_destroy(pset_first);
    set_destroy(pset_second);
}

void test__type_less_set__equal(void** state)
{
    set_t* pset_first = NULL;
    set_t* pset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        set_destroy(pset_first);
        return;
    }
    set_init(pset_first);
    for (i = 0; i < 10; ++i) {
        set_insert(pset_first, i);
    }
    set_init(pset_second);
    for (i = 0; i < 10; ++i) {
        set_insert(pset_second, i);
    }
    _type_less_set(pset_first, pset_second, &b_output);
    assert_true(set_size(pset_first) == 10);
    assert_true(set_size(pset_second) == 10);
    assert_false(b_output);
    set_destroy(pset_first);
    set_destroy(pset_second);
}

void test__type_less_set__greater(void** state)
{
    set_t* pset_first = NULL;
    set_t* pset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pset_first = create_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pset_second = create_set(int)) == NULL) {
        assert_true(false);
        set_destroy(pset_first);
        return;
    }
    set_init(pset_first);
    for (i = 0; i < 10; ++i) {
        set_insert(pset_first, i);
    }
    set_init(pset_second);
    for (i = 0; i < 4; ++i) {
        set_insert(pset_second, i);
    }
    _type_less_set(pset_first, pset_second, &b_output);
    assert_true(set_size(pset_first) == 10);
    assert_true(set_size(pset_second) == 4);
    assert_false(b_output);
    set_destroy(pset_first);
    set_destroy(pset_second);
}

/*
 * test _type_destroy_set
 */
UT_CASE_DEFINATION(_type_destroy_set)
void test__type_destroy_set__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_set(NULL, &b_output));
}

void test__type_destroy_set__null_output(void** state)
{
    set_t* pset_input = create_set(int);
    if (pset_input == NULL) {
        assert_true(false);
        return;
    }
    set_init(pset_input);
    expect_assert_failure(_type_destroy_set(pset_input, NULL));
    set_destroy(pset_input);
}

void test__type_destroy_set__ok(void** state)
{
    bool_t b_output = false;
    int i = 0;
    set_t* pset_input = create_set(int);
    if (pset_input == NULL) {
        assert_true(false);
        return;
    }
    set_init(pset_input);
    for (i = 0; i < 10; ++i) {
        set_insert(pset_input, i);
    }
    _type_destroy_set(pset_input, &b_output);
    assert_true(b_output);
    free(pset_input);
}

/*
 * test _type_init_multiset
 */
UT_CASE_DEFINATION(_type_init_multiset)
void test__type_init_multiset__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_multiset(NULL, &b_output));
}

void test__type_init_multiset__null_output(void** state)
{
    multiset_t* pmset_input = malloc(sizeof(multiset_t));
    if (pmset_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_multiset(pmset_input, NULL));
    free(pmset_input);
}

void test__type_init_multiset__ok(void** state)
{
    multiset_t* pmset_input = malloc(sizeof(multiset_t));
    const char* b_output = "int";
    if (pmset_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_multiset(pmset_input, (void*)b_output);
    //assert_true(_multiset_is_inited(pmset_input));
    multiset_destroy(pmset_input);
}

/*
 * test _type_copy_multiset
 */
UT_CASE_DEFINATION(_type_copy_multiset)
void test__type_copy_multiset__null_first(void** state)
{
    multiset_t* pmset_second = NULL;
    bool_t b_output = false;
    
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    multiset_init(pmset_second);
    expect_assert_failure(_type_copy_multiset(NULL, pmset_second, &b_output));
    multiset_destroy(pmset_second);
}

void test__type_copy_multiset__null_second(void** state)
{
    multiset_t* pmset_first = NULL;
    bool_t b_output = false;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    expect_assert_failure(_type_copy_multiset(pmset_first, NULL, &b_output));
    multiset_destroy(pmset_first);
}

void test__type_copy_multiset__null_output(void** state)
{
    multiset_t* pmset_first = NULL;
    multiset_t* pmset_second = NULL;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        multiset_destroy(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    multiset_init(pmset_second);
    expect_assert_failure(_type_copy_multiset(pmset_first, pmset_second, NULL));
    multiset_destroy(pmset_first);
    multiset_destroy(pmset_second);
}

void test__type_copy_multiset__ok(void** state)
{
    multiset_t* pmset_first = NULL;
    multiset_t* pmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        multiset_destroy(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    multiset_init(pmset_second);
    for (i = 0; i < 10; ++i) {
        multiset_insert(pmset_second, i);
    }
    _type_copy_multiset(pmset_first, pmset_second, &b_output);
    assert_true(multiset_size(pmset_first) == 10);
    assert_true(multiset_size(pmset_second) == 10);
    assert_true(b_output);
    multiset_destroy(pmset_first);
    multiset_destroy(pmset_second);
}

/*
 * test _type_less_multiset
 */
UT_CASE_DEFINATION(_type_less_multiset)
void test__type_less_multiset__null_first(void** state)
{
    multiset_t* pmset_second = NULL;
    bool_t b_output = false;
    
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    multiset_init(pmset_second);
    expect_assert_failure(_type_less_multiset(NULL, pmset_second, &b_output));
    multiset_destroy(pmset_second);
}

void test__type_less_multiset__null_second(void** state)
{
    multiset_t* pmset_first = NULL;
    bool_t b_output = false;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    expect_assert_failure(_type_less_multiset(pmset_first, NULL, &b_output));
    multiset_destroy(pmset_first);
}

void test__type_less_multiset__null_output(void** state)
{
    multiset_t* pmset_first = NULL;
    multiset_t* pmset_second = NULL;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        multiset_destroy(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    multiset_init(pmset_second);
    expect_assert_failure(_type_less_multiset(pmset_first, pmset_second, NULL));
    multiset_destroy(pmset_first);
    multiset_destroy(pmset_second);
}

void test__type_less_multiset__less(void** state)
{
    multiset_t* pmset_first = NULL;
    multiset_t* pmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        multiset_destroy(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    multiset_init(pmset_second);
    for (i = 0; i < 10; ++i) {
        multiset_insert(pmset_second, i);
    }
    _type_less_multiset(pmset_first, pmset_second, &b_output);
    assert_true(multiset_empty(pmset_first));
    assert_true(multiset_size(pmset_second) == 10);
    assert_true(b_output);
    multiset_destroy(pmset_first);
    multiset_destroy(pmset_second);
}

void test__type_less_multiset__equal(void** state)
{
    multiset_t* pmset_first = NULL;
    multiset_t* pmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        multiset_destroy(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    for (i = 0; i < 10; ++i) {
        multiset_insert(pmset_first, i);
    }
    multiset_init(pmset_second);
    for (i = 0; i < 10; ++i) {
        multiset_insert(pmset_second, i);
    }
    _type_less_multiset(pmset_first, pmset_second, &b_output);
    assert_true(multiset_size(pmset_first) == 10);
    assert_true(multiset_size(pmset_second) == 10);
    assert_false(b_output);
    multiset_destroy(pmset_first);
    multiset_destroy(pmset_second);
}

void test__type_less_multiset__greater(void** state)
{
    multiset_t* pmset_first = NULL;
    multiset_t* pmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((pmset_first = create_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmset_second = create_multiset(int)) == NULL) {
        assert_true(false);
        multiset_destroy(pmset_first);
        return;
    }
    multiset_init(pmset_first);
    for (i = 0; i < 10; ++i) {
        multiset_insert(pmset_first, i);
    }
    multiset_init(pmset_second);
    for (i = 0; i < 4; ++i) {
        multiset_insert(pmset_second, i);
    }
    _type_less_multiset(pmset_first, pmset_second, &b_output);
    assert_true(multiset_size(pmset_first) == 10);
    assert_true(multiset_size(pmset_second) == 4);
    assert_false(b_output);
    multiset_destroy(pmset_first);
    multiset_destroy(pmset_second);
}

/*
 * test _type_destroy_multiset
 */
UT_CASE_DEFINATION(_type_destroy_multiset)
void test__type_destroy_multiset__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_multiset(NULL, &b_output));
}

void test__type_destroy_multiset__null_output(void** state)
{
    multiset_t* pmset_input = create_multiset(int);
    if (pmset_input == NULL) {
        assert_true(false);
        return;
    }
    multiset_init(pmset_input);
    expect_assert_failure(_type_destroy_multiset(pmset_input, NULL));
    multiset_destroy(pmset_input);
}

void test__type_destroy_multiset__ok(void** state)
{
    bool_t b_output = false;
    int i = 0;
    multiset_t* pmset_input = create_multiset(int);
    if (pmset_input == NULL) {
        assert_true(false);
        return;
    }
    multiset_init(pmset_input);
    for (i = 0; i < 10; ++i) {
        multiset_insert(pmset_input, i);
    }
    _type_destroy_multiset(pmset_input, &b_output);
    assert_true(b_output);
    free(pmset_input);
}

/*
 * test _type_init_map
 */
UT_CASE_DEFINATION(_type_init_map)
void test__type_init_map__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_map(NULL, &b_output));
}

void test__type_init_map__null_output(void** state)
{
    map_t* pmap_input = malloc(sizeof(map_t));
    if (pmap_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_map(pmap_input, NULL));
    free(pmap_input);
}

void test__type_init_map__ok(void** state)
{
    map_t* pmap_input = malloc(sizeof(map_t));
    const char* b_output = "int, int";
    if (pmap_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_map(pmap_input, (void*)b_output);
    //assert_true(_map_is_inited(pmap_input));
    map_destroy(pmap_input);
}

/*
 * test _type_copy_map
 */
UT_CASE_DEFINATION(_type_copy_map)
void test__type_copy_map__null_first(void** state)
{
    map_t* pmap_second = NULL;
    bool_t b_output = false;
    
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    map_init(pmap_second);
    expect_assert_failure(_type_copy_map(NULL, pmap_second, &b_output));
    map_destroy(pmap_second);
}

void test__type_copy_map__null_second(void** state)
{
    map_t* pmap_first = NULL;
    bool_t b_output = false;
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(pmap_first);
        return;
    }
    map_init(pmap_first);
    expect_assert_failure(_type_copy_map(pmap_first, NULL, &b_output));
    map_destroy(pmap_first);
}

void test__type_copy_map__null_output(void** state)
{
    map_t* pmap_first = NULL;
    map_t* pmap_second = NULL;
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        map_destroy(pmap_first);
        return;
    }
    map_init(pmap_first);
    map_init(pmap_second);
    expect_assert_failure(_type_copy_map(pmap_first, pmap_second, NULL));
    map_destroy(pmap_first);
    map_destroy(pmap_second);
}

void test__type_copy_map__ok(void** state)
{
    map_t* pmap_first = NULL;
    map_t* pmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
    }
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        map_destroy(pmap_first);
        pair_destroy(ppair);
        return;
    }
    map_init(pmap_first);
    map_init(pmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        map_insert(pmap_second, ppair);
    }
    _type_copy_map(pmap_first, pmap_second, &b_output);
    assert_true(map_size(pmap_first) == 10);
    assert_true(map_size(pmap_second) == 10);
    assert_true(b_output);
    map_destroy(pmap_first);
    map_destroy(pmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_less_map
 */
UT_CASE_DEFINATION(_type_less_map)
void test__type_less_map__null_first(void** state)
{
    map_t* pmap_second = NULL;
    bool_t b_output = false;
    
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    map_init(pmap_second);
    expect_assert_failure(_type_less_map(NULL, pmap_second, &b_output));
    map_destroy(pmap_second);
}

void test__type_less_map__null_second(void** state)
{
    map_t* pmap_first = NULL;
    bool_t b_output = false;
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(pmap_first);
        return;
    }
    map_init(pmap_first);
    expect_assert_failure(_type_less_map(pmap_first, NULL, &b_output));
    map_destroy(pmap_first);
}

void test__type_less_map__null_output(void** state)
{
    map_t* pmap_first = NULL;
    map_t* pmap_second = NULL;
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        map_destroy(pmap_first);
        return;
    }
    map_init(pmap_first);
    map_init(pmap_second);
    expect_assert_failure(_type_less_map(pmap_first, pmap_second, NULL));
    map_destroy(pmap_first);
    map_destroy(pmap_second);
}

void test__type_less_map__less(void** state)
{
    map_t* pmap_first = NULL;
    map_t* pmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        map_destroy(pmap_first);
        pair_destroy(ppair);
        return;
    }
    map_init(pmap_first);
    map_init(pmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        map_insert(pmap_second, ppair);
    }
    _type_less_map(pmap_first, pmap_second, &b_output);
    assert_true(map_empty(pmap_first));
    assert_true(map_size(pmap_second) == 10);
    assert_true(b_output);
    map_destroy(pmap_first);
    map_destroy(pmap_second);
    pair_destroy(ppair);
}

void test__type_less_map__equal(void** state)
{
    map_t* pmap_first = NULL;
    map_t* pmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        map_destroy(pmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    map_init(pmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        map_insert(pmap_first, ppair);
    }
    map_init(pmap_second);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        map_insert(pmap_second, ppair);
    }
    _type_less_map(pmap_first, pmap_second, &b_output);
    assert_true(map_size(pmap_first) == 10);
    assert_true(map_size(pmap_second) == 10);
    assert_false(b_output);
    map_destroy(pmap_first);
    map_destroy(pmap_second);
    pair_destroy(ppair);
}

void test__type_less_map__greater(void** state)
{
    map_t* pmap_first = NULL;
    map_t* pmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmap_first = create_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmap_second = create_map(int, int)) == NULL) {
        assert_true(false);
        map_destroy(pmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    map_init(pmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        map_insert(pmap_first, ppair);
    }
    map_init(pmap_second);
    for (i = 0; i < 4; ++i) {
        pair_make(ppair, i, i);
        map_insert(pmap_second, ppair);
    }
    _type_less_map(pmap_first, pmap_second, &b_output);
    assert_true(map_size(pmap_first) == 10);
    assert_true(map_size(pmap_second) == 4);
    assert_false(b_output);
    map_destroy(pmap_first);
    map_destroy(pmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_destroy_map
 */
UT_CASE_DEFINATION(_type_destroy_map)
void test__type_destroy_map__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_map(NULL, &b_output));
}

void test__type_destroy_map__null_output(void** state)
{
    map_t* pmap_input = create_map(int, int);
    if (pmap_input == NULL) {
        assert_true(false);
        return;
    }
    map_init(pmap_input);
    expect_assert_failure(_type_destroy_map(pmap_input, NULL));
    map_destroy(pmap_input);
}

void test__type_destroy_map__ok(void** state)
{
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    map_t* pmap_input = create_map(int, int);
    if (pmap_input == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        map_destroy(pmap_input);
        return;
    }
    pair_init(ppair);
    map_init(pmap_input);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        map_insert(pmap_input, ppair);
    }
    _type_destroy_map(pmap_input, &b_output);
    assert_true(b_output);
    free(pmap_input);
    pair_destroy(ppair);
}

/*
 * test _type_init_multimap
 */
UT_CASE_DEFINATION(_type_init_multimap)
void test__type_init_multimap__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_multimap(NULL, &b_output));
}

void test__type_init_multimap__null_output(void** state)
{
    multimap_t* pmmap_input = malloc(sizeof(multimap_t));
    if (pmmap_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_multimap(pmmap_input, NULL));
    free(pmmap_input);
}

void test__type_init_multimap__ok(void** state)
{
    multimap_t* pmmap_input = malloc(sizeof(multimap_t));
    const char* b_output = "int, int";
    if (pmmap_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_multimap(pmmap_input, (void*)b_output);
    //assert_true(_multimap_is_inited(pmmap_input));
    multimap_destroy(pmmap_input);
}

/*
 * test _type_copy_multimap
 */
UT_CASE_DEFINATION(_type_copy_multimap)
void test__type_copy_multimap__null_first(void** state)
{
    multimap_t* pmmap_second = NULL;
    bool_t b_output = false;
    
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    multimap_init(pmmap_second);
    expect_assert_failure(_type_copy_multimap(NULL, pmmap_second, &b_output));
    multimap_destroy(pmmap_second);
}

void test__type_copy_multimap__null_second(void** state)
{
    multimap_t* pmmap_first = NULL;
    bool_t b_output = false;
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(pmmap_first);
        return;
    }
    multimap_init(pmmap_first);
    expect_assert_failure(_type_copy_multimap(pmmap_first, NULL, &b_output));
    multimap_destroy(pmmap_first);
}

void test__type_copy_multimap__null_output(void** state)
{
    multimap_t* pmmap_first = NULL;
    multimap_t* pmmap_second = NULL;
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        multimap_destroy(pmmap_first);
        return;
    }
    multimap_init(pmmap_first);
    multimap_init(pmmap_second);
    expect_assert_failure(_type_copy_multimap(pmmap_first, pmmap_second, NULL));
    multimap_destroy(pmmap_first);
    multimap_destroy(pmmap_second);
}

void test__type_copy_multimap__ok(void** state)
{
    multimap_t* pmmap_first = NULL;
    multimap_t* pmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
    }
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        multimap_destroy(pmmap_first);
        pair_destroy(ppair);
        return;
    }
    multimap_init(pmmap_first);
    multimap_init(pmmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        multimap_insert(pmmap_second, ppair);
    }
    _type_copy_multimap(pmmap_first, pmmap_second, &b_output);
    assert_true(multimap_size(pmmap_first) == 10);
    assert_true(multimap_size(pmmap_second) == 10);
    assert_true(b_output);
    multimap_destroy(pmmap_first);
    multimap_destroy(pmmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_less_multimap
 */
UT_CASE_DEFINATION(_type_less_multimap)
void test__type_less_multimap__null_first(void** state)
{
    multimap_t* pmmap_second = NULL;
    bool_t b_output = false;
    
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    multimap_init(pmmap_second);
    expect_assert_failure(_type_less_multimap(NULL, pmmap_second, &b_output));
    multimap_destroy(pmmap_second);
}

void test__type_less_multimap__null_second(void** state)
{
    multimap_t* pmmap_first = NULL;
    bool_t b_output = false;
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(pmmap_first);
        return;
    }
    multimap_init(pmmap_first);
    expect_assert_failure(_type_less_multimap(pmmap_first, NULL, &b_output));
    multimap_destroy(pmmap_first);
}

void test__type_less_multimap__null_output(void** state)
{
    multimap_t* pmmap_first = NULL;
    multimap_t* pmmap_second = NULL;
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        multimap_destroy(pmmap_first);
        return;
    }
    multimap_init(pmmap_first);
    multimap_init(pmmap_second);
    expect_assert_failure(_type_less_multimap(pmmap_first, pmmap_second, NULL));
    multimap_destroy(pmmap_first);
    multimap_destroy(pmmap_second);
}

void test__type_less_multimap__less(void** state)
{
    multimap_t* pmmap_first = NULL;
    multimap_t* pmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        multimap_destroy(pmmap_first);
        pair_destroy(ppair);
        return;
    }
    multimap_init(pmmap_first);
    multimap_init(pmmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        multimap_insert(pmmap_second, ppair);
    }
    _type_less_multimap(pmmap_first, pmmap_second, &b_output);
    assert_true(multimap_empty(pmmap_first));
    assert_true(multimap_size(pmmap_second) == 10);
    assert_true(b_output);
    multimap_destroy(pmmap_first);
    multimap_destroy(pmmap_second);
    pair_destroy(ppair);
}

void test__type_less_multimap__equal(void** state)
{
    multimap_t* pmmap_first = NULL;
    multimap_t* pmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        multimap_destroy(pmmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    multimap_init(pmmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        multimap_insert(pmmap_first, ppair);
    }
    multimap_init(pmmap_second);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        multimap_insert(pmmap_second, ppair);
    }
    _type_less_multimap(pmmap_first, pmmap_second, &b_output);
    assert_true(multimap_size(pmmap_first) == 10);
    assert_true(multimap_size(pmmap_second) == 10);
    assert_false(b_output);
    multimap_destroy(pmmap_first);
    multimap_destroy(pmmap_second);
    pair_destroy(ppair);
}

void test__type_less_multimap__greater(void** state)
{
    multimap_t* pmmap_first = NULL;
    multimap_t* pmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pmmap_first = create_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((pmmap_second = create_multimap(int, int)) == NULL) {
        assert_true(false);
        multimap_destroy(pmmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    multimap_init(pmmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        multimap_insert(pmmap_first, ppair);
    }
    multimap_init(pmmap_second);
    for (i = 0; i < 4; ++i) {
        pair_make(ppair, i, i);
        multimap_insert(pmmap_second, ppair);
    }
    _type_less_multimap(pmmap_first, pmmap_second, &b_output);
    assert_true(multimap_size(pmmap_first) == 10);
    assert_true(multimap_size(pmmap_second) == 4);
    assert_false(b_output);
    multimap_destroy(pmmap_first);
    multimap_destroy(pmmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_destroy_multimap
 */
UT_CASE_DEFINATION(_type_destroy_multimap)
void test__type_destroy_multimap__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_multimap(NULL, &b_output));
}

void test__type_destroy_multimap__null_output(void** state)
{
    multimap_t* pmmap_input = create_multimap(int, int);
    if (pmmap_input == NULL) {
        assert_true(false);
        return;
    }
    multimap_init(pmmap_input);
    expect_assert_failure(_type_destroy_multimap(pmmap_input, NULL));
    multimap_destroy(pmmap_input);
}

void test__type_destroy_multimap__ok(void** state)
{
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    multimap_t* pmmap_input = create_multimap(int, int);
    if (pmmap_input == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        multimap_destroy(pmmap_input);
        return;
    }
    pair_init(ppair);
    multimap_init(pmmap_input);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        multimap_insert(pmmap_input, ppair);
    }
    _type_destroy_multimap(pmmap_input, &b_output);
    assert_true(b_output);
    free(pmmap_input);
    pair_destroy(ppair);
}

/*
 * test _type_init_hash_set
 */
UT_CASE_DEFINATION(_type_init_hash_set)
void test__type_init_hash_set__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_hash_set(NULL, &b_output));
}

void test__type_init_hash_set__null_output(void** state)
{
    hash_set_t* phset_input = malloc(sizeof(hash_set_t));
    if (phset_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_hash_set(phset_input, NULL));
    free(phset_input);
}

void test__type_init_hash_set__ok(void** state)
{
    hash_set_t* phset_input = malloc(sizeof(hash_set_t));
    const char* b_output = "int";
    if (phset_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_hash_set(phset_input, (void*)b_output);
    //assert_true(_hash_set_is_inited(phset_input));
    hash_set_destroy(phset_input);
}

/*
 * test _type_copy_hash_set
 */
UT_CASE_DEFINATION(_type_copy_hash_set)
void test__type_copy_hash_set__null_first(void** state)
{
    hash_set_t* phset_second = NULL;
    bool_t b_output = false;
    
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_set_init(phset_second);
    expect_assert_failure(_type_copy_hash_set(NULL, phset_second, &b_output));
    hash_set_destroy(phset_second);
}

void test__type_copy_hash_set__null_second(void** state)
{
    hash_set_t* phset_first = NULL;
    bool_t b_output = false;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(phset_first);
        return;
    }
    hash_set_init(phset_first);
    expect_assert_failure(_type_copy_hash_set(phset_first, NULL, &b_output));
    hash_set_destroy(phset_first);
}

void test__type_copy_hash_set__null_output(void** state)
{
    hash_set_t* phset_first = NULL;
    hash_set_t* phset_second = NULL;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        hash_set_destroy(phset_first);
        return;
    }
    hash_set_init(phset_first);
    hash_set_init(phset_second);
    expect_assert_failure(_type_copy_hash_set(phset_first, phset_second, NULL));
    hash_set_destroy(phset_first);
    hash_set_destroy(phset_second);
}

void test__type_copy_hash_set__ok(void** state)
{
    hash_set_t* phset_first = NULL;
    hash_set_t* phset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        hash_set_destroy(phset_first);
        return;
    }
    hash_set_init(phset_first);
    hash_set_init(phset_second);
    for (i = 0; i < 10; ++i) {
        hash_set_insert(phset_second, i);
    }
    _type_copy_hash_set(phset_first, phset_second, &b_output);
    assert_true(hash_set_size(phset_first) == 10);
    assert_true(hash_set_size(phset_second) == 10);
    assert_true(b_output);
    hash_set_destroy(phset_first);
    hash_set_destroy(phset_second);
}

/*
 * test _type_less_hash_set
 */
UT_CASE_DEFINATION(_type_less_hash_set)
void test__type_less_hash_set__null_first(void** state)
{
    hash_set_t* phset_second = NULL;
    bool_t b_output = false;
    
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_set_init(phset_second);
    expect_assert_failure(_type_less_hash_set(NULL, phset_second, &b_output));
    hash_set_destroy(phset_second);
}

void test__type_less_hash_set__null_second(void** state)
{
    hash_set_t* phset_first = NULL;
    bool_t b_output = false;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(phset_first);
        return;
    }
    hash_set_init(phset_first);
    expect_assert_failure(_type_less_hash_set(phset_first, NULL, &b_output));
    hash_set_destroy(phset_first);
}

void test__type_less_hash_set__null_output(void** state)
{
    hash_set_t* phset_first = NULL;
    hash_set_t* phset_second = NULL;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        hash_set_destroy(phset_first);
        return;
    }
    hash_set_init(phset_first);
    hash_set_init(phset_second);
    expect_assert_failure(_type_less_hash_set(phset_first, phset_second, NULL));
    hash_set_destroy(phset_first);
    hash_set_destroy(phset_second);
}

void test__type_less_hash_set__less(void** state)
{
    hash_set_t* phset_first = NULL;
    hash_set_t* phset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        hash_set_destroy(phset_first);
        return;
    }
    hash_set_init(phset_first);
    hash_set_init(phset_second);
    for (i = 0; i < 10; ++i) {
        hash_set_insert(phset_second, i);
    }
    _type_less_hash_set(phset_first, phset_second, &b_output);
    assert_true(hash_set_empty(phset_first));
    assert_true(hash_set_size(phset_second) == 10);
    assert_true(b_output);
    hash_set_destroy(phset_first);
    hash_set_destroy(phset_second);
}

void test__type_less_hash_set__equal(void** state)
{
    hash_set_t* phset_first = NULL;
    hash_set_t* phset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        hash_set_destroy(phset_first);
        return;
    }
    hash_set_init(phset_first);
    for (i = 0; i < 10; ++i) {
        hash_set_insert(phset_first, i);
    }
    hash_set_init(phset_second);
    for (i = 0; i < 10; ++i) {
        hash_set_insert(phset_second, i);
    }
    _type_less_hash_set(phset_first, phset_second, &b_output);
    assert_true(hash_set_size(phset_first) == 10);
    assert_true(hash_set_size(phset_second) == 10);
    assert_false(b_output);
    hash_set_destroy(phset_first);
    hash_set_destroy(phset_second);
}

void test__type_less_hash_set__greater(void** state)
{
    hash_set_t* phset_first = NULL;
    hash_set_t* phset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phset_first = create_hash_set(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phset_second = create_hash_set(int)) == NULL) {
        assert_true(false);
        hash_set_destroy(phset_first);
        return;
    }
    hash_set_init(phset_first);
    for (i = 0; i < 10; ++i) {
        hash_set_insert(phset_first, i);
    }
    hash_set_init(phset_second);
    for (i = 0; i < 4; ++i) {
        hash_set_insert(phset_second, i);
    }
    _type_less_hash_set(phset_first, phset_second, &b_output);
    assert_true(hash_set_size(phset_first) == 10);
    assert_true(hash_set_size(phset_second) == 4);
    assert_false(b_output);
    hash_set_destroy(phset_first);
    hash_set_destroy(phset_second);
}

/*
 * test _type_destroy_hash_set
 */
UT_CASE_DEFINATION(_type_destroy_hash_set)
void test__type_destroy_hash_set__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_hash_set(NULL, &b_output));
}

void test__type_destroy_hash_set__null_output(void** state)
{
    hash_set_t* phset_input = create_hash_set(int);
    if (phset_input == NULL) {
        assert_true(false);
        return;
    }
    hash_set_init(phset_input);
    expect_assert_failure(_type_destroy_hash_set(phset_input, NULL));
    hash_set_destroy(phset_input);
}

void test__type_destroy_hash_set__ok(void** state)
{
    bool_t b_output = false;
    int i = 0;
    hash_set_t* phset_input = create_hash_set(int);
    if (phset_input == NULL) {
        assert_true(false);
        return;
    }
    hash_set_init(phset_input);
    for (i = 0; i < 10; ++i) {
        hash_set_insert(phset_input, i);
    }
    _type_destroy_hash_set(phset_input, &b_output);
    assert_true(b_output);
    free(phset_input);
}

/*
 * test _type_init_hash_multiset
 */
UT_CASE_DEFINATION(_type_init_hash_multiset)
void test__type_init_hash_multiset__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_hash_multiset(NULL, &b_output));
}

void test__type_init_hash_multiset__null_output(void** state)
{
    hash_multiset_t* phmset_input = malloc(sizeof(hash_multiset_t));
    if (phmset_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_hash_multiset(phmset_input, NULL));
    free(phmset_input);
}

void test__type_init_hash_multiset__ok(void** state)
{
    hash_multiset_t* phmset_input = malloc(sizeof(hash_multiset_t));
    const char* b_output = "int";
    if (phmset_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_hash_multiset(phmset_input, (void*)b_output);
    //assert_true(_hash_multiset_is_inited(phmset_input));
    hash_multiset_destroy(phmset_input);
}

/*
 * test _type_copy_hash_multiset
 */
UT_CASE_DEFINATION(_type_copy_hash_multiset)
void test__type_copy_hash_multiset__null_first(void** state)
{
    hash_multiset_t* phmset_second = NULL;
    bool_t b_output = false;
    
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_multiset_init(phmset_second);
    expect_assert_failure(_type_copy_hash_multiset(NULL, phmset_second, &b_output));
    hash_multiset_destroy(phmset_second);
}

void test__type_copy_hash_multiset__null_second(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    bool_t b_output = false;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    expect_assert_failure(_type_copy_hash_multiset(phmset_first, NULL, &b_output));
    hash_multiset_destroy(phmset_first);
}

void test__type_copy_hash_multiset__null_output(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    hash_multiset_t* phmset_second = NULL;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        hash_multiset_destroy(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    hash_multiset_init(phmset_second);
    expect_assert_failure(_type_copy_hash_multiset(phmset_first, phmset_second, NULL));
    hash_multiset_destroy(phmset_first);
    hash_multiset_destroy(phmset_second);
}

void test__type_copy_hash_multiset__ok(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    hash_multiset_t* phmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        hash_multiset_destroy(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    hash_multiset_init(phmset_second);
    for (i = 0; i < 10; ++i) {
        hash_multiset_insert(phmset_second, i);
    }
    _type_copy_hash_multiset(phmset_first, phmset_second, &b_output);
    assert_true(hash_multiset_size(phmset_first) == 10);
    assert_true(hash_multiset_size(phmset_second) == 10);
    assert_true(b_output);
    hash_multiset_destroy(phmset_first);
    hash_multiset_destroy(phmset_second);
}

/*
 * test _type_less_hash_multiset
 */
UT_CASE_DEFINATION(_type_less_hash_multiset)
void test__type_less_hash_multiset__null_first(void** state)
{
    hash_multiset_t* phmset_second = NULL;
    bool_t b_output = false;
    
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_multiset_init(phmset_second);
    expect_assert_failure(_type_less_hash_multiset(NULL, phmset_second, &b_output));
    hash_multiset_destroy(phmset_second);
}

void test__type_less_hash_multiset__null_second(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    bool_t b_output = false;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    expect_assert_failure(_type_less_hash_multiset(phmset_first, NULL, &b_output));
    hash_multiset_destroy(phmset_first);
}

void test__type_less_hash_multiset__null_output(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    hash_multiset_t* phmset_second = NULL;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        hash_multiset_destroy(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    hash_multiset_init(phmset_second);
    expect_assert_failure(_type_less_hash_multiset(phmset_first, phmset_second, NULL));
    hash_multiset_destroy(phmset_first);
    hash_multiset_destroy(phmset_second);
}

void test__type_less_hash_multiset__less(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    hash_multiset_t* phmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        hash_multiset_destroy(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    hash_multiset_init(phmset_second);
    for (i = 0; i < 10; ++i) {
        hash_multiset_insert(phmset_second, i);
    }
    _type_less_hash_multiset(phmset_first, phmset_second, &b_output);
    assert_true(hash_multiset_empty(phmset_first));
    assert_true(hash_multiset_size(phmset_second) == 10);
    assert_true(b_output);
    hash_multiset_destroy(phmset_first);
    hash_multiset_destroy(phmset_second);
}

void test__type_less_hash_multiset__equal(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    hash_multiset_t* phmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        hash_multiset_destroy(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    for (i = 0; i < 10; ++i) {
        hash_multiset_insert(phmset_first, i);
    }
    hash_multiset_init(phmset_second);
    for (i = 0; i < 10; ++i) {
        hash_multiset_insert(phmset_second, i);
    }
    _type_less_hash_multiset(phmset_first, phmset_second, &b_output);
    assert_true(hash_multiset_size(phmset_first) == 10);
    assert_true(hash_multiset_size(phmset_second) == 10);
    assert_false(b_output);
    hash_multiset_destroy(phmset_first);
    hash_multiset_destroy(phmset_second);
}

void test__type_less_hash_multiset__greater(void** state)
{
    hash_multiset_t* phmset_first = NULL;
    hash_multiset_t* phmset_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((phmset_first = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmset_second = create_hash_multiset(int)) == NULL) {
        assert_true(false);
        hash_multiset_destroy(phmset_first);
        return;
    }
    hash_multiset_init(phmset_first);
    for (i = 0; i < 10; ++i) {
        hash_multiset_insert(phmset_first, i);
    }
    hash_multiset_init(phmset_second);
    for (i = 0; i < 4; ++i) {
        hash_multiset_insert(phmset_second, i);
    }
    _type_less_hash_multiset(phmset_first, phmset_second, &b_output);
    assert_true(hash_multiset_size(phmset_first) == 10);
    assert_true(hash_multiset_size(phmset_second) == 4);
    assert_false(b_output);
    hash_multiset_destroy(phmset_first);
    hash_multiset_destroy(phmset_second);
}

/*
 * test _type_destroy_hash_multiset
 */
UT_CASE_DEFINATION(_type_destroy_hash_multiset)
void test__type_destroy_hash_multiset__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_hash_multiset(NULL, &b_output));
}

void test__type_destroy_hash_multiset__null_output(void** state)
{
    hash_multiset_t* phmset_input = create_hash_multiset(int);
    if (phmset_input == NULL) {
        assert_true(false);
        return;
    }
    hash_multiset_init(phmset_input);
    expect_assert_failure(_type_destroy_hash_multiset(phmset_input, NULL));
    hash_multiset_destroy(phmset_input);
}

void test__type_destroy_hash_multiset__ok(void** state)
{
    bool_t b_output = false;
    int i = 0;
    hash_multiset_t* phmset_input = create_hash_multiset(int);
    if (phmset_input == NULL) {
        assert_true(false);
        return;
    }
    hash_multiset_init(phmset_input);
    for (i = 0; i < 10; ++i) {
        hash_multiset_insert(phmset_input, i);
    }
    _type_destroy_hash_multiset(phmset_input, &b_output);
    assert_true(b_output);
    free(phmset_input);
}

/*
 * test _type_init_hash_map
 */
UT_CASE_DEFINATION(_type_init_hash_map)
void test__type_init_hash_map__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_hash_map(NULL, &b_output));
}

void test__type_init_hash_map__null_output(void** state)
{
    hash_map_t* phmap_input = malloc(sizeof(hash_map_t));
    if (phmap_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_hash_map(phmap_input, NULL));
    free(phmap_input);
}

void test__type_init_hash_map__ok(void** state)
{
    hash_map_t* phmap_input = malloc(sizeof(hash_map_t));
    const char* b_output = "int, int";
    if (phmap_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_hash_map(phmap_input, (void*)b_output);
    //assert_true(_hash_map_is_inited(phmap_input));
    hash_map_destroy(phmap_input);
}

/*
 * test _type_copy_hash_map
 */
UT_CASE_DEFINATION(_type_copy_hash_map)
void test__type_copy_hash_map__null_first(void** state)
{
    hash_map_t* phmap_second = NULL;
    bool_t b_output = false;
    
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_map_init(phmap_second);
    expect_assert_failure(_type_copy_hash_map(NULL, phmap_second, &b_output));
    hash_map_destroy(phmap_second);
}

void test__type_copy_hash_map__null_second(void** state)
{
    hash_map_t* phmap_first = NULL;
    bool_t b_output = false;
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(phmap_first);
        return;
    }
    hash_map_init(phmap_first);
    expect_assert_failure(_type_copy_hash_map(phmap_first, NULL, &b_output));
    hash_map_destroy(phmap_first);
}

void test__type_copy_hash_map__null_output(void** state)
{
    hash_map_t* phmap_first = NULL;
    hash_map_t* phmap_second = NULL;
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        hash_map_destroy(phmap_first);
        return;
    }
    hash_map_init(phmap_first);
    hash_map_init(phmap_second);
    expect_assert_failure(_type_copy_hash_map(phmap_first, phmap_second, NULL));
    hash_map_destroy(phmap_first);
    hash_map_destroy(phmap_second);
}

void test__type_copy_hash_map__ok(void** state)
{
    hash_map_t* phmap_first = NULL;
    hash_map_t* phmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
    }
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        hash_map_destroy(phmap_first);
        pair_destroy(ppair);
        return;
    }
    hash_map_init(phmap_first);
    hash_map_init(phmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_map_insert(phmap_second, ppair);
    }
    _type_copy_hash_map(phmap_first, phmap_second, &b_output);
    assert_true(hash_map_size(phmap_first) == 10);
    assert_true(hash_map_size(phmap_second) == 10);
    assert_true(b_output);
    hash_map_destroy(phmap_first);
    hash_map_destroy(phmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_less_hash_map
 */
UT_CASE_DEFINATION(_type_less_hash_map)
void test__type_less_hash_map__null_first(void** state)
{
    hash_map_t* phmap_second = NULL;
    bool_t b_output = false;
    
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_map_init(phmap_second);
    expect_assert_failure(_type_less_hash_map(NULL, phmap_second, &b_output));
    hash_map_destroy(phmap_second);
}

void test__type_less_hash_map__null_second(void** state)
{
    hash_map_t* phmap_first = NULL;
    bool_t b_output = false;
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(phmap_first);
        return;
    }
    hash_map_init(phmap_first);
    expect_assert_failure(_type_less_hash_map(phmap_first, NULL, &b_output));
    hash_map_destroy(phmap_first);
}

void test__type_less_hash_map__null_output(void** state)
{
    hash_map_t* phmap_first = NULL;
    hash_map_t* phmap_second = NULL;
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        hash_map_destroy(phmap_first);
        return;
    }
    hash_map_init(phmap_first);
    hash_map_init(phmap_second);
    expect_assert_failure(_type_less_hash_map(phmap_first, phmap_second, NULL));
    hash_map_destroy(phmap_first);
    hash_map_destroy(phmap_second);
}

void test__type_less_hash_map__less(void** state)
{
    hash_map_t* phmap_first = NULL;
    hash_map_t* phmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        hash_map_destroy(phmap_first);
        pair_destroy(ppair);
        return;
    }
    hash_map_init(phmap_first);
    hash_map_init(phmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_map_insert(phmap_second, ppair);
    }
    _type_less_hash_map(phmap_first, phmap_second, &b_output);
    assert_true(hash_map_empty(phmap_first));
    assert_true(hash_map_size(phmap_second) == 10);
    assert_true(b_output);
    hash_map_destroy(phmap_first);
    hash_map_destroy(phmap_second);
    pair_destroy(ppair);
}

void test__type_less_hash_map__equal(void** state)
{
    hash_map_t* phmap_first = NULL;
    hash_map_t* phmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        hash_map_destroy(phmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    hash_map_init(phmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_map_insert(phmap_first, ppair);
    }
    hash_map_init(phmap_second);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_map_insert(phmap_second, ppair);
    }
    _type_less_hash_map(phmap_first, phmap_second, &b_output);
    assert_true(hash_map_size(phmap_first) == 10);
    assert_true(hash_map_size(phmap_second) == 10);
    assert_false(b_output);
    hash_map_destroy(phmap_first);
    hash_map_destroy(phmap_second);
    pair_destroy(ppair);
}

void test__type_less_hash_map__greater(void** state)
{
    hash_map_t* phmap_first = NULL;
    hash_map_t* phmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmap_first = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmap_second = create_hash_map(int, int)) == NULL) {
        assert_true(false);
        hash_map_destroy(phmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    hash_map_init(phmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_map_insert(phmap_first, ppair);
    }
    hash_map_init(phmap_second);
    for (i = 0; i < 4; ++i) {
        pair_make(ppair, i, i);
        hash_map_insert(phmap_second, ppair);
    }
    _type_less_hash_map(phmap_first, phmap_second, &b_output);
    assert_true(hash_map_size(phmap_first) == 10);
    assert_true(hash_map_size(phmap_second) == 4);
    assert_false(b_output);
    hash_map_destroy(phmap_first);
    hash_map_destroy(phmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_destroy_hash_map
 */
UT_CASE_DEFINATION(_type_destroy_hash_map)
void test__type_destroy_hash_map__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_hash_map(NULL, &b_output));
}

void test__type_destroy_hash_map__null_output(void** state)
{
    hash_map_t* phmap_input = create_hash_map(int, int);
    if (phmap_input == NULL) {
        assert_true(false);
        return;
    }
    hash_map_init(phmap_input);
    expect_assert_failure(_type_destroy_hash_map(phmap_input, NULL));
    hash_map_destroy(phmap_input);
}

void test__type_destroy_hash_map__ok(void** state)
{
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    hash_map_t* phmap_input = create_hash_map(int, int);
    if (phmap_input == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        hash_map_destroy(phmap_input);
        return;
    }
    pair_init(ppair);
    hash_map_init(phmap_input);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_map_insert(phmap_input, ppair);
    }
    _type_destroy_hash_map(phmap_input, &b_output);
    assert_true(b_output);
    free(phmap_input);
    pair_destroy(ppair);
}

/*
 * test _type_init_hash_multimap
 */
UT_CASE_DEFINATION(_type_init_hash_multimap)
void test__type_init_hash_multimap__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_hash_multimap(NULL, &b_output));
}

void test__type_init_hash_multimap__null_output(void** state)
{
    hash_multimap_t* phmmap_input = malloc(sizeof(hash_multimap_t));
    if (phmmap_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_hash_multimap(phmmap_input, NULL));
    free(phmmap_input);
}

void test__type_init_hash_multimap__ok(void** state)
{
    hash_multimap_t* phmmap_input = malloc(sizeof(hash_multimap_t));
    const char* b_output = "int, int";
    if (phmmap_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_hash_multimap(phmmap_input, (void*)b_output);
    //assert_true(_hash_multimap_is_inited(phmmap_input));
    hash_multimap_destroy(phmmap_input);
}

/*
 * test _type_copy_hash_multimap
 */
UT_CASE_DEFINATION(_type_copy_hash_multimap)
void test__type_copy_hash_multimap__null_first(void** state)
{
    hash_multimap_t* phmmap_second = NULL;
    bool_t b_output = false;
    
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_multimap_init(phmmap_second);
    expect_assert_failure(_type_copy_hash_multimap(NULL, phmmap_second, &b_output));
    hash_multimap_destroy(phmmap_second);
}

void test__type_copy_hash_multimap__null_second(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    bool_t b_output = false;
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(phmmap_first);
        return;
    }
    hash_multimap_init(phmmap_first);
    expect_assert_failure(_type_copy_hash_multimap(phmmap_first, NULL, &b_output));
    hash_multimap_destroy(phmmap_first);
}

void test__type_copy_hash_multimap__null_output(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    hash_multimap_t* phmmap_second = NULL;
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        hash_multimap_destroy(phmmap_first);
        return;
    }
    hash_multimap_init(phmmap_first);
    hash_multimap_init(phmmap_second);
    expect_assert_failure(_type_copy_hash_multimap(phmmap_first, phmmap_second, NULL));
    hash_multimap_destroy(phmmap_first);
    hash_multimap_destroy(phmmap_second);
}

void test__type_copy_hash_multimap__ok(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    hash_multimap_t* phmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
    }
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        hash_multimap_destroy(phmmap_first);
        pair_destroy(ppair);
        return;
    }
    hash_multimap_init(phmmap_first);
    hash_multimap_init(phmmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmmap_second, ppair);
    }
    _type_copy_hash_multimap(phmmap_first, phmmap_second, &b_output);
    assert_true(hash_multimap_size(phmmap_first) == 10);
    assert_true(hash_multimap_size(phmmap_second) == 10);
    assert_true(b_output);
    hash_multimap_destroy(phmmap_first);
    hash_multimap_destroy(phmmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_less_hash_multimap
 */
UT_CASE_DEFINATION(_type_less_hash_multimap)
void test__type_less_hash_multimap__null_first(void** state)
{
    hash_multimap_t* phmmap_second = NULL;
    bool_t b_output = false;
    
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    hash_multimap_init(phmmap_second);
    expect_assert_failure(_type_less_hash_multimap(NULL, phmmap_second, &b_output));
    hash_multimap_destroy(phmmap_second);
}

void test__type_less_hash_multimap__null_second(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    bool_t b_output = false;
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(phmmap_first);
        return;
    }
    hash_multimap_init(phmmap_first);
    expect_assert_failure(_type_less_hash_multimap(phmmap_first, NULL, &b_output));
    hash_multimap_destroy(phmmap_first);
}

void test__type_less_hash_multimap__null_output(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    hash_multimap_t* phmmap_second = NULL;
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        hash_multimap_destroy(phmmap_first);
        return;
    }
    hash_multimap_init(phmmap_first);
    hash_multimap_init(phmmap_second);
    expect_assert_failure(_type_less_hash_multimap(phmmap_first, phmmap_second, NULL));
    hash_multimap_destroy(phmmap_first);
    hash_multimap_destroy(phmmap_second);
}

void test__type_less_hash_multimap__less(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    hash_multimap_t* phmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        hash_multimap_destroy(phmmap_first);
        pair_destroy(ppair);
        return;
    }
    hash_multimap_init(phmmap_first);
    hash_multimap_init(phmmap_second);
    pair_init(ppair);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmmap_second, ppair);
    }
    _type_less_hash_multimap(phmmap_first, phmmap_second, &b_output);
    assert_true(hash_multimap_empty(phmmap_first));
    assert_true(hash_multimap_size(phmmap_second) == 10);
    assert_true(b_output);
    hash_multimap_destroy(phmmap_first);
    hash_multimap_destroy(phmmap_second);
    pair_destroy(ppair);
}

void test__type_less_hash_multimap__equal(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    hash_multimap_t* phmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        hash_multimap_destroy(phmmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    hash_multimap_init(phmmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmmap_first, ppair);
    }
    hash_multimap_init(phmmap_second);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmmap_second, ppair);
    }
    _type_less_hash_multimap(phmmap_first, phmmap_second, &b_output);
    assert_true(hash_multimap_size(phmmap_first) == 10);
    assert_true(hash_multimap_size(phmmap_second) == 10);
    assert_false(b_output);
    hash_multimap_destroy(phmmap_first);
    hash_multimap_destroy(phmmap_second);
    pair_destroy(ppair);
}

void test__type_less_hash_multimap__greater(void** state)
{
    hash_multimap_t* phmmap_first = NULL;
    hash_multimap_t* phmmap_second = NULL;
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((phmmap_first = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair);
        return;
    }
    if ((phmmap_second = create_hash_multimap(int, int)) == NULL) {
        assert_true(false);
        hash_multimap_destroy(phmmap_first);
        pair_destroy(ppair);
        return;
    }
    pair_init(ppair);
    hash_multimap_init(phmmap_first);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmmap_first, ppair);
    }
    hash_multimap_init(phmmap_second);
    for (i = 0; i < 4; ++i) {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmmap_second, ppair);
    }
    _type_less_hash_multimap(phmmap_first, phmmap_second, &b_output);
    assert_true(hash_multimap_size(phmmap_first) == 10);
    assert_true(hash_multimap_size(phmmap_second) == 4);
    assert_false(b_output);
    hash_multimap_destroy(phmmap_first);
    hash_multimap_destroy(phmmap_second);
    pair_destroy(ppair);
}

/*
 * test _type_destroy_hash_multimap
 */
UT_CASE_DEFINATION(_type_destroy_hash_multimap)
void test__type_destroy_hash_multimap__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_hash_multimap(NULL, &b_output));
}

void test__type_destroy_hash_multimap__null_output(void** state)
{
    hash_multimap_t* phmmap_input = create_hash_multimap(int, int);
    if (phmmap_input == NULL) {
        assert_true(false);
        return;
    }
    hash_multimap_init(phmmap_input);
    expect_assert_failure(_type_destroy_hash_multimap(phmmap_input, NULL));
    hash_multimap_destroy(phmmap_input);
}

void test__type_destroy_hash_multimap__ok(void** state)
{
    pair_t* ppair = NULL;
    bool_t b_output = false;
    int i = 0;
    hash_multimap_t* phmmap_input = create_hash_multimap(int, int);
    if (phmmap_input == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair = create_pair(int, int)) == NULL) {
        assert_true(false);
        hash_multimap_destroy(phmmap_input);
        return;
    }
    pair_init(ppair);
    hash_multimap_init(phmmap_input);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        hash_multimap_insert(phmmap_input, ppair);
    }
    _type_destroy_hash_multimap(phmmap_input, &b_output);
    assert_true(b_output);
    free(phmmap_input);
    pair_destroy(ppair);
}

/*
 * test _type_init_pair
 */
UT_CASE_DEFINATION(_type_init_pair)
void test__type_init_pair__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_pair(NULL, &b_output));
}

void test__type_init_pair__null_output(void** state)
{
    pair_t* ppair_input = malloc(sizeof(pair_t));
    if (ppair_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_pair(ppair_input, NULL));
    free(ppair_input);
}

void test__type_init_pair__ok(void** state)
{
    pair_t* ppair_input = malloc(sizeof(pair_t));
    const char* b_output = "int, int";
    if (ppair_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_pair(ppair_input, (void*)b_output);
    //assert_true(_pair_is_inited(ppair_input));
    pair_destroy(ppair_input);
}

/*
 * test _type_copy_pair
 */
UT_CASE_DEFINATION(_type_copy_pair)
void test__type_copy_pair__null_first(void** state)
{
    pair_t* ppair_second = NULL;
    bool_t b_output = false;
    
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    pair_init(ppair_second);
    expect_assert_failure(_type_copy_pair(NULL, ppair_second, &b_output));
    pair_destroy(ppair_second);
}

void test__type_copy_pair__null_second(void** state)
{
    pair_t* ppair_first = NULL;
    bool_t b_output = false;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(ppair_first);
        return;
    }
    pair_init(ppair_first);
    expect_assert_failure(_type_copy_pair(ppair_first, NULL, &b_output));
    pair_destroy(ppair_first);
}

void test__type_copy_pair__null_output(void** state)
{
    pair_t* ppair_first = NULL;
    pair_t* ppair_second = NULL;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair_first);
        return;
    }
    pair_init(ppair_first);
    pair_init(ppair_second);
    expect_assert_failure(_type_copy_pair(ppair_first, ppair_second, NULL));
    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__type_copy_pair__ok(void** state)
{
    pair_t* ppair_first = NULL;
    pair_t* ppair_second = NULL;
    bool_t b_output = false;
    int i = 0;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair_first);
        return;
    }
    pair_init(ppair_first);
    pair_init_elem(ppair_second, 3, 4);
    _type_copy_pair(ppair_first, ppair_second, &b_output);
    assert_true(*(int*)pair_first(ppair_first) == 3);
    assert_true(*(int*)pair_second(ppair_first) == 4);
    assert_true(*(int*)pair_first(ppair_second) == 3);
    assert_true(*(int*)pair_second(ppair_second) == 4);
    assert_true(b_output);
    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

/*
 * test _type_less_pair
 */
UT_CASE_DEFINATION(_type_less_pair)
void test__type_less_pair__null_first(void** state)
{
    pair_t* ppair_second = NULL;
    bool_t b_output = false;
    
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    pair_init(ppair_second);
    expect_assert_failure(_type_less_pair(NULL, ppair_second, &b_output));
    pair_destroy(ppair_second);
}

void test__type_less_pair__null_second(void** state)
{
    pair_t* ppair_first = NULL;
    bool_t b_output = false;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(ppair_first);
        return;
    }
    pair_init(ppair_first);
    expect_assert_failure(_type_less_pair(ppair_first, NULL, &b_output));
    pair_destroy(ppair_first);
}

void test__type_less_pair__null_output(void** state)
{
    pair_t* ppair_first = NULL;
    pair_t* ppair_second = NULL;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair_first);
        return;
    }
    pair_init(ppair_first);
    pair_init(ppair_second);
    expect_assert_failure(_type_less_pair(ppair_first, ppair_second, NULL));
    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__type_less_pair__less(void** state)
{
    pair_t* ppair_first = NULL;
    pair_t* ppair_second = NULL;
    bool_t b_output = false;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair_first);
        return;
    }
    pair_init(ppair_first);
    pair_init_elem(ppair_second, 3, 5);
    _type_less_pair(ppair_first, ppair_second, &b_output);
    assert_true(pair_less(ppair_first, ppair_second));
    assert_true(*(int*)pair_first(ppair_first) == 0);
    assert_true(*(int*)pair_second(ppair_first) == 0);
    assert_true(*(int*)pair_first(ppair_second) == 3);
    assert_true(*(int*)pair_second(ppair_second) == 5);
    assert_true(b_output);
    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__type_less_pair__equal(void** state)
{
    pair_t* ppair_first = NULL;
    pair_t* ppair_second = NULL;
    bool_t b_output = false;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair_first);
        return;
    }
    pair_init(ppair_first);
    pair_init(ppair_second);
    _type_less_pair(ppair_first, ppair_second, &b_output);
    assert_true(pair_equal(ppair_first, ppair_second));
    assert_true(*(int*)pair_first(ppair_first) == 0);
    assert_true(*(int*)pair_second(ppair_first) == 0);
    assert_true(*(int*)pair_first(ppair_second) == 0);
    assert_true(*(int*)pair_second(ppair_second) == 0);
    assert_false(b_output);
    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

void test__type_less_pair__greater(void** state)
{
    pair_t* ppair_first = NULL;
    pair_t* ppair_second = NULL;
    bool_t b_output = false;
    if ((ppair_first = create_pair(int, int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((ppair_second = create_pair(int, int)) == NULL) {
        assert_true(false);
        pair_destroy(ppair_first);
        return;
    }
    pair_init(ppair_first);
    pair_init_elem(ppair_second, -3, 4);
    _type_less_pair(ppair_first, ppair_second, &b_output);
    assert_true(pair_greater(ppair_first, ppair_second));
    assert_true(*(int*)pair_first(ppair_first) == 0);
    assert_true(*(int*)pair_second(ppair_first) == 0);
    assert_true(*(int*)pair_first(ppair_second) == -3);
    assert_true(*(int*)pair_second(ppair_second) == 4);
    assert_false(b_output);
    pair_destroy(ppair_first);
    pair_destroy(ppair_second);
}

/*
 * test _type_destroy_pair
 */
UT_CASE_DEFINATION(_type_destroy_pair)
void test__type_destroy_pair__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_pair(NULL, &b_output));
}

void test__type_destroy_pair__null_output(void** state)
{
    pair_t* ppair_input = create_pair(int, int);
    if (ppair_input == NULL) {
        assert_true(false);
        return;
    }
    pair_init(ppair_input);
    expect_assert_failure(_type_destroy_pair(ppair_input, NULL));
    pair_destroy(ppair_input);
}

void test__type_destroy_pair__ok(void** state)
{
    bool_t b_output = false;
    pair_t* ppair_input = create_pair(int, int);
    if (ppair_input == NULL) {
        assert_true(false);
        return;
    }
    pair_init(ppair_input);
    _type_destroy_pair(ppair_input, &b_output);
    assert_true(b_output);
    free(ppair_input);
}

/*
 * test _type_init_string
 */
UT_CASE_DEFINATION(_type_init_string)
void test__type_init_string__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_string(NULL, &b_output));
}

void test__type_init_string__null_output(void** state)
{
    string_t* pstr_input = malloc(sizeof(string_t));
    if (pstr_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_string(pstr_input, NULL));
    free(pstr_input);
}

void test__type_init_string__ok(void** state)
{
    string_t* pstr_input = malloc(sizeof(string_t));
    bool_t b_output = false;
    if (pstr_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_string(pstr_input, &b_output);
    //assert_true(_string_is_inited(pstr_input));
    string_destroy(pstr_input);
}

/*
 * test _type_copy_string
 */
UT_CASE_DEFINATION(_type_copy_string)
void test__type_copy_string__null_first(void** state)
{
    string_t* pstr_second = NULL;
    bool_t b_output = false;
    
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    string_init(pstr_second);
    expect_assert_failure(_type_copy_string(NULL, pstr_second, &b_output));
    string_destroy(pstr_second);
}

void test__type_copy_string__null_second(void** state)
{
    string_t* pstr_first = NULL;
    bool_t b_output = false;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(pstr_first);
        return;
    }
    string_init(pstr_first);
    expect_assert_failure(_type_copy_string(pstr_first, NULL, &b_output));
    string_destroy(pstr_first);
}

void test__type_copy_string__null_output(void** state)
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
    expect_assert_failure(_type_copy_string(pstr_first, pstr_second, NULL));
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_copy_string__ok(void** state)
{
    string_t* pstr_first = NULL;
    string_t* pstr_second = NULL;
    bool_t b_output = false;
    int i = 0;
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
    _type_copy_string(pstr_first, pstr_second, &b_output);
    assert_true(strcmp(string_c_str(pstr_first), "abc") == 0);
    assert_true(strcmp(string_c_str(pstr_second), "abc") == 0);
    assert_true(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test _type_less_string
 */
UT_CASE_DEFINATION(_type_less_string)
void test__type_less_string__null_first(void** state)
{
    string_t* pstr_second = NULL;
    bool_t b_output = false;
    
    if ((pstr_second = create_string()) == NULL) {
        assert_true(false);
        return;
    }
    string_init(pstr_second);
    expect_assert_failure(_type_less_string(NULL, pstr_second, &b_output));
    string_destroy(pstr_second);
}

void test__type_less_string__null_second(void** state)
{
    string_t* pstr_first = NULL;
    bool_t b_output = false;
    if ((pstr_first = create_string()) == NULL) {
        assert_true(pstr_first);
        return;
    }
    string_init(pstr_first);
    expect_assert_failure(_type_less_string(pstr_first, NULL, &b_output));
    string_destroy(pstr_first);
}

void test__type_less_string__null_output(void** state)
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
    expect_assert_failure(_type_less_string(pstr_first, pstr_second, NULL));
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_less_string__less(void** state)
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
    string_init_cstr(pstr_second, "def");
    _type_less_string(pstr_first, pstr_second, &b_output);
    assert_true(string_less(pstr_first, pstr_second));
    assert_true(strcmp(string_c_str(pstr_first), "abc") == 0);
    assert_true(strcmp(string_c_str(pstr_second), "def") == 0);
    assert_true(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_less_string__equal(void** state)
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
    string_init(pstr_second);
    _type_less_string(pstr_first, pstr_second, &b_output);
    assert_true(string_equal(pstr_first, pstr_second));
    assert_true(string_empty(pstr_first));
    assert_true(string_empty(pstr_second));
    assert_false(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

void test__type_less_string__greater(void** state)
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
    string_init_cstr(pstr_first, "xyz");
    string_init_cstr(pstr_second, "abc");
    _type_less_string(pstr_first, pstr_second, &b_output);
    assert_true(string_greater(pstr_first, pstr_second));
    assert_true(strcmp(string_c_str(pstr_first), "xyz") == 0);
    assert_true(strcmp(string_c_str(pstr_second), "abc") == 0);
    assert_false(b_output);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

/*
 * test _type_destroy_string
 */
UT_CASE_DEFINATION(_type_destroy_string)
void test__type_destroy_string__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_string(NULL, &b_output));
}

void test__type_destroy_string__null_output(void** state)
{
    string_t* pstr_input = create_string();
    if (pstr_input == NULL) {
        assert_true(false);
        return;
    }
    string_init(pstr_input);
    expect_assert_failure(_type_destroy_string(pstr_input, NULL));
    string_destroy(pstr_input);
}

void test__type_destroy_string__ok(void** state)
{
    bool_t b_output = false;
    string_t* pstr_input = create_string();
    if (pstr_input == NULL) {
        assert_true(false);
        return;
    }
    string_init(pstr_input);
    _type_destroy_string(pstr_input, &b_output);
    assert_true(b_output);
    free(pstr_input);
}

/*
 * test _type_init_iterator
 */
UT_CASE_DEFINATION(_type_init_iterator)
void test__type_init_iterator__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_iterator(NULL, &b_output));
}

void test__type_init_iterator__null_output(void** state)
{
    iterator_t it_input;
    expect_assert_failure(_type_init_iterator(&it_input, NULL));
}

void test__type_init_iterator__ok(void** state)
{
    iterator_t it_input;
    bool_t b_output = false;
    _type_init_iterator(&it_input, &b_output);
}

/*
 * test _type_copy_iterator
 */
UT_CASE_DEFINATION(_type_copy_iterator)
void test__type_copy_iterator__null_first(void** state)
{
    iterator_t it_second;
    bool_t b_output = false;
    
    expect_assert_failure(_type_copy_iterator(NULL, &it_second, &b_output));
}

void test__type_copy_iterator__null_second(void** state)
{
    iterator_t it_first;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_iterator(&it_first, NULL, &b_output));
}

void test__type_copy_iterator__null_output(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    expect_assert_failure(_type_copy_iterator(&it_first, &it_second, NULL));
}

void test__type_copy_iterator__ok(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    bool_t b_output = false;
    memset(&it_second, 0x11, sizeof(iterator_t));
    _type_copy_iterator(&it_first, &it_second, &b_output);
    assert_true(memcmp(&it_first, &it_second, sizeof(iterator_t)) == 0);
    assert_true(b_output);
}

/*
 * test _type_less_iterator
 */
UT_CASE_DEFINATION(_type_less_iterator)
void test__type_less_iterator__null_first(void** state)
{
    iterator_t it_second;
    bool_t b_output = false;
    expect_assert_failure(_type_less_iterator(NULL, &it_second, &b_output));
}

void test__type_less_iterator__null_second(void** state)
{
    iterator_t it_first;
    bool_t b_output = false;
    expect_assert_failure(_type_less_iterator(&it_first, NULL, &b_output));
}

void test__type_less_iterator__null_output(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    expect_assert_failure(_type_less_iterator(&it_first, &it_second, NULL));
}

void test__type_less_iterator__less(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    bool_t b_output = false;
    memset(&it_first, 0x00, sizeof(iterator_t));
    memset(&it_second, 0x11, sizeof(iterator_t));
    _type_less_iterator(&it_first, &it_second, &b_output);
    assert_true(b_output);
}

void test__type_less_iterator__equal(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    bool_t b_output = false;
    memset(&it_first, 0x11, sizeof(iterator_t));
    memset(&it_second, 0x11, sizeof(iterator_t));
    _type_less_iterator(&it_first, &it_second, &b_output);
    assert_false(b_output);
}

void test__type_less_iterator__greater(void** state)
{
    iterator_t it_first;
    iterator_t it_second;
    bool_t b_output = false;
    memset(&it_first, 0x11, sizeof(iterator_t));
    memset(&it_second, 0x00, sizeof(iterator_t));
    _type_less_iterator(&it_first, &it_second, &b_output);
    assert_false(b_output);
}

/*
 * test _type_destroy_iterator
 */
UT_CASE_DEFINATION(_type_destroy_iterator)
void test__type_destroy_iterator__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_iterator(NULL, &b_output));
}

void test__type_destroy_iterator__null_output(void** state)
{
    iterator_t it_input;
    expect_assert_failure(_type_destroy_iterator(&it_input, NULL));
}

void test__type_destroy_iterator__ok(void** state)
{
    bool_t b_output = false;
    iterator_t it_input;
    _type_destroy_iterator(&it_input, &b_output);
    assert_true(b_output);
}

/*
 * test _type_init_pointer
 */
UT_CASE_DEFINATION(_type_init_pointer)
void test__type_init_pointer__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_pointer(NULL, &b_output));
}

void test__type_init_pointer__null_output(void** state)
{
    void* p = NULL;
    expect_assert_failure(_type_init_pointer(&p, NULL));
}

void test__type_init_pointer__ok(void** state)
{
    void* p = 0x1234;
    bool_t b_output = false;
    _type_init_pointer(&p, &b_output);
    assert_true(p == NULL);
    assert_true(b_output);
}

/*
 * test _type_copy_pointer
 */
UT_CASE_DEFINATION(_type_copy_pointer)
void test__type_copy_pointer__null_first(void** state)
{
    void* p_second = NULL;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_pointer(NULL, &p_second, &b_output));
}

void test__type_copy_pointer__null_second(void** state)
{
    void* p_first = NULL;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_pointer(&p_first, NULL, &b_output));
}

void test__type_copy_pointer__null_output(void** state)
{
    void* p_first = NULL;
    void* p_second = NULL;
    expect_assert_failure(_type_copy_pointer(&p_first, &p_second, NULL));
}

void test__type_copy_pointer__ok(void** state)
{
    void* p_first = 0x1234;
    void* p_second = 0xffff;
    bool_t b_output = false;
    _type_copy_pointer(&p_first, &p_second, &b_output);
    assert_true(b_output);
    assert_true(p_first == 0xffff);
    assert_true(p_second == 0xffff);
}

/*
 * test _type_less_pointer
 */
UT_CASE_DEFINATION(_type_less_pointer)
void test__type_less_pointer__null_first(void** state)
{
    void* p_second = NULL;
    bool_t b_output = false;
    expect_assert_failure(_type_less_pointer(NULL, &p_second, &b_output));
}

void test__type_less_pointer__null_second(void** state)
{
    void* p_first = NULL;
    bool_t b_output = false;
    expect_assert_failure(_type_less_pointer(&p_first, NULL, &b_output));
}

void test__type_less_pointer__null_output(void** state)
{
    void* p_first = NULL;
    void* p_second = NULL;
    expect_assert_failure(_type_less_pointer(&p_first, &p_second, NULL));
}

void test__type_less_pointer__less(void** state)
{
    void* p_first = 0x1234;
    void* p_second = 0xffff;
    bool_t b_output = false;
    _type_less_pointer(&p_first, &p_second, &b_output);
    assert_true(b_output);
    assert_true(p_first == 0x1234);
    assert_true(p_second == 0xffff);
}

void test__type_less_pointer__equal(void** state)
{
    void* p_first = 0x1234;
    void* p_second = 0x1234;
    bool_t b_output = false;
    _type_less_pointer(&p_first, &p_second, &b_output);
    assert_false(b_output);
    assert_true(p_first == 0x1234);
    assert_true(p_second == 0x1234);
}

void test__type_less_pointer__greater(void** state)
{
    void* p_first = 0xffff;
    void* p_second = 0x1234;
    bool_t b_output = false;
    _type_less_pointer(&p_first, &p_second, &b_output);
    assert_false(b_output);
    assert_true(p_first == 0xffff);
    assert_true(p_second == 0x1234);
}

/*
 * test _type_destroy_pointer
 */
UT_CASE_DEFINATION(_type_destroy_pointer)
void test__type_destroy_pointer__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_pointer(NULL, &b_output));
}

void test__type_destroy_pointer__null_output(void** state)
{
    void* p = NULL;
    expect_assert_failure(_type_destroy_pointer(&p, NULL));
}

void test__type_destroy_pointer__ok(void** state)
{
    void* p = 0x1234;
    bool_t b_output = false;
    _type_destroy_pointer(&p, &b_output);
    assert_true(b_output);
    assert_true(p == 0x1234);
}

/*
 * test _type_init_range
 */
UT_CASE_DEFINATION(_type_init_range)
void test__type_init_range__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_range(NULL, &b_output));
}

void test__type_init_range__null_output(void** state)
{
    range_t r_input;
    expect_assert_failure(_type_init_range(&r_input, NULL));
}

void test__type_init_range__ok(void** state)
{
    range_t r_input;
    bool_t b_output = false;
    _type_init_range(&r_input, &b_output);
}

/*
 * test _type_copy_range
 */
UT_CASE_DEFINATION(_type_copy_range)
void test__type_copy_range__null_first(void** state)
{
    range_t r_second;
    bool_t b_output = false;
    
    expect_assert_failure(_type_copy_range(NULL, &r_second, &b_output));
}

void test__type_copy_range__null_second(void** state)
{
    range_t r_first;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_range(&r_first, NULL, &b_output));
}

void test__type_copy_range__null_output(void** state)
{
    range_t r_first;
    range_t r_second;
    expect_assert_failure(_type_copy_range(&r_first, &r_second, NULL));
}

void test__type_copy_range__ok(void** state)
{
    range_t r_first;
    range_t r_second;
    bool_t b_output = false;
    memset(&r_second, 0x11, sizeof(range_t));
    _type_copy_range(&r_first, &r_second, &b_output);
    assert_true(memcmp(&r_first, &r_second, sizeof(range_t)) == 0);
    assert_true(b_output);
}

/*
 * test _type_less_range
 */
UT_CASE_DEFINATION(_type_less_range)
void test__type_less_range__null_first(void** state)
{
    range_t r_second;
    bool_t b_output = false;
    expect_assert_failure(_type_less_range(NULL, &r_second, &b_output));
}

void test__type_less_range__null_second(void** state)
{
    range_t r_first;
    bool_t b_output = false;
    expect_assert_failure(_type_less_range(&r_first, NULL, &b_output));
}

void test__type_less_range__null_output(void** state)
{
    range_t r_first;
    range_t r_second;
    expect_assert_failure(_type_less_range(&r_first, &r_second, NULL));
}

void test__type_less_range__less(void** state)
{
    range_t r_first;
    range_t r_second;
    bool_t b_output = false;
    memset(&r_first, 0x00, sizeof(range_t));
    memset(&r_second, 0x11, sizeof(range_t));
    _type_less_range(&r_first, &r_second, &b_output);
    assert_true(b_output);
}

void test__type_less_range__equal(void** state)
{
    range_t r_first;
    range_t r_second;
    bool_t b_output = false;
    memset(&r_first, 0x11, sizeof(range_t));
    memset(&r_second, 0x11, sizeof(range_t));
    _type_less_range(&r_first, &r_second, &b_output);
    assert_false(b_output);
}

void test__type_less_range__greater(void** state)
{
    range_t r_first;
    range_t r_second;
    bool_t b_output = false;
    memset(&r_first, 0x11, sizeof(range_t));
    memset(&r_second, 0x00, sizeof(range_t));
    _type_less_range(&r_first, &r_second, &b_output);
    assert_false(b_output);
}

/*
 * test _type_destroy_range
 */
UT_CASE_DEFINATION(_type_destroy_range)
void test__type_destroy_range__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_range(NULL, &b_output));
}

void test__type_destroy_range__null_output(void** state)
{
    range_t r_input;
    expect_assert_failure(_type_destroy_range(&r_input, NULL));
}

void test__type_destroy_range__ok(void** state)
{
    bool_t b_output = false;
    range_t r_input;
    _type_destroy_range(&r_input, &b_output);
    assert_true(b_output);
}

/*
 * test _type_init_basic_string
 */
UT_CASE_DEFINATION(_type_init_basic_string)
void test__type_init_basic_string__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_basic_string(NULL, &b_output));
}

void test__type_init_basic_string__null_output(void** state)
{
    basic_string_t* pbstr_input = malloc(sizeof(basic_string_t));
    if (pbstr_input == NULL) {
        assert_true(false);
        return;
    }
    expect_assert_failure(_type_init_basic_string(pbstr_input, NULL));
    free(pbstr_input);
}

void test__type_init_basic_string__ok(void** state)
{
    basic_string_t* pbstr_input = malloc(sizeof(basic_string_t));
    const char* b_output = "int";
    if (pbstr_input == NULL) {
        assert_true(false);
        return;
    }
    _type_init_basic_string(pbstr_input, (void*)b_output);
    assert_true(_basic_string_is_inited(pbstr_input));
    basic_string_destroy(pbstr_input);
}

/*
 * test _type_copy_basic_string
 */
UT_CASE_DEFINATION(_type_copy_basic_string)
void test__type_copy_basic_string__null_first(void** state)
{
    basic_string_t* pbstr_second = NULL;
    bool_t b_output = false;
    
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    basic_string_init(pbstr_second);
    expect_assert_failure(_type_copy_basic_string(NULL, pbstr_second, &b_output));
    basic_string_destroy(pbstr_second);
}

void test__type_copy_basic_string__null_second(void** state)
{
    basic_string_t* pbstr_first = NULL;
    bool_t b_output = false;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(pbstr_first);
        return;
    }
    basic_string_init(pbstr_first);
    expect_assert_failure(_type_copy_basic_string(pbstr_first, NULL, &b_output));
    basic_string_destroy(pbstr_first);
}

void test__type_copy_basic_string__null_output(void** state)
{
    basic_string_t* pbstr_first = NULL;
    basic_string_t* pbstr_second = NULL;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        basic_string_destroy(pbstr_first);
        return;
    }
    basic_string_init(pbstr_first);
    basic_string_init(pbstr_second);
    expect_assert_failure(_type_copy_basic_string(pbstr_first, pbstr_second, NULL));
    basic_string_destroy(pbstr_first);
    basic_string_destroy(pbstr_second);
}

void test__type_copy_basic_string__ok(void** state)
{
    basic_string_t* pbstr_first = NULL;
    basic_string_t* pbstr_second = NULL;
    bool_t b_output = false;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        basic_string_destroy(pbstr_first);
        return;
    }
    basic_string_init(pbstr_first);
    basic_string_init_elem(pbstr_second, 10, 0);
    _type_copy_basic_string(pbstr_first, pbstr_second, &b_output);
    assert_true(basic_string_equal(pbstr_first, pbstr_second));
    assert_true(b_output);
    basic_string_destroy(pbstr_first);
    basic_string_destroy(pbstr_second);
}

/*
 * test _type_less_basic_string
 */
UT_CASE_DEFINATION(_type_less_basic_string)
void test__type_less_basic_string__null_first(void** state)
{
    basic_string_t* pbstr_second = NULL;
    bool_t b_output = false;
    
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    basic_string_init(pbstr_second);
    expect_assert_failure(_type_less_basic_string(NULL, pbstr_second, &b_output));
    basic_string_destroy(pbstr_second);
}

void test__type_less_basic_string__null_second(void** state)
{
    basic_string_t* pbstr_first = NULL;
    bool_t b_output = false;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(pbstr_first);
        return;
    }
    basic_string_init(pbstr_first);
    expect_assert_failure(_type_less_basic_string(pbstr_first, NULL, &b_output));
    basic_string_destroy(pbstr_first);
}

void test__type_less_basic_string__null_output(void** state)
{
    basic_string_t* pbstr_first = NULL;
    basic_string_t* pbstr_second = NULL;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        basic_string_destroy(pbstr_first);
        return;
    }
    basic_string_init(pbstr_first);
    basic_string_init(pbstr_second);
    expect_assert_failure(_type_less_basic_string(pbstr_first, pbstr_second, NULL));
    basic_string_destroy(pbstr_first);
    basic_string_destroy(pbstr_second);
}

void test__type_less_basic_string__less(void** state)
{
    basic_string_t* pbstr_first = NULL;
    basic_string_t* pbstr_second = NULL;
    bool_t b_output = false;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        basic_string_destroy(pbstr_first);
        return;
    }
    basic_string_init(pbstr_first);
    basic_string_init_elem(pbstr_second, 10, 0);
    _type_less_basic_string(pbstr_first, pbstr_second, &b_output);
    assert_true(b_output);
    basic_string_destroy(pbstr_first);
    basic_string_destroy(pbstr_second);
}

void test__type_less_basic_string__equal(void** state)
{
    basic_string_t* pbstr_first = NULL;
    basic_string_t* pbstr_second = NULL;
    bool_t b_output = false;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        basic_string_destroy(pbstr_first);
        return;
    }
    basic_string_init_elem(pbstr_first, 10, 0);
    basic_string_init_elem(pbstr_second, 10, 0);
    _type_less_basic_string(pbstr_first, pbstr_second, &b_output);
    assert_true(basic_string_equal(pbstr_first, pbstr_second));
    assert_false(b_output);
    basic_string_destroy(pbstr_first);
    basic_string_destroy(pbstr_second);
}

void test__type_less_basic_string__greater(void** state)
{
    basic_string_t* pbstr_first = NULL;
    basic_string_t* pbstr_second = NULL;
    bool_t b_output = false;
    if ((pbstr_first = create_basic_string(int)) == NULL) {
        assert_true(false);
        return;
    }
    if ((pbstr_second = create_basic_string(int)) == NULL) {
        assert_true(false);
        basic_string_destroy(pbstr_first);
        return;
    }
    basic_string_init_elem(pbstr_first, 10, 0);
    basic_string_init_elem(pbstr_second, 4, 0);
    _type_less_basic_string(pbstr_first, pbstr_second, &b_output);
    assert_true(basic_string_size(pbstr_first) == 10);
    assert_true(basic_string_size(pbstr_second) == 4);
    assert_false(b_output);
    basic_string_destroy(pbstr_first);
    basic_string_destroy(pbstr_second);
}

/*
 * test _type_destroy_basic_string
 */
UT_CASE_DEFINATION(_type_destroy_basic_string)
void test__type_destroy_basic_string__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_basic_string(NULL, &b_output));
}

void test__type_destroy_basic_string__null_output(void** state)
{
    basic_string_t* pbstr_input = create_basic_string(int);
    if (pbstr_input == NULL) {
        assert_true(false);
        return;
    }
    basic_string_init(pbstr_input);
    expect_assert_failure(_type_destroy_basic_string(pbstr_input, NULL));
    basic_string_destroy(pbstr_input);
}

void test__type_destroy_basic_string__ok(void** state)
{
    bool_t b_output = false;
    basic_string_t* pbstr_input = create_basic_string(int);
    if (pbstr_input == NULL) {
        assert_true(false);
        return;
    }
    basic_string_init_elem(pbstr_input, 10, 0);
    _type_destroy_basic_string(pbstr_input, &b_output);
    assert_true(b_output);
    free(pbstr_input);
}

#ifndef _MSC_VER
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
    _Bool b_input = false;
    expect_assert_failure(_type_init_bool(&b_input, NULL));
}

void test__type_init_bool__ok(void** state)
{
    _Bool b_input = true;
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
    _Bool b_second = true;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_bool(NULL, &b_second, &b_output));
}

void test__type_copy_bool__null_second(void** state)
{
    _Bool b_first = true;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_bool(&b_first, NULL, &b_output));
}

void test__type_copy_bool__null_output(void** state)
{
    _Bool b_first = true;
    _Bool b_second = false;
    expect_assert_failure(_type_copy_bool(&b_first, &b_second, NULL));
}

void test__type_copy_bool__ok(void** state)
{
    _Bool b_first = true;
    _Bool b_second = false;
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
    _Bool b_second = true;
    bool_t b_output = false;
    expect_assert_failure(_type_less_bool(NULL, &b_second, &b_output));
}

void test__type_less_bool__null_second(void** state)
{
    _Bool b_first = true;
    bool_t b_output = false;
    expect_assert_failure(_type_less_bool(&b_first, NULL, &b_output));
}

void test__type_less_bool__null_output(void** state)
{
    _Bool b_first = true;
    _Bool b_second = false;
    expect_assert_failure(_type_less_bool(&b_first, &b_second, NULL));
}

void test__type_less_bool__less(void** state)
{
    _Bool b_first = false;
    _Bool b_second = true;
    bool_t b_output = false;
    _type_less_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_true(b_second);
    assert_true(b_output);
}

void test__type_less_bool__equal(void** state)
{
    _Bool b_first = false;
    _Bool b_second = false;
    bool_t b_output = false;
    _type_less_bool(&b_first, &b_second, &b_output);
    assert_false(b_first);
    assert_false(b_second);
    assert_false(b_output);
}

void test__type_less_bool__greater(void** state)
{
    _Bool b_first = true;
    _Bool b_second = false;
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
    _Bool b_input = false;
    expect_assert_failure(_type_destroy_bool(&b_input, NULL));
}

void test__type_destroy_bool__ok(void** state)
{
    _Bool b_input = false;
    bool_t b_output = false;
    _type_destroy_bool(&b_input, &b_output);
    assert_false(b_input);
    assert_true(b_output);
}

/*
 * test _type_init_long_long
 */
UT_CASE_DEFINATION(_type_init_long_long)
void test__type_init_long_long__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_long_long(NULL, &b_output));
}

void test__type_init_long_long__null_output(void** state)
{
    long long ll_input = 10ll;
    expect_assert_failure(_type_init_long_long(&ll_input, NULL));
}

void test__type_init_long_long__ok(void** state)
{
    long long ll_input = 100ll;
    bool_t b_output = false;
    _type_init_long_long(&ll_input, &b_output);
    assert_true(b_output);
}

/*
 * test _type_copy_long_long
 */
UT_CASE_DEFINATION(_type_copy_long_long)
void test__type_copy_long_long__null_first(void** state)
{
    long long ll_second = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_long_long(NULL, &ll_second, &b_output));
}

void test__type_copy_long_long__null_second(void** state)
{
    long long ll_first = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_long_long(&ll_first, NULL, &b_output));
}

void test__type_copy_long_long__null_output(void** state)
{
    long long ll_first = 100ll;
    long long ll_second = 100ll;
    expect_assert_failure(_type_copy_long_long(&ll_first, &ll_second, NULL));
}

void test__type_copy_long_long__ok(void** state)
{
    long long ll_first = 100ll;
    long long ll_second = 19999ll;
    bool_t b_output = false;
    _type_copy_long_long(&ll_first, &ll_second, &b_output);
    assert_true(ll_first == 19999ll);
    assert_true(ll_second == 19999ll);
    assert_true(b_output);
}

/*
 * test _type_less_long_long
 */
UT_CASE_DEFINATION(_type_less_long_long)
void test__type_less_long_long__null_first(void** state)
{
    long long ll_second = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_less_long_long(NULL, &ll_second, &b_output));
}

void test__type_less_long_long__null_second(void** state)
{
    long long ll_first = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_less_long_long(&ll_first, NULL, &b_output));
}

void test__type_less_long_long__null_output(void** state)
{
    long long ll_first = 100ll;
    long long ll_second = 100ll;
    expect_assert_failure(_type_less_long_long(&ll_first, &ll_second, NULL));
}

void test__type_less_long_long__less(void** state)
{
    long long ll_first = -9923ll;
    long long ll_second = 100ll;
    bool_t b_output = false;
    _type_less_long_long(&ll_first, &ll_second, &b_output);
    assert_true(b_output);
}

void test__type_less_long_long__equal(void** state)
{
    long long ll_first = 199ll;
    long long ll_second = 199ll;
    bool_t b_output = false;
    _type_less_long_long(&ll_first, &ll_second, &b_output);
    assert_false(b_output);
}

void test__type_less_long_long__greater(void** state)
{
    long long ll_first = 100ll;
    long long ll_second = -19ll;
    bool_t b_output = false;
    _type_less_long_long(&ll_first, &ll_second, &b_output);
    assert_false(b_output);
}

/*
 * test _type_destroy_long_long
 */
UT_CASE_DEFINATION(_type_destroy_long_long)
void test__type_destroy_long_long__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_long_long(NULL, &b_output));
}

void test__type_destroy_long_long__null_output(void** state)
{
    long long ll_input = 100ll;
    expect_assert_failure(_type_destroy_long_long(&ll_input, NULL));
}

void test__type_destroy_long_long__ok(void** state)
{
    long long ll_input = 100ll;
    bool_t b_output = false;
    _type_destroy_long_long(&ll_input, &b_output);
    assert_true(b_output);
}

/*
 * test _type_init_ulong_long
 */
UT_CASE_DEFINATION(_type_init_ulong_long)
void test__type_init_ulong_long__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_init_ulong_long(NULL, &b_output));
}

void test__type_init_ulong_long__null_output(void** state)
{
    unsigned long long ull_input = 10ll;
    expect_assert_failure(_type_init_ulong_long(&ull_input, NULL));
}

void test__type_init_ulong_long__ok(void** state)
{
    unsigned long long ull_input = 100ll;
    bool_t b_output = false;
    _type_init_ulong_long(&ull_input, &b_output);
    assert_true(b_output);
}

/*
 * test _type_copy_ulong_long
 */
UT_CASE_DEFINATION(_type_copy_ulong_long)
void test__type_copy_ulong_long__null_first(void** state)
{
    unsigned long long ull_second = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_ulong_long(NULL, &ull_second, &b_output));
}

void test__type_copy_ulong_long__null_second(void** state)
{
    unsigned long long ull_first = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_copy_ulong_long(&ull_first, NULL, &b_output));
}

void test__type_copy_ulong_long__null_output(void** state)
{
    unsigned long long ull_first = 100ll;
    unsigned long long ull_second = 100ll;
    expect_assert_failure(_type_copy_ulong_long(&ull_first, &ull_second, NULL));
}

void test__type_copy_ulong_long__ok(void** state)
{
    unsigned long long ull_first = 100ll;
    unsigned long long ull_second = 19999ll;
    bool_t b_output = false;
    _type_copy_ulong_long(&ull_first, &ull_second, &b_output);
    assert_true(ull_first == 19999ll);
    assert_true(ull_second == 19999ll);
    assert_true(b_output);
}

/*
 * test _type_less_ulong_long
 */
UT_CASE_DEFINATION(_type_less_ulong_long)
void test__type_less_ulong_long__null_first(void** state)
{
    unsigned long long ull_second = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_less_ulong_long(NULL, &ull_second, &b_output));
}

void test__type_less_ulong_long__null_second(void** state)
{
    unsigned long long ull_first = 100ll;
    bool_t b_output = false;
    expect_assert_failure(_type_less_ulong_long(&ull_first, NULL, &b_output));
}

void test__type_less_ulong_long__null_output(void** state)
{
    unsigned long long ull_first = 100ll;
    unsigned long long ull_second = 100ll;
    expect_assert_failure(_type_less_ulong_long(&ull_first, &ull_second, NULL));
}

void test__type_less_ulong_long__less(void** state)
{
    unsigned long long ull_first = 9923ll;
    unsigned long long ull_second = 11111100ll;
    bool_t b_output = false;
    _type_less_ulong_long(&ull_first, &ull_second, &b_output);
    assert_true(b_output);
}

void test__type_less_ulong_long__equal(void** state)
{
    unsigned long long ull_first = 199ll;
    unsigned long long ull_second = 199ll;
    bool_t b_output = false;
    _type_less_ulong_long(&ull_first, &ull_second, &b_output);
    assert_false(b_output);
}

void test__type_less_ulong_long__greater(void** state)
{
    unsigned long long ull_first = 100ll;
    unsigned long long ull_second = 19ll;
    bool_t b_output = false;
    _type_less_ulong_long(&ull_first, &ull_second, &b_output);
    assert_false(b_output);
}

/*
 * test _type_destroy_ulong_long
 */
UT_CASE_DEFINATION(_type_destroy_ulong_long)
void test__type_destroy_ulong_long__null_input(void** state)
{
    bool_t b_output = false;
    expect_assert_failure(_type_destroy_ulong_long(NULL, &b_output));
}

void test__type_destroy_ulong_long__null_output(void** state)
{
    unsigned long long ull_input = 100ll;
    expect_assert_failure(_type_destroy_ulong_long(&ull_input, NULL));
}

void test__type_destroy_ulong_long__ok(void** state)
{
    unsigned long long ull_input = 100ll;
    bool_t b_output = false;
    _type_destroy_ulong_long(&ull_input, &b_output);
    assert_true(b_output);
}
#endif
