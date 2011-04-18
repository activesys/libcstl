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

