#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/citerator.h"
#include "cstl/cvector.h"
#include "cstl/cstl_hashtable_iterator.h"
#include "cstl/cstl_hashtable_private.h"
#include "cstl/cstl_hashtable.h"
#include "cstl_hashtable_aux.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"
#include "cstl/cslist.h"
#include "cstl/cset.h"
#include "cstl/chash_set.h"
#include "cstl/cdeque.h"

#include "ut_def.h"
#include "ut_cstl_hashtable.h"

UT_SUIT_DEFINATION(cstl_hashtable, _create_hashtable)

/*
 * test _create_hashtable
 */
UT_CASE_DEFINATION(_create_hashtable)
void test__create_hashtable__null_typename(void** state)
{
    expect_assert_failure(_create_hashtable(NULL));
}

void test__create_hashtable__c_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("double");
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__create_hashtable__cstr(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__create_hashtable__libcstl_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("vector_t<int>");
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

typedef struct _test_test__create_hashtable__user_define
{
    int n_elem;
}_test__create_hashtable__user_define_t;

void test__create_hashtable__user_define(void** state)
{
    _hashtable_t* pt_hashtable = NULL;

    type_register(_test__create_hashtable__user_define_t, NULL, NULL, NULL, NULL);
    pt_hashtable = _create_hashtable("_test__create_hashtable__user_define_t");
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__create_hashtable__unregister(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("test__create_hashtable__unregister_t");
    assert_true(pt_hashtable == NULL);
}

/*
 * test _hashtable_init
 */
UT_CASE_DEFINATION(_hashtable_init)
void test__hashtable_init__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_init(NULL, 0, NULL, NULL));
}

void test__hashtable_init__non_created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    pt_hashtable->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_hashtable_init(pt_hashtable, 0, NULL, NULL));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init__bucket_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_hashtable));
    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init__bucket_not_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_hashtable));
    assert_true(_hashtable_bucket_count(pt_hashtable) == 193);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init__null_hash(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

static void _test__hashtable_init__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}

void test__hashtable_init__non_null_hash(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, _test__hashtable_init__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(pt_hashtable));
    assert_true(pt_hashtable->_ufun_hash == _test__hashtable_init__non_null_hash);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init__null_compare(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

static void _test__hashtable_init__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_init__non_null_compare(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, _test__hashtable_init__non_null_compare);
    assert_true(_hashtable_is_inited(pt_hashtable));
    assert_true(pt_hashtable->_bfun_compare == _test__hashtable_init__non_null_compare);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_init_copy
 */
UT_CASE_DEFINATION(_hashtable_init_copy)
void test__hashtable_init_copy__null_dest(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_init_copy(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init_copy__null_src(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_init_copy(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init_copy__non_created_dest(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");

    _hashtable_init(pt_src, 0, NULL, NULL);
    pt_dest->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_init_copy(pt_dest, pt_src));
    pt_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_init_copy__non_inited_src(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");

    expect_assert_failure(_hashtable_init_copy(pt_dest, pt_src));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_init_copy__not_same_type(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("double");

    _hashtable_init(pt_src, 0, NULL, NULL);
    expect_assert_failure(_hashtable_init_copy(pt_dest, pt_src));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_init_copy__empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("signed int");

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_init_copy__non_empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("signed int");
    int elem = 100;

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_insert_unique(pt_src, &elem);
    _hashtable_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

static void _test__hashtable_init_copy__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_init_copy__non_null_hash(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("signed int");
    int i = 0;

    _hashtable_init(pt_src, 0, _test__hashtable_init_copy__non_null_hash, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_src, &i);
    }
    _hashtable_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);
    assert_true(pt_dest->_ufun_hash == _test__hashtable_init_copy__non_null_hash);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

static void _test__hashtable_init_copy__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_init_copy__non_null_compare(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("signed int");
    int i = 0;

    _hashtable_init(pt_src, 0, NULL, _test__hashtable_init_copy__non_null_compare);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_src, &i);
    }
    _hashtable_init_copy(pt_dest, pt_src);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);
    assert_true(pt_dest->_bfun_compare == _test__hashtable_init_copy__non_null_compare);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

/*
 * test _hashtable_init_copy_equal_range
 */
UT_CASE_DEFINATION(_hashtable_init_copy_equal_range)
void test__hashtable_init_copy_equal_range__null_hashtable(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(_hashtable_init_copy_equal_range(NULL, vector_begin(pvec), vector_end(pvec), 0, NULL, NULL));

    vector_destroy(pvec);
}

void test__hashtable_init_copy_equal_range__non_created_hashtable(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);

    list_init(plist);
    pt_dest->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_init_copy_equal_range(pt_dest, list_begin(plist), list_end(plist), 0, NULL, NULL));
    pt_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

void test__hashtable_init_copy_equal_range__invalid_begin(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    slist_init(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_containertype = 3333;
    expect_assert_failure(_hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__hashtable_init_copy_equal_range__invalid_end(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    deque_init(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_iteratortype = 3333;
    expect_assert_failure(_hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__hashtable_init_copy_equal_range__invalid_range(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_hashtable_init_copy_equal_range(pt_dest, it_end, it_begin, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    set_destroy(pset);
}

void test__hashtable_init_copy_equal_range__invalid_range_not_same_type(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    multiset_init(pmset);
    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__hashtable_init_copy_equal_range__empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    hash_set_init(phset);
    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__hashtable_init_copy_equal_range__non_empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, elem);
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);

    _hashtable_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__hashtable_init_copy_equal_range__non_empty_dup(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 100);
    _hashtable_init_copy_equal_range(pt_dest, vector_begin(pvec), vector_end(pvec), 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);

    _hashtable_destroy(pt_dest);
    vector_destroy(pvec);
}

void test__hashtable_init_copy_equal_range__bucketcount(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    vector_t* pvec = create_vector(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    vector_init(pvec);
    vector_push_back(pvec, elem);
    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    _hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 193);

    _hashtable_destroy(pt_dest);
    vector_destroy(pvec);
}

static void _test__hashtable_init_copy_equal_range__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_init_copy_equal_range__non_null_hash(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    list_init(plist);
    list_push_back(plist, elem);
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    _hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 0, _test__hashtable_init_copy_equal_range__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(_hashtable_hash(pt_dest) == _test__hashtable_init_copy_equal_range__non_null_hash);

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

static void _test__hashtable_init_copy_equal_range__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_init_copy_equal_range__non_null_compare(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    slist_init(pslist);
    slist_push_front(pslist, elem);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    _hashtable_init_copy_equal_range(pt_dest, it_begin, it_end, 0, NULL, _test__hashtable_init_copy_equal_range__non_null_compare);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(pt_dest->_bfun_compare == _test__hashtable_init_copy_equal_range__non_null_compare);

    _hashtable_destroy(pt_dest);
    slist_destroy(pslist);
}

/*
 * test _hashtable_init_copy_equal_array
 */
UT_CASE_DEFINATION(_hashtable_init_copy_equal_array)
void test__hashtable_init_copy_equal_array__null_hashtable(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_hashtable_init_copy_equal_array(NULL, an_array, 10, 0, NULL, NULL));
}

void test__hashtable_init_copy_equal_array__non_created_hashtable(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    pt_dest->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_init_copy_equal_array(pt_dest, an_array, 10, 0, NULL, NULL));
    pt_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_equal_array__invalid_array(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");

    expect_assert_failure(_hashtable_init_copy_equal_array(pt_dest, NULL, 10, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_equal_array__empty(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_equal_array(pt_dest, an_array, 0, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_equal_array__non_empty(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    _hashtable_t* pt_dest = _create_hashtable("int");

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    _hashtable_init_copy_equal_array(pt_dest, an_array, 10, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_equal_array__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_equal_array(pt_dest, an_array, 10, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_equal_array__bucketcount(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_equal_array(pt_dest, an_array, 10, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);
    assert_true(_hashtable_bucket_count(pt_dest) == 193);

    _hashtable_destroy(pt_dest);
}

static void _test__hashtable_init_copy_equal_array__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_init_copy_equal_array__non_null_hash(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_equal_array(pt_dest, an_array, 10, 0, _test__hashtable_init_copy_equal_array__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(_hashtable_hash(pt_dest) == _test__hashtable_init_copy_equal_array__non_null_hash);

    _hashtable_destroy(pt_dest);
}

static void _test__hashtable_init_copy_equal_array__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_init_copy_equal_array__non_null_compare(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_equal_array(pt_dest, an_array, 10, 0, NULL, _test__hashtable_init_copy_equal_array__non_null_compare);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(pt_dest->_bfun_compare == _test__hashtable_init_copy_equal_array__non_null_compare);

    _hashtable_destroy(pt_dest);
}

/*
 * test _hashtable_init_copy_unique_range
 */
UT_CASE_DEFINATION(_hashtable_init_copy_unique_range)
void test__hashtable_init_copy_unique_range__null_hashtable(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(_hashtable_init_copy_unique_range(NULL, vector_begin(pvec), vector_end(pvec), 0, NULL, NULL));

    vector_destroy(pvec);
}

void test__hashtable_init_copy_unique_range__non_created_hashtable(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);

    list_init(plist);
    pt_dest->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_init_copy_unique_range(pt_dest, list_begin(plist), list_end(plist), 0, NULL, NULL));
    pt_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

void test__hashtable_init_copy_unique_range__invalid_begin(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    slist_init(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_containertype = 3333;
    expect_assert_failure(_hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__hashtable_init_copy_unique_range__invalid_end(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    deque_init(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_iteratortype = 3333;
    expect_assert_failure(_hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__hashtable_init_copy_unique_range__invalid_range(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    set_init(pset);
    set_insert(pset, elem);
    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_hashtable_init_copy_unique_range(pt_dest, it_end, it_begin, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    set_destroy(pset);
}

void test__hashtable_init_copy_unique_range__invalid_range_not_same_type(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    multiset_init(pmset);
    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__hashtable_init_copy_unique_range__empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    hash_set_init(phset);
    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__hashtable_init_copy_unique_range__non_empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    hash_multiset_init(phmset);
    hash_multiset_insert(phmset, elem);
    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);

    _hashtable_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__hashtable_init_copy_unique_range__non_empty_dup(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 10, 100);
    _hashtable_init_copy_unique_range(pt_dest, vector_begin(pvec), vector_end(pvec), 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);

    _hashtable_destroy(pt_dest);
    vector_destroy(pvec);
}

void test__hashtable_init_copy_unique_range__bucketcount(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    vector_t* pvec = create_vector(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    vector_init(pvec);
    vector_push_back(pvec, elem);
    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    _hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 193);

    _hashtable_destroy(pt_dest);
    vector_destroy(pvec);
}

static void _test__hashtable_init_copy_unique_range__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_init_copy_unique_range__non_null_hash(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    list_init(plist);
    list_push_back(plist, elem);
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    _hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 0, _test__hashtable_init_copy_unique_range__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(_hashtable_hash(pt_dest) == _test__hashtable_init_copy_unique_range__non_null_hash);

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

static void _test__hashtable_init_copy_unique_range__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_init_copy_unique_range__non_null_compare(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 9;

    slist_init(pslist);
    slist_push_front(pslist, elem);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    _hashtable_init_copy_unique_range(pt_dest, it_begin, it_end, 0, NULL, _test__hashtable_init_copy_unique_range__non_null_compare);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(pt_dest->_bfun_compare == _test__hashtable_init_copy_unique_range__non_null_compare);

    _hashtable_destroy(pt_dest);
    slist_destroy(pslist);
}

/*
 * test _hashtable_init_copy_unique_array
 */
UT_CASE_DEFINATION(_hashtable_init_copy_unique_array)
void test__hashtable_init_copy_unique_array__null_hashtable(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_hashtable_init_copy_unique_array(NULL, an_array, 10, 0, NULL, NULL));
}

void test__hashtable_init_copy_unique_array__non_created_hashtable(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    pt_dest->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_init_copy_unique_array(pt_dest, an_array, 10, 0, NULL, NULL));
    pt_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_unique_array__invalid_array(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");

    expect_assert_failure(_hashtable_init_copy_unique_array(pt_dest, NULL, 10, 0, NULL, NULL));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_unique_array__empty(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_unique_array(pt_dest, an_array, 0, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_unique_array__non_empty(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");
    int i = 0;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    _hashtable_init_copy_unique_array(pt_dest, an_array, 10, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 10);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_unique_array__non_empty_dup(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_unique_array(pt_dest, an_array, 10, 0, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_init_copy_unique_array__bucketcount(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_unique_array(pt_dest, an_array, 10, 100, NULL, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 193);

    _hashtable_destroy(pt_dest);
}

static void _test__hashtable_init_copy_unique_array__non_null_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_init_copy_unique_array__non_null_hash(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_unique_array(pt_dest, an_array, 10, 0, _test__hashtable_init_copy_unique_array__non_null_hash, NULL);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(_hashtable_hash(pt_dest) == _test__hashtable_init_copy_unique_array__non_null_hash);

    _hashtable_destroy(pt_dest);
}

static void _test__hashtable_init_copy_unique_array__non_null_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_init_copy_unique_array__non_null_compare(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init_copy_unique_array(pt_dest, an_array, 10, 0, NULL, _test__hashtable_init_copy_unique_array__non_null_compare);
    assert_true(_hashtable_is_inited(pt_dest));
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(_hashtable_bucket_count(pt_dest) == 53);
    assert_true(pt_dest->_bfun_compare == _test__hashtable_init_copy_unique_array__non_null_compare);

    _hashtable_destroy(pt_dest);
}

/*
 * test _hashtable_destroy
 */
UT_CASE_DEFINATION(_hashtable_destroy)
void test__hashtable_destroy__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_destroy(NULL));
}

void test__hashtable_destroy__non_created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    pt_hashtable->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_destroy(pt_hashtable));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_destroy__created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_destroy__inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_assign
 */
UT_CASE_DEFINATION(_hashtable_assign)
void test__hashtable_assign__null_dest(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_assign(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_assign__null_src(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_assign(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_assign__non_created_dest(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");

    _hashtable_init(pt_src, 0, NULL, NULL);
    expect_assert_failure(_hashtable_assign(pt_dest, pt_src));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__non_init_src(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");

    _hashtable_init(pt_dest, 0, NULL, NULL);
    expect_assert_failure(_hashtable_assign(pt_dest, pt_src));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__not_same_type(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("double");

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    expect_assert_failure(_hashtable_assign(pt_dest, pt_src));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__empty_empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    _hashtable_assign(pt_dest, pt_src);
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__non_empty_empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    _hashtable_insert_unique(pt_dest, &elem);
    _hashtable_assign(pt_dest, pt_src);
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__non_empty_non_empty_less(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_insert_unique(pt_src, &elem);
    elem = 222;
    _hashtable_insert_unique(pt_src, &elem);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    elem = 897;
    _hashtable_insert_unique(pt_dest, &elem);
    _hashtable_assign(pt_dest, pt_src);
    assert_true(_hashtable_size(pt_dest) == 2);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__non_empty_non_empty_size_equal(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_insert_unique(pt_src, &elem);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    elem = 334;
    _hashtable_insert_unique(pt_dest, &elem);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 334);
    _hashtable_assign(pt_dest, pt_src);
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 9);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__non_empty_non_empty_equal(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_insert_unique(pt_src, &elem);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    _hashtable_insert_unique(pt_dest, &elem);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 9);
    _hashtable_assign(pt_dest, pt_src);
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 9);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__non_empty_non_empty_greater(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_insert_unique(pt_src, &elem);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    elem = 876;
    _hashtable_insert_unique(pt_dest, &elem);
    elem = 333;
    _hashtable_insert_unique(pt_dest, &elem);
    _hashtable_assign(pt_dest, pt_src);
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 9);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__empty_non_empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_src, 0, NULL, NULL);
    _hashtable_insert_unique(pt_src, &elem);
    _hashtable_init(pt_dest, 0, NULL, NULL);
    _hashtable_assign(pt_dest, pt_src);
    assert_true(_hashtable_size(pt_dest) == 1);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 9);

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

void test__hashtable_assign__not_same_bucketcount(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_t* pt_src = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_src, 100, NULL, NULL);
    _hashtable_insert_unique(pt_src, &elem);
    _hashtable_init(pt_dest, 898, NULL, NULL);
    elem = 999;
    _hashtable_insert_unique(pt_dest, &elem);
    /*assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 999);*/
    expect_assert_failure(_hashtable_assign(pt_dest, pt_src));
    /*assert_true(_hashtable_size(pt_dest) == 1);*/
    /*assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 9);*/

    _hashtable_destroy(pt_dest);
    _hashtable_destroy(pt_src);
}

/*
 * test _hashtable_size
 */
UT_CASE_DEFINATION(_hashtable_size)
void test__hashtable_size__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_size(NULL));
}

void test__hashtable_size__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_size(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_size__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    assert_true(_hashtable_size(pt_hashtable) == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_size__non_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    assert_true(_hashtable_size(pt_hashtable) == 1);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_emtpy
 */
UT_CASE_DEFINATION(_hashtable_empty)
void test__hashtable_empty__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_empty(NULL));
}

void test__hashtable_empty__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_empty(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_empty__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    assert_true(_hashtable_empty(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_empty__non_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    assert_false(_hashtable_empty(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_max_size
 */
UT_CASE_DEFINATION(_hashtable_max_size)
void test__hashtable_max_size__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_max_size(NULL));
}

void test__hashtable_max_size__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_max_size(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_max_size__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    assert_true(_hashtable_max_size(pt_hashtable) > 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_max_size__non_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    assert_true(_hashtable_max_size(pt_hashtable) > 0);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_bucket_count
 */
UT_CASE_DEFINATION(_hashtable_bucket_count)
void test__hashtable_bucket_count__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_bucket_count(NULL));
}

void test__hashtable_bucket_count__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_bucket_count(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_bucket_count__53(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 10, NULL, NULL);

    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_bucket_count__193(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 100, NULL, NULL);

    assert_true(_hashtable_bucket_count(pt_hashtable) == 193);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_bucket_count__change(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int i;

    _hashtable_init(pt_hashtable, 10, NULL, NULL);

    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);
    for(i = 0; i < 100; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }
    assert_true(_hashtable_bucket_count(pt_hashtable) == 193);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_begin
 */
UT_CASE_DEFINATION(_hashtable_begin)
void test__hashtable_begin__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_begin(NULL));
}

void test__hashtable_begin__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_begin(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_begin__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    assert_true(_hashtable_iterator_equal(_hashtable_begin(pt_hashtable), _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_begin__non_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_hashtable)) == 9);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_end
 */
UT_CASE_DEFINATION(_hashtable_end)
void test__hashtable_end__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_end(NULL));
}

void test__hashtable_end__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_end(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_end__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    assert_true(_hashtable_iterator_equal(_hashtable_begin(pt_hashtable), _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_end__non_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_end(pt_hashtable);
    it_iter = _hashtable_iterator_prev(it_iter);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 9);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_key_comp
 */
UT_CASE_DEFINATION(_hashtable_key_comp)
void test__hashtable_key_comp__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_key_comp(NULL));
}

void test__hashtable_key_comp__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_key_comp(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_key_comp__default_key_comp(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    assert_true(_hashtable_key_comp(pt_hashtable) == _GET_HASHTABLE_TYPE_LESS_FUNCTION(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void _test__hashtable_key_comp__user_define_key_comp(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void test__hashtable_key_comp__user_define_key_comp(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, _test__hashtable_key_comp__user_define_key_comp);

    assert_true(_hashtable_key_comp(pt_hashtable) == _test__hashtable_key_comp__user_define_key_comp);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_hash
 */
UT_CASE_DEFINATION(_hashtable_hash)
void test__hashtable_hash__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_hash(NULL));
}

void test__hashtable_hash__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_hash(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_hash__default_hash(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_true(_hashtable_hash(pt_hashtable) == _hashtable_default_hash);

    _hashtable_destroy(pt_hashtable);
}

static void _test__hashtable_hash__user_define_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_hash__user_define_hash(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, _test__hashtable_hash__user_define_hash, NULL);
    assert_true(_hashtable_hash(pt_hashtable) == _test__hashtable_hash__user_define_hash);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_find
 */
UT_CASE_DEFINATION(_hashtable_find)
void test__hashtable_find__null_hashtable(void** state)
{
    int elem = 9;
    expect_assert_failure(_hashtable_find(NULL, &elem));
}

void test__hashtable_find__null_value(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_find(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_find__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    expect_assert_failure(_hashtable_find(pt_hashtable, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_find__c_builtin_find(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }

    elem = 2;
    it_iter = _hashtable_find(pt_hashtable, &elem);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 2);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_find__c_builtin_not_find(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }

    elem = 42;
    it_iter = _hashtable_find(pt_hashtable, &elem);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_find__cstr_find(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_unique(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _hashtable_find(pt_hashtable, pstr);
    assert_true(strcmp((char*)_hashtable_iterator_get_pointer(it_iter), "ggg") == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_find__cstr_not_find(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_unique(pt_hashtable, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _hashtable_find(pt_hashtable, pstr);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

static void _test__hashtable_find__libcstl_hash(const void* cpv_input, void* pv_output)
{
    list_t* plist = (list_t*)cpv_input;
    list_iterator_t it_iter;
    *(size_t*)pv_output = 0;
    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        *(size_t*)pv_output += *(int*)iterator_get_pointer(it_iter);
    }
}
void test__hashtable_find__libcstl_builtin_find(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    _hashtable_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_find__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_unique(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hashtable_find(pt_hashtable, plist);
    assert_true(*(int*)list_front((list_t*)_hashtable_iterator_get_pointer(it_iter)) == 6);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_find__libcstl_builtin_not_find(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    _hashtable_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_find__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_unique(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 96);
    it_iter = _hashtable_find(pt_hashtable, plist);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

typedef struct _tag_test__hashtable_find__user_define
{
    int n_elem;
}_test__hashtable_find__user_define_t;
void test__hashtable_find__user_define_find(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _hashtable_iterator_t it_iter;
    _test__hashtable_find__user_define_t elem;
    int i = 0;

    type_register(_test__hashtable_find__user_define_t, NULL, NULL, NULL, NULL);

    pt_hashtable = _create_hashtable("_test__hashtable_find__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_unique(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    it_iter = _hashtable_find(pt_hashtable, &elem);
    assert_true(((_test__hashtable_find__user_define_t*)_hashtable_iterator_get_pointer(it_iter))->n_elem == 8);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_find__user_define_not_find(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_find__user_define_t");
    _hashtable_iterator_t it_iter;
    _test__hashtable_find__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_unique(pt_hashtable, &elem);
    }

    elem.n_elem = 78;
    it_iter = _hashtable_find(pt_hashtable, &elem);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_clear
 */
UT_CASE_DEFINATION(_hashtable_clear)
void test__hashtable_clear__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_clear(NULL));
}

void test__hashtable_clear__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    pt_hashtable->_t_typeinfo._t_style = 2323;
    expect_assert_failure(_hashtable_clear(pt_hashtable));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_clear__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    assert_true(_hashtable_empty(pt_hashtable));
    _hashtable_clear(pt_hashtable);
    assert_true(_hashtable_empty(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_clear__non_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 8;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    assert_false(_hashtable_empty(pt_hashtable));
    _hashtable_clear(pt_hashtable);
    assert_true(_hashtable_empty(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_count
 */
UT_CASE_DEFINATION(_hashtable_count)
void test__hashtable_count__null_hashtable(void** state)
{
    int elem = 9;
    expect_assert_failure(_hashtable_count(NULL, &elem));
}

void test__hashtable_count__null_value(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_count(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_count__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    expect_assert_failure(_hashtable_count(pt_hashtable, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_count__c_builtin_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = 1222;
    assert_true(_hashtable_count(pt_hashtable, &elem) == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_count__c_builtin_1(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = 2;
    assert_true(_hashtable_count(pt_hashtable, &elem) == 1);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_count__c_builtin_n(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
        _hashtable_insert_equal(pt_hashtable, &i);
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = 2;
    assert_true(_hashtable_count(pt_hashtable, &elem) == 3);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_count__cstr_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "uuuuu");
    assert_true(_hashtable_count(pt_hashtable, pstr) == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_count__cstr_1(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_hashtable_count(pt_hashtable, pstr) == 1);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_count__cstr_n(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    _hashtable_insert_equal(pt_hashtable, pstr);
    _hashtable_insert_equal(pt_hashtable, pstr);
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_hashtable_count(pt_hashtable, pstr) == 4);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_count__libcstl_builtin_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_find__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 116);
    assert_true(_hashtable_count(pt_hashtable, plist) == 0);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_count__libcstl_builtin_1(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_find__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hashtable_count(pt_hashtable, plist) == 1);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_count__libcstl_builtin_n(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_find__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_equal(pt_hashtable, plist);
        _hashtable_insert_equal(pt_hashtable, plist);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hashtable_count(pt_hashtable, plist) == 3);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

typedef struct _tag_test__hashtable_count__user_define
{
    int n_elem;
}_test__hashtable_count__user_define_t;
void test__hashtable_count__user_define_0(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _test__hashtable_count__user_define_t elem;
    int i = 0;

    type_register(_test__hashtable_count__user_define_t, NULL, NULL, NULL, NULL);

    pt_hashtable = _create_hashtable("_test__hashtable_count__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 88;
    assert_true(_hashtable_count(pt_hashtable, &elem) == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_count__user_define_1(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_count__user_define_t");
    _test__hashtable_count__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hashtable_count(pt_hashtable, &elem) == 1);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_count__user_define_n(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_count__user_define_t");
    _test__hashtable_count__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_equal(pt_hashtable, &elem);
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hashtable_count(pt_hashtable, &elem) == 2);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_equal_range
 */
UT_CASE_DEFINATION(_hashtable_equal_range)
void test__hashtable_equal_range__null_hashtable(void** state)
{
    int elem = 9;
    expect_assert_failure(_hashtable_equal_range(NULL, &elem));
}

void test__hashtable_equal_range__null_value(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_equal_range(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_equal_range__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    expect_assert_failure(_hashtable_equal_range(pt_hashtable, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_equal_range__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    range_t r_range;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }

    elem = 1111;
    r_range = _hashtable_equal_range(pt_hashtable, &elem);
    assert_true(_hashtable_iterator_equal(r_range.it_begin, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_iterator_equal(r_range.it_end, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

static void _test__hashtable_equal_range__hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_equal_range__c_builtin_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    range_t r_range;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_equal_range__hash, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }

    elem = 2;
    r_range = _hashtable_equal_range(pt_hashtable, &elem);
    assert_true(*(int*)_hashtable_iterator_get_pointer(r_range.it_begin) == 2);
    assert_true(*(int*)_hashtable_iterator_get_pointer(r_range.it_end) == 3);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_equal_range__c_builtin_greater(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    range_t r_range;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_equal_range__hash, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }

    elem = -8;
    r_range = _hashtable_equal_range(pt_hashtable, &elem);
    assert_true(_hashtable_iterator_equal(r_range.it_begin, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_iterator_equal(r_range.it_end, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

static void _test__hashtable_equal_range__cstr_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = (size_t)((char*)cpv_input)[0];
}
void test__hashtable_equal_range__cstr_upper_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    range_t r_range;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 100, _test__hashtable_equal_range__cstr_hash, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_unique(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    r_range = _hashtable_equal_range(pt_hashtable, pstr);
    assert_true(strcmp((char*)_hashtable_iterator_get_pointer(r_range.it_begin), "ggg") == 0);
    assert_true(strcmp((char*)_hashtable_iterator_get_pointer(r_range.it_end), "linux") == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_equal_range__cstr_greater(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    range_t r_range;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, _test__hashtable_equal_range__cstr_hash, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_unique(pt_hashtable, pstr);

    string_assign_cstr(pstr, "vvvv");
    r_range = _hashtable_equal_range(pt_hashtable, pstr);
    assert_true(_hashtable_iterator_equal(r_range.it_begin, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_iterator_equal(r_range.it_end, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

static void _test__hashtable_equal_range__libcstl_hash(const void* cpv_input, void* pv_output)
{
    list_t* plist = (list_t*)cpv_input;
    list_iterator_t it_iter;
    *(size_t*)pv_output = 0;
    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        *(size_t*)pv_output += *(int*)iterator_get_pointer(it_iter);
    }
}
void test__hashtable_equal_range__libcstl_builtin_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_equal_range__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_unique(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    r_range = _hashtable_equal_range(pt_hashtable, plist);
    assert_true(*(int*)list_front((list_t*)_hashtable_iterator_get_pointer(r_range.it_begin)) == 6);
    assert_true(*(int*)list_front((list_t*)_hashtable_iterator_get_pointer(r_range.it_end)) == 7);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_equal_range__libcstl_builtin_greater(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    range_t r_range;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_equal_range__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _hashtable_insert_unique(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    r_range = _hashtable_equal_range(pt_hashtable, plist);
    assert_true(_hashtable_iterator_equal(r_range.it_begin, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_iterator_equal(r_range.it_end, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

typedef struct _tag_test__hashtable_equal_range__user_define
{
    int n_elem;
}_test__hashtable_equal_range__user_define_t;
void test__hashtable_equal_range__user_define_equal(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    range_t r_range;
    _test__hashtable_equal_range__user_define_t elem;
    int i = 0;

    type_register(_test__hashtable_equal_range__user_define_t, NULL, NULL, NULL, NULL);

    pt_hashtable = _create_hashtable("_test__hashtable_equal_range__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_unique(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    r_range = _hashtable_equal_range(pt_hashtable, &elem);
    assert_true(((_test__hashtable_equal_range__user_define_t*)_hashtable_iterator_get_pointer(r_range.it_begin))->n_elem == 8);
    assert_true(((_test__hashtable_equal_range__user_define_t*)_hashtable_iterator_get_pointer(r_range.it_end))->n_elem == 9);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_equal_range__user_define_greater(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_equal_range__user_define_t");
    range_t r_range;
    _test__hashtable_equal_range__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _hashtable_insert_unique(pt_hashtable, &elem);
    }

    elem.n_elem = 7;
    r_range = _hashtable_equal_range(pt_hashtable, &elem);
    assert_true(_hashtable_iterator_equal(r_range.it_begin, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_iterator_equal(r_range.it_end, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_equal
 */
UT_CASE_DEFINATION(_hashtable_equal)
void test__hashtable_equal__null_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_equal(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_equal__null_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_equal(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_equal__non_inited_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__non_inited_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);

    expect_assert_failure(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("list_t<int>");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__not_same_bucket(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 100, NULL, NULL);

    assert_false(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_true(_hashtable_equal(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_equal__size_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("signed int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__size_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__size_equal_0(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    assert_true(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__size_equal_elem_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 30; i < 40; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_equal__compare_not_equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, _test__hashtable_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_equal__equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_not_equal
 */
UT_CASE_DEFINATION(_hashtable_not_equal)
void test__hashtable_not_equal__null_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_not_equal(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_not_equal__null_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_not_equal(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_not_equal__non_inited_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__non_inited_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);

    expect_assert_failure(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("list_t<int>");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__not_same_bucket(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 1000, NULL, NULL);

    assert_true(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_false(_hashtable_not_equal(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_not_equal__size_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("signed int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__size_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__size_equal_0(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    assert_false(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 30; i < 40; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_not_equal__compare_not_equal(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_not_equal__compare_not_equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, _test__hashtable_not_equal__compare_not_equal);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_not_equal__equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_not_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_less
 */
UT_CASE_DEFINATION(_hashtable_less)
void test__hashtable_less__null_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_less__null_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_less__non_inited_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__non_inited_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("list_t<int>");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_false(_hashtable_less(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_less__size_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("signed int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__size_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__size_equal_0(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    assert_false(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__size_equal_elem_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__size_equal_elem_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 30; i < 40; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_less__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_less__compare_less(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, _test__hashtable_less__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less__equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_less(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_less_equal
 */
UT_CASE_DEFINATION(_hashtable_less_equal)
void test__hashtable_less_equal__null_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less_equal(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_less_equal__null_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less_equal(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_less_equal__non_inited_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__non_inited_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("list_t<int>");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_true(_hashtable_less_equal(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_less_equal__size_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("signed int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__size_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__size_equal_0(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    assert_true(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 30; i < 40; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_less_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_less_equal__compare_less(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, _test__hashtable_less_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_less_equal__equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_less_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_greater
 */
UT_CASE_DEFINATION(_hashtable_greater)
void test__hashtable_greater__null_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_greater__null_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_greater__non_inited_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__non_inited_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("list_t<int>");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_false(_hashtable_greater(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_greater__size_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("signed int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__size_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__size_equal_0(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    assert_false(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__size_equal_elem_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__size_equal_elem_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 30; i < 40; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_greater__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_greater__compare_less(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, _test__hashtable_greater__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater__equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_greater_equal
 */
UT_CASE_DEFINATION(_hashtable_greater_equal)
void test__hashtable_greater_equal__null_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater_equal(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_greater_equal__null_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater_equal(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_greater_equal__non_inited_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__non_inited_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("list_t<int>");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    assert_true(_hashtable_greater_equal(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_greater_equal__size_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("signed int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__size_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 0; i < 2; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__size_equal_0(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    assert_true(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_false(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 30; i < 40; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_greater_equal__compare_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_greater_equal__compare_less(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, _test__hashtable_greater_equal__compare_less);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    expect_assert_failure(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_greater_equal__equal(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_first, &i);
        _hashtable_insert_unique(pt_second, &i);
    }

    assert_true(_hashtable_greater_equal(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_swap
 */
UT_CASE_DEFINATION(_hashtable_swap)
void test__hashtable_swap__null_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_swap(NULL, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_swap__null_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_swap(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_swap__non_inited_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_swap(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_swap__non_inited_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);

    expect_assert_failure(_hashtable_swap(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_swap__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("list_t<int>");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);

    expect_assert_failure(_hashtable_swap(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_swap__not_same_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input;
}
void test__hashtable_swap__not_same_hash(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, _test__hashtable_swap__not_same_hash, NULL);

    expect_assert_failure(_hashtable_swap(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_swap__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_swap(pt_hashtable, pt_hashtable);
    assert_true(_hashtable_empty(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_swap__0_swap_n(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_second, &i);
    }

    assert_true(_hashtable_size(pt_first) == 0);
    assert_true(_hashtable_size(pt_second) == 10);
    _hashtable_swap(pt_first, pt_second);
    assert_true(_hashtable_size(pt_first) == 10);
    assert_true(_hashtable_size(pt_second) == 0);

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_swap__n_swap_0(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_first, &i);
    }

    assert_true(_hashtable_size(pt_first) == 10);
    assert_true(_hashtable_size(pt_second) == 0);
    _hashtable_swap(pt_first, pt_second);
    assert_true(_hashtable_size(pt_first) == 0);
    assert_true(_hashtable_size(pt_second) == 10);

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_swap__n_swap_n(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_first, &i);
    }
    for(i = 100; i < 110; ++i)
    {
        _hashtable_insert_equal(pt_second, &i);
    }

    assert_true(_hashtable_size(pt_first) == 10);
    assert_true(_hashtable_size(pt_second) == 10);
    assert_true(_hashtable_less(pt_first, pt_second));
    _hashtable_swap(pt_first, pt_second);
    assert_true(_hashtable_size(pt_first) == 10);
    assert_true(_hashtable_size(pt_second) == 10);
    assert_true(_hashtable_greater(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_swap__m_swap_n(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);
    for(i = 0; i < 30; ++i)
    {
        _hashtable_insert_equal(pt_first, &i);
    }
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_second, &i);
    }

    assert_true(_hashtable_size(pt_first) == 30);
    assert_true(_hashtable_size(pt_second) == 10);
    _hashtable_swap(pt_first, pt_second);
    assert_true(_hashtable_size(pt_first) == 10);
    assert_true(_hashtable_size(pt_second) == 30);

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_insert_unique
 */
UT_CASE_DEFINATION(_hashtable_insert_unique)
void test__hashtable_insert_unique__null_hashtable(void** state)
{
    int elem = 9;
    expect_assert_failure(_hashtable_insert_unique(NULL, &elem));
}

void test__hashtable_insert_unique__null_value(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_insert_unique(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_unique__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    expect_assert_failure(_hashtable_insert_unique(pt_hashtable, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_unique__c_builtin_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }

    elem = 2;
    it_iter = _hashtable_insert_unique(pt_hashtable, &elem);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_unique__c_builtin_not_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }

    elem = -8;
    it_iter = _hashtable_insert_unique(pt_hashtable, &elem);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == -8);
    assert_true(_hashtable_size(pt_hashtable) == 11);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_unique__cstr_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_unique(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _hashtable_insert_unique(pt_hashtable, pstr);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_size(pt_hashtable) == 5);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_insert_unique__cstr_not_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_unique(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_unique(pt_hashtable, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _hashtable_insert_unique(pt_hashtable, pstr);
    assert_true(strcmp((char*)_hashtable_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(_hashtable_size(pt_hashtable) == 6);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

static void _test__hashtable_insert_unique__libcstl_hash(const void* cpv_input, void* pv_output)
{
    list_t* plist = (list_t*)cpv_input;
    list_iterator_t it_iter;

    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        *(size_t*)pv_output += *(int*)iterator_get_pointer(it_iter);
    }
}
void test__hashtable_insert_unique__libcstl_builtin_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    _hashtable_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_insert_unique__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_unique(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hashtable_insert_unique(pt_hashtable, plist);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_insert_unique__libcstl_builtin_not_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    _hashtable_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_insert_unique__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _hashtable_insert_unique(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _hashtable_insert_unique(pt_hashtable, plist);
    assert_true(*(int*)list_front((list_t*)_hashtable_iterator_get_pointer(it_iter)) == 5);
    assert_true(_hashtable_size(pt_hashtable) == 11);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

typedef struct _tag_test__hashtable_insert_unique__user_define
{
    int n_elem;
}_test__hashtable_insert_unique__user_define_t;
void test__hashtable_insert_unique__user_define_equal(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _hashtable_iterator_t it_iter;
    _test__hashtable_insert_unique__user_define_t elem;
    int i = 0;

    type_register(_test__hashtable_insert_unique__user_define_t, NULL, NULL, NULL, NULL);

    pt_hashtable = _create_hashtable("_test__hashtable_insert_unique__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_unique(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    it_iter = _hashtable_insert_unique(pt_hashtable, &elem);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_unique__user_define_not_equal(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_insert_unique__user_define_t");
    _hashtable_iterator_t it_iter;
    _test__hashtable_insert_unique__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _hashtable_insert_unique(pt_hashtable, &elem);
    }

    elem.n_elem = 7;
    it_iter = _hashtable_insert_unique(pt_hashtable, &elem);
    assert_true(((_test__hashtable_insert_unique__user_define_t*)_hashtable_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(_hashtable_size(pt_hashtable) == 11);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_insert_equal
 */
UT_CASE_DEFINATION(_hashtable_insert_equal)
void test__hashtable_insert_equal__null_hashtable(void** state)
{
    int elem = 9;
    expect_assert_failure(_hashtable_insert_equal(NULL, &elem));
}

void test__hashtable_insert_equal__null_value(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_insert_equal(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_equal__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    expect_assert_failure(_hashtable_insert_equal(pt_hashtable, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_equal__c_builtin_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = 2;
    it_iter = _hashtable_insert_equal(pt_hashtable, &elem);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 2);
    assert_true(_hashtable_size(pt_hashtable) == 11);
    assert_true(_hashtable_count(pt_hashtable, &elem) == 2);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_equal__c_builtin_not_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = -8;
    it_iter = _hashtable_insert_equal(pt_hashtable, &elem);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == -8);
    assert_true(_hashtable_size(pt_hashtable) == 11);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_equal__cstr_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    it_iter = _hashtable_insert_equal(pt_hashtable, pstr);
    assert_true(strcmp((char*)_hashtable_iterator_get_pointer(it_iter), "ggg") == 0);
    assert_true(_hashtable_size(pt_hashtable) == 6);
    assert_true(_hashtable_count(pt_hashtable, pstr) == 2);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_insert_equal__cstr_not_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "vvvv");
    it_iter = _hashtable_insert_equal(pt_hashtable, pstr);
    assert_true(strcmp((char*)_hashtable_iterator_get_pointer(it_iter), "vvvv") == 0);
    assert_true(_hashtable_size(pt_hashtable) == 6);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_insert_equal__libcstl_builtin_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    _hashtable_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_insert_unique__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    it_iter = _hashtable_insert_equal(pt_hashtable, plist);
    assert_true(*(int*)list_front((list_t*)_hashtable_iterator_get_pointer(it_iter)) == 6);
    assert_true(_hashtable_size(pt_hashtable) == 11);
    assert_true(_hashtable_count(pt_hashtable, plist) == 2);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_insert_equal__libcstl_builtin_not_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    _hashtable_iterator_t it_iter;
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_insert_unique__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i * 2);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 5);
    it_iter = _hashtable_insert_equal(pt_hashtable, plist);
    assert_true(*(int*)list_front((list_t*)_hashtable_iterator_get_pointer(it_iter)) == 5);
    assert_true(_hashtable_size(pt_hashtable) == 11);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

typedef struct _tag_test__hashtable_insert_equal__user_define
{
    int n_elem;
}_test__hashtable_insert_equal__user_define_t;
void test__hashtable_insert_equal__user_define_equal(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _hashtable_iterator_t it_iter;
    _test__hashtable_insert_equal__user_define_t elem;
    int i = 0;

    type_register(_test__hashtable_insert_equal__user_define_t, NULL, NULL, NULL, NULL);

    pt_hashtable = _create_hashtable("_test__hashtable_insert_equal__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    it_iter = _hashtable_insert_equal(pt_hashtable, &elem);
    assert_true(((_test__hashtable_insert_equal__user_define_t*)_hashtable_iterator_get_pointer(it_iter))->n_elem == 8);
    assert_true(_hashtable_size(pt_hashtable) == 11);
    assert_true(_hashtable_count(pt_hashtable, &elem) == 2);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_insert_equal__user_define_not_equal(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_insert_equal__user_define_t");
    _hashtable_iterator_t it_iter;
    _test__hashtable_insert_equal__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 7;
    it_iter = _hashtable_insert_equal(pt_hashtable, &elem);
    assert_true(((_test__hashtable_insert_equal__user_define_t*)_hashtable_iterator_get_pointer(it_iter))->n_elem == 7);
    assert_true(_hashtable_size(pt_hashtable) == 11);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_insert_unique_range
 */
UT_CASE_DEFINATION(_hashtable_insert_unique_range)
void test__hashtable_insert_unique_range__null_hashtable(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(_hashtable_insert_unique_range(NULL, vector_begin(pvec), vector_end(pvec)));

    vector_destroy(pvec);
}

void test__hashtable_insert_unique_range__non_inited(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;

    list_init(plist);
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    expect_assert_failure(_hashtable_insert_unique_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

void test__hashtable_insert_unique_range__invalid_begin(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    slist_init(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_containertype = 3333;
    expect_assert_failure(_hashtable_insert_unique_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__hashtable_insert_unique_range__invalid_end(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    deque_init(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_containertype = 333;
    expect_assert_failure(_hashtable_insert_unique_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__hashtable_insert_unique_range__invalid_range(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    set_init(pset);
    set_insert(pset, elem);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_hashtable_insert_unique_range(pt_dest, it_end, it_begin));

    _hashtable_destroy(pt_dest);
    set_destroy(pset);
}

void test__hashtable_insert_unique_range__not_same_type(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    multiset_init(pmset);

    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_hashtable_insert_unique_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__hashtable_insert_unique_range__empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    hash_set_init(phset);

    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _hashtable_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__hashtable_insert_unique_range__non_empty_equal(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(phmset, i);
    }

    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _hashtable_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__hashtable_insert_unique_range__non_empty_dest_src_dup(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    vector_t* pvec = create_vector(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    _hashtable_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 15);

    _hashtable_destroy(pt_dest);
    vector_destroy(pvec);
}

void test__hashtable_insert_unique_range__non_empty_src_dup(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 15; i < 25; ++i)
    {
        list_push_back(plist, i);
        list_push_back(plist, i);
    }

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    _hashtable_insert_unique_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

static void _test__hashtable_insert_unique_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_insert_unique_range__compare(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    set_init_ex(pset, _test__hashtable_insert_unique_range__compare);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    _hashtable_insert_unique_range(pt_dest, it_begin, it_end);

    _hashtable_destroy(pt_dest);
    set_destroy(pset);
}

/*
 * test _hashtable_insert_unique_array
 */
UT_CASE_DEFINATION(_hashtable_insert_unique_array)
void test__hashtable_insert_unique_array__null_hashtable(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_hashtable_insert_unique_array(NULL, an_array, 10));
}

void test__hashtable_insert_unique_array__non_inited(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    expect_assert_failure(_hashtable_insert_unique_array(pt_dest, an_array, 10));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_unique_array__invalid_array(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init(pt_dest, 0, NULL, NULL);

    expect_assert_failure(_hashtable_insert_unique_array(pt_dest, NULL, 10));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_unique_array__empty(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init(pt_dest, 0, NULL, NULL);

    _hashtable_insert_unique_array(pt_dest, an_array, 0);
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_unique_array__non_empty_equal(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        an_array[i - 10] = i;
    }

    _hashtable_insert_unique_array(pt_dest, an_array, 10);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_unique_array__non_empty_dest_src_dup(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        an_array[i - 5] = i;
    }

    _hashtable_insert_unique_array(pt_dest, an_array, 10);
    assert_true(_hashtable_size(pt_dest) == 15);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_unique_array__non_empty_src_dup(void** state)
{
    int an_array[20] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for (i = 0; i < 20; i += 2)
    {
        an_array[i] = i + 15;
        an_array[i + 1] = i + 15;
    }

    _hashtable_insert_unique_array(pt_dest, an_array, 20);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
}

/*
 * test _hashtable_insert_equal_range
 */
UT_CASE_DEFINATION(_hashtable_insert_equal_range)
void test__hashtable_insert_equal_range__null_hashtable(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(_hashtable_insert_equal_range(NULL, vector_begin(pvec), vector_end(pvec)));

    vector_destroy(pvec);
}

void test__hashtable_insert_equal_range__non_inited(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;

    list_init(plist);
    it_begin = list_begin(plist);
    it_end = list_end(plist);
    expect_assert_failure(_hashtable_insert_equal_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

void test__hashtable_insert_equal_range__invalid_begin(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    slist_init(pslist);
    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_begin._t_iteratortype = 32232;
    expect_assert_failure(_hashtable_insert_equal_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    slist_destroy(pslist);
}

void test__hashtable_insert_equal_range__invalid_end(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    deque_t* pdeq = create_deque(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    deque_init(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_end._t_containertype = 444;
    expect_assert_failure(_hashtable_insert_equal_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    deque_destroy(pdeq);
}

void test__hashtable_insert_equal_range__invalid_range(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;
    int elem = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    set_init(pset);
    set_insert(pset, elem);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    expect_assert_failure(_hashtable_insert_equal_range(pt_dest, it_end, it_begin));

    _hashtable_destroy(pt_dest);
    set_destroy(pset);
}

void test__hashtable_insert_equal_range__not_same_type(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    multiset_t* pmset = create_multiset(double);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    multiset_init(pmset);

    it_begin = multiset_begin(pmset);
    it_end = multiset_end(pmset);
    expect_assert_failure(_hashtable_insert_equal_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
    multiset_destroy(pmset);
}

void test__hashtable_insert_equal_range__empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_set_t* phset = create_hash_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    hash_set_init(phset);

    it_begin = hash_set_begin(phset);
    it_end = hash_set_end(phset);
    _hashtable_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
    hash_set_destroy(phset);
}

void test__hashtable_insert_equal_range__non_empty_equal(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    hash_multiset_t* phmset = create_hash_multiset(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    hash_multiset_init(phmset);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        hash_multiset_insert(phmset, i);
    }

    it_begin = hash_multiset_begin(phmset);
    it_end = hash_multiset_end(phmset);
    _hashtable_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
    hash_multiset_destroy(phmset);
}

void test__hashtable_insert_equal_range__non_empty_dest_src_dup(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    vector_t* pvec = create_vector(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        vector_push_back(pvec, i);
    }

    it_begin = vector_begin(pvec);
    it_end = vector_end(pvec);
    _hashtable_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
    vector_destroy(pvec);
}

void test__hashtable_insert_equal_range__non_empty_src_dup(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    list_t* plist = create_list(int);
    iterator_t it_begin;
    iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 15; i < 25; ++i)
    {
        list_push_back(plist, i);
        list_push_back(plist, i);
    }

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    _hashtable_insert_equal_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 30);

    _hashtable_destroy(pt_dest);
    list_destroy(plist);
}

static void _test__hashtable_insert_equal_range__compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
void test__hashtable_insert_equal_range__compare(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    set_t* pset = create_set(int);
    iterator_t it_begin;
    iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    set_init_ex(pset, _test__hashtable_insert_equal_range__compare);

    it_begin = set_begin(pset);
    it_end = set_end(pset);
    _hashtable_insert_equal_range(pt_dest, it_begin, it_end);

    _hashtable_destroy(pt_dest);
    set_destroy(pset);
}

/*
 * test _hashtable_insert_equal_array
 */
UT_CASE_DEFINATION(_hashtable_insert_equal_array)
void test__hashtable_insert_equal_array__null_hashtable(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(_hashtable_insert_equal_array(NULL, an_array, 10));
}

void test__hashtable_insert_equal_array__non_inited(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    expect_assert_failure(_hashtable_insert_equal_array(pt_dest, an_array, 10));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_equal_array__invalid_array(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init(pt_dest, 0, NULL, NULL);
    expect_assert_failure(_hashtable_insert_equal_array(pt_dest, NULL, 10));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_equal_array__empty(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");

    _hashtable_init(pt_dest, 0, NULL, NULL);

    _hashtable_insert_equal_array(pt_dest, an_array, 0);
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_equal_array__non_empty_equal(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 10; i < 20; ++i)
    {
        an_array[i - 10] = i;
    }

    _hashtable_insert_equal_array(pt_dest, an_array, 10);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_equal_array__non_empty_dest_src_dup(void** state)
{
    int an_array[10] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for(i = 5; i < 15; ++i)
    {
        an_array[i - 5] = i;
    }

    _hashtable_insert_equal_array(pt_dest, an_array, 10);
    assert_true(_hashtable_size(pt_dest) == 20);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_insert_equal_array__non_empty_src_dup(void** state)
{
    int an_array[20] = {0};
    _hashtable_t* pt_dest = _create_hashtable("int");
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }
    for (i = 0; i < 20; i += 2)
    {
        an_array[i] = i + 15;
        an_array[i + 1] = i + 15;
    }

    _hashtable_insert_equal_array(pt_dest, an_array, 20);
    assert_true(_hashtable_size(pt_dest) == 30);

    _hashtable_destroy(pt_dest);
}

/*
 * test _hashtable_erase_pos
 */
UT_CASE_DEFINATION(_hashtable_erase_pos)
void test__hashtable_erase_pos__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    expect_assert_failure(_hashtable_erase_pos(NULL, _hashtable_begin(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_pos__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_pos;
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_pos = _hashtable_begin(pt_hashtable);
    pt_hashtable->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_hashtable_erase_pos(pt_hashtable, it_pos));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_pos__invalid_pos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_pos;
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_pos = _hashtable_begin(pt_hashtable);
    it_pos._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_erase_pos(pt_hashtable, it_pos));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_pos__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_pos;
    int elem = 9;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_pos = _hashtable_end(pt_hashtable);
    expect_assert_failure(_hashtable_erase_pos(pt_hashtable, it_pos));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_pos__begin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_pos;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }
    it_pos = _hashtable_begin(pt_hashtable);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_pos) == 0);
    _hashtable_erase_pos(pt_hashtable, it_pos);
    assert_true(_hashtable_size(pt_hashtable) == 9);
    it_pos = _hashtable_begin(pt_hashtable);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_pos) == 1);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_pos__middle(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_pos;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }
    i = 4;
    it_pos = _hashtable_find(pt_hashtable, &i);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_pos) == 4);
    _hashtable_erase_pos(pt_hashtable, it_pos);
    assert_true(_hashtable_size(pt_hashtable) == 9);
    it_pos = _hashtable_find(pt_hashtable, &i);
    assert_true(_hashtable_iterator_equal(it_pos, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_pos__last(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_pos;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_unique(pt_hashtable, &i);
    }
    it_pos = _hashtable_iterator_prev(_hashtable_end(pt_hashtable));
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_pos) == 9);
    _hashtable_erase_pos(pt_hashtable, it_pos);
    assert_true(_hashtable_size(pt_hashtable) == 9);
    it_pos = _hashtable_iterator_prev(_hashtable_end(pt_hashtable));
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_pos) == 8);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_pos__erase_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_pos;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &i);
    assert_true(_hashtable_size(pt_hashtable) == 1);
    it_pos = _hashtable_begin(pt_hashtable);
    _hashtable_erase_pos(pt_hashtable, it_pos);
    assert_true(_hashtable_size(pt_hashtable) == 0);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_erase_range
 */
UT_CASE_DEFINATION(_hashtable_erase_range)
void test__hashtable_erase_range__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_erase_range(NULL, _hashtable_begin(pt_hashtable), _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase_range__non_inited(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);

    it_begin = _hashtable_begin(pt_dest);
    it_end = _hashtable_end(pt_dest);
    pt_dest->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_hashtable_erase_range(pt_dest, it_begin, it_end));
    pt_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__invalid_begin(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);

    it_begin = _hashtable_begin(pt_dest);
    it_end = _hashtable_end(pt_dest);
    it_begin._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_erase_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__invalid_end(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);

    it_begin = _hashtable_begin(pt_dest);
    it_end = _hashtable_end(pt_dest);
    it_end._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_erase_range(pt_dest, it_begin, it_end));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__invalid_range(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;
    int elem = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    _hashtable_insert_unique(pt_dest, &elem);

    it_begin = _hashtable_begin(pt_dest);
    it_end = _hashtable_end(pt_dest);
    expect_assert_failure(_hashtable_erase_range(pt_dest, it_end, it_begin));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__empty(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;

    _hashtable_init(pt_dest, 0, NULL, NULL);

    it_begin = _hashtable_begin(pt_dest);
    it_end = _hashtable_end(pt_dest);
    _hashtable_erase_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_empty(pt_dest));

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__begin(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }

    it_begin = _hashtable_begin(pt_dest);
    it_end = _hashtable_iterator_next(it_begin);
    _hashtable_erase_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 9);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_begin(pt_dest)) == 1);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__middle(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }

    it_begin = _hashtable_iterator_next(_hashtable_begin(pt_dest));
    it_end = _hashtable_iterator_next(it_begin);
    _hashtable_erase_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 9);
    it_begin = _hashtable_begin(pt_dest);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_begin) == 0);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_iterator_next(it_begin)) == 2);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__end(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }

    it_end = _hashtable_end(pt_dest);
    it_begin = _hashtable_iterator_prev(it_end);
    _hashtable_erase_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 9);
    it_end = _hashtable_end(pt_dest);
    assert_true(*(int*)_hashtable_iterator_get_pointer(_hashtable_iterator_prev(it_end)) == 8);

    _hashtable_destroy(pt_dest);
}

void test__hashtable_erase_range__all(void** state)
{
    _hashtable_t* pt_dest = _create_hashtable("int");
    _hashtable_iterator_t it_begin;
    _hashtable_iterator_t it_end;
    int i = 0;

    _hashtable_init(pt_dest, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_dest, &i);
    }

    it_begin = _hashtable_begin(pt_dest);
    it_end = _hashtable_end(pt_dest);
    _hashtable_erase_range(pt_dest, it_begin, it_end);
    assert_true(_hashtable_size(pt_dest) == 0);

    _hashtable_destroy(pt_dest);
}

/*
 * test _hashtable_erase
 */
UT_CASE_DEFINATION(_hashtable_erase)
void test__hashtable_erase__null_hashtable(void** state)
{
    int elem = 9;
    expect_assert_failure(_hashtable_erase(NULL, &elem));
}

void test__hashtable_erase__null_value(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_erase(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;

    expect_assert_failure(_hashtable_erase(pt_hashtable, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase__c_builtin_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = 24;
    assert_true(_hashtable_erase(pt_hashtable, &elem) == 0);
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase__c_builtin_1(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = 8;
    assert_true(_hashtable_erase(pt_hashtable, &elem) == 1);
    assert_true(_hashtable_size(pt_hashtable) == 9);
    assert_true(_hashtable_count(pt_hashtable, &elem) == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase__c_builtin_n(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem;
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
        _hashtable_insert_equal(pt_hashtable, &i);
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    elem = 8;
    assert_true(_hashtable_erase(pt_hashtable, &elem) == 3);
    assert_true(_hashtable_size(pt_hashtable) == 27);
    assert_true(_hashtable_count(pt_hashtable, &elem) == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase__cstr_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "gggppgg");
    assert_true(_hashtable_erase(pt_hashtable, pstr) == 0);
    assert_true(_hashtable_size(pt_hashtable) == 5);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_erase__cstr_1(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_hashtable_erase(pt_hashtable, pstr) == 1);
    assert_true(_hashtable_size(pt_hashtable) == 4);
    assert_true(_hashtable_count(pt_hashtable, pstr) == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_erase__cstr_n(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pstr = create_string();

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init(pstr);
    string_assign_cstr(pstr, "aaa");
    _hashtable_insert_equal(pt_hashtable, pstr);
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "ggg");
    _hashtable_insert_equal(pt_hashtable, pstr);
    _hashtable_insert_equal(pt_hashtable, pstr);
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "nghl");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "asery");
    _hashtable_insert_equal(pt_hashtable, pstr);
    string_assign_cstr(pstr, "linux");
    _hashtable_insert_equal(pt_hashtable, pstr);

    string_assign_cstr(pstr, "ggg");
    assert_true(_hashtable_erase(pt_hashtable, pstr) == 3);
    assert_true(_hashtable_size(pt_hashtable) == 5);
    assert_true(_hashtable_count(pt_hashtable, pstr) == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_erase__libcstl_builtin_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_insert_unique__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 66);
    assert_true(_hashtable_erase(pt_hashtable, plist) == 0);
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_erase__libcstl_builtin_1(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_insert_unique__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hashtable_erase(pt_hashtable, plist) == 1);
    assert_true(_hashtable_size(pt_hashtable) == 9);
    assert_true(_hashtable_count(pt_hashtable, plist) == 0);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

void test__hashtable_erase__libcstl_builtin_n(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("list_t<int>");
    list_t* plist = create_list(int);
    int i = 0;

    _hashtable_init(pt_hashtable, 0, _test__hashtable_insert_unique__libcstl_hash, NULL);
    list_init(plist);

    for(i = 0; i < 10; i++)
    {
        list_clear(plist);
        list_push_back(plist, i);
        _hashtable_insert_equal(pt_hashtable, plist);
        _hashtable_insert_equal(pt_hashtable, plist);
    }

    list_clear(plist);
    list_push_back(plist, 6);
    assert_true(_hashtable_erase(pt_hashtable, plist) == 2);
    assert_true(_hashtable_size(pt_hashtable) == 18);
    assert_true(_hashtable_count(pt_hashtable, plist) == 0);

    _hashtable_destroy(pt_hashtable);
    list_destroy(plist);
}

typedef struct _tag_test__hashtable_erase__user_define
{
    int n_elem;
}_test__hashtable_erase__user_define_t;
void test__hashtable_erase__user_define_0(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _test__hashtable_erase__user_define_t elem;
    int i = 0;

    type_register(_test__hashtable_erase__user_define_t, NULL, NULL, NULL, NULL);

    pt_hashtable = _create_hashtable("_test__hashtable_erase__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i;
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 86;
    assert_true(_hashtable_erase(pt_hashtable, &elem) == 0);
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase__user_define_1(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_erase__user_define_t");
    _test__hashtable_insert_equal__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hashtable_erase(pt_hashtable, &elem) == 1);
    assert_true(_hashtable_size(pt_hashtable) == 9);
    assert_true(_hashtable_count(pt_hashtable, &elem) == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_erase__user_define_n(void** state)
{
    _hashtable_t* pt_hashtable =  _create_hashtable("_test__hashtable_erase__user_define_t");
    _test__hashtable_insert_equal__user_define_t elem;
    int i = 0;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    for(i = 0; i < 10; ++i)
    {
        elem.n_elem = i * 2;
        _hashtable_insert_equal(pt_hashtable, &elem);
        _hashtable_insert_equal(pt_hashtable, &elem);
        _hashtable_insert_equal(pt_hashtable, &elem);
    }

    elem.n_elem = 8;
    assert_true(_hashtable_erase(pt_hashtable, &elem) == 3);
    assert_true(_hashtable_size(pt_hashtable) == 27);
    assert_true(_hashtable_count(pt_hashtable, &elem) == 0);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_resize
 */
UT_CASE_DEFINATION(_hashtable_resize)
void test__hashtable_resize__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_resize(NULL, 200));
}

void test__hashtable_resize__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    expect_assert_failure(_hashtable_resize(pt_hashtable, 300));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_resize__less_bucketcount(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);
    assert_true(_hashtable_size(pt_hashtable) == 10);
    _hashtable_resize(pt_hashtable, 5);
    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_resize__equal_bucketcount(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);
    assert_true(_hashtable_size(pt_hashtable) == 10);
    _hashtable_resize(pt_hashtable, 53);
    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_resize__greater_bucketcount(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int i;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }

    assert_true(_hashtable_bucket_count(pt_hashtable) == 53);
    assert_true(_hashtable_size(pt_hashtable) == 10);
    _hashtable_resize(pt_hashtable, 100);
    assert_true(_hashtable_bucket_count(pt_hashtable) == 193);
    assert_true(_hashtable_size(pt_hashtable) == 10);

    _hashtable_destroy(pt_hashtable);
}

