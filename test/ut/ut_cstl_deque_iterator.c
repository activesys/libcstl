#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_deque_iterator.h"
#include "cstl/cdeque.h"
#include "cstl/cstring.h"

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
    assert_true(it_iter._t_pos._t_dequepos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_dequepos._pby_first == NULL);
    assert_true(it_iter._t_pos._t_dequepos._pby_afterlast == NULL);
    assert_true(it_iter._t_pos._t_dequepos._ppby_mappos == NULL);
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
    it_first._t_pos._t_dequepos._pby_corepos = NULL;

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
    it_second._t_pos._t_dequepos._pby_corepos = NULL;

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
    it_second._t_pos._t_dequepos._pby_corepos = it_second._t_pos._t_dequepos._pby_first;

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
    it_first._t_pos._t_dequepos._pby_corepos = NULL;

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
    it_second._t_pos._t_dequepos._pby_corepos = NULL;

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
    it_second._t_pos._t_dequepos._pby_corepos = it_second._t_pos._t_dequepos._pby_first;

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
    it_first._t_pos._t_dequepos._pby_corepos = NULL;

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
    it_second._t_pos._t_dequepos._pby_corepos = NULL;

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
    it_second._t_pos._t_dequepos._pby_corepos = it_second._t_pos._t_dequepos._pby_first;

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
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

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
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

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

/*
 * test _deque_iterator_get_pointer
 */
UT_CASE_DEFINATION(_deque_iterator_get_pointer)
void test__deque_iterator_get_pointer__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_get_pointer(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_get_pointer(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_get_pointer(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_get_pointer(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__deque_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_get_pointer(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 23);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 9);
    deque_push_front(pdeq, 100);
    it_iter = deque_begin(pdeq);

    assert_int_equal(*(int*)_deque_iterator_get_pointer(it_iter), 100);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 23);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 9);
    deque_push_back(pdeq, 100);
    it_iter = deque_begin(pdeq);

    assert_int_equal(*(int*)_deque_iterator_get_pointer(it_iter), 23);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__successfully_cstr_not_border(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, "llskd");
    deque_push_front(pdeq, "llllllll");
    deque_push_front(pdeq, "bx");
    deque_push_front(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    assert_true(strcmp("abcdefg", (char*)_deque_iterator_get_pointer(it_iter)) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer__successfully_cstr_border(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, "llskd");
    deque_push_back(pdeq, "llllllll");
    deque_push_back(pdeq, "bx");
    deque_push_back(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    assert_true(strcmp("llskd", (char*)_deque_iterator_get_pointer(it_iter)) == 0);

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_deque_iterator_get_pointer_ignore_cstr)
void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_get_pointer_ignore_cstr(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_get_pointer_ignore_cstr(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_get_pointer_ignore_cstr(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_get_pointer_ignore_cstr(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__deque_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_get_pointer_ignore_cstr(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 23);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 9);
    deque_push_front(pdeq, 100);
    it_iter = deque_begin(pdeq);

    assert_int_equal(*(int*)_deque_iterator_get_pointer_ignore_cstr(it_iter), 100);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 23);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 9);
    deque_push_back(pdeq, 100);
    it_iter = deque_begin(pdeq);

    assert_int_equal(*(int*)_deque_iterator_get_pointer_ignore_cstr(it_iter), 23);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__successfully_cstr_not_border(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, "llskd");
    deque_push_front(pdeq, "llllllll");
    deque_push_front(pdeq, "bx");
    deque_push_front(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    assert_true(strcmp("abcdefg", string_c_str(_deque_iterator_get_pointer_ignore_cstr(it_iter))) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_get_pointer_ignore_cstr__successfully_cstr_border(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, "llskd");
    deque_push_back(pdeq, "llllllll");
    deque_push_back(pdeq, "bx");
    deque_push_back(pdeq, "abcdefg");
    it_iter = deque_begin(pdeq);

    assert_true(strcmp("llskd", string_c_str(_deque_iterator_get_pointer_ignore_cstr(it_iter))) == 0);

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_next
 */
UT_CASE_DEFINATION(_deque_iterator_next)
void test__deque_iterator_next__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_next(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_next__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_next(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_next__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_next(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_next__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_next(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_next__invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_next(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_next__successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 949);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 233);
    deque_push_front(pdeq, 4);
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = _deque_iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 233);

    deque_destroy(pdeq);
}

void test__deque_iterator_next__successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 949);
    deque_push_back(pdeq, 8);
    deque_push_back(pdeq, 0);
    deque_push_back(pdeq, 233);
    deque_push_back(pdeq, 4);
    it_iter = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 949);
    it_iter = _deque_iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_prev
 */
UT_CASE_DEFINATION(_deque_iterator_prev)
void test__deque_iterator_prev__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_prev(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_prev(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_prev(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_prev(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev__invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_prev(it_iter));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev__successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 4);
    deque_push_back(pdeq, 5);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev__successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 2);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 4);
    deque_push_front(pdeq, 5);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_next_n
 */
UT_CASE_DEFINATION(_deque_iterator_next_n)
void test__deque_iterator_next_n__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_next_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_next_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_next_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_next_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_end_invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_next_n(it_iter, 20));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_begin_invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_next_n(it_iter, -20));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_end_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 5);
    assert_true(iterator_equal(it_iter, it_end));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_not_end_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 3);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_end_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 10);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_end_successfully_border_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 6);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_not_end_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 8);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 16);

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_front_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, -5);
    assert_true(iterator_equal(it_iter, it_begin));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_not_front_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, -3);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_front_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, -10);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_not_front_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, -8);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__does_not_move_successfully(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 0);

    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_end_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i + 1);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 42);

    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_not_end_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i + 1);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 40);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_not_end_span_middle_border(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i + 1);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 37);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_end_span_border_end(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 37);

    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_end_span_border_begin_end(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, 32);

    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_front_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 20; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i);
    }
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, -25);

    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_not_front_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 20; ++i)
    {
        deque_push_front(pdeq, i);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i);
    }
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, -20);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 14);

    deque_destroy(pdeq);
}

void test__deque_iterator_next_n__move_to_front_span_border_begin_end(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 32; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_next_n(it_iter, -32);

    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_prev_n
 */
UT_CASE_DEFINATION(_deque_iterator_prev_n)
void test__deque_iterator_prev_n__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_prev_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_prev_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_prev_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_prev_n(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_end_invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_prev_n(it_iter, -20));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_begin_invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_prev_n(it_iter, 20));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_end_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -5);
    assert_true(iterator_equal(it_iter, it_end));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_not_end_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -3);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_end_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -10);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_end_successfully_border_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -6);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_not_end_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -8);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 16);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_front_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 5);
    assert_true(iterator_equal(it_iter, it_begin));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_not_front_successfully_not_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_pop_back(pdeq);
    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    assert_true(it_begin._t_pos._t_dequepos._ppby_mappos == it_end._t_pos._t_dequepos._ppby_mappos);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 3);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_front_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 10);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_not_front_successfully_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 1);
    deque_push_front(pdeq, 0);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 7);
    deque_push_back(pdeq, 19);
    deque_push_back(pdeq, 14);
    deque_push_back(pdeq, 16);
    deque_push_back(pdeq, 12);
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 8);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__does_not_move_successfully(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 0);

    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_end_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i + 1);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -42);

    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_not_end_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i + 1);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -40);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_not_end_span_middle_border(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i + 1);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -37);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_end_span_border_end(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 5; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -37);

    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_end_span_border_begin_end(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 100);
    }
    it_iter = deque_begin(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, -32);

    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_front_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 20; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i);
    }
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 25);

    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_not_front_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 20; ++i)
    {
        deque_push_front(pdeq, i);
    }
    for(i = 0; i < 5; ++i)
    {
        deque_push_back(pdeq, i);
    }
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 20);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 14);

    deque_destroy(pdeq);
}

void test__deque_iterator_prev_n__move_to_front_span_border_begin_end(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init(pdeq);
    for(i = 0; i < 32; ++i)
    {
        deque_push_front(pdeq, 0);
    }
    it_iter = deque_end(pdeq);
    it_iter = _deque_iterator_prev_n(it_iter, 32);

    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_at
 */
UT_CASE_DEFINATION(_deque_iterator_at)
void test__deque_iterator_at__invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_at(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_at__invalid_iterator_container_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_at(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_at__invalid_iterator_iterator_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_at(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_at__invalid_iterator_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);
    it_iter._pt_container = NULL;

    expect_assert_failure(_deque_iterator_at(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_at__move_to_end_invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_at(it_iter, 20));

    deque_destroy(pdeq);
}

void test__deque_iterator_at__move_to_begin_invalid_returned_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_n(pdeq, 10);
    it_iter = deque_end(pdeq);

    expect_assert_failure(_deque_iterator_at(it_iter, -20));

    deque_destroy(pdeq);
}

void test__deque_iterator_at__end_invalid_iterator(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;

    deque_init_elem(pdeq, 10, 100);
    it_iter = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_at(it_iter, 10));

    deque_destroy(pdeq);
}

void test__deque_iterator_at__move_to_end_successfully(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    it_iter = deque_begin(pdeq);

    assert_int_equal(*(int*)_deque_iterator_at(it_iter, 5), 5);

    deque_destroy(pdeq);
}

void test__deque_iterator_at__move_to_end_cstr_successfully(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;
    char* s_at = NULL;

    deque_init(pdeq);
    deque_push_back(pdeq, "abc");
    deque_push_back(pdeq, "def");
    deque_push_back(pdeq, "hij");
    deque_push_back(pdeq, "klm");
    deque_push_back(pdeq, "nop");
    it_iter = deque_begin(pdeq);
    s_at = (char*)_deque_iterator_at(it_iter, 3);

    assert_true(strcmp(s_at, "klm") == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_at__move_to_front_successfully(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0;i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    it_iter = deque_end(pdeq);

    assert_int_equal(*(int*)_deque_iterator_at(it_iter, -2), 8);

    deque_destroy(pdeq);
}

void test__deque_iterator_at__move_to_front_cstr_successfully(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;
    char* s_at = NULL;

    deque_init(pdeq);
    deque_push_back(pdeq, "abc");
    deque_push_back(pdeq, "def");
    deque_push_back(pdeq, "hij");
    deque_push_back(pdeq, "klm");
    deque_push_back(pdeq, "nop");
    it_iter = deque_end(pdeq);
    s_at = (char*)_deque_iterator_at(it_iter, -3);

    assert_true(strcmp(s_at, "hij") == 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_at__does_not_move_successfully(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    it_iter = _deque_iterator_next_n(deque_begin(pdeq), 4);

    assert_int_equal(*(int*)_deque_iterator_at(it_iter, 0), 4);

    deque_destroy(pdeq);
}

void test__deque_iterator_at__does_not_move_cstr_successfully(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;
    char* s_at = NULL;

    deque_init(pdeq);
    deque_push_back(pdeq, "abc");
    deque_push_back(pdeq, "def");
    deque_push_back(pdeq, "hij");
    deque_push_back(pdeq, "klm");
    deque_push_back(pdeq, "nop");
    it_iter = deque_begin(pdeq);
    s_at = (char*)_deque_iterator_at(it_iter, 0);

    assert_true(strcmp(s_at, "abc") == 0);

    deque_destroy(pdeq);
}

/*
 * test _deque_iterator_minus
 */
UT_CASE_DEFINATION(_deque_iterator_minus)
void test__deque_iterator_minus__different_container_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_deque_iterator_minus(it_first, it_second));
}

void test__deque_iterator_minus__different_iterator_type(void** state)
{
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_deque_iterator_minus(it_first, it_second));
}

void test__deque_iterator_minus__different_container_pointer(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);

    it_first = deque_begin(pdeq);

    expect_assert_failure(_deque_iterator_minus(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_first._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_minus(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__second_is_not_belong_to_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = it_second = deque_begin(pdeq);
    it_second._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(_deque_iterator_minus(it_first, it_second));

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_less_then_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), -10);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_less_then_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 0);
    deque_pop_back(pdeq);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), -4);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_less_then_second_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 0);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 6);
    deque_push_back(pdeq, 8);
    deque_push_back(pdeq, 0);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), -10);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_less_then_second_border_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 0);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), -5);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_less_then_second_border_begin(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 6);
    deque_push_back(pdeq, 8);
    deque_push_back(pdeq, 0);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), -5);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_less_then_second_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 3);
    }

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), -32);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_greater_then_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = deque_end(pdeq);
    it_second = deque_begin(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 10);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_greater_then_second_same_chunk(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 0);
    deque_pop_back(pdeq);

    it_first = deque_end(pdeq);
    it_second = deque_begin(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 4);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_greater_then_second_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 0);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 6);
    deque_push_back(pdeq, 8);
    deque_push_back(pdeq, 0);

    it_first = deque_end(pdeq);
    it_second = deque_begin(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 10);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_greater_then_second_border_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_front(pdeq, 3);
    deque_push_front(pdeq, 5);
    deque_push_front(pdeq, 6);
    deque_push_front(pdeq, 8);
    deque_push_front(pdeq, 0);

    it_first = deque_end(pdeq);
    it_second = deque_begin(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 5);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_greater_then_second_border_begin(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    deque_push_back(pdeq, 3);
    deque_push_back(pdeq, 5);
    deque_push_back(pdeq, 6);
    deque_push_back(pdeq, 8);
    deque_push_back(pdeq, 0);

    it_first = deque_end(pdeq);
    it_second = deque_begin(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 5);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_greater_then_second_span(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);
    for(i = 0; i < 32; ++i)
    {
        deque_push_back(pdeq, 3);
    }

    it_first = deque_end(pdeq);
    it_second = deque_begin(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 32);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_equal_to_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init_n(pdeq, 10);

    it_first = deque_begin(pdeq);
    it_second = deque_begin(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 0);

    deque_destroy(pdeq);
}

void test__deque_iterator_minus__first_equal_to_second_border(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_iterator_t it_first = _create_deque_iterator();
    deque_iterator_t it_second = _create_deque_iterator();

    deque_init(pdeq);

    it_first = deque_begin(pdeq);
    it_second = deque_end(pdeq);

    assert_int_equal(_deque_iterator_minus(it_first, it_second), 0);

    deque_destroy(pdeq);
}


