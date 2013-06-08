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
#include "cstl_map_aux.h"

#include "ut_def.h"
#include "ut_cstl_map_private.h"

UT_SUIT_DEFINATION(cstl_map_private, _create_map)

/*
 * test _create_map
 */
UT_CASE_DEFINATION(_create_map)
void test__create_map__null_typename(void** state)
{
    expect_assert_failure(_create_map(NULL));
}

void test__create_map__c_builtin(void** state)
{
    map_t* pt_map = _create_map("int, double");
    assert_true(pt_map != NULL);

    map_destroy(pt_map);
}

void test__create_map__cstr(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    assert_true(pt_map != NULL);

    map_destroy(pt_map);
}

void test__create_map__libcstl_builtin(void** state)
{
    map_t* pt_map = _create_map("vector_t<int>, list_t<double>");
    assert_true(pt_map != NULL);

    map_destroy(pt_map);
}

typedef struct _test_test__create_map__user_define
{
    int n_elem;
}_test__create_map__user_define_t;

void test__create_map__user_define(void** state)
{
    map_t* pt_map = NULL;

    type_register(_test__create_map__user_define_t, NULL, NULL, NULL, NULL);
    pt_map = _create_map("_test__create_map__user_define_t, _test__create_map__user_define_t");
    assert_true(pt_map != NULL);

    map_destroy(pt_map);
}

void test__create_map__unregister(void** state)
{
    map_t* pt_map = _create_map("test__create_map__unregister_t, test__create_map__unregister_t");
    assert_true(pt_map == NULL);
}

/*
 * test _create_map_auxiliary
 */
UT_CASE_DEFINATION(_create_map_auxiliary)
void test__create_map_auxiliary__null_map(void** state)
{
    expect_assert_failure(_create_map_auxiliary(NULL, "int, int"));
}

void test__create_map_auxiliary__null_typename(void** state)
{
    map_t t_map;
    expect_assert_failure(_create_map_auxiliary(&t_map, NULL));
}

void test__create_map_auxiliary__unregistered(void** state)
{
    map_t* pt_map = malloc(sizeof(map_t));
    assert_false(_create_map_auxiliary(pt_map, "_test__create_map_auxiliary__unregistered_t, _test__create_map_auxiliary__unregistered_t"));

    free(pt_map);
}

void test__create_map_auxiliary__c_builtin(void** state)
{
    map_t* pt_map = malloc(sizeof(map_t));
    assert_true(_create_map_auxiliary(pt_map, "int, int"));
    assert_true(pt_map != NULL);
    assert_true(_pair_is_created(&pt_map->_pair_temp));
    assert_true(pt_map->_bfun_keycompare == NULL);
    assert_true(pt_map->_bfun_valuecompare == NULL);

    map_destroy(pt_map);
}

void test__create_map_auxiliary__cstr(void** state)
{
    map_t* pt_map = malloc(sizeof(map_t));
    assert_true(_create_map_auxiliary(pt_map, "char*, char*"));
    assert_true(pt_map != NULL);
    assert_true(_pair_is_created(&pt_map->_pair_temp));
    assert_true(pt_map->_bfun_keycompare == NULL);
    assert_true(pt_map->_bfun_valuecompare == NULL);

    map_destroy(pt_map);
}

void test__create_map_auxiliary__libcstl_builtin(void** state)
{
    map_t* pt_map = malloc(sizeof(map_t));
    assert_true(_create_map_auxiliary(pt_map, "vector_t<int>, list_t<int>"));
    assert_true(pt_map != NULL);
    assert_true(_pair_is_created(&pt_map->_pair_temp));
    assert_true(pt_map->_bfun_keycompare == NULL);
    assert_true(pt_map->_bfun_valuecompare == NULL);

    map_destroy(pt_map);
}

typedef struct _tag_test__create_map_auxiliary__user_define
{
    int n_elem;
}_test__create_map_auxiliary__user_define_t;

void test__create_map_auxiliary__user_define(void** state)
{
    map_t* pt_map = NULL;

    type_register(_test__create_map_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = malloc(sizeof(map_t));
    assert_true(_create_map_auxiliary(pt_map, "_test__create_map_auxiliary__user_define_t, _test__create_map_auxiliary__user_define_t"));
    assert_true(pt_map != NULL);
    assert_true(_pair_is_created(&pt_map->_pair_temp));
    assert_true(pt_map->_bfun_keycompare == NULL);
    assert_true(pt_map->_bfun_valuecompare == NULL);

    map_destroy(pt_map);
}

/*
 * test _map_destroy_auxiliary
 */
UT_CASE_DEFINATION(_map_destroy_auxiliary)
void test__map_destroy_auxiliary__null_map(void** state)
{
    expect_assert_failure(_map_destroy_auxiliary(NULL));
}

void test__map_destroy_auxiliary__non_created(void** state)
{
    map_t* pt_map = _create_map("int, int");

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_destroy_auxiliary(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_destroy_auxiliary(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_destroy_auxiliary__non_inited(void** state)
{
    map_t* pt_map = _create_map("int, int");
    map_init(pt_map);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_destroy_auxiliary(pt_map));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_destroy_auxiliary(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_destroy_auxiliary__empty(void** state)
{
    map_t* pt_map = _create_map("int, int");
    map_init(pt_map);

    _map_destroy_auxiliary(pt_map);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(pt_map->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_map->_t_tree._t_avlroot._pt_left == &pt_map->_t_tree._t_avlroot);
    assert_true(pt_map->_t_tree._t_avlroot._pt_right == &pt_map->_t_tree._t_avlroot);
#else
    assert_true(pt_map->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_map->_t_tree._t_rbroot._pt_left == &pt_map->_t_tree._t_rbroot);
    assert_true(pt_map->_t_tree._t_rbroot._pt_right == &pt_map->_t_tree._t_rbroot);
#endif
    assert_true(pt_map->_t_tree._t_nodecount == 0);
    assert_true(pt_map->_t_tree._t_compare == NULL);
    assert_true(pt_map->_pair_temp._pv_first == NULL);
    assert_true(pt_map->_pair_temp._pv_second == NULL);
    assert_true(pt_map->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_map->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_map->_bfun_keycompare == NULL);
    assert_true(pt_map->_bfun_valuecompare == NULL);
    free(pt_map);
}

void test__map_destroy_auxiliary__non_empty(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);

    pair_init_elem(pt_pair, 19, 30);
    map_init(pt_map);
    map_insert(pt_map, pt_pair);

    _map_destroy_auxiliary(pt_map);
#ifdef CSTL_MAP_AVL_TREE
    assert_true(pt_map->_t_tree._t_avlroot._pt_parent == NULL);
    assert_true(pt_map->_t_tree._t_avlroot._pt_left == &pt_map->_t_tree._t_avlroot);
    assert_true(pt_map->_t_tree._t_avlroot._pt_right == &pt_map->_t_tree._t_avlroot);
#else
    assert_true(pt_map->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_map->_t_tree._t_rbroot._pt_left == &pt_map->_t_tree._t_rbroot);
    assert_true(pt_map->_t_tree._t_rbroot._pt_right == &pt_map->_t_tree._t_rbroot);
#endif
    assert_true(pt_map->_t_tree._t_nodecount == 0);
    assert_true(pt_map->_t_tree._t_compare == NULL);
    assert_true(pt_map->_pair_temp._pv_first == NULL);
    assert_true(pt_map->_pair_temp._pv_second == NULL);
    assert_true(pt_map->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_map->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_map->_bfun_keycompare == NULL);
    assert_true(pt_map->_bfun_valuecompare == NULL);
    free(pt_map);

    pair_destroy(pt_pair);
}

/*
 * test _map_find and _map_find_varg
 */
UT_CASE_DEFINATION(_map_find__map_find_varg)
void test__map_find__map_find_varg__null_map(void** state)
{
    expect_assert_failure(_map_find(NULL, 9));
}

void test__map_find__map_find_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int, int");
    map_init(pt_map);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_find(pt_map, 9));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_find(pt_map, 9));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_find__map_find_varg__non_inited_pair(void** state)
{
    map_t* pt_map = _create_map("int, int");
    void* pv_tmp = NULL;

    map_init(pt_map);
    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_map_find(pt_map, 9));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test__map_find__map_find_varg__c_builtin_find(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int elem;
    int i;

    pair_init(pt_pair);
    map_init(pt_map);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+8);
        map_insert(pt_map, pt_pair);
    }

    elem = 2;
    it_iter = _map_find(pt_map, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    assert_true(*(int*)pair_second((pair_t*)iterator_get_pointer(it_iter)) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_find__map_find_varg__c_builtin_not_find(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    map_init(pt_map);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+5);
        map_insert(pt_map, pt_pair);
    }

    it_iter = _map_find(pt_map, 42);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_find__map_find_varg__cstr_find(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;

    pair_init(pt_pair);
    map_init(pt_map);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    it_iter = map_find(pt_map, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)iterator_get_pointer(it_iter)), "fff") == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_find__map_find_varg__cstr_not_find(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;

    pair_init(pt_pair);
    map_init(pt_map);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    it_iter = _map_find(pt_map, "vvvvv");
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_find__map_find_varg__libcstl_builtin_find(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    map_iterator_t it_iter;
    int i = 0;

    map_init(pt_map);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _map_find(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);
    assert_true(*(int*)vector_front((vector_t*)pair_second((pair_t*)iterator_get_pointer(it_iter))) == 6);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__map_find__map_find_varg__libcstl_builtin_not_find(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    map_iterator_t it_iter;
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init(pt_map);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _map_find(pt_map, plist);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__map_find__map_find_varg__user_define
{
    int n_elem;
}_test__map_find__map_find_varg__user_define_t;
void test__map_find__map_find_varg__user_define_find(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    map_iterator_t it_iter;
    _test__map_find__map_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_find__map_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_find__map_find_varg__user_define_t, _test__map_find__map_find_varg__user_define_t");
    pt_pair = create_pair(_test__map_find__map_find_varg__user_define_t, _test__map_find__map_find_varg__user_define_t);
    map_init(pt_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _map_find(pt_map, &elem);
    assert_true(((_test__map_find__map_find_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);
    assert_true(((_test__map_find__map_find_varg__user_define_t*)pair_second((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_find__map_find_varg__user_define_not_find(void** state)
{
    map_t* pt_map =  _create_map("_test__map_find__map_find_varg__user_define_t, _test__map_find__map_find_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_find__map_find_varg__user_define_t, _test__map_find__map_find_varg__user_define_t);
    map_iterator_t it_iter;
    _test__map_find__map_find_varg__user_define_t elem;
    int i = 0;

    map_init(pt_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 78;
    it_iter = _map_find(pt_map, &elem);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test _map_count and _map_count_varg
 */
UT_CASE_DEFINATION(_map_count__map_count_varg)
void test__map_count__map_count_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_count(NULL, elem));
}

void test__map_count__map_count_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int, int");
    int elem = 9;
    map_init(pt_map);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_count(pt_map, elem));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_count(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_count__map_count_varg__non_inited_pair(void** state)
{
    map_t* pt_map = _create_map("int, int");
    void* pv_tmp = NULL;
    int elem = 9;
    map_init(pt_map);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_map_count(pt_map, elem));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test__map_count__map_count_varg__c_builtin_0(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    map_init(pt_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = 1222;
    assert_true(_map_count(pt_map, elem) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__c_builtin_1(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    map_init(pt_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = 2;
    assert_true(_map_count(pt_map, elem) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__c_builtin_n(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    map_init(pt_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
    }

    elem = 2;
    assert_true(_map_count(pt_map, elem) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__cstr_0(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    map_init(pt_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(_map_count(pt_map, "uuuu") == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__cstr_1(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    map_init(pt_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(_map_count(pt_map, "ggg") == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__cstr_n(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    map_init(pt_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    map_insert(pt_map, pt_pair);
    map_insert(pt_map, pt_pair);
    map_insert(pt_map, pt_pair);
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(_map_count(pt_map, "ggg") == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__libcstl_builtin_0(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init(pt_map);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_map_count(pt_map, plist) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__map_count__map_count_varg__libcstl_builtin_1(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init(pt_map);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_map_count(pt_map, plist) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__map_count__map_count_varg__libcstl_builtin_n(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init(pt_map);
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
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_map_count(pt_map, plist) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__map_count__map_count_varg__user_define
{
    int n_elem;
}_test__map_count__map_count_varg__user_define_t;
void test__map_count__map_count_varg__user_define_0(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    _test__map_count__map_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_count__map_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_count__map_count_varg__user_define_t, _test__map_count__map_count_varg__user_define_t");
    pt_pair = create_pair(_test__map_count__map_count_varg__user_define_t, _test__map_count__map_count_varg__user_define_t);
    map_init(pt_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 88;
    assert_true(_map_count(pt_map, &elem) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__user_define_1(void** state)
{
    map_t* pt_map =  _create_map("_test__map_count__map_count_varg__user_define_t, _test__map_count__map_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_count__map_count_varg__user_define_t, _test__map_count__map_count_varg__user_define_t);
    _test__map_count__map_count_varg__user_define_t elem;
    int i = 0;

    map_init(pt_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_map_count(pt_map, &elem) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_count__map_count_varg__user_define_n(void** state)
{
    map_t* pt_map =  _create_map("_test__map_count__map_count_varg__user_define_t, _test__map_count__map_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_count__map_count_varg__user_define_t, _test__map_count__map_count_varg__user_define_t);
    _test__map_count__map_count_varg__user_define_t elem;
    int i = 0;

    map_init(pt_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_map_count(pt_map, &elem) == 1);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test _map_lower_bound and _map_lower_bound_varg
 */
UT_CASE_DEFINATION(_map_lower_bound__map_lower_bound_varg)
void test__map_lower_bound__map_lower_bound_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_lower_bound(NULL, elem));
}

void test__map_lower_bound__map_lower_bound_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int, int");
    int elem = 9;
    map_init(pt_map);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_lower_bound(pt_map, elem));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_lower_bound(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init(pt_map);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_map_lower_bound(pt_map, 111));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init(pt_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = 2;
    it_iter = _map_lower_bound(pt_map, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_lower_bound__map_lower_bound_varg__c_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init(pt_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = -8;
    it_iter = _map_lower_bound(pt_map, elem);
    assert_true(iterator_equal(it_iter, map_begin(pt_map)));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_lower_bound__map_lower_bound_varg__cstr_lower_equal(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;

    map_init(pt_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "fffff");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yrersa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    it_iter = _map_lower_bound(pt_map, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_lower_bound__map_lower_bound_varg__cstr_greater(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;

    map_init(pt_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "fffff");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yrersa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    it_iter = _map_lower_bound(pt_map, "vvvv");
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_lower_bound__map_lower_bound_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init(pt_map);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _map_lower_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__map_lower_bound__map_lower_bound_varg__libcstl_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init(pt_map);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _map_lower_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__map_lower_bound__map_lower_bound_varg__user_define
{
    int n_elem;
}_test__map_lower_bound__map_lower_bound_varg__user_define_t;
void test__map_lower_bound__map_lower_bound_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    map_iterator_t it_iter;
    _test__map_lower_bound__map_lower_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_lower_bound__map_lower_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_lower_bound__map_lower_bound_varg__user_define_t, _test__map_lower_bound__map_lower_bound_varg__user_define_t");
    pt_pair = create_pair(_test__map_lower_bound__map_lower_bound_varg__user_define_t, _test__map_lower_bound__map_lower_bound_varg__user_define_t);
    pair_init(pt_pair);
    map_init(pt_map);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _map_lower_bound(pt_map, &elem);
    assert_true(((_test__map_lower_bound__map_lower_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_lower_bound__map_lower_bound_varg__user_define_greater(void** state)
{
    map_t* pt_map =  _create_map("_test__map_lower_bound__map_lower_bound_varg__user_define_t, _test__map_lower_bound__map_lower_bound_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_lower_bound__map_lower_bound_varg__user_define_t, _test__map_lower_bound__map_lower_bound_varg__user_define_t);
    map_iterator_t it_iter;
    _test__map_lower_bound__map_lower_bound_varg__user_define_t elem;
    int i = 0;

    map_init(pt_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 7;
    it_iter = _map_lower_bound(pt_map, &elem);
    assert_true(((_test__map_lower_bound__map_lower_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test _map_upper_bound and _map_upper_bound_varg
 */
UT_CASE_DEFINATION(_map_upper_bound__map_upper_bound_varg)
void test__map_upper_bound__map_upper_bound_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_upper_bound(NULL, elem));
}

void test__map_upper_bound__map_upper_bound_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int, int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_upper_bound(pt_map, &elem));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_upper_bound(pt_map, &elem));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;

    map_init(pt_map);

    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_map_upper_bound(pt_map, 3));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = 2;
    it_iter = _map_upper_bound(pt_map, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 3);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_upper_bound__map_upper_bound_varg__c_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = -8;
    it_iter = _map_upper_bound(pt_map, elem);
    assert_true(iterator_equal(it_iter, map_begin(pt_map)));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_upper_bound__map_upper_bound_varg__cstr_upper_equal(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ddddd");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    it_iter = _map_upper_bound(pt_map, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "linux") == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_upper_bound__map_upper_bound_varg__cstr_greater(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ddddd");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    it_iter = _map_upper_bound(pt_map, "vvv");
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_upper_bound__map_upper_bound_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _map_upper_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 7);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__map_upper_bound__map_upper_bound_varg__libcstl_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _map_upper_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__map_upper_bound__map_upper_bound_varg__user_define
{
    int n_elem;
}_test__map_upper_bound__map_upper_bound_varg__user_define_t;
void test__map_upper_bound__map_upper_bound_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    map_iterator_t it_iter;
    _test__map_upper_bound__map_upper_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_upper_bound__map_upper_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_upper_bound__map_upper_bound_varg__user_define_t, _test__map_upper_bound__map_upper_bound_varg__user_define_t");
    pt_pair = create_pair(_test__map_upper_bound__map_upper_bound_varg__user_define_t, _test__map_upper_bound__map_upper_bound_varg__user_define_t);
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _map_upper_bound(pt_map, &elem);
    assert_true(((_test__map_upper_bound__map_upper_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 9);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_upper_bound__map_upper_bound_varg__user_define_greater(void** state)
{
    map_t* pt_map =  _create_map("_test__map_upper_bound__map_upper_bound_varg__user_define_t, _test__map_upper_bound__map_upper_bound_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_upper_bound__map_upper_bound_varg__user_define_t, _test__map_upper_bound__map_upper_bound_varg__user_define_t);
    map_iterator_t it_iter;
    _test__map_upper_bound__map_upper_bound_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 7;
    it_iter = _map_upper_bound(pt_map, &elem);
    assert_true(((_test__map_upper_bound__map_upper_bound_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test _map_equal_range and _map_equal_range_varg
 */
UT_CASE_DEFINATION(_map_equal_range__map_equal_range_varg)
void test__map_equal_range__map_equal_range_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_equal_range(NULL, elem));
}

void test__map_equal_range__map_equal_range_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int, int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_equal_range(pt_map, elem));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_equal_range(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;
    map_init(pt_map);

    pv_tmp = pt_map->_pair_temp._pv_second;
    pt_map->_pair_temp._pv_second = NULL;
    expect_assert_failure(_map_equal_range(pt_map, 3));
    pt_map->_pair_temp._pv_second = pv_tmp;

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = 2;
    r_range = _map_equal_range(pt_map, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)) == 2);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)) == 3);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_equal_range__map_equal_range_varg__c_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("int,int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = -8;
    r_range = _map_equal_range(pt_map, elem);
    assert_true(iterator_equal(r_range.it_begin, map_begin(pt_map)));
    assert_true(iterator_equal(r_range.it_end, map_begin(pt_map)));
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_equal_range__map_equal_range_varg__cstr_upper_equal(void** state)
{
    map_t* pt_map = _create_map("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    r_range = _map_equal_range(pt_map, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)), "ggg") == 0);
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)), "linux") == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_equal_range__map_equal_range_varg__cstr_greater(void** state)
{
    map_t* pt_map = _create_map("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    r_range = _map_equal_range(pt_map, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, map_end(pt_map)));
    assert_true(iterator_equal(r_range.it_end, map_end(pt_map)));

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_equal_range__map_equal_range_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _map_equal_range(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin))) == 6);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end))) == 7);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__map_equal_range__map_equal_range_varg__libcstl_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _map_equal_range(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin))) == 6);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end))) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__map_equal_range__map_equal_range_varg__user_define
{
    int n_elem;
}_test__map_equal_range__map_equal_range_varg__user_define_t;
void test__map_equal_range__map_equal_range_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    range_t r_range;
    _test__map_equal_range__map_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_equal_range__map_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_equal_range__map_equal_range_varg__user_define_t, _test__map_equal_range__map_equal_range_varg__user_define_t");
    pt_pair = create_pair(_test__map_equal_range__map_equal_range_varg__user_define_t, _test__map_equal_range__map_equal_range_varg__user_define_t);
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    r_range = _map_equal_range(pt_map, &elem);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)))->n_elem == 8);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)))->n_elem == 9);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_equal_range__map_equal_range_varg__user_define_greater(void** state)
{
    map_t* pt_map =  _create_map("_test__map_equal_range__map_equal_range_varg__user_define_t, _test__map_equal_range__map_equal_range_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_equal_range__map_equal_range_varg__user_define_t, _test__map_equal_range__map_equal_range_varg__user_define_t);
    range_t r_range;
    _test__map_equal_range__map_equal_range_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 7;
    r_range = _map_equal_range(pt_map, &elem);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)))->n_elem == 8);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)))->n_elem == 8);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test _map_at and _map_at_varg
 */
UT_CASE_DEFINATION(_map_at__map_at_varg)
void test__map_at__map_at_varg__null_map(void** state)
{
    expect_assert_failure(_map_at(NULL, 4));
}

void test__map_at__map_at_varg__non_inited(void** state)
{
    map_t* pt_map = create_map(int, int);

    map_init(pt_map);
#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_at(pt_map, 3));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_at(pt_map, 3));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_at__map_at_varg__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;

    map_init(pt_map);
    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_map_at(pt_map, 5));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test__map_at__map_at_varg__c_builtin_exist(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    map_init(pt_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    assert_true(*(int*)_map_at(pt_map, 4) == 4);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_at__map_at_varg__c_builtin_no_exist(void** state)
{
    map_t* pt_map = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    map_init(pt_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i * 2, i);
        map_insert(pt_map, pt_pair);
    }

    assert_true(*(int*)_map_at(pt_map, 3) == 0);
    *(int*)_map_at(pt_map, 3) = 900;
    assert_true(*(int*)_map_at(pt_map, 3) == 900);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_at__map_at_varg__cstr_exist(void** state)
{
    map_t* pt_map = create_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);

    pair_init(pt_pair);
    map_init(pt_map);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nnnnn", "ooooo");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "lso", "iso");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(strcmp((char*)_map_at(pt_map, "lso"), "iso") == 0);

    pair_destroy(pt_pair);
    map_destroy(pt_map);
}

void test__map_at__map_at_varg__cstr_no_exist(void** state)
{
    map_t* pt_map = create_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);

    pair_init(pt_pair);
    map_init(pt_map);
    pair_make(pt_pair, "aaa", "bbb");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nnnnn", "ooooo");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "lso", "iso");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(strcmp((char*)_map_at(pt_map, "tcpip"), "") == 0);

    pair_destroy(pt_pair);
    map_destroy(pt_map);
}

void test__map_at__map_at_varg__libcstl_builtin_exist(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(*(int*)vector_front((vector_t*)_map_at(pt_map, plist)) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__map_at__map_at_varg__libcstl_builtin_no_exist(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);
    pair_init(pt_pair);
    vector_init(pvec);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        vector_clear(pvec);
        list_push_back(plist, i * 2);
        vector_push_back(pvec, i);
        pair_make(pt_pair, plist, pvec);
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 7);
    assert_true(vector_empty((vector_t*)_map_at(pt_map, plist)));

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__map_at__map_at_varg__user_define
{
    int n_elem;
}_test__map_at__map_at_varg__user_define_t;
void test__map_at__map_at_varg__user_define_exist(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    _test__map_at__map_at_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_at__map_at_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_at__map_at_varg__user_define_t, _test__map_at__map_at_varg__user_define_t");
    pt_pair = create_pair(_test__map_at__map_at_varg__user_define_t, _test__map_at__map_at_varg__user_define_t);
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(((_test__map_at__map_at_varg__user_define_t*)_map_at(pt_map, &elem))->n_elem == 8);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_at__map_at_varg__user_define_no_exist(void** state)
{
    map_t* pt_map =  _create_map("_test__map_at__map_at_varg__user_define_t, _test__map_at__map_at_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_at__map_at_varg__user_define_t, _test__map_at__map_at_varg__user_define_t);
    _test__map_at__map_at_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 7;
    assert_true(((_test__map_at__map_at_varg__user_define_t*)_map_at(pt_map, &elem))->n_elem == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test _map_erase and _map_erase_varg
 */
UT_CASE_DEFINATION(_map_erase__map_erase_varg)
void test__map_erase__map_erase_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_erase(NULL, elem));
}

void test__map_erase__map_erase_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int,int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_erase(pt_map, elem));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_erase(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__non_inited_pair(void** state)
{
    map_t* pt_map = create_map(int, int);
    void* pv_tmp = NULL;

    map_init(pt_map);
    pv_tmp = pt_map->_pair_temp._pv_first;
    pt_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_map_erase(pt_map, 4));
    pt_map->_pair_temp._pv_first = pv_tmp;

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__c_builtin_0(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = 24;
    assert_true(_map_erase(pt_map, elem) == 0);
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__c_builtin_1(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
    }

    elem = 8;
    assert_true(_map_erase(pt_map, elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, elem) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__c_builtin_n(void** state)
{
    map_t* pt_map = _create_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
    }

    elem = 8;
    assert_true(_map_erase(pt_map, elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, elem) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__cstr_0(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(_map_erase(pt_map, "gggppgg") == 0);
    assert_true(map_size(pt_map) == 5);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__cstr_1(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(_map_erase(pt_map, "ggg") == 1);
    assert_true(map_size(pt_map) == 4);
    assert_true(_map_count(pt_map, "ggg") == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__cstr_n(void** state)
{
    map_t* pt_map = _create_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    map_insert(pt_map, pt_pair);
    map_insert(pt_map, pt_pair);
    map_insert(pt_map, pt_pair);
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    map_insert(pt_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    map_insert(pt_map, pt_pair);

    assert_true(_map_erase(pt_map, "ggg") == 1);
    assert_true(map_size(pt_map) == 4);
    assert_true(_map_count(pt_map, "ggg") == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__libcstl_builtin_0(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_map_erase(pt_map, plist) == 0);
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__map_erase__map_erase_varg__libcstl_builtin_1(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_map_erase(pt_map, plist) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, plist) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__map_erase__map_erase_varg__libcstl_builtin_n(void** state)
{
    map_t* pt_map = _create_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
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
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_map_erase(pt_map, plist) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, plist) == 0);

    map_destroy(pt_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__map_erase__map_erase_varg__user_define
{
    int n_elem;
}_test__map_erase__map_erase_varg__user_define_t;
void test__map_erase__map_erase_varg__user_define_0(void** state)
{
    map_t* pt_map = NULL;
    pair_t* pt_pair = NULL;
    _test__map_erase__map_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_erase__map_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_erase__map_erase_varg__user_define_t, _test__map_erase__map_erase_varg__user_define_t");
    pt_pair = create_pair(_test__map_erase__map_erase_varg__user_define_t, _test__map_erase__map_erase_varg__user_define_t);
    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 86;
    assert_true(_map_erase(pt_map, &elem) == 0);
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__user_define_1(void** state)
{
    map_t* pt_map =  _create_map("_test__map_erase__map_erase_varg__user_define_t, _test__map_erase__map_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_erase__map_erase_varg__user_define_t, _test__map_erase__map_erase_varg__user_define_t);
    _test__map_erase__map_erase_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_map_erase(pt_map, &elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, &elem) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

void test__map_erase__map_erase_varg__user_define_n(void** state)
{
    map_t* pt_map =  _create_map("_test__map_erase__map_erase_varg__user_define_t, _test__map_erase__map_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__map_erase__map_erase_varg__user_define_t, _test__map_erase__map_erase_varg__user_define_t);
    _test__map_erase__map_erase_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
        map_insert(pt_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_map_erase(pt_map, &elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, &elem) == 0);

    map_destroy(pt_map);
    pair_destroy(pt_pair);
}

/*
 * test _map_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_map_init_elem_auxiliary)
void test__map_init_elem_auxiliary__null_map_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_map_init_elem_auxiliary(NULL, &elem));
}

void test__map_init_elem_auxiliary__null_elem(void** state)
{
    map_t* pmap = create_map(int,int);

    expect_assert_failure(_map_init_elem_auxiliary(pmap, NULL));

    map_destroy(pmap);
}

void test__map_init_elem_auxiliary__non_inited(void** state)
{
    map_t* pt_map = _create_map("int,int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

#ifdef CSTL_MAP_AVL_TREE
    pt_map->_t_tree._t_avlroot._un_height = 9;
    expect_assert_failure(_map_erase(pt_map, elem));
    pt_map->_t_tree._t_avlroot._un_height = 0;
#else
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_BLACK;
    expect_assert_failure(_map_erase(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = _COLOR_RED;
#endif

    map_destroy(pt_map);
}

void test__map_init_elem_auxiliary__successfully_int(void** state)
{
    map_t* pmap = create_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    map_init(pmap);

    _map_init_elem_auxiliary(pmap, pt_pair);
    assert_true(*(int*)pair_first(pt_pair) == 0);
    assert_true(*(int*)pair_second(pt_pair) == 0);

    map_destroy(pmap);
    pair_destroy(pt_pair);
}

void test__map_init_elem_auxiliary__successfully_cstr(void** state)
{
    map_t* pmap = create_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    map_init_ex(pmap, NULL);
    /*pair_init(pt_pair);*/

    _map_init_elem_auxiliary(pmap, pt_pair);
    assert_true(strcmp((char*)pair_first(pt_pair), "") == 0);
    assert_true(strcmp((char*)pair_second(pt_pair), "") == 0);

    map_destroy(pmap);
    pair_destroy(pt_pair);
}

void test__map_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    map_t* pmap = create_map(iterator_t, iterator_t);
    pair_t* pt_pair = create_pair(iterator_t, iterator_t);
    map_init_ex(pmap, NULL);
    /*pair_init(pt_pair);*/

    _map_init_elem_auxiliary(pmap, pt_pair);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp(&it_iter, (iterator_t*)pair_first(pt_pair), sizeof(iterator_t)) == 0);
    assert_true(memcmp(&it_iter, (iterator_t*)pair_second(pt_pair), sizeof(iterator_t)) == 0);

    map_destroy(pmap);
    pair_destroy(pt_pair);
}

void test__map_init_elem_auxiliary__successfully_container(void** state)
{
    map_t* pmap = create_map(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);

    _map_init_elem_auxiliary(pmap, pt_pair);
    assert_true(_vector_is_inited((vector_t*)pair_first(pt_pair)));
    assert_true(_list_is_inited((list_t*)pair_second(pt_pair)));

    map_destroy(pmap);
    pair_destroy(pt_pair);
}

typedef struct _tag_test__map_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__map_init_elem_auxiliary__successfully_user_defined_t;

void test__map_init_elem_auxiliary__successfully_user_defined(void** state)
{
    map_t* pmap = NULL;
    pair_t* pt_pair = NULL;

    type_register(_test__map_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pmap = create_map(_test__map_init_elem_auxiliary__successfully_user_defined_t, _test__map_init_elem_auxiliary__successfully_user_defined_t);
    pt_pair = create_pair(_test__map_init_elem_auxiliary__successfully_user_defined_t, _test__map_init_elem_auxiliary__successfully_user_defined_t);

    _map_init_elem_auxiliary(pmap, pt_pair);
    assert_true(((_test__map_init_elem_auxiliary__successfully_user_defined_t*)pair_first(pt_pair))->n_elem == 0);
    assert_true(((_test__map_init_elem_auxiliary__successfully_user_defined_t*)pair_second(pt_pair))->n_elem == 0);

    map_destroy(pmap);
    pair_destroy(pt_pair);
}

