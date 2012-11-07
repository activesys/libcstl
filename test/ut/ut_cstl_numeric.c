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
#include "ut_cstl_numeric.h"

UT_SUIT_DEFINATION(cstl_numeric, algo_partial_sum)

/*
 * test algo_partial_sum
 */
UT_CASE_DEFINATION(algo_partial_sum)
void test_algo_partial_sum__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_partial_sum(deque_begin(pdeq), vector_begin(pvec), list_begin(plist)));
    deque_destroy(pdeq);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_partial_sum__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_partial_sum(deque_begin(pdeq), deque_end(pdeq), it));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_partial_sum__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_partial_sum(deque_begin(pdeq), deque_end(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_partial_sum__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init(pdeq);
    list_init(plist);
    it = algo_partial_sum(deque_begin(pdeq), deque_end(pdeq), list_begin(plist));
    assert_true(iterator_equal(it, list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_partial_sum__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {1, 3, 6, 10, 15, 21, 28, 36, 45};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, deque_size(pdeq));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sum(deque_begin(pdeq), deque_end(pdeq), list_begin(plist));
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    deque_destroy(pdeq);
    list_destroy(plist);
    list_destroy(plist_result);
}

/*
 * test algo_partial_sum_if
 */
UT_CASE_DEFINATION(algo_partial_sum_if)
void test_algo_partial_sum_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_partial_sum_if(deque_begin(pdeq), vector_begin(pvec), list_begin(plist), fun_multiplies_int));
    deque_destroy(pdeq);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_partial_sum_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_partial_sum_if(deque_begin(pdeq), deque_end(pdeq), it, fun_multiplies_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_partial_sum_if__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_partial_sum_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_multiplies_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_partial_sum_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init(pdeq);
    list_init(plist);
    it = algo_partial_sum_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_multiplies_int);
    assert_true(iterator_equal(it, list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_partial_sum_if__bfun_NULL_not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {1, 3, 6, 10, 15, 21, 28, 36, 45};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, deque_size(pdeq));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sum_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    deque_destroy(pdeq);
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_partial_sum_if__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, deque_size(pdeq));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sum_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_multiplies_int);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    deque_destroy(pdeq);
    list_destroy(plist);
    list_destroy(plist_result);
}

/*
 * test algo_adjacent_difference
 */
UT_CASE_DEFINATION(algo_adjacent_difference)
void test_algo_adjacent_difference__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_adjacent_difference(deque_begin(pdeq), vector_begin(pvec), list_begin(plist)));
    deque_destroy(pdeq);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_adjacent_difference__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_adjacent_difference(deque_begin(pdeq), deque_end(pdeq), it));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_adjacent_difference__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_adjacent_difference(deque_begin(pdeq), deque_end(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_adjacent_difference__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init(pdeq);
    list_init(plist);
    it = algo_adjacent_difference(deque_begin(pdeq), deque_end(pdeq), list_begin(plist));
    assert_true(iterator_equal(it, list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_adjacent_difference__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 3, 6, 10, 15, 21, 28, 36, 45};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, deque_size(pdeq));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_adjacent_difference(deque_begin(pdeq), deque_end(pdeq), list_begin(plist));
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    deque_destroy(pdeq);
    list_destroy(plist);
    list_destroy(plist_result);
}

/*
 * test algo_adjacent_difference_if
 */
UT_CASE_DEFINATION(algo_adjacent_difference_if)
void test_algo_adjacent_difference_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_adjacent_difference_if(deque_begin(pdeq), vector_begin(pvec), list_begin(plist), fun_multiplies_int));
    deque_destroy(pdeq);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_adjacent_difference_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_adjacent_difference_if(deque_begin(pdeq), deque_end(pdeq), it, fun_multiplies_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_adjacent_difference_if__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_adjacent_difference_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_multiplies_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_adjacent_difference_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init(pdeq);
    list_init(plist);
    it = algo_adjacent_difference_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_multiplies_int);
    assert_true(iterator_equal(it, list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_adjacent_difference_if__bfun_NULL_not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 3, 6, 10, 15, 21, 28, 36, 45};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, deque_size(pdeq));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_adjacent_difference_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    deque_destroy(pdeq);
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_adjacent_difference_if__not_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, deque_size(pdeq));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_adjacent_difference_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), fun_divides_int);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    deque_destroy(pdeq);
    list_destroy(plist);
    list_destroy(plist_result);
}

/*
 * test algo_power
 */
UT_CASE_DEFINATION(algo_power)
void test_algo_power__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;
    int n_sum = 0;

    deque_init_elem(pdeq, 1, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_power(it, 2, &n_sum));
    deque_destroy(pdeq);
}

void test_algo_power__output_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 1, 10);
    expect_assert_failure(algo_power(deque_begin(pdeq), 2, NULL));
    deque_destroy(pdeq);
}

void test_algo_power__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_sum = 0;

    deque_init_elem(pdeq, 1, 10);
    algo_power(deque_begin(pdeq), 2, &n_sum);
    assert_true(n_sum == 100);
    deque_destroy(pdeq);
}

/*
 * test algo_power_if
 */
UT_CASE_DEFINATION(algo_power_if)
void test_algo_power_if__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;
    int n_sum = 0;

    deque_init_elem(pdeq, 1, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_power_if(it, 2, fun_plus_int, &n_sum));
    deque_destroy(pdeq);
}

void test_algo_power_if__output_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 1, 10);
    expect_assert_failure(algo_power_if(deque_begin(pdeq), 2, fun_plus_int, NULL));
    deque_destroy(pdeq);
}

void test_algo_power_if__bfun_NULL_normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_sum = 0;

    deque_init_elem(pdeq, 1, 10);
    algo_power_if(deque_begin(pdeq), 2, NULL, &n_sum);
    assert_true(n_sum == 100);
    deque_destroy(pdeq);
}

void test_algo_power_if__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_sum = 0;

    deque_init_elem(pdeq, 1, 10);
    algo_power_if(deque_begin(pdeq), 2, fun_plus_int, &n_sum);
    assert_true(n_sum == 20);
    deque_destroy(pdeq);
}

