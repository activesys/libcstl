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

