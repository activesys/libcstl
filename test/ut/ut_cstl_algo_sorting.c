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

/*
 * test algo_sort
 */
UT_CASE_DEFINATION(algo_sort)
void test_algo_sort__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_sort(vector_begin(pvec), deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_sort__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_sort(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_sort__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_sort(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_sort__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_sort(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_sort__less_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {4, 0, 9, 7, 3, 1, 8, 6, 5, 2};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_sort(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_sort__more_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {
        4, 0, 9, 7, 3, 1, 8, 6, 5, 2,
        8, 9, 0, 2, 5, 3, 1, 4, 7, 6,
        0, 3, 5, 7, 9, 2, 4, 6, 8, 1,
        9, 8, 7, 6, 5, 0, 1, 2, 3, 4,
        8, 1, 0, 7, 4, 5, 9, 2, 3, 6
    };
    int an_result[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 
        4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 
        6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 
        8, 8, 8, 8, 8, 9, 9, 9, 9, 9
    };

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_sort(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_sort_if
 */
UT_CASE_DEFINATION(algo_sort_if)
void test_algo_sort_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_sort_if(vector_begin(pvec), deque_end(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_sort_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_sort_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_sort_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_sort_if(list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_sort_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_sort_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_sort_if__bfun_NULL_less_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {4, 0, 9, 7, 3, 1, 8, 6, 5, 2};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_sort_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_sort_if__bfun_NULL_more_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {
        4, 0, 9, 7, 3, 1, 8, 6, 5, 2,
        8, 9, 0, 2, 5, 3, 1, 4, 7, 6,
        0, 3, 5, 7, 9, 2, 4, 6, 8, 1,
        9, 8, 7, 6, 5, 0, 1, 2, 3, 4,
        8, 1, 0, 7, 4, 5, 9, 2, 3, 6
    };
    int an_result[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 
        4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 
        6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 
        8, 8, 8, 8, 8, 9, 9, 9, 9, 9
    };

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_sort_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_sort_if__less_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {4, 0, 9, 7, 3, 1, 8, 6, 5, 2};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_sort_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_sort_if__more_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {
        4, 0, 9, 7, 3, 1, 8, 6, 5, 2,
        8, 9, 0, 2, 5, 3, 1, 4, 7, 6,
        0, 3, 5, 7, 9, 2, 4, 6, 8, 1,
        9, 8, 7, 6, 5, 0, 1, 2, 3, 4,
        8, 1, 0, 7, 4, 5, 9, 2, 3, 6
    };
    int an_result[] = {
        9, 9, 9, 9, 9, 8, 8, 8, 8, 8,
        7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 
        5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 
        3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 
        1, 1, 1, 1, 1, 0, 0, 0, 0, 0
    };

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_sort_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_merge
 */
UT_CASE_DEFINATION(algo_merge)
void test_algo_merge__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_merge(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_merge__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(double);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge__first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init(pvec);
    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 10);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge__second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init(plist);
    deque_init_n(pdeq, 10);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge__all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    list_init(plist);
    deque_init(pdeq);
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_empty(pdeq));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge__first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4};
    int an_second[] = {5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge__second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {0, 1, 2, 3, 4};
    int an_first[] = {5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge__overlap_first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 7};
    int an_second[] = {5, 6, 8, 9, 10, 11, 12};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge__overlap_second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {0, 1, 2, 3, 4, 5, 7};
    int an_first[] = {5, 6, 8, 9, 10, 11, 12};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge__overlap(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_merge_if
 */
UT_CASE_DEFINATION(algo_merge_if)
void test_algo_merge_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_merge_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_merge_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge_if(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge_if__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it, fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge_if__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge_if__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(double);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge_if__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge_if__bfun_NULL_first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init(pvec);
    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 10);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__bfun_NULL_second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init(plist);
    deque_init_n(pdeq, 10);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__bfun_NULL_all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    list_init(plist);
    deque_init(pdeq);
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_empty(pdeq));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge_if__bfun_NULL_first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4};
    int an_second[] = {5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__bfun_NULL_second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {0, 1, 2, 3, 4};
    int an_first[] = {5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__bfun_NULL_overlap_first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 7};
    int an_second[] = {5, 6, 8, 9, 10, 11, 12};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__bfun_NULL_overlap_second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {0, 1, 2, 3, 4, 5, 7};
    int an_first[] = {5, 6, 8, 9, 10, 11, 12};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__bfun_NULL_overlap(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init(pvec);
    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 10);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init(plist);
    deque_init_n(pdeq, 10);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    list_init(plist);
    deque_init(pdeq);
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_empty(pdeq));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_merge_if__first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {9, 8, 7, 6, 5};
    int an_second[] = {4, 3, 2, 1, 0};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {9, 8, 7, 6, 5};
    int an_first[] = {4, 3, 2, 1, 0};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__overlap_first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_second[] = {7, 5, 4, 3, 2, 1, 0};
    int an_first[] = {12, 11, 10, 9, 8, 6, 5};
    int an_result[] = {12, 11, 10, 9, 8, 7, 6, 5, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__overlap_second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {7, 5, 4, 3, 2, 1, 0};
    int an_second[] = {12, 11, 10, 9, 8, 6, 5};
    int an_result[] = {12, 11, 10, 9, 8, 7, 6, 5, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_merge_if__overlap(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_second[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_result[] = {9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_first)/sizeof(an_first[0]) + sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_merge_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_inplace_merge
 */
UT_CASE_DEFINATION(algo_inplace_merge)
void test_algo_inplace_merge__invalid_first_range(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_inplace_merge(iterator_advance(list_begin(plist), 3), list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_inplace_merge__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_inplace_merge(deque_begin(pdeq), deque_end(pdeq), vector_end(pvec)));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_inplace_merge__invalid_range(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_inplace_merge(slist_begin(pslist), slist_begin(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

void test_algo_inplace_merge__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    algo_inplace_merge(list_begin(plist), list_begin(plist), list_end(plist));
    assert_true(list_empty(plist));
    list_destroy(plist);
}

void test_algo_inplace_merge__first_empty(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    algo_inplace_merge(list_begin(plist), list_begin(plist), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__second_empty(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    algo_inplace_merge(list_begin(plist), list_end(plist), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__first_lead_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__second_lead_first(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {10, 11, 12, 13, 14, 0, 1, 2, 3, 4};
    int an_result[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__overlap_first_lead_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 10), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__overlap_second_lead_first(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 10), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__overlap(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"abc", "def", "klm", "uvw", "xyz", "hij", "klm", "nop", "qrs", "uvw"};
    const char* as_result[] = {"abc", "def", "hij", "klm", "klm", "nop", "qrs", "uvw", "uvw", "xyz"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge__cstl_builtin(void** state)
{
    list_t* plist = create_list(pair_t<int, int>);
    list_t* plist_result = create_list(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int aan_array[][2] = {{0, 0}, {1, 0}, {4, 0}, {7, 0}, {9, 0}, {2, 1}, {3, 1}, {5, 1}, {6, 1}, {8, 1}};
    int aan_result[][2] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}, {4, 0}, {5, 1}, {6, 1}, {7, 0}, {8, 1}, {9, 0}};
    int i = 0;

    pair_init(ppair);
    list_init(plist);
    list_init(plist_result);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        pair_make(ppair, aan_array[i][0], aan_array[i][1]);
        list_push_back(plist, ppair);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        pair_make(ppair, aan_result[i][0], aan_result[i][1]);
        list_push_back(plist_result, ppair);
    }
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
    pair_destroy(ppair);
}

typedef struct _tag_test_algo_inplace_merge__user_define {
    int a;
    int b;
} _test_algo_inplace_merge__user_define_t;
static void _test_algo_inplace_merge__user_define_init(const void* cpv_input, void* pv_output)
{
    ((_test_algo_inplace_merge__user_define_t*)cpv_input)->a = 0;
    ((_test_algo_inplace_merge__user_define_t*)cpv_input)->b = 0;
    *(bool_t*)pv_output = true;
}
static void _test_algo_inplace_merge__user_define_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    ((_test_algo_inplace_merge__user_define_t*)cpv_first)->a = ((_test_algo_inplace_merge__user_define_t*)cpv_second)->a;
    ((_test_algo_inplace_merge__user_define_t*)cpv_first)->b = ((_test_algo_inplace_merge__user_define_t*)cpv_second)->b;
    *(bool_t*)pv_output = true;
}
static void _test_algo_inplace_merge__user_define_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = ((_test_algo_inplace_merge__user_define_t*)cpv_first)->a < ((_test_algo_inplace_merge__user_define_t*)cpv_second)->a ? true : false;
}
static void _test_algo_inplace_merge__user_define_destroy(const void* cpv_input, void* pv_output)
{
    ((_test_algo_inplace_merge__user_define_t*)cpv_input)->a = 0;
    ((_test_algo_inplace_merge__user_define_t*)cpv_input)->b = 0;
    *(bool_t*)pv_output = true;
}
void test_algo_inplace_merge__user_define(void** state)
{
    list_t* plist = NULL;
    list_t* plist_result = NULL;
    _test_algo_inplace_merge__user_define_t at_array[] = {{0, 0}, {1, 0}, {4, 0}, {7, 0}, {9, 0}, {2, 1}, {3, 1}, {5, 1}, {6, 1}, {8, 1}};
    _test_algo_inplace_merge__user_define_t at_result[] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}, {4, 0}, {5, 1}, {6, 1}, {7, 0}, {8, 1}, {9, 0}};
    int i = 0;

    type_register(_test_algo_inplace_merge__user_define_t,
        _test_algo_inplace_merge__user_define_init, _test_algo_inplace_merge__user_define_copy,
        _test_algo_inplace_merge__user_define_less, _test_algo_inplace_merge__user_define_destroy);
    plist = create_list(_test_algo_inplace_merge__user_define_t);
    plist_result = create_list(_test_algo_inplace_merge__user_define_t);

    list_init(plist);
    list_init(plist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        list_push_back(plist, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        list_push_back(plist_result, &at_result[i]);
    }
    algo_inplace_merge(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

/*
 * test algo_inplace_merge_if
 */
UT_CASE_DEFINATION(algo_inplace_merge_if)
void test_algo_inplace_merge_if__invalid_first_range(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_inplace_merge_if(iterator_advance(list_begin(plist), 3), list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_inplace_merge_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_inplace_merge_if(deque_begin(pdeq), deque_end(pdeq), vector_end(pvec), fun_greater_int));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_inplace_merge_if__invalid_range(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_inplace_merge_if(slist_begin(pslist), slist_begin(pslist), slist_end(pslist), fun_greater_int));
    slist_destroy(pslist);
}

void test_algo_inplace_merge_if__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    algo_inplace_merge_if(list_begin(plist), list_begin(plist), list_end(plist), fun_greater_int);
    assert_true(list_empty(plist));
    list_destroy(plist);
}

void test_algo_inplace_merge_if__first_empty(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    algo_inplace_merge_if(list_begin(plist), list_begin(plist), list_end(plist), fun_greater_int);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__second_empty(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    algo_inplace_merge_if(list_begin(plist), list_end(plist), list_end(plist), fun_greater_int);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__bfun_NULL_first_lead_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__bfun_NULL_second_lead_first(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {10, 11, 12, 13, 14, 0, 1, 2, 3, 4};
    int an_result[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__bfun_NULL_overlap_first_lead_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 10), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__bfun_NULL_overlap_second_lead_first(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 12, 13, 14};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 10), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__bfun_NULL_overlap(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__bfun_NULL_cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"abc", "def", "klm", "uvw", "xyz", "hij", "klm", "nop", "qrs", "uvw"};
    const char* as_result[] = {"abc", "def", "hij", "klm", "klm", "nop", "qrs", "uvw", "uvw", "xyz"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__bfun_NULL_cstl_builtin(void** state)
{
    list_t* plist = create_list(pair_t<int, int>);
    list_t* plist_result = create_list(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int aan_array[][2] = {{0, 0}, {1, 0}, {4, 0}, {7, 0}, {9, 0}, {2, 1}, {3, 1}, {5, 1}, {6, 1}, {8, 1}};
    int aan_result[][2] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}, {4, 0}, {5, 1}, {6, 1}, {7, 0}, {8, 1}, {9, 0}};
    int i = 0;

    pair_init(ppair);
    list_init(plist);
    list_init(plist_result);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        pair_make(ppair, aan_array[i][0], aan_array[i][1]);
        list_push_back(plist, ppair);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        pair_make(ppair, aan_result[i][0], aan_result[i][1]);
        list_push_back(plist_result, ppair);
    }
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
    pair_destroy(ppair);
}

typedef struct _tag_test_algo_inplace_merge_if__user_define {
    int a;
    int b;
} _test_algo_inplace_merge_if__user_define_t;
static void _test_algo_inplace_merge_if__user_define_init(const void* cpv_input, void* pv_output)
{
    ((_test_algo_inplace_merge_if__user_define_t*)cpv_input)->a = 0;
    ((_test_algo_inplace_merge_if__user_define_t*)cpv_input)->b = 0;
    *(bool_t*)pv_output = true;
}
static void _test_algo_inplace_merge_if__user_define_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    ((_test_algo_inplace_merge_if__user_define_t*)cpv_first)->a = ((_test_algo_inplace_merge_if__user_define_t*)cpv_second)->a;
    ((_test_algo_inplace_merge_if__user_define_t*)cpv_first)->b = ((_test_algo_inplace_merge_if__user_define_t*)cpv_second)->b;
    *(bool_t*)pv_output = true;
}
static void _test_algo_inplace_merge_if__user_define_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = ((_test_algo_inplace_merge_if__user_define_t*)cpv_first)->a < ((_test_algo_inplace_merge_if__user_define_t*)cpv_second)->a ? true : false;
}
static void _test_algo_inplace_merge_if__user_define_destroy(const void* cpv_input, void* pv_output)
{
    ((_test_algo_inplace_merge_if__user_define_t*)cpv_input)->a = 0;
    ((_test_algo_inplace_merge_if__user_define_t*)cpv_input)->b = 0;
    *(bool_t*)pv_output = true;
}
void test_algo_inplace_merge_if__bfun_NULL_user_define(void** state)
{
    list_t* plist = NULL;
    list_t* plist_result = NULL;
    _test_algo_inplace_merge_if__user_define_t at_array[] = {{0, 0}, {1, 0}, {4, 0}, {7, 0}, {9, 0}, {2, 1}, {3, 1}, {5, 1}, {6, 1}, {8, 1}};
    _test_algo_inplace_merge_if__user_define_t at_result[] = {{0, 0}, {1, 0}, {2, 1}, {3, 1}, {4, 0}, {5, 1}, {6, 1}, {7, 0}, {8, 1}, {9, 0}};
    int i = 0;

    type_register(_test_algo_inplace_merge_if__user_define_t,
        _test_algo_inplace_merge_if__user_define_init, _test_algo_inplace_merge_if__user_define_copy,
        _test_algo_inplace_merge_if__user_define_less, _test_algo_inplace_merge_if__user_define_destroy);
    plist = create_list(_test_algo_inplace_merge_if__user_define_t);
    plist_result = create_list(_test_algo_inplace_merge_if__user_define_t);

    list_init(plist);
    list_init(plist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        list_push_back(plist, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        list_push_back(plist_result, &at_result[i]);
    }
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), NULL);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__first_lead_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {14, 13, 12, 11, 10, 4, 3, 2, 1, 0};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), fun_greater_int);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__second_lead_first(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {4, 3, 2, 1, 0, 14, 13, 12, 11, 10};
    int an_result[] = {14, 13, 12, 11, 10, 4, 3, 2, 1, 0};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), fun_greater_int);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__overlap_first_lead_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_result[] = {14, 13, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 1, 0};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 10), list_end(plist), fun_greater_int);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__overlap_second_lead_first(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5};
    int an_result[] = {14, 13, 12, 11, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 3, 2, 1, 0};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 10), list_end(plist), fun_greater_int);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__overlap(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {9, 7, 5, 3, 1, 8, 6, 4, 2, 0};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), fun_greater_int);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"uvw", "qrs", "nop", "klm", "hij", "xyz", "uvw", "klm", "def", "abc"};
    const char* as_result[] = {"xyz", "uvw", "uvw", "qrs", "nop", "klm", "klm", "hij", "def", "abc"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), fun_greater_cstr);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_inplace_merge_if__cstl_builtin(void** state)
{
    list_t* plist = create_list(pair_t<int, int>);
    list_t* plist_result = create_list(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int aan_array[][2] = {{8, 1}, {6, 1}, {5, 1}, {3, 1}, {2, 1}, {9, 0}, {7, 0}, {4, 0}, {1, 0}, {0, 0}};
    int aan_result[][2] = {{9, 0}, {8, 1}, {7, 0}, {6, 1}, {5, 1}, {4, 0}, {3, 1}, {2, 1}, {1, 0}, {0, 0}};
    int i = 0;

    pair_init(ppair);
    list_init(plist);
    list_init(plist_result);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        pair_make(ppair, aan_array[i][0], aan_array[i][1]);
        list_push_back(plist, ppair);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        pair_make(ppair, aan_result[i][0], aan_result[i][1]);
        list_push_back(plist_result, ppair);
    }
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), fun_greater_pair);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
    pair_destroy(ppair);
}

static void _test_algo_inplace_merge_if__user_define_greater(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = ((_test_algo_inplace_merge_if__user_define_t*)cpv_first)->a > ((_test_algo_inplace_merge_if__user_define_t*)cpv_second)->a ? true : false;
}
void test_algo_inplace_merge_if__user_define(void** state)
{
    list_t* plist = create_list(_test_algo_inplace_merge_if__user_define_t);
    list_t* plist_result = create_list(_test_algo_inplace_merge_if__user_define_t);
    _test_algo_inplace_merge_if__user_define_t at_array[] = {{8, 1}, {6, 1}, {5, 1}, {3, 1}, {2, 1}, {9, 0}, {7, 0}, {4, 0}, {1, 0}, {0, 0}};
    _test_algo_inplace_merge_if__user_define_t at_result[] = {{9, 0}, {8, 1}, {7, 0}, {6, 1}, {5, 1}, {4, 0}, {3, 1}, {2, 1}, {1, 0}, {0, 0}};
    int i = 0;

    list_init(plist);
    list_init(plist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        list_push_back(plist, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        list_push_back(plist_result, &at_result[i]);
    }
    algo_inplace_merge_if(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), _test_algo_inplace_merge_if__user_define_greater);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

/*
 * test algo_stable_sort
 */
UT_CASE_DEFINATION(algo_stable_sort)
void test_algo_stable_sort__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_stable_sort(vector_begin(pvec), deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_stable_sort__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_stable_sort(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_stable_sort__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_stable_sort(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_stable_sort__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_stable_sort(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_stable_sort__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    algo_stable_sort(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_size(pdeq) == 1);
    deque_destroy(pdeq);
}

typedef struct _tag_algo_stable_sort__user_define {
    int a;
    int b;
} _test_algo_stable_sort__user_define_t;
static void _test_algo_stable_sort__user_define_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = ((_test_algo_stable_sort__user_define_t*)cpv_first)->a < ((_test_algo_stable_sort__user_define_t*)cpv_second)->a ? true : false;
}
static void _test_algo_stable_sort__user_define_greater(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = ((_test_algo_stable_sort__user_define_t*)cpv_first)->a > ((_test_algo_stable_sort__user_define_t*)cpv_second)->a ? true : false;
}
static void _test_algo_stable_sort__user_define_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_stable_sort__user_define_t)) == 0 ? true : false;
}
void test_algo_stable_sort__less_than_threshold(void** state)
{
    deque_t* pdeq = NULL;
    deque_t* pdeq_result = NULL;
    _test_algo_stable_sort__user_define_t at_array[] = {{1, 0}, {4, 0}, {3, 0}, {1, 1}, {0, 0}, {4, 1}, {2, 0}, {5, 0}, {2, 1}, {2, 2}};
    _test_algo_stable_sort__user_define_t at_result[] = {{0, 0}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {2, 2}, {3, 0}, {4, 0}, {4, 1}, {5, 0}};
    int i = 0;

    type_register(_test_algo_stable_sort__user_define_t, NULL, NULL, _test_algo_stable_sort__user_define_less, NULL);
    pdeq = create_deque(_test_algo_stable_sort__user_define_t);
    pdeq_result = create_deque(_test_algo_stable_sort__user_define_t);
    deque_init(pdeq);
    deque_init(pdeq_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        deque_push_back(pdeq_result, &at_result[i]);
    }
    algo_stable_sort(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_equal_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq_result), _test_algo_stable_sort__user_define_equal));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_stable_sort__more_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_stable_sort__user_define_t);
    deque_t* pdeq_result = create_deque(_test_algo_stable_sort__user_define_t);
    _test_algo_stable_sort__user_define_t at_array[] = {
        {1, 0}, {4, 0}, {3, 0}, {1, 1}, {0, 0}, {4, 1}, {2, 0}, {1, 2}, {2, 1}, {2, 2},
        {5, 0}, {1, 3}, {4, 2}, {4, 3}, {3, 1}, {3, 2}, {4, 4}, {5, 1}, {2, 3}, {0, 1}
    };
    _test_algo_stable_sort__user_define_t at_result[] = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3},
        {3, 0}, {3, 1}, {3, 2}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {5, 0}, {5, 1}
    };
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        deque_push_back(pdeq_result, &at_result[i]);
    }
    algo_stable_sort(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_equal_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq_result), _test_algo_stable_sort__user_define_equal));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_stable_sort_if
 */
UT_CASE_DEFINATION(algo_stable_sort_if)
void test_algo_stable_sort_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_stable_sort_if(vector_begin(pvec), deque_end(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_stable_sort_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_stable_sort_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_stable_sort_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_stable_sort_if(list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_stable_sort_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_stable_sort_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_stable_sort_if__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    algo_stable_sort_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_size(pdeq) == 1);
    deque_destroy(pdeq);
}

void test_algo_stable_sort_if__bfun_NULL_less_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_stable_sort__user_define_t);
    deque_t* pdeq_result = create_deque(_test_algo_stable_sort__user_define_t);
    _test_algo_stable_sort__user_define_t at_array[] = {{1, 0}, {4, 0}, {3, 0}, {1, 1}, {0, 0}, {4, 1}, {2, 0}, {5, 0}, {2, 1}, {2, 2}};
    _test_algo_stable_sort__user_define_t at_result[] = {{0, 0}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {2, 2}, {3, 0}, {4, 0}, {4, 1}, {5, 0}};
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        deque_push_back(pdeq_result, &at_result[i]);
    }
    algo_stable_sort_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(algo_equal_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq_result), _test_algo_stable_sort__user_define_equal));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_stable_sort_if__bfun_NULL_more_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_stable_sort__user_define_t);
    deque_t* pdeq_result = create_deque(_test_algo_stable_sort__user_define_t);
    _test_algo_stable_sort__user_define_t at_array[] = {
        {1, 0}, {4, 0}, {3, 0}, {1, 1}, {0, 0}, {4, 1}, {2, 0}, {1, 2}, {2, 1}, {2, 2},
        {5, 0}, {1, 3}, {4, 2}, {4, 3}, {3, 1}, {3, 2}, {4, 4}, {5, 1}, {2, 3}, {0, 1}
    };
    _test_algo_stable_sort__user_define_t at_result[] = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3},
        {3, 0}, {3, 1}, {3, 2}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {5, 0}, {5, 1}
    };
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        deque_push_back(pdeq_result, &at_result[i]);
    }
    algo_stable_sort_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(algo_equal_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq_result), _test_algo_stable_sort__user_define_equal));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_stable_sort_if__less_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_stable_sort__user_define_t);
    deque_t* pdeq_result = create_deque(_test_algo_stable_sort__user_define_t);
    _test_algo_stable_sort__user_define_t at_array[] = {{2, 2}, {2, 1}, {5, 0}, {2, 0}, {4, 1}, {0, 0}, {1, 1}, {3, 0}, {4, 0}, {1, 0}};
    _test_algo_stable_sort__user_define_t at_result[] = {{5, 0}, {4, 1}, {4, 0}, {3, 0}, {2, 2}, {2, 1}, {2, 0}, {1, 1}, {1, 0}, {0, 0}};
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        deque_push_back(pdeq_result, &at_result[i]);
    }
    algo_stable_sort_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_stable_sort__user_define_greater);
    assert_true(algo_equal_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq_result), _test_algo_stable_sort__user_define_equal));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_stable_sort_if__more_than_threshold(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_stable_sort__user_define_t);
    deque_t* pdeq_result = create_deque(_test_algo_stable_sort__user_define_t);
    _test_algo_stable_sort__user_define_t at_array[] = {
        {0, 1}, {2, 3}, {5, 1}, {4, 4}, {3, 2}, {3, 1}, {4, 3}, {4, 2}, {1, 3}, {5, 0},
        {2, 2}, {2, 1}, {1, 2}, {2, 0}, {4, 1}, {0, 0}, {1, 1}, {3, 0}, {4, 0}, {1, 0}
    };
    _test_algo_stable_sort__user_define_t at_result[] = {
        {5, 1}, {5, 0}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {4, 0}, {3, 2}, {3, 1}, {3, 0},
        {2, 3}, {2, 2}, {2, 1}, {2, 0}, {1, 3}, {1, 2}, {1, 1}, {1, 0}, {0, 1}, {0, 0}
    };
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        deque_push_back(pdeq_result, &at_result[i]);
    }
    algo_stable_sort_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_stable_sort__user_define_greater);
    assert_true(algo_equal_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq_result), _test_algo_stable_sort__user_define_equal));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_nth_element
 */
UT_CASE_DEFINATION(algo_nth_element)
void test_algo_nth_element__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_nth_element(vector_begin(pvec), deque_begin(pdeq), deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_nth_element__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_nth_element(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_nth_element__invalid_range(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_nth_element(list_begin(plist), iterator_next(list_begin(plist)), list_end(plist)));
    list_destroy(plist);
}

void test_algo_nth_element__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_nth_element(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_nth_element__three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 0, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element(deque_begin(pdeq), iterator_next(deque_begin(pdeq)), deque_end(pdeq));
    assert_true(*(int*)deque_at(pdeq, 0) == 0);
    assert_true(*(int*)deque_at(pdeq, 1) == 1);
    assert_true(*(int*)deque_at(pdeq, 2) == 2);
    deque_destroy(pdeq);
}

void test_algo_nth_element__first_element(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    iterator_t it;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq));
    assert_true(*(int*)deque_at(pdeq, 0) == 0);
    for (it = deque_begin(pdeq); iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_greater_equal_int(iterator_get_pointer(it), iterator_get_pointer(deque_begin(pdeq)), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element__last_element(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    iterator_t it;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), deque_end(pdeq));
    assert_true(*(int*)deque_at(pdeq, 9) == 9);
    for (it = deque_begin(pdeq); iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_less_equal_int(iterator_get_pointer(it), iterator_get_pointer(iterator_prev(deque_end(pdeq))), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 5, 5, 2, 1, 6, 0, 5, 5, 3, 9};
    iterator_t it;
    iterator_t it_nth;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_nth = iterator_advance(deque_begin(pdeq), 5);
    algo_nth_element(deque_begin(pdeq), it_nth, deque_end(pdeq));
    assert_true(*(int*)deque_at(pdeq, 5) == 5);
    for (it = deque_begin(pdeq); iterator_equal(it, it_nth); it = iterator_next(it)) {
        fun_less_equal_int(iterator_get_pointer(it), iterator_get_pointer(it_nth), &b_result);
        assert_true(b_result);
    }
    for (it = it_nth; iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_less_equal_int(iterator_get_pointer(it), iterator_get_pointer(it_nth), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element__last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element(deque_begin(pdeq), deque_end(pdeq), deque_end(pdeq));
    assert_true(*(int*)deque_at(pdeq, 9) == 9);
    deque_destroy(pdeq);
}

/*
 * test algo_nth_element_if
 */
UT_CASE_DEFINATION(algo_nth_element_if)
void test_algo_nth_element_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_nth_element_if(vector_begin(pvec), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_nth_element_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__invalid_range(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_nth_element_if(list_begin(plist), iterator_next(list_begin(plist)), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_nth_element_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_nth_element_if(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 0, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element_if(deque_begin(pdeq), iterator_next(deque_begin(pdeq)), deque_end(pdeq), fun_greater_int);
    assert_true(*(int*)deque_at(pdeq, 0) == 2);
    assert_true(*(int*)deque_at(pdeq, 1) == 1);
    assert_true(*(int*)deque_at(pdeq, 2) == 0);
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__first_element(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    iterator_t it;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element_if(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(*(int*)deque_at(pdeq, 0) == 9);
    for (it = deque_begin(pdeq); iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_less_equal_int(iterator_get_pointer(it), iterator_get_pointer(deque_begin(pdeq)), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__last_element(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    iterator_t it;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), deque_end(pdeq), fun_greater_int);
    assert_true(*(int*)deque_at(pdeq, 9) == 0);
    for (it = deque_begin(pdeq); iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_greater_equal_int(iterator_get_pointer(it), iterator_get_pointer(iterator_prev(deque_end(pdeq))), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 5, 4, 2, 1, 6, 0, 4, 4, 3, 9};
    iterator_t it;
    iterator_t it_nth;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_nth = iterator_advance(deque_begin(pdeq), 5);
    algo_nth_element_if(deque_begin(pdeq), it_nth, deque_end(pdeq), fun_greater_int);
    assert_true(*(int*)deque_at(pdeq, 5) == 4);
    for (it = deque_begin(pdeq); iterator_equal(it, it_nth); it = iterator_next(it)) {
        fun_greater_equal_int(iterator_get_pointer(it), iterator_get_pointer(it_nth), &b_result);
        assert_true(b_result);
    }
    for (it = it_nth; iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_less_equal_int(iterator_get_pointer(it), iterator_get_pointer(it_nth), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element_if(deque_begin(pdeq), deque_end(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(*(int*)deque_at(pdeq, 9) == 0);
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__bfun_NULL_first_element(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    iterator_t it;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element_if(deque_begin(pdeq), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(*(int*)deque_at(pdeq, 0) == 0);
    for (it = deque_begin(pdeq); iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_greater_equal_int(iterator_get_pointer(it), iterator_get_pointer(deque_begin(pdeq)), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__bfun_NULL_last_element(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    iterator_t it;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), deque_end(pdeq), NULL);
    assert_true(*(int*)deque_at(pdeq, 9) == 9);
    for (it = deque_begin(pdeq); iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_less_equal_int(iterator_get_pointer(it), iterator_get_pointer(iterator_prev(deque_end(pdeq))), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__bfun_NULL_normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 5, 5, 2, 1, 6, 0, 5, 5, 3, 9};
    iterator_t it;
    iterator_t it_nth;
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_nth = iterator_advance(deque_begin(pdeq), 5);
    algo_nth_element_if(deque_begin(pdeq), it_nth, deque_end(pdeq), NULL);
    assert_true(*(int*)deque_at(pdeq, 5) == 5);
    for (it = deque_begin(pdeq); iterator_equal(it, it_nth); it = iterator_next(it)) {
        fun_less_equal_int(iterator_get_pointer(it), iterator_get_pointer(it_nth), &b_result);
        assert_true(b_result);
    }
    for (it = it_nth; iterator_equal(it, deque_end(pdeq)); it = iterator_next(it)) {
        fun_greater_equal_int(iterator_get_pointer(it), iterator_get_pointer(it_nth), &b_result);
        assert_true(b_result);
    }
    deque_destroy(pdeq);
}

void test_algo_nth_element_if__bfun_NULL_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 7, 2, 1, 6, 0, 5, 3, 9};
    bool_t b_result = false;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_nth_element_if(deque_begin(pdeq), deque_end(pdeq), deque_end(pdeq), NULL);
    assert_true(*(int*)deque_at(pdeq, 9) == 9);
    deque_destroy(pdeq);
}

/*
 * test algo_includes
 */
UT_CASE_DEFINATION(algo_includes)
void test_algo_includes__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_includes(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes__invalid_second_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_includes(list_begin(plist), list_end(plist), deque_end(pdeq), deque_begin(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(char*);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_includes(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes__first_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init(plist);
    deque_init_n(pdeq, 10);
    assert_false(algo_includes(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes__second_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init(pdeq);
    assert_true(algo_includes(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes__all_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init(plist);
    deque_init(pdeq);
    assert_true(algo_includes(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes__true(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {2, 5, 6, 9};

    list_init_copy_array(plist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    deque_init_copy_array(pdeq, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_includes(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes__false(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {2, 5, 6, 9, 11};

    list_init_copy_array(plist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    deque_init_copy_array(pdeq, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_includes(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_includes_if
 */
UT_CASE_DEFINATION(algo_includes_if)
void test_algo_includes_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_includes_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__invalid_second_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_includes_if(list_begin(plist), list_end(plist), deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(char*);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__first_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init(plist);
    deque_init_n(pdeq, 10);
    assert_false(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__second_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init(pdeq);
    assert_true(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__all_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init(plist);
    deque_init(pdeq);
    assert_true(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__bfun_NULL_true(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {2, 5, 6, 9};

    list_init_copy_array(plist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    deque_init_copy_array(pdeq, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__bfun_NULL_false(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {2, 5, 6, 9, 11};

    list_init_copy_array(plist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    deque_init_copy_array(pdeq, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__true(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_second[] = {9, 6, 5, 3};

    list_init_copy_array(plist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    deque_init_copy_array(pdeq, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_includes_if__false(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_second[] = {9, 6, 5, 3, -2};

    list_init_copy_array(plist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    deque_init_copy_array(pdeq, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_includes_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_set_union
 */
UT_CASE_DEFINATION(algo_set_union)
void test_algo_set_union__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_union(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_union__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(algo_equal(list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init(plist);
    deque_init_n(pdeq, 10);
    it = algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    list_init(plist);
    deque_init(pdeq);
    it = algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union__first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4};
    int an_second[] = {10, 11, 12, 13, 14};
    int an_result[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union__first_overlap_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist)-5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union__second_overlap_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {5, 5, 6, 7, 8, 9, 9, 9, 10, 11, 12, 13, 14};
    int an_second[] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 6, 7, 8, 9, 9, 9, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist)-5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union__second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {10, 11, 12, 13, 14};
    int an_second[] = {0, 1, 2, 3, 4};
    int an_result[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_set_union_if
 */
UT_CASE_DEFINATION(algo_set_union_if)
void test_algo_set_union_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_union_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_union_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union_if__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it, fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union_if__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union_if__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union_if__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_union_if__bfun_NULL_first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4};
    int an_second[] = {10, 11, 12, 13, 14};
    int an_result[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union_if__bfun_NULL_first_overlap_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist)-5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union_if__bfun_NULL_second_overlap_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {5, 5, 6, 7, 8, 9, 9, 9, 10, 11, 12, 13, 14};
    int an_second[] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8, 9};
    int an_result[] = {0, 1, 2, 3, 4, 5, 5, 6, 6, 6, 7, 8, 9, 9, 9, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist)-5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union_if__bfun_NULL_second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {10, 11, 12, 13, 14};
    int an_second[] = {0, 1, 2, 3, 4};
    int an_result[] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union_if__first_lead_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {14, 13, 12, 11, 10};
    int an_second[] = {4, 3, 2, 1, 0};
    int an_result[] = {14, 13, 12, 11, 10, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union_if__first_overlap_second(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5};
    int an_second[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_result[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist)-5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union_if__second_overlap_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {9, 8, 7, 6, 6, 6, 5, 4, 3, 2, 1, 0};
    int an_second[] = {14, 13, 12, 11, 10, 9, 9, 9, 8, 7, 6, 5, 5};
    int an_result[] = {14, 13, 12, 11, 10, 9, 9, 9, 8, 7, 6, 6, 6, 5, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist)-5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_union_if__second_lead_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {4, 3, 2, 1, 0};
    int an_second[] = {14, 13, 12, 11, 10};
    int an_result[] = {14, 13, 12, 11, 10, 4, 3, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec)+list_size(plist));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_union_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_set_intersection
 */
UT_CASE_DEFINATION(algo_set_intersection)
void test_algo_set_intersection__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_intersection(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_intersection__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_intersection(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection__result_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {4, 3, 2, 1, 0};
    int an_second[] = {14, 13, 12, 11, 10};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init(pdeq);
    it = algo_set_intersection(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    assert_true(deque_empty(pdeq));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection__result_not_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {1, 2, 3, 4, 4, 4, 5, 6};
    int an_second[] = {2, 3, 3, 4, 4, 8, 9};
    int an_result[] = {2, 3, 4, 4};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, 4);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_intersection(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_set_intersection_if
 */
UT_CASE_DEFINATION(algo_set_intersection_if)
void test_algo_set_intersection_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_intersection_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_intersection_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection_if__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it, fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection_if__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection_if__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection_if__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection_if__bfun_NULL_result_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {4, 3, 2, 1, 0};
    int an_second[] = {14, 13, 12, 11, 10};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init(pdeq);
    it = algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    assert_true(deque_empty(pdeq));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection_if__bfun_NULL_result_not_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {1, 2, 3, 4, 4, 4, 5, 6};
    int an_second[] = {2, 3, 3, 4, 4, 8, 9};
    int an_result[] = {2, 3, 4, 4};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, 4);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_intersection_if__result_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {4, 3, 2, 1, 0};
    int an_second[] = {10, 11, 12, 13, 14};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init(pdeq);
    it = algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    assert_true(deque_empty(pdeq));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_intersection_if__result_not_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {6, 5, 4, 4, 4, 3, 2, 1};
    int an_second[] = {9, 8, 4, 4, 3, 3, 2};
    int an_result[] = {4, 4, 3, 2};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, 4);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_intersection_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_set_difference
 */
UT_CASE_DEFINATION(algo_set_difference)
void test_algo_set_difference__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_difference(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_difference__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference__result_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {-3, 1, 3, 5};
    int an_result[] = {0, 1, 2, 4, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_difference__result_not_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {1, 1, 3, 3, 5, 7, 9, 9};
    int an_second[] = {0, 2, 4, 6, 8, 8};
    int an_result[] = {1, 1, 3, 3, 5, 7, 9, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_set_difference_if
 */
UT_CASE_DEFINATION(algo_set_difference_if)
void test_algo_set_difference_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_difference_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_difference_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference_if__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it, fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference_if__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference_if__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference_if__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_difference_if__bfun_NULL_result_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {-3, 1, 3, 5};
    int an_result[] = {0, 1, 2, 4, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_difference_if__bfun_NULL_result_not_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {1, 1, 3, 3, 5, 7, 9, 9};
    int an_second[] = {0, 2, 4, 6, 8, 8};
    int an_result[] = {1, 1, 3, 3, 5, 7, 9, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_difference_if__result_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 0};
    int an_second[] = {5, 3, 1, -5};
    int an_result[] = {9, 8, 7, 6, 4, 2, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_difference_if__result_not_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {9, 9, 7, 5, 3, 3, 1, 1};
    int an_second[] = {8, 8, 6, 4, 2, 0};
    int an_result[] = {9, 9, 7, 5, 3, 3, 1, 1};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, vector_size(pvec));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_set_symmetric_difference
 */
UT_CASE_DEFINATION(algo_set_symmetric_difference)
void test_algo_set_symmetric_difference__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_symmetric_difference(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_symmetric_difference__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_symmetric_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference__result_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {-3, 1, 3, 5};
    int an_result[] = {-3, 0, 1, 2, 4, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_symmetric_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_symmetric_difference__result_not_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {1, 1, 3, 3, 5, 7, 9, 9};
    int an_second[] = {0, 2, 4, 6, 8, 8};
    int an_result[] = {0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 8, 9, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_n(pdeq, deque_size(pdeq_result));
    it = algo_set_symmetric_difference(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_set_symmetric_difference_if
 */
UT_CASE_DEFINATION(algo_set_symmetric_difference_if)
void test_algo_set_symmetric_difference_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_set_symmetric_difference_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_set_symmetric_difference_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_end(plist), list_begin(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference_if__invalid_third_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), it, fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference_if__first_not_same_type(void** state)
{
    vector_t* pvec = create_vector(double);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference_if__second_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference_if__third_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_set_symmetric_difference_if__bfun_NULL_result_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {-3, 1, 3, 5};
    int an_result[] = {-3, 0, 1, 2, 4, 6, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_symmetric_difference_if__bfun_NULL_result_not_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {1, 1, 3, 3, 5, 7, 9, 9};
    int an_second[] = {0, 2, 4, 6, 8, 8};
    int an_result[] = {0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 8, 9, 9};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_n(pdeq, deque_size(pdeq_result));
    it = algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_symmetric_difference_if__result_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 0};
    int an_second[] = {5, 3, 1, -5};
    int an_result[] = {9, 8, 7, 6, 4, 2, 1, 0, -5};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_n(pdeq, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_set_symmetric_difference_if__result_not_difference(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_first[] = {9, 9, 7, 5, 3, 3, 1, 1};
    int an_second[] = {8, 8, 6, 4, 2, 0};
    int an_result[] = {9, 9, 8, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_n(pdeq, deque_size(pdeq_result));
    it = algo_set_symmetric_difference_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_max
 */
UT_CASE_DEFINATION(algo_max)
void test_algo_max__not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 1);
    deque_init_n(pdeq, 1);
    expect_assert_failure(algo_max(vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max__first_max(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 100);
    deque_init_elem(pdeq, 1, 10);
    it = algo_max(vector_begin(pvec), deque_begin(pdeq));
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max__second_max(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 10);
    it = algo_max(vector_begin(pvec), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max__equal(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 1);
    it = algo_max(vector_begin(pvec), deque_begin(pdeq));
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

/*
 * test algo_max_if
 */
UT_CASE_DEFINATION(algo_max_if)
void test_algo_max_if__not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 1);
    deque_init_n(pdeq, 1);
    expect_assert_failure(algo_max_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max_if__equal(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 1);
    it = algo_max_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max_if__bfun_NULL_first_max(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 100);
    deque_init_elem(pdeq, 1, 10);
    it = algo_max_if(vector_begin(pvec), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max_if__bfun_NULL_second_max(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 10);
    it = algo_max_if(vector_begin(pvec), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max_if__first_max(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 100);
    deque_init_elem(pdeq, 1, 10);
    it = algo_max_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_max_if__second_max(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 10);
    it = algo_max_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

/*
 * test algo_min
 */
UT_CASE_DEFINATION(algo_min)
void test_algo_min__not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 1);
    deque_init_n(pdeq, 1);
    expect_assert_failure(algo_min(vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min__second_min(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 100);
    deque_init_elem(pdeq, 1, 10);
    it = algo_min(vector_begin(pvec), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min__first_min(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 10);
    it = algo_min(vector_begin(pvec), deque_begin(pdeq));
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min__equal(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 1);
    it = algo_min(vector_begin(pvec), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

/*
 * test algo_min_if
 */
UT_CASE_DEFINATION(algo_min_if)
void test_algo_min_if__not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 1);
    deque_init_n(pdeq, 1);
    expect_assert_failure(algo_min_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min_if__equal(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 1);
    it = algo_min_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min_if__bfun_NULL_first_min(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 10);
    it = algo_min_if(vector_begin(pvec), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min_if__bfun_NULL_second_min(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 100);
    deque_init_elem(pdeq, 1, 10);
    it = algo_min_if(vector_begin(pvec), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min_if__first_min(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 1);
    deque_init_elem(pdeq, 1, 10);
    it = algo_min_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_min_if__second_min(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_elem(pvec, 1, 100);
    deque_init_elem(pdeq, 1, 10);
    it = algo_min_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

/*
 * test algo_max_element
 */
UT_CASE_DEFINATION(algo_max_element)
void test_algo_max_element__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_max_element(deque_begin(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_max_element__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_max_element(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_max_element__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_max_element(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_max_element__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = algo_max_element(deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_max_element__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 2, 0, 3, 9, 6, 5, 1, 7};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_max_element(deque_begin(pdeq), deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it) == 9);
    deque_destroy(pdeq);
}

void test_algo_max_element__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_max_element(deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, iterator_prev(deque_end(pdeq))));
    deque_destroy(pdeq);
}

/*
 * test algo_max_element_if
 */
UT_CASE_DEFINATION(algo_max_element_if)
void test_algo_max_element_if__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_max_element_if(deque_begin(pdeq), list_begin(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_max_element_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_max_element_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_max_element_if__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_max_element_if(it, deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_max_element_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = algo_max_element_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_max_element_if__bfun_NULL_normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 2, 0, 3, 9, 6, 5, 1, 7};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_max_element_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(*(int*)iterator_get_pointer(it) == 9);
    deque_destroy(pdeq);
}

void test_algo_max_element_if__bfun_NULL_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_max_element_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, iterator_prev(deque_end(pdeq))));
    deque_destroy(pdeq);
}

void test_algo_max_element_if__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 2, 0, 3, 9, 6, 5, 1, 7};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_max_element_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(*(int*)iterator_get_pointer(it) == 0);
    deque_destroy(pdeq);
}

void test_algo_max_element_if__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_max_element_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, iterator_prev(deque_end(pdeq))));
    deque_destroy(pdeq);
}

/*
 * test algo_min_element
 */
UT_CASE_DEFINATION(algo_min_element)
void test_algo_min_element__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_min_element(deque_begin(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_min_element__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_min_element(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_min_element__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_min_element(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_min_element__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = algo_min_element(deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_min_element__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 2, 0, 3, 9, 6, 5, 1, 7};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_min_element(deque_begin(pdeq), deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it) == 0);
    deque_destroy(pdeq);
}

void test_algo_min_element__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_min_element(deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test algo_min_element_if
 */
UT_CASE_DEFINATION(algo_min_element_if)
void test_algo_min_element_if__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_min_element_if(deque_begin(pdeq), list_begin(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_min_element_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_min_element_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_min_element_if__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_min_element_if(it, deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_min_element_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = algo_min_element_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_min_element_if__bfun_NULL_normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 2, 0, 3, 9, 6, 5, 1, 7};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_min_element_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(*(int*)iterator_get_pointer(it) == 0);
    deque_destroy(pdeq);
}

void test_algo_min_element_if__bfun_NULL_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_min_element_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_min_element_if__normal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {8, 4, 2, 0, 3, 9, 6, 5, 1, 7};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_min_element_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(*(int*)iterator_get_pointer(it) == 9);
    deque_destroy(pdeq);
}

void test_algo_min_element_if__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_min_element_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test algo_lexicographical_compare
 */
UT_CASE_DEFINATION(algo_lexicographical_compare)
void test_algo_lexicographical_compare__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_lexicographical_compare(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_lexicographical_compare__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_end(plist), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare__first_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init_n(plist, 10);
    assert_true(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare__second_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init(plist);
    assert_false(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare__all_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init(plist);
    assert_false(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare__less(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 1, 3};
    int an_second[] = {5, 8, 3, 1, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare__greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 1, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_lexicographical_compare(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_lexicographical_compare_if
 */
UT_CASE_DEFINATION(algo_lexicographical_compare_if)
void test_algo_lexicographical_compare_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_lexicographical_compare_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_lexicographical_compare_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_end(plist), list_begin(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_if__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_if__first_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init_n(plist, 10);
    assert_true(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_if__second_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init(plist);
    assert_false(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_if__all_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init(plist);
    assert_false(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_if__bfun_NULL_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 1, 3};
    int an_second[] = {5, 8, 3, 1, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_if__bfun_NULL_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 1, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_if__bfun_NULL_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_if__less(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 2, 9, 1, 3};
    int an_second[] = {5, 8, 3, 1, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_if__greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 1, 9, 0, 3};
    int an_second[] = {5, 8, 3, 2, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_if__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_false(algo_lexicographical_compare_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_lexicographical_compare_3way
 */
UT_CASE_DEFINATION(algo_lexicographical_compare_3way)
void test_algo_lexicographical_compare_3way__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_lexicographical_compare_3way(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_lexicographical_compare_3way__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_end(plist), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way__first_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init_n(plist, 10);
    assert_true(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)) < 0);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way__second_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init(plist);
    assert_true(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)) > 0);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way__all_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init(plist);
    assert_true(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)) == 0);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way__less(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 1, 3};
    int an_second[] = {5, 8, 3, 1, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)) < 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_3way__greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 1, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)) > 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_3way__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist)) == 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_lexicographical_compare_3way_if
 */
UT_CASE_DEFINATION(algo_lexicographical_compare_3way_if)
void test_algo_lexicographical_compare_3way_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_lexicographical_compare_3way_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_lexicographical_compare_3way_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_end(plist), list_begin(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way_if__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way_if__first_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init_n(plist, 10);
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int) < 0);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way_if__second_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init(plist);
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int) > 0);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way_if__all_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init(pdeq);
    list_init(plist);
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int) == 0);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_lexicographical_compare_3way_if__bfun_NULL_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 1, 3};
    int an_second[] = {5, 8, 3, 1, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL) < 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_3way_if__bfun_NULL_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 1, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL) > 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_3way_if__bfun_NULL_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL) == 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_3way_if__less(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 2, 9, 1, 3};
    int an_second[] = {5, 8, 3, 1, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int) < 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_3way_if__greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 1, 9, 0, 3};
    int an_second[] = {5, 8, 3, 2, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int) > 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_lexicographical_compare_3way_if__equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {5, 8, 3, 0, 9, 0, 3};
    int an_second[] = {5, 8, 3, 0, 9, 0, 3};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    assert_true(algo_lexicographical_compare_3way_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), fun_greater_int) == 0);
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_next_permutation
 */
UT_CASE_DEFINATION(algo_next_permutation)
void test_algo_next_permutation__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_next_permutation(deque_begin(pdeq), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_next_permutation__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_next_permutation(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_next_permutation__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_next_permutation(slist_begin(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

void test_algo_next_permutation__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_false(algo_next_permutation(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_next_permutation__equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_false(algo_next_permutation(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_next_permutation__first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 9, 8};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_next_permutation(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_next_permutation__middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 7, 5, 2, 8, 9, 1, 6, 4};
    int an_result[] = {3, 7, 5, 2, 8, 9, 4, 1, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_next_permutation(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_next_permutation__last(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_false(algo_next_permutation(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_next_permutation_if
 */
UT_CASE_DEFINATION(algo_next_permutation_if)
void test_algo_next_permutation_if__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_next_permutation_if(deque_begin(pdeq), list_end(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_next_permutation_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_next_permutation_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_next_permutation_if__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_next_permutation_if(slist_begin(pslist), slist_end(pslist), fun_greater_int));
    slist_destroy(pslist);
}

void test_algo_next_permutation_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_false(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_next_permutation_if__equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_false(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_next_permutation_if__bfun_NULL_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 9, 8};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_next_permutation_if__bfun_NULL_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 7, 5, 2, 8, 9, 1, 6, 4};
    int an_result[] = {3, 7, 5, 2, 8, 9, 4, 1, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_next_permutation_if__bfun_NULL_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_false(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_next_permutation_if__first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_next_permutation_if__middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 7, 5, 2, 8, 9, 1, 4, 6};
    int an_result[] = {3, 7, 5, 2, 8, 6, 9, 4, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_next_permutation_if__last(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_false(algo_next_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_prev_permutation
 */
UT_CASE_DEFINATION(algo_prev_permutation)
void test_algo_prev_permutation__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_prev_permutation(deque_begin(pdeq), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_prev_permutation__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_prev_permutation(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_prev_permutation__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_prev_permutation(slist_begin(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

void test_algo_prev_permutation__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_false(algo_prev_permutation(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_prev_permutation__equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_false(algo_prev_permutation(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_prev_permutation__first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_prev_permutation(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_prev_permutation__middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 7, 5, 2, 8, 9, 1, 4, 6};
    int an_result[] = {3, 7, 5, 2, 8, 6, 9, 4, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_prev_permutation(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_prev_permutation__last(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_false(algo_prev_permutation(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_prev_permutation_if
 */
UT_CASE_DEFINATION(algo_prev_permutation_if)
void test_algo_prev_permutation_if__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_prev_permutation_if(deque_begin(pdeq), list_end(plist), fun_greater_int));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_prev_permutation_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_prev_permutation_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_prev_permutation_if__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_prev_permutation_if(slist_begin(pslist), slist_end(pslist), fun_greater_int));
    slist_destroy(pslist);
}

void test_algo_prev_permutation_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_false(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_prev_permutation_if__equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_false(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_prev_permutation_if__bfun_NULL_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_prev_permutation_if__bfun_NULL_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 7, 5, 2, 8, 9, 1, 4, 6};
    int an_result[] = {3, 7, 5, 2, 8, 6, 9, 4, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_prev_permutation_if__bfun_NULL_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_false(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_prev_permutation_if__first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 9, 8};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_prev_permutation_if__middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 7, 5, 2, 8, 9, 1, 6, 4};
    int an_result[] = {3, 7, 5, 2, 8, 9, 4, 1, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_prev_permutation_if__last(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_false(algo_prev_permutation_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

