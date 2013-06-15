#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_multiset_aux.h"

#include "ut_def.h"
#include "ut_cstl_multiset_private.h"

UT_SUIT_DEFINATION(cstl_multiset_private, _create_multiset)

/*
 * test _create_multiset
 */
UT_CASE_DEFINATION(_create_multiset)
void test__create_multiset__null_typename(void** state)
{
    expect_assert_failure(_create_multiset(NULL));
}

void test__create_multiset__c_builtin(void** state)
{
    multiset_t* pt_multiset = _create_multiset("double");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset__cstr(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset__libcstl_builtin(void** state)
{
    multiset_t* pt_multiset = _create_multiset("vector_t<int>");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

typedef struct _test_test__create_multiset__user_define
{
    int n_elem;
}_test__create_multiset__user_define_t;

void test__create_multiset__user_define(void** state)
{
    multiset_t* pt_multiset = NULL;

    type_register(_test__create_multiset__user_define_t, NULL, NULL, NULL, NULL);
    pt_multiset = _create_multiset("_test__create_multiset__user_define_t");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset__unregister(void** state)
{
    multiset_t* pt_multiset = _create_multiset("test__create_multiset__unregister_t");
    assert_true(pt_multiset == NULL);
}

/*
 * test _create_multiset_auxiliary
 */
UT_CASE_DEFINATION(_create_multiset_auxiliary)
void test__create_multiset_auxiliary__null_multiset(void** state)
{
    expect_assert_failure(_create_multiset_auxiliary(NULL, "int"));
}

void test__create_multiset_auxiliary__null_typename(void** state)
{
    multiset_t rbtree;
    expect_assert_failure(_create_multiset_auxiliary(&rbtree, NULL));
}

void test__create_multiset_auxiliary__unregistered(void** state)
{
    multiset_t* pt_multiset = malloc(sizeof(multiset_t));
    assert_false(_create_multiset_auxiliary(pt_multiset, "_test__create_multiset_auxiliary__unregistered_t"));

    free(pt_multiset);
}

void test__create_multiset_auxiliary__c_builtin(void** state)
{
    multiset_t* pt_multiset = malloc(sizeof(multiset_t));
    assert_true(_create_multiset_auxiliary(pt_multiset, "int"));
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset_auxiliary__cstr(void** state)
{
    multiset_t* pt_multiset = malloc(sizeof(multiset_t));
    assert_true(_create_multiset_auxiliary(pt_multiset, "char*"));
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset_auxiliary__libcstl_builtin(void** state)
{
    multiset_t* pt_multiset = malloc(sizeof(multiset_t));
    assert_true(_create_multiset_auxiliary(pt_multiset, "vector_t<int>"));
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

typedef struct _tag_test__create_multiset_auxiliary__user_define
{
    int n_elem;
}_test__create_multiset_auxiliary__user_define_t;

void test__create_multiset_auxiliary__user_define(void** state)
{
    multiset_t* pt_multiset = NULL;

    type_register(_test__create_multiset_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = malloc(sizeof(multiset_t));
    assert_true(_create_multiset_auxiliary(pt_multiset, "_test__create_multiset_auxiliary__user_define_t"));
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_destroy_auxiliary
 */
UT_CASE_DEFINATION(_multiset_destroy_auxiliary)
void test__multiset_destroy_auxiliary__null_multiset(void** state)
{
    expect_assert_failure(_multiset_destroy_auxiliary(NULL));
}

void test__multiset_destroy_auxiliary__non_created(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_destroy_auxiliary(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_destroy_auxiliary(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_destroy_auxiliary__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_init(pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_destroy_auxiliary(pt_multiset));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_destroy_auxiliary(pt_multiset));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_destroy_auxiliary__empty(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_init_ex(pt_multiset, NULL);

    _multiset_destroy_auxiliary(pt_multiset);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(pt_multiset->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_multiset->_t_tree._t_avlroot._pt_left == &pt_multiset->_t_tree._t_avlroot);
    assert_true(pt_multiset->_t_tree._t_avlroot._pt_right == &pt_multiset->_t_tree._t_avlroot);
    assert_true(pt_multiset->_t_tree._t_nodecount == 0);
    assert_true(pt_multiset->_t_tree._t_compare == NULL);
#else
    assert_true(pt_multiset->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_multiset->_t_tree._t_rbroot._pt_left == &pt_multiset->_t_tree._t_rbroot);
    assert_true(pt_multiset->_t_tree._t_rbroot._pt_right == &pt_multiset->_t_tree._t_rbroot);
    assert_true(pt_multiset->_t_tree._t_nodecount == 0);
    assert_true(pt_multiset->_t_tree._t_compare == NULL);
#endif
    free(pt_multiset);
}

void test__multiset_destroy_auxiliary__non_empty(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem = 9;
    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, elem);

    _multiset_destroy_auxiliary(pt_multiset);
#ifdef CSTL_MULTISET_AVL_TREE
    assert_true(pt_multiset->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_multiset->_t_tree._t_avlroot._pt_left == &pt_multiset->_t_tree._t_avlroot);
    assert_true(pt_multiset->_t_tree._t_avlroot._pt_right == &pt_multiset->_t_tree._t_avlroot);
    assert_true(pt_multiset->_t_tree._t_nodecount == 0);
    assert_true(pt_multiset->_t_tree._t_compare == NULL);
#else
    assert_true(pt_multiset->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_multiset->_t_tree._t_rbroot._pt_left == &pt_multiset->_t_tree._t_rbroot);
    assert_true(pt_multiset->_t_tree._t_rbroot._pt_right == &pt_multiset->_t_tree._t_rbroot);
    assert_true(pt_multiset->_t_tree._t_nodecount == 0);
    assert_true(pt_multiset->_t_tree._t_compare == NULL);
#endif
    free(pt_multiset);
}

/*
 * test _multiset_find and _multiset_find_varg
 */
UT_CASE_DEFINATION(_multiset_find__multiset_find_varg)
void test__multiset_find__multiset_find_varg__null_multiset(void** state)
{
    expect_assert_failure(_multiset_find(NULL, 9));
}

void test__multiset_find__multiset_find_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_init(pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_find(pt_multiset, 9));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_find(pt_multiset, 9));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_find__multiset_find_varg__c_builtin_find(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int elem;
    int i;

    multiset_init(pt_multiset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 2;
    it_iter = _multiset_find(pt_multiset, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    multiset_destroy(pt_multiset);
}

void test__multiset_find__multiset_find_varg__c_builtin_not_find(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int i;

    multiset_init(pt_multiset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    it_iter = _multiset_find(pt_multiset, 42);
    assert_true(iterator_equal(it_iter, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test__multiset_find__multiset_find_varg__cstr_find(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    it_iter = multiset_find(pt_multiset, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "ggg") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_find__multiset_find_varg__cstr_not_find(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    it_iter = _multiset_find(pt_multiset, "vvvvv");
    assert_true(iterator_equal(it_iter, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test__multiset_find__multiset_find_varg__libcstl_builtin_find(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init(pt_multiset);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multiset_find(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_find__multiset_find_varg__libcstl_builtin_not_find(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init(pt_multiset);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _multiset_find(pt_multiset, plist);
    assert_true(iterator_equal(it_iter, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_find__multiset_find_varg__user_define
{
    int n_elem;
}_test__multiset_find__multiset_find_varg__user_define_t;
void test__multiset_find__multiset_find_varg__user_define_find(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter;
    _test__multiset_find__multiset_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_find__multiset_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_find__multiset_find_varg__user_define_t");
    multiset_init(pt_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    it_iter = _multiset_find(pt_multiset, &elem);
    assert_true(((_test__multiset_find__multiset_find_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    multiset_destroy(pt_multiset);
}

void test__multiset_find__multiset_find_varg__user_define_not_find(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_find__multiset_find_varg__user_define_t");
    multiset_iterator_t it_iter;
    _test__multiset_find__multiset_find_varg__user_define_t elem;
    int i = 0;

    multiset_init(pt_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 78;
    it_iter = _multiset_find(pt_multiset, &elem);
    assert_true(iterator_equal(it_iter, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_count and _multiset_count_varg
 */
UT_CASE_DEFINATION(_multiset_count__multiset_count_varg)
void test__multiset_count__multiset_count_varg__null_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_multiset_count(NULL, elem));
}

void test__multiset_count__multiset_count_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem = 9;
    multiset_init(pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_count(pt_multiset, elem));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_count(pt_multiset, elem));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__c_builtin_0(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 1222;
    assert_true(_multiset_count(pt_multiset, elem) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__c_builtin_1(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem;
    int i;

    multiset_init(pt_multiset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 2;
    assert_true(_multiset_count(pt_multiset, elem) == 1);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__c_builtin_n(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem;
    int i;

    multiset_init(pt_multiset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
        multiset_insert(pt_multiset, i);
        multiset_insert(pt_multiset, i);
    }

    elem = 2;
    assert_true(_multiset_count(pt_multiset, elem) == 3);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__cstr_0(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");

    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    assert_true(_multiset_count(pt_multiset, "uuuu") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__cstr_1(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");

    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    assert_true(_multiset_count(pt_multiset, "ggg") == 1);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__cstr_n(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");

    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    assert_true(_multiset_count(pt_multiset, "ggg") == 4);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__libcstl_builtin_0(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init(pt_multiset);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_multiset_count(pt_multiset, plist) == 0);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_count__multiset_count_varg__libcstl_builtin_1(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init(pt_multiset);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multiset_count(pt_multiset, plist) == 1);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_count__multiset_count_varg__libcstl_builtin_n(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init(pt_multiset);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
        multiset_insert(pt_multiset, plist);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multiset_count(pt_multiset, plist) == 3);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_count__multiset_count_varg__user_define
{
    int n_elem;
}_test__multiset_count__multiset_count_varg__user_define_t;
void test__multiset_count__multiset_count_varg__user_define_0(void** state)
{
    multiset_t* pt_multiset = NULL;
    _test__multiset_count__multiset_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_count__multiset_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_count__multiset_count_varg__user_define_t");
    multiset_init(pt_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 88;
    assert_true(_multiset_count(pt_multiset, &elem) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__user_define_1(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_count__multiset_count_varg__user_define_t");
    _test__multiset_count__multiset_count_varg__user_define_t elem;
    int i = 0;

    multiset_init(pt_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_multiset_count(pt_multiset, &elem) == 1);

    multiset_destroy(pt_multiset);
}

void test__multiset_count__multiset_count_varg__user_define_n(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_count__multiset_count_varg__user_define_t");
    _test__multiset_count__multiset_count_varg__user_define_t elem;
    int i = 0;

    multiset_init(pt_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_multiset_count(pt_multiset, &elem) == 2);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_lower_bound and _multiset_lower_bound_varg
 */
UT_CASE_DEFINATION(_multiset_lower_bound__multiset_lower_bound_varg)
void test__multiset_lower_bound__multiset_lower_bound_varg__null_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_multiset_lower_bound(NULL, elem));
}

void test__multiset_lower_bound__multiset_lower_bound_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem = 9;
    multiset_init(pt_multiset);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_lower_bound(pt_multiset, &elem));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_lower_bound(pt_multiset, elem));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_lower_bound__multiset_lower_bound_varg__c_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int elem;
    int i;

    multiset_init(pt_multiset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 2;
    it_iter = _multiset_lower_bound(pt_multiset, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    multiset_destroy(pt_multiset);
}

void test__multiset_lower_bound__multiset_lower_bound_varg__c_builtin_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int elem;
    int i;

    multiset_init(pt_multiset);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = -8;
    it_iter = _multiset_lower_bound(pt_multiset, elem);
    assert_true(iterator_equal(it_iter, multiset_begin(pt_multiset)));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_lower_bound__multiset_lower_bound_varg__cstr_lower_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    it_iter = _multiset_lower_bound(pt_multiset, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "ggg") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_lower_bound__multiset_lower_bound_varg__cstr_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init(pt_multiset);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    it_iter = _multiset_lower_bound(pt_multiset, "vvvv");
    assert_true(iterator_equal(it_iter, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test__multiset_lower_bound__multiset_lower_bound_varg__libcstl_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init(pt_multiset);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multiset_lower_bound(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_lower_bound__multiset_lower_bound_varg__libcstl_builtin_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init(pt_multiset);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _multiset_lower_bound(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_lower_bound__multiset_lower_bound_varg__user_define
{
    int n_elem;
}_test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t;
void test__multiset_lower_bound__multiset_lower_bound_varg__user_define_equal(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter;
    _test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t");
    multiset_init(pt_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    it_iter = _multiset_lower_bound(pt_multiset, &elem);
    assert_true(((_test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    multiset_destroy(pt_multiset);
}

void test__multiset_lower_bound__multiset_lower_bound_varg__user_define_greater(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t");
    multiset_iterator_t it_iter;
    _test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t elem;
    int i = 0;

    multiset_init(pt_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 7;
    it_iter = _multiset_lower_bound(pt_multiset, &elem);
    assert_true(((_test__multiset_lower_bound__multiset_lower_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_upper_bound and _multiset_upper_bound_varg
 */
UT_CASE_DEFINATION(_multiset_upper_bound__multiset_upper_bound_varg)
void test__multiset_upper_bound__multiset_upper_bound_varg__null_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_multiset_upper_bound(NULL, elem));
}

void test__multiset_upper_bound__multiset_upper_bound_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem = 9;
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_upper_bound(pt_multiset, &elem));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_upper_bound(pt_multiset, &elem));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_upper_bound__multiset_upper_bound_varg__c_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 2;
    it_iter = _multiset_upper_bound(pt_multiset, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    multiset_destroy(pt_multiset);
}

void test__multiset_upper_bound__multiset_upper_bound_varg__c_builtin_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = -8;
    it_iter = _multiset_upper_bound(pt_multiset, elem);
    assert_true(iterator_equal(it_iter, multiset_begin(pt_multiset)));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_upper_bound__multiset_upper_bound_varg__cstr_upper_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    it_iter = _multiset_upper_bound(pt_multiset, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "linux") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_upper_bound__multiset_upper_bound_varg__cstr_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    it_iter = _multiset_upper_bound(pt_multiset, "vvv");
    assert_true(iterator_equal(it_iter, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test__multiset_upper_bound__multiset_upper_bound_varg__libcstl_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multiset_upper_bound(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 7);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_upper_bound__multiset_upper_bound_varg__libcstl_builtin_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _multiset_upper_bound(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_upper_bound__multiset_upper_bound_varg__user_define
{
    int n_elem;
}_test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t;
void test__multiset_upper_bound__multiset_upper_bound_varg__user_define_equal(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter;
    _test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t");
    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    it_iter = _multiset_upper_bound(pt_multiset, &elem);
    assert_true(((_test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 9);

    multiset_destroy(pt_multiset);
}

void test__multiset_upper_bound__multiset_upper_bound_varg__user_define_greater(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t");
    multiset_iterator_t it_iter;
    _test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t elem;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 7;
    it_iter = _multiset_upper_bound(pt_multiset, &elem);
    assert_true(((_test__multiset_upper_bound__multiset_upper_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_equal_range and _multiset_equal_range_varg
 */
UT_CASE_DEFINATION(_multiset_equal_range__multiset_equal_range_varg)
void test__multiset_equal_range__multiset_equal_range_varg__null_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_multiset_equal_range(NULL, elem));
}

void test__multiset_equal_range__multiset_equal_range_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem = 9;
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_equal_range(pt_multiset, elem));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_equal_range(pt_multiset, elem));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_equal_range__multiset_equal_range_varg__c_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    range_t r_range;
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 2;
    r_range = _multiset_equal_range(pt_multiset, elem);
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 2);
    assert_true(*(int*)iterator_get_pointer(r_range.it_end) == 3);

    multiset_destroy(pt_multiset);
}

void test__multiset_equal_range__multiset_equal_range_varg__c_builtin_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    range_t r_range;
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = -8;
    r_range = _multiset_equal_range(pt_multiset, elem);
    assert_true(iterator_equal(r_range.it_begin, multiset_begin(pt_multiset)));
    assert_true(iterator_equal(r_range.it_end, multiset_begin(pt_multiset)));
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_equal_range__multiset_equal_range_varg__cstr_upper_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    range_t r_range;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    r_range = _multiset_equal_range(pt_multiset, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_begin), "ggg") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_end), "linux") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_equal_range__multiset_equal_range_varg__cstr_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    range_t r_range;

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    r_range = _multiset_equal_range(pt_multiset, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, multiset_end(pt_multiset)));
    assert_true(iterator_equal(r_range.it_end, multiset_end(pt_multiset)));

    multiset_destroy(pt_multiset);
}

void test__multiset_equal_range__multiset_equal_range_varg__libcstl_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _multiset_equal_range(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 7);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_equal_range__multiset_equal_range_varg__libcstl_builtin_greater(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _multiset_equal_range(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 6);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_equal_range__multiset_equal_range_varg__user_define
{
    int n_elem;
}_test__multiset_equal_range__multiset_equal_range_varg__user_define_t;
void test__multiset_equal_range__multiset_equal_range_varg__user_define_equal(void** state)
{
    multiset_t* pt_multiset = NULL;
    range_t r_range;
    _test__multiset_equal_range__multiset_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_equal_range__multiset_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_equal_range__multiset_equal_range_varg__user_define_t");
    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    r_range = _multiset_equal_range(pt_multiset, &elem);
    assert_true(((_test__multiset_equal_range__multiset_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__multiset_equal_range__multiset_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 9);

    multiset_destroy(pt_multiset);
}

void test__multiset_equal_range__multiset_equal_range_varg__user_define_greater(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_equal_range__multiset_equal_range_varg__user_define_t");
    range_t r_range;
    _test__multiset_equal_range__multiset_equal_range_varg__user_define_t elem;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 7;
    r_range = _multiset_equal_range(pt_multiset, &elem);
    assert_true(((_test__multiset_equal_range__multiset_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__multiset_equal_range__multiset_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 8);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_erase and _multiset_erase_varg
 */
UT_CASE_DEFINATION(_multiset_erase__multiset_erase_varg)
void test__multiset_erase__multiset_erase_varg__null_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_multiset_erase(NULL, elem));
}

void test__multiset_erase__multiset_erase_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem = 9;
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_erase(pt_multiset, elem));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_erase(pt_multiset, elem));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__c_builtin_0(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 24;
    assert_true(_multiset_erase(pt_multiset, elem) == 0);
    assert_true(multiset_size(pt_multiset) == 10);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__c_builtin_1(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
    }

    elem = 8;
    assert_true(_multiset_erase(pt_multiset, elem) == 1);
    assert_true(multiset_size(pt_multiset) == 9);
    assert_true(_multiset_count(pt_multiset, elem) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__c_builtin_n(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        multiset_insert(pt_multiset, i);
        multiset_insert(pt_multiset, i);
        multiset_insert(pt_multiset, i);
    }

    elem = 8;
    assert_true(_multiset_erase(pt_multiset, elem) == 3);
    assert_true(multiset_size(pt_multiset) == 27);
    assert_true(_multiset_count(pt_multiset, elem) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__cstr_0(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    assert_true(_multiset_erase(pt_multiset, "gggppgg") == 0);
    assert_true(multiset_size(pt_multiset) == 5);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__cstr_1(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    assert_true(_multiset_erase(pt_multiset, "ggg") == 1);
    assert_true(multiset_size(pt_multiset) == 4);
    assert_true(_multiset_count(pt_multiset, "ggg") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__cstr_n(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");

    multiset_init_ex(pt_multiset, NULL);
    multiset_insert(pt_multiset, "aaa");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "ggg");
    multiset_insert(pt_multiset, "nghl");
    multiset_insert(pt_multiset, "asery");
    multiset_insert(pt_multiset, "linux");

    assert_true(_multiset_erase(pt_multiset, "ggg") == 4);
    assert_true(multiset_size(pt_multiset) == 4);
    assert_true(_multiset_count(pt_multiset, "ggg") == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__libcstl_builtin_0(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_multiset_erase(pt_multiset, plist) == 0);
    assert_true(multiset_size(pt_multiset) == 10);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_erase__multiset_erase_varg__libcstl_builtin_1(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multiset_erase(pt_multiset, plist) == 1);
    assert_true(multiset_size(pt_multiset) == 9);
    assert_true(_multiset_count(pt_multiset, plist) == 0);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_erase__multiset_erase_varg__libcstl_builtin_n(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        multiset_insert(pt_multiset, plist);
        multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multiset_erase(pt_multiset, plist) == 2);
    assert_true(multiset_size(pt_multiset) == 18);
    assert_true(_multiset_count(pt_multiset, plist) == 0);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_erase__multiset_erase_varg__user_define
{
    int n_elem;
}_test__multiset_erase__multiset_erase_varg__user_define_t;
void test__multiset_erase__multiset_erase_varg__user_define_0(void** state)
{
    multiset_t* pt_multiset = NULL;
    _test__multiset_erase__multiset_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_erase__multiset_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_erase__multiset_erase_varg__user_define_t");
    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 86;
    assert_true(_multiset_erase(pt_multiset, &elem) == 0);
    assert_true(multiset_size(pt_multiset) == 10);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__user_define_1(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_erase__multiset_erase_varg__user_define_t");
    _test__multiset_erase__multiset_erase_varg__user_define_t elem;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_multiset_erase(pt_multiset, &elem) == 1);
    assert_true(multiset_size(pt_multiset) == 9);
    assert_true(_multiset_count(pt_multiset, &elem) == 0);

    multiset_destroy(pt_multiset);
}

void test__multiset_erase__multiset_erase_varg__user_define_n(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_erase__multiset_erase_varg__user_define_t");
    _test__multiset_erase__multiset_erase_varg__user_define_t elem;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        multiset_insert(pt_multiset, &elem);
        multiset_insert(pt_multiset, &elem);
        multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_multiset_erase(pt_multiset, &elem) == 3);
    assert_true(multiset_size(pt_multiset) == 27);
    assert_true(_multiset_count(pt_multiset, &elem) == 0);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_insert and _multiset_insert_varg
 */
UT_CASE_DEFINATION(_multiset_insert__multiset_insert_varg)
void test__multiset_insert_varg__null_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_multiset_insert(NULL, elem));
}

void test__multiset_insert_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    int elem = 9;
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multiset_insert(pt_multiset, elem));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_insert(pt_multiset, elem));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_varg__c_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        _multiset_insert(pt_multiset, i);
    }

    elem = 2;
    it_iter = _multiset_insert(pt_multiset, elem);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == 2);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_varg__c_builtin_not_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter;
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        _multiset_insert(pt_multiset, i);
    }

    elem = -8;
    it_iter = _multiset_insert(pt_multiset, elem);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == -8);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_varg__cstr_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init_ex(pt_multiset, NULL);
    _multiset_insert(pt_multiset, "aaa");
    _multiset_insert(pt_multiset, "ggg");
    _multiset_insert(pt_multiset, "nghl");
    _multiset_insert(pt_multiset, "asery");
    _multiset_insert(pt_multiset, "linux");

    it_iter = _multiset_insert(pt_multiset, "ggg");
    assert_true(strcmp((char*)_multiset_iterator_get_pointer(it_iter), "ggg") == 0);
    assert_true(multiset_size(pt_multiset) == 6);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_varg__cstr_not_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter;

    multiset_init_ex(pt_multiset, NULL);
    _multiset_insert(pt_multiset, "aaa");
    _multiset_insert(pt_multiset, "ggg");
    _multiset_insert(pt_multiset, "nghl");
    _multiset_insert(pt_multiset, "asery");
    _multiset_insert(pt_multiset, "linux");

    it_iter = _multiset_insert(pt_multiset, "vvvv");
    assert_true(strcmp((char*)_multiset_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(multiset_size(pt_multiset) == 6);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_varg__libcstl_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multiset_insert(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)_multiset_iterator_get_pointer(it_iter)) == 6);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_insert_varg__libcstl_builtin_not_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _multiset_insert(pt_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _multiset_insert(pt_multiset, plist);
    assert_true(*(int*)list_front((list_t*)_multiset_iterator_get_pointer(it_iter)) == 5);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_insert_varg__user_define
{
    int n_elem;
}_test__multiset_insert_varg__user_define_t;
void test__multiset_insert_varg__user_define_equal(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter;
    _test__multiset_insert_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_insert_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_insert_varg__user_define_t");
    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 8;
    it_iter = _multiset_insert(pt_multiset, &elem);
    assert_true(((_test__multiset_insert_varg__user_define_t*)_multiset_iterator_get_pointer(it_iter))->n_elem == 8);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_varg__user_define_not_equal(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_insert_varg__user_define_t");
    multiset_iterator_t it_iter;
    _test__multiset_insert_varg__user_define_t elem;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _multiset_insert(pt_multiset, &elem);
    }

    elem.n_elem = 7;
    it_iter = _multiset_insert(pt_multiset, &elem);
    assert_true(((_test__multiset_insert_varg__user_define_t*)_multiset_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_insert_hint and _multiset_insert_hint_varg
 */
UT_CASE_DEFINATION(_multiset_insert_hint__multiset_insert_hint_varg)
void test__multiset_insert_hint_varg__null_multiset(void** state)
{
    int elem = 9;
    multiset_iterator_t it_hint;
    expect_assert_failure(_multiset_insert_hint(NULL, it_hint, elem));
}

void test__multiset_insert_hint_varg__non_inited(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_hint;
    int elem = 9;
    multiset_init_ex(pt_multiset, NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    pt_multiset->_t_tree._t_avlroot._un_height = 4;
    expect_assert_failure(_multiset_insert_hint(pt_multiset, it_hint, elem));
    pt_multiset->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multiset_insert_hint(pt_multiset, it_hint, elem));
    pt_multiset->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_hint_varg__c_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter = create_multiset_iterator();
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        _multiset_insert_hint(pt_multiset, it_iter, i);
    }

    elem = 2;
    it_iter = _multiset_insert_hint(pt_multiset, it_iter, elem);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == 2);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_hint_varg__c_builtin_not_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("int");
    multiset_iterator_t it_iter = create_multiset_iterator();
    int elem;
    int i;

    multiset_init_ex(pt_multiset, NULL);
    for(i = 0; i < 10; ++i)
    {
        _multiset_insert_hint(pt_multiset, it_iter, i);
    }

    elem = -8;
    it_iter = _multiset_insert_hint(pt_multiset, it_iter, elem);
    assert_true(*(int*)_multiset_iterator_get_pointer(it_iter) == -8);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_hint_varg__cstr_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter = create_multiset_iterator();

    multiset_init_ex(pt_multiset, NULL);
    _multiset_insert_hint(pt_multiset, it_iter, "aaa");
    _multiset_insert_hint(pt_multiset, it_iter, "ggg");
    _multiset_insert_hint(pt_multiset, it_iter, "nghl");
    _multiset_insert_hint(pt_multiset, it_iter, "asery");
    _multiset_insert_hint(pt_multiset, it_iter, "linux");

    it_iter = _multiset_insert_hint(pt_multiset, it_iter, "ggg");
    assert_true(strcmp((char*)_multiset_iterator_get_pointer(it_iter), "ggg") == 0);
    assert_true(multiset_size(pt_multiset) == 6);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_hint_varg__cstr_not_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    multiset_iterator_t it_iter = create_multiset_iterator();

    multiset_init_ex(pt_multiset, NULL);
    _multiset_insert_hint(pt_multiset, it_iter, "aaa");
    _multiset_insert_hint(pt_multiset, it_iter, "ggg");
    _multiset_insert_hint(pt_multiset, it_iter, "nghl");
    _multiset_insert_hint(pt_multiset, it_iter, "asery");
    _multiset_insert_hint(pt_multiset, it_iter, "linux");

    it_iter = _multiset_insert_hint(pt_multiset, it_iter, "vvvv");
    assert_true(strcmp((char*)_multiset_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(multiset_size(pt_multiset) == 6);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_hint_varg__libcstl_builtin_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter = create_multiset_iterator();
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _multiset_insert_hint(pt_multiset, it_iter, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multiset_insert_hint(pt_multiset, it_iter, plist);
    assert_true(*(int*)list_front((list_t*)_multiset_iterator_get_pointer(it_iter)) == 6);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

void test__multiset_insert_hint_varg__libcstl_builtin_not_equal(void** state)
{
    multiset_t* pt_multiset = _create_multiset("list_t<int>");
    multiset_iterator_t it_iter = create_multiset_iterator();
    list_t* plist = create_list(int);
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _multiset_insert_hint(pt_multiset, it_iter, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _multiset_insert_hint(pt_multiset, it_iter, plist);
    assert_true(*(int*)list_front((list_t*)_multiset_iterator_get_pointer(it_iter)) == 5);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__multiset_insert_hint_varg__user_define
{
    int n_elem;
}_test__multiset_insert_hint_varg__user_define_t;
void test__multiset_insert_hint_varg__user_define_equal(void** state)
{
    multiset_t* pt_multiset = NULL;
    multiset_iterator_t it_iter = create_multiset_iterator();
    _test__multiset_insert_hint_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multiset_insert_hint_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multiset = _create_multiset("_test__multiset_insert_hint_varg__user_define_t");
    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _multiset_insert_hint(pt_multiset, it_iter, &elem);
    }

    elem.n_elem = 8;
    it_iter = _multiset_insert_hint(pt_multiset, it_iter, &elem);
    assert_true(((_test__multiset_insert_hint_varg__user_define_t*)_multiset_iterator_get_pointer(it_iter))->n_elem == 8);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

void test__multiset_insert_hint_varg__user_define_not_equal(void** state)
{
    multiset_t* pt_multiset =  _create_multiset("_test__multiset_insert_hint_varg__user_define_t");
    multiset_iterator_t it_iter = create_multiset_iterator();
    _test__multiset_insert_hint_varg__user_define_t elem;
    int i = 0;

    multiset_init_ex(pt_multiset, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _multiset_insert_hint(pt_multiset, it_iter, &elem);
    }

    elem.n_elem = 7;
    it_iter = _multiset_insert_hint(pt_multiset, it_iter, &elem);
    assert_true(((_test__multiset_insert_hint_varg__user_define_t*)_multiset_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(multiset_size(pt_multiset) == 11);

    multiset_destroy(pt_multiset);
}

/*
 * test _multiset_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_multiset_init_elem_auxiliary)
void test__multiset_init_elem_auxiliary__null_multiset_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_multiset_init_elem_auxiliary(NULL, &elem));
}

void test__multiset_init_elem_auxiliary__null_elem(void** state)
{
    multiset_t* pset = create_multiset(int);

    expect_assert_failure(_multiset_init_elem_auxiliary(pset, NULL));

    multiset_destroy(pset);
}

void test__multiset_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    multiset_t* pset = create_multiset(int);
    multiset_init(pset);

    _multiset_init_elem_auxiliary(pset, &elem);
    assert_true(elem == 0);

    multiset_destroy(pset);
}

void test__multiset_init_elem_auxiliary__successfully_cstr(void** state)
{
    string_t elem;
    multiset_t* pset = create_multiset(char*);
    multiset_init_ex(pset, NULL);

    multiset_insert(pset, "abc");
    multiset_insert(pset, "def");
#ifdef CSTL_MULTISET_AVL_TREE
    _multiset_init_elem_auxiliary(pset, &elem);
#else
    _multiset_init_elem_auxiliary(pset, &elem);
#endif
    assert_true(strcmp(string_c_str(&elem), "") == 0);

    _string_destroy_auxiliary(&elem);
    multiset_destroy(pset);
}

void test__multiset_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    multiset_t* pset = create_multiset(iterator_t);
    multiset_init_ex(pset, NULL);

    multiset_insert(pset, &it_iter);

    _multiset_init_elem_auxiliary(pset, (void*)iterator_get_pointer(multiset_begin(pset)));
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)iterator_get_pointer(multiset_begin(pset)), &it_iter, sizeof(iterator_t)) == 0);

    multiset_destroy(pset);
}

void test__multiset_init_elem_auxiliary__successfully_container(void** state)
{
    vector_t vec;
    multiset_t* pset = create_multiset(vector_t<int>);

    _multiset_init_elem_auxiliary(pset, &vec);
    assert_true(_vector_is_inited(&vec));

    multiset_destroy(pset);
}

typedef struct _tag_test__multiset_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__multiset_init_elem_auxiliary__successfully_user_defined_t;

void test__multiset_init_elem_auxiliary__successfully_user_defined(void** state)
{
    _test__multiset_init_elem_auxiliary__successfully_user_defined_t t_user;
    multiset_t* pset = NULL;

    type_register(_test__multiset_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pset = create_multiset(_test__multiset_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _multiset_init_elem_auxiliary(pset, &t_user);
    assert_true(t_user.n_elem == 0);

    multiset_destroy(pset);
}
