#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/chash_set.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_hash_set_aux.h"

#include "ut_def.h"
#include "ut_cstl_hash_set_private.h"

UT_SUIT_DEFINATION(cstl_hash_set_private, _create_hash_set)

/*
 * test _create_hash_set
 */
UT_CASE_DEFINATION(_create_hash_set)
void test__create_hash_set__null_typename(void** state)
{
    expect_assert_failure(_create_hash_set(NULL));
}

void test__create_hash_set__c_builtin(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("double");
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

void test__create_hash_set__cstr(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

void test__create_hash_set__libcstl_builtin(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("vector_t<int>");
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

typedef struct _test_test__create_hash_set__user_define
{
    int n_elem;
}_test__create_hash_set__user_define_t;

void test__create_hash_set__user_define(void** state)
{
    hash_set_t* pt_hash_set = NULL;

    type_register(_test__create_hash_set__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_set = _create_hash_set("_test__create_hash_set__user_define_t");
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

void test__create_hash_set__unregister(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("test__create_hash_set__unregister_t");
    assert_true(pt_hash_set == NULL);
}

/*
 * test _create_hash_set_auxiliary
 */
UT_CASE_DEFINATION(_create_hash_set_auxiliary)
void test__create_hash_set_auxiliary__null_hash_set(void** state)
{
    expect_assert_failure(_create_hash_set_auxiliary(NULL, "int"));
}

void test__create_hash_set_auxiliary__null_typename(void** state)
{
    hash_set_t hash_set;
    expect_assert_failure(_create_hash_set_auxiliary(&hash_set, NULL));
}

void test__create_hash_set_auxiliary__unregistered(void** state)
{
    hash_set_t* pt_hash_set = malloc(sizeof(hash_set_t));
    assert_false(_create_hash_set_auxiliary(pt_hash_set, "_test__create_hash_set_auxiliary__unregistered_t"));

    free(pt_hash_set);
}

void test__create_hash_set_auxiliary__c_builtin(void** state)
{
    hash_set_t* pt_hash_set = malloc(sizeof(hash_set_t));
    assert_true(_create_hash_set_auxiliary(pt_hash_set, "int"));
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

void test__create_hash_set_auxiliary__cstr(void** state)
{
    hash_set_t* pt_hash_set = malloc(sizeof(hash_set_t));
    assert_true(_create_hash_set_auxiliary(pt_hash_set, "char*"));
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

void test__create_hash_set_auxiliary__libcstl_builtin(void** state)
{
    hash_set_t* pt_hash_set = malloc(sizeof(hash_set_t));
    assert_true(_create_hash_set_auxiliary(pt_hash_set, "vector_t<int>"));
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

typedef struct _tag_test__create_hash_set_auxiliary__user_define
{
    int n_elem;
}_test__create_hash_set_auxiliary__user_define_t;

void test__create_hash_set_auxiliary__user_define(void** state)
{
    hash_set_t* pt_hash_set = NULL;

    type_register(_test__create_hash_set_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_set = malloc(sizeof(hash_set_t));
    assert_true(_create_hash_set_auxiliary(pt_hash_set, "_test__create_hash_set_auxiliary__user_define_t"));
    assert_true(pt_hash_set != NULL);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_destroy_auxiliary
 */
UT_CASE_DEFINATION(_hash_set_destroy_auxiliary)
void test__hash_set_destroy_auxiliary__null_hash_set(void** state)
{
    expect_assert_failure(_hash_set_destroy_auxiliary(NULL));
}

void test__hash_set_destroy_auxiliary__non_created(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");

    pt_hash_set->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_set_destroy_auxiliary(pt_hash_set));
    pt_hash_set->_t_hashtable._t_typeinfo._t_style = _TYPE_CSTL_BUILTIN;

    hash_set_destroy(pt_hash_set);
}

/*
void test__hash_set_destroy_auxiliary__non_inited(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");

    expect_assert_failure(_hash_set_destroy_auxiliary(pt_hash_set));

    hash_set_destroy(pt_hash_set);
}
*/

void test__hash_set_destroy_auxiliary__empty(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    hash_set_init_ex(pt_hash_set, 0, NULL, NULL);

    _hash_set_destroy_auxiliary(pt_hash_set);
    assert_true(pt_hash_set->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_set->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_set->_t_hashtable._t_nodecount == 0);
    free(pt_hash_set);
}

void test__hash_set_destroy_auxiliary__non_empty(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    int elem = 9;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);

    _hash_set_destroy_auxiliary(pt_hash_set);
    assert_true(pt_hash_set->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_set->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_set->_t_hashtable._t_nodecount == 0);
    free(pt_hash_set);
}

/*
 * test _hash_set_find and _hash_set_find_varg
 */
UT_CASE_DEFINATION(_hash_set_find__hash_set_find_varg)
void test__hash_set_find__hash_set_find_varg__null_hash_set(void** state)
{
    expect_assert_failure(_hash_set_find(NULL, 9));
}

void test__hash_set_find__hash_set_find_varg__non_inited(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    unary_function_t ufun_hash = NULL;

    hash_set_init(pt_hash_set);
    ufun_hash = pt_hash_set->_t_hashtable._ufun_hash;
    pt_hash_set->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_set_find(pt_hash_set, 9));
    pt_hash_set->_t_hashtable._ufun_hash = ufun_hash;

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_find__hash_set_find_varg__c_builtin_find(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    hash_set_iterator_t it_iter;
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    elem = 2;
    it_iter = _hash_set_find(pt_hash_set, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_find__hash_set_find_varg__c_builtin_not_find(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    hash_set_iterator_t it_iter;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    it_iter = _hash_set_find(pt_hash_set, 42);
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_find__hash_set_find_varg__cstr_find(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");
    hash_set_iterator_t it_iter;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    it_iter = hash_set_find(pt_hash_set, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "ggg") == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_find__hash_set_find_varg__cstr_not_find(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");
    hash_set_iterator_t it_iter;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    it_iter = _hash_set_find(pt_hash_set, "vvvvv");
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

static void _test__hash_private__libcstl_builtin_hash(const void* cpv_input, void* pv_output)
{
    list_t* plist = (list_t*)cpv_input;
    list_iterator_t it_iter;
    *(size_t*)pv_output = 0;
    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        *(size_t*)pv_output += *(int*)iterator_get_pointer(it_iter);
    }
}
void test__hash_set_find__hash_set_find_varg__libcstl_builtin_find(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    hash_set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hash_set_find(pt_hash_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

void test__hash_set_find__hash_set_find_varg__libcstl_builtin_not_find(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    hash_set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _hash_set_find(pt_hash_set, plist);
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

typedef struct _tag_test__hash_set_find__hash_set_find_varg__user_define
{
    int n_elem;
}_test__hash_set_find__hash_set_find_varg__user_define_t;
void test__hash_set_find__hash_set_find_varg__user_define_find(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    hash_set_iterator_t it_iter;
    _test__hash_set_find__hash_set_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_set_find__hash_set_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_set = _create_hash_set("_test__hash_set_find__hash_set_find_varg__user_define_t");
    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 8;
    it_iter = _hash_set_find(pt_hash_set, &elem);
    assert_true(((_test__hash_set_find__hash_set_find_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_find__hash_set_find_varg__user_define_not_find(void** state)
{
    hash_set_t* pt_hash_set =  _create_hash_set("_test__hash_set_find__hash_set_find_varg__user_define_t");
    hash_set_iterator_t it_iter;
    _test__hash_set_find__hash_set_find_varg__user_define_t elem;
    int i = 0;

    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 78;
    it_iter = _hash_set_find(pt_hash_set, &elem);
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_count and _hash_set_count_varg
 */
UT_CASE_DEFINATION(_hash_set_count__hash_set_count_varg)
void test__hash_set_count__hash_set_count_varg__null_hash_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_set_count(NULL, elem));
}

void test__hash_set_count__hash_set_count_varg__non_inited(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_set_init(pt_hash_set);

    ufun_hash = pt_hash_set->_t_hashtable._ufun_hash;
    pt_hash_set->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_set_count(pt_hash_set, elem));
    pt_hash_set->_t_hashtable._ufun_hash = ufun_hash;

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__c_builtin_0(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    elem = 1222;
    assert_true(_hash_set_count(pt_hash_set, elem) == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__c_builtin_1(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    elem = 2;
    assert_true(_hash_set_count(pt_hash_set, elem) == 1);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__c_builtin_n(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
        hash_set_insert(pt_hash_set, i);
        hash_set_insert(pt_hash_set, i);
    }

    elem = 2;
    assert_true(_hash_set_count(pt_hash_set, elem) == 1);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__cstr_0(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    assert_true(_hash_set_count(pt_hash_set, "uuuu") == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__cstr_1(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    assert_true(_hash_set_count(pt_hash_set, "ggg") == 1);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__cstr_n(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    assert_true(_hash_set_count(pt_hash_set, "ggg") == 1);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__libcstl_builtin_0(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_hash_set_count(pt_hash_set, plist) == 0);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

void test__hash_set_count__hash_set_count_varg__libcstl_builtin_1(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_set_count(pt_hash_set, plist) == 1);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

void test__hash_set_count__hash_set_count_varg__libcstl_builtin_n(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
        hash_set_insert(pt_hash_set, plist);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_set_count(pt_hash_set, plist) == 1);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

typedef struct _tag_test__hash_set_count__hash_set_count_varg__user_define
{
    int n_elem;
}_test__hash_set_count__hash_set_count_varg__user_define_t;
void test__hash_set_count__hash_set_count_varg__user_define_0(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    _test__hash_set_count__hash_set_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_set_count__hash_set_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_set = _create_hash_set("_test__hash_set_count__hash_set_count_varg__user_define_t");
    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 88;
    assert_true(_hash_set_count(pt_hash_set, &elem) == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__user_define_1(void** state)
{
    hash_set_t* pt_hash_set =  _create_hash_set("_test__hash_set_count__hash_set_count_varg__user_define_t");
    _test__hash_set_count__hash_set_count_varg__user_define_t elem;
    int i = 0;

    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_set_count(pt_hash_set, &elem) == 1);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_count__hash_set_count_varg__user_define_n(void** state)
{
    hash_set_t* pt_hash_set =  _create_hash_set("_test__hash_set_count__hash_set_count_varg__user_define_t");
    _test__hash_set_count__hash_set_count_varg__user_define_t elem;
    int i = 0;

    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_set_insert(pt_hash_set, &elem);
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_set_count(pt_hash_set, &elem) == 1);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_equal_range and _hash_set_equal_range_varg
 */
UT_CASE_DEFINATION(_hash_set_equal_range__hash_set_equal_range_varg)
void test__hash_set_equal_range__hash_set_equal_range_varg__null_hash_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_set_equal_range(NULL, elem));
}

void test__hash_set_equal_range__hash_set_equal_range_varg__non_inited(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_set_init(pt_hash_set);

    ufun_hash = pt_hash_set->_t_hashtable._ufun_hash;
    pt_hash_set->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_set_equal_range(pt_hash_set, elem));
    pt_hash_set->_t_hashtable._ufun_hash = ufun_hash;

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_equal_range__hash_set_equal_range_varg__c_builtin_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    range_t r_range;
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    elem = 2;
    r_range = _hash_set_equal_range(pt_hash_set, elem);
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 2);
    assert_true(*(int*)iterator_get_pointer(r_range.it_end) == 3);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_equal_range__hash_set_equal_range_varg__c_builtin_greater(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    range_t r_range;
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    elem = -8;
    r_range = _hash_set_equal_range(pt_hash_set, elem);
    assert_true(iterator_equal(r_range.it_begin, hash_set_end(pt_hash_set)));
    assert_true(iterator_equal(r_range.it_end, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_equal_range__hash_set_equal_range_varg__cstr_upper_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");
    range_t r_range;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    r_range = _hash_set_equal_range(pt_hash_set, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_begin), "ggg") == 0);
    assert_true(iterator_equal(r_range.it_end, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_equal_range__hash_set_equal_range_varg__cstr_greater(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");
    range_t r_range;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    r_range = _hash_set_equal_range(pt_hash_set, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, hash_set_end(pt_hash_set)));
    assert_true(iterator_equal(r_range.it_end, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_equal_range__hash_set_equal_range_varg__libcstl_builtin_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _hash_set_equal_range(pt_hash_set, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 7);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

void test__hash_set_equal_range__hash_set_equal_range_varg__libcstl_builtin_greater(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _hash_set_equal_range(pt_hash_set, plist);
    assert_true(iterator_equal(r_range.it_begin, hash_set_end(pt_hash_set)));
    assert_true(iterator_equal(r_range.it_end, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

typedef struct _tag_test__hash_set_equal_range__hash_set_equal_range_varg__user_define
{
    int n_elem;
}_test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t;
void test__hash_set_equal_range__hash_set_equal_range_varg__user_define_equal(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    range_t r_range;
    _test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_set = _create_hash_set("_test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t");
    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 8;
    r_range = _hash_set_equal_range(pt_hash_set, &elem);
    assert_true(((_test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 9);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_equal_range__hash_set_equal_range_varg__user_define_greater(void** state)
{
    hash_set_t* pt_hash_set =  _create_hash_set("_test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t");
    range_t r_range;
    _test__hash_set_equal_range__hash_set_equal_range_varg__user_define_t elem;
    int i = 0;

    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 7;
    r_range = _hash_set_equal_range(pt_hash_set, &elem);
    assert_true(iterator_equal(r_range.it_begin, hash_set_end(pt_hash_set)));
    assert_true(iterator_equal(r_range.it_end, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_erase and _hash_set_erase_varg
 */
UT_CASE_DEFINATION(_hash_set_erase__hash_set_erase_varg)
void test__hash_set_erase__hash_set_erase_varg__null_hash_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_set_erase(NULL, elem));
}

void test__hash_set_erase__hash_set_erase_varg__non_inited(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_set_init(pt_hash_set);

    ufun_hash = pt_hash_set->_t_hashtable._ufun_hash;
    pt_hash_set->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_set_erase(pt_hash_set, elem));
    pt_hash_set->_t_hashtable._ufun_hash = ufun_hash;

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__c_builtin_0(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    elem = 24;
    assert_true(_hash_set_erase(pt_hash_set, elem) == 0);
    assert_true(hash_set_size(pt_hash_set) == 10);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__c_builtin_1(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
    }

    elem = 8;
    assert_true(_hash_set_erase(pt_hash_set, elem) == 1);
    assert_true(hash_set_size(pt_hash_set) == 9);
    assert_true(_hash_set_count(pt_hash_set, elem) == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__c_builtin_n(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        hash_set_insert(pt_hash_set, i);
        hash_set_insert(pt_hash_set, i);
        hash_set_insert(pt_hash_set, i);
    }

    elem = 8;
    assert_true(_hash_set_erase(pt_hash_set, elem) == 1);
    assert_true(hash_set_size(pt_hash_set) == 9);
    assert_true(_hash_set_count(pt_hash_set, elem) == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__cstr_0(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    assert_true(_hash_set_erase(pt_hash_set, "gggppgg") == 0);
    assert_true(hash_set_size(pt_hash_set) == 5);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__cstr_1(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    assert_true(_hash_set_erase(pt_hash_set, "ggg") == 1);
    assert_true(hash_set_size(pt_hash_set) == 4);
    assert_true(_hash_set_count(pt_hash_set, "ggg") == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__cstr_n(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "aaa");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "ggg");
    hash_set_insert(pt_hash_set, "nghl");
    hash_set_insert(pt_hash_set, "asery");
    hash_set_insert(pt_hash_set, "linux");

    assert_true(_hash_set_erase(pt_hash_set, "ggg") == 1);
    assert_true(hash_set_size(pt_hash_set) == 4);
    assert_true(_hash_set_count(pt_hash_set, "ggg") == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__libcstl_builtin_0(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_hash_set_erase(pt_hash_set, plist) == 0);
    assert_true(hash_set_size(pt_hash_set) == 10);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

void test__hash_set_erase__hash_set_erase_varg__libcstl_builtin_1(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_set_erase(pt_hash_set, plist) == 1);
    assert_true(hash_set_size(pt_hash_set) == 9);
    assert_true(_hash_set_count(pt_hash_set, plist) == 0);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

void test__hash_set_erase__hash_set_erase_varg__libcstl_builtin_n(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_set_insert(pt_hash_set, plist);
        hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_set_erase(pt_hash_set, plist) == 1);
    assert_true(hash_set_size(pt_hash_set) == 9);
    assert_true(_hash_set_count(pt_hash_set, plist) == 0);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

typedef struct _tag_test__hash_set_erase__hash_set_erase_varg__user_define
{
    int n_elem;
}_test__hash_set_erase__hash_set_erase_varg__user_define_t;
void test__hash_set_erase__hash_set_erase_varg__user_define_0(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    _test__hash_set_erase__hash_set_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_set_erase__hash_set_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_set = _create_hash_set("_test__hash_set_erase__hash_set_erase_varg__user_define_t");
    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 86;
    assert_true(_hash_set_erase(pt_hash_set, &elem) == 0);
    assert_true(hash_set_size(pt_hash_set) == 10);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__user_define_1(void** state)
{
    hash_set_t* pt_hash_set =  _create_hash_set("_test__hash_set_erase__hash_set_erase_varg__user_define_t");
    _test__hash_set_erase__hash_set_erase_varg__user_define_t elem;
    int i = 0;

    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_set_erase(pt_hash_set, &elem) == 1);
    assert_true(hash_set_size(pt_hash_set) == 9);
    assert_true(_hash_set_count(pt_hash_set, &elem) == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_erase__hash_set_erase_varg__user_define_n(void** state)
{
    hash_set_t* pt_hash_set =  _create_hash_set("_test__hash_set_erase__hash_set_erase_varg__user_define_t");
    _test__hash_set_erase__hash_set_erase_varg__user_define_t elem;
    int i = 0;

    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        hash_set_insert(pt_hash_set, &elem);
        hash_set_insert(pt_hash_set, &elem);
        hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_set_erase(pt_hash_set, &elem) == 1);
    assert_true(hash_set_size(pt_hash_set) == 9);
    assert_true(_hash_set_count(pt_hash_set, &elem) == 0);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_insert and _hash_set_insert_varg
 */
UT_CASE_DEFINATION(_hash_set_insert__hash_set_insert_varg)
void test__hash_set_insert_varg__null_hash_set(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_set_insert(NULL, elem));
}

void test__hash_set_insert_varg__non_inited(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_set_init(pt_hash_set);

    ufun_hash = pt_hash_set->_t_hashtable._ufun_hash;
    pt_hash_set->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_set_insert(pt_hash_set, elem));
    pt_hash_set->_t_hashtable._ufun_hash = ufun_hash;

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_insert_varg__c_builtin_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    hash_set_iterator_t it_iter;
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        _hash_set_insert(pt_hash_set, i);
    }

    elem = 2;
    it_iter = _hash_set_insert(pt_hash_set, elem);
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));
    assert_true(hash_set_size(pt_hash_set) == 10);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_insert_varg__c_builtin_not_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("int");
    hash_set_iterator_t it_iter;
    int elem;
    int i;

    hash_set_init(pt_hash_set);
    for(i = 0; i < 10; ++i)
    {
        _hash_set_insert(pt_hash_set, i);
    }

    elem = -8;
    it_iter = _hash_set_insert(pt_hash_set, elem);
    assert_true(*(int*)_hash_set_iterator_get_pointer(it_iter) == -8);
    assert_true(hash_set_size(pt_hash_set) == 11);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_insert_varg__cstr_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");
    hash_set_iterator_t it_iter;

    hash_set_init(pt_hash_set);
    _hash_set_insert(pt_hash_set, "aaa");
    _hash_set_insert(pt_hash_set, "ggg");
    _hash_set_insert(pt_hash_set, "nghl");
    _hash_set_insert(pt_hash_set, "asery");
    _hash_set_insert(pt_hash_set, "linux");

    it_iter = _hash_set_insert(pt_hash_set, "ggg");
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));
    assert_true(hash_set_size(pt_hash_set) == 5);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_insert_varg__cstr_not_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("char*");
    hash_set_iterator_t it_iter;

    hash_set_init(pt_hash_set);
    _hash_set_insert(pt_hash_set, "aaa");
    _hash_set_insert(pt_hash_set, "ggg");
    _hash_set_insert(pt_hash_set, "nghl");
    _hash_set_insert(pt_hash_set, "asery");
    _hash_set_insert(pt_hash_set, "linux");

    it_iter = _hash_set_insert(pt_hash_set, "vvvv");
    assert_true(strcmp((char*)_hash_set_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(hash_set_size(pt_hash_set) == 6);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_insert_varg__libcstl_builtin_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    hash_set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hash_set_insert(pt_hash_set, plist);
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));
    assert_true(hash_set_size(pt_hash_set) == 10);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

void test__hash_set_insert_varg__libcstl_builtin_not_equal(void** state)
{
    hash_set_t* pt_hash_set = _create_hash_set("list_t<int>");
    hash_set_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_set_init_ex(pt_hash_set, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _hash_set_insert(pt_hash_set, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _hash_set_insert(pt_hash_set, plist);
    assert_true(*(int*)list_front((list_t*)_hash_set_iterator_get_pointer(it_iter)) == 5);
    assert_true(hash_set_size(pt_hash_set) == 11);

    hash_set_destroy(pt_hash_set);
    list_destroy(plist);
}

typedef struct _tag_test__hash_set_insert_varg__user_define
{
    int n_elem;
}_test__hash_set_insert_varg__user_define_t;
void test__hash_set_insert_varg__user_define_equal(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    hash_set_iterator_t it_iter;
    _test__hash_set_insert_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_set_insert_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_set = _create_hash_set("_test__hash_set_insert_varg__user_define_t");
    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 8;
    it_iter = _hash_set_insert(pt_hash_set, &elem);
    assert_true(iterator_equal(it_iter, hash_set_end(pt_hash_set)));
    assert_true(hash_set_size(pt_hash_set) == 10);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_insert_varg__user_define_not_equal(void** state)
{
    hash_set_t* pt_hash_set =  _create_hash_set("_test__hash_set_insert_varg__user_define_t");
    hash_set_iterator_t it_iter;
    _test__hash_set_insert_varg__user_define_t elem;
    int i = 0;

    hash_set_init(pt_hash_set);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _hash_set_insert(pt_hash_set, &elem);
    }

    elem.n_elem = 7;
    it_iter = _hash_set_insert(pt_hash_set, &elem);
    assert_true(((_test__hash_set_insert_varg__user_define_t*)_hash_set_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(hash_set_size(pt_hash_set) == 11);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_hash_set_init_elem_auxiliary)
void test__hash_set_init_elem_auxiliary__null_hash_set_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_hash_set_init_elem_auxiliary(NULL, &elem));
}

void test__hash_set_init_elem_auxiliary__null_elem(void** state)
{
    hash_set_t* phash_set = create_hash_set(int);

    expect_assert_failure(_hash_set_init_elem_auxiliary(phash_set, NULL));

    hash_set_destroy(phash_set);
}

void test__hash_set_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    hash_set_t* phash_set = create_hash_set(int);
    hash_set_init(phash_set);

    _hash_set_init_elem_auxiliary(phash_set, &elem);
    assert_true(elem == 0);

    hash_set_destroy(phash_set);
}

void test__hash_set_init_elem_auxiliary__successfully_cstr(void** state)
{
    hash_set_t* phash_set = create_hash_set(char*);
    string_t* pstr = create_string();
    hash_set_init(phash_set);

    hash_set_insert(phash_set, "abc");
    hash_set_insert(phash_set, "def");
    _hash_set_init_elem_auxiliary(phash_set, pstr);
    assert_true(string_empty(pstr));

    hash_set_destroy(phash_set);
    string_destroy(pstr);
}

void test__hash_set_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    hash_set_t* phash_set = create_hash_set(iterator_t);
    hash_set_init(phash_set);

    hash_set_insert(phash_set, &it_iter);

    _hash_set_init_elem_auxiliary(phash_set, (void*)iterator_get_pointer(hash_set_begin(phash_set)));
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)iterator_get_pointer(hash_set_begin(phash_set)), &it_iter, sizeof(iterator_t)) == 0);

    hash_set_destroy(phash_set);
}

void test__hash_set_init_elem_auxiliary__successfully_container(void** state)
{
    vector_t vec;
    hash_set_t* phash_set = create_hash_set(vector_t<int>);

    _hash_set_init_elem_auxiliary(phash_set, &vec);
    assert_true(_vector_is_inited(&vec));

    hash_set_destroy(phash_set);
}

typedef struct _tag_test__hash_set_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__hash_set_init_elem_auxiliary__successfully_user_defined_t;

void test__hash_set_init_elem_auxiliary__successfully_user_defined(void** state)
{
    _test__hash_set_init_elem_auxiliary__successfully_user_defined_t t_user;
    hash_set_t* phash_set = NULL;

    type_register(_test__hash_set_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    phash_set = create_hash_set(_test__hash_set_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _hash_set_init_elem_auxiliary(phash_set, &t_user);
    assert_true(t_user.n_elem == 0);

    hash_set_destroy(phash_set);
}

