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

    pvec_src->_pc_finish = (char*)0x732;
    expect_assert_failure(vector_init_copy(pvec_dest, pvec_src));

    pvec_src->_pc_finish = NULL;
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
    vec._pc_start = (char*)0x37;

    expect_assert_failure(vector_destroy(&vec));
}

void test_vector_destroy__created_non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_destroy(pvec);
    assert_true(pvec->_pc_start == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_endofstorage == NULL);
}

void test_vector_destroy__inited_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    vector_destroy(pvec);
    assert_true(pvec->_pc_start == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_endofstorage == NULL);
}

void test_vector_destroy__inited_non_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 199);

    vector_destroy(pvec);
    assert_true(pvec->_pc_start == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_endofstorage == NULL);
}

