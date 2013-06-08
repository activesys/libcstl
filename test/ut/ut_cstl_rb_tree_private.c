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

#include "ut_def.h"
#include "ut_cstl_rb_tree_private.h"

UT_SUIT_DEFINATION(cstl_rb_tree_private, _create_rb_tree_auxiliary)
/*
 * test _create_rb_tree_auxiliary
 */
UT_CASE_DEFINATION(_create_rb_tree_auxiliary)
void test__create_rb_tree_auxiliary__null_rb_tree(void** state)
{
    expect_assert_failure(_create_rb_tree_auxiliary(NULL, "int"));
}

void test__create_rb_tree_auxiliary__null_typename(void** state)
{
    _rb_tree_t rbtree;
    expect_assert_failure(_create_rb_tree_auxiliary(&rbtree, NULL));
}

void test__create_rb_tree_auxiliary__unregistered(void** state)
{
    _rb_tree_t* pt_rb_tree = malloc(sizeof(_rb_tree_t));
    assert_false(_create_rb_tree_auxiliary(pt_rb_tree, "_test__create_rb_tree_auxiliary__unregistered_t"));

    free(pt_rb_tree);
}

void test__create_rb_tree_auxiliary__c_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = malloc(sizeof(_rb_tree_t));
    assert_true(_create_rb_tree_auxiliary(pt_rb_tree, "int"));
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__create_rb_tree_auxiliary__cstr(void** state)
{
    _rb_tree_t* pt_rb_tree = malloc(sizeof(_rb_tree_t));
    assert_true(_create_rb_tree_auxiliary(pt_rb_tree, "char*"));
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

void test__create_rb_tree_auxiliary__libcstl_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = malloc(sizeof(_rb_tree_t));
    assert_true(_create_rb_tree_auxiliary(pt_rb_tree, "vector_t<int>"));
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

typedef struct _tag_test__create_rb_tree_auxiliary__user_define
{
    int n_elem;
}_test__create_rb_tree_auxiliary__user_define_t;

void test__create_rb_tree_auxiliary__user_define(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;

    type_register(_test__create_rb_tree_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_rb_tree = malloc(sizeof(_rb_tree_t));
    assert_true(_create_rb_tree_auxiliary(pt_rb_tree, "_test__create_rb_tree_auxiliary__user_define_t"));
    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_destroy_auxiliary
 */
UT_CASE_DEFINATION(_rb_tree_destroy_auxiliary)
void test__rb_tree_destroy_auxiliary__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_destroy_auxiliary(NULL));
}

void test__rb_tree_destroy_auxiliary__non_created(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_destroy_auxiliary(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_destroy_auxiliary__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_destroy_auxiliary(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_destroy_auxiliary__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_destroy_auxiliary(pt_rb_tree);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == NULL);
    assert_true(pt_rb_tree->_t_rbroot._pt_left == &pt_rb_tree->_t_rbroot);
    assert_true(pt_rb_tree->_t_rbroot._pt_right == &pt_rb_tree->_t_rbroot);
    assert_true(pt_rb_tree->_t_nodecount == 0);
    assert_true(pt_rb_tree->_t_compare == NULL);
    free(pt_rb_tree);
}

void test__rb_tree_destroy_auxiliary__non_empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    _rb_tree_destroy_auxiliary(pt_rb_tree);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == NULL);
    assert_true(pt_rb_tree->_t_rbroot._pt_left == &pt_rb_tree->_t_rbroot);
    assert_true(pt_rb_tree->_t_rbroot._pt_right == &pt_rb_tree->_t_rbroot);
    assert_true(pt_rb_tree->_t_nodecount == 0);
    assert_true(pt_rb_tree->_t_compare == NULL);
    free(pt_rb_tree);
}

