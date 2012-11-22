#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/citerator.h"
#include "cstl/cstl_rb_tree_iterator.h"
#include "cstl/cstl_rb_tree_private.h"
#include "cstl/cstl_rb_tree.h"
#include "cstl_rb_tree_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_rb_tree_iterator.h"

UT_SUIT_DEFINATION(cstl_rb_tree_iterator, _create_rb_tree_iterator)
/*
 * test _create_rb_tree_iterator
 */
UT_CASE_DEFINATION(_create_rb_tree_iterator)
void test__create_rb_tree_iterator__successfully(void** state)
{
    _rb_tree_iterator_t it_iter = _create_rb_tree_iterator();
    assert_true(it_iter._t_pos._t_treepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
}

/*
 * test _rb_tree_iterator_get_value
 */
UT_CASE_DEFINATION(_rb_tree_iterator_get_value)
void test__rb_tree_iterator_get_value__null_corepos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 0;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_get_value(it_iter, &elem));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_value__null_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 0;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_get_value(it_iter, &elem));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_value__end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 0;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_end(pt_rb_tree);

    expect_assert_failure(_rb_tree_iterator_get_value(it_iter, &elem));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_value__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_end(pt_rb_tree);

    expect_assert_failure(_rb_tree_iterator_get_value(it_iter, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_value__c_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 12;
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_begin(pt_rb_tree);
    elem = 0;
    _rb_tree_iterator_get_value(it_iter, &elem);
    assert_true(elem == 12);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_value__cstr(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();
    char* p = NULL;
    string_init_cstr(pstr, "abc");
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    it_iter = _rb_tree_begin(pt_rb_tree);
    _rb_tree_iterator_get_value(it_iter, &p);
    assert_true(strcmp(p, "abc") == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_iterator_get_value__libcstl_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("vector_t<int>");
    _rb_tree_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _rb_tree_init(pt_rb_tree, NULL);
    vector_init_n(pvec, 10);
    _rb_tree_insert_unique(pt_rb_tree, pvec);

    it_iter = _rb_tree_begin(pt_rb_tree);
    vector_clear(pvec);
    _rb_tree_iterator_get_value(it_iter, pvec);
    assert_true(vector_size(pvec) == 10);

    _rb_tree_destroy(pt_rb_tree);
    vector_destroy(pvec);
}

typedef struct _tag_test__rb_tree_iterator_get_value__user_define
{
    int elem;
}_test__rb_tree_iterator_get_value__user_define_t;
void test__rb_tree_iterator_get_value__user_define(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_iterator_get_value__user_define_t elem;

    type_register(_test__rb_tree_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_rb_tree = _create_rb_tree("_test__rb_tree_iterator_get_value__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);
    elem.elem = 100;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_begin(pt_rb_tree);
    elem.elem = 0;
    _rb_tree_iterator_get_value(it_iter, &elem);
    assert_true(elem.elem == 100);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_iterator_get_pointer
 */
UT_CASE_DEFINATION(_rb_tree_iterator_get_pointer)
void test__rb_tree_iterator_get_pointer__null_corepos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_get_pointer(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer__null_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_get_pointer(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer__end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_end(pt_rb_tree);

    expect_assert_failure(_rb_tree_iterator_get_pointer(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer__c_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 12;
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 12);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer__cstr(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();
    string_init_cstr(pstr, "abc");
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(it_iter), "abc") == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_iterator_get_pointer__libcstl_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("vector_t<int>");
    _rb_tree_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _rb_tree_init(pt_rb_tree, NULL);
    vector_init_n(pvec, 10);
    _rb_tree_insert_unique(pt_rb_tree, pvec);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(vector_size((vector_t*)_rb_tree_iterator_get_pointer(it_iter)) == 10);

    _rb_tree_destroy(pt_rb_tree);
    vector_destroy(pvec);
}

typedef struct _tag_test__rb_tree_iterator_get_pointer__user_define
{
    int elem;
}_test__rb_tree_iterator_get_pointer__user_define_t;
void test__rb_tree_iterator_get_pointer__user_define(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_iterator_get_pointer__user_define_t elem;

    type_register(_test__rb_tree_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_rb_tree = _create_rb_tree("_test__rb_tree_iterator_get_pointer__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);
    elem.elem = 100;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(((_test__rb_tree_iterator_get_pointer__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->elem == 100);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_rb_tree_iterator_get_pointer_ignore_cstr)
void test__rb_tree_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_get_pointer_ignore_cstr(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer_ignore_cstr__null_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_get_pointer_ignore_cstr(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer_ignore_cstr__end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_end(pt_rb_tree);

    expect_assert_failure(_rb_tree_iterator_get_pointer_ignore_cstr(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 12;
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(*(int*)_rb_tree_iterator_get_pointer_ignore_cstr(it_iter) == 12);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();
    string_init_cstr(pstr, "abc");
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(strcmp(string_c_str(_rb_tree_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("vector_t<int>");
    _rb_tree_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _rb_tree_init(pt_rb_tree, NULL);
    vector_init_n(pvec, 10);
    _rb_tree_insert_unique(pt_rb_tree, pvec);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(vector_size((vector_t*)_rb_tree_iterator_get_pointer_ignore_cstr(it_iter)) == 10);

    _rb_tree_destroy(pt_rb_tree);
    vector_destroy(pvec);
}

typedef struct _tag_test__rb_tree_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__rb_tree_iterator_get_pointer_ignore_cstr__user_define_t;
void test__rb_tree_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__rb_tree_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_rb_tree = _create_rb_tree("_test__rb_tree_iterator_get_pointer_ignore_cstr__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);
    elem.elem = 100;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(((_test__rb_tree_iterator_get_pointer_ignore_cstr__user_define_t*)_rb_tree_iterator_get_pointer_ignore_cstr(it_iter))->elem == 100);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_iterator_next
 */
UT_CASE_DEFINATION(_rb_tree_iterator_next)
void test__rb_tree_iterator_next__null_corepos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_next(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_next__null_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_next(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_next__end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_end(pt_rb_tree);

    expect_assert_failure(_rb_tree_iterator_next(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_next__last(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 10;
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter = _rb_tree_iterator_next(it_iter);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_next__begin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 10;
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 3;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 3);
    it_iter = _rb_tree_iterator_next(it_iter);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 10);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_iterator_prev
 */
UT_CASE_DEFINATION(_rb_tree_iterator_prev)
void test__rb_tree_iterator_prev__null_corepos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_prev(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_prev__null_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    _rb_tree_init(pt_rb_tree, NULL);

    it_iter = _rb_tree_begin(pt_rb_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_prev(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_prev__begin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 100;
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_begin(pt_rb_tree);

    expect_assert_failure(_rb_tree_iterator_prev(it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_prev__end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 10;
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_iter = _rb_tree_end(pt_rb_tree);

    it_iter = _rb_tree_iterator_prev(it_iter);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_prev__last(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 10;
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 3;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_iter = _rb_tree_iterator_prev(_rb_tree_end(pt_rb_tree));
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 10);
    it_iter = _rb_tree_iterator_prev(it_iter);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 3);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_iterator_equal
 */
UT_CASE_DEFINATION(_rb_tree_iterator_equal)
void test__rb_tree_iterator_equal__invalid_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_rb_tree, NULL);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_equal(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_equal__invalid_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_rb_tree, NULL);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_equal(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_equal__not_same_rb_tree(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);
    it_first = _rb_tree_begin(pt_first);
    it_second = _rb_tree_begin(pt_second);
    expect_assert_failure(_rb_tree_iterator_equal(it_first, it_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_iterator_equal__equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    assert_true(_rb_tree_iterator_equal(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_equal__not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 2;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_iterator_next(it_first);
    assert_false(_rb_tree_iterator_equal(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_iterator_distance
 */
UT_CASE_DEFINATION(_rb_tree_iterator_distance)
void test__rb_tree_iterator_distance__invalid_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_rb_tree, NULL);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_distance(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_distance__invalid_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_rb_tree, NULL);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_distance(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_distance__not_same_rb_tree(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);
    it_first = _rb_tree_begin(pt_first);
    it_second = _rb_tree_begin(pt_second);
    expect_assert_failure(_rb_tree_iterator_distance(it_first, it_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_iterator_distance__0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    assert_true(_rb_tree_iterator_distance(it_first, it_second) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_distance__greater_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 2;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_iterator_next(it_first);
    assert_true(_rb_tree_iterator_distance(it_first, it_second) == 1);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_distance__less_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 2;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_end(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    assert_true(_rb_tree_iterator_distance(it_first, it_second) == -2);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_iterator_before
 */
UT_CASE_DEFINATION(_rb_tree_iterator_before)
void test__rb_tree_iterator_before__invalid_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_rb_tree, NULL);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_before(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_before__invalid_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_rb_tree, NULL);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_before(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_before__not_same_rb_tree(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);
    it_first = _rb_tree_begin(pt_first);
    it_second = _rb_tree_begin(pt_second);
    expect_assert_failure(_rb_tree_iterator_before(it_first, it_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_iterator_before__equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    assert_false(_rb_tree_iterator_before(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_before__true(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 2;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_begin(pt_rb_tree);
    it_second = _rb_tree_iterator_next(it_first);
    assert_true(_rb_tree_iterator_before(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_before__false(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_second;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 2;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_first = _rb_tree_end(pt_rb_tree);
    it_second = _rb_tree_begin(pt_rb_tree);
    assert_false(_rb_tree_iterator_before(it_first, it_second));

    _rb_tree_destroy(pt_rb_tree);
}

