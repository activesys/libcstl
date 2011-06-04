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

/*
 * test _rb_tree_same_type
 */
UT_CASE_DEFINATION(_rb_tree_same_type)
void test__rb_tree_same_type__null_first(void** state)
{
    _rb_tree_t rbtree;

    expect_assert_failure(_rb_tree_same_type(NULL, &rbtree));
}

void test__rb_tree_same_type__null_second(void** state)
{
    _rb_tree_t rbtree;

    expect_assert_failure(_rb_tree_same_type(&rbtree, NULL));
}

void test__rb_tree_same_type__non_created_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    pt_first->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_same_type(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type__non_created_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    pt_second->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_same_type(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type__same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    assert_true(_rb_tree_same_type(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("double");

    assert_false(_rb_tree_same_type(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_same_type_ex
 */
UT_CASE_DEFINATION(_rb_tree_same_type_ex)
void test__rb_tree_same_type_ex__null_first(void** state)
{
    _rb_tree_t rbtree;

    expect_assert_failure(_rb_tree_same_type_ex(NULL, &rbtree));
}

void test__rb_tree_same_type_ex__null_second(void** state)
{
    _rb_tree_t rbtree;

    expect_assert_failure(_rb_tree_same_type_ex(&rbtree, NULL));
}

void test__rb_tree_same_type_ex__non_created_first(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    pt_first->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_same_type_ex(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type_ex__non_created_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    pt_second->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_same_type_ex(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type_ex__same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    assert_true(_rb_tree_same_type_ex(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type_ex__not_same_type(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("double");

    assert_false(_rb_tree_same_type_ex(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type_ex__not_same_compare(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");
    binary_function_t t_compare = (binary_function_t)0x998;

    _rb_tree_init(pt_first, NULL);
    _rb_tree_init(pt_second, t_compare);
    assert_false(_rb_tree_same_type_ex(pt_first, pt_second));

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

/*
 * test _rb_tree_destroy_subtree
 */
UT_CASE_DEFINATION(_rb_tree_destroy_subtree)
void test__rb_tree_destroy_subtree__null_rb_tree(void** state)
{
    expect_assert_failure(_rb_tree_destroy_subtree(NULL, NULL));
}

void test__rb_tree_destroy_subtree__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    pt_rb_tree->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_destroy_subtree(pt_rb_tree, NULL));
    pt_rb_tree->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_destroy_subtree__null_root(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    assert_true(_rb_tree_destroy_subtree(pt_rb_tree, NULL) == NULL);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_destroy_subtree__root(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int i = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    pt_rb_tree->_t_rbroot._pt_parent->_pt_left = _rb_tree_destroy_subtree(
        pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent->_pt_left);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent->_pt_left == NULL);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_find_value
 */
UT_CASE_DEFINATION(_rb_tree_find_value)
void test__rb_tree_find_value__null_rb_tree(void** state)
{
    int elem = 90;
    expect_assert_failure(_rb_tree_find_value(NULL, NULL, &elem));
}

void test__rb_tree_find_value__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 90;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = black;
    expect_assert_failure(_rb_tree_find_value(pt_rb_tree, NULL, &elem));
    pt_rb_tree->_t_rbroot._t_color = red;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find_value__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_find_value(pt_rb_tree, NULL, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find_value__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 100;
    _rb_tree_init(pt_rb_tree, NULL);

    assert_true(_rb_tree_find_value(pt_rb_tree, NULL, &elem) == NULL);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find_value__non_empty_not_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int i = 0;
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    i = 100;
    assert_true(_rb_tree_find_value(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent, &i) == NULL);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_find_value__non_empty_find(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_rb_node = NULL;
    int i = 0;
    _rb_tree_init(pt_rb_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        _rb_tree_insert_unique(pt_rb_tree, &i);
    }
    i = 5;
    pt_rb_node = _rb_tree_find_value(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent, &i);
    assert_true(pt_rb_node != NULL);
    assert_true(*(int*)pt_rb_node->_pc_data == 5);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_clockwise_rotation
 */
UT_CASE_DEFINATION(_rb_tree_clockwise_rotation)
void test__rb_tree_clockwise_rotation__null_root(void** state)
{
    expect_assert_failure(_rb_tree_clockwise_rotation(NULL));
}

void test__rb_tree_clockwise_rotation__null_root_left(void** state)
{
    _rbnode_t node;
    node._pt_left = NULL;
    node._pt_right = NULL;
    node._pt_parent = NULL;
    node._t_color = red;

    expect_assert_failure(_rb_tree_clockwise_rotation(&node));
}

void test__rb_tree_clockwise_rotation__rotate(void** state)
{
    /*
     *     A         B
     *    /         / \
     *   B    =>   C   A
     *  / \           /
     * C   D         D
     */
    _rbnode_t a;
    _rbnode_t b;
    _rbnode_t c;
    _rbnode_t d;

    a._pt_left = &b;
    a._pt_parent = NULL;
    a._pt_right = NULL;
    a._t_color = red;

    b._pt_left = &c;
    b._pt_parent = &a;
    b._pt_right = &d;
    b._t_color = red;

    c._pt_left = NULL;
    c._pt_parent = &b;
    c._pt_right = NULL;
    c._t_color = red;

    d._pt_left = NULL;
    d._pt_parent = &b;
    d._pt_right = NULL;
    d._t_color = red;

    assert_true(_rb_tree_clockwise_rotation(&a) == &b);
    assert_true(b._pt_left == &c && b._pt_right == &a);
    assert_true(c._pt_left == NULL && c._pt_right == NULL && c._pt_parent == &b);
    assert_true(a._pt_left == &d && a._pt_right == NULL && a._pt_parent == &b);
    assert_true(d._pt_left == NULL && d._pt_right == NULL && d._pt_parent == &a);
}

/*
 * test _rb_tree_anticlockwise_rotation
 */
UT_CASE_DEFINATION(_rb_tree_anticlockwise_rotation)
void test__rb_tree_anticlockwise_rotation__null_root(void** state)
{
    expect_assert_failure(_rb_tree_anticlockwise_rotation(NULL));
}

void test__rb_tree_anticlockwise_rotation__null_root_right(void** state)
{
    _rbnode_t node;
    node._pt_left = NULL;
    node._pt_parent = NULL;
    node._pt_right = NULL;
    node._t_color = red;

    expect_assert_failure(_rb_tree_anticlockwise_rotation(&node));
}

void test__rb_tree_anticlockwise_rotation__rotate(void** state)
{
    /*
     *  A              B
     *   \            / \
     *    B     =>   A   D
     *   / \          \
     *  C   D          C
     */
    _rbnode_t a;
    _rbnode_t b;
    _rbnode_t c;
    _rbnode_t d;

    a._pt_left = NULL;
    a._pt_parent = NULL;
    a._pt_right = &b;
    a._t_color = red;

    b._pt_left = &c;
    b._pt_parent = &a;
    b._pt_right = &d;
    b._t_color = red;

    c._pt_left = NULL;
    c._pt_parent = &b;
    c._pt_right = NULL;
    c._t_color = red;

    d._pt_left = NULL;
    d._pt_parent = &b;
    d._pt_right = NULL;
    d._t_color = red;

    assert_true(_rb_tree_anticlockwise_rotation(&a) == &b);
    assert_true(a._pt_left == NULL && a._pt_parent == &b && a._pt_right == &c);
    assert_true(b._pt_left == &a && b._pt_right == &d);
    assert_true(c._pt_left == NULL && c._pt_parent == &a && c._pt_right == NULL);
    assert_true(d._pt_left == NULL && d._pt_parent == &b && d._pt_right == NULL);
}

/*
 * test _rb_tree_insert_rbnode
 */
UT_CASE_DEFINATION(_rb_tree_insert_rbnode)
void test__rb_tree_insert_rbnode__null_rb_tree(void** state)
{
    int elem = 100;
    expect_assert_failure(_rb_tree_insert_rbnode(NULL, &elem));
}

void test__rb_tree_insert_rbnode__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 100;

    expect_assert_failure(_rb_tree_insert_rbnode(pt_rb_tree, &elem));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__null_value(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_insert_rbnode(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__empty(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;
    int elem = 100;

    _rb_tree_init(pt_rb_tree, NULL);
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node == pt_rb_tree->_t_rbroot._pt_parent);
    assert_true(*(int*)pt_node->_pc_data = 100);
    assert_true(pt_node->_pt_left == pt_node->_pt_right);
    assert_true(pt_node->_pt_left == NULL);
    assert_true(pt_node->_t_color == black);

    pt_rb_tree->_t_rbroot._pt_left = pt_node;
    pt_rb_tree->_t_rbroot._pt_right = pt_node;
    pt_rb_tree->_t_nodecount++;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__left_red(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;
    int elem = 0;

    _rbnode_t* pt_5 = NULL;

    _rb_tree_init(pt_rb_tree, NULL);
    /*
     *      5(b)       5(b)
     *           ->   / 
     *               2(r)
     */
    elem = 5;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    pt_5 = pt_rb_tree->_t_rbroot._pt_parent;
    assert_true(*(int*)pt_5->_pc_data == 5);

    elem = 2;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node->_pt_parent == pt_5);
    assert_true(pt_node == pt_5->_pt_left);
    assert_true(*(int*)pt_node->_pc_data == 2);
    assert_true(pt_node->_t_color == red);

    pt_rb_tree->_t_rbroot._pt_left = pt_node;
    pt_rb_tree->_t_rbroot._pt_right = pt_5;
    pt_rb_tree->_t_nodecount++;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__right_red(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;
    int elem = 0;
    _rbnode_t* pt_5 = NULL;

    _rb_tree_init(pt_rb_tree, NULL);
    /*
     *      5(b)      5(b)
     *          ->     \
     *                  8(r)
     */
    elem = 5;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    pt_5 = pt_rb_tree->_t_rbroot._pt_parent;
    assert_true(*(int*)pt_5->_pc_data == 5);

    elem = 8;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node->_pt_parent == pt_5);
    assert_true(pt_node == pt_5->_pt_right);
    assert_true(*(int*)pt_node->_pc_data == 8);
    assert_true(pt_node->_t_color == red);

    pt_rb_tree->_t_rbroot._pt_left = pt_5;
    pt_rb_tree->_t_rbroot._pt_right = pt_node;
    pt_rb_tree->_t_nodecount++;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__children_red(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;
    int elem = 0;
    _rbnode_t* pt_5 = NULL;
    _rbnode_t* pt_2 = NULL;

    _rb_tree_init(pt_rb_tree, NULL);
    /*
     *      5(b)       5(b)
     *       /    ->   /  \
     *      2(r)      2(r) 8(r)
     */
    elem = 5;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 2;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    pt_5 = pt_rb_tree->_t_rbroot._pt_parent;
    pt_2 = pt_5->_pt_left;
    assert_true(*(int*)pt_5->_pc_data == 5);
    assert_true(pt_5->_t_color == black);
    assert_true(pt_2 != NULL);
    assert_true(*(int*)pt_2->_pc_data == 2);
    assert_true(pt_2->_t_color == red);

    elem = 8;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node->_pt_parent == pt_5);
    assert_true(pt_node == pt_5->_pt_right);
    assert_true(*(int*)pt_node->_pc_data == 8);
    assert_true(pt_node->_t_color == red);

    pt_rb_tree->_t_rbroot._pt_left = pt_2;
    pt_rb_tree->_t_rbroot._pt_right = pt_node;
    pt_rb_tree->_t_nodecount++;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__root_red_children(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;

    int elem = 0;
    _rbnode_t* pt_5 = NULL;
    _rbnode_t* pt_2 = NULL;
    _rbnode_t* pt_8 = NULL;

    _rb_tree_init(pt_rb_tree, NULL);
    /*
     *       5(b)           5(b) 
     *      /  \      ->    /  \
     *     2(r) 8(r)       2(b) 8(b)
     *                    /
     *                  1(r)
     */
    elem = 5;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 8;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 2;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    pt_5 = pt_rb_tree->_t_rbroot._pt_parent;
    pt_8 = pt_5->_pt_right;
    pt_2 = pt_5->_pt_left;
    assert_true(*(int*)pt_5->_pc_data == 5);
    assert_true(pt_5->_t_color == black);
    assert_true(*(int*)pt_8->_pc_data == 8);
    assert_true(pt_8->_t_color == red);
    assert_true(*(int*)pt_2->_pc_data == 2);
    assert_true(pt_2->_t_color == red);

    elem = 1;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_5->_t_color == black);
    assert_true(pt_8->_pt_parent == pt_5);
    assert_true(pt_8 == pt_5->_pt_right);
    assert_true(pt_8->_t_color == black);
    assert_true(pt_2->_pt_parent == pt_5);
    assert_true(pt_2 == pt_5->_pt_left);
    assert_true(pt_2->_t_color == black);
    assert_true(pt_node->_pt_parent == pt_2);
    assert_true(pt_node == pt_2->_pt_left);
    assert_true(*(int*)pt_node->_pc_data == 1);
    assert_true(pt_node->_t_color == red);

    pt_rb_tree->_t_rbroot._pt_left = pt_node;
    pt_rb_tree->_t_rbroot._pt_right = pt_8;
    pt_rb_tree->_t_nodecount++; 
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__not_root_red_children(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;

    int elem = 0;
    _rbnode_t* pt_5 = NULL;
    _rbnode_t* pt_3 = NULL;
    _rbnode_t* pt_8 = NULL;
    _rbnode_t* pt_4 = NULL;
    _rbnode_t* pt_1 = NULL;

    _rb_tree_init(pt_rb_tree, NULL);
    /*
     *       5(b)          5(b)   
     *      /  \     ->   /  \
     *     3(b) 8(b)     3(r) 8(b)
     *    /  \          /   \
     *   1(r) 4(r)     1(b)  4(b)
     *                   \
     *                   2(r)
     */
    elem = 5;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 8;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 3;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 1;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 4;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    pt_5 = pt_rb_tree->_t_rbroot._pt_parent;
    pt_8 = pt_5->_pt_right;
    pt_3 = pt_5->_pt_left;
    pt_1 = pt_3->_pt_left;
    pt_4 = pt_3->_pt_right;
    assert_true(*(int*)pt_5->_pc_data == 5);
    assert_true(pt_5->_t_color == black);
    assert_true(*(int*)pt_8->_pc_data == 8);
    assert_true(pt_8->_t_color == black);
    assert_true(*(int*)pt_3->_pc_data == 3);
    assert_true(pt_3->_t_color == black);
    assert_true(*(int*)pt_1->_pc_data == 1);
    assert_true(pt_1->_t_color == red);
    assert_true(*(int*)pt_4->_pc_data == 4);
    assert_true(pt_4->_t_color == red);

    elem = 2;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_5->_t_color == black);
    assert_true(pt_8->_pt_parent == pt_5);
    assert_true(pt_8 == pt_5->_pt_right);
    assert_true(pt_8->_t_color == black);
    assert_true(pt_3->_pt_parent == pt_5);
    assert_true(pt_3 == pt_5->_pt_left);
    assert_true(pt_3->_t_color == red);
    assert_true(pt_1->_pt_parent == pt_3);
    assert_true(pt_1 == pt_3->_pt_left);
    assert_true(pt_1->_t_color == black);
    assert_true(pt_4->_pt_parent == pt_3);
    assert_true(pt_4 == pt_3->_pt_right);
    assert_true(pt_4->_t_color == black);
    assert_true(pt_node->_pt_parent == pt_1);
    assert_true(pt_node == pt_1->_pt_right);
    assert_true(*(int*)pt_node->_pc_data == 2);
    assert_true(pt_node->_t_color == red);

    pt_rb_tree->_t_rbroot._pt_left = pt_1;
    pt_rb_tree->_t_rbroot._pt_right = pt_8;
    pt_rb_tree->_t_nodecount++; 
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__red_left_child(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;

    int elem = 0;
    _rbnode_t* pt_5 = NULL;
    _rbnode_t* pt_3 = NULL;

    _rb_tree_init(pt_rb_tree, NULL);
    /*
     *  5(b)      5(b)        3(b)   
     *   /        /      ->   /  \
     *  3(r) ->  3(r)       1(r) 5(r)
     *          /
     *         1(r)
     */
    elem = 5;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 3;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    pt_5 = pt_rb_tree->_t_rbroot._pt_parent;
    pt_3 = pt_5->_pt_left;
    assert_true(*(int*)pt_5->_pc_data == 5);
    assert_true(pt_5->_t_color == black);
    assert_true(*(int*)pt_3->_pc_data == 3);
    assert_true(pt_3->_t_color == red);

    elem = 1;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_3->_t_color == black);
    assert_true(pt_5->_pt_parent == pt_3);
    assert_true(pt_5 == pt_3->_pt_right);
    assert_true(pt_5->_t_color == red);
    assert_true(pt_node->_pt_parent == pt_3);
    assert_true(pt_node == pt_3->_pt_left);
    assert_true(*(int*)pt_node->_pc_data == 1);
    assert_true(pt_node->_t_color == red);

    pt_rb_tree->_t_rbroot._pt_left = pt_node;
    pt_rb_tree->_t_rbroot._pt_right = pt_5;
    pt_rb_tree->_t_nodecount++; 
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_insert_rbnode__red_right_child(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_node = NULL;

    int elem = 0;
    _rbnode_t* pt_5 = NULL;
    _rbnode_t* pt_3 = NULL;

    _rb_tree_init(pt_rb_tree, NULL);
    /*
     *  5(b)      5(b)        4(b)   
     *   /        /      ->   /  \
     *  3(r) ->  3(r)       3(r) 5(r)
     *            \
     *             4(r)
     */
    elem = 5;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 3;
    _rb_tree_insert_unique(pt_rb_tree, &elem);

    pt_5 = pt_rb_tree->_t_rbroot._pt_parent;
    pt_3 = pt_5->_pt_left;
    assert_true(*(int*)pt_5->_pc_data == 5);
    assert_true(pt_5->_t_color == black);
    assert_true(*(int*)pt_3->_pc_data == 3);
    assert_true(pt_3->_t_color == red);

    elem = 4;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node == pt_rb_tree->_t_rbroot._pt_parent);
    assert_true(pt_node->_t_color == black);
    assert_true(*(int*)pt_node->_pc_data == 4);
    assert_true(pt_node->_pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(pt_3->_t_color == red);
    assert_true(pt_3->_pt_parent == pt_node);
    assert_true(pt_3 == pt_node->_pt_left);
    assert_true(pt_5->_t_color == red);
    assert_true(pt_5 == pt_node->_pt_right);
    assert_true(pt_5->_pt_parent == pt_node);

    pt_rb_tree->_t_rbroot._pt_left = pt_3;
    pt_rb_tree->_t_rbroot._pt_right = pt_5;
    pt_rb_tree->_t_nodecount++; 
    _rb_tree_destroy(pt_rb_tree);
}

