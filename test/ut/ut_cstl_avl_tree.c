#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_avl_tree_iterator.h"
#include "cstl/cstl_avl_tree_private.h"
#include "cstl/cstl_avl_tree.h"
#include "cstl_avl_tree_aux.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"

#include "ut_def.h"
#include "ut_cstl_avl_tree.h"

UT_SUIT_DEFINATION(cstl_avl_tree, _create_avl_tree)

/*
 * test _create_avl_tree
 */
UT_CASE_DEFINATION(_create_avl_tree)
void test__create_avl_tree__null_typename(void** state)
{
    expect_assert_failure(_create_avl_tree(NULL));
}

void test__create_avl_tree__c_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("double");
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__create_avl_tree__cstr(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__create_avl_tree__libcstl_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("vector_t<int>");
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

typedef struct _test_test__create_avl_tree__user_define
{
    int n_elem;
}_test__create_avl_tree__user_define_t;

void test__create_avl_tree__user_define(void** state)
{
    _avl_tree_t* pt_avl_tree = NULL;

    type_register(_test__create_avl_tree__user_define_t, NULL, NULL, NULL, NULL);
    pt_avl_tree = _create_avl_tree("_test__create_avl_tree__user_define_t");
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__create_avl_tree__unregister(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("test__create_avl_tree__unregister_t");
    assert_true(pt_avl_tree == NULL);
}

/*
 * test _avl_tree_init
 */
UT_CASE_DEFINATION(_avl_tree_init)
void test__avl_tree_init__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_init(NULL, NULL));
}

void test__avl_tree_init__non_created(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    pt_avl_tree->_t_avlroot._un_height = 8;
    expect_assert_failure(_avl_tree_init(pt_avl_tree, NULL));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init__null_compare(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    assert_true(_avl_tree_is_inited(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

static void _test__avl_tree_init__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__avl_tree_init__non_null_compare(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, _test__avl_tree_init__non_null_compare);
    assert_true(_avl_tree_is_inited(pt_avl_tree));
    assert_true(pt_avl_tree->_t_compare == _test__avl_tree_init__non_null_compare);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_init_copy
 */
UT_CASE_DEFINATION(_avl_tree_init_copy)
void test__avl_tree_init_copy__null_dest(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_init_copy(NULL, pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_copy__null_src(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    expect_assert_failure(_avl_tree_init_copy(pt_avl_tree, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_copy__non_created_dest(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");

    _avl_tree_init(pt_src, NULL);
    pt_dest->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_init_copy(pt_dest, pt_src));
    pt_dest->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy__non_inited_src(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");

    _avl_tree_init(pt_src, NULL);
    pt_src->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_init_copy(pt_dest, pt_src));
    pt_src->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy__not_same_type(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("double");

    _avl_tree_init(pt_src, NULL);
    expect_assert_failure(_avl_tree_init_copy(pt_dest, pt_src));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy__empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("signed int");

    _avl_tree_init(pt_src, NULL);
    _avl_tree_init_copy(pt_dest, pt_src);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_empty(pt_dest));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy__non_empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("signed int");
    int elem = 100;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    _avl_tree_init_copy(pt_dest, pt_src);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_size(pt_dest) == 1);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

static void _test__avl_tree_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__avl_tree_init_copy__non_null_compare(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("signed int");
    int i = 0;

    _avl_tree_init(pt_src, _test__avl_tree_init_copy__non_null_compare);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_src, &i);
    }
    _avl_tree_init_copy(pt_dest, pt_src);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_size(pt_dest) == 10);
    assert_true(pt_dest->_t_compare == _test__avl_tree_init_copy__non_null_compare);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

/*
 * test _avl_tree_init_copy_range
 */
UT_CASE_DEFINATION(_avl_tree_init_copy_range)
void test__avl_tree_init_copy_range__null_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_init_copy_range(NULL, _avl_tree_begin(pt_avl_tree), _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_copy_range__non_created_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_dest->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_init_copy_range(pt_dest, _avl_tree_begin(pt_avl_tree), _avl_tree_end(pt_avl_tree)));
    pt_dest->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
    _avl_tree_destroy(pt_dest);
}

void test__avl_tree_init_copy_range__invalid_begin(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_init_copy_range(pt_dest, it_begin, it_end));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range__invalid_end(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    it_end._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_init_copy_range(pt_dest, it_begin, it_end));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range__invalid_range(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    expect_assert_failure(_avl_tree_init_copy_range(pt_dest, it_end, it_begin));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range__invalid_range_not_same_type(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("double");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    expect_assert_failure(_avl_tree_init_copy_range(pt_dest, it_begin, it_end));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range__empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    _avl_tree_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_empty(pt_dest));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range__non_empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    _avl_tree_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_size(pt_dest) == 1);
    assert_true(_avl_tree_equal(pt_dest, pt_src));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

/*
 * test _avl_tree_init_copy_range_ex
 */
UT_CASE_DEFINATION(_avl_tree_init_copy_range_ex)
void test__avl_tree_init_copy_range_ex__null_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_init_copy_range_ex(NULL, _avl_tree_begin(pt_avl_tree), _avl_tree_end(pt_avl_tree), NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_copy_range_ex__non_created_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_dest->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_init_copy_range_ex(pt_dest, _avl_tree_begin(pt_avl_tree), _avl_tree_end(pt_avl_tree), NULL));
    pt_dest->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
    _avl_tree_destroy(pt_dest);
}

void test__avl_tree_init_copy_range_ex__invalid_begin(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    it_begin._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range_ex__invalid_end(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    it_end._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range_ex__invalid_range(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    expect_assert_failure(_avl_tree_init_copy_range_ex(pt_dest, it_end, it_begin, NULL));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range_ex__invalid_range_not_same_type(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("double");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    expect_assert_failure(_avl_tree_init_copy_range_ex(pt_dest, it_begin, it_end, NULL));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range_ex__empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    _avl_tree_init(pt_src, NULL);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    _avl_tree_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_empty(pt_dest));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_init_copy_range_ex__non_empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    _avl_tree_init_copy_range_ex(pt_dest, it_begin, it_end, NULL);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_size(pt_dest) == 1);
    assert_true(_avl_tree_equal(pt_dest, pt_src));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

static void _test__avl_tree_init_compare_range_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__avl_tree_init_copy_range_ex__compare(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    it_begin = _avl_tree_begin(pt_src);
    it_end = _avl_tree_end(pt_src);
    _avl_tree_init_copy_range_ex(pt_dest, it_begin, it_end, _test__avl_tree_init_compare_range_ex__compare);
    assert_true(_avl_tree_is_inited(pt_dest));
    assert_true(_avl_tree_size(pt_dest) == 1);
    assert_true(pt_dest->_t_compare == _test__avl_tree_init_compare_range_ex__compare);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

/*
 * test _avl_tree_destroy
 */
UT_CASE_DEFINATION(_avl_tree_destroy)
void test__avl_tree_destroy__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_destroy(NULL));
}

void test__avl_tree_destroy__non_created(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    pt_avl_tree->_t_avlroot._un_height = 1;
    expect_assert_failure(_avl_tree_destroy(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_destroy__created(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_destroy__inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_assign
 */
UT_CASE_DEFINATION(_avl_tree_assign)
void test__avl_tree_assign__null_dest(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_assign(NULL, pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_assign__null_src(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_assign(pt_avl_tree, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_assign__non_created_dest(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");

    _avl_tree_init(pt_src, NULL);
    pt_dest->_t_avlroot._un_height = 1;
    expect_assert_failure(_avl_tree_assign(pt_dest, pt_src));
    pt_dest->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__non_init_src(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");

    _avl_tree_init(pt_src, NULL);
    _avl_tree_init(pt_dest, NULL);
    pt_src->_t_avlroot._un_height = 1;
    expect_assert_failure(_avl_tree_assign(pt_dest, pt_src));
    pt_src->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__not_same_type(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("double");

    _avl_tree_init(pt_src, NULL);
    _avl_tree_init(pt_dest, NULL);
    expect_assert_failure(_avl_tree_assign(pt_dest, pt_src));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__empty_empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");

    _avl_tree_init(pt_src, NULL);
    _avl_tree_init(pt_dest, NULL);
    _avl_tree_assign(pt_dest, pt_src);
    assert_true(_avl_tree_empty(pt_dest));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__non_empty_empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_init(pt_dest, NULL);
    _avl_tree_insert_unique(pt_dest, &elem);
    _avl_tree_assign(pt_dest, pt_src);
    assert_true(_avl_tree_empty(pt_dest));

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__non_empty_non_empty_less(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    elem = 222;
    _avl_tree_insert_unique(pt_src, &elem);
    _avl_tree_init(pt_dest, NULL);
    elem = 897;
    _avl_tree_insert_unique(pt_dest, &elem);
    _avl_tree_assign(pt_dest, pt_src);
    assert_true(_avl_tree_size(pt_dest) == 2);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__non_empty_non_empty_size_equal(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    _avl_tree_init(pt_dest, NULL);
    elem = 334;
    _avl_tree_insert_unique(pt_dest, &elem);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(_avl_tree_begin(pt_dest)) == 334);
    _avl_tree_assign(pt_dest, pt_src);
    assert_true(_avl_tree_size(pt_dest) == 1);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(_avl_tree_begin(pt_dest)) == 9);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__non_empty_non_empty_equal(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    _avl_tree_init(pt_dest, NULL);
    _avl_tree_insert_unique(pt_dest, &elem);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(_avl_tree_begin(pt_dest)) == 9);
    _avl_tree_assign(pt_dest, pt_src);
    assert_true(_avl_tree_size(pt_dest) == 1);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(_avl_tree_begin(pt_dest)) == 9);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__non_empty_non_empty_greater(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    _avl_tree_init(pt_dest, NULL);
    elem = 876;
    _avl_tree_insert_unique(pt_dest, &elem);
    elem = 333;
    _avl_tree_insert_unique(pt_dest, &elem);
    _avl_tree_assign(pt_dest, pt_src);
    assert_true(_avl_tree_size(pt_dest) == 1);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(_avl_tree_begin(pt_dest)) == 9);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

void test__avl_tree_assign__empty_non_empty(void** state)
{
    _avl_tree_t* pt_dest = _create_avl_tree("int");
    _avl_tree_t* pt_src = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_src, NULL);
    _avl_tree_insert_unique(pt_src, &elem);
    _avl_tree_init(pt_dest, NULL);
    _avl_tree_assign(pt_dest, pt_src);
    assert_true(_avl_tree_size(pt_dest) == 1);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(_avl_tree_begin(pt_dest)) == 9);

    _avl_tree_destroy(pt_dest);
    _avl_tree_destroy(pt_src);
}

/*
 * test _avl_tree_size
 */
UT_CASE_DEFINATION(_avl_tree_size)
void test__avl_tree_size__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_size(NULL));
}

void test__avl_tree_size__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_size(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_size__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_size(pt_avl_tree) == 0);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_size__non_empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    assert_true(_avl_tree_size(pt_avl_tree) == 1);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_emtpy
 */
UT_CASE_DEFINATION(_avl_tree_empty)
void test__avl_tree_empty__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_empty(NULL));
}

void test__avl_tree_empty__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 4;
    expect_assert_failure(_avl_tree_empty(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_empty__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_empty(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_empty__non_empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    assert_false(_avl_tree_empty(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_max_size
 */
UT_CASE_DEFINATION(_avl_tree_max_size)
void test__avl_tree_max_size__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_max_size(NULL));
}

void test__avl_tree_max_size__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 4;
    expect_assert_failure(_avl_tree_max_size(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_max_size__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_max_size(pt_avl_tree) > 0);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_max_size__non_empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    assert_true(_avl_tree_max_size(pt_avl_tree) > 0);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_begin
 */
UT_CASE_DEFINATION(_avl_tree_begin)
void test__avl_tree_begin__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_begin(NULL));
}

void test__avl_tree_begin__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 4;
    expect_assert_failure(_avl_tree_begin(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_begin__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_iterator_equal(_avl_tree_begin(pt_avl_tree), _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_begin__non_empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 9;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    assert_true(*(int*)_avl_tree_iterator_get_pointer(_avl_tree_begin(pt_avl_tree)) == 9);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_end
 */
UT_CASE_DEFINATION(_avl_tree_end)
void test__avl_tree_end__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_end(NULL));
}

void test__avl_tree_end__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 4;
    expect_assert_failure(_avl_tree_end(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_end__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_iterator_equal(_avl_tree_begin(pt_avl_tree), _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_end__non_empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem = 9;

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    it_iter = _avl_tree_end(pt_avl_tree);
    it_iter = _avl_tree_iterator_prev(it_iter);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(it_iter) == 9);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_key_comp
 */
UT_CASE_DEFINATION(_avl_tree_key_comp)
void test__avl_tree_key_comp__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_key_comp(NULL));
}

void test__avl_tree_key_comp__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 4;
    expect_assert_failure(_avl_tree_key_comp(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_key_comp__default_key_comp(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_key_comp(pt_avl_tree) == _GET_AVL_TREE_TYPE_LESS_FUNCTION(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void _test__avl_tree_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test__avl_tree_key_comp__user_define_key_comp(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, _test__avl_tree_key_comp__user_define_key_comp);

    assert_true(_avl_tree_key_comp(pt_avl_tree) == _test__avl_tree_key_comp__user_define_key_comp);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_find
 */
UT_CASE_DEFINATION(_avl_tree_find)
void test__avl_tree_find__null_avl_tree(void** state)
{
    int elem = 9;
    expect_assert_failure(_avl_tree_find(NULL, &elem));
}

void test__avl_tree_find__null_value(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_find(pt_avl_tree, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 9;
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 4;
    expect_assert_failure(_avl_tree_find(pt_avl_tree, &elem));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find__c_builtin_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem;
    int i;

    _avl_tree_init(pt_avl_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }

    elem = 2;
    it_iter = _avl_tree_find(pt_avl_tree, &elem);
    assert_true(*(int*)_avl_tree_iterator_get_pointer(it_iter) == 2);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find__c_builtin_not_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int elem;
    int i;

    _avl_tree_init(pt_avl_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }

    elem = 42;
    it_iter = _avl_tree_find(pt_avl_tree, &elem);
    assert_true(_avl_tree_iterator_equal(it_iter, _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find__cstr_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    _avl_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _avl_tree_init(pt_avl_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _avl_tree_insert_unique(pt_avl_tree, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _avl_tree_find(pt_avl_tree, pstr);
    assert_true(strcmp((char*)_avl_tree_iterator_get_pointer(it_iter), "ggg") == 0);

    _avl_tree_destroy(pt_avl_tree);
    string_destroy(pstr);
}

void test__avl_tree_find__cstr_not_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    _avl_tree_iterator_t it_iter;
    string_t* pstr = create_string();

    _avl_tree_init(pt_avl_tree, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "ggg");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "nghl");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "asery");
    _avl_tree_insert_unique(pt_avl_tree, pstr);
    string_assign_cstr(pstr, "linux");
    _avl_tree_insert_unique(pt_avl_tree, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _avl_tree_find(pt_avl_tree, pstr);
    assert_true(_avl_tree_iterator_equal(it_iter, _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
    string_destroy(pstr);
}

void test__avl_tree_find__libcstl_builtin_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("list_t<int>");
    _avl_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _avl_tree_insert_unique(pt_avl_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _avl_tree_find(pt_avl_tree, plist);
    assert_true(*(int*)list_front((list_t*)_avl_tree_iterator_get_pointer(it_iter)) == 6);

    _avl_tree_destroy(pt_avl_tree);
    list_destroy(plist);
}

void test__avl_tree_find__libcstl_builtin_not_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("list_t<int>");
    _avl_tree_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _avl_tree_insert_unique(pt_avl_tree, plist);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _avl_tree_find(pt_avl_tree, plist);
    assert_true(_avl_tree_iterator_equal(it_iter, _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
    list_destroy(plist);
}

typedef struct _tag_test__avl_tree_find__user_define
{
    int n_elem;
}_test__avl_tree_find__user_define_t;
void test__avl_tree_find__user_define_find(void** state)
{
    _avl_tree_t* pt_avl_tree = NULL;
    _avl_tree_iterator_t it_iter;
    _test__avl_tree_find__user_define_t elem;
    int i = 0;

    type_register(_test__avl_tree_find__user_define_t, NULL, NULL, NULL, NULL);

    pt_avl_tree = _create_avl_tree("_test__avl_tree_find__user_define_t");
    _avl_tree_init(pt_avl_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _avl_tree_insert_unique(pt_avl_tree, &elem);
    }

    elem.n_elem = 8;
    it_iter = _avl_tree_find(pt_avl_tree, &elem);
    assert_true(((_test__avl_tree_find__user_define_t*)_avl_tree_iterator_get_pointer(it_iter))->n_elem == 8);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find__user_define_not_find(void** state)
{
    _avl_tree_t* pt_avl_tree =  _create_avl_tree("_test__avl_tree_find__user_define_t");
    _avl_tree_iterator_t it_iter;
    _test__avl_tree_find__user_define_t elem;
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _avl_tree_insert_unique(pt_avl_tree, &elem);
    }

    elem.n_elem = 78;
    it_iter = _avl_tree_find(pt_avl_tree, &elem);
    assert_true(_avl_tree_iterator_equal(it_iter, _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}
