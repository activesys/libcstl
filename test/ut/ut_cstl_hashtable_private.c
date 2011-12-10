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

#include "ut_def.h"
#include "ut_cstl_hashtable_private.h"

UT_SUIT_DEFINATION(cstl_hashtable_private, _create_hashtable_auxiliary)
/*
 * test _create_hashtable_auxiliary
 */
UT_CASE_DEFINATION(_create_hashtable_auxiliary)
void test__create_hashtable_auxiliary__null_hashtable(void** state)
{
    expect_assert_failure(_create_hashtable_auxiliary(NULL, "int"));
}

void test__create_hashtable_auxiliary__null_typename(void** state)
{
    _hashtable_t htable;
    expect_assert_failure(_create_hashtable_auxiliary(&htable, NULL));
}

void test__create_hashtable_auxiliary__unregistered(void** state)
{
    _hashtable_t* pt_hashtable = malloc(sizeof(_hashtable_t));
    assert_false(_create_hashtable_auxiliary(pt_hashtable, "_test__create_hashtable_auxiliary__unregistered_t"));

    free(pt_hashtable);
}

void test__create_hashtable_auxiliary__c_builtin(void** state)
{
    _hashtable_t* pt_hashtable = malloc(sizeof(_hashtable_t));
    assert_true(_create_hashtable_auxiliary(pt_hashtable, "int"));
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__create_hashtable_auxiliary__cstr(void** state)
{
    _hashtable_t* pt_hashtable = malloc(sizeof(_hashtable_t));
    assert_true(_create_hashtable_auxiliary(pt_hashtable, "char*"));
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

void test__create_hashtable_auxiliary__libcstl_builtin(void** state)
{
    _hashtable_t* pt_hashtable = malloc(sizeof(_hashtable_t));
    assert_true(_create_hashtable_auxiliary(pt_hashtable, "vector_t<int>"));
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

typedef struct _tag_test__create_hashtable_auxiliary__user_define
{
    int n_elem;
}_test__create_hashtable_auxiliary__user_define_t;

void test__create_hashtable_auxiliary__user_define(void** state)
{
    _hashtable_t* pt_hashtable = NULL;

    type_register(_test__create_hashtable_auxiliary__user_define_t, NULL, NULL, NULL, NULL);

    pt_hashtable = malloc(sizeof(_hashtable_t));
    assert_true(_create_hashtable_auxiliary(pt_hashtable, "_test__create_hashtable_auxiliary__user_define_t"));
    assert_true(_hashtable_is_created(pt_hashtable));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_destroy_auxiliary
 */
UT_CASE_DEFINATION(_hashtable_destroy_auxiliary)
void test__hashtable_destroy_auxiliary__null_hashtable(void** state)
{
    expect_assert_failure(_hashtable_destroy_auxiliary(NULL));
}

void test__hashtable_destroy_auxiliary__non_created(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");

    pt_hashtable->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_destroy_auxiliary(pt_hashtable));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_destroy_auxiliary__non_inited(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    pt_hashtable->_t_typeinfo._t_style = 999;
    expect_assert_failure(_hashtable_destroy_auxiliary(pt_hashtable));
    pt_hashtable->_t_typeinfo._t_style = _TYPE_C_BUILTIN;

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_destroy_auxiliary__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_destroy_auxiliary(pt_hashtable);
    assert_true(pt_hashtable->_t_nodecount == 0);
    assert_true(pt_hashtable->_bfun_compare == NULL);
    assert_true(pt_hashtable->_ufun_hash == NULL);
    free(pt_hashtable);
}

void test__hashtable_destroy_auxiliary__non_empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    int elem = 9;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    _hashtable_destroy_auxiliary(pt_hashtable);
    assert_true(pt_hashtable->_t_nodecount == 0);
    assert_true(pt_hashtable->_bfun_compare == NULL);
    assert_true(pt_hashtable->_ufun_hash == NULL);
    free(pt_hashtable);
}

