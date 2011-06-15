#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_rb_tree_iterator.h"
#include "cstl/cstl_rb_tree_private.h"
#include "cstl/cstl_rb_tree.h"
#include "cstl_rb_tree_aux.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"

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

    pt_rb_tree->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_init(pt_rb_tree, NULL));
    pt_rb_tree->_t_rbroot._t_color = red;

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
    pt_dest->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_init_copy(pt_dest, pt_src));
    pt_dest->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_dest);
    _rb_tree_destroy(pt_src);
}

void test__rb_tree_init_copy__non_inited_src(void** state)
{
    _rb_tree_t* pt_dest = _create_rb_tree("int");
    _rb_tree_t* pt_src = _create_rb_tree("int");

    _rb_tree_init(pt_src, NULL);
    pt_src->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_init_copy(pt_dest, pt_src));
    pt_src->_t_rbroot._t_color = red;

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

