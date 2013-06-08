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
#include "cstl_rb_tree_aux.h"
#include "cstl_avl_tree_aux.h"
#include "cstl_set_aux.h"
#include "cstl/cdeque.h"

#include "ut_def.h"
#include "ut_cstl_multiset.h"

UT_SUIT_DEFINATION(cstl_multiset, multiset_init)

/*
 * test multiset_init
 */
UT_CASE_DEFINATION(multiset_init)
void test_multiset_init__null_multiset(void** state)
{
    expect_assert_failure(multiset_init(NULL));
}

void test_multiset_init__non_created(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_init__null_compare(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init(pt_multiset);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_multiset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_multiset->_t_tree));
#endif

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_init_ex
 */
UT_CASE_DEFINATION(multiset_init_ex)
void test_multiset_init_ex__null_multiset(void** state)
{
    expect_assert_failure(multiset_init_ex(NULL, NULL));
}

void test_multiset_init_ex__non_created(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init_ex(pt_multiset, NULL));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init_ex(pt_multiset, NULL));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_init_ex__null_compare(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_multiset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_multiset->_t_tree));
#endif

    multiset_destroy(pt_multiset);
}

static void _test_multiset_init_ex__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_init_ex__non_null_compare(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, _test_multiset_init_ex__non_null_compare);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_multiset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_multiset->_t_tree));
#endif
    assert_true(pt_multiset->_t_tree._t_compare == _test_multiset_init_ex__non_null_compare);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_init_copy
 */
UT_CASE_DEFINATION(multiset_init_copy)
void test_multiset_init_copy__null_dest(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_init_copy(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_init_copy__null_src(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    expect_assert_failure(multiset_init_copy(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_init_copy__non_created_dest(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);

    multiset_init_ex(pt_src, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy__non_inited_src(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);

    multiset_init_ex(pt_src, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy__not_same_type(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(double);

    multiset_init_ex(pt_src, NULL);
    expect_assert_failure(multiset_init_copy(pt_dest, pt_src));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy__empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(signed int);

    multiset_init_ex(pt_src, NULL);
    multiset_init_copy(pt_dest, pt_src);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy__non_empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(signed int);
    int elem = 100;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    multiset_init_copy(pt_dest, pt_src);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 1);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

static void _test_multiset_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_init_copy__non_null_compare(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(signed int);
    int i = 0;

    multiset_init_ex(pt_src, _test_multiset_init_copy__non_null_compare);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_src, i);
    }
    multiset_init_copy(pt_dest, pt_src);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 10);
    assert_true(pt_dest->_t_tree._t_compare == _test_multiset_init_copy__non_null_compare);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

/*
 * test multiset_init_copy_range
 */
UT_CASE_DEFINATION(multiset_init_copy_range)
void test_multiset_init_copy_range__null_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_init_copy_range(NULL, multiset_begin(pt_multiset), multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test_multiset_init_copy_range__non_created_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_t* pt_dest = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init_copy_range(pt_dest, multiset_begin(pt_multiset), multiset_end(pt_multiset)));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init_copy_range(pt_dest, multiset_begin(pt_multiset), multiset_end(pt_multiset)));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_range__invalid_begin(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(multiset_init_copy_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range__invalid_end(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    it_end._t_iteratortype = 44444;
    expect_assert_failure(multiset_init_copy_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range__invalid_range(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_init_copy_range(pt_dest, it_end, it_begin));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range__invalid_range_not_same_type(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(double);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_init_copy_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range__empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_init_copy_range(pt_dest, it_begin, it_end);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range__non_empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_init_copy_range(pt_dest, it_begin, it_end);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 1);
    assert_true(multiset_equal(pt_dest, pt_src));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range__other_container_range(void** state)
{
    multiset_t* pmset = create_multiset(int);
    deque_t* pdeq = create_deque(int);
    int i = 0;

    deque_init(pdeq);
    for (i = 0; i < 10; ++i) {
        deque_push_back(pdeq, i);
    }
    multiset_init_copy_range(pmset, deque_begin(pdeq), deque_end(pdeq));
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmset->_t_tree));
#endif
    assert_true(multiset_size(pmset) == 10);

    multiset_destroy(pmset);
    deque_destroy(pdeq);
}

void test_multiset_init_copy_range__other_container_range_dup(void** state)
{
    multiset_t* pmset = create_multiset(int);
    deque_t* pdeq = create_deque(int);
    int i = 0;

    deque_init(pdeq);
    for (i = 0; i < 10; ++i) {
        deque_push_back(pdeq, i);
        deque_push_back(pdeq, i);
    }
    multiset_init_copy_range(pmset, deque_begin(pdeq), deque_end(pdeq));
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmset->_t_tree));
#endif
    assert_true(multiset_size(pmset) == 20);

    multiset_destroy(pmset);
    deque_destroy(pdeq);
}

/*
 * test multiset_init_copy_array
 */
UT_CASE_DEFINATION(multiset_init_copy_array)
void test_multiset_init_copy_array__null_multiset(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(multiset_init_copy_array(NULL, an_array, 10));
}

void test_multiset_init_copy_array__non_created_multiset(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init_copy_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init_copy_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array__invalid_array(void** state)
{
    multiset_t* pt_dest = create_multiset(int);

    expect_assert_failure(multiset_init_copy_array(pt_dest, NULL, 10));

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array__empty(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    multiset_init_copy_array(pt_dest, an_array, 0);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array__non_empty(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    multiset_init_copy_array(pt_dest, an_array, 10);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 10);

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);

    multiset_init_copy_array(pt_dest, an_array, 10);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 10);

    multiset_destroy(pt_dest);
}

/*
 * test multiset_init_copy_range_ex
 */
UT_CASE_DEFINATION(multiset_init_copy_range_ex)
void test_multiset_init_copy_range_ex__null_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_init_copy_range_ex(NULL, multiset_begin(pt_multiset), multiset_end(pt_multiset), NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_init_copy_range_ex__non_created_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_t* pt_dest = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init_copy_range_ex(pt_dest, multiset_begin(pt_multiset), multiset_end(pt_multiset), NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init_copy_range_ex(pt_dest, multiset_begin(pt_multiset), multiset_end(pt_multiset), NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_range_ex__invalid_begin(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(multiset_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range_ex__invalid_end(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    it_end._t_iteratortype = 33333;
    expect_assert_failure(multiset_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range_ex__invalid_range(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_init_copy_range_ex(pt_dest, it_end, it_begin, NULL));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range_ex__invalid_range_not_same_type(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(double);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range_ex__empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_src, NULL);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range_ex__non_empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 1);
    assert_true(multiset_equal(pt_dest, pt_src));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

static void _test__multiset_init_compare_range_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_init_copy_range_ex__compare(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_init_copy_range_ex(pt_dest, it_begin, it_end, _test__multiset_init_compare_range_ex__compare);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 1);
    assert_true(pt_dest->_t_tree._t_compare == _test__multiset_init_compare_range_ex__compare);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_init_copy_range_ex__other_container_range(void** state)
{
    multiset_t* pmset = create_multiset(int);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    for (i = 0; i < 10; ++i) {
        list_push_back(plist, i);
    }
    multiset_init_copy_range_ex(pmset, list_begin(plist), list_end(plist), NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmset->_t_tree));
#endif
    assert_true(multiset_size(pmset) == 10);

    multiset_destroy(pmset);
    list_destroy(plist);
}

void test_multiset_init_copy_range_ex__other_container_range_dup(void** state)
{
    multiset_t* pmset = create_multiset(int);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    for (i = 0; i < 10; ++i) {
        list_push_back(plist, i);
        list_push_back(plist, i);
    }
    multiset_init_copy_range_ex(pmset, list_begin(plist), list_end(plist), NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmset->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmset->_t_tree));
#endif
    assert_true(multiset_size(pmset) == 20);

    multiset_destroy(pmset);
    list_destroy(plist);
}

/*
 * test multiset_init_copy_array_ex
 */
UT_CASE_DEFINATION(multiset_init_copy_array_ex)
void test_multiset_init_copy_array_ex__null_multiset(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(multiset_init_copy_array_ex(NULL, an_array, 10, NULL));
}

void test_multiset_init_copy_array_ex__non_created_multiset(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_init_copy_array_ex(pt_dest, an_array, 10, NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_init_copy_array_ex(pt_dest, an_array, 10, NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array_ex__invalid_array(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    expect_assert_failure(multiset_init_copy_array_ex(pt_dest, NULL, 10, NULL));

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array_ex__empty(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    multiset_init_copy_array_ex(pt_dest, an_array, 0, NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array_ex__non_empty(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    multiset_init_copy_array_ex(pt_dest, an_array, 10, NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 10);

    multiset_destroy(pt_dest);
}

void test_multiset_init_copy_array_ex__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    multiset_init_copy_array_ex(pt_dest, an_array, 10, NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 10);

    multiset_destroy(pt_dest);
}

static void _test__multiset_init_compare_array_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_init_copy_array_ex__compare(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    multiset_init_copy_array_ex(pt_dest, an_array, 10, _test__multiset_init_compare_array_ex__compare);

#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(multiset_size(pt_dest) == 10);
    assert_true(pt_dest->_t_tree._t_compare == _test__multiset_init_compare_array_ex__compare);

    multiset_destroy(pt_dest);
}

/*
 * test multiset_destroy
 */
UT_CASE_DEFINATION(multiset_destroy)
void test_multiset_destroy__null_multiset(void** state)
{
    expect_assert_failure(multiset_destroy(NULL));
}

void test_multiset_destroy__non_created(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_destroy(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_destroy(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_destroy__created(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_destroy(pt_multiset);
}

void test_multiset_destroy__inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_assign
 */
UT_CASE_DEFINATION(multiset_assign)
void test_multiset_assign__null_dest(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    expect_assert_failure(multiset_assign(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_assign__null_src(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    expect_assert_failure(multiset_assign(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_assign__non_created_dest(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);

    multiset_init_ex(pt_src, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__non_init_src(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);

    multiset_init_ex(pt_src, NULL);
    multiset_init_ex(pt_dest, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__not_same_type(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(double);

    multiset_init_ex(pt_src, NULL);
    multiset_init_ex(pt_dest, NULL);
    expect_assert_failure(multiset_assign(pt_dest, pt_src));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__empty_empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);

    multiset_init_ex(pt_src, NULL);
    multiset_init_ex(pt_dest, NULL);
    multiset_assign(pt_dest, pt_src);
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__non_empty_empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_init_ex(pt_dest, NULL);
    multiset_insert(pt_dest, elem);
    multiset_assign(pt_dest, pt_src);
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__non_empty_non_empty_less(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    elem = 222;
    multiset_insert(pt_src, elem);
    multiset_init_ex(pt_dest, NULL);
    elem = 897;
    multiset_insert(pt_dest, elem);
    multiset_assign(pt_dest, pt_src);
    assert_true(multiset_size(pt_dest) == 2);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__non_empty_non_empty_size_equal(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    multiset_init_ex(pt_dest, NULL);
    elem = 334;
    multiset_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_dest)) == 334);
    multiset_assign(pt_dest, pt_src);
    assert_true(multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_dest)) == 9);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__non_empty_non_empty_equal(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    multiset_init_ex(pt_dest, NULL);
    multiset_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_dest)) == 9);
    multiset_assign(pt_dest, pt_src);
    assert_true(multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_dest)) == 9);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__non_empty_non_empty_greater(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    multiset_init_ex(pt_dest, NULL);
    elem = 876;
    multiset_insert(pt_dest, elem);
    elem = 333;
    multiset_insert(pt_dest, elem);
    multiset_assign(pt_dest, pt_src);
    assert_true(multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_dest)) == 9);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_assign__empty_non_empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);
    multiset_init_ex(pt_dest, NULL);
    multiset_assign(pt_dest, pt_src);
    assert_true(multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_dest)) == 9);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

/*
 * test multiset_size
 */
UT_CASE_DEFINATION(multiset_size)
void test_multiset_size__null_multiset(void** state)
{
    expect_assert_failure(multiset_size(NULL));
}

void test_multiset_size__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_size(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_size(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_size__empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    assert_true(multiset_size(pt_multiset) == 0);

    multiset_destroy(pt_multiset);
}

void test_multiset_size__non_empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    assert_true(multiset_size(pt_multiset) == 1);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_empty
 */
UT_CASE_DEFINATION(multiset_empty)
void test_multiset_empty__null_multiset(void** state)
{
    expect_assert_failure(multiset_empty(NULL));
}

void test_multiset_empty__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_empty(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_empty(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_empty__empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    assert_true(multiset_empty(pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_empty__non_empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    assert_false(multiset_empty(pt_multiset));

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_max_size
 */
UT_CASE_DEFINATION(multiset_max_size)
void test_multiset_max_size__null_multiset(void** state)
{
    expect_assert_failure(multiset_max_size(NULL));
}

void test_multiset_max_size__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_max_size(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_max_size(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_max_size__empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    assert_true(multiset_max_size(pt_multiset) > 0);

    multiset_destroy(pt_multiset);
}

void test_multiset_max_size__non_empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    assert_true(multiset_max_size(pt_multiset) > 0);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_begin
 */
UT_CASE_DEFINATION(multiset_begin)
void test_multiset_begin__null_multiset(void** state)
{
    expect_assert_failure(multiset_begin(NULL));
}

void test_multiset_begin__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_begin(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_begin(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_begin__empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    assert_true(_multiset_iterator_equal(multiset_begin(pt_multiset), multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test_multiset_begin__non_empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_multiset)) == 9);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_end
 */
UT_CASE_DEFINATION(multiset_end)
void test_multiset_end__null_multiset(void** state)
{
    expect_assert_failure(multiset_end(NULL));
}

void test_multiset_end__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_end(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_end(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_end__empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    assert_true(iterator_equal(multiset_begin(pt_multiset), multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test_multiset_end__non_empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_iter;
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);

    it_iter = multiset_end(pt_multiset);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_key_comp
 */
UT_CASE_DEFINATION(multiset_key_comp)
void test_multiset_key_comp__null_multiset(void** state)
{
    expect_assert_failure(multiset_key_comp(NULL));
}

void test_multiset_key_comp__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_key_comp(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_key_comp(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_key_comp__default_key_comp(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    assert_true(multiset_key_comp(pt_multiset) == _GET_SET_TYPE_LESS_FUNCTION(pt_multiset));

    multiset_destroy(pt_multiset);
}

void _test_multiset_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_multiset_key_comp__user_define_key_comp(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, _test_multiset_key_comp__user_define_key_comp);

    assert_true(multiset_key_comp(pt_multiset) == _test_multiset_key_comp__user_define_key_comp);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_clear
 */
UT_CASE_DEFINATION(multiset_clear)
void test_multiset_clear__null_multiset(void** state)
{
    expect_assert_failure(multiset_clear(NULL));
}

void test_multiset_clear__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_clear(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_clear(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_clear__empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    assert_true(multiset_empty(pt_multiset));
    multiset_clear(pt_multiset);
    assert_true(multiset_empty(pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_clear__non_empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    int elem = 8;
    multiset_init_ex(pt_multiset, NULL);

    multiset_insert(pt_multiset, elem);
    assert_false(multiset_empty(pt_multiset));
    multiset_clear(pt_multiset);
    assert_true(multiset_empty(pt_multiset));

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_equal
 */
UT_CASE_DEFINATION(multiset_equal)
void test_multiset_equal__null_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_equal(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_equal__null_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_equal(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_equal__non_inited_first(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__non_inited_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(multiset_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__not_same_type(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(list_t<int>);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    expect_assert_failure(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__same_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    assert_true(multiset_equal(pt_multiset, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_equal__size_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(signed int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__size_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__size_equal_0(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    assert_true(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__size_equal_elem_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

static void _test_multiset_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_equal__compare_not_equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, _test_multiset_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    expect_assert_failure(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_equal__equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

/*
 * test multiset_not_equal
 */
UT_CASE_DEFINATION(multiset_not_equal)
void test_multiset_not_equal__null_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_not_equal(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_not_equal__null_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_not_equal(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_not_equal__non_inited_first(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__non_inited_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__not_same_type(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(list_t<int>);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    expect_assert_failure(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__same_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    assert_false(multiset_not_equal(pt_multiset, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_not_equal__size_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(signed int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__size_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__size_equal_0(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    assert_false(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

static void _test_multiset_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_not_equal__compare_not_equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, _test_multiset_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    expect_assert_failure(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_not_equal__equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_not_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

/*
 * test multiset_less
 */
UT_CASE_DEFINATION(multiset_less)
void test_multiset_less__null_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_less(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_less__null_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_less(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_less__non_inited_first(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_less(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_less(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__non_inited_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_less(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_less(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__not_same_type(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(list_t<int>);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    expect_assert_failure(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__same_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    assert_false(multiset_less(pt_multiset, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_less__size_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(signed int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__size_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__size_equal_0(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    assert_false(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__size_equal_elem_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__size_equal_elem_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

static void _test_multiset_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_less__compare_less(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, _test_multiset_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    expect_assert_failure(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less__equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_less(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

/*
 * test multiset_less_equal
 */
UT_CASE_DEFINATION(multiset_less_equal)
void test_multiset_less_equal__null_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_less_equal(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_less_equal__null_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_less_equal(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_less_equal__non_inited_first(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__non_inited_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__not_same_type(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(list_t<int>);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    expect_assert_failure(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__same_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    assert_true(multiset_less_equal(pt_multiset, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_less_equal__size_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(signed int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__size_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__size_equal_0(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    assert_true(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

static void _test_multiset_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_less_equal__compare_less(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, _test_multiset_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    expect_assert_failure(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_less_equal__equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_less_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

/*
 * test multiset_greater
 */
UT_CASE_DEFINATION(multiset_greater)
void test_multiset_greater__null_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_greater(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_greater__null_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_greater(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_greater__non_inited_first(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_greater(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_greater(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__non_inited_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_greater(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_greater(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__not_same_type(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(list_t<int>);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    expect_assert_failure(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__same_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    assert_false(multiset_greater(pt_multiset, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_greater__size_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(signed int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__size_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__size_equal_0(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    assert_false(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__size_equal_elem_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__size_equal_elem_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

static void _test_multiset_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_greater__compare_less(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, _test_multiset_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    expect_assert_failure(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater__equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

/*
 * test multiset_greater_equal
 */
UT_CASE_DEFINATION(multiset_greater_equal)
void test_multiset_greater_equal__null_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_greater_equal(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_greater_equal__null_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_greater_equal(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_greater_equal__non_inited_first(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(multiset_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__non_inited_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__not_same_type(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(list_t<int>);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    expect_assert_failure(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__same_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    assert_true(multiset_greater_equal(pt_multiset, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_greater_equal__size_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(signed int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__size_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__size_equal_0(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    assert_true(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_false(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

static void _test_multiset_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_greater_equal__compare_less(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, _test_multiset_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    expect_assert_failure(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_greater_equal__equal(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_greater_equal(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

/*
 * test multiset_swap
 */
UT_CASE_DEFINATION(multiset_swap)
void test_multiset_swap__null_first(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_swap(NULL, pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_swap__null_second(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_swap(pt_multiset, NULL));

    multiset_destroy(pt_multiset);
}

void test_multiset_swap__non_inited_first(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_swap(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_swap(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_swap__non_inited_second(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 8;
    expect_assert_failure(multiset_swap(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_swap(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_swap__not_same_type(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(list_t<int>);

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);

    expect_assert_failure(multiset_swap(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_swap__same_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);

    multiset_init_ex(pt_multiset, NULL);
    multiset_swap(pt_multiset, pt_multiset);
    assert_true(multiset_empty(pt_multiset));

    multiset_destroy(pt_multiset);
}

void test_multiset_swap__0_swap_n(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i = 0;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_size(pt_first) == 0);
    assert_true(multiset_size(pt_second) == 10);
    multiset_swap(pt_first, pt_second);
    assert_true(multiset_size(pt_first) == 10);
    assert_true(multiset_size(pt_second) == 0);

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_swap__n_swap_0(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i = 0;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }

    assert_true(multiset_size(pt_first) == 10);
    assert_true(multiset_size(pt_second) == 0);
    multiset_swap(pt_first, pt_second);
    assert_true(multiset_size(pt_first) == 0);
    assert_true(multiset_size(pt_second) == 10);

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_swap__n_swap_n(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i = 0;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 100; i < 110; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_size(pt_first) == 10);
    assert_true(multiset_size(pt_second) == 10);
    assert_true(multiset_less(pt_first, pt_second));
    multiset_swap(pt_first, pt_second);
    assert_true(multiset_size(pt_first) == 10);
    assert_true(multiset_size(pt_second) == 10);
    assert_true(multiset_greater(pt_first, pt_second));

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

void test_multiset_swap__m_swap_n(void** state)
{
    multiset_t* pt_first = create_multiset(int);
    multiset_t* pt_second = create_multiset(int);
    int i = 0;

    multiset_init_ex(pt_first, NULL);
    multiset_init_ex(pt_second, NULL);
    for(i = 0; i < 30; ++i)
    {
        multiset_insert(pt_first, i);
    }
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_second, i);
    }

    assert_true(multiset_size(pt_first) == 30);
    assert_true(multiset_size(pt_second) == 10);
    multiset_swap(pt_first, pt_second);
    assert_true(multiset_size(pt_first) == 10);
    assert_true(multiset_size(pt_second) == 30);

    multiset_destroy(pt_first);
    multiset_destroy(pt_second);
}

/*
 * test multiset_insert_range
 */
UT_CASE_DEFINATION(multiset_insert_range)
void test_multiset_insert_range__null_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_insert_range(NULL, multiset_begin(pt_multiset), multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test_multiset_insert_range__non_inited(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__invalid_begin(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(multiset_insert_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__invalid_end(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    it_end._t_containertype = 3333;
    expect_assert_failure(multiset_insert_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__invalid_range(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int elem = 0;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);
    multiset_insert(pt_src, elem);

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_insert_range(pt_dest, it_end, it_begin));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__not_same_type(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(vector_t<int>);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    expect_assert_failure(multiset_insert_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__non_empty_equal(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }
    for(i = 10; i < 20; ++i)
    {
        multiset_insert(pt_src, i);
    }

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(multiset_size(pt_dest) == 20);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__non_empty_dest_src_dup(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }
    for(i = 5; i < 15; ++i)
    {
        multiset_insert(pt_src, i);
    }

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(multiset_size(pt_dest) == 20);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__non_empty_src_dup(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }
    for(i = 15; i < 25; ++i)
    {
        multiset_insert(pt_src, i);
        multiset_insert(pt_src, i);
    }

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(multiset_size(pt_dest) == 30);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

static void _test_multiset_insert_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multiset_insert_range__compare(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_t* pt_src = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);
    multiset_init_ex(pt_src, _test_multiset_insert_range__compare);

    it_begin = multiset_begin(pt_src);
    it_end = multiset_end(pt_src);
    multiset_insert_range(pt_dest, it_begin, it_end);

    multiset_destroy(pt_dest);
    multiset_destroy(pt_src);
}

void test_multiset_insert_range__other_container_range(void** state)
{
    multiset_t* pmset = create_multiset(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multiset_init(pmset);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    multiset_insert_range(pmset, vector_begin(pvec), vector_end(pvec));
    assert_true(multiset_size(pmset) == 10);

    multiset_destroy(pmset);
    vector_destroy(pvec);
}

/*
 * test multiset_insert_array
 */
UT_CASE_DEFINATION(multiset_insert_array)
void test_multiset_insert_array__null_multiset(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(multiset_insert_array(NULL, an_array, 10));
}

void test_multiset_insert_array__non_inited(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);

    multiset_init_ex(pt_dest, NULL);
#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multiset_insert_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_insert_array(pt_dest, an_array, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
}

void test_multiset_insert_array__invalid_array(void** state)
{
    multiset_t* pt_dest = create_multiset(int);

    multiset_init_ex(pt_dest, NULL);

    expect_assert_failure(multiset_insert_array(pt_dest, NULL, 10));

    multiset_destroy(pt_dest);
}

void test_multiset_insert_array__empty(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);

    multiset_init_ex(pt_dest, NULL);

    multiset_insert_array(pt_dest, an_array, 0);
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
}

void test_multiset_insert_array__non_empty_equal(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }
    for(i = 10; i < 20; ++i)
    {
        an_array[i - 10] = i;
    }

    multiset_insert_array(pt_dest, an_array, 10);
    assert_true(multiset_size(pt_dest) == 20);

    multiset_destroy(pt_dest);
}

void test_multiset_insert_array__non_empty_dest_src_dup(void** state)
{
    int an_array[10] = {0};
    multiset_t* pt_dest = create_multiset(int);
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }
    for(i = 5; i < 15; ++i)
    {
        an_array[i - 5] = i;
    }

    multiset_insert_array(pt_dest, an_array, 10);
    assert_true(multiset_size(pt_dest) == 20);

    multiset_destroy(pt_dest);
}

void test_multiset_insert_array__non_empty_src_dup(void** state)
{
    int an_array[20] = {0};
    multiset_t* pt_dest = create_multiset(int);
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }
    for (i = 0; i < 20; i += 2)
    {
        an_array[i] = i + 15;
        an_array[i + 1] = i + 15;
    }

    multiset_insert_array(pt_dest, an_array, 20);
    assert_true(multiset_size(pt_dest) == 30);

    multiset_destroy(pt_dest);
}

/*
 * test multiset_erase_pos
 */
UT_CASE_DEFINATION(multiset_erase_pos)
void test_multiset_erase_pos__null_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    expect_assert_failure(multiset_erase_pos(NULL, multiset_begin(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_pos__non_inited(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_pos;
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    it_pos = multiset_begin(pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(multiset_erase_pos(pt_multiset, it_pos));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_erase_pos(pt_multiset, it_pos));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_pos__invalid_pos(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_pos;
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    it_pos = multiset_begin(pt_multiset);
    it_pos._t_pos._t_treepos._pby_corepos = NULL;
    expect_assert_failure(multiset_erase_pos(pt_multiset, it_pos));

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_pos__end(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_pos;
    int elem = 9;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, elem);
    it_pos = multiset_end(pt_multiset);
    expect_assert_failure(multiset_erase_pos(pt_multiset, it_pos));

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_pos__begin(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_pos;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }
    it_pos = multiset_begin(pt_multiset);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    multiset_erase_pos(pt_multiset, it_pos);
    assert_true(multiset_size(pt_multiset) == 9);
    it_pos = multiset_begin(pt_multiset);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_pos__middle(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_pos;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }
    i = 4;
    it_pos = multiset_find(pt_multiset, i);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    multiset_erase_pos(pt_multiset, it_pos);
    assert_true(multiset_size(pt_multiset) == 9);
    it_pos = multiset_find(pt_multiset, i);
    assert_true(_multiset_iterator_equal(it_pos, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_pos__last(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_pos;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }
    it_pos = iterator_prev(multiset_end(pt_multiset));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    multiset_erase_pos(pt_multiset, it_pos);
    assert_true(multiset_size(pt_multiset) == 9);
    it_pos = iterator_prev(multiset_end(pt_multiset));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_pos__erase_empty(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_iterator_t it_pos;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, i);
    assert_true(multiset_size(pt_multiset) == 1);
    it_pos = multiset_begin(pt_multiset);
    multiset_erase_pos(pt_multiset, it_pos);
    assert_true(multiset_size(pt_multiset) == 0);

    multiset_destroy(pt_multiset);
}

/*
 * test multiset_erase_range
 */
UT_CASE_DEFINATION(multiset_erase_range)
void test_multiset_erase_range__null_multiset(void** state)
{
    multiset_t* pt_multiset = create_multiset(int);
    multiset_init_ex(pt_multiset, NULL);

    expect_assert_failure(multiset_erase_range(NULL, multiset_begin(pt_multiset), multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test_multiset_erase_range__non_inited(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);

    it_begin = multiset_begin(pt_dest);
    it_end = multiset_end(pt_dest);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(multiset_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multiset_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__invalid_begin(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);

    it_begin = multiset_begin(pt_dest);
    it_end = multiset_end(pt_dest);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(multiset_erase_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__invalid_end(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);

    it_begin = multiset_begin(pt_dest);
    it_end = multiset_end(pt_dest);
    it_end._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(multiset_erase_range(pt_dest, it_begin, it_end));

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__invalid_range(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int elem = 0;

    multiset_init_ex(pt_dest, NULL);
    multiset_insert(pt_dest, elem);

    it_begin = multiset_begin(pt_dest);
    it_end = multiset_end(pt_dest);
    expect_assert_failure(multiset_erase_range(pt_dest, it_end, it_begin));

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__empty(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;

    multiset_init_ex(pt_dest, NULL);

    it_begin = multiset_begin(pt_dest);
    it_end = multiset_end(pt_dest);
    multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(multiset_empty(pt_dest));

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__begin(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }

    it_begin = multiset_begin(pt_dest);
    it_end = iterator_next(it_begin);
    multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(multiset_size(pt_dest) == 9);
    assert_true(*(int*)iterator_get_pointer(multiset_begin(pt_dest)) == 1);

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__middle(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }

    it_begin = iterator_next(multiset_begin(pt_dest));
    it_end = iterator_next(it_begin);
    multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(multiset_size(pt_dest) == 9);
    it_begin = multiset_begin(pt_dest);
    assert_true(*(int*)iterator_get_pointer(it_begin) == 0);
    assert_true(*(int*)iterator_get_pointer(iterator_next(it_begin)) == 2);

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__end(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }

    it_end = multiset_end(pt_dest);
    it_begin = iterator_prev(it_end);
    multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(multiset_size(pt_dest) == 9);
    it_end = multiset_end(pt_dest);
    assert_true(*(int*)iterator_get_pointer(iterator_prev(it_end)) == 8);

    multiset_destroy(pt_dest);
}

void test_multiset_erase_range__all(void** state)
{
    multiset_t* pt_dest = create_multiset(int);
    multiset_iterator_t it_begin;
    multiset_iterator_t it_end;
    int i = 0;

    multiset_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_dest, i);
    }

    it_begin = multiset_begin(pt_dest);
    it_end = multiset_end(pt_dest);
    multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(multiset_size(pt_dest) == 0);

    multiset_destroy(pt_dest);
}

