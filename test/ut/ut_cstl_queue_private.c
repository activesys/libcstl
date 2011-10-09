#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cqueue.h"

#include "ut_def.h"
#include "ut_cstl_queue_private.h"

UT_SUIT_DEFINATION(cstl_queue_private, _create_queue)

/*
 * test _create_queue
 */
UT_CASE_DEFINATION(_create_queue)
void test__create_queue__null_typename(void** state)
{
    expect_assert_failure(_create_queue(NULL));
}

void test__create_queue__unregisted_type(void** state)
{
    assert_true(_create_queue("_test__create_queue__unregisted_type_t") == NULL);
}

void test__create_queue__c_builtin_type(void** state)
{
    queue_t* pque = _create_queue("unsigned int");
    assert_true(pque != NULL);

    queue_destroy(pque);
}

void test__create_queue__libcstl_builtin_type(void** state)
{
    queue_t* pque = _create_queue("vector_t         <      int>     ");
    assert_true(pque != NULL);

    queue_destroy(pque);
}

typedef struct _tag_test__create_queue__user_defined_type
{
    int n_elem;
}_test__create_queue__user_defined_type_t;

void test__create_queue__user_defined_type(void** state)
{
    queue_t* pque = NULL;

    type_register(struct _tag_test__create_queue__user_defined_type, NULL, NULL, NULL, NULL);
    pque = _create_queue("struct      _tag_test__create_queue__user_defined_type");
    assert_true(pque != NULL);

    queue_destroy(pque);
}

void test__create_queue__user_defined_type_dup(void** state)
{
    queue_t* pque = NULL;

    type_duplicate(struct _tag_test__create_queue__user_defined_type, _test__create_queue__user_defined_type_t);
    pque = _create_queue("_test__create_queue__user_defined_type_t");
    assert_true(pque != NULL);

    queue_destroy(pque);
}

/*
 * test _create_queue_auxiliary
 */
UT_CASE_DEFINATION(_create_queue_auxiliary)
void test__create_queue_auxiliary__null_queue_adaptor(void** state)
{
    expect_assert_failure(_create_queue_auxiliary(NULL, "int"));
}

void test__create_queue_auxiliary__null_typename(void** state)
{
    queue_t* pque = malloc(sizeof(queue_t));
    expect_assert_failure(_create_queue_auxiliary(pque, NULL));

    free(pque);
}

void test__create_queue_auxiliary__unregisted_type(void** state)
{
    queue_t* pque = malloc(sizeof(queue_t));
    assert_false(_create_queue_auxiliary(pque, "_test__create_queue_auxiliary__unregisted_type_t"));

    free(pque);
}

void test__create_queue_auxiliary__c_builtin(void** state)
{
    queue_t* pque = malloc(sizeof(queue_t));
    assert_true(_create_queue_auxiliary(pque, "double"));

    queue_destroy(pque);
}

void test__create_queue_auxiliary__libcstl_builtin(void** state)
{
    queue_t* pque = malloc(sizeof(queue_t));
    assert_true(_create_queue_auxiliary(pque, "queue_t<   vector_t     <     string_t>>       "));

    queue_destroy(pque);
}

typedef struct _tag_test__create_queue_auxiliary__user_defined
{
    int n_elem;
}_test__create_queue_auxiliary__user_defined_t;
void test__create_queue_auxiliary__user_defined(void** state)
{
    queue_t* pque = NULL;
    type_register(struct _tag_test__create_queue_auxiliary__user_defined, NULL, NULL, NULL, NULL);
    pque = malloc(sizeof(queue_t));
    assert_true(_create_queue_auxiliary(pque, "struct _tag_test__create_queue_auxiliary__user_defined"));

    queue_destroy(pque);
}

void test__create_queue_auxiliary__user_defined_dup(void** state)
{
    queue_t* pque = NULL;
    type_duplicate(struct _tag_test__create_queue_auxiliary__user_defined, _test__create_queue_auxiliary__user_defined_t);
    pque = malloc(sizeof(queue_t));
    assert_true(_create_queue_auxiliary(pque, "_test__create_queue_auxiliary__user_defined_t"));

    queue_destroy(pque);
}

/*
 * test _queue_destroy_auxiliary
 */
UT_CASE_DEFINATION(_queue_destroy_auxiliary)
void test__queue_destroy_auxiliary__null_queue_adaptor(void** state)
{
    expect_assert_failure(_queue_destroy_auxiliary(NULL));
}

void test__queue_destroy_auxiliary__non_created_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    pque->_t_sequence._t_typeinfo._t_style = 9484;
    expect_assert_failure(_queue_destroy_auxiliary(pque));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test__queue_destroy_auxiliary__non_inited(void** state)
{
    queue_t* pque = create_queue(int);
    _queue_destroy_auxiliary(pque);

    free(pque);
}

void test__queue_destroy_auxiliary__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    _queue_destroy_auxiliary(pque);

    free(pque);
}

void test__queue_destroy_auxiliary__non_empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    queue_push(pque, 100);
    queue_push(pque, 300);
    _queue_destroy_auxiliary(pque);

    free(pque);
}

/*
 * test _queue_push and _queue_push_varg
 */
UT_CASE_DEFINATION(_queue_push__queue_push_varg)
void test__queue_push__queue_push_varg__null_queue_adaptor(void** state)
{
    expect_assert_failure(_queue_push(NULL, 100));
}

void test__queue_push__queue_push_varg__non_inited_queue_adaptor(void** state)
{
    queue_t* pque = create_queue(int);

    pque->_t_sequence._t_typeinfo._t_style = 4444;
    expect_assert_failure(_queue_push(pque, 100));

    pque->_t_sequence._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    queue_destroy(pque);
}

void test__queue_push__queue_push_varg__empty(void** state)
{
    queue_t* pque = create_queue(int);

    queue_init(pque);
    _queue_push(pque, 100);
    assert_true(queue_size(pque) == 1);
    assert_true(*(int*)queue_back(pque) == 100);

    queue_destroy(pque);
}

void test__queue_push__queue_push_varg__non_empty(void** state)
{
    queue_t* pque = create_queue(int);
    size_t t_oldsize = 0;

    queue_init(pque);
    _queue_push(pque, 400);
    _queue_push(pque, 600);
    t_oldsize = queue_size(pque);
    _queue_push(pque, 100);
    assert_true(queue_size(pque) == t_oldsize + 1);
    assert_true(*(int*)queue_back(pque) == 100);

    queue_destroy(pque);
}

void test__queue_push__queue_push_varg__non_empty_multiple(void** state)
{
    queue_t* pque = create_queue(int);
    size_t t_oldsize = 0;

    queue_init(pque);
    _queue_push(pque, 400);
    _queue_push(pque, 600);
    t_oldsize = queue_size(pque);
    _queue_push(pque, 100, 98, 23523, 2222);
    assert_true(queue_size(pque) == t_oldsize + 1);
    assert_true(*(int*)queue_back(pque) == 100);

    queue_destroy(pque);
}

