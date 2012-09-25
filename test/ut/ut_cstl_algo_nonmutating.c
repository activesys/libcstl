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
#include "cstl/calgorithm.h"

#include "ut_def.h"
#include "ut_cstl_algo_nonmutating.h"

UT_SUIT_DEFINATION(cstl_algo_nonmutating, algo_for_each)

/*
 * test algo_for_each
 */
UT_CASE_DEFINATION(algo_for_each)
void test_algo_for_each__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);

    expect_assert_failure(algo_for_each(vector_begin(pvec), list_begin(plist), NULL));

    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_for_each__invalid_range_2(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    expect_assert_failure(algo_for_each(vector_end(pvec), vector_begin(pvec), NULL));

    vector_destroy(pvec);
}

void test_algo_for_each__empty_range(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    algo_for_each(list_begin(plist), list_end(plist), NULL);
    assert_true(list_empty(plist));

    list_destroy(plist);
}

void test_algo_for_each__ufun_NULL(void** state)
{
    deque_t* pdeq1 = create_deque(int);
    deque_t* pdeq2 = create_deque(int);
    int i = 0;

    deque_init(pdeq1);
    deque_init(pdeq2);
    for (i = 0; i < 10; ++i) {
        deque_push_back(pdeq1, 1);
    }
    deque_assign(pdeq2, pdeq1);
    assert_true(deque_equal(pdeq1, pdeq2));
    algo_for_each(deque_begin(pdeq1), deque_end(pdeq1), NULL);
    assert_true(deque_equal(pdeq1, pdeq2));
    deque_destroy(pdeq1);
    deque_destroy(pdeq2);
}

static void _fun_test_algo_for_each__mutate_all(const void* cpv_input, void* pv_output)
{
    *(int*)cpv_input += 100;
}

void test_algo_for_each__mutate_all(void** state)
{
    slist_t* pslist1 = create_slist(int);
    slist_t* pslist2 = create_slist(int);
    iterator_t it1;
    iterator_t it2;
    int i = 0;

    slist_init(pslist1);
    slist_init(pslist2);

    for (i = 0; i < 10; ++i) {
        slist_push_front(pslist1, i);
    }
    slist_assign(pslist2, pslist1);
    algo_for_each(slist_begin(pslist1), slist_end(pslist1), _fun_test_algo_for_each__mutate_all);
    for (it1 = slist_begin(pslist1), it2 = slist_begin(pslist2);
         !iterator_equal(it1, slist_end(pslist1)) && !iterator_equal(it2, slist_end(pslist2));
         it1 = iterator_next(it1), it2 = iterator_next(it2)) {
        assert_true(
            *(int*)iterator_get_pointer(it1) ==
            *(int*)iterator_get_pointer(it2) + 100);
    }

    slist_destroy(pslist1);
    slist_destroy(pslist2);
}

void test_algo_for_each__mutate_partial(void** state)
{
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init_n(pvec, 10);
    algo_for_each(vector_begin(pvec), iterator_next_n(vector_begin(pvec), 5), _fun_test_algo_for_each__mutate_all);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        } else {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

