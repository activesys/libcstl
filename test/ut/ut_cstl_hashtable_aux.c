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
#include "cstl/cdeque.h"
#include "cstl/cset.h"

#include "ut_def.h"
#include "ut_cstl_hashtable_aux.h"

UT_SUIT_DEFINATION(cstl_hashtable_aux, _hashtable_is_created)
/*
 * test _hashtable_is_created
 */
UT_CASE_DEFINATION(_hashtable_is_created)
void test__hashtable_is_created__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_is_created(NULL));
}

void test__hashtable_is_created__non_inited_allocator(void** state)
{
    _hashtable_t htable;

    type_register(_hashnode_t*, NULL, NULL, NULL, NULL);

    _create_vector_auxiliary(&htable._vec_bucket, _HASHTABLE_NODE_NAME);
    htable._t_nodecount = 0;
    htable._ufun_hash = NULL;
    htable._bfun_compare = NULL;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);

#ifdef CSTL_MEMORY_MANAGEMENT
    htable._t_allocator._t_mempoolsize = 1;
    assert_false(_hashtable_is_created(&htable));
    htable._t_allocator._t_mempoolsize = 0;
#else
    assert_true(_hashtable_is_created(&htable));
#endif

    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_rbroot_bucket(void** state)
{
    _hashtable_t htable;

    htable._t_nodecount = 0;
    htable._ufun_hash = NULL;
    htable._bfun_compare = NULL;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_rbroot_hash(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._vec_bucket, _HASHTABLE_NODE_NAME);
    htable._ufun_hash = (unary_function_t)0xabc;
    htable._bfun_compare = NULL;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_compare(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._vec_bucket, _HASHTABLE_NODE_NAME);
    htable._ufun_hash = NULL;
    htable._bfun_compare = (binary_function_t)0x888;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_nodecount(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._vec_bucket, _HASHTABLE_NODE_NAME);
    htable._ufun_hash = NULL;
    htable._bfun_compare = NULL;
    htable._t_nodecount = 9;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_typeinfo_style(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._vec_bucket, _HASHTABLE_NODE_NAME);
    htable._ufun_hash = NULL;
    htable._bfun_compare = NULL;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = 90;
    htable._t_typeinfo._pt_type = (_type_t*)0x999;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__invalid_typeinfo_type(void** state)
{
    _hashtable_t htable;

    _create_vector_auxiliary(&htable._vec_bucket, _HASHTABLE_NODE_NAME);
    htable._ufun_hash = NULL;
    htable._bfun_compare = NULL;
    htable._t_nodecount = 0;
    htable._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    htable._t_typeinfo._pt_type = NULL;
    _alloc_init(&htable._t_allocator);
    assert_false(_hashtable_is_created(&htable));
    _alloc_destroy(&htable._t_allocator);
}

void test__hashtable_is_created__created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_is_inited
 */
UT_CASE_DEFINATION(_hashtable_is_inited)
void test__hashtable_is_inited__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_is_inited(NULL));
}

void test__hashtable_is_inited__invalid_typeinfo_style(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 8, NULL, NULL);

    pt_hashtable->_t_typeinfo._t_style = 999;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_typeinfo_type(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _type_t* pt_type = NULL;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    pt_type = pt_hashtable->_t_typeinfo._pt_type;
    pt_hashtable->_t_typeinfo._pt_type = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_t_typeinfo._pt_type = pt_type;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_hash(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    unary_function_t t_hash = NULL;

    _hashtable_init(pt_hashtable, 199, NULL, NULL);

    t_hash = pt_hashtable->_ufun_hash;
    pt_hashtable->_ufun_hash = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_ufun_hash = t_hash;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_compare(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    binary_function_t t_compare = NULL;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);

    t_compare = pt_hashtable->_bfun_compare;
    pt_hashtable->_bfun_compare = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_bfun_compare = t_compare;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__invalid_bucket(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _byte_t* pby_start = NULL;

    _hashtable_init(pt_hashtable, 3345, NULL, NULL);

    pby_start = pt_hashtable->_vec_bucket._pby_start;
    pt_hashtable->_vec_bucket._pby_start = NULL;
    assert_false(_hashtable_is_inited(pt_hashtable));
    pt_hashtable->_vec_bucket._pby_start = pby_start;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_is_inited__inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 5, NULL, NULL);

    assert_true(_hashtable_is_inited(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_belong_to_hashtable
 */
UT_CASE_DEFINATION(_hashtable_iterator_belong_to_hashtable)
void test__hashtable_iterator_belong_to_hashtable__null_hashtable(void** state)
{
    _hashtable_iterator_t it_iter;
    expect_assert_failure(_hashtable_iterator_belong_to_hashtable(NULL, it_iter));
}

void test__hashtable_iterator_belong_to_hashtable__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    it_iter = _hashtable_begin(pt_hashtable);
    pt_hashtable->_ufun_hash = NULL;
    expect_assert_failure(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));
    pt_hashtable->_ufun_hash = _hashtable_default_hash;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_belong_to_hashtable__null_bucketpos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    it_iter = _hashtable_begin(pt_hashtable);
    it_iter._t_pos._t_hashpos._pby_bucketpos = NULL;
    expect_assert_failure(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_belong_to_hashtable__null_hashtablepos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    it_iter = _hashtable_begin(pt_hashtable);
    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_belong_to_hashtable__begin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int n_elem = 9;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    _hashtable_insert_equal(pt_hashtable, &n_elem);
    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_belong_to_hashtable__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int n_elem = 9;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    _hashtable_insert_equal(pt_hashtable, &n_elem);
    it_iter = _hashtable_end(pt_hashtable);
    assert_true(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_belong_to_hashtable__middle(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int i = 0;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }
    it_iter = _hashtable_iterator_next(_hashtable_begin(pt_hashtable));
    assert_true(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_belong_to_hashtable__invalid_bucketpos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int i = 0;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }
    it_iter = _hashtable_iterator_next(_hashtable_begin(pt_hashtable));
    it_iter._t_pos._t_hashpos._pby_bucketpos = (char*)0x44444;
    assert_false(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_belong_to_hashtable__invalid_corepos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int i = 0;

    _hashtable_init(pt_hashtable, 9, NULL, NULL);
    for(i = 0; i < 10; ++i)
    {
        _hashtable_insert_equal(pt_hashtable, &i);
    }
    it_iter = _hashtable_iterator_next(_hashtable_begin(pt_hashtable));
    it_iter._t_pos._t_hashpos._pby_corepos = (char*)0x04;
    assert_false(_hashtable_iterator_belong_to_hashtable(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_same_hashtable_iterator_type
 */
UT_CASE_DEFINATION(_hashtable_same_hashtable_iterator_type)
void test__hashtable_same_hashtable_iterator_type__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_same_hashtable_iterator_type(NULL, _hashtable_begin(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type__non_created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t htable;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_same_hashtable_iterator_type(&htable, _hashtable_begin(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type__invalid_iter(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_iter = _hashtable_begin(pt_hashtable);
    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_same_hashtable_iterator_type(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type__same_container(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(_hashtable_same_hashtable_iterator_type(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type__same(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t* pt_iter = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_init(pt_iter, 100, NULL, NULL);
    assert_true(_hashtable_same_hashtable_iterator_type(pt_hashtable, _hashtable_begin(pt_iter)));

    _hashtable_destroy(pt_hashtable);
    _hashtable_destroy(pt_iter);
}

void test__hashtable_same_hashtable_iterator_type__not_same(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t* pt_iter = _create_hashtable("double");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_init(pt_iter, 100, NULL, NULL);
    assert_false(_hashtable_same_hashtable_iterator_type(pt_hashtable, _hashtable_begin(pt_iter)));

    _hashtable_destroy(pt_hashtable);
    _hashtable_destroy(pt_iter);
}

/*
 * test _hashtable_same_iterator_type
 */
UT_CASE_DEFINATION(_hashtable_same_iterator_type)
void test__hashtable_same_iterator_type__null_hashtable(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    expect_assert_failure(_hashtable_same_iterator_type(NULL, vector_begin(pvec)));

    vector_destroy(pvec);
}

void test__hashtable_same_iterator_type__non_created(void** state)
{
    list_t* plist = create_list(int);
    _hashtable_t htable;

    list_init(plist);
    expect_assert_failure(_hashtable_same_iterator_type(&htable, list_begin(plist)));

    list_destroy(plist);
}

void test__hashtable_same_iterator_type__invalid_iter(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    slist_t* pslist = create_slist(int);
    iterator_t it_iter;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    slist_init(pslist);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 444;
    expect_assert_failure(_hashtable_same_iterator_type(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
    slist_destroy(pslist);
}

void test__hashtable_same_iterator_type__same(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    deque_t* pdeq = create_deque(int);

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    deque_init(pdeq);
    assert_true(_hashtable_same_iterator_type(pt_hashtable, deque_begin(pdeq)));

    _hashtable_destroy(pt_hashtable);
    deque_destroy(pdeq);
}

void test__hashtable_same_iterator_type__not_same(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    set_t* pset = create_set(double);

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    set_init(pset);
    assert_false(_hashtable_same_iterator_type(pt_hashtable, set_begin(pset)));

    _hashtable_destroy(pt_hashtable);
    set_destroy(pset);
}

/*
 * test _hashtable_same_hashtable_iterator_type_ex
 */
UT_CASE_DEFINATION(_hashtable_same_hashtable_iterator_type_ex)
void test__hashtable_same_hashtable_iterator_type_ex__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_same_hashtable_iterator_type_ex(NULL, _hashtable_begin(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type_ex__non_created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t htable;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_same_hashtable_iterator_type_ex(&htable, _hashtable_begin(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type_ex__invalid_iter(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_iter = _hashtable_begin(pt_hashtable);
    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_same_hashtable_iterator_type_ex(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type_ex__same_container(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(_hashtable_same_hashtable_iterator_type_ex(pt_hashtable, it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_hashtable_iterator_type_ex__same(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t* pt_iter = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_init(pt_iter, 0, NULL, NULL);
    assert_true(_hashtable_same_hashtable_iterator_type_ex(pt_hashtable, _hashtable_begin(pt_iter)));

    _hashtable_destroy(pt_hashtable);
    _hashtable_destroy(pt_iter);
}

void test__hashtable_same_hashtable_iterator_type_ex__not_same_type(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t* pt_iter = _create_hashtable("double");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_init(pt_iter, 0, NULL, NULL);
    assert_false(_hashtable_same_hashtable_iterator_type_ex(pt_hashtable, _hashtable_begin(pt_iter)));

    _hashtable_destroy(pt_hashtable);
    _hashtable_destroy(pt_iter);
}

static void _test__hashtable_same_hashtable_iterator_type_ex__not_same_hash(const void* cpv_first, void* pv_output)
{
    pv_output = (void*)cpv_first;
}
void test__hashtable_same_hashtable_iterator_type_ex__not_same_hash(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t* pt_iter = _create_hashtable("double");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_init(pt_iter, 0, _test__hashtable_same_hashtable_iterator_type_ex__not_same_hash, NULL);
    assert_false(_hashtable_same_hashtable_iterator_type_ex(pt_hashtable, _hashtable_begin(pt_iter)));

    _hashtable_destroy(pt_hashtable);
    _hashtable_destroy(pt_iter);
}

static void _test__hashtable_same_hashtable_iterator_type_ex__not_same_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_first + *(int*)cpv_second;
}
void test__hashtable_same_hashtable_iterator_type_ex__not_same_compare(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_t* pt_iter = _create_hashtable("double");

    _hashtable_init(pt_hashtable, 0, NULL, _test__hashtable_same_hashtable_iterator_type_ex__not_same_compare);
    _hashtable_init(pt_iter, 0, NULL, NULL);
    assert_false(_hashtable_same_hashtable_iterator_type_ex(pt_hashtable, _hashtable_begin(pt_iter)));

    _hashtable_destroy(pt_hashtable);
    _hashtable_destroy(pt_iter);
}

/*
 * test _hashtable_same_type
 */
UT_CASE_DEFINATION(_hashtable_same_type)
void test__hashtable_same_type__null_first(void** state)
{
    _hashtable_t htable;

    expect_assert_failure(_hashtable_same_type(NULL, &htable));
}

void test__hashtable_same_type__null_second(void** state)
{
    _hashtable_t htable;

    expect_assert_failure(_hashtable_same_type(&htable, NULL));
}

void test__hashtable_same_type__non_created_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    pt_first->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_hashtable_same_type(pt_first, pt_second));
    pt_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_same_type__non_created_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    pt_second->_t_typeinfo._t_style = 22222;
    expect_assert_failure(_hashtable_same_type(pt_first, pt_second));
    pt_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_same_type__same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    assert_true(_hashtable_same_type(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_same_type__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    assert_true(_hashtable_same_type(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_type__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("double");

    assert_false(_hashtable_same_type(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_same_type__not_same_hash(const void* cpv_input, void* pv_output)
{
    pv_output = (void*)cpv_input;
}
void test__hashtable_same_type__not_same_hash(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, _test__hashtable_same_type__not_same_hash, NULL);
    assert_true(_hashtable_same_type(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_same_type__not_same_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_first + *(int*)cpv_second;
}
void test__hashtable_same_type__not_same_compare(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, _test__hashtable_same_type__not_same_compare);
    _hashtable_init(pt_second, 0, NULL, NULL);
    assert_true(_hashtable_same_type(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_same_type_ex
 */
UT_CASE_DEFINATION(_hashtable_same_type_ex)
void test__hashtable_same_type_ex__null_first(void** state)
{
    _hashtable_t htable;

    expect_assert_failure(_hashtable_same_type_ex(NULL, &htable));
}

void test__hashtable_same_type_ex__null_second(void** state)
{
    _hashtable_t htable;

    expect_assert_failure(_hashtable_same_type_ex(&htable, NULL));
}

void test__hashtable_same_type_ex__non_created_first(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    pt_first->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_hashtable_same_type_ex(pt_first, pt_second));
    pt_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_same_type_ex__non_created_second(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    pt_second->_t_typeinfo._t_style = 22222;
    expect_assert_failure(_hashtable_same_type_ex(pt_first, pt_second));
    pt_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_same_type_ex__same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    assert_true(_hashtable_same_type_ex(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_same_type_ex__same_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    assert_true(_hashtable_same_type_ex(pt_hashtable, pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_same_type_ex__not_same_type(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("double");

    assert_false(_hashtable_same_type_ex(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_same_type_ex__not_same_hash(const void* cpv_input, void* pv_output)
{
    pv_output = (void*)cpv_input;
}
void test__hashtable_same_type_ex__not_same_hash(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, _test__hashtable_same_type_ex__not_same_hash, NULL);
    assert_false(_hashtable_same_type_ex(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

static void _test__hashtable_same_type_ex__not_same_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_first + *(int*)cpv_second;
}
void test__hashtable_same_type_ex__not_same_compare(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");

    _hashtable_init(pt_first, 0, NULL, _test__hashtable_same_type_ex__not_same_compare);
    _hashtable_init(pt_second, 0, NULL, NULL);
    assert_false(_hashtable_same_type_ex(pt_first, pt_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

/*
 * test _hashtable_get_prime
 */
UT_CASE_DEFINATION(_hashtable_get_prime)
void test__hashtable_get_prime__0(void** state)
{
    assert_true(_hashtable_get_prime(0) == 53);
}

void test__hashtable_get_prime__53(void** state)
{
    assert_true(_hashtable_get_prime(53) == 53);
}

void test__hashtable_get_prime__8000000(void** state)
{
    assert_true(_hashtable_get_prime(8000000) == 12582917);
}

void test__hashtable_get_prime__201326611(void** state)
{
    assert_true(_hashtable_get_prime(201326611) == 201326611);
}

void test__hashtable_get_prime__4294967290(void** state)
{
    assert_true(_hashtable_get_prime(4294967290ul) == 4294967291ul);
}

void test__hashtable_get_prime__4294967291(void** state)
{
    assert_true(_hashtable_get_prime(4294967291ul) == 4294967291ul);
}

void test__hashtable_get_prime__4294967295(void** state)
{
    assert_true(_hashtable_get_prime(4294967295ul) == 4294967295ul);
}

/*
 * test _hashtable_default_hash
 */
UT_CASE_DEFINATION(_hashtable_default_hash)
void test__hashtable_default_hash__null_input(void** state)
{
    size_t t_size = 9;
    expect_assert_failure(_hashtable_default_hash(NULL, &t_size));
}

void test__hashtable_default_hash__null_output(void** state)
{
    int a = 9;
    expect_assert_failure(_hashtable_default_hash(&a, NULL));
}

void test__hashtable_default_hash__0(void** state)
{
    int a = 0;
    size_t ret = sizeof(a);
    _hashtable_default_hash(&a, &ret);
    assert_true(ret == 0);
}

void test__hashtable_default_hash__not_0(void** state)
{
    int a = 0x01020304;
    size_t ret = sizeof(a);
    _hashtable_default_hash(&a, &ret);
    assert_true(ret == 0x0a);
}

/*
 * test _hashtable_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_hashtable_init_elem_auxiliary)
void test__hashtable_init_elem_auxiliary__null_hashtable(void** state)
{
    _hashnode_t node;
    expect_assert_failure(_hashtable_init_elem_auxiliary(NULL, &node));
}

void test__hashtable_init_elem_auxiliary__null_node(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    expect_assert_failure(_hashtable_init_elem_auxiliary(pt_hashtable, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init_elem_auxiliary__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashnode_t node;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    pt_hashtable->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_init_elem_auxiliary(pt_hashtable, &node));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init_elem_auxiliary__c_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashnode_t node;
    int elem = 9;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    *(int*)node._pby_data = 100;
    _hashtable_insert_unique(pt_hashtable, &elem);
    _hashtable_init_elem_auxiliary(pt_hashtable, &node);
    assert_true(*(int*)node._pby_data == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_init_elem_auxiliary__cstr(void** state)
{
    _hashnode_t* p = NULL;
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pt_str = create_string();
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init_cstr(pt_str, "abc");
    p = malloc(_HASHTABLE_NODE_SIZE(_GET_HASHTABLE_TYPE_SIZE(pt_hashtable)));

    _hashtable_insert_unique(pt_hashtable, pt_str);
    it_iter = _hashtable_begin(pt_hashtable);
    _hashtable_init_elem_auxiliary(pt_hashtable, p);
    assert_true(strcmp(string_c_str(p->_pby_data), "") == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pt_str);
    _string_destroy_auxiliary(p->_pby_data);
    free(p);
}

void test__hashtable_init_elem_auxiliary__cstl_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("vector_t<int>");
    vector_t* pvec = create_vector(int);
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    vector_init(pvec);

    _hashtable_insert_unique(pt_hashtable, pvec);
    it_iter = _hashtable_begin(pt_hashtable);
    _hashtable_init_elem_auxiliary(pt_hashtable, (_hashnode_t*)it_iter._t_pos._t_hashpos._pby_corepos);
    assert_true(vector_empty((vector_t*)((_hashnode_t*)it_iter._t_pos._t_hashpos._pby_corepos)->_pby_data));

    vector_destroy(pvec);
    _hashtable_destroy(pt_hashtable);
}

typedef struct _tag_test__hashtable_init_elem_auxiliary__user_define
{
    int elem;
}_test__hashtable_init_elem_auxiliary__user_define_t;

void test__hashtable_init_elem_auxiliary__user_define(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _test__hashtable_init_elem_auxiliary__user_define_t elem;
    _hashtable_iterator_t it_iter;

    type_register(_test__hashtable_init_elem_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pt_hashtable = _create_hashtable("_test__hashtable_init_elem_auxiliary__user_define_t");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    elem.elem = 9;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_begin(pt_hashtable);
    _hashtable_init_elem_auxiliary(pt_hashtable, (_hashnode_t*)it_iter._t_pos._t_hashpos._pby_corepos);
    assert_true(((_test__hashtable_init_elem_auxiliary__user_define_t*)((_hashnode_t*)it_iter._t_pos._t_hashpos._pby_corepos)->_pby_data)->elem == 0);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_hash_auxiliary
 */
UT_CASE_DEFINATION(_hashtable_hash_auxiliary)
void test__hashtable_hash_auxiliary__null_hashtable(void** state)
{
    int a = 9;
    size_t ret = sizeof(a);
    expect_assert_failure(_hashtable_hash_auxiliary(NULL, &a, &ret));
}

void test__hashtable_hash_auxiliary__null_input(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    size_t ret = sizeof(int);

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_hash_auxiliary(pt_hashtable, NULL, &ret));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_hash_auxiliary__null_output(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int a = 4;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_hash_auxiliary(pt_hashtable, &a, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_hash_auxiliary__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int a = 4;
    size_t ret = sizeof(int);

    expect_assert_failure(_hashtable_hash_auxiliary(pt_hashtable, &a, &ret));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_hash_auxiliary__c_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int a = 0x01020304;
    size_t ret = sizeof(int);

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_hash_auxiliary(pt_hashtable, &a, &ret);
    assert_true(ret == 0x0a);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_hash_auxiliary__c_str(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    string_t* pt_string = create_string();
    size_t ret;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    string_init_cstr(pt_string, "abc");

    _hashtable_hash_auxiliary(pt_hashtable, pt_string, &ret);
    assert_true(ret = 294);

    string_destroy(pt_string);
    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_elem_compare_auxiliary
 */
UT_CASE_DEFINATION(_hashtable_elem_compare_auxiliary)
void test__hashtable_elem_compare_auxiliary__null_hashtable(void** state)
{
    int n_first;
    int n_second;
    bool_t t_result;
    expect_assert_failure(_hashtable_elem_compare_auxiliary(NULL, &n_first, &n_second, &t_result));
}

void test__hashtable_elem_compare_auxiliary__null_first(void** state)
{
    int n_second;
    bool_t t_result;
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_elem_compare_auxiliary(pt_hashtable, NULL, &n_second, &t_result));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_elem_compare_auxiliary__null_second(void** state)
{
    int n_first;
    bool_t t_result;
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_elem_compare_auxiliary(pt_hashtable, &n_first, NULL, &t_result));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_elem_compare_auxiliary__null_output(void** state)
{
    int n_first;
    int n_second;
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    expect_assert_failure(_hashtable_elem_compare_auxiliary(pt_hashtable, &n_first, &n_second, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_elem_compare_auxiliary__non_inited(void** state)
{
    int n_first;
    int n_second;
    bool_t b_result;
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    pt_hashtable->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_hashtable_elem_compare_auxiliary(pt_hashtable, &n_first, &n_second, &b_result));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_elem_compare_auxiliary__int(void** state)
{
    int n_first = 5;
    int n_second = 9;
    bool_t b_result = false;
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_elem_compare_auxiliary(pt_hashtable, &n_first, &n_second, &b_result);
    assert_true(b_result);

    _hashtable_destroy(pt_hashtable);
}

static void _test__hashtable_elem_compare_auxiliary__cstr_compare(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = strcmp((char*)cpv_first, (char*)cpv_second) < 0 ? true : false;
}
void test__hashtable_elem_compare_auxiliary__cstr(void** state)
{
    string_t* pstr_first = create_string();
    string_t* pstr_second = create_string();
    bool_t b_result = false;
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_init(pt_hashtable, 0, NULL, _test__hashtable_elem_compare_auxiliary__cstr_compare);

    string_init_cstr(pstr_first, "abc");
    string_init_cstr(pstr_second, "xyz");
    _hashtable_elem_compare_auxiliary(pt_hashtable, pstr_first, pstr_second, &b_result);
    assert_true(b_result);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr_first);
    string_destroy(pstr_second);
}

