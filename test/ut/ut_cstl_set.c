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
#include "cstl/cslist.h"
#include "cstl_vector_aux.h"
#include "cstl_rb_tree_aux.h"
#include "cstl_avl_tree_aux.h"
#include "cstl_set_aux.h"

#include "ut_def.h"
#include "ut_cstl_set.h"

UT_SUIT_DEFINATION(cstl_set, set_init)

/*
 * test set_init
 */
UT_CASE_DEFINATION(set_init)
void test_set_init__null_set(void** state)
{
    expect_assert_failure(set_init(NULL));
}

void test_set_init__non_created(void** state)
{
    set_t* pt_set = create_set(int);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_init__null_compare(void** state)
{
    set_t* pt_set = create_set(int);

    set_init(pt_set);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_set->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_set->_t_tree));
#endif

    set_destroy(pt_set);
}

/*
 * test set_init_ex
 */
UT_CASE_DEFINATION(set_init_ex)
void test_set_init_ex__null_set(void** state)
{
    expect_assert_failure(set_init_ex(NULL, NULL));
}

void test_set_init_ex__non_created(void** state)
{
    set_t* pt_set = create_set(int);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init_ex(pt_set, NULL));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init_ex(pt_set, NULL));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_init_ex__null_compare(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_set->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_set->_t_tree));
#endif

    set_destroy(pt_set);
}

static void _test_set_init_ex__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_init_ex__non_null_compare(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, _test_set_init_ex__non_null_compare);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_set->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_set->_t_tree));
#endif
    assert_true(pt_set->_t_tree._t_compare == _test_set_init_ex__non_null_compare);

    set_destroy(pt_set);
}

/*
 * test set_init_copy
 */
UT_CASE_DEFINATION(set_init_copy)
void test_set_init_copy__null_dest(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_init_copy(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_init_copy__null_src(void** state)
{
    set_t* pt_set = create_set(int);

    expect_assert_failure(set_init_copy(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_init_copy__non_created_dest(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);

    set_init_ex(pt_src, NULL);
#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy__non_inited_src(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);

    set_init_ex(pt_src, NULL);
#ifdef CSTL_SET_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy__not_same_type(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(double);

    set_init_ex(pt_src, NULL);
    expect_assert_failure(set_init_copy(pt_dest, pt_src));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy__empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(signed int);

    set_init_ex(pt_src, NULL);
    set_init_copy(pt_dest, pt_src);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy__non_empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(signed int);
    int elem = 100;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    set_init_copy(pt_dest, pt_src);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 1);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

static void _test_set_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_init_copy__non_null_compare(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(signed int);
    int i = 0;

    set_init_ex(pt_src, _test_set_init_copy__non_null_compare);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_src, i);
    }
    set_init_copy(pt_dest, pt_src);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 10);
    assert_true(pt_dest->_t_tree._t_compare == _test_set_init_copy__non_null_compare);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

/*
 * test set_init_copy_range
 */
UT_CASE_DEFINATION(set_init_copy_range)
void test_set_init_copy_range__null_set(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_init_copy_range(NULL, set_begin(pt_set), set_end(pt_set)));

    set_destroy(pt_set);
}

void test_set_init_copy_range__non_created_set(void** state)
{
    set_t* pt_set = create_set(int);
    set_t* pt_dest = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init_copy_range(pt_dest, set_begin(pt_set), set_end(pt_set)));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init_copy_range(pt_dest, set_begin(pt_set), set_end(pt_set)));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
    set_destroy(pt_dest);
}

void test_set_init_copy_range__invalid_begin(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(set_init_copy_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range__invalid_end(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    it_end._t_iteratortype = 44444;
    expect_assert_failure(set_init_copy_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range__invalid_range(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_init_copy_range(pt_dest, it_end, it_begin));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range__invalid_range_not_same_type(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(double);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_init_copy_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range__empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_init_copy_range(pt_dest, it_begin, it_end);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range__non_empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_init_copy_range(pt_dest, it_begin, it_end);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 1);
    assert_true(set_equal(pt_dest, pt_src));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range__other_container_range(void** state)
{
    set_t* pset = create_set(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    set_init_copy_range(pset, vector_begin(pvec), vector_end(pvec));
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pset->_t_tree));
#endif
    assert_true(set_size(pset) == 10);

    set_destroy(pset);
    vector_destroy(pvec);
}

void test_set_init_copy_range__other_container_range_dup(void** state)
{
    set_t* pset = create_set(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
        vector_push_back(pvec, i);
    }
    set_init_copy_range(pset, vector_begin(pvec), vector_end(pvec));
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pset->_t_tree));
#endif
    assert_true(set_size(pset) == 10);

    set_destroy(pset);
    vector_destroy(pvec);
}

/*
 * test set_init_copy_array
 */
UT_CASE_DEFINATION(set_init_copy_array)
void test_set_init_copy_array__null_set(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(set_init_copy_array(NULL, an_array, 10));
}

void test_set_init_copy_array__non_created_set(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init_copy_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init_copy_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
}

void test_set_init_copy_array__invalid_array(void** state)
{
    set_t* pt_dest = create_set(int);

    expect_assert_failure(set_init_copy_array(pt_dest, NULL, 10));

    set_destroy(pt_dest);
}

void test_set_init_copy_array__empty(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    set_init_copy_array(pt_dest, an_array, 0);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
}

void test_set_init_copy_array__non_empty(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    set_init_copy_array(pt_dest, an_array, 10);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 10);

    set_destroy(pt_dest);
}

void test_set_init_copy_array__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    set_init_copy_array(pt_dest, an_array, 10);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 1);

    set_destroy(pt_dest);
}

/*
 * test set_init_copy_range_ex
 */
UT_CASE_DEFINATION(set_init_copy_range_ex)
void test_set_init_copy_range_ex__null_set(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_init_copy_range_ex(NULL, set_begin(pt_set), set_end(pt_set), NULL));

    set_destroy(pt_set);
}

void test_set_init_copy_range_ex__non_created_set(void** state)
{
    set_t* pt_set = create_set(int);
    set_t* pt_dest = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init_copy_range_ex(pt_dest, set_begin(pt_set), set_end(pt_set), NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init_copy_range_ex(pt_dest, set_begin(pt_set), set_end(pt_set), NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
    set_destroy(pt_dest);
}

void test_set_init_copy_range_ex__invalid_begin(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(set_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range_ex__invalid_end(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    it_end._t_iteratortype = 33333;
    expect_assert_failure(set_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range_ex__invalid_range(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_init_copy_range_ex(pt_dest, it_end, it_begin, NULL));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range_ex__invalid_range_not_same_type(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(double);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range_ex__empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_src, NULL);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range_ex__non_empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 1);
    assert_true(set_equal(pt_dest, pt_src));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

static void _test__set_init_compare_range_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_init_copy_range_ex__compare(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_init_copy_range_ex(pt_dest, it_begin, it_end, _test__set_init_compare_range_ex__compare);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 1);
    assert_true(pt_dest->_t_tree._t_compare == _test__set_init_compare_range_ex__compare);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_init_copy_range_ex__other_container_range(void** state)
{
    set_t* pset = create_set(int);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    for (i = 0; i < 10; ++i) {
        list_push_front(plist, i);
    }
    set_init_copy_range_ex(pset, list_begin(plist), list_end(plist), NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pset->_t_tree));
#endif
    assert_true(set_size(pset) == 10);

    set_destroy(pset);
    list_destroy(plist);
}

void test_set_init_copy_range_ex__other_container_range_dup(void** state)
{
    set_t* pset = create_set(int);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    for (i = 0; i < 10; ++i) {
        list_push_front(plist, i);
        list_push_front(plist, i);
    }
    set_init_copy_range_ex(pset, list_begin(plist), list_end(plist), NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pset->_t_tree));
#endif
    assert_true(set_size(pset) == 10);

    set_destroy(pset);
    list_destroy(plist);
}

/*
 * test set_init_copy_array_ex
 */
UT_CASE_DEFINATION(set_init_copy_array_ex)
void test_set_init_copy_array_ex__null_set(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(set_init_copy_array_ex(NULL, an_array, 10, NULL));
}

void test_set_init_copy_array_ex__non_created_set(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(set_init_copy_array_ex(pt_dest, an_array, 10, NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_init_copy_array_ex(pt_dest, an_array, 10, NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
}

void test_set_init_copy_array_ex__invalid_array(void** state)
{
    set_t* pt_dest = create_set(int);

    expect_assert_failure(set_init_copy_array_ex(pt_dest, NULL, 10, NULL));

    set_destroy(pt_dest);
}

void test_set_init_copy_array_ex__empty(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    set_init_copy_array_ex(pt_dest, an_array, 0, NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
}

void test_set_init_copy_array_ex__non_empty(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    set_init_copy_array_ex(pt_dest, an_array, 10, NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 10);

    set_destroy(pt_dest);
}

void test_set_init_copy_array_ex__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    set_init_copy_array_ex(pt_dest, an_array, 10, NULL);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 1);

    set_destroy(pt_dest);
}

static void _test__set_init_compare_array_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_init_copy_array_ex__compare(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    set_init_copy_array_ex(pt_dest, an_array, 10, _test__set_init_compare_array_ex__compare);
#ifdef CSTL_SET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(set_size(pt_dest) == 1);
    assert_true(pt_dest->_t_tree._t_compare == _test__set_init_compare_array_ex__compare);

    set_destroy(pt_dest);
}

/*
 * test set_destroy
 */
UT_CASE_DEFINATION(set_destroy)
void test_set_destroy__null_set(void** state)
{
    expect_assert_failure(set_destroy(NULL));
}

void test_set_destroy__non_created(void** state)
{
    set_t* pt_set = create_set(int);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_destroy(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_destroy(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_destroy__created(void** state)
{
    set_t* pt_set = create_set(int);

    set_destroy(pt_set);
}

void test_set_destroy__inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    set_destroy(pt_set);
}

/*
 * test set_assign
 */
UT_CASE_DEFINATION(set_assign)
void test_set_assign__null_dest(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    expect_assert_failure(set_assign(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_assign__null_src(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    expect_assert_failure(set_assign(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_assign__non_created_dest(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);

    set_init_ex(pt_src, NULL);
#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__non_init_src(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);

    set_init_ex(pt_src, NULL);
    set_init_ex(pt_dest, NULL);
#ifdef CSTL_SET_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__not_same_type(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(double);

    set_init_ex(pt_src, NULL);
    set_init_ex(pt_dest, NULL);
    expect_assert_failure(set_assign(pt_dest, pt_src));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__empty_empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);

    set_init_ex(pt_src, NULL);
    set_init_ex(pt_dest, NULL);
    set_assign(pt_dest, pt_src);
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__non_empty_empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_init_ex(pt_dest, NULL);
    set_insert(pt_dest, elem);
    set_assign(pt_dest, pt_src);
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__non_empty_non_empty_less(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    elem = 222;
    set_insert(pt_src, elem);
    set_init_ex(pt_dest, NULL);
    elem = 897;
    set_insert(pt_dest, elem);
    set_assign(pt_dest, pt_src);
    assert_true(set_size(pt_dest) == 2);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__non_empty_non_empty_size_equal(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    set_init_ex(pt_dest, NULL);
    elem = 334;
    set_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(set_begin(pt_dest)) == 334);
    set_assign(pt_dest, pt_src);
    assert_true(set_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(set_begin(pt_dest)) == 9);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__non_empty_non_empty_equal(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    set_init_ex(pt_dest, NULL);
    set_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(set_begin(pt_dest)) == 9);
    set_assign(pt_dest, pt_src);
    assert_true(set_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(set_begin(pt_dest)) == 9);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__non_empty_non_empty_greater(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    set_init_ex(pt_dest, NULL);
    elem = 876;
    set_insert(pt_dest, elem);
    elem = 333;
    set_insert(pt_dest, elem);
    set_assign(pt_dest, pt_src);
    assert_true(set_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(set_begin(pt_dest)) == 9);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_assign__empty_non_empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    int elem = 9;

    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);
    set_init_ex(pt_dest, NULL);
    set_assign(pt_dest, pt_src);
    assert_true(set_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(set_begin(pt_dest)) == 9);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

/*
 * test set_size
 */
UT_CASE_DEFINATION(set_size)
void test_set_size__null_set(void** state)
{
    expect_assert_failure(set_size(NULL));
}

void test_set_size__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_size(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_size(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_size__empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    assert_true(set_size(pt_set) == 0);

    set_destroy(pt_set);
}

void test_set_size__non_empty(void** state)
{
    set_t* pt_set = create_set(int);
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    assert_true(set_size(pt_set) == 1);

    set_destroy(pt_set);
}

/*
 * test set_empty
 */
UT_CASE_DEFINATION(set_empty)
void test_set_empty__null_set(void** state)
{
    expect_assert_failure(set_empty(NULL));
}

void test_set_empty__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_empty(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_empty(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_empty__empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    assert_true(set_empty(pt_set));

    set_destroy(pt_set);
}

void test_set_empty__non_empty(void** state)
{
    set_t* pt_set = create_set(int);
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    assert_false(set_empty(pt_set));

    set_destroy(pt_set);
}

/*
 * test set_max_size
 */
UT_CASE_DEFINATION(set_max_size)
void test_set_max_size__null_set(void** state)
{
    expect_assert_failure(set_max_size(NULL));
}

void test_set_max_size__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_max_size(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_max_size(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_max_size__empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    assert_true(set_max_size(pt_set) > 0);

    set_destroy(pt_set);
}

void test_set_max_size__non_empty(void** state)
{
    set_t* pt_set = create_set(int);
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    assert_true(set_max_size(pt_set) > 0);

    set_destroy(pt_set);
}

/*
 * test set_begin
 */
UT_CASE_DEFINATION(set_begin)
void test_set_begin__null_set(void** state)
{
    expect_assert_failure(set_begin(NULL));
}

void test_set_begin__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_begin(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_begin(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_begin__empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    assert_true(_set_iterator_equal(set_begin(pt_set), set_end(pt_set)));

    set_destroy(pt_set);
}

void test_set_begin__non_empty(void** state)
{
    set_t* pt_set = create_set(int);
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    assert_true(*(int*)iterator_get_pointer(set_begin(pt_set)) == 9);

    set_destroy(pt_set);
}

/*
 * test set_end
 */
UT_CASE_DEFINATION(set_end)
void test_set_end__null_set(void** state)
{
    expect_assert_failure(set_end(NULL));
}

void test_set_end__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_end(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_end(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_end__empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    assert_true(iterator_equal(set_begin(pt_set), set_end(pt_set)));

    set_destroy(pt_set);
}

void test_set_end__non_empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_iter;
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);

    it_iter = set_end(pt_set);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    set_destroy(pt_set);
}

/*
 * test set_key_comp
 */
UT_CASE_DEFINATION(set_key_comp)
void test_set_key_comp__null_set(void** state)
{
    expect_assert_failure(set_key_comp(NULL));
}

void test_set_key_comp__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_key_comp(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_key_comp(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_key_comp__default_key_comp(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    assert_true(set_key_comp(pt_set) == _GET_SET_TYPE_LESS_FUNCTION(pt_set));

    set_destroy(pt_set);
}

void _test_set_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_set_key_comp__user_define_key_comp(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, _test_set_key_comp__user_define_key_comp);

    assert_true(set_key_comp(pt_set) == _test_set_key_comp__user_define_key_comp);

    set_destroy(pt_set);
}

/*
 * test set_clear
 */
UT_CASE_DEFINATION(set_clear)
void test_set_clear__null_set(void** state)
{
    expect_assert_failure(set_clear(NULL));
}

void test_set_clear__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_clear(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_clear(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_clear__empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    assert_true(set_empty(pt_set));
    set_clear(pt_set);
    assert_true(set_empty(pt_set));

    set_destroy(pt_set);
}

void test_set_clear__non_empty(void** state)
{
    set_t* pt_set = create_set(int);
    int elem = 8;
    set_init_ex(pt_set, NULL);

    set_insert(pt_set, elem);
    assert_false(set_empty(pt_set));
    set_clear(pt_set);
    assert_true(set_empty(pt_set));

    set_destroy(pt_set);
}

/*
 * test set_equal
 */
UT_CASE_DEFINATION(set_equal)
void test_set_equal__null_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_equal(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_equal__null_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_equal(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_equal__non_inited_first(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__non_inited_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__not_same_type(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(list_t<int>);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    expect_assert_failure(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__same_set(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    assert_true(set_equal(pt_set, pt_set));

    set_destroy(pt_set);
}

void test_set_equal__size_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(signed int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__size_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__size_equal_0(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    assert_true(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__size_equal_elem_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__size_equal_elem_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

static void _test_set_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_equal__compare_not_equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, _test_set_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    expect_assert_failure(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_equal__equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    assert_true(set_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

/*
 * test set_not_equal
 */
UT_CASE_DEFINATION(set_not_equal)
void test_set_not_equal__null_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_not_equal(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_not_equal__null_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_not_equal(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_not_equal__non_inited_first(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(set_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__non_inited_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__not_same_type(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(list_t<int>);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    expect_assert_failure(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__same_set(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    assert_false(set_not_equal(pt_set, pt_set));

    set_destroy(pt_set);
}

void test_set_not_equal__size_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(signed int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__size_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__size_equal_0(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    assert_false(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

static void _test_set_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_not_equal__compare_not_equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, _test_set_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    expect_assert_failure(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_not_equal__equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    assert_false(set_not_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

/*
 * test set_less
 */
UT_CASE_DEFINATION(set_less)
void test_set_less__null_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_less(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_less__null_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_less(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_less__non_inited_first(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_less(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_less(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__non_inited_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 4;
    expect_assert_failure(set_less(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_less(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__not_same_type(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(list_t<int>);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    expect_assert_failure(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__same_set(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    assert_false(set_less(pt_set, pt_set));

    set_destroy(pt_set);
}

void test_set_less__size_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(signed int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__size_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__size_equal_0(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    assert_false(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__size_equal_elem_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__size_equal_elem_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

static void _test_set_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_less__compare_less(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, _test_set_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    expect_assert_failure(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less__equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    assert_false(set_less(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

/*
 * test set_less_equal
 */
UT_CASE_DEFINATION(set_less_equal)
void test_set_less_equal__null_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_less_equal(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_less_equal__null_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_less_equal(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_less_equal__non_inited_first(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__non_inited_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__not_same_type(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(list_t<int>);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    expect_assert_failure(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__same_set(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    assert_true(set_less_equal(pt_set, pt_set));

    set_destroy(pt_set);
}

void test_set_less_equal__size_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(signed int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__size_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__size_equal_0(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    assert_true(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

static void _test_set_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_less_equal__compare_less(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, _test_set_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    expect_assert_failure(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_less_equal__equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    assert_true(set_less_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

/*
 * test set_greater
 */
UT_CASE_DEFINATION(set_greater)
void test_set_greater__null_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_greater(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_greater__null_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_greater(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_greater__non_inited_first(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_greater(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_greater(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__non_inited_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_greater(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_greater(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__not_same_type(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(list_t<int>);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    expect_assert_failure(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__same_set(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    assert_false(set_greater(pt_set, pt_set));

    set_destroy(pt_set);
}

void test_set_greater__size_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(signed int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__size_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__size_equal_0(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    assert_false(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__size_equal_elem_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__size_equal_elem_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

static void _test_set_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_greater__compare_less(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, _test_set_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    expect_assert_failure(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater__equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    assert_false(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

/*
 * test set_greater_equal
 */
UT_CASE_DEFINATION(set_greater_equal)
void test_set_greater_equal__null_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_greater_equal(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_greater_equal__null_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_greater_equal(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_greater_equal__non_inited_first(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__non_inited_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__not_same_type(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(list_t<int>);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    expect_assert_failure(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__same_set(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    assert_true(set_greater_equal(pt_set, pt_set));

    set_destroy(pt_set);
}

void test_set_greater_equal__size_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(signed int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__size_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__size_equal_0(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    assert_true(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_false(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

static void _test_set_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_greater_equal__compare_less(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, _test_set_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    expect_assert_failure(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_greater_equal__equal(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
        set_insert(pt_second, i);
    }

    assert_true(set_greater_equal(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

/*
 * test set_swap
 */
UT_CASE_DEFINATION(set_swap)
void test_set_swap__null_first(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_swap(NULL, pt_set));

    set_destroy(pt_set);
}

void test_set_swap__null_second(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_swap(pt_set, NULL));

    set_destroy(pt_set);
}

void test_set_swap__non_inited_first(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_swap(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_swap(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_swap__non_inited_second(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_swap(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_swap(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_swap__not_same_type(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(list_t<int>);

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);

    expect_assert_failure(set_swap(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_swap__same_set(void** state)
{
    set_t* pt_set = create_set(int);

    set_init_ex(pt_set, NULL);
    set_swap(pt_set, pt_set);
    assert_true(set_empty(pt_set));

    set_destroy(pt_set);
}

void test_set_swap__0_swap_n(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i = 0;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_size(pt_first) == 0);
    assert_true(set_size(pt_second) == 10);
    set_swap(pt_first, pt_second);
    assert_true(set_size(pt_first) == 10);
    assert_true(set_size(pt_second) == 0);

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_swap__n_swap_0(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i = 0;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }

    assert_true(set_size(pt_first) == 10);
    assert_true(set_size(pt_second) == 0);
    set_swap(pt_first, pt_second);
    assert_true(set_size(pt_first) == 0);
    assert_true(set_size(pt_second) == 10);

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_swap__n_swap_n(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i = 0;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 100; i < 110; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_size(pt_first) == 10);
    assert_true(set_size(pt_second) == 10);
    assert_true(set_less(pt_first, pt_second));
    set_swap(pt_first, pt_second);
    assert_true(set_size(pt_first) == 10);
    assert_true(set_size(pt_second) == 10);
    assert_true(set_greater(pt_first, pt_second));

    set_destroy(pt_first);
    set_destroy(pt_second);
}

void test_set_swap__m_swap_n(void** state)
{
    set_t* pt_first = create_set(int);
    set_t* pt_second = create_set(int);
    int i = 0;

    set_init_ex(pt_first, NULL);
    set_init_ex(pt_second, NULL);
    for(i = 0; i < 30; ++i)
    {
        set_insert(pt_first, i);
    }
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_second, i);
    }

    assert_true(set_size(pt_first) == 30);
    assert_true(set_size(pt_second) == 10);
    set_swap(pt_first, pt_second);
    assert_true(set_size(pt_first) == 10);
    assert_true(set_size(pt_second) == 30);

    set_destroy(pt_first);
    set_destroy(pt_second);
}

/*
 * test set_insert_range
 */
UT_CASE_DEFINATION(set_insert_range)
void test_set_insert_range__null_set(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_insert_range(NULL, set_begin(pt_set), set_end(pt_set)));

    set_destroy(pt_set);
}

void test_set_insert_range__non_inited(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 8;
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__invalid_begin(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(set_insert_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__invalid_end(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    it_end._t_containertype = 3333;
    expect_assert_failure(set_insert_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__invalid_range(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int elem = 0;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);
    set_insert(pt_src, elem);

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_insert_range(pt_dest, it_end, it_begin));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__not_same_type(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(vector_t<int>);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    expect_assert_failure(set_insert_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_insert_range(pt_dest, it_begin, it_end);
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__non_empty_equal(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int i = 0;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }
    for(i = 10; i < 20; ++i)
    {
        set_insert(pt_src, i);
    }

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_insert_range(pt_dest, it_begin, it_end);
    assert_true(set_size(pt_dest) == 20);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__non_empty_dest_src_dup(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int i = 0;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }
    for(i = 5; i < 15; ++i)
    {
        set_insert(pt_src, i);
    }

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_insert_range(pt_dest, it_begin, it_end);
    assert_true(set_size(pt_dest) == 15);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__non_empty_src_dup(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int i = 0;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }
    for(i = 15; i < 25; ++i)
    {
        set_insert(pt_src, i);
        set_insert(pt_src, i);
    }

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_insert_range(pt_dest, it_begin, it_end);
    assert_true(set_size(pt_dest) == 20);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

static void _test_set_insert_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_set_insert_range__compare(void** state)
{
    set_t* pt_dest = create_set(int);
    set_t* pt_src = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);
    set_init_ex(pt_src, _test_set_insert_range__compare);

    it_begin = set_begin(pt_src);
    it_end = set_end(pt_src);
    set_insert_range(pt_dest, it_begin, it_end);

    set_destroy(pt_dest);
    set_destroy(pt_src);
}

void test_set_insert_range__other_container_range(void** state)
{
    set_t* pset = create_set(int);
    slist_t* pslist = create_slist(int);
    int i = 0;

    set_init(pset);
    slist_init(pslist);
    for (i = 0; i < 10; ++i) {
        slist_push_front(pslist, i);
    }
    set_insert_range(pset, slist_begin(pslist), slist_end(pslist));
    assert_true(set_size(pset) == 10);

    set_destroy(pset);
    slist_destroy(pslist);
}

/*
 * test set_insert_array
 */
UT_CASE_DEFINATION(set_insert_array)
void test_set_insert_array__null_set(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(set_insert_array(NULL, an_array, 10));
}

void test_set_insert_array__non_inited(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    set_init_ex(pt_dest, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_insert_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_insert_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
}

void test_set_insert_array__invalid_array(void** state)
{
    set_t* pt_dest = create_set(int);

    set_init_ex(pt_dest, NULL);

    expect_assert_failure(set_insert_array(pt_dest, NULL, 10));

    set_destroy(pt_dest);
}

void test_set_insert_array__empty(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);

    set_init_ex(pt_dest, NULL);

    set_insert_array(pt_dest, an_array, 0);
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
}

void test_set_insert_array__non_empty_equal(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);
    int i = 0;

    set_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }
    for(i = 10; i < 20; ++i)
    {
        an_array[i - 10] = i;
    }

    set_insert_array(pt_dest, an_array, 10);
    assert_true(set_size(pt_dest) == 20);

    set_destroy(pt_dest);
}

void test_set_insert_array__non_empty_dest_src_dup(void** state)
{
    int an_array[10] = {0};
    set_t* pt_dest = create_set(int);
    int i = 0;

    set_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }
    for(i = 5; i < 15; ++i)
    {
        an_array[i - 5] = i;
    }

    set_insert_array(pt_dest, an_array, 10);
    assert_true(set_size(pt_dest) == 15);

    set_destroy(pt_dest);
}

void test_set_insert_array__non_empty_src_dup(void** state)
{
    int an_array[20] = {0};
    set_t* pt_dest = create_set(int);
    int i = 0;

    set_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }
    for (i = 0; i < 20; i += 2)
    {
        an_array[i] = i + 15;
        an_array[i + 1] = i + 15;
    }

    set_insert_array(pt_dest, an_array, 20);
    assert_true(set_size(pt_dest) == 20);

    set_destroy(pt_dest);
}

/*
 * test set_erase_pos
 */
UT_CASE_DEFINATION(set_erase_pos)
void test_set_erase_pos__null_set(void** state)
{
    set_t* pt_set = create_set(int);
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    expect_assert_failure(set_erase_pos(NULL, set_begin(pt_set)));

    set_destroy(pt_set);
}

void test_set_erase_pos__non_inited(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_pos;
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    it_pos = set_begin(pt_set);
#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_erase_pos(pt_set, it_pos));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_erase_pos(pt_set, it_pos));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test_set_erase_pos__invalid_pos(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_pos;
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    it_pos = set_begin(pt_set);
    it_pos._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(set_erase_pos(pt_set, it_pos));

    set_destroy(pt_set);
}

void test_set_erase_pos__end(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_pos;
    int elem = 9;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, elem);
    it_pos = set_end(pt_set);
    expect_assert_failure(set_erase_pos(pt_set, it_pos));

    set_destroy(pt_set);
}

void test_set_erase_pos__begin(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_pos;
    int i = 0;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }
    it_pos = set_begin(pt_set);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    set_erase_pos(pt_set, it_pos);
    assert_true(set_size(pt_set) == 9);
    it_pos = set_begin(pt_set);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);

    set_destroy(pt_set);
}

void test_set_erase_pos__middle(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_pos;
    int i = 0;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }
    i = 4;
    it_pos = set_find(pt_set, i);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    set_erase_pos(pt_set, it_pos);
    assert_true(set_size(pt_set) == 9);
    it_pos = set_find(pt_set, i);
    assert_true(_set_iterator_equal(it_pos, set_end(pt_set)));

    set_destroy(pt_set);
}

void test_set_erase_pos__last(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_pos;
    int i = 0;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }
    it_pos = iterator_prev(set_end(pt_set));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    set_erase_pos(pt_set, it_pos);
    assert_true(set_size(pt_set) == 9);
    it_pos = iterator_prev(set_end(pt_set));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);

    set_destroy(pt_set);
}

void test_set_erase_pos__erase_empty(void** state)
{
    set_t* pt_set = create_set(int);
    set_iterator_t it_pos;
    int i = 0;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, i);
    assert_true(set_size(pt_set) == 1);
    it_pos = set_begin(pt_set);
    set_erase_pos(pt_set, it_pos);
    assert_true(set_size(pt_set) == 0);

    set_destroy(pt_set);
}

/*
 * test set_erase_range
 */
UT_CASE_DEFINATION(set_erase_range)
void test_set_erase_range__null_set(void** state)
{
    set_t* pt_set = create_set(int);
    set_init_ex(pt_set, NULL);

    expect_assert_failure(set_erase_range(NULL, set_begin(pt_set), set_end(pt_set)));

    set_destroy(pt_set);
}

void test_set_erase_range__non_inited(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);

    it_begin = set_begin(pt_dest);
    it_end = set_end(pt_dest);
#ifdef CSTL_SET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(set_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(set_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_dest);
}

void test_set_erase_range__invalid_begin(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);

    it_begin = set_begin(pt_dest);
    it_end = set_end(pt_dest);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(set_erase_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
}

void test_set_erase_range__invalid_end(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);

    it_begin = set_begin(pt_dest);
    it_end = set_end(pt_dest);
    it_end._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(set_erase_range(pt_dest, it_begin, it_end));

    set_destroy(pt_dest);
}

void test_set_erase_range__invalid_range(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int elem = 0;

    set_init_ex(pt_dest, NULL);
    set_insert(pt_dest, elem);

    it_begin = set_begin(pt_dest);
    it_end = set_end(pt_dest);
    expect_assert_failure(set_erase_range(pt_dest, it_end, it_begin));

    set_destroy(pt_dest);
}

void test_set_erase_range__empty(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;

    set_init_ex(pt_dest, NULL);

    it_begin = set_begin(pt_dest);
    it_end = set_end(pt_dest);
    set_erase_range(pt_dest, it_begin, it_end);
    assert_true(set_empty(pt_dest));

    set_destroy(pt_dest);
}

void test_set_erase_range__begin(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int i = 0;

    set_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }

    it_begin = set_begin(pt_dest);
    it_end = iterator_next(it_begin);
    set_erase_range(pt_dest, it_begin, it_end);
    assert_true(set_size(pt_dest) == 9);
    assert_true(*(int*)iterator_get_pointer(set_begin(pt_dest)) == 1);

    set_destroy(pt_dest);
}

void test_set_erase_range__middle(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int i = 0;

    set_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }

    it_begin = iterator_next(set_begin(pt_dest));
    it_end = iterator_next(it_begin);
    set_erase_range(pt_dest, it_begin, it_end);
    assert_true(set_size(pt_dest) == 9);
    it_begin = set_begin(pt_dest);
    assert_true(*(int*)iterator_get_pointer(it_begin) == 0);
    assert_true(*(int*)iterator_get_pointer(iterator_next(it_begin)) == 2);

    set_destroy(pt_dest);
}

void test_set_erase_range__end(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int i = 0;

    set_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }

    it_end = set_end(pt_dest);
    it_begin = iterator_prev(it_end);
    set_erase_range(pt_dest, it_begin, it_end);
    assert_true(set_size(pt_dest) == 9);
    it_end = set_end(pt_dest);
    assert_true(*(int*)iterator_get_pointer(iterator_prev(it_end)) == 8);

    set_destroy(pt_dest);
}

void test_set_erase_range__all(void** state)
{
    set_t* pt_dest = create_set(int);
    set_iterator_t it_begin;
    set_iterator_t it_end;
    int i = 0;

    set_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_dest, i);
    }

    it_begin = set_begin(pt_dest);
    it_end = set_end(pt_dest);
    set_erase_range(pt_dest, it_begin, it_end);
    assert_true(set_size(pt_dest) == 0);

    set_destroy(pt_dest);
}

