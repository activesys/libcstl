#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cqueue.h"
#include "cstl/calgorithm.h"
#include "cstl/cfunctional.h"

#include "ut_def.h"
#include "ut_cstl_priority_queue_private.h"

UT_SUIT_DEFINATION(cstl_priority_queue_private, _create_priority_queue)

/*
 * test _create_priority_queue
 */
UT_CASE_DEFINATION(_create_priority_queue)
void test__create_priority_queue__null_typename(void** state)
{
    expect_assert_failure(_create_priority_queue(NULL));
}

void test__create_priority_queue__unregisted_type(void** state)
{
    assert_true(_create_priority_queue("_test__create_priority_queue__unregisted_type_t") == NULL);
}

void test__create_priority_queue__c_builtin_type(void** state)
{
    priority_queue_t* ppque = _create_priority_queue("unsigned int");
    assert_true(ppque != NULL);

    priority_queue_destroy(ppque);
}

void test__create_priority_queue__libcstl_builtin_type(void** state)
{
    priority_queue_t* ppque = _create_priority_queue("vector_t         <      int>     ");
    assert_true(ppque != NULL);

    priority_queue_destroy(ppque);
}

typedef struct _tag_test__create_priority_queue__user_defined_type
{
    int n_elem;
}_test__create_priority_queue__user_defined_type_t;

void test__create_priority_queue__user_defined_type(void** state)
{
    priority_queue_t* ppque = NULL;

    type_register(struct _tag_test__create_priority_queue__user_defined_type, NULL, NULL, NULL, NULL);
    ppque = _create_priority_queue("struct      _tag_test__create_priority_queue__user_defined_type");
    assert_true(ppque != NULL);

    priority_queue_destroy(ppque);
}

/*
 * test _create_priority_queue_auxiliary
 */
UT_CASE_DEFINATION(_create_priority_queue_auxiliary)
void test__create_priority_queue_auxiliary__null_priority_queue_adaptor(void** state)
{
    expect_assert_failure(_create_priority_queue_auxiliary(NULL, "int"));
}

void test__create_priority_queue_auxiliary__null_typename(void** state)
{
    priority_queue_t* pque = malloc(sizeof(priority_queue_t));
    expect_assert_failure(_create_priority_queue_auxiliary(pque, NULL));

    free(pque);
}

void test__create_priority_queue_auxiliary__unregisted_type(void** state)
{
    priority_queue_t* pque = malloc(sizeof(priority_queue_t));
    assert_false(_create_priority_queue_auxiliary(pque, "_test__create_priority_queue_auxiliary__unregisted_type_t"));

    free(pque);
}

void test__create_priority_queue_auxiliary__c_builtin(void** state)
{
    priority_queue_t* pque = malloc(sizeof(priority_queue_t));
    assert_true(_create_priority_queue_auxiliary(pque, "double"));

    priority_queue_destroy(pque);
}

void test__create_priority_queue_auxiliary__libcstl_builtin(void** state)
{
    priority_queue_t* pque = malloc(sizeof(priority_queue_t));
    assert_true(_create_priority_queue_auxiliary(pque, "priority_queue_t<   vector_t     <     string_t>>       "));

    priority_queue_destroy(pque);
}

typedef struct _tag_test__create_priority_queue_auxiliary__user_defined
{
    int n_elem;
}_test__create_priority_queue_auxiliary__user_defined_t;
void test__create_priority_queue_auxiliary__user_defined(void** state)
{
    priority_queue_t* pque = NULL;
    type_register(struct _tag_test__create_priority_queue_auxiliary__user_defined, NULL, NULL, NULL, NULL);
    pque = malloc(sizeof(priority_queue_t));
    assert_true(_create_priority_queue_auxiliary(pque, "struct _tag_test__create_priority_queue_auxiliary__user_defined"));

    priority_queue_destroy(pque);
}

void test__create_priority_queue_auxiliary__user_defined_dup(void** state)
{
    priority_queue_t* pque = NULL;
    type_duplicate(struct _tag_test__create_priority_queue_auxiliary__user_defined, _test__create_priority_queue_auxiliary__user_defined_t);
    pque = malloc(sizeof(priority_queue_t));
    assert_true(_create_priority_queue_auxiliary(pque, "_test__create_priority_queue_auxiliary__user_defined_t"));

    priority_queue_destroy(pque);
}

/*
 * test _priority_queue_destroy_auxiliary
 */
UT_CASE_DEFINATION(_priority_queue_destroy_auxiliary)
void test__priority_queue_destroy_auxiliary__null_priority_queue_adaptor(void** state)
{
    expect_assert_failure(_priority_queue_destroy_auxiliary(NULL));
}

void test__priority_queue_destroy_auxiliary__non_created_priority_queue_adaptor(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);

    priority_queue_init(pque);
    pque->_vec_base._t_typeinfo._t_style = 9484;
    expect_assert_failure(_priority_queue_destroy_auxiliary(pque));

    pque->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    priority_queue_destroy(pque);
}

void test__priority_queue_destroy_auxiliary__non_inited(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);
    _priority_queue_destroy_auxiliary(pque);

    free(pque);
}

void test__priority_queue_destroy_auxiliary__empty(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);

    priority_queue_init(pque);
    _priority_queue_destroy_auxiliary(pque);

    free(pque);
}

void test__priority_queue_destroy_auxiliary__non_empty(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);

    priority_queue_init(pque);
    priority_queue_push(pque, 100);
    priority_queue_push(pque, 300);
    _priority_queue_destroy_auxiliary(pque);

    free(pque);
}

/*
 * test _priority_queue_push
 */
UT_CASE_DEFINATION(_priority_queue_push)
void test__priority_queue_push__null_priority_queue_adaptor(void** state)
{
    expect_assert_failure(_priority_queue_push(NULL, 100));
}

void test__priority_queue_push__non_inited_priority_queue_adaptor(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);

    pque->_vec_base._t_typeinfo._t_style = 4444;
    expect_assert_failure(_priority_queue_push(pque, 100));

    pque->_vec_base._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    priority_queue_destroy(pque);
}

void test__priority_queue_push__empty(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);

    priority_queue_init(pque);
    _priority_queue_push(pque, 100);
    assert_true(priority_queue_size(pque) == 1);
    assert_true(*(int*)priority_queue_top(pque) == 100);
    assert_true(algo_is_heap(vector_begin(&pque->_vec_base), vector_end(&pque->_vec_base)));

    priority_queue_destroy(pque);
}

void test__priority_queue_push__non_empty(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);
    size_t t_oldsize = 0;

    priority_queue_init(pque);
    _priority_queue_push(pque, 400);
    _priority_queue_push(pque, 600);
    t_oldsize = priority_queue_size(pque);
    _priority_queue_push(pque, 1000);
    assert_true(priority_queue_size(pque) == t_oldsize + 1);
    assert_true(*(int*)priority_queue_top(pque) == 1000);
    assert_true(algo_is_heap(vector_begin(&pque->_vec_base), vector_end(&pque->_vec_base)));

    priority_queue_destroy(pque);
}

void test__priority_queue_push__non_empty_multiple(void** state)
{
    priority_queue_t* pque = create_priority_queue(int);
    size_t t_oldsize = 0;

    priority_queue_init_ex(pque, fun_greater_int);
    _priority_queue_push(pque, 400);
    _priority_queue_push(pque, 600);
    t_oldsize = priority_queue_size(pque);
    _priority_queue_push(pque, 100);
    assert_true(priority_queue_size(pque) == t_oldsize + 1);
    assert_true(*(int*)priority_queue_top(pque) == 100);
    assert_true(algo_is_heap_if(vector_begin(&pque->_vec_base), vector_end(&pque->_vec_base), fun_greater_int));

    priority_queue_destroy(pque);
}

