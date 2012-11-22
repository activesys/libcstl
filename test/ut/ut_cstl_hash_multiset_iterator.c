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
#include "ut_cstl_hash_multiset_iterator.h"

UT_SUIT_DEFINATION(cstl_hash_multiset_iterator, create_hash_multiset_iterator)
/*
 * test _create_hash_multiset_iterator
 */
UT_CASE_DEFINATION(create_hash_multiset_iterator)
void test_create_hash_multiset_iterator__successfully(void** state)
{
    hash_multiset_iterator_t it_iter = create_hash_multiset_iterator();
    assert_true(it_iter._t_pos._t_treepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _HASH_MULTISET_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

/*
 * test _hash_multiset_iterator_get_value
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_get_value)
void test__hash_multiset_iterator_get_value__null_corepos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 0;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_value(it_iter, &elem));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__null_hashtable(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 0;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_value(it_iter, &elem));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__null_bucketpos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 0;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_value(it_iter, &elem));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__invalid_container_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 0;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_containertype = 1000;
    expect_assert_failure(_hash_multiset_iterator_get_value(it_iter, &elem));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__invalid_iterator_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 0;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_iteratortype = 1000;
    expect_assert_failure(_hash_multiset_iterator_get_value(it_iter, &elem));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__end(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 0;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_end(pt_hash_multiset);

    expect_assert_failure(_hash_multiset_iterator_get_value(it_iter, &elem));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__null_value(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_end(pt_hash_multiset);

    expect_assert_failure(_hash_multiset_iterator_get_value(it_iter, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__c_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 12;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    elem = 0;
    _hash_multiset_iterator_get_value(it_iter, &elem);
    assert_true(elem == 12);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__cstr(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(char*);
    hash_multiset_iterator_t it_iter;
    char* p = NULL;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "abc");

    it_iter = hash_multiset_begin(pt_hash_multiset);
    _hash_multiset_iterator_get_value(it_iter, &p);
    assert_true(strcmp(p, "abc") == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_value__libcstl_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(vector_t<int>);
    hash_multiset_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    hash_multiset_init(pt_hash_multiset);
    vector_init_n(pvec, 10);
    hash_multiset_insert(pt_hash_multiset, pvec);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    vector_clear(pvec);
    _hash_multiset_iterator_get_value(it_iter, pvec);
    assert_true(vector_size(pvec) == 10);

    hash_multiset_destroy(pt_hash_multiset);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_multiset_iterator_get_value__user_define
{
    int elem;
}_test__hash_multiset_iterator_get_value__user_define_t;
void test__hash_multiset_iterator_get_value__user_define(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    hash_multiset_iterator_t it_iter;
    _test__hash_multiset_iterator_get_value__user_define_t elem;

    type_register(_test__hash_multiset_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multiset = create_hash_multiset(_test__hash_multiset_iterator_get_value__user_define_t);
    hash_multiset_init(pt_hash_multiset);
    elem.elem = 100;
    hash_multiset_insert(pt_hash_multiset, &elem);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    elem.elem = 0;
    _hash_multiset_iterator_get_value(it_iter, &elem);
    assert_true(elem.elem == 100);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_iterator_get_pointer
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_get_pointer)
void test__hash_multiset_iterator_get_pointer__null_corepos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_pointer(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__null_hashtable(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_pointer(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__null_bucketpos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_pointer(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__invalid_container_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_hash_multiset_iterator_get_pointer(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__invalid_iterator_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_hash_multiset_iterator_get_pointer(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__end(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_end(pt_hash_multiset);

    expect_assert_failure(_hash_multiset_iterator_get_pointer(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__c_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 12;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(*(int*)_hash_multiset_iterator_get_pointer(it_iter) == 12);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__cstr(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(char*);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "abc");

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(strcmp((char*)_hash_multiset_iterator_get_pointer(it_iter), "abc") == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer__libcstl_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(vector_t<int>);
    hash_multiset_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    hash_multiset_init(pt_hash_multiset);
    vector_init_n(pvec, 10);
    hash_multiset_insert(pt_hash_multiset, pvec);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(vector_size((vector_t*)_hash_multiset_iterator_get_pointer(it_iter)) == 10);

    hash_multiset_destroy(pt_hash_multiset);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_multiset_iterator_get_pointer__user_define
{
    int elem;
}_test__hash_multiset_iterator_get_pointer__user_define_t;
void test__hash_multiset_iterator_get_pointer__user_define(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    hash_multiset_iterator_t it_iter;
    _test__hash_multiset_iterator_get_pointer__user_define_t elem;

    type_register(_test__hash_multiset_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multiset = create_hash_multiset(_test__hash_multiset_iterator_get_pointer__user_define_t);
    hash_multiset_init(pt_hash_multiset);
    elem.elem = 100;
    hash_multiset_insert(pt_hash_multiset, &elem);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(((_test__hash_multiset_iterator_get_pointer__user_define_t*)_hash_multiset_iterator_get_pointer(it_iter))->elem == 100);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_get_pointer_ignore_cstr)
void test__hash_multiset_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__null_hashtable(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__null_bucketpos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__invalid_container_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__invalid_iterator_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__end(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_end(pt_hash_multiset);

    expect_assert_failure(_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 12;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(*(int*)_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter) == 12);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(char*);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, "abc");

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(strcmp(string_c_str(_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(vector_t<int>);
    hash_multiset_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    hash_multiset_init(pt_hash_multiset);
    vector_init_n(pvec, 10);
    hash_multiset_insert(pt_hash_multiset, pvec);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(vector_size((vector_t*)_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter)) == 10);

    hash_multiset_destroy(pt_hash_multiset);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_multiset_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__hash_multiset_iterator_get_pointer_ignore_cstr__user_define_t;
void test__hash_multiset_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    hash_multiset_t* pt_hash_multiset = NULL;
    hash_multiset_iterator_t it_iter;
    _test__hash_multiset_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__hash_multiset_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_multiset = create_hash_multiset(_test__hash_multiset_iterator_get_pointer_ignore_cstr__user_define_t);
    hash_multiset_init(pt_hash_multiset);
    elem.elem = 100;
    hash_multiset_insert(pt_hash_multiset, &elem);

    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(((_test__hash_multiset_iterator_get_pointer_ignore_cstr__user_define_t*)_hash_multiset_iterator_get_pointer_ignore_cstr(it_iter))->elem == 100);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_iterator_next
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_next)
void test__hash_multiset_iterator_next__null_corepos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multiset_iterator_next(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_next__null_hashtable(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_next(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_next__null_bucketpos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multiset_iterator_next(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_next__invalid_container_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_containertype = 2394;
    expect_assert_failure(_hash_multiset_iterator_next(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_next__invalid_iterator_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_iteratortype = 44444;
    expect_assert_failure(_hash_multiset_iterator_next(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_next__end(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_end(pt_hash_multiset);

    expect_assert_failure(_hash_multiset_iterator_next(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_next__last(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 10;
    hash_multiset_init(pt_hash_multiset);

    hash_multiset_insert(pt_hash_multiset, elem);
    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter = _hash_multiset_iterator_next(it_iter);
    assert_true(_hash_multiset_iterator_equal(it_iter, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_next__begin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 10;
    hash_multiset_init(pt_hash_multiset);

    hash_multiset_insert(pt_hash_multiset, elem);
    elem = 3;
    hash_multiset_insert(pt_hash_multiset, elem);
    it_iter = hash_multiset_begin(pt_hash_multiset);
    assert_true(*(int*)_hash_multiset_iterator_get_pointer(it_iter) == 3);
    it_iter = _hash_multiset_iterator_next(it_iter);
    assert_true(*(int*)_hash_multiset_iterator_get_pointer(it_iter) == 10);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_iterator_prev
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_prev)
void test__hash_multiset_iterator_prev__null_corepos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_multiset_iterator_prev(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_prev__null_hashtable(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_prev(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_prev__null_bucketpos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_multiset_iterator_prev(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_prev__invalid_containter_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_containertype = 33333;
    expect_assert_failure(_hash_multiset_iterator_prev(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_prev__invalid_iterator_type(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    hash_multiset_init(pt_hash_multiset);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    it_iter._t_iteratortype = 5555;
    expect_assert_failure(_hash_multiset_iterator_prev(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_prev__begin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 100;
    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);

    it_iter = hash_multiset_begin(pt_hash_multiset);

    expect_assert_failure(_hash_multiset_iterator_prev(it_iter));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_prev__end(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 10;
    hash_multiset_init(pt_hash_multiset);

    hash_multiset_insert(pt_hash_multiset, elem);
    it_iter = hash_multiset_end(pt_hash_multiset);

    it_iter = _hash_multiset_iterator_prev(it_iter);
    assert_true(_hash_multiset_iterator_equal(it_iter, hash_multiset_begin(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_prev__last(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 10;
    hash_multiset_init(pt_hash_multiset);

    hash_multiset_insert(pt_hash_multiset, elem);
    elem = 3;
    hash_multiset_insert(pt_hash_multiset, elem);
    it_iter = _hash_multiset_iterator_prev(hash_multiset_end(pt_hash_multiset));
    assert_true(*(int*)_hash_multiset_iterator_get_pointer(it_iter) == 10);
    it_iter = _hash_multiset_iterator_prev(it_iter);
    assert_true(*(int*)_hash_multiset_iterator_get_pointer(it_iter) == 3);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_iterator_equal
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_equal)
void test__hash_multiset_iterator_equal__invalid_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_hash_multiset);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_equal(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_equal__invalid_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_hash_multiset);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    it_second._t_iteratortype = 45553;
    expect_assert_failure(_hash_multiset_iterator_equal(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_equal__not_same_hash_multiset(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);
    it_first = hash_multiset_begin(pt_first);
    it_second = hash_multiset_begin(pt_second);
    expect_assert_failure(_hash_multiset_iterator_equal(it_first, it_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test__hash_multiset_iterator_equal__equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    assert_true(_hash_multiset_iterator_equal(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_equal__not_equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    elem = 2;
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = _hash_multiset_iterator_next(it_first);
    assert_false(_hash_multiset_iterator_equal(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_iterator_distance
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_distance)
void test__hash_multiset_iterator_distance__invalid_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_hash_multiset);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_distance(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_distance__invalid_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_hash_multiset);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    it_second._t_containertype = 4444;
    expect_assert_failure(_hash_multiset_iterator_distance(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_distance__not_same_hash_multiset(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);
    it_first = hash_multiset_begin(pt_first);
    it_second = hash_multiset_begin(pt_second);
    expect_assert_failure(_hash_multiset_iterator_distance(it_first, it_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test__hash_multiset_iterator_distance__0(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    assert_true(_hash_multiset_iterator_distance(it_first, it_second) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_distance__greater_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    elem = 2;
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = _hash_multiset_iterator_next(it_first);
    assert_true(_hash_multiset_iterator_distance(it_first, it_second) == 1);

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_distance__less_0(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    elem = 2;
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_end(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    assert_true(_hash_multiset_iterator_distance(it_first, it_second) == -2);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test _hash_multiset_iterator_before
 */
UT_CASE_DEFINATION(_hash_multiset_iterator_before)
void test__hash_multiset_iterator_before__invalid_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_hash_multiset);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_multiset_iterator_before(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_before__invalid_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_hash_multiset);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    it_second._t_iteratortype = 999;
    expect_assert_failure(_hash_multiset_iterator_before(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_before__not_same_hash_multiset(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);
    it_first = hash_multiset_begin(pt_first);
    it_second = hash_multiset_begin(pt_second);
    expect_assert_failure(_hash_multiset_iterator_before(it_first, it_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test__hash_multiset_iterator_before__equal(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    assert_false(_hash_multiset_iterator_before(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_before__true(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    elem = 2;
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_begin(pt_hash_multiset);
    it_second = _hash_multiset_iterator_next(it_first);
    assert_true(_hash_multiset_iterator_before(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

void test__hash_multiset_iterator_before__false(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_first;
    hash_multiset_iterator_t it_second;
    int elem = 100;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    elem = 2;
    hash_multiset_insert(pt_hash_multiset, elem);
    it_first = hash_multiset_end(pt_hash_multiset);
    it_second = hash_multiset_begin(pt_hash_multiset);
    assert_false(_hash_multiset_iterator_before(it_first, it_second));

    hash_multiset_destroy(pt_hash_multiset);
}

