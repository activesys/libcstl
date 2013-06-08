#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cmap.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_list_aux.h"
#include "cstl_multimap_aux.h"

#include "ut_def.h"
#include "ut_cstl_multimap_private.h"

UT_SUIT_DEFINATION(cstl_multimap_private, _create_multimap)

/*
 * test _create_multimap
 */
UT_CASE_DEFINATION(_create_multimap)
void test__create_multimap__null_typename(void** state)
{
    expect_assert_failure(_create_multimap(NULL));
}

void test__create_multimap__c_builtin(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, double");
    assert_true(pt_multimap != NULL);

    multimap_destroy(pt_multimap);
}

void test__create_multimap__cstr(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    assert_true(pt_multimap != NULL);

    multimap_destroy(pt_multimap);
}

void test__create_multimap__libcstl_builtin(void** state)
{
    multimap_t* pt_multimap = _create_multimap("vector_t<int>, list_t<double>");
    assert_true(pt_multimap != NULL);

    multimap_destroy(pt_multimap);
}

typedef struct _test_test__create_multimap__user_define
{
    int n_elem;
}_test__create_multimap__user_define_t;

void test__create_multimap__user_define(void** state)
{
    multimap_t* pt_multimap = NULL;

    type_register(_test__create_multimap__user_define_t, NULL, NULL, NULL, NULL);
    pt_multimap = _create_multimap("_test__create_multimap__user_define_t, _test__create_multimap__user_define_t");
    assert_true(pt_multimap != NULL);

    multimap_destroy(pt_multimap);
}

void test__create_multimap__unregister(void** state)
{
    multimap_t* pt_multimap = _create_multimap("test__create_multimap__unregister_t, test__create_multimap__unregister_t");
    assert_true(pt_multimap == NULL);
}

/*
 * test _create_multimap_auxiliary
 */
UT_CASE_DEFINATION(_create_multimap_auxiliary)
void test__create_multimap_auxiliary__null_multimap(void** state)
{
    expect_assert_failure(_create_multimap_auxiliary(NULL, "int, int"));
}

void test__create_multimap_auxiliary__null_typename(void** state)
{
    multimap_t t_multimap;
    expect_assert_failure(_create_multimap_auxiliary(&t_multimap, NULL));
}

void test__create_multimap_auxiliary__unregistered(void** state)
{
    multimap_t* pt_multimap = malloc(sizeof(multimap_t));
    assert_false(_create_multimap_auxiliary(pt_multimap, "_test__create_multimap_auxiliary__unregistered_t, _test__create_multimap_auxiliary__unregistered_t"));

    free(pt_multimap);
}

void test__create_multimap_auxiliary__c_builtin(void** state)
{
    multimap_t* pt_multimap = malloc(sizeof(multimap_t));
    assert_true(_create_multimap_auxiliary(pt_multimap, "int, int"));
    assert_true(pt_multimap != NULL);
    assert_true(_pair_is_created(&pt_multimap->_pair_temp));
    assert_true(pt_multimap->_bfun_keycompare == NULL);
    assert_true(pt_multimap->_bfun_valuecompare == NULL);

    multimap_destroy(pt_multimap);
}

void test__create_multimap_auxiliary__cstr(void** state)
{
    multimap_t* pt_multimap = malloc(sizeof(multimap_t));
    assert_true(_create_multimap_auxiliary(pt_multimap, "char*, char*"));
    assert_true(pt_multimap != NULL);
    assert_true(_pair_is_created(&pt_multimap->_pair_temp));
    assert_true(pt_multimap->_bfun_keycompare == NULL);
    assert_true(pt_multimap->_bfun_valuecompare == NULL);

    multimap_destroy(pt_multimap);
}

void test__create_multimap_auxiliary__libcstl_builtin(void** state)
{
    multimap_t* pt_multimap = malloc(sizeof(multimap_t));
    assert_true(_create_multimap_auxiliary(pt_multimap, "vector_t<int>, list_t<int>"));
    assert_true(pt_multimap != NULL);
    assert_true(_pair_is_created(&pt_multimap->_pair_temp));
    assert_true(pt_multimap->_bfun_keycompare == NULL);
    assert_true(pt_multimap->_bfun_valuecompare == NULL);

    multimap_destroy(pt_multimap);
}

typedef struct _tag_test__create_multimap_auxiliary__user_define
{
    int n_elem;
}_test__create_multimap_auxiliary__user_define_t;

void test__create_multimap_auxiliary__user_define(void** state)
{
    multimap_t* pt_multimap = NULL;

    type_register(_test__create_multimap_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = malloc(sizeof(multimap_t));
    assert_true(_create_multimap_auxiliary(pt_multimap, "_test__create_multimap_auxiliary__user_define_t, _test__create_multimap_auxiliary__user_define_t"));
    assert_true(pt_multimap != NULL);
    assert_true(_pair_is_created(&pt_multimap->_pair_temp));
    assert_true(pt_multimap->_bfun_keycompare == NULL);
    assert_true(pt_multimap->_bfun_valuecompare == NULL);

    multimap_destroy(pt_multimap);
}

/*
 * test _multimap_destroy_auxiliary
 */
UT_CASE_DEFINATION(_multimap_destroy_auxiliary)
void test__multimap_destroy_auxiliary__null_multimap(void** state)
{
    expect_assert_failure(_multimap_destroy_auxiliary(NULL));
}

void test__multimap_destroy_auxiliary__non_created(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_destroy_auxiliary(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_destroy_auxiliary(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_destroy_auxiliary__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    multimap_init(pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_destroy_auxiliary(pt_multimap));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_destroy_auxiliary(pt_multimap));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_destroy_auxiliary__empty(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    multimap_init(pt_multimap);

    _multimap_destroy_auxiliary(pt_multimap);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(pt_multimap->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_multimap->_t_tree._t_avlroot._pt_left == &pt_multimap->_t_tree._t_avlroot);
    assert_true(pt_multimap->_t_tree._t_avlroot._pt_right == &pt_multimap->_t_tree._t_avlroot);
#else
    assert_true(pt_multimap->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_multimap->_t_tree._t_rbroot._pt_left == &pt_multimap->_t_tree._t_rbroot);
    assert_true(pt_multimap->_t_tree._t_rbroot._pt_right == &pt_multimap->_t_tree._t_rbroot);
#endif
    assert_true(pt_multimap->_t_tree._t_nodecount == 0);
    assert_true(pt_multimap->_t_tree._t_compare == NULL);
    assert_true(pt_multimap->_pair_temp._pv_first == NULL);
    assert_true(pt_multimap->_pair_temp._pv_second == NULL);
    assert_true(pt_multimap->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_multimap->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_multimap->_bfun_keycompare == NULL);
    assert_true(pt_multimap->_bfun_valuecompare == NULL);
    free(pt_multimap);
}

void test__multimap_destroy_auxiliary__non_empty(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);

    pair_init_elem(pt_pair, 19, 30);
    multimap_init(pt_multimap);
    multimap_insert(pt_multimap, pt_pair);

    _multimap_destroy_auxiliary(pt_multimap);
#ifdef CSTL_MULTIMAP_AVL_TREE
    assert_true(pt_multimap->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_multimap->_t_tree._t_avlroot._pt_left == &pt_multimap->_t_tree._t_avlroot);
    assert_true(pt_multimap->_t_tree._t_avlroot._pt_right == &pt_multimap->_t_tree._t_avlroot);
#else
    assert_true(pt_multimap->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_multimap->_t_tree._t_rbroot._pt_left == &pt_multimap->_t_tree._t_rbroot);
    assert_true(pt_multimap->_t_tree._t_rbroot._pt_right == &pt_multimap->_t_tree._t_rbroot);
#endif
    assert_true(pt_multimap->_t_tree._t_nodecount == 0);
    assert_true(pt_multimap->_t_tree._t_compare == NULL);
    assert_true(pt_multimap->_pair_temp._pv_first == NULL);
    assert_true(pt_multimap->_pair_temp._pv_second == NULL);
    assert_true(pt_multimap->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_multimap->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_multimap->_bfun_keycompare == NULL);
    assert_true(pt_multimap->_bfun_valuecompare == NULL);
    free(pt_multimap);

    pair_destroy(pt_pair);
}

/*
 * test _multimap_find and _multimap_find_varg
 */
UT_CASE_DEFINATION(_multimap_find__multimap_find_varg)
void test__multimap_find__multimap_find_varg__null_multimap(void** state)
{
    expect_assert_failure(_multimap_find(NULL, 9));
}

void test__multimap_find__multimap_find_varg__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    multimap_init(pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_find(pt_multimap, 9));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_find(pt_multimap, 9));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_find__multimap_find_varg__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    void* pv_tmp = NULL;

    multimap_init(pt_multimap);
    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_multimap_find(pt_multimap, 9));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test__multimap_find__multimap_find_varg__c_builtin_find(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem;
    int i;

    pair_init(pt_pair);
    multimap_init(pt_multimap);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+8);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 2;
    it_iter = _multimap_find(pt_multimap, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    assert_true(*(int*)pair_second((pair_t*)iterator_get_pointer(it_iter)) == 10);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_find__multimap_find_varg__c_builtin_not_find(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    multimap_init(pt_multimap);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+5);
        multimap_insert(pt_multimap, pt_pair);
    }

    it_iter = _multimap_find(pt_multimap, 42);
    assert_true(iterator_equal(it_iter, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_find__multimap_find_varg__cstr_find(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;

    pair_init(pt_pair);
    multimap_init(pt_multimap);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = multimap_find(pt_multimap, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)iterator_get_pointer(it_iter)), "fff") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_find__multimap_find_varg__cstr_not_find(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;

    pair_init(pt_pair);
    multimap_init(pt_multimap);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = _multimap_find(pt_multimap, "vvvvv");
    assert_true(iterator_equal(it_iter, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_find__multimap_find_varg__libcstl_builtin_find(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    multimap_iterator_t it_iter;
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multimap_find(pt_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);
    assert_true(*(int*)vector_front((vector_t*)pair_second((pair_t*)iterator_get_pointer(it_iter))) == 6);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__multimap_find__multimap_find_varg__libcstl_builtin_not_find(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    multimap_iterator_t it_iter;
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _multimap_find(pt_multimap, plist);
    assert_true(iterator_equal(it_iter, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__multimap_find__multimap_find_varg__user_define
{
    int n_elem;
}_test__multimap_find__multimap_find_varg__user_define_t;
void test__multimap_find__multimap_find_varg__user_define_find(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test__multimap_find__multimap_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multimap_find__multimap_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = _create_multimap("_test__multimap_find__multimap_find_varg__user_define_t, _test__multimap_find__multimap_find_varg__user_define_t");
    pt_pair = create_pair(_test__multimap_find__multimap_find_varg__user_define_t, _test__multimap_find__multimap_find_varg__user_define_t);
    multimap_init(pt_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _multimap_find(pt_multimap, &elem);
    assert_true(((_test__multimap_find__multimap_find_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);
    assert_true(((_test__multimap_find__multimap_find_varg__user_define_t*)pair_second((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_find__multimap_find_varg__user_define_not_find(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_find__multimap_find_varg__user_define_t, _test__multimap_find__multimap_find_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_find__multimap_find_varg__user_define_t, _test__multimap_find__multimap_find_varg__user_define_t);
    multimap_iterator_t it_iter;
    _test__multimap_find__multimap_find_varg__user_define_t elem;
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 78;
    it_iter = _multimap_find(pt_multimap, &elem);
    assert_true(iterator_equal(it_iter, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_count and _multimap_count_varg
 */
UT_CASE_DEFINATION(_multimap_count__multimap_count_varg)
void test__multimap_count__multimap_count_varg__null_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_multimap_count(NULL, elem));
}

void test__multimap_count__multimap_count_varg__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    int elem = 9;
    multimap_init(pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_count(pt_multimap, elem));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_count(pt_multimap, elem));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_count__multimap_count_varg__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    void* pv_tmp = NULL;
    int elem = 9;
    multimap_init(pt_multimap);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_multimap_count(pt_multimap, elem));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test__multimap_count__multimap_count_varg__c_builtin_0(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 1222;
    assert_true(_multimap_count(pt_multimap, elem) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__c_builtin_1(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 2;
    assert_true(_multimap_count(pt_multimap, elem) == 1);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__c_builtin_n(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 2;
    assert_true(_multimap_count(pt_multimap, elem) == 2);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__cstr_0(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    assert_true(_multimap_count(pt_multimap, "uuuu") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__cstr_1(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    assert_true(_multimap_count(pt_multimap, "ggg") == 1);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__cstr_n(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    multimap_insert(pt_multimap, pt_pair);
    multimap_insert(pt_multimap, pt_pair);
    multimap_insert(pt_multimap, pt_pair);
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    assert_true(_multimap_count(pt_multimap, "ggg") == 4);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__libcstl_builtin_0(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_multimap_count(pt_multimap, plist) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__multimap_count__multimap_count_varg__libcstl_builtin_1(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multimap_count(pt_multimap, plist) == 1);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__multimap_count__multimap_count_varg__libcstl_builtin_n(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multimap_count(pt_multimap, plist) == 4);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__multimap_count__multimap_count_varg__user_define
{
    int n_elem;
}_test__multimap_count__multimap_count_varg__user_define_t;
void test__multimap_count__multimap_count_varg__user_define_0(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    _test__multimap_count__multimap_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multimap_count__multimap_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = _create_multimap("_test__multimap_count__multimap_count_varg__user_define_t, _test__multimap_count__multimap_count_varg__user_define_t");
    pt_pair = create_pair(_test__multimap_count__multimap_count_varg__user_define_t, _test__multimap_count__multimap_count_varg__user_define_t);
    multimap_init(pt_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 88;
    assert_true(_multimap_count(pt_multimap, &elem) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__user_define_1(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_count__multimap_count_varg__user_define_t, _test__multimap_count__multimap_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_count__multimap_count_varg__user_define_t, _test__multimap_count__multimap_count_varg__user_define_t);
    _test__multimap_count__multimap_count_varg__user_define_t elem;
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_multimap_count(pt_multimap, &elem) == 1);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_count__multimap_count_varg__user_define_n(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_count__multimap_count_varg__user_define_t, _test__multimap_count__multimap_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_count__multimap_count_varg__user_define_t, _test__multimap_count__multimap_count_varg__user_define_t);
    _test__multimap_count__multimap_count_varg__user_define_t elem;
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_multimap_count(pt_multimap, &elem) == 4);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_lower_bound and _multimap_lower_bound_varg
 */
UT_CASE_DEFINATION(_multimap_lower_bound__multimap_lower_bound_varg)
void test__multimap_lower_bound__multimap_lower_bound_varg__null_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_multimap_lower_bound(NULL, elem));
}

void test__multimap_lower_bound__multimap_lower_bound_varg__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    int elem = 9;
    multimap_init(pt_multimap);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_lower_bound(pt_multimap, elem));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_lower_bound(pt_multimap, elem));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init(pt_multimap);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_multimap_lower_bound(pt_multimap, 111));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__c_builtin_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem;
    int i;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 2;
    it_iter = _multimap_lower_bound(pt_multimap, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__c_builtin_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem;
    int i;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = -8;
    it_iter = _multimap_lower_bound(pt_multimap, elem);
    assert_true(iterator_equal(it_iter, multimap_begin(pt_multimap)));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__cstr_lower_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fffff");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yrersa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = _multimap_lower_bound(pt_multimap, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__cstr_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;

    multimap_init(pt_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fffff");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yrersa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = _multimap_lower_bound(pt_multimap, "vvvv");
    assert_true(iterator_equal(it_iter, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__libcstl_builtin_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init(pt_multimap);
    list_init(plist);
    vector_init(pvec);
    pair_init(pt_pair);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multimap_lower_bound(pt_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__libcstl_builtin_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init(pt_multimap);
    list_init(plist);
    vector_init(pvec);
    pair_init(pt_pair);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i * 2);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _multimap_lower_bound(pt_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__multimap_lower_bound__multimap_lower_bound_varg__user_define
{
    int n_elem;
}_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t;
void test__multimap_lower_bound__multimap_lower_bound_varg__user_define_equal(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = _create_multimap("_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t, _test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t");
    pt_pair = create_pair(_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t, _test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t);
    pair_init(pt_pair);
    multimap_init(pt_multimap);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _multimap_lower_bound(pt_multimap, &elem);
    assert_true(((_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_lower_bound__multimap_lower_bound_varg__user_define_greater(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t, _test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t, _test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t);
    multimap_iterator_t it_iter;
    _test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t elem;
    int i = 0;

    multimap_init(pt_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 7;
    it_iter = _multimap_lower_bound(pt_multimap, &elem);
    assert_true(((_test__multimap_lower_bound__multimap_lower_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_upper_bound and _multimap_upper_bound_varg
 */
UT_CASE_DEFINATION(_multimap_upper_bound__multimap_upper_bound_varg)
void test__multimap_upper_bound__multimap_upper_bound_varg__null_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_multimap_upper_bound(NULL, elem));
}

void test__multimap_upper_bound__multimap_upper_bound_varg__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    int elem = 9;
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_upper_bound(pt_multimap, &elem));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_upper_bound(pt_multimap, &elem));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init(pt_multimap);

    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_multimap_upper_bound(pt_multimap, 3));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__c_builtin_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 2;
    it_iter = _multimap_upper_bound(pt_multimap, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 3);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__c_builtin_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    multimap_iterator_t it_iter;
    int elem;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = -8;
    it_iter = _multimap_upper_bound(pt_multimap, elem);
    assert_true(iterator_equal(it_iter, multimap_begin(pt_multimap)));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__cstr_upper_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ddddd");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = _multimap_upper_bound(pt_multimap, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "linux") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__cstr_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_iterator_t it_iter;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ddddd");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    it_iter = _multimap_upper_bound(pt_multimap, "vvv");
    assert_true(iterator_equal(it_iter, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__libcstl_builtin_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    list_init(plist);
    pair_init(pt_pair);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _multimap_upper_bound(pt_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 7);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__libcstl_builtin_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    multimap_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    list_init(plist);
    pair_init(pt_pair);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _multimap_upper_bound(pt_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__multimap_upper_bound__multimap_upper_bound_varg__user_define
{
    int n_elem;
}_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t;
void test__multimap_upper_bound__multimap_upper_bound_varg__user_define_equal(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    multimap_iterator_t it_iter;
    _test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = _create_multimap("_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t, _test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t");
    pt_pair = create_pair(_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t, _test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t);
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _multimap_upper_bound(pt_multimap, &elem);
    assert_true(((_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 9);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_upper_bound__multimap_upper_bound_varg__user_define_greater(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t, _test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t, _test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t);
    multimap_iterator_t it_iter;
    _test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t elem;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 7;
    it_iter = _multimap_upper_bound(pt_multimap, &elem);
    assert_true(((_test__multimap_upper_bound__multimap_upper_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_equal_range and _multimap_equal_range_varg
 */
UT_CASE_DEFINATION(_multimap_equal_range__multimap_equal_range_varg)
void test__multimap_equal_range__multimap_equal_range_varg__null_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_multimap_equal_range(NULL, elem));
}

void test__multimap_equal_range__multimap_equal_range_varg__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    int elem = 9;
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_equal_range(pt_multimap, elem));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_equal_range(pt_multimap, elem));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_equal_range__multimap_equal_range_varg__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;
    multimap_init(pt_multimap);

    pv_tmp = pt_multimap->_pair_temp._pv_second;
    pt_multimap->_pair_temp._pv_second = NULL;
    expect_assert_failure(_multimap_equal_range(pt_multimap, 3));
    pt_multimap->_pair_temp._pv_second = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test__multimap_equal_range__multimap_equal_range_varg__c_builtin_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 2;
    r_range = _multimap_equal_range(pt_multimap, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)) == 2);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)) == 3);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_equal_range__multimap_equal_range_varg__c_builtin_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int,int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = -8;
    r_range = _multimap_equal_range(pt_multimap, elem);
    assert_true(iterator_equal(r_range.it_begin, multimap_begin(pt_multimap)));
    assert_true(iterator_equal(r_range.it_end, multimap_begin(pt_multimap)));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_equal_range__multimap_equal_range_varg__cstr_upper_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    r_range = _multimap_equal_range(pt_multimap, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)), "ggg") == 0);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)), "linux") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_equal_range__multimap_equal_range_varg__cstr_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    r_range = _multimap_equal_range(pt_multimap, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, multimap_end(pt_multimap)));
    assert_true(iterator_equal(r_range.it_end, multimap_end(pt_multimap)));

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_equal_range__multimap_equal_range_varg__libcstl_builtin_equal(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _multimap_equal_range(pt_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin))) == 6);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end))) == 7);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__multimap_equal_range__multimap_equal_range_varg__libcstl_builtin_greater(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i * 2);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _multimap_equal_range(pt_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin))) == 6);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end))) == 6);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__multimap_equal_range__multimap_equal_range_varg__user_define
{
    int n_elem;
}_test__multimap_equal_range__multimap_equal_range_varg__user_define_t;
void test__multimap_equal_range__multimap_equal_range_varg__user_define_equal(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    range_t r_range;
    _test__multimap_equal_range__multimap_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multimap_equal_range__multimap_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = _create_multimap("_test__multimap_equal_range__multimap_equal_range_varg__user_define_t, _test__multimap_equal_range__multimap_equal_range_varg__user_define_t");
    pt_pair = create_pair(_test__multimap_equal_range__multimap_equal_range_varg__user_define_t, _test__multimap_equal_range__multimap_equal_range_varg__user_define_t);
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    r_range = _multimap_equal_range(pt_multimap, &elem);
    assert_true(((_test__multimap_equal_range__multimap_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)))->n_elem == 8);
    assert_true(((_test__multimap_equal_range__multimap_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)))->n_elem == 9);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_equal_range__multimap_equal_range_varg__user_define_greater(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_equal_range__multimap_equal_range_varg__user_define_t, _test__multimap_equal_range__multimap_equal_range_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_equal_range__multimap_equal_range_varg__user_define_t, _test__multimap_equal_range__multimap_equal_range_varg__user_define_t);
    range_t r_range;
    _test__multimap_equal_range__multimap_equal_range_varg__user_define_t elem;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 7;
    r_range = _multimap_equal_range(pt_multimap, &elem);
    assert_true(((_test__multimap_equal_range__multimap_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)))->n_elem == 8);
    assert_true(((_test__multimap_equal_range__multimap_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)))->n_elem == 8);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_erase and _multimap_erase_varg
 */
UT_CASE_DEFINATION(_multimap_erase__multimap_erase_varg)
void test__multimap_erase__multimap_erase_varg__null_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_multimap_erase(NULL, elem));
}

void test__multimap_erase__multimap_erase_varg__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int,int");
    int elem = 9;
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_erase(pt_multimap, elem));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_erase(pt_multimap, elem));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_erase__multimap_erase_varg__non_inited_pair(void** state)
{
    multimap_t* pt_multimap = create_multimap(int, int);
    void* pv_tmp = NULL;

    multimap_init(pt_multimap);
    pv_tmp = pt_multimap->_pair_temp._pv_first;
    pt_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_multimap_erase(pt_multimap, 4));
    pt_multimap->_pair_temp._pv_first = pv_tmp;

    multimap_destroy(pt_multimap);
}

void test__multimap_erase__multimap_erase_varg__c_builtin_0(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 24;
    assert_true(_multimap_erase(pt_multimap, elem) == 0);
    assert_true(multimap_size(pt_multimap) == 10);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__c_builtin_1(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 8;
    assert_true(_multimap_erase(pt_multimap, elem) == 1);
    assert_true(multimap_size(pt_multimap) == 9);
    assert_true(_multimap_count(pt_multimap, elem) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__c_builtin_n(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem = 8;
    assert_true(_multimap_erase(pt_multimap, elem) == 3);
    assert_true(multimap_size(pt_multimap) == 27);
    assert_true(_multimap_count(pt_multimap, elem) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__cstr_0(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    assert_true(_multimap_erase(pt_multimap, "gggppgg") == 0);
    assert_true(multimap_size(pt_multimap) == 5);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__cstr_1(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    assert_true(_multimap_erase(pt_multimap, "ggg") == 1);
    assert_true(multimap_size(pt_multimap) == 4);
    assert_true(_multimap_count(pt_multimap, "ggg") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__cstr_n(void** state)
{
    multimap_t* pt_multimap = _create_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    multimap_insert(pt_multimap, pt_pair);
    multimap_insert(pt_multimap, pt_pair);
    multimap_insert(pt_multimap, pt_pair);
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    multimap_insert(pt_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    multimap_insert(pt_multimap, pt_pair);

    assert_true(_multimap_erase(pt_multimap, "ggg") == 4);
    assert_true(multimap_size(pt_multimap) == 4);
    assert_true(_multimap_count(pt_multimap, "ggg") == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__libcstl_builtin_0(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_multimap_erase(pt_multimap, plist) == 0);
    assert_true(multimap_size(pt_multimap) == 10);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__multimap_erase__multimap_erase_varg__libcstl_builtin_1(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multimap_erase(pt_multimap, plist) == 1);
    assert_true(multimap_size(pt_multimap) == 9);
    assert_true(_multimap_count(pt_multimap, plist) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__multimap_erase__multimap_erase_varg__libcstl_builtin_n(void** state)
{
    multimap_t* pt_multimap = _create_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);
    list_init(plist);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_multimap_erase(pt_multimap, plist) == 3);
    assert_true(multimap_size(pt_multimap) == 27);
    assert_true(_multimap_count(pt_multimap, plist) == 0);

    multimap_destroy(pt_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__multimap_erase__multimap_erase_varg__user_define
{
    int n_elem;
}_test__multimap_erase__multimap_erase_varg__user_define_t;
void test__multimap_erase__multimap_erase_varg__user_define_0(void** state)
{
    multimap_t* pt_multimap = NULL;
    pair_t* pt_pair = NULL;
    _test__multimap_erase__multimap_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__multimap_erase__multimap_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_multimap = _create_multimap("_test__multimap_erase__multimap_erase_varg__user_define_t, _test__multimap_erase__multimap_erase_varg__user_define_t");
    pt_pair = create_pair(_test__multimap_erase__multimap_erase_varg__user_define_t, _test__multimap_erase__multimap_erase_varg__user_define_t);
    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 86;
    assert_true(_multimap_erase(pt_multimap, &elem) == 0);
    assert_true(multimap_size(pt_multimap) == 10);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__user_define_1(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_erase__multimap_erase_varg__user_define_t, _test__multimap_erase__multimap_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_erase__multimap_erase_varg__user_define_t, _test__multimap_erase__multimap_erase_varg__user_define_t);
    _test__multimap_erase__multimap_erase_varg__user_define_t elem;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_multimap_erase(pt_multimap, &elem) == 1);
    assert_true(multimap_size(pt_multimap) == 9);
    assert_true(_multimap_count(pt_multimap, &elem) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

void test__multimap_erase__multimap_erase_varg__user_define_n(void** state)
{
    multimap_t* pt_multimap =  _create_multimap("_test__multimap_erase__multimap_erase_varg__user_define_t, _test__multimap_erase__multimap_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__multimap_erase__multimap_erase_varg__user_define_t, _test__multimap_erase__multimap_erase_varg__user_define_t);
    _test__multimap_erase__multimap_erase_varg__user_define_t elem;
    int i = 0;

    multimap_init_ex(pt_multimap, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
        multimap_insert(pt_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_multimap_erase(pt_multimap, &elem) == 3);
    assert_true(multimap_size(pt_multimap) == 27);
    assert_true(_multimap_count(pt_multimap, &elem) == 0);

    multimap_destroy(pt_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _multimap_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_multimap_init_elem_auxiliary)
void test__multimap_init_elem_auxiliary__null_multimap_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_multimap_init_elem_auxiliary(NULL, &elem));
}

void test__multimap_init_elem_auxiliary__null_elem(void** state)
{
    multimap_t* pmultimap = create_multimap(int,int);

    expect_assert_failure(_multimap_init_elem_auxiliary(pmultimap, NULL));

    multimap_destroy(pmultimap);
}

void test__multimap_init_elem_auxiliary__non_inited(void** state)
{
    multimap_t* pt_multimap = _create_multimap("int,int");
    int elem = 9;
    multimap_init_ex(pt_multimap, NULL);

#ifdef CSTL_MULTIMAP_AVL_TREE
    pt_multimap->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_multimap_erase(pt_multimap, elem));
    pt_multimap->_t_tree._t_avlroot._un_height = 0;
#else
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_multimap_erase(pt_multimap, elem));
    pt_multimap->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    multimap_destroy(pt_multimap);
}

void test__multimap_init_elem_auxiliary__successfully_int(void** state)
{
    multimap_t* pmultimap = create_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    multimap_init(pmultimap);

    _multimap_init_elem_auxiliary(pmultimap, pt_pair);
    assert_true(*(int*)pair_first(pt_pair) == 0);
    assert_true(*(int*)pair_second(pt_pair) == 0);

    multimap_destroy(pmultimap);
    pair_destroy(pt_pair);
}

void test__multimap_init_elem_auxiliary__successfully_cstr(void** state)
{
    multimap_t* pmultimap = create_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    multimap_init_ex(pmultimap, NULL);
    /*pair_init(pt_pair);*/

    _multimap_init_elem_auxiliary(pmultimap, pt_pair);
    assert_true(strcmp((char*)pair_first(pt_pair), "") == 0);
    assert_true(strcmp((char*)pair_second(pt_pair), "") == 0);

    multimap_destroy(pmultimap);
    pair_destroy(pt_pair);
}

void test__multimap_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    multimap_t* pmultimap = create_multimap(iterator_t, iterator_t);
    pair_t* pt_pair = create_pair(iterator_t, iterator_t);
    multimap_init_ex(pmultimap, NULL);
    /*pair_init(pt_pair);*/

    _multimap_init_elem_auxiliary(pmultimap, pt_pair);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp(&it_iter, (iterator_t*)pair_first(pt_pair), sizeof(iterator_t)) == 0);
    assert_true(memcmp(&it_iter, (iterator_t*)pair_second(pt_pair), sizeof(iterator_t)) == 0);

    multimap_destroy(pmultimap);
    pair_destroy(pt_pair);
}

void test__multimap_init_elem_auxiliary__successfully_container(void** state)
{
    multimap_t* pmultimap = create_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);

    _multimap_init_elem_auxiliary(pmultimap, pt_pair);
    assert_true(_vector_is_inited((vector_t*)pair_first(pt_pair)));
    assert_true(_list_is_inited((list_t*)pair_second(pt_pair)));

    multimap_destroy(pmultimap);
    pair_destroy(pt_pair);
}

typedef struct _tag_test__multimap_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__multimap_init_elem_auxiliary__successfully_user_defined_t;

void test__multimap_init_elem_auxiliary__successfully_user_defined(void** state)
{
    multimap_t* pmultimap = NULL;
    pair_t* pt_pair = NULL;

    type_register(_test__multimap_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pmultimap = create_multimap(_test__multimap_init_elem_auxiliary__successfully_user_defined_t, _test__multimap_init_elem_auxiliary__successfully_user_defined_t);
    pt_pair = create_pair(_test__multimap_init_elem_auxiliary__successfully_user_defined_t, _test__multimap_init_elem_auxiliary__successfully_user_defined_t);

    _multimap_init_elem_auxiliary(pmultimap, pt_pair);
    assert_true(((_test__multimap_init_elem_auxiliary__successfully_user_defined_t*)pair_first(pt_pair))->n_elem == 0);
    assert_true(((_test__multimap_init_elem_auxiliary__successfully_user_defined_t*)pair_second(pt_pair))->n_elem == 0);

    multimap_destroy(pmultimap);
    pair_destroy(pt_pair);
}

