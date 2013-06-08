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
#include "cstl/cslist.h"
#include "cstl/cdeque.h"
#include "cstl/cset.h"
#include "cstl_vector_aux.h"
#include "cstl_hashtable_aux.h"
#include "cstl_hash_multiset_aux.h"

#include "ut_def.h"
#include "ut_cstl_hash_multiset.h"

UT_SUIT_DEFINATION(cstl_hash_multiset, hash_multiset_init)

/*
 * test hash_multiset_init
 */
UT_CASE_DEFINATION(hash_multiset_init)
void test_hash_multiset_init__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_init(NULL));
}

void test_hash_multiset_init__non_created(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    pt_hash_multiset->_t_hashtable._ufun_hash = (unary_function_t)0x999;
    expect_assert_failure(hash_multiset_init(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._ufun_hash = NULL;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init__null_compare(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    assert_true(_hashtable_is_inited(&pt_hash_multiset->_t_hashtable));

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_init_ex
 */
UT_CASE_DEFINATION(hash_multiset_init_ex)
void test_hash_multiset_init_ex__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_init_ex(NULL, 0, NULL, NULL));
}

void test_hash_multiset_init_ex__non_created(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_ex__0_bucket(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_hash_multiset->_t_hashtable));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_ex__non_0_bucket(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_hash_multiset->_t_hashtable));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_ex__null_hash(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_hash_multiset->_t_hashtable));

    hash_multiset_destroy(pt_hash_multiset);
}

static void _test_hash_multiset_init_ex__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_init_ex__non_null_hash(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 0, _test_hash_multiset_init_ex__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(&pt_hash_multiset->_t_hashtable));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_ex__null_compare(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_hash_multiset->_t_hashtable));

    hash_multiset_destroy(pt_hash_multiset);
}

static void _test_hash_multiset_init_ex__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_init_ex__non_null_compare(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, _test_hash_multiset_init_ex__non_null_compare);
    assert_true(_hashtable_is_inited(&pt_hash_multiset->_t_hashtable));
    assert_true(pt_hash_multiset->_t_hashtable._bfun_compare == _test_hash_multiset_init_ex__non_null_compare);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_init_copy
 */
UT_CASE_DEFINATION(hash_multiset_init_copy)
void test_hash_multiset_init_copy__null_dest(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    expect_assert_failure(hash_multiset_init_copy(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_copy__null_src(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    expect_assert_failure(hash_multiset_init_copy(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_copy__non_created_dest(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    pt_dest->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_init_copy(pt_dest, pt_src));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy__non_inited_src(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    pt_src->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_init_copy(pt_dest, pt_src));
    pt_src->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy__not_same_type(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(double);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    expect_assert_failure(hash_multiset_init_copy(pt_dest, pt_src));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy__empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(signed int);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy__non_empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(signed int);
    int elem = 100;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    hash_multiset_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy__non_0_bucket(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(signed int);
    int i = 0;

    hash_multiset_init_ex(pt_src, 100, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_src, i);
    }
    hash_multiset_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);
    assert_true(hash_multiset_bucket_count(pt_dest) == 193);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test_hash_multiset_init_copy__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_init_copy__non_null_hash(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(signed int);
    int i = 0;

    hash_multiset_init_ex(pt_src, 0, _test_hash_multiset_init_copy__non_null_hash, NULL);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_src, i);
    }
    hash_multiset_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);
    assert_true(hash_multiset_hash(pt_dest) == _test_hash_multiset_init_copy__non_null_hash);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test_hash_multiset_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_init_copy__non_null_compare(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(signed int);
    int i = 0;

    hash_multiset_init_ex(pt_src, 0, NULL, _test_hash_multiset_init_copy__non_null_compare);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_src, i);
    }
    hash_multiset_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);
    assert_true(hash_multiset_key_comp(pt_dest) == _test_hash_multiset_init_copy__non_null_compare);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

/*
 * test hash_multiset_init_copy_range
 */
UT_CASE_DEFINATION(hash_multiset_init_copy_range)
void test_hash_multiset_init_copy_range__null_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    expect_assert_failure(hash_multiset_init_copy_range(NULL, hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_copy_range__non_created_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_dest->_t_hashtable._t_typeinfo._t_style = 99;
    expect_assert_failure(hash_multiset_init_copy_range(pt_dest, hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset)));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_range__invalid_begin(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    it_begin._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(hash_multiset_init_copy_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range__invalid_end(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    it_end._t_iteratortype = 44444;
    expect_assert_failure(hash_multiset_init_copy_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range__invalid_range(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    expect_assert_failure(hash_multiset_init_copy_range(pt_dest, it_end, it_begin));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range__invalid_range_not_same_type(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(double);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    expect_assert_failure(hash_multiset_init_copy_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range__empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range__non_empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_equal(pt_dest, pt_src));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range__non_empty_dup(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 100);
    hash_multiset_init_copy_range(phmset, vector_begin(pvec), vector_end(pvec));
    assert_true(_hashtable_is_inited(&phmset->_t_hashtable));
    assert_true(hash_multiset_size(phmset) == 10);

    hash_multiset_destroy(phmset);
    vector_destroy(pvec);
}

void test_hash_multiset_init_copy_range__non_0_bucket(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 100, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_bucket_count(pt_dest) == 53);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test_hash_multiset_init_copy_range__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_init_copy_range__non_null_hash(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, _test_hash_multiset_init_copy_range__non_null_hash, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_hash(pt_dest) == _hashtable_default_hash);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test_hash_multiset_init_copy_range__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_init_copy_range__non_null_compare(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, _test_hash_multiset_init_copy_range__non_null_compare);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_key_comp(pt_dest) != _test_hash_multiset_init_copy_range__non_null_compare);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range__other(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 100);
    hash_multiset_init_copy_range(phmset, vector_begin(pvec), vector_end(pvec));
    assert_true(hash_multiset_size(phmset) == 10);

    vector_destroy(pvec);
    hash_multiset_destroy(phmset);
}

void test_hash_multiset_init_copy_range__other_not_same(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(double);
    list_t* plist = create_list(int);

    list_init_elem(plist, 1, 1);
    expect_assert_failure(hash_multiset_init_copy_range(phmset, list_begin(plist), list_end(plist)));

    list_destroy(plist);
    hash_multiset_destroy(phmset);
}

/*
 * test hash_multiset_init_copy_array
 */
UT_CASE_DEFINATION(hash_multiset_init_copy_array)
void test_hash_multiset_init_copy_array__null_hash_multiset(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(hash_multiset_init_copy_array(NULL, an_array, 10));
}

void test_hash_multiset_init_copy_array__non_created_hash_multiset(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    pt_dest->_t_hashtable._t_typeinfo._t_style = 99;
    expect_assert_failure(hash_multiset_init_copy_array(pt_dest, an_array, 10));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array__invalid_array(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    expect_assert_failure(hash_multiset_init_copy_array(pt_dest, NULL, 10));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array__empty(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init_copy_array(pt_dest, an_array, 0);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array__non_empty(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    hash_multiset_init_copy_array(pt_dest, an_array, 10);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* phmset = create_hash_multiset(int);

    hash_multiset_init_copy_array(phmset, an_array, 10);
    assert_true(_hashtable_is_inited(&phmset->_t_hashtable));
    assert_true(hash_multiset_size(phmset) == 10);

    hash_multiset_destroy(phmset);
}

/*
 * test hash_multiset_init_copy_range_ex
 */
UT_CASE_DEFINATION(hash_multiset_init_copy_range_ex)
void test_hash_multiset_init_copy_range_ex__null_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    expect_assert_failure(hash_multiset_init_copy_range_ex(NULL, hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset), 0, NULL, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_init_copy_range_ex__non_created_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_dest->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_init_copy_range_ex(pt_dest, hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset), 0, NULL, NULL));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_range_ex__invalid_begin(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    it_begin._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 0, NULL, NULL));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range_ex__invalid_end(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    it_end._t_iteratortype = 33333;
    expect_assert_failure(hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 0, NULL, NULL));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range_ex__invalid_range(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    expect_assert_failure(hash_multiset_init_copy_range_ex(pt_dest, it_end, it_begin, 0, NULL, NULL));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range_ex__invalid_range_not_same_type(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(double);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    expect_assert_failure(hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 0, NULL, NULL));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range_ex__empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range_ex__non_empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_equal(pt_dest, pt_src));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range_ex__non_0_bucket(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_bucket_count(pt_dest) == 193);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test_hash_multiset_init_copy_range_ex__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_init_copy_range_ex__hash(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 0, _test_hash_multiset_init_copy_range_ex__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_hash(pt_dest) == _test_hash_multiset_init_copy_range_ex__non_null_hash);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test__hash_multiset_init_compare_range_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_init_copy_range_ex__compare(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_init_copy_range_ex(pt_dest, it_begin, it_end, 0, NULL, _test__hash_multiset_init_compare_range_ex__compare);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(hash_multiset_key_comp(pt_dest) == _test__hash_multiset_init_compare_range_ex__compare);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_init_copy_range_ex__other(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 10);
    hash_multiset_init_copy_range_ex(phmset, slist_begin(pslist), slist_end(pslist), 0, NULL, NULL);
    assert_true(hash_multiset_size(phmset) == 10);

    slist_destroy(pslist);
    hash_multiset_destroy(phmset);
}

void test_hash_multiset_init_copy_range_ex__other_not_same(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(double);
    deque_t* pdeq = create_deque(int);

    deque_init_elem(pdeq, 10, 10);
    expect_assert_failure(hash_multiset_init_copy_range_ex(phmset, deque_begin(pdeq), deque_end(pdeq), 0, NULL, NULL));

    deque_destroy(pdeq);
    hash_multiset_destroy(phmset);
}

/*
 * test hash_multiset_init_copy_array_ex
 */
UT_CASE_DEFINATION(hash_multiset_init_copy_array_ex)
void test_hash_multiset_init_copy_array_ex__null_hash_multiset(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(hash_multiset_init_copy_array_ex(NULL, an_array, 10, 0, NULL, NULL));
}

void test_hash_multiset_init_copy_array_ex__non_created_hash_multiset(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    pt_dest->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_init_copy_array_ex(pt_dest, an_array, 10, 0, NULL, NULL));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array_ex__invalid_array(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    expect_assert_failure(hash_multiset_init_copy_array_ex(pt_dest, NULL, 10, 0, NULL, NULL));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array_ex__empty(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init_copy_array_ex(pt_dest, an_array, 0, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array_ex__non_empty(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    hash_multiset_init_copy_array_ex(pt_dest, an_array, 10, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_init_copy_array_ex__non_0_bucket(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init_copy_array_ex(pt_dest, an_array, 10, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);
    assert_true(hash_multiset_bucket_count(pt_dest) == 193);

    hash_multiset_destroy(pt_dest);
}

static void _test_hash_multiset_init_copy_array_ex__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_init_copy_array_ex__hash(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init_copy_array_ex(pt_dest, an_array, 10, 0, _test_hash_multiset_init_copy_array_ex__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);
    assert_true(hash_multiset_hash(pt_dest) == _test_hash_multiset_init_copy_array_ex__non_null_hash);

    hash_multiset_destroy(pt_dest);
}

static void _test__hash_multiset_init_compare_array_ex__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_init_copy_array_ex__compare(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init_copy_array_ex(pt_dest, an_array, 10, 0, NULL, _test__hash_multiset_init_compare_array_ex__compare);
    assert_true(_hashtable_is_inited(&pt_dest->_t_hashtable));
    assert_true(hash_multiset_size(pt_dest) == 10);
    assert_true(hash_multiset_key_comp(pt_dest) == _test__hash_multiset_init_compare_array_ex__compare);

    hash_multiset_destroy(pt_dest);
}

/*
 * test hash_multiset_destroy
 */
UT_CASE_DEFINATION(hash_multiset_destroy)
void test_hash_multiset_destroy__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_destroy(NULL));
}

void test_hash_multiset_destroy__non_created(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_destroy(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_destroy__created(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_destroy__inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_assign
 */
UT_CASE_DEFINATION(hash_multiset_assign)
void test_hash_multiset_assign__null_dest(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    expect_assert_failure(hash_multiset_assign(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_assign__null_src(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    expect_assert_failure(hash_multiset_assign(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_assign__non_created_dest(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    pt_dest->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_assign(pt_dest, pt_src));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__non_init_src(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    pt_src->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_assign(pt_dest, pt_src));
    pt_src->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__not_same_type(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(double);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    expect_assert_failure(hash_multiset_assign(pt_dest, pt_src));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__empty_empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    hash_multiset_assign(pt_dest, pt_src);
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__non_empty_empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    hash_multiset_insert(pt_dest, elem);
    hash_multiset_assign(pt_dest, pt_src);
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__non_empty_non_empty_less(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    elem = 222;
    hash_multiset_insert(pt_src, elem);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    elem = 897;
    hash_multiset_insert(pt_dest, elem);
    hash_multiset_assign(pt_dest, pt_src);
    assert_true(hash_multiset_size(pt_dest) == 2);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__non_empty_non_empty_size_equal(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    elem = 334;
    hash_multiset_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_dest)) == 334);
    hash_multiset_assign(pt_dest, pt_src);
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_dest)) == 9);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__non_empty_non_empty_equal(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    hash_multiset_insert(pt_dest, elem);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_dest)) == 9);
    hash_multiset_assign(pt_dest, pt_src);
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_dest)) == 9);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__non_empty_non_empty_greater(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    elem = 876;
    hash_multiset_insert(pt_dest, elem);
    elem = 333;
    hash_multiset_insert(pt_dest, elem);
    hash_multiset_assign(pt_dest, pt_src);
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_dest)) == 9);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_assign__empty_non_empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_src, 0, NULL, NULL);
    hash_multiset_insert(pt_src, elem);
    hash_multiset_init_ex(pt_dest, 0, NULL, NULL);
    hash_multiset_assign(pt_dest, pt_src);
    assert_true(hash_multiset_size(pt_dest) == 1);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_dest)) == 9);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

/*
 * test hash_multiset_size
 */
UT_CASE_DEFINATION(hash_multiset_size)
void test_hash_multiset_size__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_size(NULL));
}

void test_hash_multiset_size__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_size(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_size__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(hash_multiset_size(pt_hash_multiset) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_size__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    hash_multiset_insert(pt_hash_multiset, elem);

    assert_true(hash_multiset_size(pt_hash_multiset) == 1);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_empty
 */
UT_CASE_DEFINATION(hash_multiset_empty)
void test_hash_multiset_empty__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_empty(NULL));
}

void test_hash_multiset_empty__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_empty(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_empty__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(hash_multiset_empty(pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_empty__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    hash_multiset_insert(pt_hash_multiset, elem);

    assert_false(hash_multiset_empty(pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_max_size
 */
UT_CASE_DEFINATION(hash_multiset_max_size)
void test_hash_multiset_max_size__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_max_size(NULL));
}

void test_hash_multiset_max_size__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 3333;
    expect_assert_failure(hash_multiset_max_size(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_max_size__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(hash_multiset_max_size(pt_hash_multiset) > 0);

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_max_size__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    hash_multiset_insert(pt_hash_multiset, elem);

    assert_true(hash_multiset_max_size(pt_hash_multiset) > 0);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_bucket_count
 */
UT_CASE_DEFINATION(hash_multiset_bucket_count)
void test_hash_multiset_bucket_count__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_bucket_count(NULL));
}

void test_hash_multiset_bucket_count__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 3333;
    expect_assert_failure(hash_multiset_bucket_count(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_bucket_count__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(hash_multiset_bucket_count(pt_hash_multiset) == 53);

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_bucket_count__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_hash_multiset, 100, NULL, NULL);
    hash_multiset_insert(pt_hash_multiset, elem);

    assert_true(hash_multiset_bucket_count(pt_hash_multiset) == 193);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_begin
 */
UT_CASE_DEFINATION(hash_multiset_begin)
void test_hash_multiset_begin__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_begin(NULL));
}

void test_hash_multiset_begin__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_begin(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_begin__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(_hash_multiset_iterator_equal(hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_begin__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    hash_multiset_insert(pt_hash_multiset, elem);

    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_hash_multiset)) == 9);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_end
 */
UT_CASE_DEFINATION(hash_multiset_end)
void test_hash_multiset_end__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_end(NULL));
}

void test_hash_multiset_end__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_end(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_end__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(iterator_equal(hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_end__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_iter;
    int elem = 9;

    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);
    hash_multiset_insert(pt_hash_multiset, elem);

    it_iter = hash_multiset_end(pt_hash_multiset);
    it_iter = iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_key_comp
 */
UT_CASE_DEFINATION(hash_multiset_key_comp)
void test_hash_multiset_key_comp__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_key_comp(NULL));
}

void test_hash_multiset_key_comp__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_key_comp(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_key_comp__default_key_comp(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(hash_multiset_key_comp(pt_hash_multiset) == _GET_HASH_MULTISET_TYPE_LESS_FUNCTION(pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void _test_hash_multiset_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test_hash_multiset_key_comp__user_define_key_comp(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, _test_hash_multiset_key_comp__user_define_key_comp);

    assert_true(hash_multiset_key_comp(pt_hash_multiset) == _test_hash_multiset_key_comp__user_define_key_comp);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_hash
 */
UT_CASE_DEFINATION(hash_multiset_hash)
void test_hash_multiset_hash__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_hash(NULL));
}

void test_hash_multiset_hash__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_hash(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_hash__default_hash(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(hash_multiset_hash(pt_hash_multiset) == _hashtable_default_hash);

    hash_multiset_destroy(pt_hash_multiset);
}

void _test_hash_multiset_hash__user_define_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}

void test_hash_multiset_hash__user_define_hash(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, _test_hash_multiset_hash__user_define_hash, NULL);

    assert_true(hash_multiset_hash(pt_hash_multiset) == _test_hash_multiset_hash__user_define_hash);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_clear
 */
UT_CASE_DEFINATION(hash_multiset_clear)
void test_hash_multiset_clear__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_clear(NULL));
}

void test_hash_multiset_clear__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_clear(pt_hash_multiset));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_clear__empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    assert_true(hash_multiset_empty(pt_hash_multiset));
    hash_multiset_clear(pt_hash_multiset);
    assert_true(hash_multiset_empty(pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_clear__non_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    int elem = 8;
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    hash_multiset_insert(pt_hash_multiset, elem);
    assert_false(hash_multiset_empty(pt_hash_multiset));
    hash_multiset_clear(pt_hash_multiset);
    assert_true(hash_multiset_empty(pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_equal
 */
UT_CASE_DEFINATION(hash_multiset_equal)
void test_hash_multiset_equal__null_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 0, NULL, NULL);

    expect_assert_failure(hash_multiset_equal(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_equal__null_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_equal(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_equal__non_inited_first(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init_ex(pt_first, 0, NULL, NULL);
    hash_multiset_init_ex(pt_second, 0, NULL, NULL);

    pt_first->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_equal(pt_first, pt_second));
    pt_first->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__non_inited_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init_ex(pt_first, 0, NULL, NULL);
    hash_multiset_init_ex(pt_second, 0, NULL, NULL);

    pt_second->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_equal(pt_first, pt_second));
    pt_second->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__not_same_type(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(list_t<int>);

    hash_multiset_init_ex(pt_first, 0, NULL, NULL);
    hash_multiset_init_ex(pt_second, 0, NULL, NULL);

    expect_assert_failure(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__same_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    assert_true(hash_multiset_equal(pt_hash_multiset, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_equal__size_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(signed int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__size_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__size_equal_0(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    assert_true(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__size_equal_elem_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__size_equal_elem_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 30; i < 40; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init_ex(pt_first, 0, NULL, NULL);
    hash_multiset_init_ex(pt_second, 100, NULL, NULL);

    assert_false(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_equal__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_equal__not_same_hash(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init_ex(pt_first, 0, _test_hash_multiset_equal__not_same_hash, NULL);
    hash_multiset_init_ex(pt_second, 0, NULL, NULL);

    expect_assert_failure(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_equal__compare_not_equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, NULL, _test_hash_multiset_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_equal__equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

/*
 * test hash_multiset_not_equal
 */
UT_CASE_DEFINATION(hash_multiset_not_equal)
void test_hash_multiset_not_equal__null_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_not_equal(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_not_equal__null_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_not_equal(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_not_equal__non_inited_first(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_first->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_not_equal(pt_first, pt_second));
    pt_first->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__non_inited_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_second->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_not_equal(pt_first, pt_second));
    pt_second->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__not_same_type(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(list_t<int>);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    expect_assert_failure(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__same_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    assert_false(hash_multiset_not_equal(pt_hash_multiset, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_not_equal__size_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(signed int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__size_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__size_equal_0(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    assert_false(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 30; i < 40; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 100, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_not_equal__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_not_equal__not_same_hash(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, _test_hash_multiset_not_equal__not_same_hash, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_not_equal__compare_not_equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, NULL, _test_hash_multiset_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_not_equal__equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_not_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

/*
 * test hash_multiset_less
 */
UT_CASE_DEFINATION(hash_multiset_less)
void test_hash_multiset_less__null_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_less(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_less__null_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_less(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_less__non_inited_first(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_first->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_less(pt_first, pt_second));
    pt_first->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__non_inited_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_second->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_less(pt_first, pt_second));
    pt_second->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__not_same_type(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(list_t<int>);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    expect_assert_failure(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__same_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    assert_false(hash_multiset_less(pt_hash_multiset, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_less__size_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(signed int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__size_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__size_equal_0(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    assert_false(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__size_equal_elem_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__size_equal_elem_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 30; i < 40; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 100, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_less__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_less__not_same_hash(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, _test_hash_multiset_less__not_same_hash, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_less__compare_less(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, NULL, _test_hash_multiset_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less__equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_less(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

/*
 * test hash_multiset_less_equal
 */
UT_CASE_DEFINATION(hash_multiset_less_equal)
void test_hash_multiset_less_equal__null_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_less_equal(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_less_equal__null_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_less_equal(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_less_equal__non_inited_first(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_first->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_less_equal(pt_first, pt_second));
    pt_first->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__non_inited_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_second->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_less_equal(pt_first, pt_second));
    pt_second->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__not_same_type(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(list_t<int>);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    expect_assert_failure(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__same_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    assert_true(hash_multiset_less_equal(pt_hash_multiset, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_less_equal__size_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(signed int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__size_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__size_equal_0(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    assert_true(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 30; i < 40; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 100, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_less_equal__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_less_equal__not_same_hash(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, _test_hash_multiset_less_equal__not_same_hash, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_less_equal__compare_less(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, NULL, _test_hash_multiset_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_less_equal__equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_less_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

/*
 * test hash_multiset_greater
 */
UT_CASE_DEFINATION(hash_multiset_greater)
void test_hash_multiset_greater__null_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_greater(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_greater__null_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_greater(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_greater__non_inited_first(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_first->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_greater(pt_first, pt_second));
    pt_first->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__non_inited_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_second->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_greater(pt_first, pt_second));
    pt_second->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__not_same_type(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(list_t<int>);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    expect_assert_failure(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__same_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    assert_false(hash_multiset_greater(pt_hash_multiset, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_greater__size_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(signed int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__size_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__size_equal_0(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    assert_false(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__size_equal_elem_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__size_equal_elem_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 30; i < 40; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 890, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_greater__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_greater__not_same_hash(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, _test_hash_multiset_greater__not_same_hash, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_greater__compare_less(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, NULL, _test_hash_multiset_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater__equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

/*
 * test hash_multiset_greater_equal
 */
UT_CASE_DEFINATION(hash_multiset_greater_equal)
void test_hash_multiset_greater_equal__null_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_greater_equal(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_greater_equal__null_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_greater_equal(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_greater_equal__non_inited_first(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_first->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_greater_equal(pt_first, pt_second));
    pt_first->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__non_inited_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_second->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_greater_equal(pt_first, pt_second));
    pt_second->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__not_same_type(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(list_t<int>);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    expect_assert_failure(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__same_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    assert_true(hash_multiset_greater_equal(pt_hash_multiset, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_greater_equal__size_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(signed int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__size_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 2; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__size_equal_0(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    assert_true(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_false(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 30; i < 40; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 100, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_greater_equal__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_greater_equal__not_same_hash(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, _test_hash_multiset_greater_equal__not_same_hash, NULL);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_greater_equal__compare_less(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, NULL, _test_hash_multiset_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    expect_assert_failure(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_greater_equal__equal(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_greater_equal(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

/*
 * test hash_multiset_swap
 */
UT_CASE_DEFINATION(hash_multiset_swap)
void test_hash_multiset_swap__null_first(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_swap(NULL, pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_swap__null_second(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_swap(pt_hash_multiset, NULL));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_swap__non_inited_first(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_first->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_swap(pt_first, pt_second));
    pt_first->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_swap__non_inited_second(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    pt_second->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_swap(pt_first, pt_second));
    pt_second->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_swap__not_same_type(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(list_t<int>);

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);

    expect_assert_failure(hash_multiset_swap(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_swap__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 928, NULL, NULL);

    expect_assert_failure(hash_multiset_swap(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_swap__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test_hash_multiset_swap__not_same_hash(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, _test_hash_multiset_swap__not_same_hash, NULL);

    expect_assert_failure(hash_multiset_swap(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

static void _test_hash_multiset_swap__not_same_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_swap__not_same_compare(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);

    hash_multiset_init(pt_first);
    hash_multiset_init_ex(pt_second, 0, NULL, _test_hash_multiset_swap__not_same_compare);

    expect_assert_failure(hash_multiset_swap(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_swap__same_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_swap(pt_hash_multiset, pt_hash_multiset);
    assert_true(hash_multiset_empty(pt_hash_multiset));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_swap__0_swap_n(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i = 0;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_size(pt_first) == 0);
    assert_true(hash_multiset_size(pt_second) == 10);
    hash_multiset_swap(pt_first, pt_second);
    assert_true(hash_multiset_size(pt_first) == 10);
    assert_true(hash_multiset_size(pt_second) == 0);

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_swap__n_swap_0(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i = 0;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }

    assert_true(hash_multiset_size(pt_first) == 10);
    assert_true(hash_multiset_size(pt_second) == 0);
    hash_multiset_swap(pt_first, pt_second);
    assert_true(hash_multiset_size(pt_first) == 0);
    assert_true(hash_multiset_size(pt_second) == 10);

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_swap__n_swap_n(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i = 0;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 100; i < 110; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_size(pt_first) == 10);
    assert_true(hash_multiset_size(pt_second) == 10);
    assert_true(hash_multiset_less(pt_first, pt_second));
    hash_multiset_swap(pt_first, pt_second);
    assert_true(hash_multiset_size(pt_first) == 10);
    assert_true(hash_multiset_size(pt_second) == 10);
    assert_true(hash_multiset_greater(pt_first, pt_second));

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

void test_hash_multiset_swap__m_swap_n(void** state)
{
    hash_multiset_t* pt_first = create_hash_multiset(int);
    hash_multiset_t* pt_second = create_hash_multiset(int);
    int i = 0;

    hash_multiset_init(pt_first);
    hash_multiset_init(pt_second);
    for(i = 0; i < 30; ++i)
    {
        hash_multiset_insert(pt_first, i);
    }
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_second, i);
    }

    assert_true(hash_multiset_size(pt_first) == 30);
    assert_true(hash_multiset_size(pt_second) == 10);
    hash_multiset_swap(pt_first, pt_second);
    assert_true(hash_multiset_size(pt_first) == 10);
    assert_true(hash_multiset_size(pt_second) == 30);

    hash_multiset_destroy(pt_first);
    hash_multiset_destroy(pt_second);
}

/*
 * test hash_multiset_insert_range
 */
UT_CASE_DEFINATION(hash_multiset_insert_range)
void test_hash_multiset_insert_range__null_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_insert_range(NULL, hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_insert_range__non_inited(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);

    pt_dest->_t_hashtable._t_typeinfo._t_style = 999;
    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    expect_assert_failure(hash_multiset_insert_range(pt_dest, it_begin, it_end));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__invalid_begin(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    it_begin._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(hash_multiset_insert_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__invalid_end(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    it_end._t_containertype = 3333;
    expect_assert_failure(hash_multiset_insert_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__invalid_range(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 0;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);
    hash_multiset_insert(pt_src, elem);

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    expect_assert_failure(hash_multiset_insert_range(pt_dest, it_end, it_begin));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__not_same_type(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(vector_t<int>);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    expect_assert_failure(hash_multiset_insert_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__non_empty_equal(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(pt_src, i);
    }

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 20);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__non_empty_dest_src_dup(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for(i = 5; i < 15; ++i)
    {
        hash_multiset_insert(pt_src, i);
    }

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 20);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__non_empty_src_dup(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    hash_multiset_init(pt_src);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for(i = 15; i < 25; ++i)
    {
        hash_multiset_insert(pt_src, i);
        hash_multiset_insert(pt_src, i);
    }

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 30);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__not_same_bucketcount(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    hash_multiset_init_ex(pt_src, 100, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for(i = 215; i < 225; ++i)
    {
        hash_multiset_insert(pt_src, i);
        hash_multiset_insert(pt_src, i);
    }

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 30);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test_hash_multiset_insert_range__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input + 793;
}
void test_hash_multiset_insert_range__not_same_hash(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    hash_multiset_init_ex(pt_src, 0, _test_hash_multiset_insert_range__not_same_hash, NULL);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for(i = 215; i < 225; ++i)
    {
        hash_multiset_insert(pt_src, i);
        hash_multiset_insert(pt_src, i);
    }

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_insert_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 30);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

static void _test_hash_multiset_insert_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test_hash_multiset_insert_range__compare(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_t* pt_src = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);
    hash_multiset_init_ex(pt_src, 0, NULL, _test_hash_multiset_insert_range__compare);

    it_begin = hash_multiset_begin(pt_src);
    it_end = hash_multiset_end(pt_src);
    hash_multiset_insert_range(pt_dest, it_begin, it_end);

    hash_multiset_destroy(pt_dest);
    hash_multiset_destroy(pt_src);
}

void test_hash_multiset_insert_range__other(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(int);
    set_t* pset = create_set(int);
    int i = 0;

    set_init(pset);
    hash_multiset_init(phmset);
    for (i = 0; i < 10; ++i) {
        set_insert(pset, i);
    }
    hash_multiset_insert_range(phmset, set_begin(pset), set_end(pset));
    assert_true(hash_multiset_size(phmset) == 10);

    hash_multiset_destroy(phmset);
    set_destroy(pset);
}

void test_hash_multiset_insert_range__other_not_same(void** state)
{
    hash_multiset_t* phmset = create_hash_multiset(double);
    set_t* pset = create_set(int);
    int i = 0;

    set_init(pset);
    hash_multiset_init(phmset);
    for (i = 0; i < 10; ++i) {
        set_insert(pset, i);
    }
    expect_assert_failure(hash_multiset_insert_range(phmset, set_begin(pset), set_end(pset)));

    hash_multiset_destroy(phmset);
    set_destroy(pset);
}

/*
 * test hash_multiset_insert_array
 */
UT_CASE_DEFINATION(hash_multiset_insert_array)
void test_hash_multiset_insert_array__null_hash_multiset(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(hash_multiset_insert_array(NULL, an_array, 10));
}

void test_hash_multiset_insert_array__non_inited(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init(pt_dest);

    pt_dest->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_insert_array(pt_dest, an_array, 10));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_insert_array__invalid_array(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init(pt_dest);

    expect_assert_failure(hash_multiset_insert_array(pt_dest, NULL, 10));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_insert_array__empty(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);

    hash_multiset_init(pt_dest);

    hash_multiset_insert_array(pt_dest, an_array, 0);
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_insert_array__non_empty_equal(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    int i = 0;

    hash_multiset_init(pt_dest);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for(i = 10; i < 20; ++i)
    {
        an_array[i - 10] = i;
    }

    hash_multiset_insert_array(pt_dest, an_array, 10);
    assert_true(hash_multiset_size(pt_dest) == 20);

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_insert_array__non_empty_dest_src_dup(void** state)
{
    int an_array[10] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    int i = 0;

    hash_multiset_init(pt_dest);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for(i = 5; i < 15; ++i)
    {
        an_array[i - 5] = i;
    }

    hash_multiset_insert_array(pt_dest, an_array, 10);
    assert_true(hash_multiset_size(pt_dest) == 20);

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_insert_array__non_empty_src_dup(void** state)
{
    int an_array[20] = {0};
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    int i = 0;

    hash_multiset_init(pt_dest);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }
    for (i = 0; i < 20; i += 2)
    {
        an_array[i] = i + 15;
        an_array[i + 1] = i + 15;
    }

    hash_multiset_insert_array(pt_dest, an_array, 20);
    assert_true(hash_multiset_size(pt_dest) == 30);

    hash_multiset_destroy(pt_dest);
}

/*
 * test hash_multiset_erase_pos
 */
UT_CASE_DEFINATION(hash_multiset_erase_pos)
void test_hash_multiset_erase_pos__null_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    int elem = 9;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    expect_assert_failure(hash_multiset_erase_pos(NULL, hash_multiset_begin(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_pos__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_pos;
    int elem = 9;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    it_pos = hash_multiset_begin(pt_hash_multiset);
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_erase_pos(pt_hash_multiset, it_pos));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_pos__invalid_pos(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_pos;
    int elem = 9;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    it_pos = hash_multiset_begin(pt_hash_multiset);
    it_pos._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(hash_multiset_erase_pos(pt_hash_multiset, it_pos));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_pos__end(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_pos;
    int elem = 9;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, elem);
    it_pos = hash_multiset_end(pt_hash_multiset);
    expect_assert_failure(hash_multiset_erase_pos(pt_hash_multiset, it_pos));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_pos__begin(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_pos;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }
    it_pos = hash_multiset_begin(pt_hash_multiset);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    hash_multiset_erase_pos(pt_hash_multiset, it_pos);
    assert_true(hash_multiset_size(pt_hash_multiset) == 9);
    it_pos = hash_multiset_begin(pt_hash_multiset);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_pos__middle(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_pos;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }
    i = 4;
    it_pos = hash_multiset_find(pt_hash_multiset, i);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 4);
    hash_multiset_erase_pos(pt_hash_multiset, it_pos);
    assert_true(hash_multiset_size(pt_hash_multiset) == 9);
    it_pos = hash_multiset_find(pt_hash_multiset, i);
    assert_true(_hash_multiset_iterator_equal(it_pos, hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_pos__last(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_pos;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_hash_multiset, i);
    }
    it_pos = iterator_prev(hash_multiset_end(pt_hash_multiset));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    hash_multiset_erase_pos(pt_hash_multiset, it_pos);
    assert_true(hash_multiset_size(pt_hash_multiset) == 9);
    it_pos = iterator_prev(hash_multiset_end(pt_hash_multiset));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_pos__erase_empty(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_iterator_t it_pos;
    int i = 0;

    hash_multiset_init(pt_hash_multiset);
    hash_multiset_insert(pt_hash_multiset, i);
    assert_true(hash_multiset_size(pt_hash_multiset) == 1);
    it_pos = hash_multiset_begin(pt_hash_multiset);
    hash_multiset_erase_pos(pt_hash_multiset, it_pos);
    assert_true(hash_multiset_size(pt_hash_multiset) == 0);

    hash_multiset_destroy(pt_hash_multiset);
}

/*
 * test hash_multiset_erase_range
 */
UT_CASE_DEFINATION(hash_multiset_erase_range)
void test_hash_multiset_erase_range__null_hash_multiset(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    expect_assert_failure(hash_multiset_erase_range(NULL, hash_multiset_begin(pt_hash_multiset), hash_multiset_end(pt_hash_multiset)));

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_erase_range__non_inited(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);

    it_begin = hash_multiset_begin(pt_dest);
    it_end = hash_multiset_end(pt_dest);
    pt_dest->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__invalid_begin(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);

    it_begin = hash_multiset_begin(pt_dest);
    it_end = hash_multiset_end(pt_dest);
    it_begin._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(hash_multiset_erase_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__invalid_end(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);

    it_begin = hash_multiset_begin(pt_dest);
    it_end = hash_multiset_end(pt_dest);
    it_end._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(hash_multiset_erase_range(pt_dest, it_begin, it_end));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__invalid_range(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int elem = 0;

    hash_multiset_init(pt_dest);
    hash_multiset_insert(pt_dest, elem);

    it_begin = hash_multiset_begin(pt_dest);
    it_end = hash_multiset_end(pt_dest);
    expect_assert_failure(hash_multiset_erase_range(pt_dest, it_end, it_begin));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__empty(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;

    hash_multiset_init(pt_dest);

    it_begin = hash_multiset_begin(pt_dest);
    it_end = hash_multiset_end(pt_dest);
    hash_multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_empty(pt_dest));

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__begin(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }

    it_begin = hash_multiset_begin(pt_dest);
    it_end = iterator_next(it_begin);
    hash_multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 9);
    assert_true(*(int*)iterator_get_pointer(hash_multiset_begin(pt_dest)) == 1);

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__middle(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }

    it_begin = iterator_next(hash_multiset_begin(pt_dest));
    it_end = iterator_next(it_begin);
    hash_multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 9);
    it_begin = hash_multiset_begin(pt_dest);
    assert_true(*(int*)iterator_get_pointer(it_begin) == 0);
    assert_true(*(int*)iterator_get_pointer(iterator_next(it_begin)) == 2);

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__end(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }

    it_end = hash_multiset_end(pt_dest);
    it_begin = iterator_prev(it_end);
    hash_multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 9);
    it_end = hash_multiset_end(pt_dest);
    assert_true(*(int*)iterator_get_pointer(iterator_prev(it_end)) == 8);

    hash_multiset_destroy(pt_dest);
}

void test_hash_multiset_erase_range__all(void** state)
{
    hash_multiset_t* pt_dest = create_hash_multiset(int);
    hash_multiset_iterator_t it_begin;
    hash_multiset_iterator_t it_end;
    int i = 0;

    hash_multiset_init(pt_dest);
    for(i = 0; i < 10; ++i)
    {
        hash_multiset_insert(pt_dest, i);
    }

    it_begin = hash_multiset_begin(pt_dest);
    it_end = hash_multiset_end(pt_dest);
    hash_multiset_erase_range(pt_dest, it_begin, it_end);
    assert_true(hash_multiset_size(pt_dest) == 0);

    hash_multiset_destroy(pt_dest);
}

/*
 * test hash_multiset_resize
 */
UT_CASE_DEFINATION(hash_multiset_resize)
void test_hash_multiset_resize__null_hash_multiset(void** state)
{
    expect_assert_failure(hash_multiset_resize(NULL, 23));
}

void test_hash_multiset_resize__non_inited(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = 999;
    expect_assert_failure(hash_multiset_resize(pt_hash_multiset, 290));
    pt_hash_multiset->_t_hashtable._t_typeinfo._t_style = _TYPE_C_BUILTIN;

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_resize__greater(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init(pt_hash_multiset);

    assert_true(hash_multiset_bucket_count(pt_hash_multiset) == 53);
    hash_multiset_resize(pt_hash_multiset, 100);
    assert_true(hash_multiset_bucket_count(pt_hash_multiset) == 193);

    hash_multiset_destroy(pt_hash_multiset);
}

void test_hash_multiset_resize__less(void** state)
{
    hash_multiset_t* pt_hash_multiset = create_hash_multiset(int);
    hash_multiset_init_ex(pt_hash_multiset, 100, NULL, NULL);

    assert_true(hash_multiset_bucket_count(pt_hash_multiset) == 193);
    hash_multiset_resize(pt_hash_multiset, 0);
    assert_true(hash_multiset_bucket_count(pt_hash_multiset) == 193);

    hash_multiset_destroy(pt_hash_multiset);
}

