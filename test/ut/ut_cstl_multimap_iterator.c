#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cmap.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_multimap_aux.h"

#include "ut_def.h"
#include "ut_cstl_multimap_iterator.h"

UT_SUIT_DEFINATION(cstl_multimap_iterator, create_multimap_iterator)
/*
 * test _create_multimap_iterator
 */
UT_CASE_DEFINATION(create_multimap_iterator)
void test_create_multimap_iterator__successfully(void** state)
{
    multimap_iterator_t it_iter = create_multimap_iterator();
    assert_true(it_iter._t_pos._t_treepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _MULTIMAP_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

/*
 * test _multimap_iterator_get_value
 */
UT_CASE_DEFINATION(_multimap_iterator_get_value)
void test__multimap_iterator_get_value__null_corepos(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    int elem = 0;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multimap_iterator_get_value(it_iter, &elem));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_value__null_tree(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    int elem = 0;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_get_value(it_iter, &elem));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_value__invalid_container_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    int elem = 0;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_containertype = 1000;
    expect_assert_failure(_multimap_iterator_get_value(it_iter, &elem));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_value__invalid_iterator_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    int elem = 0;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_iteratortype = 1000;
    expect_assert_failure(_multimap_iterator_get_value(it_iter, &elem));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_value__end(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    int elem = 0;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_end(pt_multimap);

    expect_assert_failure(_multimap_iterator_get_value(it_iter, &elem));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_value__null_value(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_end(pt_multimap);

    expect_assert_failure(_multimap_iterator_get_value(it_iter, NULL));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_value__c_builtin(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 12;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    pair_make(pt_pair, 0, 0);
    _multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(*(int*)pair_first(pt_pair) == 12);
    assert_true(*(int*)pair_second(pt_pair) == 12);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_get_value__cstr(void** state)
{
    multimap_t* pt_multimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, "abc", "def");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    pair_make(pt_pair, "", "");
    _multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(strcmp((char*)pair_first(pt_pair), "abc") == 0);
    assert_true(strcmp((char*)pair_second(pt_pair), "def") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_get_value__libcstl_builtin(void** state)
{
    multimap_t* pt_multimap = create_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);
    multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    multimap_init_ex(pt_multimap, NULL);
    vector_init_n(pvec, 10);
    list_init(plist);
    pair_init_elem(pt_pair, pvec, plist);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    vector_clear(pvec);
    list_push_back(plist, 333);
    pair_make(pt_pair, pvec, plist);
    _multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(vector_size((vector_t*)pair_first(pt_pair)) == 10);
    assert_true(list_empty((list_t*)pair_second(pt_pair)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
    list_destroy(plist);
}

typedef struct _tag_test__multimap_iterator_get_value__user_define
{
    int elem;
}_test__multimap_iterator_get_value__user_define_t;
void test__multimap_iterator_get_value__user_define(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test__multimap_iterator_get_value__user_define_t elem;

    type_register(_test__multimap_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_multimap = create_multimap(_test__multimap_iterator_get_value__user_define_t, _test__multimap_iterator_get_value__user_define_t);
    pt_pair = create_pair(_test__multimap_iterator_get_value__user_define_t, _test__multimap_iterator_get_value__user_define_t);
    multimap_init_ex(pt_multimap, NULL);
    elem.elem = 100;
    pair_init_elem(pt_pair, &elem, &elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    elem.elem = 0;
    pair_make(pt_pair, &elem, &elem);
    _multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(((_test__multimap_iterator_get_value__user_define_t*)pair_first(pt_pair))->elem == 100);
    assert_true(((_test__multimap_iterator_get_value__user_define_t*)pair_second(pt_pair))->elem == 100);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_iterator_get_pointer
 */
UT_CASE_DEFINATION(_multimap_iterator_get_pointer)
void test__multimap_iterator_get_pointer__null_corepos(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multimap_iterator_get_pointer(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer__null_tree(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_get_pointer(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer__invalid_container_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_multimap_iterator_get_pointer(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer__invalid_iterator_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_multimap_iterator_get_pointer(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer__end(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_end(pt_multimap);

    expect_assert_failure(_multimap_iterator_get_pointer(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer__c_builtin(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 12;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(*(int*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter)) == 12);
    assert_true(*(int*)pair_second((pair_t*)_multimap_iterator_get_pointer(it_iter)) == 12);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_get_pointer__cstr(void** state)
{
    multimap_t* pt_multimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, "abc", "def");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(strcmp((char*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter)), "abc") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)_multimap_iterator_get_pointer(it_iter)), "def") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_get_pointer__libcstl_builtin(void** state)
{
    multimap_t* pt_multimap = create_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);
    multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    multimap_init_ex(pt_multimap, NULL);
    vector_init_n(pvec, 10);
    list_init(plist);
    pair_init_elem(pt_pair, pvec, plist);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(vector_size((vector_t*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter))) == 10);
    assert_true(list_size((list_t*)pair_second((pair_t*)_multimap_iterator_get_pointer(it_iter))) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
    list_destroy(plist);
}

typedef struct _tag_test__multimap_iterator_get_pointer__user_define
{
    int elem;
}_test__multimap_iterator_get_pointer__user_define_t;
void test__multimap_iterator_get_pointer__user_define(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test__multimap_iterator_get_pointer__user_define_t elem;

    type_register(_test__multimap_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_multimap = create_multimap(_test__multimap_iterator_get_pointer__user_define_t, _test__multimap_iterator_get_pointer__user_define_t);
    pt_pair = create_pair(_test__multimap_iterator_get_pointer__user_define_t, _test__multimap_iterator_get_pointer__user_define_t);
    multimap_init_ex(pt_multimap, NULL);
    elem.elem = 100;
    pair_init_elem(pt_pair, &elem, &elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(((_test__multimap_iterator_get_pointer__user_define_t*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter)))->elem == 100);
    assert_true(((_test__multimap_iterator_get_pointer__user_define_t*)pair_second((pair_t*)_multimap_iterator_get_pointer(it_iter)))->elem == 100);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_multimap_iterator_get_pointer_ignore_cstr)
void test__multimap_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer_ignore_cstr__null_tree(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer_ignore_cstr__invalid_container_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer_ignore_cstr__invalid_iterator_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer_ignore_cstr__end(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_end(pt_multimap);

    expect_assert_failure(_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 12;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(*(int*)pair_first((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter)) == 12);
    assert_true(*(int*)pair_second((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter)) == 12);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    multimap_t* pt_multimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, "abc", "def");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(strcmp((char*)pair_first((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter)), "def") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    multimap_t* pt_multimap = create_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);
    multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    multimap_init_ex(pt_multimap, NULL);
    vector_init_n(pvec, 10);
    list_init(plist);
    pair_init_elem(pt_pair, pvec, plist);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(vector_size((vector_t*)pair_first((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter))) == 10);
    assert_true(list_size((list_t*)pair_second((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter))) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
    list_destroy(plist);
}

typedef struct _tag_test__multimap_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__multimap_iterator_get_pointer_ignore_cstr__user_define_t;
void test__multimap_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test__multimap_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__multimap_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_multimap = create_multimap(_test__multimap_iterator_get_pointer_ignore_cstr__user_define_t, _test__multimap_iterator_get_pointer_ignore_cstr__user_define_t);
    pt_pair = create_pair(_test__multimap_iterator_get_pointer_ignore_cstr__user_define_t, _test__multimap_iterator_get_pointer_ignore_cstr__user_define_t);
    multimap_init_ex(pt_multimap, NULL);
    elem.elem = 100;
    pair_init_elem(pt_pair, &elem, &elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    assert_true(((_test__multimap_iterator_get_pointer_ignore_cstr__user_define_t*)pair_first((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter)))->elem == 100);
    assert_true(((_test__multimap_iterator_get_pointer_ignore_cstr__user_define_t*)pair_second((pair_t*)_multimap_iterator_get_pointer_ignore_cstr(it_iter)))->elem == 100);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_iterator_next
 */
UT_CASE_DEFINATION(_multimap_iterator_next)
void test__multimap_iterator_next__null_corepos(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multimap_iterator_next(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_next__null_tree(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_next(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_next__invalid_container_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_containertype = 2394;
    expect_assert_failure(_multimap_iterator_next(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_next__invalid_iterator_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_iteratortype = 44444;
    expect_assert_failure(_multimap_iterator_next(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_next__end(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_end(pt_multimap);

    expect_assert_failure(_multimap_iterator_next(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_next__last(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 10;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);

    multimap_insert(pt_multimap, pt_pair);
    it_iter = multimap_begin(pt_multimap);

    it_iter = _multimap_iterator_next(it_iter);
    assert_true(_multimap_iterator_equal(it_iter, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_next__begin(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 10;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);

    multimap_insert(pt_multimap, pt_pair);
    elem = 3;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_iter = multimap_begin(pt_multimap);
    assert_true(*(int*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter)) == 3);
    it_iter = _multimap_iterator_next(it_iter);
    assert_true(*(int*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter)) == 10);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_iterator_prev
 */
UT_CASE_DEFINATION(_multimap_iterator_prev)
void test__multimap_iterator_prev__null_corepos(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multimap_iterator_prev(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_prev__null_tree(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_prev(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_prev__invalid_containter_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int,int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_containertype = 33333;
    expect_assert_failure(_multimap_iterator_prev(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_prev__invalid_iterator_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int,int);
    multimap_iterator_t it_iter;
    multimap_init_ex(pt_multimap, NULL);

    it_iter = multimap_begin(pt_multimap);

    it_iter._t_iteratortype = 5555;
    expect_assert_failure(_multimap_iterator_prev(it_iter));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_prev__begin(void** state)
{
    multimap_t* pt_multimap = create_multimap(int,int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 100;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_begin(pt_multimap);
    expect_assert_failure(_multimap_iterator_prev(it_iter));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_prev__end(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 10;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);

    multimap_insert(pt_multimap, pt_pair);
    it_iter = multimap_end(pt_multimap);

    it_iter = _multimap_iterator_prev(it_iter);
    assert_true(_multimap_iterator_equal(it_iter, multimap_begin(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_prev__last(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 10;
    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);

    multimap_insert(pt_multimap, pt_pair);
    elem = 3;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_iter = _multimap_iterator_prev(multimap_end(pt_multimap));
    assert_true(*(int*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter)) == 10);
    it_iter = _multimap_iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)_multimap_iterator_get_pointer(it_iter)) == 3);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_iterator_equal
 */
UT_CASE_DEFINATION(_multimap_iterator_equal)
void test__multimap_iterator_equal__invalid_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_multimap, NULL);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_equal(it_first, it_second));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_equal__invalid_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_multimap, NULL);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    it_second._t_iteratortype = 45553;
    expect_assert_failure(_multimap_iterator_equal(it_first, it_second));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_equal__not_same_multimap(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);
    it_first = multimap_begin(pt_first);
    it_second = multimap_begin(pt_second);
    expect_assert_failure(_multimap_iterator_equal(it_first, it_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test__multimap_iterator_equal__equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    assert_true(_multimap_iterator_equal(it_first, it_second));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_equal__not_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_begin(pt_multimap);
    it_second = _multimap_iterator_next(it_first);
    assert_false(_multimap_iterator_equal(it_first, it_second));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_iterator_distance
 */
UT_CASE_DEFINATION(_multimap_iterator_distance)
void test__multimap_iterator_distance__invalid_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_multimap, NULL);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_distance(it_first, it_second));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_distance__invalid_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_multimap, NULL);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    it_second._t_containertype = 4444;
    expect_assert_failure(_multimap_iterator_distance(it_first, it_second));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_distance__not_same_multimap(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);
    it_first = multimap_begin(pt_first);
    it_second = multimap_begin(pt_second);
    expect_assert_failure(_multimap_iterator_distance(it_first, it_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test__multimap_iterator_distance__0(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    assert_true(_multimap_iterator_distance(it_first, it_second) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_distance__greater_0(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_begin(pt_multimap);
    it_second = _multimap_iterator_next(it_first);
    assert_true(_multimap_iterator_distance(it_first, it_second) == 1);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_distance__less_0(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_end(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    assert_true(_multimap_iterator_distance(it_first, it_second) == -2);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_iterator_before
 */
UT_CASE_DEFINATION(_multimap_iterator_before)
void test__multimap_iterator_before__invalid_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_multimap, NULL);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    it_first._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_multimap_iterator_before(it_first, it_second));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_before__invalid_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_multimap, NULL);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    it_second._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_multimap_iterator_before(it_first, it_second));

    multimap_destroy(pt_multimap);
}

void test__multimap_iterator_before__not_same_multimap(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);
    it_first = multimap_begin(pt_first);
    it_second = multimap_begin(pt_second);
    expect_assert_failure(_multimap_iterator_before(it_first, it_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test__multimap_iterator_before__equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_begin(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    assert_false(_multimap_iterator_before(it_first, it_second));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_before__true(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_begin(pt_multimap);
    it_second = _multimap_iterator_next(it_first);
    assert_true(_multimap_iterator_before(it_first, it_second));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_iterator_before__false(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_first;
    multimap_iterator_t it_second;
    int elem = 100;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_first = multimap_end(pt_multimap);
    it_second = multimap_begin(pt_multimap);
    assert_false(_multimap_iterator_before(it_first, it_second));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

