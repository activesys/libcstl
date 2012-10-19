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

/*
 * test _algo_replace_if and _algo_replace_if_varg
 */
UT_CASE_DEFINATION(_algo_replace_if__algo_replace_if_varg)
void test__algo_replace_if__algo_replace_if_varg__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_replace_if(vector_begin(pvec), list_begin(plist), NULL, 10));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_replace_if__algo_replace_if_varg__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_replace_if(deque_end(pdeq), deque_begin(pdeq), NULL, 10));
    deque_destroy(pdeq);
}

void test__algo_replace_if__algo_replace_if_varg__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(_algo_replace_if(it, slist_end(pslist), NULL, 10));
    slist_destroy(pslist);
}

void test__algo_replace_if__algo_replace_if_varg__range_empty(void** state)
{
    set_t* pset = create_set(int);

    set_init(pset);
    _algo_replace_if(set_begin(pset), set_end(pset), NULL, 10);
    assert_true(set_empty(pset));
    set_destroy(pset);
}

void test__algo_replace_if__algo_replace_if_varg__ufun_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 2, 2, 2, 3, 4, 5, 2, 2, 4, 5};
    int an_result[] = {1, 2, 2, 2, 3, 4, 5, 2, 2, 4, 5};

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_replace_if(vector_begin(pvec), vector_end(pvec), NULL, 0);
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

static void _test__algo_replace_if__algo_replace_if_varg__c_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}
void test__algo_replace_if__algo_replace_if_varg__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 0, 3, 0, 5, 0, 7, 0, 9, 0};

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    _algo_replace_if(vector_begin(pvec), vector_end(pvec), _test__algo_replace_if__algo_replace_if_varg__c_builtin, 0);
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

static void _test__algo_replace_if__algo_replace_if_varg__cstr(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = strncmp((char*)cpv_input, "Windows", strlen("Windows")) == 0 ? true : false;
}
void test__algo_replace_if__algo_replace_if_varg__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"FreeBSD", "Windows 95", "Windows 7", "Windows XP", "CentOS", "AIX"};
    const char* as_result[] = {"FreeBSD", "Linux", "Linux", "Linux", "CentOS", "AIX"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    _algo_replace_if(list_begin(plist), list_end(plist), _test__algo_replace_if__algo_replace_if_varg__cstr, "Linux");
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);

}

static void _test__algo_replace_if__algo_replace_if_varg__cstl_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)vector_at((vector_t*)cpv_input, 0) + *(int*)vector_at((vector_t*)cpv_input, 1) == 10 ? true : false;
}
void test__algo_replace_if__algo_replace_if_varg__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    deque_t* pdeq_result = create_deque(vector_t<int>);
    vector_t* pvec_old = create_vector(int);
    vector_t* pvec_new = create_vector(int);
    int aan_array[][2] = {{1, 2}, {2, 8}, {3, 7}, {4, 4}, {10, 1}};
    int aan_result[][2] = {{1, 2}, {0, 0}, {0, 0}, {4, 4}, {10, 1}};
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    vector_init(pvec_old);
    vector_init(pvec_new);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec_old, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, pvec_old);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        vector_assign_array(pvec_new, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pvec_new);
    }
    vector_assign_elem(pvec_new, 2, 0);
    _algo_replace_if(deque_begin(pdeq), deque_end(pdeq), _test__algo_replace_if__algo_replace_if_varg__cstl_builtin, pvec_new);
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    vector_destroy(pvec_old);
    vector_destroy(pvec_new);
}

typedef struct _tag_test__algo_replace_if__algo_replace_if_varg__user_define {
    int a;
    int b;
} _test__algo_replace_if__algo_replace_if_varg__user_define_t;
static void _test__algo_replace_if__algo_replace_if_varg__user_define(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test__algo_replace_if__algo_replace_if_varg__user_define_t*)cpv_input)->a ==
        ((_test__algo_replace_if__algo_replace_if_varg__user_define_t*)cpv_input)->b ?
        true : false;
}
void test__algo_replace_if__algo_replace_if_varg__user_define(void** state)
{
    slist_t* pslist = NULL;
    slist_t* pslist_result = NULL;
    _test__algo_replace_if__algo_replace_if_varg__user_define_t at_array[] = {{1, 2}, {5, 5}, {8, 8}, {0, 0}, {1, 9}};
    _test__algo_replace_if__algo_replace_if_varg__user_define_t at_result[] = {{1, 2}, {100, 100}, {100, 100}, {100, 100}, {1, 9}};
    _test__algo_replace_if__algo_replace_if_varg__user_define_t t_new = {100, 100};
    int i = 0;

    type_register(_test__algo_replace_if__algo_replace_if_varg__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test__algo_replace_if__algo_replace_if_varg__user_define_t);
    pslist_result = create_slist(_test__algo_replace_if__algo_replace_if_varg__user_define_t);
    slist_init(pslist);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    _algo_replace_if(slist_begin(pslist), slist_end(pslist), _test__algo_replace_if__algo_replace_if_varg__user_define, &t_new);
    assert_true(slist_equal(pslist, pslist_result));
    slist_destroy(pslist);
    slist_destroy(pslist_result);
}

