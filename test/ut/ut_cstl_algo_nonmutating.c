#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/chash_map.h"
#include "cstl/chash_set.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl/cdeque.h"
#include "cstl/cslist.h"
#include "cstl/cmap.h"
#include "cstl/cset.h"
#include "cstl/cstack.h"
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

static void _fun_test_algo_for_each__cstr(const void* cpv_input, void* pv_output)
{
    size_t len = strlen((char*)cpv_input);
    size_t i = 0;

    for (i = 0; i < len; ++i) {
        ((char*)cpv_input)[i] = (char)toupper(((char*)cpv_input)[i]);
    }
}
void test_algo_for_each__cstr(void** state)
{
    list_t* plist = create_list(char*);
    iterator_t it;
    int i = 0;
    const char* array[] = {"windows", "linux", "libcstl"};
    const char* result[] = {"WINDOWS", "LINUX", "LIBCSTL"};

    list_init_copy_array(plist, array, 3);

    algo_for_each(list_begin(plist), list_end(plist), _fun_test_algo_for_each__cstr);
    for (i = 0, it = list_begin(plist);
         i < 3 && !iterator_equal(it, list_end(plist));
         ++i, it = iterator_next(it)) {
        assert_true(strcmp(result[i], (char*)iterator_get_pointer(it)) == 0);
    }

    list_destroy(plist);
}

static void _fun_test_algo_for_each__cstl_builtin(const void* cpv_input, void* pv_output)
{
    map_clear((map_t*)cpv_input);
}
void test_algo_for_each__cstl_builtin(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);
    map_t* pmap = create_map(int, int);
    iterator_t it;
    int i = 0;

    deque_init(pdeq);
    map_init(pmap);

    for (i = 0; i < 10; ++i) {
        *(int*)map_at(pmap, i) = i;
        deque_push_back(pdeq, pmap);
    }
    algo_for_each(deque_begin(pdeq), deque_end(pdeq), _fun_test_algo_for_each__cstl_builtin);
    for (it = deque_begin(pdeq);
         !iterator_equal(it, deque_end(pdeq));
         it = iterator_next(it)) {
        assert_true(map_empty((map_t*)iterator_get_pointer(it)));
    }

    map_destroy(pmap);
    deque_destroy(pdeq);
}

typedef struct _tag_test_algo_for_each__user_define {
    int a;
    int b;
}_test_algo_for_each__user_define_t;
static void _fun_test_algo_for_each__user_define(const void* cpv_input, void* pv_output)
{
    ((_test_algo_for_each__user_define_t*)cpv_input)->a += 100;
    ((_test_algo_for_each__user_define_t*)cpv_input)->b -= 100;
}
void test_algo_for_each__user_define(void** state)
{
    vector_t* pvec = NULL;
    _test_algo_for_each__user_define_t t_elem;
    int i = 0;

    type_register(_test_algo_for_each__user_define_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(_test_algo_for_each__user_define_t);
    vector_init(pvec);

    for (i = 0; i < 10; ++i) {
        t_elem.a = t_elem.b = i;
        vector_push_back(pvec, &t_elem);
    }
    algo_for_each(vector_begin(pvec), vector_end(pvec), _fun_test_algo_for_each__user_define);
    for (i = 0; i < 10; ++i) {
        assert_true(
            ((_test_algo_for_each__user_define_t*)vector_at(pvec, i))->a == i + 100 &&
            ((_test_algo_for_each__user_define_t*)vector_at(pvec, i))->b == i - 100);
    }

    vector_destroy(pvec);
}

/*
 * test algo_find_if
 */
UT_CASE_DEFINATION(algo_find_if)
void test_algo_find_if__invalid_range(void** state)
{
    slist_t* pslist = create_slist(int);
    list_t* plist = create_list(int);

    slist_init_n(pslist, 10);
    list_init_n(plist, 10);

    expect_assert_failure(algo_find_if(list_begin(plist), slist_end(pslist), NULL));

    slist_destroy(pslist);
    list_destroy(plist);
}

void test_algo_find_if__invalid_range_2(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init_n(pvec, 10);

    expect_assert_failure(algo_find_if(vector_end(pvec), vector_begin(pvec), NULL));

    vector_destroy(pvec);
}

void test_algo_find_if__empty_range(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init(plist);
    it = algo_find_if(list_begin(plist), list_end(plist), NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    list_destroy(plist);
}

void test_algo_find_if__ufun_NULL(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;
    int i = 0;

    vector_init(pvec);

    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    it = algo_find_if(vector_begin(pvec), vector_end(pvec), NULL);
    assert_true(iterator_equal(it, vector_end(pvec)));

    vector_destroy(pvec);
}

static void _test_algo_find_if__c_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 3 ? true : false;
}
void test_algo_find_if__c_builtin_found(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;
    int i = 0;

    deque_init(pdeq);

    for (i = 0; i < 10; ++i) {
        deque_push_back(pdeq, i);
    }
    it = algo_find_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_find_if__c_builtin);
    assert_true(*(int*)iterator_get_pointer(it) == 4);
    assert_true(iterator_equal(it, iterator_next_n(deque_begin(pdeq), 4)));

    deque_destroy(pdeq);
}

void test_algo_find_if__c_builtin_not_found(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init_elem(pvec, 10, 3);
    it = algo_find_if(vector_begin(pvec), vector_end(pvec), _test_algo_find_if__c_builtin);
    assert_true(iterator_equal(it, vector_end(pvec)));
    vector_destroy(pvec);
}

static void _test_algo_find_if__cstr(const void* cpv_input, void* pv_output)
{
    size_t len = strlen((char*)cpv_input);
    size_t i = 0;

    *(bool_t*)pv_output = true;
    for (i = 0; i < len; ++i) {
        if (isdigit(((char*)cpv_input)[i]) == 0) {
            *(bool_t*)pv_output = false;
            break;
        }
    }
}
void test_algo_find_if__cstr_found(void** state)
{
    list_t* plist = create_list(char*);
    iterator_t it;
    const char* array[] = {"Sina", "163", "baidu"};

    list_init_copy_array(plist, array, 3);
    it = algo_find_if(list_begin(plist), list_end(plist), _test_algo_find_if__cstr);
    assert_true(strcmp((char*)iterator_get_pointer(it), array[1]) == 0);
    assert_true(iterator_equal(it, iterator_next(list_begin(plist))));
    list_destroy(plist);
}

void test_algo_find_if__cstr_not_found(void** state)
{
    slist_t* pslist = create_slist(char*);
    iterator_t it;
    const char* array[] = {"i18n", "10gn", "haha", "qq"};

    slist_init_copy_array(pslist, array, 4);
    it = algo_find_if(slist_begin(pslist), slist_end(pslist), _test_algo_find_if__cstr);
    assert_true(iterator_equal(it, slist_end(pslist)));
    slist_destroy(pslist);
}

static void _test_algo_find_if__cstl_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = vector_size((vector_t*)cpv_input) == 3 ? true : false;
}
void test_algo_find_if__cstl_builtin_found(void** state)
{
    vector_t* pvec = create_vector(vector_t<int>);
    vector_t* pvec_elem = create_vector(int);
    iterator_t it;

    vector_init_elem(pvec_elem, 3, 100);
    vector_init_elem(pvec, 10, pvec_elem);

    it = algo_find_if(vector_begin(pvec), vector_end(pvec), _test_algo_find_if__cstl_builtin);
    assert_true(iterator_equal(it, vector_begin(pvec)));

    vector_destroy(pvec);
    vector_destroy(pvec_elem);
}

void test_algo_find_if__cstl_builtin_not_found(void** state)
{
    deque_t* pdeq = create_deque(vector_t<double>);
    iterator_t it;

    deque_init_n(pdeq, 10);
    it = algo_find_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_find_if__cstl_builtin);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

typedef struct _tag_test_algo_find_if__user_define {
    int a;
    int b;
}_test_algo_find_if__user_define_t;
static void _test_algo_find_if__user_define(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test_algo_find_if__user_define_t*)cpv_input)->a *
        ((_test_algo_find_if__user_define_t*)cpv_input)->b == 250 ?
        true : false;
}
void test_algo_find_if__user_define_found(void** state)
{
    list_t* plist = NULL;
    _test_algo_find_if__user_define_t t_elem;
    iterator_t it;
    int i = 0;

    type_register(_test_algo_find_if__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_algo_find_if__user_define_t);
    list_init(plist);

    for (i = 0; i < 10; ++i) {
        t_elem.a = i;
        t_elem.b = i * 10;
        list_push_back(plist, &t_elem);
    }
    it = algo_find_if(list_begin(plist), list_end(plist), _test_algo_find_if__user_define);
    assert_true(
        ((_test_algo_find_if__user_define_t*)iterator_get_pointer(it))->a == 5 &&
        ((_test_algo_find_if__user_define_t*)iterator_get_pointer(it))->b == 50);
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist), 5)));

    list_destroy(plist);
}

void test_algo_find_if__user_define_not_found(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_find_if__user_define_t);
    iterator_t it;
    _test_algo_find_if__user_define_t t_elem;

    t_elem.a = t_elem.b = 100;
    deque_init_elem(pdeq, 10, &t_elem);
    it = algo_find_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_find_if__user_define);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test algo_adjacent_find
 */
UT_CASE_DEFINATION(algo_adjacent_find)
void test_algo_adjacent_find__invalid_range_invalid_iter(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_last;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_last = vector_end(pvec);
    it_first._t_iteratortype = _INPUT_ITERATOR;
    it_last._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_adjacent_find(it_first, it_last));
    vector_destroy(pvec);
}

void test_algo_adjacent_find__invalid_range_not_belong_to_same_container(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init(pvec);
    list_init(plist);

    expect_assert_failure(algo_adjacent_find(vector_begin(pvec), list_end(plist)));

    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_adjacent_find__invalid_range_reverse(void** state)
{
    deque_t* pdeq = create_deque(int);
    
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_adjacent_find(deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test_algo_adjacent_find__c_builtin_found(void** state)
{
    multiset_t* pmset = create_multiset(int);
    iterator_t it;
    int i = 0;

    multiset_init(pmset);

    for (i = 0; i < 10; ++i) {
        multiset_insert(pmset, i);
        multiset_insert(pmset, i);
    }
    it = algo_adjacent_find(multiset_begin(pmset), multiset_end(pmset));
    assert_true(iterator_equal(it, multiset_begin(pmset)));

    multiset_destroy(pmset);
}

void test_algo_adjacent_find__c_builtin_not_found(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it;
    int i = 0;

    set_init(pset);

    for (i = 0; i < 10; ++i) {
        set_insert(pset, i);
    }
    it = algo_adjacent_find(set_begin(pset), set_end(pset));
    assert_true(iterator_equal(it, set_end(pset)));

    set_destroy(pset);
}

void test_algo_adjacent_find__cstr_found(void** state)
{
    list_t* plist = create_list(char*);
    const char* s_array[] = {"linux", "aix", "windows", "libcstl", "libcstl", "mac"};
    iterator_t it;

    list_init_copy_array(plist, s_array, 6);

    it = algo_adjacent_find(list_begin(plist), list_end(plist));
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist), 3)));
    assert_true(strcmp((char*)iterator_get_pointer(it), s_array[3]) == 0);
    assert_true(strcmp((char*)iterator_get_pointer(iterator_next(it)), s_array[4]) == 0);

    list_destroy(plist);
}

void test_algo_adjacent_find__cstr_not_found(void** state)
{
    hash_set_t* phset = create_hash_set(char*);
    const char* s_array[] = {"linux", "windows", "unix", "mac"};
    iterator_t it;

    hash_set_init_copy_array(phset, s_array, 4);

    it = algo_adjacent_find(hash_set_begin(phset), hash_set_end(phset));
    assert_true(iterator_equal(it, hash_set_end(phset)));

    hash_set_destroy(phset);
}

void test_algo_adjacent_find__cstl_builtin_found(void** state)
{
    vector_t* pvec = create_vector(stack_t<int>);
    stack_t* pstack = create_stack(int);
    iterator_t it;
    int i = 0;

    vector_init(pvec);
    stack_init(pstack);

    for (i = 0; i < 10; ++i) {
        stack_push(pstack, i);
        vector_push_back(pvec, pstack);
        vector_push_back(pvec, pstack);
    }
    it = algo_adjacent_find(vector_begin(pvec), vector_end(pvec));
    assert_true(iterator_equal(it, vector_begin(pvec)));

    stack_destroy(pstack);
    vector_destroy(pvec);
}

void test_algo_adjacent_find__cstl_builtin_not_found(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);
    map_t* pmap = create_map(int, int);
    iterator_t it;
    int i = 0;

    deque_init(pdeq);
    map_init(pmap);

    for (i = 0; i < 10; ++i) {
        *(int*)map_at(pmap, i) = i;
        deque_push_back(pdeq, pmap);
    }
    it = algo_adjacent_find(deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, deque_end(pdeq)));

    map_destroy(pmap);
    deque_destroy(pdeq);
}

typedef struct _tag_test_algo_adjacent_find__user_define {
    int a;
    int b;
}_test_algo_adjacent_find__user_define_t;
static void _test_algo_adjacent_find__user_define_init(const void* cpv_input, void* pv_output)
{
    if (pv_output != NULL) {
        *(bool_t*)pv_output = true;
    }
    ((_test_algo_adjacent_find__user_define_t*)cpv_input)->a = ((_test_algo_adjacent_find__user_define_t*)cpv_input)->b = 0;
}
static void _test_algo_adjacent_find__user_define_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    if (pv_output != NULL) {
        *(bool_t*)pv_output = true;
    }
    ((_test_algo_adjacent_find__user_define_t*)cpv_first)->a = ((_test_algo_adjacent_find__user_define_t*)cpv_second)->a;
    ((_test_algo_adjacent_find__user_define_t*)cpv_first)->b = ((_test_algo_adjacent_find__user_define_t*)cpv_second)->b;
}
static void _test_algo_adjacent_find__user_define_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test_algo_adjacent_find__user_define_t*)cpv_first)->a < ((_test_algo_adjacent_find__user_define_t*)cpv_second)->a &&
        ((_test_algo_adjacent_find__user_define_t*)cpv_first)->b < ((_test_algo_adjacent_find__user_define_t*)cpv_second)->b ?
        true : false;
}
static void _test_algo_adjacent_find__user_define_destroy(const void* cpv_input, void* pv_output)
{
    if (pv_output != NULL) {
        *(bool_t*)pv_output = true;
    }
    ((_test_algo_adjacent_find__user_define_t*)cpv_input)->a = ((_test_algo_adjacent_find__user_define_t*)cpv_input)->b = 0;
}
void test_algo_adjacent_find__user_define_found(void** state)
{
    list_t* plist = NULL;
    _test_algo_adjacent_find__user_define_t t_elem;
    iterator_t it;
    int i = 0;

    type_register(
        _test_algo_adjacent_find__user_define_t,
        _test_algo_adjacent_find__user_define_init,
        _test_algo_adjacent_find__user_define_copy,
        _test_algo_adjacent_find__user_define_less,
        _test_algo_adjacent_find__user_define_destroy);
    plist = create_list(_test_algo_adjacent_find__user_define_t);
    list_init(plist);

    for (i = 0; i < 10; ++i) {
        t_elem.a = t_elem.b = i;
        list_push_back(plist, &t_elem);
        list_push_back(plist, &t_elem);
    }
    it = algo_adjacent_find(list_begin(plist), list_end(plist));
    assert_true(iterator_equal(it, list_begin(plist)));

    list_destroy(plist);
}

void test_algo_adjacent_find__user_define_not_found(void** state)
{
    slist_t* pslist = create_slist(_test_algo_adjacent_find__user_define_t);
    _test_algo_adjacent_find__user_define_t t_elem;
    iterator_t it;
    int i = 0;

    slist_init(pslist);

    for (i = 0; i < 10; ++i) {
        t_elem.a = t_elem.b = i;
        slist_push_front(pslist, &t_elem);
    }
    it = algo_adjacent_find(slist_begin(pslist), slist_end(pslist));
    assert_true(iterator_equal(it, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_algo_adjacent_find__empty(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init(pvec);
    it = algo_adjacent_find(vector_begin(pvec), vector_end(pvec));
    assert_true(iterator_equal(it, vector_end(pvec)));
    vector_destroy(pvec);
}

/*
 * test algo_adjacent_find_if
 */
UT_CASE_DEFINATION(algo_adjacent_find_if)
void test_algo_adjacent_find_if__invalid_range_invalid_iter(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it_first;
    iterator_t it_last;

    vector_init_n(pvec, 10);
    it_first = vector_begin(pvec);
    it_last = vector_end(pvec);
    it_first._t_iteratortype = _INPUT_ITERATOR;
    it_last._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_adjacent_find_if(it_first, it_last, NULL));
    vector_destroy(pvec);
}

void test_algo_adjacent_find_if__invalid_range_not_belong_to_same_container(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init(plist);
    deque_init(pdeq);
    expect_assert_failure(algo_adjacent_find_if(list_begin(plist), deque_end(pdeq), NULL));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_adjacent_find_if__invalid_range_reverse(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(algo_adjacent_find_if(slist_end(pslist), slist_begin(pslist), NULL));
    slist_destroy(pslist);
}

void test_algo_adjacent_find_if__empty(void** state)
{
    set_t* pset = create_set(int);
    iterator_t it;

    set_init(pset);
    it = algo_adjacent_find_if(set_begin(pset), set_end(pset), NULL);
    assert_true(iterator_equal(it, set_end(pset)));
    set_destroy(pset);
}

void test_algo_adjacent_find_if__bfun_NULL_found(void** state)
{
    vector_t* pvec = create_vector(int);
    iterator_t it;
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
        vector_push_back(pvec, i);
    }
    it = algo_adjacent_find_if(vector_begin(pvec), vector_end(pvec), NULL);
    assert_true(iterator_equal(it, vector_begin(pvec)));
    vector_destroy(pvec);
}

void test_algo_adjacent_find_if__bfun_NULL_not_found(void** state)
{
    list_t* plist = create_list(int);
    int n_array[] = {1, 5, 9, 2, 90, 42, 1};
    iterator_t it;

    list_init_copy_array(plist, n_array, 7);
    it = algo_adjacent_find_if(list_begin(plist), list_end(plist), NULL);
    assert_true(iterator_equal(it, list_end(plist)));
    list_destroy(plist);
}

static void _test_algo_adjacent_find_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        *(int*)cpv_first > 0 && *(int*)cpv_first % 10 == 0 &&
        *(int*)cpv_second > 0 && *(int*)cpv_second % 10 == 0 ?
        true : false;
}
void test_algo_adjacent_find_if__c_builtin_found(void** state)
{
    deque_t* pdeq = create_deque(int);
    int n_array[] = {1, 8, 93, 0, 20, 100, 79};
    iterator_t it;

    deque_init_copy_array(pdeq, n_array, 7);
    it = algo_adjacent_find_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_adjacent_find_if__c_builtin);
    assert_true(iterator_equal(it, iterator_next_n(deque_begin(pdeq), 4)));
    assert_true(*(int*)iterator_get_pointer(it) == 20);
    assert_true(*(int*)iterator_get_pointer(iterator_next(it)) == 100);
    deque_destroy(pdeq);
}

void test_algo_adjacent_find_if__c_builtin_not_found(void** state)
{
    list_t* plist = create_list(int);
    int n_array[] = {1, 9, 4, 0, 20, 0, 34, 1};
    iterator_t it;

    list_init_copy_array(plist, n_array, 8);
    it = algo_adjacent_find_if(list_begin(plist), list_end(plist), _test_algo_adjacent_find_if__c_builtin);
    assert_true(iterator_equal(it, list_end(plist)));
    list_destroy(plist);
}

static void _test_algo_adjacent_find_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strlen((char*)cpv_first) * 3 == strlen((char*)cpv_second) ? true : false;
}
void test_algo_adjacent_find_if__cstr_found(void** state)
{
    slist_t* pslist = create_slist(char*);
    const char* s_array[] = {"Linux", "Mac", "Windows 7", "AIX", "FreeBSD"};
    iterator_t it;
    
    slist_init_copy_array(pslist, s_array, sizeof(s_array)/sizeof(s_array[0]));
    it = algo_adjacent_find_if(slist_begin(pslist), slist_end(pslist), _test_algo_adjacent_find_if__cstr);
    assert_true(iterator_equal(it, iterator_next(slist_begin(pslist))));
    assert_true(strcmp((char*)iterator_get_pointer(it), "Mac") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(iterator_next(it)), "Windows 7") == 0);
    slist_destroy(pslist);
}

void test_algo_adjacent_find_if__cstr_not_found(void** state)
{
    vector_t* pvec = create_vector(char*);
    const char* s_array[] = {"Fedora", "Ubuntu", "CentOS", "RHEL"};
    iterator_t it;

    vector_init_copy_array(pvec, s_array, sizeof(s_array)/sizeof(s_array[0]));
    it = algo_adjacent_find_if(vector_begin(pvec), vector_end(pvec), _test_algo_adjacent_find_if__cstr);
    assert_true(iterator_equal(it, vector_end(pvec)));
    vector_destroy(pvec);
}

static void _test_algo_adjacent_find_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = vector_size((vector_t*)cpv_first) == 2 && vector_size((vector_t*)cpv_second) == 3 ? true : false;
}
void test_algo_adjacent_find_if__cstl_builtin_found(void** state)
{
    vector_t* pvec = create_vector(vector_t<int>);
    vector_t* pvec_elem = create_vector(int);
    iterator_t it;
    int i = 0;

    vector_init(pvec);
    vector_init(pvec_elem);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec_elem, i);
        vector_push_back(pvec, pvec_elem);
    }
    it = algo_adjacent_find_if(vector_begin(pvec), vector_end(pvec), _test_algo_adjacent_find_if__cstl_builtin);
    assert_true(iterator_equal(it, iterator_next(vector_begin(pvec))));
    assert_true(vector_size((vector_t*)iterator_get_pointer(it)) == 2);
    assert_true(vector_size((vector_t*)iterator_get_pointer(iterator_next(it))) == 3);
    vector_destroy(pvec);
    vector_destroy(pvec_elem);
}

void test_algo_adjacent_find_if__cstl_builtin_not_found(void** state)
{
    list_t* plist = create_list(vector_t<int>);
    iterator_t it;

    list_init_n(plist, 10);
    it = algo_adjacent_find_if(list_begin(plist), list_end(plist), _test_algo_adjacent_find_if__cstl_builtin);
    assert_true(iterator_equal(it, list_end(plist)));
    list_destroy(plist);
}

typedef struct _tag_test_algo_adjacent_find_if__user_define {
    int a;
    int b;
}_test_algo_adjacent_find_if__user_define_t;
static void _test_algo_adjacent_find_if__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    _test_algo_adjacent_find_if__user_define_t* pt_first = (_test_algo_adjacent_find_if__user_define_t*)cpv_first;
    _test_algo_adjacent_find_if__user_define_t* pt_second = (_test_algo_adjacent_find_if__user_define_t*)cpv_second;

    *(bool_t*)pv_output = pt_first->a < pt_second->a && pt_first ->b > pt_second->b ? true : false;
}
void test_algo_adjacent_find_if__user_define_found(void** state)
{
    deque_t* pdeq = NULL;
    _test_algo_adjacent_find_if__user_define_t t_array[] = {{3, 9}, {8, 18}, {8, 0}, {10, -4}, {0, 0}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_adjacent_find_if__user_define_t, NULL, NULL, NULL, NULL);
    pdeq = create_deque(_test_algo_adjacent_find_if__user_define_t);
    deque_init(pdeq);

    for (i = 0; i < sizeof(t_array) / sizeof(t_array[0]); ++i) {
        deque_push_back(pdeq, &t_array[i]);
    }
    it = algo_adjacent_find_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_adjacent_find_if__user_define);
    assert_true(iterator_equal(it, iterator_next_n(deque_begin(pdeq), 2)));
    assert_true(
        ((_test_algo_adjacent_find_if__user_define_t*)iterator_get_pointer(it))->a == 8 &&
        ((_test_algo_adjacent_find_if__user_define_t*)iterator_get_pointer(it))->b == 0);
    assert_true(
        ((_test_algo_adjacent_find_if__user_define_t*)iterator_get_pointer(iterator_next(it)))->a == 10 &&
        ((_test_algo_adjacent_find_if__user_define_t*)iterator_get_pointer(iterator_next(it)))->b == -4);

    deque_destroy(pdeq);
}

void test_algo_adjacent_find_if__user_define_not_found(void** state)
{
    slist_t* pslist = create_slist(_test_algo_adjacent_find_if__user_define_t);
    _test_algo_adjacent_find_if__user_define_t t_elem;
    iterator_t it;
    int i = 0;

    slist_init(pslist);

    for (i = 0; i < 10; ++i) {
        t_elem.a = t_elem.b = i;
        slist_push_front(pslist, &t_elem);
    }
    it = algo_adjacent_find_if(slist_begin(pslist), slist_end(pslist), _test_algo_adjacent_find_if__user_define);
    assert_true(iterator_equal(it, slist_end(pslist)));

    slist_destroy(pslist);
}

/*
 * test algo_find_first_of
 */
UT_CASE_DEFINATION(algo_find_first_of)
void test_algo_find_first_of__invalid_first_range_not_belong_to_same(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 3);
    deque_init_n(pdeq, 3);
    expect_assert_failure(algo_find_first_of(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_find_first_of__invalid_first_range_reverse(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 2);
    expect_assert_failure(algo_find_first_of(list_end(plist), list_begin(plist), slist_begin(pslist), slist_end(pslist)));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_find_first_of__invalid_second_range_invalid_iter(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it_first2;
    iterator_t it_last2;

    vector_init_n(pvec, 10);
    list_init_n(plist, 2);
    it_first2 = list_begin(plist);
    it_last2 = list_end(plist);
    it_first2._t_iteratortype = _INPUT_ITERATOR;
    it_last2._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_find_first_of(vector_begin(pvec), vector_end(pvec), it_first2, it_last2));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_find_first_of__invalid_second_range_not_belong_to_same(void** state)
{
    deque_t* pdeq = create_deque(int);
    set_t* pset = create_set(int);
    hash_set_t* phset = create_hash_set(int);

    deque_init_n(pdeq, 10);
    set_init(pset);
    hash_set_init(phset);
    expect_assert_failure(algo_find_first_of(deque_begin(pdeq), deque_end(pdeq), set_begin(pset), hash_set_end(phset)));
    deque_destroy(pdeq);
    set_destroy(pset);
    hash_set_destroy(phset);
}

void test_algo_find_first_of__invalid_second_range_reverse(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 3);
    expect_assert_failure(algo_find_first_of(list_begin(plist), list_end(plist), slist_end(pslist), slist_begin(pslist)));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_find_first_of__first_range_empty(void** state)
{
    set_t* pset = create_set(int);
    vector_t* pvec = create_vector(int);
    iterator_t it;

    set_init(pset);
    vector_init_n(pvec, 10);
    it = algo_find_first_of(set_begin(pset), set_end(pset), vector_begin(pvec), vector_end(pvec));
    assert_true(iterator_equal(it, set_end(pset)));
    set_destroy(pset);
    vector_destroy(pvec);
}

void test_algo_find_first_of__second_range_empty(void** state)
{
    list_t* plist = create_list(int);
    multiset_t* pmset = create_multiset(int);
    iterator_t it;

    list_init_n(plist, 10);
    multiset_init(pmset);
    it = algo_find_first_of(list_begin(plist), list_end(plist), multiset_begin(pmset), multiset_end(pmset));
    assert_true(iterator_equal(it, list_end(plist)));
    list_destroy(plist);
    multiset_destroy(pmset);
}

void test_algo_find_first_of__c_builtin_found(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it;
    int an_first[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_second[] = {12, 0, 5, 99, 10};

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    it = algo_find_first_of(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist));
    assert_true(iterator_equal(it, iterator_next_n(vector_begin(pvec), 4)));
    assert_true(*(int*)iterator_get_pointer(it) == 5);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_find_first_of__c_builtin_not_found(void** state)
{
    deque_t* pdeq = create_deque(int);
    set_t* pset = create_set(int);
    iterator_t it;
    int an_first[] = {9, 23, 4, 1, 0, 11, 3, 2};
    int an_second[] = {-2, -4, -9, -111};

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    set_init_copy_array(pset, an_second, sizeof(an_second)/sizeof(an_second[0]));
    it = algo_find_first_of(deque_begin(pdeq), deque_end(pdeq), set_begin(pset), set_end(pset));
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
    set_destroy(pset);
}

void test_algo_find_first_of__cstr_found(void** state)
{
    set_t* pset = create_set(char*);
    hash_set_t* phset = create_hash_set(char*);
    const char* s_first[] = {"C", "C++", "Python", "Perl", "PHP", "Lisp", "Ruby"};
    const char* s_second[] = {"Java", "JavaScript", "Python"};
    iterator_t it;

    set_init_copy_array(pset, s_first, sizeof(s_first)/sizeof(s_first[0]));
    hash_set_init_copy_array(phset, s_second, sizeof(s_second)/sizeof(s_second[0]));
    it = algo_find_first_of(set_begin(pset), set_end(pset), hash_set_begin(phset), hash_set_end(phset));
    assert_true(strcmp((char*)iterator_get_pointer(it), "Python") == 0);
    set_destroy(pset);
    hash_set_destroy(phset);
}

void test_algo_find_first_of__cstr_not_found(void** state)
{
    multiset_t* pmset = create_multiset(char*);
    vector_t* pvec = create_vector(char*);
    iterator_t it;
    const char* s_first[] = {"C", "C++", "Python", "Perl", "PHP", "Lisp", "Ruby"};
    const char* s_second[] = {"C#", "ASP.NET", "VBA"};

    multiset_init_copy_array(pmset, s_first, sizeof(s_first)/sizeof(s_first[0]));
    vector_init_copy_array(pvec, s_second, sizeof(s_second)/sizeof(s_second[0]));
    it = algo_find_first_of(multiset_begin(pmset), multiset_end(pmset), vector_begin(pvec), vector_end(pvec));
    assert_true(iterator_equal(it, multiset_end(pmset)));
    multiset_destroy(pmset);
    vector_destroy(pvec);
}

void test_algo_find_first_of__cstl_builtin_found(void** state)
{
    list_t* plist = create_list(map_t<int, int>);
    slist_t* pslist = create_slist(map_t<int, int>);
    map_t* pmap = create_map(int, int);
    iterator_t it;
    int i = 0;

    list_init(plist);
    slist_init(pslist);
    map_init(pmap);
    for (i = 0; i < 10; ++i) {
        map_clear(pmap);
        *(int*)map_at(pmap, i) = i;
        list_push_back(plist, pmap);
    }
    for (i = -3; i < 1; ++i) {
        map_clear(pmap);
        *(int*)map_at(pmap, i) = i;
        slist_push_front(pslist, pmap);
    }
    it = algo_find_first_of(list_begin(plist), list_end(plist), slist_begin(pslist), slist_end(pslist));
    assert_true(map_size((map_t*)iterator_get_pointer(it)) == 1);
    assert_true(
        *(int*)pair_first((pair_t*)iterator_get_pointer(map_find((map_t*)iterator_get_pointer(it), 0))) == 0 &&
        *(int*)pair_second((pair_t*)iterator_get_pointer(map_find((map_t*)iterator_get_pointer(it), 0))) == 0);
    list_destroy(plist);
    slist_destroy(pslist);
    map_destroy(pmap);
}

void test_algo_find_first_of__cstl_builtin_not_found(void** state)
{
    set_t* pset1 = create_set(list_t<int>);
    set_t* pset2 = create_set(list_t<int>);
    list_t* plist = create_list(int);
    iterator_t it;
    int an_first[][3] = {{1, 2, 3}, {9, 0, -2}, {1, 3, 4}, {3, 3, 3}};
    int an_second[][3] = {{33, 33, 33}, {44, 44, 44}, {55, 55, 55}, {66, 66, 66}, {77, 77, 77}};
    int i = 0;

    set_init(pset1);
    set_init(pset2);
    list_init(plist);

    for (i = 0; i < sizeof(an_first)/sizeof(an_first[0]); ++i) {
        list_assign_array(plist, an_first[i], sizeof(an_first[i])/sizeof(an_first[i][0]));
        set_insert(pset1, plist);
    }
    for (i = 0; i < sizeof(an_second)/sizeof(an_second[0]); ++i) {
        list_assign_array(plist, an_second[i], sizeof(an_second[i])/sizeof(an_second[i][0]));
        set_insert(pset2, plist);
    }
    it = algo_find_first_of(set_begin(pset1), set_end(pset1), set_begin(pset2), set_end(pset2));
    assert_true(iterator_equal(it, set_end(pset1)));

    set_destroy(pset1);
    set_destroy(pset2);
    list_destroy(plist);
}

typedef struct _tag_test_algo_find_first_of__user_define {
    int a;
    int b;
}_test_find_first_of__user_define_t;
static void _test_find_first_of__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test_find_first_of__user_define_t*)cpv_first)->a < ((_test_find_first_of__user_define_t*)cpv_second)->a &&
        ((_test_find_first_of__user_define_t*)cpv_first)->b < ((_test_find_first_of__user_define_t*)cpv_second)->b ?
        true : false;
}
void test_algo_find_first_of__user_define_found(void** state)
{
    vector_t* pvec = NULL;
    list_t* plist = NULL;
    _test_find_first_of__user_define_t at_first[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    _test_find_first_of__user_define_t at_second[] = {{10, 10}, {9, 9}, {7, 8}};
    iterator_t it;
    int i = 0;

    type_register(_test_find_first_of__user_define_t, NULL, NULL, _test_find_first_of__user_define, NULL);
    pvec = create_vector(_test_find_first_of__user_define_t);
    plist = create_list(_test_find_first_of__user_define_t);
    vector_init(pvec);
    list_init(plist);

    for (i = 0; i < sizeof(at_first)/sizeof(at_first[0]); ++i) {
        vector_push_back(pvec, &at_first[i]);
    }
    for (i = 0; i < sizeof(at_second)/sizeof(at_second[0]); ++i) {
        list_push_back(plist, &at_second[i]);
    }
    it = algo_find_first_of(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist));
    assert_true(
        ((_test_find_first_of__user_define_t*)iterator_get_pointer(it))->a == 7 &&
        ((_test_find_first_of__user_define_t*)iterator_get_pointer(it))->b == 8);

    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_find_first_of__user_define_not_found(void** state)
{
    slist_t* pslist = create_slist(_test_find_first_of__user_define_t);
    deque_t* pdeq = create_deque(_test_find_first_of__user_define_t);
    iterator_t it;
    _test_find_first_of__user_define_t at_first[] = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
    _test_find_first_of__user_define_t at_second[] = {{11, 11}, {12, 12}, {13, 14}};
    int i = 0;

    slist_init(pslist);
    deque_init(pdeq);

    for (i = 0; i < sizeof(at_first)/sizeof(at_first[0]); ++i) {
        slist_push_front(pslist, &at_first[i]);
    }
    for (i = 0; i < sizeof(at_second)/sizeof(at_second[0]); ++i) {
        deque_push_back(pdeq, &at_second[i]);
    }
    it = algo_find_first_of(slist_begin(pslist), slist_end(pslist), deque_begin(pdeq), deque_end(pdeq));
    assert_true(iterator_equal(it, slist_end(pslist)));

    slist_destroy(pslist);
    deque_destroy(pdeq);
}

/*
 * test algo_find_first_of_if
 */
UT_CASE_DEFINATION(algo_find_first_of_if)
void test_algo_find_first_of_if__invalid_first_range_not_belong_to_same(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    set_t* pset = create_set(int);

    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    set_init(pset);
    expect_assert_failure(algo_find_first_of_if(list_begin(plist), vector_end(pvec), set_begin(pset), set_end(pset), NULL));
    list_destroy(plist);
    vector_destroy(pvec);
    set_destroy(pset);
}

void test_algo_find_first_of_if__invalid_first_range_reverse(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);

    list_init_elem(plist, 10, 100);
    vector_init_elem(pvec, 10, 100);
    expect_assert_failure(algo_find_first_of_if(list_end(plist), list_begin(plist), vector_begin(pvec), vector_end(pvec), NULL));
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_find_first_of_if__invalid_second_range_invalid_iter(void** state)
{
    set_t* pset = create_set(int);
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_first2;
    iterator_t it_last2;

    set_init(pset);
    hash_set_init(phset);
    it_first2 = hash_set_begin(phset);
    it_last2 = hash_set_end(phset);
    it_first2._t_iteratortype = _INPUT_ITERATOR;
    it_last2._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_find_first_of_if(set_begin(pset), set_end(pset), it_first2, it_last2, NULL));
    set_destroy(pset);
    hash_set_destroy(phset);
}

void test_algo_find_first_of_if__invalid_second_range_not_belong_to_same(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    slist_t* pslist = create_slist(int);

    list_init_elem(plist, 10, 100);
    vector_init_elem(pvec, 10, 100);
    slist_init_elem(pslist, 10, 100);
    expect_assert_failure(algo_find_first_of_if(list_begin(plist), list_end(plist), vector_begin(pvec), slist_end(pslist), NULL));
    list_destroy(plist);
    vector_destroy(pvec);
    slist_destroy(pslist);
}

void test_algo_find_first_of_if__invalid_second_range_reverse(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    deque_t* pdeq = create_deque(int);

    hash_set_init(phset);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_find_first_of_if(hash_set_begin(phset), hash_set_end(phset), deque_end(pdeq), deque_begin(pdeq), NULL));
    hash_set_destroy(phset);
    deque_destroy(pdeq);
}

void test_algo_find_first_of_if__first_range_empty(void** state)
{
    set_t* pset = create_set(int);
    list_t* plist = create_list(int);
    iterator_t it;

    set_init(pset);
    list_init_elem(plist, 10, 100);
    it = algo_find_first_of_if(set_begin(pset), set_end(pset), list_begin(plist), list_end(plist), NULL);
    assert_true(iterator_equal(it, set_end(pset)));
    set_destroy(pset);
    list_destroy(plist);
}

void test_algo_find_first_of_if__second_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    multiset_t* pmset = create_multiset(int);
    iterator_t it;

    deque_init_elem(pdeq, 10, 100);
    multiset_init(pmset);
    it = algo_find_first_of_if(deque_begin(pdeq), deque_end(pdeq), multiset_begin(pmset), multiset_end(pmset), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
    multiset_destroy(pmset);
}

void test_algo_find_first_of_if__bfun_NULL_found(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int an_first[] = {1, 8, 9, -3, 22, 109, 1024};
    int an_second[] = {8888, 109, 902, -3, 0, 19};
    iterator_t it;

    list_init_copy_array(plist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    vector_init_copy_array(pvec, an_second, sizeof(an_second)/sizeof(an_second[0]));
    it = algo_find_first_of_if(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec), NULL);
    assert_true(iterator_equal(it, iterator_advance(list_begin(plist), 3)));
    assert_true(*(int*)iterator_get_pointer(it) == -3);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_find_first_of_if__bfun_NULL_not_found(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_first[] = {3, 9, 90, 111, 34, 52, 1043, 2};
    int an_second[] = {-9, -3, -444, -1045};
    iterator_t it;

    deque_init_copy_array(pdeq, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    it = algo_find_first_of_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

static void _test_algo_find_first_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        *(int*)cpv_first != 0 && *(int*)cpv_second != 0 &&
        *(int*)cpv_first == *(int*)cpv_second * 10 ? true : false;
}
void test_algo_find_first_of_if__c_builtin_found(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_first[] = {3, 23, 9, 1, 23, 40, 11, 8};
    int an_second[] = {1, 2, 3, 4, 5};
    iterator_t it;

    vector_init_copy_array(pvec, an_first, sizeof(an_first)/sizeof(an_first[0]));
    list_init_copy_array(plist, an_second, sizeof(an_second)/sizeof(an_second[0]));
    it = algo_find_first_of_if(
        vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist),
        _test_algo_find_first_if__c_builtin);
    assert_true(*(int*)iterator_get_pointer(it) == 40);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_find_first_of_if__c_builtin_not_found(void** state)
{
    slist_t* pslist = create_slist(int);
    deque_t* pdeq = create_deque(int);
    int an_first[] = {1, 39, 0, 44, 560, 10, -9, 4, 2};
    int an_second[] = {3, 4, 5, 6, 8};
    iterator_t it;

    slist_init_copy_array(pslist, an_first, sizeof(an_first)/sizeof(an_first[0]));
    deque_init_copy_array(pdeq, an_second, sizeof(an_second)/sizeof(an_second[0]));
    it = algo_find_first_of_if(
        slist_begin(pslist), slist_end(pslist), deque_begin(pdeq), deque_end(pdeq),
        _test_algo_find_first_if__c_builtin);
    assert_true(iterator_equal(it, slist_end(pslist)));
    slist_destroy(pslist);
    deque_destroy(pdeq);
}

static void _test_algo_find_first_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        strncmp((char*)cpv_first, (char*)cpv_second, strlen((char*)cpv_second)) == 0 ? true : false;
}
void test_algo_find_first_of_if__cstr_found(void** state)
{
    deque_t* pdeq = create_deque(char*);
    list_t* plist = create_list(char*);
    const char* s_first[] = {"HTML", "XML", "JavaScript", "CSS", "PHP", "MySQL"};
    const char* s_second[] = {"C", "C++", "Java", "Perl", "Python"};
    iterator_t it;

    deque_init_copy_array(pdeq, s_first, sizeof(s_first)/sizeof(s_first[0]));
    list_init_copy_array(plist, s_second, sizeof(s_second)/sizeof(s_second[0]));
    it = algo_find_first_of_if(
        deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist),
        _test_algo_find_first_if__cstr);
    assert_true(strcmp((char*)iterator_get_pointer(it), "JavaScript") == 0);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_find_first_of_if__cstr_not_found(void** state)
{
    slist_t* pslist = create_slist(char*);
    deque_t* pdeq = create_deque(char*);
    const char* s_first[] = {"Fedora", "Ubuntu", "CentOS", "RHEL", "FreeBSD"};
    const char* s_second[] = {"Windows", "DOS", "OS/2"};
    iterator_t it;

    slist_init_copy_array(pslist, s_first, sizeof(s_first)/sizeof(s_first[0]));
    deque_init_copy_array(pdeq, s_second, sizeof(s_second)/sizeof(s_second[0]));
    it = algo_find_first_of_if(
        slist_begin(pslist), slist_end(pslist), deque_begin(pdeq), deque_end(pdeq),
        _test_algo_find_first_if__cstr);
    assert_true(iterator_equal(it, slist_end(pslist)));
    slist_destroy(pslist);
    deque_destroy(pdeq);
}

static void _test_algo_find_first_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    iterator_t it_first;
    iterator_t it_second;

    *(bool_t*)pv_output = true;

    if (list_size((list_t*)cpv_first) != list_size((list_t*)cpv_second)) {
        *(bool_t*)pv_output = false;
        return;
    }
    for (it_first = list_begin((list_t*)cpv_first), it_second = list_end((list_t*)cpv_second);
         !iterator_equal(it_first, list_end((list_t*)cpv_first)) && !iterator_equal(it_second, list_begin((list_t*)cpv_second));
         it_first = iterator_next(it_first), it_second = iterator_prev(it_second)) {
        if (*(int*)iterator_get_pointer(it_first) != *(int*)iterator_get_pointer(iterator_prev(it_second))) {
            *(bool_t*)pv_output = false;
            return;
        }
    }
}
void test_algo_find_first_of_if__cstl_builtin_found(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    deque_t* pdeq = create_deque(list_t<int>);
    list_t* plist = create_list(int);
    int aan_first[][3] = {{1, 2, 3}, {5, 6, 8}, {0, 9, 1}, {3, 3, 4}, {8, 21, 3}};
    int aan_second[][3] = {{3, 4, 5}, {9, 3, 4}, {1, 9, 0}, {3, 3, 3}};
    iterator_t it;
    iterator_t it_result;
    int i = 0;

    vector_init(pvec);
    deque_init(pdeq);
    list_init(plist);
    for (i = 0; i < sizeof(aan_first)/sizeof(aan_first[0]); ++i) {
        list_assign_array(plist, aan_first[i], sizeof(aan_first[i])/sizeof(aan_first[i][0]));
        vector_push_back(pvec, plist);
    }
    for (i = 0; i < sizeof(aan_second)/sizeof(aan_second[0]); ++i) {
        list_assign_array(plist, aan_second[i], sizeof(aan_second[i])/sizeof(aan_second[i][0]));
        deque_push_back(pdeq, plist);
    }
    it = algo_find_first_of_if(
        vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq),
        _test_algo_find_first_if__cstl_builtin);
    assert_true(iterator_equal(it, iterator_next_n(vector_begin(pvec), 2)));
    it_result = list_begin((list_t*)iterator_get_pointer(it));
    assert_true(*(int*)iterator_get_pointer(it_result) == 0);
    it_result = iterator_next(it_result);
    assert_true(*(int*)iterator_get_pointer(it_result) == 9);
    it_result = iterator_next(it_result);
    assert_true(*(int*)iterator_get_pointer(it_result) == 1);
    vector_destroy(pvec);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_find_first_of_if__cstl_builtin_not_found(void** state)
{
    set_t* pset = create_set(list_t<int>);
    hash_set_t* phset = create_hash_set(list_t<int>);
    list_t* plist = create_list(int);
    int aan_first[][3] = {{1, 2, 3}, {5, 6, 8}, {9, 9, 1}, {3, 3, 4}, {8, 21, 3}};
    int aan_second[][3] = {{3, 4, 5}, {9, 3, 4}, {1, 9, 0}, {3, 3, 3}};
    iterator_t it;
    int i = 0;

    set_init(pset);
    hash_set_init(phset);
    list_init(plist);
    for (i = 0; i < sizeof(aan_first)/sizeof(aan_first[0]); ++i) {
        list_assign_array(plist, aan_first[i], sizeof(aan_first[i])/sizeof(aan_first[i][0]));
        set_insert(pset, plist);
    }
    for (i = 0; i < sizeof(aan_second)/sizeof(aan_second[0]); ++i) {
        list_assign_array(plist, aan_second[i], sizeof(aan_second[i])/sizeof(aan_second[i][0]));
        hash_set_insert(phset, plist);
    }
    it = algo_find_first_of_if(
        set_begin(pset), set_end(pset), hash_set_begin(phset), hash_set_end(phset),
        _test_algo_find_first_if__cstl_builtin);
    assert_true(iterator_equal(it, set_end(pset)));
    set_destroy(pset);
    hash_set_destroy(phset);
    list_destroy(plist);
}

typedef struct _tag_test_algo_find_first_of_if__user_define {
    int a;
    int b;
}_test_algo_find_first__user_define_t;
static void _test_algo_find_first__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test_algo_find_first__user_define_t*)cpv_first)->a == ((_test_algo_find_first__user_define_t*)cpv_second)->b &&
        ((_test_algo_find_first__user_define_t*)cpv_first)->b == ((_test_algo_find_first__user_define_t*)cpv_second)->a ?
        true : false;
}
void test_algo_find_first_of_if__user_define_found(void** state)
{
    set_t* pset = NULL;
    list_t* plist = NULL;
    _test_algo_find_first__user_define_t at_first[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_find_first__user_define_t at_second[] = {{3, 3}, {4, 5}, {8, 7}, {2, 2}};
    iterator_t it;
    int i = 0;

    type_register(_test_algo_find_first__user_define_t, NULL, NULL, NULL, NULL);
    pset = create_set(_test_algo_find_first__user_define_t);
    plist = create_list(_test_algo_find_first__user_define_t);
    set_init(pset);
    list_init(plist);
    for (i = 0; i < sizeof(at_first)/sizeof(at_first[0]); ++i) {
        set_insert(pset, &at_first[i]);
    }
    for (i = 0; i < sizeof(at_second)/sizeof(at_second[0]); ++i) {
        list_push_back(plist, &at_second[i]);
    }
    it = algo_find_first_of_if(
        set_begin(pset), set_end(pset), list_begin(plist), list_end(plist),
        _test_algo_find_first__user_define);
    assert_true(
        ((_test_algo_find_first__user_define_t*)iterator_get_pointer(it))->a == 7 &&
        ((_test_algo_find_first__user_define_t*)iterator_get_pointer(it))->b == 8);
    set_destroy(pset);
    list_destroy(plist);
}

void test_algo_find_first_of_if__user_define_not_found(void** state)
{
    vector_t* pvec = create_vector(_test_algo_find_first__user_define_t);
    deque_t* pdeq = create_deque(_test_algo_find_first__user_define_t);
    _test_algo_find_first__user_define_t at_first[] = {{33, 33}, {44, 22}, {49, 4}, {100, 2}, {4, 5}};
    _test_algo_find_first__user_define_t at_second[] = {{88, 90}, {100, 2}};
    iterator_t it;
    int i = 0;

    vector_init(pvec);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_first)/sizeof(at_first[0]); ++i) {
        vector_push_back(pvec, &at_first[i]);
    }
    for (i = 0; i < sizeof(at_second)/sizeof(at_second[0]); ++i) {
        deque_push_back(pdeq, &at_second[i]);
    }
    it = algo_find_first_of_if(
        vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), deque_end(pdeq),
        _test_algo_find_first__user_define);
    assert_true(iterator_equal(it, vector_end(pvec)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_find_first_of_if__not_same_type(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(deque_t<int>);

    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_find_first_of_if(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec), NULL));
    list_destroy(plist);
    vector_destroy(pvec);
}

/*
 * test algo_count_if
 */
UT_CASE_DEFINATION(algo_count_if)
void test_algo_count_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_count_if(vector_begin(pvec), list_end(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_count_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_count_if(deque_end(pdeq), deque_begin(pdeq), NULL));
    deque_destroy(pdeq);
}

void test_algo_count_if__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(algo_count_if(slist_begin(pslist), slist_end(pslist), NULL) == 0);
    slist_destroy(pslist);
}

void test_algo_count_if__ufun_NULL(void** state)
{
    set_t* pset = create_set(int);
    int an_array[] = {1, 4, 0, -4, 56, 1, 44};

    set_init_copy_array(pset, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_count_if(set_begin(pset), set_end(pset), NULL) == 0);
    set_destroy(pset);
}

static void _test_algo_count_if__c_builtin(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 2 == 0 ? true : false;
}
void test_algo_count_if__c_builtin_0(void** state)
{
    multiset_t* pmset = create_multiset(int);
    int an_array[] = {11, 9, 67, 881, -97, -13, -1, 3, 3};

    multiset_init_copy_array(pmset, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_count_if(multiset_begin(pmset), multiset_end(pmset), _test_algo_count_if__c_builtin) == 0);
    multiset_destroy(pmset);
}

void test_algo_count_if__c_builtin_1(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    int an_array[] = {11, 9, 67, 888, -97, -13, -1, 3, 3};

    hash_set_init_copy_array(phset, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_count_if(hash_set_begin(phset), hash_set_end(phset), _test_algo_count_if__c_builtin) == 1);
    hash_set_destroy(phset);
}

void test_algo_count_if__c_builtin_n(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    int an_array[] = {0, 9, 66, 888, -97, -16, -8, 3, 3};

    hash_multiset_init_copy_array(phmset, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(algo_count_if(hash_multiset_begin(phmset), hash_multiset_end(phmset), _test_algo_count_if__c_builtin) == 5);
    hash_multiset_destroy(phmset);
}

static void _test_algo_count_if__cstr(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = strncmp((char*)cpv_input, "Windows", 7) == 0 ? true : false;
}
void test_algo_count_if__cstr_0(void** state)
{
    vector_t* pvec = create_vector(char*);
    const char* as_array[] = {"Linux", "MSDOS", "AIX", "FreeBSD", "Mac"};

    vector_init_copy_array(pvec, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(algo_count_if(vector_begin(pvec), vector_end(pvec), _test_algo_count_if__cstr) == 0);
    vector_destroy(pvec);
}

void test_algo_count_if__cstr_1(void** state)
{
    list_t* plist = create_list(char*);
    const char* as_array[] = {"Linux", "MSDOS", "AIX", "FreeBSD", "Mac", "Windows 7"};

    list_init_copy_array(plist, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(algo_count_if(list_begin(plist), list_end(plist), _test_algo_count_if__cstr) == 1);
    list_destroy(plist);
}

void test_algo_count_if__cstr_n(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"Windows", "Windows 3.1", "Windows 95", "Windows 98", "Windows NT", "Windows ME", "Windows 2000"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(algo_count_if(deque_begin(pdeq), deque_end(pdeq), _test_algo_count_if__cstr) == sizeof(as_array)/sizeof(as_array[0]));
    deque_destroy(pdeq);
}

static void _test_algo_count_if__cstl_builtin(const void* cpv_input, void* pv_output)
{
    vector_t* pvec = (vector_t*)cpv_input;
    size_t i = 0;
    int n_count = 0;

    for (i = 0; i < vector_size(pvec); ++i) {
        n_count += *(int*)vector_at(pvec, i);
    }

    *(bool_t*)pv_output = n_count > 100 ? true : false;
}
void test_algo_count_if__cstl_builtin_0(void** state)
{
    slist_t* pslist = create_slist(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][3] = {{3, 9, 0}, {2, 12, 9}, {22, 0, -10}, {3, -9, -100}, {88, 1, 1}, {4, 2, 4}};
    int i = 0;

    vector_init(pvec);
    slist_init(pslist);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        slist_push_front(pslist, pvec);
    }
    assert_true(algo_count_if(slist_begin(pslist), slist_end(pslist), _test_algo_count_if__cstl_builtin) == 0);
    vector_destroy(pvec);
    slist_destroy(pslist);
}

void test_algo_count_if__cstl_builtin_1(void** state)
{
    set_t* pset = create_set(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][3] = {{3, 9, 0}, {2, 12, 9}, {22, 80, 10}, {3, -9, -100}, {88, 1, 1}, {4, 2, 4}};
    int i = 0;

    vector_init(pvec);
    set_init(pset);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        set_insert(pset, pvec);
    }
    assert_true(algo_count_if(set_begin(pset), set_end(pset), _test_algo_count_if__cstl_builtin) == 1);
    vector_destroy(pvec);
    set_destroy(pset);
}

void test_algo_count_if__cstl_builtin_n(void** state)
{
    multiset_t* pmset = create_multiset(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array[][3] = {{3, 9, 0}, {2, 12, 9}, {22, 80, 10}, {3, 9, 100}, {88, 9, 9}, {4, 2, 4}};
    int i = 0;

    vector_init(pvec);
    multiset_init(pmset);
    for (i = 0; i < sizeof(aan_array)/sizeof(aan_array[0]); ++i) {
        vector_assign_array(pvec, aan_array[i], sizeof(aan_array[i])/sizeof(aan_array[i][0]));
        multiset_insert(pmset, pvec);
    }
    assert_true(algo_count_if(multiset_begin(pmset), multiset_end(pmset), _test_algo_count_if__cstl_builtin) == 3);
    vector_destroy(pvec);
    multiset_destroy(pmset);
}

typedef struct _tag_test_algo_count_if__user_define {
    int a;
    int b;
    int c;
}_test_algo_count_if__user_define_t;
static void _test_algo_count_if__user_define(const void* cpv_input, void* pv_output)
{
    _test_algo_count_if__user_define_t* pt_elem = (_test_algo_count_if__user_define_t*)cpv_input;

    *(bool_t*)pv_output = pt_elem->c == pt_elem->a + pt_elem->b ? true : false;
}
void test_algo_count_if__user_define_0(void** state)
{
    hash_set_t* phset = NULL;
    _test_algo_count_if__user_define_t at_array[] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11}, {0, 1, 2}, {3, 4, 5}};
    int i = 0;

    type_register(_test_algo_count_if__user_define_t, NULL, NULL, NULL, NULL);
    phset = create_hash_set(_test_algo_count_if__user_define_t);
    hash_set_init(phset);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        hash_set_insert(phset, &at_array[i]);
    }
    assert_true(algo_count_if(hash_set_begin(phset), hash_set_end(phset), _test_algo_count_if__user_define) == 0);
    hash_set_destroy(phset);
}

void test_algo_count_if__user_define_1(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(_test_algo_count_if__user_define_t);
    _test_algo_count_if__user_define_t at_array[] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11}, {1, 1, 2}, {3, 4, 5}};
    int i = 0;

    hash_multiset_init(phmset);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        hash_multiset_insert(phmset, &at_array[i]);
    }
    assert_true(algo_count_if(hash_multiset_begin(phmset), hash_multiset_end(phmset), _test_algo_count_if__user_define) == 1);
    hash_multiset_destroy(phmset);
}

void test_algo_count_if__user_define_n(void** state)
{
    vector_t* pvec = create_vector(_test_algo_count_if__user_define_t);
    _test_algo_count_if__user_define_t at_array[] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 19}, {1, 1, 2}, {3, 4, 5}};
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < sizeof(at_array)/sizeof(at_array[0]); ++i) {
        vector_push_back(pvec, &at_array[i]);
    }
    assert_true(algo_count_if(vector_begin(pvec), vector_end(pvec), _test_algo_count_if__user_define) == 2);
    vector_destroy(pvec);
}

/*
 * test algo_mismatch
 */
UT_CASE_DEFINATION(algo_mismatch)
void test_algo_mismatch__invalid_first_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_mismatch(list_begin(plist), deque_end(pdeq), slist_begin(pslist)));
    list_destroy(plist);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_mismatch__invalid_first_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_mismatch(vector_end(pvec), vector_begin(pvec), deque_begin(pdeq)));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_mismatch__invalid_range_not_same_type(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(long);

    set_init(pset);
    multiset_init(pmset);
    expect_assert_failure(algo_mismatch(set_begin(pset), set_end(pset), multiset_begin(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_mismatch__first_range_empty(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_multiset_t* phmset = create_hash_multiset(int);
    range_t r_result;

    hash_set_init(phset);
    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 100);
    r_result = algo_mismatch(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset));
    assert_true(iterator_equal(r_result.it_begin, hash_set_end(phset)));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

void test_algo_mismatch__c_builtin_mismatch(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int an_array2[] = {1, 2, -3, 4, 5, 6, -7, 8};
    range_t r_result;

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    r_result = algo_mismatch(vector_begin(pvec), vector_end(pvec), list_begin(plist));
    assert_true(iterator_equal(r_result.it_begin, iterator_next_n(vector_begin(pvec), 2)));
    assert_true(*(int*)iterator_get_pointer(r_result.it_begin) == 3);
    assert_true(iterator_equal(r_result.it_end, iterator_advance(list_begin(plist), 2)));
    assert_true(*(int*)iterator_get_pointer(r_result.it_end) == -3);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_mismatch__c_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int an_array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    slist_init_copy_array(pslist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    r_result = algo_mismatch(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist));
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_mismatch__cstr_mismatch(void** state)
{
    set_t* pset = create_set(char*);
    multiset_t* pmset = create_multiset(char*);
    const char* as_array1[] = {"C", "C++", "PHP", "Perl", "XML"};
    const char* as_array2[] = {"C", "C++", "PHP", "Python", "XML"};
    range_t r_result;

    set_init_copy_array(pset, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    multiset_init_copy_array(pmset, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    r_result = algo_mismatch(set_begin(pset), set_end(pset), multiset_begin(pmset));
    assert_true(strcmp((char*)iterator_get_pointer(r_result.it_begin), "Perl") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(r_result.it_end), "Python") == 0);
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_mismatch__cstr_match(void** state)
{
    hash_set_t* phset = create_hash_set(char*);
    hash_multiset_t* phmset = create_hash_multiset(char*);
    const char* as_array[] = {"HTML", "XML", "JavaScript", "CSS", "PHP", "CGI"};
    range_t r_result;

    hash_set_init_copy_array(phset, as_array, sizeof(as_array)/sizeof(as_array[0]));
    hash_multiset_init_copy_array(phmset, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = algo_mismatch(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset));
    assert_true(iterator_equal(r_result.it_begin, hash_set_end(phset)));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

void test_algo_mismatch__cstl_builtin_mismatch(void** state)
{
    vector_t* pvec = create_vector(deque_t<int>);
    list_t* plist = create_list(deque_t<int>);
    deque_t* pdeq = create_deque(int);
    int aan_array1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 0, 0}, {-1, -2, -3}};
    int aan_array2[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {9, 9, 9}, {1, 2, 1}, {0, 0, 0}, {-1, -2, -3}};
    int i = 0;
    range_t r_result;

    vector_init(pvec);
    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        deque_assign_array(pdeq, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        vector_push_back(pvec, pdeq);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        deque_assign_array(pdeq, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        list_push_back(plist, pdeq);
    }
    r_result = algo_mismatch(vector_begin(pvec), vector_end(pvec), list_begin(plist));
    assert_true(
        *(int*)deque_at((deque_t*)iterator_get_pointer(r_result.it_begin), 0) == 0 &&
        *(int*)deque_at((deque_t*)iterator_get_pointer(r_result.it_begin), 1) == 0 &&
        *(int*)deque_at((deque_t*)iterator_get_pointer(r_result.it_begin), 2) == 0);
    assert_true(
        *(int*)deque_at((deque_t*)iterator_get_pointer(r_result.it_end), 0) == 9 &&
        *(int*)deque_at((deque_t*)iterator_get_pointer(r_result.it_end), 1) == 9 &&
        *(int*)deque_at((deque_t*)iterator_get_pointer(r_result.it_end), 2) == 9);
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_mismatch__cstl_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);
    slist_t* pslist = create_slist(list_t<int>);
    list_t* plist = create_list(int);
    int aan_array1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {9, 9, 9}, {1, 2, 1}};
    int aan_array2[][3] = {{-1, -2, -3}, {0, 0, 0}, {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {9, 9, 9}, {1, 2, 1}};
    int i = 0;
    range_t r_result;

    deque_init(pdeq);
    slist_init(pslist);
    list_init(plist);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        list_assign_array(plist, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        deque_push_front(pdeq, plist);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        list_assign_array(plist, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        slist_push_front(pslist, plist);
    }
    r_result = algo_mismatch(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist));
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
    list_destroy(plist);
}

typedef struct _tag_test_algo_mismatch__user_define {
    int a;
    int b;
}_test_algo_mismatch__user_define_t;
static void _test_algo_mismatch__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_mismatch__user_define_t)) < 0 ? true : false;
}
void test_algo_mismatch__user_define_mismatch(void** state)
{
    vector_t* pvec = NULL;
    list_t* plist = NULL;
    _test_algo_mismatch__user_define_t at_array1[] = {{9, 2}, {2, 4}, {4, 0}, {0, 1}, {1, 7}};
    _test_algo_mismatch__user_define_t at_array2[] = {{9, 2}, {2, 4}, {4, 0}, {0, 0}, {1, 7}};
    int i = 0;
    range_t r_result;

    type_register(_test_algo_mismatch__user_define_t, NULL, NULL, _test_algo_mismatch__user_define, NULL);
    pvec = create_vector(_test_algo_mismatch__user_define_t);
    plist = create_list(_test_algo_mismatch__user_define_t);
    vector_init(pvec);
    list_init(plist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        vector_push_back(pvec, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        list_push_back(plist, &at_array2[i]);
    }
    r_result = algo_mismatch(vector_begin(pvec), vector_end(pvec), list_begin(plist));
    assert_true(
        ((_test_algo_mismatch__user_define_t*)iterator_get_pointer(r_result.it_begin))->a == 0 &&
        ((_test_algo_mismatch__user_define_t*)iterator_get_pointer(r_result.it_begin))->b == 1);
    assert_true(
        ((_test_algo_mismatch__user_define_t*)iterator_get_pointer(r_result.it_end))->a == 0 &&
        ((_test_algo_mismatch__user_define_t*)iterator_get_pointer(r_result.it_end))->b == 0);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_mismatch__user_define_match(void** state)
{
    vector_t* pvec = create_vector(_test_algo_mismatch__user_define_t);
    list_t* plist = create_list(_test_algo_mismatch__user_define_t);
    _test_algo_mismatch__user_define_t at_array1[] = {{9, 2}, {2, 4}, {4, 0}, {0, 1}, {1, 7}};
    _test_algo_mismatch__user_define_t at_array2[] = {{9, 2}, {2, 4}, {4, 0}, {0, 1}, {1, 7}};
    int i = 0;
    range_t r_result;

    vector_init(pvec);
    list_init(plist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        vector_push_back(pvec, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        list_push_back(plist, &at_array2[i]);
    }
    r_result = algo_mismatch(vector_begin(pvec), vector_end(pvec), list_begin(plist));
    assert_true(iterator_equal(r_result.it_begin, vector_end(pvec)));
    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test algo_mismatch_if
 */
UT_CASE_DEFINATION(algo_mismatch_if)
void test_algo_mismatch_if__invalid_first_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    set_t* pset = create_set(int);

    deque_init_n(pdeq, 10);
    slist_init_n(pslist, 10);
    set_init(pset);
    expect_assert_failure(algo_mismatch_if(deque_begin(pdeq), slist_begin(pslist), set_begin(pset), NULL));
    deque_destroy(pdeq);
    slist_destroy(pslist);
    set_destroy(pset);
}

void test_algo_mismatch_if__invalid_first_range2(void** state)
{
    vector_t* pvec = create_vector(int);
    multiset_t* pmset = create_multiset(int);

    vector_init_n(pvec, 10);
    multiset_init(pmset);
    expect_assert_failure(algo_mismatch_if(vector_end(pvec), vector_begin(pvec), multiset_begin(pmset), NULL));
    vector_destroy(pvec);
    multiset_destroy(pmset);
}

void test_algo_mismatch_if__invalid_range_not_same_type(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_multiset_t* phmset = create_hash_multiset(char*);

    hash_set_init(phset);
    hash_multiset_init(phmset);
    expect_assert_failure(algo_mismatch_if(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset), NULL));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

void test_algo_mismatch_if__first_range_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    range_t r_result;

    vector_init(pvec);
    list_init_n(plist, 10);
    r_result = algo_mismatch_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), NULL);
    assert_true(iterator_equal(r_result.it_begin, vector_end(pvec)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_mismatch_if__bfun_NULL_mismatch(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int an_array2[] = {1, 2, 3, 4, 55, 6, 77, 88, 99, 0, 1, 2, 3};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    slist_init_copy_array(pslist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    r_result = algo_mismatch_if(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), NULL);
    assert_true(*(int*)iterator_get_pointer(r_result.it_begin) == 5);
    assert_true(*(int*)iterator_get_pointer(r_result.it_end) == 55);
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_mismatch_if__bfun_NULL_match(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int i = 0;
    range_t r_result;

    set_init(pset);
    multiset_init(pmset);
    for (i = 0; i < sizeof(an_array1)/sizeof(an_array1[0]); ++i) {
        set_insert(pset, an_array1[i]);
    }
    for (i = 0; i < sizeof(an_array2)/sizeof(an_array2[0]); ++i) {
        multiset_insert(pmset, an_array2[i]);
    }
    r_result = algo_mismatch_if(set_begin(pset), set_end(pset), multiset_begin(pmset), NULL);
    assert_true(iterator_equal(r_result.it_begin, set_end(pset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

static void _test_algo_mismatch_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = (*(int*)cpv_first - *(int*)cpv_second) % 10 == 0 ? true : false;
}
void test_algo_mismatch_if__c_builtin_mismatch(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array1[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int an_array2[] = {1, 2, 3, 41, 5, 6, 7, 8, 9};
    range_t r_result;

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    r_result = algo_mismatch_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), _test_algo_mismatch_if__c_builtin);
    assert_true(*(int*)iterator_get_pointer(r_result.it_begin) == 44);
    assert_true(*(int*)iterator_get_pointer(r_result.it_end) == 41);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_mismatch_if__c_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int an_array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    slist_init_copy_array(pslist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    r_result = algo_mismatch_if(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), _test_algo_mismatch_if__c_builtin);
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

static void _test_algo_mismatch_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output =
        strncmp((char*)cpv_first, (char*)cpv_second,
            strlen((char*)cpv_first) < strlen((char*)cpv_second) ? strlen((char*)cpv_first) : strlen((char*)cpv_second)) == 0 ?
        true : false;
}
void test_algo_mismatch_if__cstr_mismatch(void** state)
{
    vector_t* pvec = create_vector(char*);
    list_t* plist = create_list(char*);
    const char* as_array1[] = {"Windows", "Windows 7", "Windows vista", "Windows XP", "Windows 2000"};
    const char* as_array2[] = {"Windows 98", "Windows", "Windows ME", "Windows XP Professional", "Windows 2000 Server"};
    range_t r_result;

    vector_init_copy_array(pvec, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    list_init_copy_array(plist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    r_result = algo_mismatch_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), _test_algo_mismatch_if__cstr);
    assert_true(strcmp((char*)iterator_get_pointer(r_result.it_begin), "Windows vista") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(r_result.it_end), "Windows ME") == 0);
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_mismatch_if__cstr_match(void** state)
{
    deque_t* pdeq = create_deque(char*);
    list_t* plist = create_list(char*);
    const char* as_array1[] = {"Ubuntu-12.04-i386", "Redhat", "Fedora17", "FreeBSD", "CentOS x86_64"};
    const char* as_array2[] = {"Ubuntu-12.04", "Redhat Enterprise Linux", "Fedora", "FreeBSD", "CentOS"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    list_init_copy_array(plist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    r_result = algo_mismatch_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), _test_algo_mismatch_if__cstr);
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

static void _test_algo_mismatch_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    size_t i = 0;

    *(bool_t*)pv_output = true;
    if (vector_size((vector_t*)cpv_first) != vector_size((vector_t*)cpv_second)) {
        *(bool_t*)pv_output = false;
        return;
    }
    for (i = 0; i < vector_size((vector_t*)cpv_first); ++i) {
        if (*(int*)vector_at((vector_t*)cpv_first, i) - *(int*)vector_at((vector_t*)cpv_second, i) != 10) {
            *(bool_t*)pv_output = false;
            return;
        }
    }
}
void test_algo_mismatch_if__cstl_builtin_mismatch(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    list_t* plist = create_list(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array1[][3] = {{10, 11, 12}, {20, 21, 22}, {30, 31, 32}, {33, 34, 35}, {36, 37, 38}};
    int aan_array2[][3] = {{0, 1, 2}, {10, 11, 12}, {30, 21, 22}, {23, 24, 25}, {26, 27, 28}, {1, 2, 3}};
    range_t r_result;
    size_t i = 0;

    vector_init(pvec);
    deque_init(pdeq);
    list_init(plist);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        vector_assign_array(pvec, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        deque_push_back(pdeq, pvec);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        vector_assign_array(pvec, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        list_push_back(plist, pvec);
    }
    r_result = algo_mismatch_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), _test_algo_mismatch_if__cstl_builtin);
    assert_true(
        *(int*)vector_at((vector_t*)iterator_get_pointer(r_result.it_begin), 0) == 30 &&
        *(int*)vector_at((vector_t*)iterator_get_pointer(r_result.it_begin), 1) == 31 &&
        *(int*)vector_at((vector_t*)iterator_get_pointer(r_result.it_begin), 2) == 32);
    assert_true(
        *(int*)vector_at((vector_t*)iterator_get_pointer(r_result.it_end), 0) == 30 &&
        *(int*)vector_at((vector_t*)iterator_get_pointer(r_result.it_end), 1) == 21 &&
        *(int*)vector_at((vector_t*)iterator_get_pointer(r_result.it_end), 2) == 22);
    vector_destroy(pvec);
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_mismatch_if__cstl_builtin_match(void** state)
{
    set_t* pset = create_set(vector_t<int>);
    multiset_t* pmset = create_multiset(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array1[][3] = {{10, 11, 12}, {20, 21, 22}, {30, 31, 32}, {33, 34, 35}, {36, 37, 38}};
    int aan_array2[][3] = {{0, 1, 2}, {10, 11, 12}, {20, 21, 22}, {23, 24, 25}, {26, 27, 28}, {100, 200, 300}};
    range_t r_result;
    size_t i = 0;

    set_init(pset);
    multiset_init(pmset);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        vector_assign_array(pvec, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        set_insert(pset, pvec);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        vector_assign_array(pvec, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        multiset_insert(pmset, pvec);
    }
    r_result = algo_mismatch_if(set_begin(pset), set_end(pset), multiset_begin(pmset), _test_algo_mismatch_if__cstl_builtin);
    assert_true(iterator_equal(r_result.it_begin, set_end(pset)));
    set_destroy(pset);
    multiset_destroy(pmset);
    vector_destroy(pvec);
}

typedef struct _tag_test_algo_mismatch_if__user_define {
    int a;
    int b;
} _test_algo_mismatch_if__user_define_t;
static void _test_algo_mismatch_if__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    _test_algo_mismatch_if__user_define_t* pt_first = (_test_algo_mismatch_if__user_define_t*)cpv_first;
    _test_algo_mismatch_if__user_define_t* pt_second = (_test_algo_mismatch_if__user_define_t*)cpv_second;

    *(bool_t*)pv_output = pt_first->a - pt_second->a > pt_first->b - pt_second->b ? true : false;
}
void test_algo_mismatch_if__user_define_mismatch(void** state)
{
    list_t* plist = NULL;
    deque_t* pdeq = NULL;
    _test_algo_mismatch_if__user_define_t at_array1[] = {{12, 21}, {90, 11}, {43, 27}, {88, 1}, {14, 33}};
    _test_algo_mismatch_if__user_define_t at_array2[] = {{9, 50}, {22, 11}, {-3, 35}, {102, 1}, {10, 32}, {11, 3}};
    range_t r_result;
    int i = 0;

    type_register(_test_algo_mismatch_if__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_algo_mismatch_if__user_define_t);
    pdeq = create_deque(_test_algo_mismatch_if__user_define_t);
    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        list_push_back(plist, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    r_result = algo_mismatch_if(list_begin(plist), list_end(plist), deque_begin(pdeq), _test_algo_mismatch_if__user_define);
    assert_true(
        ((_test_algo_mismatch_if__user_define_t*)iterator_get_pointer(r_result.it_begin))->a == 88 &&
        ((_test_algo_mismatch_if__user_define_t*)iterator_get_pointer(r_result.it_begin))->b == 1);
    assert_true(
        ((_test_algo_mismatch_if__user_define_t*)iterator_get_pointer(r_result.it_end))->a == 102 &&
        ((_test_algo_mismatch_if__user_define_t*)iterator_get_pointer(r_result.it_end))->b == 1);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_mismatch_if__user_define_match(void** state)
{
    list_t* plist = NULL;
    deque_t* pdeq = NULL;
    _test_algo_mismatch_if__user_define_t at_array1[] = {{12, 21}, {90, 11}, {43, 27}, {88, 1}, {14, 33}};
    _test_algo_mismatch_if__user_define_t at_array2[] = {{9, 50}, {22, 11}, {-3, 35}, {10, 1}, {10, 32}, {11, 3}};
    range_t r_result;
    int i = 0;

    type_register(_test_algo_mismatch_if__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_algo_mismatch_if__user_define_t);
    pdeq = create_deque(_test_algo_mismatch_if__user_define_t);
    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        list_push_back(plist, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    r_result = algo_mismatch_if(list_begin(plist), list_end(plist), deque_begin(pdeq), _test_algo_mismatch_if__user_define);
    assert_true(iterator_equal(r_result.it_begin, list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_equal
 */
UT_CASE_DEFINATION(algo_equal)
void test_algo_equal__invalid_first_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_equal(list_begin(plist), deque_begin(pdeq), vector_begin(pvec)));
    list_destroy(plist);
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_equal__invalid_first_range2(void** state)
{
    set_t* pset = create_set(int);
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    set_init(pset);
    expect_assert_failure(algo_equal(slist_end(pslist), slist_begin(pslist), set_begin(pset)));
    slist_destroy(pslist);
    set_destroy(pset);
}

void test_algo_equal__invalid_range_not_same_type(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(vector_t<int>);

    set_init(pset);
    multiset_init(pmset);
    expect_assert_failure(algo_equal(set_begin(pset), set_end(pset), multiset_begin(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_equal__first_range_empty(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_multiset_t* phmset = create_hash_multiset(int);

    hash_set_init(phset);
    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, 10);
    assert_true(algo_equal(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset)));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

void test_algo_equal__c_builtin_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_equal__c_builtin_unequal(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {1, 1, 1, 1, 1, 1, 1};
    int an_array2[] = {1, 1, 1, 2, 1, 1, 1};

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    slist_init_copy_array(pslist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_false(algo_equal(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_equal__cstr_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    list_t* plist = create_list(char*);
    const char* as_array1[] = {"AAA", "BBB", "CCC", "DDD", "EEE"};
    const char* as_array2[] = {"AAA", "BBB", "CCC", "DDD", "EEE"};

    deque_init_copy_array(pdeq, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    list_init_copy_array(plist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_equal__cstr_unequal(void** state)
{
    vector_t* pvec = create_vector(char*);
    slist_t* pslist = create_slist(char*);
    const char* as_array1[] = {"abc", "def", "hij", "klm", "nop", "qrs"};
    const char* as_array2[] = {"abc", "def", "hiJ", "klm", "nop", "qrs"};

    vector_init_copy_array(pvec, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    slist_init_copy_array(pslist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_false(algo_equal(vector_begin(pvec), vector_end(pvec), slist_begin(pslist)));
    vector_destroy(pvec);
    slist_destroy(pslist);
}

void test_algo_equal__cstl_builtin_equal(void** state)
{
    set_t* pset = create_set(list_t<int>);
    multiset_t* pmset = create_multiset(list_t<int>);
    list_t* plist = create_list(int);
    int aan_array1[][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}, {5, 5, 5}};
    int aan_array2[][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}, {5, 5, 5}};
    int i = 0;

    set_init(pset);
    multiset_init(pmset);
    list_init(plist);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        list_assign_array(plist, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        set_insert(pset, plist);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        list_assign_array(plist, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        multiset_insert(pmset, plist);
    }
    assert_true(algo_equal(set_begin(pset), set_end(pset), multiset_begin(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
    list_destroy(plist);
}

void test_algo_equal__cstl_builtin_unequal(void** state)
{
    set_t* pset = create_set(list_t<int>);
    multiset_t* pmset = create_multiset(list_t<int>);
    list_t* plist = create_list(int);
    int aan_array1[][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}, {5, 5, 5}};
    int aan_array2[][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}, {5, 6, 5}};
    int i = 0;

    set_init(pset);
    multiset_init(pmset);
    list_init(plist);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        list_assign_array(plist, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        set_insert(pset, plist);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        list_assign_array(plist, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        multiset_insert(pmset, plist);
    }
    assert_false(algo_equal(set_begin(pset), set_end(pset), multiset_begin(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
    list_destroy(plist);
}

typedef struct _tag_test_algo_equal__user_define {
    int a;
    int b;
} _test_algo_equal__user_define_t;
static void _test_algo_equal__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_equal__user_define_t)) < 0 ? true : false;
}
void test_algo_equal__user_define_equal(void** state)
{
    vector_t* pvec = NULL;
    list_t* plist = NULL;
    _test_algo_equal__user_define_t at_array1[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    _test_algo_equal__user_define_t at_array2[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
    int i = 0;

    type_register(_test_algo_equal__user_define_t, NULL, NULL, _test_algo_equal__user_define, NULL);
    pvec = create_vector(_test_algo_equal__user_define_t);
    plist = create_list(_test_algo_equal__user_define_t);
    vector_init(pvec);
    list_init(plist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        vector_push_back(pvec, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        list_push_back(plist, &at_array2[i]);
    }
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_equal__user_define_unequal(void** state)
{
    vector_t* pvec = create_vector(_test_algo_equal__user_define_t);
    list_t* plist = create_list(_test_algo_equal__user_define_t);
    _test_algo_equal__user_define_t at_array1[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    _test_algo_equal__user_define_t at_array2[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 6}, {6, 6}};
    int i = 0;

    vector_init(pvec);
    list_init(plist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        vector_push_back(pvec, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        list_push_back(plist, &at_array2[i]);
    }
    assert_false(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));
    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test algo_equal_if
 */
UT_CASE_DEFINATION(algo_equal_if)
void test_algo_equal_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_equal_if(vector_begin(pvec), list_end(plist), slist_begin(pslist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_equal_if__invalid_first_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_equal_if(deque_end(pdeq), deque_begin(pdeq), list_begin(plist), NULL));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_equal_if__invalid_range_not_same_type(void** state)
{
    set_t* pset = create_set(int);
    hash_set_t* phset = create_hash_set(double);

    set_init(pset);
    hash_set_init(phset);
    expect_assert_failure(algo_equal_if(set_begin(pset), set_end(pset), hash_set_begin(phset), NULL));
    set_destroy(pset);
    hash_set_destroy(phset);
}

void test_algo_equal_if__first_range_empty(void** state)
{
    multiset_t* pmset = create_multiset(int);
    hash_set_t* phset = create_hash_set(int);

    multiset_init(pmset);
    hash_set_init(phset);
    assert_true(algo_equal_if(multiset_begin(pmset), multiset_end(pmset), hash_set_begin(phset), NULL));
    multiset_destroy(pmset);
    hash_set_destroy(phset);
}

void test_algo_equal_if__bfun_NULL_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(algo_equal_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_equal_if__bfun_NULL_unequal(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list_init_copy_array(plist, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    slist_init_copy_array(pslist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_false(algo_equal_if(list_begin(plist), list_end(plist), slist_begin(pslist), NULL));
    list_destroy(plist);
    slist_destroy(pslist);
}

static void _test_algo_equal_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) == abs(*(int*)cpv_second) ? true : false;
}
void test_algo_equal_if__c_builtin_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array1[] = {99, 20, -4, 1, 0, -324, -8};
    int an_array2[] = {-99, -20, -4, -1, 0, 324, 8};

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(algo_equal_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), _test_algo_equal_if__c_builtin));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_equal_if__c_builtin_unequal(void** state)
{
    vector_t* pvec = create_vector(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {99, 20, -4, 1, 1, -324, -8};
    int an_array2[] = {-99, -20, -4, -1, 0, 324, 8};

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    slist_init_copy_array(pslist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_false(algo_equal_if(vector_begin(pvec), vector_end(pvec), slist_begin(pslist), _test_algo_equal_if__c_builtin));
    vector_destroy(pvec);
    slist_destroy(pslist);
}

static void _test_algo_equal_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = false;
    if ((strcmp((char*)cpv_first, "Linux") == 0 &&
         (strcmp((char*)cpv_second, "Fedora") == 0 ||
          strcmp((char*)cpv_second, "Redhat") == 0 ||
          strcmp((char*)cpv_second, "Ubuntu") == 0 ||
          strcmp((char*)cpv_second, "CentOS") == 0)) ||
        (strcmp((char*)cpv_second, "Linux") == 0 &&
         (strcmp((char*)cpv_first, "Fedora") == 0 ||
          strcmp((char*)cpv_first, "Redhat") == 0 ||
          strcmp((char*)cpv_first, "Ubuntu") == 0 ||
          strcmp((char*)cpv_first, "CentOS") == 0))) {
        *(bool_t*)pv_output = true;
    }
}
void test_algo_equal_if__cstr_equal(void** state)
{
    multiset_t* pmset = create_multiset(char*);
    set_t* pset = create_set(char*);
    const char* as_array1[] = {"Linux", "Linux", "Linux", "Linux"};
    const char* as_array2[] = {"Fedora", "CentOS", "Ubuntu", "Redhat"};

    multiset_init_copy_array(pmset, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    set_init_copy_array(pset, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(algo_equal_if(multiset_begin(pmset), multiset_end(pmset), set_begin(pset), _test_algo_equal_if__cstr));
    multiset_destroy(pmset);
    set_destroy(pset);
}

void test_algo_equal_if__cstr_unequal(void** state)
{
    hash_set_t* phset = create_hash_set(char*);
    hash_multiset_t* phmset = create_hash_multiset(char*);
    const char* as_array1[] = {"Fedora", "CentOS", "Ubuntu", "Redhat"};
    const char* as_array2[] = {"Linux", "Linux", "FreeBSD", "Linux"};

    hash_set_init_copy_array(phset, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    hash_multiset_init_copy_array(phmset, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_false(algo_equal_if(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset), _test_algo_equal_if__cstr));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

static void _test_algo_equal_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = set_size((set_t*)cpv_first) == set_size((set_t*)cpv_second) ? true : false;
}
void test_algo_equal_if__cstl_builtin_equal(void** state)
{
    vector_t* pvec = create_vector(set_t<int>);
    list_t* plist = create_list(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}, {1, 2, 3}};
    int aan_array2[][3] = {{2, 4, 5}, {0, 4, 6}, {3, 1, 8}, {1, 4, 2}, {5, 0, 8}};
    int i = 0;

    vector_init(pvec);
    list_init(plist);
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
    assert_true(algo_equal_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), _test_algo_equal_if__cstl_builtin));
    vector_destroy(pvec);
    list_destroy(plist);
    set_destroy(pset);
}

void test_algo_equal_if__cstl_builtin_unequal(void** state)
{
    set_t* pset = create_set(set_t<int>);
    multiset_t* pmset = create_multiset(set_t<int>);
    set_t* pset_elem = create_set(int);
    int aan_array1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 5}};
    int aan_array2[][2] = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
    int i = 0;

    set_init(pset);
    multiset_init(pmset);
    set_init(pset_elem);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        set_clear(pset_elem);
        set_insert_array(pset_elem, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        set_insert(pset, pset_elem);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        set_clear(pset_elem);
        set_insert_array(pset_elem, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        multiset_insert(pmset, pset_elem);
    }
    assert_false(algo_equal_if(set_begin(pset), set_end(pset), multiset_begin(pmset), _test_algo_equal_if__cstl_builtin));
    set_destroy(pset);
    multiset_destroy(pmset);
    set_destroy(pset_elem);
}

typedef struct _tag_test_algo_equal_if__user_define {
    int a;
    int b;
} _test_algo_equal_if__user_define_t;
static void _test_algo_equal_if__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    _test_algo_equal_if__user_define_t* pt_first = (_test_algo_equal_if__user_define_t*)cpv_first;
    _test_algo_equal_if__user_define_t* pt_second = (_test_algo_equal_if__user_define_t*)cpv_second;

    *(bool_t*)pv_output = pt_first->a == pt_second->b && pt_first->b == pt_second->a ? true : false;
}
void test_algo_equal_if__user_define_equal(void** state)
{
    list_t* plist = NULL;
    deque_t* pdeq = NULL;
    _test_algo_equal_if__user_define_t at_array1[] = {{1, 2}, {3, 4}, {4, 5}};
    _test_algo_equal_if__user_define_t at_array2[] = {{2, 1}, {4, 3}, {5, 4}, {6, 6}};
    int i = 0;

    type_register(_test_algo_equal_if__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_algo_equal_if__user_define_t);
    pdeq = create_deque(_test_algo_equal_if__user_define_t);
    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        list_push_back(plist, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    assert_true(algo_equal_if(list_begin(plist), list_end(plist), deque_begin(pdeq), _test_algo_equal_if__user_define));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_equal_if__user_define_unequal(void** state)
{
    vector_t* pvec = create_vector(_test_algo_equal_if__user_define_t);
    deque_t* pdeq = create_deque(_test_algo_equal_if__user_define_t);
    _test_algo_equal_if__user_define_t at_array1[] = {{1, 2}, {3, 4}, {4, 5}};
    _test_algo_equal_if__user_define_t at_array2[] = {{2, 1}, {4, 4}, {5, 4}, {6, 6}};
    int i = 0;

    vector_init(pvec);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        vector_push_back(pvec, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    assert_false(algo_equal_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), _test_algo_equal_if__user_define));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

/*
 * test algo_search
 */
UT_CASE_DEFINATION(algo_search)
void test_algo_search__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_search(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_search(list_end(plist), list_begin(plist), slist_begin(pslist), slist_end(pslist)));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_search__invalid_first_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it_first1;
    iterator_t it_last1;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it_first1 = deque_begin(pdeq);
    it_last1 = deque_end(pdeq);
    it_first1._t_iteratortype = _INPUT_ITERATOR;
    it_last1._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_search(it_first1, it_last1, list_begin(plist), list_end(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_search__invalid_second_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);

    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_search(list_begin(plist), list_end(plist), deque_begin(pdeq), vector_end(pvec)));
    list_destroy(plist);
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_search__invalid_second_range2(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    expect_assert_failure(algo_search(deque_begin(pdeq), deque_end(pdeq), list_end(plist), list_begin(plist)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_search__invalid_second_range3(void** state)
{
    slist_t* pslist = create_slist(int);
    list_t* plist = create_list(int);
    iterator_t it_first2;
    iterator_t it_last2;

    slist_init_n(pslist, 10);
    list_init_n(plist, 10);
    it_first2 = list_begin(plist);
    it_last2 = list_end(plist);
    it_first2._t_iteratortype = _INPUT_ITERATOR;
    it_last2._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_search(slist_begin(pslist), slist_end(pslist), it_first2, it_last2));
    slist_destroy(pslist);
    list_destroy(plist);
}

void test_algo_search__invalid_range_not_same_type(void** state)
{
    set_t* pset = create_set(int);
    hash_set_t* phset = create_hash_set(char*);

    set_init(pset);
    hash_set_init(phset);
    expect_assert_failure(algo_search(set_begin(pset), set_end(pset), hash_set_begin(phset), hash_set_end(phset)));
    set_destroy(pset);
    hash_set_destroy(phset);
}

void test_algo_search__first_range_empty(void** state)
{
    set_t* pset = create_set(int);
    list_t* plist = create_list(int);

    set_init(pset);
    list_init_n(plist, 10);
    assert_true(iterator_equal(algo_search(set_begin(pset), set_end(pset), list_begin(plist), list_end(plist)), set_end(pset)));
    set_destroy(pset);
    list_destroy(plist);
}

void test_algo_search__second_range_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array[] = {1, 2, 3, 4, 5};

    vector_init_copy_array(pvec, an_array, sizeof(an_array)/sizeof(an_array[0]));
    list_init(plist);
    assert_true(iterator_equal(algo_search(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist)), vector_begin(pvec)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_search__c_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(int);
    slist_t* pslist = create_slist(int);
    int an_array1[] = {1, 4, 6, 8, 0, 2, 5, 6, 9, 2};
    int an_array2[] = {1, 4, 6, 8, 0};

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    slist_init_copy_array(pslist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(algo_search(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), slist_end(pslist)), deque_begin(pdeq)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_search__c_builtin_mismatch(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {11, 12, 13};

    set_init_copy_array(pset, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    multiset_init_copy_array(pmset, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(algo_search(set_begin(pset), set_end(pset), multiset_begin(pmset), multiset_end(pmset)), set_end(pset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_search__cstr_match(void** state)
{
    vector_t* pvec = create_vector(char*);
    list_t* plist = create_list(char*);
    const char* as_array1[] = {"abc", "def", "hij", "klm", "nop", "qrs"};
    const char* as_array2[] = {"hij", "klm"};

    vector_init_copy_array(pvec, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    list_init_copy_array(plist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(algo_search(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist)), iterator_next_n(vector_begin(pvec), 2)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_search__cstr_mismatch(void** state)
{
    slist_t* pslist = create_slist(char*);
    deque_t* pdeq = create_deque(char*);
    const char* as_array1[] = {"abc", "def", "hij", "klm", "nop", "qrs"};
    const char* as_array2[] = {"hij", "klm", "xyz"};

    slist_init_copy_array(pslist, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    deque_init_copy_array(pdeq, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(algo_search(slist_begin(pslist), slist_end(pslist), deque_begin(pdeq), deque_end(pdeq)), slist_end(pslist)));
    slist_destroy(pslist);
    deque_destroy(pdeq);
}

void test_algo_search__cstl_builtin_match(void** state)
{
    set_t* pset = create_set(vector_t<int>);
    multiset_t* pmset = create_multiset(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    int aan_array2[][3] = {{10, 11, 12}, {13, 14, 15}};
    int i = 0;

    set_init(pset);
    multiset_init(pmset);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        vector_assign_array(pvec, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        set_insert(pset, pvec);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        vector_assign_array(pvec, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        multiset_insert(pmset, pvec);
    }
    assert_true(iterator_equal(algo_search(set_begin(pset), set_end(pset), multiset_begin(pmset), multiset_end(pmset)), iterator_advance(set_end(pset), -2)));
    set_destroy(pset);
    multiset_destroy(pmset);
    vector_destroy(pvec);
}

void test_algo_search__cstl_builtin_mismatch(void** state)
{
    hash_set_t* phset = create_hash_set(list_t<int>);
    hash_multiset_t* phmset = create_hash_multiset(list_t<int>);
    list_t* plist = create_list(int);
    int aan_array1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    int aan_array2[][3] = {{100, 101, 102}, {103, 104, 105}};
    int i = 0;

    hash_set_init(phset);
    hash_multiset_init(phmset);
    list_init(plist);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        list_assign_array(plist, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        hash_set_insert(phset, plist);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        list_assign_array(plist, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        hash_multiset_insert(phmset, plist);
    }
    assert_true(iterator_equal(algo_search(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset), hash_multiset_end(phmset)), hash_set_end(phset)));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
    list_destroy(plist);
}

typedef struct _tag_test_algo_search__user_define {
    int a;
    int b;
} _test_algo_search__user_define_t;
static void _test_algo_search__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_search__user_define_t)) < 0 ? true : false;
}
void test_algo_search__user_define_match(void** state)
{
    vector_t* pvec = NULL;
    list_t* plist = NULL;
    _test_algo_search__user_define_t at_array1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_search__user_define_t at_array2[] = {{5, 6}, {7, 8}};
    int i = 0;

    type_register(_test_algo_search__user_define_t, NULL, NULL, _test_algo_search__user_define, NULL);
    pvec = create_vector(_test_algo_search__user_define_t);
    plist = create_list(_test_algo_search__user_define_t);
    vector_init(pvec);
    list_init(plist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        vector_push_back(pvec, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        list_push_back(plist, &at_array2[i]);
    }
    assert_true(iterator_equal(algo_search(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist)), iterator_next_n(vector_begin(pvec), 2)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_search__user_define_mismatch(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_search__user_define_t);
    slist_t* pslist = create_slist(_test_algo_search__user_define_t);
    _test_algo_search__user_define_t at_array1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_search__user_define_t at_array2[] = {{5, 6}, {8, 7}};
    int i = 0;

    deque_init(pdeq);
    slist_init(pslist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        deque_push_front(pdeq, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        slist_push_front(pslist, &at_array2[i]);
    }
    assert_true(iterator_equal(algo_search(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), slist_end(pslist)), deque_end(pdeq)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

/*
 * test algo_search_if
 */
UT_CASE_DEFINATION(algo_search_if)
void test_algo_search_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_search_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_if__invalid_first_range2(void** state)
{
    slist_t* pslist = create_slist(int);
    deque_t* pdeq = create_deque(int);

    slist_init_n(pslist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_search_if(slist_end(pslist), slist_begin(pslist), deque_begin(pdeq), deque_end(pdeq), NULL));
    slist_destroy(pslist);
    deque_destroy(pdeq);
}

void test_algo_search_if__invalid_first_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it_first1;
    iterator_t it_last1;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    it_first1 = vector_begin(pvec);
    it_last1 = vector_end(pvec);
    it_first1._t_iteratortype = _INPUT_ITERATOR;
    it_last1._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_search_if(it_first1, it_last1, list_begin(plist), list_end(plist), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_search_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_search_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_begin(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_if__invalid_second_range2(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_search_if(list_begin(plist), list_end(plist), slist_end(pslist), slist_begin(pslist), NULL));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_search_if__invalid_second_range3(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    iterator_t it_first2;
    iterator_t it_last2;

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    it_first2 = list_begin(plist);
    it_last2 = list_end(plist);
    it_first2._t_iteratortype = _INPUT_ITERATOR;
    it_last2._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_search_if(vector_begin(pvec), vector_end(pvec), it_first2, it_last2, NULL));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_search_if__invalid_range_not_same_type(void** state)
{
    set_t* pset = create_set(int);
    hash_set_t* phset = create_hash_set(vector_t<int>);

    set_init(pset);
    hash_set_init(phset);
    expect_assert_failure(algo_search_if(set_begin(pset), set_end(pset), hash_set_begin(phset), hash_set_end(phset), NULL));
    set_destroy(pset);
    hash_set_destroy(phset);
}

void test_algo_search_if__first_range_empty(void** state)
{
    multiset_t* pmset = create_multiset(int);
    list_t* plist = create_list(int);

    multiset_init(pmset);
    list_init_n(plist, 10);
    assert_true(iterator_equal(algo_search_if(multiset_begin(pmset), multiset_end(pmset), list_begin(plist), list_end(plist), NULL), multiset_end(pmset)));
    multiset_destroy(pmset);
    list_destroy(plist);
}

void test_algo_search_if__second_range_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    hash_set_t* phset = create_hash_set(int);

    deque_init_n(pdeq, 10);
    hash_set_init(phset);
    assert_true(iterator_equal(algo_search_if(deque_begin(pdeq), deque_end(pdeq), hash_set_begin(phset), hash_set_end(phset), NULL), deque_begin(pdeq)));
    deque_destroy(pdeq);
    hash_set_destroy(phset);
}

void test_algo_search_if__bfun_NULL_match(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {4 ,5 ,6};

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(algo_search_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL), iterator_next_n(deque_begin(pdeq), 3)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_search_if__bfun_NULL_mismatch(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {4 ,5 ,6, 9};

    vector_init_copy_array(pvec, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(algo_search_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), NULL), vector_end(pvec)));
    vector_destroy(pvec);
    list_destroy(plist);
}

static void _test_algo_search_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first * 10 == *(int*)cpv_second ? true : false;
}
void test_algo_search_if__c_builtin_match(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {10, 20, 30, 40, 50 ,60, 70, 80, 90};

    set_init_copy_array(pset, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    multiset_init_copy_array(pmset, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_search_if(set_begin(pset), set_end(pset), multiset_begin(pmset), multiset_end(pmset), _test_algo_search_if__c_builtin),
        set_begin(pset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_search_if__c_builtin_mismatch(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    hash_multiset_t* phmset = create_hash_multiset(int);
    int an_array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int an_array2[] = {10, 20, 30, 40, 50 ,60, 70, 80, 90, 0};

    hash_set_init_copy_array(phset, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    hash_multiset_init_copy_array(phmset, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_search_if(hash_set_begin(phset), hash_set_end(phset), hash_multiset_begin(phmset), hash_multiset_end(phmset), _test_algo_search_if__c_builtin),
        hash_set_end(phset)));
    hash_set_destroy(phset);
    hash_multiset_destroy(phmset);
}

static void _test_algo_search_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strlen((char*)cpv_first) == strlen((char*)cpv_second) ? true : false;
}
void test_algo_search_if__cstr_match(void** state)
{
    vector_t* pvec = create_vector(char*);
    list_t* plist = create_list(char*);
    const char* as_array1[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff"};
    const char* as_array2[] = {"xxx", "yyyy"};

    vector_init_copy_array(pvec, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    list_init_copy_array(plist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(
        algo_search_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), _test_algo_search_if__cstr),
        iterator_next_n(vector_begin(pvec), 2)));
    vector_destroy(pvec);
    list_destroy(plist);
}

void test_algo_search_if__cstr_mismatch(void** state)
{
    vector_t* pvec = create_vector(char*);
    list_t* plist = create_list(char*);
    const char* as_array1[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff"};
    const char* as_array2[] = {"xxx", "yyy"};

    vector_init_copy_array(pvec, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    list_init_copy_array(plist, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(
        algo_search_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), list_end(plist), _test_algo_search_if__cstr),
        vector_end(pvec)));
    vector_destroy(pvec);
    list_destroy(plist);
}

static void _test_algo_search_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    size_t i = 0;
    int n_sum1 = 0;
    int n_sum2 = 0;
    vector_t* pvec_first = (vector_t*)cpv_first;
    vector_t* pvec_second = (vector_t*)cpv_second;

    for (i = 0; i < vector_size(pvec_first); ++i) {
        n_sum1 += *(int*)vector_at(pvec_first, i);
    }
    for (i = 0; i < vector_size(pvec_second); ++i) {
        n_sum2 += *(int*)vector_at(pvec_second, i);
    }

    *(bool_t*)pv_output = n_sum1 == n_sum2 ? true : false;
}
void test_algo_search_if__cstl_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    list_t* plist = create_list(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int i = 0;
    int aan_array1[][3] = {{4, 5, 6}, {9, 1, 10}, {20, -10, 10}, {8, 8, -1}, {100, -99, 14}};
    int aan_array2[][4] = {{5, 5, 5, 5}, {10, 10, 0, 0}};

    deque_init(pdeq);
    list_init(plist);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        vector_assign_array(pvec, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        deque_push_back(pdeq, pvec);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        vector_assign_array(pvec, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        list_push_back(plist, pvec);
    }
    assert_true(iterator_equal(
        algo_search_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), _test_algo_search_if__cstl_builtin),
        iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_search_if__cstl_builtin_mismatch(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);
    list_t* plist = create_list(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int i = 0;
    int aan_array1[][3] = {{4, 5, 6}, {9, 1, 10}, {20, -10, 10}, {8, 8, -1}, {100, -99, 14}};
    int aan_array2[][4] = {{5, 5, 5, 5}, {0, 0, 0, 0}};

    deque_init(pdeq);
    list_init(plist);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        vector_assign_array(pvec, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        deque_push_back(pdeq, pvec);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        vector_assign_array(pvec, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        list_push_back(plist, pvec);
    }
    assert_true(iterator_equal(
        algo_search_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), _test_algo_search_if__cstl_builtin),
        deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test_algo_search_if__user_define {
    int a;
    int b;
} _test_algo_search_if__user_define_t;
static void _test_algo_search_if__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test_algo_search_if__user_define_t*)cpv_first)->a == ((_test_algo_search_if__user_define_t*)cpv_second)->b &&
        ((_test_algo_search_if__user_define_t*)cpv_first)->b == ((_test_algo_search_if__user_define_t*)cpv_second)->a ?
        true : false;
}
void test_algo_search_if__user_define_match(void** state)
{
    deque_t* pdeq = NULL;
    slist_t* pslist = NULL;
    _test_algo_search_if__user_define_t at_array1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_search_if__user_define_t at_array2[] = {{2, 1}, {4, 3}, {6, 5}};
    int i = 0;

    type_register(_test_algo_search_if__user_define_t, NULL, NULL, NULL, NULL);
    pdeq = create_deque(_test_algo_search_if__user_define_t);
    pslist = create_slist(_test_algo_search_if__user_define_t);
    deque_init(pdeq);
    slist_init(pslist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        deque_push_front(pdeq, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        slist_push_front(pslist, &at_array2[i]);
    }
    assert_true(iterator_equal(
        algo_search_if(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), slist_end(pslist), _test_algo_search_if__user_define),
        iterator_next_n(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

void test_algo_search_if__user_define_mismatch(void** state)
{
    deque_t* pdeq = create_deque(_test_algo_search_if__user_define_t);
    slist_t* pslist = create_slist(_test_algo_search_if__user_define_t);
    _test_algo_search_if__user_define_t at_array1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
    _test_algo_search_if__user_define_t at_array2[] = {{2, 1}, {3, 4}, {6, 5}};
    int i = 0;

    deque_init(pdeq);
    slist_init(pslist);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        deque_push_front(pdeq, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        slist_push_front(pslist, &at_array2[i]);
    }
    assert_true(iterator_equal(
        algo_search_if(deque_begin(pdeq), deque_end(pdeq), slist_begin(pslist), slist_end(pslist), _test_algo_search_if__user_define),
        deque_end(pdeq)));
    deque_destroy(pdeq);
    slist_destroy(pslist);
}

/*
 * test algo_search_end and algo_find_end
 */
UT_CASE_DEFINATION(algo_search_end_algo_find_end)
void test_algo_search_end_algo_find_end__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_find_end(vector_begin(pvec), list_begin(plist), deque_begin(pdeq), deque_end(pdeq)));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_end_algo_find_end__invalid_first_range2(void** state)
{
    slist_t* pslist = create_slist(int);
    set_t* pset = create_set(int);

    slist_init_n(pslist, 10);
    set_init(pset);
    expect_assert_failure(algo_find_end(slist_end(pslist), slist_begin(pslist), set_begin(pset), set_end(pset)));
    slist_destroy(pslist);
    set_destroy(pset);
}

void test_algo_search_end_algo_find_end__invalid_first_range3(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);
    iterator_t it_first1;

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    it_first1 = list_begin(plist);
    it_first1._t_iteratortype = _OUTPUT_ITERATOR;
    expect_assert_failure(algo_find_end(it_first1, list_end(plist), slist_begin(pslist), slist_end(pslist)));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_search_end_algo_find_end__invalid_second_range(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 10);
    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_find_end(list_begin(plist), list_end(plist), vector_begin(pvec), deque_end(pdeq)));
    list_destroy(plist);
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test_algo_search_end_algo_find_end__invalid_second_range2(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(int);

    slist_init_n(pslist, 10);
    vector_init_n(pvec, 10);
    expect_assert_failure(algo_find_end(slist_begin(pslist), slist_end(pslist), vector_end(pvec), vector_begin(pvec)));
    slist_destroy(pslist);
    vector_destroy(pvec);
}

void test_algo_search_end_algo_find_end__invalid_second_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it_last2;

    deque_init_n(pdeq, 10);
    list_init_n(plist, 10);
    it_last2 = list_end(plist);
    it_last2._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_find_end(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), it_last2));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_search_end_algo_find_end__invalid_range_not_same_type(void** state)
{
    set_t* pset = create_set(int);
    multiset_t* pmset = create_multiset(list_t<int>);

    set_init(pset);
    multiset_init(pmset);
    expect_assert_failure(algo_find_end(set_begin(pset), set_end(pset), multiset_begin(pmset), multiset_end(pmset)));
    set_destroy(pset);
    multiset_destroy(pmset);
}

void test_algo_search_end_algo_find_end__first_range_empty(void** state)
{
    hash_set_t* phset = create_hash_set(int);
    vector_t* pvec = create_vector(int);

    hash_set_init(phset);
    vector_init_n(pvec, 10);
    assert_true(iterator_equal(algo_find_end(hash_set_begin(phset), hash_set_end(phset), vector_begin(pvec), vector_end(pvec)), hash_set_end(phset)));
    hash_set_destroy(phset);
    vector_destroy(pvec);
}

void test_algo_search_end_algo_find_end__second_range_empty(void** state)
{
    list_t* plist = create_list(int);
    set_t* pset = create_set(int);

    list_init_n(plist, 10);
    set_init(pset);
    assert_true(iterator_equal(algo_find_end(list_begin(plist), list_end(plist), set_begin(pset), set_end(pset)), list_end(plist)));
    list_destroy(plist);
    set_destroy(pset);
}

void test_algo_search_end_algo_find_end__c_builtin_match(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int an_array1[] = {1, 1, 2, 3, 1, 2, 2, 3, 1, 2, 3};
    int an_array2[] = {1, 2, 3};

    list_init_copy_array(plist, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    vector_init_copy_array(pvec, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec)),
        iterator_advance(list_end(plist), -3)));
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_search_end_algo_find_end__c_builtin_mismatch(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int an_array1[] = {1, 1, 2, 3, 1, 2, 2, 3, 1, 2, 3};
    int an_array2[] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};

    list_init_copy_array(plist, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    vector_init_copy_array(pvec, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec)),
        list_end(plist)));
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_search_end_algo_find_end__cstr_match(void** state)
{
    list_t* plist = create_list(char*);
    vector_t* pvec = create_vector(char*);
    const char* as_array1[] = {"xxxx", "xxxx", "xxxx", "abcd", "github", "sina", "xxxx", "xxxx", "nnoopq"};
    const char* as_array2[] = {"xxxx", "xxxx", "xxxx"};

    list_init_copy_array(plist, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    vector_init_copy_array(pvec, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec)),
        list_begin(plist)));
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_search_end_algo_find_end__cstr_mismatch(void** state)
{
    list_t* plist = create_list(char*);
    vector_t* pvec = create_vector(char*);
    const char* as_array1[] = {"xxxx", "xxxx", "xxxx", "abcd", "github", "sina", "xxxx", "xxxx", "nnoopq"};
    const char* as_array2[] = {"xxxx", "xxxx", "xxxx", "xxxx"};

    list_init_copy_array(plist, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    vector_init_copy_array(pvec, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec)),
        list_end(plist)));
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_search_end_algo_find_end__cstl_builtin_match(void** state)
{
    list_t* plist = create_list(vector_t<int>);
    deque_t* pdeq = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array1[][3] = {{1, 2, 3}, {1, 1, 1}, {1, 1, 1}, {4, 5, 6}, {8, 8, 8}, {9, 9, 0}, {1, 2, 3}, {1, 2, 3}};
    int aan_array2[][3] = {{1, 2, 3}};
    int i = 0;

    list_init(plist);
    deque_init(pdeq);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        vector_assign_array(pvec, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        list_push_back(plist, pvec);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        vector_assign_array(pvec, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        deque_push_back(pdeq, pvec);
    }
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)),
        iterator_prev(list_end(plist))));
    list_destroy(plist);
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_search_end_algo_find_end__cstl_builtin_mismatch(void** state)
{
    list_t* plist = create_list(vector_t<int>);
    deque_t* pdeq = create_deque(vector_t<int>);
    vector_t* pvec = create_vector(int);
    int aan_array1[][3] = {{1, 2, 3}, {1, 1, 1}, {1, 1, 1}, {4, 5, 6}, {8, 8, 8}, {9, 9, 0}, {1, 2, 3}, {1, 2, 3}};
    int aan_array2[][3] = {{1, 2, 3}, {3, 2, 1}};
    int i = 0;

    list_init(plist);
    deque_init(pdeq);
    vector_init(pvec);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        vector_assign_array(pvec, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        list_push_back(plist, pvec);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        vector_assign_array(pvec, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        deque_push_back(pdeq, pvec);
    }
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)),
        list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

typedef struct _tag_test_algo_search_end_algo_find_end__user_define {
    int a;
    int b;
} _test_algo_search_end_algo_find_end__user_define_t;
static void _test_algo_search_end_algo_find_end__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = memcmp(cpv_first, cpv_second, sizeof(_test_algo_search_end_algo_find_end__user_define_t)) < 0 ? true : false;
}
void test_algo_search_end_algo_find_end__user_define_match(void** state)
{
    list_t* plist = NULL;
    deque_t* pdeq = NULL;
    _test_algo_search_end_algo_find_end__user_define_t at_array1[] = {{1, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {4, 4}, {4, 4}, {0, 0}};
    _test_algo_search_end_algo_find_end__user_define_t at_array2[] = {{2, 2}, {2, 2}};
    int i = 0;

    type_register(_test_algo_search_end_algo_find_end__user_define_t, NULL, NULL, _test_algo_search_end_algo_find_end__user_define, NULL);
    plist = create_list(_test_algo_search_end_algo_find_end__user_define_t);
    pdeq = create_deque(_test_algo_search_end_algo_find_end__user_define_t);
    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        list_push_back(plist, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)),
        iterator_advance(list_begin(plist), 3)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_end_algo_find_end__user_define_mismatch(void** state)
{
    list_t* plist = create_list(_test_algo_search_end_algo_find_end__user_define_t);
    deque_t* pdeq = create_deque(_test_algo_search_end_algo_find_end__user_define_t);
    _test_algo_search_end_algo_find_end__user_define_t at_array1[] = {{1, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {4, 4}, {4, 4}, {0, 0}};
    _test_algo_search_end_algo_find_end__user_define_t at_array2[] = {{2, 2}, {3, 3}};
    int i = 0;

    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        list_push_back(plist, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    assert_true(iterator_equal(
        algo_find_end(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq)),
        list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test algo_search_end_if and algo_find_end_if
 */
UT_CASE_DEFINATION(algo_search_end_if_algo_find_end_if)
void test_algo_search_end_if_algo_find_end_if__invalid_first_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_find_end_if(vector_begin(pvec), list_end(plist), deque_begin(pdeq), deque_end(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_end_if_algo_find_end_if__invalid_first_range2(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_find_end_if(list_end(plist), list_begin(plist), slist_begin(pslist), slist_end(pslist), NULL));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_search_end_if_algo_find_end_if__invalid_first_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    iterator_t it_last1;

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    it_last1 = deque_end(pdeq);
    it_last1._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_find_end_if(deque_begin(pdeq), it_last1, vector_begin(pvec), vector_end(pvec), NULL));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_search_end_if_algo_find_end_if__invalid_second_range(void** state)
{
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    list_init_n(plist, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(algo_find_end_if(vector_begin(pvec), vector_end(pvec), list_begin(plist), deque_end(pdeq), NULL));
    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_end_if_algo_find_end_if__invalid_second_range2(void** state)
{
    list_t* plist = create_list(int);
    slist_t* pslist = create_slist(int);

    list_init_n(plist, 10);
    slist_init_n(pslist, 10);
    expect_assert_failure(algo_find_end_if(list_begin(plist), list_end(plist), slist_end(pslist), slist_begin(pslist), NULL));
    list_destroy(plist);
    slist_destroy(pslist);
}

void test_algo_search_end_if_algo_find_end_if__invalid_second_range3(void** state)
{
    deque_t* pdeq = create_deque(int);
    vector_t* pvec = create_vector(int);
    iterator_t it_last2;

    deque_init_n(pdeq, 10);
    vector_init_n(pvec, 10);
    it_last2 = vector_end(pvec);
    it_last2._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(algo_find_end_if(deque_begin(pdeq), deque_end(pdeq), vector_begin(pvec), it_last2, NULL));
    deque_destroy(pdeq);
    vector_destroy(pvec);
}

void test_algo_search_end_if_algo_find_end_if__invalid_range_not_same_type(void** state)
{
    set_t* pset = create_set(int);
    hash_set_t* phset = create_hash_set(vector_t<int>);

    set_init(pset);
    hash_set_init(phset);
    expect_assert_failure(algo_find_end_if(set_begin(pset), set_end(pset), hash_set_begin(phset), hash_set_end(phset), NULL));
    set_destroy(pset);
    hash_set_destroy(phset);
}

void test_algo_search_end_if_algo_find_end_if__first_range_empty(void** state)
{
    multiset_t* pmset = create_multiset(int);
    vector_t* pvec = create_vector(int);

    multiset_init(pmset);
    vector_init_n(pvec, 10);
    assert_true(iterator_equal(
        algo_find_end_if(multiset_begin(pmset), multiset_end(pmset), vector_begin(pvec), vector_end(pvec), NULL),
        multiset_end(pmset)));
    multiset_destroy(pmset);
    vector_destroy(pvec);
}

void test_algo_search_end_if_algo_find_end_if__second_range_empty(void** state)
{
    list_t* plist = create_list(int);
    hash_set_t* phset = create_hash_set(int);

    list_init_n(plist, 10);
    hash_set_init(phset);
    assert_true(iterator_equal(
        algo_find_end_if(list_begin(plist), list_end(plist), hash_set_begin(phset), hash_set_end(phset), NULL),
        list_end(plist)));
    list_destroy(plist);
    hash_set_destroy(phset);
}

void test_algo_search_end_if_algo_find_end_if__bfun_NULL_match(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array1[] = {1, 1, 1, 2, 2, 2, 2, 4, 4, 6, 7, 8, 0, 0, 0};
    int an_array2[] = {4, 4};

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_find_end_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL),
        iterator_next_n(deque_begin(pdeq), 7)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_algo_search_end_if_algo_find_end_if__bfun_NULL_mismatch(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    int an_array1[] = {1, 1, 1, 2, 2, 2, 2, 4, 4, 6, 7, 8, 0, 0, 0};
    int an_array2[] = {4, 4, 4};

    deque_init_copy_array(pdeq, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    list_init_copy_array(plist, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_find_end_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), NULL),
        deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
}

static void _test_algo_search_end_if_algo_find_end_if__c_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) == abs(*(int*)cpv_second) ? true : false;
}
void test_algo_search_end_if_algo_find_end_if__c_builtin_match(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_array1[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 1, 2, 3};
    int an_array2[] = {-1, -2, -3};

    list_init_copy_array(plist, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    deque_init_copy_array(pdeq, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_find_end_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), _test_algo_search_end_if_algo_find_end_if__c_builtin),
        iterator_advance(list_end(plist), -3)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_end_if_algo_find_end_if__c_builtin_mismatch(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);
    int an_array1[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 1, 2, 3};
    int an_array2[] = {0, -1, -2, -3};

    list_init_copy_array(plist, an_array1, sizeof(an_array1)/sizeof(an_array1[0]));
    deque_init_copy_array(pdeq, an_array2, sizeof(an_array2)/sizeof(an_array2[0]));
    assert_true(iterator_equal(
        algo_find_end_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), _test_algo_search_end_if_algo_find_end_if__c_builtin),
        list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

static void _test_algo_search_end_if_algo_find_end_if__cstr(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strlen((char*)cpv_first) == strlen((char*)cpv_second) ? true : false;
}
void test_algo_search_end_if_algo_find_end_if__cstr_match(void** state)
{
    list_t* plist = create_list(char*);
    vector_t* pvec = create_vector(char*);
    const char* as_array1[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff"};
    const char* as_array2[] = {"x", "yy", "zzz"};

    list_init_copy_array(plist, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    vector_init_copy_array(pvec, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(
        algo_find_end_if(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec), _test_algo_search_end_if_algo_find_end_if__cstr),
        list_begin(plist)));
    list_destroy(plist);
    vector_destroy(pvec);
}

void test_algo_search_end_if_algo_find_end_if__cstr_mismatch(void** state)
{
    list_t* plist = create_list(char*);
    vector_t* pvec = create_vector(char*);
    const char* as_array1[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff"};
    const char* as_array2[] = {"x", "yy", ""};

    list_init_copy_array(plist, as_array1, sizeof(as_array1)/sizeof(as_array1[0]));
    vector_init_copy_array(pvec, as_array2, sizeof(as_array2)/sizeof(as_array2[0]));
    assert_true(iterator_equal(
        algo_find_end_if(list_begin(plist), list_end(plist), vector_begin(pvec), vector_end(pvec), _test_algo_search_end_if_algo_find_end_if__cstr),
        list_end(plist)));
    list_destroy(plist);
    vector_destroy(pvec);
}

static void _test_algo_search_end_if_algo_find_end_if__cstl_builtin(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = set_size((set_t*)cpv_first) == set_size((set_t*)cpv_second) ? true : false;
}
void test_algo_search_end_if_algo_find_end_if__cstl_builtin_match(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);
    list_t* plist = create_list(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array1[][3] = {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}, {2, 5, 8}};
    int aan_array2[][3] = {{1, 8, 4}, {3, 4, 5}};
    int i = 0;

    deque_init(pdeq);
    list_init(plist);
    set_init(pset);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        deque_push_back(pdeq, pset);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        list_push_back(plist, pset);
    }
    assert_true(iterator_equal(
        algo_find_end_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), _test_algo_search_end_if_algo_find_end_if__cstl_builtin),
        iterator_next_n(deque_begin(pdeq), 4)));
    deque_destroy(pdeq);
    list_destroy(plist);
    set_destroy(pset);
}

void test_algo_search_end_if_algo_find_end_if__cstl_builtin_mismatch(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);
    list_t* plist = create_list(set_t<int>);
    set_t* pset = create_set(int);
    int aan_array1[][3] = {{1, 2, 3}, {3, 4, 5}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}, {2, 5, 8}};
    int aan_array2[][3] = {{1, 8, 4}, {3, 3, 3}};
    int i = 0;

    deque_init(pdeq);
    list_init(plist);
    set_init(pset);
    for (i = 0; i < sizeof(aan_array1)/sizeof(aan_array1[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array1[i], sizeof(aan_array1[i])/sizeof(aan_array1[i][0]));
        deque_push_back(pdeq, pset);
    }
    for (i = 0; i < sizeof(aan_array2)/sizeof(aan_array2[0]); ++i) {
        set_clear(pset);
        set_insert_array(pset, aan_array2[i], sizeof(aan_array2[i])/sizeof(aan_array2[i][0]));
        list_push_back(plist, pset);
    }
    assert_true(iterator_equal(
        algo_find_end_if(deque_begin(pdeq), deque_end(pdeq), list_begin(plist), list_end(plist), _test_algo_search_end_if_algo_find_end_if__cstl_builtin),
        deque_end(pdeq)));
    deque_destroy(pdeq);
    list_destroy(plist);
    set_destroy(pset);
}

typedef struct _tag_test_algo_search_end_if_algo_find_end_if__user_define {
    int a;
    int b;
} _test_algo_search_end_if_algo_find_end_if__user_define_t;
static void _test_algo_search_end_if_algo_find_end_if__user_define(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = 
        ((_test_algo_search_end_if_algo_find_end_if__user_define_t*)cpv_first)->a + ((_test_algo_search_end_if_algo_find_end_if__user_define_t*)cpv_first)->b ==
        ((_test_algo_search_end_if_algo_find_end_if__user_define_t*)cpv_second)->a + ((_test_algo_search_end_if_algo_find_end_if__user_define_t*)cpv_second)->b ?
        true : false;
}
void test_algo_search_end_if_algo_find_end_if__user_define_match(void** state)
{
    list_t* plist = NULL;
    deque_t* pdeq = NULL;
    _test_algo_search_end_if_algo_find_end_if__user_define_t at_array1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 1}, {10, 10}};
    _test_algo_search_end_if_algo_find_end_if__user_define_t at_array2[] = {{1, 2}, {1, 6}};
    int i = 0;

    type_register(_test_algo_search_end_if_algo_find_end_if__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_algo_search_end_if_algo_find_end_if__user_define_t);
    pdeq = create_deque(_test_algo_search_end_if_algo_find_end_if__user_define_t);
    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        list_push_back(plist, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    assert_true(iterator_equal(
        algo_find_end_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), _test_algo_search_end_if_algo_find_end_if__user_define),
        list_begin(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

void test_algo_search_end_if_algo_find_end_if__user_define_mismatch(void** state)
{
    list_t* plist = create_list(_test_algo_search_end_if_algo_find_end_if__user_define_t);
    deque_t* pdeq = create_deque(_test_algo_search_end_if_algo_find_end_if__user_define_t);
    _test_algo_search_end_if_algo_find_end_if__user_define_t at_array1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 1}, {10, 10}};
    _test_algo_search_end_if_algo_find_end_if__user_define_t at_array2[] = {{1, 0}, {0, 6}};
    int i = 0;

    list_init(plist);
    deque_init(pdeq);
    for (i = 0; i < sizeof(at_array1)/sizeof(at_array1[0]); ++i) {
        list_push_back(plist, &at_array1[i]);
    }
    for (i = 0; i < sizeof(at_array2)/sizeof(at_array2[0]); ++i) {
        deque_push_back(pdeq, &at_array2[i]);
    }
    assert_true(iterator_equal(
        algo_find_end_if(list_begin(plist), list_end(plist), deque_begin(pdeq), deque_end(pdeq), _test_algo_search_end_if_algo_find_end_if__user_define),
        list_end(plist)));
    list_destroy(plist);
    deque_destroy(pdeq);
}

