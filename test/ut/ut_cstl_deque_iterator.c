#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_deque_iterator.h"
#include "cstl/cdeque.h"

#include "ut_def.h"
#include "ut_cstl_deque_iterator.h"

UT_SUIT_DEFINATION(cstl_deque_iterator, _create_deque_iterator)

/*
 * test _create_deque_iterator
 */
UT_CASE_DEFINATION(_create_deque_iterator)
void test__create_deque_iterator__successfully(void** state)
{
    deque_iterator_t it_iter = _create_deque_iterator();
    assert_true(it_iter._t_pos._t_dequepos._pc_corepos == NULL);
    assert_true(it_iter._t_pos._t_dequepos._pc_first == NULL);
    assert_true(it_iter._t_pos._t_dequepos._pc_afterlast == NULL);
    assert_true(it_iter._t_pos._t_dequepos._ppc_mappos == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _DEQUE_CONTAINER);
    assert_true(it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR);
}

/*
 * test _deque_iterator_equal
 */
UT_CASE_DEFINATION(_deque_iterator_equal)
void test__deque_iterator_equal__different_container_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_equal(it_first, it_second));
}

void test__deque_iterator_equal__different_iterator_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_equal(it_first, it_second));
}

void test__deque_iterator_equal__different_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);

    it_first = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_equal(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_equal__first_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_first._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_equal(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_equal__second_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_second._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_equal(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_equal__equal_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 10);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);

    it_first = it_second = deque_begin(pdeq);

    assert_true(_deque_iterator_equal(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_equal__equal_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 45);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);
    it_second._t_pos._t_dequepos._pc_corepos = it_second._t_pos._t_dequepos._pc_first;

    assert_true(_deque_iterator_equal(it_first, it_second));
    assert_true(_deque_iterator_equal(it_second, it_first));

    deque_destroy(pdeq);
}

void test__deque_iterator_equal__not_equal_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 10);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 40);
    deque_push_front(pdeq, 45);

    it_first = deque_begin(pdeq);
    it_second = iterator_next(it_first);

    assert_false(_deque_iterator_equal(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_equal__not_equal_not_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 10);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 40);
    deque_push_back(pdeq, 45);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_false(_deque_iterator_equal(it_first, it_second));

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_less
 */
UT_CASE_DEFINATION(_deque_iterator_less)
void test__deque_iterator_less__different_container_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_less(it_first, it_second));
}

void test__deque_iterator_less__different_iterator_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_less(it_first, it_second));
}

void test__deque_iterator_less__different_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);

    it_first = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__first_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_first._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__second_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_second._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__first_greater_than_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);

    it_first = iterator_next_n(deque_begin(pdeq), 3);
    it_second = deque_begin(pdeq);

    assert_false(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__first_equal_to_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);

    it_first = iterator_next_n(deque_begin(pdeq), 3);
    it_second = it_first;

    assert_false(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__first_less_than_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);

    it_first = deque_begin(pdeq);
    it_second = iterator_next_n(it_first, 2);

    assert_true(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__first_greater_than_second_not_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 9);

    it_first = iterator_prev_n(deque_end(pdeq), 2);
    it_second = iterator_next(deque_begin(pdeq));

    assert_false(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__first_equal_to_second_not_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 9);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);
    it_second._t_pos._t_dequepos._pc_corepos = it_second._t_pos._t_dequepos._pc_first;

    assert_false(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_less__first_less_than_second_not_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 9);

    it_first = iterator_next(deque_begin(pdeq));
    it_second = iterator_prev(deque_end(pdeq));

    assert_true(_deque_iterator_less(it_first, it_second));

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_before
 */
UT_CASE_DEFINATION(_deque_iterator_before)
void test__deque_iterator_before__different_container_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_before(it_first, it_second));
}

void test__deque_iterator_before__different_iterator_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_before(it_first, it_second));
}

void test__deque_iterator_before__different_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);

    it_first = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__first_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_first._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__second_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_second._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__first_greater_than_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);

    it_first = iterator_next_n(deque_begin(pdeq), 3);
    it_second = deque_begin(pdeq);

    assert_false(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__first_equal_to_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);

    it_first = iterator_next_n(deque_begin(pdeq), 3);
    it_second = it_first;

    assert_false(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__first_less_than_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);

    it_first = deque_begin(pdeq);
    it_second = iterator_next_n(it_first, 2);

    assert_true(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__first_greater_than_second_not_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 9);

    it_first = iterator_prev_n(deque_end(pdeq), 2);
    it_second = iterator_next(deque_begin(pdeq));

    assert_false(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__first_equal_to_second_not_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 9);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);
    it_second._t_pos._t_dequepos._pc_corepos = it_second._t_pos._t_dequepos._pc_first;

    assert_false(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_before__first_less_than_second_not_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 9);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 9);

    it_first = iterator_next(deque_begin(pdeq));
    it_second = iterator_prev(deque_end(pdeq));

    assert_true(_deque_iterator_before(it_first, it_second));

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_get_value
 */
UT_CASE_DEFINATION(_deque_iterator_get_value)
void test__deque_iterator_get_value__invalid_iterator(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_get_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__invalid_iterator_container_type(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_get_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__invalid_iterator_iterator_type(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_get_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__invalid_iterator_container_pointer(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_get_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__deque_end(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_get_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__invalid_value_buffer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_get_value(it_iter, NULL));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__successfully_not_border(void** state)
{
    int value = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 10);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 4);
    it_iter = deque_begin(pdeq);

    _deque_iterator_get_value(it_iter, &value);
    assert_int_equal(value, 4);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__successfully_border(void** state)
{
    int value = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 10);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 4);
    it_iter = deque_begin(pdeq);

    _deque_iterator_get_value(it_iter, &value);
    assert_int_equal(value, 10);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__successfully_cstr_not_border(void** state)
{
    char* str = NULL;
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, "ahdlfa");
    deque_push_front(pdeq, "iiii");
    deque_push_front(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    _deque_iterator_get_value(it_iter, &str);
    assert_true(strcmp(str, "abcdefg") == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_value__successfully_cstr_border(void** state)
{
    char* str = NULL;
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, "ahdlfa");
    deque_push_back(pdeq, "iiii");
    deque_push_back(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    _deque_iterator_get_value(it_iter, &str);
    assert_true(strcmp(str, "ahdlfa") == 0);

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_set_value
 */
UT_CASE_DEFINATION(_deque_iterator_set_value)
void test__deque_iterator_set_value__invalid_iterator(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pc_corepos = NULL;

    expect_assert_failure(_deque_iterator_set_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__invalid_iterator_container_type(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_set_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__invalid_iterator_iterator_type(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_set_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__invalid_iterator_container_pointer(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_set_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__deque_end(void** state)
{
    int value;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_set_value(it_iter, &value));

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__invalid_value_buffer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_set_value(it_iter, NULL));

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__successfully_not_border(void** state)
{
    int value = 100;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 34);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 9);
    it_iter = deque_begin(pdeq);

    _deque_iterator_set_value(it_iter, &value);
    assert_int_equal(*(int*)deque_at(pdeq, 0), 100);

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__successfully_border(void** state)
{
    int value = 100;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 34);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 9);
    it_iter = deque_begin(pdeq);

    _deque_iterator_set_value(it_iter, &value);
    assert_int_equal(*(int*)deque_at(pdeq, 0), 100);

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__successfully_cstr_not_border(void** state)
{
    const char* str = "AAAAAAAAAAA";
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, "aldkfaldkjf");
    deque_push_front(pdeq, "bbbb");
    deque_push_front(pdeq, "vbbvbv");
    it_iter = deque_begin(pdeq);

    _deque_iterator_set_value(it_iter, str);
    assert_true(strcmp(str, (char*)deque_at(pdeq, 0)) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_set_value__successfully_cstr_border(void** state)
{
    const char* str = "AAAAAAAAAAA";
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, "aldkfaldkjf");
    deque_push_back(pdeq, "bbbb");
    deque_push_back(pdeq, "vbbvbv");
    it_iter = deque_begin(pdeq);

    _deque_iterator_set_value(it_iter, str);
    assert_true(strcmp(str, (char*)deque_at(pdeq, 0)) == 0);

    deque_destroy(pdeq);
}

