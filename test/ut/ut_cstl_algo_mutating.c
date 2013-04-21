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

#include "ut_def.h"
#include "ut_cstl_algo_mutating.h"

UT_SUIT_DEFINATION(cstl_algo_mutating, algo_copy)

/*
 * test algo_copy
 */
UT_CASE_DEFINATION(algo_copy)
void test_algo_copy__invalid_source_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_copy(vector_begin(pvec), list_begin(plist), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_copy__invalid_source_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_copy(deque_end(pdeq), deque_begin(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_copy__invalid_source_range3(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);
    iterator_t it;

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 993;
    expect_assert_failure(algo_copy(it, list_end(plist), slist_begin(pslist)));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_copy__invalid_dest_range(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);
    iterator_t it;

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = 993;
    expect_assert_failure(algo_copy(list_begin(plist), list_end(plist), it));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_copy__invalid_range_not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(char*);

    deque_init_n(pdeq, 20);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_copy(deque_begin(pdeq), deque_end(pdeq), vector_begin(pvec)));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_copy__source_range_empty(void** state)
{
    set_t* pset = create_set(int);
    list_t* plist = create_list(int);
    iterator_t it;

    set_init(pset);
    list_init_n(plist, 10);
    it = algo_copy(set_begin(pset), set_end(pset), list_begin(plist));
    assert_true(iterator_equal(list_begin(plist), it));
    set_destroy(pset);
    list_destroy(plist);
}

void test_algo_copy__overlapping_left(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {4, 5, 6, 7, 8, 9, 7, 8, 9};
    iterator_t it_first;
    iterator_t it_last;
    iterator_t it_result;
    iterator_t it_end;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it_first = iterator_advance(list_begin(plist), 3);
    it_last = list_end(plist);
    it_result = list_begin(plist);
    it_end = algo_copy(it_first, it_last, it_result);

    assert_true(iterator_distance(it_first, it_last) == iterator_distance(it_result, it_end));
    assert_true(list_equal(plist, plist_result));

    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_copy__overlapping_right(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    iterator_t it_first;
    iterator_t it_last;
    iterator_t it_result;
    iterator_t it_end;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it_first = list_begin(plist);
    it_last = iterator_advance(it_first, 6);
    it_result = iterator_advance(it_first, 3);
    it_end = algo_copy(it_first, it_last, it_result);

    assert_true(iterator_distance(it_first, it_last) == iterator_distance(it_result, it_end));
    assert_true(list_equal(plist, plist_result));

    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_copy__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, 10);
    it = algo_copy(vector_begin(pvec), vector_end(pvec), list_begin(plist));
    assert_true(iterator_distance(vector_begin(pvec), vector_end(pvec)) == iterator_distance(list_begin(plist), it));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_copy__cstr(void** state)
{
    deque_t* pdeq = create_deque(char*);
    slist_t* pslist = create_slist(char*);
    const char* as_array[] = {"a", "b", "c", "d", "e", "f"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    slist_init_n(pslist, 10);
    it = algo_copy(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist));
    assert_true(iterator_distance(deque_begin(pdeq), deque_end(pdeq)) == iterator_distance(slist_begin(pslist), it));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_copy__cstl_builtin(void** state)
{
    set_t* pset = create_set(deque_t<int>);
    list_t* plist = create_list(deque_t<int>);
    deque_t* pdeq = create_deque(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    iterator_t it;
    int i = 0;

    set_init(pset);
    list_init_n(plist, 10);
    deque_init(pdeq);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        deque_assign_array(pdeq, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        set_insert(pset, pdeq);
    }
    it = algo_copy(set_begin(pset), set_end(pset), list_begin(plist));
    assert_true(iterator_distance(set_begin(pset), set_end(pset)) == iterator_distance(list_begin(plist), it));
    assert_true(algo_equal(set_begin(pset), set_end(pset), list_begin(plist)));
    set_destroy(pset);
    list_destroy(plist);
    deque_destroy(pdeq);
}

typedef struct _tag_test_algo_copy__user_define {
    int a;
    int b;
} _test_algo_copy__user_define_t;
void test_algo_copy__user_define(void** state)
{
    multiset_t* pmset = NULL;
    deque_t* pdeq = NULL;
    _test_algo_copy__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_copy__user_define_t, NULL, NULL, NULL, NULL);
    pmset = create_multiset(_test_algo_copy__user_define_t);
    pdeq = create_deque(_test_algo_copy__user_define_t);
    multiset_init(pmset);
    deque_init_n(pdeq, 10);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        multiset_insert(pmset, &at_array[i]);
    }
    it = algo_copy(multiset_begin(pmset), multiset_end(pmset), deque_begin(pdeq));
    assert_true(iterator_distance(multiset_begin(pmset), multiset_end(pmset)) == iterator_distance(deque_begin(pdeq), it));
    assert_true(algo_equal(multiset_begin(pmset), multiset_end(pmset), deque_begin(pdeq)));
    multiset_destroy(pmset);
    deque_destroy(pdeq);
}

/*
 * test algo_copy_n
 */
UT_CASE_DEFINATION(algo_copy_n)
void test_algo_copy_n__invalid_source_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_copy_n(it, 10, list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_copy_n__invalid_dest_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_copy_n(deque_begin(pdeq), 10, it));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_copy_n__invalid_range_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_copy_n(vector_begin(pvec), 10, list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_copy_n__source_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_copy_n(deque_begin(pdeq), 0, iterator_next_n(deque_begin(pdeq), 5));
    assert_true(iterator_equal(it, iterator_next_n(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test_algo_copy_n__overlapping_left(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {3, 4, 5, 6, 7, 8, 9, 0, 9, 0};
    iterator_t it_first;
    iterator_t it_result;
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it_first = iterator_advance(list_begin(plist), 2);
    it_result = list_begin(plist);
    it = algo_copy_n(it_first, 8, it_result);
    assert_true(iterator_distance(it_result, it) == 8);
    assert_true(algo_equal(list_begin(plist), list_end(plist), list_begin(plist_result)));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_copy_n__overlapping_right(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    iterator_t it_first;
    iterator_t it_result;
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it_first = list_begin(plist);
    it_result = iterator_next(list_begin(plist));
    it = algo_copy_n(it_first, 9, it_result);
    assert_true(iterator_distance(it_result, it) == 9);
    assert_true(algo_equal(list_begin(plist), list_end(plist), list_begin(plist_result)));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_copy_n__c_builtin(void** state)
{
    set_t* pset = create_set(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    set_init_copy_array(pset, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, 10);
    it = algo_copy_n(set_begin(pset), 10, list_begin(plist));
    assert_true(iterator_distance(list_begin(plist), it) == 10);
    assert_true(algo_equal(set_begin(pset), set_end(pset), list_begin(plist)));
    set_destroy(pset);
    list_destroy(plist);
}

void test_algo_copy_n__cstr(void** state)
{
    multiset_t* pmset = create_multiset(char*);
    vector_t* pvec = create_vector(char*);
    const char* as_array[] = {"Windows 3.1", "Windows 95", "Windows 98", "Windows ME", "Windows 2000"};
    iterator_t it;

    multiset_init_copy_array(pmset, as_array, sizeof(as_array)/sizeof(as_array[0]));
    vector_init_n(pvec, 10);
    it = algo_copy_n(multiset_begin(pmset), 5, vector_begin(pvec));
    assert_true(iterator_distance(vector_begin(pvec), it));
    assert_true(algo_equal(multiset_begin(pmset), multiset_end(pmset), vector_begin(pvec)));
    multiset_destroy(pmset);
    vector_destroy(pvec);
}

void test_algo_copy_n__cstl_builtin(void** state)
{
    hash_set_t* phset = create_hash_set(vector_t<int>);
    deque_t* pdeq = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}, {3, 4, 5}};
    iterator_t it;
    int i = 0;

    hash_set_init(phset);
    deque_init_n(pdeq, 10);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        hash_set_insert(phset, pvec);
    }
    it = algo_copy_n(hash_set_begin(phset), hash_set_size(phset), deque_begin(pdeq));
    assert_true(iterator_distance(deque_begin(pdeq), it) == hash_set_size(phset));
    assert_true(algo_equal(hash_set_begin(phset), hash_set_end(phset), deque_begin(pdeq)));
    hash_set_destroy(phset);
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

typedef struct _tag_test_algo_copy_n__user_define {
    int a;
    int b;
} _test_algo_copy_n__user_define_t;
void test_algo_copy_n__user_define(void** state)
{
    hash_multiset_t* phmset = NULL;
    slist_t* pslist = NULL;
    _test_algo_copy_n__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_copy_n__user_define_t, NULL, NULL, NULL, NULL);
    phmset = create_hash_multiset(_test_algo_copy_n__user_define_t);
    pslist = create_slist(_test_algo_copy_n__user_define_t);
    hash_multiset_init(phmset);
    slist_init_n(pslist, 10);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        hash_multiset_insert(phmset, &at_array[i]);
    }
    it = algo_copy_n(hash_multiset_begin(phmset), hash_multiset_size(phmset), slist_begin(pslist));
    assert_true(iterator_distance(slist_begin(pslist), it) == hash_multiset_size(phmset));
    assert_true(algo_equal(hash_multiset_begin(phmset), hash_multiset_end(phmset), slist_begin(pslist)));
    hash_multiset_destroy(phmset);
    slist_destroy(pslist);
}

/*
 * test algo_copy_backward
 */
UT_CASE_DEFINATION(algo_copy_backward)
void test_algo_copy_backward__invalid_source_range(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_copy_backward(it, iterator_next(vector_begin(pvec)), iterator_next_n(vector_begin(pvec), 5)));
    vector_destroy(pvec);
}

void test_algo_copy_backward__invalid_source_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_copy_backward(list_end(plist), list_begin(plist), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_copy_backward__invalid_source_range3(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_copy_backward(list_begin(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_copy_backward__invalid_dest_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_copy_backward(deque_begin(pdeq), deque_end(pdeq), slist_end(pslist)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_copy_backward__invalid_range_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_copy_backward(vector_begin(pvec), vector_end(pvec), list_end(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_copy_backward__source_range_empty(void** state)
{
    set_t* pset = create_set(int);
    list_t* plist = create_list(int);
    iterator_t it;

    set_init(pset);
    list_init_n(plist, 10);
    it = algo_copy_backward(set_begin(pset), set_end(pset), list_end(plist));
    assert_true(iterator_equal(it, list_end(plist)));
    set_destroy(pset);
    list_destroy(plist);
}

void test_algo_copy_backward__overlapping_left(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {9, 0, 9, 0, 9, 0, 9, 0, 9, 0};
    iterator_t it_first;
    iterator_t it_last;
    iterator_t it_result;
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it_first = iterator_advance(list_begin(plist), 2);
    it_last = list_end(plist);
    it_result = iterator_advance(list_end(plist), -2);
    it = algo_copy_backward(it_first, it_last, it_result);
    assert_true(iterator_equal(it, list_begin(plist)));
    assert_true(algo_equal(list_begin(plist), list_end(plist), list_begin(plist_result)));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_copy_backward__overlapping_right(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 2, 3, 4, 1, 2, 3, 4, 5, 6};
    iterator_t it_first;
    iterator_t it_last;
    iterator_t it_result;
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it_first = list_begin(plist);
    it_last = iterator_advance(it_first, 6);
    it_result = list_end(plist);
    it = algo_copy_backward(it_first, it_last, it_result);
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist), 4)));
    assert_true(algo_equal(list_begin(plist), list_end(plist), list_begin(plist_result)));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_copy_backward__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist, 10);
    it = algo_copy_backward(vector_begin(pvec), vector_end(pvec), list_end(plist));
    assert_true(iterator_distance(it, list_end(plist)) == vector_size(pvec));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_copy_backward__cstr(void** state)
{
    set_t* pset = create_set(char*);
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"CentOS", "Fedora", "Ubuntu", "FreeBSD", "AIX"};
    iterator_t it;

    set_init_copy_array(pset, as_array, sizeof(as_array)/sizeof(as_array[0]));
    deque_init_n(pdeq, 10);
    it = algo_copy_backward(set_begin(pset), set_end(pset), deque_end(pdeq));
    assert_true(iterator_distance(it, deque_end(pdeq)) == set_size(pset));
    assert_true(algo_equal(set_begin(pset), set_end(pset), it));
    set_destroy(pset);
    deque_destroy(pdeq);
}

void test_algo_copy_backward__cstl_builtin(void** state)
{
    hash_set_t* phset = create_hash_set(vector_t<int>);
    list_t* plist = create_list(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][5] = {{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}, {4, 5, 6, 7, 8}, {5, 6, 7, 8, 9}};
    iterator_t it;
    int i = 0;

    hash_set_init(phset);
    list_init_n(plist, 10);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        hash_set_insert(phset, pvec);
    }
    it = algo_copy_backward(hash_set_begin(phset), hash_set_end(phset), list_end(plist));
    assert_true(iterator_distance(it, list_end(plist)) == hash_set_size(phset));
    assert_true(algo_equal(hash_set_begin(phset), hash_set_end(phset), it));
    hash_set_destroy(phset);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test_algo_copy_backward__user_define {
    int a;
    int b;
} _test_algo_copy_backward__user_define_t;
void test_algo_copy_backward__user_define(void** state)
{
    multiset_t* pmset = NULL;
    deque_t* pdeq = NULL;
    _test_algo_copy_backward__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_copy_backward__user_define_t, NULL, NULL, NULL, NULL);
    pmset = create_multiset(_test_algo_copy_backward__user_define_t);
    pdeq = create_deque(_test_algo_copy_backward__user_define_t);
    multiset_init(pmset);
    deque_init_n(pdeq, 10);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        multiset_insert(pmset, &at_array[i]);
    }
    it = algo_copy_backward(multiset_begin(pmset), multiset_end(pmset), deque_end(pdeq));
    assert_true(iterator_distance(it, deque_end(pdeq)) == multiset_size(pmset));
    assert_true(algo_equal(multiset_begin(pmset), multiset_end(pmset), it));
    multiset_destroy(pmset);
    deque_destroy(pdeq);
}

/*
 * test algo_swap and algo_iter_swap
 */
UT_CASE_DEFINATION(algo_swap_algo_iter_swap)
void test_algo_swap_algo_iter_swap__invalid_first(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = iterator_next(it_first);
    it_first._t_iteratortype = 199;
    expect_assert_failure(algo_swap(it_first, it_second));
    vector_destroy(pvec);
}

void test_algo_swap_algo_iter_swap__invalid_second(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_second;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_second = iterator_next(it_first);
    it_second._t_iteratortype = 199;
    expect_assert_failure(algo_swap(it_first, it_second));
    vector_destroy(pvec);
}

void test_algo_swap_algo_iter_swap__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(char*);

    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_swap(list_begin(plist), vector_begin(pvec)));
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_swap_algo_iter_swap__c_builtin(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;
    iterator_t it_second;

    list_init(plist);
    list_push_back(plist, 10);
    list_push_back(plist, 20);
    it_first = list_begin(plist);
    it_second = iterator_next(it_first);
    assert_true(*(int*)iterator_get_pointer(it_first) == 10);
    assert_true(*(int*)iterator_get_pointer(it_second) == 20);
    algo_swap(it_first, it_second);
    assert_true(*(int*)iterator_get_pointer(it_first) == 20);
    assert_true(*(int*)iterator_get_pointer(it_second) == 10);
    list_destroy(plist);
}

void test_algo_swap_algo_iter_swap__cstr(void** state)
{
    deque_t* pdeq = create_deque(char*);
    iterator_t it_first;
    iterator_t it_second;

    deque_init(pdeq);
    deque_push_back(pdeq, "Linux");
    deque_push_back(pdeq, "Windows");
    it_first = deque_begin(pdeq);
    it_second = iterator_next(it_first);
    assert_true(strcmp((char*)iterator_get_pointer(it_first), "Linux") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(it_second), "Windows") == 0);
    algo_swap(it_first, it_second);
    assert_true(strcmp((char*)iterator_get_pointer(it_first), "Windows") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(it_second), "Linux") == 0);
    deque_destroy(pdeq);
}

void test_algo_swap_algo_iter_swap__cstl_builtin(void** state)
{
    slist_t* pslist = create_slist(set_t<int>);
    set_t* pset = create_set(int);
    iterator_t it_first;
    iterator_t it_second;

    slist_init(pslist);
    set_init(pset);
    slist_push_front(pslist, pset);
    set_insert(pset, 100);
    slist_push_front(pslist, pset);
    it_first = slist_begin(pslist);
    it_second = iterator_next(it_first);
    assert_true(set_size((set_t*)iterator_get_pointer(it_first)) == 1);
    assert_true(set_size((set_t*)iterator_get_pointer(it_second)) == 0);
    algo_swap(it_first, it_second);
    assert_true(set_size((set_t*)iterator_get_pointer(it_first)) == 0);
    assert_true(set_size((set_t*)iterator_get_pointer(it_second)) == 1);
    slist_destroy(pslist);
    set_destroy(pset);
}

typedef struct _tag_test_algo_swap_algo_iter_swap__user_define {
    int a;
    int b;
} _test_algo_swap_algo_iter_swap__user_define_t;
void test_algo_swap_algo_iter_swap__user_define(void** state)
{
    vector_t* pvec = NULL;
    _test_algo_swap_algo_iter_swap__user_define_t t_elem;
    iterator_t it_first;
    iterator_t it_second;

    type_register(_test_algo_swap_algo_iter_swap__user_define_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(_test_algo_swap_algo_iter_swap__user_define_t);
    vector_init(pvec);
    t_elem.a = t_elem.b = 10;
    vector_push_back(pvec, &t_elem);
    t_elem.a = t_elem.b = 20;
    vector_push_back(pvec, &t_elem);
    it_first = vector_begin(pvec);
    it_second = iterator_next(it_first);
    assert_true(
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_first))->a == 10 &&
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_first))->b == 10);
    assert_true(
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_second))->a == 20 &&
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_second))->b == 20);
    algo_swap(it_first, it_second);
    assert_true(
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_first))->a == 20 &&
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_first))->b == 20);
    assert_true(
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_second))->a == 10 &&
        ((_test_algo_swap_algo_iter_swap__user_define_t*)iterator_get_pointer(it_second))->b == 10);
    vector_destroy(pvec);
}

/*
 * test algo_swap_ranges
 */
UT_CASE_DEFINATION(algo_swap_ranges)
void test_algo_swap_ranges__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_swap_ranges(vector_begin(pvec), list_begin(plist), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_swap_ranges__invalid_first_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_swap_ranges(deque_end(pdeq), deque_begin(pdeq), slist_begin(pslist)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_swap_ranges__invalid_first_range3(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);
    iterator_t it;

    set_init(pset);
    multiset_init(pmset);
    it = set_begin(pset);
    it._t_iteratortype = 199;
    expect_assert_failure(algo_swap_ranges(it, set_end(pset), multiset_begin(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_swap_ranges__invalid_second_range(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);
    iterator_t it;

    set_init(pset);
    multiset_init(pmset);
    it = multiset_begin(pmset);
    it._t_iteratortype = 199;
    expect_assert_failure(algo_swap_ranges(set_begin(pset), set_end(pset), it));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_swap_ranges__invalid_range_not_same_type(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_multiset_t* phmset = create_hash_multiset(char*);

    hash_set_init(phset);
    hash_multiset_init(phmset);
    expect_assert_failure(algo_swap_ranges(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset)));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

void test_algo_swap_ranges__first_range_empty(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);

    set_init(pset);
    multiset_init(pmset);
    assert_true(iterator_equal(algo_swap_ranges(set_begin(pset), set_end(pset), multiset_begin(pmset)), multiset_begin(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_swap_ranges__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {5, 6, 7, 8, 9, 0, 3, 4, 1, 2};
    iterator_t it_first1;
    iterator_t it_last1;
    iterator_t it_first2;
    iterator_t it_last2;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it_first1 = vector_begin(pvec);
    it_last1 = iterator_next_n(it_first1, 6);
    it_first2 = iterator_next_n(it_first1, 4);
    it_last2 = algo_swap_ranges(it_first1, it_last1, it_first2);
    assert_true(iterator_distance(it_first1, it_last1) == iterator_distance(it_first2, it_last2));
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

void test_algo_swap_ranges__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"abc", "def", "hij", "klm", "nop", "<--->", "AAAA", "BBBB", "CCCC", "DDDD", "EEEE"};
    const char* as_result[] = {"AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "<--->", "abc", "def", "hij", "klm", "nop"};
    iterator_t it_first1;
    iterator_t it_last1;
    iterator_t it_first2;
    iterator_t it_last2;

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    it_first1 = list_begin(plist);
    it_last1 = iterator_advance(it_first1, 5);
    it_first2 = iterator_advance(it_first1, 6);
    it_last2 = algo_swap_ranges(it_first1, it_last1, it_first2);
    assert_true(iterator_distance(it_first1, it_last1) == iterator_distance(it_first2, it_last2));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_swap_ranges__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    deque_t* pdeq_result = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}, {16, 17, 18}, {19, 20, 21}, {22, 23, 24}};
    int aan_result[][3] = {{7, 8, 9}, {10, 11, 12}, {13, 14, 15}, {16, 17, 18}, {19, 20, 21}, {22, 23, 24}, {1, 2, 3}, {4, 5, 6}};
    iterator_t it_first1;
    iterator_t it_last1;
    iterator_t it_first2;
    iterator_t it_last2;
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, pvec);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        vector_assign_array(pvec, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pvec);
    }
    it_first1 = iterator_next_n(deque_begin(pdeq), 2);
    it_last1 = deque_end(pdeq);
    it_first2 = deque_begin(pdeq);
    it_last2 = algo_swap_ranges(it_first1, it_last1, it_first2);
    assert_true(iterator_distance(it_first1, it_last1) == iterator_distance(it_first2, it_last2));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    vector_destroy(pvec);
}

typedef struct _tag_test_algo_swap_ranges__user_define {
    int a;
    int b;
} _test_algo_swap_ranges__user_define_t;
void test_algo_swap_ranges__user_define(void** state)
{
    list_t* plist = NULL;
    list_t* plist_result = NULL;
    _test_algo_swap_ranges__user_define_t at_array[] = {{1, 2}, {3, 4}, {0, 0}, {101, 102}, {103, 104}};
    _test_algo_swap_ranges__user_define_t at_result[] = {{101, 102}, {103, 104}, {0, 0}, {1, 2}, {3, 4}};
    iterator_t it_first1;
    iterator_t it_last1;
    iterator_t it_first2;
    iterator_t it_last2;
    int i = 0;

    type_register(_test_algo_swap_ranges__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_algo_swap_ranges__user_define_t);
    plist_result = create_list(_test_algo_swap_ranges__user_define_t);
    list_init(plist);
    list_init(plist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        list_push_back(plist, &at_array[i]);
    }
    for (i = 0; i <sizeof(at_result)/sizeof(at_result[0]); ++i) {
        list_push_back(plist_result, &at_result[i]);
    }
    it_first1 = iterator_advance(list_begin(plist), 3);
    it_last1 = list_end(plist);
    it_first2 = list_begin(plist);
    it_last2 = algo_swap_ranges(it_first1, it_last1, it_first2);
    assert_true(iterator_distance(it_first1, it_last1) == iterator_distance(it_first2, it_last2));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

/*
 * test algo_transform
 */
UT_CASE_DEFINATION(algo_transform)
void test_algo_transform__invalid_source_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_transform(vector_begin(pvec), list_begin(plist), list_begin(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_transform__invalid_source_range2(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_transform(list_end(plist), list_begin(plist), list_begin(plist), NULL));
    list_destroy(plist);
}

void test_algo_transform__invalid_source_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_transform(it, deque_end(pdeq), slist_begin(pslist), NULL));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_transform__invalid_dest_range(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);
    iterator_t it;

    set_init(pset);
    multiset_init(pmset);
    it = multiset_begin(pmset);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_transform(set_begin(pset), set_end(pset), it, NULL));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_transform__invalid_range_not_same_type(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_multiset_t* phmset = create_hash_multiset(double);

    hash_set_init(phset);
    hash_multiset_init(phmset);
    expect_assert_failure(algo_transform(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset), NULL));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

void test_algo_transform__source_range_empty(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);

    set_init(pset);
    multiset_init(pmset);
    assert_true(iterator_equal(algo_transform(set_begin(pset), set_end(pset), multiset_begin(pmset), NULL), multiset_begin(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_transform__ufun_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    size_t i = 0;
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_n(pvec_result, vector_size(pvec));
    it = algo_transform(vector_begin(pvec), vector_end(pvec), vector_begin(pvec_result), NULL);
    assert_true(iterator_equal(it, vector_end(pvec_result)));
    for (i = 0; i < vector_size(pvec_result); ++i) {
        assert_true(*(int*)vector_at(pvec_result, i) == 0);
    }
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

static void _test_algo_transform__c_builtin(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = abs(*(int*)cpv_input);
}
void test_algo_transform__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, 0};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_transform(vector_begin(pvec), vector_end(pvec), vector_begin(pvec), _test_algo_transform__c_builtin);
    assert_true(iterator_equal(it, vector_end(pvec)));
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

static void _test_algo_transform__cstr(const void* cpv_input, void* pv_output)
{
    size_t i = 0;

    for (i = 0; i < strlen((char*)cpv_input); ++i) {
        ((char*)pv_output)[i] = toupper(((char*)cpv_input)[i]);
    }
}
void test_algo_transform__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"abc", "def", "aaa", "mmm", "xyz"};
    const char* as_result[] = {"ABC", "DEF", "AAA", "MMM", "XYZ"};
    iterator_t it;

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    it = algo_transform(list_begin(plist), list_end(plist), list_begin(plist), _test_algo_transform__cstr);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

static void _test_algo_transform__cstl_builtin(const void* cpv_input, void* pv_output)
{
    size_t i = 0;
    vector_clear((vector_t*)pv_output);
    for (i = 0; i < vector_size((vector_t*)cpv_input); ++i) {
        vector_push_back((vector_t*)pv_output, *(int*)vector_at((vector_t*)cpv_input, i) + 100);
    }
}
void test_algo_transform__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    deque_t* pdeq_result = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}, {3, 4, 5}};
    int aan_result[][3] = {{101, 102, 103}, {104, 105, 106}, {107, 108, 109}, {100, 101, 102}, {103, 104, 105}};
    iterator_t it;
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, pvec);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        vector_assign_array(pvec, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pvec);
    }
    it = algo_transform(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq), _test_algo_transform__cstl_builtin);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    vector_destroy(pvec);
}

typedef struct _tag_test_algo_transform__user_define {
    int a;
    int b;
} _test_algo_transform__user_define_t;
static void _test_algo_transform__user_define(const void* cpv_input, void* pv_output)
{
    _test_algo_transform__user_define_t t_elem;
    memcpy(&t_elem, cpv_input, sizeof(_test_algo_transform__user_define_t));
    ((_test_algo_transform__user_define_t*)pv_output)->a = t_elem.b;
    ((_test_algo_transform__user_define_t*)pv_output)->b = t_elem.a;
}
void test_algo_transform__user_define(void** state)
{
    slist_t* pslist = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_transform__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_transform__user_define_t at_result[] = {{2, 1}, {4, 3}, {6, 5}, {8, 7}, {0, 9}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_transform__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_algo_transform__user_define_t);
    pslist_result = create_slist(_test_algo_transform__user_define_t);
    slist_init(pslist);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    it = algo_transform(slist_begin(pslist), slist_end(pslist), slist_begin(pslist), _test_algo_transform__user_define);
    assert_true(iterator_equal(it, slist_end(pslist)));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

/*
 * test algo_transform_binary
 */
UT_CASE_DEFINATION(algo_transform_binary)
void test_algo_transform_binary__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_transform_binary(vector_begin(pvec), list_begin(plist), list_begin(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__invalid_first_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_transform_binary(vector_end(pvec), vector_begin(pvec), list_begin(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__invalid_first_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = vector_end(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_transform_binary(vector_begin(pvec), it, list_begin(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_transform_binary(vector_begin(pvec), vector_end(pvec), it, deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__invalid_dest_range(void** state)
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
    expect_assert_failure(algo_transform_binary(vector_begin(pvec), vector_end(pvec), list_begin(plist), it, NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__invalid_range_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_transform_binary(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__invalid_range_not_same_type2(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_transform_binary(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__first_range_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    it = algo_transform_binary(vector_begin(pvec), vector_begin(pvec), list_begin(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_transform_binary__bfun_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    deque_init_n(pdeq, 10);
    it = algo_transform_binary(vector_begin(pvec), vector_end(pvec), vector_begin(pvec), list_begin(plist), NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(algo_equal(list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

static void _test_algo_transform_binary__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_first + *(int*)cpv_second;
}
void test_algo_transform_binary__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_array2[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    it = algo_transform_binary(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_begin(pdeq), _test_algo_transform_binary__c_builtin);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

static void _test_algo_transform_binary__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
}

void test_algo_transform_binary__cstr(void** state)
{
    vector_t* pvec = create_vector(char*);
    list_t* plist = create_list(char*);
    deque_t* pdeq = create_deque(char*);
    slist_t* pslist = create_slist(char*);
    const char* as_array1[] = {"abc", "def", "hij", "opq", "mno"};
    const char* as_array2[] = {"ABC", "DEF", "HIJ", "OPQ", "MNO"};
    const char* as_array3[] = {"xxxx", "xxxx", "xxxx", "xxxx", "xxxx"};
    iterator_t it;

    vector_init_copy_array(pvec, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    list_init_copy_array(plist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    deque_init_copy_array(pdeq, as_array3, sizeof(as_array3)/sizeof(as_array3[0]));
    slist_init_n(pslist, 5);
    it = algo_transform_binary(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_begin(pdeq), _test_algo_transform_binary__cstr);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

static void _test_algo_transform_binary__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    set_clear((set_t*)pv_output);
    set_insert_range((set_t*)pv_output, set_begin((set_t*)cpv_first), set_end((set_t*)cpv_first));
    set_insert_range((set_t*)pv_output, set_begin((set_t*)cpv_second), set_end((set_t*)cpv_second));
}
void test_algo_transform_binary__cstl_builtin(void** state)
{
    vector_t* pvec = create_vector(set_t<int>);
    list_t* plist = create_list(set_t<int>);
    deque_t* pdeq = create_deque(set_t<int>);
    slist_t* pslist = create_slist(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    int aan_array2[][2] = {{100, 101}, {102, 103}, {104, 105}, {106, 107}, {108, 109}};
    int aan_result[][5] = {{13, 14, 15, 108, 109}, {10, 11, 12, 106, 107}, {7, 8, 9, 104, 105}, {4, 5, 6, 102, 103}, {1, 2, 3, 100, 101}};
    iterator_t it;
    int i = 0;

    vector_init(pvec);
    list_init(plist);
    deque_init_n(pdeq, 5);
    slist_init(pslist);
    set_init(pset);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        vector_push_back(pvec, pset);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        list_push_back(plist, pset);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        slist_push_front(pslist, pset);
    }
    it = algo_transform_binary(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_begin(pdeq), _test_algo_transform_binary__cstl_builtin);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
    set_destroy(pset);
}

typedef struct _tag_test_algo_transform_binary__user_define {
    int a;
    int b;
} _test_algo_transform_binary__user_define_t;
static void _test_algo_transform_binary__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    _test_algo_transform_binary__user_define_t* pt_first = ((_test_algo_transform_binary__user_define_t*)cpv_first);
    _test_algo_transform_binary__user_define_t* pt_second = ((_test_algo_transform_binary__user_define_t*)cpv_second);
    _test_algo_transform_binary__user_define_t* pt_output = ((_test_algo_transform_binary__user_define_t*)pv_output);

    pt_output->a = pt_first->a + pt_second->a;
    pt_output->b = pt_first->b + pt_second->b;
}
void test_algo_transform_binary__user_define(void** state)
{
    vector_t* pvec = NULL;
    list_t* plist = NULL;
    deque_t* pdeq = NULL;
    slist_t* pslist = NULL;
    _test_algo_transform_binary__user_define_t at_array1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_transform_binary__user_define_t at_array2[] = {{-1, -2}, {-3, -4}, {-5, -6}, {-7, -8}, {-9, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_transform_binary__user_define_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(_test_algo_transform_binary__user_define_t);
    plist = create_list(_test_algo_transform_binary__user_define_t);
    pdeq = create_deque(_test_algo_transform_binary__user_define_t);
    pslist = create_slist(_test_algo_transform_binary__user_define_t);
    vector_init(pvec);
    list_init(plist);
    deque_init_n(pdeq, 5);
    slist_init_n(pslist, 5);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        vector_push_back(pvec, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        list_push_back(plist, &at_array2[i]);
    }
    it = algo_transform_binary(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_begin(pdeq), _test_algo_transform_binary__user_define);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

/*
 *  test algo_replace
 */
UT_CASE_DEFINATION(algo_replace)
void test_algo_replace__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_replace(vector_begin(pvec), list_begin(plist), 0, 10));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_replace__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_replace(deque_end(pdeq), deque_begin(pdeq), 0, 19));
    deque_destroy(pdeq);
}

void test_algo_replace__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_replace(it, slist_end(pslist), 0, 10));
    slist_destroy(pslist);
}

void test_algo_replace__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {9, 2, 3, 9, 9, 9, 9, 9, 0};
    int an_result[] = {0, 2, 3, 0, 0, 0, 0, 0, 0};

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_replace(vector_begin(pvec), vector_end(pvec), 9, 0);
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

void test_algo_replace__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"Windows", "Fedora", "Windows", "FreeBSD", "AIX"};
    const char* as_result[] = {"Linux", "Fedora", "Linux", "FreeBSD", "AIX"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    algo_replace(list_begin(plist), list_end(plist), "Windows", "Linux");
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_replace__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset_1 = create_set(int);
    set_t* pset_2 = create_set(int);
    int aan_array[][3] = {{1, 2, 3}, {1, 2, 3}, {7, 8, 9}, {1, 2, 3}, {1, 2, 3}};
    int aan_result[][3] = {{100, 200, 300}, {100, 200, 300}, {7, 8, 9}, {100, 200, 300}, {100, 200, 300}};
    int an_array1[] = {1, 2, 3};
    int an_array2[] = {100, 200, 300};
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    set_init(pset_1);
    set_init(pset_2);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        set_clear(pset_1);
        set_insert_array(pset_1, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, pset_1);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        set_clear(pset_2);
        set_insert_array(pset_2, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pset_2);
    }
    set_clear(pset_1);
    set_clear(pset_2);
    set_insert_array(pset_1, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    set_insert_array(pset_2, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    algo_replace(deque_begin(pdeq), deque_end(pdeq), pset_1, pset_2);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    set_destroy(pset_1);
    set_destroy(pset_2);
}

typedef struct _tag_test_algo_replace__user_define {
    int a;
    int b;
} _test_algo_replace__user_define_t;
void test_algo_replace__user_define(void** state)
{
    slist_t* pslist = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_replace__user_define_t at_array[] = {{8, 8}, {8, 8}, {8, 8}, {8, 8}, {8, 8}};
    _test_algo_replace__user_define_t at_result[] = {{1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}};
    int i = 0;

    type_register(_test_algo_replace__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_algo_replace__user_define_t);
    pslist_result = create_slist(_test_algo_replace__user_define_t);
    slist_init(pslist);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[i]); ++i) {
        slist_push_front(pslist, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    algo_replace(slist_begin(pslist), slist_end(pslist), &at_array[0], &at_result[0]);
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

/*
 * test algo_replace_copy
 */
UT_CASE_DEFINATION(algo_replace_copy)
void test_algo_replace_copy__invalid_source_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_replace_copy(vector_begin(pvec), list_begin(plist), deque_begin(pdeq), 0, 10));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_replace_copy__invalid_source_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_replace_copy(deque_end(pdeq), deque_begin(pdeq), slist_begin(pslist), 0, 10));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_replace_copy__invalid_source_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_replace_copy(it, vector_end(pvec), deque_begin(pdeq), 0, 10));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_replace_copy__invalid_dest_range(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);
    iterator_t it;

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_replace_copy(list_begin(plist), list_end(plist), it, 0, 10));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_replace_copy__invalid_range_not_same_type(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(char*);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_replace_copy(vector_begin(pvec), vector_end(pvec), list_begin(plist), 0, 0));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_replace_copy__source_range_empty(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);

    set_init(pset);
    multiset_init(pmset);
    algo_replace_copy(set_begin(pset), set_end(pset), multiset_begin(pmset), 0, 100);
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_replace_copy__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 3, 5, 0, 29, 1, 6, 72, 1, 1};
    int an_result[] = {0, 3, 5, 0, 29, 0, 6, 72, 0, 0};

    vector_init_copy_array(pvec_src, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_n(pvec_dest, 10);
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_replace_copy(vector_begin(pvec_src), vector_end(pvec_src), vector_begin(pvec_dest), 1, 0);
    assert_true(vector_equal(pvec_dest, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_dest);
    vector_destroy(pvec_result);
}

void test_algo_replace_copy__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_dest = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"Windows", "Linux", "Linux", "Windows", "Windows"};
    const char* as_result[] = {"XXOO", "Linux", "Linux", "XXOO", "XXOO"};

    list_init_copy_array(plist_src, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_n(plist_dest, 5);
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    algo_replace_copy(list_begin(plist_src), list_end(plist_src), list_begin(plist_dest), "Windows", "XXOO");
    assert_true(list_equal(plist_result, plist_dest));
    list_destroy(plist_src);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

void test_algo_replace_copy__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_dest = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    set_t* pset_new = create_set(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}, {4, 5, 6}};
    int aan_result[][3] = {{100, 200, 300}, {4, 5, 6}, {7, 8, 9}, {100, 200, 300}, {4, 5, 6}};
    int i = 0;

    deque_init(pdeq_src);
    deque_init_n(pdeq_dest, 5);
    deque_init(pdeq_result);
    set_init(pset);
    set_init(pset_new);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq_src, pset);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pset);
    }
    set_clear(pset);
    set_insert_array(pset, aan_array[0], sizeof(aan_array[0])/sizeof(aan_array[0][0]));
    set_clear(pset_new);
    set_insert_array(pset_new, aan_result[0], sizeof(aan_result[0])/sizeof(aan_result[0][0]));
    algo_replace_copy(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest), pset, pset_new);
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_result);
    set_destroy(pset);
    set_destroy(pset_new);
}

typedef struct _tag_test_algo_replace_copy__user_define {
    int a;
    int b;
} _test_algo_replace_copy__user_define_t;
void test_algo_replace_copy__user_define(void** state)
{
    slist_t* pslist_src = NULL;
    slist_t* pslist_dest = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_replace_copy__user_define_t at_array[] = {{1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}};
    _test_algo_replace_copy__user_define_t at_result[] = {{100, 100}, {100, 100}, {100, 100}, {100, 100}, {100, 100}};
    int i = 0;

    type_register(_test_algo_replace_copy__user_define_t, NULL, NULL, NULL, NULL);
    pslist_src = create_slist(_test_algo_replace_copy__user_define_t);
    pslist_dest = create_slist(_test_algo_replace_copy__user_define_t);
    pslist_result = create_slist(_test_algo_replace_copy__user_define_t);
    slist_init(pslist_src);
    slist_init_n(pslist_dest, 5);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist_src, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    algo_replace_copy(slist_begin(pslist_src), slist_end(pslist_src), slist_begin(pslist_dest), &at_array[0], &at_result[0]);
    assert_true(slist_equal(pslist_dest, pslist_result));
    slist_destroy(pslist_src);
    slist_destroy(pslist_dest);
    slist_destroy(pslist_result);
}

/*
 * test algo_generate
 */
UT_CASE_DEFINATION(algo_generate)
void test_algo_generate__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_generate(vector_begin(pvec), list_begin(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_generate__invalid_range2(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_generate(list_end(plist), list_begin(plist), NULL));
    list_destroy(plist);
}

void test_algo_generate__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_generate(it, deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_generate__range_empty(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    algo_generate(set_begin(pset), set_end(pset), NULL);
    assert_true(set_empty(pset));
    set_destroy(pset);
}

void test_algo_generate__ufun_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);

    vector_init_n(pvec, 10);
    vector_init_n(pvec_result, 10);
    algo_generate(vector_begin(pvec), vector_end(pvec), NULL);
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

static void _test_algo_generate__c_builtin(const void* cpv_input, void* pv_output)
{
    static int n_elem = 0;
    *(int*)pv_output = n_elem++ * 100;
}
void test_algo_generate__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_result[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900};

    vector_init_n(pvec, 10);
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_generate(vector_begin(pvec), vector_end(pvec), _test_algo_generate__c_builtin);
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

static void _test_algo_generate__cstr(const void* cpv_input, void* pv_output)
{
}
void test_algo_generate__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);

    list_init_elem(plist, 10, "abc");
    list_init_elem(plist_result, 10, "abc");
    algo_generate(list_begin(plist), list_end(plist), _test_algo_generate__cstr);
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

static void _test_algo_generate__cstl_builtin(const void* cpv_input, void* pv_output)
{
    static int n_elem = 0;
    set_insert((set_t*)pv_output, n_elem++);
}
void test_algo_generate__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_result[][1] = {{0}, {1}, {2}, {3}, {4}};
    int i = 0;

    deque_init_n(pdeq, 5);
    deque_init(pdeq_result);
    set_init(pset);
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pset);
    }
    algo_generate(deque_begin(pdeq), deque_end(pdeq), _test_algo_generate__cstl_builtin);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test_algo_generate__user_define {
    int a;
    int b;
} _test_algo_generate__user_define_t;
static void _test_algo_generate__user_define(const void* cpv_input, void* pv_output)
{
    static int n_elem = 4;
    ((_test_algo_generate__user_define_t*)pv_output)->a = ((_test_algo_generate__user_define_t*)pv_output)->b = n_elem--;
}
void test_algo_generate__user_define(void** state)
{
    slist_t* pslist = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_generate__user_define_t at_result[] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}};
    int i = 0;

    type_register(_test_algo_generate__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_algo_generate__user_define_t);
    pslist_result = create_slist(_test_algo_generate__user_define_t);
    slist_init_n(pslist, 5);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    algo_generate(slist_begin(pslist), slist_end(pslist), _test_algo_generate__user_define);
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

/*
 * test algo_generate_n
 */
UT_CASE_DEFINATION(algo_generate_n)
void test_algo_generate_n__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_generate_n(it, 10, NULL));
    vector_destroy(pvec);
}

void test_algo_generate_n__empty(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init(plist);
    it = algo_generate_n(list_begin(plist), 0, NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_empty(plist));
    list_destroy(plist);
}

void test_algo_generate_n__ufun_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    iterator_t it;

    deque_init_elem(pdeq, 10, 100);
    deque_init_copy(pdeq_result, pdeq);
    it = algo_generate_n(deque_begin(pdeq), 10, NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

static void _test_algo_generate_n__c_builtin(const void* cpv_input, void* pv_output)
{
    static int n_elem = 0;
    *(int*)pv_output = n_elem++ * 100;
}
void test_algo_generate_n__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_result[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900};
    iterator_t it;

    vector_init_n(pvec, 10);
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_generate_n(vector_begin(pvec), 10, _test_algo_generate_n__c_builtin);
    assert_true(iterator_equal(it, vector_end(pvec)));
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

static void _test_algo_generate_n__cstr(const void* cpv_input, void* pv_output)
{
}
void test_algo_generate_n__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    iterator_t it;

    list_init_elem(plist, 10, "abc");
    list_init_elem(plist_result, 10, "abc");
    it = algo_generate_n(list_begin(plist), 10, _test_algo_generate_n__cstr);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

static void _test_algo_generate_n__cstl_builtin(const void* cpv_input, void* pv_output)
{
    static int n_elem = 0;
    set_insert((set_t*)pv_output, n_elem++);
}
void test_algo_generate_n__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_result[][1] = {{0}, {1}, {2}, {3}, {4}};
    iterator_t it;
    int i = 0;

    deque_init_n(pdeq, 5);
    deque_init(pdeq_result);
    set_init(pset);
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pset);
    }
    it = algo_generate_n(deque_begin(pdeq), 5, _test_algo_generate_n__cstl_builtin);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test_algo_generate_n__user_define {
    int a;
    int b;
} _test_algo_generate_n__user_define_t;
static void _test_algo_generate_n__user_define(const void* cpv_input, void* pv_output)
{
    static int n_elem = 4;
    ((_test_algo_generate_n__user_define_t*)pv_output)->a = ((_test_algo_generate_n__user_define_t*)pv_output)->b = n_elem--;
}
void test_algo_generate_n__user_define(void** state)
{
    slist_t* pslist = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_generate_n__user_define_t at_result[] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_generate_n__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_algo_generate_n__user_define_t);
    pslist_result = create_slist(_test_algo_generate_n__user_define_t);
    slist_init_n(pslist, 5);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    it = algo_generate_n(slist_begin(pslist), 5, _test_algo_generate_n__user_define);
    assert_true(iterator_equal(it, slist_end(pslist)));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

/*
 * test algo_remove_if
 */
UT_CASE_DEFINATION(algo_remove_if)
void test_algo_remove_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_remove_if(vector_begin(pvec), list_begin(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_remove_if__invalid_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(algo_remove_if(vector_end(pvec), vector_begin(pvec), NULL));
    vector_destroy(pvec);
}

void test_algo_remove_if__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_remove_if(it, deque_end(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_remove_if__empty(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init(plist);
    it = algo_remove_if(list_begin(plist), list_end(plist), NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(list_empty(plist));
    list_destroy(plist);
}

void test_algo_remove_if__ufun_NULL(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_elem(pslist, 10, 100);
    it = algo_remove_if(slist_begin(pslist), slist_end(pslist), NULL);
    assert_true(iterator_equal(it, slist_end(pslist)));
    slist_destroy(pslist);
}

static void _test_algo_remove_if__c_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 3 == 0 ? true : false;
}
void test_algo_remove_if__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 2, 4, 5, 7, 8, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_remove_if(vector_begin(pvec_src), vector_end(pvec_src), _test_algo_remove_if__c_builtin);
    assert_true(iterator_equal(it, iterator_advance(vector_begin(pvec_src), 6)));
    assert_true(vector_equal(pvec_src, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_result);
}

static void _test_algo_remove_if__cstr(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = strncmp((char*)cpv_input, "Windows", strlen("Windows")) == 0 ? true : false;
}
void test_algo_remove_if__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_src[] = {"Windows 8", "Windows 7", "Windows vista", "FreeBSD", "Windows XP", "Windows 2000", "Windows ME"};
    const char* as_result[] = {"FreeBSD", "Windows 7", "Windows vista", "FreeBSD", "Windows XP", "Windows 2000", "Windows ME"};
    iterator_t it;

    list_init_copy_array(plist_src, as_src, sizeof(as_src)/sizeof(as_src[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    it = algo_remove_if(list_begin(plist_src), list_end(plist_src), _test_algo_remove_if__cstr);
    assert_true(iterator_equal(it, iterator_next(list_begin(plist_src))));
    assert_true(list_equal(plist_src, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_result);
}

static void _test_algo_remove_if__cstl_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = set_size((set_t*)cpv_input) == 3 ? true : false;
}
void test_algo_remove_if__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_src[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}, {3, 4, 5}};
    int aan_result[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}, {3, 4, 5}};
    iterator_t it;
    int i = 0;

    deque_init(pdeq_src);
    deque_init(pdeq_result);
    set_init(pset);
    for (i = 0; i < sizeof(aan_src)/sizeof(aan_src[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_src[i], sizeof(aan_src[i])/sizeof(aan_src[i][0]));
        deque_push_back(pdeq_src, pset);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pset);
    }
    it = algo_remove_if(deque_begin(pdeq_src), deque_end(pdeq_src), _test_algo_remove_if__cstl_builtin);
    assert_true(iterator_equal(it, deque_begin(pdeq_src)));
    assert_true(deque_equal(pdeq_src, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test_algo_remove_if__user_define {
    int a;
    int b;
} _test_algo_remove_if__user_define_t;
static void _test_algo_remove_if__user_define(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output =
        ((_test_algo_remove_if__user_define_t*)cpv_input)->a ==
        ((_test_algo_remove_if__user_define_t*)cpv_input)->b ?
        true : false;
}
void test_algo_remove_if__user_define(void** state)
{
    slist_t* pslist_src = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_remove_if__user_define_t at_src[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_remove_if__user_define_t at_result[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_remove_if__user_define_t, NULL, NULL, NULL, NULL);
    pslist_src = create_slist(_test_algo_remove_if__user_define_t);
    pslist_result = create_slist(_test_algo_remove_if__user_define_t);
    slist_init(pslist_src);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_src)/sizeof(at_src[0]); ++i) {
        slist_push_front(pslist_src, &at_src[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    it = algo_remove_if(slist_begin(pslist_src), slist_end(pslist_src), _test_algo_remove_if__user_define);
    assert_true(iterator_equal(it, slist_end(pslist_src)));
    assert_true(slist_equal(pslist_src, pslist_result));
    slist_destroy(pslist_src);
    slist_destroy(pslist_result);
}

/*
 * test algo_remove_copy_if
 */
UT_CASE_DEFINATION(algo_remove_copy_if)
void test_algo_remove_copy_if__invalid_source_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_remove_copy_if(vector_begin(pvec), list_begin(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_remove_copy_if__invalid_source_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_remove_copy_if(vector_end(pvec), vector_begin(pvec), list_begin(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_remove_copy_if__invalid_source_range3(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);
    iterator_t it;

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_remove_copy_if(it, list_end(plist), slist_begin(pslist), NULL));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_remove_copy_if__invalid_dest_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_remove_copy_if(vector_begin(pvec), vector_end(pvec), it, NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_remove_copy_if__invalid_range_not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_remove_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_remove_copy_if__source_range_empty(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init(plist);
    deque_init(pdeq);
    it = algo_remove_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_remove_copy_if__ufun_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it;

    vector_init_elem(pvec, 10, 100);
    list_init_n(plist, 10);
    it = algo_remove_copy_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

static void _test_algo_remove_copy_if__c_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 3 == 0 ? true : false;
}
void test_algo_remove_copy_if__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 2, 4, 5, 7, 8, 0, 0, 0, 0};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    vector_init_n(pvec_dest, vector_size(pvec_src));
    it = algo_remove_copy_if(vector_begin(pvec_src), vector_end(pvec_src), vector_begin(pvec_dest), _test_algo_remove_copy_if__c_builtin);
    assert_true(iterator_equal(it, iterator_advance(vector_begin(pvec_dest), 6)));
    assert_true(vector_equal(pvec_dest, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_dest);
    vector_destroy(pvec_result);
}

static void _test_algo_remove_copy_if__cstr(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = strncmp((char*)cpv_input, "Linux", strlen("Linux")) == 0 ? true : false;
}
void test_algo_remove_copy_if__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_dest = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_src[] = {"Linux", "Linux", "AIX", "Windows", "FreeBSD"};
    const char* as_result[] = {"AIX", "Windows", "FreeBSD", "", ""};
    iterator_t it;

    list_init_copy_array(plist_src, as_src, sizeof(as_src)/sizeof(as_src[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    list_init_n(plist_dest, list_size(plist_src));
    it = algo_remove_copy_if(list_begin(plist_src), list_end(plist_src), list_begin(plist_dest), _test_algo_remove_copy_if__cstr);
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist_dest), 3)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

static void _test_algo_remove_copy_if__cstl_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = set_size((set_t*)cpv_input) == 3 ? true : false;
}
void test_algo_remove_copy_if__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_dest = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_src[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}, {3, 4, 5}};
    iterator_t it;
    int i = 0;

    deque_init(pdeq_src);
    deque_init_n(pdeq_dest, 5);
    deque_init_n(pdeq_result, 5);
    set_init(pset);
    for (i = 0; i < sizeof(aan_src)/sizeof(aan_src[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_src[i], sizeof(aan_src[i])/sizeof(aan_src[i][0]));
        deque_push_back(pdeq_src, pset);
    }
    it = algo_remove_copy_if(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest), _test_algo_remove_copy_if__cstl_builtin);
    assert_true(iterator_equal(it, deque_begin(pdeq_dest)));
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test_algo_remove_copy_if__user_define {
    int a;
    int b;
} _test_algo_remove_copy_if__user_define_t;
static void _test_algo_remove_copy_if__user_define(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output =
        ((_test_algo_remove_copy_if__user_define_t*)cpv_input)->a ==
        ((_test_algo_remove_copy_if__user_define_t*)cpv_input)->b ? true : false;
}
void test_algo_remove_copy_if__user_define(void** state)
{
    slist_t* pslist_src = NULL;
    slist_t* pslist_dest = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_remove_copy_if__user_define_t at_src[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_remove_copy_if__user_define_t at_result[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    int i = 0;
    iterator_t it;

    type_register(_test_algo_remove_copy_if__user_define_t, NULL, NULL, NULL, NULL);
    pslist_src = create_slist(_test_algo_remove_copy_if__user_define_t);
    pslist_dest = create_slist(_test_algo_remove_copy_if__user_define_t);
    pslist_result = create_slist(_test_algo_remove_copy_if__user_define_t);
    slist_init(pslist_src);
    slist_init(pslist_result);
    slist_init_n(pslist_dest, 5);
    for (i = 0; i < sizeof(at_src)/sizeof(at_src[0]); ++i) {
        slist_push_front(pslist_src, &at_src[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    it = algo_remove_copy_if(slist_begin(pslist_src), slist_end(pslist_src), slist_begin(pslist_dest), _test_algo_remove_copy_if__user_define);
    assert_true(iterator_equal(it, slist_end(pslist_dest)));
    assert_true(slist_equal(pslist_dest, pslist_result));
    slist_destroy(pslist_src);
    slist_destroy(pslist_dest);
    slist_destroy(pslist_result);
}

/*
 * test algo_unique
 */
UT_CASE_DEFINATION(algo_unique)
void test_algo_unique__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_unique(vector_begin(pvec), list_end(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_unique__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_unique(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_unique__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_unique(it, slist_end(pslist)));
    slist_destroy(pslist);
}

void test_algo_unique__empty(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init(pvec);
    it = algo_unique(vector_begin(pvec), vector_end(pvec));
    assert_true(iterator_equal(it, vector_begin(pvec)));
    assert_true(vector_empty(pvec));
    vector_destroy(pvec);
}

void test_algo_unique__no_duplication(void** state)
{
    list_t* plist_src = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    list_init_copy_array(plist_src, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_unique(list_begin(plist_src), list_end(plist_src));
    assert_true(iterator_equal(it, list_end(plist_src)));
    assert_true(list_equal(plist_src, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_result);
}

void test_algo_unique__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_src[] = {1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_unique(vector_begin(pvec_src), vector_end(pvec_src));
    assert_true(iterator_equal(it, iterator_advance(vector_begin(pvec_src), 10)));
    assert_true(vector_equal(pvec_src, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_result);
}

void test_algo_unique__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_src[] = {"Linux", "Windows", "Windows", "Mac", "FreeBSD", "UNIX"};
    const char* as_result[] = {"Linux", "Windows", "Mac", "FreeBSD", "UNIX", "UNIX"};
    iterator_t it;

    list_init_copy_array(plist_src, as_src, sizeof(as_src)/sizeof(as_src[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    it = algo_unique(list_begin(plist_src), list_end(plist_src));
    assert_true(iterator_equal(it, iterator_prev(list_end(plist_src))));
    assert_true(list_equal(plist_src, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_result);
}

void test_algo_unique__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_src[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}, {1, 2, 3}};
    iterator_t it;
    int i = 0;

    set_init(pset);
    deque_init(pdeq_src);
    for (i = 0; i < sizeof(aan_src)/sizeof(aan_src[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_src[i], sizeof(aan_src[i])/sizeof(aan_src[i][0]));
        deque_push_back(pdeq_src, pset);
    }
    deque_init_copy(pdeq_result, pdeq_src);
    it = algo_unique(deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(iterator_equal(it, iterator_prev(deque_end(pdeq_src))));
    assert_true(deque_equal(pdeq_src, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test_algo_unique__user_define {
    int a;
    int b;
} _test_algo_unique__user_define_t;
static void _test_algo_unique__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_unique__user_define_t)) < 0 ? true : false;
}
void test_algo_unique__user_define(void** state)
{
    deque_t* pdeq_src = NULL;
    deque_t* pdeq_result = NULL;
    _test_algo_unique__user_define_t t_elem = {1, 1};
    iterator_t it;

    type_register(_test_algo_unique__user_define_t, NULL, NULL, _test_algo_unique__user_define, NULL);
    pdeq_src = create_deque(_test_algo_unique__user_define_t);
    pdeq_result = create_deque(_test_algo_unique__user_define_t);
    deque_init_elem(pdeq_src, 10, &t_elem);
    deque_init_copy(pdeq_result, pdeq_src);
    it = algo_unique(deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq_src))));
    assert_true(deque_equal(pdeq_src, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
}

/*
 * test algo_unique_if
 */
UT_CASE_DEFINATION(algo_unique_if)
void test_algo_unique_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_unique_if(vector_begin(pvec), list_end(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_unique_if__invalid_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(algo_unique_if(vector_end(pvec), vector_begin(pvec), NULL));
    vector_destroy(pvec);
}

void test_algo_unique_if__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_unique_if(it, deque_begin(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_unique_if__empty(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it;

    set_init(pset);
    it = algo_unique_if(set_begin(pset), set_end(pset), NULL);
    assert_true(iterator_equal(it, set_begin(pset)));
    assert_true(set_empty(pset));
    set_destroy(pset);
}

void test_algo_unique_if__bfun_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 1, 1, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 4, 5, 6, 7, 8, 9, 0, 9, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_unique_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq), -2)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

static void _test_algo_unique_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first > *(int*)cpv_second ? true : false;
}
void test_algo_unique_if__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_src[] = {4, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {4, 4, 5, 6, 7, 8, 9, 7, 8, 9};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_unique_if(vector_begin(pvec_src), vector_end(pvec_src), _test_algo_unique_if__c_builtin);
    assert_true(iterator_equal(it, iterator_advance(vector_begin(pvec_src), 7)));
    assert_true(vector_equal(pvec_src, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_result);
}

static void _test_algo_unique_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strlen((char*)cpv_first) == strlen((char*)cpv_second) ? true : false;
}
void test_algo_unique_if__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_src[] = {"abc", "xxx", "wwwww", "wwwww", "haha", "haha", "mm"};
    const char* as_result[] = {"abc", "wwwww", "haha", "mm", "haha", "haha", "mm"};
    iterator_t it;

    list_init_copy_array(plist_src, as_src, sizeof(as_src)/sizeof(as_src[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    it = algo_unique_if(list_begin(plist_src), list_end(plist_src), _test_algo_unique_if__cstr);
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist_src), 4)));
    assert_true(list_equal(plist_src, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_result);
}

static void _test_algo_unique_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = set_size((set_t*)cpv_first) == set_size((set_t*)cpv_second) ? true : false;
}
void test_algo_unique_if__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}, {4, 5, 6}};
    iterator_t it;
    int i = 0;

    set_init(pset);
    deque_init(pdeq_src);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq_src, pset);
    }
    deque_init_copy(pdeq_result, pdeq_src);
    it = algo_unique_if(deque_begin(pdeq_src), deque_end(pdeq_src), _test_algo_unique_if__cstl_builtin);
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq_src))));
    assert_true(deque_equal(pdeq_src, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test_algo_unique_if__user_define {
    int a;
    int b;
} _test_algo_unique_if__user_define_t;
static void _test_algo_unique_if__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_unique_if__user_define_t)) == 0 ? true : false;
}
void test_algo_unique_if__user_define(void** state)
{
    slist_t* pslist_src = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_unique_if__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_unique_if__user_define_t, NULL, NULL, NULL, NULL);
    pslist_src = create_slist(_test_algo_unique_if__user_define_t);
    pslist_result = create_slist(_test_algo_unique_if__user_define_t);
    slist_init(pslist_src);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist_src, &at_array[i]);
    }
    slist_init_copy(pslist_result, pslist_src);
    it = algo_unique_if(slist_begin(pslist_src), slist_end(pslist_src), _test_algo_unique_if__user_define);
    assert_true(iterator_equal(it, slist_end(pslist_src)));
    assert_true(slist_equal(pslist_src, pslist_result));
    slist_destroy(pslist_src);
    slist_destroy(pslist_result);
}

/*
 * test algo_unique_copy
 */
UT_CASE_DEFINATION(algo_unique_copy)
void test_algo_unique_copy__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_unique_copy(vector_begin(pvec), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_unique_copy__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_unique_copy(deque_end(pdeq), deque_begin(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_unique_copy__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    deque_init_n(pdeq, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_unique_copy(it, slist_end(pslist), deque_begin(pdeq)));
    slist_destroy(pslist);
    deque_destroy(pdeq);
}

void test_algo_unique_copy__invalid_dest_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_unique_copy(vector_begin(pvec), vector_end(pvec), it));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_unique_copy__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_unique_copy(deque_begin(pdeq), deque_end(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_unique_copy__empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_dest = create_vector(int);
    iterator_t it;

    vector_init(pvec);
    vector_init(pvec_dest);
    it = algo_unique_copy(vector_begin(pvec), vector_end(pvec), vector_end(pvec_dest));
    assert_true(iterator_equal(it, vector_begin(pvec_dest)));
    assert_true(vector_empty(pvec_dest));
    vector_destroy(pvec);
    vector_destroy(pvec_dest);
}

void test_algo_unique_copy__no_duplication(void** state)
{
    list_t* plist_src = create_list(int);
    list_t* plist_dest = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    list_init_copy_array(plist_src, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_n(plist_dest, list_size(plist_src));
    it = algo_unique_copy(list_begin(plist_src), list_end(plist_src), list_begin(plist_dest));
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_result);
    list_destroy(plist_dest);
}

void test_algo_unique_copy__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_src[] = {1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    vector_init_n(pvec_dest, vector_size(pvec_src));
    it = algo_unique_copy(vector_begin(pvec_src), vector_end(pvec_src), vector_begin(pvec_dest));
    assert_true(iterator_equal(it, iterator_advance(vector_begin(pvec_dest), 10)));
    assert_true(vector_equal(pvec_dest, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_result);
    vector_destroy(pvec_dest);
}

void test_algo_unique_copy__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_dest = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_src[] = {"Linux", "Windows", "Windows", "Mac", "FreeBSD", "UNIX"};
    const char* as_result[] = {"Linux", "Windows", "Mac", "FreeBSD", "UNIX", ""};
    iterator_t it;

    list_init_copy_array(plist_src, as_src, sizeof(as_src)/sizeof(as_src[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    list_init_n(plist_dest, list_size(plist_src));
    it = algo_unique_copy(list_begin(plist_src), list_end(plist_src), list_begin(plist_dest));
    assert_true(iterator_equal(it, iterator_prev(list_end(plist_dest))));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_result);
    list_destroy(plist_dest);
}

void test_algo_unique_copy__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_dest = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_src[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}, {1, 2, 3}};
    iterator_t it;
    int i = 0;

    set_init(pset);
    deque_init(pdeq_src);
    for (i = 0; i < sizeof(aan_src)/sizeof(aan_src[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_src[i], sizeof(aan_src[i])/sizeof(aan_src[i][0]));
        deque_push_back(pdeq_src, pset);
    }
    deque_init_copy(pdeq_result, pdeq_src);
    set_clear((set_t*)deque_back(pdeq_result));
    deque_init_n(pdeq_dest, deque_size(pdeq_src));
    it = algo_unique_copy(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest));
    assert_true(iterator_equal(it, iterator_prev(deque_end(pdeq_dest))));
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
    deque_destroy(pdeq_dest);
    set_destroy(pset);
}

typedef struct _tag_test_algo_unique_copy__user_define {
    int a;
    int b;
} _test_algo_unique_copy__user_define_t;
static void _test_algo_unique_copy__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_unique_copy__user_define_t)) < 0 ? true : false;
}
void test_algo_unique_copy__user_define(void** state)
{
    deque_t* pdeq_src = NULL;
    deque_t* pdeq_dest = NULL;
    deque_t* pdeq_result = NULL;
    _test_algo_unique_copy__user_define_t t_elem = {1, 1};
    iterator_t it;

    type_register(_test_algo_unique_copy__user_define_t, NULL, NULL, _test_algo_unique_copy__user_define, NULL);
    pdeq_src = create_deque(_test_algo_unique_copy__user_define_t);
    pdeq_result = create_deque(_test_algo_unique_copy__user_define_t);
    pdeq_dest = create_deque(_test_algo_unique_copy__user_define_t);
    deque_init_elem(pdeq_src, 10, &t_elem);
    deque_init_n(pdeq_result, 9);
    deque_push_front(pdeq_result, &t_elem);
    deque_init_n(pdeq_dest, 10);
    it = algo_unique_copy(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest));
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq_dest))));
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
    deque_destroy(pdeq_dest);
}

/*
 * test algo_unique_copy_if
 */
UT_CASE_DEFINATION(algo_unique_copy_if)
void test_algo_unique_copy_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_unique_copy_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_unique_copy_if__invalid_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_unique_copy_if(vector_end(pvec), vector_begin(pvec), list_begin(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_unique_copy_if__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_unique_copy_if(it, deque_begin(pdeq), vector_begin(pvec), NULL));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_unique_copy_if__invalid_dest_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_unique_copy_if(deque_begin(pdeq), deque_end(pdeq), it, NULL));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_unique_copy_if__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(char*);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_unique_copy_if(list_begin(plist), list_end(plist), deque_begin(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_unique_copy_if__empty(void** state)
{
    set_t* pset = create_set(int);
    set_t* pset_dest = create_set(int);
    iterator_t it;

    set_init(pset);
    set_init(pset_dest);
    it = algo_unique_copy_if(set_begin(pset), set_end(pset), set_begin(pset_dest), NULL);
    assert_true(iterator_equal(it, set_begin(pset_dest)));
    assert_true(set_empty(pset_dest));
    set_destroy(pset);
    set_destroy(pset_dest);
}

void test_algo_unique_copy_if__bfun_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 1, 1, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 4, 5, 6, 7, 8, 9, 0, 0, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_n(pdeq_dest, deque_size(pdeq));
    it = algo_unique_copy_if(deque_begin(pdeq), deque_end(pdeq), deque_begin(pdeq_dest), NULL);
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq_dest), -2)));
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    deque_destroy(pdeq_dest);
}

static void _test_algo_unique_copy_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first > *(int*)cpv_second ? true : false;
}
void test_algo_unique_copy_if__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_src[] = {4, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_result[] = {4, 4, 5, 6, 7, 8, 9, 0, 0, 0};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    vector_init_n(pvec_dest, vector_size(pvec_src));
    it = algo_unique_copy_if(vector_begin(pvec_src), vector_end(pvec_src), vector_begin(pvec_dest), _test_algo_unique_copy_if__c_builtin);
    assert_true(iterator_equal(it, iterator_advance(vector_begin(pvec_dest), 7)));
    assert_true(vector_equal(pvec_dest, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_result);
    vector_destroy(pvec_dest);
}

static void _test_algo_unique_copy_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strlen((char*)cpv_first) == strlen((char*)cpv_second) ? true : false;
}
void test_algo_unique_copy_if__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_dest = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_src[] = {"abc", "xxx", "wwwww", "wwwww", "haha", "haha", "mm"};
    const char* as_result[] = {"abc", "wwwww", "haha", "mm", "", "", ""};
    iterator_t it;

    list_init_copy_array(plist_src, as_src, sizeof(as_src)/sizeof(as_src[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    list_init_n(plist_dest, list_size(plist_src));
    it = algo_unique_copy_if(list_begin(plist_src), list_end(plist_src), list_begin(plist_dest), _test_algo_unique_copy_if__cstr);
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist_dest), 4)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_result);
    list_destroy(plist_dest);
}

static void _test_algo_unique_copy_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = set_size((set_t*)cpv_first) == set_size((set_t*)cpv_second) ? true : false;
}
void test_algo_unique_copy_if__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_dest = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}, {4, 5, 6}};
    iterator_t it;
    int i = 0;

    set_init(pset);
    deque_init(pdeq_src);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq_src, pset);
    }
    deque_init_n(pdeq_result, deque_size(pdeq_src) - 1);
    deque_push_front(pdeq_result, deque_front(pdeq_src));
    deque_init_n(pdeq_dest, deque_size(pdeq_src));
    it = algo_unique_copy_if(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest), _test_algo_unique_copy_if__cstl_builtin);
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq_dest))));
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
    deque_destroy(pdeq_dest);
    set_destroy(pset);
}

typedef struct _tag_test_algo_unique_copy_if__user_define {
    int a;
    int b;
} _test_algo_unique_copy_if__user_define_t;
static void _test_algo_unique_copy_if__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_unique_copy_if__user_define_t)) == 0 ? true : false;
}
void test_algo_unique_copy_if__user_define(void** state)
{
    slist_t* pslist_src = NULL;
    slist_t* pslist_dest = NULL;
    slist_t* pslist_result = NULL;
    _test_algo_unique_copy_if__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_unique_copy_if__user_define_t, NULL, NULL, NULL, NULL);
    pslist_src = create_slist(_test_algo_unique_copy_if__user_define_t);
    pslist_dest = create_slist(_test_algo_unique_copy_if__user_define_t);
    pslist_result = create_slist(_test_algo_unique_copy_if__user_define_t);
    slist_init(pslist_src);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist_src, &at_array[i]);
    }
    slist_init_copy(pslist_result, pslist_src);
    slist_init_n(pslist_dest, slist_size(pslist_src));
    it = algo_unique_copy_if(slist_begin(pslist_src), slist_end(pslist_src), slist_begin(pslist_dest), _test_algo_unique_copy_if__user_define);
    assert_true(iterator_equal(it, slist_end(pslist_dest)));
    assert_true(slist_equal(pslist_dest, pslist_result));
    slist_destroy(pslist_src);
    slist_destroy(pslist_result);
    slist_destroy(pslist_dest);
}

/*
 * test algo_reverse
 */
UT_CASE_DEFINATION(algo_reverse)
void test_algo_reverse__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_reverse(vector_begin(pvec), deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_reverse__invalid_range2(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_reverse(list_end(plist), list_begin(plist)));
    list_destroy(plist);
}

void test_algo_reverse__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_reverse(slist_begin(pslist), slist_end(pslist)));
    slist_destroy(pslist);
}

void test_algo_reverse__empty(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    algo_reverse(vector_begin(pvec), vector_end(pvec));
    assert_true(vector_empty(pvec));
    vector_destroy(pvec);
}

void test_algo_reverse__one(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 1);
    algo_reverse(list_begin(plist), list_end(plist));
    assert_true(list_size(plist) == 1);
    list_destroy(plist);
}

void test_algo_reverse__reverse(void** state)
{
    deque_t* pdeq_src = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    deque_init_copy_array(pdeq_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    algo_reverse(deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_equal(pdeq_src, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
}

/*
 * test algo_reverse_copy
 */
UT_CASE_DEFINATION(algo_reverse_copy)
void test_algo_reverse_copy__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_reverse_copy(vector_begin(pvec), deque_end(pdeq), list_begin(plist)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_reverse_copy__invalid_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_reverse_copy(list_end(plist), list_begin(plist), deque_begin(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_reverse_copy__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(int);

    slist_init_n(pslist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_reverse_copy(slist_begin(pslist), slist_end(pslist), vector_begin(pvec)));
    slist_destroy(pslist);
    vector_destroy(pvec);
}

void test_algo_reverse_copy__invalid_dest_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_reverse_copy(deque_begin(pdeq), deque_end(pdeq), it));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_reverse_copy__not_same_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(double);

    deque_init_n(pdeq, 1);
    list_init_n(plist, 1);
    expect_assert_failure(algo_reverse_copy(deque_begin(pdeq), deque_end(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_reverse_copy__empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it;

    vector_init(pvec);
    list_init(plist);
    it = algo_reverse_copy(vector_begin(pvec), vector_end(pvec), list_begin(plist));
    assert_true(iterator_equal(it, list_begin(plist)));
    assert_true(vector_empty(pvec));
    assert_true(list_empty(plist));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_reverse_copy__one(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    list_init_elem(plist, 1, 100);
    deque_init_n(pdeq, 1);
    it = algo_reverse_copy(list_begin(plist), list_end(plist), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(list_size(plist) == 1);
    assert_true(deque_size(pdeq) == 1);
    assert_true(*(int*)deque_front(pdeq) == 100);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_reverse_copy__reverse_copy(void** state)
{
    deque_t* pdeq_src = create_deque(int);
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    iterator_t it;

    deque_init_copy_array(pdeq_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    deque_init_n(pdeq_dest, deque_size(pdeq_src));
    it = algo_reverse_copy(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest));
    assert_true(iterator_equal(it, deque_end(pdeq_dest)));
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_result);
    deque_destroy(pdeq_dest);
}

/*
 * test algo_rotate
 */
UT_CASE_DEFINATION(algo_rotate)
void test_algo_rotate__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_rotate(vector_begin(pvec), list_begin(plist), list_end(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_rotate__invalid_first_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(algo_rotate(iterator_next_n(vector_begin(pvec), 3), vector_begin(pvec), vector_end(pvec)));
    vector_destroy(pvec);
}

void test_algo_rotate__invalid_first_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_rotate(it, deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_rotate__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_rotate(vector_begin(pvec), vector_end(pvec), list_end(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_rotate__invalid_second_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(algo_rotate(vector_begin(pvec), vector_end(pvec), iterator_next(vector_begin(pvec))));
    vector_destroy(pvec);
}

void test_algo_rotate__invalid_second_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_rotate(deque_begin(pdeq), deque_begin(pdeq), it));
    deque_destroy(pdeq);
}

void test_algo_rotate__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init(pslist);
    it = algo_rotate(slist_begin(pslist), slist_begin(pslist), slist_end(pslist));
    assert_true(iterator_equal(it, slist_begin(pslist)));
    assert_true(slist_empty(pslist));
    slist_destroy(pslist);
}

void test_algo_rotate__first_range_empty(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = algo_rotate(slist_begin(pslist), slist_begin(pslist), slist_end(pslist));
    assert_true(iterator_equal(it, slist_begin(pslist)));
    slist_destroy(pslist);
}

void test_algo_rotate__second_range_empty(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = algo_rotate(slist_begin(pslist), slist_end(pslist), slist_end(pslist));
    assert_true(iterator_equal(it, slist_end(pslist)));
    slist_destroy(pslist);
}

void test_algo_rotate__first_less_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {2, 3, 4, 5, 6, 7, 8, 9, 0, 1};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_rotate(vector_begin(pvec), iterator_next(vector_begin(pvec)), vector_end(pvec));
    assert_true(iterator_equal(it, iterator_advance(vector_end(pvec), -1)));
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

void test_algo_rotate__first_greater_than_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_rotate(list_begin(plist), iterator_advance(list_end(plist), -1), list_end(plist));
    assert_true(iterator_equal(it, iterator_next(list_begin(plist))));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test_algo_rotate__first_equal_to_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {6, 7, 8, 9, 0, 1, 2, 3, 4, 5};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_rotate(deque_begin(pdeq), iterator_advance(deque_begin(pdeq), 5), deque_end(pdeq));
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_rotate_copy
 */
UT_CASE_DEFINATION(algo_rotate_copy)
void test_algo_rotate_copy__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_rotate_copy(vector_begin(pvec), list_begin(plist), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_rotate_copy__invalid_first_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_rotate_copy(iterator_advance(vector_begin(pvec), 3), vector_begin(pvec), vector_end(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_rotate_copy__invalid_first_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_rotate_copy(it, iterator_advance(vector_begin(pvec), 3), vector_end(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_rotate_copy__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_rotate_copy(vector_begin(pvec), vector_end(pvec), list_end(plist), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_rotate_copy__invalid_second_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_rotate_copy(vector_begin(pvec), vector_end(pvec), iterator_advance(vector_begin(pvec), 3), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_rotate_copy__invalid_second_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = vector_end(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_rotate_copy(vector_begin(pvec), iterator_advance(vector_begin(pvec), 3), it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_rotate_copy__invalid_dest_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_rotate_copy(vector_begin(pvec), iterator_advance(vector_begin(pvec), 3), vector_end(pvec), it));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_rotate_copy__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(double);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_rotate_copy(list_begin(plist), iterator_next(list_begin(plist)), list_end(plist), slist_begin(pslist)));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_rotate_copy__empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init(pdeq);
    it = algo_rotate_copy(vector_begin(pvec), vector_end(pvec), vector_end(pvec), deque_begin(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    assert_true(deque_empty(pdeq));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_rotate_copy__first_range_empty(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_dest = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    list_init_n(plist_dest, list_size(plist));
    it = algo_rotate_copy(list_begin(plist), list_begin(plist), list_end(plist), list_begin(plist_dest));
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

void test_algo_rotate_copy__second_range_empty(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_dest = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy(plist_result, plist);
    list_init_n(plist_dest, list_size(plist));
    it = algo_rotate_copy(list_begin(plist), list_end(plist), list_end(plist), list_begin(plist_dest));
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

void test_algo_rotate_copy__first_less_than_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_dest = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {3, 4, 5, 6, 7, 8, 9, 0, 1, 2};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    list_init_n(plist_dest, list_size(plist));
    it = algo_rotate_copy(list_begin(plist), iterator_advance(list_begin(plist), 2), list_end(plist), list_begin(plist_dest));
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

void test_algo_rotate_copy__first_equal_to_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_dest = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {6, 7, 8, 9, 0, 1, 2, 3, 4, 5};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    list_init_n(plist_dest, list_size(plist));
    it = algo_rotate_copy(list_begin(plist), iterator_advance(list_begin(plist), 5), list_end(plist), list_begin(plist_dest));
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

void test_algo_rotate_copy__first_greater_than_second(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_dest = create_list(int);
    list_t* plist_result = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {8, 9, 0, 1, 2, 3, 4, 5, 6, 7};
    iterator_t it;

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init_copy_array(plist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    list_init_n(plist_dest, list_size(plist));
    it = algo_rotate_copy(list_begin(plist), iterator_advance(list_end(plist), -3), list_end(plist), list_begin(plist_dest));
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

/*
 * test algo_random_shuffle
 */
UT_CASE_DEFINATION(algo_random_shuffle)
void test_algo_random_shuffle__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_shuffle(vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_shuffle__invalid_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_shuffle(vector_end(pvec), vector_begin(pvec)));
    vector_destroy(pvec);
}

void test_algo_random_shuffle__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_random_shuffle(list_begin(plist), list_end(plist)));
    list_destroy(plist);
}

void test_algo_random_shuffle__random(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_random_shuffle(deque_begin(pdeq), deque_end(pdeq));
    deque_destroy(pdeq);
}

/*
 * test algo_random_shuffle_if
 */
UT_CASE_DEFINATION(algo_random_shuffle_if)
void test_algo_random_shuffle_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_shuffle_if(vector_begin(pvec), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_shuffle_if__invalid_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_shuffle_if(vector_end(pvec), vector_begin(pvec), NULL));
    vector_destroy(pvec);
}

void test_algo_random_shuffle_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(algo_random_shuffle_if(list_begin(plist), list_end(plist), NULL));
    list_destroy(plist);
}

void test_algo_random_shuffle_if__ufun_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    algo_random_shuffle_if(deque_begin(pdeq), deque_end(pdeq), NULL);
    deque_destroy(pdeq);
}

static void _test_algo_random_shuffle_if__random(const void* cpv_input, void* pv_output)
{
    static size_t t_result = 1;
    *(size_t*)pv_output = t_result++;
}
void test_algo_random_shuffle_if__random(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy(pvec_result, pvec);
    algo_random_shuffle_if(vector_begin(pvec), vector_end(pvec), _test_algo_random_shuffle_if__random);
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

/*
 * test algo_random_sample
 */
UT_CASE_DEFINATION(algo_random_sample)
void test_algo_random_sample__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_sample(deque_begin(pdeq), list_begin(plist), vector_begin(pvec), vector_end(pvec)));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample(list_end(plist), list_begin(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample__invalid_first_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_random_sample(it, vector_end(pvec), deque_begin(pdeq), deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_sample(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), vector_end(pvec)));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample__invalid_second_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample(list_begin(plist), list_end(plist), deque_end(pdeq), deque_begin(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample__invalid_second_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_random_sample(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_random_sample__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample__all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init(pdeq);
    it = algo_random_sample(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample__first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init_n(pdeq, 10);
    it = algo_random_sample(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample__second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init(pdeq);
    it = algo_random_sample(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample__first_less_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 15);
    it = algo_random_sample(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 10)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample__first_equal_to_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 10);
    it = algo_random_sample(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample__first_greater_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 5);
    it = algo_random_sample(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

/*
 * test algo_random_sample_if
 */
UT_CASE_DEFINATION(algo_random_sample_if)
void test_algo_random_sample_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_sample_if(deque_begin(pdeq), list_begin(plist), vector_begin(pvec), vector_end(pvec), NULL));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample_if__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample_if(list_end(plist), list_begin(plist), deque_begin(pdeq), deque_end(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__invalid_first_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_random_sample_if(it, vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), NULL));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_sample_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), vector_end(pvec), NULL));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample_if__invalid_second_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample_if(list_begin(plist), list_end(plist), deque_end(pdeq), deque_begin(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__invalid_second_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_random_sample_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_random_sample_if__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init(pdeq);
    it = algo_random_sample_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init_n(pdeq, 10);
    it = algo_random_sample_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init(pdeq);
    it = algo_random_sample_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__first_less_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 15);
    it = algo_random_sample_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 10)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__first_equal_to_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 10);
    it = algo_random_sample_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_if__first_greater_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 5);
    it = algo_random_sample_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

static void _test_algo_random_sample_if__ufun_non_NULL(const void* cpv_input, void* pv_output)
{
    static size_t t_result = 0;
    *(size_t*)pv_output = t_result++;
}
void test_algo_random_sample_if__ufun_not_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_random_sample_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq), _test_algo_random_sample_if__ufun_non_NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    vector_destroy(pvec);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_random_sample_n
 */
UT_CASE_DEFINATION(algo_random_sample_n)
void test_algo_random_sample_n__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_sample_n(deque_begin(pdeq), list_begin(plist), vector_begin(pvec), 10));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample_n__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample_n(list_end(plist), list_begin(plist), deque_begin(pdeq), 10));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__invalid_first_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_random_sample_n(it, vector_end(pvec), deque_begin(pdeq), 10));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_random_sample_n(deque_begin(pdeq), deque_end(pdeq), it, 10));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample_n__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample_n(list_begin(plist), list_end(plist), deque_begin(pdeq), 10));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init(pdeq);
    it = algo_random_sample_n(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 0);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init_n(pdeq, 10);
    it = algo_random_sample_n(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 10);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init(pdeq);
    it = algo_random_sample_n(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 0);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__first_less_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 15);
    it = algo_random_sample_n(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 15);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 10)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__first_equal_to_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 10);
    it = algo_random_sample_n(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 10);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n__first_greater_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 5);
    it = algo_random_sample_n(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 5);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

/*
 * test algo_random_sample_n_if
 */
UT_CASE_DEFINATION(algo_random_sample_n_if)
void test_algo_random_sample_n_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_random_sample_n_if(deque_begin(pdeq), list_begin(plist), vector_begin(pvec), 10, NULL));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample_n_if__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample_n_if(list_end(plist), list_begin(plist), deque_begin(pdeq), 10, NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__invalid_first_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_random_sample_n_if(it, vector_end(pvec), deque_begin(pdeq), 10, NULL));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__invalid_second_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    it = list_begin(plist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_random_sample_n_if(deque_begin(pdeq), deque_end(pdeq), it, 10, NULL));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_random_sample_n_if__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(double);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_random_sample_n_if(list_begin(plist), list_end(plist), deque_begin(pdeq), 10, NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__all_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init(pdeq);
    it = algo_random_sample_n_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 0, NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__first_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init(pvec);
    deque_init_n(pdeq, 10);
    it = algo_random_sample_n_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 10, NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__second_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init(pdeq);
    it = algo_random_sample_n_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 0, NULL);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__first_less_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 15);
    it = algo_random_sample_n_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 15, NULL);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 10)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__first_equal_to_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 10);
    it = algo_random_sample_n_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 10, NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_random_sample_n_if__first_greater_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 5);
    it = algo_random_sample_n_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 5, NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

static void _test_algo_random_sample_n_if__ufun_non_NULL(const void* cpv_input, void* pv_output)
{
    static size_t t_result = 0;
    *(size_t*)pv_output = t_result++;
}
void test_algo_random_sample_n_if__ufun_not_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_result = create_deque(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 2, 3, 4, 5};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    deque_init_n(pdeq, 5);
    deque_init_copy_array(pdeq_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_random_sample_n_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), 5, _test_algo_random_sample_n_if__ufun_non_NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test algo_partition
 */
UT_CASE_DEFINATION(algo_partition)
void test_algo_partition__invalid_range(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_1 = create_slist(int);

    slist_init_n(pslist, 10);
    slist_init_n(pslist_1, 10);
    expect_assert_failure(algo_partition(slist_begin(pslist), slist_end(pslist_1), NULL));
    slist_destroy(pslist);
    slist_destroy(pslist_1);
}

void test_algo_partition__invalid_range2(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_partition(slist_end(pslist), slist_begin(pslist), NULL));
    slist_destroy(pslist);
}

void test_algo_partition__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_partition(slist_begin(pslist), it, NULL));
    slist_destroy(pslist);
}

void test_algo_partition__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init(pslist);
    it = algo_partition(slist_begin(pslist), slist_end(pslist), NULL);
    assert_true(iterator_equal(it, slist_begin(pslist)));
    slist_destroy(pslist);
}

void test_algo_partition__ufun_NULL(void** state)
{
    slist_t* pslist = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_partition(slist_begin(pslist), slist_end(pslist), NULL);
    assert_true(iterator_equal(it, slist_begin(pslist)));
    slist_destroy(pslist);
}

static void _test_algo_partition__all_satify(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input < 10 ? true : false;
}
void test_algo_partition__all_satify(void** state)
{
    slist_t* pslist = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_partition(slist_begin(pslist), slist_end(pslist), _test_algo_partition__all_satify);
    assert_true(iterator_equal(it, slist_end(pslist)));
    slist_destroy(pslist);
}

static void _test_algo_partition__all_not_satify(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 10 ? true : false;
}
void test_algo_partition__all_not_satify(void** state)
{
    slist_t* pslist = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_partition(slist_begin(pslist), slist_end(pslist), _test_algo_partition__all_not_satify);
    assert_true(iterator_equal(it, slist_begin(pslist)));
    slist_destroy(pslist);
}

static void _test_algo_partition__normal(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}
void test_algo_partition__normal(void** state)
{
    slist_t* pslist = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_partition(slist_begin(pslist), slist_end(pslist), _test_algo_partition__normal);
    assert_true(iterator_equal(it, iterator_advance(slist_begin(pslist), 5)));
    slist_destroy(pslist);
}

/*
 * test algo_stable_partition
 */
UT_CASE_DEFINATION(algo_stable_partition)
void test_algo_stable_partition__invalid_range(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_1 = create_slist(int);

    slist_init_n(pslist, 10);
    slist_init_n(pslist_1, 10);
    expect_assert_failure(algo_stable_partition(slist_begin(pslist), slist_end(pslist_1), NULL));
    slist_destroy(pslist);
    slist_destroy(pslist_1);
}

void test_algo_stable_partition__invalid_range2(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_stable_partition(slist_end(pslist), slist_begin(pslist), NULL));
    slist_destroy(pslist);
}

void test_algo_stable_partition__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = 100;
    expect_assert_failure(algo_stable_partition(slist_begin(pslist), it, NULL));
    slist_destroy(pslist);
}

void test_algo_stable_partition__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init(pslist);
    it = algo_stable_partition(slist_begin(pslist), slist_end(pslist), NULL);
    assert_true(iterator_equal(it, slist_begin(pslist)));
    slist_destroy(pslist);
}

void test_algo_stable_partition__ufun_NULL(void** state)
{
    slist_t* pslist = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = algo_stable_partition(slist_begin(pslist), slist_end(pslist), NULL);
    assert_true(iterator_equal(it, slist_begin(pslist)));
    slist_destroy(pslist);
}

static void _test_algo_stable_partition__all_satify(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input < 10 ? true : false;
}
void test_algo_stable_partition__all_satify(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_result = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    slist_init_copy(pslist_result, pslist);
    it = algo_stable_partition(slist_begin(pslist), slist_end(pslist), _test_algo_stable_partition__all_satify);
    assert_true(iterator_equal(it, slist_end(pslist)));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

static void _test_algo_stable_partition__all_not_satify(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 10 ? true : false;
}
void test_algo_stable_partition__all_not_satify(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_result = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    slist_init_copy(pslist_result, pslist);
    it = algo_stable_partition(slist_begin(pslist), slist_end(pslist), _test_algo_stable_partition__all_not_satify);
    assert_true(iterator_equal(it, slist_begin(pslist)));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

static void _test_algo_stable_partition__normal(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}
void test_algo_stable_partition__normal(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_result = create_slist(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {2, 4, 6, 8, 0, 1, 3, 5, 7, 9};
    iterator_t it;

    slist_init_copy_array(pslist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    slist_init_copy_array(pslist_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = algo_stable_partition(slist_begin(pslist), slist_end(pslist), _test_algo_stable_partition__normal);
    assert_true(iterator_equal(it, iterator_advance(slist_begin(pslist), 5)));
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

