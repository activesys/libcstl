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
#include "cstl_algo_sorting_aux.h"

#include "ut_def.h"
#include "ut_cstl_algo_sorting_aux.h"

UT_SUIT_DEFINATION(cstl_algo_sorting_aux, _algo_lg)

/*
 * test _algo_lg
 */
UT_CASE_DEFINATION(_algo_lg)
void test__algo_lg__0(void** state)
{
    assert_true(_algo_lg(0) == 0);
}

void test__algo_lg__1(void** state)
{
    assert_true(_algo_lg(1) == 0);
}

void test__algo_lg__2_power_n(void** state)
{
    assert_true(_algo_lg(8) == 3);
}

void test__algo_lg__not_2_power_n(void** state)
{
    assert_true(_algo_lg(17) == 4);
}

/*
 * test _algo_median_of_three_if
 */
UT_CASE_DEFINATION(_algo_median_of_three_if)
void test__algo_median_of_three_if__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_median_of_three_if(list_begin(plist), vector_begin(pvec), iterator_next(vector_begin(pvec)), _fun_get_binary(vector_begin(pvec), _LESS_FUN)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_median_of_three_if__invalid_middle(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_middle = create_vector(int);

    vector_init_n(pvec, 10);
    vector_init_n(pvec_middle, 10);
    expect_assert_failure(_algo_median_of_three_if(vector_begin(pvec), vector_begin(pvec_middle), iterator_next(vector_begin(pvec)), _fun_get_binary(vector_begin(pvec), _LESS_FUN)));
    vector_destroy(pvec);
    vector_destroy(pvec_middle);
}

void test__algo_median_of_three_if__invalid_last(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_median_of_three_if(deque_begin(pdeq), iterator_next(deque_begin(pdeq)), deque_end(pdeq), _fun_get_binary(deque_begin(pdeq), _LESS_FUN)));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__bfun_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_median_of_three_if(deque_begin(pdeq), iterator_next(deque_begin(pdeq)), iterator_advance(deque_begin(pdeq), 2), NULL));
    deque_destroy(pdeq);
}

static void _test__algo_median_of_three_if(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__algo_median_of_three_if__first_less_middle_less_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_middle));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__first_less_middle_equal_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 2};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_last));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__first_equal_middle_less_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 1, 2};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_first));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__first_equal_middle_equal_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 1, 1};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_middle));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__middle_less_first_less_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 1, 3};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_first));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__middle_less_first_equal_last(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 1, 2};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_last));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__last_less_first_less_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 3, 1};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_first));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__last_less_first_equal_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 2, 1};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_middle));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__last_equal_first_less_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 1};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_first));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__first_less_last_less_middle(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 3, 2};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_last));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__middle_less_last_less_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {3, 1, 2};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_last));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__middle_equal_last_less_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {2, 1, 1};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_middle));
    deque_destroy(pdeq);
}

void test__algo_median_of_three_if__last_less_middle_less_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {3, 2, 1};
    iterator_t it_first;
    iterator_t it_middle;
    iterator_t it_last;
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it_first = deque_begin(pdeq);
    it_middle = iterator_next(it_first);
    it_last = iterator_next(it_middle);
    it = _algo_median_of_three_if(it_first, it_middle, it_last, _test__algo_median_of_three_if);
    assert_true(iterator_equal(it, it_middle));
    deque_destroy(pdeq);
}

