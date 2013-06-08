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
#include "cstl_rb_tree_aux.h"
#include "cstl_avl_tree_aux.h"
#include "cstl_multimap_aux.h"

#include "ut_def.h"
#include "ut_cstl_multimap.h"

UT_SUIT_DEFINATION(cstl_multimap, multimap_init)

/*
 * test multimap_init
 */
UT_CASE_DEFINATION(multimap_init)
void test_multimap_init__null_multimap(void** state)
{
    expect_assert_failure(multimap_init(NULL));
}

void test_multimap_init__non_created(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_init__non_created_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    pt_multimap->_pair_temp._pv_first = (void*)0x9999;
    expect_assert_failure(multimap_init(pt_multimap));
    pt_multimap->_pair_temp._pv_first = NULL;

    multimap_destroy(pt_multimap);
}

void test_multimap_init__null_compare(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init(pt_multimap);
    assert_true(_pair_is_inited(&pt_multimap->_pair_temp));
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_multimap->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_multimap->_t_tree));
#endif

    multimap_destroy(pt_multimap);
}

/*
 * test multimap_init_ex
 */
UT_CASE_DEFINATION(multimap_init_ex)
void test_multimap_init_ex__null_multimap(void** state)
{
    expect_assert_failure(multimap_init_ex(NULL, NULL));
}

void test_multimap_init_ex__non_created(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init_ex(pt_multimap, NULL));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init_ex(pt_multimap, NULL));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_init_ex__non_created_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    pt_multimap->_pair_temp._pv_first = (void*)0x7777;
    expect_assert_failure(multimap_init_ex(pt_multimap, NULL));
    pt_multimap->_pair_temp._pv_first = NULL;

    multimap_destroy(pt_multimap);
}

void test_multimap_init_ex__null_compare(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_multimap->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_multimap->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_multimap->_pair_temp));

    multimap_destroy(pt_multimap);
}

static void _test_multimap_init_ex__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_init_ex__non_null_compare(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, _test_multimap_init_ex__non_null_compare);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_multimap->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_multimap->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_multimap->_pair_temp));
    assert_true(pt_multimap->_bfun_keycompare == _test_multimap_init_ex__non_null_compare);
    assert_true(pt_multimap->_pair_temp._bfun_mapkeycompare == _test_multimap_init_ex__non_null_compare);

    multimap_destroy(pt_multimap);
}

/*
 * test multimap_init_copy
 */
UT_CASE_DEFINATION(multimap_init_copy)
void test_multimap_init_copy__null_dest(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_init_copy(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_init_copy__null_src(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    expect_assert_failure(multimap_init_copy(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_init_copy__non_created_dest(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);

    multimap_init_ex(pt_src, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy__non_created_dest_pair(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);

    multimap_init_ex(pt_src, NULL);
    pt_dest->_pair_temp._pv_first = (void*)0x733;
    expect_assert_failure(multimap_init_copy(pt_dest, pt_src));
    pt_dest->_pair_temp._pv_first = NULL;

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy__non_inited_src(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);

    multimap_init_ex(pt_src, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy__non_inited_src_pair(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_src, NULL);
    pv_tmp = pt_src->_pair_temp._pv_first;
    pt_src->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_init_copy(pt_dest, pt_src));
    pt_src->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy__not_same_type(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(double, int);

    multimap_init_ex(pt_src, NULL);
    expect_assert_failure(multimap_init_copy(pt_dest, pt_src));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy__empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(signed int, int);

    multimap_init_ex(pt_src, NULL);
    multimap_init_copy(pt_dest, pt_src);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy__non_empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 100;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    multimap_init_copy(pt_dest, pt_src);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 1);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

static void _test_multimap_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_init_copy__non_null_compare(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    multimap_init_ex(pt_src, _test_multimap_init_copy__non_null_compare);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_src, pt_pair);
    }
    multimap_init_copy(pt_dest, pt_src);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 10);
    assert_true(pt_dest->_bfun_keycompare == _test_multimap_init_copy__non_null_compare);
    assert_true(pt_dest->_pair_temp._bfun_mapkeycompare == _test_multimap_init_copy__non_null_compare);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

/*
 * test multimap_init_copy_range
 */
UT_CASE_DEFINATION(multimap_init_copy_range)
void test_multimap_init_copy_range__null_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_init_copy_range(NULL, multimap_begin(pt_multimap), multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
}

void test_multimap_init_copy_range__non_created_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init_copy_range(pt_dest, multimap_begin(pt_multimap), multimap_end(pt_multimap)));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init_copy_range(pt_dest, multimap_begin(pt_multimap), multimap_end(pt_multimap)));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_range__non_created_multimap_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    pt_dest->_pair_temp._pv_first = (void*)0x8989;
    expect_assert_failure(multimap_init_copy_range(pt_dest, multimap_begin(pt_multimap), multimap_end(pt_multimap)));
    pt_dest->_pair_temp._pv_first = NULL;

    multimap_destroy(pt_multimap);
    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_range__invalid_begin(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    it_begin._t_containertype = 99999;
    expect_assert_failure(multimap_init_copy_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy_range__invalid_end(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    it_end._t_iteratortype = 44444;
    expect_assert_failure(multimap_init_copy_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy_range__invalid_range(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int elem = 9;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_init_copy_range(pt_dest, it_end, it_begin));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_init_copy_range__invalid_range_not_same_type(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(double, int);
    pair_t* ppair = create_pair(double, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(ppair, 10.9, 1);
    multimap_insert(pt_src, ppair);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_init_copy_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(ppair);
}

void test_multimap_init_copy_range__empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_init_copy_range(pt_dest, it_begin, it_end);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy_range__non_empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int elem = 9;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_init_copy_range(pt_dest, it_begin, it_end);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 1);
    assert_true(multimap_equal(pt_dest, pt_src));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_init_copy_range__other_container_range(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    multimap_init_copy_range(pmmap, vector_begin(pvec), vector_end(pvec));
    assert_true(multimap_size(pmmap) == 10);

    multimap_destroy(pmmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_multimap_init_copy_range__other_container_range_not_same_type(void** state)
{
    multimap_t* pmmap = create_multimap(int, double);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    expect_assert_failure(multimap_init_copy_range(pmmap, vector_begin(pvec), vector_end(pvec)));

    multimap_destroy(pmmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

/*
void test_multimap_init_copy_range__other_container_range_not_pair(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    expect_assert_failure(multimap_init_copy_range(pmmap, vector_begin(pvec), vector_end(pvec)));

    multimap_destroy(pmmap);
    vector_destroy(pvec);
}
*/

/*
 * test multimap_init_copy_array
 */
UT_CASE_DEFINATION(multimap_init_copy_array)
void test_multimap_init_copy_array__null_multimap(void** state)
{
    pair_t* appair[10] = {NULL};
    expect_assert_failure(multimap_init_copy_array(NULL, appair, 10));
}

void test_multimap_init_copy_array__non_created_multimap(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init_copy_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init_copy_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_array__non_created_multimap_pair(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    pt_dest->_pair_temp._pv_first = (void*)0x8989;
    expect_assert_failure(multimap_init_copy_array(pt_dest, appair, 10));
    pt_dest->_pair_temp._pv_first = NULL;

    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_array__invalid_array(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);

    expect_assert_failure(multimap_init_copy_array(pt_dest, NULL, 10));

    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_array__invalid_array_not_same_type(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, double);
        pair_init_elem(appair[i], i, i);
    }
    expect_assert_failure(multimap_init_copy_array(pt_dest, appair, 10));

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_init_copy_array__empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    multimap_init_copy_array(pt_dest, appair, 0);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_init_copy_array__non_empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    multimap_init_copy_array(pt_dest, appair, 10);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 10);

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_init_copy_array__non_empty_dup(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], 1, 1);
    }
    multimap_init_copy_array(pt_dest, appair, 10);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 10);

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

/*
void test_multimap_init_copy_array__array_not_pair(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    multimap_t* pmmap = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    expect_assert_failure(multimap_init_copy_array(pmmap, an_array, 10));

    multimap_destroy(pmmap);
}
*/

/*
 * test multimap_init_copy_range_ex
 */
UT_CASE_DEFINATION(multimap_init_copy_range_ex)
void test_multimap_init_copy_range_ex__null_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_init_copy_range_ex(NULL, multimap_begin(pt_multimap), multimap_end(pt_multimap), NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_init_copy_range_ex__non_created_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init_copy_range_ex(pt_dest, multimap_begin(pt_multimap), multimap_end(pt_multimap), NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init_copy_range_ex(pt_dest, multimap_begin(pt_multimap), multimap_end(pt_multimap), NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_range_ex__non_created_multimap_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    pt_dest->_pair_temp._pv_second = (void*)0x7383;
    expect_assert_failure(multimap_init_copy_range_ex(pt_dest, multimap_begin(pt_multimap), multimap_end(pt_multimap), NULL));
    pt_dest->_pair_temp._pv_second = NULL;

    multimap_destroy(pt_multimap);
    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_range_ex__invalid_begin(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    it_begin._t_containertype = 99999;
    expect_assert_failure(multimap_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy_range_ex__invalid_end(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    it_end._t_iteratortype = 33333;
    expect_assert_failure(multimap_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy_range_ex__invalid_range(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int elem = 9;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_init_copy_range_ex(pt_dest, it_end, it_begin, NULL));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_init_copy_range_ex__invalid_range_not_same_type(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(double, int);
    pair_t* ppair = create_pair(double, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(ppair, 10.3, 3);
    multimap_insert(pt_src, ppair);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(ppair);
}

void test_multimap_init_copy_range_ex__empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_src, NULL);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_init_copy_range_ex__non_empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int elem = 9;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 1);
    assert_true(multimap_equal(pt_dest, pt_src));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

static void _test__multimap_init_compare_range_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_init_copy_range_ex__compare(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int elem = 9;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_init_copy_range_ex(pt_dest, it_begin, it_end, _test__multimap_init_compare_range_ex__compare);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 1);
    assert_true(pt_dest->_bfun_keycompare == _test__multimap_init_compare_range_ex__compare);
    assert_true(pt_dest->_pair_temp._bfun_mapkeycompare == _test__multimap_init_compare_range_ex__compare);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_init_copy_range_ex__other_container_range(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    multimap_init_copy_range_ex(pmmap, vector_begin(pvec), vector_end(pvec), NULL);
    assert_true(multimap_size(pmmap) == 10);

    multimap_destroy(pmmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_multimap_init_copy_range_ex__other_container_range_not_same_type(void** state)
{
    multimap_t* pmmap = create_multimap(int, double);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    expect_assert_failure(multimap_init_copy_range_ex(pmmap, vector_begin(pvec), vector_end(pvec), NULL));

    multimap_destroy(pmmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

/*
void test_multimap_init_copy_range_ex__other_container_range_not_pair(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    expect_assert_failure(multimap_init_copy_range_ex(pmmap, vector_begin(pvec), vector_end(pvec), NULL));

    multimap_destroy(pmmap);
    vector_destroy(pvec);
}
*/

/*
 * test multimap_init_copy_array_ex
 */
UT_CASE_DEFINATION(multimap_init_copy_array_ex)
void test_multimap_init_copy_array_ex__null_multimap(void** state)
{
    pair_t* appair[10] = {NULL};
    expect_assert_failure(multimap_init_copy_array_ex(NULL, appair, 10, NULL));
}

void test_multimap_init_copy_array_ex__non_created_multimap(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_init_copy_array_ex(pt_dest, appair, 10, NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_init_copy_array_ex(pt_dest, appair, 10, NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_array_ex__non_created_multimap_pair(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    pt_dest->_pair_temp._pv_second = (void*)0x7383;
    expect_assert_failure(multimap_init_copy_array_ex(pt_dest, appair, 10, NULL));
    pt_dest->_pair_temp._pv_second = NULL;

    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_array_ex__invalid_array(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    expect_assert_failure(multimap_init_copy_array_ex(pt_dest, NULL, 10, NULL));
    multimap_destroy(pt_dest);
}

void test_multimap_init_copy_array_ex__invalid_array_not_same_type(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, double);
        pair_init_elem(appair[i], i, i);
    }
    expect_assert_failure(multimap_init_copy_array_ex(pt_dest, appair, 10, NULL));

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_init_copy_array_ex__empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    multimap_init_copy_array_ex(pt_dest, appair, 0, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_init_copy_array_ex__non_empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    multimap_init_copy_array_ex(pt_dest, appair, 10, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 10);

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_init_copy_array_ex__non_empty_dup(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], 1, 1);
    }
    multimap_init_copy_array_ex(pt_dest, appair, 10, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 10);

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

static void _test__multimap_init_compare_array_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_init_copy_array_ex__compare(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, 1);
    }
    multimap_init_copy_array_ex(pt_dest, appair, 10, _test__multimap_init_compare_array_ex__compare);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(multimap_size(pt_dest) == 10);
    assert_true(pt_dest->_bfun_keycompare == _test__multimap_init_compare_array_ex__compare);
    assert_true(pt_dest->_pair_temp._bfun_mapkeycompare == _test__multimap_init_compare_array_ex__compare);

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

/*
void test_multimap_init_copy_array_ex__array_not_pair(void** state)
{
    int an_array[10] = {0};
    multimap_t* pmmap = create_multimap(int, int);
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    expect_assert_failure(multimap_init_copy_array_ex(pmmap, an_array, 10, NULL));

    multimap_destroy(pmmap);
}
*/

/*
 * test multimap_destroy
 */
UT_CASE_DEFINATION(multimap_destroy)
void test_multimap_destroy__null_multimap(void** state)
{
    expect_assert_failure(multimap_destroy(NULL));
}

void test_multimap_destroy__non_created(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_destroy(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_destroy(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_destroy__created(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_destroy(pt_multimap);
}

void test_multimap_destroy__inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    multimap_destroy(pt_multimap);
}

void test_multimap_destroy__non_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);

    multimap_init(pt_multimap);
    pair_init_elem(pt_pair, 2, 4);
    multimap_insert(pt_multimap, pt_pair);
    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_assign
 */
UT_CASE_DEFINATION(multimap_assign)
void test_multimap_assign__null_dest(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    expect_assert_failure(multimap_assign(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_assign__null_src(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    expect_assert_failure(multimap_assign(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_assign__non_created_dest(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_assign__non_created_dest_pair(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_assign(pt_dest, pt_src));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_assign__non_init_src(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);

    multimap_init_ex(pt_src, NULL);
    multimap_init_ex(pt_dest, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_assign__non_init_src_pair(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_src, NULL);
    multimap_init_ex(pt_dest, NULL);
    pv_tmp = pt_src->_pair_temp._pv_second;
    pt_src->_pair_temp._pv_second = NULL;
    expect_assert_failure(multimap_assign(pt_dest, pt_src));
    pt_src->_pair_temp._pv_second = pv_tmp;

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_assign__not_same_type(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(double, int);

    multimap_init_ex(pt_src, NULL);
    multimap_init_ex(pt_dest, NULL);
    expect_assert_failure(multimap_assign(pt_dest, pt_src));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_assign__empty_empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);

    multimap_init_ex(pt_src, NULL);
    multimap_init_ex(pt_dest, NULL);
    multimap_assign(pt_dest, pt_src);
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_assign__non_empty_empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    multimap_init_ex(pt_src, NULL);
    multimap_init_ex(pt_dest, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_dest, pt_pair);
    multimap_assign(pt_dest, pt_src);
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_assign__non_empty_non_empty_less(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 999;

    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    elem = 222;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);

    multimap_init_ex(pt_dest, NULL);
    elem = 897;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_dest, pt_pair);

    multimap_assign(pt_dest, pt_src);
    assert_true(multimap_size(pt_dest) == 2);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_assign__non_empty_non_empty_size_equal(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    multimap_init_ex(pt_src, NULL);

    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);

    multimap_init_ex(pt_dest, NULL);
    elem = 334;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_dest, pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_dest))) == 334);
    multimap_assign(pt_dest, pt_src);
    assert_true(multimap_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_dest))) == 9);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_assign__non_empty_non_empty_equal(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    multimap_init_ex(pt_src, NULL);

    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);

    multimap_init_ex(pt_dest, NULL);
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_dest, pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_dest))) == 9);
    multimap_assign(pt_dest, pt_src);
    assert_true(multimap_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_dest))) == 9);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_assign__non_empty_non_empty_greater(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    multimap_init_ex(pt_src, NULL);

    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);

    multimap_init_ex(pt_dest, NULL);
    elem = 876;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_dest, pt_pair);
    elem = 333;
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_dest, pt_pair);
    multimap_assign(pt_dest, pt_src);
    assert_true(multimap_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_dest))) == 9);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_assign__empty_non_empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    multimap_init_ex(pt_src, NULL);
    pair_make(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);
    multimap_init_ex(pt_dest, NULL);
    multimap_assign(pt_dest, pt_src);
    assert_true(multimap_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_dest))) == 9);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

/*
 * test multimap_size
 */
UT_CASE_DEFINATION(multimap_size)
void test_multimap_size__null_multimap(void** state)
{
    expect_assert_failure(multimap_size(NULL));
}

void test_multimap_size__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_size(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_size(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_size__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_size(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_size__empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(multimap_size(pt_multimap) == 0);

    multimap_destroy(pt_multimap);
}

void test_multimap_size__non_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    assert_true(multimap_size(pt_multimap) == 1);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_empty
 */
UT_CASE_DEFINATION(multimap_empty)
void test_multimap_empty__null_multimap(void** state)
{
    expect_assert_failure(multimap_empty(NULL));
}

void test_multimap_empty__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_empty(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_empty(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_empty__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_empty(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_empty__empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(multimap_empty(pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_empty__non_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    assert_false(multimap_empty(pt_multimap));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_max_size
 */
UT_CASE_DEFINATION(multimap_max_size)
void test_multimap_max_size__null_multimap(void** state)
{
    expect_assert_failure(multimap_max_size(NULL));
}

void test_multimap_max_size__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_max_size(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_max_size(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_max_size__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_max_size(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_max_size__empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(multimap_max_size(pt_multimap) > 0);

    multimap_destroy(pt_multimap);
}

void test_multimap_max_size__non_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    assert_true(multimap_max_size(pt_multimap) > 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_begin
 */
UT_CASE_DEFINATION(multimap_begin)
void test_multimap_begin__null_multimap(void** state)
{
    expect_assert_failure(multimap_begin(NULL));
}

void test_multimap_begin__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_begin(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_begin(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_begin__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_begin(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_begin__empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(_multimap_iterator_equal(multimap_begin(pt_multimap), multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
}

void test_multimap_begin__non_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_multimap))) == 9);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_end
 */
UT_CASE_DEFINATION(multimap_end)
void test_multimap_end__null_multimap(void** state)
{
    expect_assert_failure(multimap_end(NULL));
}

void test_multimap_end__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_end(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_end(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_end__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_end(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_end__empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(iterator_equal(multimap_begin(pt_multimap), multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
}

void test_multimap_end__non_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_end(pt_multimap);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_key_comp
 */
UT_CASE_DEFINATION(multimap_key_comp)
void test_multimap_key_comp__null_multimap(void** state)
{
    expect_assert_failure(multimap_key_comp(NULL));
}

void test_multimap_key_comp__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_key_comp(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_key_comp__default_key_comp(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(multimap_key_comp(pt_multimap) == _GET_MULTIMAP_FIRST_TYPE_LESS_FUNCTION(pt_multimap));

    multimap_destroy(pt_multimap);
}

void _test_multimap_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_multimap_key_comp__user_define_key_comp(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, _test_multimap_key_comp__user_define_key_comp);

    assert_true(multimap_key_comp(pt_multimap) == _test_multimap_key_comp__user_define_key_comp);

    multimap_destroy(pt_multimap);
}

/*
 * test multimap_value_comp
 */
UT_CASE_DEFINATION(multimap_value_comp)
void test_multimap_value_comp__null_multimap(void** state)
{
    expect_assert_failure(multimap_value_comp(NULL));
}

void test_multimap_value_comp__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_value_comp(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_value_comp__default_value_comp(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(multimap_value_comp(pt_multimap) == _multimap_value_compare);

    multimap_destroy(pt_multimap);
}

void _test_multimap_value_comp__user_define_value_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_multimap_value_comp__user_define_value_comp(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, _test_multimap_value_comp__user_define_value_comp);

    assert_true(multimap_value_comp(pt_multimap) == _multimap_value_compare);

    multimap_destroy(pt_multimap);
}

/*
 * test multimap_clear
 */
UT_CASE_DEFINATION(multimap_clear)
void test_multimap_clear__null_multimap(void** state)
{
    expect_assert_failure(multimap_clear(NULL));
}

void test_multimap_clear__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_clear(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_clear(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test_multimap_clear__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_clear(pt_multimap));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test_multimap_clear__empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    assert_true(multimap_empty(pt_multimap));
    multimap_clear(pt_multimap);
    assert_true(multimap_empty(pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_clear__non_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 8;
    multimap_init_ex(pt_multimap, NULL);

    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    assert_false(multimap_empty(pt_multimap));
    multimap_clear(pt_multimap);
    assert_true(multimap_empty(pt_multimap));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_equal
 */
UT_CASE_DEFINATION(multimap_equal)
void test_multimap_equal__null_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_equal(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_equal__null_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_equal(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_equal__non_inited_first(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_equal__non_inited_first_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_equal__non_inited_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_equal__non_inited_second_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_equal__not_same_type(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(list_t<int>,int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    expect_assert_failure(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_equal__same_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    assert_true(multimap_equal(pt_multimap, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_equal__size_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_equal__size_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_equal__size_equal_0(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    assert_true(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_equal__size_equal_elem_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_multimap_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_equal__compare_not_equal(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, _test_multimap_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_equal__equal(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test multimap_not_equal
 */
UT_CASE_DEFINATION(multimap_not_equal)
void test_multimap_not_equal__null_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_not_equal(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_not_equal__null_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_not_equal(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_not_equal__non_inited_first(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_not_equal__non_inited_first_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_not_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_not_equal__non_inited_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_not_equal__non_inited_second_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_not_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_not_equal__not_same_type(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(list_t<int>, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    expect_assert_failure(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_not_equal__same_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    assert_false(multimap_not_equal(pt_multimap, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_not_equal__size_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_not_equal__size_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_not_equal__size_equal_0(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    assert_false(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_multimap_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_not_equal__compare_not_equal(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, _test_multimap_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_not_equal__equal(void** state)
{
    multimap_t* pt_first = create_multimap(int,int);
    multimap_t* pt_second = create_multimap(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_not_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test multimap_less
 */
UT_CASE_DEFINATION(multimap_less)
void test_multimap_less__null_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_less(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_less__null_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_less(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_less__non_inited_first(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_less(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_less(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less__non_inited_first_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_less(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less__non_inited_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_less(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_less(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less__non_inited_second_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_less(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less__not_same_type(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(list_t<int>, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    expect_assert_failure(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less__same_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    assert_false(multimap_less(pt_multimap, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_less__size_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less__size_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less__size_equal_0(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    assert_false(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less__size_equal_elem_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less__size_equal_elem_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_multimap_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_less__compare_less(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, _test_multimap_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    expect_assert_failure(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less__equal(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_less(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test multimap_less_equal
 */
UT_CASE_DEFINATION(multimap_less_equal)
void test_multimap_less_equal__null_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_less_equal(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_less_equal__null_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_less_equal(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_less_equal__non_inited_first(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less_equal__non_inited_first_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_less_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less_equal__non_inited_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less_equal__non_inited_second_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_less_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less_equal__not_same_type(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(list_t<int>, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    expect_assert_failure(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less_equal__same_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    assert_true(multimap_less_equal(pt_multimap, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_less_equal__size_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less_equal__size_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less_equal__size_equal_0(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    assert_true(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_multimap_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_less_equal__compare_less(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, _test_multimap_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    expect_assert_failure(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_less_equal__equal(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_less_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test multimap_greater
 */
UT_CASE_DEFINATION(multimap_greater)
void test_multimap_greater__null_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_greater(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_greater__null_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_greater(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_greater__non_inited_first(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_greater(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_greater(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater__non_inited_first_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_greater(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater__non_inited_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_greater(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_greater(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater__non_inited_second_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_greater(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater__not_same_type(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(list_t<int>, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    expect_assert_failure(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater__same_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    assert_false(multimap_greater(pt_multimap, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_greater__size_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater__size_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater__size_equal_0(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    assert_false(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater__size_equal_elem_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater__size_equal_elem_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_multimap_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_greater__compare_less(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, _test_multimap_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    expect_assert_failure(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater__equal(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test multimap_greater_equal
 */
UT_CASE_DEFINATION(multimap_greater_equal)
void test_multimap_greater_equal__null_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_greater_equal(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_greater_equal__null_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_greater_equal(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_greater_equal__non_inited_first(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater_equal__non_inited_first_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater_equal__non_inited_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater_equal__non_inited_second_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_second;
    pt_second->_pair_temp._pv_second = NULL;
    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_second = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater_equal__not_same_type(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(list_t<int>, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater_equal__same_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    assert_true(multimap_greater_equal(pt_multimap, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_greater_equal__size_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater_equal__size_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater_equal__size_equal_0(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    assert_true(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_false(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_multimap_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_greater_equal__compare_less(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, _test_multimap_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    expect_assert_failure(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_greater_equal__equal(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_greater_equal(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test multimap_swap
 */
UT_CASE_DEFINATION(multimap_swap)
void test_multimap_swap__null_first(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_swap(NULL, pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_swap__null_second(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_swap(pt_multimap, NULL));

    multimap_destroy(pt_multimap);
}

void test_multimap_swap__non_inited_first(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_swap(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_swap(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_swap__non_inited_first_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_swap(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_swap__non_inited_second(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_swap(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_swap(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_swap__non_inited_second_pair(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_swap(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_swap__not_same_type(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(list_t<int>, int);

    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);

    expect_assert_failure(multimap_swap(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
}

void test_multimap_swap__same_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);

    multimap_init_ex(pt_multimap, NULL);
    multimap_swap(pt_multimap, pt_multimap);
    assert_true(multimap_empty(pt_multimap));

    multimap_destroy(pt_multimap);
}

void test_multimap_swap__0_swap_n(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_size(pt_first) == 0);
    assert_true(multimap_size(pt_second) == 10);
    multimap_swap(pt_first, pt_second);
    assert_true(multimap_size(pt_first) == 10);
    assert_true(multimap_size(pt_second) == 0);

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_swap__n_swap_0(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }

    assert_true(multimap_size(pt_first) == 10);
    assert_true(multimap_size(pt_second) == 0);
    multimap_swap(pt_first, pt_second);
    assert_true(multimap_size(pt_first) == 0);
    assert_true(multimap_size(pt_second) == 10);

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_swap__n_swap_n(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 100; i < 110; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_size(pt_first) == 10);
    assert_true(multimap_size(pt_second) == 10);
    assert_true(multimap_less(pt_first, pt_second));
    multimap_swap(pt_first, pt_second);
    assert_true(multimap_size(pt_first) == 10);
    assert_true(multimap_size(pt_second) == 10);
    assert_true(multimap_greater(pt_first, pt_second));

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_multimap_swap__m_swap_n(void** state)
{
    multimap_t* pt_first = create_multimap(int, int);
    multimap_t* pt_second = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_first, NULL);
    multimap_init_ex(pt_second, NULL);
    for(i = 0; i < 30; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_second, pt_pair);
    }

    assert_true(multimap_size(pt_first) == 30);
    assert_true(multimap_size(pt_second) == 10);
    multimap_swap(pt_first, pt_second);
    assert_true(multimap_size(pt_first) == 10);
    assert_true(multimap_size(pt_second) == 30);

    multimap_destroy(pt_first);
    multimap_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test multimap_insert
 */
UT_CASE_DEFINATION(multimap_insert)
void test_multimap_insert__null_multimap(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);
    expect_assert_failure(multimap_insert(NULL, pt_pair));
    pair_destroy(pt_pair);
}

void test_multimap_insert__null_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init(pt_multimap);
    expect_assert_failure(multimap_insert(pt_multimap, NULL));
    multimap_destroy(pt_multimap);
}

void test_multimap_insert__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_insert(pt_multimap, pt_pair));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_insert(pt_multimap, pt_pair));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    void* pv_tmp = NULL;
    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_insert(pt_multimap, pt_pair));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__pair_non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_insert(pt_multimap, pt_pair));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__not_smae_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, double);

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    expect_assert_failure(multimap_insert(pt_multimap, pt_pair));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__c_builtin_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    pair_make(pt_pair, 3, 444);
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter))== 3);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__c_builtin_not_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    pair_make(pt_pair, -8, 3);
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter))== -8);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__cstr_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;
    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "window");
    multimap_insert(pt_multimap, pt_pair);

    pair_make(pt_pair, "ggg", "llll");
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);
    assert_true(multimap_size(pt_multimap) == 6);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__cstr_not_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;
    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "window");
    multimap_insert(pt_multimap, pt_pair);

    pair_make(pt_pair, "vvvv", "llll");
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "vvvv") == 0);
    assert_true(multimap_size(pt_multimap) == 6);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__libcstl_builtin_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test_multimap_insert__libcstl_builtin_not_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 44);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 44);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test_multimap_insert__user_define
{
    int n_elem;
}_test_multimap_insert__user_define_t;
void test_multimap_insert__user_define_equal(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test_multimap_insert__user_define_t elem;
    int i = 0;

    type_register(_test_multimap_insert__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = create_multimap(_test_multimap_insert__user_define_t, _test_multimap_insert__user_define_t);
    pt_pair = create_pair(_test_multimap_insert__user_define_t, _test_multimap_insert__user_define_t);

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    pair_make(pt_pair, &elem, &elem);
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(((_test_multimap_insert__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert__user_define_not_equal(void** state)
{
    multimap_t* pt_multimap =  create_multimap(_test_multimap_insert__user_define_t, _test_multimap_insert__user_define_t);
    pair_t* pt_pair = create_pair(_test_multimap_insert__user_define_t, _test_multimap_insert__user_define_t);
    multimap_iterator_t it_iter;
    _test_multimap_insert__user_define_t elem;
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 7;
    pair_make(pt_pair, &elem, &elem);
    it_iter = multimap_insert(pt_multimap, pt_pair);
    assert_true(((_test_multimap_insert__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 7);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_insert_hint
 */
UT_CASE_DEFINATION(multimap_insert_hint)
void test_multimap_insert_hint__null_multimap(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_hint;
    pair_init(pt_pair);
    expect_assert_failure(multimap_insert_hint(NULL, it_hint, pt_pair));
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__null_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_iterator_t it_hint;
    multimap_init(pt_multimap);
    it_hint = multimap_begin(pt_multimap);
    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, NULL));
    multimap_destroy(pt_multimap);
}

void test_multimap_insert_hint__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_hint;
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    it_hint = multimap_begin(pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, pt_pair));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, pt_pair));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_hint;
    void* pv_tmp = NULL;
    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);
    it_hint = multimap_begin(pt_multimap);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, pt_pair));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__pair_non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_hint;
    multimap_init_ex(pt_multimap, NULL);
    it_hint = multimap_begin(pt_multimap);

    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, pt_pair));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__hint_invalid_container_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_hint;
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    it_hint = multimap_begin(pt_multimap);
    it_hint._t_containertype = 9999;

    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, pt_pair));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__hint_invalid_iterator_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_hint;
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    it_hint = multimap_begin(pt_multimap);
    it_hint._t_iteratortype = 8888;

    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, pt_pair));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__hint_invalid_container(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_hint;
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    it_hint = multimap_begin(pt_multimap);
    it_hint._pt_container = NULL;

    expect_assert_failure(multimap_insert_hint(pt_multimap, it_hint, pt_pair));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__not_smae_type(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, double);

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    expect_assert_failure(multimap_insert_hint(pt_multimap, multimap_begin(pt_multimap), pt_pair));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__c_builtin_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    }

    pair_make(pt_pair, 3, 444);
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter))== 3);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__c_builtin_not_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    }

    pair_make(pt_pair, -8, 3);
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter))== -8);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__cstr_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;
    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "linux", "window");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);

    pair_make(pt_pair, "ggg", "llll");
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);
    assert_true(multimap_size(pt_multimap) == 6);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__cstr_not_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;
    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    pair_make(pt_pair, "linux", "window");
    multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);

    pair_make(pt_pair, "vvvv", "llll");
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "vvvv") == 0);
    assert_true(multimap_size(pt_multimap) == 6);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__libcstl_builtin_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test_multimap_insert_hint__libcstl_builtin_not_equal(void** state)
{
    multimap_t* pt_multimap = create_multimap(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 44);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 44);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test_multimap_insert_hint__user_define
{
    int n_elem;
}_test_multimap_insert_hint__user_define_t;
void test_multimap_insert_hint__user_define_equal(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test_multimap_insert_hint__user_define_t elem;
    int i = 0;

    type_register(_test_multimap_insert_hint__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = create_multimap(_test_multimap_insert_hint__user_define_t, _test_multimap_insert_hint__user_define_t);
    pt_pair = create_pair(_test_multimap_insert_hint__user_define_t, _test_multimap_insert_hint__user_define_t);

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    }

    elem.n_elem = 8;
    pair_make(pt_pair, &elem, &elem);
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(((_test_multimap_insert_hint__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_insert_hint__user_define_not_equal(void** state)
{
    multimap_t* pt_multimap =  create_multimap(_test_multimap_insert_hint__user_define_t, _test_multimap_insert_hint__user_define_t);
    pair_t* pt_pair = create_pair(_test_multimap_insert_hint__user_define_t, _test_multimap_insert_hint__user_define_t);
    multimap_iterator_t it_iter;
    _test_multimap_insert_hint__user_define_t elem;
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_multimap, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    }

    elem.n_elem = 7;
    pair_make(pt_pair, &elem, &elem);
    it_iter = multimap_insert_hint(pt_multimap, multimap_end(pt_multimap), pt_pair);
    assert_true(((_test_multimap_insert_hint__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 7);
    assert_true(multimap_size(pt_multimap) == 11);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_insert_range
 */
UT_CASE_DEFINATION(multimap_insert_range)
void test_multimap_insert_range__null_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_insert_range(NULL, multimap_begin(pt_multimap), multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
}

void test_multimap_insert_range__non_inited(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, 3, 3);
    multimap_insert(pt_src, pt_pair);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_insert_range__non_inited_pair(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);

    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_insert_range__invalid_begin(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    it_begin._t_containertype = 33333;
    expect_assert_failure(multimap_insert_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_insert_range__invalid_end(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    it_end._t_iteratortype = 3333;
    expect_assert_failure(multimap_insert_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_insert_range__invalid_range(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int elem = 0;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_src, pt_pair);

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_insert_range(pt_dest, it_end, it_begin));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_insert_range__not_same_type(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(double, int);
    pair_t* ppair = create_pair(double, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
    pair_init_elem(ppair, 10.3, 1);
    multimap_insert(pt_src, ppair);

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    expect_assert_failure(multimap_insert_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(ppair);
}

void test_multimap_insert_range__empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_insert_range(pt_dest, it_begin, it_end);
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
}

void test_multimap_insert_range__non_empty_equal(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int i = 0;

    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_src, pt_pair);
    }

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_insert_range(pt_dest, it_begin, it_end);
    assert_true(multimap_size(pt_dest) == 20);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_insert_range__non_empty_dest_src_dup(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }
    for(i = 5; i < 15; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_src, pt_pair);
    }

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_insert_range(pt_dest, it_begin, it_end);
    assert_true(multimap_size(pt_dest) == 20);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_insert_range__non_empty_src_dup(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }
    for(i = 15; i < 25; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_src, pt_pair);
        multimap_insert(pt_src, pt_pair);
    }

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_insert_range(pt_dest, it_begin, it_end);
    assert_true(multimap_size(pt_dest) == 30);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

static void _test_multimap_insert_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_multimap_insert_range__compare(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_t* pt_src = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    pair_init(pt_pair);
    multimap_init_ex(pt_dest, NULL);
    multimap_init_ex(pt_src, _test_multimap_insert_range__compare);

    it_begin = multimap_begin(pt_src);
    it_end = multimap_end(pt_src);
    multimap_insert_range(pt_dest, it_begin, it_end);

    multimap_destroy(pt_dest);
    multimap_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_multimap_insert_range__other_container_range(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    multimap_init(pmmap);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    multimap_insert_range(pmmap, vector_begin(pvec), vector_end(pvec));
    assert_true(multimap_size(pmmap) == 10);

    multimap_destroy(pmmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_multimap_insert_range__other_container_range_not_same_type(void** state)
{
    multimap_t* pmmap = create_multimap(int, double);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    multimap_init(pmmap);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    expect_assert_failure(multimap_insert_range(pmmap, vector_begin(pvec), vector_end(pvec)));

    multimap_destroy(pmmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

/*
void test_multimap_insert_range__other_container_range_not_pair(void** state)
{
    multimap_t* pmmap = create_multimap(int, int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    multimap_init(pmmap);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    expect_assert_failure(multimap_insert_range(pmmap, vector_begin(pvec), vector_end(pvec)));

    multimap_destroy(pmmap);
    vector_destroy(pvec);
}
*/

/*
 * test multimap_insert_array
 */
UT_CASE_DEFINATION(multimap_insert_array)
void test_multimap_insert_array__null_multimap(void** state)
{
    pair_t* appair[10] = {NULL};
    expect_assert_failure(multimap_insert_array(NULL, appair, 10));
}

void test_multimap_insert_array__non_inited(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    multimap_init_ex(pt_dest, NULL);
#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_insert_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_insert_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
}

void test_multimap_insert_array__non_inited_pair(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init_ex(pt_dest, NULL);

    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_insert_array(pt_dest, appair, 10));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_dest);
}

void test_multimap_insert_array__invalid_array(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);

    multimap_init_ex(pt_dest, NULL);

    expect_assert_failure(multimap_insert_array(pt_dest, NULL, 10));

    multimap_destroy(pt_dest);
}

void test_multimap_insert_array__not_same_type(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    multimap_init_ex(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, double);
        pair_init_elem(appair[i], i, i);
    }

    expect_assert_failure(multimap_insert_array(pt_dest, appair, 10));

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_insert_array__empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);

    multimap_init_ex(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }

    multimap_insert_array(pt_dest, appair, 0);
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_insert_array__non_empty_equal(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    multimap_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        appair[i - 10] = create_pair(int, int);
        pair_init_elem(appair[i - 10], i, i);
    }

    multimap_insert_array(pt_dest, appair, 10);
    assert_true(multimap_size(pt_dest) == 20);

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_insert_array__non_empty_dest_src_dup(void** state)
{
    pair_t* appair[10] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }
    for(i = 5; i < 15; ++i)
    {
        appair[i - 5] = create_pair(int, int);
        pair_init_elem(appair[i - 5], i, i);
    }

    multimap_insert_array(pt_dest, appair, 10);
    assert_true(multimap_size(pt_dest) == 20);

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_multimap_insert_array__non_empty_src_dup(void** state)
{
    pair_t* appair[20] = {NULL};
    multimap_t* pt_dest = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    multimap_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }
    for (i = 0; i < 20; i += 2)
    {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i + 15, i + 15);
        appair[i + 1] = create_pair(int, int);
        pair_init_elem(appair[i + 1], i + 15, i + 15);
    }

    multimap_insert_array(pt_dest, appair, 20);
    assert_true(multimap_size(pt_dest) == 30);

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
    for (i = 0; i < 20; ++i) {
        pair_destroy(appair[i]);
    }
}

/*
void test_multimap_insert_array__array_not_pair(void** state)
{
    int an_array[10] = {0};
    multimap_t* pmmap = create_multimap(int, int);
    int i = 0;

    multimap_init(pmmap);
    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    expect_assert_failure(multimap_insert_array(pmmap, an_array, 10));

    multimap_destroy(pmmap);
}
*/

/*
 * test multimap_erase_pos
 */
UT_CASE_DEFINATION(multimap_erase_pos)
void test_multimap_erase_pos__null_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    expect_assert_failure(multimap_erase_pos(NULL, multimap_begin(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__non_inited(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_pos;
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_pos = multimap_begin(pt_multimap);
#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_erase_pos(pt_multimap, it_pos));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_erase_pos(pt_multimap, it_pos));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    void* pv_tmp = NULL;
    multimap_iterator_t it_pos;
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_pos = multimap_begin(pt_multimap);
    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_erase_pos(pt_multimap, it_pos));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__invalid_pos(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_pos;
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_pos = multimap_begin(pt_multimap);
    it_pos._t_iteratortype = 99494;
    expect_assert_failure(multimap_erase_pos(pt_multimap, it_pos));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__end(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_pos;
    int elem = 9;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_multimap, pt_pair);
    it_pos = multimap_end(pt_multimap);
    expect_assert_failure(multimap_erase_pos(pt_multimap, it_pos));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__begin(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_pos;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }
    it_pos = multimap_begin(pt_multimap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 0);
    multimap_erase_pos(pt_multimap, it_pos);
    assert_true(multimap_size(pt_multimap) == 9);
    it_pos = multimap_begin(pt_multimap);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 1);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__middle(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_pos;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }
    i = 4;
    it_pos = multimap_find(pt_multimap, i);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 4);
    multimap_erase_pos(pt_multimap, it_pos);
    assert_true(multimap_size(pt_multimap) == 9);
    it_pos = multimap_find(pt_multimap, i);
    assert_true(iterator_equal(it_pos, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__last(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_pos;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }
    it_pos = iterator_prev(multimap_end(pt_multimap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 9);
    multimap_erase_pos(pt_multimap, it_pos);
    assert_true(multimap_size(pt_multimap) == 9);
    it_pos = iterator_prev(multimap_end(pt_multimap));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 8);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test_multimap_erase_pos__erase_empty(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_pos;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init_elem(pt_pair, i, i);
    multimap_insert(pt_multimap, pt_pair);
    assert_true(multimap_size(pt_multimap) == 1);
    it_pos = multimap_begin(pt_multimap);
    multimap_erase_pos(pt_multimap, it_pos);
    assert_true(multimap_size(pt_multimap) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test multimap_erase_range
 */
UT_CASE_DEFINATION(multimap_erase_range)
void test_multimap_erase_range__null_multimap(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    multimap_init_ex(pt_multimap, NULL);

    expect_assert_failure(multimap_erase_range(NULL, multimap_begin(pt_multimap), multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
}

void test_multimap_erase_range__non_inited(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);

    it_begin = multimap_begin(pt_dest);
    it_end = multimap_end(pt_dest);
#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(multimap_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(multimap_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_dest);
}

void test_multimap_erase_range__non_inited_pair(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);

    it_begin = multimap_begin(pt_dest);
    it_end = multimap_end(pt_dest);
    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    expect_assert_failure(multimap_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_dest);
}

void test_multimap_erase_range__invalid_begin(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);

    it_begin = multimap_begin(pt_dest);
    it_end = multimap_end(pt_dest);
    it_begin._t_containertype = 555;
    expect_assert_failure(multimap_erase_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
}

void test_multimap_erase_range__invalid_end(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);

    it_begin = multimap_begin(pt_dest);
    it_end = multimap_end(pt_dest);
    it_end._t_iteratortype = 5555;
    expect_assert_failure(multimap_erase_range(pt_dest, it_begin, it_end));

    multimap_destroy(pt_dest);
}

void test_multimap_erase_range__invalid_range(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int elem = 0;

    multimap_init_ex(pt_dest, NULL);
    pair_init_elem(pt_pair, elem, elem);
    multimap_insert(pt_dest, pt_pair);

    it_begin = multimap_begin(pt_dest);
    it_end = multimap_end(pt_dest);
    expect_assert_failure(multimap_erase_range(pt_dest, it_end, it_begin));

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_multimap_erase_range__empty(void** state)
{
    multimap_t* pt_dest = create_multimap(int,int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;

    multimap_init_ex(pt_dest, NULL);

    it_begin = multimap_begin(pt_dest);
    it_end = multimap_end(pt_dest);
    multimap_erase_range(pt_dest, it_begin, it_end);
    assert_true(multimap_empty(pt_dest));

    multimap_destroy(pt_dest);
}

void test_multimap_erase_range__begin(void** state)
{
    multimap_t* pt_dest = create_multimap(int,int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int i = 0;

    multimap_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }

    it_begin = multimap_begin(pt_dest);
    it_end = iterator_next(it_begin);
    multimap_erase_range(pt_dest, it_begin, it_end);
    assert_true(multimap_size(pt_dest) == 9);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(multimap_begin(pt_dest))) == 1);

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_multimap_erase_range__middle(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int i = 0;

    multimap_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }

    it_begin = iterator_next(multimap_begin(pt_dest));
    it_end = iterator_next(it_begin);
    multimap_erase_range(pt_dest, it_begin, it_end);
    assert_true(multimap_size(pt_dest) == 9);
    it_begin = multimap_begin(pt_dest);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_begin)) == 0);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(iterator_next(it_begin))) == 2);

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_multimap_erase_range__end(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int i = 0;

    multimap_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }

    it_end = multimap_end(pt_dest);
    it_begin = iterator_prev(it_end);
    multimap_erase_range(pt_dest, it_begin, it_end);
    assert_true(multimap_size(pt_dest) == 9);
    it_end = multimap_end(pt_dest);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(iterator_prev(it_end))) == 8);

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_multimap_erase_range__all(void** state)
{
    multimap_t* pt_dest = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_begin;
    multimap_iterator_t it_end;
    int i = 0;

    multimap_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_dest, pt_pair);
    }

    it_begin = multimap_begin(pt_dest);
    it_end = multimap_end(pt_dest);
    multimap_erase_range(pt_dest, it_begin, it_end);
    assert_true(multimap_size(pt_dest) == 0);

    multimap_destroy(pt_dest);
    pair_destroy(pt_pair);
}

