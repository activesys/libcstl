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
#include "cstl/clist.h"

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

#ifdef CSTL_MEMORY_MANAGEMENT
    avltree._t_allocator._t_mempoolsize = 1;
    assert_false(_avl_tree_is_created(&avltree));
    avltree._t_allocator._t_mempoolsize = 0;
#else
    assert_true(_avl_tree_is_created(&avltree));
#endif

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

void test__avl_tree_is_inited__inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_is_inited(pt_avl_tree));

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
    it_iter._t_pos._t_treepos._pby_corepos = NULL;
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
    it_iter._t_pos._t_treepos._pby_corepos = (_byte_t*)0x888;
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
 * test _avl_tree_same_iterator_type
 */
UT_CASE_DEFINATION(_avl_tree_same_iterator_type)
void test__avl_tree_same_iterator_type__null_avl_tree_container(void** state)
{
    _avl_tree_t* pavl_tree = _create_avl_tree("int");
    _avl_tree_init(pavl_tree, NULL);

    expect_assert_failure(_avl_tree_same_iterator_type(NULL, _avl_tree_begin(pavl_tree)));

    _avl_tree_destroy(pavl_tree);
}

void test__avl_tree_same_iterator_type__invalid_iterator_null_container(void** state)
{
    _avl_tree_t* pavl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pavl_tree, NULL);
    it_iter = _avl_tree_begin(pavl_tree);
    it_iter._pt_container = NULL;
    expect_assert_failure(_avl_tree_same_iterator_type(pavl_tree, it_iter));

    _avl_tree_destroy(pavl_tree);
}

void test__avl_tree_same_iterator_type__invalid_iterator_container_type(void** state)
{
    _avl_tree_t* pavl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pavl_tree, NULL);
    it_iter = _avl_tree_begin(pavl_tree);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_avl_tree_same_iterator_type(pavl_tree, it_iter));

    _avl_tree_destroy(pavl_tree);
}

void test__avl_tree_same_iterator_type__invalid_iterator_iterator_type(void** state)
{
    _avl_tree_t* pavl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pavl_tree, NULL);
    it_iter = _avl_tree_begin(pavl_tree);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_avl_tree_same_iterator_type(pavl_tree, it_iter));

    _avl_tree_destroy(pavl_tree);
}

/*
void test__avl_tree_same_iterator_type__same_type_belong_to_avl_tree(void** state)
{
    _avl_tree_t* pavl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pavl_tree, NULL);
    it_iter = _avl_tree_begin(pavl_tree);
    it_iter._t_containertype = _SET_CONTAINER;
    it_iter._t_iteratortype = _BIDIRECTIONAL_ITERATOR;
    assert_true(_avl_tree_same_iterator_type(pavl_tree, it_iter));

    _avl_tree_destroy(pavl_tree);
}

void test__avl_tree_same_iterator_type__same_type_not_belong_to_avl_tree(void** state)
{
    _avl_tree_t* pavl_tree_first = _create_avl_tree("int");
    _avl_tree_t* pavl_tree_second = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pavl_tree_second, NULL);
    it_iter = _avl_tree_begin(pavl_tree_second);
    assert_true(_avl_tree_same_iterator_type(pavl_tree_first, it_iter));

    _avl_tree_destroy(pavl_tree_first);
    _avl_tree_destroy(pavl_tree_second);
}

void test__avl_tree_same_iterator_type__not_same_type(void** state)
{
    _avl_tree_t* pavl_tree_first = _create_avl_tree("int");
    _avl_tree_t* pavl_tree_second = _create_avl_tree("double");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pavl_tree_second, NULL);
    it_iter = _avl_tree_begin(pavl_tree_second);
    assert_false(_avl_tree_same_iterator_type(pavl_tree_first, it_iter));

    _avl_tree_destroy(pavl_tree_first);
    _avl_tree_destroy(pavl_tree_second);
}
*/

void test__avl_tree_same_iterator_type__same_type_not_avl_tree_iterator(void** state)
{
    _avl_tree_t* pavl_tree = _create_avl_tree("int");
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(_avl_tree_same_iterator_type(pavl_tree, list_begin(plist)));

    _avl_tree_destroy(pavl_tree);
    list_destroy(plist);
}

void test__avl_tree_same_iterator_type__not_same_type_not_avl_tree_iterator(void** state)
{
    _avl_tree_t* pavl_tree = _create_avl_tree("int");
    list_t* plist = create_list(double);

    list_init(plist);
    assert_false(_avl_tree_same_iterator_type(pavl_tree, list_begin(plist)));

    _avl_tree_destroy(pavl_tree);
    list_destroy(plist);
}

/*
 * test _avl_tree_same_avl_tree_iterator_type_ex
 */
UT_CASE_DEFINATION(_avl_tree_same_avl_tree_iterator_type_ex)
void test__avl_tree_same_avl_tree_iterator_type_ex__null_avl_tree(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_same_avl_tree_iterator_type_ex(NULL, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type_ex__non_created(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t avltree;

    _avl_tree_init(pt_avl_tree, NULL);
    avltree._t_avlroot._un_height = 123;
    expect_assert_failure(_avl_tree_same_avl_tree_iterator_type_ex(&avltree, _avl_tree_begin(pt_avl_tree)));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type_ex__invalid_iter(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pt_avl_tree, NULL);
    it_iter = _avl_tree_begin(pt_avl_tree);
    it_iter._t_pos._t_treepos._pt_tree = NULL;
    expect_assert_failure(_avl_tree_same_avl_tree_iterator_type_ex(pt_avl_tree, it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type_ex__same_container(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_iterator_t it_iter;

    _avl_tree_init(pt_avl_tree, NULL);
    it_iter = _avl_tree_begin(pt_avl_tree);
    assert_true(_avl_tree_same_avl_tree_iterator_type_ex(pt_avl_tree, it_iter));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_same_avl_tree_iterator_type_ex__same(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t* pt_iter = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_init(pt_iter, NULL);
    assert_true(_avl_tree_same_avl_tree_iterator_type_ex(pt_avl_tree, _avl_tree_begin(pt_iter)));

    _avl_tree_destroy(pt_avl_tree);
    _avl_tree_destroy(pt_iter);
}

void test__avl_tree_same_avl_tree_iterator_type_ex__not_same(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_t* pt_iter = _create_avl_tree("double");

    _avl_tree_init(pt_avl_tree, NULL);
    _avl_tree_init(pt_iter, NULL);
    assert_false(_avl_tree_same_avl_tree_iterator_type_ex(pt_avl_tree, _avl_tree_begin(pt_iter)));

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

/*
 * test _avl_tree_same_type_ex
 */
UT_CASE_DEFINATION(_avl_tree_same_type_ex)
void test__avl_tree_same_type_ex__null_first(void** state)
{
    _avl_tree_t avltree;

    expect_assert_failure(_avl_tree_same_type_ex(NULL, &avltree));
}

void test__avl_tree_same_type_ex__null_second(void** state)
{
    _avl_tree_t avltree;

    expect_assert_failure(_avl_tree_same_type_ex(&avltree, NULL));
}

void test__avl_tree_same_type_ex__non_created_first(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");

    pt_first->_t_avlroot._un_height = 5;
    expect_assert_failure(_avl_tree_same_type_ex(pt_first, pt_second));
    pt_first->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type_ex__non_created_second(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");

    pt_second->_t_avlroot._un_height = 5;
    expect_assert_failure(_avl_tree_same_type_ex(pt_first, pt_second));
    pt_second->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type_ex__same_type(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");

    assert_true(_avl_tree_same_type_ex(pt_first, pt_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type_ex__not_same_type(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("double");

    assert_false(_avl_tree_same_type_ex(pt_first, pt_second));

    _avl_tree_destroy(pt_first);
    _avl_tree_destroy(pt_second);
}

void test__avl_tree_same_type_ex__not_same_compare(void** state)
{
    _avl_tree_t* pt_first = _create_avl_tree("int");
    _avl_tree_t* pt_second = _create_avl_tree("int");
    binary_function_t t_compare = (binary_function_t)0x998;

    _avl_tree_init(pt_first, NULL);
    _avl_tree_init(pt_second, t_compare);
    assert_false(_avl_tree_same_type_ex(pt_first, pt_second));

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

void test__avl_tree_find_value__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 90;
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_find_value(pt_avl_tree, NULL, &elem));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find_value__null_value(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_find_value(pt_avl_tree, NULL, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find_value__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 100;
    _avl_tree_init(pt_avl_tree, NULL);

    assert_true(_avl_tree_find_value(pt_avl_tree, NULL, &elem) == NULL);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find_value__non_empty_not_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int i = 0;
    _avl_tree_init(pt_avl_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }
    i = 100;
    assert_true(_avl_tree_find_value(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, &i) == NULL);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_find_value__non_empty_find(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avlnode_t* pt_avl_node = NULL;
    int i = 0;
    _avl_tree_init(pt_avl_tree, NULL);

    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }
    i = 5;
    pt_avl_node = _avl_tree_find_value(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, &i);
    assert_true(pt_avl_node != NULL);
    assert_true(*(int*)pt_avl_node->_pby_data == 5);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_destroy_subtree
 */
UT_CASE_DEFINATION(_avl_tree_destroy_subtree)
void test__avl_tree_destroy_subtree__null_avl_tree(void** state)
{
    expect_assert_failure(_avl_tree_destroy_subtree(NULL, NULL));
}

void test__avl_tree_destroy_subtree__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_destroy_subtree(pt_avl_tree, NULL));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_destroy_subtree__null_root(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    assert_true(_avl_tree_destroy_subtree(pt_avl_tree, NULL) == NULL);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_destroy_subtree__root(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int i = 0;

    _avl_tree_init(pt_avl_tree, NULL);
    for(i = 0; i < 10; ++i)
    {
        _avl_tree_insert_unique(pt_avl_tree, &i);
    }
    pt_avl_tree->_t_avlroot._pt_parent->_pt_left = _avl_tree_destroy_subtree(
        pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent->_pt_left);
    assert_true(pt_avl_tree->_t_avlroot._pt_parent->_pt_left == NULL);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_left_signal_rotate
 */
UT_CASE_DEFINATION(_avl_tree_left_signal_rotate)
void test__avl_tree_left_signal_rotate__null_root(void** state)
{
    expect_assert_failure(_avl_tree_left_signal_rotate(NULL));
}

void test__avl_tree_left_signal_rotate__null_root_left(void** state)
{
    _avlnode_t node;
    node._pt_left = NULL;
    node._pt_right = NULL;
    node._pt_parent = NULL;
    node._un_height = 0;

    expect_assert_failure(_avl_tree_left_signal_rotate(&node));
}

void test__avl_tree_left_signal_rotate__rotate(void** state)
{
    /*
     *     A         B
     *    /         / \
     *   B    =>   C   A
     *  / \           /
     * C   D         D
     */
    _avlnode_t a;
    _avlnode_t b;
    _avlnode_t c;
    _avlnode_t d;

    a._pt_left = &b;
    a._pt_parent = NULL;
    a._pt_right = NULL;
    a._un_height = 2;

    b._pt_left = &c;
    b._pt_parent = &a;
    b._pt_right = &d;
    b._un_height = 1;

    c._pt_left = NULL;
    c._pt_parent = &b;
    c._pt_right = NULL;
    c._un_height = 0;

    d._pt_left = NULL;
    d._pt_parent = &b;
    d._pt_right = NULL;
    d._un_height = 0;

    assert_true(_avl_tree_left_signal_rotate(&a) == &b);
    assert_true(a._un_height == 1);
    assert_true(b._un_height == 2);
    assert_true(c._un_height == 0);
    assert_true(d._un_height == 0);
    assert_true(b._pt_left == &c && b._pt_right == &a);
    assert_true(c._pt_left == NULL && c._pt_right == NULL && c._pt_parent == &b);
    assert_true(a._pt_left == &d && a._pt_right == NULL && a._pt_parent == &b);
    assert_true(d._pt_left == NULL && d._pt_right == NULL && d._pt_parent == &a);
}

/*
 * test _avl_tree_right_signal_rotate
 */
UT_CASE_DEFINATION(_avl_tree_right_signal_rotate)
void test__avl_tree_right_signal_rotate__null_root(void** state)
{
    expect_assert_failure(_avl_tree_right_signal_rotate(NULL));
}

void test__avl_tree_right_signal_rotate__null_root_right(void** state)
{
    _avlnode_t node;
    node._pt_left = NULL;
    node._pt_parent = NULL;
    node._pt_right = NULL;
    node._un_height = 0;

    expect_assert_failure(_avl_tree_right_signal_rotate(&node));
}

void test__avl_tree_right_signal_rotate__rotate(void** state)
{
    /*
     *  A              B
     *   \            / \
     *    B     =>   A   D
     *   / \          \
     *  C   D          C
     */
    _avlnode_t a;
    _avlnode_t b;
    _avlnode_t c;
    _avlnode_t d;

    a._pt_left = NULL;
    a._pt_parent = NULL;
    a._pt_right = &b;
    a._un_height = 2;

    b._pt_left = &c;
    b._pt_parent = &a;
    b._pt_right = &d;
    b._un_height = 1;

    c._pt_left = NULL;
    c._pt_parent = &b;
    c._pt_right = NULL;
    c._un_height = 0;

    d._pt_left = NULL;
    d._pt_parent = &b;
    d._pt_right = NULL;
    d._un_height = 0;

    assert_true(_avl_tree_right_signal_rotate(&a) == &b);
    assert_true(a._un_height == 1);
    assert_true(b._un_height == 2);
    assert_true(c._un_height == 0);
    assert_true(d._un_height == 0);
    assert_true(a._pt_left == NULL && a._pt_parent == &b && a._pt_right == &c);
    assert_true(b._pt_left == &a && b._pt_right == &d);
    assert_true(c._pt_left == NULL && c._pt_parent == &a && c._pt_right == NULL);
    assert_true(d._pt_left == NULL && d._pt_parent == &b && d._pt_right == NULL);
}

/*
 * test _avl_tree_left_double_rotate
 */
UT_CASE_DEFINATION(_avl_tree_left_double_rotate)
void test__avl_tree_left_double_rotate__null_root(void** state)
{
    expect_assert_failure(_avl_tree_left_double_rotate(NULL));
}

void test__avl_tree_left_double_rotate__rotate(void** state)
{
    /*
     *       A               A                 E
     *      / \             / \              /   \
     *     B   C           E   C            B     A
     *    / \       =>    / \        =>    / \   / \
     *   D   E           B   G            D   F G   C
     *      / \         / \
     *     F   G       D   F
     */        
    _avlnode_t a;
    _avlnode_t b;
    _avlnode_t c;
    _avlnode_t d;
    _avlnode_t e;
    _avlnode_t f;
    _avlnode_t g;

    a._pt_left = &b;
    a._pt_parent = NULL;
    a._pt_right = &c;
    a._un_height = 3;

    b._pt_left = &d;
    b._pt_parent = &a;
    b._pt_right = &e;
    b._un_height = 2;

    c._pt_left = NULL;
    c._pt_parent = &a;
    c._pt_right = NULL;
    c._un_height = 0;

    d._pt_left = NULL;
    d._pt_parent = &b;
    d._pt_right = NULL;
    d._un_height = 0;

    e._pt_left = &f;
    e._pt_parent = &b;
    e._pt_right = &g;
    e._un_height = 1;

    f._pt_left = NULL;
    f._pt_parent = &e;
    f._pt_right = NULL;
    f._un_height = 0;

    g._pt_left = NULL;
    g._pt_parent = &e;
    g._pt_right = NULL;
    g._un_height = 0;

    /*
     *       A               A                 E
     *      / \             / \              /   \
     *     B   C           E   C            B     A
     *    / \       =>    / \        =>    / \   / \
     *   D   E           B   G            D   F G   C
     *      / \         / \
     *     F   G       D   F
     */        
    assert_true(_avl_tree_left_double_rotate(&a) == &e);
    assert_true(a._un_height == 1);
    assert_true(b._un_height == 1);
    assert_true(c._un_height == 0);
    assert_true(d._un_height == 0);
    assert_true(e._un_height == 2);
    assert_true(f._un_height == 0);
    assert_true(g._un_height == 0);
    assert_true(a._pt_left == &g && a._pt_parent == &e && a._pt_right == &c);
    assert_true(b._pt_left == &d && b._pt_parent == &e && b._pt_right == &f);
    assert_true(c._pt_left == NULL && c._pt_parent == &a && c._pt_right == NULL);
    assert_true(d._pt_left == NULL && d._pt_parent == &b && d._pt_right == NULL);
    assert_true(e._pt_left == &b && e._pt_right == &a);
    assert_true(f._pt_left == NULL && f._pt_parent == &b && f._pt_right == NULL);
    assert_true(g._pt_left == NULL && g._pt_parent == &a && g._pt_right == NULL);
}

/*
 * test _avl_tree_right_double_rotate
 */
UT_CASE_DEFINATION(_avl_tree_right_double_rotate)
void test__avl_tree_right_double_rotate__null_root(void** state)
{
    expect_assert_failure(_avl_tree_right_double_rotate(NULL));
}

void test__avl_tree_right_double_rotate__rotate(void** state)
{
    /*
     *       A               A                   D 
     *      / \             / \                /   \
     *     B   C           B   D              A     C
     *        / \    =>       / \       =>   / \   / \
     *       D   E           F   C          B   F G   E
     *      / \                 / \
     *     F   G               G   E
     */
    _avlnode_t a;
    _avlnode_t b;
    _avlnode_t c;
    _avlnode_t d;
    _avlnode_t e;
    _avlnode_t f;
    _avlnode_t g;

    a._pt_left = &b;
    a._pt_parent = NULL;
    a._pt_right = &c;
    a._un_height = 3;

    b._pt_left = NULL;
    b._pt_parent = &a;
    b._pt_right = NULL;
    b._un_height = 0;

    c._pt_left = &d;
    c._pt_parent = &a;
    c._pt_right = &e;
    c._un_height = 2;

    d._pt_left = &f;
    d._pt_parent = &c;
    d._pt_right = &g;
    d._un_height = 1;

    e._pt_left = NULL;
    e._pt_parent = &c;
    e._pt_right = NULL;
    e._un_height = 0;

    f._pt_left = NULL;
    f._pt_parent = &d;
    f._pt_right = NULL;
    f._un_height = 0;

    g._pt_left = NULL;
    g._pt_parent = &d;
    g._pt_right = NULL;
    g._un_height = 0;

    /*
     *       A               A                   D 
     *      / \             / \                /   \
     *     B   C           B   D              A     C
     *        / \    =>       / \       =>   / \   / \
     *       D   E           F   C          B   F G   E
     *      / \                 / \
     *     F   G               G   E
     */
    assert_true(_avl_tree_right_double_rotate(&a) == &d);
    assert_true(a._un_height == 1);
    assert_true(b._un_height == 0);
    assert_true(c._un_height == 1);
    assert_true(d._un_height == 2);
    assert_true(e._un_height == 0);
    assert_true(f._un_height == 0);
    assert_true(g._un_height == 0);
    assert_true(a._pt_left == &b && a._pt_parent == &d && a._pt_right == &f);
    assert_true(b._pt_left == NULL && b._pt_parent == &a && b._pt_right == NULL);
    assert_true(c._pt_left == &g && c._pt_parent == &d && c._pt_right == &e);
    assert_true(d._pt_left == &a && d._pt_right == &c);
    assert_true(e._pt_left == NULL && e._pt_parent == &c && e._pt_right == NULL);
    assert_true(f._pt_left == NULL && f._pt_parent == &a && f._pt_right == NULL);
    assert_true(g._pt_left == NULL && g._pt_parent == &c && g._pt_right == NULL);
}

/*
 * test _avl_tree_insert_avlnode
 */
UT_CASE_DEFINATION(_avl_tree_insert_avlnode)
void test__avl_tree_insert_avlnode__null_avl_tree(void** state)
{
    int elem = 100;
    expect_assert_failure(_avl_tree_insert_avlnode(NULL, NULL, &elem));
}

void test__avl_tree_insert_avlnode__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 100;

    expect_assert_failure(_avl_tree_insert_avlnode(pt_avl_tree, NULL, &elem));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_insert_avlnode__null_value(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_insert_avlnode(pt_avl_tree, NULL, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_insert_avlnode__empty(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_insert_result_t t_result;
    int elem = 100;

    _avl_tree_init(pt_avl_tree, NULL);
    t_result = _avl_tree_insert_avlnode(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, &elem);
    assert_true(t_result._pt_adjust == t_result._pt_new);
    assert_true(*(int*)t_result._pt_new->_pby_data == 100);
    assert_true(t_result._pt_new->_pt_left == t_result._pt_new->_pt_right);
    assert_true(t_result._pt_new->_pt_left == NULL);
    assert_true(t_result._pt_new->_un_height == 0);

    pt_avl_tree->_t_avlroot._pt_parent = t_result._pt_new;
    pt_avl_tree->_t_avlroot._pt_left = t_result._pt_new;
    pt_avl_tree->_t_avlroot._pt_right = t_result._pt_new;
    pt_avl_tree->_t_nodecount++;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_insert_avlnode__left(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_insert_result_t t_result;
    int elem = 0;
    _avlnode_t* pt_5 = NULL;
    _avlnode_t* pt_2 = NULL;
    _avlnode_t* pt_8 = NULL;

    _avl_tree_init(pt_avl_tree, NULL);
    /*
     *      5         5
     *     / \  ->   / \
     *    2   8     2   8
     *               \
     *                4
     */
    elem = 5;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 2;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 8;
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    pt_5 = pt_avl_tree->_t_avlroot._pt_parent;
    pt_2 = pt_5->_pt_left;
    pt_8 = pt_5->_pt_right;
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(*(int*)pt_2->_pby_data == 2);
    assert_true(*(int*)pt_8->_pby_data == 8);

    elem = 4;
    t_result = _avl_tree_insert_avlnode(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, &elem);
    assert_true(t_result._pt_adjust == pt_5);
    assert_true(t_result._pt_new == pt_2->_pt_right);

    pt_2->_un_height++;
    pt_5->_un_height++;
    pt_avl_tree->_t_nodecount++;
    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_insert_avlnode__right(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_insert_result_t t_result;
    int elem = 0;
    _avlnode_t* pt_5 = NULL;
    _avlnode_t* pt_2 = NULL;
    _avlnode_t* pt_8 = NULL;

    _avl_tree_init(pt_avl_tree, NULL);
    /*
     *      5         5
     *     / \  ->   / \
     *    2   8     2   8
     *                   \
     *                    14
     */
    elem = 5;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 2;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 8;
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    pt_5 = pt_avl_tree->_t_avlroot._pt_parent;
    pt_2 = pt_5->_pt_left;
    pt_8 = pt_5->_pt_right;
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(*(int*)pt_2->_pby_data == 2);
    assert_true(*(int*)pt_8->_pby_data == 8);

    elem = 14;
    t_result = _avl_tree_insert_avlnode(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, &elem);
    assert_true(t_result._pt_adjust == pt_5);
    assert_true(t_result._pt_new == pt_8->_pt_right);

    pt_8->_un_height++;
    pt_5->_un_height++;
    pt_avl_tree->_t_nodecount++;
    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_insert_avlnode__rotate(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_insert_result_t t_result;
    int elem = 0;
    _avlnode_t* pt_5 = NULL;
    _avlnode_t* pt_8 = NULL;

    _avl_tree_init(pt_avl_tree, NULL);
    /*
     *      5         5           8
     *       \  ->     \   ->    / \
     *        8         8       5  14
     *                   \
     *                    14
     */
    elem = 5;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    elem = 8;
    _avl_tree_insert_unique(pt_avl_tree, &elem);

    pt_5 = pt_avl_tree->_t_avlroot._pt_parent;
    pt_8 = pt_5->_pt_right;
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(*(int*)pt_8->_pby_data == 8);

    elem = 14;
    t_result = _avl_tree_insert_avlnode(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, &elem);
    assert_true(t_result._pt_adjust == pt_8);
    assert_true(t_result._pt_new == pt_8->_pt_right);
    assert_true(pt_8->_pt_left == pt_5 && pt_8->_pt_right == t_result._pt_new);
    assert_true(pt_5->_pt_left == NULL && pt_5->_pt_parent == pt_8 && pt_5->_pt_right == NULL);
    assert_true(t_result._pt_new->_pt_left == NULL &&
            t_result._pt_new->_pt_parent == pt_8 &&
            t_result._pt_new->_pt_right == NULL);

    pt_avl_tree->_t_avlroot._pt_parent = pt_8;
    pt_avl_tree->_t_avlroot._pt_left = pt_5;
    pt_avl_tree->_t_avlroot._pt_right = t_result._pt_new;
    pt_8->_pt_parent = &pt_avl_tree->_t_avlroot;
    pt_8->_un_height = 1;
    pt_5->_un_height = 0;
    t_result._pt_new->_un_height = 0;
    pt_avl_tree->_t_nodecount = 3;
    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_get_height
 */
UT_CASE_DEFINATION(_avl_tree_get_height)
void test__avl_tree_get_height__null_root(void** state)
{
    assert_true(_avl_tree_get_height(NULL) == -1);
}

void test__avl_tree_get_heght__not_null(void** state)
{
    _avlnode_t node;
    node._un_height = 5;

    assert_true(_avl_tree_get_height(&node) == 5);
}

/*
 * test _avl_tree_get_min_avlnode
 */
UT_CASE_DEFINATION(_avl_tree_get_min_avlnode)
void test__avl_tree_get_min_avlnode__null_root(void** state)
{
    expect_assert_failure(_avl_tree_get_min_avlnode(NULL));
}

void test__avl_tree_get_min_avlnode__one_node(void** state)
{
    _avlnode_t node;
    node._pt_left = node._pt_right = node._pt_parent = NULL;

    assert_true(_avl_tree_get_min_avlnode(&node) == &node);
}

void test__avl_tree_get_min_avlnode__sub_tree(void** state)
{
    /*
     *    5
     *   / \
     *  2   8
     *   \
     *    4
     */
    _avlnode_t node5;
    _avlnode_t node2;
    _avlnode_t node8;
    _avlnode_t node4;

    node5._pt_left = &node2;
    node5._pt_right = &node8;
    node5._pt_parent = NULL;

    node2._pt_left = NULL;
    node2._pt_right = &node4;
    node2._pt_parent = &node5;

    node8._pt_left = NULL;
    node8._pt_right = NULL;
    node8._pt_parent = &node5;

    node4._pt_left = NULL;
    node4._pt_right = NULL;
    node4._pt_parent = &node2;

    assert_true(_avl_tree_get_min_avlnode(&node5) == &node2);
}

/*
 * test _avl_tree_get_max_avlnode
 */
UT_CASE_DEFINATION(_avl_tree_get_max_avlnode)
void test__avl_tree_get_max_avlnode__null_root(void** state)
{
    expect_assert_failure(_avl_tree_get_max_avlnode(NULL));
}

void test__avl_tree_get_max_avlnode__one_node(void** state)
{
    _avlnode_t node;
    node._pt_left = node._pt_right = node._pt_parent = NULL;

    assert_true(_avl_tree_get_max_avlnode(&node) == &node);
}

void test__avl_tree_get_max_avlnode__sub_tree(void** state)
{
    /*
     *    5
     *   / \
     *  2   8
     *   \
     *    4
     */
    _avlnode_t node5;
    _avlnode_t node2;
    _avlnode_t node8;
    _avlnode_t node4;

    node5._pt_left = &node2;
    node5._pt_right = &node8;
    node5._pt_parent = NULL;

    node2._pt_left = NULL;
    node2._pt_right = &node4;
    node2._pt_parent = &node5;

    node8._pt_left = NULL;
    node8._pt_right = NULL;
    node8._pt_parent = &node5;

    node4._pt_left = NULL;
    node4._pt_right = NULL;
    node4._pt_parent = &node2;

    assert_true(_avl_tree_get_max_avlnode(&node5) == &node8);
}

/*
 * test _avl_tree_rebalance
 */
UT_CASE_DEFINATION(_avl_tree_rebalance)
void test___avl_tree_rebalance__null(void** state)
{
    assert_true(_avl_tree_rebalance(NULL) == NULL);
}

void test__avl_tree_rebalance__ll(void** state)
{
    /*
     *     5        3
     *    /        / \
     *   3    ->  1   5 
     *  /
     * 1
     */
    _avlnode_t node1;
    _avlnode_t node3;
    _avlnode_t node5;

    node5._pt_left = &node3;
    node5._pt_right = NULL;
    node5._pt_parent = NULL;
    node5._un_height = 2;

    node3._pt_left = &node1;
    node3._pt_right = NULL;
    node3._pt_parent = &node5;
    node3._un_height = 1;

    node1._pt_left = NULL;
    node1._pt_right = NULL;
    node1._pt_parent = &node3;
    node1._un_height = 0;

    assert_true(_avl_tree_rebalance(&node5) == &node3);
    assert_true(node3._pt_left == &node1 && node3._pt_right == &node5 && node3._un_height == 1);
    assert_true(node1._pt_left == NULL && node1._pt_parent == &node3 && node1._pt_right == NULL && node1._un_height == 0);
    assert_true(node5._pt_left == NULL && node5._pt_parent == &node3 && node5._pt_right == NULL && node5._un_height == 0);
}

void test__avl_tree_rebalance__lr(void** state)
{
    /*
     *     5        3
     *    /        / \
     *   1    ->  1   5 
     *    \
     *     3
     */
    _avlnode_t node1;
    _avlnode_t node3;
    _avlnode_t node5;

    node5._pt_left = &node1;
    node5._pt_right = NULL;
    node5._pt_parent = NULL;
    node5._un_height = 2;

    node3._pt_left = NULL;
    node3._pt_right = NULL;
    node3._pt_parent = &node1;
    node3._un_height = 0;

    node1._pt_left = NULL;
    node1._pt_right = &node3;
    node1._pt_parent = &node5;
    node1._un_height = 1;

    assert_true(_avl_tree_rebalance(&node5) == &node3);
    assert_true(node3._pt_left == &node1 && node3._pt_right == &node5 && node3._un_height == 1);
    assert_true(node1._pt_left == NULL && node1._pt_parent == &node3 && node1._pt_right == NULL && node1._un_height == 0);
    assert_true(node5._pt_left == NULL && node5._pt_parent == &node3 && node5._pt_right == NULL && node5._un_height == 0);
}

void test__avl_tree_rebalance__rr(void** state)
{
    /*
     * 1            3
     *  \          / \
     *   3    ->  1   5 
     *    \
     *     5
     */
    _avlnode_t node1;
    _avlnode_t node3;
    _avlnode_t node5;

    node5._pt_left = NULL;
    node5._pt_right = NULL;
    node5._pt_parent = &node3;
    node5._un_height = 0;

    node3._pt_left = NULL;
    node3._pt_right = &node5;
    node3._pt_parent = &node1;
    node3._un_height = 1;

    node1._pt_left = NULL;
    node1._pt_right = &node3;
    node1._pt_parent = NULL;
    node1._un_height = 2;

    assert_true(_avl_tree_rebalance(&node1) == &node3);
    assert_true(node3._pt_left == &node1 && node3._pt_right == &node5 && node3._un_height == 1);
    assert_true(node1._pt_left == NULL && node1._pt_parent == &node3 && node1._pt_right == NULL && node1._un_height == 0);
    assert_true(node5._pt_left == NULL && node5._pt_parent == &node3 && node5._pt_right == NULL && node5._un_height == 0);
}

void test__avl_tree_rebalance__rl(void** state)
{
    /*
     * 1            3
     *  \          / \
     *   5    ->  1   5 
     *  /
     * 3
     */
    _avlnode_t node1;
    _avlnode_t node3;
    _avlnode_t node5;

    node5._pt_left = &node3;
    node5._pt_right = NULL;
    node5._pt_parent = &node1;
    node5._un_height = 1;

    node3._pt_left = NULL;
    node3._pt_right = NULL;
    node3._pt_parent = &node5;
    node3._un_height = 0;

    node1._pt_left = NULL;
    node1._pt_right = &node5;
    node1._pt_parent = NULL;
    node1._un_height = 2;

    assert_true(_avl_tree_rebalance(&node1) == &node3);
    assert_true(node3._pt_left == &node1 && node3._pt_right == &node5 && node3._un_height == 1);
    assert_true(node1._pt_left == NULL && node1._pt_parent == &node3 && node1._pt_right == NULL && node1._un_height == 0);
    assert_true(node5._pt_left == NULL && node5._pt_parent == &node3 && node5._pt_right == NULL && node5._un_height == 0);
}

void test__avl_tree_rebalance__no_rotate(void** state)
{
    /*
     *    3
     *   / \
     *  1   5 
     *
     *
     */
    _avlnode_t node1;
    _avlnode_t node3;
    _avlnode_t node5;

    node5._pt_left = NULL;
    node5._pt_right = NULL;
    node5._pt_parent = &node3;
    node5._un_height = 0;

    node3._pt_left = &node1;
    node3._pt_right = &node5;
    node3._pt_parent = NULL;
    node3._un_height = 1;

    node1._pt_left = NULL;
    node1._pt_right = NULL;
    node1._pt_parent = &node3;
    node1._un_height = 0;

    assert_true(_avl_tree_rebalance(&node3) == &node3);
    assert_true(node3._pt_left == &node1 && node3._pt_right == &node5 && node3._un_height == 1);
    assert_true(node1._pt_left == NULL && node1._pt_parent == &node3 && node1._pt_right == NULL && node1._un_height == 0);
    assert_true(node5._pt_left == NULL && node5._pt_parent == &node3 && node5._pt_right == NULL && node5._un_height == 0);
}

/*
 * test _avl_tree_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_avl_tree_init_elem_auxiliary)
void test__avl_tree_init_elem_auxiliary__null_avl_tree(void** state)
{
    _avlnode_t node;
    expect_assert_failure(_avl_tree_init_elem_auxiliary(NULL, &node));
}

void test__avl_tree_init_elem_auxiliary__null_node(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    expect_assert_failure(_avl_tree_init_elem_auxiliary(pt_avl_tree, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_elem_auxiliary__non_inited(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avlnode_t node;
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_init_elem_auxiliary(pt_avl_tree, &node));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_elem_auxiliary__c_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    int elem = 9;
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_insert_unique(pt_avl_tree, &elem);
    _avl_tree_init_elem_auxiliary(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert_true(*(int*)pt_avl_tree->_t_avlroot._pt_parent->_pby_data == 0);

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_elem_auxiliary__cstr(void** state)
{
    _avlnode_t* p = NULL;
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    string_t* pt_str = create_string();
    _avl_tree_init(pt_avl_tree, NULL);
    string_init_cstr(pt_str, "abc");
    p = malloc(_AVL_TREE_NODE_SIZE(_GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)));

    _avl_tree_insert_unique(pt_avl_tree, pt_str);
    _avl_tree_init_elem_auxiliary(pt_avl_tree, p);
    assert_true(strcmp(string_c_str(p->_pby_data), "") == 0);

    _string_destroy_auxiliary(p->_pby_data);
    free(p);
    string_destroy(pt_str);
    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_init_elem_auxiliary__cstl_builtin(void** state)
{
    _avl_tree_t* pt_avl_tree = _create_avl_tree("vector_t<int>");
    vector_t* pvec = create_vector(int);
    _avl_tree_init(pt_avl_tree, NULL);
    vector_init(pvec);

    _avl_tree_insert_unique(pt_avl_tree, pvec);
    _avl_tree_init_elem_auxiliary(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert_true(vector_empty((vector_t*)pt_avl_tree->_t_avlroot._pt_parent->_pby_data));

    vector_destroy(pvec);
    _avl_tree_destroy(pt_avl_tree);
}

typedef struct _tag_test__avl_tree_init_elem_auxiliary__user_define
{
    int elem;
}_test__avl_tree_init_elem_auxiliary__user_define_t;

void test__avl_tree_init_elem_auxiliary__user_define(void** state)
{
    _avl_tree_t* pt_avl_tree = NULL;
    _test__avl_tree_init_elem_auxiliary__user_define_t elem;

    type_register(_test__avl_tree_init_elem_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pt_avl_tree = _create_avl_tree("_test__avl_tree_init_elem_auxiliary__user_define_t");

    _avl_tree_init(pt_avl_tree, NULL);
    elem.elem = 9;
    _avl_tree_insert_unique(pt_avl_tree, &elem);
    _avl_tree_init_elem_auxiliary(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert_true(
        ((_test__avl_tree_init_elem_auxiliary__user_define_t*)pt_avl_tree->_t_avlroot._pt_parent->_pby_data)->elem == 0);

    _avl_tree_destroy(pt_avl_tree);
}

/*
 * test _avl_tree_elem_compare_auxiliary
 */
UT_CASE_DEFINATION(_avl_tree_elem_compare_auxiliary)
void test__avl_tree_elem_compare_auxiliary__null_avl_tree(void** state)
{
    int n_first;
    int n_second;
    bool_t t_result;
    expect_assert_failure(_avl_tree_elem_compare_auxiliary(NULL, &n_first, &n_second, &t_result));
}

void test__avl_tree_elem_compare_auxiliary__null_first(void** state)
{
    int n_second;
    bool_t t_result;
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_elem_compare_auxiliary(pt_avl_tree, NULL, &n_second, &t_result));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_elem_compare_auxiliary__null_second(void** state)
{
    int n_first;
    bool_t t_result;
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_elem_compare_auxiliary(pt_avl_tree, &n_first, NULL, &t_result));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_elem_compare_auxiliary__null_output(void** state)
{
    int n_first;
    int n_second;
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");

    _avl_tree_init(pt_avl_tree, NULL);
    expect_assert_failure(_avl_tree_elem_compare_auxiliary(pt_avl_tree, &n_first, &n_second, NULL));

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_elem_compare_auxiliary__non_inited(void** state)
{
    int n_first;
    int n_second;
    bool_t b_result;
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    pt_avl_tree->_t_avlroot._un_height = 9;
    expect_assert_failure(_avl_tree_elem_compare_auxiliary(pt_avl_tree, &n_first, &n_second, &b_result));
    pt_avl_tree->_t_avlroot._un_height = 0;

    _avl_tree_destroy(pt_avl_tree);
}

void test__avl_tree_elem_compare_auxiliary__int(void** state)
{
    int n_first = 5;
    int n_second = 9;
    bool_t b_result = false;
    _avl_tree_t* pt_avl_tree = _create_avl_tree("int");
    _avl_tree_init(pt_avl_tree, NULL);

    _avl_tree_elem_compare_auxiliary(pt_avl_tree, &n_first, &n_second, &b_result);
    assert_true(b_result);

    _avl_tree_destroy(pt_avl_tree);
}

static void _test__avl_tree_elem_compare_auxiliary__cstr_compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strcmp((char*)cpv_first, (char*)cpv_second) < 0 ? true : false;
}
void test__avl_tree_elem_compare_auxiliary__cstr(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();
    bool_t b_result = false;
    _avl_tree_t* pt_avl_tree = _create_avl_tree("char*");
    _avl_tree_init(pt_avl_tree, NULL);

    string_init_cstr(pstr_first, "abc");
    string_init_cstr(pstr_second, "xyz");
    _avl_tree_elem_compare_auxiliary(pt_avl_tree, pstr_first, pstr_second, &b_result);
    assert_true(b_result);

    _avl_tree_destroy(pt_avl_tree);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

