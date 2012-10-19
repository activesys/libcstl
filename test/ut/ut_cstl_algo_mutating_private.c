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
#include "ut_cstl_algo_mutating_private.h"

UT_SUIT_DEFINATION(cstl_algo_mutating_private, _algo_replace_once__algo_replace_once_varg)

/*
 * test _algo_replace_once and _algo_replace_once_varg
 */
UT_CASE_DEFINATION(_algo_replace_once__algo_replace_once_varg)
void test__algo_replace_once__algo_replace_once_varg__invalid_iter(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_replace_once(it, 100));
    vector_destroy(pvec);
}

void test__algo_replace_once__algo_replace_once_varg__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    _algo_replace_once(vector_begin(pvec), 100);
    assert_true(*(int*)vector_at(pvec, 0) == 100);
    vector_destroy(pvec);
}

void test__algo_replace_once__algo_replace_once_varg__cstr(void** state)
{
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "abc");
    _algo_replace_once(list_begin(plist), "Linux");
    assert_true(strcmp((char*)iterator_get_pointer(list_begin(plist)), "Linux") == 0);
    list_destroy(plist);
}

void test__algo_replace_once__algo_replace_once_varg__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);
    set_t* pset = create_set(int);

    deque_init_n(pdeq, 10);
    set_init(pset);
    set_insert(pset, 100);
    _algo_replace_once(deque_begin(pdeq), pset);
    assert_true(set_equal((set_t*)iterator_get_pointer(deque_begin(pdeq)), pset));
    deque_destroy(pdeq);
    set_destroy(pset);
}

typedef struct _tag_test__algo_replace_once__algo_replace_once_varg {
    int a;
    int b;
} _test__algo_replace_once__algo_replace_once_varg_t;
void test__algo_replace_once__algo_replace_once_varg__user_define(void** state)
{
    slist_t* pslist = NULL;
    _test__algo_replace_once__algo_replace_once_varg_t t_elem = {100, 100};

    type_register(_test__algo_replace_once__algo_replace_once_varg_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test__algo_replace_once__algo_replace_once_varg_t);
    slist_init_n(pslist, 10);
    _algo_replace_once(slist_begin(pslist), &t_elem);
    assert_true(memcmp(iterator_get_pointer(slist_begin(pslist)), &t_elem, sizeof(_test__algo_replace_once__algo_replace_once_varg_t)) == 0);
    slist_destroy(pslist);
}

