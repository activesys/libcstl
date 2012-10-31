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
#include "ut_cstl_heap.h"

UT_SUIT_DEFINATION(cstl_heap, algo_make_heap)

/*
 * test algo_make_heap
 */
UT_CASE_DEFINATION(algo_make_heap)
void test_algo_make_heap__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_make_heap(vector_begin(pvec), deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_make_heap__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_make_heap(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_make_heap__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_make_heap(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_make_heap__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_make_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_make_heap__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    algo_make_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_size(pdeq) == 1);
    deque_destroy(pdeq);
}

void test_algo_make_heap__is_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 4, 5, 7, 3, 1, 2, 0, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy(pdeq_result, pdeq);
    algo_make_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_make_heap__is_first_half_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 4, 0, 1, 3, 5, 2, 7, 6};
    int an_result[] = {9, 8, 5, 7, 6, 3, 4, 2, 0, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_make_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_make_heap__is_second_half_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 2, 9, 7, 4, 8, 6, 1, 5, 3};
    int an_result[] = {9, 7, 8, 5, 4, 0, 6, 1, 2, 3};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_make_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_make_heap__not_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {9, 8, 6, 7, 4, 5, 2, 0, 3, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_make_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_make_heap_if
 */
UT_CASE_DEFINATION(algo_make_heap_if)
void test_algo_make_heap_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_make_heap_if(vector_begin(pvec), deque_end(pdeq), NULL));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_make_heap_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_make_heap_if(deque_end(pdeq), deque_begin(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_make_heap_if__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_make_heap_if(slist_begin(pslist), slist_end(pslist), NULL));
    slist_destroy(pslist);
}

void test_algo_make_heap_if__bfun_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {9, 8, 6, 7, 4, 5, 2, 0, 3, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_make_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_make_heap_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    algo_make_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test_algo_make_heap_if__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    algo_make_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_size(pdeq) == 1);
    deque_destroy(pdeq);
}

void test_algo_make_heap_if__is_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy(pdeq_result, pdeq);
    algo_make_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_make_heap_if__is_first_half_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {0, 1, 2, 7, 9, 5, 6, 3, 8, 4};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_make_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_make_heap_if__is_second_half_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {6, 8, 1, 0, 3, 5, 4, 2, 7, 9};
    int an_result[] = {0, 2, 1, 6, 3, 5, 4, 8, 7, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_make_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_make_heap_if__not_heap(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_result[] = {0, 1, 3, 2, 5, 4, 7, 9, 6, 8};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_make_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_is_heap
 */
UT_CASE_DEFINATION(algo_is_heap)
void test_algo_is_heap__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_heap(vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_is_heap__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_heap(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_heap__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_is_heap(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_is_heap__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_heap__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_heap__true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_make_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_heap__false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 3, 6, 5, 4, 7, 2, 1, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_is_heap__all_equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test algo_is_heap_if
 */
UT_CASE_DEFINATION(algo_is_heap_if)
void test_algo_is_heap_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_heap_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_is_heap_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_is_heap_if(list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_is_heap_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__bfun_NULL_true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__bfun_NULL_false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__bfun_NULL_all_equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_is_heap_if__all_equal(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

/*
 * test algo_push_heap
 */
UT_CASE_DEFINATION(algo_push_heap)
void test_algo_push_heap__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_push_heap(vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_push_heap__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_push_heap(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_push_heap__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_push_heap(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_push_heap__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_push_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_push_heap__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_begin(pdeq)));
    algo_push_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_push_heap__two(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), iterator_prev(deque_end(pdeq))));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_push_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_push_heap__three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 0, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), iterator_prev(deque_end(pdeq))));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_push_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_push_heap__more(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 5, 4, 3, 2, 1, 0, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), iterator_prev(deque_end(pdeq))));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_push_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test algo_push_heap_if
 */
UT_CASE_DEFINATION(algo_push_heap_if)
void test_algo_push_heap_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_push_heap_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_push_heap_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_push_heap_if(list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_push_heap_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_begin(pdeq), fun_greater_int));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__bfun_NULL_two(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), NULL));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__bfun_NULL_three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 0, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), NULL));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__bfun_NULL_more(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 5, 4, 3, 2, 1, 0, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), NULL));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__two(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), fun_greater_int));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), fun_greater_int));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_push_heap_if__more(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), fun_greater_int));
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_push_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

/*
 * test algo_pop_heap
 */
UT_CASE_DEFINATION(algo_pop_heap)
void test_algo_pop_heap__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_pop_heap(vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_pop_heap__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_pop_heap(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_pop_heap__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_pop_heap(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_pop_heap__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_pop_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_pop_heap__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_begin(pdeq)));
    algo_pop_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_pop_heap__two(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_pop_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(algo_is_heap(deque_begin(pdeq), iterator_prev(deque_end(pdeq))));
    deque_destroy(pdeq);
}

void test_algo_pop_heap__three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 0, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_pop_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(algo_is_heap(deque_begin(pdeq), iterator_prev(deque_end(pdeq))));
    deque_destroy(pdeq);
}

void test_algo_pop_heap__more(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_pop_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(algo_is_heap(deque_begin(pdeq), iterator_prev(deque_end(pdeq))));
    deque_destroy(pdeq);
}

/*
 * test algo_pop_heap_if
 */
UT_CASE_DEFINATION(algo_pop_heap_if)
void test_algo_pop_heap_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_pop_heap_if(vector_begin(pvec), deque_begin(pdeq), fun_greater_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_pop_heap_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_pop_heap_if(list_begin(plist), list_end(plist), fun_greater_int));
    list_destroy(plist);
}

void test_algo_pop_heap_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_begin(pdeq), fun_greater_int));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__bfun_NULL_two(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), NULL));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__bfun_NULL_three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 0, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), NULL));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__bfun_NULL_more(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), NULL));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), NULL));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__two(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__three(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), fun_greater_int));
    deque_destroy(pdeq);
}

void test_algo_pop_heap_if__more(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    algo_pop_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_false(algo_is_heap_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    assert_true(algo_is_heap_if(deque_begin(pdeq), iterator_prev(deque_end(pdeq)), fun_greater_int));
    deque_destroy(pdeq);
}

/*
 * test algo_sort_heap
 */
UT_CASE_DEFINATION(algo_sort_heap)
void test_algo_sort_heap__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_sort_heap(vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_sort_heap__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_sort_heap(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_sort_heap__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_sort_heap(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_sort_heap__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_sort_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_sort_heap__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    assert_true(algo_is_heap(deque_begin(pdeq), deque_begin(pdeq)));
    algo_sort_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_sort_heap__two(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 1};
    int an_result[] = {1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_sort_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_sort_heap__three(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 0, 1};
    int an_result[] = {0, 1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_sort_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test_algo_sort_heap__more(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    assert_true(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    algo_sort_heap(deque_begin(pdeq), deque_end(pdeq));
    assert_false(algo_is_heap(deque_begin(pdeq), deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

