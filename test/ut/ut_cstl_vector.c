#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"
#include "cstl/clist.h"

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
    vec._pby_start = (_byte_t*)0x887;
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
    vec._pby_finish = (_byte_t*)0x234;
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

/*
 * test vector_init_copy
 */
UT_CASE_DEFINATION(vector_init_copy)
void test_vector_init_copy__null_dest(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_init_copy(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_init_copy__null_src(void** state)
{
    vector_t* pvec = create_vector(int);

    expect_assert_failure(vector_init_copy(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_init_copy__non_create_dest(void** state)
{
    vector_t vec;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    vec._t_typeinfo._pt_type = NULL;
    expect_assert_failure(vector_init_copy(&vec, pvec));

    vector_destroy(pvec);
}

void test_vector_init_copy__non_inited_src(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    pvec_src->_pby_finish = (_byte_t*)0x732;
    expect_assert_failure(vector_init_copy(pvec_dest, pvec_src));

    pvec_src->_pby_finish = NULL;
    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__not_same_type(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(double);
    vector_init(pvec_src);

    expect_assert_failure(vector_init_copy(pvec_dest, pvec_src));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_c_builtin_empty(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec_src);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 0);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_c_builtin_little(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 10, 2010);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 2010);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_c_builtin_huge(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1000, 2010);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 2010);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_cstr_empty(void** state)
{
    vector_t* pvec_dest = create_vector(char*);
    vector_t* pvec_src = create_vector(char*);
    vector_init(pvec_src);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 0);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_cstr_little(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(char*);
    vector_t* pvec_src = create_vector(char*);
    vector_init_elem(pvec_src, 19, "c-string");

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 35);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec_dest, i), "c-string") == 0);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_cstr_huge(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(char*);
    vector_t* pvec_src = create_vector(char*);
    vector_init_elem(pvec_src, 19000, "c-string");

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 28500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec_dest, i), "c-string") == 0);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_cstl_builtin_empty(void** state)
{
    vector_t* pvec_dest = create_vector(vector_t<int>);
    vector_t* pvec_src = create_vector(vector_t<int>);
    vector_t* pvec_elem = create_vector(int);
    vector_init_elem(pvec_elem, 23, 21234);
    vector_init(pvec_src);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 0);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
    vector_destroy(pvec_elem);
}

void test_vector_init_copy__successfully_cstl_builtin_little(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(vector_t<int>);
    vector_t* pvec_src = create_vector(vector_t<int>);
    vector_t* pvec_elem = create_vector(int);
    vector_init_elem(pvec_elem, 23, 21234);
    vector_init_elem(pvec_src, 32, pvec_elem);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 48);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(vector_equal((vector_t*)vector_at(pvec_dest, i), pvec_elem));
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
    vector_destroy(pvec_elem);
}

void test_vector_init_copy__successfully_cstl_builtin_huge(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(vector_t<int>);
    vector_t* pvec_src = create_vector(vector_t<int>);
    vector_t* pvec_elem = create_vector(int);
    vector_init_elem(pvec_elem, 23, 21234);
    vector_init_elem(pvec_src, 3702, pvec_elem);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 5553);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(vector_equal((vector_t*)vector_at(pvec_dest, i), pvec_elem));
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
    vector_destroy(pvec_elem);
}

typedef struct _tag_test_vector_init_copy__successfully_user_define
{
    int n_elem;
}_test_vector_init_copy__successfully_user_define_t;
void test_vector_init_copy__successfully_user_define_empty(void** state)
{
    vector_t* pvec_dest = NULL;
    vector_t* pvec_src = NULL;
    type_register(_test_vector_init_copy__successfully_user_define_t, NULL, NULL, NULL, NULL);
    pvec_dest = create_vector(_test_vector_init_copy__successfully_user_define_t);
    pvec_src = create_vector(_test_vector_init_copy__successfully_user_define_t);
    vector_init(pvec_src);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 0);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_user_define_little(void** state)
{
    size_t i = 0;
    _test_vector_init_copy__successfully_user_define_t t_user;
    vector_t* pvec_dest = create_vector(_test_vector_init_copy__successfully_user_define_t);
    vector_t* pvec_src = create_vector(_test_vector_init_copy__successfully_user_define_t);
    t_user.n_elem = 100;
    vector_init_elem(pvec_src, 17, &t_user);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 33);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(memcmp(
            (_test_vector_init_copy__successfully_user_define_t*)vector_at(pvec_dest, i), &t_user, sizeof(t_user)) == 0);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy__successfully_user_define_huge(void** state)
{
    size_t i = 0;
    _test_vector_init_copy__successfully_user_define_t t_user;
    vector_t* pvec_dest = create_vector(_test_vector_init_copy__successfully_user_define_t);
    vector_t* pvec_src = create_vector(_test_vector_init_copy__successfully_user_define_t);
    t_user.n_elem = 100;
    vector_init_elem(pvec_src, 11117, &t_user);

    vector_init_copy(pvec_dest, pvec_src);
    assert_true(vector_size(pvec_dest) == vector_size(pvec_src));
    assert_true(vector_capacity(pvec_dest) == 16675);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(memcmp(
            (_test_vector_init_copy__successfully_user_define_t*)vector_at(pvec_dest, i), &t_user, sizeof(t_user)) == 0);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

/*
 * test vector_init_copy_range
 */
UT_CASE_DEFINATION(vector_init_copy_range)
void test_vector_init_copy_range__null_dest(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init(pvec);
    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);

    expect_assert_failure(vector_init_copy_range(NULL, it_begin, it_end));

    vector_destroy(pvec);
}

void test_vector_init_copy_range__invalid_begin_iterator(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init(pvec_src);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    it_begin._t_iteratortype = 23445;
    expect_assert_failure(vector_init_copy_range(pvec_dest, it_begin, it_end));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__invalid_end_iterator(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init(pvec_src);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    it_end._t_containertype = 9999;
    expect_assert_failure(vector_init_copy_range(pvec_dest, it_begin, it_end));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__invalid_range(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init_elem(pvec_src, 19, 323);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    expect_assert_failure(vector_init_copy_range(pvec_dest, it_end, it_begin));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__not_same_type(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(double);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init_elem(pvec_src, 19, 323);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    expect_assert_failure(vector_init_copy_range(pvec_dest, it_begin, it_end));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__successfully_empty_range(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init_elem(pvec_src, 19, 323);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    vector_init_copy_range(pvec_dest, it_begin, it_begin);
    assert_true(vector_size(pvec_dest) == 0);
    assert_true(vector_capacity(pvec_dest) == 0);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__successfully_c_builtin(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init(pvec_src);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec_src, i);
    }
    it_begin = iterator_next_n(vector_begin(pvec_src), 3);
    it_end = iterator_next_n(it_begin, 5);

    vector_init_copy_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 21);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == i + 3);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__successfully_cstr(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(char*);
    vector_t* pvec_src = create_vector(char*);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init_elem(pvec_src, 100, "abcdefg");
    it_begin = vector_begin(pvec_src);
    it_end = iterator_next_n(it_begin, 10);

    vector_init_copy_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec_dest, i), "abcdefg") == 0);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__successfully_cstl_builtin(void** state)
{
    size_t i = 0;
    vector_t* pvec_dest = create_vector(vector_t<int>);
    vector_t* pvec_src = create_vector(vector_t<int>);
    vector_t* pvec_elem = create_vector(int);
    vector_iterator_t it_begin;
    vector_iterator_t it_end;

    vector_init_elem(pvec_elem, 18, 23);
    vector_init_elem(pvec_src, 1004, pvec_elem);
    it_begin = iterator_next_n(vector_begin(pvec_src), 100);
    it_end = vector_end(pvec_src);

    vector_init_copy_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 1356);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(vector_equal((vector_t*)vector_at(pvec_dest, i), pvec_elem));
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
    vector_destroy(pvec_elem);
}

void test_vector_init_copy_range__successfully_user_define(void** state)
{
    typedef struct _tag_test_vector_init_copy_range__successfully_user_define
    {
        int n_elem;
    }_test_vector_init_copy_range__successfully_user_define_t;

    size_t i = 0;
    vector_t* pvec_dest = NULL;
    vector_t* pvec_src = NULL;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    _test_vector_init_copy_range__successfully_user_define_t t_user;

    type_register(_test_vector_init_copy_range__successfully_user_define_t, NULL, NULL, NULL, NULL);

    pvec_dest = create_vector(_test_vector_init_copy_range__successfully_user_define_t);
    pvec_src = create_vector(_test_vector_init_copy_range__successfully_user_define_t);

    t_user.n_elem = 28743;
    vector_init_elem(pvec_src, 10000, &t_user);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    vector_init_copy_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 15000);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(memcmp((_test_vector_init_copy_range__successfully_user_define_t*)vector_at(pvec_dest, i),
            &t_user, sizeof(t_user)) == 0);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_init_copy_range__other_container_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    size_t i = 0;

    list_init_elem(plist, 10, 100);
    vector_init_copy_range(pvec, list_begin(plist), list_end(plist));
    assert_true(vector_size(pvec) == 10);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test vector_init_copy_array
 */
UT_CASE_DEFINATION(vector_init_copy_array)
void test_vector_init_copy_array__null_dest(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(vector_init_copy_array(NULL, an_array, 10));
}

void test_vector_init_copy_array__invalid_array(void** state)
{
    vector_t* pvec_dest = create_vector(int);

    expect_assert_failure(vector_init_copy_array(pvec_dest, NULL, 10));

    vector_destroy(pvec_dest);
}

void test_vector_init_copy_array__successfully_empty_array(void** state)
{
    int an_array[10] = {0};
    vector_t* pvec_dest = create_vector(int);

    vector_init_copy_array(pvec_dest, an_array, 0);
    assert_true(vector_size(pvec_dest) == 0);
    assert_true(vector_capacity(pvec_dest) == 0);

    vector_destroy(pvec_dest);
}

void test_vector_init_copy_array__successfully_c_builtin(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);

    for(i = 0; i < 10; ++i)
    {
        an_array[i] = i;
    }

    vector_init_copy_array(pvec_dest, an_array + 3, 5);
    assert_true(vector_size(pvec_dest) == 5);
    assert_true(vector_capacity(pvec_dest) == 21);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == i + 3);
    }

    vector_destroy(pvec_dest);
}

void test_vector_init_copy_array__successfully_cstr(void** state)
{
    const char* as_array[10] = {NULL};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(char*);

    for (i = 0; i < 10; ++i) {
        as_array[i] = "abcdefg";
    }
    vector_init_copy_array(pvec_dest, as_array, 10);
    assert_true(vector_size(pvec_dest) == 10);
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest)-1; ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec_dest, i), "abcdefg") == 0);
    }

    vector_destroy(pvec_dest);
}

void test_vector_init_copy_array__successfully_cstl_builtin(void** state)
{
    vector_t* apvec_array[1004] = {NULL};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(vector_t<int>);

    for (i = 0; i < 1004; ++i) {
        apvec_array[i] = create_vector(int);
        vector_init_elem(apvec_array[i], i, i);
    }
    vector_init_copy_array(pvec_dest, apvec_array + 100, 904);
    assert_true(vector_size(pvec_dest) == 904);
    assert_true(vector_capacity(pvec_dest) == 1356);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(vector_equal((vector_t*)vector_at(pvec_dest, i), apvec_array[i + 100]));
    }

    vector_destroy(pvec_dest);
    for (i = 0; i < 1004; ++i) {
        vector_destroy(apvec_array[i]);
    }
}

void test_vector_init_copy_array__successfully_user_define(void** state)
{
    typedef struct _tag_test_vector_init_copy_array__successfully_user_define
    {
        int n_elem;
    }_test_vector_init_copy_array__successfully_user_define_t;

    _test_vector_init_copy_array__successfully_user_define_t* apt_array[10000] = {NULL};
    size_t i = 0;
    vector_t* pvec_dest = NULL;

    type_register(_test_vector_init_copy_array__successfully_user_define_t, NULL, NULL, NULL, NULL);

    pvec_dest = create_vector(_test_vector_init_copy_array__successfully_user_define_t);

    for (i = 0; i < 10000; ++i) {
        apt_array[i] = malloc(sizeof(_test_vector_init_copy_array__successfully_user_define_t));
        apt_array[i]->n_elem = i;
    }
    vector_init_copy_array(pvec_dest, apt_array, 10000);
    assert_true(vector_size(pvec_dest) == 10000);
    assert_true(vector_capacity(pvec_dest) == 15000);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(memcmp((_test_vector_init_copy_array__successfully_user_define_t*)vector_at(pvec_dest, i),
            apt_array[i], sizeof(_test_vector_init_copy_array__successfully_user_define_t)) == 0);
    }

    vector_destroy(pvec_dest);
    for (i = 0; i < 10000; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test vector_destroy
 */
UT_CASE_DEFINATION(vector_destroy)
void test_vector_destroy__null_vector_container(void** state)
{
    expect_assert_failure(vector_destroy(NULL));
}

void test_vector_destroy__non_created(void** state)
{
    vector_t vec;
    vec._pby_start = (_byte_t*)0x37;

    expect_assert_failure(vector_destroy(&vec));
}

void test_vector_destroy__created_non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_destroy(pvec);
}

void test_vector_destroy__inited_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    vector_destroy(pvec);
}

void test_vector_destroy__inited_non_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 199);

    vector_destroy(pvec);
}

/*
 * test vector_size
 */
UT_CASE_DEFINATION(vector_size)
void test_vector_size__null_vector_container(void** state)
{
    expect_assert_failure(vector_size(NULL));
}

void test_vector_size__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_start = (_byte_t*)0x887;
    expect_assert_failure(vector_size(pvec));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test_vector_size__successfully_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_size__successfully_non_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 45);

    assert_true(vector_size(pvec) == 45);

    vector_destroy(pvec);
}

/*
 * test vector_empty
 */
UT_CASE_DEFINATION(vector_empty)
void test_vector_empty__null_vector_container(void** state)
{
    expect_assert_failure(vector_empty(NULL));
}

void test_vector_empty__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x34;
    expect_assert_failure(vector_empty(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_empty__successfully_empty(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(vector_empty(pvec));

    vector_destroy(pvec);
}

void test_vector_empty__successfully_non_empty(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 239);
    assert_false(vector_empty(pvec));

    vector_destroy(pvec);
}

/*
 * test vector_max_size
 */
UT_CASE_DEFINATION(vector_max_size)
void test_vector_max_size__null_vector_container(void** state)
{
    expect_assert_failure(vector_max_size(NULL));
}

void test_vector_max_size__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x783;
    expect_assert_failure(vector_max_size(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_max_size__successfully(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(vector_max_size(pvec) != 0);

    vector_destroy(pvec);
}

/*
 * test vector_capacity
 */
UT_CASE_DEFINATION(vector_capacity)
void test_vector_capacity__null_vector_container(void** state)
{
    expect_assert_failure(vector_capacity(NULL));
}

void test_vector_capacity__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_endofstorage = (_byte_t*)0x623;
    expect_assert_failure(vector_capacity(pvec));

    pvec->_pby_endofstorage = NULL;
    vector_destroy(pvec);
}

void test_vector_capacity__successfully_empty(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_capacity__successfully_little(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 3);
    assert_true(vector_capacity(pvec) == 19);

    vector_destroy(pvec);
}

void test_vector_capacity__successfully_huge(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 3983);
    assert_true(vector_capacity(pvec) == 5974);

    vector_destroy(pvec);
}

/*
 * test vector_reserve
 */
UT_CASE_DEFINATION(vector_reserve)
void test_vector_reserve__null_vector_container(void** state)
{
    expect_assert_failure(vector_reserve(NULL, 100));
}

void test_vector_reserve__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x34;
    expect_assert_failure(vector_reserve(pvec, 100));    

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_reserve__shrink(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 100);
    assert_true(vector_capacity(pvec) == 150);
    vector_reserve(pvec, 0);
    assert_true(vector_capacity(pvec) == 150);

    vector_destroy(pvec);
}

void test_vector_reserve__not_change(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 100);
    assert_true(vector_capacity(pvec) == 150);
    vector_reserve(pvec, 150);
    assert_true(vector_capacity(pvec) == 150);

    vector_destroy(pvec);
}

void test_vector_reserve__expand(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 100);
    assert_true(vector_capacity(pvec) == 150);
    vector_reserve(pvec, 850);
    assert_true(vector_capacity(pvec) == 850);

    vector_destroy(pvec);
}

/*
 * test vector_equal
 */
UT_CASE_DEFINATION(vector_equal)
void test_vector_equal__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_equal(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_equal__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_equal(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_equal__non_inited_first(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_second);
    pvec_first->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_equal(pvec_first, pvec_second));

    pvec_first->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__non_inited_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    pvec_second->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_equal(pvec_first, pvec_second));

    pvec_second->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);

    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(vector_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__same_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_equal(pvec, pvec));

    vector_destroy(pvec);
}

void test_vector_equal__size_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init_n(pvec_second, 48);
    assert_false(vector_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__size_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_n(pvec_first, 233);
    vector_init_n(pvec_second, 48);
    assert_false(vector_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__size_equal_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_true(vector_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__size_equal_elem_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 4545);
    assert_false(vector_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__size_equal_elem_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 45);
    assert_false(vector_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_equal__size_equal_elem_equal(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 100);
    assert_true(vector_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test vector_not_equal
 */
UT_CASE_DEFINATION(vector_not_equal)
void test_vector_not_equal__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_not_equal(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_not_equal__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_not_equal(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_not_equal__non_inited_first(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_second);
    pvec_first->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_not_equal(pvec_first, pvec_second));

    pvec_first->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__non_inited_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    pvec_second->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_not_equal(pvec_first, pvec_second));

    pvec_second->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);

    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(vector_not_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__same_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_false(vector_not_equal(pvec, pvec));

    vector_destroy(pvec);
}

void test_vector_not_equal__size_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init_n(pvec_second, 48);
    assert_true(vector_not_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__size_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_n(pvec_first, 233);
    vector_init_n(pvec_second, 48);
    assert_true(vector_not_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__size_equal_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_false(vector_not_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 4545);
    assert_true(vector_not_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 45);
    assert_true(vector_not_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_not_equal__size_equal_elem_equal(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 100);
    assert_false(vector_not_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test vector_less
 */
UT_CASE_DEFINATION(vector_less)
void test_vector_less__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_less(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_less__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_less(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_less__non_inited_first(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_second);
    pvec_first->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_less(pvec_first, pvec_second));

    pvec_first->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__non_inited_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    pvec_second->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_less(pvec_first, pvec_second));

    pvec_second->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);

    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(vector_less(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__same_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_false(vector_less(pvec, pvec));

    vector_destroy(pvec);
}

void test_vector_less__size_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init_n(pvec_second, 48);
    assert_true(vector_less(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__size_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_n(pvec_first, 233);
    vector_init_n(pvec_second, 48);
    assert_false(vector_less(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__size_equal_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_false(vector_less(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__size_equal_elem_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 4545);
    assert_true(vector_less(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__size_equal_elem_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 45);
    assert_false(vector_less(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less__size_equal_elem_equal(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 100);
    assert_false(vector_less(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test vector_less_equal
 */
UT_CASE_DEFINATION(vector_less_equal)
void test_vector_less_equal__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_less_equal(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_less_equal__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_less_equal(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_less_equal__non_inited_first(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_second);
    pvec_first->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_less_equal(pvec_first, pvec_second));

    pvec_first->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__non_inited_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    pvec_second->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_less_equal(pvec_first, pvec_second));

    pvec_second->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);

    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(vector_less_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__same_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_less_equal(pvec, pvec));

    vector_destroy(pvec);
}

void test_vector_less_equal__size_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init_n(pvec_second, 48);
    assert_true(vector_less_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__size_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_n(pvec_first, 233);
    vector_init_n(pvec_second, 48);
    assert_false(vector_less_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__size_equal_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_true(vector_less_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 4545);
    assert_true(vector_less_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 45);
    assert_false(vector_less_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_less_equal__size_equal_elem_equal(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 100);
    assert_true(vector_less_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test vector_greater
 */
UT_CASE_DEFINATION(vector_greater)
void test_vector_greater__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_greater(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_greater__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_greater(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_greater__non_inited_first(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_second);
    pvec_first->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_greater(pvec_first, pvec_second));

    pvec_first->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__non_inited_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    pvec_second->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_greater(pvec_first, pvec_second));

    pvec_second->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);

    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(vector_greater(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__same_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_false(vector_greater(pvec, pvec));

    vector_destroy(pvec);
}

void test_vector_greater__size_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init_n(pvec_second, 48);
    assert_false(vector_greater(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__size_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_n(pvec_first, 233);
    vector_init_n(pvec_second, 48);
    assert_true(vector_greater(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__size_equal_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_false(vector_greater(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__size_equal_elem_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 4545);
    assert_false(vector_greater(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__size_equal_elem_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 45);
    assert_true(vector_greater(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater__size_equal_elem_equal(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 100);
    assert_false(vector_greater(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test vector_greater_equal
 */
UT_CASE_DEFINATION(vector_greater_equal)
void test_vector_greater_equal__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_greater_equal(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_greater_equal__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_greater_equal(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_greater_equal__non_inited_first(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_second);
    pvec_first->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_greater_equal(pvec_first, pvec_second));

    pvec_first->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__non_inited_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    pvec_second->_pby_finish = (_byte_t*)0x73;
    expect_assert_failure(vector_greater_equal(pvec_first, pvec_second));

    pvec_second->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);

    vector_init(pvec_first);
    vector_init(pvec_second);
    expect_assert_failure(vector_greater_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__same_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_greater_equal(pvec, pvec));

    vector_destroy(pvec);
}

void test_vector_greater_equal__size_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init_n(pvec_second, 48);
    assert_false(vector_greater_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__size_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_n(pvec_first, 233);
    vector_init_n(pvec_second, 48);
    assert_true(vector_greater_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__size_equal_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init(pvec_second);
    assert_true(vector_greater_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 4545);
    assert_false(vector_greater_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 45);
    assert_true(vector_greater_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_greater_equal__size_equal_elem_equal(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init_elem(pvec_first, 10, 100);
    vector_init_elem(pvec_second, 10, 100);
    assert_true(vector_greater_equal(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test vector_assign
 */
UT_CASE_DEFINATION(vector_assign)
void test_vector_assign__null_dest(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_assign(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_assign__null_src(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_assign(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_assign__non_inited_dest(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init(pvec_src);
    pvec_dest->_pby_finish = (_byte_t*)0x22;

    expect_assert_failure(vector_assign(pvec_dest, pvec_src));

    pvec_dest->_pby_finish = NULL;
    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__non_inited_src(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init(pvec_dest);
    pvec_src->_pby_finish = (_byte_t*)0x22;

    expect_assert_failure(vector_assign(pvec_dest, pvec_src));

    pvec_src->_pby_finish = NULL;
    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__not_same_type(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(double);

    vector_init(pvec_dest);
    vector_init(pvec_src);

    expect_assert_failure(vector_assign(pvec_dest, pvec_src));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__same_container(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);

    vector_assign(pvec, pvec);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_assign__0_assign_0(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init(pvec_dest);
    vector_init(pvec_src);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 0);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__0_assign_10(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init(pvec_dest);
    vector_init_n(pvec_src, 10);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 26);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__0_assign_1000(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init(pvec_dest);
    vector_init_n(pvec_src, 1000);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 1500);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__10_assign_0(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_n(pvec_dest, 10);
    vector_init(pvec_src);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 26);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__10_assign_10_vector_equal(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_n(pvec_dest, 10);
    vector_init_n(pvec_src, 10);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 26);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__10_assign_10_vector_not_equal(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_elem(pvec_dest, 10, 100);
    vector_init_n(pvec_src, 10);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 26);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__10_assign_1000(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_elem(pvec_dest, 10, 100);
    vector_init_n(pvec_src, 1000);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 1500);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__1000_assign_0(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_elem(pvec_dest, 1000, 100);
    vector_init(pvec_src);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 1500);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__1000_assign_10(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_elem(pvec_dest, 1000, 100);
    vector_init_n(pvec_src, 10);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 1500);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__1000_assign_1010(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_elem(pvec_dest, 1000, 100);
    vector_init_n(pvec_src, 1010);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 1500);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign__1000_assign_1810(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);

    vector_init_elem(pvec_dest, 1000, 100);
    vector_init_n(pvec_src, 1810);

    vector_assign(pvec_dest, pvec_src);
    assert_true(vector_equal(pvec_dest, pvec_src));
    assert_true(vector_capacity(pvec_dest) == 2715);

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

/*
 * test vector_assign_range
 */
UT_CASE_DEFINATION(vector_assign_range)
void test_vector_assign_range__null_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_assign_range(NULL, vector_begin(pvec), vector_end(pvec)));

    vector_destroy(pvec);
}

void test_vector_assign_range__non_inited(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec_src);

    pvec_dest->_pby_start = (_byte_t*)0x354;
    expect_assert_failure(vector_assign_range(pvec_dest, vector_begin(pvec_src), vector_end(pvec_src)));

    pvec_dest->_pby_start = NULL;
    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__invalid_it_begin(void** state)
{
    vector_iterator_t it_begin;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec_src);
    vector_init(pvec_dest);
    it_begin._t_iteratortype = 284;

    expect_assert_failure(vector_assign_range(pvec_dest, it_begin, vector_end(pvec_src)));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__invalid_it_end(void** state)
{
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec_src);
    vector_init(pvec_dest);
    it_end._t_iteratortype = 284;

    expect_assert_failure(vector_assign_range(pvec_dest, vector_begin(pvec_src), it_end));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__invalid_range(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_n(pvec_src, 12);
    vector_init(pvec_dest);

    expect_assert_failure(vector_assign_range(pvec_dest, vector_end(pvec_src), vector_begin(pvec_src)));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__invalid_range_not_same_type(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(double);
    vector_init_n(pvec_src, 12);
    vector_init(pvec_dest);

    expect_assert_failure(vector_assign_range(pvec_dest, vector_begin(pvec_src), vector_end(pvec_src)));

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__range_belong_to_vector(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_init(pvec_dest);

    vector_assign_range(pvec_dest, vector_begin(pvec_dest), vector_end(pvec_dest));

    vector_destroy(pvec_dest);
}

void test_vector_assign_range__0_assign_range_0(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1200, 100);
    vector_init(pvec_dest);

    it_begin = vector_begin(pvec_src);
    it_end = vector_begin(pvec_src);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 0);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__0_assign_range_10(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1200, 100);
    vector_init(pvec_dest);

    it_begin = vector_begin(pvec_src);
    it_end = iterator_next_n(it_begin, 10);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__0_assign_range_1000(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1200, 100);
    vector_init(pvec_dest);

    it_begin = vector_begin(pvec_src);
    it_end = iterator_next_n(it_begin, 1000);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__10_assign_range_0(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1200, 100);
    vector_init_elem(pvec_dest, 10, 100);

    it_begin = iterator_next_n(vector_begin(pvec_src), 111);
    it_end = it_begin;
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__10_assign_range_10_same_elem(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1200, 100);
    vector_init_elem(pvec_dest, 10, 100);

    it_begin = iterator_next_n(vector_begin(pvec_src), 111);
    it_end = iterator_next_n(it_begin, 10);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__10_assign_range_10_not_same_elem(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1200, 100);
    vector_init_elem(pvec_dest, 10, 0);

    it_begin = iterator_next_n(vector_begin(pvec_src), 111);
    it_end = iterator_next_n(it_begin, 10);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__10_assign_range_1000(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1200, 100);
    vector_init_elem(pvec_dest, 10, 0);

    it_begin = iterator_next_n(vector_begin(pvec_src), 111);
    it_end = iterator_next_n(it_begin, 1000);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__1000_assign_range_0(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1700, 100);
    vector_init_elem(pvec_dest, 1000, 0);

    it_begin = vector_begin(pvec_src);
    it_end = it_begin;
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__1000_assign_range_10(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1700, 100);
    vector_init_elem(pvec_dest, 1000, 0);

    it_begin = vector_begin(pvec_src);
    it_end = iterator_next_n(it_begin, 10);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__1000_assign_range_1700(void** state)
{
    size_t i = 0;
    vector_iterator_t it_begin;
    vector_iterator_t it_end;
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1700, 100);
    vector_init_elem(pvec_dest, 1000, 0);

    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);
    vector_assign_range(pvec_dest, it_begin, it_end);
    assert_true(vector_size(pvec_dest) == iterator_distance(it_begin, it_end));
    assert_true(vector_capacity(pvec_dest) == 2550);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
    vector_destroy(pvec_src);
}

void test_vector_assign_range__other_container_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    size_t i = 0;

    vector_init_n(pvec, 10);
    list_init_elem(plist, 100, 100);
    assert_true(vector_size(pvec) == 10);
    vector_assign_range(pvec, list_begin(plist), list_end(plist));
    assert_true(vector_size(pvec) == 100);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test vector_assign_array
 */
UT_CASE_DEFINATION(vector_assign_array)
void test_vector_assign_array__null_vector_container(void** state)
{
    int an_array[10] = {0};
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_assign_array(NULL, an_array, 10));

    vector_destroy(pvec);
}

void test_vector_assign_array__non_inited(void** state)
{
    int an_array[10] = {0};
    vector_t* pvec_dest = create_vector(int);

    pvec_dest->_pby_start = (_byte_t*)0x354;
    expect_assert_failure(vector_assign_array(pvec_dest, an_array, 10));

    pvec_dest->_pby_start = NULL;
    vector_destroy(pvec_dest);
}

void test_vector_assign_array__invalid_array(void** state)
{
    vector_t* pvec_dest = create_vector(int);
    vector_init(pvec_dest);

    expect_assert_failure(vector_assign_array(pvec_dest, NULL, 10));

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__0_assign_array_0(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init(pvec_dest);

    vector_assign_array(pvec_dest, an_array, 0);
    assert_true(vector_size(pvec_dest) == 0);
    assert_true(vector_capacity(pvec_dest) == 0);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__0_assign_array_10(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init(pvec_dest);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    vector_assign_array(pvec_dest, an_array, 10);
    assert_true(vector_size(pvec_dest) == 10);
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__0_assign_array_1000(void** state)
{
    int an_array[1000] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init(pvec_dest);

    for (i = 0; i < 1000; ++i) {
        an_array[i] = 100;
    }
    vector_assign_array(pvec_dest, an_array, 1000);
    assert_true(vector_size(pvec_dest) == 1000);
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__10_assign_array_0(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init_elem(pvec_dest, 10, 100);

    vector_assign_array(pvec_dest, an_array, 0);
    assert_true(vector_size(pvec_dest) == 0);
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__10_assign_array_10_same_elem(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init_elem(pvec_dest, 10, 100);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    vector_assign_array(pvec_dest, an_array, 10);
    assert_true(vector_size(pvec_dest) == 10);
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__10_assign_array_10_not_same_elem(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init_elem(pvec_dest, 10, 0);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    vector_assign_array(pvec_dest, an_array, 10);
    assert_true(vector_size(pvec_dest) == 10);
    assert_true(vector_capacity(pvec_dest) == 26);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__10_assign_array_1000(void** state)
{
    int an_array[1000] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init_elem(pvec_dest, 10, 0);

    for (i = 0; i < 1000; ++i) {
        an_array[i] = 100;
    }
    vector_assign_array(pvec_dest, an_array, 1000);
    assert_true(vector_size(pvec_dest) == 1000);
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__1000_assign_array_0(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init_elem(pvec_dest, 1000, 0);

    vector_assign_array(pvec_dest, an_array, 0);
    assert_true(vector_size(pvec_dest) == 0);
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__1000_assign_array_10(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init_elem(pvec_dest, 1000, 0);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    vector_assign_array(pvec_dest, an_array, 10);
    assert_true(vector_size(pvec_dest) == 10);
    assert_true(vector_capacity(pvec_dest) == 1500);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__1000_assign_array_1700(void** state)
{
    int an_array[1700] = {0};
    size_t i = 0;
    vector_t* pvec_dest = create_vector(int);
    vector_init_elem(pvec_dest, 1000, 0);

    for (i = 0; i < 1700; ++i) {
        an_array[i] = 100;
    }
    vector_assign_array(pvec_dest, an_array, 1700);
    assert_true(vector_size(pvec_dest) == 1700);
    assert_true(vector_capacity(pvec_dest) == 2550);
    for(i = 0; i < vector_size(pvec_dest); ++i)
    {
        assert_true(*(int*)vector_at(pvec_dest, i) == 100);
    }

    vector_destroy(pvec_dest);
}

void test_vector_assign_array__cstr(void** state)
{
    const char* as_array[] = {
        "Linux", "abc", "xxxx", "damahou", "99999999", "maoxingren", "x", "yz"
    };
    vector_t* pvec = create_vector(char*);
    size_t i = 0;

    vector_init_n(pvec, 10);
    assert_true(vector_size(pvec) == 10);
    vector_assign_array(pvec, as_array, 8);
    assert_true(vector_size(pvec) == 8);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(strcmp((char*)vector_at(pvec, i), as_array[i]) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_assign_array__cstl(void** state)
{
    list_t* aplist_array[10] = {NULL};
    vector_t* pvec = create_vector(list_t<int>);
    size_t i = 0;

    for (i = 0; i < 10; ++i) {
        aplist_array[i] = create_list(int);
        list_init_elem(aplist_array[i], i, i);
    }
    vector_init(pvec);
    assert_true(vector_size(pvec) == 0);
    vector_assign_array(pvec, aplist_array, 10);
    assert_true(vector_size(pvec) == 10);
    for (i = 0; i < 10; ++i) {
        assert_true(list_equal(vector_at(pvec, i), aplist_array[i]));
    }

    vector_destroy(pvec);
    for (i = 0; i < 10; ++i) {
        list_destroy(aplist_array[i]);
    }
}

typedef struct _test_vector_assign_array__user_define {
    int n_elem;
}_test_vector_assign_array__user_define_t;
void test_vector_assign_array__user_define(void** state)
{
    _test_vector_assign_array__user_define_t* apt_array[10] = {NULL};
    vector_t* pvec = NULL;
    size_t i = 0;

    type_register(_test_vector_assign_array__user_define_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(_test_vector_assign_array__user_define_t);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_vector_assign_array__user_define_t));
        apt_array[i]->n_elem = i;
    }
    assert_true(vector_size(pvec) == 0);
    vector_assign_array(pvec, apt_array, 10);
    assert_true(vector_size(pvec) == 10);
    for (i = 0; i < 10; ++i) {
        assert_true(((_test_vector_assign_array__user_define_t*)vector_at(pvec, i))->n_elem == apt_array[i]->n_elem);
    }

    vector_destroy(pvec);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test vector_swap
 */
UT_CASE_DEFINATION(vector_swap)
void test_vector_swap__null_first(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(vector_swap(NULL, pvec));

    vector_destroy(pvec);
}

void test_vector_swap__null_second(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(vector_swap(pvec, NULL));

    vector_destroy(pvec);
}

void test_vector_swap__non_inited_first(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_second);
    pvec_first->_pby_finish = (_byte_t*)0x88;

    expect_assert_failure(vector_swap(pvec_first, pvec_second));

    pvec_first->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__non_inited_second(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    pvec_second->_pby_finish = (_byte_t*)0x88;

    expect_assert_failure(vector_swap(pvec_first, pvec_second));

    pvec_second->_pby_finish = NULL;
    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__not_same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);

    vector_init(pvec_first);
    vector_init(pvec_second);

    expect_assert_failure(vector_swap(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__vector_equal(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);

    vector_init(pvec_first);
    vector_init(pvec_second);

    vector_swap(pvec_first, pvec_second);

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__0_swap_10(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init(pvec_first);
    vector_init_elem(pvec_second, 10, 100);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__0_swap_1000(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init(pvec_first);
    vector_init_elem(pvec_second, 1000, 100);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__10_swap_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init_n(pvec_first, 10);
    vector_init(pvec_second);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__10_swap_10(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init_n(pvec_first, 10);
    vector_init_elem(pvec_second, 10, 100);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__10_swap_1000(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init_n(pvec_first, 10);
    vector_init_elem(pvec_second, 1000, 100);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__1000_swap_0(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init_n(pvec_first, 1000);
    vector_init_elem(pvec_second, 0, 100);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__1000_swap_10(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init_n(pvec_first, 1000);
    vector_init_elem(pvec_second, 10, 100);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test_vector_swap__1000_swap_1010(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    size_t t_firstsize = 0;
    size_t t_firstcapacity = 0;
    size_t t_secondsize = 0;
    size_t t_secondcapacity = 0;
    size_t i = 0;

    vector_init_n(pvec_first, 1000);
    vector_init_elem(pvec_second, 1010, 100);

    t_firstsize = vector_size(pvec_first);
    t_firstcapacity = vector_capacity(pvec_first);
    t_secondsize = vector_size(pvec_second);
    t_secondcapacity = vector_capacity(pvec_second);
    vector_swap(pvec_first, pvec_second);

    assert_true(vector_size(pvec_first) == t_secondsize);
    assert_true(vector_capacity(pvec_first) == t_secondcapacity);
    assert_true(vector_size(pvec_second) == t_firstsize);
    assert_true(vector_capacity(pvec_second) == t_firstcapacity);
    for(i = 0; i < vector_size(pvec_first); ++i)
    {
        assert_true(*(int*)vector_at(pvec_first, i) == 100);
    }
    for(i = 0; i < vector_size(pvec_second); ++i)
    {
        assert_true(*(int*)vector_at(pvec_second, i) == 0);
    }

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test vector_at
 */
UT_CASE_DEFINATION(vector_at)
void test_vector_at__null_vector_container(void** state)
{
    expect_assert_failure(vector_at(NULL, 0));
}

void test_vector_at__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_start = (_byte_t*)0x223;
    expect_assert_failure(vector_at(pvec, 0));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test_vector_at__invalid_subscript_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_at(pvec, 0));

    vector_destroy(pvec);
}

void test_vector_at__invalid_subscript_end(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    expect_assert_failure(vector_at(pvec, vector_size(pvec)));

    vector_destroy(pvec);
}

void test_vector_at__invalid_subscript(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    expect_assert_failure(vector_at(pvec, 132));

    vector_destroy(pvec);
}

void test_vector_at__successfully(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }

    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == i);
    }

    vector_destroy(pvec);
}

void test_vector_at__successfully_cstr(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_init(pvec);

    vector_push_back(pvec, "abc");
    vector_push_back(pvec, "def");
    vector_push_back(pvec, "hij");

    assert_true(strcmp((char*)vector_at(pvec, 0), "abc") == 0);
    assert_true(strcmp((char*)vector_at(pvec, 1), "def") == 0);
    assert_true(strcmp((char*)vector_at(pvec, 2), "hij") == 0);

    vector_destroy(pvec);
}

/*
 * test vector_front
 */
UT_CASE_DEFINATION(vector_front)
void test_vector_front__null_vector_container(void** state)
{
    expect_assert_failure(vector_front(NULL));
}

void test_vector_front__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x334;
    expect_assert_failure(vector_front(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_front__empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_front(pvec));

    vector_destroy(pvec);
}

void test_vector_front__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    vector_push_back(pvec, 2);
    vector_push_back(pvec, 345);
    vector_push_back(pvec, 24);
    assert_true(*(int*)vector_front(pvec) == 2);

    vector_destroy(pvec);
}

void test_vector_front__successfully_cstr(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_init(pvec);

    vector_push_back(pvec, "wodjad");
    vector_push_back(pvec, "345");
    vector_push_back(pvec, "mmmmmm");
    assert_true(strcmp((char*)vector_front(pvec), "wodjad") == 0);

    vector_destroy(pvec);
}

/*
 * test vector_back
 */
UT_CASE_DEFINATION(vector_back)
void test_vector_back__null_vector_container(void** state)
{
    expect_assert_failure(vector_back(NULL));
}

void test_vector_back__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x334;
    expect_assert_failure(vector_back(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_back__empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_back(pvec));

    vector_destroy(pvec);
}

void test_vector_back__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    vector_push_back(pvec, 2);
    vector_push_back(pvec, 345);
    vector_push_back(pvec, 24);
    assert_true(*(int*)vector_back(pvec) == 24);

    vector_destroy(pvec);
}

void test_vector_back__successfully_cstr(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_init(pvec);

    vector_push_back(pvec, "wodjad");
    vector_push_back(pvec, "345");
    vector_push_back(pvec, "mmmmmm");
    assert_true(strcmp((char*)vector_back(pvec), "mmmmmm") == 0);

    vector_destroy(pvec);
}

/*
 * test vector_begin
 */
UT_CASE_DEFINATION(vector_begin)
void test_vector_begin__null_vector_container(void** state)
{
    expect_assert_failure(vector_begin(NULL));
}

void test_vector_begin__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x354;
    expect_assert_failure(vector_begin(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_begin__empty(void** state)
{
    vector_iterator_t it_begin;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    it_begin = vector_begin(pvec);
    assert_true(_vector_iterator_belong_to_vector(pvec, it_begin));
    assert_true(iterator_equal(it_begin, vector_end(pvec)));

    vector_destroy(pvec);
}

void test_vector_begin__non_empty(void** state)
{
    vector_iterator_t it_begin;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    vector_push_back(pvec, 123);
    vector_push_back(pvec, 209);
    vector_push_back(pvec, 3);

    it_begin = vector_begin(pvec);
    assert_true(_vector_iterator_belong_to_vector(pvec, it_begin));
    assert_true(it_begin._t_pos._pby_corepos == pvec->_pby_start);
    assert_true(*(int*)iterator_get_pointer(it_begin) == 123);

    vector_destroy(pvec);
}

/*
 * test vector_end
 */
UT_CASE_DEFINATION(vector_end)
void test_vector_end__null_vector_container(void** state)
{
    expect_assert_failure(vector_end(NULL));
}

void test_vector_end__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x354;
    expect_assert_failure(vector_end(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_end__empty(void** state)
{
    vector_iterator_t it_end;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    it_end = vector_end(pvec);
    assert_true(_vector_iterator_belong_to_vector(pvec, it_end));
    assert_true(iterator_equal(it_end, vector_begin(pvec)));

    vector_destroy(pvec);
}

void test_vector_end__non_empty(void** state)
{
    vector_iterator_t it_end;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    vector_push_back(pvec, 123);
    vector_push_back(pvec, 209);
    vector_push_back(pvec, 3);

    it_end = vector_end(pvec);
    assert_true(_vector_iterator_belong_to_vector(pvec, it_end));
    assert_true(it_end._t_pos._pby_corepos == pvec->_pby_finish);

    vector_destroy(pvec);
}

/*
 * test vector_insert_range
 */
UT_CASE_DEFINATION(vector_insert_range)
void test_vector_insert_range__null_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec);
    vector_init(pvec_src);

    expect_assert_failure(vector_insert_range(NULL, vector_begin(pvec), vector_begin(pvec_src), vector_end(pvec_src)));

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec_src);
    pvec->_pby_start = (_byte_t*)0x78;

    expect_assert_failure(vector_insert_range(pvec, vector_begin(pvec), vector_begin(pvec_src), vector_end(pvec_src)));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__invalid_position(void** state)
{
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec_src);
    vector_init_n(pvec, 10);
    it_pos = vector_begin(pvec);
    it_pos._t_pos._pby_corepos = NULL;

    expect_assert_failure(vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src)));

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__invalid_range(void** state)
{
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_n(pvec_src, 10);
    vector_init_n(pvec, 10);
    it_pos = vector_begin(pvec);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    expect_assert_failure(vector_insert_range(pvec, it_pos, it_end, it_begin));

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__invalid_range_not_same_type(void** state)
{
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(double);
    vector_init(pvec_src);
    vector_init_n(pvec, 10);
    it_pos = vector_begin(pvec);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    expect_assert_failure(vector_insert_range(pvec, it_pos, it_begin, it_end));

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__invalid_range_belong_to_vector(void** state)
{
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec_src);
    vector_init_n(pvec, 10);
    it_pos = vector_begin(pvec);
    it_begin = vector_begin(pvec_src);
    it_end = vector_end(pvec_src);

    vector_insert_range(pvec, it_pos, it_pos, it_pos);

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__empty_insert_0(void** state)
{
    vector_iterator_t it_pos;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec);
    vector_init(pvec_src);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__empty_insert_10(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec);
    vector_init_elem(pvec_src, 10, 100);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__empty_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init(pvec);
    vector_init_elem(pvec_src, 1000, 100);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__begin_insert_0(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_n(pvec, 1000);
    vector_init_elem(pvec_src, 0, 100);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__begin_insert_10(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 10, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__begin_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1000, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__middle_insert_0(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 0, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__middle_insert_10(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 10, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 300 && i < 310)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__middle_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1457, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 2457);
    assert_true(vector_capacity(pvec) == 3685);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 300 && i < 1757)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__end_insert_0(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 0, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__end_insert_10(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 10, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__end_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_t* pvec_src = create_vector(int);
    vector_init_elem(pvec_src, 1100, 100);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    vector_insert_range(pvec, it_pos, vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(vector_size(pvec) == 2100);
    assert_true(vector_capacity(pvec) == 3150);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
    vector_destroy(pvec_src);
}

void test_vector_insert_range__other_container_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    size_t i = 0;

    vector_init_n(pvec, 10);
    list_init_elem(plist, 100, 100);
    assert_true(vector_size(pvec) == 10);
    vector_insert_range(pvec, vector_end(pvec), list_begin(plist), list_end(plist));
    assert_true(vector_size(pvec) == 110);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
    }

    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test vector_insert_array
 */
UT_CASE_DEFINATION(vector_insert_array)
void test_vector_insert_array__null_vector_container(void** state)
{
    int an_array[10] = {0};
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(vector_insert_array(NULL, vector_begin(pvec), an_array, 10));

    vector_destroy(pvec);
}

void test_vector_insert_array__non_inited(void** state)
{
    int an_array[10] = {0};
    vector_t* pvec = create_vector(int);
    pvec->_pby_start = (_byte_t*)0x78;

    expect_assert_failure(vector_insert_array(pvec, vector_begin(pvec), an_array, 10));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test_vector_insert_array__invalid_position(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);
    it_pos = vector_begin(pvec);
    it_pos._t_pos._pby_corepos = NULL;

    expect_assert_failure(vector_insert_array(pvec, it_pos, an_array, 10));

    vector_destroy(pvec);
}

void test_vector_insert_array__invalid_array(void** state)
{
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);
    it_pos = vector_begin(pvec);

    expect_assert_failure(vector_insert_array(pvec, it_pos, NULL, 10));

    vector_destroy(pvec);
}

void test_vector_insert_array__empty_insert_0(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    vector_insert_array(pvec, it_pos, an_array, 0);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_insert_array__empty_insert_10(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    vector_insert_array(pvec, it_pos, an_array, 10);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__empty_insert_1000(void** state)
{
    int an_array[1000] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    for (i = 0; i < 1000; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    vector_insert_array(pvec, it_pos, an_array, 1000);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__begin_insert_0(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    vector_insert_array(pvec, it_pos, an_array, 0);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__begin_insert_10(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    vector_insert_array(pvec, it_pos, an_array, 10);
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__begin_insert_1000(void** state)
{
    int an_array[1000] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    for (i = 0; i < 1000; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    vector_insert_array(pvec, it_pos, an_array, 1000);
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__middle_insert_0(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    vector_insert_array(pvec, it_pos, an_array, 0);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__middle_insert_10(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    vector_insert_array(pvec, it_pos, an_array, 10);
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 300 && i < 310)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__middle_insert_1000(void** state)
{
    int an_array[1457] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    for (i = 0; i < 1457; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    vector_insert_array(pvec, it_pos, an_array, 1457);
    assert_true(vector_size(pvec) == 2457);
    assert_true(vector_capacity(pvec) == 3685);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 300 && i < 1757)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__end_insert_0(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    vector_insert_array(pvec, it_pos, an_array, 0);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__end_insert_10(void** state)
{
    int an_array[10] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    vector_insert_array(pvec, it_pos, an_array, 10);
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__end_insert_1000(void** state)
{
    int an_array[1100] = {0};
    vector_iterator_t it_pos;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    for (i = 0; i < 1100; ++i) {
        an_array[i] = 100;
    }
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    vector_insert_array(pvec, it_pos, an_array, 1100);
    assert_true(vector_size(pvec) == 2100);
    assert_true(vector_capacity(pvec) == 3150);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__cstr(void** state)
{
    const char* as_array[] = {
        "linux", "windows", "mac", "freebsd", "solaris"
    };
    vector_t* pvec = create_vector(char*);
    size_t i = 0;

    vector_init_n(pvec, 10);
    assert_true(vector_size(pvec) == 10);
    vector_insert_array(pvec, vector_end(pvec), as_array, 5);
    assert_true(vector_size(pvec) == 15);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 10)
        {
            assert_true(strcmp((char*)vector_at(pvec, i), "") == 0);
        }
        else
        {
            assert_true(strcmp((char*)vector_at(pvec, i), as_array[i - 10]) == 0);
        }
    }

    vector_destroy(pvec);
}

void test_vector_insert_array__cstl(void** state)
{
    list_t* aplist_array[10] = {NULL};
    vector_t* pvec = create_vector(list_t<int>);
    size_t i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        aplist_array[i] = create_list(int);
        list_init_elem(aplist_array[i], i, i);
    }
    assert_true(vector_size(pvec) == 0);
    vector_insert_array(pvec, vector_end(pvec), aplist_array, 10);
    assert_true(vector_size(pvec) == 10);
    for (i = 0; i < 10; ++i) {
        assert_true(list_equal(vector_at(pvec, i), aplist_array[i]));
    }

    vector_destroy(pvec);
    for (i = 0; i < 10; ++i) {
        list_destroy(aplist_array[i]);
    }
}

typedef struct _test_vector_insert_array__user_define {
    int n_elem;
}_test_vector_insert_array__user_define_t;
void test_vector_insert_array__user_define(void** state)
{
    _test_vector_insert_array__user_define_t* apt_array[10] = {NULL};
    vector_t* pvec = NULL;
    size_t i = 0;

    type_register(_test_vector_insert_array__user_define_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(_test_vector_insert_array__user_define_t);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_vector_insert_array__user_define_t));
        apt_array[i]->n_elem = i;
    }
    assert_true(vector_size(pvec) == 0);
    vector_insert_array(pvec, vector_end(pvec), apt_array, 10);
    assert_true(vector_size(pvec) == 10);
    for (i = 0; i < 10; ++i) {
        assert_true(((_test_vector_insert_array__user_define_t*)vector_at(pvec, i))->n_elem == apt_array[i]->n_elem);
    }

    vector_destroy(pvec);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test vector_pop_back
 */
UT_CASE_DEFINATION(vector_pop_back)
void test_vector_pop_back__null_vector_container(void** state)
{
    expect_assert_failure(vector_pop_back(NULL));
}

void test_vector_pop_back__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x3445;
    expect_assert_failure(vector_pop_back(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_pop_back__empty(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(vector_pop_back(pvec));

    vector_destroy(pvec);
}

void test_vector_pop_back__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);
    assert_true(*(int*)vector_back(pvec) == 9);
    vector_pop_back(pvec);
    assert_true(vector_size(pvec) == t_oldsize - 1);
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(*(int*)vector_back(pvec) == 8);

    vector_destroy(pvec);
}

/*
 * test vector_erase
 */
UT_CASE_DEFINATION(vector_erase)
void test_vector_erase__null_vector_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_pos = vector_begin(pvec);
    expect_assert_failure(vector_erase(NULL, it_pos));

    vector_destroy(pvec);
}

void test_vector_erase__non_inited_vector_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    _byte_t*  pby_oldfinish = NULL;
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_pos = vector_begin(pvec);
    pby_oldfinish = pvec->_pby_finish;
    pvec->_pby_finish = NULL;
    expect_assert_failure(vector_erase(pvec, it_pos));

    pvec->_pby_finish = pby_oldfinish;
    vector_destroy(pvec);
}

void test_vector_erase__invalid_pos_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_pos = vector_end(pvec);
    expect_assert_failure(vector_erase(pvec, it_pos));

    vector_destroy(pvec);
}

void test_vector_erase__invalid_pos(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_pos = vector_end(pvec);
    it_pos._t_pos._pby_corepos = NULL;
    expect_assert_failure(vector_erase(pvec, it_pos));

    vector_destroy(pvec);
}

void test_vector_erase__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_pos = vector_begin(pvec);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_iter = vector_erase(pvec, it_pos);
    assert_true(vector_size(pvec) == t_oldsize - 1);
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    vector_destroy(pvec);
}

void test_vector_erase__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_pos = iterator_next(vector_begin(pvec));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_iter = vector_erase(pvec, it_pos);
    assert_true(vector_size(pvec) == t_oldsize - 1);
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    vector_destroy(pvec);
}

void test_vector_erase__successfully_back(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_pos = iterator_prev(vector_end(pvec));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_iter = vector_erase(pvec, it_pos);
    assert_true(vector_size(pvec) == t_oldsize - 1);
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(*(int*)vector_back(pvec) == 8);
    assert_true(iterator_equal(it_iter, vector_end(pvec)));

    vector_destroy(pvec);
}

/*
 * test vector_erase_range
 */
UT_CASE_DEFINATION(vector_erase_range)
void test_vector_erase_range__null_vector_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    expect_assert_failure(vector_erase_range(NULL, it_begin, it_end));

    vector_destroy(pvec);
}

void test_vector_erase_range__non_inited_vector_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    _byte_t*  pby_oldfinish = NULL;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    pby_oldfinish = pvec->_pby_finish;
    pvec->_pby_finish = NULL;
    expect_assert_failure(vector_erase_range(pvec, it_begin, it_end));

    pvec->_pby_finish = pby_oldfinish;
    vector_destroy(pvec);
}

void test_vector_erase_range__invalid_range_not_belong_to_vector(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    expect_assert_failure(vector_erase_range(pvec, it_begin, it_end));

    vector_destroy(pvec);
}

void test_vector_erase_range__invalid_range(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    expect_assert_failure(vector_erase_range(pvec, it_end, it_begin));

    vector_destroy(pvec);
}

void test_vector_erase_range__successfully_empty(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    size_t t_erasesize = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    it_iter = vector_erase_range(pvec, it_begin, it_begin);
    assert_true(vector_size(pvec) == t_oldsize - t_erasesize);
    assert_true(vector_capacity(pvec) == t_oldcapacity);

    vector_destroy(pvec);
}

void test_vector_erase_range__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    size_t t_erasesize = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = vector_begin(pvec);
    it_end = iterator_next_n(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = vector_erase_range(pvec, it_begin, it_end);
    assert_true(vector_size(pvec) == t_oldsize - t_erasesize);
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    vector_destroy(pvec);
}

void test_vector_erase_range__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    size_t t_erasesize = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = iterator_next_n(vector_begin(pvec), 3);
    it_end = iterator_next_n(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = vector_erase_range(pvec, it_begin, it_end);
    assert_true(vector_size(pvec) == t_oldsize - t_erasesize);
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);

    vector_destroy(pvec);
}

void test_vector_erase_range__successfully_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    size_t t_erasesize = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = iterator_next_n(vector_begin(pvec), 6);
    it_end = vector_end(pvec);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = vector_erase_range(pvec, it_begin, it_end);
    assert_true(vector_size(pvec) == t_oldsize - t_erasesize);
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(*(int*)vector_back(pvec) == 5);
    assert_true(iterator_equal(it_iter, vector_end(pvec)));

    vector_destroy(pvec);
}

void test_vector_erase_range__successfully_all(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_oldcapacity = 0;
    size_t t_erasesize = 0;
    vector_iterator_t it_begin = _create_vector_iterator();
    vector_iterator_t it_end = _create_vector_iterator();
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    t_oldsize = vector_size(pvec);
    t_oldcapacity = vector_capacity(pvec);

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = vector_erase_range(pvec, it_begin, it_end);
    assert_true(vector_size(pvec) == t_oldsize - t_erasesize);
    assert_true(vector_empty(pvec));
    assert_true(vector_capacity(pvec) == t_oldcapacity);
    assert_true(iterator_equal(it_iter, vector_end(pvec)));

    vector_destroy(pvec);
}

/*
 * test vector_clear
 */
UT_CASE_DEFINATION(vector_clear)
void test_vector_clear__null_vector_container(void** state)
{
    expect_assert_failure(vector_clear(NULL));
}

void test_vector_clear__non_inited_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_finish = (_byte_t*)0x89;
    expect_assert_failure(vector_clear(pvec));

    pvec->_pby_finish = NULL;
    vector_destroy(pvec);
}

void test_vector_clear__empty_vector_container(void** state)
{
    size_t t_oldcapacity = 0;
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    t_oldcapacity = vector_capacity(pvec);

    vector_clear(pvec);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == t_oldcapacity);

    vector_destroy(pvec);
}

void test_vector_clear__non_empty_vector_container(void** state)
{
    size_t t_oldcapacity = 0;
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 198);
    t_oldcapacity = vector_capacity(pvec);

    vector_clear(pvec);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == t_oldcapacity);

    vector_destroy(pvec);
}

/*
 * test vector_resize
 */
UT_CASE_DEFINATION(vector_resize)
void test_vector_resize__null_vector_container(void** state)
{
    expect_assert_failure(vector_resize(NULL, 10));
}

void test_vector_resize__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);
    pvec->_pby_start = (_byte_t*)0x987;

    expect_assert_failure(vector_resize(pvec, 10));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test_vector_resize__successfully_0_resize_0(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    vector_resize(pvec, 0);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test_vector_resize__successfully_0_resize_10(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    vector_resize(pvec, 10);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_resize__successfully_0_resize_1000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    vector_resize(pvec, 1000);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_resize__successfully_10_resize_0(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    vector_resize(pvec, 0);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 26);

    vector_destroy(pvec);
}

void test_vector_resize__successfully_10_resize_10(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    vector_resize(pvec, 10);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_resize__successfully_10_resize_1000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    vector_resize(pvec, 1000);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_resize__successfully_1000_resize_0(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    vector_resize(pvec, 0);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 1500);

    vector_destroy(pvec);
}

void test_vector_resize__successfully_1000_resize_10(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    vector_resize(pvec, 10);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_resize__successfully_1000_resize_1000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    vector_resize(pvec, 1000);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_resize__successfully_1000_resize_1200(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    vector_resize(pvec, 1200);
    assert_true(vector_size(pvec) == 1200);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test_vector_resize__successfully_1000_resize_2000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    vector_resize(pvec, 2000);
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

