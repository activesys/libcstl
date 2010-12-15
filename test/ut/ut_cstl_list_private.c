#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_list_iterator.h"
#include "cstl/clist.h"
#include "cstl_list_aux.h"
#include "cstl/cvector.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_list_private.h"

UT_SUIT_DEFINATION(cstl_list_private, test__create_list__null_typename)

/*
 * test _create_list
 */
UT_CASE_DEFINATION(_create_list)
void test__create_list__null_typename(void** state)
{
    expect_assert_failure(_create_list(NULL));
}

void test__create_list__unregisted_type(void** state)
{
    assert_true(_create_list("_test__create_list__unregisted_type_t") == NULL);
}

void test__create_list__c_builtin_type(void** state)
{
    list_t* plist = _create_list("unsigned int");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "unsigned int") == 0);

    list_destroy(plist);
}

void test__create_list__libcstl_builtin_type(void** state)
{
    list_t* plist = _create_list("vector_t         <      int>     ");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "vector_t<int>") == 0);

    list_destroy(plist);
}

typedef struct _tag_test__create_list__user_defined_type
{
    int n_elem;
}_test__create_list__user_defined_type_t;

void test__create_list__user_defined_type(void** state)
{
    list_t* plist = NULL;

    type_register(struct _tag_test__create_list__user_defined_type, NULL, NULL, NULL, NULL);
    plist = _create_list("struct      _tag_test__create_list__user_defined_type");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "struct _tag_test__create_list__user_defined_type") == 0);

    list_destroy(plist);
}

void test__create_list__user_defined_type_dup(void** state)
{
    list_t* plist = NULL;

    type_duplicate(struct _tag_test__create_list__user_defined_type, _test__create_list__user_defined_type_t);
    plist = _create_list("_test__create_list__user_defined_type_t");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "_test__create_list__user_defined_type_t") == 0);

    list_destroy(plist);
}

