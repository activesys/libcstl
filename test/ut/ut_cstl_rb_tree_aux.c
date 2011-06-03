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

/*
 * test _rb_tree_iterator_belong_to_rb_tree
 */
UT_CASE_DEFINATION(_rb_tree_iterator_belong_to_rb_tree)
void test__rb_tree_iterator_belong_to_rb_tree__null_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_iterator_belong_to_rb_tree(NULL, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__non_inited_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    pt_rb_tree->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, it_iter));
    pt_rb_tree->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__invalid_iter_corepos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    it_iter._t_pos._t_treepos._pc_corepos = NULL;
    expect_assert_failure(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__invalid_iter_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__empty_begin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_true(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__empty_end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_true(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__non_empty_begin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    assert_true(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__non_empty_end(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    assert_true(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, _rb_tree_end(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__non_empty_middle(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    assert_true(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, _rb_tree_iterator_next(_rb_tree_begin(pt_rb_tree))));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__invalid_pos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    it_iter = _rb_tree_begin(pt_rb_tree);
    it_iter._t_pos._t_treepos._pc_corepos = (char*)0x888;
    assert_false(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_same_rb_tree_iterator_type
 */
UT_CASE_DEFINATION(_rb_tree_same_rb_tree_iterator_type)
void test__rb_tree_same_rb_tree_iterator_type__null_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_same_rb_tree_iterator_type(NULL, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type__non_created(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_t rbtree;

    _rb_tree_init(pt_rb_tree, NULL);
    rbtree._t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_same_rb_tree_iterator_type(&rbtree, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type__invalid_iter(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type__same_container(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type__same(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_t* pt_iter = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_init(pt_iter, NULL);
    assert_true(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, _rb_tree_begin(pt_iter)));

    _rb_tree_destroy(pt_rb_tree);
    _rb_tree_destroy(pt_iter);
}

void test__rb_tree_same_rb_tree_iterator_type__not_same(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_t* pt_iter = _create_rb_tree("double");

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_init(pt_iter, NULL);
    assert_false(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, _rb_tree_begin(pt_iter)));

    _rb_tree_destroy(pt_rb_tree);
    _rb_tree_destroy(pt_iter);
}

/*
 * test _rb_tree_same_rb_tree_iterator_type_ex
 */
UT_CASE_DEFINATION(_rb_tree_same_rb_tree_iterator_type_ex)
void test__rb_tree_same_rb_tree_iterator_type_ex__null_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_same_rb_tree_iterator_type_ex(NULL, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type_ex__non_created(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_t rbtree;

    _rb_tree_init(pt_rb_tree, NULL);
    rbtree._t_rbroot._t_color = red;
    expect_assert_failure(_rb_tree_same_rb_tree_iterator_type_ex(&rbtree, _rb_tree_begin(pt_rb_tree)));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type_ex__invalid_iter(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_rb_tree_same_rb_tree_iterator_type_ex(pt_rb_tree, it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type_ex__same_container(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    assert_true(_rb_tree_same_rb_tree_iterator_type_ex(pt_rb_tree, it_iter));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_same_rb_tree_iterator_type_ex__same(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_t* pt_iter = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_init(pt_iter, NULL);
    assert_true(_rb_tree_same_rb_tree_iterator_type_ex(pt_rb_tree, _rb_tree_begin(pt_iter)));

    _rb_tree_destroy(pt_rb_tree);
    _rb_tree_destroy(pt_iter);
}

void test__rb_tree_same_rb_tree_iterator_type_ex__not_same(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_t* pt_iter = _create_rb_tree("double");

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_init(pt_iter, NULL);
    assert_false(_rb_tree_same_rb_tree_iterator_type_ex(pt_rb_tree, _rb_tree_begin(pt_iter)));

    _rb_tree_destroy(pt_rb_tree);
    _rb_tree_destroy(pt_iter);
}

/*
 * test _rb_tree_rbnode_belong_to_rb_tree
 */
UT_CASE_DEFINATION(_rb_tree_rbnode_belong_to_rb_tree)
void test__rb_tree_rbnode_belong_to_rb_tree__null_root(void** state)
{
    _rbnode_t t_pos;
    assert_false(_rb_tree_rbnode_belong_to_rb_tree(NULL, &t_pos));
}

void test__rb_tree_rbnode_belong_to_rb_tree__null_pos(void** state)
{
    _rbnode_t t_root;
    assert_false(_rb_tree_rbnode_belong_to_rb_tree(&t_root, NULL));
}

void test__rb_tree_rbnode_belong_to_rb_tree__equal(void** state)
{
    _rbnode_t t_node;
    assert_true(_rb_tree_rbnode_belong_to_rb_tree(&t_node, &t_node));
}

void test__rb_tree_rbnode_belong_to_rb_tree__find(void** state)
{
    _rbnode_t t_root;
    _rbnode_t t_left;
    _rbnode_t t_right;

    t_root._pt_left = &t_left;
    t_root._pt_right = &t_right;
    t_root._pt_parent = NULL;
    t_left._pt_left = t_left._pt_right = NULL;
    t_left._pt_parent = &t_root;
    t_right._pt_left = t_right._pt_right = NULL;
    t_right._pt_parent = &t_root;

    assert_true(_rb_tree_rbnode_belong_to_rb_tree(&t_root, &t_right));
}

void test__rb_tree_rbnode_belong_to_rb_tree__not_find(void** state)
{
    _rbnode_t t_root;
    _rbnode_t t_left;
    _rbnode_t t_right;
    _rbnode_t t_pos;

    t_root._pt_left = &t_left;
    t_root._pt_right = &t_right;
    t_root._pt_parent = NULL;
    t_left._pt_left = t_left._pt_right = NULL;
    t_left._pt_parent = &t_root;
    t_right._pt_left = t_right._pt_right = NULL;
    t_right._pt_parent = &t_root;

    assert_false(_rb_tree_rbnode_belong_to_rb_tree(&t_root, &t_pos));
}

