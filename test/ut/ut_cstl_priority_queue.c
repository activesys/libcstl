#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cqueue.h"
#include "cstl/calgorithm.h"
#include "cstl/cfunctional.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_priority_queue.h"

UT_SUIT_DEFINATION(cstl_priority_queue, priority_queue_init)

/*
 * test priority_queue_init
 */
UT_CASE_DEFINATION(priority_queue_init)
void test_priority_queue_init__null(void** state)
{
    expect_assert_failure(priority_queue_init(NULL));
}

void test_priority_queue_init__successfully(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == NULL);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_init_ex
 */
UT_CASE_DEFINATION(priority_queue_init_ex)
void test_priority_queue_init_ex__null(void** state)
{
    expect_assert_failure(priority_queue_init_ex(NULL, NULL));
}

void test_priority_queue_init_ex__bfun_NULL(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init_ex(ppque, NULL);
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == NULL);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_ex__successfully(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init_ex(ppque, fun_greater_int);
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == fun_greater_int);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_destroy
 */
UT_CASE_DEFINATION(priority_queue_destroy)
void test_priority_queue_destroy__null(void** state)
{
    expect_assert_failure(priority_queue_destroy(NULL));
}

void test_priority_queue_destroy__not_init(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    priority_queue_destroy(ppque);
}

void test_priority_queue_destroy__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init_ex(ppque, fun_greater_int);
    priority_queue_destroy(ppque);
}

void test_priority_queue_destroy__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init_ex(ppque, fun_greater_int);
    priority_queue_push(ppque, 100);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_init_copy
 */
UT_CASE_DEFINATION(priority_queue_init_copy)
void test_priority_queue_init_copy__dest_NULL(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    expect_assert_failure(priority_queue_init_copy(NULL, ppque));
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy__src_NULL(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    expect_assert_failure(priority_queue_init_copy(ppque, NULL));
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy__src_not_init(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init(ppque_src);
    ppque_src->_t_vector._pby_start = 0x100;
    expect_assert_failure(priority_queue_init_copy(ppque_dest, ppque_src));
    ppque_src->_t_vector._pby_start = 0x00;
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_init_copy__not_same_type(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(double);

    priority_queue_init(ppque_src);
    expect_assert_failure(priority_queue_init_copy(ppque_dest, ppque_src));
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_init_copy__bfun_NULL(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init(ppque_src);
    priority_queue_init_copy(ppque_dest, ppque_src);
    assert_true(_vector_is_inited(&ppque_dest->_t_vector));
    assert_true(ppque_dest->_t_binary_op == NULL);
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_init_copy__bfun_not_NULL(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init_ex(ppque_src, fun_greater_int);
    priority_queue_push(ppque_src, 100);
    priority_queue_push(ppque_src, 200);
    priority_queue_push(ppque_src, 300);
    priority_queue_init_copy(ppque_dest, ppque_src);
    assert_true(_vector_is_inited(&ppque_dest->_t_vector));
    assert_true(ppque_dest->_t_binary_op == fun_greater_int);
    assert_true(priority_queue_size(ppque_dest) == 3);
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

/*
 * test priority_queue_init_copy_range
 */
UT_CASE_DEFINATION(priority_queue_init_copy_range)
void test_priority_queue_init_copy_range__dest_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(priority_queue_init_copy_range(NULL, deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
}

void test_priority_queue_init_copy_range__invalid_range(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(priority_queue_init_copy_range(ppque, deque_end(pdeq), deque_begin(pdeq)));
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_range__not_same_type(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(double);

    deque_init_n(pdeq, 10);
    expect_assert_failure(priority_queue_init_copy_range(ppque, deque_begin(pdeq), deque_end(pdeq)));
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_range__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    priority_queue_init_copy_range(ppque, deque_begin(pdeq), deque_end(pdeq));
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == NULL);
    assert_true(priority_queue_size(ppque) == 0);
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_range__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {4, 2, 0, 8, 9, 1, 3, 5, 7, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    priority_queue_init_copy_range(ppque, deque_begin(pdeq), deque_end(pdeq));
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == NULL);
    assert_true(priority_queue_size(ppque) == 10);
    assert_true(*(int*)priority_queue_top(ppque) == 9);
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_init_copy_range_ex
 */
UT_CASE_DEFINATION(priority_queue_init_copy_range_ex)
void test_priority_queue_init_copy_range_ex__dest_NULL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(priority_queue_init_copy_range_ex(NULL, deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
}

void test_priority_queue_init_copy_range_ex__invalid_range(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    expect_assert_failure(priority_queue_init_copy_range_ex(ppque, deque_end(pdeq), deque_begin(pdeq), fun_greater_int));
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_range_ex__not_same_type(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(double);

    deque_init_n(pdeq, 10);
    expect_assert_failure(priority_queue_init_copy_range_ex(ppque, deque_begin(pdeq), deque_end(pdeq), fun_greater_int));
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_range_ex__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    priority_queue_init_copy_range_ex(ppque, deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == fun_greater_int);
    assert_true(priority_queue_size(ppque) == 0);
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_range_ex__bfun_NULL_not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {4, 2, 0, 8, 9, 1, 3, 5, 7, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    priority_queue_init_copy_range_ex(ppque, deque_begin(pdeq), deque_end(pdeq), NULL);
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == NULL);
    assert_true(priority_queue_size(ppque) == 10);
    assert_true(*(int*)priority_queue_top(ppque) == 9);
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_range_ex__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    deque_t* pdeq = create_deque(int);
    int an_array[] = {4, 2, 0, 8, 9, 1, 3, 5, 7, 6};

    deque_init_copy_array(pdeq, an_array, sizeof(an_array)/sizeof(an_array[0]));
    priority_queue_init_copy_range_ex(ppque, deque_begin(pdeq), deque_end(pdeq), fun_greater_int);
    assert_true(_vector_is_inited(&ppque->_t_vector));
    assert_true(ppque->_t_binary_op == fun_greater_int);
    assert_true(priority_queue_size(ppque) == 10);
    assert_true(*(int*)priority_queue_top(ppque) == 0);
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

