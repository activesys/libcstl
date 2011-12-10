#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/chash_set.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl_hash_multiset_aux.h"

#include "ut_def.h"
#include "ut_cstl_hash_multiset_aux.h"

UT_SUIT_DEFINATION(cstl_hash_multiset_aux, _hash_multiset_get_varg_value_auxiliary)

/*
 * test _hash_multiset_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_hash_multiset_get_varg_value_auxiliary)
static void _wrapper_hash_multiset_get_varg_value_auxiliary(hash_multiset_t* phset_set, void* pv_varg, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pv_varg);
    _hash_multiset_get_varg_value_auxiliary(phset_set, val_elemlist, pv_varg);
    va_end(val_elemlist);
}

void test__hash_multiset_get_varg_value_auxiliary__null_hash_multiset_container(void** state)
{
    int n_elem;
    expect_assert_failure(_wrapper_hash_multiset_get_varg_value_auxiliary(NULL, &n_elem, 100));
}

void test__hash_multiset_get_varg_value_auxiliary__null_node(void** state)
{
    hash_multiset_t* phset_set = create_hash_multiset(int);

    expect_assert_failure(_wrapper_hash_multiset_get_varg_value_auxiliary(phset_set, NULL, 100));

    hash_multiset_destroy(phset_set);
}

/*
void test__hash_multiset_get_varg_value_auxiliary__non_created_hash_multiset_containter(void** state)
{
    int node;
    hash_multiset_t hash_multiset;

    expect_assert_failure(_wrapper_hash_multiset_get_varg_value_auxiliary(&hash_multiset, &node, 100));
}
*/

void test__hash_multiset_get_varg_value_auxiliary__c_builtin(void** state)
{
    int n_elem = 0;
    hash_multiset_t* phset_set = create_hash_multiset(int);
    hash_multiset_init(phset_set);

    _wrapper_hash_multiset_get_varg_value_auxiliary(phset_set, &n_elem, 100);
    assert_true(n_elem == 100);

    hash_multiset_destroy(phset_set);
}

void test__hash_multiset_get_varg_value_auxiliary__cstr(void** state)
{
    hash_multiset_t* phset_set = create_hash_multiset(char*);
    string_t* pstr = NULL;
    hash_multiset_init(phset_set);
    pstr = create_string();

    _wrapper_hash_multiset_get_varg_value_auxiliary(phset_set, pstr, "abcdefg");
    assert_true(strcmp(string_c_str(pstr), "abcdefg") == 0);

    string_destroy(pstr);
    hash_multiset_destroy(phset_set);
}

void test__hash_multiset_get_varg_value_auxiliary__libcstl_builtin(void** state)
{
    hash_multiset_t* phset_set = create_hash_multiset(vector_t<int>);
    vector_t* pvec = create_vector(int);
    vector_t* pvec_varg = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    hash_multiset_init(phset_set);

    _wrapper_hash_multiset_get_varg_value_auxiliary(phset_set, pvec_varg, pvec);
    assert_true(vector_equal(pvec_varg, pvec));

    vector_destroy(pvec_varg);
    hash_multiset_destroy(phset_set);
    vector_destroy(pvec);
}

void test__hash_multiset_get_varg_value_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__hash_multiset_get_varg_value_auxiliary__user_define
    {
        int n_elem;
    }_test__hash_multiset_get_varg_value_auxiliary__user_define_t;

    hash_multiset_t* phset_set = NULL;
    _test__hash_multiset_get_varg_value_auxiliary__user_define_t t_use;
    _test__hash_multiset_get_varg_value_auxiliary__user_define_t t_varg;

    type_register(_test__hash_multiset_get_varg_value_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    phset_set = create_hash_multiset(_test__hash_multiset_get_varg_value_auxiliary__user_define_t);
    hash_multiset_init(phset_set);
    t_use.n_elem = 10000;

    _wrapper_hash_multiset_get_varg_value_auxiliary(phset_set, &t_varg, &t_use);
    assert_true(t_varg.n_elem == t_use.n_elem);

    hash_multiset_destroy(phset_set);
}

/*
 * test _hash_multiset_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_hash_multiset_destroy_varg_value_auxiliary)
void test__hash_multiset_destroy_varg_value_auxiliary__null_hash_multiset_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_hash_multiset_destroy_varg_value_auxiliary(NULL, &varg));
}

void test__hash_multiset_destroy_varg_value_auxiliary__null_varg(void** state)
{
    hash_multiset_t* phset_set = create_hash_multiset(int);
    hash_multiset_init(phset_set);
    expect_assert_failure(_hash_multiset_destroy_varg_value_auxiliary(phset_set, NULL));
    hash_multiset_destroy(phset_set);
}

/*
void test__hash_multiset_destroy_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    hash_multiset_t deq;
    deq._t_mapsize = 3;
    expect_assert_failure(_hash_multiset_destroy_varg_value_auxiliary(&deq, &varg));
}
*/

void test__hash_multiset_destroy_varg_value_auxiliary__successfully(void** state)
{
    int varg = 100;
    hash_multiset_t* phset_set = create_hash_multiset(int);
    hash_multiset_init(phset_set);
    _hash_multiset_destroy_varg_value_auxiliary(phset_set, &varg);
    hash_multiset_destroy(phset_set);
}

