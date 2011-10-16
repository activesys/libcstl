#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl_set_aux.h"

#include "ut_def.h"
#include "ut_cstl_set_aux.h"

UT_SUIT_DEFINATION(cstl_set_aux, _set_get_varg_value_auxiliary)

/*
 * test _set_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_set_get_varg_value_auxiliary)
static void _wrapper_set_get_varg_value_auxiliary(set_t* pset_set, void* pv_varg, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pv_varg);
    _set_get_varg_value_auxiliary(pset_set, val_elemlist, pv_varg);
    va_end(val_elemlist);
}

void test__set_get_varg_value_auxiliary__null_set_container(void** state)
{
    int n_elem;
    expect_assert_failure(_wrapper_set_get_varg_value_auxiliary(NULL, &n_elem, 100));
}

void test__set_get_varg_value_auxiliary__null_node(void** state)
{
    set_t* pset = create_set(int);

    expect_assert_failure(_wrapper_set_get_varg_value_auxiliary(pset, NULL, 100));

    set_destroy(pset);
}

/*
void test__set_get_varg_value_auxiliary__non_created_set_containter(void** state)
{
    int node;
    set_t set;

    expect_assert_failure(_wrapper_set_get_varg_value_auxiliary(&set, &node, 100));
}
*/

void test__set_get_varg_value_auxiliary__c_builtin(void** state)
{
    int n_elem = 0;
    set_t* pset = create_set(int);
    set_init(pset);

    _wrapper_set_get_varg_value_auxiliary(pset, &n_elem, 100);
    assert_true(n_elem == 100);

    set_destroy(pset);
}

void test__set_get_varg_value_auxiliary__cstr(void** state)
{
    set_t* pset = create_set(char*);
    string_t* pstr = NULL;
    set_init(pset);
    pstr = create_string();

    _wrapper_set_get_varg_value_auxiliary(pset, pstr, "abcdefg");
    assert_true(strcmp(string_c_str(pstr), "abcdefg") == 0);

    string_destroy(pstr);
    set_destroy(pset);
}

void test__set_get_varg_value_auxiliary__libcstl_builtin(void** state)
{
    set_t* pset = create_set(vector_t<int>);
    vector_t* pvec = create_vector(int);
    vector_t* pvec_varg = create_vector(int);
    vector_init_elem(pvec, 10, 100);
    set_init(pset);

    _wrapper_set_get_varg_value_auxiliary(pset, pvec_varg, pvec);
    assert_true(vector_equal(pvec_varg, pvec));

    vector_destroy(pvec_varg);
    set_destroy(pset);
    vector_destroy(pvec);
}

void test__set_get_varg_value_auxiliary__user_define(void** state)
{
    typedef struct _tag_test__set_get_varg_value_auxiliary__user_define
    {
        int n_elem;
    }_test__set_get_varg_value_auxiliary__user_define_t;

    set_t* pset = NULL;
    _test__set_get_varg_value_auxiliary__user_define_t t_use;
    _test__set_get_varg_value_auxiliary__user_define_t t_varg;

    type_register(_test__set_get_varg_value_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    pset = create_set(_test__set_get_varg_value_auxiliary__user_define_t);
    set_init(pset);
    t_use.n_elem = 10000;

    _wrapper_set_get_varg_value_auxiliary(pset, &t_varg, &t_use);
    assert_true(t_varg.n_elem == t_use.n_elem);

    set_destroy(pset);
}

/*
 * test _set_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_set_destroy_varg_value_auxiliary)
void test__set_destroy_varg_value_auxiliary__null_set_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_set_destroy_varg_value_auxiliary(NULL, &varg));
}

void test__set_destroy_varg_value_auxiliary__null_varg(void** state)
{
    set_t* pset = create_set(int);
    set_init(pset);
    expect_assert_failure(_set_destroy_varg_value_auxiliary(pset, NULL));
    set_destroy(pset);
}

/*
void test__set_destroy_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    set_t deq;
    deq._t_mapsize = 3;
    expect_assert_failure(_set_destroy_varg_value_auxiliary(&deq, &varg));
}
*/

void test__set_destroy_varg_value_auxiliary__successfully(void** state)
{
    int varg = 100;
    set_t* pset = create_set(int);
    set_init(pset);
    _set_destroy_varg_value_auxiliary(pset, &varg);
    set_destroy(pset);
}

