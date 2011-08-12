#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cmap.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_rb_tree_aux.h"
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

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_init(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_init__non_created_pair(void** state)
{
    map_t* pt_map = create_map(int, int);

    pt_map->_t_pair._pv_first = (void*)0x9999;
    expect_assert_failure(map_init(pt_map));
    pt_map->_t_pair._pv_first = NULL;

    map_destroy(pt_map);
}

void test_map_init__null_compare(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init(pt_map);
    assert_true(_pair_is_inited(&pt_map->_t_pair));
    assert_true(_rb_tree_is_inited(&pt_map->_t_tree));

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

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_init_ex(pt_map, NULL));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_init_ex__non_created_pair(void** state)
{
    map_t* pt_map = create_map(int, int);

    pt_map->_t_pair._pv_first = (void*)0x7777;
    expect_assert_failure(map_init_ex(pt_map, NULL));
    pt_map->_t_pair._pv_first = NULL;

    map_destroy(pt_map);
}

void test_map_init_ex__null_compare(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init_ex(pt_map, NULL);
    assert_true(_rb_tree_is_inited(&pt_map->_t_tree));
    assert_true(_pair_is_inited(&pt_map->_t_pair));

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
    assert_true(_rb_tree_is_inited(&pt_map->_t_tree));
    assert_true(_pair_is_inited(&pt_map->_t_pair));
    assert_true(pt_map->_t_keycompare == _test_map_init_ex__non_null_compare);
    assert_true(pt_map->_t_pair._t_mapkeycompare == _test_map_init_ex__non_null_compare);

    map_destroy(pt_map);
}

/*
 * test map_init_copy
 */
/*
UT_CASE_DEFINATION(map_init_copy)
void test_map_init_copy__null_dest(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_init_copy(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_init_copy__null_src(void** state)
{
    map_t* pt_map = create_map(int);

    expect_assert_failure(map_init_copy(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_init_copy__non_created_dest(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);

    map_init_ex(pt_src, NULL);
    pt_dest->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__non_inited_src(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);

    map_init_ex(pt_src, NULL);
    pt_src->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_init_copy(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__not_same_type(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(double);

    map_init_ex(pt_src, NULL);
    expect_assert_failure(map_init_copy(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(signed int);

    map_init_ex(pt_src, NULL);
    map_init_copy(pt_dest, pt_src);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy__non_empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(signed int);
    int elem = 100;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    map_init_copy(pt_dest, pt_src);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_size(pt_dest) == 1);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

static void _test_map_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_init_copy__non_null_compare(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(signed int);
    int i = 0;

    map_init_ex(pt_src, _test_map_init_copy__non_null_compare);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_src, i);
    }
    map_init_copy(pt_dest, pt_src);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_size(pt_dest) == 10);
    assert_true(pt_dest->_t_tree._t_compare == _test_map_init_copy__non_null_compare);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}
*/

/*
 * test map_init_copy_range
 */
/*
UT_CASE_DEFINATION(map_init_copy_range)
void test_map_init_copy_range__null_map(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_init_copy_range(NULL, map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_init_copy_range__non_created_map(void** state)
{
    map_t* pt_map = create_map(int);
    map_t* pt_dest = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_dest->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_init_copy_range(pt_dest, map_begin(pt_map), map_end(pt_map)));
    pt_dest->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
    map_destroy(pt_dest);
}

void test_map_init_copy_range__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(map_init_copy_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
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
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range(pt_dest, it_end, it_begin));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range__invalid_range_not_same_type(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(double);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range__empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range__non_empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_size(pt_dest) == 1);
    assert_true(map_equal(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}
*/

/*
 * test map_init_copy_range_ex
 */
/*
UT_CASE_DEFINATION(map_init_copy_range_ex)
void test_map_init_copy_range_ex__null_map(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_init_copy_range_ex(NULL, map_begin(pt_map), map_end(pt_map), NULL));

    map_destroy(pt_map);
}

void test_map_init_copy_range_ex__non_created_map(void** state)
{
    map_t* pt_map = create_map(int);
    map_t* pt_dest = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_dest->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_init_copy_range_ex(pt_dest, map_begin(pt_map), map_end(pt_map), NULL));
    pt_dest->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
    map_destroy(pt_dest);
}

void test_map_init_copy_range_ex__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range_ex__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
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
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range_ex(pt_dest, it_end, it_begin, NULL));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range_ex__invalid_range_not_same_type(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(double);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range_ex__empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_src, NULL);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_init_copy_range_ex__non_empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_size(pt_dest) == 1);
    assert_true(map_equal(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

static void _test__map_init_compare_range_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_init_copy_range_ex__compare(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_init_copy_range_ex(pt_dest, it_begin, it_end, _test__map_init_compare_range_ex__compare);
    assert_true(_rb_tree_is_inited(&pt_dest->_t_tree));
    assert_true(map_size(pt_dest) == 1);
    assert_true(pt_dest->_t_tree._t_compare == _test__map_init_compare_range_ex__compare);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}
*/

/*
 * test map_destroy
 */
/*
UT_CASE_DEFINATION(map_destroy)
void test_map_destroy__null_map(void** state)
{
    expect_assert_failure(map_destroy(NULL));
}

void test_map_destroy__non_created(void** state)
{
    map_t* pt_map = create_map(int);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_destroy(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_destroy__created(void** state)
{
    map_t* pt_map = create_map(int);

    map_destroy(pt_map);
}

void test_map_destroy__inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    map_destroy(pt_map);
}
*/

/*
 * test map_assign
 */
/*
UT_CASE_DEFINATION(map_assign)
void test_map_assign__null_dest(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    expect_assert_failure(map_assign(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_assign__null_src(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    expect_assert_failure(map_assign(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_assign__non_created_dest(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);

    map_init_ex(pt_src, NULL);
    pt_dest->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_dest->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_init_src(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    pt_src->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_assign(pt_dest, pt_src));
    pt_src->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__not_same_type(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(double);

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    expect_assert_failure(map_assign(pt_dest, pt_src));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__empty_empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    map_assign(pt_dest, pt_src);
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_empty_empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_init_ex(pt_dest, NULL);
    map_insert(pt_dest, elem);
    map_assign(pt_dest, pt_src);
    assert_true(map_empty(pt_dest));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_empty_non_empty_less(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    elem = 222;
    map_insert(pt_src, elem);
    map_init_ex(pt_dest, NULL);
    elem = 897;
    map_insert(pt_dest, elem);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 2);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_empty_non_empty_size_equal(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    map_init_ex(pt_dest, NULL);
    elem = 334;
    map_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(map_begin(pt_dest)) == 334);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(map_begin(pt_dest)) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_empty_non_empty_equal(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    map_init_ex(pt_dest, NULL);
    map_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(map_begin(pt_dest)) == 9);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(map_begin(pt_dest)) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__non_empty_non_empty_greater(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    map_init_ex(pt_dest, NULL);
    elem = 876;
    map_insert(pt_dest, elem);
    elem = 333;
    map_insert(pt_dest, elem);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(map_begin(pt_dest)) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_assign__empty_non_empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    int elem = 9;

    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);
    map_init_ex(pt_dest, NULL);
    map_assign(pt_dest, pt_src);
    assert_true(map_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(map_begin(pt_dest)) == 9);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}
*/

/*
 * test map_size
 */
/*
UT_CASE_DEFINATION(map_size)
void test_map_size__null_map(void** state)
{
    expect_assert_failure(map_size(NULL));
}

void test_map_size__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_size(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_size__empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    assert_true(map_size(pt_map) == 0);

    map_destroy(pt_map);
}

void test_map_size__non_empty(void** state)
{
    map_t* pt_map = create_map(int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);

    assert_true(map_size(pt_map) == 1);

    map_destroy(pt_map);
}
*/

/*
 * test map_empty
 */
/*
UT_CASE_DEFINATION(map_empty)
void test_map_empty__null_map(void** state)
{
    expect_assert_failure(map_empty(NULL));
}

void test_map_empty__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_empty(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_empty__empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
}

void test_map_empty__non_empty(void** state)
{
    map_t* pt_map = create_map(int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);

    assert_false(map_empty(pt_map));

    map_destroy(pt_map);
}
*/

/*
 * test map_max_size
 */
/*
UT_CASE_DEFINATION(map_max_size)
void test_map_max_size__null_map(void** state)
{
    expect_assert_failure(map_max_size(NULL));
}

void test_map_max_size__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_max_size(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_max_size__empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    assert_true(map_max_size(pt_map) > 0);

    map_destroy(pt_map);
}

void test_map_max_size__non_empty(void** state)
{
    map_t* pt_map = create_map(int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);

    assert_true(map_max_size(pt_map) > 0);

    map_destroy(pt_map);
}
*/

/*
 * test map_begin
 */
/*
UT_CASE_DEFINATION(map_begin)
void test_map_begin__null_map(void** state)
{
    expect_assert_failure(map_begin(NULL));
}

void test_map_begin__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_begin(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_begin__empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    assert_true(_map_iterator_equal(map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_begin__non_empty(void** state)
{
    map_t* pt_map = create_map(int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);

    assert_true(*(int*)iterator_get_pointer(map_begin(pt_map)) == 9);

    map_destroy(pt_map);
}
*/

/*
 * test map_end
 */
/*
UT_CASE_DEFINATION(map_end)
void test_map_end__null_map(void** state)
{
    expect_assert_failure(map_end(NULL));
}

void test_map_end__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_end(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_end__empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    assert_true(iterator_equal(map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_end__non_empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_iter;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);

    it_iter = map_end(pt_map);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    map_destroy(pt_map);
}
*/

/*
 * test map_key_comp
 */
/*
UT_CASE_DEFINATION(map_key_comp)
void test_map_key_comp__null_map(void** state)
{
    expect_assert_failure(map_key_comp(NULL));
}

void test_map_key_comp__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_key_comp(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_key_comp__default_key_comp(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    assert_true(map_key_comp(pt_map) == _GET_MAP_TYPE_LESS_FUNCTION(pt_map));

    map_destroy(pt_map);
}

void _test_map_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_map_key_comp__user_define_key_comp(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, _test_map_key_comp__user_define_key_comp);

    assert_true(map_key_comp(pt_map) == _test_map_key_comp__user_define_key_comp);

    map_destroy(pt_map);
}
*/

/*
 * test map_clear
 */
/*
UT_CASE_DEFINATION(map_clear)
void test_map_clear__null_map(void** state)
{
    expect_assert_failure(map_clear(NULL));
}

void test_map_clear__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_clear(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_clear__empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    assert_true(map_empty(pt_map));
    map_clear(pt_map);
    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
}

void test_map_clear__non_empty(void** state)
{
    map_t* pt_map = create_map(int);
    int elem = 8;
    map_init_ex(pt_map, NULL);

    map_insert(pt_map, elem);
    assert_false(map_empty(pt_map));
    map_clear(pt_map);
    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
}
*/

/*
 * test map_equal
 */
/*
UT_CASE_DEFINATION(map_equal)
void test_map_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_first->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_second->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(list_t<int>);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    assert_true(map_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(signed int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_true(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

static void _test_map_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_equal__compare_not_equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_false(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_equal__equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_true(map_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}
*/

/*
 * test map_not_equal
 */
/*
UT_CASE_DEFINATION(map_not_equal)
void test_map_not_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_not_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_not_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_not_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_not_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_first->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_second->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_not_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(list_t<int>);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    assert_false(map_not_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_not_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(signed int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_false(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

static void _test_map_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_not_equal__compare_not_equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_true(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_not_equal__equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_false(map_not_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}
*/

/*
 * test map_less
 */
/*
UT_CASE_DEFINATION(map_less)
void test_map_less__null_first(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_less__null_second(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_less__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_first->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_second->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_less(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__not_same_type(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(list_t<int>);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__same_map(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    assert_false(map_less(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_less__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(signed int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

static void _test_map_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_less__compare_less(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    expect_assert_failure(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less__equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_false(map_less(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}
*/

/*
 * test map_less_equal
 */
/*
UT_CASE_DEFINATION(map_less_equal)
void test_map_less_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_less_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_less_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_less_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_first->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_second->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_less_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(list_t<int>);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    assert_true(map_less_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_less_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(signed int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

static void _test_map_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_less_equal__compare_less(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    expect_assert_failure(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_less_equal__equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_true(map_less_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}
*/

/*
 * test map_greater
 */
/*
UT_CASE_DEFINATION(map_greater)
void test_map_greater__null_first(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_greater__null_second(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_greater__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_first->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_second->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_greater(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__not_same_type(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(list_t<int>);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__same_map(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    assert_false(map_greater(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_greater__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(signed int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

static void _test_map_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_greater__compare_less(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    expect_assert_failure(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater__equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_false(map_greater(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}
*/

/*
 * test map_greater_equal
 */
/*
UT_CASE_DEFINATION(map_greater_equal)
void test_map_greater_equal__null_first(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater_equal(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_greater_equal__null_second(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_greater_equal(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_greater_equal__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_first->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_second->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_greater_equal(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__not_same_type(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(list_t<int>);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__same_map(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    assert_true(map_greater_equal(pt_map, pt_map));

    map_destroy(pt_map);
}

void test_map_greater_equal__size_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(signed int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__size_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__size_equal_0(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_false(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 30; i < 40; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

static void _test_map_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_greater_equal__compare_less(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, _test_map_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    expect_assert_failure(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_greater_equal__equal(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
        map_insert(pt_second, i);
    }

    assert_true(map_greater_equal(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}
*/

/*
 * test map_swap
 */
/*
UT_CASE_DEFINATION(map_swap)
void test_map_swap__null_first(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_swap(NULL, pt_map));

    map_destroy(pt_map);
}

void test_map_swap__null_second(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_swap(pt_map, NULL));

    map_destroy(pt_map);
}

void test_map_swap__non_inited_first(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_first->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_first->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__non_inited_second(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    pt_second->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_swap(pt_first, pt_second));
    pt_second->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__not_same_type(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(list_t<int>);

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);

    expect_assert_failure(map_swap(pt_first, pt_second));

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__same_map(void** state)
{
    map_t* pt_map = create_map(int);

    map_init_ex(pt_map, NULL);
    map_swap(pt_map, pt_map);
    assert_true(map_empty(pt_map));

    map_destroy(pt_map);
}

void test_map_swap__0_swap_n(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i = 0;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_size(pt_first) == 0);
    assert_true(map_size(pt_second) == 10);
    map_swap(pt_first, pt_second);
    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 0);

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__n_swap_0(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i = 0;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }

    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 0);
    map_swap(pt_first, pt_second);
    assert_true(map_size(pt_first) == 0);
    assert_true(map_size(pt_second) == 10);

    map_destroy(pt_first);
    map_destroy(pt_second);
}

void test_map_swap__n_swap_n(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i = 0;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 100; i < 110; ++i)
    {
        map_insert(pt_second, i);
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
}

void test_map_swap__m_swap_n(void** state)
{
    map_t* pt_first = create_map(int);
    map_t* pt_second = create_map(int);
    int i = 0;

    map_init_ex(pt_first, NULL);
    map_init_ex(pt_second, NULL);
    for(i = 0; i < 30; ++i)
    {
        map_insert(pt_first, i);
    }
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_second, i);
    }

    assert_true(map_size(pt_first) == 30);
    assert_true(map_size(pt_second) == 10);
    map_swap(pt_first, pt_second);
    assert_true(map_size(pt_first) == 10);
    assert_true(map_size(pt_second) == 30);

    map_destroy(pt_first);
    map_destroy(pt_second);
}
*/

/*
 * test map_insert_range
 */
/*
UT_CASE_DEFINATION(map_insert_range)
void test_map_insert_range__null_map(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_insert_range(NULL, map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_insert_range__non_inited(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    pt_dest->_t_tree._t_rbroot._t_color = BLACK;
    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    it_end._t_containertype = 3333;
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__invalid_range(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 0;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    map_insert(pt_src, elem);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_end, it_begin));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__not_same_type(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(vector_t<int>);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    expect_assert_failure(map_insert_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__empty(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
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
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_dest, i);
    }
    for(i = 10; i < 20; ++i)
    {
        map_insert(pt_src, i);
    }

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 20);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__non_empty_dest_src_dup(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_dest, i);
    }
    for(i = 5; i < 15; ++i)
    {
        map_insert(pt_src, i);
    }

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 15);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

void test_map_insert_range__non_empty_src_dup(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_dest, i);
    }
    for(i = 15; i < 25; ++i)
    {
        map_insert(pt_src, i);
        map_insert(pt_src, i);
    }

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 20);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}

static void _test_map_insert_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_map_insert_range__compare(void** state)
{
    map_t* pt_dest = create_map(int);
    map_t* pt_src = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);
    map_init_ex(pt_src, _test_map_insert_range__compare);

    it_begin = map_begin(pt_src);
    it_end = map_end(pt_src);
    map_insert_range(pt_dest, it_begin, it_end);

    map_destroy(pt_dest);
    map_destroy(pt_src);
}
*/

/*
 * test map_erase_pos
 */
/*
UT_CASE_DEFINATION(map_erase_pos)
void test_map_erase_pos__null_map(void** state)
{
    map_t* pt_map = create_map(int);
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);
    expect_assert_failure(map_erase_pos(NULL, map_begin(pt_map)));

    map_destroy(pt_map);
}

void test_map_erase_pos__non_inited(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_pos;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);
    it_pos = map_begin(pt_map);
    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_erase_pos(pt_map, it_pos));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test_map_erase_pos__invalid_pos(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_pos;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);
    it_pos = map_begin(pt_map);
    it_pos._t_pos._t_treepos._pc_corepos = NULL;
    expect_assert_failure(map_erase_pos(pt_map, it_pos));

    map_destroy(pt_map);
}

void test_map_erase_pos__end(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_pos;
    int elem = 9;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, elem);
    it_pos = map_end(pt_map);
    expect_assert_failure(map_erase_pos(pt_map, it_pos));

    map_destroy(pt_map);
}

void test_map_erase_pos__begin(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }
    it_pos = map_begin(pt_map);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 9);
    it_pos = map_begin(pt_map);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);

    map_destroy(pt_map);
}

void test_map_erase_pos__middle(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }
    i = 4;
    it_pos = map_find(pt_map, i);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 9);
    it_pos = map_find(pt_map, i);
    assert_true(_map_iterator_equal(it_pos, map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_erase_pos__last(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }
    it_pos = iterator_prev(map_end(pt_map));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 9);
    it_pos = iterator_prev(map_end(pt_map));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);

    map_destroy(pt_map);
}

void test_map_erase_pos__erase_empty(void** state)
{
    map_t* pt_map = create_map(int);
    map_iterator_t it_pos;
    int i = 0;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, i);
    assert_true(map_size(pt_map) == 1);
    it_pos = map_begin(pt_map);
    map_erase_pos(pt_map, it_pos);
    assert_true(map_size(pt_map) == 0);

    map_destroy(pt_map);
}
*/

/*
 * test map_erase_range
 */
/*
UT_CASE_DEFINATION(map_erase_range)
void test_map_erase_range__null_map(void** state)
{
    map_t* pt_map = create_map(int);
    map_init_ex(pt_map, NULL);

    expect_assert_failure(map_erase_range(NULL, map_begin(pt_map), map_end(pt_map)));

    map_destroy(pt_map);
}

void test_map_erase_range__non_inited(void** state)
{
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    pt_dest->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_dest);
}

void test_map_erase_range__invalid_begin(void** state)
{
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
}

void test_map_erase_range__invalid_end(void** state)
{
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;

    map_init_ex(pt_dest, NULL);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    it_end._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(map_erase_range(pt_dest, it_begin, it_end));

    map_destroy(pt_dest);
}

void test_map_erase_range__invalid_range(void** state)
{
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int elem = 0;

    map_init_ex(pt_dest, NULL);
    map_insert(pt_dest, elem);

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    expect_assert_failure(map_erase_range(pt_dest, it_end, it_begin));

    map_destroy(pt_dest);
}

void test_map_erase_range__empty(void** state)
{
    map_t* pt_dest = create_map(int);
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
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_dest, i);
    }

    it_begin = map_begin(pt_dest);
    it_end = iterator_next(it_begin);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 9);
    assert_true(*(int*)iterator_get_pointer(map_begin(pt_dest)) == 1);

    map_destroy(pt_dest);
}

void test_map_erase_range__middle(void** state)
{
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_dest, i);
    }

    it_begin = iterator_next(map_begin(pt_dest));
    it_end = iterator_next(it_begin);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 9);
    it_begin = map_begin(pt_dest);
    assert_true(*(int*)iterator_get_pointer(it_begin) == 0);
    assert_true(*(int*)iterator_get_pointer(iterator_next(it_begin)) == 2);

    map_destroy(pt_dest);
}

void test_map_erase_range__end(void** state)
{
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_dest, i);
    }

    it_end = map_end(pt_dest);
    it_begin = iterator_prev(it_end);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 9);
    it_end = map_end(pt_dest);
    assert_true(*(int*)iterator_get_pointer(iterator_prev(it_end)) == 8);

    map_destroy(pt_dest);
}

void test_map_erase_range__all(void** state)
{
    map_t* pt_dest = create_map(int);
    map_iterator_t it_begin;
    map_iterator_t it_end;
    int i = 0;

    map_init_ex(pt_dest, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_dest, i);
    }

    it_begin = map_begin(pt_dest);
    it_end = map_end(pt_dest);
    map_erase_range(pt_dest, it_begin, it_end);
    assert_true(map_size(pt_dest) == 0);

    map_destroy(pt_dest);
}
*/

