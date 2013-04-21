#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/citerator.h"
#include "cstl/cstl_avl_tree_iterator.h"
#include "cstl/cstl_avl_tree_private.h"
#include "cstl/cstl_avl_tree.h"
#include "cstl_avl_tree_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_avl_tree_iterator.h"

UT_SUIT_DEFINATION(cstl_avl_tree_iterator, _create_avl_tree_iterator)
/*
 * test _create_avl_tree_iterator
 */
UT_CASE_DEFINATION(_create_avl_tree_iterator)
void test__create_avl_tree_iterator__successfully(void** state)
{
    _avl_tree_iterator_t it_iter = _create_avl_tree_iterator();
    assert_true(it_iter._t_pos._t_treepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
}

/*
 * test _avl_tree_iterator_get_value
 */
UT_CASE_DEFINATION(_avl_tree_iterator_get_value)
void test__avl_tree_iterator_get_value__null_corepos(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 0;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_get_value(it_iter, &elem));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_value__null_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 0;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_get_value(it_iter, &elem));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_value__end(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 0;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_end(pt_avl_tree);

    expect_assert_failure(_avl_tree_iterator_get_value(it_iter, &elem));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_value__null_value(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_end(pt_avl_tree);

    expect_assert_failure(_avl_tree_iterator_get_value(it_iter, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_value__c_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 12;
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_begin(pt_avl_tree);
    elem = 0;
    _avl_tree_iterator_get_value(it_iter, &elem);
    assert_true(elem == 12);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_value__cstr(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    _avl_tree_iterator_t it_iter;
    string_t* pstr = create_string();
    char* p = NULL;
    string_init_cstr(pstr, "abc");
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, pstr);

    it_iter = _avl_tree_begin(pt_avl_tree);
    _avl_tree_iterator_get_value(it_iter, &p);
    assert_true(strcmp(p, "abc") == 0);

    _avl_tree_destroy(pt_avl_tree);
    string_destroy(pstr);
}

void test__avl_tree_iterator_get_value__libcstl_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("vector_t<int>");
    _avl_tree_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _avl_tree_init(pt_avl_tree, NULL);
    vector_init_n(pvec, 10);
    _avl_tree_insert_unique(pt_avl_tree, pvec);

    it_iter = _avl_tree_begin(pt_avl_tree);
    vector_clear(pvec);
    _avl_tree_iterator_get_value(it_iter, pvec);
    assert_true(vector_size(pvec) == 10);

    _avl_tree_destroy(pt_avl_tree);
    vector_destroy(pvec);
}

typedef struct _tag_test__avl_tree_iterator_get_value__user_define
{
    int elem;
}_test__avl_tree_iterator_get_value__user_define_t;
void test__avl_tree_iterator_get_value__user_define(void** state)
{
    _avl_tree_t* pt_avl_tree = NULL;
    _avl_tree_iterator_t it_iter;
    _test__avl_tree_iterator_get_value__user_define_t elem;

    type_register(_test__avl_tree_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_avl_tree = _create_avl_tree("_test__avl_tree_iterator_get_value__user_define_t");
    _avl_tree_init(pt_avl_tree, NULL);
    elem.elem = 100;
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_begin(pt_avl_tree);
    elem.elem = 0;
    _avl_tree_iterator_get_value(it_iter, &elem);
    assert_true(elem.elem == 100);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_get_pointer
 */
UT_CASE_DEFINATION(_avl_tree_iterator_get_pointer)
void test__avl_tree_iterator_get_pointer__null_corepos(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_get_pointer(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer__null_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_get_pointer(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer__end(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_end(pt_avl_tree);

    expect_assert_failure(_avl_tree_iterator_get_pointer(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer__c_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 12;
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(it_iter) == 12);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer__cstr(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    _avl_tree_iterator_t it_iter;
    string_t* pstr = create_string();
    string_init_cstr(pstr, "abc");
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, pstr);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(strcmp((char*)_avl_tree_iterator_get_pointer(it_iter), "abc") == 0);

    _avl_tree_destroy(pt_avl_tree);
    string_destroy(pstr);
}

void test__avl_tree_iterator_get_pointer__libcstl_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("vector_t<int>");
    _avl_tree_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _avl_tree_init(pt_avl_tree, NULL);
    vector_init_n(pvec, 10);
    _avl_tree_insert_unique(pt_avl_tree, pvec);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(vector_size((vector_t*)_avl_tree_iterator_get_pointer(it_iter)) == 10);

    _avl_tree_destroy(pt_avl_tree);
    vector_destroy(pvec);
}

typedef struct _tag_test__avl_tree_iterator_get_pointer__user_define
{
    int elem;
}_test__avl_tree_iterator_get_pointer__user_define_t;
void test__avl_tree_iterator_get_pointer__user_define(void** state)
{
    _avl_tree_t* pt_avl_tree = NULL;
    _avl_tree_iterator_t it_iter;
    _test__avl_tree_iterator_get_pointer__user_define_t elem;

    type_register(_test__avl_tree_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_avl_tree = _create_avl_tree("_test__avl_tree_iterator_get_pointer__user_define_t");
    _avl_tree_init(pt_avl_tree, NULL);
    elem.elem = 100;
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(((_test__avl_tree_iterator_get_pointer__user_define_t*)_avl_tree_iterator_get_pointer(it_iter))->elem == 100);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_avl_tree_iterator_get_pointer_ignore_cstr)
void test__avl_tree_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_get_pointer_ignore_cstr(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer_ignore_cstr__null_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_get_pointer_ignore_cstr(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer_ignore_cstr__end(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_end(pt_avl_tree);

    expect_assert_failure(_avl_tree_iterator_get_pointer_ignore_cstr(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 12;
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(*(int*)_avl_tree_iterator_get_pointer_ignore_cstr(it_iter) == 12);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    _avl_tree_iterator_t it_iter;
    string_t* pstr = create_string();
    string_init_cstr(pstr, "abc");
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, pstr);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(strcmp(string_c_str(_avl_tree_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);

    _avl_tree_destroy(pt_avl_tree);
    string_destroy(pstr);
}

void test__avl_tree_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("vector_t<int>");
    _avl_tree_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _avl_tree_init(pt_avl_tree, NULL);
    vector_init_n(pvec, 10);
    _avl_tree_insert_unique(pt_avl_tree, pvec);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(vector_size((vector_t*)_avl_tree_iterator_get_pointer_ignore_cstr(it_iter)) == 10);

    _avl_tree_destroy(pt_avl_tree);
    vector_destroy(pvec);
}

typedef struct _tag_test__avl_tree_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__avl_tree_iterator_get_pointer_ignore_cstr__user_define_t;
void test__avl_tree_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    _avl_tree_t* pt_avl_tree = NULL;
    _avl_tree_iterator_t it_iter;
    _test__avl_tree_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__avl_tree_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_avl_tree = _create_avl_tree("_test__avl_tree_iterator_get_pointer_ignore_cstr__user_define_t");
    _avl_tree_init(pt_avl_tree, NULL);
    elem.elem = 100;
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(((_test__avl_tree_iterator_get_pointer_ignore_cstr__user_define_t*)_avl_tree_iterator_get_pointer_ignore_cstr(it_iter))->elem == 100);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_next
 */
UT_CASE_DEFINATION(_avl_tree_iterator_next)
void test__avl_tree_iterator_next__null_corepos(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_next(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_next__null_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_next(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_next__end(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_end(pt_avl_tree);

    expect_assert_failure(_avl_tree_iterator_next(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_next__last(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 10;
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter = _avl_tree_iterator_next(it_iter);
    assert_true(_avl_tree_iterator_equal(it_iter, _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_next__begin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 10;
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 3;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(it_iter) == 3);
    it_iter = _avl_tree_iterator_next(it_iter);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(it_iter) == 10);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_prev
 */
UT_CASE_DEFINATION(_avl_tree_iterator_prev)
void test__avl_tree_iterator_prev__null_corepos(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_prev(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_prev__null_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    _avl_tree_init(pt_avl_tree, NULL);

    it_iter = _avl_tree_begin(pt_avl_tree);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_prev(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_prev__begin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 100;
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_begin(pt_avl_tree);

    expect_assert_failure(_avl_tree_iterator_prev(it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_prev__end(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 10;
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_iter = _avl_tree_end(pt_avl_tree);

    it_iter = _avl_tree_iterator_prev(it_iter);
    assert_true(_avl_tree_iterator_equal(it_iter, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_prev__last(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 10;
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 3;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_iter = _avl_tree_iterator_prev(_avl_tree_end(pt_avl_tree));
    assert_true(*(int*)_avl_tree_iterator_get_pointer(it_iter) == 10);
    it_iter = _avl_tree_iterator_prev(it_iter);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(it_iter) == 3);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_equal
 */
UT_CASE_DEFINATION(_avl_tree_iterator_equal)
void test__avl_tree_iterator_equal__invalid_first(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_avl_tree, NULL);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_equal(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_equal__invalid_second(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_avl_tree, NULL);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_equal(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_equal__not_same_avl_tree(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_first, NULL);
    _avl_tree_init(pt_second, NULL);
    it_first = _avl_tree_begin(pt_first);
    it_second = _avl_tree_begin(pt_second);
    expect_assert_failure(_avl_tree_iterator_equal(it_first, it_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_iterator_equal__equal(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    assert_true(_avl_tree_iterator_equal(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_equal__not_equal(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 2;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_iterator_next(it_first);
    assert_false(_avl_tree_iterator_equal(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_distance
 */
UT_CASE_DEFINATION(_avl_tree_iterator_distance)
void test__avl_tree_iterator_distance__invalid_first(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_avl_tree, NULL);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_distance(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_distance__invalid_second(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_avl_tree, NULL);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_distance(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_distance__not_same_avl_tree(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_first, NULL);
    _avl_tree_init(pt_second, NULL);
    it_first = _avl_tree_begin(pt_first);
    it_second = _avl_tree_begin(pt_second);
    expect_assert_failure(_avl_tree_iterator_distance(it_first, it_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_iterator_distance__0(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    assert_true(_avl_tree_iterator_distance(it_first, it_second) == 0);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_distance__greater_0(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 2;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_iterator_next(it_first);
    assert_true(_avl_tree_iterator_distance(it_first, it_second) == 1);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_distance__less_0(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 2;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_end(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    assert_true(_avl_tree_iterator_distance(it_first, it_second) == -2);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_before
 */
UT_CASE_DEFINATION(_avl_tree_iterator_before)
void test__avl_tree_iterator_before__invalid_first(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_avl_tree, NULL);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_before(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_before__invalid_second(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_avl_tree, NULL);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_before(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_before__not_same_avl_tree(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;

    _avl_tree_init(pt_first, NULL);
    _avl_tree_init(pt_second, NULL);
    it_first = _avl_tree_begin(pt_first);
    it_second = _avl_tree_begin(pt_second);
    expect_assert_failure(_avl_tree_iterator_before(it_first, it_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_iterator_before__equal(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    assert_false(_avl_tree_iterator_before(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_before__true(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 2;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_begin(pt_avl_tree);
    it_second = _avl_tree_iterator_next(it_first);
    assert_true(_avl_tree_iterator_before(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_before__false(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_second;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 2;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    it_first = _avl_tree_end(pt_avl_tree);
    it_second = _avl_tree_begin(pt_avl_tree);
    assert_false(_avl_tree_iterator_before(it_first, it_second));

    _avl_tree_destroy(pt_avl_tree);
}


