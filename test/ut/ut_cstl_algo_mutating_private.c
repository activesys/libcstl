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

/*
 * test _algo_replace_copy_if and _algo_replace_copy_if_varg
 */
UT_CASE_DEFINATION(_algo_replace_copy_if__algo_replace_copy_if_varg)
void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_replace_copy_if(vector_begin(pvec), list_begin(plist), deque_begin(pdeq), NULL, 10));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_replace_copy_if(vector_end(pvec), vector_begin(pvec), list_begin(plist), NULL, 10));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_replace_copy_if(it, deque_end(pdeq), slist_begin(pslist), NULL, 10));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_dest_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_replace_copy_if(vector_begin(pvec), vector_end(pvec), it, NULL, 10));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_range_not_same_type(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(double);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_replace_copy_if(list_begin(plist), list_end(plist), slist_begin(pslist), NULL, 10));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test__algo_replace_copy_if__algo_replace_copy_if_varg__bfun_op_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it;

    vector_init_elem(pvec, 10, 1);
    list_init_elem(plist, 10, 1);
    it = _algo_replace_copy_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), NULL, 100);
    assert_true(iterator_equal(it, list_end(plist)));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

static void _test__algo_replace_copy_if__algo_replace_copy_if_varg__c_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}
void test__algo_replace_copy_if__algo_replace_copy_if_varg__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_result[] = {1, 0, 3, 0, 5, 0, 7, 0, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    vector_init_n(pvec_dest, 10);
    it = _algo_replace_copy_if(vector_begin(pvec_src), vector_end(pvec_src), vector_begin(pvec_dest), _test__algo_replace_copy_if__algo_replace_copy_if_varg__c_builtin, 0);
    assert_true(iterator_equal(it, vector_end(pvec_dest)));
    assert_true(vector_equal(pvec_dest, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_dest);
    vector_destroy(pvec_result);
}

static void _test__algo_replace_copy_if__algo_replace_copy_if_varg__cstr(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = strncmp((char*)cpv_input, "Windows", strlen("Windows")) == 0 ? true : false;
}
void test__algo_replace_copy_if__algo_replace_copy_if_varg__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_dest = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"Windows 8", "Windows 7", "Windows vista", "Windows XP", "Windows 2003"};
    iterator_t it;

    list_init_copy_array(plist_src, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_n(plist_dest, 5);
    list_init_elem(plist_result, 5, "Linux");
    it = _algo_replace_copy_if(list_begin(plist_src), list_end(plist_src), list_begin(plist_dest), _test__algo_replace_copy_if__algo_replace_copy_if_varg__cstr, "Linux");
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

static void _test__algo_replace_copy_if__algo_replace_copy_if_varg__cstl_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = set_size((set_t*)cpv_input) == 3 ? true : false;
}
void test__algo_replace_copy_if__algo_replace_copy_if_varg__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_dest = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array[][3] = {{1, 2, 3}, {4, 4, 5}, {9, 9, 9}, {0, 0, 0}, {4, 5, 6}};
    int aan_result[][3] = {{100, 200, 300}, {4, 4, 5}, {9, 9, 9}, {0, 0, 0}, {100, 200, 300}};
    iterator_t it;
    int i = 0;

    deque_init(pdeq_src);
    deque_init_n(pdeq_dest, 5);
    deque_init(pdeq_result);
    set_init(pset);
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
    set_insert_array(pset, aan_result[0], sizeof(aan_result[0])/sizeof(aan_result[0][0]));
    it = _algo_replace_copy_if(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest), _test__algo_replace_copy_if__algo_replace_copy_if_varg__cstl_builtin, pset);
    assert_true(iterator_equal(it, deque_end(pdeq_dest)));
    assert_true(deque_equal(pdeq_dest, pdeq_result));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test__algo_replace_copy_if__algo_replace_copy_if_varg__user_define {
    int a;
    int b;
} _test__algo_replace_if__algo_replace_copy_if_varg__user_define_t;
static void _test__algo_replace_copy_if__algo_replace_copy_if_varg__user_define(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output =
        ((_test__algo_replace_if__algo_replace_copy_if_varg__user_define_t*)cpv_input)->a * 2 ==
        ((_test__algo_replace_if__algo_replace_copy_if_varg__user_define_t*)cpv_input)->b ? true : false;
}
void test__algo_replace_copy_if__algo_replace_copy_if_varg__user_define(void** state)
{
    slist_t* pslist_src = NULL;
    slist_t* pslist_dest = NULL;
    slist_t* pslist_result = NULL;
    _test__algo_replace_if__algo_replace_copy_if_varg__user_define_t at_array[] = {{1, 2}, {3, 6}, {4, 8}, {5, 0}, {0, 0}};
    _test__algo_replace_if__algo_replace_copy_if_varg__user_define_t at_result[] = {{100, 100}, {100, 100}, {100, 100}, {5, 0}, {100, 100}};
    _test__algo_replace_if__algo_replace_copy_if_varg__user_define_t t_elem = {100, 100};
    iterator_t it;
    int i = 0;

    type_register(_test__algo_replace_if__algo_replace_copy_if_varg__user_define_t, NULL, NULL, NULL, NULL);
    pslist_src = create_slist(_test__algo_replace_if__algo_replace_copy_if_varg__user_define_t);
    pslist_dest = create_slist(_test__algo_replace_if__algo_replace_copy_if_varg__user_define_t);
    pslist_result = create_slist(_test__algo_replace_if__algo_replace_copy_if_varg__user_define_t);
    slist_init(pslist_src);
    slist_init_n(pslist_dest, 5);
    slist_init(pslist_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        slist_push_front(pslist_src, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        slist_push_front(pslist_result, &at_result[i]);
    }
    it = _algo_replace_copy_if(slist_begin(pslist_src), slist_end(pslist_src), slist_begin(pslist_dest),
        _test__algo_replace_copy_if__algo_replace_copy_if_varg__user_define, &t_elem);
    assert_true(iterator_equal(it, slist_end(pslist_dest)));
    assert_true(slist_equal(pslist_dest, pslist_result));
    slist_destroy(pslist_src);
    slist_destroy(pslist_dest);
    slist_destroy(pslist_result);
}

/*
 * test _algo_fill and _algo_fill_varg
 */
UT_CASE_DEFINATION(_algo_fill__algo_fill_varg)
void test__algo_fill__algo_fill_varg__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_fill(vector_begin(pvec), list_begin(plist), 100));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_fill__algo_fill_varg__invalid_range2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);
    expect_assert_failure(_algo_fill(vector_end(pvec), vector_begin(pvec), 100));
    vector_destroy(pvec);
}

void test__algo_fill__algo_fill_varg__invalid_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_fill(it, deque_end(pdeq), 100));
    deque_destroy(pdeq);
}

void test__algo_fill__algo_fill_varg__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    _algo_fill(slist_begin(pslist), slist_end(pslist), 100);
    assert_true(slist_empty(pslist));
    slist_destroy(pslist);
}

void test__algo_fill__algo_fill_varg__c_builtin(void** state)
{
    vector_t* pvec_fill = create_vector(int);
    vector_t* pvec_result = create_vector(int);

    vector_init_n(pvec_fill, 10);
    vector_init_elem(pvec_result, 10, 100);
    _algo_fill(vector_begin(pvec_fill), vector_end(pvec_fill), 100);
    assert_true(vector_equal(pvec_fill, pvec_result));
    vector_destroy(pvec_fill);
    vector_destroy(pvec_result);
}

void test__algo_fill__algo_fill_varg__cstr(void** state)
{
    list_t* plist_fill = create_list(char*);
    list_t* plist_result = create_list(char*);

    list_init_n(plist_fill, 10);
    list_init_elem(plist_result, 10, "Hello");
    _algo_fill(list_begin(plist_fill), list_end(plist_fill), "Hello");
    assert_true(list_equal(plist_fill, plist_result));
    list_destroy(plist_fill);
    list_destroy(plist_result);
}

void test__algo_fill__algo_fill_varg__cstl_builtin(void** state)
{
    deque_t* pdeq_fill = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);

    set_init(pset);
    set_insert(pset, 100);
    set_insert(pset, 200);
    deque_init_n(pdeq_fill, 10);
    deque_init_elem(pdeq_result, 10, pset);
    _algo_fill(deque_begin(pdeq_fill), deque_end(pdeq_fill), pset);
    assert_true(deque_equal(pdeq_fill, pdeq_result));
    set_destroy(pset);
    deque_destroy(pdeq_fill);
    deque_destroy(pdeq_result);
}

typedef struct _tag_test__algo_fill__algo_fill_varg__user_define {
    int a;
    int b;
} _test__algo_fill__algo_fill_varg__user_define_t;
void test__algo_fill__algo_fill_varg__user_define(void** state)
{
    slist_t* pslist_fill = NULL;
    slist_t* pslist_result = NULL;
    _test__algo_fill__algo_fill_varg__user_define_t t_elem = {100, 100};

    type_register(_test__algo_fill__algo_fill_varg__user_define_t, NULL, NULL, NULL, NULL);
    pslist_fill = create_slist(_test__algo_fill__algo_fill_varg__user_define_t);
    pslist_result = create_slist(_test__algo_fill__algo_fill_varg__user_define_t);
    slist_init_n(pslist_fill, 10);
    slist_init_elem(pslist_result, 10, &t_elem);
    _algo_fill(slist_begin(pslist_fill), slist_end(pslist_fill), &t_elem);
    assert_true(slist_equal(pslist_fill, pslist_result));
    slist_destroy(pslist_fill);
    slist_destroy(pslist_result);
}

/*
 * test _algo_fill_n and _algo_fill_n_varg
 */
UT_CASE_DEFINATION(_algo_fill_n__algo_fill_n_varg)
void test__algo_fill_n__algo_fill_n_varg__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    it = vector_begin(pvec);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_fill_n(it, 10, 100));
    vector_destroy(pvec);
}

void test__algo_fill_n__algo_fill_n_varg__empty(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init(plist);
    it = _algo_fill_n(list_begin(plist), 0, 10);
    assert_true(iterator_equal(it, list_begin(plist)));
    assert_true(list_empty(plist));
    list_destroy(plist);
}

void test__algo_fill_n__algo_fill_n_varg__c_builtin(void** state)
{
    vector_t* pvec_fill = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    iterator_t it;

    vector_init_n(pvec_fill, 10);
    vector_init_elem(pvec_result, 10, 100);
    it = _algo_fill_n(vector_begin(pvec_fill), 10, 100);
    assert_true(iterator_equal(it, vector_end(pvec_fill)));
    assert_true(vector_equal(pvec_fill, pvec_result));
    vector_destroy(pvec_fill);
    vector_destroy(pvec_result);
}

void test__algo_fill_n__algo_fill_n_varg__cstr(void** state)
{
    list_t* plist_fill = create_list(char*);
    list_t* plist_result = create_list(char*);
    iterator_t it;

    list_init_n(plist_fill, 10);
    list_init_elem(plist_result, 10, "Linux");
    it = _algo_fill_n(list_begin(plist_fill), 10, "Linux");
    assert_true(iterator_equal(it, list_end(plist_fill)));
    assert_true(list_equal(plist_fill, plist_result));
    list_destroy(plist_fill);
    list_destroy(plist_result);
}

void test__algo_fill_n__algo_fill_n_varg__cstl_builtin(void** state)
{
    deque_t* pdeq_fill = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    iterator_t it;

    set_init(pset);
    set_insert(pset, 100);
    deque_init_n(pdeq_fill, 10);
    deque_init_elem(pdeq_result, 10, pset);
    it = _algo_fill_n(deque_begin(pdeq_fill), 10, pset);
    assert_true(iterator_equal(it, deque_end(pdeq_fill)));
    assert_true(deque_equal(pdeq_fill, pdeq_result));
    set_destroy(pset);
    deque_destroy(pdeq_fill);
    deque_destroy(pdeq_result);
}

typedef struct _tag_test__algo_fill_n__algo_fill_n_varg__user_define {
    int a;
    int b;
} _test__algo_fill_n__algo_fill_n_varg__user_define_t;
void test__algo_fill_n__algo_fill_n_varg__user_define(void** state)
{
    slist_t* pslist_fill = NULL;
    slist_t* pslist_result = NULL;
    _test__algo_fill_n__algo_fill_n_varg__user_define_t t_elem = {100, 100};
    iterator_t it;

    type_register(_test__algo_fill_n__algo_fill_n_varg__user_define_t, NULL, NULL, NULL, NULL);
    pslist_fill = create_slist(_test__algo_fill_n__algo_fill_n_varg__user_define_t);
    pslist_result = create_slist(_test__algo_fill_n__algo_fill_n_varg__user_define_t);
    slist_init_n(pslist_fill, 10);
    slist_init_elem(pslist_result, 10, &t_elem);
    it = _algo_fill_n(slist_begin(pslist_fill), 10, &t_elem);
    assert_true(iterator_equal(it, slist_end(pslist_fill)));
    assert_true(slist_equal(pslist_fill, pslist_result));
    slist_destroy(pslist_fill);
    slist_destroy(pslist_result);
}

/*
 * test _algo_remove and _algo_remove_varg
 */
UT_CASE_DEFINATION(_algo_remove__algo_remove_varg)
void test__algo_remove__algo_remove_varg__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_remove(vector_begin(pvec), list_begin(plist), 10));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_remove__algo_remove_varg__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_remove(deque_end(pdeq), deque_begin(pdeq), 10));
    deque_destroy(pdeq);
}

void test__algo_remove__algo_remove_varg__invalid_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    iterator_t it;

    slist_init_n(pslist, 10);
    it = slist_begin(pslist);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_remove(it, slist_end(pslist), 100));
    slist_destroy(pslist);
}

void test__algo_remove__algo_remove_varg__empty(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it;

    set_init(pset);
    it = _algo_remove(set_begin(pset), set_end(pset), 10);
    assert_true(iterator_equal(it, set_begin(pset)));
    assert_true(set_empty(pset));
    set_destroy(pset);
}

void test__algo_remove__algo_remove_varg__c_builtin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_array[] = {1, 2, 2, 2, 3, 4, 2, 8, 9, 0};
    int an_result[] = {1, 3, 4, 8, 9, 0, 2, 8, 9, 0};
    iterator_t it;

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    it = _algo_remove(vector_begin(pvec), vector_end(pvec), 2);
    assert_true(iterator_equal(it, iterator_next_n(vector_begin(pvec), 6)));
    assert_true(vector_equal(pvec, pvec_result));
    vector_destroy(pvec);
    vector_destroy(pvec_result);
}

void test__algo_remove__algo_remove_varg__cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_array[] = {"Windows", "MAC", "AIX", "Linux", "Windows", "FreeBSD"};
    const char* as_result[] = {"MAC", "AIX", "Linux", "FreeBSD", "Windows", "FreeBSD"};
    iterator_t it;

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    it = _algo_remove(list_begin(plist), list_end(plist), "Windows");
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist), 4)));
    assert_true(list_equal(plist, plist_result));
    list_destroy(plist);
    list_destroy(plist_result);
}

void test__algo_remove__algo_remove_varg__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);
    deque_t* pdeq_result = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array[][3] = {{0}, {0}, {0}, {0}, {0}};
    int aan_result[][3] = {{0}, {0}, {0}, {0}, {0}};
    iterator_t it;
    int i = 0;

    deque_init(pdeq);
    deque_init(pdeq_result);
    set_init(pset);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        deque_push_back(pdeq, pset);
    }
    for (i = 0; i < sizeof(aan_result)/sizeof(aan_result[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_result[i], sizeof(aan_result[i])/sizeof(aan_result[i][0]));
        deque_push_back(pdeq_result, pset);
    }
    set_clear(pset);
    set_insert(pset, 0);
    it = _algo_remove(deque_begin(pdeq), deque_end(pdeq), pset);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
    set_destroy(pset);
}

typedef struct _tag_test__algo_remove__algo_remove_varg__user_define {
    int a;
    int b;
} _test__algo_remove__algo_remove_varg__user_define_t;
static void _test__algo_remove__algo_remove_varg__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test__algo_remove__algo_remove_varg__user_define_t)) < 0 ? true : false;
}
void test__algo_remove__algo_remove_varg__user_define(void** state)
{
    deque_t* pdeq = NULL;
    deque_t* pdeq_result = NULL;
    _test__algo_remove__algo_remove_varg__user_define_t at_array[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test__algo_remove__algo_remove_varg__user_define_t at_result[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test__algo_remove__algo_remove_varg__user_define_t t_elem = {0, 0};
    iterator_t it;
    int i = 0;

    type_register(_test__algo_remove__algo_remove_varg__user_define_t, NULL, NULL, _test__algo_remove__algo_remove_varg__user_define, NULL);
    pdeq = create_deque(_test__algo_remove__algo_remove_varg__user_define_t);
    pdeq_result = create_deque(_test__algo_remove__algo_remove_varg__user_define_t);
    deque_init(pdeq);
    deque_init(pdeq_result);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        deque_push_back(pdeq, &at_array[i]);
    }
    for (i = 0; i < sizeof(at_result)/sizeof(at_result[0]); ++i) {
        deque_push_back(pdeq_result, &at_result[i]);
    }
    it = _algo_remove(deque_begin(pdeq), deque_end(pdeq), &t_elem);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    assert_true(deque_equal(pdeq, pdeq_result));
    deque_destroy(pdeq);
    deque_destroy(pdeq_result);
}

/*
 * test _algo_remove_copy and _algo_remove_copy_varg
 */
UT_CASE_DEFINATION(_algo_remove_copy__algo_remove_copy_varg)
void test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(_algo_remove_copy(vector_begin(pvec), list_begin(plist), deque_begin(pdeq), 10));
    vector_destroy(pvec);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range2(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_remove_copy(list_end(plist), list_begin(plist), slist_begin(pslist), 10));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_remove_copy(it, deque_end(pdeq), list_begin(plist), 10));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test__algo_remove_copy__algo_remove_copy_varg__invalid_dest_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    it = deque_begin(pdeq);
    it._t_iteratortype = 100;
    expect_assert_failure(_algo_remove_copy(vector_begin(pvec), vector_end(pvec), it, 10));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_remove_copy__algo_remove_copy_varg__invalid_range_not_same_type(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(double);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(_algo_remove_copy(list_begin(plist), list_end(plist), slist_begin(pslist), 10));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test__algo_remove_copy__algo_remove_copy_varg__source_range_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it;

    vector_init(pvec);
    list_init(plist);
    it = _algo_remove_copy(vector_begin(pvec), vector_end(pvec), list_begin(plist), 10);
    assert_true(iterator_equal(it, list_begin(plist)));
    assert_true(vector_empty(pvec));
    assert_true(list_empty(plist));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test__algo_remove_copy__algo_remove_copy_varg__c_builtin(void** state)
{
    vector_t* pvec_src = create_vector(int);
    vector_t* pvec_dest = create_vector(int);
    vector_t* pvec_result = create_vector(int);
    int an_src[] = {1, 1, 8, 8, 1, 1, 8, 8, 8, 8};
    int an_result[] = {8, 8, 8, 8, 8, 8};
    iterator_t it;

    vector_init_copy_array(pvec_src, an_src, sizeof(an_src)/sizeof(an_src[0]));
    vector_init_copy_array(pvec_result, an_result, sizeof(an_result)/sizeof(an_result[0]));
    vector_init_n(pvec_dest, vector_size(pvec_result));
    it = _algo_remove_copy(vector_begin(pvec_src), vector_end(pvec_src), vector_begin(pvec_dest), 1);
    assert_true(iterator_equal(it, vector_end(pvec_dest)));
    assert_true(vector_equal(pvec_dest, pvec_result));
    vector_destroy(pvec_src);
    vector_destroy(pvec_dest);
    vector_destroy(pvec_result);
}

void test__algo_remove_copy__algo_remove_copy_varg__cstr(void** state)
{
    list_t* plist_src = create_list(char*);
    list_t* plist_dest = create_list(char*);
    list_t* plist_result = create_list(char*);
    const char* as_src[] = {"Linux", "Linux", "Linux", "MSDOS", "Windows", "FreeBSD"};
    const char* as_result[] = {"Linux", "Linux", "Linux", "Windows", "FreeBSD"};
    iterator_t it;

    list_init_copy_array(plist_src, as_src, sizeof(as_src)/sizeof(as_src[0]));
    list_init_copy_array(plist_result, as_result, sizeof(as_result)/sizeof(as_result[0]));
    list_init_n(plist_dest, list_size(plist_result));
    it = _algo_remove_copy(list_begin(plist_src), list_end(plist_src), list_begin(plist_dest), "MSDOS");
    assert_true(iterator_equal(it, list_end(plist_dest)));
    assert_true(list_equal(plist_dest, plist_result));
    list_destroy(plist_src);
    list_destroy(plist_dest);
    list_destroy(plist_result);
}

void test__algo_remove_copy__algo_remove_copy_varg__cstl_builtin(void** state)
{
    deque_t* pdeq_src = create_deque(set_t<int>);
    deque_t* pdeq_dest = create_deque(set_t<int>);
    set_t* pset = create_set(int);
    iterator_t it;

    set_init(pset);
    set_insert(pset, 100);
    set_insert(pset, 200);
    deque_init_elem(pdeq_src, 10, pset);
    deque_init(pdeq_dest);
    it = _algo_remove_copy(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest), pset);
    assert_true(iterator_equal(it, deque_begin(pdeq_dest)));
    assert_true(deque_empty(pdeq_dest));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_dest);
    set_destroy(pset);
}

typedef struct _tag_test__algo_remove_copy__algo_remove_copy_varg__user_define {
    int a;
    int b;
} _test__algo_remove_copy__algo_remove_copy_varg__user_define_t;
static void _test__algo_remove_copy__algo_remove_copy_varg__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test__algo_remove_copy__algo_remove_copy_varg__user_define_t)) < 0 ? true : false;
}
void test__algo_remove_copy__algo_remove_copy_varg__user_define(void** state)
{
    deque_t* pdeq_src = NULL;
    deque_t* pdeq_dest = NULL;
    _test__algo_remove_copy__algo_remove_copy_varg__user_define_t t_elem = {100, 200};
    iterator_t it;

    type_register(_test__algo_remove_copy__algo_remove_copy_varg__user_define_t, NULL, NULL, _test__algo_remove_copy__algo_remove_copy_varg__user_define, NULL);
    pdeq_src = create_deque(_test__algo_remove_copy__algo_remove_copy_varg__user_define_t);
    pdeq_dest = create_deque(_test__algo_remove_copy__algo_remove_copy_varg__user_define_t);
    deque_init_elem(pdeq_src, 10, &t_elem);
    deque_init_copy(pdeq_dest, pdeq_src);
    t_elem.a = t_elem.b = 0;
    it = _algo_remove_copy(deque_begin(pdeq_src), deque_end(pdeq_src), deque_begin(pdeq_dest), &t_elem);
    assert_true(iterator_equal(it, deque_end(pdeq_dest)));
    assert_true(deque_equal(pdeq_src, pdeq_dest));
    deque_destroy(pdeq_src);
    deque_destroy(pdeq_dest);
}

