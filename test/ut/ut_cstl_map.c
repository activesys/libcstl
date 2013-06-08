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
#include "cstl_map_aux.h"

#include "ut_def.h"
#include "ut_cstl_map.h"

UT_SUIT_DEFINATION(cstl_map, map_init)

/*
 * test map_init
 */
UT_CASE_DEFINATION(map_init)
void test_map_init__null_map(void** state)
{
    expect_assert_failure(map_init(NULL));
}

void test_map_init__non_created(void** state)
{
    map_t* pt_map = create_map(int, int);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_init__non_created_pair(void** state)
{
    map_t* pt_map = create_map(int, int);

    pt_map->_pair_temp._pv_first = (void*)0x9999;
    expect_assert_failure(map_init(pt_map));
    pt_map->_pair_temp._pv_first = NULL;

    map_destroy(pt_map);
}

void test_map_init__null_compare(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init(pt_map);
    assert_true(_pair_is_inited(&pt_map->_pair_temp));
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_map->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_map->_t_tree));
#endif

    map_destroy(pt_map);
}

/*
 * test map_init_ex
 */
UT_CASE_DEFINATION(map_init_ex)
void test_map_init_ex__null_map(void** state)
{
    expect_assert_failure(map_init_ex(NULL, NULL));
}

void test_map_init_ex__non_created(void** state)
{
    map_t* pt_map = create_map(int, int);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init_ex(pt_map, NULL));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init_ex(pt_map, NULL));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_init_ex__non_created_pair(void** state)
{
    map_t* pt_map = create_map(int, int);

    pt_map->_pair_temp._pv_first = (void*)0x7777;
    expect_assert_failure(map_init_ex(pt_map, NULL));
    pt_map->_pair_temp._pv_first = NULL;

    map_destroy(pt_map);
}

void test_map_init_ex__null_compare(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_map->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_map->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_map->_pair_temp));

    map_destroy(pt_map);
}

static void _test_map_init_ex__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_init_ex__non_null_compare(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, _test_map_init_ex__non_null_compare);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_map->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_map->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_map->_pair_temp));
    assert_true(pt_map->_bfun_keycompare == _test_map_init_ex__non_null_compare);
    assert_true(pt_map->_pair_temp._bfun_mapkeycompare == _test_map_init_ex__non_null_compare);

    map_destroy(pt_map);
}

/*
 * test map_init_copy
 */
UT_CASE_DEFINATION(map_init_copy)
void test_map_init_copy__null_dest(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_init_copy(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_init_copy__null_src(void** state)
{
    map_t* pt_map = create_map(int, int);

    expect_assert_failure(map_init_copy(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_init_copy__non_created_dest(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);

    map_init_ex(pt_src, NULL);
#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__non_created_dest_pair(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);

    map_init_ex(pt_src, NULL);
    pt_dest->_pair_temp._pv_first = (void*)0x733;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_dest->_pair_temp._pv_first = NULL;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__non_inited_src(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);

    map_init_ex(pt_src, NULL);
#ifdef CSTL_MAP_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__non_inited_src_pair(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_src, NULL);
    pv_tmp = pt_src->_pair_temp._pv_first;
    pt_src->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_src->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__not_same_type(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(double, int);

    map_init_ex(pt_src, NULL);
    expect_assert_failure(map_init_copy(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(signed int, int);

    map_init_ex(pt_src, NULL);
    map_init_copy(pt_dest, pt_src);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__non_empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 100;

    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    map_init_copy(pt_dest, pt_src);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 1);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

static void _test_map_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_init_copy__non_null_compare(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    map_init_ex(pt_src, _test_map_init_copy__non_null_compare);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_src, pt_pair);
    }
    map_init_copy(pt_dest, pt_src);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 10);
    assert_true(pt_dest->_bfun_keycompare == _test_map_init_copy__non_null_compare);
    assert_true(pt_dest->_pair_temp._bfun_mapkeycompare == _test_map_init_copy__non_null_compare);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

/*
 * test map_init_copy_range
 */
UT_CASE_DEFINATION(map_init_copy_range)
void test_map_init_copy_range__null_map(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_init_copy_range(NULL, map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_init_copy_range__non_created_map(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_t* pt_dest = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init_copy_range(pt_dest, map_begin(pt_map), map_end(pt_map)));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init_copy_range(pt_dest, map_begin(pt_map), map_end(pt_map)));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
    map_destroy(pt_dest);
}

void test_map_init_copy_range__non_created_map_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_t* pt_dest = create_map(int, int);
    map_init_ex(pt_map, NULL);

    pt_dest->_pair_temp._pv_first = (void*)0x8989;
    expect_assert_failure(map_init_copy_range(pt_dest, map_begin(pt_map), map_end(pt_map)));
    pt_dest->_pair_temp._pv_first = NULL;

    map_destroy(pt_map);
    map_destroy(pt_dest);
}

void test_map_init_copy_range__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_begin._t_containertype = 99999;
    expect_assert_failure(map_init_copy_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_end._t_iteratortype = 44444;
    expect_assert_failure(map_init_copy_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range__invalid_range(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range(pt_dest, it_end, it_begin));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_init_copy_range__invalid_range_not_same_type(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(double, int);
    pair_t* ppair = create_pair(double, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    pair_init_elem(ppair, 19.3, 4);
    map_insert(pt_src, ppair);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(ppair);
}

void test_map_init_copy_range__empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range(pt_dest, it_begin, it_end);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range__non_empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range(pt_dest, it_begin, it_end);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 1);
    assert_true(map_equal(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_init_copy_range__other_container_range(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    map_init_copy_range(pmap, vector_begin(pvec), vector_end(pvec));
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmap->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmap->_t_tree));
#endif
    assert_true(_pair_is_inited(&pmap->_pair_temp));
    assert_true(map_size(pmap) == 10);

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_map_init_copy_range__other_container_range_dup(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
        vector_push_back(pvec, ppair);
    }
    map_init_copy_range(pmap, vector_begin(pvec), vector_end(pvec));
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmap->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmap->_t_tree));
#endif
    assert_true(_pair_is_inited(&pmap->_pair_temp));
    assert_true(map_size(pmap) == 10);

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_map_init_copy_range__other_container_range_not_same_type(void** state)
{
    map_t* pmap = create_map(int, double);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    expect_assert_failure(map_init_copy_range(pmap, vector_begin(pvec), vector_end(pvec)));

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

/*
void test_map_init_copy_range__other_container_range_not_pair(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    expect_assert_failure(map_init_copy_range(pmap, vector_begin(pvec), vector_end(pvec)));

    map_destroy(pmap);
    vector_destroy(pvec);
}
*/

/*
 * test map_init_copy_array
 */
UT_CASE_DEFINATION(map_init_copy_array)
void test_map_init_copy_array__null_map(void** state)
{
    pair_t* appair[10] = {0};
    expect_assert_failure(map_init_copy_array(NULL, appair, 10));
}

void test_map_init_copy_array__non_created_map(void** state)
{
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init_copy_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init_copy_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
}

void test_map_init_copy_array__non_created_map_pair(void** state)
{
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    pt_dest->_pair_temp._pv_first = (void*)0x8989;
    expect_assert_failure(map_init_copy_array(pt_dest, appair, 10));
    pt_dest->_pair_temp._pv_first = NULL;

    map_destroy(pt_dest);
}

void test_map_init_copy_array__invalid_array(void** state)
{
    map_t* pt_dest = create_map(int, int);

    expect_assert_failure(map_init_copy_array(pt_dest, NULL, 10));

    map_destroy(pt_dest);
}

void test_map_init_copy_array__invalid_array_not_same_type(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(double, int);
        pair_init_elem(appair[i], i, i);
    }
    expect_assert_failure(map_init_copy_array(pt_dest, appair, 10));

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_init_copy_array__empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    map_init_copy_array(pt_dest, appair, 0);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_init_copy_array__non_empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    map_init_copy_array(pt_dest, appair, 10);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 10);

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_init_copy_array__non_empty_dup(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], 0, 0);
    }
    map_init_copy_array(pt_dest, appair, 10);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 1);

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

/*
void test_map_init_copy_array__array_not_pair(void** state)
{
    int an_array[10] = {0};
    map_t* pmap = create_map(int, int);
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    expect_assert_failure(map_init_copy_array(pmap, an_array, 10));

    map_destroy(pmap);
}
*/

/*
 * test map_init_copy_range_ex
 */
UT_CASE_DEFINATION(map_init_copy_range_ex)
void test_map_init_copy_range_ex__null_map(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_init_copy_range_ex(NULL, map_begin(pt_map), map_end(pt_map), NULL));

    map_destroy(pt_map);
}

void test_map_init_copy_range_ex__non_created_map(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_t* pt_dest = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init_copy_range_ex(pt_dest, map_begin(pt_map), map_end(pt_map), NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init_copy_range_ex(pt_dest, map_begin(pt_map), map_end(pt_map), NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
    map_destroy(pt_dest);
}

void test_map_init_copy_range_ex__non_created_map_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_t* pt_dest = create_map(int, int);
    map_init_ex(pt_map, NULL);

    pt_dest->_pair_temp._pv_second = (void*)0x7383;
    expect_assert_failure(map_init_copy_range_ex(pt_dest, map_begin(pt_map), map_end(pt_map), NULL));
    pt_dest->_pair_temp._pv_second = NULL;

    map_destroy(pt_map);
    map_destroy(pt_dest);
}

void test_map_init_copy_range_ex__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_begin._t_containertype = 99999;
    expect_assert_failure(map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range_ex__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_end._t_iteratortype = 33333;
    expect_assert_failure(map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range_ex__invalid_range(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range_ex(pt_dest, it_end, it_begin, NULL));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_init_copy_range_ex__invalid_range_not_same_type(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(double, int);
    pair_t* ppair = create_pair(double, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    pair_init_elem(ppair, 1.3, 1);
    map_insert(pt_src, ppair);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(ppair);
}

void test_map_init_copy_range_ex__empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range_ex__non_empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 1);
    assert_true(map_equal(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

static void _test__map_init_compare_range_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_init_copy_range_ex__compare(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range_ex(pt_dest, it_begin, it_end, _test__map_init_compare_range_ex__compare);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 1);
    assert_true(pt_dest->_bfun_keycompare == _test__map_init_compare_range_ex__compare);
    assert_true(pt_dest->_pair_temp._bfun_mapkeycompare == _test__map_init_compare_range_ex__compare);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_init_copy_range_ex__other_container_range(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    map_init_copy_range_ex(pmap, vector_begin(pvec), vector_end(pvec), NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmap->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmap->_t_tree));
#endif
    assert_true(_pair_is_inited(&pmap->_pair_temp));
    assert_true(map_size(pmap) == 10);

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_map_init_copy_range_ex__other_container_range_dup(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
        vector_push_back(pvec, ppair);
    }
    map_init_copy_range_ex(pmap, vector_begin(pvec), vector_end(pvec), NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pmap->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pmap->_t_tree));
#endif
    assert_true(_pair_is_inited(&pmap->_pair_temp));
    assert_true(map_size(pmap) == 10);

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_map_init_copy_range_ex__other_container_range_not_same_type(void** state)
{
    map_t* pmap = create_map(int, double);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    expect_assert_failure(map_init_copy_range_ex(pmap, vector_begin(pvec), vector_end(pvec), NULL));

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

/*
void test_map_init_copy_range_ex__other_container_range_not_pair(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    expect_assert_failure(map_init_copy_range_ex(pmap, vector_begin(pvec), vector_end(pvec), NULL));

    map_destroy(pmap);
    vector_destroy(pvec);
}
*/

/*
 * test map_init_copy_array_ex
 */
UT_CASE_DEFINATION(map_init_copy_array_ex)
void test_map_init_copy_array_ex__null_map(void** state)
{
    pair_t* appair[10] = {NULL};
    expect_assert_failure(map_init_copy_array_ex(NULL, appair, 10, NULL));
}

void test_map_init_copy_array_ex__non_created_map(void** state)
{
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_init_copy_array_ex(pt_dest, appair, 10, NULL));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_init_copy_array_ex(pt_dest, appair, 10, NULL));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
}

void test_map_init_copy_array_ex__non_created_map_pair(void** state)
{
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    pt_dest->_pair_temp._pv_second = (void*)0x7383;
    expect_assert_failure(map_init_copy_array_ex(pt_dest, appair, 10, NULL));
    pt_dest->_pair_temp._pv_second = NULL;

    map_destroy(pt_dest);
}

void test_map_init_copy_array_ex__invalid_array(void** state)
{
    map_t* pt_dest = create_map(int, int);

    expect_assert_failure(map_init_copy_array_ex(pt_dest, NULL, 10, NULL));

    map_destroy(pt_dest);
}

void test_map_init_copy_array_ex__invalid_array_not_same_type(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(double, double);
        pair_init_elem(appair[i], i, i);
    }
    expect_assert_failure(map_init_copy_array_ex(pt_dest, appair, 10, NULL));

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_init_copy_array_ex__empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    map_init_copy_array_ex(pt_dest, appair, 0, NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_init_copy_array_ex__non_empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    map_init_copy_array_ex(pt_dest, appair, 10, NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 10);

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_init_copy_array_ex__non_empty_dup(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], 1, 4);
    }
    map_init_copy_array_ex(pt_dest, appair, 10, NULL);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 1);

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

static void _test__map_init_compare_array_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_init_copy_array_ex__compare(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }
    map_init_copy_array_ex(pt_dest, appair, 10, _test__map_init_compare_array_ex__compare);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(_avl_tree_is_inited(&pt_dest->_t_tree));
#else
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
#endif
    assert_true(_pair_is_inited(&pt_dest->_pair_temp));
    assert_true(map_size(pt_dest) == 10);
    assert_true(pt_dest->_bfun_keycompare == _test__map_init_compare_array_ex__compare);
    assert_true(pt_dest->_pair_temp._bfun_mapkeycompare == _test__map_init_compare_array_ex__compare);

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

/*
void test_map_init_copy_array_ex__array_not_pair(void** state)
{
    int an_array[10] = {0};
    map_t* pmap = create_map(int, int);
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    expect_assert_failure(map_init_copy_array_ex(pmap, an_array, 10, NULL));

    map_destroy(pmap);
}
*/

/*
 * test map_destroy
 */
UT_CASE_DEFINATION(map_destroy)
void test_map_destroy__null_map(void** state)
{
    expect_assert_failure(map_destroy(NULL));
}

void test_map_destroy__non_created(void** state)
{
    map_t* pt_map = create_map(int, int);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_destroy(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_destroy(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_destroy__created(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_destroy(pt_map);
}

void test_map_destroy__inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    map_destroy(pt_map);
}

void test_map_destroy__non_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);

    map_init(pt_map);
    pair_init_elem(pt_pair, 2, 4);
    map_insert(pt_map, pt_pair);
    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_assign
 */
UT_CASE_DEFINATION(map_assign)
void test_map_assign__null_dest(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    expect_assert_failure(map_assign(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_assign__null_src(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    expect_assert_failure(map_assign(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_assign__non_created_dest(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_created_dest_pair(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_init_src(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
#ifdef CSTL_MAP_AVL_TREE
    pt_src->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_avlroot._un_height = 0;
#else
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_init_src_pair(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    pv_tmp = pt_src->_pair_temp._pv_second;
    pt_src->_pair_temp._pv_second = NULL;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_src->_pair_temp._pv_second = pv_tmp;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__not_same_type(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(double, int);

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    expect_assert_failure(map_assign(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__empty_empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    map_assign(pt_dest, pt_src);
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_empty_empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_dest, pt_pair);
    map_assign(pt_dest, pt_src);
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_assign__non_empty_non_empty_less(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 999;

    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    elem = 222;
    pair_make(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);

    map_init_ex(pt_dest, NULL);
    elem = 897;
    pair_make(pt_pair, elem, elem);
    map_insert(pt_dest, pt_pair);

    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 2);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_assign__non_empty_non_empty_size_equal(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    map_init_ex(pt_src, NULL);

    pair_make(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);

    map_init_ex(pt_dest, NULL);
    elem = 334;
    pair_make(pt_pair, elem, elem);
    map_insert(pt_dest, pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_dest))) == 334);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_dest))) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_assign__non_empty_non_empty_equal(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    map_init_ex(pt_src, NULL);

    pair_make(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);

    map_init_ex(pt_dest, NULL);
    pair_make(pt_pair, elem, elem);
    map_insert(pt_dest, pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_dest))) == 9);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_dest))) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_assign__non_empty_non_empty_greater(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    map_init_ex(pt_src, NULL);

    pair_make(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);

    map_init_ex(pt_dest, NULL);
    elem = 876;
    pair_make(pt_pair, elem, elem);
    map_insert(pt_dest, pt_pair);
    elem = 333;
    pair_make(pt_pair, elem, elem);
    map_insert(pt_dest, pt_pair);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_dest))) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_assign__empty_non_empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    pair_init(pt_pair);
    map_init_ex(pt_src, NULL);
    pair_make(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);
    map_init_ex(pt_dest, NULL);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_dest))) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

/*
 * test map_size
 */
UT_CASE_DEFINATION(map_size)
void test_map_size__null_map(void** state)
{
    expect_assert_failure(map_size(NULL));
}

void test_map_size__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_size(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_size(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_size__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_size(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_size__empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(map_size(pt_map) == 0);

    map_destroy(pt_map);
}

void test_map_size__non_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);

    assert_true(map_size(pt_map) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_empty
 */
UT_CASE_DEFINATION(map_empty)
void test_map_empty__null_map(void** state)
{
    expect_assert_failure(map_empty(NULL));
}

void test_map_empty__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_empty(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_empty(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_empty__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_empty(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_empty__empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
}

void test_map_empty__non_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);

    assert_false(map_empty(pt_map));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_max_size
 */
UT_CASE_DEFINATION(map_max_size)
void test_map_max_size__null_map(void** state)
{
    expect_assert_failure(map_max_size(NULL));
}

void test_map_max_size__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_max_size(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_max_size(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_max_size__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_max_size(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_max_size__empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(map_max_size(pt_map) > 0);

    map_destroy(pt_map);
}

void test_map_max_size__non_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);

    assert_true(map_max_size(pt_map) > 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_begin
 */
UT_CASE_DEFINATION(map_begin)
void test_map_begin__null_map(void** state)
{
    expect_assert_failure(map_begin(NULL));
}

void test_map_begin__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_begin(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_begin(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_begin__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_begin(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_begin__empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(_map_iterator_equal(map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_begin__non_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);

    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_map))) == 9);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_end
 */
UT_CASE_DEFINATION(map_end)
void test_map_end__null_map(void** state)
{
    expect_assert_failure(map_end(NULL));
}

void test_map_end__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_end(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_end(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_end__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_end(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_end__empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(iterator_equal(map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_end__non_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);

    it_iter = map_end(pt_map);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 9);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_key_comp
 */
UT_CASE_DEFINATION(map_key_comp)
void test_map_key_comp__null_map(void** state)
{
    expect_assert_failure(map_key_comp(NULL));
}

void test_map_key_comp__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_key_comp(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_key_comp__default_key_comp(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(map_key_comp(pt_map) == _GET_MAP_FIRST_TYPE_LESS_FUNCTION(pt_map));

    map_destroy(pt_map);
}

void _test_map_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_map_key_comp__user_define_key_comp(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, _test_map_key_comp__user_define_key_comp);

    assert_true(map_key_comp(pt_map) == _test_map_key_comp__user_define_key_comp);

    map_destroy(pt_map);
}

/*
 * test map_value_comp
 */
UT_CASE_DEFINATION(map_value_comp)
void test_map_value_comp__null_map(void** state)
{
    expect_assert_failure(map_value_comp(NULL));
}

void test_map_value_comp__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_value_comp(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_value_comp__default_value_comp(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(map_value_comp(pt_map) == _map_value_compare);

    map_destroy(pt_map);
}

void _test_map_value_comp__user_define_value_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_map_value_comp__user_define_value_comp(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, _test_map_value_comp__user_define_value_comp);

    assert_true(map_value_comp(pt_map) == _map_value_compare);

    map_destroy(pt_map);
}

/*
 * test map_clear
 */
UT_CASE_DEFINATION(map_clear)
void test_map_clear__null_map(void** state)
{
    expect_assert_failure(map_clear(NULL));
}

void test_map_clear__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_clear(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_clear(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test_map_clear__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_clear(pt_map));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test_map_clear__empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    assert_true(map_empty(pt_map));
    map_clear(pt_map);
    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
}

void test_map_clear__non_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 8;
    map_init_ex(pt_map, NULL);

    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);
    assert_false(map_empty(pt_map));
    map_clear(pt_map);
    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_equal
 */
UT_CASE_DEFINATION(map_equal)
void test_map_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__non_inited_first_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__non_inited_second_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(list_t<int>,int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    assert_true(map_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_true(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_map_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_equal__compare_not_equal(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_equal__equal(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test map_not_equal
 */
UT_CASE_DEFINATION(map_not_equal)
void test_map_not_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_not_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_not_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_not_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_not_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__non_inited_first_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__non_inited_second_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(list_t<int>, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    assert_false(map_not_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_not_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_not_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_not_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_false(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_map_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_not_equal__compare_not_equal(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_not_equal__equal(void** state)
{
    map_t* pt_first = create_map(int,int);
    map_t* pt_second = create_map(signed int,int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test map_less
 */
UT_CASE_DEFINATION(map_less)
void test_map_less__null_first(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_less__null_second(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_less__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__non_inited_first_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__non_inited_second_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__not_same_type(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(list_t<int>, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__same_map(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    assert_false(map_less(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_less__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_map_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_less__compare_less(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    expect_assert_failure(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less__equal(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test map_less_equal
 */
UT_CASE_DEFINATION(map_less_equal)
void test_map_less_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_less_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_less_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__non_inited_first_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__non_inited_second_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(list_t<int>, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    assert_true(map_less_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_less_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_map_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_less_equal__compare_less(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    expect_assert_failure(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_less_equal__equal(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test map_greater
 */
UT_CASE_DEFINATION(map_greater)
void test_map_greater__null_first(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_greater__null_second(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_greater__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__non_inited_first_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__non_inited_second_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__not_same_type(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(list_t<int>, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__same_map(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    assert_false(map_greater(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_greater__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_map_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_greater__compare_less(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    expect_assert_failure(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater__equal(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test map_greater_equal
 */
UT_CASE_DEFINATION(map_greater_equal)
void test_map_greater_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_greater_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_greater_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__non_inited_first_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__non_inited_second_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_second;
    pt_second->_pair_temp._pv_second = NULL;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_second->_pair_temp._pv_second = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(list_t<int>, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    assert_true(map_greater_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_greater_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(signed int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 2; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_false(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

static void _test_map_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_greater_equal__compare_less(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    expect_assert_failure(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_greater_equal__equal(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test map_swap
 */
UT_CASE_DEFINATION(map_swap)
void test_map_swap__null_first(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_swap(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_swap__null_second(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_swap(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_swap__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_first->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_first->_t_tree._t_avlroot._un_height = 0;
#else
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__non_inited_first_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_first->_pair_temp._pv_first;
    pt_first->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_first->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_second->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_second->_t_tree._t_avlroot._un_height = 0;
#else
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__non_inited_second_pair(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pv_tmp = pt_second->_pair_temp._pv_first;
    pt_second->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_second->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__not_same_type(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(list_t<int>, int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_swap(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__same_map(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    map_swap(pt_map, pt_map);
    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
}

void test_map_swap__0_swap_n(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_size(pt_first) == 0);
    assert_true(map_size(pt_second) == 10);
    map_swap(pt_first, pt_second);
    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 0);

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_swap__n_swap_0(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }

    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 0);
    map_swap(pt_first, pt_second);
    assert_true(map_size(pt_first) == 0);
    assert_true(map_size(pt_second) == 10);

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_swap__n_swap_n(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 100; i < 110; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 10);
    assert_true(map_less(pt_first, pt_second));
    map_swap(pt_first, pt_second);
    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 10);
    assert_true(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

void test_map_swap__m_swap_n(void** state)
{
    map_t* pt_first = create_map(int, int);
    map_t* pt_second = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 30; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_first, pt_pair);
    }
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_second, pt_pair);
    }

    assert_true(map_size(pt_first) == 30);
    assert_true(map_size(pt_second) == 10);
    map_swap(pt_first, pt_second);
    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 30);

    map_destroy(pt_first);
    map_destroy(pt_second);
    pair_destroy(pt_pair);
}

/*
 * test map_insert
 */
UT_CASE_DEFINATION(map_insert)
void test_map_insert__null_map(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    pair_init(pt_pair);
    expect_assert_failure(map_insert(NULL, pt_pair));
    pair_destroy(pt_pair);
}

void test_map_insert__null_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init(pt_map);
    expect_assert_failure(map_insert(pt_map, NULL));
    map_destroy(pt_map);
}

void test_map_insert__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_insert(pt_map, pt_pair));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_insert(pt_map, pt_pair));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    void* pv_tmp = NULL;
    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_insert(pt_map, pt_pair));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__pair_non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_insert(pt_map, pt_pair));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__not_smae_type(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, double);

    map_init(pt_map);
    pair_init(pt_pair);
    expect_assert_failure(map_insert(pt_map, pt_pair));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__c_builtin_equal(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    pair_make(pt_pair, 3, 444);
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__c_builtin_not_equal(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    pair_make(pt_pair, -8, 3);
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter))== -8);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__cstr_equal(void** state)
{
    map_t* pt_map = create_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;
    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "window");
    map_insert(pt_map, pt_pair);

    pair_make(pt_pair, "ggg", "llll");
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 5);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__cstr_not_equal(void** state)
{
    map_t* pt_map = create_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;
    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "window");
    map_insert(pt_map, pt_pair);

    pair_make(pt_pair, "vvvv", "llll");
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "vvvv") == 0);
    assert_true(map_size(pt_map) == 6);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = create_map(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test_map_insert__libcstl_builtin_not_equal(void** state)
{
    map_t* pt_map = create_map(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 44);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 44);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test_map_insert__user_define
{
    int n_elem;
}_test_map_insert__user_define_t;
void test_map_insert__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    map_iterator_t it_iter;
    _test_map_insert__user_define_t elem;
    int i = 0;

    type_register(_test_map_insert__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = create_map(_test_map_insert__user_define_t, _test_map_insert__user_define_t);
    pt_pair = create_pair(_test_map_insert__user_define_t, _test_map_insert__user_define_t);

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    pair_make(pt_pair, &elem, &elem);
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert__user_define_not_equal(void** state)
{
    map_t* pt_map =  create_map(_test_map_insert__user_define_t, _test_map_insert__user_define_t);
    pair_t* pt_pair = create_pair(_test_map_insert__user_define_t, _test_map_insert__user_define_t);
    map_iterator_t it_iter;
    _test_map_insert__user_define_t elem;
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 7;
    pair_make(pt_pair, &elem, &elem);
    it_iter = map_insert(pt_map, pt_pair);
    assert_true(((_test_map_insert__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 7);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_insert_hint
 */
UT_CASE_DEFINATION(map_insert_hint)
void test_map_insert_hint__null_map(void** state)
{
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_hint;
    pair_init(pt_pair);
    expect_assert_failure(map_insert_hint(NULL, it_hint, pt_pair));
    pair_destroy(pt_pair);
}

void test_map_insert_hint__null_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_iterator_t it_hint;
    map_init(pt_map);
    it_hint = map_begin(pt_map);
    expect_assert_failure(map_insert_hint(pt_map, it_hint, NULL));
    map_destroy(pt_map);
}

void test_map_insert_hint__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_hint;
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    it_hint = map_begin(pt_map);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_insert_hint(pt_map, it_hint, pt_pair));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_insert_hint(pt_map, it_hint, pt_pair));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_hint;
    void* pv_tmp = NULL;
    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);
    it_hint = map_begin(pt_map);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_insert_hint(pt_map, it_hint, pt_pair));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__pair_non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_hint;
    map_init_ex(pt_map, NULL);
    it_hint = map_begin(pt_map);

    expect_assert_failure(map_insert_hint(pt_map, it_hint, pt_pair));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__hint_invalid_container_type(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_hint;
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    it_hint = map_begin(pt_map);
    it_hint._t_containertype = 9999;

    expect_assert_failure(map_insert_hint(pt_map, it_hint, pt_pair));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__hint_invalid_iterator_type(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_hint;
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    it_hint = map_begin(pt_map);
    it_hint._t_iteratortype = 8888;

    expect_assert_failure(map_insert_hint(pt_map, it_hint, pt_pair));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__hint_invalid_container(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_hint;
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    it_hint = map_begin(pt_map);
    it_hint._pt_container = NULL;

    expect_assert_failure(map_insert_hint(pt_map, it_hint, pt_pair));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__not_smae_type(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, double);

    map_init(pt_map);
    pair_init(pt_pair);
    expect_assert_failure(map_insert_hint(pt_map, map_begin(pt_map), pt_pair));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__c_builtin_equal(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    }

    pair_make(pt_pair, 3, 444);
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__c_builtin_not_equal(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    }

    pair_make(pt_pair, -8, 3);
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter))== -8);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__cstr_equal(void** state)
{
    map_t* pt_map = create_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;
    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "linux", "window");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);

    pair_make(pt_pair, "ggg", "llll");
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 5);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__cstr_not_equal(void** state)
{
    map_t* pt_map = create_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;
    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    pair_make(pt_pair, "aaa", "aaa");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    pair_make(pt_pair, "linux", "window");
    map_insert_hint(pt_map, map_end(pt_map), pt_pair);

    pair_make(pt_pair, "vvvv", "llll");
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "vvvv") == 0);
    assert_true(map_size(pt_map) == 6);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = create_map(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test_map_insert_hint__libcstl_builtin_not_equal(void** state)
{
    map_t* pt_map = create_map(list_t<int>, vector_t<int>);
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        vector_push_back(pvec, i);
        list_push_back(plist, i);
        pair_make(pt_pair, plist, pvec);
        map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 44);
    vector_clear(pvec);
    vector_push_back(pvec, 3);
    pair_make(pt_pair, plist, pvec);
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 44);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test_map_insert_hint__user_define
{
    int n_elem;
}_test_map_insert_hint__user_define_t;
void test_map_insert_hint__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    map_iterator_t it_iter;
    _test_map_insert_hint__user_define_t elem;
    int i = 0;

    type_register(_test_map_insert_hint__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = create_map(_test_map_insert_hint__user_define_t, _test_map_insert_hint__user_define_t);
    pt_pair = create_pair(_test_map_insert_hint__user_define_t, _test_map_insert_hint__user_define_t);

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    }

    elem.n_elem = 8;
    pair_make(pt_pair, &elem, &elem);
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_insert_hint__user_define_not_equal(void** state)
{
    map_t* pt_map =  create_map(_test_map_insert_hint__user_define_t, _test_map_insert_hint__user_define_t);
    pair_t* pt_pair = create_pair(_test_map_insert_hint__user_define_t, _test_map_insert_hint__user_define_t);
    map_iterator_t it_iter;
    _test_map_insert_hint__user_define_t elem;
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    }

    elem.n_elem = 7;
    pair_make(pt_pair, &elem, &elem);
    it_iter = map_insert_hint(pt_map, map_end(pt_map), pt_pair);
    assert_true(((_test_map_insert_hint__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 7);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_insert_range
 */
UT_CASE_DEFINATION(map_insert_range)
void test_map_insert_range__null_map(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_insert_range(NULL, map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_insert_range__non_inited(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, 3, 3);
    map_insert(pt_src, pt_pair);

#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_insert_range__non_inited_pair(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    void* pv_tmp = NULL;
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_begin._t_containertype = 33333;
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_end._t_iteratortype = 3333;
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__invalid_range(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 0;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_src, pt_pair);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_end, it_begin));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_insert_range__not_same_type(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, double);
    pair_t* ppair = create_pair(int, double);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    pair_init_elem(ppair, 1, 10.3);
    map_insert(pt_src, ppair);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(ppair);
}

void test_map_insert_range__empty(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__non_empty_equal(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_src, pt_pair);
    }

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 20);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_insert_range__non_empty_dest_src_dup(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }
    for(i = 5; i < 15; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_src, pt_pair);
    }

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 15);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_insert_range__non_empty_src_dup(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }
    for(i = 15; i < 25; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_src, pt_pair);
        map_insert(pt_src, pt_pair);
    }

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 20);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

static void _test_map_insert_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_insert_range__compare(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_t* pt_src = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    pair_init(pt_pair);
    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, _test_map_insert_range__compare);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);

    map_destroy(pt_dest);
    map_destroy(pt_src);
    pair_destroy(pt_pair);
}

void test_map_insert_range__other_container_range(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    map_init(pmap);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    map_insert_range(pmap, vector_begin(pvec), vector_end(pvec));
    assert_true(map_size(pmap) == 10);

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

void test_map_insert_range__other_container_range_not_same_type(void** state)
{
    map_t* pmap = create_map(int, double);
    vector_t* pvec = create_vector(pair_t<int, int>);
    pair_t* ppair = create_pair(int, int);
    int i = 0;

    pair_init(ppair);
    vector_init(pvec);
    map_init(pmap);
    for (i = 0; i < 10; ++i) {
        pair_make(ppair, i, i);
        vector_push_back(pvec, ppair);
    }
    expect_assert_failure(map_insert_range(pmap, vector_begin(pvec), vector_end(pvec)));

    map_destroy(pmap);
    vector_destroy(pvec);
    pair_destroy(ppair);
}

/*
void test_map_insert_range__other_container_range_not_pair(void** state)
{
    map_t* pmap = create_map(int, int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    vector_init(pvec);
    map_init(pmap);
    for (i = 0; i < 10; ++i) {
        vector_push_back(pvec, i);
    }
    expect_assert_failure(map_insert_range(pmap, vector_begin(pvec), vector_end(pvec)));

    map_destroy(pmap);
    vector_destroy(pvec);
}
*/

/*
 * test map_insert_array
 */
UT_CASE_DEFINATION(map_insert_array)
void test_map_insert_array__null_map(void** state)
{
    pair_t* appair[10] = {NULL};
    expect_assert_failure(map_insert_array(NULL, appair, 10));
}

void test_map_insert_array__non_inited(void** state)
{
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    map_init_ex(pt_dest, NULL);
#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_insert_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_insert_array(pt_dest, appair, 10));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
}

void test_map_insert_array__non_inited_pair(void** state)
{
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);
    void* pv_tmp = NULL;

    map_init_ex(pt_dest, NULL);

    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_insert_array(pt_dest, appair, 10));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_dest);
}

void test_map_insert_array__invalid_array(void** state)
{
    map_t* pt_dest = create_map(int, int);

    map_init_ex(pt_dest, NULL);
    expect_assert_failure(map_insert_array(pt_dest, NULL, 10));

    map_destroy(pt_dest);
}

void test_map_insert_array__not_same_type(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    map_init_ex(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, double);
        pair_init_elem(appair[i], i, i);
    }

    expect_assert_failure(map_insert_array(pt_dest, appair, 10));

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_insert_array__empty(void** state)
{
    int i = 0;
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);

    map_init_ex(pt_dest, NULL);
    for (i = 0; i < 10; ++i) {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i, i);
    }

    map_insert_array(pt_dest, appair, 0);
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_insert_array__non_empty_equal(void** state)
{
    pair_t* appair[10] = {0};
    map_t* pt_dest = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    map_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }
    for(i = 10; i < 20; ++i)
    {
        appair[i - 10] = create_pair(int, int);
        pair_init_elem(appair[i - 10], i, i);
    }

    map_insert_array(pt_dest, appair, 10);
    assert_true(map_size(pt_dest) == 20);

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_insert_array__non_empty_dest_src_dup(void** state)
{
    pair_t* appair[10] = {NULL};
    map_t* pt_dest = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }
    for(i = 5; i < 15; ++i)
    {
        appair[i - 5] = create_pair(int, int);
        pair_init_elem(appair[i - 5], i, i);
    }

    map_insert_array(pt_dest, appair, 10);
    assert_true(map_size(pt_dest) == 15);

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
    for (i = 0; i < 10; ++i) {
        pair_destroy(appair[i]);
    }
}

void test_map_insert_array__non_empty_src_dup(void** state)
{
    pair_t* appair[20] = {NULL};
    map_t* pt_dest = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    pair_init(pt_pair);
    map_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }
    for (i = 0; i < 20; i += 2)
    {
        appair[i] = create_pair(int, int);
        pair_init_elem(appair[i], i + 15, i + 15);
        appair[i + 1] = create_pair(int, int);
        pair_init_elem(appair[i + 1], i + 15, i + 15);
    }

    map_insert_array(pt_dest, appair, 20);
    assert_true(map_size(pt_dest) == 20);

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
    for (i = 0; i < 20; ++i) {
        pair_destroy(appair[i]);
    }
}

/*
void test_map_insert_array__array_not_pair(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    map_t* pmap = create_map(int, int);

    map_init(pmap);
    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    expect_assert_failure(map_insert_array(pmap, an_array, 10));

    map_destroy(pmap);
}
*/

/*
 * test map_erase_pos
 */
UT_CASE_DEFINATION(map_erase_pos)
void test_map_erase_pos__null_map(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);
    expect_assert_failure(map_erase_pos(NULL, map_begin(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_pos;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);
    it_pos = map_begin(pt_map);
#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_erase_pos(pt_map, it_pos));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_erase_pos(pt_map, it_pos));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    void* pv_tmp = NULL;
    map_iterator_t it_pos;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);
    it_pos = map_begin(pt_map);
    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_erase_pos(pt_map, it_pos));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__invalid_pos(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_pos;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);
    it_pos = map_begin(pt_map);
    it_pos._t_iteratortype = 99494;
    expect_assert_failure(map_erase_pos(pt_map, it_pos));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__end(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_pos;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_map, pt_pair);
    it_pos = map_end(pt_map);
    expect_assert_failure(map_erase_pos(pt_map, it_pos));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__begin(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }
    it_pos = map_begin(pt_map);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 0);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 9);
    it_pos = map_begin(pt_map);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__middle(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }
    i = 4;
    it_pos = map_find(pt_map, i);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 4);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 9);
    it_pos = map_find(pt_map, i);
    assert_true(iterator_equal(it_pos, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__last(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }
    it_pos = iterator_prev(map_end(pt_map));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 9);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 9);
    it_pos = iterator_prev(map_end(pt_map));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_pos)) == 8);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test_map_erase_pos__erase_empty(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init_elem(pt_pair, i, i);
    map_insert(pt_map, pt_pair);
    assert_true(map_size(pt_map) == 1);
    it_pos = map_begin(pt_map);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test map_erase_range
 */
UT_CASE_DEFINATION(map_erase_range)
void test_map_erase_range__null_map(void** state)
{
    map_t* pt_map = create_map(int, int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_erase_range(NULL, map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_erase_range__non_inited(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
#ifdef CSTL_MAP_AVL_TREE
    pt_dest->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_avlroot._un_height = 0;
#else
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_dest);
}

void test_map_erase_range__non_inited_pair(void** state)
{
    map_t* pt_dest = create_map(int, int);
    void* pv_tmp = NULL;
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    pv_tmp = pt_dest->_pair_temp._pv_first;
    pt_dest->_pair_temp._pv_first = NULL;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_dest);
}

void test_map_erase_range__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    it_begin._t_containertype = 555;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
}

void test_map_erase_range__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    it_end._t_iteratortype = 5555;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
}

void test_map_erase_range__invalid_range(void** state)
{
    map_t* pt_dest = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 0;

    map_init_ex(pt_dest, NULL);
    pair_init_elem(pt_pair, elem, elem);
    map_insert(pt_dest, pt_pair);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    expect_assert_failure(map_erase_range(pt_dest, it_end, it_begin));

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_map_erase_range__empty(void** state)
{
    map_t* pt_dest = create_map(int,int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
}

void test_map_erase_range__begin(void** state)
{
    map_t* pt_dest = create_map(int,int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }

    it_begin = map_begin(pt_dest);
    it_end = iterator_next(it_begin);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 9);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(map_begin(pt_dest))) == 1);

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_map_erase_range__middle(void** state)
{
    map_t* pt_dest = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }

    it_begin = iterator_next(map_begin(pt_dest));
    it_end = iterator_next(it_begin);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 9);
    it_begin = map_begin(pt_dest);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_begin)) == 0);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(iterator_next(it_begin))) == 2);

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_map_erase_range__end(void** state)
{
    map_t* pt_dest = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }

    it_end = map_end(pt_dest);
    it_begin = iterator_prev(it_end);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 9);
    it_end = map_end(pt_dest);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(iterator_prev(it_end))) == 8);

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
}

void test_map_erase_range__all(void** state)
{
    map_t* pt_dest = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_dest, pt_pair);
    }

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 0);

    map_destroy(pt_dest);
    pair_destroy(pt_pair);
}

