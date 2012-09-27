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

