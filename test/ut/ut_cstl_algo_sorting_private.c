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
#include "ut_cstl_algo_sorting_private.h"

UT_SUIT_DEFINATION(cstl_algo_sorting_private, _algo_lower_bound)

/*
 * test _algo_lower_bound
 */
UT_CASE_DEFINATION(_algo_lower_bound)
void test__algo_lower_bound__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_lower_bound(vector_begin(pvec), deque_end(pdeq), 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_lower_bound__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_lower_bound(deque_end(pdeq), deque_begin(pdeq), 0));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_lower_bound(it, list_end(plist), 0));
    list_destroy(plist);
}

void test__algo_lower_bound__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), -3);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), 9);
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq), -1)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), 10);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), "abc");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), "mno");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), "pqr");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), "rst");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), "xyz");
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq), -1)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound__cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound(deque_begin(pdeq), deque_end(pdeq), "zzz");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test _algo_lower_bound_if
 */
UT_CASE_DEFINATION(_algo_lower_bound_if)
void test__algo_lower_bound_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_lower_bound_if(vector_begin(pvec), deque_end(pdeq), fun_greater_int, 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_lower_bound_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int, 0));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_lower_bound_if(it, list_end(plist), fun_greater_int, 0));
    list_destroy(plist);
}

void test__algo_lower_bound_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 0);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, -3);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 0);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 9);
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq), -1)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 10);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "abc");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "mno");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "pqr");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "rst");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "xyz");
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq), -1)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if__bfun_NULL_cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "zzz");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 13);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 9);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 4);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 4);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 0);
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq), -1)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, -1);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "zzz");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "xyz");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "ttt");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "rst");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "mno");
    assert_true(iterator_equal(it, iterator_advance(deque_end(pdeq), -1)));
    deque_destroy(pdeq);
}

void test__algo_lower_bound_if___cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_lower_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "abc");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test _algo_upper_bound
 */
UT_CASE_DEFINATION(_algo_upper_bound)
void test__algo_upper_bound__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_upper_bound(vector_begin(pvec), deque_end(pdeq), 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_upper_bound__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_upper_bound(deque_end(pdeq), deque_begin(pdeq), 0));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_upper_bound(it, list_end(plist), 0));
    list_destroy(plist);
}

void test__algo_upper_bound__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), -3);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 6)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), 9);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), 10);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), "abc");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), "mno");
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), "pqr");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), "rst");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 3)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), "xyz");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound__cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound(deque_begin(pdeq), deque_end(pdeq), "zzz");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test _algo_upper_bound_if
 */
UT_CASE_DEFINATION(_algo_upper_bound_if)
void test__algo_upper_bound_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_upper_bound_if(vector_begin(pvec), deque_end(pdeq), fun_greater_int, 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_upper_bound_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int, 0));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_upper_bound_if(it, list_end(plist), fun_greater_int, 0));
    list_destroy(plist);
}

void test__algo_upper_bound_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    iterator_t it;

    deque_init(pdeq);
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 0);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, -3);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 0);
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 5);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 6)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 9);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, 10);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "abc");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "mno");
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "pqr");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "rst");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 3)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "xyz");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if__bfun_NULL_cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), NULL, "zzz");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 13);
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 9);
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 4);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 4);
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 6)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 0);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    iterator_t it;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, -1);
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "zzz");
    assert_true(iterator_equal(it, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "xyz");
    assert_true(iterator_equal(it, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "ttt");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "rst");
    assert_true(iterator_equal(it, iterator_advance(deque_begin(pdeq), 3)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "mno");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_upper_bound_if___cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    iterator_t it;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    it = _algo_upper_bound_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "abc");
    assert_true(iterator_equal(it, deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test _algo_equal_range
 */
UT_CASE_DEFINATION(_algo_equal_range)
void test__algo_equal_range__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_equal_range(vector_begin(pvec), deque_end(pdeq), 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_equal_range__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_equal_range(deque_end(pdeq), deque_begin(pdeq), 0));
    deque_destroy(pdeq);
}

void test__algo_equal_range__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_equal_range(it, list_end(plist), 0));
    list_destroy(plist);
}

void test__algo_equal_range__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    range_t r_result;

    deque_init(pdeq);
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), -3);
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), 0);
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_equal_range__greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), 5);
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 5)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), 5);
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 5)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 6)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), 9);
    assert_true(iterator_equal(r_result.it_begin, iterator_prev(deque_end(pdeq))));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), 10);
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), "abc");
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), "mno");
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_equal_range__cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), "pqr");
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 2)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), "rst");
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 2)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 3)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), "xyz");
    assert_true(iterator_equal(r_result.it_begin, iterator_prev(deque_end(pdeq))));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range__cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range(deque_begin(pdeq), deque_end(pdeq), "zzz");
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test _algo_equal_range_if
 */
UT_CASE_DEFINATION(_algo_equal_range_if)
void test__algo_equal_range_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_equal_range_if(vector_begin(pvec), deque_end(pdeq), fun_greater_int, 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_equal_range_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int, 0));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_equal_range_if(it, list_end(plist), fun_greater_int, 0));
    list_destroy(plist);
}

void test__algo_equal_range_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    range_t r_result;

    deque_init(pdeq);
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 0);
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, -3);
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, 0);
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, 5);
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 5)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, 5);
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 5)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 6)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, 9);
    assert_true(iterator_equal(r_result.it_begin, iterator_prev(deque_end(pdeq))));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, 10);
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, "abc");
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, "mno");
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, "pqr");
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 2)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, "rst");
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 2)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 3)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, "xyz");
    assert_true(iterator_equal(r_result.it_begin, iterator_prev(deque_end(pdeq))));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if__bfun_NULL_cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), NULL, "zzz");
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___all_greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 13);
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 9);
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___greater(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 3, 2, 1, 0};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 4);
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 5)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 5)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___greater_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 4);
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 5)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 6)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 0);
    assert_true(iterator_equal(r_result.it_begin, iterator_prev(deque_end(pdeq))));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___all_less(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    range_t r_result;

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, -1);
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___cstr_all_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "zzz");
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_begin(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___cstr_all_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "xyz");
    assert_true(iterator_equal(r_result.it_begin, deque_begin(pdeq)));
    assert_true(iterator_equal(r_result.it_end, iterator_next(deque_begin(pdeq))));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___cstr_greater(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "ttt");
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 2)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 2)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___cstr_greater_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "rst");
    assert_true(iterator_equal(r_result.it_begin, iterator_advance(deque_begin(pdeq), 2)));
    assert_true(iterator_equal(r_result.it_end, iterator_advance(deque_begin(pdeq), 3)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___cstr_all_less_equal(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "mno");
    assert_true(iterator_equal(r_result.it_begin, iterator_prev(deque_end(pdeq))));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test__algo_equal_range_if___cstr_all_less(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};
    range_t r_result;

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    r_result = _algo_equal_range_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "abc");
    assert_true(iterator_equal(r_result.it_begin, deque_end(pdeq)));
    assert_true(iterator_equal(r_result.it_end, deque_end(pdeq)));
    deque_destroy(pdeq);
}

/*
 * test _algo_binary_search
 */
UT_CASE_DEFINATION(_algo_binary_search)
void test__algo_binary_search__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_binary_search(vector_begin(pvec), deque_end(pdeq), 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_binary_search__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_binary_search(deque_end(pdeq), deque_begin(pdeq), 0));
    deque_destroy(pdeq);
}

void test__algo_binary_search__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_binary_search(it, list_end(plist), 0));
    list_destroy(plist);
}

void test__algo_binary_search__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_false(_algo_binary_search(deque_begin(pdeq), deque_end(pdeq), 0));
    deque_destroy(pdeq);
}

void test__algo_binary_search__true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(_algo_binary_search(deque_begin(pdeq), deque_end(pdeq), 1));
    deque_destroy(pdeq);
}

void test__algo_binary_search__false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(_algo_binary_search(deque_begin(pdeq), deque_end(pdeq), 1));
    deque_destroy(pdeq);
}

void test__algo_binary_search__cstr_true(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(_algo_binary_search(deque_begin(pdeq), deque_end(pdeq), "rst"));
    deque_destroy(pdeq);
}

void test__algo_binary_search__cstr_false(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_false(_algo_binary_search(deque_begin(pdeq), deque_end(pdeq), "pqr"));
    deque_destroy(pdeq);
}

/*
 * test _algo_binary_search_if
 */
UT_CASE_DEFINATION(_algo_binary_search_if)
void test__algo_binary_search_if__invalid_range(void** state)
{
    vector_t* pvec = create_vector(int);
    deque_t* pdeq = create_deque(int);

    vector_init_n(pvec, 10);
    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_binary_search_if(vector_begin(pvec), deque_end(pdeq), fun_greater_int, 0));
    vector_destroy(pvec);
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__invalid_range2(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(_algo_binary_search_if(deque_end(pdeq), deque_begin(pdeq), fun_greater_int, 0));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__invalid_range3(void** state)
{
    list_t* plist = create_list(int);
    iterator_t it;

    list_init_n(plist, 10);
    it = list_begin(plist);
    it._t_iteratortype = _INPUT_ITERATOR;
    expect_assert_failure(_algo_binary_search_if(it, list_end(plist), fun_greater_int, 0));
    list_destroy(plist);
}

void test__algo_binary_search_if__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_false(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 0));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__bfun_NULL_true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), NULL, 1));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__bfun_NULL_false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {0, 2, 3, 4, 5, 6, 7, 8, 9};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), NULL, 1));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__bfun_NULL_cstr_true(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), NULL, "rst"));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__bfun_NULL_cstr_false(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"mno", "opq", "rst", "uvw", "xyz"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_false(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), NULL, "pqr"));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__true(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 1));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__false(void** state)
{
    deque_t* pdeq = create_deque(int);
    int an_array[] = {9, 8, 7, 6, 5, 4, 3, 2, 0};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_false(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_int, 1));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__cstr_true(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_true(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "rst"));
    deque_destroy(pdeq);
}

void test__algo_binary_search_if__cstr_false(void** state)
{
    deque_t* pdeq = create_deque(char*);
    const char* as_array[] = {"xyz", "uvw", "rst", "opq", "mno"};

    deque_init_copy_array(pdeq, as_array, sizeof(as_array)/sizeof(as_array[0]));
    assert_false(_algo_binary_search_if(deque_begin(pdeq), deque_end(pdeq), fun_greater_cstr, "pqr"));
    deque_destroy(pdeq);
}

