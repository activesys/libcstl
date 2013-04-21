#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_set_aux.h"

#include "ut_def.h"
#include "ut_cstl_set_iterator.h"

UT_SUIT_DEFINATION(cstl_set_iterator, create_set_iterator)
/*
 * test _create_set_iterator
 */
UT_CASE_DEFINATION(create_set_iterator)
void test_create_set_iterator__successfully(void** state)
{
    set_iterator_t it_iter = create_set_iterator();
    assert_true(it_iter._t_pos._t_treepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _SET_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

/*
 * test _set_iterator_get_value
 */
UT_CASE_DEFINATION(_set_iterator_get_value)
void test__set_iterator_get_value__null_corepos(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 0;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_set_iterator_get_value(it_iter, &elem));

    set_destroy(pt_set);
}

void test__set_iterator_get_value__null_tree(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 0;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_get_value(it_iter, &elem));

    set_destroy(pt_set);
}

void test__set_iterator_get_value__invalid_container_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 0;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_containertype = 1000;
    expect_assert_failure(_set_iterator_get_value(it_iter, &elem));

    set_destroy(pt_set);
}

void test__set_iterator_get_value__invalid_iterator_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 0;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_iteratortype = 1000;
    expect_assert_failure(_set_iterator_get_value(it_iter, &elem));

    set_destroy(pt_set);
}

void test__set_iterator_get_value__end(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 0;
    set_init_ex(pt_set, NULL);

    it_iter = set_end(pt_set);

    expect_assert_failure(_set_iterator_get_value(it_iter, &elem));

    set_destroy(pt_set);
}

void test__set_iterator_get_value__null_value(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_end(pt_set);

    expect_assert_failure(_set_iterator_get_value(it_iter, NULL));

    set_destroy(pt_set);
}

void test__set_iterator_get_value__c_builtin(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 12;
    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    it_iter = set_begin(pt_set);
    elem = 0;
    _set_iterator_get_value(it_iter, &elem);
    assert_true(elem == 12);

    set_destroy(pt_set);
}

void test__set_iterator_get_value__cstr(void** state)
{
    set_t* pt_set = create_set(char*);
    set_iterator_t it_iter;
    char* p = NULL;
    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "abc");

    it_iter = set_begin(pt_set);
    _set_iterator_get_value(it_iter, &p);
    assert_true(strcmp(p, "abc") == 0);

    set_destroy(pt_set);
}

void test__set_iterator_get_value__libcstl_builtin(void** state)
{
    set_t* pt_set = create_set(vector_t<int>);
    set_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    set_init_ex(pt_set, NULL);
    vector_init_n(pvec, 10);
    set_insert(pt_set, pvec);

    it_iter = set_begin(pt_set);
    vector_clear(pvec);
    _set_iterator_get_value(it_iter, pvec);
    assert_true(vector_size(pvec) == 10);

    set_destroy(pt_set);
    vector_destroy(pvec);
}

typedef struct _tag_test__set_iterator_get_value__user_define
{
    int elem;
}_test__set_iterator_get_value__user_define_t;
void test__set_iterator_get_value__user_define(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter;
    _test__set_iterator_get_value__user_define_t elem;

    type_register(_test__set_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_set = create_set(_test__set_iterator_get_value__user_define_t);
    set_init_ex(pt_set, NULL);
    elem.elem = 100;
    set_insert(pt_set, &elem);

    it_iter = set_begin(pt_set);
    elem.elem = 0;
    _set_iterator_get_value(it_iter, &elem);
    assert_true(elem.elem == 100);

    set_destroy(pt_set);
}

/*
 * test _set_iterator_get_pointer
 */
UT_CASE_DEFINATION(_set_iterator_get_pointer)
void test__set_iterator_get_pointer__null_corepos(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_set_iterator_get_pointer(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer__null_tree(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_get_pointer(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer__invalid_container_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_set_iterator_get_pointer(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer__invalid_iterator_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_set_iterator_get_pointer(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer__end(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_end(pt_set);

    expect_assert_failure(_set_iterator_get_pointer(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer__c_builtin(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 12;
    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    it_iter = set_begin(pt_set);
    assert_true(*(int*)_set_iterator_get_pointer(it_iter) == 12);

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer__cstr(void** state)
{
    set_t* pt_set = create_set(char*);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "abc");

    it_iter = set_begin(pt_set);
    assert_true(strcmp((char*)_set_iterator_get_pointer(it_iter), "abc") == 0);

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer__libcstl_builtin(void** state)
{
    set_t* pt_set = create_set(vector_t<int>);
    set_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    set_init_ex(pt_set, NULL);
    vector_init_n(pvec, 10);
    set_insert(pt_set, pvec);

    it_iter = set_begin(pt_set);
    assert_true(vector_size((vector_t*)_set_iterator_get_pointer(it_iter)) == 10);

    set_destroy(pt_set);
    vector_destroy(pvec);
}

typedef struct _tag_test__set_iterator_get_pointer__user_define
{
    int elem;
}_test__set_iterator_get_pointer__user_define_t;
void test__set_iterator_get_pointer__user_define(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter;
    _test__set_iterator_get_pointer__user_define_t elem;

    type_register(_test__set_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_set = create_set(_test__set_iterator_get_pointer__user_define_t);
    set_init_ex(pt_set, NULL);
    elem.elem = 100;
    set_insert(pt_set, &elem);

    it_iter = set_begin(pt_set);
    assert_true(((_test__set_iterator_get_pointer__user_define_t*)_set_iterator_get_pointer(it_iter))->elem == 100);

    set_destroy(pt_set);
}

/*
 * test _set_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_set_iterator_get_pointer_ignore_cstr)
void test__set_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_set_iterator_get_pointer_ignore_cstr(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer_ignore_cstr__null_tree(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_get_pointer_ignore_cstr(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer_ignore_cstr__invalid_container_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_set_iterator_get_pointer_ignore_cstr(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer_ignore_cstr__invalid_iterator_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_set_iterator_get_pointer_ignore_cstr(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer_ignore_cstr__end(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_end(pt_set);

    expect_assert_failure(_set_iterator_get_pointer_ignore_cstr(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 12;
    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    it_iter = set_begin(pt_set);
    assert_true(*(int*)_set_iterator_get_pointer_ignore_cstr(it_iter) == 12);

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    set_t* pt_set = create_set(char*);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "abc");

    it_iter = set_begin(pt_set);
    assert_true(strcmp(string_c_str(_set_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);

    set_destroy(pt_set);
}

void test__set_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    set_t* pt_set = create_set(vector_t<int>);
    set_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    set_init_ex(pt_set, NULL);
    vector_init_n(pvec, 10);
    set_insert(pt_set, pvec);

    it_iter = set_begin(pt_set);
    assert_true(vector_size((vector_t*)_set_iterator_get_pointer_ignore_cstr(it_iter)) == 10);

    set_destroy(pt_set);
    vector_destroy(pvec);
}

typedef struct _tag_test__set_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__set_iterator_get_pointer_ignore_cstr__user_define_t;
void test__set_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter;
    _test__set_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__set_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_set = create_set(_test__set_iterator_get_pointer_ignore_cstr__user_define_t);
    set_init_ex(pt_set, NULL);
    elem.elem = 100;
    set_insert(pt_set, &elem);

    it_iter = set_begin(pt_set);
    assert_true(((_test__set_iterator_get_pointer_ignore_cstr__user_define_t*)_set_iterator_get_pointer_ignore_cstr(it_iter))->elem == 100);

    set_destroy(pt_set);
}

/*
 * test _set_iterator_next
 */
UT_CASE_DEFINATION(_set_iterator_next)
void test__set_iterator_next__null_corepos(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_set_iterator_next(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_next__null_tree(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_next(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_next__invalid_container_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_containertype = 2394;
    expect_assert_failure(_set_iterator_next(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_next__invalid_iterator_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_iteratortype = 44444;
    expect_assert_failure(_set_iterator_next(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_next__end(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_end(pt_set);

    expect_assert_failure(_set_iterator_next(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_next__last(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 10;
    set_init_ex(pt_set, NULL);

    set_insert(pt_set, elem);
    it_iter = set_begin(pt_set);

    it_iter = _set_iterator_next(it_iter);
    assert_true(_set_iterator_equal(it_iter, set_end(pt_set)));

    set_destroy(pt_set);
}

void test__set_iterator_next__begin(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 10;
    set_init_ex(pt_set, NULL);

    set_insert(pt_set, elem);
    elem = 3;
    set_insert(pt_set, elem);
    it_iter = set_begin(pt_set);
    assert_true(*(int*)_set_iterator_get_pointer(it_iter) == 3);
    it_iter = _set_iterator_next(it_iter);
    assert_true(*(int*)_set_iterator_get_pointer(it_iter) == 10);

    set_destroy(pt_set);
}

/*
 * test _set_iterator_prev
 */
UT_CASE_DEFINATION(_set_iterator_prev)
void test__set_iterator_prev__null_corepos(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_set_iterator_prev(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_prev__null_tree(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_prev(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_prev__invalid_containter_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_containertype = 33333;
    expect_assert_failure(_set_iterator_prev(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_prev__invalid_iterator_type(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    set_init_ex(pt_set, NULL);

    it_iter = set_begin(pt_set);

    it_iter._t_iteratortype = 5555;
    expect_assert_failure(_set_iterator_prev(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_prev__begin(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 100;
    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    it_iter = set_begin(pt_set);

    expect_assert_failure(_set_iterator_prev(it_iter));

    set_destroy(pt_set);
}

void test__set_iterator_prev__end(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 10;
    set_init_ex(pt_set, NULL);

    set_insert(pt_set, elem);
    it_iter = set_end(pt_set);

    it_iter = _set_iterator_prev(it_iter);
    assert_true(_set_iterator_equal(it_iter, set_begin(pt_set)));

    set_destroy(pt_set);
}

void test__set_iterator_prev__last(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 10;
    set_init_ex(pt_set, NULL);

    set_insert(pt_set, elem);
    elem = 3;
    set_insert(pt_set, elem);
    it_iter = _set_iterator_prev(set_end(pt_set));
    assert_true(*(int*)_set_iterator_get_pointer(it_iter) == 10);
    it_iter = _set_iterator_prev(it_iter);
    assert_true(*(int*)_set_iterator_get_pointer(it_iter) == 3);

    set_destroy(pt_set);
}

/*
 * test _set_iterator_equal
 */
UT_CASE_DEFINATION(_set_iterator_equal)
void test__set_iterator_equal__invalid_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_set, NULL);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_equal(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_equal__invalid_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_set, NULL);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    it_second._t_iteratortype = 45553;
    expect_assert_failure(_set_iterator_equal(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_equal__not_same_set(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);
    it_first = set_begin(pt_first);
    it_second = set_begin(pt_second);
    expect_assert_failure(_set_iterator_equal(it_first, it_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test__set_iterator_equal__equal(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    assert_true(_set_iterator_equal(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_equal__not_equal(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    elem = 2;
    set_insert(pt_set, elem);
    it_first = set_begin(pt_set);
    it_second = _set_iterator_next(it_first);
    assert_false(_set_iterator_equal(it_first, it_second));

    set_destroy(pt_set);
}

/*
 * test _set_iterator_distance
 */
UT_CASE_DEFINATION(_set_iterator_distance)
void test__set_iterator_distance__invalid_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_set, NULL);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_distance(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_distance__invalid_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_set, NULL);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    it_second._t_containertype = 4444;
    expect_assert_failure(_set_iterator_distance(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_distance__not_same_set(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);
    it_first = set_begin(pt_first);
    it_second = set_begin(pt_second);
    expect_assert_failure(_set_iterator_distance(it_first, it_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test__set_iterator_distance__0(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    assert_true(_set_iterator_distance(it_first, it_second) == 0);

    set_destroy(pt_set);
}

void test__set_iterator_distance__greater_0(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    elem = 2;
    set_insert(pt_set, elem);
    it_first = set_begin(pt_set);
    it_second = _set_iterator_next(it_first);
    assert_true(_set_iterator_distance(it_first, it_second) == 1);

    set_destroy(pt_set);
}

void test__set_iterator_distance__less_0(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    elem = 2;
    set_insert(pt_set, elem);
    it_first = set_end(pt_set);
    it_second = set_begin(pt_set);
    assert_true(_set_iterator_distance(it_first, it_second) == -2);

    set_destroy(pt_set);
}

/*
 * test _set_iterator_before
 */
UT_CASE_DEFINATION(_set_iterator_before)
void test__set_iterator_before__invalid_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_set, NULL);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_set_iterator_before(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_before__invalid_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_set, NULL);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_set_iterator_before(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_before__not_same_set(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);
    it_first = set_begin(pt_first);
    it_second = set_begin(pt_second);
    expect_assert_failure(_set_iterator_before(it_first, it_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test__set_iterator_before__equal(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    it_first = set_begin(pt_set);
    it_second = set_begin(pt_set);
    assert_false(_set_iterator_before(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_before__true(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    elem = 2;
    set_insert(pt_set, elem);
    it_first = set_begin(pt_set);
    it_second = _set_iterator_next(it_first);
    assert_true(_set_iterator_before(it_first, it_second));

    set_destroy(pt_set);
}

void test__set_iterator_before__false(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_first;
    set_iterator_t it_second;
    int elem = 100;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    elem = 2;
    set_insert(pt_set, elem);
    it_first = set_end(pt_set);
    it_second = set_begin(pt_set);
    assert_false(_set_iterator_before(it_first, it_second));

    set_destroy(pt_set);
}

