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
#include "ut_cstl_hash_set_iterator.h"

UT_SUIT_DEFINATION(cstl_hash_set_iterator, create_hash_set_iterator)
/*
 * test _create_hash_set_iterator
 */
UT_CASE_DEFINATION(create_hash_set_iterator)
void test_create_hash_set_iterator__successfully(void** state)
{
    hash_set_iterator_t it_iter = create_hash_set_iterator();
    assert_true(it_iter._t_pos._t_treepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_treepos._pt_tree == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _HASH_SET_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

/*
 * test _hash_set_iterator_get_value
 */
UT_CASE_DEFINATION(_hash_set_iterator_get_value)
void test__hash_set_iterator_get_value__null_corepos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 0;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_set_iterator_get_value(it_iter, &elem));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__null_hashtable(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 0;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_get_value(it_iter, &elem));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__null_bucketpos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 0;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_set_iterator_get_value(it_iter, &elem));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__invalid_container_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 0;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_containertype = 1000;
    expect_assert_failure(_hash_set_iterator_get_value(it_iter, &elem));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__invalid_iterator_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 0;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_iteratortype = 1000;
    expect_assert_failure(_hash_set_iterator_get_value(it_iter, &elem));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__end(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 0;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_end(pt_hash_set);

    expect_assert_failure(_hash_set_iterator_get_value(it_iter, &elem));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__null_value(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_end(pt_hash_set);

    expect_assert_failure(_hash_set_iterator_get_value(it_iter, NULL));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__c_builtin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 12;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);

    it_iter = hash_set_begin(pt_hash_set);
    elem = 0;
    _hash_set_iterator_get_value(it_iter, &elem);
    assert_true(elem == 12);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__cstr(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(char*);
    hash_set_iterator_t it_iter;
    char* p = NULL;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "abc");

    it_iter = hash_set_begin(pt_hash_set);
    _hash_set_iterator_get_value(it_iter, &p);
    assert_true(strcmp(p, "abc") == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_value__libcstl_builtin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(vector_t<int>);
    hash_set_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    hash_set_init(pt_hash_set);
    vector_init_n(pvec, 10);
    hash_set_insert(pt_hash_set, pvec);

    it_iter = hash_set_begin(pt_hash_set);
    vector_clear(pvec);
    _hash_set_iterator_get_value(it_iter, pvec);
    assert_true(vector_size(pvec) == 10);

    hash_set_destroy(pt_hash_set);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_set_iterator_get_value__user_define
{
    int elem;
}_test__hash_set_iterator_get_value__user_define_t;
void test__hash_set_iterator_get_value__user_define(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    hash_set_iterator_t it_iter;
    _test__hash_set_iterator_get_value__user_define_t elem;

    type_register(_test__hash_set_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_set = create_hash_set(_test__hash_set_iterator_get_value__user_define_t);
    hash_set_init(pt_hash_set);
    elem.elem = 100;
    hash_set_insert(pt_hash_set, &elem);

    it_iter = hash_set_begin(pt_hash_set);
    elem.elem = 0;
    _hash_set_iterator_get_value(it_iter, &elem);
    assert_true(elem.elem == 100);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_iterator_get_pointer
 */
UT_CASE_DEFINATION(_hash_set_iterator_get_pointer)
void test__hash_set_iterator_get_pointer__null_corepos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_set_iterator_get_pointer(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__null_hashtable(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_get_pointer(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__null_bucketpos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_set_iterator_get_pointer(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__invalid_container_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_hash_set_iterator_get_pointer(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__invalid_iterator_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_hash_set_iterator_get_pointer(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__end(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_end(pt_hash_set);

    expect_assert_failure(_hash_set_iterator_get_pointer(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__c_builtin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 12;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(*(int*)_hash_set_iterator_get_pointer(it_iter) == 12);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__cstr(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(char*);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "abc");

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(strcmp((char*)_hash_set_iterator_get_pointer(it_iter), "abc") == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer__libcstl_builtin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(vector_t<int>);
    hash_set_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    hash_set_init(pt_hash_set);
    vector_init_n(pvec, 10);
    hash_set_insert(pt_hash_set, pvec);

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(vector_size((vector_t*)_hash_set_iterator_get_pointer(it_iter)) == 10);

    hash_set_destroy(pt_hash_set);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_set_iterator_get_pointer__user_define
{
    int elem;
}_test__hash_set_iterator_get_pointer__user_define_t;
void test__hash_set_iterator_get_pointer__user_define(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    hash_set_iterator_t it_iter;
    _test__hash_set_iterator_get_pointer__user_define_t elem;

    type_register(_test__hash_set_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_set = create_hash_set(_test__hash_set_iterator_get_pointer__user_define_t);
    hash_set_init(pt_hash_set);
    elem.elem = 100;
    hash_set_insert(pt_hash_set, &elem);

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(((_test__hash_set_iterator_get_pointer__user_define_t*)_hash_set_iterator_get_pointer(it_iter))->elem == 100);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_hash_set_iterator_get_pointer_ignore_cstr)
void test__hash_set_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_set_iterator_get_pointer_ignore_cstr(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__null_hashtable(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_get_pointer_ignore_cstr(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__null_bucketpos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_set_iterator_get_pointer_ignore_cstr(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__invalid_container_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_containertype = 9384;
    expect_assert_failure(_hash_set_iterator_get_pointer_ignore_cstr(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__invalid_iterator_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_iteratortype = 3333;
    expect_assert_failure(_hash_set_iterator_get_pointer_ignore_cstr(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__end(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_end(pt_hash_set);

    expect_assert_failure(_hash_set_iterator_get_pointer_ignore_cstr(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 12;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(*(int*)_hash_set_iterator_get_pointer_ignore_cstr(it_iter) == 12);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(char*);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, "abc");

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(strcmp(string_c_str(_hash_set_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(vector_t<int>);
    hash_set_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    hash_set_init(pt_hash_set);
    vector_init_n(pvec, 10);
    hash_set_insert(pt_hash_set, pvec);

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(vector_size((vector_t*)_hash_set_iterator_get_pointer_ignore_cstr(it_iter)) == 10);

    hash_set_destroy(pt_hash_set);
    vector_destroy(pvec);
}

typedef struct _tag_test__hash_set_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__hash_set_iterator_get_pointer_ignore_cstr__user_define_t;
void test__hash_set_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    hash_set_t* pt_hash_set = NULL;
    hash_set_iterator_t it_iter;
    _test__hash_set_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__hash_set_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_hash_set = create_hash_set(_test__hash_set_iterator_get_pointer_ignore_cstr__user_define_t);
    hash_set_init(pt_hash_set);
    elem.elem = 100;
    hash_set_insert(pt_hash_set, &elem);

    it_iter = hash_set_begin(pt_hash_set);
    assert_true(((_test__hash_set_iterator_get_pointer_ignore_cstr__user_define_t*)_hash_set_iterator_get_pointer_ignore_cstr(it_iter))->elem == 100);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_iterator_next
 */
UT_CASE_DEFINATION(_hash_set_iterator_next)
void test__hash_set_iterator_next__null_corepos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_set_iterator_next(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_next__null_hashtable(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_next(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_next__null_bucketpos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_set_iterator_next(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_next__invalid_container_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_containertype = 2394;
    expect_assert_failure(_hash_set_iterator_next(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_next__invalid_iterator_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_iteratortype = 44444;
    expect_assert_failure(_hash_set_iterator_next(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_next__end(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_end(pt_hash_set);

    expect_assert_failure(_hash_set_iterator_next(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_next__last(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 10;
    hash_set_init(pt_hash_set);

    hash_set_insert(pt_hash_set, elem);
    it_iter = hash_set_begin(pt_hash_set);

    it_iter = _hash_set_iterator_next(it_iter);
    assert_true(_hash_set_iterator_equal(it_iter, hash_set_end(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_next__begin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 10;
    hash_set_init(pt_hash_set);

    hash_set_insert(pt_hash_set, elem);
    elem = 3;
    hash_set_insert(pt_hash_set, elem);
    it_iter = hash_set_begin(pt_hash_set);
    assert_true(*(int*)_hash_set_iterator_get_pointer(it_iter) == 3);
    it_iter = _hash_set_iterator_next(it_iter);
    assert_true(*(int*)_hash_set_iterator_get_pointer(it_iter) == 10);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_iterator_prev
 */
UT_CASE_DEFINATION(_hash_set_iterator_prev)
void test__hash_set_iterator_prev__null_corepos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_corepos = NULL;
    expect_assert_failure(_hash_set_iterator_prev(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_prev__null_hashtable(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_prev(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_prev__null_bucketpos(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hash_set_iterator_prev(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_prev__invalid_containter_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_containertype = 33333;
    expect_assert_failure(_hash_set_iterator_prev(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_prev__invalid_iterator_type(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    hash_set_init(pt_hash_set);

    it_iter = hash_set_begin(pt_hash_set);

    it_iter._t_iteratortype = 5555;
    expect_assert_failure(_hash_set_iterator_prev(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_prev__begin(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 100;
    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);

    it_iter = hash_set_begin(pt_hash_set);

    expect_assert_failure(_hash_set_iterator_prev(it_iter));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_prev__end(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 10;
    hash_set_init(pt_hash_set);

    hash_set_insert(pt_hash_set, elem);
    it_iter = hash_set_end(pt_hash_set);

    it_iter = _hash_set_iterator_prev(it_iter);
    assert_true(_hash_set_iterator_equal(it_iter, hash_set_begin(pt_hash_set)));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_prev__last(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_iter;
    int elem = 10;
    hash_set_init(pt_hash_set);

    hash_set_insert(pt_hash_set, elem);
    elem = 3;
    hash_set_insert(pt_hash_set, elem);
    it_iter = _hash_set_iterator_prev(hash_set_end(pt_hash_set));
    assert_true(*(int*)_hash_set_iterator_get_pointer(it_iter) == 10);
    it_iter = _hash_set_iterator_prev(it_iter);
    assert_true(*(int*)_hash_set_iterator_get_pointer(it_iter) == 3);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_iterator_equal
 */
UT_CASE_DEFINATION(_hash_set_iterator_equal)
void test__hash_set_iterator_equal__invalid_first(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_hash_set);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_equal(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_equal__invalid_second(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_hash_set);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    it_second._t_iteratortype = 45553;
    expect_assert_failure(_hash_set_iterator_equal(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_equal__not_same_hash_set(void** state)
{
    hash_set_t* pt_first = create_hash_set(int);
    hash_set_t* pt_second = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_first);
    hash_set_init(pt_second);
    it_first = hash_set_begin(pt_first);
    it_second = hash_set_begin(pt_second);
    expect_assert_failure(_hash_set_iterator_equal(it_first, it_second));

    hash_set_destroy(pt_first);
    hash_set_destroy(pt_second);
}

void test__hash_set_iterator_equal__equal(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    assert_true(_hash_set_iterator_equal(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_equal__not_equal(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    elem = 2;
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_begin(pt_hash_set);
    it_second = _hash_set_iterator_next(it_first);
    assert_false(_hash_set_iterator_equal(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_iterator_distance
 */
UT_CASE_DEFINATION(_hash_set_iterator_distance)
void test__hash_set_iterator_distance__invalid_first(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_hash_set);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_distance(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_distance__invalid_second(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_hash_set);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    it_second._t_containertype = 4444;
    expect_assert_failure(_hash_set_iterator_distance(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_distance__not_same_hash_set(void** state)
{
    hash_set_t* pt_first = create_hash_set(int);
    hash_set_t* pt_second = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_first);
    hash_set_init(pt_second);
    it_first = hash_set_begin(pt_first);
    it_second = hash_set_begin(pt_second);
    expect_assert_failure(_hash_set_iterator_distance(it_first, it_second));

    hash_set_destroy(pt_first);
    hash_set_destroy(pt_second);
}

void test__hash_set_iterator_distance__0(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    assert_true(_hash_set_iterator_distance(it_first, it_second) == 0);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_distance__greater_0(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    elem = 2;
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_begin(pt_hash_set);
    it_second = _hash_set_iterator_next(it_first);
    assert_true(_hash_set_iterator_distance(it_first, it_second) == 1);

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_distance__less_0(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    elem = 2;
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_end(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    assert_true(_hash_set_iterator_distance(it_first, it_second) == -2);

    hash_set_destroy(pt_hash_set);
}

/*
 * test _hash_set_iterator_before
 */
UT_CASE_DEFINATION(_hash_set_iterator_before)
void test__hash_set_iterator_before__invalid_first(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_hash_set);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hash_set_iterator_before(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_before__invalid_second(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_hash_set);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    it_second._t_iteratortype = 999;
    expect_assert_failure(_hash_set_iterator_before(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_before__not_same_hash_set(void** state)
{
    hash_set_t* pt_first = create_hash_set(int);
    hash_set_t* pt_second = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;

    hash_set_init(pt_first);
    hash_set_init(pt_second);
    it_first = hash_set_begin(pt_first);
    it_second = hash_set_begin(pt_second);
    expect_assert_failure(_hash_set_iterator_before(it_first, it_second));

    hash_set_destroy(pt_first);
    hash_set_destroy(pt_second);
}

void test__hash_set_iterator_before__equal(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_begin(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    assert_false(_hash_set_iterator_before(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_before__true(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    elem = 2;
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_begin(pt_hash_set);
    it_second = _hash_set_iterator_next(it_first);
    assert_true(_hash_set_iterator_before(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

void test__hash_set_iterator_before__false(void** state)
{
    hash_set_t* pt_hash_set = create_hash_set(int);
    hash_set_iterator_t it_first;
    hash_set_iterator_t it_second;
    int elem = 100;

    hash_set_init(pt_hash_set);
    hash_set_insert(pt_hash_set, elem);
    elem = 2;
    hash_set_insert(pt_hash_set, elem);
    it_first = hash_set_end(pt_hash_set);
    it_second = hash_set_begin(pt_hash_set);
    assert_false(_hash_set_iterator_before(it_first, it_second));

    hash_set_destroy(pt_hash_set);
}

