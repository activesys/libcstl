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

