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

#include "ut_def.h"
#include "ut_cstl_algo_sorting.h"

UT_SUIT_DEFINATION(cstl_algo_sorting, algo_is_sorted)

/*
 * test algo_is_sorted
 */
UT_CASE_DEFINATION(algo_is_sorted)
void test_algo_is_sorted__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_sorted(vector_begin(pvec), deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_is_sorted__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_sorted(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_sorted__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_is_sorted(it, list_end(plist)));
    list_destroy(plist);
}

void test_algo_is_sorted__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_sorted(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_sorted__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_sorted(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_sorted__true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_sorted(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_sorted__false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(algo_is_sorted(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_sorted__all_equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(algo_is_sorted(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test algo_is_sorted_if
 */
UT_CASE_DEFINATION(algo_is_sorted_if)
void test_algo_is_sorted_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_sorted_if(vector_begin(pvec), deque_end(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_sorted_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_is_sorted_if(it, list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_is_sorted_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__bfun_NULL_true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__bfun_NULL_false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__bfun_NULL_all_equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_sorted_if__all_equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(algo_is_sorted_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

/*
 * test algo_partial_sort
 */
UT_CASE_DEFINATION(algo_partial_sort)
void test_algo_partial_sort__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_partial_sort(deque_begin(pdeq), deque_end(pdeq), vector_begin(pvec)));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_partial_sort__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort(deque_end(pdeq), deque_begin(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_partial_sort__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_partial_sort(list_begin(plist), list_end(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_partial_sort__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_partial_sort(deque_begin(pdeq), deque_begin(pdeq), deque_begin(pdeq));
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_partial_sort__first_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy(pdeq_result, pdeq);
    algo_partial_sort(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};
    int an_result[] = {0, 1, 2, 3, 4};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_partial_sort(deque_begin(pdeq), iterator_advance(deque_begin(pdeq), 5), deque_end(pdeq));
    assert_true(algo_equal(deque_begin(pdeq_result), deque_end(pdeq_result), deque_begin(pdeq)));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort__second_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_partial_sort(deque_begin(pdeq), deque_end(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_partial_sort_if
 */
UT_CASE_DEFINATION(algo_partial_sort_if)
void test_algo_partial_sort_if__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_partial_sort_if(deque_begin(pdeq), deque_end(pdeq), vector_begin(pvec), fun_greater_int));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_partial_sort_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_if(deque_end(pdeq), deque_begin(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_partial_sort_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_partial_sort_if(list_begin(plist), list_end(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_partial_sort_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_partial_sort_if(deque_begin(pdeq), deque_begin(pdeq), deque_begin(pdeq), fun_greater_int);
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_partial_sort_if__bfun_NULL_first_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy(pdeq_result, pdeq);
    algo_partial_sort_if(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_if__bfun_NULL_normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};
    int an_result[] = {0, 1, 2, 3, 4};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_partial_sort_if(deque_begin(pdeq), iterator_advance(deque_begin(pdeq), 5), deque_end(pdeq), NULL);
    assert_true(algo_equal(deque_begin(pdeq_result), deque_end(pdeq_result), deque_begin(pdeq)));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_if__bfun_NULL_second_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_partial_sort_if(deque_begin(pdeq), deque_end(pdeq), deque_end(pdeq), NULL);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_if__first_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy(pdeq_result, pdeq);
    algo_partial_sort_if(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_if__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};
    int an_result[] = {9, 8, 7, 6, 5};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_partial_sort_if(deque_begin(pdeq), iterator_advance(deque_begin(pdeq), 5), deque_end(pdeq), fun_greater_int);
    assert_true(algo_equal(deque_begin(pdeq_result), deque_end(pdeq_result), deque_begin(pdeq)));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_if__second_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 5, 0, 9, 8, 1, 3, 6, 7, 4};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_partial_sort_if(deque_begin(pdeq), deque_end(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_partial_sort_copy
 */
UT_CASE_DEFINATION(algo_partial_sort_copy)
void test_algo_partial_sort_copy__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy(list_end(plist), list_begin(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__invalid_first_range3(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_partial_sort_copy(it, list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy(list_begin(plist), list_end(plist), vector_begin(pvec), deque_end(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__invalid_second_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_end(pdeq), deque_begin(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__invalid_second_range3(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_partial_sort_copy(list_begin(plist), list_end(plist), slist_begin(pslist), slist_end(pslist)));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_partial_sort_copy__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(char*);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__first_range_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init(plist);
    deque_init_n(pdeq, 10);
    it = algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__second_range_emtpy(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init_n(plist, 10);
    deque_init(pdeq);
    it = algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__all_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init(plist);
    deque_init(pdeq);
    it = algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy__first_less_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 9)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_copy__first_equal_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_copy__first_greater_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {1, 2, 3, 4, 5};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_partial_sort_copy_if
 */
UT_CASE_DEFINATION(algo_partial_sort_copy_if)
void test_algo_partial_sort_copy_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy_if(list_end(plist), list_begin(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__invalid_first_range3(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_partial_sort_copy_if(it, list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy_if(list_begin(plist), list_end(plist), vector_begin(pvec), deque_end(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__invalid_second_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__invalid_second_range3(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_partial_sort_copy_if(list_begin(plist), list_end(plist), slist_begin(pslist), slist_end(pslist), fun_greater_int));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_partial_sort_copy_if__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(char*);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__first_range_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init(plist);
    deque_init_n(pdeq, 10);
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__second_range_emtpy(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init_n(plist, 10);
    deque_init(pdeq);
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__all_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init(plist);
    deque_init(pdeq);
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_partial_sort_copy_if__bfun_NULL_first_less_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 9)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_copy_if__bfun_NULL_first_equal_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_copy_if__bfun_NULL_first_greater_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {1, 2, 3, 4, 5};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_copy_if__first_less_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 9)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_copy_if__first_equal_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_partial_sort_copy_if__first_greater_second(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 3, 4, 5, 7, 1, 8, 2, 6};
    int an_result[] = {9, 8, 7, 6, 5};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_partial_sort_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

