#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl_multiset_aux.h"

#include "ut_def.h"
#include "ut_cstl_multiset_aux.h"

UT_SUIT_DEFINATION(cstl_multiset_aux, _multiset_get_varg_value_auxiliary)

/*
 * test _multiset_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_multiset_get_varg_value_auxiliary)
static void _wrapper_multiset_get_varg_value_auxiliary(multiset_t* pmset_mset, void* pv_varg, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pv_varg);
    _multiset_get_varg_value_auxiliary(pmset_mset, val_elemlist, pv_varg);
    va_end(val_elemlist);
}

void test__multiset_get_varg_value_auxiliary__null_multiset_container(void** state)
{
    int n_elem;
    expect_assert_failure(_wrapper_multiset_get_varg_value_auxiliary(NULL, &n_elem, 100));
}

void test__multiset_get_varg_value_auxiliary__null_node(void** state)
{
    multiset_t* pmultiset = create_multiset(int);

    expect_assert_failure(_wrapper_multiset_get_varg_value_auxiliary(pmultiset, NULL, 100));

    multiset_destroy(pmultiset);
}

/*
void test__multiset_get_varg_value_auxiliary__non_created_multiset_containter(void** state)
{
    int node;
    multiset_t multiset;

    expect_assert_failure(_wrapper_multiset_get_varg_value_auxiliary(&multiset, &node, 100));
}
*/

void test__multiset_get_varg_value_auxiliary__c_builtin(void** state)
{
    int n_elem = 0;
    multiset_t* pmultiset = create_multiset(int);
    multiset_init(pmultiset);

    _wrapper_multiset_get_varg_value_auxiliary(pmultiset, &n_elem, 100);
    assert_true(n_elem == 100);

    multiset_destroy(pmultiset);
}

void test__multiset_get_varg_value_auxiliary__cstr(void** state)
{
    multiset_t* pmultiset = create_multiset(char*);
    string_t* pstr = NULL;
    multiset_init(pmultiset);
    pstr = create_string();

    _wrapper_multiset_get_varg_value_auxiliary(pmultiset, pstr, "abcdefg");
    assert_true(strcmp(string_c_str(pstr), "abcdefg") == 0);

    string_destroy(pstr);
    multiset_destroy(pmultiset);
}

void test__multiset_get_varg_value_auxiliary__libcstl_builtin(void** state)
{
    multiset_t* pmultiset = create_multiset(vector_t<int>);
    vector_t* pvec = create_vector(int);
    vector_t* pvec_varg = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    multiset_init(pmultiset);

    _wrapper_multiset_get_varg_value_auxiliary(pmultiset, pvec_varg, pvec);
    assert_true(vector_equal(pvec_varg, pvec));

    vector_destroy(pvec_varg);
    multiset_destroy(pmultiset);
    vector_destroy(pvec);
}

void test__multiset_get_varg_value_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__multiset_get_varg_value_auxiliary__user_define
    {
        int n_elem;
    }_test__multiset_get_varg_value_auxiliary__user_define_t;

    multiset_t* pmultiset = NULL;
    _test__multiset_get_varg_value_auxiliary__user_define_t t_use;
    _test__multiset_get_varg_value_auxiliary__user_define_t t_varg;

    type_register(_test__multiset_get_varg_value_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pmultiset = create_multiset(_test__multiset_get_varg_value_auxiliary__user_define_t);
    multiset_init(pmultiset);
    t_use.n_elem = 10000;

    _wrapper_multiset_get_varg_value_auxiliary(pmultiset, &t_varg, &t_use);
    assert_true(t_varg.n_elem == t_use.n_elem);

    multiset_destroy(pmultiset);
}

/*
 * test _multiset_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_multiset_destroy_varg_value_auxiliary)
void test__multiset_destroy_varg_value_auxiliary__null_multiset_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_multiset_destroy_varg_value_auxiliary(NULL, &varg));
}

void test__multiset_destroy_varg_value_auxiliary__null_varg(void** state)
{
    multiset_t* pmultiset = create_multiset(int);
    multiset_init(pmultiset);
    expect_assert_failure(_multiset_destroy_varg_value_auxiliary(pmultiset, NULL));
    multiset_destroy(pmultiset);
}

/*
void test__multiset_destroy_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    multiset_t deq;
    deq._t_mapsize = 3;
    expect_assert_failure(_multiset_destroy_varg_value_auxiliary(&deq, &varg));
}
*/

void test__multiset_destroy_varg_value_auxiliary__successfully(void** state)
{
    int varg = 100;
    multiset_t* pmultiset = create_multiset(int);
    multiset_init(pmultiset);
    _multiset_destroy_varg_value_auxiliary(pmultiset, &varg);
    multiset_destroy(pmultiset);
}

