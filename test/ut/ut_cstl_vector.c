#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_vector.h"

UT_SUIT_DEFINATION(cstl_vector, vector_init)

/*
 * test vector_init
 */
UT_CASE_DEFINATION(vector_init)
void test_vector_init__null_vector_container(void** state)
{
    expect_assert_failure(vector_init(NULL));
}

void test_vector_init__non_created(void** state)
{
    vector_t vec;
    vec._pc_start = (char*)0x887;
    expect_assert_failure(vector_init(&vec));
}

void test_vector_init__successfully_c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_init__successfully_cstl_builtin(void** state)
{
    vector_t* pvec = create_vector(vector_t<int>);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_init__successfully_cstr(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_init__successfully_user_defined(void** state)
{
    typedef struct _tagtest_vector_init__successfully_user_defined
    {
        int n_elem;
    }_test_vector_init__successfully_user_defined_t;
    vector_t* pvec = NULL;

    type_register(_test_vector_init__successfully_user_defined_t, NULL, NULL, NULL, NULL);

    pvec = create_vector(_test_vector_init__successfully_user_defined_t);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

/*
 * test vector_init_n
 */
UT_CASE_DEFINATION(vector_init_n)
void test_vector_init_n__null_vector_container(void** state)
{
    expect_assert_failure(vector_init_n(NULL, 10));
}

void test_vector_init_n__non_created(void** state)
{
    vector_t vec;
    vec._pc_finish = (char*)0x234;
    expect_assert_failure(vector_init_n(&vec, 10));
}

void test_vector_init_n__successfully_0(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 0);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_init_n__successfully_c_builtin(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_init_n__successfully_cstr(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(char*);

    vector_init_n(pvec, 20);
    assert_true(vector_size(pvec) == 20);
    assert_true(vector_capacity(pvec) == 36);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec, i), "") == 0);
    }

    vector_destroy(pvec);
}

void test_vector_init_n__successfully_cstl_builtin(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(vector_t<int>);

    vector_init_n(pvec, 40);
    assert_true(vector_size(pvec) == 40);
    assert_true(vector_capacity(pvec) == 60);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(_vector_is_inited((vector_t*)vector_at(pvec, i)));
    }

    vector_destroy(pvec);
}

void test_vector_init_n__successfully_user_defined(void** state)
{
    typedef struct _tag_test_vector_init_n__successfully_user_defined
    {
        int n_elem;
    }_test_vector_init_n__successfully_user_defined_t;

    _test_vector_init_n__successfully_user_defined_t t_elem;
    size_t i = 0;
    vector_t* pvec = NULL;

    type_register(_test_vector_init_n__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(_test_vector_init_n__successfully_user_defined_t);

    vector_init_n(pvec, 160);
    assert_true(vector_size(pvec) == 160);
    assert_true(vector_capacity(pvec) == 240);
    memset(&t_elem, 0x00, sizeof(t_elem));
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(memcmp((_test_vector_init_n__successfully_user_defined_t*)vector_at(pvec, i), &t_elem, sizeof(t_elem)) == 0);
    }

    vector_destroy(pvec);
}

