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
#include "cstl_algo_mutating_aux.h"

#include "ut_def.h"
#include "ut_cstl_algo_mutating_aux.h"

UT_SUIT_DEFINATION(cstl_algo_mutating_aux, _algo_rotate_forward)

/*
 * test _algo_rotate_forward
 */
UT_CASE_DEFINATION(_algo_rotate_forward)
void test__algo_rotate_forward__invalid_first_range(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 10);
    expect_assert_failure(_algo_rotate_forward(slist_begin(pslist_first), slist_begin(pslist_second), slist_end(pslist_second)));
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__algo_rotate_forward__invalid_first_range2(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_rotate_forward(iterator_advance(slist_begin(pslist), 3), slist_begin(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

void test__algo_rotate_forward__invalid_first_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_rotate_forward(it, iterator_advance(slist_begin(pslist), 3), slist_end(pslist)));
    slist_destroy(pslist);
}

void test__algo_rotate_forward__invalid_second_range(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 10);
    slist_init_n(pslist_second, 10);
    expect_assert_failure(_algo_rotate_forward(slist_begin(pslist_first), iterator_advance(slist_begin(pslist_first), 3), slist_end(pslist_second)));
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__algo_rotate_forward__invalid_second_range2(void** state)
{
    slist_t* pslist= create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_rotate_forward(slist_begin(pslist), slist_end(pslist), iterator_advance(slist_begin(pslist), 3)));
    slist_destroy(pslist);
}

void test__algo_rotate_forward__invalid_second_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_end(pslist);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_rotate_forward(slist_begin(pslist), iterator_advance(slist_begin(pslist), 3), it));
    slist_destroy(pslist);
}

void test__algo_rotate_forward__first_less_than_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_result = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {2, 3, 4, 5, 6, 7, 8, 9, 0, 1};

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    slist_init_copy_array(pslist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_rotate_forward(slist_begin(pslist), iterator_next(slist_begin(pslist)), slist_end(pslist));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

void test__algo_rotate_forward__first_equal_to_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_result = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {6, 7, 8, 9, 0, 1, 2, 3, 4, 5};

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    slist_init_copy_array(pslist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_rotate_forward(slist_begin(pslist), iterator_advance(slist_begin(pslist), 5), slist_end(pslist));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

void test__algo_rotate_forward__first_greater_than_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_result = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    slist_init_copy_array(pslist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_rotate_forward(slist_begin(pslist), iterator_advance(slist_begin(pslist), 9), slist_end(pslist));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

void test__algo_rotate_forward__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(_algo_rotate_forward(slist_begin(pslist), slist_begin(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

void test__algo_rotate_forward__first_range_empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_rotate_forward(slist_begin(pslist), slist_begin(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

void test__algo_rotate_forward__second_range_empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_rotate_forward(slist_begin(pslist), slist_end(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

/*
 * test _algo_partition_biditer
 */
UT_CASE_DEFINATION(_algo_partition_biditer)
void test__algo_partition_biditer__invalid_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_partition_biditer(list_begin(plist), deque_begin(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test__algo_partition_biditer__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_partition_biditer(deque_end(pdeq), deque_begin(pdeq), NULL));
    deque_destroy(pdeq);
}

void test__algo_partition_biditer__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_partition_biditer(slist_begin(pslist), slist_end(pslist), NULL));
    slist_destroy(pslist);
}

void test__algo_partition_biditer__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = _algo_partition_biditer(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_partition_biditer__ufun_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_partition_biditer(vector_begin(pvec), vector_end(pvec), NULL);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
}

static void _test__algo_partition_biditer__all_satify(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input < 10 ? true : false;
}
void test__algo_partition_biditer__all_satify(void** state)
{
    vector_t* pvec = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_partition_biditer(vector_begin(pvec), vector_end(pvec), _test__algo_partition_biditer__all_satify);
    assert_true(iterator_equal(it, vector_end(pvec)));
    vector_destroy(pvec);
}

static void _test__algo_partition_biditer__all_not_satify(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 10 ? true : false;
}
void test__algo_partition_biditer__all_not_satify(void** state)
{
    vector_t* pvec = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_partition_biditer(vector_begin(pvec), vector_end(pvec), _test__algo_partition_biditer__all_not_satify);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
}

static void _test__algo_partition_biditer__normal(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}
void test__algo_partition_biditer__normal(void** state)
{
    vector_t* pvec = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_partition_biditer(vector_begin(pvec), vector_end(pvec), _test__algo_partition_biditer__normal);
    assert_true(iterator_equal(it, iterator_advance(vector_begin(pvec), 5)));
    vector_destroy(pvec);
}

