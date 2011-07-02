#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"

#include "ut_def.h"
#include "ut_cstl_set_private.h"

UT_SUIT_DEFINATION(cstl_set_private, _create_set)

/*
 * test _create_set
 */
UT_CASE_DEFINATION(_create_set)
void test__create_set__null_typename(void** state)
{
    expect_assert_failure(_create_set(NULL));
}

void test__create_set__c_builtin(void** state)
{
    set_t* pt_set = _create_set("double");
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

void test__create_set__cstr(void** state)
{
    set_t* pt_set = _create_set("char*");
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

void test__create_set__libcstl_builtin(void** state)
{
    set_t* pt_set = _create_set("vector_t<int>");
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

typedef struct _test_test__create_set__user_define
{
    int n_elem;
}_test__create_set__user_define_t;

void test__create_set__user_define(void** state)
{
    set_t* pt_set = NULL;

    type_register(_test__create_set__user_define_t, NULL, NULL, NULL, NULL);
    pt_set = _create_set("_test__create_set__user_define_t");
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

void test__create_set__unregister(void** state)
{
    set_t* pt_set = _create_set("test__create_set__unregister_t");
    assert_true(pt_set == NULL);
}

/*
 * test _create_set_auxiliary
 */
UT_CASE_DEFINATION(_create_set_auxiliary)
void test__create_set_auxiliary__null_set(void** state)
{
    expect_assert_failure(_create_set_auxiliary(NULL, "int"));
}

void test__create_set_auxiliary__null_typename(void** state)
{
    set_t rbtree;
    expect_assert_failure(_create_set_auxiliary(&rbtree, NULL));
}

void test__create_set_auxiliary__unregistered(void** state)
{
    set_t* pt_set = malloc(sizeof(set_t));
    assert_false(_create_set_auxiliary(pt_set, "_test__create_set_auxiliary__unregistered_t"));

    free(pt_set);
}

void test__create_set_auxiliary__c_builtin(void** state)
{
    set_t* pt_set = malloc(sizeof(set_t));
    assert_true(_create_set_auxiliary(pt_set, "int"));
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

void test__create_set_auxiliary__cstr(void** state)
{
    set_t* pt_set = malloc(sizeof(set_t));
    assert_true(_create_set_auxiliary(pt_set, "char*"));
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

void test__create_set_auxiliary__libcstl_builtin(void** state)
{
    set_t* pt_set = malloc(sizeof(set_t));
    assert_true(_create_set_auxiliary(pt_set, "vector_t<int>"));
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

typedef struct _tag_test__create_set_auxiliary__user_define
{
    int n_elem;
}_test__create_set_auxiliary__user_define_t;

void test__create_set_auxiliary__user_define(void** state)
{
    set_t* pt_set = NULL;

    type_register(_test__create_set_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = malloc(sizeof(set_t));
    assert_true(_create_set_auxiliary(pt_set, "_test__create_set_auxiliary__user_define_t"));
    assert_true(pt_set != NULL);

    set_destroy(pt_set);
}

/*
 * test _set_destroy_auxiliary
 */
UT_CASE_DEFINATION(_set_destroy_auxiliary)
void test__set_destroy_auxiliary__null_set(void** state)
{
    expect_assert_failure(_set_destroy_auxiliary(NULL));
}

void test__set_destroy_auxiliary__non_created(void** state)
{
    set_t* pt_set = _create_set("int");

    pt_set->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_set_destroy_auxiliary(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = RED;

    set_destroy(pt_set);
}

void test__set_destroy_auxiliary__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    set_init(pt_set);

    pt_set->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_set_destroy_auxiliary(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = RED;

    set_destroy(pt_set);
}

void test__set_destroy_auxiliary__empty(void** state)
{
    set_t* pt_set = _create_set("int");
    set_init_ex(pt_set, NULL);

    _set_destroy_auxiliary(pt_set);
    assert_true(pt_set->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_set->_t_tree._t_rbroot._pt_left == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_rbroot._pt_right == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_nodecount == 0);
    assert_true(pt_set->_t_tree._t_compare == NULL);
    free(pt_set);
}

void test__set_destroy_auxiliary__non_empty(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init(pt_set);
    set_insert(pt_set, &elem);

    _set_destroy_auxiliary(pt_set);
    assert_true(pt_set->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_set->_t_tree._t_rbroot._pt_left == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_rbroot._pt_right == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_nodecount == 0);
    assert_true(pt_set->_t_tree._t_compare == NULL);
    free(pt_set);
}

