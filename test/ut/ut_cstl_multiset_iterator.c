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
#include "ut_cstl_multiset_iterator.h"

UT_SUIT_DEFINATION(cstl_multiset_iterator, create_multiset_iterator)
/*
 * test _create_multiset_iterator
 */
UT_CASE_DEFINATION(create_multiset_iterator)
void test_create_multiset_iterator__successfully(void** state)
{
    multiset_iterator_t it_iter = create_multiset_iterator();
    assert_true(it_iter._t_pos._t_treepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _MULTISET_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

/*
 * test _multiset_iterator_get_value
 */
UT_CASE_DEFINATION(_multiset_iterator_get_value)
void test__multiset_iterator_get_value__null_corepos(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 0;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multiset_iterator_get_value(it_iter, &elem));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__null_tree(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 0;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_get_value(it_iter, &elem));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__invalid_container_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 0;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_containertype = 1000;
    expect_assert_failure(_multiset_iterator_get_value(it_iter, &elem));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__invalid_iterator_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 0;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_iteratortype = 1000;
    expect_assert_failure(_multiset_iterator_get_value(it_iter, &elem));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__end(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 0;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_end(pt_multiset);

    expect_assert_failure(_multiset_iterator_get_value(it_iter, &elem));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__null_value(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_end(pt_multiset);

    expect_assert_failure(_multiset_iterator_get_value(it_iter, NULL));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__c_builtin(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 12;
    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    it_iter = multiset_begin(pt_multiset);
    elem = 0;
    _multiset_iterator_get_value(it_iter, &elem);
    assert_true(elem == 12);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__cstr(void** state)
{
    multiset_t* pt_multiset = create_multiset(char*);
    multiset_iterator_t it_iter;
    char* p = NULL;
    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "abc");

    it_iter = multiset_begin(pt_multiset);
    _multiset_iterator_get_value(it_iter, &p);
    assert_true(strcmp(p, "abc") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_value__libcstl_builtin(void** state)
{
    multiset_t* pt_multiset = create_multiset(vector_t<int>);
    multiset_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    multiset_init_ex(pt_multiset, NULL);
    vector_init_n(pvec, 10);
    multiset_insert(pt_multiset, pvec);

    it_iter = multiset_begin(pt_multiset);
    vector_clear(pvec);
    _multiset_iterator_get_value(it_iter, pvec);
    assert_true(vector_size(pvec) == 10);

    multiset_destroy(pt_multiset);
    vector_destroy(pvec);
}

typedef struct _tag_test__multiset_iterator_get_value__user_define
{
    int elem;
}_test__multiset_iterator_get_value__user_define_t;
void test__multiset_iterator_get_value__user_define(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter;
    _test__multiset_iterator_get_value__user_define_t elem;

    type_register(_test__multiset_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_multiset = create_multiset(_test__multiset_iterator_get_value__user_define_t);
    multiset_init_ex(pt_multiset, NULL);
    elem.elem = 100;
    multiset_insert(pt_multiset, &elem);

    it_iter = multiset_begin(pt_multiset);
    elem.elem = 0;
    _multiset_iterator_get_value(it_iter, &elem);
    assert_true(elem.elem == 100);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_iterator_get_pointer
 */
UT_CASE_DEFINATION(_multiset_iterator_get_pointer)
void test__multiset_iterator_get_pointer__null_corepos(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multiset_iterator_get_pointer(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer__null_tree(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_get_pointer(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer__invalid_container_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_multiset_iterator_get_pointer(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer__invalid_iterator_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_multiset_iterator_get_pointer(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer__end(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_end(pt_multiset);

    expect_assert_failure(_multiset_iterator_get_pointer(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer__c_builtin(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 12;
    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    it_iter = multiset_begin(pt_multiset);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == 12);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer__cstr(void** state)
{
    multiset_t* pt_multiset = create_multiset(char*);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "abc");

    it_iter = multiset_begin(pt_multiset);
    assert_true(strcmp((char*)_multiset_iterator_get_pointer(it_iter), "abc") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer__libcstl_builtin(void** state)
{
    multiset_t* pt_multiset = create_multiset(vector_t<int>);
    multiset_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    multiset_init_ex(pt_multiset, NULL);
    vector_init_n(pvec, 10);
    multiset_insert(pt_multiset, pvec);

    it_iter = multiset_begin(pt_multiset);
    assert_true(vector_size((vector_t*)_multiset_iterator_get_pointer(it_iter)) == 10);

    multiset_destroy(pt_multiset);
    vector_destroy(pvec);
}

typedef struct _tag_test__multiset_iterator_get_pointer__user_define
{
    int elem;
}_test__multiset_iterator_get_pointer__user_define_t;
void test__multiset_iterator_get_pointer__user_define(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter;
    _test__multiset_iterator_get_pointer__user_define_t elem;

    type_register(_test__multiset_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_multiset = create_multiset(_test__multiset_iterator_get_pointer__user_define_t);
    multiset_init_ex(pt_multiset, NULL);
    elem.elem = 100;
    multiset_insert(pt_multiset, &elem);

    it_iter = multiset_begin(pt_multiset);
    assert_true(((_test__multiset_iterator_get_pointer__user_define_t*)_multiset_iterator_get_pointer(it_iter))->elem == 100);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_multiset_iterator_get_pointer_ignore_cstr)
void test__multiset_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer_ignore_cstr__null_tree(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer_ignore_cstr__invalid_container_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer_ignore_cstr__invalid_iterator_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer_ignore_cstr__end(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_end(pt_multiset);

    expect_assert_failure(_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 12;
    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    it_iter = multiset_begin(pt_multiset);
    assert_true(*(int*)_multiset_iterator_get_pointer_ignore_cstr(it_iter) == 12);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    multiset_t* pt_multiset = create_multiset(char*);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "abc");

    it_iter = multiset_begin(pt_multiset);
    assert_true(strcmp(string_c_str(_multiset_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    multiset_t* pt_multiset = create_multiset(vector_t<int>);
    multiset_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    multiset_init_ex(pt_multiset, NULL);
    vector_init_n(pvec, 10);
    multiset_insert(pt_multiset, pvec);

    it_iter = multiset_begin(pt_multiset);
    assert_true(vector_size((vector_t*)_multiset_iterator_get_pointer_ignore_cstr(it_iter)) == 10);

    multiset_destroy(pt_multiset);
    vector_destroy(pvec);
}

typedef struct _tag_test__multiset_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__multiset_iterator_get_pointer_ignore_cstr__user_define_t;
void test__multiset_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter;
    _test__multiset_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__multiset_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_multiset = create_multiset(_test__multiset_iterator_get_pointer_ignore_cstr__user_define_t);
    multiset_init_ex(pt_multiset, NULL);
    elem.elem = 100;
    multiset_insert(pt_multiset, &elem);

    it_iter = multiset_begin(pt_multiset);
    assert_true(((_test__multiset_iterator_get_pointer_ignore_cstr__user_define_t*)_multiset_iterator_get_pointer_ignore_cstr(it_iter))->elem == 100);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_iterator_next
 */
UT_CASE_DEFINATION(_multiset_iterator_next)
void test__multiset_iterator_next__null_corepos(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multiset_iterator_next(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_next__null_tree(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_next(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_next__invalid_container_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_containertype = 2394;
    expect_assert_failure(_multiset_iterator_next(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_next__invalid_iterator_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_iteratortype = 44444;
    expect_assert_failure(_multiset_iterator_next(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_next__end(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_end(pt_multiset);

    expect_assert_failure(_multiset_iterator_next(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_next__last(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 10;
    multiset_init_ex(pt_multiset, NULL);

    multiset_insert(pt_multiset, elem);
    it_iter = multiset_begin(pt_multiset);

    it_iter = _multiset_iterator_next(it_iter);
    assert_true(_multiset_iterator_equal(it_iter, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_next__begin(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 10;
    multiset_init_ex(pt_multiset, NULL);

    multiset_insert(pt_multiset, elem);
    elem = 3;
    multiset_insert(pt_multiset, elem);
    it_iter = multiset_begin(pt_multiset);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == 3);
    it_iter = _multiset_iterator_next(it_iter);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == 10);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_iterator_prev
 */
UT_CASE_DEFINATION(_multiset_iterator_prev)
void test__multiset_iterator_prev__null_corepos(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multiset_iterator_prev(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_prev__null_tree(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_prev(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_prev__invalid_containter_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_containertype = 33333;
    expect_assert_failure(_multiset_iterator_prev(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_prev__invalid_iterator_type(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    multiset_init_ex(pt_multiset, NULL);

    it_iter = multiset_begin(pt_multiset);

    it_iter._t_iteratortype = 5555;
    expect_assert_failure(_multiset_iterator_prev(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_prev__begin(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 100;
    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    it_iter = multiset_begin(pt_multiset);

    expect_assert_failure(_multiset_iterator_prev(it_iter));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_prev__end(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 10;
    multiset_init_ex(pt_multiset, NULL);

    multiset_insert(pt_multiset, elem);
    it_iter = multiset_end(pt_multiset);

    it_iter = _multiset_iterator_prev(it_iter);
    assert_true(_multiset_iterator_equal(it_iter, multiset_begin(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_prev__last(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 10;
    multiset_init_ex(pt_multiset, NULL);

    multiset_insert(pt_multiset, elem);
    elem = 3;
    multiset_insert(pt_multiset, elem);
    it_iter = _multiset_iterator_prev(multiset_end(pt_multiset));
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == 10);
    it_iter = _multiset_iterator_prev(it_iter);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == 3);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_iterator_equal
 */
UT_CASE_DEFINATION(_multiset_iterator_equal)
void test__multiset_iterator_equal__invalid_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_multiset, NULL);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_equal(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_equal__invalid_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_multiset, NULL);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    it_second._t_iteratortype = 45553;
    expect_assert_failure(_multiset_iterator_equal(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_equal__not_same_multiset(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);
    it_first = multiset_begin(pt_first);
    it_second = multiset_begin(pt_second);
    expect_assert_failure(_multiset_iterator_equal(it_first, it_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test__multiset_iterator_equal__equal(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    assert_true(_multiset_iterator_equal(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_equal__not_equal(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    elem = 2;
    multiset_insert(pt_multiset, elem);
    it_first = multiset_begin(pt_multiset);
    it_second = _multiset_iterator_next(it_first);
    assert_false(_multiset_iterator_equal(it_first, it_second));

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_iterator_distance
 */
UT_CASE_DEFINATION(_multiset_iterator_distance)
void test__multiset_iterator_distance__invalid_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_multiset, NULL);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_distance(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_distance__invalid_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_multiset, NULL);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    it_second._t_containertype = 4444;
    expect_assert_failure(_multiset_iterator_distance(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_distance__not_same_multiset(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);
    it_first = multiset_begin(pt_first);
    it_second = multiset_begin(pt_second);
    expect_assert_failure(_multiset_iterator_distance(it_first, it_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test__multiset_iterator_distance__0(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    assert_true(_multiset_iterator_distance(it_first, it_second) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_distance__greater_0(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    elem = 2;
    multiset_insert(pt_multiset, elem);
    it_first = multiset_begin(pt_multiset);
    it_second = _multiset_iterator_next(it_first);
    assert_true(_multiset_iterator_distance(it_first, it_second) == 1);

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_distance__less_0(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    elem = 2;
    multiset_insert(pt_multiset, elem);
    it_first = multiset_end(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    assert_true(_multiset_iterator_distance(it_first, it_second) == -2);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_iterator_before
 */
UT_CASE_DEFINATION(_multiset_iterator_before)
void test__multiset_iterator_before__invalid_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_multiset, NULL);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multiset_iterator_before(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_before__invalid_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_multiset, NULL);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multiset_iterator_before(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_before__not_same_multiset(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);
    it_first = multiset_begin(pt_first);
    it_second = multiset_begin(pt_second);
    expect_assert_failure(_multiset_iterator_before(it_first, it_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test__multiset_iterator_before__equal(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    it_first = multiset_begin(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    assert_false(_multiset_iterator_before(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_before__true(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    elem = 2;
    multiset_insert(pt_multiset, elem);
    it_first = multiset_begin(pt_multiset);
    it_second = _multiset_iterator_next(it_first);
    assert_true(_multiset_iterator_before(it_first, it_second));

    multiset_destroy(pt_multiset);
}

void test__multiset_iterator_before__false(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_first;
    multiset_iterator_t it_second;
    int elem = 100;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    elem = 2;
    multiset_insert(pt_multiset, elem);
    it_first = multiset_end(pt_multiset);
    it_second = multiset_begin(pt_multiset);
    assert_false(_multiset_iterator_before(it_first, it_second));

    multiset_destroy(pt_multiset);
}

