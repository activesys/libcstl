#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/citerator.h"
#include "cstl/cstl_avl_tree_iterator.h"
#include "cstl/cstl_avl_tree_private.h"
#include "cstl/cstl_avl_tree.h"
#include "cstl_avl_tree_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_avl_tree_private.h"

UT_SUIT_DEFINATION(cstl_avl_tree_private, _create_avl_tree_auxiliary)
/*
 * test _create_avl_tree_auxiliary
 */
UT_CASE_DEFINATION(_create_avl_tree_auxiliary)
void test__create_avl_tree_auxiliary__null_avl_tree(void** state)
{
    expect_assert_failure(_create_avl_tree_auxiliary(NULL, "int"));
}

void test__create_avl_tree_auxiliary__null_typename(void** state)
{
    _avl_tree_t avltree;
    expect_assert_failure(_create_avl_tree_auxiliary(&avltree, NULL));
}

void test__create_avl_tree_auxiliary__unregistered(void** state)
{
    _avl_tree_t* pt_avl_tree = malloc(sizeof(_avl_tree_t));
    assert_false(_create_avl_tree_auxiliary(pt_avl_tree, "_test__create_avl_tree_auxiliary__unregistered_t"));

    free(pt_avl_tree);
}

void test__create_avl_tree_auxiliary__c_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = malloc(sizeof(_avl_tree_t));
    assert_true(_create_avl_tree_auxiliary(pt_avl_tree, "int"));
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__create_avl_tree_auxiliary__cstr(void** state)
{
    _avl_tree_t* pt_avl_tree = malloc(sizeof(_avl_tree_t));
    assert_true(_create_avl_tree_auxiliary(pt_avl_tree, "char*"));
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

void test__create_avl_tree_auxiliary__libcstl_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = malloc(sizeof(_avl_tree_t));
    assert_true(_create_avl_tree_auxiliary(pt_avl_tree, "vector_t<int>"));
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

typedef struct _tag_test__create_avl_tree_auxiliary__user_define
{
    int n_elem;
}_test__create_avl_tree_auxiliary__user_define_t;

void test__create_avl_tree_auxiliary__user_define(void** state)
{
    _avl_tree_t* pt_avl_tree = NULL;

    type_register(_test__create_avl_tree_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_avl_tree = malloc(sizeof(_avl_tree_t));
    assert_true(_create_avl_tree_auxiliary(pt_avl_tree, "_test__create_avl_tree_auxiliary__user_define_t"));
    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_destroy_auxiliary
 */
UT_CASE_DEFINATION(_avl_tree_destroy_auxiliary)
void test__avl_tree_destroy_auxiliary__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_destroy_auxiliary(NULL));
}

void test__avl_tree_destroy_auxiliary__non_created(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_destroy_auxiliary(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_destroy_auxiliary__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_destroy_auxiliary(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_destroy_auxiliary__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_destroy_auxiliary(pt_avl_tree);
    assert_true(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    assert_true(pt_avl_tree->_t_avlroot._pt_left == &pt_avl_tree->_t_avlroot);
    assert_true(pt_avl_tree->_t_avlroot._pt_right == &pt_avl_tree->_t_avlroot);
    assert_true(pt_avl_tree->_t_nodecount == 0);
    assert_true(pt_avl_tree->_t_compare == NULL);
    free(pt_avl_tree);
}

void test__avl_tree_destroy_auxiliary__non_empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 9;
    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    _avl_tree_destroy_auxiliary(pt_avl_tree);
    assert_true(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    assert_true(pt_avl_tree->_t_avlroot._pt_left == &pt_avl_tree->_t_avlroot);
    assert_true(pt_avl_tree->_t_avlroot._pt_right == &pt_avl_tree->_t_avlroot);
    assert_true(pt_avl_tree->_t_nodecount == 0);
    assert_true(pt_avl_tree->_t_compare == NULL);
    free(pt_avl_tree);
}

