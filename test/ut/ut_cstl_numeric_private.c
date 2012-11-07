#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/chash_map.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl/cdeque.h"
#include "cstl/cslist.h"
#include "cstl/cmap.h"
#include "cstl/cset.h"
#include "cstl/chash_set.h"
#include "cstl/calgorithm.h"
#include "cstl/cfunctional.h"
#include "cstl/cnumeric.h"

#include "ut_def.h"
#include "ut_cstl_numeric_private.h"

UT_SUIT_DEFINATION(cstl_numeric_private, _algo_iota)

/*
 * test _algo_iota
 */
UT_CASE_DEFINATION(_algo_iota)
void test__algo_iota__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(_algo_iota(deque_begin(pdeq), vector_begin(pvec), 0));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test__algo_iota__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_iota(deque_end(pdeq), deque_begin(pdeq), 0));
    deque_destroy(pdeq);
}

void test__algo_iota__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_iota(it, deque_begin(pdeq), 0));
    deque_destroy(pdeq);
}

void test__algo_iota__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _algo_iota(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test__algo_iota__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_result[] = {-4, -3, -2, -1, 0, 1, 2, 3, 4, 5};

    deque_init_n(pdeq, 10);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_iota(deque_begin(pdeq), deque_end(pdeq), -4);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test _algo_accumulate
 */
UT_CASE_DEFINATION(_algo_accumulate)
void test__algo_accumulate__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(_algo_accumulate(deque_begin(pdeq), vector_begin(pvec), &n_sum, 0));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test__algo_accumulate__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_accumulate(deque_end(pdeq), deque_begin(pdeq), &n_sum, 0));
    deque_destroy(pdeq);
}

void test__algo_accumulate__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_accumulate(it, deque_begin(pdeq), &n_sum, 0));
    deque_destroy(pdeq);
}

void test__algo_accumulate__output_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_accumulate(deque_begin(pdeq), deque_end(pdeq), NULL, 0));
    deque_destroy(pdeq);
}

void test__algo_accumulate__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_sum = 0;

    deque_init(pdeq);
    _algo_accumulate(deque_begin(pdeq), deque_end(pdeq), &n_sum, 100);
    assert_true(n_sum == 100);
    deque_destroy(pdeq);
}

void test__algo_accumulate__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n_sum = 0;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    _algo_accumulate(deque_begin(pdeq), deque_end(pdeq), &n_sum, 100);
    assert_true(n_sum == 145);
    deque_destroy(pdeq);
}

/*
 * test _algo_accumulate_if
 */
UT_CASE_DEFINATION(_algo_accumulate_if)
void test__algo_accumulate_if__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(_algo_accumulate_if(deque_begin(pdeq), vector_begin(pvec), fun_minus_int, &n_sum, 0));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test__algo_accumulate_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_accumulate_if(deque_end(pdeq), deque_begin(pdeq), fun_minus_int, &n_sum, 0));
    deque_destroy(pdeq);
}

void test__algo_accumulate_if__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_accumulate_if(it, deque_begin(pdeq), fun_minus_int, &n_sum, 0));
    deque_destroy(pdeq);
}

void test__algo_accumulate_if__output_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_accumulate_if(deque_begin(pdeq), deque_end(pdeq), fun_minus_int, NULL, 0));
    deque_destroy(pdeq);
}

void test__algo_accumulate_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_sum = 0;

    deque_init(pdeq);
    _algo_accumulate_if(deque_begin(pdeq), deque_end(pdeq), fun_minus_int, &n_sum, 100);
    assert_true(n_sum == 100);
    deque_destroy(pdeq);
}

void test__algo_accumulate_if__bfun_NULL_not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n_sum = 0;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    _algo_accumulate_if(deque_begin(pdeq), deque_end(pdeq), NULL, &n_sum, 100);
    assert_true(n_sum == 145);
    deque_destroy(pdeq);
}

void test__algo_accumulate_if__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n_sum = 0;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    _algo_accumulate_if(deque_begin(pdeq), deque_end(pdeq), fun_minus_int, &n_sum, 100);
    assert_true(n_sum == 55);
    deque_destroy(pdeq);
}

/*
 * test _algo_inner_product
 */
UT_CASE_DEFINATION(_algo_inner_product)
void test__algo_inner_product__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_inner_product(deque_end(pdeq), deque_begin(pdeq), list_begin(plist), &n_sum, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_inner_product(deque_begin(pdeq), deque_end(pdeq), it, &n_sum, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_inner_product(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), &n_sum, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product__output_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_inner_product(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), NULL, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int n_sum = 0;

    deque_init(pdeq);
    list_init(plist);
    _algo_inner_product(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), &n_sum, 100);
    assert_true(n_sum == 100);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n_sum = 0;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_range(plist, deque_begin(pdeq), deque_end(pdeq));
    _algo_inner_product(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), &n_sum, 0);
    assert_true(n_sum == 285);
    deque_destroy(pdeq);
    list_destroy(plist);
}

/*
 * test _algo_inner_product_if
 */
UT_CASE_DEFINATION(_algo_inner_product_if)
void test__algo_inner_product_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_inner_product_if(deque_end(pdeq), deque_begin(pdeq), list_begin(plist), fun_plus_int, fun_multiplies_int, &n_sum, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_inner_product_if(deque_begin(pdeq), deque_end(pdeq), it, fun_plus_int, fun_multiplies_int, &n_sum, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product_if__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);
    int n_sum = 0;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_inner_product_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_plus_int, fun_multiplies_int, &n_sum, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product_if__output_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_inner_product_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_plus_int, fun_multiplies_int, NULL, 0));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int n_sum = 0;

    deque_init(pdeq);
    list_init(plist);
    _algo_inner_product_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_plus_int, fun_multiplies_int, &n_sum, 100);
    assert_true(n_sum == 100);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product_if__bfun_op1_NULL_not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n_sum = 0;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_range(plist, deque_begin(pdeq), deque_end(pdeq));
    _algo_inner_product_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), NULL, fun_plus_int, &n_sum, 0);
    assert_true(n_sum == 90);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product_if__bfun_op2_NULL_not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n_sum = 0;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_range(plist, deque_begin(pdeq), deque_end(pdeq));
    _algo_inner_product_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_minus_int, NULL, &n_sum, 0);
    assert_true(n_sum == -285);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_inner_product_if__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n_sum = 0;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_range(plist, deque_begin(pdeq), deque_end(pdeq));
    _algo_inner_product_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_minus_int, fun_plus_int, &n_sum, 0);
    assert_true(n_sum == -90);
    deque_destroy(pdeq);
    list_destroy(plist);
}

