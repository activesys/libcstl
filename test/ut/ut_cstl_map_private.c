#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cmap.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
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
    assert_true(_pair_is_created(&pt_map->_t_pair));
    assert_true(pt_map->_t_keycompare == NULL);
    assert_true(pt_map->_t_valuecompare == NULL);

    map_destroy(pt_map);
}

void test__create_map_auxiliary__cstr(void** state)
{
    map_t* pt_map = malloc(sizeof(map_t));
    assert_true(_create_map_auxiliary(pt_map, "char*, char*"));
    assert_true(pt_map != NULL);
    assert_true(_pair_is_created(&pt_map->_t_pair));
    assert_true(pt_map->_t_keycompare == NULL);
    assert_true(pt_map->_t_valuecompare == NULL);

    map_destroy(pt_map);
}

void test__create_map_auxiliary__libcstl_builtin(void** state)
{
    map_t* pt_map = malloc(sizeof(map_t));
    assert_true(_create_map_auxiliary(pt_map, "vector_t<int>, list_t<int>"));
    assert_true(pt_map != NULL);
    assert_true(_pair_is_created(&pt_map->_t_pair));
    assert_true(pt_map->_t_keycompare == NULL);
    assert_true(pt_map->_t_valuecompare == NULL);

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
    assert_true(_pair_is_created(&pt_map->_t_pair));
    assert_true(pt_map->_t_keycompare == NULL);
    assert_true(pt_map->_t_valuecompare == NULL);

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

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_destroy_auxiliary(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_destroy_auxiliary__non_inited(void** state)
{
    map_t* pt_map = _create_map("int, int");
    map_init(pt_map);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_destroy_auxiliary(pt_map));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_destroy_auxiliary__empty(void** state)
{
    map_t* pt_map = _create_map("int, int");
    map_init(pt_map);

    _map_destroy_auxiliary(pt_map);
    assert_true(pt_map->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_map->_t_tree._t_rbroot._pt_left == &pt_map->_t_tree._t_rbroot);
    assert_true(pt_map->_t_tree._t_rbroot._pt_right == &pt_map->_t_tree._t_rbroot);
    assert_true(pt_map->_t_tree._t_nodecount == 0);
    assert_true(pt_map->_t_tree._t_compare == NULL);
    assert_true(pt_map->_t_pair._pv_first == NULL);
    assert_true(pt_map->_t_pair._pv_second == NULL);
    assert_true(pt_map->_t_pair._t_mapkeycompare == NULL);
    assert_true(pt_map->_t_pair._t_mapvaluecompare == NULL);
    assert_true(pt_map->_t_keycompare == NULL);
    assert_true(pt_map->_t_valuecompare == NULL);
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
    assert_true(pt_map->_t_tree._t_rbroot._pt_parent == NULL);
    assert_true(pt_map->_t_tree._t_rbroot._pt_left == &pt_map->_t_tree._t_rbroot);
    assert_true(pt_map->_t_tree._t_rbroot._pt_right == &pt_map->_t_tree._t_rbroot);
    assert_true(pt_map->_t_tree._t_nodecount == 0);
    assert_true(pt_map->_t_tree._t_compare == NULL);
    assert_true(pt_map->_t_pair._pv_first == NULL);
    assert_true(pt_map->_t_pair._pv_second == NULL);
    assert_true(pt_map->_t_pair._t_mapkeycompare == NULL);
    assert_true(pt_map->_t_pair._t_mapvaluecompare == NULL);
    assert_true(pt_map->_t_keycompare == NULL);
    assert_true(pt_map->_t_valuecompare == NULL);
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

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_find(pt_map, 9));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_find__map_find_varg__non_inited_pair(void** state)
{
    map_t* pt_map = _create_map("int, int");
    void* pv_tmp = NULL;

    map_init(pt_map);
    pv_tmp = pt_map->_t_pair._pv_first;
    pt_map->_t_pair._pv_first = NULL;
    expect_assert_failure(_map_find(pt_map, 9));
    pt_map->_t_pair._pv_first = pv_tmp;

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
    int elem;
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

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_count(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_count__map_count_varg__non_inited_pair(void** state)
{
    map_t* pt_map = _create_map("int, int");
    void* pv_tmp = NULL;
    int elem = 9;
    map_init(pt_map);

    pv_tmp = pt_map->_t_pair._pv_first;
    pt_map->_t_pair._pv_first = NULL;
    expect_assert_failure(_map_count(pt_map, elem));
    pt_map->_t_pair._pv_first = pv_tmp;

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
/*
UT_CASE_DEFINATION(_map_lower_bound__map_lower_bound_varg)
void test__map_lower_bound__map_lower_bound_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_lower_bound(NULL, elem));
}

void test__map_lower_bound__map_lower_bound_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem = 9;
    map_init(pt_map);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_lower_bound(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init(pt_map);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = 2;
    it_iter = _map_lower_bound(pt_map, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__c_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init(pt_map);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = -8;
    it_iter = _map_lower_bound(pt_map, elem);
    assert_true(iterator_equal(it_iter, map_begin(pt_map)));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__cstr_lower_equal(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init(pt_map);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    it_iter = _map_lower_bound(pt_map, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "ggg") == 0);

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__cstr_greater(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init(pt_map);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    it_iter = _map_lower_bound(pt_map, "vvvv");
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init(pt_map);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _map_lower_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
}

void test__map_lower_bound__map_lower_bound_varg__libcstl_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init(pt_map);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _map_lower_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
}

typedef struct _tag_test__map_lower_bound__map_lower_bound_varg__user_define
{
    int n_elem;
}_test__map_lower_bound__map_lower_bound_varg__user_define_t;
void test__map_lower_bound__map_lower_bound_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    map_iterator_t it_iter;
    _test__map_lower_bound__map_lower_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_lower_bound__map_lower_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_lower_bound__map_lower_bound_varg__user_define_t");
    map_init(pt_map);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 8;
    it_iter = _map_lower_bound(pt_map, &elem);
    assert_true(((_test__map_lower_bound__map_lower_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    map_destroy(pt_map);
}

void test__map_lower_bound__map_lower_bound_varg__user_define_greater(void** state)
{
    map_t* pt_map =  _create_map("_test__map_lower_bound__map_lower_bound_varg__user_define_t");
    map_iterator_t it_iter;
    _test__map_lower_bound__map_lower_bound_varg__user_define_t elem;
    int i = 0;

    map_init(pt_map);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 7;
    it_iter = _map_lower_bound(pt_map, &elem);
    assert_true(((_test__map_lower_bound__map_lower_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    map_destroy(pt_map);
}
*/

/*
 * test _map_upper_bound and _map_upper_bound_varg
 */
/*
UT_CASE_DEFINATION(_map_upper_bound__map_upper_bound_varg)
void test__map_upper_bound__map_upper_bound_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_upper_bound(NULL, elem));
}

void test__map_upper_bound__map_upper_bound_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_upper_bound(pt_map, &elem));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = 2;
    it_iter = _map_upper_bound(pt_map, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__c_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = -8;
    it_iter = _map_upper_bound(pt_map, elem);
    assert_true(iterator_equal(it_iter, map_begin(pt_map)));
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__cstr_upper_equal(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    it_iter = _map_upper_bound(pt_map, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "linux") == 0);

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__cstr_greater(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    it_iter = _map_upper_bound(pt_map, "vvv");
    assert_true(iterator_equal(it_iter, map_end(pt_map)));

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _map_upper_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 7);

    map_destroy(pt_map);
    list_destroy(plist);
}

void test__map_upper_bound__map_upper_bound_varg__libcstl_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _map_upper_bound(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
}

typedef struct _tag_test__map_upper_bound__map_upper_bound_varg__user_define
{
    int n_elem;
}_test__map_upper_bound__map_upper_bound_varg__user_define_t;
void test__map_upper_bound__map_upper_bound_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    map_iterator_t it_iter;
    _test__map_upper_bound__map_upper_bound_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_upper_bound__map_upper_bound_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_upper_bound__map_upper_bound_varg__user_define_t");
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 8;
    it_iter = _map_upper_bound(pt_map, &elem);
    assert_true(((_test__map_upper_bound__map_upper_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 9);

    map_destroy(pt_map);
}

void test__map_upper_bound__map_upper_bound_varg__user_define_greater(void** state)
{
    map_t* pt_map =  _create_map("_test__map_upper_bound__map_upper_bound_varg__user_define_t");
    map_iterator_t it_iter;
    _test__map_upper_bound__map_upper_bound_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 7;
    it_iter = _map_upper_bound(pt_map, &elem);
    assert_true(((_test__map_upper_bound__map_upper_bound_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    map_destroy(pt_map);
}
*/

/*
 * test _map_equal_range and _map_equal_range_varg
 */
/*
UT_CASE_DEFINATION(_map_equal_range__map_equal_range_varg)
void test__map_equal_range__map_equal_range_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_equal_range(NULL, elem));
}

void test__map_equal_range__map_equal_range_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_equal_range(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int");
    range_t r_range;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = 2;
    r_range = _map_equal_range(pt_map, elem);
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 2);
    assert_true(*(int*)iterator_get_pointer(r_range.it_end) == 3);

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__c_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("int");
    range_t r_range;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = -8;
    r_range = _map_equal_range(pt_map, elem);
    assert_true(iterator_equal(r_range.it_begin, map_begin(pt_map)));
    assert_true(iterator_equal(r_range.it_end, map_begin(pt_map)));
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 0);

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__cstr_upper_equal(void** state)
{
    map_t* pt_map = _create_map("char*");
    range_t r_range;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    r_range = _map_equal_range(pt_map, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_begin), "ggg") == 0);
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_end), "linux") == 0);

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__cstr_greater(void** state)
{
    map_t* pt_map = _create_map("char*");
    range_t r_range;

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    r_range = _map_equal_range(pt_map, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, map_end(pt_map)));
    assert_true(iterator_equal(r_range.it_end, map_end(pt_map)));

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _map_equal_range(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 7);

    map_destroy(pt_map);
    list_destroy(plist);
}

void test__map_equal_range__map_equal_range_varg__libcstl_builtin_greater(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _map_equal_range(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 6);

    map_destroy(pt_map);
    list_destroy(plist);
}

typedef struct _tag_test__map_equal_range__map_equal_range_varg__user_define
{
    int n_elem;
}_test__map_equal_range__map_equal_range_varg__user_define_t;
void test__map_equal_range__map_equal_range_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    range_t r_range;
    _test__map_equal_range__map_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_equal_range__map_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_equal_range__map_equal_range_varg__user_define_t");
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 8;
    r_range = _map_equal_range(pt_map, &elem);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 9);

    map_destroy(pt_map);
}

void test__map_equal_range__map_equal_range_varg__user_define_greater(void** state)
{
    map_t* pt_map =  _create_map("_test__map_equal_range__map_equal_range_varg__user_define_t");
    range_t r_range;
    _test__map_equal_range__map_equal_range_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 7;
    r_range = _map_equal_range(pt_map, &elem);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__map_equal_range__map_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 8);

    map_destroy(pt_map);
}
*/

/*
 * test _map_erase and _map_erase_varg
 */
/*
UT_CASE_DEFINATION(_map_erase__map_erase_varg)
void test__map_erase__map_erase_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_erase(NULL, elem));
}

void test__map_erase__map_erase_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_erase(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__c_builtin_0(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = 24;
    assert_true(_map_erase(pt_map, elem) == 0);
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__c_builtin_1(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
    }

    elem = 8;
    assert_true(_map_erase(pt_map, elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, elem) == 0);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__c_builtin_n(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        map_insert(pt_map, i);
        map_insert(pt_map, i);
        map_insert(pt_map, i);
    }

    elem = 8;
    assert_true(_map_erase(pt_map, elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, elem) == 0);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__cstr_0(void** state)
{
    map_t* pt_map = _create_map("char*");

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    assert_true(_map_erase(pt_map, "gggppgg") == 0);
    assert_true(map_size(pt_map) == 5);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__cstr_1(void** state)
{
    map_t* pt_map = _create_map("char*");

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    assert_true(_map_erase(pt_map, "ggg") == 1);
    assert_true(map_size(pt_map) == 4);
    assert_true(_map_count(pt_map, "ggg") == 0);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__cstr_n(void** state)
{
    map_t* pt_map = _create_map("char*");

    map_init_ex(pt_map, NULL);
    map_insert(pt_map, "aaa");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "ggg");
    map_insert(pt_map, "nghl");
    map_insert(pt_map, "asery");
    map_insert(pt_map, "linux");

    assert_true(_map_erase(pt_map, "ggg") == 1);
    assert_true(map_size(pt_map) == 4);
    assert_true(_map_count(pt_map, "ggg") == 0);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__libcstl_builtin_0(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_map_erase(pt_map, plist) == 0);
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    list_destroy(plist);
}

void test__map_erase__map_erase_varg__libcstl_builtin_1(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_map_erase(pt_map, plist) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, plist) == 0);

    map_destroy(pt_map);
    list_destroy(plist);
}

void test__map_erase__map_erase_varg__libcstl_builtin_n(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        map_insert(pt_map, plist);
        map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_map_erase(pt_map, plist) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, plist) == 0);

    map_destroy(pt_map);
    list_destroy(plist);
}

typedef struct _tag_test__map_erase__map_erase_varg__user_define
{
    int n_elem;
}_test__map_erase__map_erase_varg__user_define_t;
void test__map_erase__map_erase_varg__user_define_0(void** state)
{
    map_t* pt_map = NULL;
    _test__map_erase__map_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_erase__map_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_erase__map_erase_varg__user_define_t");
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 86;
    assert_true(_map_erase(pt_map, &elem) == 0);
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__user_define_1(void** state)
{
    map_t* pt_map =  _create_map("_test__map_erase__map_erase_varg__user_define_t");
    _test__map_erase__map_erase_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 8;
    assert_true(_map_erase(pt_map, &elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, &elem) == 0);

    map_destroy(pt_map);
}

void test__map_erase__map_erase_varg__user_define_n(void** state)
{
    map_t* pt_map =  _create_map("_test__map_erase__map_erase_varg__user_define_t");
    _test__map_erase__map_erase_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        map_insert(pt_map, &elem);
        map_insert(pt_map, &elem);
        map_insert(pt_map, &elem);
    }

    elem.n_elem = 8;
    assert_true(_map_erase(pt_map, &elem) == 1);
    assert_true(map_size(pt_map) == 9);
    assert_true(_map_count(pt_map, &elem) == 0);

    map_destroy(pt_map);
}
*/

/*
 * test _map_insert and _map_insert_varg
 */
/*
UT_CASE_DEFINATION(_map_insert__map_insert_varg)
void test__map_insert_varg__null_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_map_insert(NULL, elem));
}

void test__map_insert_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int");
    int elem = 9;
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_insert(pt_map, elem));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_insert_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        _map_insert(pt_map, i);
    }

    elem = 2;
    it_iter = _map_insert(pt_map, elem);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
}

void test__map_insert_varg__c_builtin_not_equal(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        _map_insert(pt_map, i);
    }

    elem = -8;
    it_iter = _map_insert(pt_map, elem);
    assert_true(*(int*)_map_iterator_get_pointer(it_iter) == -8);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
}

void test__map_insert_varg__cstr_equal(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    _map_insert(pt_map, "aaa");
    _map_insert(pt_map, "ggg");
    _map_insert(pt_map, "nghl");
    _map_insert(pt_map, "asery");
    _map_insert(pt_map, "linux");

    it_iter = _map_insert(pt_map, "ggg");
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 5);

    map_destroy(pt_map);
}

void test__map_insert_varg__cstr_not_equal(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    _map_insert(pt_map, "aaa");
    _map_insert(pt_map, "ggg");
    _map_insert(pt_map, "nghl");
    _map_insert(pt_map, "asery");
    _map_insert(pt_map, "linux");

    it_iter = _map_insert(pt_map, "vvvv");
    assert_true(strcmp((char*)_map_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(map_size(pt_map) == 6);

    map_destroy(pt_map);
}

void test__map_insert_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _map_insert(pt_map, plist);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    list_destroy(plist);
}

void test__map_insert_varg__libcstl_builtin_not_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _map_insert(pt_map, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _map_insert(pt_map, plist);
    assert_true(*(int*)list_front((list_t*)_map_iterator_get_pointer(it_iter)) == 5);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    list_destroy(plist);
}

typedef struct _tag_test__map_insert_varg__user_define
{
    int n_elem;
}_test__map_insert_varg__user_define_t;
void test__map_insert_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    map_iterator_t it_iter;
    _test__map_insert_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_insert_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_insert_varg__user_define_t");
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _map_insert(pt_map, &elem);
    }

    elem.n_elem = 8;
    it_iter = _map_insert(pt_map, &elem);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
}

void test__map_insert_varg__user_define_not_equal(void** state)
{
    map_t* pt_map =  _create_map("_test__map_insert_varg__user_define_t");
    map_iterator_t it_iter;
    _test__map_insert_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _map_insert(pt_map, &elem);
    }

    elem.n_elem = 7;
    it_iter = _map_insert(pt_map, &elem);
    assert_true(((_test__map_insert_varg__user_define_t*)_map_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
}
*/

/*
 * test _map_insert_hint and _map_insert_hint_varg
 */
/*
UT_CASE_DEFINATION(_map_insert_hint__map_insert_hint_varg)
void test__map_insert_hint_varg__null_map(void** state)
{
    int elem = 9;
    map_iterator_t it_hint;
    expect_assert_failure(_map_insert_hint(NULL, it_hint, elem));
}

void test__map_insert_hint_varg__non_inited(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_hint;
    int elem = 9;
    map_init_ex(pt_map, NULL);

    pt_map->_t_tree._t_rbroot._t_color = BLACK;
    expect_assert_failure(_map_insert_hint(pt_map, it_hint, elem));
    pt_map->_t_tree._t_rbroot._t_color = RED;

    map_destroy(pt_map);
}

void test__map_insert_hint_varg__c_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        _map_insert_hint(pt_map, it_iter, i);
    }

    elem = 2;
    it_iter = _map_insert_hint(pt_map, it_iter, elem);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
}

void test__map_insert_hint_varg__c_builtin_not_equal(void** state)
{
    map_t* pt_map = _create_map("int");
    map_iterator_t it_iter;
    int elem;
    int i;

    map_init_ex(pt_map, NULL);
    for(i = 0; i < 10; ++i)
    {
        _map_insert_hint(pt_map, it_iter, i);
    }

    elem = -8;
    it_iter = _map_insert_hint(pt_map, it_iter, elem);
    assert_true(*(int*)_map_iterator_get_pointer(it_iter) == -8);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
}

void test__map_insert_hint_varg__cstr_equal(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    _map_insert_hint(pt_map, it_iter, "aaa");
    _map_insert_hint(pt_map, it_iter, "ggg");
    _map_insert_hint(pt_map, it_iter, "nghl");
    _map_insert_hint(pt_map, it_iter, "asery");
    _map_insert_hint(pt_map, it_iter, "linux");

    it_iter = _map_insert_hint(pt_map, it_iter, "ggg");
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 5);

    map_destroy(pt_map);
}

void test__map_insert_hint_varg__cstr_not_equal(void** state)
{
    map_t* pt_map = _create_map("char*");
    map_iterator_t it_iter;

    map_init_ex(pt_map, NULL);
    _map_insert_hint(pt_map, it_iter, "aaa");
    _map_insert_hint(pt_map, it_iter, "ggg");
    _map_insert_hint(pt_map, it_iter, "nghl");
    _map_insert_hint(pt_map, it_iter, "asery");
    _map_insert_hint(pt_map, it_iter, "linux");

    it_iter = _map_insert_hint(pt_map, it_iter, "vvvv");
    assert_true(strcmp((char*)_map_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(map_size(pt_map) == 6);

    map_destroy(pt_map);
}

void test__map_insert_hint_varg__libcstl_builtin_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _map_insert_hint(pt_map, it_iter, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _map_insert_hint(pt_map, it_iter, plist);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
    list_destroy(plist);
}

void test__map_insert_hint_varg__libcstl_builtin_not_equal(void** state)
{
    map_t* pt_map = _create_map("list_t<int>");
    map_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    map_init_ex(pt_map, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _map_insert_hint(pt_map, it_iter, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _map_insert_hint(pt_map, it_iter, plist);
    assert_true(*(int*)list_front((list_t*)_map_iterator_get_pointer(it_iter)) == 5);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
    list_destroy(plist);
}

typedef struct _tag_test__map_insert_hint_varg__user_define
{
    int n_elem;
}_test__map_insert_hint_varg__user_define_t;
void test__map_insert_hint_varg__user_define_equal(void** state)
{
    map_t* pt_map = NULL;
    map_iterator_t it_iter;
    _test__map_insert_hint_varg__user_define_t elem;
    int i = 0;

    type_register(_test__map_insert_hint_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_map = _create_map("_test__map_insert_hint_varg__user_define_t");
    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _map_insert_hint(pt_map, it_iter, &elem);
    }

    elem.n_elem = 8;
    it_iter = _map_insert_hint(pt_map, it_iter, &elem);
    assert_true(iterator_equal(it_iter, map_end(pt_map)));
    assert_true(map_size(pt_map) == 10);

    map_destroy(pt_map);
}

void test__map_insert_hint_varg__user_define_not_equal(void** state)
{
    map_t* pt_map =  _create_map("_test__map_insert_hint_varg__user_define_t");
    map_iterator_t it_iter;
    _test__map_insert_hint_varg__user_define_t elem;
    int i = 0;

    map_init_ex(pt_map, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _map_insert_hint(pt_map, it_iter, &elem);
    }

    elem.n_elem = 7;
    it_iter = _map_insert_hint(pt_map, it_iter, &elem);
    assert_true(((_test__map_insert_hint_varg__user_define_t*)_map_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(map_size(pt_map) == 11);

    map_destroy(pt_map);
}
*/

/*
 * test _map_init_elem_auxiliary
 */
/*
UT_CASE_DEFINATION(_map_init_elem_auxiliary)
void test__map_init_elem_auxiliary__null_map_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_map_init_elem_auxiliary(NULL, &elem));
}

void test__map_init_elem_auxiliary__null_elem(void** state)
{
    map_t* pmap = create_map(int);

    expect_assert_failure(_map_init_elem_auxiliary(pmap, NULL));

    map_destroy(pmap);
}

void test__map_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    map_t* pmap = create_map(int);
    map_init(pmap);

    _map_init_elem_auxiliary(pmap, &elem);
    assert_true(elem == 0);

    map_destroy(pmap);
}

void test__map_init_elem_auxiliary__successfully_cstr(void** state)
{
    map_t* pmap = create_map(char*);
    map_init_ex(pmap, NULL);

    map_insert(pmap, "abc");
    map_insert(pmap, "def");
    _map_init_elem_auxiliary(pmap, pmap->_t_tree._t_rbroot._pt_left->_pby_data); 
    assert_true(strcmp((char*)iterator_get_pointer(map_begin(pmap)), "") == 0);

    map_destroy(pmap);
}

void test__map_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    map_t* pmap = create_map(iterator_t);
    map_init_ex(pmap, NULL);

    map_insert(pmap, &it_iter);

    _map_init_elem_auxiliary(pmap, (void*)iterator_get_pointer(map_begin(pmap)));
    memmap(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)iterator_get_pointer(map_begin(pmap)), &it_iter, sizeof(iterator_t)) == 0);

    map_destroy(pmap);
}

void test__map_init_elem_auxiliary__successfully_container(void** state)
{
    vector_t vec;
    map_t* pmap = create_map(vector_t<int>);

    _map_init_elem_auxiliary(pmap, &vec);
    assert_true(_vector_is_inited(&vec));

    map_destroy(pmap);
}

typedef struct _tag_test__map_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__map_init_elem_auxiliary__successfully_user_defined_t;

void test__map_init_elem_auxiliary__successfully_user_defined(void** state)
{
    _test__map_init_elem_auxiliary__successfully_user_defined_t t_user;
    map_t* pmap = NULL;

    type_register(_test__map_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pmap = create_map(_test__map_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _map_init_elem_auxiliary(pmap, &t_user);
    assert_true(t_user.n_elem == 0);

    map_destroy(pmap);
}
*/

