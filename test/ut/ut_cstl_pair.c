#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_rb_tree_aux.h"
#include "cstl_pair_aux.h"

#include "ut_def.h"
#include "ut_cstl_pair.h"

UT_SUIT_DEFINATION(cstl_pair, pair_init)

/*
 * test pair_init
 */
UT_CASE_DEFINATION(pair_init)
void test_pair_init__null_pair(void** state)
{
    expect_assert_failure(pair_init(NULL));
}

void test_pair_init__non_created(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pt_pair->_pv_first = (void*)0x8888;
    expect_assert_failure(pair_init(pt_pair));
    pt_pair->_pv_first = NULL;

    pair_destroy(pt_pair);
}

void test_pair_init__init(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    assert_true(_pair_is_inited(pt_pair));

    pair_destroy(pt_pair);
}

/*
 * test pair_init_copy
 */
UT_CASE_DEFINATION(pair_init_copy)
void test_pair_init_copy__null_dest(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_init_copy(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_init_copy__null_src(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    expect_assert_failure(pair_init_copy(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_init_copy__non_created_dest(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(int, int);

    pair_init(pt_src);
    pt_dest->_pv_second = (void*)0x3333;
    expect_assert_failure(pair_init_copy(pt_dest, pt_src));
    pt_dest->_pv_second = NULL;

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_init_copy__non_inited_src(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(int, int);

    expect_assert_failure(pair_init_copy(pt_dest, pt_src));

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_init_copy__not_same_type(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(int, double);

    pair_init(pt_src);
    expect_assert_failure(pair_init_copy(pt_dest, pt_src));

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_init_copy__empty(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(signed int, signed);

    pair_init(pt_src);
    pt_src->_bfun_mapvaluecompare = (binary_function_t)0x3333;
    pair_init_copy(pt_dest, pt_src);
    assert_true(_pair_is_inited(pt_dest));
    assert_true(pair_equal(pt_dest, pt_src));
    assert_true(pt_dest->_bfun_mapkeycompare == pt_src->_bfun_mapkeycompare);
    assert_true(pt_dest->_bfun_mapvaluecompare == pt_dest->_bfun_mapvaluecompare);

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_init_copy__non_empty(void** state)
{
    pair_t* pt_dest = create_pair(int, double);
    pair_t* pt_src = create_pair(signed int, double);

    pair_init_elem(pt_src, 100, 33.45);
    pair_init_copy(pt_dest, pt_src);
    assert_true(_pair_is_inited(pt_dest));
    assert_true(*(int*)pair_first(pt_dest) == 100);
    assert_true(*(double*)pair_second(pt_dest) == 33.45);

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

/*
 * test pair_destroy
 */
UT_CASE_DEFINATION(pair_destroy)
void test_pair_destroy__null_pair(void** state)
{
    expect_assert_failure(pair_destroy(NULL));
}

void test_pair_destroy__non_created(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pt_pair->_pv_first = (void*)0x999;
    expect_assert_failure(pair_destroy(pt_pair));
    pt_pair->_pv_first = NULL;

    pair_destroy(pt_pair);
}

void test_pair_destroy__created(void** state)
{
    pair_t* pt_pair = create_pair(int, double);

    pair_destroy(pt_pair);
}

void test_pair_destroy__inited(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    pair_destroy(pt_pair);
}

/*
 * test pair_assign
 */
UT_CASE_DEFINATION(pair_assign)
void test_pair_assign__null_dest(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    expect_assert_failure(pair_assign(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_assign__null_src(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    expect_assert_failure(pair_assign(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_assign__non_init_dest(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(int, int);

    pair_init(pt_src);
    expect_assert_failure(pair_assign(pt_dest, pt_src));

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_assign__non_init_src(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(int, int);

    pair_init(pt_dest);
    expect_assert_failure(pair_assign(pt_dest, pt_src));

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_assign__not_same_type(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(double, int);

    pair_init(pt_src);
    pair_init(pt_dest);
    expect_assert_failure(pair_assign(pt_dest, pt_src));

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_assign__equal_not_same(void** state)
{
    pair_t* pt_dest = create_pair(int, int);
    pair_t* pt_src = create_pair(int, int);

    pair_init(pt_src);
    pt_src->_bfun_mapkeycompare = (binary_function_t)0x999;
    pair_init(pt_dest);
    pt_dest->_bfun_mapvaluecompare = (binary_function_t)0x888;
    pair_assign(pt_dest, pt_src);
    assert_true(pair_equal(pt_dest, pt_src));
    assert_true(pt_dest->_bfun_mapkeycompare == pt_src->_bfun_mapkeycompare);
    assert_true(pt_dest->_bfun_mapvaluecompare == pt_src->_bfun_mapvaluecompare);

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

void test_pair_assign__same_pair(void** state)
{
    pair_t* pt_pair = create_pair(int, double);

    pair_init(pt_pair);
    pair_assign(pt_pair, pt_pair);

    pair_destroy(pt_pair);
}

void test_pair_assign__not_equal(void** state)
{
    pair_t* pt_dest = create_pair(int, double);
    pair_t* pt_src = create_pair(int, double);

    pair_init_elem(pt_dest, 55, 22.103);
    pair_init_elem(pt_src, 90, -8.34);
    pair_assign(pt_dest, pt_src);
    assert_true(pair_equal(pt_dest, pt_src));
    assert_true(pt_dest->_bfun_mapkeycompare == pt_src->_bfun_mapkeycompare);
    assert_true(pt_dest->_bfun_mapvaluecompare == pt_src->_bfun_mapvaluecompare);
    assert_true(*(int*)pair_first(pt_dest) == 90);
    assert_true(*(double*)pair_second(pt_dest) == -8.34);

    pair_destroy(pt_dest);
    pair_destroy(pt_src);
}

/*
 * test pair_first
 */
UT_CASE_DEFINATION(pair_first)
void test_pair_first__null_pair(void** state)
{
    expect_assert_failure(pair_first(NULL));
}

void test_pair_first__non_inited(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    expect_assert_failure(pair_first(pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_first__c_builtin(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init_elem(pt_pair, 9, 2);

    assert_true(*(int*)pair_first(pt_pair) == 9);

    pair_destroy(pt_pair);
}

void test_pair_first__str(void** state)
{
    pair_t* pt_pair = create_pair(char*, int);

    pair_init_elem(pt_pair, "NULL", 9);

    assert_true(strcmp((char*)pair_first(pt_pair), "NULL") == 0);

    pair_destroy(pt_pair);
}

void test_pair_first__cstl_builtin(void** state)
{
    pair_t* pt_pair = create_pair(vector_t<int>, int);
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 5, 12);
    pair_init_elem(pt_pair, pvec, 4);

    assert_true(vector_size((vector_t*)pair_first(pt_pair)) == 5);
    assert_true(*(int*)vector_front((vector_t*)pair_first(pt_pair)) == 12);

    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test_pair_first__user_define
{
    int n_elem;
}_test_pair_first__user_define_t;
void test_pair_first__user_define(void** state)
{
    pair_t* pt_pair = NULL;
    _test_pair_first__user_define_t t_elem;

    type_register(_test_pair_first__user_define_t, NULL, NULL, NULL, NULL);

    pt_pair = create_pair(_test_pair_first__user_define_t, int);
    t_elem.n_elem = 299;
    pair_init_elem(pt_pair, &t_elem, 22);

    assert_true(((_test_pair_first__user_define_t*)pair_first(pt_pair))->n_elem == 299);

    pair_destroy(pt_pair);
}

/*
 * test pair_second
 */
UT_CASE_DEFINATION(pair_second)
void test_pair_second__null_pair(void** state)
{
    expect_assert_failure(pair_second(NULL));
}

void test_pair_second__non_inited(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    expect_assert_failure(pair_second(pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_second__c_builtin(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init_elem(pt_pair, 9, 2);

    assert_true(*(int*)pair_second(pt_pair) == 2);

    pair_destroy(pt_pair);
}

void test_pair_second__str(void** state)
{
    pair_t* pt_pair = create_pair(int, char*);

    pair_init_elem(pt_pair, 9, "NULL");

    assert_true(strcmp((char*)pair_second(pt_pair), "NULL") == 0);

    pair_destroy(pt_pair);
}

void test_pair_second__cstl_builtin(void** state)
{
    pair_t* pt_pair = create_pair(int, vector_t<int>);
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 5, 12);
    pair_init_elem(pt_pair, 4, pvec);

    assert_true(vector_size((vector_t*)pair_second(pt_pair)) == 5);
    assert_true(*(int*)vector_front((vector_t*)pair_second(pt_pair)) == 12);

    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test_pair_second__user_define
{
    int n_elem;
}_test_pair_second__user_define_t;
void test_pair_second__user_define(void** state)
{
    pair_t* pt_pair = NULL;
    _test_pair_second__user_define_t t_elem;

    type_register(_test_pair_second__user_define_t, NULL, NULL, NULL, NULL);

    pt_pair = create_pair(int, _test_pair_second__user_define_t);
    t_elem.n_elem = 299;
    pair_init_elem(pt_pair, 33, &t_elem);

    assert_true(((_test_pair_second__user_define_t*)pair_second(pt_pair))->n_elem == 299);

    pair_destroy(pt_pair);
}

/*
 * test pair_equal
 */
UT_CASE_DEFINATION(pair_equal)
void test_pair_equal__null_first(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_equal(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_equal__null_second(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_equal(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_equal__non_inited_first(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_second);

    expect_assert_failure(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_equal__non_inited_second(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_first);

    expect_assert_failure(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_equal__not_same_type(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(list_t<int>, int);

    pair_init(pt_first);
    pair_init(pt_second);

    expect_assert_failure(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_equal__same_pair(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    assert_true(pair_equal(pt_pair, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_equal__less_first_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(signed int, int);

    pair_init_elem(pt_first, 12, 9);
    pair_init_elem(pt_second, 88, 9);

    assert_false(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_equal__less_second_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 3, 9);
    pair_init_elem(pt_second, 3, 99);

    assert_false(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_equal__greater_first_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 6, 9);
    pair_init_elem(pt_second, 3, 9);

    assert_false(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_equal__greater_second_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 9);
    pair_init_elem(pt_second, 8, 8);

    assert_false(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_equal__equal(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 8);
    pair_init_elem(pt_second, 8, 8);

    assert_true(pair_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

/*
 * test pair_not_equal
 */
UT_CASE_DEFINATION(pair_not_equal)
void test_pair_not_equal__null_first(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_not_equal(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_not_equal__null_second(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_not_equal(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_not_equal__non_inited_first(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_second);

    expect_assert_failure(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_not_equal__non_inited_second(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_first);

    expect_assert_failure(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_not_equal__not_same_type(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(list_t<int>, int);

    pair_init(pt_first);
    pair_init(pt_second);

    expect_assert_failure(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_not_equal__same_pair(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    assert_false(pair_not_equal(pt_pair, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_not_equal__less_first_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(signed int, int);

    pair_init_elem(pt_first, 12, 9);
    pair_init_elem(pt_second, 88, 9);

    assert_true(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_not_equal__less_second_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 3, 9);
    pair_init_elem(pt_second, 3, 99);

    assert_true(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_not_equal__greater_first_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 6, 9);
    pair_init_elem(pt_second, 3, 9);

    assert_true(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_not_equal__greater_second_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 9);
    pair_init_elem(pt_second, 8, 8);

    assert_true(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_not_equal__equal(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 8);
    pair_init_elem(pt_second, 8, 8);

    assert_false(pair_not_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

/*
 * test pair_less
 */
UT_CASE_DEFINATION(pair_less)
void test_pair_less__null_first(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_less(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_less__null_second(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_less(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_less__non_inited_first(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_second);

    expect_assert_failure(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less__non_inited_second(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_first);

    expect_assert_failure(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less__not_same_type(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(list_t<int>, int);

    pair_init(pt_first);
    pair_init(pt_second);

    expect_assert_failure(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less__same_pair(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    assert_false(pair_less(pt_pair, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_less__less_first_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(signed int, int);

    pair_init_elem(pt_first, 12, 9);
    pair_init_elem(pt_second, 88, 9);

    assert_true(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less__less_second_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 3, 9);
    pair_init_elem(pt_second, 3, 99);

    assert_true(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less__greater_first_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 6, 9);
    pair_init_elem(pt_second, 3, 9);

    assert_false(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less__greater_second_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 9);
    pair_init_elem(pt_second, 8, 8);

    assert_false(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less__equal(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 8);
    pair_init_elem(pt_second, 8, 8);

    assert_false(pair_less(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

/*
 * test pair_less_equal
 */
UT_CASE_DEFINATION(pair_less_equal)
void test_pair_less_equal__null_first(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_less_equal(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_less_equal__null_second(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_less_equal(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_less_equal__non_inited_first(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_second);

    expect_assert_failure(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less_equal__non_inited_second(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_first);

    expect_assert_failure(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less_equal__not_same_type(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(list_t<int>, int);

    pair_init(pt_first);
    pair_init(pt_second);

    expect_assert_failure(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less_equal__same_pair(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    assert_true(pair_less_equal(pt_pair, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_less_equal__less_first_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(signed int, int);

    pair_init_elem(pt_first, 12, 9);
    pair_init_elem(pt_second, 88, 9);

    assert_true(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less_equal__less_second_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 3, 9);
    pair_init_elem(pt_second, 3, 99);

    assert_true(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less_equal__greater_first_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 6, 9);
    pair_init_elem(pt_second, 3, 9);

    assert_false(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less_equal__greater_second_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 9);
    pair_init_elem(pt_second, 8, 8);

    assert_false(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_less_equal__equal(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 8);
    pair_init_elem(pt_second, 8, 8);

    assert_true(pair_less_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

/*
 * test pair_greater
 */
UT_CASE_DEFINATION(pair_greater)
void test_pair_greater__null_first(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_greater(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_greater__null_second(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_greater(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_greater__non_inited_first(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_second);

    expect_assert_failure(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater__non_inited_second(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_first);

    expect_assert_failure(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater__not_same_type(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(list_t<int>, int);

    pair_init(pt_first);
    pair_init(pt_second);

    expect_assert_failure(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater__same_pair(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    assert_false(pair_greater(pt_pair, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_greater__less_first_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(signed int, int);

    pair_init_elem(pt_first, 12, 9);
    pair_init_elem(pt_second, 88, 9);

    assert_false(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater__less_second_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 3, 9);
    pair_init_elem(pt_second, 3, 99);

    assert_false(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater__greater_first_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 6, 9);
    pair_init_elem(pt_second, 3, 9);

    assert_true(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater__greater_second_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 9);
    pair_init_elem(pt_second, 8, 8);

    assert_true(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater__equal(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 8);
    pair_init_elem(pt_second, 8, 8);

    assert_false(pair_greater(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

/*
 * test pair_greater_equal
 */
UT_CASE_DEFINATION(pair_greater_equal)
void test_pair_greater_equal__null_first(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_greater_equal(NULL, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_greater_equal__null_second(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);

    expect_assert_failure(pair_greater_equal(pt_pair, NULL));

    pair_destroy(pt_pair);
}

void test_pair_greater_equal__non_inited_first(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_second);

    expect_assert_failure(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater_equal__non_inited_second(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init(pt_first);

    expect_assert_failure(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater_equal__not_same_type(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(list_t<int>, int);

    pair_init(pt_first);
    pair_init(pt_second);

    expect_assert_failure(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater_equal__same_pair(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    pair_init(pt_pair);
    assert_true(pair_greater_equal(pt_pair, pt_pair));

    pair_destroy(pt_pair);
}

void test_pair_greater_equal__less_first_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(signed int, int);

    pair_init_elem(pt_first, 12, 9);
    pair_init_elem(pt_second, 88, 9);

    assert_false(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater_equal__less_second_less(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 3, 9);
    pair_init_elem(pt_second, 3, 99);

    assert_false(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater_equal__greater_first_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 6, 9);
    pair_init_elem(pt_second, 3, 9);

    assert_true(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater_equal__greater_second_greater(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 9);
    pair_init_elem(pt_second, 8, 8);

    assert_true(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

void test_pair_greater_equal__equal(void** state)
{
    pair_t* pt_first = create_pair(int, int);
    pair_t* pt_second = create_pair(int, int);

    pair_init_elem(pt_first, 8, 8);
    pair_init_elem(pt_second, 8, 8);

    assert_true(pair_greater_equal(pt_first, pt_second));

    pair_destroy(pt_first);
    pair_destroy(pt_second);
}

