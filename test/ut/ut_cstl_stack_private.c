#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstack.h"

#include "ut_def.h"
#include "ut_cstl_stack_private.h"

UT_SUIT_DEFINATION(cstl_stack_private, _create_stack)

/*
 * test _create_stack
 */
UT_CASE_DEFINATION(_create_stack)
void test__create_stack__null_typename(void** state)
{
    expect_assert_failure(_create_stack(NULL));
}

void test__create_stack__unregisted_type(void** state)
{
    assert_true(_create_stack("_test__create_stack__unregisted_type_t") == NULL);
}

void test__create_stack__c_builtin_type(void** state)
{
    stack_t* psk = _create_stack("unsigned int");
    assert_true(psk != NULL);

    stack_destroy(psk);
}

void test__create_stack__libcstl_builtin_type(void** state)
{
    stack_t* psk = _create_stack("vector_t         <      int>     ");
    assert_true(psk != NULL);

    stack_destroy(psk);
}

typedef struct _tag_test__create_stack__user_defined_type
{
    int n_elem;
}_test__create_stack__user_defined_type_t;

void test__create_stack__user_defined_type(void** state)
{
    stack_t* psk = NULL;

    type_register(struct _tag_test__create_stack__user_defined_type, NULL, NULL, NULL, NULL);
    psk = _create_stack("struct      _tag_test__create_stack__user_defined_type");
    assert_true(psk != NULL);

    stack_destroy(psk);
}

void test__create_stack__user_defined_type_dup(void** state)
{
    stack_t* psk = NULL;

    type_duplicate(struct _tag_test__create_stack__user_defined_type, _test__create_stack__user_defined_type_t);
    psk = _create_stack("_test__create_stack__user_defined_type_t");
    assert_true(psk != NULL);

    stack_destroy(psk);
}

/*
 * test _create_stack_auxiliary
 */
UT_CASE_DEFINATION(_create_stack_auxiliary)
void test__create_stack_auxiliary__null_stack_adaptor(void** state)
{
    expect_assert_failure(_create_stack_auxiliary(NULL, "int"));
}

void test__create_stack_auxiliary__null_typename(void** state)
{
    stack_t* psk = malloc(sizeof(stack_t));
    expect_assert_failure(_create_stack_auxiliary(psk, NULL));

    free(psk);
}

void test__create_stack_auxiliary__unregisted_type(void** state)
{
    stack_t* psk = malloc(sizeof(stack_t));
    assert_false(_create_stack_auxiliary(psk, "_test__create_stack_auxiliary__unregisted_type_t"));

    free(psk);
}

void test__create_stack_auxiliary__c_builtin(void** state)
{
    stack_t* psk = malloc(sizeof(stack_t));
    assert_true(_create_stack_auxiliary(psk, "double"));

    stack_destroy(psk);
}

void test__create_stack_auxiliary__libcstl_builtin(void** state)
{
    stack_t* psk = malloc(sizeof(stack_t));
    assert_true(_create_stack_auxiliary(psk, "stack_t<   vector_t     <     string_t>>       "));

    stack_destroy(psk);
}

typedef struct _tag_test__create_stack_auxiliary__user_defined
{
    int n_elem;
}_test__create_stack_auxiliary__user_defined_t;
void test__create_stack_auxiliary__user_defined(void** state)
{
    stack_t* psk = NULL;
    type_register(struct _tag_test__create_stack_auxiliary__user_defined, NULL, NULL, NULL, NULL);
    psk = malloc(sizeof(stack_t));
    assert_true(_create_stack_auxiliary(psk, "struct _tag_test__create_stack_auxiliary__user_defined"));

    stack_destroy(psk);
}

void test__create_stack_auxiliary__user_defined_dup(void** state)
{
    stack_t* psk = NULL;
    type_duplicate(struct _tag_test__create_stack_auxiliary__user_defined, _test__create_stack_auxiliary__user_defined_t);
    psk = malloc(sizeof(stack_t));
    assert_true(_create_stack_auxiliary(psk, "_test__create_stack_auxiliary__user_defined_t"));

    stack_destroy(psk);
}

/*
 * test _stack_destroy_auxiliary
 */
UT_CASE_DEFINATION(_stack_destroy_auxiliary)
void test__stack_destroy_auxiliary__null_stack_adaptor(void** state)
{
    expect_assert_failure(_stack_destroy_auxiliary(NULL));
}

void test__stack_destroy_auxiliary__non_created_stack_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    psk->_t_sequence._t_typeinfo._t_style = 9484;
    expect_assert_failure(_stack_destroy_auxiliary(psk));

    psk->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk);
}

void test__stack_destroy_auxiliary__non_inited(void** state)
{
    stack_t* psk = create_stack(int);
    _stack_destroy_auxiliary(psk);

    free(psk);
}

void test__stack_destroy_auxiliary__empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    _stack_destroy_auxiliary(psk);

    free(psk);
}

void test__stack_destroy_auxiliary__non_empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    stack_push(psk, 100);
    stack_push(psk, 300);
    _stack_destroy_auxiliary(psk);

    free(psk);
}

/*
 * test _stack_push and _stack_push_varg
 */
UT_CASE_DEFINATION(_stack_push__stack_push_varg)
void test__stack_push__stack_push_varg__null_stack_adaptor(void** state)
{
    expect_assert_failure(_stack_push(NULL, 100));
}

void test__stack_push__stack_push_varg__non_inited_stack_adaptor(void** state)
{
    stack_t* psk = create_stack(int);

    psk->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(_stack_push(psk, 100));

    psk->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    stack_destroy(psk);
}

void test__stack_push__stack_push_varg__empty(void** state)
{
    stack_t* psk = create_stack(int);

    stack_init(psk);
    _stack_push(psk, 100);
    assert_true(stack_size(psk) == 1);
    assert_true(*(int*)stack_top(psk) == 100);

    stack_destroy(psk);
}

void test__stack_push__stack_push_varg__non_empty(void** state)
{
    stack_t* psk = create_stack(int);
    size_t t_oldsize = 0;

    stack_init(psk);
    _stack_push(psk, 400);
    _stack_push(psk, 600);
    t_oldsize = stack_size(psk);
    _stack_push(psk, 100);
    assert_true(stack_size(psk) == t_oldsize + 1);
    assert_true(*(int*)stack_top(psk) == 100);

    stack_destroy(psk);
}

void test__stack_push__stack_push_varg__non_empty_multiple(void** state)
{
    stack_t* psk = create_stack(int);
    size_t t_oldsize = 0;

    stack_init(psk);
    _stack_push(psk, 400);
    _stack_push(psk, 600);
    t_oldsize = stack_size(psk);
    _stack_push(psk, 100, 98, 23523, 2222);
    assert_true(stack_size(psk) == t_oldsize + 1);
    assert_true(*(int*)stack_top(psk) == 100);

    stack_destroy(psk);
}

