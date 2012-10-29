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
#include "cstl_heap_aux.h"

#include "ut_def.h"
#include "ut_cstl_heap_aux.h"

UT_SUIT_DEFINATION(cstl_heap_aux, _algo_adjust_heap)

/*
 * test _algo_adjust_heap
 */
UT_CASE_DEFINATION(_algo_adjust_heap)
void test__algo_adjust_heap__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_adjust_heap(vector_begin(pvec), deque_end(pdeq), vector_begin(pvec), fun_less_int));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_adjust_heap__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_adjust_heap(deque_end(pdeq), deque_begin(pdeq), deque_begin(pdeq), fun_less_int));
    deque_destroy(pdeq);
}

void test__algo_adjust_heap__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(_algo_adjust_heap(list_begin(plist), list_end(plist), list_begin(plist), fun_less_int));
    list_destroy(plist);
}

void test__algo_adjust_heap__invalid_parent(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(_algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), vector_begin(pvec), fun_less_int));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test__algo_adjust_heap__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_empty(pdeq));
    deque_destroy(pdeq);
}

void test__algo_adjust_heap__one(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 1);
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_size(pdeq) == 1);
    deque_destroy(pdeq);
}

void test__algo_adjust_heap__two1(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 1};
    int an_result[] = {2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test__algo_adjust_heap__two2(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2};
    int an_result[] = {2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test__algo_adjust_heap__three1(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 2, 1};
    int an_result[] = {3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test__algo_adjust_heap__three2(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {2, 3, 1};
    int an_result[] = {3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test__algo_adjust_heap__three3(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {3, 1, 2};
    int an_result[] = {3, 1, 2};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

void test__algo_adjust_heap__three4(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3};
    int an_result[] = {3, 2, 1};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_adjust_heap(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), fun_less_int);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

