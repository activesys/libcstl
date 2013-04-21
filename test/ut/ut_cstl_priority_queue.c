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
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == NULL);
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
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == NULL);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_ex__successfully(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init_ex(ppque, fun_greater_int);
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == fun_greater_int);
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
    ppque_src->_vec_base._pby_start = (void*)0x100;
    expect_assert_failure(priority_queue_init_copy(ppque_dest, ppque_src));
    ppque_src->_vec_base._pby_start = NULL;
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
    assert_true(_vector_is_inited(&ppque_dest->_vec_base));
    assert_true(ppque_dest->_bfun_priority == NULL);
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
    assert_true(_vector_is_inited(&ppque_dest->_vec_base));
    assert_true(ppque_dest->_bfun_priority == fun_greater_int);
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
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == NULL);
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
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == NULL);
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
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == fun_greater_int);
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
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == NULL);
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
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(ppque->_bfun_priority == fun_greater_int);
    assert_true(priority_queue_size(ppque) == 10);
    assert_true(*(int*)priority_queue_top(ppque) == 0);
    deque_destroy(pdeq);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_assign
 */
UT_CASE_DEFINATION(priority_queue_assign)
void test_priority_queue_assign__dest_NULL(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    expect_assert_failure(priority_queue_assign(NULL, ppque));
    priority_queue_destroy(ppque);
}

void test_priority_queue_assign__src_NULL(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    expect_assert_failure(priority_queue_assign(ppque, NULL));
    priority_queue_destroy(ppque);
}

void test_priority_queue_assign__dest_not_init(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init(ppque_dest);
    priority_queue_init(ppque_src);
    ppque_dest->_vec_base._pby_start = (void*)0x100;
    expect_assert_failure(priority_queue_assign(ppque_dest, ppque_src));
    ppque_dest->_vec_base._pby_start = NULL;
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_assign__src_not_init(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init(ppque_dest);
    priority_queue_init(ppque_src);
    ppque_src->_vec_base._pby_start = (void*)0x100;
    expect_assert_failure(priority_queue_assign(ppque_dest, ppque_src));
    ppque_src->_vec_base._pby_start = NULL;
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_assign__not_same_type(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(double);

    priority_queue_init(ppque_dest);
    priority_queue_init(ppque_src);
    expect_assert_failure(priority_queue_assign(ppque_dest, ppque_src));
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_assign__not_same_rule(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init(ppque_dest);
    priority_queue_init_ex(ppque_src, fun_greater_int);
    expect_assert_failure(priority_queue_assign(ppque_dest, ppque_src));
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_assign__empty(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init(ppque_dest);
    priority_queue_init(ppque_src);
    priority_queue_push(ppque_dest, 100);
    priority_queue_push(ppque_dest, 200);
    priority_queue_assign(ppque_dest, ppque_src);
    assert_true(priority_queue_empty(ppque_dest));
    assert_true(ppque_dest->_bfun_priority == NULL);
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

void test_priority_queue_assign__not_empty(void** state)
{
    priority_queue_t* ppque_dest = create_priority_queue(int);
    priority_queue_t* ppque_src = create_priority_queue(int);

    priority_queue_init(ppque_dest);
    priority_queue_init(ppque_src);
    priority_queue_push(ppque_src, 100);
    priority_queue_push(ppque_src, 200);
    priority_queue_assign(ppque_dest, ppque_src);
    assert_true(priority_queue_size(ppque_dest) == 2);
    assert_true(ppque_dest->_bfun_priority == NULL);
    priority_queue_destroy(ppque_dest);
    priority_queue_destroy(ppque_src);
}

/*
 * test priority_queue_empty
 */
UT_CASE_DEFINATION(priority_queue_empty)
void test_priority_queue_empty__NULL(void** state)
{
    expect_assert_failure(priority_queue_empty(NULL));
}

void test_priority_queue_empty__not_init(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    ppque->_vec_base._pby_start = (void*)0x100;
    expect_assert_failure(priority_queue_empty(ppque));
    ppque->_vec_base._pby_start = NULL;
    priority_queue_destroy(ppque);
}

void test_priority_queue_empty__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    assert_true(priority_queue_empty(ppque));
    priority_queue_destroy(ppque);
}

void test_priority_queue_empty__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    priority_queue_push(ppque, 100);
    assert_false(priority_queue_empty(ppque));
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_size
 */
UT_CASE_DEFINATION(priority_queue_size)
void test_priority_queue_size__NULL(void** state)
{
    expect_assert_failure(priority_queue_size(NULL));
}

void test_priority_queue_size__not_init(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    ppque->_vec_base._pby_start = (void*)0x100;
    expect_assert_failure(priority_queue_size(ppque));
    ppque->_vec_base._pby_start = NULL;
    priority_queue_destroy(ppque);
}

void test_priority_queue_size__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    assert_true(priority_queue_size(ppque) == 0);
    priority_queue_destroy(ppque);
}

void test_priority_queue_size__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    priority_queue_push(ppque, 100);
    assert_true(priority_queue_size(ppque) == 1);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_top
 */
UT_CASE_DEFINATION(priority_queue_top)
void test_priority_queue_top__NULL(void** state)
{
    expect_assert_failure(priority_queue_top(NULL));
}

void test_priority_queue_top__not_init(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    ppque->_vec_base._pby_start = (void*)0x100;
    expect_assert_failure(priority_queue_top(ppque));
    ppque->_vec_base._pby_start = NULL;
    priority_queue_destroy(ppque);
}

void test_priority_queue_top__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    expect_assert_failure(priority_queue_top(ppque));
    priority_queue_destroy(ppque);
}

void test_priority_queue_top__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    priority_queue_push(ppque, 100);
    assert_true(*(int*)priority_queue_top(ppque) == 100);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_pop
 */
UT_CASE_DEFINATION(priority_queue_pop)
void test_priority_queue_pop__NULL(void** state)
{
    expect_assert_failure(priority_queue_pop(NULL));
}

void test_priority_queue_pop__not_init(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    ppque->_vec_base._pby_start = (void*)0x100;
    expect_assert_failure(priority_queue_pop(ppque));
    ppque->_vec_base._pby_start = NULL;
    priority_queue_destroy(ppque);
}

void test_priority_queue_pop__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    expect_assert_failure(priority_queue_pop(ppque));
    priority_queue_destroy(ppque);
}

void test_priority_queue_pop__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init(ppque);
    priority_queue_push(ppque, 100);
    priority_queue_push(ppque, 200);
    priority_queue_push(ppque, 139);
    assert_true(*(int*)priority_queue_top(ppque) == 200);
    priority_queue_pop(ppque);
    assert_true(*(int*)priority_queue_top(ppque) == 139);
    assert_true(priority_queue_size(ppque) == 2);
    priority_queue_destroy(ppque);
}

void test_priority_queue_pop__not_empty_ex(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    priority_queue_init_ex(ppque, fun_greater_int);
    priority_queue_push(ppque, 100);
    priority_queue_push(ppque, 200);
    priority_queue_push(ppque, 139);
    assert_true(*(int*)priority_queue_top(ppque) == 100);
    priority_queue_pop(ppque);
    assert_true(*(int*)priority_queue_top(ppque) == 139);
    assert_true(priority_queue_size(ppque) == 2);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_init_copy_array
 */
UT_CASE_DEFINATION(priority_queue_init_copy_array)
void test_priority_queue_init_copy_array__dest_null(void** state)
{
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    expect_assert_failure(priority_queue_init_copy_array(NULL, an_array, sizeof(an_array)/sizeof(an_array[0])));
}

void test_priority_queue_init_copy_array__src_null(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    expect_assert_failure(priority_queue_init_copy_array(ppque, NULL, 10));
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_array__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    priority_queue_init_copy_array(ppque, an_array, 0);
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(priority_queue_empty(ppque));
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_array__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    int an_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    priority_queue_init_copy_array(ppque, an_array, sizeof(an_array)/sizeof(an_array[0]));
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(priority_queue_size(ppque) == 10);
    assert_true(*(int*)priority_queue_top(ppque) == 9);
    priority_queue_destroy(ppque);
}

/*
 * test priority_queue_init_copy_array_ex
 */
UT_CASE_DEFINATION(priority_queue_init_copy_array_ex)
void test_priority_queue_init_copy_array_ex__dest_null(void** state)
{
    int an_array_ex[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    expect_assert_failure(priority_queue_init_copy_array_ex(NULL, an_array_ex, sizeof(an_array_ex)/sizeof(an_array_ex[0]), fun_greater_int));
}

void test_priority_queue_init_copy_array_ex__src_null(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);

    expect_assert_failure(priority_queue_init_copy_array_ex(ppque, NULL, 10, fun_greater_int));
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_array_ex__empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    int an_array_ex[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    priority_queue_init_copy_array_ex(ppque, an_array_ex, 0, fun_greater_int);
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(priority_queue_empty(ppque));
    assert_true(ppque->_bfun_priority == fun_greater_int);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_array_ex__not_empty(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    int an_array_ex[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    priority_queue_init_copy_array_ex(ppque, an_array_ex, sizeof(an_array_ex)/sizeof(an_array_ex[0]), fun_greater_int);
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(priority_queue_size(ppque) == 10);
    assert_true(*(int*)priority_queue_top(ppque) == 0);
    assert_true(ppque->_bfun_priority == fun_greater_int);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_array_ex__empty_bfun_NULL(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    int an_array_ex[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    priority_queue_init_copy_array_ex(ppque, an_array_ex, 0, NULL);
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(priority_queue_empty(ppque));
    assert_true(ppque->_bfun_priority == NULL);
    priority_queue_destroy(ppque);
}

void test_priority_queue_init_copy_array_ex__not_empty_bfun_NULL(void** state)
{
    priority_queue_t* ppque = create_priority_queue(int);
    int an_array_ex[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    priority_queue_init_copy_array_ex(ppque, an_array_ex, sizeof(an_array_ex)/sizeof(an_array_ex[0]), NULL);
    assert_true(_vector_is_inited(&ppque->_vec_base));
    assert_true(priority_queue_size(ppque) == 10);
    assert_true(*(int*)priority_queue_top(ppque) == 9);
    assert_true(ppque->_bfun_priority == NULL);
    priority_queue_destroy(ppque);
}

