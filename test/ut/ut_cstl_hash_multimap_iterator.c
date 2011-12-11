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
#include "cstl_hash_multimap_aux.h"

#include "ut_def.h"
#include "ut_cstl_hash_multimap_iterator.h"

UT_SUIT_DEFINATION(cstl_hash_multimap_iterator, create_hash_multimap_iterator)
/*
 * test _create_hash_multimap_iterator
 */
UT_CASE_DEFINATION(create_hash_multimap_iterator)
void test_create_hash_multimap_iterator__successfully(void** state)
{
    hash_multimap_iterator_t it_iter = create_hash_multimap_iterator();
    assert_true(it_iter._t_pos._t_hashpos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_hashpos._pby_bucketpos == NULL);
    assert_true(it_iter._t_pos._t_hashpos._pt_hashtable == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _HASH_MULTIMAP_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

/*
 * test _hash_multimap_iterator_get_value
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_get_value)
void test__hash_multimap_iterator_get_value__null_corepos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 0;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_value(it_iter, &elem));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_value__null_hashtable(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 0;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_value(it_iter, &elem));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_value__null_bucketpos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 0;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_value(it_iter, &elem));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_value__invalid_container_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 0;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_containertype = 1000;
    expect_assert_failure(_hash_multimap_iterator_get_value(it_iter, &elem));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_value__invalid_iterator_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 0;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_iteratortype = 1000;
    expect_assert_failure(_hash_multimap_iterator_get_value(it_iter, &elem));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_value__end(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 0;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_end(pt_hash_multimap);

    expect_assert_failure(_hash_multimap_iterator_get_value(it_iter, &elem));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_value__null_value(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_end(pt_hash_multimap);

    expect_assert_failure(_hash_multimap_iterator_get_value(it_iter, NULL));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_value__c_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 12;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    pair_make(pt_pair, 0, 0);
    _hash_multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(*(int*)pair_first(pt_pair) == 12);
    assert_true(*(int*)pair_second(pt_pair) == 12);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_get_value__cstr(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, "abc", "def");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    pair_make(pt_pair, "", "");
    _hash_multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(strcmp((char*)pair_first(pt_pair), "abc") == 0);
    assert_true(strcmp((char*)pair_second(pt_pair), "def") == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_get_value__libcstl_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);
    hash_multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    hash_multimap_init(pt_hash_multimap);
    vector_init_n(pvec, 10);
    list_init(plist);
    pair_init_elem(pt_pair, pvec, plist);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    vector_clear(pvec);
    list_push_back(plist, 333);
    pair_make(pt_pair, pvec, plist);
    _hash_multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(vector_size((vector_t*)pair_first(pt_pair)) == 10);
    assert_true(list_empty((list_t*)pair_second(pt_pair)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multimap_iterator_get_value__user_define
{
    int elem;
}_test__hash_multimap_iterator_get_value__user_define_t;
void test__hash_multimap_iterator_get_value__user_define(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;
    pair_t* pt_pair = NULL;
    hash_multimap_iterator_t it_iter;
    _test__hash_multimap_iterator_get_value__user_define_t elem;

    type_register(_test__hash_multimap_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multimap = create_hash_multimap(_test__hash_multimap_iterator_get_value__user_define_t, _test__hash_multimap_iterator_get_value__user_define_t);
    pt_pair = create_pair(_test__hash_multimap_iterator_get_value__user_define_t, _test__hash_multimap_iterator_get_value__user_define_t);
    hash_multimap_init(pt_hash_multimap);
    elem.elem = 100;
    pair_init_elem(pt_pair, &elem, &elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    elem.elem = 0;
    pair_make(pt_pair, &elem, &elem);
    _hash_multimap_iterator_get_value(it_iter, pt_pair);
    assert_true(((_test__hash_multimap_iterator_get_value__user_define_t*)pair_first(pt_pair))->elem == 100);
    assert_true(((_test__hash_multimap_iterator_get_value__user_define_t*)pair_second(pt_pair))->elem == 100);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_iterator_get_pointer
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_get_pointer)
void test__hash_multimap_iterator_get_pointer__null_corepos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_pointer(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer__null_hashtable(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_pointer(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer__null_bucketpos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_pointer(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer__invalid_container_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_hash_multimap_iterator_get_pointer(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer__invalid_iterator_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_hash_multimap_iterator_get_pointer(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer__end(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_end(pt_hash_multimap);

    expect_assert_failure(_hash_multimap_iterator_get_pointer(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer__c_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 12;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(*(int*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)) == 12);
    assert_true(*(int*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)) == 12);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_get_pointer__cstr(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, "abc", "def");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(strcmp((char*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)), "abc") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)), "def") == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_get_pointer__libcstl_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);
    hash_multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    hash_multimap_init(pt_hash_multimap);
    vector_init_n(pvec, 10);
    list_init(plist);
    pair_init_elem(pt_pair, pvec, plist);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(vector_size((vector_t*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter))) == 10);
    assert_true(list_size((list_t*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer(it_iter))) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multimap_iterator_get_pointer__user_define
{
    int elem;
}_test__hash_multimap_iterator_get_pointer__user_define_t;
void test__hash_multimap_iterator_get_pointer__user_define(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;
    pair_t* pt_pair = NULL;
    hash_multimap_iterator_t it_iter;
    _test__hash_multimap_iterator_get_pointer__user_define_t elem;

    type_register(_test__hash_multimap_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multimap = create_hash_multimap(_test__hash_multimap_iterator_get_pointer__user_define_t, _test__hash_multimap_iterator_get_pointer__user_define_t);
    pt_pair = create_pair(_test__hash_multimap_iterator_get_pointer__user_define_t, _test__hash_multimap_iterator_get_pointer__user_define_t);
    hash_multimap_init(pt_hash_multimap);
    elem.elem = 100;
    pair_init_elem(pt_pair, &elem, &elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(((_test__hash_multimap_iterator_get_pointer__user_define_t*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)))->elem == 100);
    assert_true(((_test__hash_multimap_iterator_get_pointer__user_define_t*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)))->elem == 100);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_get_pointer_ignore_cstr)
void test__hash_multimap_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__null_hashtable(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__null_bucketpos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__invalid_container_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__invalid_iterator_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__end(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_end(pt_hash_multimap);

    expect_assert_failure(_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 12;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(*(int*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter)) == 12);
    assert_true(*(int*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter)) == 12);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(char*, char*);
    pair_t* pt_pair = create_pair(char*, char*);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, "abc", "def");
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(strcmp((char*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);
    assert_true(strcmp((char*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter)), "def") == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(vector_t<int>, list_t<int>);
    pair_t* pt_pair = create_pair(vector_t<int>, list_t<int>);
    hash_multimap_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    list_t* plist = create_list(int);
    hash_multimap_init(pt_hash_multimap);
    vector_init_n(pvec, 10);
    list_init(plist);
    pair_init_elem(pt_pair, pvec, plist);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(vector_size((vector_t*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter))) == 10);
    assert_true(list_size((list_t*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter))) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
    vector_destroy(pvec);
    list_destroy(plist);
}

typedef struct _tag_test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t;
void test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    hash_multimap_t* pt_hash_multimap = NULL;
    pair_t* pt_pair = NULL;
    hash_multimap_iterator_t it_iter;
    _test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multimap = create_hash_multimap(_test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t, _test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t);
    pt_pair = create_pair(_test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t, _test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t);
    hash_multimap_init(pt_hash_multimap);
    elem.elem = 100;
    pair_init_elem(pt_pair, &elem, &elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(((_test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter)))->elem == 100);
    assert_true(((_test__hash_multimap_iterator_get_pointer_ignore_cstr__user_define_t*)pair_second((pair_t*)_hash_multimap_iterator_get_pointer_ignore_cstr(it_iter)))->elem == 100);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_iterator_next
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_next)
void test__hash_multimap_iterator_next__null_corepos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multimap_iterator_next(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_next__null_hashtable(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multimap_iterator_next(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_next__null_bucketpos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multimap_iterator_next(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_next__invalid_container_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_containertype = 2394;
    expect_assert_failure(_hash_multimap_iterator_next(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_next__invalid_iterator_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_iteratortype = 44444;
    expect_assert_failure(_hash_multimap_iterator_next(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_next__end(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_end(pt_hash_multimap);

    expect_assert_failure(_hash_multimap_iterator_next(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_next__last(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 10;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);

    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter = _hash_multimap_iterator_next(it_iter);
    assert_true(_hash_multimap_iterator_equal(it_iter, hash_multimap_end(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_next__begin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 10;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);

    hash_multimap_insert(pt_hash_multimap, pt_pair);
    elem = 3;
    pair_make(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_iter = hash_multimap_begin(pt_hash_multimap);
    assert_true(*(int*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)) == 3);
    it_iter = _hash_multimap_iterator_next(it_iter);
    assert_true(*(int*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)) == 10);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_iterator_prev
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_prev)
void test__hash_multimap_iterator_prev__null_corepos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multimap_iterator_prev(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_prev__null_hashtable(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multimap_iterator_prev(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_prev__null_bucketpos(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multimap_iterator_prev(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_prev__invalid_containter_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int,int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_containertype = 33333;
    expect_assert_failure(_hash_multimap_iterator_prev(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_prev__invalid_iterator_type(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int,int);
    hash_multimap_iterator_t it_iter;
    hash_multimap_init(pt_hash_multimap);

    it_iter = hash_multimap_begin(pt_hash_multimap);

    it_iter._t_iteratortype = 5555;
    expect_assert_failure(_hash_multimap_iterator_prev(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_prev__begin(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int,int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 100;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);

    it_iter = hash_multimap_begin(pt_hash_multimap);
    expect_assert_failure(_hash_multimap_iterator_prev(it_iter));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_prev__end(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 10;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);

    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_iter = hash_multimap_end(pt_hash_multimap);

    it_iter = _hash_multimap_iterator_prev(it_iter);
    assert_true(_hash_multimap_iterator_equal(it_iter, hash_multimap_begin(pt_hash_multimap)));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_prev__last(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_iter;
    int elem = 10;
    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);

    hash_multimap_insert(pt_hash_multimap, pt_pair);
    elem = 3;
    pair_make(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_iter = _hash_multimap_iterator_prev(hash_multimap_end(pt_hash_multimap));
    assert_true(*(int*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)) == 10);
    it_iter = _hash_multimap_iterator_prev(it_iter);
    assert_true(*(int*)pair_first((pair_t*)_hash_multimap_iterator_get_pointer(it_iter)) == 3);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_iterator_equal
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_equal)
void test__hash_multimap_iterator_equal__invalid_first(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_hash_multimap);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multimap_iterator_equal(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_equal__invalid_second(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_hash_multimap);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    it_second._t_iteratortype = 45553;
    expect_assert_failure(_hash_multimap_iterator_equal(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_equal__not_same_hash_multimap(void** state)
{
    hash_multimap_t* pt_first = create_hash_multimap(int, int);
    hash_multimap_t* pt_second = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_first);
    hash_multimap_init(pt_second);
    it_first = hash_multimap_begin(pt_first);
    it_second = hash_multimap_begin(pt_second);
    expect_assert_failure(_hash_multimap_iterator_equal(it_first, it_second));

    hash_multimap_destroy(pt_first);
    hash_multimap_destroy(pt_second);
}

void test__hash_multimap_iterator_equal__equal(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    assert_true(_hash_multimap_iterator_equal(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_equal__not_equal(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = _hash_multimap_iterator_next(it_first);
    assert_false(_hash_multimap_iterator_equal(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_iterator_distance
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_distance)
void test__hash_multimap_iterator_distance__invalid_first(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_hash_multimap);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    it_first._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multimap_iterator_distance(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_distance__invalid_second(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_hash_multimap);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    it_second._t_containertype = 4444;
    expect_assert_failure(_hash_multimap_iterator_distance(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_distance__not_same_hash_multimap(void** state)
{
    hash_multimap_t* pt_first = create_hash_multimap(int, int);
    hash_multimap_t* pt_second = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_first);
    hash_multimap_init(pt_second);
    it_first = hash_multimap_begin(pt_first);
    it_second = hash_multimap_begin(pt_second);
    expect_assert_failure(_hash_multimap_iterator_distance(it_first, it_second));

    hash_multimap_destroy(pt_first);
    hash_multimap_destroy(pt_second);
}

void test__hash_multimap_iterator_distance__0(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    assert_true(_hash_multimap_iterator_distance(it_first, it_second) == 0);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_distance__greater_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = _hash_multimap_iterator_next(it_first);
    assert_true(_hash_multimap_iterator_distance(it_first, it_second) == 1);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_distance__less_0(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_end(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    assert_true(_hash_multimap_iterator_distance(it_first, it_second) == -2);

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

/*
 * test _hash_multimap_iterator_before
 */
UT_CASE_DEFINATION(_hash_multimap_iterator_before)
void test__hash_multimap_iterator_before__invalid_first(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_hash_multimap);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multimap_iterator_before(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_before__invalid_second(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_hash_multimap);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    it_second._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multimap_iterator_before(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
}

void test__hash_multimap_iterator_before__not_same_hash_multimap(void** state)
{
    hash_multimap_t* pt_first = create_hash_multimap(int, int);
    hash_multimap_t* pt_second = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;

    hash_multimap_init(pt_first);
    hash_multimap_init(pt_second);
    it_first = hash_multimap_begin(pt_first);
    it_second = hash_multimap_begin(pt_second);
    expect_assert_failure(_hash_multimap_iterator_before(it_first, it_second));

    hash_multimap_destroy(pt_first);
    hash_multimap_destroy(pt_second);
}

void test__hash_multimap_iterator_before__equal(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    assert_false(_hash_multimap_iterator_before(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_before__true(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_begin(pt_hash_multimap);
    it_second = _hash_multimap_iterator_next(it_first);
    assert_true(_hash_multimap_iterator_before(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

void test__hash_multimap_iterator_before__false(void** state)
{
    hash_multimap_t* pt_hash_multimap = create_hash_multimap(int, int);
    pair_t* pt_pair = create_pair(int, int);
    hash_multimap_iterator_t it_first;
    hash_multimap_iterator_t it_second;
    int elem = 100;

    hash_multimap_init(pt_hash_multimap);
    pair_init_elem(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    elem = 2;
    pair_make(pt_pair, elem, elem);
    hash_multimap_insert(pt_hash_multimap, pt_pair);
    it_first = hash_multimap_end(pt_hash_multimap);
    it_second = hash_multimap_begin(pt_hash_multimap);
    assert_false(_hash_multimap_iterator_before(it_first, it_second));

    hash_multimap_destroy(pt_hash_multimap);
    pair_destroy(pt_pair);
}

