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
#include "cstl/cfunctional.h"

#include "ut_def.h"
#include "ut_cstl_function.h"

UT_SUIT_DEFINATION(cstl_function, fun_equal_pointer_usage)

/*
 * test fun_equal_pointer usage
 */
UT_CASE_DEFINATION(fun_equal_pointer_usage)
void test__fun_equal_pointer_usage__algo_unique_copy(void** state)
{
    vector_t* pvec = create_vector(void*);
    list_t* plist = create_list(void*);
    deque_t* pdeq = create_deque(void*);

    void* src[] = {0x1111, 0x1111, 0x1111, 0x2222, 0x2222, 0x3333, 0x4444, 0x4444, 0x8888, 0x8888};
    void* result[] = {0x1111, 0x2222, 0x3333, 0x4444, 0x8888, 0x00, 0x00, 0x00, 0x00, 0x00};

    vector_init_copy_array(pvec, src, 10);
    list_init_copy_array(plist, result, 10);
    deque_init_n(pdeq, vector_size(pvec));

    algo_unique_copy(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), list_begin(plist)));

    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test fun_not_equal_pointer usage
 */
UT_CASE_DEFINATION(fun_not_equal_pointer_usage)
void test__fun_not_equal_pointer_usage__algo_unique_copy_if(void** state)
{
    vector_t* pvec = create_vector(void*);
    list_t* plist = create_list(void*);
    deque_t* pdeq = create_deque(void*);

    void* src[] = {0x1111, 0x8888, 0x9999, 0x2222, 0x1111, 0x3333, 0x1111, 0x4444, 0x8888, 0x8888};
    void* result[] = {0x1111, 0x1111, 0x1111, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    vector_init_copy_array(pvec, src, 10);
    list_init_copy_array(plist, result, 10);
    deque_init_n(pdeq, vector_size(pvec));

    algo_unique_copy_if(vector_begin(pvec), vector_end(pvec), deque_begin(pdeq), _fun_get_binary(vector_begin(pvec), _NOT_EQUAL_FUN));
    assert_true(algo_equal(deque_begin(pdeq), deque_end(pdeq), list_begin(plist)));

    vector_destroy(pvec);
    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test fun_greater_pointer usage
 */
UT_CASE_DEFINATION(fun_greater_pointer_usage)
void test__fun_greater_pointer_usage__algo_sort_if(void** state)
{
    vector_t* pvec = create_vector(void*);
    list_t* plist = create_list(void*);

    void* src[] = {0x1111, 0x8888, 0x9999, 0x2222, 0x1111, 0x3333, 0x1111, 0x4444, 0x8888, 0x8888};
    void* result[] = {0x9999, 0x8888, 0x8888, 0x8888, 0x4444, 0x3333, 0x2222, 0x1111, 0x1111, 0x1111};

    vector_init_copy_array(pvec, src, 10);
    list_init_copy_array(plist, result, 10);

    algo_sort_if(vector_begin(pvec), vector_end(pvec), _fun_get_binary(vector_begin(pvec), _GREATER_FUN));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));

    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test fun_greater_equal_pointer usage
 */
UT_CASE_DEFINATION(fun_greater_equal_pointer_usage)
void test__fun_greater_equal_pointer_usage__algo_sort_if(void** state)
{
    vector_t* pvec = create_vector(void*);
    list_t* plist = create_list(void*);

    void* src[] = {0x1111, 0x8888, 0x9999, 0x2222, 0x1111, 0x3333, 0x1111, 0x4444, 0x8888, 0x8888};
    void* result[] = {0x9999, 0x8888, 0x8888, 0x8888, 0x4444, 0x3333, 0x2222, 0x1111, 0x1111, 0x1111};

    vector_init_copy_array(pvec, src, 10);
    list_init_copy_array(plist, result, 10);

    algo_sort_if(vector_begin(pvec), vector_end(pvec), _fun_get_binary(vector_begin(pvec), _GREATER_EQUAL_FUN));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));

    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test fun_less_pointer usage
 */
UT_CASE_DEFINATION(fun_less_pointer_usage)
void test__fun_less_pointer_usage__algo_sort_if(void** state)
{
    vector_t* pvec = create_vector(void*);
    list_t* plist = create_list(void*);

    void* src[] = {0x1111, 0x8888, 0x9999, 0x2222, 0x1111, 0x3333, 0x1111, 0x4444, 0x8888, 0x8888};
    void* result[] = {0x1111, 0x1111, 0x1111, 0x2222, 0x3333, 0x4444, 0x8888, 0x8888, 0x8888, 0x9999};

    vector_init_copy_array(pvec, src, 10);
    list_init_copy_array(plist, result, 10);

    algo_sort_if(vector_begin(pvec), vector_end(pvec), _fun_get_binary(vector_begin(pvec), _LESS_FUN));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));

    vector_destroy(pvec);
    list_destroy(plist);
}

/*
 * test fun_less_equal_pointer usage
 */
UT_CASE_DEFINATION(fun_less_equal_pointer_usage)
void test__fun_less_equal_pointer_usage__algo_sort_if(void** state)
{
    vector_t* pvec = create_vector(void*);
    list_t* plist = create_list(void*);

    void* src[] = {0x1111, 0x8888, 0x9999, 0x2222, 0x1111, 0x3333, 0x1111, 0x4444, 0x8888, 0x8888};
    void* result[] = {0x1111, 0x1111, 0x1111, 0x2222, 0x3333, 0x4444, 0x8888, 0x8888, 0x8888, 0x9999};

    vector_init_copy_array(pvec, src, 10);
    list_init_copy_array(plist, result, 10);

    algo_sort_if(vector_begin(pvec), vector_end(pvec), _fun_get_binary(vector_begin(pvec), _LESS_EQUAL_FUN));
    assert_true(algo_equal(vector_begin(pvec), vector_end(pvec), list_begin(plist)));

    vector_destroy(pvec);
    list_destroy(plist);
}
