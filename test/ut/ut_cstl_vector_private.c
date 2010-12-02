#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_vector_private.h"

UT_SUIT_DEFINATION(cstl_vector_private, _create_vector)

/*
 * test _create_vector
 */
UT_CASE_DEFINATION(_create_vector)

void test__create_vector__null_typename(void** state)
{
    expect_assert_failure(_create_vector(NULL));
}

void test__create_vector__unregisted_type(void** state)
{
    assert_true(_create_vector("unregisted_type_t") == NULL);
}

void test__create_vector__c_builtin_type(void** state)
{
    vector_t* pvec = _create_vector("unsigned int");
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__create_vector__libcstl_builtin_type(void** state)
{
    vector_t* pvec = _create_vector("list_t<int>");
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__create_vector__registed_type(void** state)
{
    typedef struct _tagabc{int n_elem;}abc_t;
    vector_t* pvec = NULL;
    type_register(abc_t, NULL, NULL, NULL, NULL);
    pvec = _create_vector("abc_t");
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

