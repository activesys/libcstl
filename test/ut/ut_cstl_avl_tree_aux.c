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
#include "cstl_avl_tree_aux.h"

#include "ut_def.h"
#include "ut_cstl_avl_tree_aux.h"

UT_SUIT_DEFINATION(cstl_avl_tree_aux, _avl_tree_is_created)
/*
 * test _avl_tree_is_created
 */
UT_CASE_DEFINATION(_avl_tree_is_created)
void test__avl_tree_is_created__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_is_created(NULL));
}

void test__avl_tree_is_created__non_inited_allocator(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    avltree._t_allocator._t_mempoolsize = 1;
    assert_false(_avl_tree_is_created(&avltree));
    avltree._t_allocator._t_mempoolsize = 0;
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_avlroot_left(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = &avltree._t_avlroot;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_avlroot_right(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = &avltree._t_avlroot;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_avlroot_parent(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = &avltree._t_avlroot;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_avlroot_height(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 6;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_compare(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = (binary_function_t)0x888;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_nodecount(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 9;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_typeinfo_style(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = 90;
    avltree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__invalid_typeinfo_type(void** state)
{
    _avl_tree_t avltree;

    avltree._t_avlroot._pt_left = NULL;
    avltree._t_avlroot._pt_right = NULL;
    avltree._t_avlroot._pt_parent = NULL;
    avltree._t_avlroot._un_height = 0;
    avltree._t_compare = NULL;
    avltree._t_nodecount = 0;
    avltree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    avltree._t_typeinfo._pt_type = NULL;
    _alloc_init(&avltree._t_allocator);
    assert_false(_avl_tree_is_created(&avltree));
    _alloc_destroy(&avltree._t_allocator);
}

void test__avl_tree_is_created__created(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    assert_true(_avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_is_inited
 */
UT_CASE_DEFINATION(_avl_tree_is_inited)
void test__avl_tree_is_inited__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_is_inited(NULL));
}

void test__avl_tree_is_inited__invalid_typeinfo_style(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_typeinfo._t_style = 999;
    assert_false(_avl_tree_is_inited(pt_avl_tree));
    pt_avl_tree->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_is_inited__invalid_typeinfo_type(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _type_t* pt_type = NULL;

    _avl_tree_init(pt_avl_tree, NULL);

    pt_type = pt_avl_tree->_t_typeinfo._pt_type;
    pt_avl_tree->_t_typeinfo._pt_type = NULL;
    assert_false(_avl_tree_is_inited(pt_avl_tree));
    pt_avl_tree->_t_typeinfo._pt_type = pt_type;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_is_inited__invalid_avlroot_left(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avlnode_t* pt_avl_node = NULL;

    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_node = pt_avl_tree->_t_avlroot._pt_left;
    pt_avl_tree->_t_avlroot._pt_left = NULL;
    assert_false(_avl_tree_is_inited(pt_avl_tree));
    pt_avl_tree->_t_avlroot._pt_left = pt_avl_node;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_is_inited__invalid_avlroot_right(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avlnode_t* pt_avl_node = NULL;

    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_node = pt_avl_tree->_t_avlroot._pt_right;
    pt_avl_tree->_t_avlroot._pt_right = NULL;
    assert_false(_avl_tree_is_inited(pt_avl_tree));
    pt_avl_tree->_t_avlroot._pt_right = pt_avl_node;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_is_inited__invalid_avlroot_height(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 5;
    assert_false(_avl_tree_is_inited(pt_avl_tree));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_is_inited__invalid_compare(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    binary_function_t t_compare = NULL;

    _avl_tree_init(pt_avl_tree, NULL);

    t_compare = pt_avl_tree->_t_compare;
    pt_avl_tree->_t_compare = NULL;
    assert_false(_avl_tree_is_inited(pt_avl_tree));
    pt_avl_tree->_t_compare = t_compare;

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_iterator_belong_to_avl_tree
 */
UT_CASE_DEFINATION(_avl_tree_iterator_belong_to_avl_tree)
void test__avl_tree_iterator_belong_to_avl_tree__null_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_iterator_belong_to_avl_tree(NULL, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__non_inited_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pt_avl_tree, NULL);
    it_iter = _avl_tree_begin(pt_avl_tree);
    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, it_iter));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__invalid_iter_corepos(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pt_avl_tree, NULL);
    it_iter = _avl_tree_begin(pt_avl_tree);
    it_iter._t_pos._t_treepos._pc_corepos = NULL;
    expect_assert_failure(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__invalid_iter_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pt_avl_tree, NULL);
    it_iter = _avl_tree_begin(pt_avl_tree);
    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__empty_begin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    assert_true(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__empty_end(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    assert_true(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__non_empty_begin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }
    assert_true(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__non_empty_end(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }
    assert_true(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, _avl_tree_end(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__non_empty_middle(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }
    assert_true(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, _avl_tree_iterator_next(_avl_tree_begin(pt_avl_tree))));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_iterator_belong_to_avl_tree__invalid_pos(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }
    it_iter = _avl_tree_begin(pt_avl_tree);
    it_iter._t_pos._t_treepos._pc_corepos = (char*)0x888;
    assert_false(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_same_avl_tree_iterator_type
 */
UT_CASE_DEFINATION(_avl_tree_same_avl_tree_iterator_type)
void test__avl_tree_same_avl_tree_iterator_type__null_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_same_avl_tree_iterator_type(NULL, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type__non_created(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t avltree;

    _avl_tree_init(pt_avl_tree, NULL);
    avltree._t_avlroot._un_height = 123;
    expect_assert_failure(_avl_tree_same_avl_tree_iterator_type(&avltree, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type__invalid_iter(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pt_avl_tree, NULL);
    it_iter = _avl_tree_begin(pt_avl_tree);
    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type__same_container(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pt_avl_tree, NULL);
    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type__same(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t* pt_iter = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_init(pt_iter, NULL);
    assert_true(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, _avl_tree_begin(pt_iter)));

    _avl_tree_destroy(pt_avl_tree);
    _avl_tree_destroy(pt_iter);
}

void test__avl_tree_same_avl_tree_iterator_type__not_same(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t* pt_iter = _create_avl_tree("double");

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_init(pt_iter, NULL);
    assert_false(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, _avl_tree_begin(pt_iter)));

    _avl_tree_destroy(pt_avl_tree);
    _avl_tree_destroy(pt_iter);
}

/*
 * test _avl_tree_avlnode_belong_to_avl_tree
 */
UT_CASE_DEFINATION(_avl_tree_avlnode_belong_to_avl_tree)
void test__avl_tree_avlnode_belong_to_avl_tree__null_root(void** state)
{
    _avlnode_t t_pos;
    assert_false(_avl_tree_avlnode_belong_to_avl_tree(NULL, &t_pos));
}

void test__avl_tree_avlnode_belong_to_avl_tree__null_pos(void** state)
{
    _avlnode_t t_root;
    assert_false(_avl_tree_avlnode_belong_to_avl_tree(&t_root, NULL));
}

void test__avl_tree_avlnode_belong_to_avl_tree__equal(void** state)
{
    _avlnode_t t_node;
    assert_true(_avl_tree_avlnode_belong_to_avl_tree(&t_node, &t_node));
}

void test__avl_tree_avlnode_belong_to_avl_tree__find(void** state)
{
    _avlnode_t t_root;
    _avlnode_t t_left;
    _avlnode_t t_right;

    t_root._pt_left = &t_left;
    t_root._pt_right = &t_right;
    t_root._pt_parent = NULL;
    t_left._pt_left = t_left._pt_right = NULL;
    t_left._pt_parent = &t_root;
    t_right._pt_left = t_right._pt_right = NULL;
    t_right._pt_parent = &t_root;

    assert_true(_avl_tree_avlnode_belong_to_avl_tree(&t_root, &t_right));
}

void test__avl_tree_avlnode_belong_to_avl_tree__not_find(void** state)
{
    _avlnode_t t_root;
    _avlnode_t t_left;
    _avlnode_t t_right;
    _avlnode_t t_pos;

    t_root._pt_left = &t_left;
    t_root._pt_right = &t_right;
    t_root._pt_parent = NULL;
    t_left._pt_left = t_left._pt_right = NULL;
    t_left._pt_parent = &t_root;
    t_right._pt_left = t_right._pt_right = NULL;
    t_right._pt_parent = &t_root;

    assert_false(_avl_tree_avlnode_belong_to_avl_tree(&t_root, &t_pos));
}

/*
 * test _avl_tree_same_type
 */
UT_CASE_DEFINATION(_avl_tree_same_type)
void test__avl_tree_same_type__null_first(void** state)
{
    _avl_tree_t avltree;

    expect_assert_failure(_avl_tree_same_type(NULL, &avltree));
}

void test__avl_tree_same_type__null_second(void** state)
{
    _avl_tree_t avltree;

    expect_assert_failure(_avl_tree_same_type(&avltree, NULL));
}

void test__avl_tree_same_type__non_created_first(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");

    pt_first->_t_avlroot._un_height = 5;
    expect_assert_failure(_avl_tree_same_type(pt_first, pt_second));
    pt_first->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type__non_created_second(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");

    pt_second->_t_avlroot._un_height = 5;
    expect_assert_failure(_avl_tree_same_type(pt_first, pt_second));
    pt_second->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type__same_type(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");

    assert_true(_avl_tree_same_type(pt_first, pt_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type__not_same_type(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("double");

    assert_false(_avl_tree_same_type(pt_first, pt_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type__not_same_compare(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");
    binary_function_t t_compare = (binary_function_t)0x998;

    _avl_tree_init(pt_first, NULL);
    _avl_tree_init(pt_second, t_compare);
    assert_false(_avl_tree_same_type(pt_first, pt_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

/*
 * test _avl_tree_find_value
 */
UT_CASE_DEFINATION(_avl_tree_find_value)
void test__avl_tree_find_value__null_avl_tree(void** state)
{
    int elem = 90;
    expect_assert_failure(_avl_tree_find_value(NULL, NULL, &elem));
}

void test__avl_tree_find_value__null_value(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_find_value(pt_avl_tree, NULL, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

