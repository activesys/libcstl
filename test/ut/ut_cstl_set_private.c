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
#include "cstl_set_aux.h"

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

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 50;
    expect_assert_failure(_set_destroy_auxiliary(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_destroy_auxiliary(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_destroy_auxiliary__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    set_init(pt_set);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_destroy_auxiliary(pt_set));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_destroy_auxiliary(pt_set));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_destroy_auxiliary__empty(void** state)
{
    set_t* pt_set = _create_set("int");
    set_init_ex(pt_set, NULL);

    _set_destroy_auxiliary(pt_set);
#ifdef CSTL_SET_AVL_TREE
    assert_true(pt_set->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_set->_t_tree._t_avlroot._pt_left == &pt_set->_t_tree._t_avlroot);
    assert_true(pt_set->_t_tree._t_avlroot._pt_right == &pt_set->_t_tree._t_avlroot);
    assert_true(pt_set->_t_tree._t_nodecount == 0);
    assert_true(pt_set->_t_tree._t_compare == NULL);
#else
    assert_true(pt_set->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_set->_t_tree._t_rbroot._pt_left == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_rbroot._pt_right == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_nodecount == 0);
    assert_true(pt_set->_t_tree._t_compare == NULL);
#endif
    free(pt_set);
}

void test__set_destroy_auxiliary__non_empty(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init(pt_set);
    set_insert(pt_set, elem);

    _set_destroy_auxiliary(pt_set);
#ifdef CSTL_SET_AVL_TREE
    assert_true(pt_set->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_set->_t_tree._t_avlroot._pt_left == &pt_set->_t_tree._t_avlroot);
    assert_true(pt_set->_t_tree._t_avlroot._pt_right == &pt_set->_t_tree._t_avlroot);
    assert_true(pt_set->_t_tree._t_nodecount == 0);
    assert_true(pt_set->_t_tree._t_compare == NULL);
#else
    assert_true(pt_set->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_set->_t_tree._t_rbroot._pt_left == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_rbroot._pt_right == &pt_set->_t_tree._t_rbroot);
    assert_true(pt_set->_t_tree._t_nodecount == 0);
    assert_true(pt_set->_t_tree._t_compare == NULL);
#endif
    free(pt_set);
}

/*
 * test _set_find and _set_find_varg
 */
UT_CASE_DEFINATION(_set_find__set_find_varg)
void test__set_find__set_find_varg__null_set(void** state)
{
    expect_assert_failure(_set_find(NULL, 9));
}

void test__set_find__set_find_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    set_init(pt_set);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_find(pt_set, 9));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_find(pt_set, 9));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_find__set_find_varg__c_builtin_find(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int elem;
    int i;

    set_init(pt_set);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 2;
    it_iter = _set_find(pt_set, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    set_destroy(pt_set);
}

void test__set_find__set_find_varg__c_builtin_not_find(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int i;

    set_init(pt_set);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    it_iter = _set_find(pt_set, 42);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));

    set_destroy(pt_set);
}

void test__set_find__set_find_varg__cstr_find(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init(pt_set);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    it_iter = set_find(pt_set, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "ggg") == 0);

    set_destroy(pt_set);
}

void test__set_find__set_find_varg__cstr_not_find(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init(pt_set);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    it_iter = _set_find(pt_set, "vvvvv");
    assert_true(iterator_equal(it_iter, set_end(pt_set)));

    set_destroy(pt_set);
}

void test__set_find__set_find_varg__libcstl_builtin_find(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init(pt_set);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _set_find(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_find__set_find_varg__libcstl_builtin_not_find(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init(pt_set);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _set_find(pt_set, plist);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_find__set_find_varg__user_define
{
    int n_elem;
}_test__set_find__set_find_varg__user_define_t;
void test__set_find__set_find_varg__user_define_find(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter;
    _test__set_find__set_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_find__set_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_find__set_find_varg__user_define_t");
    set_init(pt_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    it_iter = _set_find(pt_set, &elem);
    assert_true(((_test__set_find__set_find_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    set_destroy(pt_set);
}

void test__set_find__set_find_varg__user_define_not_find(void** state)
{
    set_t* pt_set =  _create_set("_test__set_find__set_find_varg__user_define_t");
    set_iterator_t it_iter;
    _test__set_find__set_find_varg__user_define_t elem;
    int i = 0;

    set_init(pt_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 78;
    it_iter = _set_find(pt_set, &elem);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));

    set_destroy(pt_set);
}

/*
 * test _set_count and _set_count_varg
 */
UT_CASE_DEFINATION(_set_count__set_count_varg)
void test__set_count__set_count_varg__null_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_set_count(NULL, elem));
}

void test__set_count__set_count_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init(pt_set);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_count(pt_set, elem));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_count(pt_set, elem));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__c_builtin_0(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 1222;
    assert_true(_set_count(pt_set, elem) == 0);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__c_builtin_1(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem;
    int i;

    set_init(pt_set);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 2;
    assert_true(_set_count(pt_set, elem) == 1);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__c_builtin_n(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem;
    int i;

    set_init(pt_set);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
        set_insert(pt_set, i);
        set_insert(pt_set, i);
    }

    elem = 2;
    assert_true(_set_count(pt_set, elem) == 1);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__cstr_0(void** state)
{
    set_t* pt_set = _create_set("char*");

    set_init(pt_set);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    assert_true(_set_count(pt_set, "uuuu") == 0);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__cstr_1(void** state)
{
    set_t* pt_set = _create_set("char*");

    set_init(pt_set);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    assert_true(_set_count(pt_set, "ggg") == 1);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__cstr_n(void** state)
{
    set_t* pt_set = _create_set("char*");

    set_init(pt_set);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    assert_true(_set_count(pt_set, "ggg") == 1);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__libcstl_builtin_0(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    set_init(pt_set);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_set_count(pt_set, plist) == 0);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_count__set_count_varg__libcstl_builtin_1(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    set_init(pt_set);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_set_count(pt_set, plist) == 1);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_count__set_count_varg__libcstl_builtin_n(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    set_init(pt_set);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
        set_insert(pt_set, plist);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_set_count(pt_set, plist) == 1);

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_count__set_count_varg__user_define
{
    int n_elem;
}_test__set_count__set_count_varg__user_define_t;
void test__set_count__set_count_varg__user_define_0(void** state)
{
    set_t* pt_set = NULL;
    _test__set_count__set_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_count__set_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_count__set_count_varg__user_define_t");
    set_init(pt_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 88;
    assert_true(_set_count(pt_set, &elem) == 0);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__user_define_1(void** state)
{
    set_t* pt_set =  _create_set("_test__set_count__set_count_varg__user_define_t");
    _test__set_count__set_count_varg__user_define_t elem;
    int i = 0;

    set_init(pt_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_set_count(pt_set, &elem) == 1);

    set_destroy(pt_set);
}

void test__set_count__set_count_varg__user_define_n(void** state)
{
    set_t* pt_set =  _create_set("_test__set_count__set_count_varg__user_define_t");
    _test__set_count__set_count_varg__user_define_t elem;
    int i = 0;

    set_init(pt_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_set_count(pt_set, &elem) == 1);

    set_destroy(pt_set);
}

/*
 * test _set_lower_bound and _set_lower_bound_varg
 */
UT_CASE_DEFINATION(_set_lower_bound__set_lower_bound_varg)
void test__set_lower_bound__set_lower_bound_varg__null_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_set_lower_bound(NULL, elem));
}

void test__set_lower_bound__set_lower_bound_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init(pt_set);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_lower_bound(pt_set, elem));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_lower_bound(pt_set, elem));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_lower_bound__set_lower_bound_varg__c_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int elem;
    int i;

    set_init(pt_set);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 2;
    it_iter = _set_lower_bound(pt_set, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    set_destroy(pt_set);
}

void test__set_lower_bound__set_lower_bound_varg__c_builtin_greater(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int elem;
    int i;

    set_init(pt_set);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = -8;
    it_iter = _set_lower_bound(pt_set, elem);
    assert_true(iterator_equal(it_iter, set_begin(pt_set)));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    set_destroy(pt_set);
}

void test__set_lower_bound__set_lower_bound_varg__cstr_lower_equal(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init(pt_set);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    it_iter = _set_lower_bound(pt_set, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "ggg") == 0);

    set_destroy(pt_set);
}

void test__set_lower_bound__set_lower_bound_varg__cstr_greater(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init(pt_set);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    it_iter = _set_lower_bound(pt_set, "vvvv");
    assert_true(iterator_equal(it_iter, set_end(pt_set)));

    set_destroy(pt_set);
}

void test__set_lower_bound__set_lower_bound_varg__libcstl_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init(pt_set);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _set_lower_bound(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_lower_bound__set_lower_bound_varg__libcstl_builtin_greater(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init(pt_set);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _set_lower_bound(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_lower_bound__set_lower_bound_varg__user_define
{
    int n_elem;
}_test__set_lower_bound__set_lower_bound_varg__user_define_t;
void test__set_lower_bound__set_lower_bound_varg__user_define_equal(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter;
    _test__set_lower_bound__set_lower_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_lower_bound__set_lower_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_lower_bound__set_lower_bound_varg__user_define_t");
    set_init(pt_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    it_iter = _set_lower_bound(pt_set, &elem);
    assert_true(((_test__set_lower_bound__set_lower_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    set_destroy(pt_set);
}

void test__set_lower_bound__set_lower_bound_varg__user_define_greater(void** state)
{
    set_t* pt_set =  _create_set("_test__set_lower_bound__set_lower_bound_varg__user_define_t");
    set_iterator_t it_iter;
    _test__set_lower_bound__set_lower_bound_varg__user_define_t elem;
    int i = 0;

    set_init(pt_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 7;
    it_iter = _set_lower_bound(pt_set, &elem);
    assert_true(((_test__set_lower_bound__set_lower_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    set_destroy(pt_set);
}

/*
 * test _set_upper_bound and _set_upper_bound_varg
 */
UT_CASE_DEFINATION(_set_upper_bound__set_upper_bound_varg)
void test__set_upper_bound__set_upper_bound_varg__null_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_set_upper_bound(NULL, elem));
}

void test__set_upper_bound__set_upper_bound_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_upper_bound(pt_set, &elem));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_upper_bound(pt_set, &elem));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_upper_bound__set_upper_bound_varg__c_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 2;
    it_iter = _set_upper_bound(pt_set, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    set_destroy(pt_set);
}

void test__set_upper_bound__set_upper_bound_varg__c_builtin_greater(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = -8;
    it_iter = _set_upper_bound(pt_set, elem);
    assert_true(iterator_equal(it_iter, set_begin(pt_set)));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    set_destroy(pt_set);
}

void test__set_upper_bound__set_upper_bound_varg__cstr_upper_equal(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    it_iter = _set_upper_bound(pt_set, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "linux") == 0);

    set_destroy(pt_set);
}

void test__set_upper_bound__set_upper_bound_varg__cstr_greater(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    it_iter = _set_upper_bound(pt_set, "vvv");
    assert_true(iterator_equal(it_iter, set_end(pt_set)));

    set_destroy(pt_set);
}

void test__set_upper_bound__set_upper_bound_varg__libcstl_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _set_upper_bound(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 7);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_upper_bound__set_upper_bound_varg__libcstl_builtin_greater(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _set_upper_bound(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_upper_bound__set_upper_bound_varg__user_define
{
    int n_elem;
}_test__set_upper_bound__set_upper_bound_varg__user_define_t;
void test__set_upper_bound__set_upper_bound_varg__user_define_equal(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter;
    _test__set_upper_bound__set_upper_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_upper_bound__set_upper_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_upper_bound__set_upper_bound_varg__user_define_t");
    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    it_iter = _set_upper_bound(pt_set, &elem);
    assert_true(((_test__set_upper_bound__set_upper_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 9);

    set_destroy(pt_set);
}

void test__set_upper_bound__set_upper_bound_varg__user_define_greater(void** state)
{
    set_t* pt_set =  _create_set("_test__set_upper_bound__set_upper_bound_varg__user_define_t");
    set_iterator_t it_iter;
    _test__set_upper_bound__set_upper_bound_varg__user_define_t elem;
    int i = 0;

    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 7;
    it_iter = _set_upper_bound(pt_set, &elem);
    assert_true(((_test__set_upper_bound__set_upper_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    set_destroy(pt_set);
}

/*
 * test _set_equal_range and _set_equal_range_varg
 */
UT_CASE_DEFINATION(_set_equal_range__set_equal_range_varg)
void test__set_equal_range__set_equal_range_varg__null_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_set_equal_range(NULL, elem));
}

void test__set_equal_range__set_equal_range_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_equal_range(pt_set, elem));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_equal_range(pt_set, elem));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_equal_range__set_equal_range_varg__c_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("int");
    range_t r_range;
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 2;
    r_range = _set_equal_range(pt_set, elem);
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 2);
    assert_true(*(int*)iterator_get_pointer(r_range.it_end) == 3);

    set_destroy(pt_set);
}

void test__set_equal_range__set_equal_range_varg__c_builtin_greater(void** state)
{
    set_t* pt_set = _create_set("int");
    range_t r_range;
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = -8;
    r_range = _set_equal_range(pt_set, elem);
    assert_true(iterator_equal(r_range.it_begin, set_begin(pt_set)));
    assert_true(iterator_equal(r_range.it_end, set_begin(pt_set)));
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 0);

    set_destroy(pt_set);
}

void test__set_equal_range__set_equal_range_varg__cstr_upper_equal(void** state)
{
    set_t* pt_set = _create_set("char*");
    range_t r_range;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    r_range = _set_equal_range(pt_set, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_begin), "ggg") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_end), "linux") == 0);

    set_destroy(pt_set);
}

void test__set_equal_range__set_equal_range_varg__cstr_greater(void** state)
{
    set_t* pt_set = _create_set("char*");
    range_t r_range;

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    r_range = _set_equal_range(pt_set, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, set_end(pt_set)));
    assert_true(iterator_equal(r_range.it_end, set_end(pt_set)));

    set_destroy(pt_set);
}

void test__set_equal_range__set_equal_range_varg__libcstl_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _set_equal_range(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 7);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_equal_range__set_equal_range_varg__libcstl_builtin_greater(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _set_equal_range(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 6);

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_equal_range__set_equal_range_varg__user_define
{
    int n_elem;
}_test__set_equal_range__set_equal_range_varg__user_define_t;
void test__set_equal_range__set_equal_range_varg__user_define_equal(void** state)
{
    set_t* pt_set = NULL;
    range_t r_range;
    _test__set_equal_range__set_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_equal_range__set_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_equal_range__set_equal_range_varg__user_define_t");
    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    r_range = _set_equal_range(pt_set, &elem);
    assert_true(((_test__set_equal_range__set_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__set_equal_range__set_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 9);

    set_destroy(pt_set);
}

void test__set_equal_range__set_equal_range_varg__user_define_greater(void** state)
{
    set_t* pt_set =  _create_set("_test__set_equal_range__set_equal_range_varg__user_define_t");
    range_t r_range;
    _test__set_equal_range__set_equal_range_varg__user_define_t elem;
    int i = 0;

    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 7;
    r_range = _set_equal_range(pt_set, &elem);
    assert_true(((_test__set_equal_range__set_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__set_equal_range__set_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 8);

    set_destroy(pt_set);
}

/*
 * test _set_erase and _set_erase_varg
 */
UT_CASE_DEFINATION(_set_erase__set_erase_varg)
void test__set_erase__set_erase_varg__null_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_set_erase(NULL, elem));
}

void test__set_erase__set_erase_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_erase(pt_set, elem));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_erase(pt_set, elem));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__c_builtin_0(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 24;
    assert_true(_set_erase(pt_set, elem) == 0);
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__c_builtin_1(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
    }

    elem = 8;
    assert_true(_set_erase(pt_set, elem) == 1);
    assert_true(set_size(pt_set) == 9);
    assert_true(_set_count(pt_set, elem) == 0);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__c_builtin_n(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        set_insert(pt_set, i);
        set_insert(pt_set, i);
        set_insert(pt_set, i);
    }

    elem = 8;
    assert_true(_set_erase(pt_set, elem) == 1);
    assert_true(set_size(pt_set) == 9);
    assert_true(_set_count(pt_set, elem) == 0);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__cstr_0(void** state)
{
    set_t* pt_set = _create_set("char*");

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    assert_true(_set_erase(pt_set, "gggppgg") == 0);
    assert_true(set_size(pt_set) == 5);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__cstr_1(void** state)
{
    set_t* pt_set = _create_set("char*");

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    assert_true(_set_erase(pt_set, "ggg") == 1);
    assert_true(set_size(pt_set) == 4);
    assert_true(_set_count(pt_set, "ggg") == 0);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__cstr_n(void** state)
{
    set_t* pt_set = _create_set("char*");

    set_init_ex(pt_set, NULL);
    set_insert(pt_set, "aaa");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "ggg");
    set_insert(pt_set, "nghl");
    set_insert(pt_set, "asery");
    set_insert(pt_set, "linux");

    assert_true(_set_erase(pt_set, "ggg") == 1);
    assert_true(set_size(pt_set) == 4);
    assert_true(_set_count(pt_set, "ggg") == 0);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__libcstl_builtin_0(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_set_erase(pt_set, plist) == 0);
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_erase__set_erase_varg__libcstl_builtin_1(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_set_erase(pt_set, plist) == 1);
    assert_true(set_size(pt_set) == 9);
    assert_true(_set_count(pt_set, plist) == 0);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_erase__set_erase_varg__libcstl_builtin_n(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        set_insert(pt_set, plist);
        set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_set_erase(pt_set, plist) == 1);
    assert_true(set_size(pt_set) == 9);
    assert_true(_set_count(pt_set, plist) == 0);

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_erase__set_erase_varg__user_define
{
    int n_elem;
}_test__set_erase__set_erase_varg__user_define_t;
void test__set_erase__set_erase_varg__user_define_0(void** state)
{
    set_t* pt_set = NULL;
    _test__set_erase__set_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_erase__set_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_erase__set_erase_varg__user_define_t");
    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 86;
    assert_true(_set_erase(pt_set, &elem) == 0);
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__user_define_1(void** state)
{
    set_t* pt_set =  _create_set("_test__set_erase__set_erase_varg__user_define_t");
    _test__set_erase__set_erase_varg__user_define_t elem;
    int i = 0;

    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_set_erase(pt_set, &elem) == 1);
    assert_true(set_size(pt_set) == 9);
    assert_true(_set_count(pt_set, &elem) == 0);

    set_destroy(pt_set);
}

void test__set_erase__set_erase_varg__user_define_n(void** state)
{
    set_t* pt_set =  _create_set("_test__set_erase__set_erase_varg__user_define_t");
    _test__set_erase__set_erase_varg__user_define_t elem;
    int i = 0;

    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        set_insert(pt_set, &elem);
        set_insert(pt_set, &elem);
        set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_set_erase(pt_set, &elem) == 1);
    assert_true(set_size(pt_set) == 9);
    assert_true(_set_count(pt_set, &elem) == 0);

    set_destroy(pt_set);
}

/*
 * test _set_insert and _set_insert_varg
 */
UT_CASE_DEFINATION(_set_insert__set_insert_varg)
void test__set_insert_varg__null_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_set_insert(NULL, elem));
}

void test__set_insert_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    int elem = 9;
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_insert(pt_set, elem));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_insert(pt_set, elem));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_insert_varg__c_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        _set_insert(pt_set, i);
    }

    elem = 2;
    it_iter = _set_insert(pt_set, elem);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
}

void test__set_insert_varg__c_builtin_not_equal(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter;
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        _set_insert(pt_set, i);
    }

    elem = -8;
    it_iter = _set_insert(pt_set, elem);
    assert_true(*(int*)_set_iterator_get_pointer(it_iter) == -8);
    assert_true(set_size(pt_set) == 11);

    set_destroy(pt_set);
}

void test__set_insert_varg__cstr_equal(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init_ex(pt_set, NULL);
    _set_insert(pt_set, "aaa");
    _set_insert(pt_set, "ggg");
    _set_insert(pt_set, "nghl");
    _set_insert(pt_set, "asery");
    _set_insert(pt_set, "linux");

    it_iter = _set_insert(pt_set, "ggg");
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 5);

    set_destroy(pt_set);
}

void test__set_insert_varg__cstr_not_equal(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter;

    set_init_ex(pt_set, NULL);
    _set_insert(pt_set, "aaa");
    _set_insert(pt_set, "ggg");
    _set_insert(pt_set, "nghl");
    _set_insert(pt_set, "asery");
    _set_insert(pt_set, "linux");

    it_iter = _set_insert(pt_set, "vvvv");
    assert_true(strcmp((char*)_set_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(set_size(pt_set) == 6);

    set_destroy(pt_set);
}

void test__set_insert_varg__libcstl_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _set_insert(pt_set, plist);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_insert_varg__libcstl_builtin_not_equal(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _set_insert(pt_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _set_insert(pt_set, plist);
    assert_true(*(int*)list_front((list_t*)_set_iterator_get_pointer(it_iter)) == 5);
    assert_true(set_size(pt_set) == 11);

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_insert_varg__user_define
{
    int n_elem;
}_test__set_insert_varg__user_define_t;
void test__set_insert_varg__user_define_equal(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter;
    _test__set_insert_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_insert_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_insert_varg__user_define_t");
    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _set_insert(pt_set, &elem);
    }

    elem.n_elem = 8;
    it_iter = _set_insert(pt_set, &elem);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
}

void test__set_insert_varg__user_define_not_equal(void** state)
{
    set_t* pt_set =  _create_set("_test__set_insert_varg__user_define_t");
    set_iterator_t it_iter;
    _test__set_insert_varg__user_define_t elem;
    int i = 0;

    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _set_insert(pt_set, &elem);
    }

    elem.n_elem = 7;
    it_iter = _set_insert(pt_set, &elem);
    assert_true(((_test__set_insert_varg__user_define_t*)_set_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(set_size(pt_set) == 11);

    set_destroy(pt_set);
}

/*
 * test _set_insert_hint and _set_insert_hint_varg
 */
UT_CASE_DEFINATION(_set_insert_hint__set_insert_hint_varg)
void test__set_insert_hint_varg__null_set(void** state)
{
    int elem = 9;
    set_iterator_t it_hint;
    expect_assert_failure(_set_insert_hint(NULL, it_hint, elem));
}

void test__set_insert_hint_varg__non_inited(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_hint;
    int elem = 9;
    set_init_ex(pt_set, NULL);

#ifdef CSTL_SET_AVL_TREE
    pt_set->_t_tree._t_avlroot._un_height = 5;
    expect_assert_failure(_set_insert_hint(pt_set, it_hint, elem));
    pt_set->_t_tree._t_avlroot._un_height = 0;
#else
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_set_insert_hint(pt_set, it_hint, elem));
    pt_set->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    set_destroy(pt_set);
}

void test__set_insert_hint_varg__c_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter = create_set_iterator();
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        _set_insert_hint(pt_set, it_iter, i);
    }

    elem = 2;
    it_iter = _set_insert_hint(pt_set, it_iter, elem);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
}

void test__set_insert_hint_varg__c_builtin_not_equal(void** state)
{
    set_t* pt_set = _create_set("int");
    set_iterator_t it_iter = create_set_iterator();
    int elem;
    int i;

    set_init_ex(pt_set, NULL);
    for(i = 0; i < 10; ++i)
    {
        _set_insert_hint(pt_set, it_iter, i);
    }

    elem = -8;
    it_iter = _set_insert_hint(pt_set, it_iter, elem);
    assert_true(*(int*)_set_iterator_get_pointer(it_iter) == -8);
    assert_true(set_size(pt_set) == 11);

    set_destroy(pt_set);
}

void test__set_insert_hint_varg__cstr_equal(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter = create_set_iterator();

    set_init_ex(pt_set, NULL);
    _set_insert_hint(pt_set, it_iter, "aaa");
    _set_insert_hint(pt_set, it_iter, "ggg");
    _set_insert_hint(pt_set, it_iter, "nghl");
    _set_insert_hint(pt_set, it_iter, "asery");
    _set_insert_hint(pt_set, it_iter, "linux");

    it_iter = _set_insert_hint(pt_set, it_iter, "ggg");
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 5);

    set_destroy(pt_set);
}

void test__set_insert_hint_varg__cstr_not_equal(void** state)
{
    set_t* pt_set = _create_set("char*");
    set_iterator_t it_iter = create_set_iterator();

    set_init_ex(pt_set, NULL);
    _set_insert_hint(pt_set, it_iter, "aaa");
    _set_insert_hint(pt_set, it_iter, "ggg");
    _set_insert_hint(pt_set, it_iter, "nghl");
    _set_insert_hint(pt_set, it_iter, "asery");
    _set_insert_hint(pt_set, it_iter, "linux");

    it_iter = _set_insert_hint(pt_set, it_iter, "vvvv");
    assert_true(strcmp((char*)_set_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(set_size(pt_set) == 6);

    set_destroy(pt_set);
}

void test__set_insert_hint_varg__libcstl_builtin_equal(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter = create_set_iterator();
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _set_insert_hint(pt_set, it_iter, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _set_insert_hint(pt_set, it_iter, plist);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
    list_destroy(plist);
}

void test__set_insert_hint_varg__libcstl_builtin_not_equal(void** state)
{
    set_t* pt_set = _create_set("list_t<int>");
    set_iterator_t it_iter = create_set_iterator();
    list_t* plist = create_list(int);
    int i = 0;

    set_init_ex(pt_set, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _set_insert_hint(pt_set, it_iter, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _set_insert_hint(pt_set, it_iter, plist);
    assert_true(*(int*)list_front((list_t*)_set_iterator_get_pointer(it_iter)) == 5);
    assert_true(set_size(pt_set) == 11);

    set_destroy(pt_set);
    list_destroy(plist);
}

typedef struct _tag_test__set_insert_hint_varg__user_define
{
    int n_elem;
}_test__set_insert_hint_varg__user_define_t;
void test__set_insert_hint_varg__user_define_equal(void** state)
{
    set_t* pt_set = NULL;
    set_iterator_t it_iter = create_set_iterator();
    _test__set_insert_hint_varg__user_define_t elem;
    int i = 0;

    type_register(_test__set_insert_hint_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_set = _create_set("_test__set_insert_hint_varg__user_define_t");
    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _set_insert_hint(pt_set, it_iter, &elem);
    }

    elem.n_elem = 8;
    it_iter = _set_insert_hint(pt_set, it_iter, &elem);
    assert_true(iterator_equal(it_iter, set_end(pt_set)));
    assert_true(set_size(pt_set) == 10);

    set_destroy(pt_set);
}

void test__set_insert_hint_varg__user_define_not_equal(void** state)
{
    set_t* pt_set =  _create_set("_test__set_insert_hint_varg__user_define_t");
    set_iterator_t it_iter = create_set_iterator();
    _test__set_insert_hint_varg__user_define_t elem;
    int i = 0;

    set_init_ex(pt_set, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _set_insert_hint(pt_set, it_iter, &elem);
    }

    elem.n_elem = 7;
    it_iter = _set_insert_hint(pt_set, it_iter, &elem);
    assert_true(((_test__set_insert_hint_varg__user_define_t*)_set_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(set_size(pt_set) == 11);

    set_destroy(pt_set);
}

/*
 * test _set_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_set_init_elem_auxiliary)
void test__set_init_elem_auxiliary__null_set_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_set_init_elem_auxiliary(NULL, &elem));
}

void test__set_init_elem_auxiliary__null_elem(void** state)
{
    set_t* pset = create_set(int);

    expect_assert_failure(_set_init_elem_auxiliary(pset, NULL));

    set_destroy(pset);
}

void test__set_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    set_t* pset = create_set(int);
    set_init(pset);

    _set_init_elem_auxiliary(pset, &elem);
    assert_true(elem == 0);

    set_destroy(pset);
}

void test__set_init_elem_auxiliary__successfully_cstr(void** state)
{
    string_t elem;
    set_t* pset = create_set(char*);
    set_init_ex(pset, NULL);

    set_insert(pset, "abc");
    set_insert(pset, "def");
#ifdef CSTL_SET_AVL_TREE
    _set_init_elem_auxiliary(pset, &elem);
#else
    _set_init_elem_auxiliary(pset, &elem);
#endif
    assert_true(strcmp(string_c_str(&elem), "") == 0);

    _string_destroy_auxiliary(&elem);
    set_destroy(pset);
}

void test__set_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    set_t* pset = create_set(iterator_t);
    set_init_ex(pset, NULL);

    set_insert(pset, &it_iter);

    _set_init_elem_auxiliary(pset, (void*)iterator_get_pointer(set_begin(pset)));
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)iterator_get_pointer(set_begin(pset)), &it_iter, sizeof(iterator_t)) == 0);

    set_destroy(pset);
}

void test__set_init_elem_auxiliary__successfully_container(void** state)
{
    vector_t vec;
    set_t* pset = create_set(vector_t<int>);

    _set_init_elem_auxiliary(pset, &vec);
    assert_true(_vector_is_inited(&vec));

    set_destroy(pset);
}

typedef struct _tag_test__set_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__set_init_elem_auxiliary__successfully_user_defined_t;

void test__set_init_elem_auxiliary__successfully_user_defined(void** state)
{
    _test__set_init_elem_auxiliary__successfully_user_defined_t t_user;
    set_t* pset = NULL;

    type_register(_test__set_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pset = create_set(_test__set_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _set_init_elem_auxiliary(pset, &t_user);
    assert_true(t_user.n_elem == 0);

    set_destroy(pset);
}

