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
#include "ut_cstl_algo_nonmutating_private.h"

UT_SUIT_DEFINATION(cstl_algo_nonmutating_private, _algo_find__algo_find_varg)

/*
 * test _algo_find and _algo_find_varg
 */
UT_CASE_DEFINATION(_algo_find__algo_find_varg)
void test__algo_find__algo_find_varg__invalid_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);

    expect_assert_failure(_algo_find(list_begin(plist), deque_end(pdeq), 100));

    list_destroy(plist);
    deque_destroy(pdeq);
}

void test__algo_find__algo_find_varg__invalid_range_2(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    expect_assert_failure(_algo_find(vector_end(pvec), vector_begin(pvec), 100));

    vector_destroy(pvec);
}

void test__algo_find__algo_find_varg__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;
    slist_init(pslist);

    it = _algo_find(slist_begin(pslist), slist_end(pslist), 0);
    assert_true(iterator_equal(it, slist_end(pslist)));

    slist_destroy(pslist);
}

void test__algo_find__algo_find_varg__c_builtin_not_found(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_elem(plist, 10, 100);
    it = _algo_find(list_begin(plist), list_end(plist), 0);
    assert_true(iterator_equal(it, list_end(plist)));
    list_destroy(plist);
}

void test__algo_find__algo_find_varg__c_builtin_found(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;
    int i = 0;

    deque_init(pdeq);
    for (i = 0; i < 10; ++i) {
        deque_push_back(pdeq, i);
    }
    it = _algo_find(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_find__algo_find_varg__cstr_not_found(void** state)
{
    deque_t* pdeq = create_deque(char*);
    iterator_t it;
    const char* array[5] = {"Fedora", "Ubuntu", "CentOS", "AIX", "libcstl"};

    deque_init_copy_array(pdeq, array, 5);
    it = _algo_find(deque_begin(pdeq), deque_end(pdeq), "Windows");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_find__algo_find_varg__cstr_found(void** state)
{
    list_t* plist = create_list(char*);
    iterator_t it;
    const char* array[5] = {"Fedora", "Ubuntu", "CentOS", "AIX", "libcstl"};

    list_init_copy_array(plist, array, 5);
    it = _algo_find(list_begin(plist), list_end(plist), "Ubuntu");
    assert_true(iterator_equal(it, iterator_next(list_begin(plist))));
    list_destroy(plist);
}

void test__algo_find__algo_find_varg__cstl_builtin_not_found(void** state)
{
    list_t* plist = create_list(map_t<int, int>);
    iterator_t it;
    map_t* pmap = create_map(int, int);
    int i = 0;

    list_init(plist);
    map_init(pmap);

    for (i = 0; i < 10; ++i) {
        map_clear(pmap);
        *(int*)map_at(pmap, i) = i;
        list_push_back(plist, pmap);
    }

    map_clear(pmap);
    it = _algo_find(list_begin(plist), list_end(plist), pmap);
    assert_true(iterator_equal(it, list_end(plist)));

    map_destroy(pmap);
    list_destroy(plist);
}

void test__algo_find__algo_find_varg__cstl_builtin_found(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    list_t* plist = create_list(int);
    iterator_t it;
    int i = 0;

    vector_init(pvec);
    list_init(plist);

    for (i = 0; i < 10; ++i) {
        list_clear(plist);
        list_assign_elem(plist, i, i);
        vector_push_back(pvec, plist);
    }

    list_clear(plist);
    list_assign_elem(plist, 5, 5);
    it = _algo_find(vector_begin(pvec), vector_end(pvec), plist);
    assert_true(iterator_equal(it, iterator_next_n(vector_begin(pvec), 5)));

    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag__test__algo_find__algo_find_varg {
    int a;
    int b;
}_test__algo_find__algo_find_varg_t;

void _test__algo_find__algo_find_varg_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test__algo_find__algo_find_varg_t)) < 0 ? true : false;
}
void test__algo_find__algo_find_varg__user_define_not_found(void** state)
{
    list_t* plist = NULL;
    _test__algo_find__algo_find_varg_t t_elem;
    iterator_t it;
    int i = 0;

    type_register(_test__algo_find__algo_find_varg_t, NULL, NULL, _test__algo_find__algo_find_varg_less, NULL);
    plist = create_list(_test__algo_find__algo_find_varg_t);
    list_init(plist);

    for (i = 0; i < 10; ++i) {
        t_elem.a = t_elem.b = i;
        list_push_back(plist, &t_elem);
    }

    t_elem.a = t_elem.b = 100;
    it = _algo_find(list_begin(plist), list_end(plist), &t_elem);
    assert_true(iterator_equal(it, list_end(plist)));

    list_destroy(plist);
}

void test__algo_find__algo_find_varg__user_define_found(void** state)
{
    deque_t* pdeq = create_deque(_test__algo_find__algo_find_varg_t);
    _test__algo_find__algo_find_varg_t t_elem;
    iterator_t it;
    int i = 0;

    deque_init(pdeq);

    for (i = 0; i < 10; ++i) {
        t_elem.a = t_elem.b = i;
        deque_push_back(pdeq, &t_elem);
    }

    t_elem.a = t_elem.b = 3;
    it = _algo_find(deque_begin(pdeq), deque_end(pdeq), &t_elem);
    assert_true(iterator_equal(it, iterator_next_n(deque_begin(pdeq), 3)));

    deque_destroy(pdeq);
}

/*
 * test _algo_count and _algo_count_varg
 */
UT_CASE_DEFINATION(_algo_count__algo_count_varg)
void test__algo_count__algo_count_varg__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_count(vector_begin(pvec), list_end(plist), 100));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_count__algo_count_varg__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 10, 100);
    expect_assert_failure(_algo_count(deque_end(pdeq), deque_begin(pdeq), 100));
    deque_destroy(pdeq);
}

void test__algo_count__algo_count_varg__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(_algo_count(slist_begin(pslist), slist_end(pslist), 0) == 0);
    slist_destroy(pslist);
}

void test__algo_count__algo_count_varg__c_builtin_0(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 100);
    assert_true(_algo_count(vector_begin(pvec), vector_end(pvec), 88) == 0);
    vector_destroy(pvec);
}

void test__algo_count__algo_count_varg__c_builtin_1(void** state)
{
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    for (i = 0; i < 10; ++i) {
        list_push_back(plist, i);
    }
    assert_true(_algo_count(list_begin(plist), list_end(plist), 4) == 1);
    list_destroy(plist);
}

void test__algo_count__algo_count_varg__c_builtin_n(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 10, 100);
    assert_true(_algo_count(deque_begin(pdeq), deque_end(pdeq), 100) == 10);
    deque_destroy(pdeq);
}

void test__algo_count__algo_count_varg__cstr_0(void** state)
{
    slist_t* pslist = create_slist(char*);
    const char* as_array[] = {"Windows", "Linux", "Mac OS X", "FreeBSD", "AIX"};

    slist_init_copy_array(pslist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(_algo_count(slist_begin(pslist), slist_end(pslist), "QNX") == 0);
    slist_destroy(pslist);
}

void test__algo_count__algo_count_varg__cstr_1(void** state)
{
    set_t* pset = create_set(char*);
    const char* as_array[] = {"Windows", "Linux", "Mac OS X", "FreeBSD", "AIX"};

    set_init_copy_array(pset, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(_algo_count(set_begin(pset), set_end(pset), "Linux"));
    set_destroy(pset);
}

void test__algo_count__algo_count_varg__cstr_n(void** state)
{
    multiset_t* pmset = create_multiset(char*);
    const char* as_array[] = {"Windows", "Linux", "Mac OS X", "FreeBSD", "AIX", "Linux", "Linux"};

    multiset_init_copy_array(pmset, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(_algo_count(multiset_begin(pmset), multiset_end(pmset), "Linux") == 3);
    multiset_destroy(pmset);
}

void test__algo_count__algo_count_varg__cstl_builtin_0(void** state)
{
    hash_set_t* phset = create_hash_set(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_set_init(phset);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
        hash_set_insert(phset, pvec);
    }
    vector_resize_elem(pvec, 33, 33);
    assert_true(_algo_count(hash_set_begin(phset), hash_set_end(phset), pvec) == 0);
    hash_set_destroy(phset);
    vector_destroy(pvec);
}

void test__algo_count__algo_count_varg__cstl_builtin_1(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(list_t<int>);
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init(phmset);
    list_init(plist);
    for (i = 0; i < 10; ++i) {
        list_push_back(plist, i);
        hash_multiset_insert(phmset, plist);
    }
    list_pop_back(plist);
    list_pop_back(plist);
    list_pop_back(plist);
    assert_true(_algo_count(hash_multiset_begin(phmset), hash_multiset_end(phmset), plist) == 1);
    list_destroy(plist);
    hash_multiset_destroy(phmset);
}

void test__algo_count__algo_count_varg__cstl_builtin_n(void** state)
{
    vector_t* pvec = create_vector(deque_t<int>);
    deque_t* pdeq = create_deque(int);
    int i = 0;

    vector_init(pvec);
    deque_init(pdeq);
    for (i = 0; i < 10; ++i) {
        deque_push_back(pdeq, i);
        vector_push_back(pvec, pdeq);
        vector_push_back(pvec, pdeq);
        vector_push_back(pvec, pdeq);
    }
    deque_pop_back(pdeq);
    deque_pop_back(pdeq);
    deque_pop_back(pdeq);
    assert_true(_algo_count(vector_begin(pvec), vector_end(pvec), pdeq) == 3);
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

typedef struct _tag_test__algo_count__algo_count_varg__user_define {
    int a;
    int b;
}_test__algo_count__algo_count_varg__user_define_t;
static void _test__algo_count__algo_count_varg__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test__algo_count__algo_count_varg__user_define_t)) < 0 ? true : false;
}
void test__algo_count__algo_count_varg__user_define_0(void** state)
{
    list_t* plist = NULL;
    _test__algo_count__algo_count_varg__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}, {0, 0}};
    _test__algo_count__algo_count_varg__user_define_t t_elem = {8, 8};
    int i = 0;

    type_register(_test__algo_count__algo_count_varg__user_define_t, NULL, NULL, _test__algo_count__algo_count_varg__user_define, NULL);
    plist = create_list(_test__algo_count__algo_count_varg__user_define_t);
    list_init(plist);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        list_push_back(plist, &at_array[i]);
    }
    assert_true(_algo_count(list_begin(plist), list_end(plist), &t_elem) == 0);
    list_destroy(plist);
}

void test__algo_count__algo_count_varg__user_define_1(void** state)
{
    deque_t* pdeq = create_deque(_test__algo_count__algo_count_varg__user_define_t);
    _test__algo_count__algo_count_varg__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}, {0, 0}};
    _test__algo_count__algo_count_varg__user_define_t t_elem = {7, 8};
    int i = 0;

    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    assert_true(_algo_count(deque_begin(pdeq), deque_end(pdeq), &t_elem) == 1);
    deque_destroy(pdeq);
}

void test__algo_count__algo_count_varg__user_define_n(void** state)
{
    slist_t* pslist = create_slist(_test__algo_count__algo_count_varg__user_define_t);
    _test__algo_count__algo_count_varg__user_define_t at_array[] = {{1, 2}, {3, 4}, {0, 0}, {0, 0}, {9, 0}, {0, 0}};
    _test__algo_count__algo_count_varg__user_define_t t_elem = {0, 0};
    int i = 0;

    slist_init(pslist);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist, &at_array[i]);
    }
    assert_true(_algo_count(slist_begin(pslist), slist_end(pslist), &t_elem) == 3);
    slist_destroy(pslist);
}

/*
 * test _algo_search_n
 */
UT_CASE_DEFINATION(_algo_search_n)
void test__algo_search_n__invalid_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_search_n(deque_begin(pdeq), list_begin(plist), 10, 10));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_search_n__invalid_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(_algo_search_n(vector_end(pvec), vector_begin(pvec), 10, 0));
    vector_destroy(pvec);
}

void test__algo_search_n__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it_first;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_first._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_search_n(it_first, list_end(plist), 10, 0));
    list_destroy(plist);
}

void test__algo_search_n__range_empty(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    assert_true(iterator_equal(_algo_search_n(set_begin(pset), set_end(pset), 10, 0), set_end(pset)));
    set_destroy(pset);
}

void test__algo_search_n__count_0(void** state)
{
    multiset_t* pmset = create_multiset(int);
    int an_array[] = {1, 2, 3, 4, 5, 6};

    multiset_init_copy_array(pmset, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(_algo_search_n(multiset_begin(pmset), multiset_end(pmset), 0, 0), multiset_begin(pmset)));
    multiset_destroy(pmset);
}

void test__algo_search_n__c_builtin_match(void** state)
{
    vector_t* pvec = create_vector(int);
    int an_array[] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(_algo_search_n(vector_begin(pvec), vector_end(pvec), 4, 1), vector_begin(pvec)));
    vector_destroy(pvec);
}

void test__algo_search_n__c_builtin_mismatch(void** state)
{
    vector_t* pvec = create_vector(int);
    int an_array[] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(_algo_search_n(vector_begin(pvec), vector_end(pvec), 4, 8), vector_end(pvec)));
    vector_destroy(pvec);
}

void test__algo_search_n__cstr_match(void** state)
{
    list_t* plist = create_list(char*);
    const char* as_array[] = {"ABC", "ABC", "DEF", "XYZ", "XYZ"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(iterator_equal(_algo_search_n(list_begin(plist), list_end(plist), 1, "DEF"), iterator_advance(list_begin(plist), 2)));
    list_destroy(plist);
}

void test__algo_search_n__cstr_mismatch(void** state)
{
    list_t* plist = create_list(char*);
    const char* as_array[] = {"ABC", "ABC", "DEF", "XYZ", "XYZ"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(iterator_equal(_algo_search_n(list_begin(plist), list_end(plist), 2, "DEF"), list_end(plist)));
    list_destroy(plist);
}

void test__algo_search_n__cstl_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][2] = {{1, 1}, {2, 2}, {2, 2}, {3, 3}, {4, 4}};
    int an_array[] = {2, 2};
    int i = 0;

    deque_init(pdeq);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, pvec);
    }
    vector_assign_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(_algo_search_n(deque_begin(pdeq), deque_end(pdeq), 2, pvec), iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test__algo_search_n__cstl_builtin_mismatch(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][2] = {{1, 1}, {2, 2}, {2, 2}, {3, 3}, {4, 4}};
    int an_array[] = {2, 2};
    int i = 0;

    deque_init(pdeq);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, pvec);
    }
    vector_assign_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(_algo_search_n(deque_begin(pdeq), deque_end(pdeq), 9, pvec), deque_end(pdeq)));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

typedef struct _tag_test__algo_search_n__user_define {
    int a;
    int b;
} _test__algo_search_n__user_define_t;
static void _test__algo_search_n__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test__algo_search_n__user_define_t)) < 0 ? true : false;
}
void test__algo_search_n__user_define_match(void** state)
{
    list_t* plist = NULL;
    _test__algo_search_n__user_define_t at_array[] = {{8, 8}, {8, 8}, {9, 9}, {9, 9}, {9, 9}, {9, 9}};
    _test__algo_search_n__user_define_t t_elem = {9, 9};
    int i = 0;

    type_register(_test__algo_search_n__user_define_t, NULL, NULL, _test__algo_search_n__user_define, NULL);
    plist = create_list(_test__algo_search_n__user_define_t);
    list_init(plist);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        list_push_back(plist, &at_array[i]);
    }
    assert_true(iterator_equal(_algo_search_n(list_begin(plist), list_end(plist), 4, &t_elem), iterator_advance(list_begin(plist), 2)));
    list_destroy(plist);
}

void test__algo_search_n__user_define_mismatch(void** state)
{
    list_t* plist = create_list(_test__algo_search_n__user_define_t);
    _test__algo_search_n__user_define_t at_array[] = {{8, 8}, {8, 8}, {9, 9}, {9, 9}, {9, 9}, {9, 9}};
    _test__algo_search_n__user_define_t t_elem = {19, 19};
    int i = 0;

    list_init(plist);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        list_push_back(plist, &at_array[i]);
    }
    assert_true(iterator_equal(_algo_search_n(list_begin(plist), list_end(plist), 4, &t_elem), list_end(plist)));
    list_destroy(plist);
}

/*
 * test _algo_search_n_if and _algo_search_n_if_varg
 */
UT_CASE_DEFINATION(_algo_search_n_if__algo_search_n_if_varg)
void test__algo_search_n_if__algo_search_n_if_varg__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_search_n_if(vector_begin(pvec), list_end(plist), 10, NULL, 1));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_search_n_if__algo_search_n_if_varg__invalid_range2(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_search_n_if(slist_end(pslist), slist_begin(pslist), 10, NULL, 1));
    slist_destroy(pslist);
}

void test__algo_search_n_if__algo_search_n_if_varg__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it_last;

    deque_init_n(pdeq, 10);
    it_last = deque_end(pdeq);
    it_last._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_search_n_if(deque_begin(pdeq), it_last, 10, NULL, 1));
    deque_destroy(pdeq);
}

void test__algo_search_n_if__algo_search_n_if_varg__range_empty(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    assert_true(iterator_equal(_algo_search_n_if(set_begin(pset), set_end(pset), 10, NULL, 0), set_end(pset)));
    set_destroy(pset);
}

void test__algo_search_n_if__algo_search_n_if_varg__count_0(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8};

    hash_set_init_copy_array(phset, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(_algo_search_n_if(hash_set_begin(phset), hash_set_end(phset), 0, NULL, 10), hash_set_begin(phset)));
    hash_set_destroy(phset);
}

void test__algo_search_n_if__algo_search_n_if_varg__bfun_NULL_match(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 123);
    assert_true(iterator_equal(_algo_search_n_if(vector_begin(pvec), vector_end(pvec), 10, NULL, 123), vector_begin(pvec)));
    vector_destroy(pvec);
}

void test__algo_search_n_if__algo_search_n_if_varg__bfun_NULL_mismatch(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 123);
    assert_true(iterator_equal(_algo_search_n_if(vector_begin(pvec), vector_end(pvec), 10, NULL, 111), vector_end(pvec)));
    vector_destroy(pvec);
}

static void _test__algo_search_n_if__algo_search_n_if_varg__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__algo_search_n_if__algo_search_n_if_varg__c_builtin_match(void** state)
{
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(
        _algo_search_n_if(list_begin(plist), list_end(plist), 3, _test__algo_search_n_if__algo_search_n_if_varg__c_builtin, 5),
        list_begin(plist)));
    list_destroy(plist);
}

void test__algo_search_n_if__algo_search_n_if_varg__c_builtin_mismatch(void** state)
{
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init_copy_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(
        _algo_search_n_if(list_begin(plist), list_end(plist), 3, _test__algo_search_n_if__algo_search_n_if_varg__c_builtin, 0),
        list_end(plist)));
    list_destroy(plist);
}

static void _test__algo_search_n_if__algo_search_n_if_varg__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strlen((char*)cpv_first) == strlen((char*)cpv_second) ? true : false;
}
void test__algo_search_n_if__algo_search_n_if_varg__cstr_match(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"a", "bb", "xxx", "ooo", "mm", "haha"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(iterator_equal(
        _algo_search_n_if(deque_begin(pdeq), deque_end(pdeq), 2, _test__algo_search_n_if__algo_search_n_if_varg__cstr, "abc"),
        iterator_next_n(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_search_n_if__algo_search_n_if_varg__cstr_mismatch(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"a", "bb", "xxx", "ooo", "mm", "haha"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(iterator_equal(
        _algo_search_n_if(deque_begin(pdeq), deque_end(pdeq), 2, _test__algo_search_n_if__algo_search_n_if_varg__cstr, "abcdef"),
        deque_end(pdeq)));
    deque_destroy(pdeq);
}

static void _test__algo_search_n_if__algo_search_n_if_varg__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = list_size((list_t*)cpv_first) == list_size((list_t*)cpv_second) ? true : false;
}
void test__algo_search_n_if__algo_search_n_if_varg__cstl_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);
    list_t* plist = create_list(int);
    int aan_array[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    int an_array[] = {8, 8, 8, 8};
    int i = 0;

    deque_init(pdeq);
    list_init(plist);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        list_assign_array(plist, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, plist);
    }
    list_assign_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(
        _algo_search_n_if(deque_begin(pdeq), deque_end(pdeq), 3, _test__algo_search_n_if__algo_search_n_if_varg__cstl_builtin, plist),
        deque_begin(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_search_n_if__algo_search_n_if_varg__cstl_builtin_mismatch(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);
    list_t* plist = create_list(int);
    int aan_array[][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    int an_array[] = {8, 8, 8, 8, 8};
    int i = 0;

    deque_init(pdeq);
    list_init(plist);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        list_assign_array(plist, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, plist);
    }
    list_assign_array(plist, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(iterator_equal(
        _algo_search_n_if(deque_begin(pdeq), deque_end(pdeq), 1, _test__algo_search_n_if__algo_search_n_if_varg__cstl_builtin, plist),
        deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

typedef struct _tag_test__algo_search_n_if__algo_search_n_if_varg__user_define {
    int a;
    int b;
} _test__algo_search_n_if__algo_search_n_if_varg__user_define_t;
static void _test__algo_search_n_if__algo_search_n_if_varg__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test__algo_search_n_if__algo_search_n_if_varg__user_define_t*)cpv_first)->a < ((_test__algo_search_n_if__algo_search_n_if_varg__user_define_t*)cpv_second)->a &&
        ((_test__algo_search_n_if__algo_search_n_if_varg__user_define_t*)cpv_first)->b < ((_test__algo_search_n_if__algo_search_n_if_varg__user_define_t*)cpv_second)->b ?
        true : false;
}
void test__algo_search_n_if__algo_search_n_if_varg__user_define_match(void** state)
{
    slist_t* pslist = NULL;
    _test__algo_search_n_if__algo_search_n_if_varg__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test__algo_search_n_if__algo_search_n_if_varg__user_define_t t_elem = {4, 5};
    int i = 0;

    type_register(_test__algo_search_n_if__algo_search_n_if_varg__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test__algo_search_n_if__algo_search_n_if_varg__user_define_t);
    slist_init(pslist);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist, &at_array[i]);
    }
    assert_true(iterator_equal(
        _algo_search_n_if(slist_begin(pslist), slist_end(pslist), 2, _test__algo_search_n_if__algo_search_n_if_varg__user_define, &t_elem),
        iterator_advance(slist_begin(pslist), 3)));
    slist_destroy(pslist);
}

void test__algo_search_n_if__algo_search_n_if_varg__user_define_mismatch(void** state)
{
    slist_t* pslist = create_slist(_test__algo_search_n_if__algo_search_n_if_varg__user_define_t);
    _test__algo_search_n_if__algo_search_n_if_varg__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test__algo_search_n_if__algo_search_n_if_varg__user_define_t t_elem = {4, 5};
    int i = 0;

    slist_init(pslist);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist, &at_array[i]);
    }
    assert_true(iterator_equal(
        _algo_search_n_if(slist_begin(pslist), slist_end(pslist), 2, _test__algo_search_n_if__algo_search_n_if_varg__user_define, &t_elem),
        iterator_advance(slist_begin(pslist), 3)));
    slist_destroy(pslist);
}

