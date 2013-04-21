#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/chash_map.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_list_aux.h"
#include "cstl_hash_map_aux.h"

#include "ut_def.h"
#include "ut_cstl_hash_map_private.h"

UT_SUIT_DEFINATION(cstl_hash_map_private, _create_hash_map)

/*
 * test _create_hash_map
 */
UT_CASE_DEFINATION(_create_hash_map)
void test__create_hash_map__null_typename(void** state)
{
    expect_assert_failure(_create_hash_map(NULL));
}

void test__create_hash_map__c_builtin(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, double");
    assert_true(pt_hash_map != NULL);

    hash_map_destroy(pt_hash_map);
}

void test__create_hash_map__cstr(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    assert_true(pt_hash_map != NULL);

    hash_map_destroy(pt_hash_map);
}

void test__create_hash_map__libcstl_builtin(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("vector_t<int>, list_t<double>");
    assert_true(pt_hash_map != NULL);

    hash_map_destroy(pt_hash_map);
}

typedef struct _test_test__create_hash_map__user_define
{
    int n_elem;
}_test__create_hash_map__user_define_t;

void test__create_hash_map__user_define(void** state)
{
    hash_map_t* pt_hash_map = NULL;

    type_register(_test__create_hash_map__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_map = _create_hash_map("_test__create_hash_map__user_define_t, _test__create_hash_map__user_define_t");
    assert_true(pt_hash_map != NULL);

    hash_map_destroy(pt_hash_map);
}

void test__create_hash_map__unregister(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("test__create_hash_map__unregister_t, test__create_hash_map__unregister_t");
    assert_true(pt_hash_map == NULL);
}

/*
 * test _create_hash_map_auxiliary
 */
UT_CASE_DEFINATION(_create_hash_map_auxiliary)
void test__create_hash_map_auxiliary__null_hash_map(void** state)
{
    expect_assert_failure(_create_hash_map_auxiliary(NULL, "int, int"));
}

void test__create_hash_map_auxiliary__null_typename(void** state)
{
    hash_map_t t_hash_map;
    expect_assert_failure(_create_hash_map_auxiliary(&t_hash_map, NULL));
}

void test__create_hash_map_auxiliary__unregistered(void** state)
{
    hash_map_t* pt_hash_map = malloc(sizeof(hash_map_t));
    assert_false(_create_hash_map_auxiliary(pt_hash_map, "_test__create_hash_map_auxiliary__unregistered_t, _test__create_hash_map_auxiliary__unregistered_t"));

    free(pt_hash_map);
}

void test__create_hash_map_auxiliary__c_builtin(void** state)
{
    hash_map_t* pt_hash_map = malloc(sizeof(hash_map_t));
    assert_true(_create_hash_map_auxiliary(pt_hash_map, "int, int"));
    assert_true(pt_hash_map != NULL);
    assert_true(_pair_is_created(&pt_hash_map->_pair_temp));
    assert_true(pt_hash_map->_bfun_keycompare == NULL);
    assert_true(pt_hash_map->_bfun_valuecompare == NULL);

    hash_map_destroy(pt_hash_map);
}

void test__create_hash_map_auxiliary__cstr(void** state)
{
    hash_map_t* pt_hash_map = malloc(sizeof(hash_map_t));
    assert_true(_create_hash_map_auxiliary(pt_hash_map, "char*, char*"));
    assert_true(pt_hash_map != NULL);
    assert_true(_pair_is_created(&pt_hash_map->_pair_temp));
    assert_true(pt_hash_map->_bfun_keycompare == NULL);
    assert_true(pt_hash_map->_bfun_valuecompare == NULL);

    hash_map_destroy(pt_hash_map);
}

void test__create_hash_map_auxiliary__libcstl_builtin(void** state)
{
    hash_map_t* pt_hash_map = malloc(sizeof(hash_map_t));
    assert_true(_create_hash_map_auxiliary(pt_hash_map, "vector_t<int>, list_t<int>"));
    assert_true(pt_hash_map != NULL);
    assert_true(_pair_is_created(&pt_hash_map->_pair_temp));
    assert_true(pt_hash_map->_bfun_keycompare == NULL);
    assert_true(pt_hash_map->_bfun_valuecompare == NULL);

    hash_map_destroy(pt_hash_map);
}

typedef struct _tag_test__create_hash_map_auxiliary__user_define
{
    int n_elem;
}_test__create_hash_map_auxiliary__user_define_t;

void test__create_hash_map_auxiliary__user_define(void** state)
{
    hash_map_t* pt_hash_map = NULL;

    type_register(_test__create_hash_map_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_map = malloc(sizeof(hash_map_t));
    assert_true(_create_hash_map_auxiliary(pt_hash_map, "_test__create_hash_map_auxiliary__user_define_t, _test__create_hash_map_auxiliary__user_define_t"));
    assert_true(pt_hash_map != NULL);
    assert_true(_pair_is_created(&pt_hash_map->_pair_temp));
    assert_true(pt_hash_map->_bfun_keycompare == NULL);
    assert_true(pt_hash_map->_bfun_valuecompare == NULL);

    hash_map_destroy(pt_hash_map);
}

/*
 * test _hash_map_destroy_auxiliary
 */
UT_CASE_DEFINATION(_hash_map_destroy_auxiliary)
void test__hash_map_destroy_auxiliary__null_hash_map(void** state)
{
    expect_assert_failure(_hash_map_destroy_auxiliary(NULL));
}

void test__hash_map_destroy_auxiliary__non_created(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");

    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 4444;
    expect_assert_failure(_hash_map_destroy_auxiliary(pt_hash_map));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_destroy_auxiliary__non_inited(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    hash_map_init(pt_hash_map);

    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 4444;
    expect_assert_failure(_hash_map_destroy_auxiliary(pt_hash_map));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_destroy_auxiliary__empty(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    hash_map_init(pt_hash_map);

    _hash_map_destroy_auxiliary(pt_hash_map);
    assert_true(pt_hash_map->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_map->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_map->_t_hashtable._t_nodecount == 0);
    assert_true(pt_hash_map->_pair_temp._pv_first == NULL);
    assert_true(pt_hash_map->_pair_temp._pv_second == NULL);
    assert_true(pt_hash_map->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_hash_map->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_hash_map->_bfun_keycompare == NULL);
    assert_true(pt_hash_map->_bfun_valuecompare == NULL);
    free(pt_hash_map);
}

void test__hash_map_destroy_auxiliary__non_empty(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);

    pair_init_elem(pt_pair, 19, 30);
    hash_map_init(pt_hash_map);
    hash_map_insert(pt_hash_map, pt_pair);

    _hash_map_destroy_auxiliary(pt_hash_map);
    assert_true(pt_hash_map->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_map->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_map->_t_hashtable._t_nodecount == 0);
    assert_true(pt_hash_map->_pair_temp._pv_first == NULL);
    assert_true(pt_hash_map->_pair_temp._pv_second == NULL);
    assert_true(pt_hash_map->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_hash_map->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_hash_map->_bfun_keycompare == NULL);
    assert_true(pt_hash_map->_bfun_valuecompare == NULL);
    free(pt_hash_map);

    pair_destroy(pt_pair);
}

/*
 * test _hash_map_find and _hash_map_find_varg
 */
UT_CASE_DEFINATION(_hash_map_find__hash_map_find_varg)
void test__hash_map_find__hash_map_find_varg__null_hash_map(void** state)
{
    expect_assert_failure(_hash_map_find(NULL, 9));
}

void test__hash_map_find__hash_map_find_varg__non_inited(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    hash_map_init(pt_hash_map);

    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_map_find(pt_hash_map, 9));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_find__hash_map_find_varg__non_inited_pair(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    void* pv_tmp = NULL;

    hash_map_init(pt_hash_map);
    pv_tmp = pt_hash_map->_pair_temp._pv_first;
    pt_hash_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_hash_map_find(pt_hash_map, 9));
    pt_hash_map->_pair_temp._pv_first = pv_tmp;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_find__hash_map_find_varg__c_builtin_find(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    hash_map_iterator_t it_iter;
    int elem;
    int i;

    pair_init(pt_pair);
    hash_map_init(pt_hash_map);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+8);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 2;
    it_iter = _hash_map_find(pt_hash_map, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    assert_true(*(int*)pair_second((pair_t*)iterator_get_pointer(it_iter)) == 10);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_find__hash_map_find_varg__c_builtin_not_find(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    hash_map_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    hash_map_init(pt_hash_map);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+5);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    it_iter = _hash_map_find(pt_hash_map, 42);
    assert_true(iterator_equal(it_iter, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_find__hash_map_find_varg__cstr_find(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    hash_map_iterator_t it_iter;

    pair_init(pt_pair);
    hash_map_init(pt_hash_map);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    it_iter = hash_map_find(pt_hash_map, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)iterator_get_pointer(it_iter)), "fff") == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_find__hash_map_find_varg__cstr_not_find(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    hash_map_iterator_t it_iter;

    pair_init(pt_pair);
    hash_map_init(pt_hash_map);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    it_iter = _hash_map_find(pt_hash_map, "vvvvv");
    assert_true(iterator_equal(it_iter, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

static void _test__hash_map_find__libcstl_builtin_hash(const void* cpv_input, void* pv_output)
{
    list_t* plist = (list_t*)pair_first((pair_t*)cpv_input);
    list_iterator_t it_iter;
    *(size_t*)pv_output = 0;
    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        *(size_t*)pv_output += *(int*)iterator_get_pointer(it_iter);
    }
}
void test__hash_map_find__hash_map_find_varg__libcstl_builtin_find(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    hash_map_iterator_t it_iter;
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hash_map_find(pt_hash_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);
    assert_true(*(int*)vector_front((vector_t*)pair_second((pair_t*)iterator_get_pointer(it_iter))) == 6);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_map_find__hash_map_find_varg__libcstl_builtin_not_find(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    hash_map_iterator_t it_iter;
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _hash_map_find(pt_hash_map, plist);
    assert_true(iterator_equal(it_iter, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_map_find__hash_map_find_varg__user_define
{
    int n_elem;
}_test__hash_map_find__hash_map_find_varg__user_define_t;
void test__hash_map_find__hash_map_find_varg__user_define_find(void** state)
{
    hash_map_t* pt_hash_map = NULL;
    pair_t* pt_pair = NULL;
    hash_map_iterator_t it_iter;
    _test__hash_map_find__hash_map_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_map_find__hash_map_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_map = _create_hash_map("_test__hash_map_find__hash_map_find_varg__user_define_t, _test__hash_map_find__hash_map_find_varg__user_define_t");
    pt_pair = create_pair(_test__hash_map_find__hash_map_find_varg__user_define_t, _test__hash_map_find__hash_map_find_varg__user_define_t);
    hash_map_init(pt_hash_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _hash_map_find(pt_hash_map, &elem);
    assert_true(((_test__hash_map_find__hash_map_find_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);
    assert_true(((_test__hash_map_find__hash_map_find_varg__user_define_t*)pair_second((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_find__hash_map_find_varg__user_define_not_find(void** state)
{
    hash_map_t* pt_hash_map =  _create_hash_map("_test__hash_map_find__hash_map_find_varg__user_define_t, _test__hash_map_find__hash_map_find_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_map_find__hash_map_find_varg__user_define_t, _test__hash_map_find__hash_map_find_varg__user_define_t);
    hash_map_iterator_t it_iter;
    _test__hash_map_find__hash_map_find_varg__user_define_t elem;
    int i = 0;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 78;
    it_iter = _hash_map_find(pt_hash_map, &elem);
    assert_true(iterator_equal(it_iter, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

/*
 * test _hash_map_count and _hash_map_count_varg
 */
UT_CASE_DEFINATION(_hash_map_count__hash_map_count_varg)
void test__hash_map_count__hash_map_count_varg__null_hash_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_map_count(NULL, elem));
}

void test__hash_map_count__hash_map_count_varg__non_inited(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    int elem = 9;
    hash_map_init(pt_hash_map);

    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_map_count(pt_hash_map, elem));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_count__hash_map_count_varg__non_inited_pair(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    void* pv_tmp = NULL;
    int elem = 9;
    hash_map_init(pt_hash_map);

    pv_tmp = pt_hash_map->_pair_temp._pv_first;
    pt_hash_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_hash_map_count(pt_hash_map, elem));
    pt_hash_map->_pair_temp._pv_first = pv_tmp;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_count__hash_map_count_varg__c_builtin_0(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 1222;
    assert_true(_hash_map_count(pt_hash_map, elem) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__c_builtin_1(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 2;
    assert_true(_hash_map_count(pt_hash_map, elem) == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__c_builtin_n(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 2;
    assert_true(_hash_map_count(pt_hash_map, elem) == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__cstr_0(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(_hash_map_count(pt_hash_map, "uuuu") == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__cstr_1(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(_hash_map_count(pt_hash_map, "ggg") == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__cstr_n(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_map_insert(pt_hash_map, pt_pair);
    hash_map_insert(pt_hash_map, pt_pair);
    hash_map_insert(pt_hash_map, pt_pair);
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(_hash_map_count(pt_hash_map, "ggg") == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__libcstl_builtin_0(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_hash_map_count(pt_hash_map, plist) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_map_count__hash_map_count_varg__libcstl_builtin_1(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_map_count(pt_hash_map, plist) == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_map_count__hash_map_count_varg__libcstl_builtin_n(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_map_count(pt_hash_map, plist) == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_map_count__hash_map_count_varg__user_define
{
    int n_elem;
}_test__hash_map_count__hash_map_count_varg__user_define_t;
void test__hash_map_count__hash_map_count_varg__user_define_0(void** state)
{
    hash_map_t* pt_hash_map = NULL;
    pair_t* pt_pair = NULL;
    _test__hash_map_count__hash_map_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_map_count__hash_map_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_map = _create_hash_map("_test__hash_map_count__hash_map_count_varg__user_define_t, _test__hash_map_count__hash_map_count_varg__user_define_t");
    pt_pair = create_pair(_test__hash_map_count__hash_map_count_varg__user_define_t, _test__hash_map_count__hash_map_count_varg__user_define_t);
    hash_map_init(pt_hash_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 88;
    assert_true(_hash_map_count(pt_hash_map, &elem) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__user_define_1(void** state)
{
    hash_map_t* pt_hash_map =  _create_hash_map("_test__hash_map_count__hash_map_count_varg__user_define_t, _test__hash_map_count__hash_map_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_map_count__hash_map_count_varg__user_define_t, _test__hash_map_count__hash_map_count_varg__user_define_t);
    _test__hash_map_count__hash_map_count_varg__user_define_t elem;
    int i = 0;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_map_count(pt_hash_map, &elem) == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_count__hash_map_count_varg__user_define_n(void** state)
{
    hash_map_t* pt_hash_map =  _create_hash_map("_test__hash_map_count__hash_map_count_varg__user_define_t, _test__hash_map_count__hash_map_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_map_count__hash_map_count_varg__user_define_t, _test__hash_map_count__hash_map_count_varg__user_define_t);
    _test__hash_map_count__hash_map_count_varg__user_define_t elem;
    int i = 0;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_map_count(pt_hash_map, &elem) == 1);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

/*
 * test _hash_map_equal_range and _hash_map_equal_range_varg
 */
UT_CASE_DEFINATION(_hash_map_equal_range__hash_map_equal_range_varg)
void test__hash_map_equal_range__hash_map_equal_range_varg__null_hash_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_map_equal_range(NULL, elem));
}

void test__hash_map_equal_range__hash_map_equal_range_varg__non_inited(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    int elem = 9;
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);

    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_map_equal_range(pt_hash_map, elem));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__non_inited_pair(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(int, int);
    void* pv_tmp = NULL;
    hash_map_init(pt_hash_map);

    pv_tmp = pt_hash_map->_pair_temp._pv_second;
    pt_hash_map->_pair_temp._pv_second = NULL;
    expect_assert_failure(_hash_map_equal_range(pt_hash_map, 3));
    pt_hash_map->_pair_temp._pv_second = pv_tmp;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__c_builtin_equal(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 2;
    r_range = _hash_map_equal_range(pt_hash_map, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)) == 2);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)) == 3);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__c_builtin_greater(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int,int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = -8;
    r_range = _hash_map_equal_range(pt_hash_map, elem);
    assert_true(iterator_equal(r_range.it_begin, hash_map_end(pt_hash_map)));
    assert_true(iterator_equal(r_range.it_end, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__cstr_upper_equal(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    r_range = _hash_map_equal_range(pt_hash_map, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)), "ggg") == 0);
    assert_true(iterator_equal(r_range.it_end, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__cstr_greater(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    r_range = _hash_map_equal_range(pt_hash_map, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, hash_map_end(pt_hash_map)));
    assert_true(iterator_equal(r_range.it_end, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__libcstl_builtin_equal(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _hash_map_equal_range(pt_hash_map, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin))) == 6);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end))) == 7);

    hash_map_destroy(pt_hash_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__libcstl_builtin_greater(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _hash_map_equal_range(pt_hash_map, plist);
    assert_true(iterator_equal(r_range.it_begin, hash_map_end(pt_hash_map)));
    assert_true(iterator_equal(r_range.it_end, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_map_equal_range__hash_map_equal_range_varg__user_define
{
    int n_elem;
}_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t;
void test__hash_map_equal_range__hash_map_equal_range_varg__user_define_equal(void** state)
{
    hash_map_t* pt_hash_map = NULL;
    pair_t* pt_pair = NULL;
    range_t r_range;
    _test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_map = _create_hash_map("_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t, _test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t");
    pt_pair = create_pair(_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t, _test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t);
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 8;
    r_range = _hash_map_equal_range(pt_hash_map, &elem);
    assert_true(((_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)))->n_elem == 8);
    assert_true(((_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)))->n_elem == 9);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_equal_range__hash_map_equal_range_varg__user_define_greater(void** state)
{
    hash_map_t* pt_hash_map =  _create_hash_map("_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t, _test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t, _test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t);
    range_t r_range;
    _test__hash_map_equal_range__hash_map_equal_range_varg__user_define_t elem;
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 7;
    r_range = _hash_map_equal_range(pt_hash_map, &elem);
    assert_true(iterator_equal(r_range.it_begin, hash_map_end(pt_hash_map)));
    assert_true(iterator_equal(r_range.it_end, hash_map_end(pt_hash_map)));

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

/*
 * test _hash_map_at and _hash_map_at_varg
 */
UT_CASE_DEFINATION(_hash_map_at__hash_map_at_varg)
void test__hash_map_at__hash_map_at_varg__null_hash_map(void** state)
{
    expect_assert_failure(_hash_map_at(NULL, 4));
}

void test__hash_map_at__hash_map_at_varg__non_inited(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(int, int);

    hash_map_init(pt_hash_map);
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 555;
    expect_assert_failure(_hash_map_at(pt_hash_map, 3));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_at__hash_map_at_varg__non_inited_pair(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(int, int);
    void* pv_tmp = NULL;

    hash_map_init(pt_hash_map);
    pv_tmp = pt_hash_map->_pair_temp._pv_first;
    pt_hash_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_hash_map_at(pt_hash_map, 5));
    pt_hash_map->_pair_temp._pv_first = pv_tmp;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_at__hash_map_at_varg__c_builtin_exist(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    assert_true(*(int*)_hash_map_at(pt_hash_map, 4) == 4);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_at__hash_map_at_varg__c_builtin_no_exist(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    int i = 0;

    hash_map_init(pt_hash_map);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i * 2, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    assert_true(*(int*)_hash_map_at(pt_hash_map, 3) == 0);
    *(int*)_hash_map_at(pt_hash_map, 3) = 900;
    assert_true(*(int*)_hash_map_at(pt_hash_map, 3) == 900);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_at__hash_map_at_varg__cstr_exist(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);

    pair_init(pt_pair);
    hash_map_init(pt_hash_map);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nnnnn", "ooooo");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "lso", "iso");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(strcmp((char*)_hash_map_at(pt_hash_map, "lso"), "iso") == 0);

    pair_destroy(pt_pair);
    hash_map_destroy(pt_hash_map);
}

void test__hash_map_at__hash_map_at_varg__cstr_no_exist(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);

    pair_init(pt_pair);
    hash_map_init(pt_hash_map);
    pair_make(pt_pair, "aaa", "bbb");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nnnnn", "ooooo");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "lso", "iso");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(strcmp((char*)_hash_map_at(pt_hash_map, "tcpip"), "") == 0);

    pair_destroy(pt_pair);
    hash_map_destroy(pt_hash_map);
}

void test__hash_map_at__hash_map_at_varg__libcstl_builtin_exist(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(*(int*)vector_front((vector_t*)_hash_map_at(pt_hash_map, plist)) == 6);

    hash_map_destroy(pt_hash_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__hash_map_at__hash_map_at_varg__libcstl_builtin_no_exist(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 7);
    assert_true(vector_empty((vector_t*)_hash_map_at(pt_hash_map, plist)));

    hash_map_destroy(pt_hash_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_map_at__hash_map_at_varg__user_define
{
    int n_elem;
}_test__hash_map_at__hash_map_at_varg__user_define_t;
void test__hash_map_at__hash_map_at_varg__user_define_exist(void** state)
{
    hash_map_t* pt_hash_map = NULL;
    pair_t* pt_pair = NULL;
    _test__hash_map_at__hash_map_at_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_map_at__hash_map_at_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_map = _create_hash_map("_test__hash_map_at__hash_map_at_varg__user_define_t, _test__hash_map_at__hash_map_at_varg__user_define_t");
    pt_pair = create_pair(_test__hash_map_at__hash_map_at_varg__user_define_t, _test__hash_map_at__hash_map_at_varg__user_define_t);
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(((_test__hash_map_at__hash_map_at_varg__user_define_t*)_hash_map_at(pt_hash_map, &elem))->n_elem == 8);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_at__hash_map_at_varg__user_define_no_exist(void** state)
{
    hash_map_t* pt_hash_map =  _create_hash_map("_test__hash_map_at__hash_map_at_varg__user_define_t, _test__hash_map_at__hash_map_at_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_map_at__hash_map_at_varg__user_define_t, _test__hash_map_at__hash_map_at_varg__user_define_t);
    _test__hash_map_at__hash_map_at_varg__user_define_t elem;
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 7;
    assert_true(((_test__hash_map_at__hash_map_at_varg__user_define_t*)_hash_map_at(pt_hash_map, &elem))->n_elem == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

/*
 * test _hash_map_erase and _hash_map_erase_varg
 */
UT_CASE_DEFINATION(_hash_map_erase__hash_map_erase_varg)
void test__hash_map_erase__hash_map_erase_varg__null_hash_map(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_map_erase(NULL, elem));
}

void test__hash_map_erase__hash_map_erase_varg__non_inited(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int,int");
    int elem = 9;
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);

    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 4444;
    expect_assert_failure(_hash_map_erase(pt_hash_map, elem));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_erase__hash_map_erase_varg__non_inited_pair(void** state)
{
    hash_map_t* pt_hash_map = create_hash_map(int, int);
    void* pv_tmp = NULL;

    hash_map_init(pt_hash_map);
    pv_tmp = pt_hash_map->_pair_temp._pv_first;
    pt_hash_map->_pair_temp._pv_first = NULL;
    expect_assert_failure(_hash_map_erase(pt_hash_map, 4));
    pt_hash_map->_pair_temp._pv_first = pv_tmp;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_erase__hash_map_erase_varg__c_builtin_0(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 24;
    assert_true(_hash_map_erase(pt_hash_map, elem) == 0);
    assert_true(hash_map_size(pt_hash_map) == 10);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__c_builtin_1(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 8;
    assert_true(_hash_map_erase(pt_hash_map, elem) == 1);
    assert_true(hash_map_size(pt_hash_map) == 9);
    assert_true(_hash_map_count(pt_hash_map, elem) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__c_builtin_n(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem = 8;
    assert_true(_hash_map_erase(pt_hash_map, elem) == 1);
    assert_true(hash_map_size(pt_hash_map) == 9);
    assert_true(_hash_map_count(pt_hash_map, elem) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__cstr_0(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(_hash_map_erase(pt_hash_map, "gggppgg") == 0);
    assert_true(hash_map_size(pt_hash_map) == 5);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__cstr_1(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(_hash_map_erase(pt_hash_map, "ggg") == 1);
    assert_true(hash_map_size(pt_hash_map) == 4);
    assert_true(_hash_map_count(pt_hash_map, "ggg") == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__cstr_n(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_map_insert(pt_hash_map, pt_pair);
    hash_map_insert(pt_hash_map, pt_pair);
    hash_map_insert(pt_hash_map, pt_pair);
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_map_insert(pt_hash_map, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_map_insert(pt_hash_map, pt_pair);

    assert_true(_hash_map_erase(pt_hash_map, "ggg") == 1);
    assert_true(hash_map_size(pt_hash_map) == 4);
    assert_true(_hash_map_count(pt_hash_map, "ggg") == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_0(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_hash_map_erase(pt_hash_map, plist) == 0);
    assert_true(hash_map_size(pt_hash_map) == 10);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_1(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_map_erase(pt_hash_map, plist) == 1);
    assert_true(hash_map_size(pt_hash_map) == 9);
    assert_true(_hash_map_count(pt_hash_map, plist) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_n(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, _test__hash_map_find__libcstl_builtin_hash, NULL);
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
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_map_erase(pt_hash_map, plist) == 1);
    assert_true(hash_map_size(pt_hash_map) == 9);
    assert_true(_hash_map_count(pt_hash_map, plist) == 0);

    hash_map_destroy(pt_hash_map);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_map_erase__hash_map_erase_varg__user_define
{
    int n_elem;
}_test__hash_map_erase__hash_map_erase_varg__user_define_t;
void test__hash_map_erase__hash_map_erase_varg__user_define_0(void** state)
{
    hash_map_t* pt_hash_map = NULL;
    pair_t* pt_pair = NULL;
    _test__hash_map_erase__hash_map_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_map_erase__hash_map_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_map = _create_hash_map("_test__hash_map_erase__hash_map_erase_varg__user_define_t, _test__hash_map_erase__hash_map_erase_varg__user_define_t");
    pt_pair = create_pair(_test__hash_map_erase__hash_map_erase_varg__user_define_t, _test__hash_map_erase__hash_map_erase_varg__user_define_t);
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 86;
    assert_true(_hash_map_erase(pt_hash_map, &elem) == 0);
    assert_true(hash_map_size(pt_hash_map) == 10);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__user_define_1(void** state)
{
    hash_map_t* pt_hash_map =  _create_hash_map("_test__hash_map_erase__hash_map_erase_varg__user_define_t, _test__hash_map_erase__hash_map_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_map_erase__hash_map_erase_varg__user_define_t, _test__hash_map_erase__hash_map_erase_varg__user_define_t);
    _test__hash_map_erase__hash_map_erase_varg__user_define_t elem;
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_map_erase(pt_hash_map, &elem) == 1);
    assert_true(hash_map_size(pt_hash_map) == 9);
    assert_true(_hash_map_count(pt_hash_map, &elem) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_erase__hash_map_erase_varg__user_define_n(void** state)
{
    hash_map_t* pt_hash_map =  _create_hash_map("_test__hash_map_erase__hash_map_erase_varg__user_define_t, _test__hash_map_erase__hash_map_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_map_erase__hash_map_erase_varg__user_define_t, _test__hash_map_erase__hash_map_erase_varg__user_define_t);
    _test__hash_map_erase__hash_map_erase_varg__user_define_t elem;
    int i = 0;

    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
        hash_map_insert(pt_hash_map, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_map_erase(pt_hash_map, &elem) == 1);
    assert_true(hash_map_size(pt_hash_map) == 9);
    assert_true(_hash_map_count(pt_hash_map, &elem) == 0);

    hash_map_destroy(pt_hash_map);
    pair_destroy(pt_pair);
}

/*
 * test _hash_map_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_hash_map_init_elem_auxiliary)
void test__hash_map_init_elem_auxiliary__null_hash_map_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_hash_map_init_elem_auxiliary(NULL, &elem));
}

void test__hash_map_init_elem_auxiliary__null_elem(void** state)
{
    hash_map_t* phash_map = create_hash_map(int,int);

    expect_assert_failure(_hash_map_init_elem_auxiliary(phash_map, NULL));

    hash_map_destroy(phash_map);
}

void test__hash_map_init_elem_auxiliary__non_inited(void** state)
{
    hash_map_t* pt_hash_map = _create_hash_map("int,int");
    int elem = 9;
    hash_map_init_ex(pt_hash_map, 0, NULL, NULL);

    pt_hash_map->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_map_erase(pt_hash_map, elem));
    pt_hash_map->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_map_destroy(pt_hash_map);
}

void test__hash_map_init_elem_auxiliary__successfully_int(void** state)
{
    hash_map_t* phash_map = create_hash_map(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_map_init(phash_map);

    _hash_map_init_elem_auxiliary(phash_map, pt_pair);
    assert_true(*(int*)pair_first(pt_pair) == 0);
    assert_true(*(int*)pair_second(pt_pair) == 0);

    hash_map_destroy(phash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_init_elem_auxiliary__successfully_cstr(void** state)
{
    hash_map_t* phash_map = create_hash_map(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    hash_map_init_ex(phash_map, 0, NULL, NULL);
    /*pair_init(pt_pair);*/

    _hash_map_init_elem_auxiliary(phash_map, pt_pair);
    assert_true(strcmp((char*)pair_first(pt_pair), "") == 0);
    assert_true(strcmp((char*)pair_second(pt_pair), "") == 0);

    hash_map_destroy(phash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    hash_map_t* phash_map = create_hash_map(iterator_t, iterator_t);
    pair_t* pt_pair = create_pair(iterator_t, iterator_t);
    hash_map_init_ex(phash_map, 0, NULL, NULL);
    /*pair_init(pt_pair);*/

    _hash_map_init_elem_auxiliary(phash_map, pt_pair);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp(&it_iter, (iterator_t*)pair_first(pt_pair), sizeof(iterator_t)) == 0);
    assert_true(memcmp(&it_iter, (iterator_t*)pair_second(pt_pair), sizeof(iterator_t)) == 0);

    hash_map_destroy(phash_map);
    pair_destroy(pt_pair);
}

void test__hash_map_init_elem_auxiliary__successfully_container(void** state)
{
    hash_map_t* phash_map = create_hash_map(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);

    _hash_map_init_elem_auxiliary(phash_map, pt_pair);
    assert_true(_vector_is_inited((vector_t*)pair_first(pt_pair)));
    assert_true(_list_is_inited((list_t*)pair_second(pt_pair)));

    hash_map_destroy(phash_map);
    pair_destroy(pt_pair);
}

typedef struct _tag_test__hash_map_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__hash_map_init_elem_auxiliary__successfully_user_defined_t;

void test__hash_map_init_elem_auxiliary__successfully_user_defined(void** state)
{
    hash_map_t* phash_map = NULL;
    pair_t* pt_pair = NULL;

    type_register(_test__hash_map_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    phash_map = create_hash_map(_test__hash_map_init_elem_auxiliary__successfully_user_defined_t, _test__hash_map_init_elem_auxiliary__successfully_user_defined_t);
    pt_pair = create_pair(_test__hash_map_init_elem_auxiliary__successfully_user_defined_t, _test__hash_map_init_elem_auxiliary__successfully_user_defined_t);

    _hash_map_init_elem_auxiliary(phash_map, pt_pair);
    assert_true(((_test__hash_map_init_elem_auxiliary__successfully_user_defined_t*)pair_first(pt_pair))->n_elem == 0);
    assert_true(((_test__hash_map_init_elem_auxiliary__successfully_user_defined_t*)pair_second(pt_pair))->n_elem == 0);

    hash_map_destroy(phash_map);
    pair_destroy(pt_pair);
}

