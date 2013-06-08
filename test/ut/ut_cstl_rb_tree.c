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
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cslist.h"
#include "cstl/cset.h"
#include "cstl/chash_set.h"
#include "cstl/cdeque.h"

#include "ut_def.h"
#include "ut_cstl_rb_tree.h"

UT_SUIT_DEFINATION(cstl_rb_tree, _create_rb_tree)

/*
 * test _create_rb_tree
 */
UT_CASE_DEFINATION(_create_rb_tree)
void test__create_rb_tree__null_typename(void** state)
{
    expect_assert_failure(_create_rb_tree(NULL));
}

void test__create_rb_tree__c_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("double");
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__create_rb_tree__cstr(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__create_rb_tree__libcstl_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("vector_t<int>");
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

typedef struct _test_test__create_rb_tree__user_define
{
    int n_elem;
}_test__create_rb_tree__user_define_t;

void test__create_rb_tree__user_define(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;

    type_register(_test__create_rb_tree__user_define_t, NULL, NULL, NULL, NULL);
    pt_rb_tree = _create_rb_tree("_test__create_rb_tree__user_define_t");
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__create_rb_tree__unregister(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("test__create_rb_tree__unregister_t");
    assert_true(pt_rb_tree == NULL);
}

/*
 * test _rb_tree_init
 */
UT_CASE_DEFINATION(_rb_tree_init)
void test__rb_tree_init__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_init(NULL, NULL));
}

void test__rb_tree_init__non_created(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init(pt_rb_tree, NULL));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_init__null_compare(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_true(_rb_tree_is_inited(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

static void _test__rb_tree_init__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_init__non_null_compare(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, _test__rb_tree_init__non_null_compare);
    assert_true(_rb_tree_is_inited(pt_rb_tree));
    assert_true(pt_rb_tree->_t_compare == _test__rb_tree_init__non_null_compare);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_init_copy
 */
UT_CASE_DEFINATION(_rb_tree_init_copy)
void test__rb_tree_init_copy__null_dest(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_init_copy(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_init_copy__null_src(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    expect_assert_failure(_rb_tree_init_copy(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_init_copy__non_created_dest(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");

    _rb_tree_init(pt_src, NULL);
    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy(pt_dest, pt_src));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_init_copy__non_inited_src(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");

    _rb_tree_init(pt_src, NULL);
    pt_src->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy(pt_dest, pt_src));
    pt_src->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_init_copy__not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("double");

    _rb_tree_init(pt_src, NULL);
    expect_assert_failure(_rb_tree_init_copy(pt_dest, pt_src));

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_init_copy__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("signed int");

    _rb_tree_init(pt_src, NULL);
    _rb_tree_init_copy(pt_dest, pt_src);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_init_copy__non_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("signed int");
    int elem = 100;

    _rb_tree_init(pt_src, NULL);
    _rb_tree_insert_unique(pt_src, &elem);
    _rb_tree_init_copy(pt_dest, pt_src);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

static void _test__rb_tree_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_init_copy__non_null_compare(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("signed int");
    int i = 0;

    _rb_tree_init(pt_src, _test__rb_tree_init_copy__non_null_compare);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_src, &i);
    }
    _rb_tree_init_copy(pt_dest, pt_src);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);
    assert_true(pt_dest->_t_compare == _test__rb_tree_init_copy__non_null_compare);

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

/*
 * test _rb_tree_init_copy_equal_range
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_equal_range)
void test__rb_tree_init_copy_equal_range__null_rb_tree(void** state)
{
    vector_t* pvec = create_vector(int);

    expect_assert_failure(_rb_tree_init_copy_equal_range(NULL, vector_begin(pvec), vector_end(pvec)));

    vector_destroy(pvec);
}

void test__rb_tree_init_copy_equal_range__non_created_rb_tree(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    list_init(plist);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_equal_range(pt_dest, list_begin(plist), list_end(plist)));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

void test__rb_tree_init_copy_equal_range__invalid_begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    slist_init(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_iteratortype = 333;
    expect_assert_failure(_rb_tree_init_copy_equal_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__rb_tree_init_copy_equal_range__invalid_end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    deque_init(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_containertype = 3333;
    expect_assert_failure(_rb_tree_init_copy_equal_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__rb_tree_init_copy_equal_range__invalid_range(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    assert_true(set_size(pset) == 1);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_rb_tree_init_copy_equal_range(pt_dest, it_end, it_begin));

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

void test__rb_tree_init_copy_equal_range__invalid_range_not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    multiset_init(pmset);
    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_rb_tree_init_copy_equal_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__rb_tree_init_copy_equal_range__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    hash_set_init(phset);
    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _rb_tree_init_copy_equal_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__rb_tree_init_copy_equal_range__non_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, elem);
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_equal_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__rb_tree_init_copy_equal_range__non_empty_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, elem);
    hash_multiset_insert(phmset, elem);
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_equal_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 2);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

/*
 * test _rb_tree_init_copy_unique_range
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_unique_range)
void test__rb_tree_init_copy_unique_range__null_rb_tree(void** state)
{
    vector_t* pvec = create_vector(int);

    expect_assert_failure(_rb_tree_init_copy_unique_range(NULL, vector_begin(pvec), vector_end(pvec)));

    vector_destroy(pvec);
}

void test__rb_tree_init_copy_unique_range__non_created_rb_tree(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    list_init(plist);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_unique_range(pt_dest, list_begin(plist), list_end(plist)));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

void test__rb_tree_init_copy_unique_range__invalid_begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    slist_init(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_iteratortype = 333;
    expect_assert_failure(_rb_tree_init_copy_unique_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__rb_tree_init_copy_unique_range__invalid_end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    deque_init(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_containertype = 3333;
    expect_assert_failure(_rb_tree_init_copy_unique_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__rb_tree_init_copy_unique_range__invalid_range(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    assert_true(set_size(pset) == 1);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_rb_tree_init_copy_unique_range(pt_dest, it_end, it_begin));

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

void test__rb_tree_init_copy_unique_range__invalid_range_not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    multiset_init(pmset);
    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_rb_tree_init_copy_unique_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__rb_tree_init_copy_unique_range__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    hash_set_init(phset);
    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _rb_tree_init_copy_unique_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__rb_tree_init_copy_unique_range__non_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, elem);
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_unique_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__rb_tree_init_copy_unique_range__non_empty_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, elem);
    hash_multiset_insert(phmset, elem);
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_unique_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

/*
 * test _rb_tree_init_copy_equal_array
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_equal_array)
void test__rb_tree_init_copy_equal_array__null_rb_tree(void** state)
{
    int an_array[10] = {0};

    expect_assert_failure(_rb_tree_init_copy_equal_array(NULL, an_array, 10));
}

void test__rb_tree_init_copy_equal_array__non_created_rb_tree(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_equal_array(pt_dest, an_array, 10));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array__invalid_array(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    expect_assert_failure(_rb_tree_init_copy_equal_array(pt_dest, NULL, 10));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array__empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init_copy_equal_array(pt_dest, an_array, 0);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array__non_empty(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    _rb_tree_init_copy_equal_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init_copy_equal_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
}

/*
 * test _rb_tree_init_copy_unique_array
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_unique_array)
void test__rb_tree_init_copy_unique_array__null_rb_tree(void** state)
{
    int an_array[10] = {0};

    expect_assert_failure(_rb_tree_init_copy_unique_array(NULL, an_array, 10));
}

void test__rb_tree_init_copy_unique_array__non_created_rb_tree(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_unique_array(pt_dest, an_array, 10));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array__invalid_array(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    expect_assert_failure(_rb_tree_init_copy_unique_array(pt_dest, NULL, 10));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array__empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init_copy_unique_array(pt_dest, an_array, 0);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array__non_empty(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    _rb_tree_init_copy_unique_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init_copy_unique_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);

    _rb_tree_destroy(pt_dest);
}

/*
 * test _rb_tree_init_copy_equal_range_ex
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_equal_range_ex)
void test__rb_tree_init_copy_equal_range_ex__null_rb_tree(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_rb_tree_init_copy_equal_range_ex(NULL, vector_begin(pvec), vector_end(pvec), NULL));

    vector_destroy(pvec);
}

void test__rb_tree_init_copy_equal_range_ex__non_created_rb_tree(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    list_init(plist);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_equal_range_ex(pt_dest, list_begin(plist), list_end(plist), NULL));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

void test__rb_tree_init_copy_equal_range_ex__invalid_begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    slist_init(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_containertype = 444;
    expect_assert_failure(_rb_tree_init_copy_equal_range_ex(pt_dest, it_begin, it_end, NULL));

    _rb_tree_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__rb_tree_init_copy_equal_range_ex__invalid_end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    deque_init(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_iteratortype = 4444;
    expect_assert_failure(_rb_tree_init_copy_equal_range_ex(pt_dest, it_begin, it_end, NULL));

    _rb_tree_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__rb_tree_init_copy_equal_range_ex__invalid_range(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_rb_tree_init_copy_equal_range_ex(pt_dest, it_end, it_begin, NULL));

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

void test__rb_tree_init_copy_equal_range_ex__invalid_range_not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    multiset_init(pmset);
    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_rb_tree_init_copy_equal_range_ex(pt_dest, it_begin, it_end, NULL));

    _rb_tree_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__rb_tree_init_copy_equal_range_ex__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    hash_set_init(phset);
    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _rb_tree_init_copy_equal_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__rb_tree_init_copy_equal_range_ex__non_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    for (elem = 0; elem < 10; ++elem) {
        hash_multiset_insert(phmset, elem);
    }
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_equal_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__rb_tree_init_copy_equal_range_ex__non_empty_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    for (elem = 0; elem < 10; ++elem) {
        hash_multiset_insert(phmset, 0);
    }
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_equal_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

static void _test__rb_tree_init_compare_equal_range_ex__compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_init_copy_equal_range_ex__compare(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    _rb_tree_init_copy_equal_range_ex(pt_dest, it_begin, it_end, _test__rb_tree_init_compare_equal_range_ex__compare);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);
    assert_true(pt_dest->_t_compare == _test__rb_tree_init_compare_equal_range_ex__compare);

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

/*
 * test _rb_tree_init_copy_unique_range_ex
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_unique_range_ex)
void test__rb_tree_init_copy_unique_range_ex__null_rb_tree(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_rb_tree_init_copy_unique_range_ex(NULL, vector_begin(pvec), vector_end(pvec), NULL));

    vector_destroy(pvec);
}

void test__rb_tree_init_copy_unique_range_ex__non_created_rb_tree(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    list_init(plist);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_unique_range_ex(pt_dest, list_begin(plist), list_end(plist), NULL));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

void test__rb_tree_init_copy_unique_range_ex__invalid_begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    slist_init(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_containertype = 444;
    expect_assert_failure(_rb_tree_init_copy_unique_range_ex(pt_dest, it_begin, it_end, NULL));

    _rb_tree_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__rb_tree_init_copy_unique_range_ex__invalid_end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    deque_init(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_iteratortype = 4444;
    expect_assert_failure(_rb_tree_init_copy_unique_range_ex(pt_dest, it_begin, it_end, NULL));

    _rb_tree_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__rb_tree_init_copy_unique_range_ex__invalid_range(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_rb_tree_init_copy_unique_range_ex(pt_dest, it_end, it_begin, NULL));

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

void test__rb_tree_init_copy_unique_range_ex__invalid_range_not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    multiset_init(pmset);
    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_rb_tree_init_copy_unique_range_ex(pt_dest, it_begin, it_end, NULL));

    _rb_tree_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__rb_tree_init_copy_unique_range_ex__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    hash_set_init(phset);
    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _rb_tree_init_copy_unique_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__rb_tree_init_copy_unique_range_ex__non_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    for (elem = 0; elem < 10; ++elem) {
        hash_multiset_insert(phmset, elem);
    }
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_unique_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__rb_tree_init_copy_unique_range_ex__non_empty_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    for (elem = 0; elem < 10; ++elem) {
        hash_multiset_insert(phmset, 0);
    }
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_init_copy_unique_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

static void _test__rb_tree_init_compare_unique_range_ex__compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_init_copy_unique_range_ex__compare(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    _rb_tree_init_copy_unique_range_ex(pt_dest, it_begin, it_end, _test__rb_tree_init_compare_unique_range_ex__compare);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);
    assert_true(pt_dest->_t_compare == _test__rb_tree_init_compare_unique_range_ex__compare);

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

/*
 * test _rb_tree_init_copy_equal_array_ex
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_equal_array_ex)
void test__rb_tree_init_copy_equal_array_ex__null_rb_tree(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_rb_tree_init_copy_equal_array_ex(NULL, an_array, 10, NULL));
}

void test__rb_tree_init_copy_equal_array_ex__non_created_rb_tree(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_equal_array_ex(pt_dest, an_array, 10, NULL));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array_ex__invalid_array(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    expect_assert_failure(_rb_tree_init_copy_equal_array_ex(pt_dest, NULL, 10, NULL));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array_ex__empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init_copy_equal_array_ex(pt_dest, an_array, 0, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array_ex__non_empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int elem = 9;

    for (elem = 0; elem < 10; ++elem) {
        an_array[elem] = elem;
    }
    _rb_tree_init_copy_equal_array_ex(pt_dest, an_array, 10, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_equal_array_ex__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init_copy_equal_array_ex(pt_dest, an_array, 10, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
}

static void _test__rb_tree_init_compare_equal_array_ex__compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_init_copy_equal_array_ex__compare(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init_copy_equal_array_ex(pt_dest, an_array, 10, _test__rb_tree_init_compare_equal_array_ex__compare);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);
    assert_true(pt_dest->_t_compare == _test__rb_tree_init_compare_equal_array_ex__compare);

    _rb_tree_destroy(pt_dest);
}

/*
 * test _rb_tree_init_copy_unique_array_ex
 */
UT_CASE_DEFINATION(_rb_tree_init_copy_unique_array_ex)
void test__rb_tree_init_copy_unique_array_ex__null_rb_tree(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_rb_tree_init_copy_unique_array_ex(NULL, an_array, 10, NULL));
}

void test__rb_tree_init_copy_unique_array_ex__non_created_rb_tree(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_copy_unique_array_ex(pt_dest, an_array, 10, NULL));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array_ex__invalid_array(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    expect_assert_failure(_rb_tree_init_copy_unique_array_ex(pt_dest, NULL, 10, NULL));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array_ex__empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_init_copy_unique_array_ex(pt_dest, an_array, 0, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array_ex__non_empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int elem = 9;

    for (elem = 0; elem < 10; ++elem) {
        an_array[elem] = elem;
    }
    _rb_tree_init_copy_unique_array_ex(pt_dest, an_array, 10, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 10);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_init_copy_unique_array_ex__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_init_copy_unique_array_ex(pt_dest, an_array, 10, NULL);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);

    _rb_tree_destroy(pt_dest);
}

static void _test__rb_tree_init_compare_unique_array_ex__compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_init_copy_unique_array_ex__compare(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_init_copy_unique_array_ex(pt_dest, an_array, 10, _test__rb_tree_init_compare_unique_array_ex__compare);
    assert_true(_rb_tree_is_inited(pt_dest));
    assert_true(_rb_tree_size(pt_dest) == 1);
    assert_true(pt_dest->_t_compare == _test__rb_tree_init_compare_unique_array_ex__compare);

    _rb_tree_destroy(pt_dest);
}

/*
 * test _rb_tree_destroy
 */
UT_CASE_DEFINATION(_rb_tree_destroy)
void test__rb_tree_destroy__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_destroy(NULL));
}

void test__rb_tree_destroy__non_created(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_destroy(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_destroy__created(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_destroy__inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_assign
 */
UT_CASE_DEFINATION(_rb_tree_assign)
void test__rb_tree_assign__null_dest(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_assign(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_assign__null_src(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_assign(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_assign__non_created_dest(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");

    _rb_tree_init(pt_src, NULL);
    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_assign(pt_dest, pt_src));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__non_init_src(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");

    _rb_tree_init(pt_src, NULL);
    _rb_tree_init(pt_dest, NULL);
    pt_src->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_assign(pt_dest, pt_src));
    pt_src->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("double");

    _rb_tree_init(pt_src, NULL);
    _rb_tree_init(pt_dest, NULL);
    expect_assert_failure(_rb_tree_assign(pt_dest, pt_src));

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__empty_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");

    _rb_tree_init(pt_src, NULL);
    _rb_tree_init(pt_dest, NULL);
    _rb_tree_assign(pt_dest, pt_src);
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__non_empty_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_src, NULL);
    _rb_tree_init(pt_dest, NULL);
    _rb_tree_insert_unique(pt_dest, &elem);
    _rb_tree_assign(pt_dest, pt_src);
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__non_empty_non_empty_less(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_src, NULL);
    _rb_tree_insert_unique(pt_src, &elem);
    elem = 222;
    _rb_tree_insert_unique(pt_src, &elem);
    _rb_tree_init(pt_dest, NULL);
    elem = 897;
    _rb_tree_insert_unique(pt_dest, &elem);
    _rb_tree_assign(pt_dest, pt_src);
    assert_true(_rb_tree_size(pt_dest) == 2);

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__non_empty_non_empty_size_equal(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_src, NULL);
    _rb_tree_insert_unique(pt_src, &elem);
    _rb_tree_init(pt_dest, NULL);
    elem = 334;
    _rb_tree_insert_unique(pt_dest, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_dest)) == 334);
    _rb_tree_assign(pt_dest, pt_src);
    assert_true(_rb_tree_size(pt_dest) == 1);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_dest)) == 9);

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__non_empty_non_empty_equal(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_src, NULL);
    _rb_tree_insert_unique(pt_src, &elem);
    _rb_tree_init(pt_dest, NULL);
    _rb_tree_insert_unique(pt_dest, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_dest)) == 9);
    _rb_tree_assign(pt_dest, pt_src);
    assert_true(_rb_tree_size(pt_dest) == 1);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_dest)) == 9);

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__non_empty_non_empty_greater(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_src, NULL);
    _rb_tree_insert_unique(pt_src, &elem);
    _rb_tree_init(pt_dest, NULL);
    elem = 876;
    _rb_tree_insert_unique(pt_dest, &elem);
    elem = 333;
    _rb_tree_insert_unique(pt_dest, &elem);
    _rb_tree_assign(pt_dest, pt_src);
    assert_true(_rb_tree_size(pt_dest) == 1);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_dest)) == 9);

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_assign__empty_non_empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_src, NULL);
    _rb_tree_insert_unique(pt_src, &elem);
    _rb_tree_init(pt_dest, NULL);
    _rb_tree_assign(pt_dest, pt_src);
    assert_true(_rb_tree_size(pt_dest) == 1);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_dest)) == 9);

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

/*
 * test _rb_tree_size
 */
UT_CASE_DEFINATION(_rb_tree_size)
void test__rb_tree_size__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_size(NULL));
}

void test__rb_tree_size__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_size(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_size__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_size(pt_rb_tree) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_size__non_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    assert_true(_rb_tree_size(pt_rb_tree) == 1);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_emtpy
 */
UT_CASE_DEFINATION(_rb_tree_empty)
void test__rb_tree_empty__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_empty(NULL));
}

void test__rb_tree_empty__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_empty(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_empty__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_empty(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_empty__non_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    assert_false(_rb_tree_empty(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_max_size
 */
UT_CASE_DEFINATION(_rb_tree_max_size)
void test__rb_tree_max_size__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_max_size(NULL));
}

void test__rb_tree_max_size__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_max_size(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_max_size__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_max_size(pt_rb_tree) > 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_max_size__non_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    assert_true(_rb_tree_max_size(pt_rb_tree) > 0);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_begin
 */
UT_CASE_DEFINATION(_rb_tree_begin)
void test__rb_tree_begin__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_begin(NULL));
}

void test__rb_tree_begin__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_begin(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_begin__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_iterator_equal(_rb_tree_begin(pt_rb_tree), _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_begin__non_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_rb_tree)) == 9);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_end
 */
UT_CASE_DEFINATION(_rb_tree_end)
void test__rb_tree_end__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_end(NULL));
}

void test__rb_tree_end__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_end(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_end__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_iterator_equal(_rb_tree_begin(pt_rb_tree), _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_end__non_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    it_iter = _rb_tree_end(pt_rb_tree);
    it_iter = _rb_tree_iterator_prev(it_iter);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 9);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_key_comp
 */
UT_CASE_DEFINATION(_rb_tree_key_comp)
void test__rb_tree_key_comp__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_key_comp(NULL));
}

void test__rb_tree_key_comp__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_key_comp(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_key_comp__default_key_comp(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_key_comp(pt_rb_tree) == _GET_RB_TREE_TYPE_LESS_FUNCTION(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void _test__rb_tree_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test__rb_tree_key_comp__user_define_key_comp(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, _test__rb_tree_key_comp__user_define_key_comp);

    assert_true(_rb_tree_key_comp(pt_rb_tree) == _test__rb_tree_key_comp__user_define_key_comp);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_find
 */
UT_CASE_DEFINATION(_rb_tree_find)
void test__rb_tree_find__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_find(NULL, &elem));
}

void test__rb_tree_find__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_find(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_find(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find__c_builtin_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = 2;
    it_iter = _rb_tree_find(pt_rb_tree, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 2);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find__c_builtin_not_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = 42;
    it_iter = _rb_tree_find(pt_rb_tree, &elem);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find__cstr_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _rb_tree_find(pt_rb_tree, pstr);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(it_iter), "ggg") == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_find__cstr_not_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _rb_tree_find(pt_rb_tree, pstr);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_find__libcstl_builtin_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _rb_tree_find(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 6);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_find__libcstl_builtin_not_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _rb_tree_find(pt_rb_tree, plist);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_find__user_define
{
    int n_elem;
}_test__rb_tree_find__user_define_t;
void test__rb_tree_find__user_define_find(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_find__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_find__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_find__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    it_iter = _rb_tree_find(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_find__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 8);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find__user_define_not_find(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_find__user_define_t");
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_find__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 78;
    it_iter = _rb_tree_find(pt_rb_tree, &elem);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_clear
 */
UT_CASE_DEFINATION(_rb_tree_clear)
void test__rb_tree_clear__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_clear(NULL));
}

void test__rb_tree_clear__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_clear(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_clear__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_empty(pt_rb_tree));
    _rb_tree_clear(pt_rb_tree);
    assert_true(_rb_tree_empty(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_clear__non_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 8;
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_insert_unique(pt_rb_tree, &elem);
    assert_false(_rb_tree_empty(pt_rb_tree));
    _rb_tree_clear(pt_rb_tree);
    assert_true(_rb_tree_empty(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_count
 */
UT_CASE_DEFINATION(_rb_tree_count)
void test__rb_tree_count__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_count(NULL, &elem));
}

void test__rb_tree_count__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_count(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_count__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_count(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_count__c_builtin_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = 1222;
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_count__c_builtin_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = 2;
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 1);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_count__c_builtin_n(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
        _rb_tree_insert_equal(pt_rb_tree, &i);
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = 2;
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 3);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_count__cstr_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "uuuuu");
    assert_true(_rb_tree_count(pt_rb_tree, pstr) == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_count__cstr_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_rb_tree_count(pt_rb_tree, pstr) == 1);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_count__cstr_n(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_rb_tree_count(pt_rb_tree, pstr) == 4);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_count__libcstl_builtin_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_rb_tree_count(pt_rb_tree, plist) == 0);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_count__libcstl_builtin_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_rb_tree_count(pt_rb_tree, plist) == 1);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_count__libcstl_builtin_n(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_equal(pt_rb_tree, plist);
        _rb_tree_insert_equal(pt_rb_tree, plist);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_rb_tree_count(pt_rb_tree, plist) == 3);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_count__user_define
{
    int n_elem;
}_test__rb_tree_count__user_define_t;
void test__rb_tree_count__user_define_0(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _test__rb_tree_count__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_count__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_count__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 88;
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_count__user_define_1(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_count__user_define_t");
    _test__rb_tree_count__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 1);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_count__user_define_n(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_count__user_define_t");
    _test__rb_tree_count__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 2);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_lower_bound
 */
UT_CASE_DEFINATION(_rb_tree_lower_bound)
void test__rb_tree_lower_bound__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_lower_bound(NULL, &elem));
}

void test__rb_tree_lower_bound__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_lower_bound(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_lower_bound__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_lower_bound(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_lower_bound__c_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = 2;
    it_iter = _rb_tree_lower_bound(pt_rb_tree, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 2);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_lower_bound__c_builtin_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = -8;
    it_iter = _rb_tree_lower_bound(pt_rb_tree, &elem);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_begin(pt_rb_tree)));
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_lower_bound__cstr_lower_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _rb_tree_lower_bound(pt_rb_tree, pstr);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(it_iter), "ggg") == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_lower_bound__cstr_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _rb_tree_lower_bound(pt_rb_tree, pstr);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_lower_bound__libcstl_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _rb_tree_lower_bound(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 6);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_lower_bound__libcstl_builtin_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _rb_tree_lower_bound(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 6);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_lower_bound__user_define
{
    int n_elem;
}_test__rb_tree_lower_bound__user_define_t;
void test__rb_tree_lower_bound__user_define_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_lower_bound__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_lower_bound__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_lower_bound__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    it_iter = _rb_tree_lower_bound(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_lower_bound__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 8);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_lower_bound__user_define_greater(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_lower_bound__user_define_t");
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_lower_bound__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 7;
    it_iter = _rb_tree_lower_bound(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_lower_bound__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 8);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_upper_bound
 */
UT_CASE_DEFINATION(_rb_tree_upper_bound)
void test__rb_tree_upper_bound__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_upper_bound(NULL, &elem));
}

void test__rb_tree_upper_bound__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_upper_bound(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_upper_bound__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_upper_bound(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_upper_bound__c_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = 2;
    it_iter = _rb_tree_upper_bound(pt_rb_tree, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 3);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_upper_bound__c_builtin_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = -8;
    it_iter = _rb_tree_upper_bound(pt_rb_tree, &elem);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_begin(pt_rb_tree)));
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_upper_bound__cstr_upper_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _rb_tree_upper_bound(pt_rb_tree, pstr);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(it_iter), "linux") == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_upper_bound__cstr_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _rb_tree_upper_bound(pt_rb_tree, pstr);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_upper_bound__libcstl_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _rb_tree_upper_bound(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 7);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_upper_bound__libcstl_builtin_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _rb_tree_upper_bound(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 6);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_upper_bound__user_define
{
    int n_elem;
}_test__rb_tree_upper_bound__user_define_t;
void test__rb_tree_upper_bound__user_define_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_upper_bound__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_upper_bound__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_upper_bound__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    it_iter = _rb_tree_upper_bound(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_upper_bound__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 9);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_upper_bound__user_define_greater(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_upper_bound__user_define_t");
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_upper_bound__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 7;
    it_iter = _rb_tree_upper_bound(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_upper_bound__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 8);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_equal_range
 */
UT_CASE_DEFINATION(_rb_tree_equal_range)
void test__rb_tree_equal_range__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_equal_range(NULL, &elem));
}

void test__rb_tree_equal_range__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_equal_range(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal_range__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_equal_range(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal_range__c_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    range_t r_range;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = 2;
    r_range = _rb_tree_equal_range(pt_rb_tree, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(r_range.it_begin) == 2);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(r_range.it_end) == 3);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal_range__c_builtin_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    range_t r_range;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = -8;
    r_range = _rb_tree_equal_range(pt_rb_tree, &elem);
    assert_true(_rb_tree_iterator_equal(r_range.it_begin, _rb_tree_begin(pt_rb_tree)));
    assert_true(_rb_tree_iterator_equal(r_range.it_end, _rb_tree_begin(pt_rb_tree)));
    assert_true(*(int*)_rb_tree_iterator_get_pointer(r_range.it_begin) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal_range__cstr_upper_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    range_t r_range;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    r_range = _rb_tree_equal_range(pt_rb_tree, pstr);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(r_range.it_begin), "ggg") == 0);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(r_range.it_end), "linux") == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_equal_range__cstr_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    range_t r_range;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "vvvv");
    r_range = _rb_tree_equal_range(pt_rb_tree, pstr);
    assert_true(_rb_tree_iterator_equal(r_range.it_begin, _rb_tree_end(pt_rb_tree)));
    assert_true(_rb_tree_iterator_equal(r_range.it_end, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_equal_range__libcstl_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _rb_tree_equal_range(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(r_range.it_end)) == 7);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_equal_range__libcstl_builtin_greater(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _rb_tree_equal_range(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(r_range.it_end)) == 6);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_equal_range__user_define
{
    int n_elem;
}_test__rb_tree_equal_range__user_define_t;
void test__rb_tree_equal_range__user_define_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    range_t r_range;
    _test__rb_tree_equal_range__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_equal_range__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_equal_range__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    r_range = _rb_tree_equal_range(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_equal_range__user_define_t*)_rb_tree_iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__rb_tree_equal_range__user_define_t*)_rb_tree_iterator_get_pointer(r_range.it_end))->n_elem == 9);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal_range__user_define_greater(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_equal_range__user_define_t");
    range_t r_range;
    _test__rb_tree_equal_range__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 7;
    r_range = _rb_tree_equal_range(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_equal_range__user_define_t*)_rb_tree_iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__rb_tree_equal_range__user_define_t*)_rb_tree_iterator_get_pointer(r_range.it_end))->n_elem == 8);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_equal
 */
UT_CASE_DEFINATION(_rb_tree_equal)
void test__rb_tree_equal__null_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_equal(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal__null_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_equal(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal__non_inited_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_equal(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__non_inited_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_equal(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("list_t<int>");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    expect_assert_failure(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__same_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_true(_rb_tree_equal(pt_rb_tree, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_equal__size_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("signed int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__size_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__size_equal_0(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    assert_true(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__size_equal_elem_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

static void _test__rb_tree_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_equal__compare_not_equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, _test__rb_tree_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_equal__equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_not_equal
 */
UT_CASE_DEFINATION(_rb_tree_not_equal)
void test__rb_tree_not_equal__null_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_not_equal(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_not_equal__null_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_not_equal(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_not_equal__non_inited_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_not_equal(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__non_inited_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_not_equal(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("list_t<int>");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    expect_assert_failure(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__same_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_false(_rb_tree_not_equal(pt_rb_tree, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_not_equal__size_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("signed int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__size_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__size_equal_0(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    assert_false(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

static void _test__rb_tree_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_not_equal__compare_not_equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, _test__rb_tree_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_not_equal__equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_not_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_less
 */
UT_CASE_DEFINATION(_rb_tree_less)
void test__rb_tree_less__null_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_less(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_less__null_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_less(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_less__non_inited_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_less(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__non_inited_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_less(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("list_t<int>");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    expect_assert_failure(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__same_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_false(_rb_tree_less(pt_rb_tree, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_less__size_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("signed int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__size_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__size_equal_0(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    assert_false(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__size_equal_elem_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__size_equal_elem_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

static void _test__rb_tree_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_less__compare_less(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, _test__rb_tree_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less__equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_less(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_less_equal
 */
UT_CASE_DEFINATION(_rb_tree_less_equal)
void test__rb_tree_less_equal__null_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_less_equal(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_less_equal__null_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_less_equal(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_less_equal__non_inited_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_less_equal(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__non_inited_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_less_equal(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("list_t<int>");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    expect_assert_failure(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__same_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_true(_rb_tree_less_equal(pt_rb_tree, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_less_equal__size_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("signed int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__size_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__size_equal_0(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    assert_true(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

static void _test__rb_tree_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_less_equal__compare_less(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, _test__rb_tree_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_less_equal__equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_less_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_greater
 */
UT_CASE_DEFINATION(_rb_tree_greater)
void test__rb_tree_greater__null_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_greater(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_greater__null_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_greater(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_greater__non_inited_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_greater(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__non_inited_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_greater(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("list_t<int>");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    expect_assert_failure(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__same_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_false(_rb_tree_greater(pt_rb_tree, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_greater__size_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("signed int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__size_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__size_equal_0(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    assert_false(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__size_equal_elem_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__size_equal_elem_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

static void _test__rb_tree_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_greater__compare_less(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, _test__rb_tree_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater__equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_greater_equal
 */
UT_CASE_DEFINATION(_rb_tree_greater_equal)
void test__rb_tree_greater_equal__null_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_greater_equal(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_greater_equal__null_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_greater_equal(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_greater_equal__non_inited_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_greater_equal(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__non_inited_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_greater_equal(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("list_t<int>");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    expect_assert_failure(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__same_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_true(_rb_tree_greater_equal(pt_rb_tree, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_greater_equal__size_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("signed int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__size_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__size_equal_0(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    assert_true(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_false(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

static void _test__rb_tree_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_greater_equal__compare_less(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, _test__rb_tree_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_greater_equal__equal(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_first, &i);
        _rb_tree_insert_unique(pt_second, &i);
    }

    assert_true(_rb_tree_greater_equal(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_swap
 */
UT_CASE_DEFINATION(_rb_tree_swap)
void test__rb_tree_swap__null_first(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_swap(NULL, pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_swap__null_second(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_swap(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_swap__non_inited_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_swap(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_swap__non_inited_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_swap(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_swap__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("list_t<int>");

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);

    expect_assert_failure(_rb_tree_swap(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_swap__same_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_swap(pt_rb_tree, pt_rb_tree);
    assert_true(_rb_tree_empty(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_swap__0_swap_n(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_second, &i);
    }

    assert_true(_rb_tree_size(pt_first) == 0);
    assert_true(_rb_tree_size(pt_second) == 10);
    _rb_tree_swap(pt_first, pt_second);
    assert_true(_rb_tree_size(pt_first) == 10);
    assert_true(_rb_tree_size(pt_second) == 0);

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_swap__n_swap_0(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_first, &i);
    }

    assert_true(_rb_tree_size(pt_first) == 10);
    assert_true(_rb_tree_size(pt_second) == 0);
    _rb_tree_swap(pt_first, pt_second);
    assert_true(_rb_tree_size(pt_first) == 0);
    assert_true(_rb_tree_size(pt_second) == 10);

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_swap__n_swap_n(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_first, &i);
    }
    for(i = 100; i < 110; ++i)
    {
        _rb_tree_insert_equal(pt_second, &i);
    }

    assert_true(_rb_tree_size(pt_first) == 10);
    assert_true(_rb_tree_size(pt_second) == 10);
    assert_true(_rb_tree_less(pt_first, pt_second));
    _rb_tree_swap(pt_first, pt_second);
    assert_true(_rb_tree_size(pt_first) == 10);
    assert_true(_rb_tree_size(pt_second) == 10);
    assert_true(_rb_tree_greater(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_swap__m_swap_n(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, NULL);
    for(i = 0; i < 30; ++i)
    {
        _rb_tree_insert_equal(pt_first, &i);
    }
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_second, &i);
    }

    assert_true(_rb_tree_size(pt_first) == 30);
    assert_true(_rb_tree_size(pt_second) == 10);
    _rb_tree_swap(pt_first, pt_second);
    assert_true(_rb_tree_size(pt_first) == 10);
    assert_true(_rb_tree_size(pt_second) == 30);

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_insert_unique
 */
UT_CASE_DEFINATION(_rb_tree_insert_unique)
void test__rb_tree_insert_unique__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_insert_unique(NULL, &elem));
}

void test__rb_tree_insert_unique__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_insert_unique(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_unique__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_insert_unique(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_unique__c_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = 2;
    it_iter = _rb_tree_insert_unique(pt_rb_tree, &elem);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));
    assert_true(_rb_tree_size(pt_rb_tree) == 10);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_unique__c_builtin_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }

    elem = -8;
    it_iter = _rb_tree_insert_unique(pt_rb_tree, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == -8);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_unique__cstr_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _rb_tree_insert_unique(pt_rb_tree, pstr);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));
    assert_true(_rb_tree_size(pt_rb_tree) == 5);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_insert_unique__cstr_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_unique(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_unique(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _rb_tree_insert_unique(pt_rb_tree, pstr);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(_rb_tree_size(pt_rb_tree) == 6);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_insert_unique__libcstl_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _rb_tree_insert_unique(pt_rb_tree, plist);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));
    assert_true(_rb_tree_size(pt_rb_tree) == 10);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_insert_unique__libcstl_builtin_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _rb_tree_insert_unique(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _rb_tree_insert_unique(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 5);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_insert_unique__user_define
{
    int n_elem;
}_test__rb_tree_insert_unique__user_define_t;
void test__rb_tree_insert_unique__user_define_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_insert_unique__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_insert_unique__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_insert_unique__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    it_iter = _rb_tree_insert_unique(pt_rb_tree, &elem);
    assert_true(_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree)));
    assert_true(_rb_tree_size(pt_rb_tree) == 10);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_unique__user_define_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_insert_unique__user_define_t");
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_insert_unique__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _rb_tree_insert_unique(pt_rb_tree, &elem);
    }

    elem.n_elem = 7;
    it_iter = _rb_tree_insert_unique(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_insert_unique__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_insert_equal
 */
UT_CASE_DEFINATION(_rb_tree_insert_equal)
void test__rb_tree_insert_equal__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_insert_equal(NULL, &elem));
}

void test__rb_tree_insert_equal__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_insert_equal(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_equal__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_insert_equal(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_equal__c_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = 2;
    it_iter = _rb_tree_insert_equal(pt_rb_tree, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == 2);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 2);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_equal__c_builtin_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = -8;
    it_iter = _rb_tree_insert_equal(pt_rb_tree, &elem);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_iter) == -8);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_equal__cstr_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _rb_tree_insert_equal(pt_rb_tree, pstr);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(it_iter), "ggg") == 0);
    assert_true(_rb_tree_size(pt_rb_tree) == 6);
    assert_true(_rb_tree_count(pt_rb_tree, pstr) == 2);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_insert_equal__cstr_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _rb_tree_insert_equal(pt_rb_tree, pstr);
    assert_true(strcmp((char*)_rb_tree_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(_rb_tree_size(pt_rb_tree) == 6);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_insert_equal__libcstl_builtin_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _rb_tree_insert_equal(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 6);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);
    assert_true(_rb_tree_count(pt_rb_tree, plist) == 2);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_insert_equal__libcstl_builtin_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    _rb_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _rb_tree_insert_equal(pt_rb_tree, plist);
    assert_true(*(int*)list_front((list_t*)_rb_tree_iterator_get_pointer(it_iter)) == 5);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_insert_equal__user_define
{
    int n_elem;
}_test__rb_tree_insert_equal__user_define_t;
void test__rb_tree_insert_equal__user_define_equal(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_insert_equal__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_insert_equal__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_insert_equal__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    it_iter = _rb_tree_insert_equal(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_insert_equal__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 8);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 2);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_equal__user_define_not_equal(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_insert_equal__user_define_t");
    _rb_tree_iterator_t it_iter;
    _test__rb_tree_insert_equal__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 7;
    it_iter = _rb_tree_insert_equal(pt_rb_tree, &elem);
    assert_true(((_test__rb_tree_insert_equal__user_define_t*)_rb_tree_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(_rb_tree_size(pt_rb_tree) == 11);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_insert_unique_range
 */
UT_CASE_DEFINATION(_rb_tree_insert_unique_range)
void test__rb_tree_insert_unique_range__null_rb_tree(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_rb_tree_insert_unique_range(NULL, vector_begin(pvec), vector_end(pvec)));

    vector_destroy(pvec);
}

void test__rb_tree_insert_unique_range__non_inited(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    list_init(plist);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    expect_assert_failure(_rb_tree_insert_unique_range(pt_dest, it_begin, it_end));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

void test__rb_tree_insert_unique_range__invalid_begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    deque_init(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_begin._t_iteratortype = 4444;
    expect_assert_failure(_rb_tree_insert_unique_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__rb_tree_insert_unique_range__invalid_end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    slist_init(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_end._t_containertype = 2323;
    expect_assert_failure(_rb_tree_insert_unique_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__rb_tree_insert_unique_range__invalid_range(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 0;

    _rb_tree_init(pt_dest, NULL);
    set_init(pset);
    set_insert(pset, elem);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_rb_tree_insert_unique_range(pt_dest, it_end, it_begin));

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

void test__rb_tree_insert_unique_range__not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    multiset_init(pmset);

    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_rb_tree_insert_unique_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__rb_tree_insert_unique_range__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    hash_set_init(phset);

    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _rb_tree_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__rb_tree_insert_unique_range__non_empty_equal(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(phmset, i);
    }

    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__rb_tree_insert_unique_range__non_empty_dest_src_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    vector_t* pvec = create_vector(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    _rb_tree_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 15);

    _rb_tree_destroy(pt_dest);
    vector_destroy(pvec);
}

void test__rb_tree_insert_unique_range__non_empty_src_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 15; i < 25; ++i)
    {
        list_push_back(plist, i);
        list_push_back(plist, i);
    }

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    _rb_tree_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

static void _test__rb_tree_insert_unique_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_insert_unique_range__compare(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    set_init_ex(pset, _test__rb_tree_insert_unique_range__compare);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    _rb_tree_insert_unique_range(pt_dest, it_begin, it_end);

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

/*
 * test _rb_tree_insert_unique_array
 */
UT_CASE_DEFINATION(_rb_tree_insert_unique_array)
void test__rb_tree_insert_unique_array__null_rb_tree(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_rb_tree_insert_unique_array(NULL, an_array, 10));
}

void test__rb_tree_insert_unique_array__non_inited(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init(pt_dest, NULL);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_insert_unique_array(pt_dest, an_array, 10));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_unique_array__invalid_array(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init(pt_dest, NULL);

    expect_assert_failure(_rb_tree_insert_unique_array(pt_dest, NULL, 10));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_unique_array__empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init(pt_dest, NULL);

    _rb_tree_insert_unique_array(pt_dest, an_array, 0);
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_unique_array__non_empty_equal(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        an_array[i - 10] = i;
    }

    _rb_tree_insert_unique_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_unique_array__non_empty_dest_src_dup(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        an_array[i - 5] = i;
    }

    _rb_tree_insert_unique_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 15);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_unique_array__non_empty_src_dup(void** state)
{
    int an_array[20] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for (i = 0; i < 20; i += 2)
    {
        an_array[i] = i + 15;
        an_array[i + 1] = i + 15;
    }

    _rb_tree_insert_unique_array(pt_dest, an_array, 20);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_unique_array__cstr(void** state)
{
    const char* as_array[] = {
        "Linux", "Windows", "Mac", "FreeBSD", "UNIX"
    };
    _rb_tree_t* pt_dest = _create_rb_tree("char*");

    _rb_tree_init(pt_dest, NULL);

    _rb_tree_insert_unique_array(pt_dest, as_array, 5);
    assert_true(_rb_tree_size(pt_dest) == 5);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_unique_array__cstl(void** state)
{
    size_t i = 0;
    vector_t* apvec_array[10] = {NULL};
    _rb_tree_t* pt_dest = _create_rb_tree("vector_t<int>");
    _rb_tree_iterator_t it;

    _rb_tree_init(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        apvec_array[i] = create_vector(int);
        vector_init_elem(apvec_array[i], i, i);
    }
    _rb_tree_insert_unique_array(pt_dest, apvec_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 10);
    for (it = _rb_tree_begin(pt_dest), i = 0; 
         !_rb_tree_iterator_equal(it, _rb_tree_end(pt_dest)); 
         it = _rb_tree_iterator_next(it), ++i) {
        assert_true(vector_equal(_rb_tree_iterator_get_pointer(it), apvec_array[i]));
    }

    _rb_tree_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        vector_destroy(apvec_array[i]);
    }
}

typedef struct _test__rb_tree_insert_unique_array__user_define {
    int n_elem;
}_test__rb_tree_insert_unique_array__user_define_t;
void _test__rb_tree_insert_unique_array__user_define_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = ((_test__rb_tree_insert_unique_array__user_define_t*)cpv_first)->n_elem <
           ((_test__rb_tree_insert_unique_array__user_define_t*)cpv_second)->n_elem ? true : false;
}
void test__rb_tree_insert_unique_array__user_define(void** state)
{
    size_t i = 0;
    _test__rb_tree_insert_unique_array__user_define_t* apt_array[10] = {NULL};
    _rb_tree_t* pt_dest = NULL;
    _rb_tree_iterator_t it;

    type_register(_test__rb_tree_insert_unique_array__user_define_t,
        NULL, NULL, _test__rb_tree_insert_unique_array__user_define_less, NULL);
    pt_dest = _create_rb_tree("_test__rb_tree_insert_unique_array__user_define_t");
    _rb_tree_init(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test__rb_tree_insert_unique_array__user_define_t));
        apt_array[i]->n_elem = i;
    }
    _rb_tree_insert_unique_array(pt_dest, apt_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 10);
    for (it = _rb_tree_begin(pt_dest), i = 0;
         !_rb_tree_iterator_equal(it, _rb_tree_end(pt_dest));
         it = _rb_tree_iterator_next(it), ++i) {
        assert_true(((_test__rb_tree_insert_unique_array__user_define_t*)_rb_tree_iterator_get_pointer(it))->n_elem ==
            apt_array[i]->n_elem);
    }

    _rb_tree_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test _rb_tree_insert_equal_range
 */
UT_CASE_DEFINATION(_rb_tree_insert_equal_range)
void test__rb_tree_insert_equal_range__null_rb_tree(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_rb_tree_insert_equal_range(NULL, vector_begin(pvec), vector_end(pvec)));

    vector_destroy(pvec);
}

void test__rb_tree_insert_equal_range__non_inited(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    list_init(plist);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    expect_assert_failure(_rb_tree_insert_equal_range(pt_dest, it_begin, it_end));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

void test__rb_tree_insert_equal_range__invalid_begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    slist_init(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_containertype = 4444;
    expect_assert_failure(_rb_tree_insert_equal_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__rb_tree_insert_equal_range__invalid_end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    deque_init(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_iteratortype = 3333;
    expect_assert_failure(_rb_tree_insert_equal_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__rb_tree_insert_equal_range__invalid_range(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 0;

    _rb_tree_init(pt_dest, NULL);
    set_init(pset);
    set_insert(pset, elem);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_rb_tree_insert_equal_range(pt_dest, it_end, it_begin));

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

void test__rb_tree_insert_equal_range__not_same_type(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    multiset_init(pmset);

    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_rb_tree_insert_equal_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__rb_tree_insert_equal_range__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    hash_set_init(phset);

    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _rb_tree_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__rb_tree_insert_equal_range__non_empty_equal(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(phmset, i);
    }

    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _rb_tree_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__rb_tree_insert_equal_range__non_empty_dest_src_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    vector_t* pvec = create_vector(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    _rb_tree_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
    vector_destroy(pvec);
}

void test__rb_tree_insert_equal_range__non_empty_src_dup(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 15; i < 25; ++i)
    {
        list_push_back(plist, i);
        list_push_back(plist, i);
    }

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    _rb_tree_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 30);

    _rb_tree_destroy(pt_dest);
    list_destroy(plist);
}

static void _test__rb_tree_insert_equal_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__rb_tree_insert_equal_range__compare(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);
    set_init_ex(pset, _test__rb_tree_insert_equal_range__compare);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    _rb_tree_insert_equal_range(pt_dest, it_begin, it_end);

    _rb_tree_destroy(pt_dest);
    set_destroy(pset);
}

/*
 * test _rb_tree_insert_equal_array
 */
UT_CASE_DEFINATION(_rb_tree_insert_equal_array)
void test__rb_tree_insert_equal_array__null_rb_tree(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_rb_tree_insert_equal_array(NULL, an_array, 10));
}

void test__rb_tree_insert_equal_array__non_inited(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init(pt_dest, NULL);

    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_insert_equal_array(pt_dest, an_array, 10));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_equal_array__invalid_array(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init(pt_dest, NULL);

    expect_assert_failure(_rb_tree_insert_equal_array(pt_dest, NULL, 10));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_equal_array__empty(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");

    _rb_tree_init(pt_dest, NULL);

    _rb_tree_insert_equal_array(pt_dest, an_array, 0);
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_equal_array__non_empty_equal(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        an_array[i - 10] = i;
    }

    _rb_tree_insert_equal_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_equal_array__non_empty_dest_src_dup(void** state)
{
    int an_array[10] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        an_array[i - 5] = i;
    }

    _rb_tree_insert_equal_array(pt_dest, an_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 20);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_equal_array__non_empty_src_dup(void** state)
{
    int an_array[20] = {0};
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }
    for (i = 0; i < 20; i += 2)
    {
        an_array[i] = i + 5;
        an_array[i + 1] = i + 5;
    }

    _rb_tree_insert_equal_array(pt_dest, an_array, 20);
    assert_true(_rb_tree_size(pt_dest) == 30);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_equal_array__cstr(void** state)
{
    const char* as_array[] = {
        "Linux", "Windows", "Mac", "FreeBSD", "UNIX"
    };
    _rb_tree_t* pt_dest = _create_rb_tree("char*");

    _rb_tree_init(pt_dest, NULL);

    _rb_tree_insert_equal_array(pt_dest, as_array, 5);
    assert_true(_rb_tree_size(pt_dest) == 5);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_insert_equal_array__cstl(void** state)
{
    size_t i = 0;
    vector_t* apvec_array[10] = {NULL};
    _rb_tree_t* pt_dest = _create_rb_tree("vector_t<int>");
    _rb_tree_iterator_t it;

    _rb_tree_init(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        apvec_array[i] = create_vector(int);
        vector_init_elem(apvec_array[i], i, i);
    }
    _rb_tree_insert_equal_array(pt_dest, apvec_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 10);
    for (it = _rb_tree_begin(pt_dest), i = 0; 
         !_rb_tree_iterator_equal(it, _rb_tree_end(pt_dest)); 
         it = _rb_tree_iterator_next(it), ++i) {
        assert_true(vector_equal(_rb_tree_iterator_get_pointer(it), apvec_array[i]));
    }

    _rb_tree_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        vector_destroy(apvec_array[i]);
    }
}

typedef struct _test__rb_tree_insert_equal_array__user_define {
    int n_elem;
}_test__rb_tree_insert_equal_array__user_define_t;
void _test__rb_tree_insert_equal_array__user_define_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = ((_test__rb_tree_insert_equal_array__user_define_t*)cpv_first)->n_elem <
           ((_test__rb_tree_insert_equal_array__user_define_t*)cpv_second)->n_elem ? true : false;
}
void test__rb_tree_insert_equal_array__user_define(void** state)
{
    size_t i = 0;
    _test__rb_tree_insert_equal_array__user_define_t* apt_array[10] = {NULL};
    _rb_tree_t* pt_dest = NULL;
    _rb_tree_iterator_t it;

    type_register(_test__rb_tree_insert_equal_array__user_define_t,
        NULL, NULL, _test__rb_tree_insert_equal_array__user_define_less, NULL);
    pt_dest = _create_rb_tree("_test__rb_tree_insert_equal_array__user_define_t");
    _rb_tree_init(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test__rb_tree_insert_equal_array__user_define_t));
        apt_array[i]->n_elem = i;
    }
    _rb_tree_insert_equal_array(pt_dest, apt_array, 10);
    assert_true(_rb_tree_size(pt_dest) == 10);
    for (it = _rb_tree_begin(pt_dest), i = 0;
         !_rb_tree_iterator_equal(it, _rb_tree_end(pt_dest));
         it = _rb_tree_iterator_next(it), ++i) {
        assert_true(((_test__rb_tree_insert_equal_array__user_define_t*)_rb_tree_iterator_get_pointer(it))->n_elem ==
            apt_array[i]->n_elem);
    }

    _rb_tree_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test _rb_tree_erase_pos
 */
UT_CASE_DEFINATION(_rb_tree_erase_pos)
void test__rb_tree_erase_pos__null_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    expect_assert_failure(_rb_tree_erase_pos(NULL, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_pos__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_pos;
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_pos = _rb_tree_begin(pt_rb_tree);
    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_erase_pos(pt_rb_tree, it_pos));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_pos__invalid_pos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_pos;
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_pos = _rb_tree_begin(pt_rb_tree);
    it_pos._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(_rb_tree_erase_pos(pt_rb_tree, it_pos));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_pos__end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_pos;
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    it_pos = _rb_tree_end(pt_rb_tree);
    expect_assert_failure(_rb_tree_erase_pos(pt_rb_tree, it_pos));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_pos__begin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_pos;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    it_pos = _rb_tree_begin(pt_rb_tree);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_pos) == 0);
    _rb_tree_erase_pos(pt_rb_tree, it_pos);
    assert_true(_rb_tree_size(pt_rb_tree) == 9);
    it_pos = _rb_tree_begin(pt_rb_tree);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_pos) == 1);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_pos__middle(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_pos;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    i = 4;
    it_pos = _rb_tree_find(pt_rb_tree, &i);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_pos) == 4);
    _rb_tree_erase_pos(pt_rb_tree, it_pos);
    assert_true(_rb_tree_size(pt_rb_tree) == 9);
    it_pos = _rb_tree_find(pt_rb_tree, &i);
    assert_true(_rb_tree_iterator_equal(it_pos, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_pos__last(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_pos;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    it_pos = _rb_tree_iterator_prev(_rb_tree_end(pt_rb_tree));
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_pos) == 9);
    _rb_tree_erase_pos(pt_rb_tree, it_pos);
    assert_true(_rb_tree_size(pt_rb_tree) == 9);
    it_pos = _rb_tree_iterator_prev(_rb_tree_end(pt_rb_tree));
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_pos) == 8);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_pos__erase_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_pos;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &i);
    assert_true(_rb_tree_size(pt_rb_tree) == 1);
    it_pos = _rb_tree_begin(pt_rb_tree);
    _rb_tree_erase_pos(pt_rb_tree, it_pos);
    assert_true(_rb_tree_size(pt_rb_tree) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_erase_range
 */
UT_CASE_DEFINATION(_rb_tree_erase_range)
void test__rb_tree_erase_range__null_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_erase_range(NULL, _rb_tree_begin(pt_rb_tree), _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase_range__non_inited(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);

    it_begin = _rb_tree_begin(pt_dest);
    it_end = _rb_tree_end(pt_dest);
    pt_dest->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__invalid_begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);

    it_begin = _rb_tree_begin(pt_dest);
    it_end = _rb_tree_end(pt_dest);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_erase_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__invalid_end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);

    it_begin = _rb_tree_begin(pt_dest);
    it_end = _rb_tree_end(pt_dest);
    it_end._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_erase_range(pt_dest, it_begin, it_end));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__invalid_range(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;
    int elem = 0;

    _rb_tree_init(pt_dest, NULL);
    _rb_tree_insert_unique(pt_dest, &elem);

    it_begin = _rb_tree_begin(pt_dest);
    it_end = _rb_tree_end(pt_dest);
    expect_assert_failure(_rb_tree_erase_range(pt_dest, it_end, it_begin));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__empty(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;

    _rb_tree_init(pt_dest, NULL);

    it_begin = _rb_tree_begin(pt_dest);
    it_end = _rb_tree_end(pt_dest);
    _rb_tree_erase_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_empty(pt_dest));

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__begin(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }

    it_begin = _rb_tree_begin(pt_dest);
    it_end = _rb_tree_iterator_next(it_begin);
    _rb_tree_erase_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 9);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_begin(pt_dest)) == 1);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__middle(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }

    it_begin = _rb_tree_iterator_next(_rb_tree_begin(pt_dest));
    it_end = _rb_tree_iterator_next(it_begin);
    _rb_tree_erase_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 9);
    it_begin = _rb_tree_begin(pt_dest);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(it_begin) == 0);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_iterator_next(it_begin)) == 2);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__end(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }

    it_end = _rb_tree_end(pt_dest);
    it_begin = _rb_tree_iterator_prev(it_end);
    _rb_tree_erase_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 9);
    it_end = _rb_tree_end(pt_dest);
    assert_true(*(int*)_rb_tree_iterator_get_pointer(_rb_tree_iterator_prev(it_end)) == 8);

    _rb_tree_destroy(pt_dest);
}

void test__rb_tree_erase_range__all(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;
    int i = 0;

    _rb_tree_init(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_dest, &i);
    }

    it_begin = _rb_tree_begin(pt_dest);
    it_end = _rb_tree_end(pt_dest);
    _rb_tree_erase_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_size(pt_dest) == 0);

    _rb_tree_destroy(pt_dest);
}

/*
 * test _rb_tree_erase
 */
UT_CASE_DEFINATION(_rb_tree_erase)
void test__rb_tree_erase__null_rb_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_rb_tree_erase(NULL, &elem));
}

void test__rb_tree_erase__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_erase(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_erase(pt_rb_tree, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase__c_builtin_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = 24;
    assert_true(_rb_tree_erase(pt_rb_tree, &elem) == 0);
    assert_true(_rb_tree_size(pt_rb_tree) == 10);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase__c_builtin_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = 8;
    assert_true(_rb_tree_erase(pt_rb_tree, &elem) == 1);
    assert_true(_rb_tree_size(pt_rb_tree) == 9);
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase__c_builtin_n(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem;
    int i;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_equal(pt_rb_tree, &i);
        _rb_tree_insert_equal(pt_rb_tree, &i);
        _rb_tree_insert_equal(pt_rb_tree, &i);
    }

    elem = 8;
    assert_true(_rb_tree_erase(pt_rb_tree, &elem) == 3);
    assert_true(_rb_tree_size(pt_rb_tree) == 27);
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase__cstr_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "gggppgg");
    assert_true(_rb_tree_erase(pt_rb_tree, pstr) == 0);
    assert_true(_rb_tree_size(pt_rb_tree) == 5);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_erase__cstr_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_rb_tree_erase(pt_rb_tree, pstr) == 1);
    assert_true(_rb_tree_size(pt_rb_tree) == 4);
    assert_true(_rb_tree_count(pt_rb_tree, pstr) == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_erase__cstr_n(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    string_t* pstr = create_string();

    _rb_tree_init(pt_rb_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _rb_tree_insert_equal(pt_rb_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _rb_tree_insert_equal(pt_rb_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_rb_tree_erase(pt_rb_tree, pstr) == 3);
    assert_true(_rb_tree_size(pt_rb_tree) == 5);
    assert_true(_rb_tree_count(pt_rb_tree, pstr) == 0);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr);
}

void test__rb_tree_erase__libcstl_builtin_0(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_rb_tree_erase(pt_rb_tree, plist) == 0);
    assert_true(_rb_tree_size(pt_rb_tree) == 10);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_erase__libcstl_builtin_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_rb_tree_erase(pt_rb_tree, plist) == 1);
    assert_true(_rb_tree_size(pt_rb_tree) == 9);
    assert_true(_rb_tree_count(pt_rb_tree, plist) == 0);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

void test__rb_tree_erase__libcstl_builtin_n(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _rb_tree_insert_equal(pt_rb_tree, plist);
        _rb_tree_insert_equal(pt_rb_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_rb_tree_erase(pt_rb_tree, plist) == 2);
    assert_true(_rb_tree_size(pt_rb_tree) == 18);
    assert_true(_rb_tree_count(pt_rb_tree, plist) == 0);

    _rb_tree_destroy(pt_rb_tree);
    list_destroy(plist);
}

typedef struct _tag_test__rb_tree_erase__user_define
{
    int n_elem;
}_test__rb_tree_erase__user_define_t;
void test__rb_tree_erase__user_define_0(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _test__rb_tree_erase__user_define_t elem;
    int i = 0;

    type_register(_test__rb_tree_erase__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = _create_rb_tree("_test__rb_tree_erase__user_define_t");
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 86;
    assert_true(_rb_tree_erase(pt_rb_tree, &elem) == 0);
    assert_true(_rb_tree_size(pt_rb_tree) == 10);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase__user_define_1(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_erase__user_define_t");
    _test__rb_tree_insert_equal__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    assert_true(_rb_tree_erase(pt_rb_tree, &elem) == 1);
    assert_true(_rb_tree_size(pt_rb_tree) == 9);
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_erase__user_define_n(void** state)
{
    _rb_tree_t* pt_rb_tree =  _create_rb_tree("_test__rb_tree_erase__user_define_t");
    _test__rb_tree_insert_equal__user_define_t elem;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _rb_tree_insert_equal(pt_rb_tree, &elem);
        _rb_tree_insert_equal(pt_rb_tree, &elem);
        _rb_tree_insert_equal(pt_rb_tree, &elem);
    }

    elem.n_elem = 8;
    assert_true(_rb_tree_erase(pt_rb_tree, &elem) == 3);
    assert_true(_rb_tree_size(pt_rb_tree) == 27);
    assert_true(_rb_tree_count(pt_rb_tree, &elem) == 0);

    _rb_tree_destroy(pt_rb_tree);
}

