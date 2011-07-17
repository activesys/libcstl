#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cset.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl_vector_aux.h"
#include "cstl_multiset_aux.h"

#include "ut_def.h"
#include "ut_cstl_multiset_private.h"

UT_SUIT_DEFINATION(cstl_multiset_private, _create_multiset)

/*
 * test _create_multiset
 */
UT_CASE_DEFINATION(_create_multiset)
void test__create_multiset__null_typename(void** state)
{
    expect_assert_failure(_create_multiset(NULL));
}

void test__create_multiset__c_builtin(void** state)
{
    multiset_t* pt_multiset = _create_multiset("double");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset__cstr(void** state)
{
    multiset_t* pt_multiset = _create_multiset("char*");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset__libcstl_builtin(void** state)
{
    multiset_t* pt_multiset = _create_multiset("vector_t<int>");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

typedef struct _test_test__create_multiset__user_define
{
    int n_elem;
}_test__create_multiset__user_define_t;

void test__create_multiset__user_define(void** state)
{
    multiset_t* pt_multiset = NULL;

    type_register(_test__create_multiset__user_define_t, NULL, NULL, NULL, NULL);
    pt_multiset = _create_multiset("_test__create_multiset__user_define_t");
    assert_true(pt_multiset != NULL);

    multiset_destroy(pt_multiset);
}

void test__create_multiset__unregister(void** state)
{
    multiset_t* pt_multiset = _create_multiset("test__create_multiset__unregister_t");
    assert_true(pt_multiset == NULL);
}

