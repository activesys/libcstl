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
#include "cstl_hash_multimap_aux.h"

#include "ut_def.h"
#include "ut_cstl_hash_multimap_private.h"

UT_SUIT_DEFINATION(cstl_hash_multimap_private, _create_hash_multimap)

/*
 * test _create_hash_multimap
 */
UT_CASE_DEFINATION(_create_hash_multimap)
void test__create_hash_multimap__null_typename(void** state)
{
    expect_assert_failure(_create_hash_multimap(NULL));
}

void test__create_hash_multimap__c_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, double");
    assert_true(pt_hash_multimap != NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

void test__create_hash_multimap__cstr(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    assert_true(pt_hash_multimap != NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

void test__create_hash_multimap__libcstl_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("vector_t<int>, list_t<double>");
    assert_true(pt_hash_multimap != NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

typedef struct _test_test__create_hash_multimap__user_define
{
    int n_elem;
}_test__create_hash_multimap__user_define_t;

void test__create_hash_multimap__user_define(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;

    type_register(_test__create_hash_multimap__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multimap = _create_hash_multimap("_test__create_hash_multimap__user_define_t, _test__create_hash_multimap__user_define_t");
    assert_true(pt_hash_multimap != NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

void test__create_hash_multimap__unregister(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("test__create_hash_multimap__unregister_t, test__create_hash_multimap__unregister_t");
    assert_true(pt_hash_multimap == NULL);
}

/*
 * test _create_hash_multimap_auxiliary
 */
UT_CASE_DEFINATION(_create_hash_multimap_auxiliary)
void test__create_hash_multimap_auxiliary__null_hash_multimap(void** state)
{
    expect_assert_failure(_create_hash_multimap_auxiliary(NULL, "int, int"));
}

void test__create_hash_multimap_auxiliary__null_typename(void** state)
{
    hash_multimap_t t_hash_multimap;
    expect_assert_failure(_create_hash_multimap_auxiliary(&t_hash_multimap, NULL));
}

void test__create_hash_multimap_auxiliary__unregistered(void** state)
{
    hash_multimap_t* pt_hash_multimap = malloc(sizeof(hash_multimap_t));
    assert_false(_create_hash_multimap_auxiliary(pt_hash_multimap, "_test__create_hash_multimap_auxiliary__unregistered_t, _test__create_hash_multimap_auxiliary__unregistered_t"));

    free(pt_hash_multimap);
}

void test__create_hash_multimap_auxiliary__c_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = malloc(sizeof(hash_multimap_t));
    assert_true(_create_hash_multimap_auxiliary(pt_hash_multimap, "int, int"));
    assert_true(pt_hash_multimap != NULL);
    assert_true(_pair_is_created(&pt_hash_multimap->_pair_temp));
    assert_true(pt_hash_multimap->_bfun_keycompare == NULL);
    assert_true(pt_hash_multimap->_bfun_valuecompare == NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

void test__create_hash_multimap_auxiliary__cstr(void** state)
{
    hash_multimap_t* pt_hash_multimap = malloc(sizeof(hash_multimap_t));
    assert_true(_create_hash_multimap_auxiliary(pt_hash_multimap, "char*, char*"));
    assert_true(pt_hash_multimap != NULL);
    assert_true(_pair_is_created(&pt_hash_multimap->_pair_temp));
    assert_true(pt_hash_multimap->_bfun_keycompare == NULL);
    assert_true(pt_hash_multimap->_bfun_valuecompare == NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

void test__create_hash_multimap_auxiliary__libcstl_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = malloc(sizeof(hash_multimap_t));
    assert_true(_create_hash_multimap_auxiliary(pt_hash_multimap, "vector_t<int>, list_t<int>"));
    assert_true(pt_hash_multimap != NULL);
    assert_true(_pair_is_created(&pt_hash_multimap->_pair_temp));
    assert_true(pt_hash_multimap->_bfun_keycompare == NULL);
    assert_true(pt_hash_multimap->_bfun_valuecompare == NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

typedef struct _tag_test__create_hash_multimap_auxiliary__user_define
{
    int n_elem;
}_test__create_hash_multimap_auxiliary__user_define_t;

void test__create_hash_multimap_auxiliary__user_define(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;

    type_register(_test__create_hash_multimap_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multimap = malloc(sizeof(hash_multimap_t));
    assert_true(_create_hash_multimap_auxiliary(pt_hash_multimap, "_test__create_hash_multimap_auxiliary__user_define_t, _test__create_hash_multimap_auxiliary__user_define_t"));
    assert_true(pt_hash_multimap != NULL);
    assert_true(_pair_is_created(&pt_hash_multimap->_pair_temp));
    assert_true(pt_hash_multimap->_bfun_keycompare == NULL);
    assert_true(pt_hash_multimap->_bfun_valuecompare == NULL);

    hash_multimap_destroy(pt_hash_multimap);
}

/*
 * test _hash_multimap_destroy_auxiliary
 */
UT_CASE_DEFINATION(_hash_multimap_destroy_auxiliary)
void test__hash_multimap_destroy_auxiliary__null_hash_multimap(void** state)
{
    expect_assert_failure(_hash_multimap_destroy_auxiliary(NULL));
}

void test__hash_multimap_destroy_auxiliary__non_created(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");

    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = 4444;
    expect_assert_failure(_hash_multimap_destroy_auxiliary(pt_hash_multimap));
    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_destroy_auxiliary__non_inited(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    hash_multimap_init(pt_hash_multimap);

    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = 4444;
    expect_assert_failure(_hash_multimap_destroy_auxiliary(pt_hash_multimap));
    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_destroy_auxiliary__empty(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    hash_multimap_init(pt_hash_multimap);

    _hash_multimap_destroy_auxiliary(pt_hash_multimap);
    assert_true(pt_hash_multimap->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_multimap->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_multimap->_t_hashtable._t_nodecount == 0);
    assert_true(pt_hash_multimap->_pair_temp._pv_first == NULL);
    assert_true(pt_hash_multimap->_pair_temp._pv_second == NULL);
    assert_true(pt_hash_multimap->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_hash_multimap->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_hash_multimap->_bfun_keycompare == NULL);
    assert_true(pt_hash_multimap->_bfun_valuecompare == NULL);
    free(pt_hash_multimap);
}

void test__hash_multimap_destroy_auxiliary__non_empty(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);

    pair_init_elem(pt_pair, 19, 30);
    hash_multimap_init(pt_hash_multimap);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    _hash_multimap_destroy_auxiliary(pt_hash_multimap);
    assert_true(pt_hash_multimap->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_multimap->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_multimap->_t_hashtable._t_nodecount == 0);
    assert_true(pt_hash_multimap->_pair_temp._pv_first == NULL);
    assert_true(pt_hash_multimap->_pair_temp._pv_second == NULL);
    assert_true(pt_hash_multimap->_pair_temp._bfun_mapkeycompare == NULL);
    assert_true(pt_hash_multimap->_pair_temp._bfun_mapvaluecompare == NULL);
    assert_true(pt_hash_multimap->_bfun_keycompare == NULL);
    assert_true(pt_hash_multimap->_bfun_valuecompare == NULL);
    free(pt_hash_multimap);

    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_find and _hash_multimap_find_varg
 */
UT_CASE_DEFINATION(_hash_multimap_find__hash_multimap_find_varg)
void test__hash_multimap_find__hash_multimap_find_varg__null_hash_multimap(void** state)
{
    expect_assert_failure(_hash_multimap_find(NULL, 9));
}

void test__hash_multimap_find__hash_multimap_find_varg__non_inited(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    hash_multimap_init(pt_hash_multimap);

    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_multimap_find(pt_hash_multimap, 9));
    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_find__hash_multimap_find_varg__non_inited_pair(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    void* pv_tmp = NULL;

    hash_multimap_init(pt_hash_multimap);
    pv_tmp = pt_hash_multimap->_pair_temp._pv_first;
    pt_hash_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_hash_multimap_find(pt_hash_multimap, 9));
    pt_hash_multimap->_pair_temp._pv_first = pv_tmp;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_find__hash_multimap_find_varg__c_builtin_find(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem;
    int i;

    pair_init(pt_pair);
    hash_multimap_init(pt_hash_multimap);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+8);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 2;
    it_iter = _hash_multimap_find(pt_hash_multimap, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(it_iter)) == 2);
    assert_true(*(int*)pair_second((pair_t*)iterator_get_pointer(it_iter)) == 10);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_find__hash_multimap_find_varg__c_builtin_not_find(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int i;

    pair_init(pt_pair);
    hash_multimap_init(pt_hash_multimap);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i+5);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    it_iter = _hash_multimap_find(pt_hash_multimap, 42);
    assert_true(iterator_equal(it_iter, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_find__hash_multimap_find_varg__cstr_find(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    hash_multimap_iterator_t it_iter;

    pair_init(pt_pair);
    hash_multimap_init(pt_hash_multimap);
    pair_make(pt_pair, "aaa", "bbb");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_find(pt_hash_multimap, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(it_iter)), "ggg") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)iterator_get_pointer(it_iter)), "fff") == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_find__hash_multimap_find_varg__cstr_not_find(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);
    hash_multimap_iterator_t it_iter;

    pair_init(pt_pair);
    hash_multimap_init(pt_hash_multimap);
    pair_make(pt_pair, "aaa", "bbb");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "nghl");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = _hash_multimap_find(pt_hash_multimap, "vvvvv");
    assert_true(iterator_equal(it_iter, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

static void _test__hash_multimap_find__libcstl_builtin_hash(const void* cpv_input, void* pv_output)
{
    list_t* plist = (list_t*)pair_first((pair_t*)cpv_input);
    list_iterator_t it_iter;
    *(size_t*)pv_output = 0;
    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        *(size_t*)pv_output += *(int*)iterator_get_pointer(it_iter);
    }
}
void test__hash_multimap_find__hash_multimap_find_varg__libcstl_builtin_find(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    hash_multimap_iterator_t it_iter;
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hash_multimap_find(pt_hash_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(it_iter))) == 6);
    assert_true(*(int*)vector_front((vector_t*)pair_second((pair_t*)iterator_get_pointer(it_iter))) == 6);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_multimap_find__hash_multimap_find_varg__libcstl_builtin_not_find(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    hash_multimap_iterator_t it_iter;
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _hash_multimap_find(pt_hash_multimap, plist);
    assert_true(iterator_equal(it_iter, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_multimap_find__hash_multimap_find_varg__user_define
{
    int n_elem;
}_test__hash_multimap_find__hash_multimap_find_varg__user_define_t;
void test__hash_multimap_find__hash_multimap_find_varg__user_define_find(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;
    pair_t* pt_pair = NULL;
    hash_multimap_iterator_t it_iter;
    _test__hash_multimap_find__hash_multimap_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multimap_find__hash_multimap_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multimap = _create_hash_multimap("_test__hash_multimap_find__hash_multimap_find_varg__user_define_t, _test__hash_multimap_find__hash_multimap_find_varg__user_define_t");
    pt_pair = create_pair(_test__hash_multimap_find__hash_multimap_find_varg__user_define_t, _test__hash_multimap_find__hash_multimap_find_varg__user_define_t);
    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 8;
    it_iter = _hash_multimap_find(pt_hash_multimap, &elem);
    assert_true(((_test__hash_multimap_find__hash_multimap_find_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);
    assert_true(((_test__hash_multimap_find__hash_multimap_find_varg__user_define_t*)pair_second((pair_t*)iterator_get_pointer(it_iter)))->n_elem == 8);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_find__hash_multimap_find_varg__user_define_not_find(void** state)
{
    hash_multimap_t* pt_hash_multimap =  _create_hash_multimap("_test__hash_multimap_find__hash_multimap_find_varg__user_define_t, _test__hash_multimap_find__hash_multimap_find_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_multimap_find__hash_multimap_find_varg__user_define_t, _test__hash_multimap_find__hash_multimap_find_varg__user_define_t);
    hash_multimap_iterator_t it_iter;
    _test__hash_multimap_find__hash_multimap_find_varg__user_define_t elem;
    int i = 0;

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 78;
    it_iter = _hash_multimap_find(pt_hash_multimap, &elem);
    assert_true(iterator_equal(it_iter, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_count and _hash_multimap_count_varg
 */
UT_CASE_DEFINATION(_hash_multimap_count__hash_multimap_count_varg)
void test__hash_multimap_count__hash_multimap_count_varg__null_hash_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_multimap_count(NULL, elem));
}

void test__hash_multimap_count__hash_multimap_count_varg__non_inited(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    int elem = 9;
    hash_multimap_init(pt_hash_multimap);

    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_multimap_count(pt_hash_multimap, elem));
    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_count__hash_multimap_count_varg__non_inited_pair(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    void* pv_tmp = NULL;
    int elem = 9;
    hash_multimap_init(pt_hash_multimap);

    pv_tmp = pt_hash_multimap->_pair_temp._pv_first;
    pt_hash_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_hash_multimap_count(pt_hash_multimap, elem));
    pt_hash_multimap->_pair_temp._pv_first = pv_tmp;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_count__hash_multimap_count_varg__c_builtin_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 1222;
    assert_true(_hash_multimap_count(pt_hash_multimap, elem) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__c_builtin_1(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 2;
    assert_true(_hash_multimap_count(pt_hash_multimap, elem) == 1);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__c_builtin_n(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 2;
    assert_true(_hash_multimap_count(pt_hash_multimap, elem) == 2);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__cstr_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    assert_true(_hash_multimap_count(pt_hash_multimap, "uuuu") == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__cstr_1(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    assert_true(_hash_multimap_count(pt_hash_multimap, "ggg") == 1);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__cstr_n(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "fff");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "xxxxx");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    assert_true(_hash_multimap_count(pt_hash_multimap, "ggg") == 4);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__libcstl_builtin_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_hash_multimap_count(pt_hash_multimap, plist) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_multimap_count__hash_multimap_count_varg__libcstl_builtin_1(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multimap_count(pt_hash_multimap, plist) == 1);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_multimap_count__hash_multimap_count_varg__libcstl_builtin_n(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multimap_count(pt_hash_multimap, plist) == 4);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_multimap_count__hash_multimap_count_varg__user_define
{
    int n_elem;
}_test__hash_multimap_count__hash_multimap_count_varg__user_define_t;
void test__hash_multimap_count__hash_multimap_count_varg__user_define_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;
    pair_t* pt_pair = NULL;
    _test__hash_multimap_count__hash_multimap_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multimap_count__hash_multimap_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multimap = _create_hash_multimap("_test__hash_multimap_count__hash_multimap_count_varg__user_define_t, _test__hash_multimap_count__hash_multimap_count_varg__user_define_t");
    pt_pair = create_pair(_test__hash_multimap_count__hash_multimap_count_varg__user_define_t, _test__hash_multimap_count__hash_multimap_count_varg__user_define_t);
    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 88;
    assert_true(_hash_multimap_count(pt_hash_multimap, &elem) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__user_define_1(void** state)
{
    hash_multimap_t* pt_hash_multimap =  _create_hash_multimap("_test__hash_multimap_count__hash_multimap_count_varg__user_define_t, _test__hash_multimap_count__hash_multimap_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_multimap_count__hash_multimap_count_varg__user_define_t, _test__hash_multimap_count__hash_multimap_count_varg__user_define_t);
    _test__hash_multimap_count__hash_multimap_count_varg__user_define_t elem;
    int i = 0;

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_multimap_count(pt_hash_multimap, &elem) == 1);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_count__hash_multimap_count_varg__user_define_n(void** state)
{
    hash_multimap_t* pt_hash_multimap =  _create_hash_multimap("_test__hash_multimap_count__hash_multimap_count_varg__user_define_t, _test__hash_multimap_count__hash_multimap_count_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_multimap_count__hash_multimap_count_varg__user_define_t, _test__hash_multimap_count__hash_multimap_count_varg__user_define_t);
    _test__hash_multimap_count__hash_multimap_count_varg__user_define_t elem;
    int i = 0;

    hash_multimap_init(pt_hash_multimap);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_multimap_count(pt_hash_multimap, &elem) == 4);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_equal_range and _hash_multimap_equal_range_varg
 */
UT_CASE_DEFINATION(_hash_multimap_equal_range__hash_multimap_equal_range_varg)
void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__null_hash_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_multimap_equal_range(NULL, elem));
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__non_inited(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    int elem = 9;
    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);

    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_multimap_equal_range(pt_hash_multimap, elem));
    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__non_inited_pair(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    void* pv_tmp = NULL;
    hash_multimap_init(pt_hash_multimap);

    pv_tmp = pt_hash_multimap->_pair_temp._pv_second;
    pt_hash_multimap->_pair_temp._pv_second = NULL;
    expect_assert_failure(_hash_multimap_equal_range(pt_hash_multimap, 3));
    pt_hash_multimap->_pair_temp._pv_second = pv_tmp;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__c_builtin_equal(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 2;
    r_range = _hash_multimap_equal_range(pt_hash_multimap, elem);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)) == 2);
    assert_true(*(int*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)) == 3);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__c_builtin_greater(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int,int");
    pair_t* pt_pair = create_pair(int, int);
    range_t r_range;
    int elem;
    int i;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = -8;
    r_range = _hash_multimap_equal_range(pt_hash_multimap, elem);
    assert_true(iterator_equal(r_range.it_begin, hash_multimap_end(pt_hash_multimap)));
    assert_true(iterator_equal(r_range.it_end, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__cstr_upper_equal(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    r_range = _hash_multimap_equal_range(pt_hash_multimap, "ggg");
    assert_true(strcmp((char*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)), "ggg") == 0);
    assert_true(iterator_equal(r_range.it_end, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__cstr_greater(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*,char*");
    pair_t* pt_pair = create_pair(char*,      char*);
    range_t r_range;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "bbb");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "slskf");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    r_range = _hash_multimap_equal_range(pt_hash_multimap, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, hash_multimap_end(pt_hash_multimap)));
    assert_true(iterator_equal(r_range.it_end, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__libcstl_builtin_equal(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _hash_multimap_equal_range(pt_hash_multimap, plist);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin))) == 6);
    assert_true(*(int*)list_front((list_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end))) == 7);

    hash_multimap_destroy(pt_hash_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__libcstl_builtin_greater(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    range_t r_range;
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _hash_multimap_equal_range(pt_hash_multimap, plist);
    assert_true(iterator_equal(r_range.it_begin, hash_multimap_end(pt_hash_multimap)));
    assert_true(iterator_equal(r_range.it_end, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define
{
    int n_elem;
}_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t;
void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_equal(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;
    pair_t* pt_pair = NULL;
    range_t r_range;
    _test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multimap = _create_hash_multimap("_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t, _test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t");
    pt_pair = create_pair(_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t, _test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t);
    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 8;
    r_range = _hash_multimap_equal_range(pt_hash_multimap, &elem);
    assert_true(((_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_begin)))->n_elem == 8);
    assert_true(((_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t*)pair_first((pair_t*)iterator_get_pointer(r_range.it_end)))->n_elem == 9);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_greater(void** state)
{
    hash_multimap_t* pt_hash_multimap =  _create_hash_multimap("_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t, _test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t, _test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t);
    range_t r_range;
    _test__hash_multimap_equal_range__hash_multimap_equal_range_varg__user_define_t elem;
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 7;
    r_range = _hash_multimap_equal_range(pt_hash_multimap, &elem);
    assert_true(iterator_equal(r_range.it_begin, hash_multimap_end(pt_hash_multimap)));
    assert_true(iterator_equal(r_range.it_end, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_erase and _hash_multimap_erase_varg
 */
UT_CASE_DEFINATION(_hash_multimap_erase__hash_multimap_erase_varg)
void test__hash_multimap_erase__hash_multimap_erase_varg__null_hash_multimap(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_multimap_erase(NULL, elem));
}

void test__hash_multimap_erase__hash_multimap_erase_varg__non_inited(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int,int");
    int elem = 9;
    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);

    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = 4444;
    expect_assert_failure(_hash_multimap_erase(pt_hash_multimap, elem));
    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__non_inited_pair(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    void* pv_tmp = NULL;

    hash_multimap_init(pt_hash_multimap);
    pv_tmp = pt_hash_multimap->_pair_temp._pv_first;
    pt_hash_multimap->_pair_temp._pv_first = NULL;
    expect_assert_failure(_hash_multimap_erase(pt_hash_multimap, 4));
    pt_hash_multimap->_pair_temp._pv_first = pv_tmp;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__c_builtin_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 24;
    assert_true(_hash_multimap_erase(pt_hash_multimap, elem) == 0);
    assert_true(hash_multimap_size(pt_hash_multimap) == 10);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__c_builtin_1(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 8;
    assert_true(_hash_multimap_erase(pt_hash_multimap, elem) == 1);
    assert_true(hash_multimap_size(pt_hash_multimap) == 9);
    assert_true(_hash_multimap_count(pt_hash_multimap, elem) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__c_builtin_n(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int, int");
    pair_t* pt_pair = create_pair(int, int);
    int elem;
    int i;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    for(i = 0; i < 10; ++i)
    {
        pair_make(pt_pair, i, i);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem = 8;
    assert_true(_hash_multimap_erase(pt_hash_multimap, elem) == 3);
    assert_true(hash_multimap_size(pt_hash_multimap) == 27);
    assert_true(_hash_multimap_count(pt_hash_multimap, elem) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__cstr_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    assert_true(_hash_multimap_erase(pt_hash_multimap, "gggppgg") == 0);
    assert_true(hash_multimap_size(pt_hash_multimap) == 5);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__cstr_1(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    assert_true(_hash_multimap_erase(pt_hash_multimap, "ggg") == 1);
    assert_true(hash_multimap_size(pt_hash_multimap) == 4);
    assert_true(_hash_multimap_count(pt_hash_multimap, "ggg") == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__cstr_n(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("char*, char*");
    pair_t* pt_pair = create_pair(char*, char*);

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);
    pair_make(pt_pair, "aaa", "ccc");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "ggg", "ggg");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "nghl", "lhgn");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "asery", "yresa");
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    pair_make(pt_pair, "linux", "windows");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    assert_true(_hash_multimap_erase(pt_hash_multimap, "ggg") == 4);
    assert_true(hash_multimap_size(pt_hash_multimap) == 4);
    assert_true(_hash_multimap_count(pt_hash_multimap, "ggg") == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__libcstl_builtin_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_hash_multimap_erase(pt_hash_multimap, plist) == 0);
    assert_true(hash_multimap_size(pt_hash_multimap) == 10);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__libcstl_builtin_1(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multimap_erase(pt_hash_multimap, plist) == 1);
    assert_true(hash_multimap_size(pt_hash_multimap) == 9);
    assert_true(_hash_multimap_count(pt_hash_multimap, plist) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    list_destroy(plist);
    vector_destroy(pvec);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__libcstl_builtin_n(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("list_t<int>, vector_t<int>");
    pair_t* pt_pair = create_pair(list_t<int>, vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, _test__hash_multimap_find__libcstl_builtin_hash, NULL);
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
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multimap_erase(pt_hash_multimap, plist) == 3);
    assert_true(hash_multimap_size(pt_hash_multimap) == 27);
    assert_true(_hash_multimap_count(pt_hash_multimap, plist) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    list_destroy(plist);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_multimap_erase__hash_multimap_erase_varg__user_define
{
    int n_elem;
}_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t;
void test__hash_multimap_erase__hash_multimap_erase_varg__user_define_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;
    pair_t* pt_pair = NULL;
    _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multimap = _create_hash_multimap("_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t, _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t");
    pt_pair = create_pair(_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t, _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t);
    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 86;
    assert_true(_hash_multimap_erase(pt_hash_multimap, &elem) == 0);
    assert_true(hash_multimap_size(pt_hash_multimap) == 10);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__user_define_1(void** state)
{
    hash_multimap_t* pt_hash_multimap =  _create_hash_multimap("_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t, _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t, _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t);
    _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t elem;
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_multimap_erase(pt_hash_multimap, &elem) == 1);
    assert_true(hash_multimap_size(pt_hash_multimap) == 9);
    assert_true(_hash_multimap_count(pt_hash_multimap, &elem) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_erase__hash_multimap_erase_varg__user_define_n(void** state)
{
    hash_multimap_t* pt_hash_multimap =  _create_hash_multimap("_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t, _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t");
    pair_t* pt_pair = create_pair(_test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t, _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t);
    _test__hash_multimap_erase__hash_multimap_erase_varg__user_define_t elem;
    int i = 0;

    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);
    pair_init(pt_pair);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        pair_make(pt_pair, &elem, &elem);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
        hash_multimap_insert(pt_hash_multimap, pt_pair);
    }

    elem.n_elem = 8;
    assert_true(_hash_multimap_erase(pt_hash_multimap, &elem) == 3);
    assert_true(hash_multimap_size(pt_hash_multimap) == 27);
    assert_true(_hash_multimap_count(pt_hash_multimap, &elem) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_hash_multimap_init_elem_auxiliary)
void test__hash_multimap_init_elem_auxiliary__null_hash_multimap_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_hash_multimap_init_elem_auxiliary(NULL, &elem));
}

void test__hash_multimap_init_elem_auxiliary__null_elem(void** state)
{
    hash_multimap_t* phash_multimap = create_hash_multimap(int,int);

    expect_assert_failure(_hash_multimap_init_elem_auxiliary(phash_multimap, NULL));

    hash_multimap_destroy(phash_multimap);
}

void test__hash_multimap_init_elem_auxiliary__non_inited(void** state)
{
    hash_multimap_t* pt_hash_multimap = _create_hash_multimap("int,int");
    int elem = 9;
    hash_multimap_init_ex(pt_hash_multimap, 0, NULL, NULL);

    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_multimap_erase(pt_hash_multimap, elem));
    pt_hash_multimap->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_init_elem_auxiliary__successfully_int(void** state)
{
    hash_multimap_t* phash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_init(phash_multimap);

    _hash_multimap_init_elem_auxiliary(phash_multimap, pt_pair);
    assert_true(*(int*)pair_first(pt_pair) == 0);
    assert_true(*(int*)pair_second(pt_pair) == 0);

    hash_multimap_destroy(phash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_init_elem_auxiliary__successfully_cstr(void** state)
{
    hash_multimap_t* phash_multimap = create_hash_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    hash_multimap_init_ex(phash_multimap, 0, NULL, NULL);
    /*pair_init(pt_pair);*/

    _hash_multimap_init_elem_auxiliary(phash_multimap, pt_pair);
    assert_true(strcmp((char*)pair_first(pt_pair), "") == 0);
    assert_true(strcmp((char*)pair_second(pt_pair), "") == 0);

    hash_multimap_destroy(phash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    hash_multimap_t* phash_multimap = create_hash_multimap(iterator_t, iterator_t);
    pair_t* pt_pair = create_pair(iterator_t, iterator_t);
    hash_multimap_init_ex(phash_multimap, 0, NULL, NULL);
    /*pair_init(pt_pair);*/

    _hash_multimap_init_elem_auxiliary(phash_multimap, pt_pair);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp(&it_iter, (iterator_t*)pair_first(pt_pair), sizeof(iterator_t)) == 0);
    assert_true(memcmp(&it_iter, (iterator_t*)pair_second(pt_pair), sizeof(iterator_t)) == 0);

    hash_multimap_destroy(phash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_init_elem_auxiliary__successfully_container(void** state)
{
    hash_multimap_t* phash_multimap = create_hash_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);

    _hash_multimap_init_elem_auxiliary(phash_multimap, pt_pair);
    assert_true(_vector_is_inited((vector_t*)pair_first(pt_pair)));
    assert_true(_list_is_inited((list_t*)pair_second(pt_pair)));

    hash_multimap_destroy(phash_multimap);
    pair_destroy(pt_pair);
}

typedef struct _tag_test__hash_multimap_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t;

void test__hash_multimap_init_elem_auxiliary__successfully_user_defined(void** state)
{
    hash_multimap_t* phash_multimap = NULL;
    pair_t* pt_pair = NULL;

    type_register(_test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    phash_multimap = create_hash_multimap(_test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t, _test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t);
    pt_pair = create_pair(_test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t, _test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t);

    _hash_multimap_init_elem_auxiliary(phash_multimap, pt_pair);
    assert_true(((_test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t*)pair_first(pt_pair))->n_elem == 0);
    assert_true(((_test__hash_multimap_init_elem_auxiliary__successfully_user_defined_t*)pair_second(pt_pair))->n_elem == 0);

    hash_multimap_destroy(phash_multimap);
    pair_destroy(pt_pair);
}

