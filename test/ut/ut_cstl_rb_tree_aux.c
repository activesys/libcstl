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
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl/cslist.h"

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
    rbtree._t_rbroot._t_color = _COLOR_RED;
    rbtree._t_compare = NULL;
    rbtree._t_nodecount = 0;
    rbtree._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    rbtree._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&rbtree._t_allocator);

#ifdef CSTL_MEMORY_MANAGEMENT
    rbtree._t_allocator._t_mempoolsize = 1;
    assert_false(_rb_tree_is_created(&rbtree));
    rbtree._t_allocator._t_mempoolsize = 0;
#else
    assert_true(_rb_tree_is_created(&rbtree));
#endif

    _alloc_destroy(&rbtree._t_allocator);
}

void test__rb_tree_is_created__invalid_rbroot_left(void** state)
{
    _rb_tree_t rbtree;

    rbtree._t_rbroot._pt_left = &rbtree._t_rbroot;
    rbtree._t_rbroot._pt_right = NULL;
    rbtree._t_rbroot._pt_parent = NULL;
    rbtree._t_rbroot._t_color = _COLOR_RED;
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
    rbtree._t_rbroot._t_color = _COLOR_RED;
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
    rbtree._t_rbroot._t_color = _COLOR_RED;
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
    rbtree._t_rbroot._t_color = _COLOR_BLACK;
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
    rbtree._t_rbroot._t_color = _COLOR_RED;
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
    rbtree._t_rbroot._t_color = _COLOR_RED;
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
    rbtree._t_rbroot._t_color = _COLOR_RED;
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
    rbtree._t_rbroot._t_color = _COLOR_RED;
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

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    assert_false(_rb_tree_is_inited(pt_rb_tree));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

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
    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, it_iter));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_iterator_belong_to_rb_tree__invalid_iter_corepos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_iterator_t it_iter;

    _rb_tree_init(pt_rb_tree, NULL);
    it_iter = _rb_tree_begin(pt_rb_tree);
    it_iter._t_pos._t_treepos._pby_corepos = NULL;
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
    it_iter._t_pos._t_treepos._pby_corepos = (char*)0x888;
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
    rbtree._t_rbroot._t_color = _COLOR_BLACK;
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
 * test _rb_tree_same_iterator_type
 */
UT_CASE_DEFINATION(_rb_tree_same_iterator_type)
void test__rb_tree_same_iterator_type__null_rb_tree_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);
    expect_assert_failure(_rb_tree_same_iterator_type(NULL, vector_begin(pvec)));
    vector_destroy(pvec);
}

void test__rb_tree_same_iterator_type__invalid_iterator(void** state)
{
    list_t* plist = create_list(int);
    _rb_tree_t* prbtree = _create_rb_tree("int");
    iterator_t it_iter;

    list_init(plist);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 4444;
    expect_assert_failure(_rb_tree_same_iterator_type(prbtree, it_iter));

    list_destroy(plist);
    _rb_tree_destroy(prbtree);
}

void test__rb_tree_same_iterator_type__same(void** state)
{
    slist_t* pslist = create_slist(int);
    _rb_tree_t* prbtree = _create_rb_tree("int");

    slist_init(pslist);
    _rb_tree_init(prbtree, NULL);
    assert_true(_rb_tree_same_iterator_type(prbtree, slist_begin(pslist)));

    slist_destroy(pslist);
    _rb_tree_destroy(prbtree);
}

void test__rb_tree_same_iterator_type__not_same(void** state)
{
    slist_t* pslist = create_slist(double);
    _rb_tree_t* prbtree = _create_rb_tree("int");

    slist_init(pslist);
    _rb_tree_init(prbtree, NULL);
    assert_false(_rb_tree_same_iterator_type(prbtree, slist_begin(pslist)));

    slist_destroy(pslist);
    _rb_tree_destroy(prbtree);
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
    rbtree._t_rbroot._t_color = _COLOR_BLACK;
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

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_same_type(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type__non_created_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_same_type(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

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

    pt_first->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_same_type_ex(pt_first, pt_second));
    pt_first->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_first);
    _rb_tree_destroy(pt_second);
}

void test__rb_tree_same_type_ex__non_created_second(void** state)
{
    _rb_tree_t* pt_first = _create_rb_tree("int");
    _rb_tree_t* pt_second = _create_rb_tree("int");

    pt_second->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_same_type_ex(pt_first, pt_second));
    pt_second->_t_rbroot._t_color = _COLOR_RED;

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
    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_destroy_subtree(pt_rb_tree, NULL));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

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

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_find_value(pt_rb_tree, NULL, &elem));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

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
    assert_true(*(int*)pt_rb_node->_pby_data == 5);

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
    node._t_color = _COLOR_RED;

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
    a._t_color = _COLOR_RED;

    b._pt_left = &c;
    b._pt_parent = &a;
    b._pt_right = &d;
    b._t_color = _COLOR_RED;

    c._pt_left = NULL;
    c._pt_parent = &b;
    c._pt_right = NULL;
    c._t_color = _COLOR_RED;

    d._pt_left = NULL;
    d._pt_parent = &b;
    d._pt_right = NULL;
    d._t_color = _COLOR_RED;

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
    node._t_color = _COLOR_RED;

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
    a._t_color = _COLOR_RED;

    b._pt_left = &c;
    b._pt_parent = &a;
    b._pt_right = &d;
    b._t_color = _COLOR_RED;

    c._pt_left = NULL;
    c._pt_parent = &b;
    c._pt_right = NULL;
    c._t_color = _COLOR_RED;

    d._pt_left = NULL;
    d._pt_parent = &b;
    d._pt_right = NULL;
    d._t_color = _COLOR_RED;

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
    assert_true(*(int*)pt_node->_pby_data = 100);
    assert_true(pt_node->_pt_left == pt_node->_pt_right);
    assert_true(pt_node->_pt_left == NULL);
    assert_true(pt_node->_t_color == _COLOR_BLACK);

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
    assert_true(*(int*)pt_5->_pby_data == 5);

    elem = 2;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node->_pt_parent == pt_5);
    assert_true(pt_node == pt_5->_pt_left);
    assert_true(*(int*)pt_node->_pby_data == 2);
    assert_true(pt_node->_t_color == _COLOR_RED);

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
    assert_true(*(int*)pt_5->_pby_data == 5);

    elem = 8;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node->_pt_parent == pt_5);
    assert_true(pt_node == pt_5->_pt_right);
    assert_true(*(int*)pt_node->_pby_data == 8);
    assert_true(pt_node->_t_color == _COLOR_RED);

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
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(pt_5->_t_color == _COLOR_BLACK);
    assert_true(pt_2 != NULL);
    assert_true(*(int*)pt_2->_pby_data == 2);
    assert_true(pt_2->_t_color == _COLOR_RED);

    elem = 8;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node->_pt_parent == pt_5);
    assert_true(pt_node == pt_5->_pt_right);
    assert_true(*(int*)pt_node->_pby_data == 8);
    assert_true(pt_node->_t_color == _COLOR_RED);

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
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(pt_5->_t_color == _COLOR_BLACK);
    assert_true(*(int*)pt_8->_pby_data == 8);
    assert_true(pt_8->_t_color == _COLOR_RED);
    assert_true(*(int*)pt_2->_pby_data == 2);
    assert_true(pt_2->_t_color == _COLOR_RED);

    elem = 1;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_5->_t_color == _COLOR_BLACK);
    assert_true(pt_8->_pt_parent == pt_5);
    assert_true(pt_8 == pt_5->_pt_right);
    assert_true(pt_8->_t_color == _COLOR_BLACK);
    assert_true(pt_2->_pt_parent == pt_5);
    assert_true(pt_2 == pt_5->_pt_left);
    assert_true(pt_2->_t_color == _COLOR_BLACK);
    assert_true(pt_node->_pt_parent == pt_2);
    assert_true(pt_node == pt_2->_pt_left);
    assert_true(*(int*)pt_node->_pby_data == 1);
    assert_true(pt_node->_t_color == _COLOR_RED);

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
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(pt_5->_t_color == _COLOR_BLACK);
    assert_true(*(int*)pt_8->_pby_data == 8);
    assert_true(pt_8->_t_color == _COLOR_BLACK);
    assert_true(*(int*)pt_3->_pby_data == 3);
    assert_true(pt_3->_t_color == _COLOR_BLACK);
    assert_true(*(int*)pt_1->_pby_data == 1);
    assert_true(pt_1->_t_color == _COLOR_RED);
    assert_true(*(int*)pt_4->_pby_data == 4);
    assert_true(pt_4->_t_color == _COLOR_RED);

    elem = 2;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_5->_t_color == _COLOR_BLACK);
    assert_true(pt_8->_pt_parent == pt_5);
    assert_true(pt_8 == pt_5->_pt_right);
    assert_true(pt_8->_t_color == _COLOR_BLACK);
    assert_true(pt_3->_pt_parent == pt_5);
    assert_true(pt_3 == pt_5->_pt_left);
    assert_true(pt_3->_t_color == _COLOR_RED);
    assert_true(pt_1->_pt_parent == pt_3);
    assert_true(pt_1 == pt_3->_pt_left);
    assert_true(pt_1->_t_color == _COLOR_BLACK);
    assert_true(pt_4->_pt_parent == pt_3);
    assert_true(pt_4 == pt_3->_pt_right);
    assert_true(pt_4->_t_color == _COLOR_BLACK);
    assert_true(pt_node->_pt_parent == pt_1);
    assert_true(pt_node == pt_1->_pt_right);
    assert_true(*(int*)pt_node->_pby_data == 2);
    assert_true(pt_node->_t_color == _COLOR_RED);

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
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(pt_5->_t_color == _COLOR_BLACK);
    assert_true(*(int*)pt_3->_pby_data == 3);
    assert_true(pt_3->_t_color == _COLOR_RED);

    elem = 1;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_3->_t_color == _COLOR_BLACK);
    assert_true(pt_5->_pt_parent == pt_3);
    assert_true(pt_5 == pt_3->_pt_right);
    assert_true(pt_5->_t_color == _COLOR_RED);
    assert_true(pt_node->_pt_parent == pt_3);
    assert_true(pt_node == pt_3->_pt_left);
    assert_true(*(int*)pt_node->_pby_data == 1);
    assert_true(pt_node->_t_color == _COLOR_RED);

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
    assert_true(*(int*)pt_5->_pby_data == 5);
    assert_true(pt_5->_t_color == _COLOR_BLACK);
    assert_true(*(int*)pt_3->_pby_data == 3);
    assert_true(pt_3->_t_color == _COLOR_RED);

    elem = 4;
    pt_node = _rb_tree_insert_rbnode(pt_rb_tree, &elem);
    assert_true(pt_node == pt_rb_tree->_t_rbroot._pt_parent);
    assert_true(pt_node->_t_color == _COLOR_BLACK);
    assert_true(*(int*)pt_node->_pby_data == 4);
    assert_true(pt_node->_pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(pt_3->_t_color == _COLOR_RED);
    assert_true(pt_3->_pt_parent == pt_node);
    assert_true(pt_3 == pt_node->_pt_left);
    assert_true(pt_5->_t_color == _COLOR_RED);
    assert_true(pt_5 == pt_node->_pt_right);
    assert_true(pt_5->_pt_parent == pt_node);

    pt_rb_tree->_t_rbroot._pt_left = pt_3;
    pt_rb_tree->_t_rbroot._pt_right = pt_5;
    pt_rb_tree->_t_nodecount++; 
    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_get_color
 */
UT_CASE_DEFINATION(_rb_tree_get_color)
void test__rb_tree_get_color__null_root(void** state)
{
    assert_true(_rb_tree_get_color(NULL) == _COLOR_BLACK);
}

void test__rb_tree_get_color__invalid_color(void** state)
{
    _rbnode_t node;
    node._t_color = 5;

    expect_assert_failure(_rb_tree_get_color(&node));
}

void test__rb_tree_get_color__red(void** state)
{
    _rbnode_t node;
    node._t_color = _COLOR_RED;

    assert_true(_rb_tree_get_color(&node) == _COLOR_RED);
}

void test__rb_tree_get_color__black(void** state)
{
    _rbnode_t node;
    node._t_color = _COLOR_BLACK;

    assert_true(_rb_tree_get_color(&node) == _COLOR_BLACK);
}

/*
 * test _rb_tree_get_min_rbnode
 */
UT_CASE_DEFINATION(_rb_tree_get_min_rbnode)
void test__rb_tree_get_min_rbnode__null_root(void** state)
{
    expect_assert_failure(_rb_tree_get_min_rbnode(NULL));
}

void test__rb_tree_get_min_rbnode__one_node(void** state)
{
    _rbnode_t node;
    node._pt_left = node._pt_right = node._pt_parent = NULL;

    assert_true(_rb_tree_get_min_rbnode(&node) == &node);
}

void test__rb_tree_get_min_rbnode__sub_tree(void** state)
{
    /*
     *    5
     *   / \
     *  2   8
     *   \
     *    4
     */
    _rbnode_t node5;
    _rbnode_t node2;
    _rbnode_t node8;
    _rbnode_t node4;

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

    assert_true(_rb_tree_get_min_rbnode(&node5) == &node2);
}

/*
 * test _rb_tree_get_max_rbnode
 */
UT_CASE_DEFINATION(_rb_tree_get_max_rbnode)
void test__rb_tree_get_max_rbnode__null_root(void** state)
{
    expect_assert_failure(_rb_tree_get_max_rbnode(NULL));
}

void test__rb_tree_get_max_rbnode__one_node(void** state)
{
    _rbnode_t node;
    node._pt_left = node._pt_right = node._pt_parent = NULL;

    assert_true(_rb_tree_get_max_rbnode(&node) == &node);
}

void test__rb_tree_get_max_rbnode__sub_tree(void** state)
{
    /*
     *    5
     *   / \
     *  2   8
     *   \
     *    4
     */
    _rbnode_t node5;
    _rbnode_t node2;
    _rbnode_t node8;
    _rbnode_t node4;

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

    assert_true(_rb_tree_get_max_rbnode(&node5) == &node8);
}

/*
 * test _rb_tree_rebalance
 */
UT_CASE_DEFINATION(_rb_tree_rebalance)
void test__rb_tree_rebalance__null_rb_tree(void** state)
{
    _rbnode_t node;
    expect_assert_failure(_rb_tree_rebalance(NULL, &node));
}

void test__rb_tree_rebalance__null_pos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_rebalance(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__not_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t node;

    expect_assert_failure(_rb_tree_rebalance(pt_rb_tree, &node));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__invalid_node(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t node;

    _rb_tree_init(pt_rb_tree, NULL);
    node._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_rebalance(pt_rb_tree, &node));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__root(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;

    _rb_tree_init(pt_rb_tree, NULL);
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    expect_assert_failure(_rb_tree_rebalance(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_1_1(void** state)
{
    /*
     *       ggp(?)              ggp(?) 
     *      /     \             /    \
     *     gp(b) sgp(b)   =>   gp(r) sgp(b)   
     *    /    \               /   \
     *   p(r)  sp(r)         p(b) sp(b)
     *  /                    /          
     * c(r)                c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = &t_sgp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = NULL;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_gp);
    assert_true(t_ggp._pt_right == &t_sgp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_p);
    assert_true(t_gp._pt_right == &t_sp);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_1_2(void** state)
{
    /*
     *       ggp(?)              ggp(?) 
     *      /     \             /    \
     *     gp(b) sgp(b)   =>   gp(r) sgp(b)   
     *    /    \               /   \
     *   p(r)  sp(r)         p(b) sp(b)
     *     \                    \
     *    c(r)                c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = &t_sgp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = NULL;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_gp);
    assert_true(t_ggp._pt_right == &t_sgp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_p);
    assert_true(t_gp._pt_right == &t_sp);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == NULL);
    assert_true(t_p._pt_right == &t_c);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_1_3(void** state)
{
    /*
     *     ggp(?)             ggp(?)   
     *     /    \             /    \
     *  sgp(b)  gp(b)    => sgp(b) gp(r)   
     *         /    \              /  \
     *        p(r)  sp(r)        p(b) sp(b)
     *        /                  /         
     *       c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_sgp;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = NULL;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_sgp);
    assert_true(t_ggp._pt_right == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_p);
    assert_true(t_gp._pt_right == &t_sp);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_1_4(void** state)
{
    /*
     *     ggp(?)             ggp(?)   
     *     /    \             /    \
     *  sgp(b)  gp(b)    => sgp(b) gp(r)   
     *         /    \              /  \
     *        p(r)  sp(r)        p(b) sp(b)
     *          \                  \
     *         c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_sgp;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = NULL;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_sgp);
    assert_true(t_ggp._pt_right == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_p);
    assert_true(t_gp._pt_right == &t_sp);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == NULL);
    assert_true(t_p._pt_right == &t_c);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_1_5(void** state)
{
    /*
     *         gp(b)    =>        gp(b)   
     *         /    \              /  \
     *        p(r)  sp(r)        p(b) sp(b)
     *        /                  /         
     *       c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = NULL;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_p);
    assert_true(t_gp._pt_right == &t_sp);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_1_6(void** state)
{
    /*
     *         gp(b)    =>        gp(b)   
     *         /    \              /  \
     *        p(r)  sp(r)        p(b) sp(b)
     *          \                  \
     *         c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = NULL;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_p);
    assert_true(t_gp._pt_right == &t_sp);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == NULL);
    assert_true(t_p._pt_right == &t_c);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_2_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = &t_s;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *         gp(b)      =>          p(b)
     *        /    \                  /    \
     *       p(r)  sp(b)             c(r)   gp(r)
     *      /   \                    /  \   /  \
     *     c(r) s(b)             l(b) r(b) s(b) sp(b)
     *     /  \                   /
     *   l(b) r(b)             i(r)
     *    /
     *   i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == &t_gp);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == &t_l);
    assert_true(t_c._pt_right == &t_r);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_p);
    assert_true(t_gp._pt_left == &t_s);
    assert_true(t_gp._pt_right == &t_sp);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_c);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_c);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_2_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = NULL;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = &t_s;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *            ggp(b)                ggp(b)
     *           /                       /
     *         gp(b)       =>          p(b)
     *        /    \                  /    \
     *       p(r)  sp(b)             c(r)   gp(r)
     *      /   \                    /  \   /  \
     *     c(r) s(b)             l(b) r(b) s(b) sp(b)
     *     /  \                   /
     *   l(b) r(b)             i(r)
     *    /
     *   i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_p);
    assert_true(t_ggp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_ggp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == &t_gp);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == &t_l);
    assert_true(t_c._pt_right == &t_r);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_p);
    assert_true(t_gp._pt_left == &t_s);
    assert_true(t_gp._pt_right == &t_sp);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_c);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_c);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_2_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = NULL;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = &t_s;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *          ggp(b)                ggp(b)
     *           \                       \
     *         gp(b)       =>          p(b)
     *        /    \                  /    \
     *       p(r)  sp(b)             c(r)   gp(r)
     *      /   \                    /  \   /  \
     *     c(r) s(b)             l(b) r(b) s(b) sp(b)
     *     /  \                   /
     *   l(b) r(b)             i(r)
     *    /
     *   i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == NULL);
    assert_true(t_ggp._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_ggp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == &t_gp);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == &t_l);
    assert_true(t_c._pt_right == &t_r);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_p);
    assert_true(t_gp._pt_left == &t_s);
    assert_true(t_gp._pt_right == &t_sp);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_c);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_c);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_3_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = NULL;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *          ggp(b)                ggp(b)
     *           /                       /
     *         gp(b)       =>          c(b)
     *        /    \                  /    \
     *       p(r)  sp(b)             p(r)   gp(r)
     *       /   \                   /  \     /  \
     *      s(b) c(r)              s(b) l(b) r(b) sp(b)
     *           /  \                   /
     *        l(b) r(b)              i(r)
     *        /
     *       i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_c);
    assert_true(t_ggp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_BLACK);
    assert_true(t_c._pt_parent == &t_ggp);
    assert_true(t_c._pt_left == &t_p);
    assert_true(t_c._pt_right == &t_gp);
    /* p */
    assert_true(t_p._t_color == _COLOR_RED);
    assert_true(t_p._pt_parent == &t_c);
    assert_true(t_p._pt_left == &t_s);
    assert_true(t_p._pt_right == &t_l);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_c);
    assert_true(t_gp._pt_left == &t_r);
    assert_true(t_gp._pt_right == &t_sp);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_p);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_gp);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_3_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = NULL;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *          ggp(b)                ggp(b)
     *           \                       \
     *         gp(b)       =>          c(b)
     *        /    \                  /    \
     *       p(r)  sp(b)             p(r)   gp(r)
     *       /   \                   /  \     /  \
     *      s(b) c(r)              s(b) l(b) r(b) sp(b)
     *           /  \                   /
     *        l(b) r(b)              i(r)
     *        /
     *       i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == NULL);
    assert_true(t_ggp._pt_right == &t_c);
    /* c */
    assert_true(t_c._t_color == _COLOR_BLACK);
    assert_true(t_c._pt_parent == &t_ggp);
    assert_true(t_c._pt_left == &t_p);
    assert_true(t_c._pt_right == &t_gp);
    /* p */
    assert_true(t_p._t_color == _COLOR_RED);
    assert_true(t_p._pt_parent == &t_c);
    assert_true(t_p._pt_left == &t_s);
    assert_true(t_p._pt_right == &t_l);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_c);
    assert_true(t_gp._pt_left == &t_r);
    assert_true(t_gp._pt_right == &t_sp);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_p);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_gp);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_3_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = &t_sp;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *         gp(b)       =>          c(b)
     *        /    \                  /    \
     *       p(r)  sp(b)             p(r)   gp(r)
     *       /   \                   /  \     /  \
     *      s(b) c(r)              s(b) l(b) r(b) sp(b)
     *           /  \                   /
     *        l(b) r(b)              i(r)
     *        /
     *       i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_c);
    /* c */
    assert_true(t_c._t_color == _COLOR_BLACK);
    assert_true(t_c._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_c._pt_left == &t_p);
    assert_true(t_c._pt_right == &t_gp);
    /* p */
    assert_true(t_p._t_color == _COLOR_RED);
    assert_true(t_p._pt_parent == &t_c);
    assert_true(t_p._pt_left == &t_s);
    assert_true(t_p._pt_right == &t_l);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_c);
    assert_true(t_gp._pt_left == &t_r);
    assert_true(t_gp._pt_right == &t_sp);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_p);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_gp);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_4_1(void** state)
{
    /*
     *       ggp(?)              ggp(?) 
     *      /     \             /    \
     *     gp(b) sgp(b)   =>   gp(r) sgp(b)   
     *    /    \               /   \
     *   sp(r)  p(r)         sp(b) p(b)
     *          /                    /          
     *         c(r)                c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = &t_sgp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = NULL;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_gp);
    assert_true(t_ggp._pt_right == &t_sgp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_p);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_4_2(void** state)
{
    /*
     *       ggp(?)              ggp(?) 
     *      /     \             /    \
     *     gp(b) sgp(b)   =>   gp(r) sgp(b)   
     *    /    \               /   \
     *   sp(r)  p(r)         sp(b) p(b)
     *           \                    \
     *           c(r)                c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = &t_sgp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = NULL;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_gp);
    assert_true(t_ggp._pt_right == &t_sgp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_p);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == NULL);
    assert_true(t_p._pt_right == &t_c);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_4_3(void** state)
{
    /*
     *     ggp(?)             ggp(?)   
     *     /    \             /    \
     *  sgp(b)  gp(b)    => sgp(b) gp(r)   
     *         /    \              /  \
     *        sp(r)  p(r)        sp(b) p(b)
     *               /                  /         
     *              c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_sgp;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = NULL;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_sgp);
    assert_true(t_ggp._pt_right == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_p);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_4_4(void** state)
{
    /*
     *     ggp(?)             ggp(?)   
     *     /    \             /    \
     *  sgp(b)  gp(b)    => sgp(b) gp(r)   
     *         /    \              /  \
     *        sp(r)  p(r)        sp(b) p(b)
     *                \                  \
     *                c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_sgp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_sgp;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* sgp */
    t_sgp._t_color = _COLOR_BLACK;
    t_sgp._pt_parent = &t_ggp;
    t_sgp._pt_left = NULL;
    t_sgp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = NULL;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent = &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_sgp);
    assert_true(t_ggp._pt_right == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_ggp);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_p);
    /* sgp */
    assert_true(t_sgp._t_color == _COLOR_BLACK);
    assert_true(t_sgp._pt_parent == &t_ggp);
    assert_true(t_sgp._pt_left == NULL);
    assert_true(t_sgp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == NULL);
    assert_true(t_p._pt_right == &t_c);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_4_5(void** state)
{
    /*
     *         gp(b)    =>        gp(b)   
     *         /    \              /  \
     *        sp(r)  p(r)        sp(b) p(b)
     *               /                  /         
     *              c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = NULL;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == &t_c);
    assert_true(t_p._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_4_6(void** state)
{
    /*
     *         gp(b)    =>        gp(b)   
     *         /    \              /  \
     *        sp(r)  p(r)        sp(b) p(b)
     *                \                  \
     *               c(r)               c(r)        
     */
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = NULL;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_RED;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = NULL;
    t_c._pt_right = NULL;

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_gp);
    assert_true(t_p._pt_left == NULL);
    assert_true(t_p._pt_right == &t_c);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == NULL);
    assert_true(t_c._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_5_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *         gp(b)      =>          p(b)
     *        /    \                  /    \
     *       sp(b)  p(r)             gp(r)   c(r)
     *             /   \            /  \     /  \
     *           s(b) c(r)       sp(b) s(b) l(b) r(b)
     *                /  \                  /
     *              l(b) r(b)             i(r)
     *              /
     *             i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_p._pt_left == &t_gp);
    assert_true(t_p._pt_right == &t_c);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == &t_l);
    assert_true(t_c._pt_right == &t_r);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_p);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_s);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_c);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_c);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_5_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = NULL;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *            ggp(b)                ggp(b)
     *           /                       /
     *         gp(b)       =>          p(b)
     *        /    \                  /    \
     *       sp(b)  p(r)             gp(r)   c(r)
     *             /   \            /  \     /  \
     *           s(b) c(r)       sp(b) s(b) l(b) r(b)
     *               /  \                   /
     *             l(b) r(b)              i(r)
     *             /
     *           i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_p);
    assert_true(t_ggp._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_ggp);
    assert_true(t_p._pt_left == &t_gp);
    assert_true(t_p._pt_right == &t_c);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == &t_l);
    assert_true(t_c._pt_right == &t_r);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_p);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_s);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_c);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_c);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_5_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = NULL;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_c;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *          ggp(b)                ggp(b)
     *           \                       \
     *         gp(b)       =>          p(b)
     *        /    \                  /    \
     *       sp(b)  p(r)             gp(r)   c(r)
     *              /   \            /  \    /  \
     *            s(b) c(r)      sp(b) s(b) l(b) r(b)
     *                 /  \                 /
     *              l(b) r(b)             i(r)
     *               /
     *             i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == NULL);
    assert_true(t_ggp._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_ggp);
    assert_true(t_p._pt_left == &t_gp);
    assert_true(t_p._pt_right == &t_c);
    /* c */
    assert_true(t_c._t_color == _COLOR_RED);
    assert_true(t_c._pt_parent == &t_p);
    assert_true(t_c._pt_left == &t_l);
    assert_true(t_c._pt_right == &t_r);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_p);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_s);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_c);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_c);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_6_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = &t_gp;
    t_ggp._pt_right = NULL;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = &t_s;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *          ggp(b)                ggp(b)
     *           /                       /
     *         gp(b)       =>          c(b)
     *        /    \                  /    \
     *       sp(b)  p(r)             gp(r)   p(r)
     *             /   \            /  \     /  \
     *           c(r) s(b)       sp(b) l(b) r(b) s(b)
     *           /  \                 /
     *        l(b) r(b)             i(r)
     *         /
     *       i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == &t_c);
    assert_true(t_ggp._pt_right == NULL);
    /* c */
    assert_true(t_c._t_color == _COLOR_BLACK);
    assert_true(t_c._pt_parent == &t_ggp);
    assert_true(t_c._pt_left == &t_gp);
    assert_true(t_c._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_RED);
    assert_true(t_p._pt_parent == &t_c);
    assert_true(t_p._pt_left == &t_r);
    assert_true(t_p._pt_right == &t_s);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_c);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_l);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_gp);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_p);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_6_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_ggp;
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_ggp;
    /* ggp */
    t_ggp._t_color = _COLOR_BLACK;
    t_ggp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_ggp._pt_left = NULL;
    t_ggp._pt_right = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &t_ggp;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = &t_s;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *          ggp(b)                ggp(b)
     *           \                       \
     *         gp(b)       =>          c(b)
     *        /    \                  /    \
     *       sp(b)  p(r)             gp(r)   p(r)
     *             /   \            /  \     /  \
     *           c(r) s(b)       sp(b) l(b) r(b) s(b)
     *           /  \                 /
     *        l(b) r(b)             i(r)
     *         /
     *       i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_ggp);
    /* ggp */
    assert_true(t_ggp._t_color == _COLOR_BLACK);
    assert_true(t_ggp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_ggp._pt_left == NULL);
    assert_true(t_ggp._pt_right == &t_c);
    /* c */
    assert_true(t_c._t_color == _COLOR_BLACK);
    assert_true(t_c._pt_parent == &t_ggp);
    assert_true(t_c._pt_left == &t_gp);
    assert_true(t_c._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_RED);
    assert_true(t_p._pt_parent == &t_c);
    assert_true(t_p._pt_left == &t_r);
    assert_true(t_p._pt_right == &t_s);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_c);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_l);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_gp);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_p);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_rebalance__case_6_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_sp;
    _rbnode_t t_c;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_i;

    _rb_tree_init(pt_rb_tree, NULL);
    /* make rb tree */
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_sp;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_c;
    t_p._pt_right = &t_s;
    /* sp */
    t_sp._t_color = _COLOR_BLACK;
    t_sp._pt_parent = &t_gp;
    t_sp._pt_left = NULL;
    t_sp._pt_right = NULL;
    /* c */
    t_c._t_color = _COLOR_RED;
    t_c._pt_parent = &t_p;
    t_c._pt_left = &t_l;
    t_c._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_c;
    t_l._pt_left = &t_i;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_c;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* i */
    t_i._t_color = _COLOR_RED;
    t_i._pt_parent = &t_l;
    t_i._pt_left = NULL;
    t_i._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = NULL;
    t_s._pt_right = NULL;

    /*
     *         gp(b)       =>          c(b)
     *        /    \                  /    \
     *       sp(b)  p(r)             gp(r)   p(r)
     *             /   \            /  \     /  \
     *           c(r) s(b)       sp(b) l(b) r(b) s(b)
     *           /  \                 /
     *        l(b) r(b)             i(r)
     *         /
     *       i(r)
     *
     * this case come from case_1_1.
     */

    _rb_tree_rebalance(pt_rb_tree, &t_c);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_c);
    /* c */
    assert_true(t_c._t_color == _COLOR_BLACK);
    assert_true(t_c._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_c._pt_left == &t_gp);
    assert_true(t_c._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_RED);
    assert_true(t_p._pt_parent == &t_c);
    assert_true(t_p._pt_left == &t_r);
    assert_true(t_p._pt_right == &t_s);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_RED);
    assert_true(t_gp._pt_parent == &t_c);
    assert_true(t_gp._pt_left == &t_sp);
    assert_true(t_gp._pt_right == &t_l);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_gp);
    assert_true(t_l._pt_left == &t_i);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_p);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == NULL);
    /* sp */
    assert_true(t_sp._t_color == _COLOR_BLACK);
    assert_true(t_sp._pt_parent == &t_gp);
    assert_true(t_sp._pt_left == NULL);
    assert_true(t_sp._pt_right == NULL);
    /* i */
    assert_true(t_i._t_color == _COLOR_RED);
    assert_true(t_i._pt_parent == &t_l);
    assert_true(t_i._pt_left == NULL);
    assert_true(t_i._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_fixup_deletion
 */
UT_CASE_DEFINATION(_rb_tree_fixup_deletion)
void test__rb_tree_fixup_deletion__null_rb_tree(void** state)
{
    _rbnode_t t_pos;
    _rbnode_t t_parent;

    t_parent._pt_right = &t_pos;
    t_pos._pt_parent = &t_parent;
    expect_assert_failure(_rb_tree_fixup_deletion(NULL, &t_pos, &t_parent));
}

void test__rb_tree_fixup_deletion__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rbnode_t t_parent;
    t_parent._pt_left = t_parent._pt_right = NULL;
    expect_assert_failure(_rb_tree_fixup_deletion(pt_rb_tree, NULL, &t_parent));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__null_parent(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_fixup_deletion(pt_rb_tree, NULL, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__parent_not_belong_to_rb_tree(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_parent;

    _rb_tree_init(pt_rb_tree, NULL);
    t_parent._pt_left = NULL;
    t_parent._pt_right = (_rbnode_t*)0x999;
    expect_assert_failure(_rb_tree_fixup_deletion(pt_rb_tree, NULL, &t_parent));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__parent_no_child(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_parent = NULL;
    int elem = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    elem = 4;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 3;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 7;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    pt_parent = pt_rb_tree->_t_rbroot._pt_parent->_pt_left;

    expect_assert_failure(_rb_tree_fixup_deletion(pt_rb_tree, NULL, pt_parent));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__invalid_pos(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t* pt_parent = NULL;
    _rbnode_t* pt_pos = NULL;
    int elem = 0;

    _rb_tree_init(pt_rb_tree, NULL);
    elem = 4;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 3;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    elem = 7;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    pt_parent = pt_rb_tree->_t_rbroot._pt_parent->_pt_left;
    pt_pos = pt_rb_tree->_t_rbroot._pt_parent->_pt_right;

    expect_assert_failure(_rb_tree_fixup_deletion(pt_rb_tree, pt_pos, pt_parent));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_1_1_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_ll;
    _rbnode_t t_lr;

    _rb_tree_init(pt_rb_tree, NULL);
    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_RED;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = &t_ll;
    t_l._pt_right = &t_lr;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* ll */
    t_ll._t_color = _COLOR_RED;
    t_ll._pt_parent = &t_l;
    t_ll._pt_left = NULL;
    t_ll._pt_right = NULL;
    /* lr */
    t_lr._t_color = _COLOR_RED;
    t_lr._pt_parent = &t_l;
    t_lr._pt_left = NULL;
    t_lr._pt_right = NULL;
    /* Case:1
     *        gp(?)            gp(?)                gp(?)
     *         |                |                    |
     *         p(b)    =>       s(b)       =>       s(b)
     *        / \              /   \                /  \
     *     x(b) s(r)         p(r)  r(b)           l(r) r(b)
     *          /  \         /  \                / \
     *        l(b) r(b)    x(b) l(b)           p(b) lr(b)
     *        /  \              /  \          /  \
     *    ll(r) lr(r)        ll(r) lr(r)    x(b) ll(r)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* l */
    assert_true(t_l._t_color == _COLOR_RED);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == &t_p);
    assert_true(t_l._pt_right == &t_lr);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_l);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == &t_ll);
    /* lr */
    assert_true(t_lr._t_color == _COLOR_BLACK);
    assert_true(t_lr._pt_parent == &t_l);
    assert_true(t_lr._pt_left == NULL);
    assert_true(t_lr._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* ll */
    assert_true(t_ll._t_color == _COLOR_RED);
    assert_true(t_ll._pt_parent == &t_p);
    assert_true(t_ll._pt_left == NULL);
    assert_true(t_ll._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_1_1_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_ll;
    _rbnode_t t_lr;

    _rb_tree_init(pt_rb_tree, NULL);
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_RED;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = &t_ll;
    t_l._pt_right = &t_lr;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* ll */
    t_ll._t_color = _COLOR_RED;
    t_ll._pt_parent = &t_l;
    t_ll._pt_left = NULL;
    t_ll._pt_right = NULL;
    /* lr */
    t_lr._t_color = _COLOR_RED;
    t_lr._pt_parent = &t_l;
    t_lr._pt_left = NULL;
    t_lr._pt_right = NULL;
    /* Case:1
     *        gp(?)            gp(?)                gp(?)
     *         /                /                    /
     *         p(b)    =>       s(b)       =>       s(b)
     *        / \              /   \                /  \
     *     x(b) s(r)         p(r)  r(b)           l(r) r(b)
     *          /  \         /  \                / \
     *        l(b) r(b)    x(b) l(b)           p(b) lr(b)
     *        /  \              /  \          /  \
     *    ll(r) lr(r)        ll(r) lr(r)    x(b) ll(r)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_s);
    assert_true(t_gp._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* l */
    assert_true(t_l._t_color == _COLOR_RED);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == &t_p);
    assert_true(t_l._pt_right == &t_lr);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_l);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == &t_ll);
    /* lr */
    assert_true(t_lr._t_color == _COLOR_BLACK);
    assert_true(t_lr._pt_parent == &t_l);
    assert_true(t_lr._pt_left == NULL);
    assert_true(t_lr._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* ll */
    assert_true(t_ll._t_color == _COLOR_RED);
    assert_true(t_ll._pt_parent == &t_p);
    assert_true(t_ll._pt_left == NULL);
    assert_true(t_ll._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_1_1_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_ll;
    _rbnode_t t_lr;

    _rb_tree_init(pt_rb_tree, NULL);
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = NULL;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_RED;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = &t_ll;
    t_l._pt_right = &t_lr;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;
    /* ll */
    t_ll._t_color = _COLOR_RED;
    t_ll._pt_parent = &t_l;
    t_ll._pt_left = NULL;
    t_ll._pt_right = NULL;
    /* lr */
    t_lr._t_color = _COLOR_RED;
    t_lr._pt_parent = &t_l;
    t_lr._pt_left = NULL;
    t_lr._pt_right = NULL;
    /* Case:1
     *        gp(?)            gp(?)                gp(?)
     *         \                \                    \
     *         p(b)    =>       s(b)       =>       s(b)
     *        / \              /   \                /  \
     *     x(b) s(r)         p(r)  r(b)           l(r) r(b)
     *          /  \         /  \                / \
     *        l(b) r(b)    x(b) l(b)           p(b) lr(b)
     *        /  \              /  \          /  \
     *    ll(r) lr(r)        ll(r) lr(r)    x(b) ll(r)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == NULL);
    assert_true(t_gp._pt_right == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* l */
    assert_true(t_l._t_color == _COLOR_RED);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == &t_p);
    assert_true(t_l._pt_right == &t_lr);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_l);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == &t_ll);
    /* lr */
    assert_true(t_lr._t_color == _COLOR_BLACK);
    assert_true(t_lr._pt_parent == &t_l);
    assert_true(t_lr._pt_left == NULL);
    assert_true(t_lr._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* ll */
    assert_true(t_ll._t_color == _COLOR_RED);
    assert_true(t_ll._pt_parent == &t_p);
    assert_true(t_ll._pt_left == NULL);
    assert_true(t_ll._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_1_2_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_rl;
    _rbnode_t t_rr;

    _rb_tree_init(pt_rb_tree, NULL);
    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_RED;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = &t_rl;
    t_r._pt_right = &t_rr;
    /* rl */
    t_rl._t_color = _COLOR_RED;
    t_rl._pt_parent = &t_r;
    t_rl._pt_left = NULL;
    t_rl._pt_right = NULL;
    /* lr */
    t_rr._t_color = _COLOR_RED;
    t_rr._pt_parent = &t_r;
    t_rr._pt_left = NULL;
    t_rr._pt_right = NULL;
    /* Case:1
     *        gp(?)            gp(?)                gp(?)
     *         |                |                    |
     *         p(b)    =>       s(b)       =>       s(b)
     *        / \              /   \                /  \
     *     s(r) x(b)        l(b)    p(r)         l(b)  r(r)
     *      /  \                    /  \                /  \
     *    l(b) r(b)               r(b) x(b)           rl(b) p(b)
     *         /  \               /  \                       /  \
     *      rl(r) rr(r)         rl(r) rr(r)                rr(r) x(b)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_RED);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == &t_rl);
    assert_true(t_r._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_r);
    assert_true(t_p._pt_left == &t_rr);
    assert_true(t_p._pt_right == &t_x);
    /* rl */
    assert_true(t_rl._t_color == _COLOR_BLACK);
    assert_true(t_rl._pt_parent == &t_r);
    assert_true(t_rl._pt_left == NULL);
    assert_true(t_rl._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* rr */
    assert_true(t_rr._t_color == _COLOR_RED);
    assert_true(t_rr._pt_parent == &t_p);
    assert_true(t_rr._pt_left == NULL);
    assert_true(t_rr._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_1_2_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_rl;
    _rbnode_t t_rr;

    _rb_tree_init(pt_rb_tree, NULL);
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_RED;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = &t_rl;
    t_r._pt_right = &t_rr;
    /* rl */
    t_rl._t_color = _COLOR_RED;
    t_rl._pt_parent = &t_r;
    t_rl._pt_left = NULL;
    t_rl._pt_right = NULL;
    /* lr */
    t_rr._t_color = _COLOR_RED;
    t_rr._pt_parent = &t_r;
    t_rr._pt_left = NULL;
    t_rr._pt_right = NULL;
    /* Case:1
     *        gp(?)            gp(?)                gp(?)
     *         /                /                    /
     *         p(b)    =>       s(b)       =>       s(b)
     *        / \              /   \                /  \
     *     s(r) x(b)        l(b)    p(r)         l(b)  r(r)
     *      /  \                    /  \                /  \
     *    l(b) r(b)               r(b) x(b)           rl(b) p(b)
     *         /  \               /  \                       /  \
     *      rl(r) rr(r)         rl(r) rr(r)                rr(r) x(b)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_s);
    assert_true(t_gp._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_RED);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == &t_rl);
    assert_true(t_r._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_r);
    assert_true(t_p._pt_left == &t_rr);
    assert_true(t_p._pt_right == &t_x);
    /* rl */
    assert_true(t_rl._t_color == _COLOR_BLACK);
    assert_true(t_rl._pt_parent == &t_r);
    assert_true(t_rl._pt_left == NULL);
    assert_true(t_rl._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* rr */
    assert_true(t_rr._t_color == _COLOR_RED);
    assert_true(t_rr._pt_parent == &t_p);
    assert_true(t_rr._pt_left == NULL);
    assert_true(t_rr._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_1_2_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;
    _rbnode_t t_rl;
    _rbnode_t t_rr;

    _rb_tree_init(pt_rb_tree, NULL);
    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = NULL;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_RED;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = &t_rl;
    t_r._pt_right = &t_rr;
    /* rl */
    t_rl._t_color = _COLOR_RED;
    t_rl._pt_parent = &t_r;
    t_rl._pt_left = NULL;
    t_rl._pt_right = NULL;
    /* lr */
    t_rr._t_color = _COLOR_RED;
    t_rr._pt_parent = &t_r;
    t_rr._pt_left = NULL;
    t_rr._pt_right = NULL;
    /* Case:1
     *        gp(?)            gp(?)                gp(?)
     *         \                \                    \
     *         p(b)    =>       s(b)       =>       s(b)
     *        / \              /   \                /  \
     *     s(r) x(b)        l(b)    p(r)         l(b)  r(r)
     *      /  \                    /  \                /  \
     *    l(b) r(b)               r(b) x(b)           rl(b) p(b)
     *         /  \               /  \                       /  \
     *      rl(r) rr(r)         rl(r) rr(r)                rr(r) x(b)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == NULL);
    assert_true(t_gp._pt_right == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);
    /* r */
    assert_true(t_r._t_color == _COLOR_RED);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == &t_rl);
    assert_true(t_r._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_r);
    assert_true(t_p._pt_left == &t_rr);
    assert_true(t_p._pt_right == &t_x);
    /* rl */
    assert_true(t_rl._t_color == _COLOR_BLACK);
    assert_true(t_rl._pt_parent == &t_r);
    assert_true(t_rl._pt_left == NULL);
    assert_true(t_rl._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* rr */
    assert_true(t_rr._t_color == _COLOR_RED);
    assert_true(t_rr._pt_parent == &t_p);
    assert_true(t_rr._pt_left == NULL);
    assert_true(t_rr._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_2_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:2
    *         gp(?)               gp(?)
    *          |                   |
    *          p(?)        =>      p(?)  new x
    *         /  \                /  \
    *       x(b) s(b)            x(b) s(r)
    *            /  \                 /  \
    *           l(b) r(b)            l(b) r(b)
    */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == &t_s);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_RED);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_2_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:2
     *         gp(?)               gp(?)
     *          |                   |
     *          p(?)        =>      p(?)  new x
     *         /  \                /  \
     *       s(b) x(b)            s(r) x(b)
     *      /  \                 /  \
     *    l(b) r(b)            l(b) r(b)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_p._pt_left == &t_s);
    assert_true(t_p._pt_right == &t_x);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_RED);
    assert_true(t_s._pt_parent == &t_p);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_r);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_3_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_RED;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_BLACK;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:3
     *         p(?)          =>         p(?)                         l(?)
     *        /  \                     /   \                         /  \
     *       x(b) s(b)               x(b)  l(b)  new s   =>        p(b) s(b)
     *            /  \                       \                     /      \
     *           l(r) r(b)                    s(r)               x(b)     r(b)
     *                                         \
     *                                          r(b)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_l);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_l._pt_left == &t_p);
    assert_true(t_l._pt_right == &t_s);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_l);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_l);
    assert_true(t_s._pt_left == NULL);
    assert_true(t_s._pt_right == &t_r);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_3_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_BLACK;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_RED;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:3
     *         p(?)          =>         p(?)               r(?)
     *        /  \                     /   \               /  \
     *       s(b) x(b)         new s r(b)  x(b)    =>    s(b) p(b)
     *      /  \                     /                   /      \
     *    l(b) r(r)                s(r)                l(b)     x(b)
     *                             /
     *                           l(b)
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_r);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_r._pt_left == &t_s);
    assert_true(t_r._pt_right == &t_p);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &t_r);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == NULL);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_r);
    assert_true(t_p._pt_left == NULL);
    assert_true(t_p._pt_right == &t_x);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_4_1_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_RED;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_RED;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:4
     *         gp(?)                   gp(?)
     *          |                       |
     *          p(?)          =>       s(?)
     *         /  \                   /   \
     *        x(b) s(b)              p(b) r(b)
     *            /   \             /  \
     *           l(?) r(r)        x(b) l(?)     new x = root
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_s._pt_left == &t_p);
    assert_true(t_s._pt_right == &t_r);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_s);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == &t_l);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_RED);
    assert_true(t_l._pt_parent == &t_p);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_4_1_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_RED;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_RED;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:4
     *         gp(?)                   gp(?)
     *          /                       /
     *          p(?)          =>       s(?)
     *         /  \                   /   \
     *        x(b) s(b)              p(b) r(b)
     *            /   \             /  \
     *           l(?) r(r)        x(b) l(?)     new x = root
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_s);
    assert_true(t_gp._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_RED);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_p);
    assert_true(t_s._pt_right == &t_r);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_s);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == &t_l);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_RED);
    assert_true(t_l._pt_parent == &t_p);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_4_1_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = NULL;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_x;
    t_p._pt_right = &t_s;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_RED;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_RED;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:4
     *         gp(?)                   gp(?)
     *          \                       \
     *          p(?)          =>       s(?)
     *         /  \                   /   \
     *        x(b) s(b)              p(b) r(b)
     *            /   \             /  \
     *           l(?) r(r)        x(b) l(?)     new x = root
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == NULL);
    assert_true(t_gp._pt_right == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_RED);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_p);
    assert_true(t_s._pt_right == &t_r);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_s);
    assert_true(t_p._pt_left == &t_x);
    assert_true(t_p._pt_right == &t_l);
    /* r */
    assert_true(t_r._t_color == _COLOR_BLACK);
    assert_true(t_r._pt_parent == &t_s);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_RED);
    assert_true(t_l._pt_parent == &t_p);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_4_2_1(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_p;
    /* p */
    t_p._t_color = _COLOR_BLACK;
    t_p._pt_parent = &pt_rb_tree->_t_rbroot;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_RED;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_RED;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:4
     *         gp(?)                   gp(?)
     *          |                       |
     *          p(?)          =>       s(?)
     *         /  \                   /   \
     *        s(b) x(b)              l(b) p(b)
     *       /   \                        /  \
     *      l(r) r(?)                    r(?) x(b)     new x = root
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_BLACK);
    assert_true(t_s._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_s);
    assert_true(t_p._pt_left == &t_r);
    assert_true(t_p._pt_right == &t_x);
    /* r */
    assert_true(t_r._t_color == _COLOR_RED);
    assert_true(t_r._pt_parent == &t_p);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_4_2_2(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = &t_p;
    t_gp._pt_right = NULL;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_RED;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_RED;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:4
     *         gp(?)                   gp(?)
     *          /                       /
     *          p(?)          =>       s(?)
     *         /  \                   /   \
     *        s(b) x(b)              l(b) p(b)
     *       /   \                        /  \
     *      l(r) r(?)                    r(?) x(b)     new x = root
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == &t_s);
    assert_true(t_gp._pt_right == NULL);
    /* s */
    assert_true(t_s._t_color == _COLOR_RED);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_s);
    assert_true(t_p._pt_left == &t_r);
    assert_true(t_p._pt_right == &t_x);
    /* r */
    assert_true(t_r._t_color == _COLOR_RED);
    assert_true(t_r._pt_parent == &t_p);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_fixup_deletion__case_4_2_3(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t t_gp;
    _rbnode_t t_p;
    _rbnode_t t_x;
    _rbnode_t t_s;
    _rbnode_t t_l;
    _rbnode_t t_r;

    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._pt_parent = &t_gp;
    /* gp */
    t_gp._t_color = _COLOR_BLACK;
    t_gp._pt_parent = &pt_rb_tree->_t_rbroot;
    t_gp._pt_left = NULL;
    t_gp._pt_right = &t_p;
    /* p */
    t_p._t_color = _COLOR_RED;
    t_p._pt_parent = &t_gp;
    t_p._pt_left = &t_s;
    t_p._pt_right = &t_x;
    /* x */
    t_x._t_color = _COLOR_BLACK;
    t_x._pt_parent = &t_p;
    t_x._pt_left = NULL;
    t_x._pt_right = NULL;
    /* s */
    t_s._t_color = _COLOR_BLACK;
    t_s._pt_parent = &t_p;
    t_s._pt_left = &t_l;
    t_s._pt_right = &t_r;
    /* l */
    t_l._t_color = _COLOR_RED;
    t_l._pt_parent = &t_s;
    t_l._pt_left = NULL;
    t_l._pt_right = NULL;
    /* r */
    t_r._t_color = _COLOR_RED;
    t_r._pt_parent = &t_s;
    t_r._pt_left = NULL;
    t_r._pt_right = NULL;

    /* Case:4
     *         gp(?)                   gp(?)
     *          \                       \
     *          p(?)          =>       s(?)
     *         /  \                   /   \
     *        s(b) x(b)              l(b) p(b)
     *       /   \                        /  \
     *      l(r) r(?)                    r(?) x(b)     new x = root
     */
    _rb_tree_fixup_deletion(pt_rb_tree, &t_x, &t_p);
    assert_true(pt_rb_tree->_t_rbroot._pt_parent == &t_gp);
    /* gp */
    assert_true(t_gp._t_color == _COLOR_BLACK);
    assert_true(t_gp._pt_parent == &pt_rb_tree->_t_rbroot);
    assert_true(t_gp._pt_left == NULL);
    assert_true(t_gp._pt_right == &t_s);
    /* s */
    assert_true(t_s._t_color == _COLOR_RED);
    assert_true(t_s._pt_parent == &t_gp);
    assert_true(t_s._pt_left == &t_l);
    assert_true(t_s._pt_right == &t_p);
    /* p */
    assert_true(t_p._t_color == _COLOR_BLACK);
    assert_true(t_p._pt_parent == &t_s);
    assert_true(t_p._pt_left == &t_r);
    assert_true(t_p._pt_right == &t_x);
    /* r */
    assert_true(t_r._t_color == _COLOR_RED);
    assert_true(t_r._pt_parent == &t_p);
    assert_true(t_r._pt_left == NULL);
    assert_true(t_r._pt_right == NULL);
    /* x */
    assert_true(t_x._t_color == _COLOR_BLACK);
    assert_true(t_x._pt_parent == &t_p);
    assert_true(t_x._pt_left == NULL);
    assert_true(t_x._pt_right == NULL);
    /* l */
    assert_true(t_l._t_color == _COLOR_BLACK);
    assert_true(t_l._pt_parent == &t_s);
    assert_true(t_l._pt_left == NULL);
    assert_true(t_l._pt_right == NULL);

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_rb_tree_init_elem_auxiliary)
void test__rb_tree_init_elem_auxiliary__null_rb_tree(void** state)
{
    _rbnode_t node;
    expect_assert_failure(_rb_tree_init_elem_auxiliary(NULL, &node));
}

void test__rb_tree_init_elem_auxiliary__null_node(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    expect_assert_failure(_rb_tree_init_elem_auxiliary(pt_rb_tree, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_init_elem_auxiliary__non_inited(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rbnode_t node;
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_init_elem_auxiliary(pt_rb_tree, &node));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_init_elem_auxiliary__c_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    int elem = 9;
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_insert_unique(pt_rb_tree, &elem);
    _rb_tree_init_elem_auxiliary(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent);
    assert_true(*(int*)pt_rb_tree->_t_rbroot._pt_parent->_pby_data == 0);

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_init_elem_auxiliary__cstr(void** state)
{
    _rbnode_t* p = NULL;
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    string_t* pt_str = create_string();
    _rb_tree_init(pt_rb_tree, NULL);
    string_init_cstr(pt_str, "abc");
    p = malloc(_RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)));

    _rb_tree_insert_unique(pt_rb_tree, pt_str);
    _rb_tree_init_elem_auxiliary(pt_rb_tree, p);
    assert_true(strcmp(string_c_str(p->_pby_data), "") == 0);

    _string_destroy_auxiliary(p->_pby_data);
    free(p);
    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pt_str);
}

void test__rb_tree_init_elem_auxiliary__cstl_builtin(void** state)
{
    _rb_tree_t* pt_rb_tree = _create_rb_tree("vector_t<int>");
    vector_t* pvec = create_vector(int);
    _rb_tree_init(pt_rb_tree, NULL);
    vector_init(pvec);

    _rb_tree_insert_unique(pt_rb_tree, pvec);
    _rb_tree_init_elem_auxiliary(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent);
    assert_true(vector_empty((vector_t*)pt_rb_tree->_t_rbroot._pt_parent->_pby_data));

    vector_destroy(pvec);
    _rb_tree_destroy(pt_rb_tree);
}

typedef struct _tag_test__rb_tree_init_elem_auxiliary__user_define
{
    int elem;
}_test__rb_tree_init_elem_auxiliary__user_define_t;

void test__rb_tree_init_elem_auxiliary__user_define(void** state)
{
    _rb_tree_t* pt_rb_tree = NULL;
    _test__rb_tree_init_elem_auxiliary__user_define_t elem;

    type_register(_test__rb_tree_init_elem_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pt_rb_tree = _create_rb_tree("_test__rb_tree_init_elem_auxiliary__user_define_t");

    _rb_tree_init(pt_rb_tree, NULL);
    elem.elem = 9;
    _rb_tree_insert_unique(pt_rb_tree, &elem);
    _rb_tree_init_elem_auxiliary(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent);
    assert_true(
        ((_test__rb_tree_init_elem_auxiliary__user_define_t*)pt_rb_tree->_t_rbroot._pt_parent->_pby_data)->elem == 0);

    _rb_tree_destroy(pt_rb_tree);
}

/*
 * test _rb_tree_elem_compare_auxiliary
 */
UT_CASE_DEFINATION(_rb_tree_elem_compare_auxiliary)
void test__rb_tree_elem_compare_auxiliary__null_rb_tree(void** state)
{
    int n_first;
    int n_second;
    bool_t t_result;
    expect_assert_failure(_rb_tree_elem_compare_auxiliary(NULL, &n_first, &n_second, &t_result));
}

void test__rb_tree_elem_compare_auxiliary__null_first(void** state)
{
    int n_second;
    bool_t t_result;
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_elem_compare_auxiliary(pt_rb_tree, NULL, &n_second, &t_result));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_elem_compare_auxiliary__null_second(void** state)
{
    int n_first;
    bool_t t_result;
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_elem_compare_auxiliary(pt_rb_tree, &n_first, NULL, &t_result));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_elem_compare_auxiliary__null_output(void** state)
{
    int n_first;
    int n_second;
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");

    _rb_tree_init(pt_rb_tree, NULL);
    expect_assert_failure(_rb_tree_elem_compare_auxiliary(pt_rb_tree, &n_first, &n_second, NULL));

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_elem_compare_auxiliary__non_inited(void** state)
{
    int n_first;
    int n_second;
    bool_t b_result;
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    pt_rb_tree->_t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_rb_tree_elem_compare_auxiliary(pt_rb_tree, &n_first, &n_second, &b_result));
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;

    _rb_tree_destroy(pt_rb_tree);
}

void test__rb_tree_elem_compare_auxiliary__int(void** state)
{
    int n_first = 5;
    int n_second = 9;
    bool_t b_result = false;
    _rb_tree_t* pt_rb_tree = _create_rb_tree("int");
    _rb_tree_init(pt_rb_tree, NULL);

    _rb_tree_elem_compare_auxiliary(pt_rb_tree, &n_first, &n_second, &b_result);
    assert_true(b_result);

    _rb_tree_destroy(pt_rb_tree);
}

static void _test__rb_tree_elem_compare_auxiliary__cstr_compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strcmp((char*)cpv_first, (char*)cpv_second) < 0 ? true : false;
}
void test__rb_tree_elem_compare_auxiliary__cstr(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();
    bool_t b_result = false;
    _rb_tree_t* pt_rb_tree = _create_rb_tree("char*");
    _rb_tree_init(pt_rb_tree, _test__rb_tree_elem_compare_auxiliary__cstr_compare);

    string_init_cstr(pstr_first, "abc");
    string_init_cstr(pstr_second, "xyz");
    _rb_tree_elem_compare_auxiliary(pt_rb_tree, pstr_first, pstr_second, &b_result);
    assert_true(b_result);

    _rb_tree_destroy(pt_rb_tree);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

