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
/*#include "cstl/cstl_rb_tree.h"*/
#include "cstl_rb_tree_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_rb_tree_aux.h"

UT_SUIT_DEFINATION(cstl_rb_tree_aux, _rb_tree_is_created)
/*
 * test _rb_tree_is_created
 */
UT_CASE_DEFINATION(_rb_tree_is_created)
void test__rb_tree_is_created__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_is_created(NULL));
}

void test__rb_tree_is_created__non_inited_allocator(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    rbtree._t_allocator._t_mempoolsize = 1;
    assert_false(_rb_tree_is_created(&rbtree));
    rbtree._t_allocator._t_mempoolsize = 0;
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_rbroot_left(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = &rbtree._t_rbroot;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_rbroot_right(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = &rbtree._t_rbroot;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_rbroot_parent(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = &rbtree._t_rbroot;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_rbroot_color(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = black;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_compare(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = (binary_function_t)0x888;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_nodecount(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 9;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_typeinfo_style(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = 90;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_typeinfo_type(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = NULL;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = red;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = NULL;
    _alloc_init(&rbtree._t_allocator);
    assert_false(_rb_tree_is_created(&rbtree));
    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__created(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    assert_true(_rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_is_inited
 */
UT_CASE_DEFINATION(_rb_tree_is_inited)
void test__rb_tree_is_inited__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_is_inited(NULL));
}

void test__rb_tree_is_inited__invalid_typeinfo_style(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_typeinfo._t_style = 999;
    assert_false(_rb_tree_is_inited(pt_rb_tree));
    pt_rb_tree->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_is_inited__invalid_typeinfo_type(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _type_t* pt_type = NULL;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_type = pt_rb_tree->_t_typeinfo._pt_type;
    pt_rb_tree->_t_typeinfo._pt_type = NULL;
    assert_false(_rb_tree_is_inited(pt_rb_tree));
    pt_rb_tree->_t_typeinfo._pt_type = pt_type;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_is_inited__invalid_rbroot_left(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_rb_node = NULL;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_node = pt_rb_tree->_t_rbroot._pt_left;
    pt_rb_tree->_t_rbroot._pt_left = NULL;
    assert_false(_rb_tree_is_inited(pt_rb_tree));
    pt_rb_tree->_t_rbroot._pt_left = pt_rb_node;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_is_inited__invalid_rbroot_right(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_rb_node = NULL;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_node = pt_rb_tree->_t_rbroot._pt_right;
    pt_rb_tree->_t_rbroot._pt_right = NULL;
    assert_false(_rb_tree_is_inited(pt_rb_tree));
    pt_rb_tree->_t_rbroot._pt_right = pt_rb_node;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_is_inited__invalid_rbroot_color(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = black;
    assert_false(_rb_tree_is_inited(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_is_inited__invalid_compare(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    binary_function_t t_compare = NULL;

    _rb_tree_init(pt_rb_tree, NULL);

    t_compare = pt_rb_tree->_t_compare;
    pt_rb_tree->_t_compare = NULL;
    assert_false(_rb_tree_is_inited(pt_rb_tree));
    pt_rb_tree->_t_compare = t_compare;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_is_inited__inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_is_inited(pt_rb_tree));

    _rb_tree_destroy(pt_rb_tree);
}

