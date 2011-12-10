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
#include "cstl_hash_multiset_aux.h"

#include "ut_def.h"
#include "ut_cstl_hash_multiset_private.h"

UT_SUIT_DEFINATION(cstl_hash_multiset_private, _create_hash_multiset)

/*
 * test _create_hash_multiset
 */
UT_CASE_DEFINATION(_create_hash_multiset)
void test__create_hash_multiset__null_typename(void** state)
{
    expect_assert_failure(_create_hash_multiset(NULL));
}

void test__create_hash_multiset__c_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("double");
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__create_hash_multiset__cstr(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__create_hash_multiset__libcstl_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("vector_t<int>");
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

typedef struct _test_test__create_hash_multiset__user_define
{
    int n_elem;
}_test__create_hash_multiset__user_define_t;

void test__create_hash_multiset__user_define(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;

    type_register(_test__create_hash_multiset__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multiset = _create_hash_multiset("_test__create_hash_multiset__user_define_t");
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__create_hash_multiset__unregister(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("test__create_hash_multiset__unregister_t");
    assert_true(pt_hash_multiset == NULL);
}

/*
 * test _create_hash_multiset_auxiliary
 */
UT_CASE_DEFINATION(_create_hash_multiset_auxiliary)
void test__create_hash_multiset_auxiliary__null_hash_multiset(void** state)
{
    expect_assert_failure(_create_hash_multiset_auxiliary(NULL, "int"));
}

void test__create_hash_multiset_auxiliary__null_typename(void** state)
{
    hash_multiset_t hash_multiset;
    expect_assert_failure(_create_hash_multiset_auxiliary(&hash_multiset, NULL));
}

void test__create_hash_multiset_auxiliary__unregistered(void** state)
{
    hash_multiset_t* pt_hash_multiset = malloc(sizeof(hash_multiset_t));
    assert_false(_create_hash_multiset_auxiliary(pt_hash_multiset, "_test__create_hash_multiset_auxiliary__unregistered_t"));

    free(pt_hash_multiset);
}

void test__create_hash_multiset_auxiliary__c_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = malloc(sizeof(hash_multiset_t));
    assert_true(_create_hash_multiset_auxiliary(pt_hash_multiset, "int"));
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__create_hash_multiset_auxiliary__cstr(void** state)
{
    hash_multiset_t* pt_hash_multiset = malloc(sizeof(hash_multiset_t));
    assert_true(_create_hash_multiset_auxiliary(pt_hash_multiset, "char*"));
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__create_hash_multiset_auxiliary__libcstl_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = malloc(sizeof(hash_multiset_t));
    assert_true(_create_hash_multiset_auxiliary(pt_hash_multiset, "vector_t<int>"));
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

typedef struct _tag_test__create_hash_multiset_auxiliary__user_define
{
    int n_elem;
}_test__create_hash_multiset_auxiliary__user_define_t;

void test__create_hash_multiset_auxiliary__user_define(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;

    type_register(_test__create_hash_multiset_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multiset = malloc(sizeof(hash_multiset_t));
    assert_true(_create_hash_multiset_auxiliary(pt_hash_multiset, "_test__create_hash_multiset_auxiliary__user_define_t"));
    assert_true(pt_hash_multiset != NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_destroy_auxiliary
 */
UT_CASE_DEFINATION(_hash_multiset_destroy_auxiliary)
void test__hash_multiset_destroy_auxiliary__null_hash_multiset(void** state)
{
    expect_assert_failure(_hash_multiset_destroy_auxiliary(NULL));
}

void test__hash_multiset_destroy_auxiliary__non_created(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(_hash_multiset_destroy_auxiliary(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_CSTL_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

/*
void test__hash_multiset_destroy_auxiliary__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");

    expect_assert_failure(_hash_multiset_destroy_auxiliary(pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}
*/

void test__hash_multiset_destroy_auxiliary__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    _hash_multiset_destroy_auxiliary(pt_hash_multiset);
    assert_true(pt_hash_multiset->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_multiset->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_multiset->_t_hashtable._t_nodecount == 0);
    free(pt_hash_multiset);
}

void test__hash_multiset_destroy_auxiliary__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    int elem = 9;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);

    _hash_multiset_destroy_auxiliary(pt_hash_multiset);
    assert_true(pt_hash_multiset->_t_hashtable._bfun_compare == NULL);
    assert_true(pt_hash_multiset->_t_hashtable._ufun_hash == NULL);
    assert_true(pt_hash_multiset->_t_hashtable._t_nodecount == 0);
    free(pt_hash_multiset);
}

/*
 * test _hash_multiset_find and _hash_multiset_find_varg
 */
UT_CASE_DEFINATION(_hash_multiset_find__hash_multiset_find_varg)
void test__hash_multiset_find__hash_multiset_find_varg__null_hash_multiset(void** state)
{
    expect_assert_failure(_hash_multiset_find(NULL, 9));
}

void test__hash_multiset_find__hash_multiset_find_varg__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    unary_function_t ufun_hash = NULL;

    hash_multiset_init(pt_hash_multiset);
    ufun_hash = pt_hash_multiset->_t_hashtable._ufun_hash;
    pt_hash_multiset->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_multiset_find(pt_hash_multiset, 9));
    pt_hash_multiset->_t_hashtable._ufun_hash = ufun_hash;

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_find__hash_multiset_find_varg__c_builtin_find(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    hash_multiset_iterator_t it_iter;
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 2;
    it_iter = _hash_multiset_find(pt_hash_multiset, elem);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_find__hash_multiset_find_varg__c_builtin_not_find(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    hash_multiset_iterator_t it_iter;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    it_iter = _hash_multiset_find(pt_hash_multiset, 42);
    assert_true(iterator_equal(it_iter, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_find__hash_multiset_find_varg__cstr_find(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");
    hash_multiset_iterator_t it_iter;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    it_iter = hash_multiset_find(pt_hash_multiset, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "ggg") == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_find__hash_multiset_find_varg__cstr_not_find(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");
    hash_multiset_iterator_t it_iter;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    it_iter = _hash_multiset_find(pt_hash_multiset, "vvvvv");
    assert_true(iterator_equal(it_iter, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
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
void test__hash_multiset_find__hash_multiset_find_varg__libcstl_builtin_find(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    hash_multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hash_multiset_find(pt_hash_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(it_iter)) == 6);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

void test__hash_multiset_find__hash_multiset_find_varg__libcstl_builtin_not_find(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    hash_multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _hash_multiset_find(pt_hash_multiset, plist);
    assert_true(iterator_equal(it_iter, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multiset_find__hash_multiset_find_varg__user_define
{
    int n_elem;
}_test__hash_multiset_find__hash_multiset_find_varg__user_define_t;
void test__hash_multiset_find__hash_multiset_find_varg__user_define_find(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    hash_multiset_iterator_t it_iter;
    _test__hash_multiset_find__hash_multiset_find_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multiset_find__hash_multiset_find_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multiset = _create_hash_multiset("_test__hash_multiset_find__hash_multiset_find_varg__user_define_t");
    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 8;
    it_iter = _hash_multiset_find(pt_hash_multiset, &elem);
    assert_true(((_test__hash_multiset_find__hash_multiset_find_varg__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 8);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_find__hash_multiset_find_varg__user_define_not_find(void** state)
{
    hash_multiset_t* pt_hash_multiset =  _create_hash_multiset("_test__hash_multiset_find__hash_multiset_find_varg__user_define_t");
    hash_multiset_iterator_t it_iter;
    _test__hash_multiset_find__hash_multiset_find_varg__user_define_t elem;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 78;
    it_iter = _hash_multiset_find(pt_hash_multiset, &elem);
    assert_true(iterator_equal(it_iter, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_count and _hash_multiset_count_varg
 */
UT_CASE_DEFINATION(_hash_multiset_count__hash_multiset_count_varg)
void test__hash_multiset_count__hash_multiset_count_varg__null_hash_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_multiset_count(NULL, elem));
}

void test__hash_multiset_count__hash_multiset_count_varg__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_multiset_init(pt_hash_multiset);

    ufun_hash = pt_hash_multiset->_t_hashtable._ufun_hash;
    pt_hash_multiset->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_multiset_count(pt_hash_multiset, elem));
    pt_hash_multiset->_t_hashtable._ufun_hash = ufun_hash;

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__c_builtin_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 1222;
    assert_true(_hash_multiset_count(pt_hash_multiset, elem) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__c_builtin_1(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 2;
    assert_true(_hash_multiset_count(pt_hash_multiset, elem) == 1);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__c_builtin_n(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
        hash_multiset_insert(pt_hash_multiset, i);
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 2;
    assert_true(_hash_multiset_count(pt_hash_multiset, elem) == 3);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__cstr_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    assert_true(_hash_multiset_count(pt_hash_multiset, "uuuu") == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__cstr_1(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    assert_true(_hash_multiset_count(pt_hash_multiset, "ggg") == 1);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__cstr_n(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    assert_true(_hash_multiset_count(pt_hash_multiset, "ggg") == 4);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__libcstl_builtin_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_hash_multiset_count(pt_hash_multiset, plist) == 0);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

void test__hash_multiset_count__hash_multiset_count_varg__libcstl_builtin_1(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multiset_count(pt_hash_multiset, plist) == 1);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

void test__hash_multiset_count__hash_multiset_count_varg__libcstl_builtin_n(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
        hash_multiset_insert(pt_hash_multiset, plist);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multiset_count(pt_hash_multiset, plist) == 3);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multiset_count__hash_multiset_count_varg__user_define
{
    int n_elem;
}_test__hash_multiset_count__hash_multiset_count_varg__user_define_t;
void test__hash_multiset_count__hash_multiset_count_varg__user_define_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    _test__hash_multiset_count__hash_multiset_count_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multiset_count__hash_multiset_count_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multiset = _create_hash_multiset("_test__hash_multiset_count__hash_multiset_count_varg__user_define_t");
    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 88;
    assert_true(_hash_multiset_count(pt_hash_multiset, &elem) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__user_define_1(void** state)
{
    hash_multiset_t* pt_hash_multiset =  _create_hash_multiset("_test__hash_multiset_count__hash_multiset_count_varg__user_define_t");
    _test__hash_multiset_count__hash_multiset_count_varg__user_define_t elem;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_multiset_count(pt_hash_multiset, &elem) == 1);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_count__hash_multiset_count_varg__user_define_n(void** state)
{
    hash_multiset_t* pt_hash_multiset =  _create_hash_multiset("_test__hash_multiset_count__hash_multiset_count_varg__user_define_t");
    _test__hash_multiset_count__hash_multiset_count_varg__user_define_t elem;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_multiset_insert(pt_hash_multiset, &elem);
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_multiset_count(pt_hash_multiset, &elem) == 2);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_equal_range and _hash_multiset_equal_range_varg
 */
UT_CASE_DEFINATION(_hash_multiset_equal_range__hash_multiset_equal_range_varg)
void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__null_hash_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_multiset_equal_range(NULL, elem));
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_multiset_init(pt_hash_multiset);

    ufun_hash = pt_hash_multiset->_t_hashtable._ufun_hash;
    pt_hash_multiset->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_multiset_equal_range(pt_hash_multiset, elem));
    pt_hash_multiset->_t_hashtable._ufun_hash = ufun_hash;

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__c_builtin_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    range_t r_range;
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 2;
    r_range = _hash_multiset_equal_range(pt_hash_multiset, elem);
    assert_true(*(int*)iterator_get_pointer(r_range.it_begin) == 2);
    assert_true(*(int*)iterator_get_pointer(r_range.it_end) == 3);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__c_builtin_greater(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    range_t r_range;
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = -8;
    r_range = _hash_multiset_equal_range(pt_hash_multiset, elem);
    assert_true(iterator_equal(r_range.it_begin, hash_multiset_end(pt_hash_multiset)));
    assert_true(iterator_equal(r_range.it_end, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__cstr_upper_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");
    range_t r_range;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    r_range = _hash_multiset_equal_range(pt_hash_multiset, "ggg");
    assert_true(strcmp((char*)iterator_get_pointer(r_range.it_begin), "ggg") == 0);
    assert_true(iterator_equal(r_range.it_end, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__cstr_greater(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");
    range_t r_range;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    r_range = _hash_multiset_equal_range(pt_hash_multiset, "vvvv");
    assert_true(iterator_equal(r_range.it_begin, hash_multiset_end(pt_hash_multiset)));
    assert_true(iterator_equal(r_range.it_end, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__libcstl_builtin_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _hash_multiset_equal_range(pt_hash_multiset, plist);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)iterator_get_pointer(r_range.it_end)) == 7);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__libcstl_builtin_greater(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _hash_multiset_equal_range(pt_hash_multiset, plist);
    assert_true(iterator_equal(r_range.it_begin, hash_multiset_end(pt_hash_multiset)));
    assert_true(iterator_equal(r_range.it_end, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define
{
    int n_elem;
}_test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t;
void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    range_t r_range;
    _test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multiset = _create_hash_multiset("_test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t");
    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 8;
    r_range = _hash_multiset_equal_range(pt_hash_multiset, &elem);
    assert_true(((_test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t*)iterator_get_pointer(r_range.it_end))->n_elem == 9);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_greater(void** state)
{
    hash_multiset_t* pt_hash_multiset =  _create_hash_multiset("_test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t");
    range_t r_range;
    _test__hash_multiset_equal_range__hash_multiset_equal_range_varg__user_define_t elem;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 7;
    r_range = _hash_multiset_equal_range(pt_hash_multiset, &elem);
    assert_true(iterator_equal(r_range.it_begin, hash_multiset_end(pt_hash_multiset)));
    assert_true(iterator_equal(r_range.it_end, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_erase and _hash_multiset_erase_varg
 */
UT_CASE_DEFINATION(_hash_multiset_erase__hash_multiset_erase_varg)
void test__hash_multiset_erase__hash_multiset_erase_varg__null_hash_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_multiset_erase(NULL, elem));
}

void test__hash_multiset_erase__hash_multiset_erase_varg__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_multiset_init(pt_hash_multiset);

    ufun_hash = pt_hash_multiset->_t_hashtable._ufun_hash;
    pt_hash_multiset->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_multiset_erase(pt_hash_multiset, elem));
    pt_hash_multiset->_t_hashtable._ufun_hash = ufun_hash;

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__c_builtin_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 24;
    assert_true(_hash_multiset_erase(pt_hash_multiset, elem) == 0);
    assert_true(hash_multiset_size(pt_hash_multiset) == 10);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__c_builtin_1(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 8;
    assert_true(_hash_multiset_erase(pt_hash_multiset, elem) == 1);
    assert_true(hash_multiset_size(pt_hash_multiset) == 9);
    assert_true(_hash_multiset_count(pt_hash_multiset, elem) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__c_builtin_n(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
        hash_multiset_insert(pt_hash_multiset, i);
        hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 8;
    assert_true(_hash_multiset_erase(pt_hash_multiset, elem) == 3);
    assert_true(hash_multiset_size(pt_hash_multiset) == 27);
    assert_true(_hash_multiset_count(pt_hash_multiset, elem) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__cstr_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    assert_true(_hash_multiset_erase(pt_hash_multiset, "gggppgg") == 0);
    assert_true(hash_multiset_size(pt_hash_multiset) == 5);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__cstr_1(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    assert_true(_hash_multiset_erase(pt_hash_multiset, "ggg") == 1);
    assert_true(hash_multiset_size(pt_hash_multiset) == 4);
    assert_true(_hash_multiset_count(pt_hash_multiset, "ggg") == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__cstr_n(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "aaa");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "ggg");
    hash_multiset_insert(pt_hash_multiset, "nghl");
    hash_multiset_insert(pt_hash_multiset, "asery");
    hash_multiset_insert(pt_hash_multiset, "linux");

    assert_true(_hash_multiset_erase(pt_hash_multiset, "ggg") == 4);
    assert_true(hash_multiset_size(pt_hash_multiset) == 4);
    assert_true(_hash_multiset_count(pt_hash_multiset, "ggg") == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__libcstl_builtin_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_hash_multiset_erase(pt_hash_multiset, plist) == 0);
    assert_true(hash_multiset_size(pt_hash_multiset) == 10);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__libcstl_builtin_1(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multiset_erase(pt_hash_multiset, plist) == 1);
    assert_true(hash_multiset_size(pt_hash_multiset) == 9);
    assert_true(_hash_multiset_count(pt_hash_multiset, plist) == 0);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__libcstl_builtin_n(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        hash_multiset_insert(pt_hash_multiset, plist);
        hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hash_multiset_erase(pt_hash_multiset, plist) == 2);
    assert_true(hash_multiset_size(pt_hash_multiset) == 18);
    assert_true(_hash_multiset_count(pt_hash_multiset, plist) == 0);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multiset_erase__hash_multiset_erase_varg__user_define
{
    int n_elem;
}_test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t;
void test__hash_multiset_erase__hash_multiset_erase_varg__user_define_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    _test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multiset = _create_hash_multiset("_test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t");
    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 86;
    assert_true(_hash_multiset_erase(pt_hash_multiset, &elem) == 0);
    assert_true(hash_multiset_size(pt_hash_multiset) == 10);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__user_define_1(void** state)
{
    hash_multiset_t* pt_hash_multiset =  _create_hash_multiset("_test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t");
    _test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t elem;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_multiset_erase(pt_hash_multiset, &elem) == 1);
    assert_true(hash_multiset_size(pt_hash_multiset) == 9);
    assert_true(_hash_multiset_count(pt_hash_multiset, &elem) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_erase__hash_multiset_erase_varg__user_define_n(void** state)
{
    hash_multiset_t* pt_hash_multiset =  _create_hash_multiset("_test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t");
    _test__hash_multiset_erase__hash_multiset_erase_varg__user_define_t elem;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        hash_multiset_insert(pt_hash_multiset, &elem);
        hash_multiset_insert(pt_hash_multiset, &elem);
        hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hash_multiset_erase(pt_hash_multiset, &elem) == 3);
    assert_true(hash_multiset_size(pt_hash_multiset) == 27);
    assert_true(_hash_multiset_count(pt_hash_multiset, &elem) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_insert and _hash_multiset_insert_varg
 */
UT_CASE_DEFINATION(_hash_multiset_insert__hash_multiset_insert_varg)
void test__hash_multiset_insert_varg__null_hash_multiset(void** state)
{
    int elem = 9;
    expect_assert_failure(_hash_multiset_insert(NULL, elem));
}

void test__hash_multiset_insert_varg__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    unary_function_t ufun_hash = NULL;
    int elem = 9;
    hash_multiset_init(pt_hash_multiset);

    ufun_hash = pt_hash_multiset->_t_hashtable._ufun_hash;
    pt_hash_multiset->_t_hashtable._ufun_hash = NULL;
    expect_assert_failure(_hash_multiset_insert(pt_hash_multiset, elem));
    pt_hash_multiset->_t_hashtable._ufun_hash = ufun_hash;

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_insert_varg__c_builtin_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    hash_multiset_iterator_t it_iter;
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        _hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = 2;
    it_iter = _hash_multiset_insert(pt_hash_multiset, elem);
    assert_true(*(int*)_hash_multiset_iterator_get_pointer(it_iter) == 2);
    assert_true(hash_multiset_size(pt_hash_multiset) == 11);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_insert_varg__c_builtin_not_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("int");
    hash_multiset_iterator_t it_iter;
    int elem;
    int i;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        _hash_multiset_insert(pt_hash_multiset, i);
    }

    elem = -8;
    it_iter = _hash_multiset_insert(pt_hash_multiset, elem);
    assert_true(*(int*)_hash_multiset_iterator_get_pointer(it_iter) == -8);
    assert_true(hash_multiset_size(pt_hash_multiset) == 11);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_insert_varg__cstr_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");
    hash_multiset_iterator_t it_iter;

    hash_multiset_init(pt_hash_multiset);
    _hash_multiset_insert(pt_hash_multiset, "aaa");
    _hash_multiset_insert(pt_hash_multiset, "ggg");
    _hash_multiset_insert(pt_hash_multiset, "nghl");
    _hash_multiset_insert(pt_hash_multiset, "asery");
    _hash_multiset_insert(pt_hash_multiset, "linux");

    it_iter = _hash_multiset_insert(pt_hash_multiset, "ggg");
    assert_true(strcmp((char*)_hash_multiset_iterator_get_pointer(it_iter), "ggg") == 0);
    assert_true(hash_multiset_size(pt_hash_multiset) == 6);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_insert_varg__cstr_not_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("char*");
    hash_multiset_iterator_t it_iter;

    hash_multiset_init(pt_hash_multiset);
    _hash_multiset_insert(pt_hash_multiset, "aaa");
    _hash_multiset_insert(pt_hash_multiset, "ggg");
    _hash_multiset_insert(pt_hash_multiset, "nghl");
    _hash_multiset_insert(pt_hash_multiset, "asery");
    _hash_multiset_insert(pt_hash_multiset, "linux");

    it_iter = _hash_multiset_insert(pt_hash_multiset, "vvvv");
    assert_true(strcmp((char*)_hash_multiset_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(hash_multiset_size(pt_hash_multiset) == 6);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_insert_varg__libcstl_builtin_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    hash_multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hash_multiset_insert(pt_hash_multiset, plist);
    assert_true(*(int*)list_front((list_t*)_hash_multiset_iterator_get_pointer(it_iter)) == 6);
    assert_true(hash_multiset_size(pt_hash_multiset) == 11);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

void test__hash_multiset_insert_varg__libcstl_builtin_not_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = _create_hash_multiset("list_t<int>");
    hash_multiset_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    hash_multiset_init_ex(pt_hash_multiset, 0, _test__hash_private__libcstl_builtin_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _hash_multiset_insert(pt_hash_multiset, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _hash_multiset_insert(pt_hash_multiset, plist);
    assert_true(*(int*)list_front((list_t*)_hash_multiset_iterator_get_pointer(it_iter)) == 5);
    assert_true(hash_multiset_size(pt_hash_multiset) == 11);

    hash_multiset_destroy(pt_hash_multiset);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multiset_insert_varg__user_define
{
    int n_elem;
}_test__hash_multiset_insert_varg__user_define_t;
void test__hash_multiset_insert_varg__user_define_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    hash_multiset_iterator_t it_iter;
    _test__hash_multiset_insert_varg__user_define_t elem;
    int i = 0;

    type_register(_test__hash_multiset_insert_varg__user_define_t, NULL, NULL, NULL, NULL);

    pt_hash_multiset = _create_hash_multiset("_test__hash_multiset_insert_varg__user_define_t");
    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 8;
    it_iter = _hash_multiset_insert(pt_hash_multiset, &elem);
    assert_true(((_test__hash_multiset_insert_varg__user_define_t*)_hash_multiset_iterator_get_pointer(it_iter))->n_elem == 8);
    assert_true(hash_multiset_size(pt_hash_multiset) == 11);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_insert_varg__user_define_not_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset =  _create_hash_multiset("_test__hash_multiset_insert_varg__user_define_t");
    hash_multiset_iterator_t it_iter;
    _test__hash_multiset_insert_varg__user_define_t elem;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _hash_multiset_insert(pt_hash_multiset, &elem);
    }

    elem.n_elem = 7;
    it_iter = _hash_multiset_insert(pt_hash_multiset, &elem);
    assert_true(((_test__hash_multiset_insert_varg__user_define_t*)_hash_multiset_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(hash_multiset_size(pt_hash_multiset) == 11);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_hash_multiset_init_elem_auxiliary)
void test__hash_multiset_init_elem_auxiliary__null_hash_multiset_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_hash_multiset_init_elem_auxiliary(NULL, &elem));
}

void test__hash_multiset_init_elem_auxiliary__null_elem(void** state)
{
    hash_multiset_t* phash_multiset = create_hash_multiset(int);

    expect_assert_failure(_hash_multiset_init_elem_auxiliary(phash_multiset, NULL));

    hash_multiset_destroy(phash_multiset);
}

void test__hash_multiset_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    hash_multiset_t* phash_multiset = create_hash_multiset(int);
    hash_multiset_init(phash_multiset);

    _hash_multiset_init_elem_auxiliary(phash_multiset, &elem);
    assert_true(elem == 0);

    hash_multiset_destroy(phash_multiset);
}

void test__hash_multiset_init_elem_auxiliary__successfully_cstr(void** state)
{
    hash_multiset_t* phash_multiset = create_hash_multiset(char*);
    string_t* pstr = create_string();
    hash_multiset_init(phash_multiset);

    hash_multiset_insert(phash_multiset, "abc");
    hash_multiset_insert(phash_multiset, "def");
    _hash_multiset_init_elem_auxiliary(phash_multiset, pstr);
    assert_true(string_empty(pstr));

    hash_multiset_destroy(phash_multiset);
    string_destroy(pstr);
}

void test__hash_multiset_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter;
    hash_multiset_t* phash_multiset = create_hash_multiset(iterator_t);
    hash_multiset_init(phash_multiset);

    hash_multiset_insert(phash_multiset, &it_iter);

    _hash_multiset_init_elem_auxiliary(phash_multiset, (void*)iterator_get_pointer(hash_multiset_begin(phash_multiset)));
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)iterator_get_pointer(hash_multiset_begin(phash_multiset)), &it_iter, sizeof(iterator_t)) == 0);

    hash_multiset_destroy(phash_multiset);
}

void test__hash_multiset_init_elem_auxiliary__successfully_container(void** state)
{
    vector_t vec;
    hash_multiset_t* phash_multiset = create_hash_multiset(vector_t<int>);

    _hash_multiset_init_elem_auxiliary(phash_multiset, &vec);
    assert_true(_vector_is_inited(&vec));

    hash_multiset_destroy(phash_multiset);
}

typedef struct _tag_test__hash_multiset_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__hash_multiset_init_elem_auxiliary__successfully_user_defined_t;

void test__hash_multiset_init_elem_auxiliary__successfully_user_defined(void** state)
{
    _test__hash_multiset_init_elem_auxiliary__successfully_user_defined_t t_user;
    hash_multiset_t* phash_multiset = NULL;

    type_register(_test__hash_multiset_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    phash_multiset = create_hash_multiset(_test__hash_multiset_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _hash_multiset_init_elem_auxiliary(phash_multiset, &t_user);
    assert_true(t_user.n_elem == 0);

    hash_multiset_destroy(phash_multiset);
}

