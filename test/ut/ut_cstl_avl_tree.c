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

