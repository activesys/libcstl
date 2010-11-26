#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"

#include "ut_cstl_vector_iterator.h"

/*
 * test _create_vector_iterator
 */
void test__create_vector_iterator__successfully(void** state)
{
    vector_iterator_t it_iter = _create_vector_iterator();
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _VECTOR_CONTAINER);
    assert_true(it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR);
    assert_true(it_iter._t_pos._pc_corepos == NULL);
}

/*
 * test _vector_iterator_equal
 */
void test__vector_iterator_equal__different_container_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_equal(it_first, it_second));
}

void test__vector_iterator_equal__different_iterator_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;

    expect_assert_failure(_vector_iterator_equal(it_first, it_second));
}

void test__vector_iterator_equal__different_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init(pvec);

    it_first = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_equal(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_equal__first_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_first._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_equal(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_equal__second_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_second._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_equal(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_equal__equal(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init(pvec);

    it_first = it_second = vector_begin(pvec);

    assert_true(_vector_iterator_equal(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_equal__not_equal(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);

    assert_false(_vector_iterator_equal(it_first, it_second));

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_less
 */
void test__vector_iterator_less__different_container_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_less(it_first, it_second));
}

void test__vector_iterator_less__different_iterator_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;

    expect_assert_failure(_vector_iterator_less(it_first, it_second));
}

void test__vector_iterator_less__different_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init(pvec);

    it_first = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_less(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_less__first_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_first._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_less(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_less__second_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_second._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_less(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_less__first_greater_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);

    assert_false(_vector_iterator_less(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_less__first_equal_to_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);

    assert_false(_vector_iterator_less(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_less__first_less_than_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);

    assert_true(_vector_iterator_less(it_first, it_second));

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_before
 */
void test__vector_iterator_before__different_container_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_before(it_first, it_second));
}

void test__vector_iterator_before__different_iterator_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_iteratortype = _RANDOM_ACCESS_ITERATOR;

    expect_assert_failure(_vector_iterator_before(it_first, it_second));
}

void test__vector_iterator_before__different_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init(pvec);

    it_first = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_before__first_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_first._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_before__second_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_second._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_before__first_after_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);

    assert_false(_vector_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_before__first_equal_to_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);

    assert_false(_vector_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_before__first_before_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);

    assert_true(_vector_iterator_before(it_first, it_second));

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_get_value
 */
void test__vector_iterator_get_value__invalid_iterator(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_get_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_get_value__vector_end(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    expect_assert_failure(_vector_iterator_get_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_get_value__invalid_value_buffer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_get_value(it_iter, NULL));

    vector_destroy(pvec);
}

void test__vector_iterator_get_value__successfully(void** state)
{
    int value = 0;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, 100);
    it_iter = vector_begin(pvec);

    _vector_iterator_get_value(it_iter, &value);
    assert_int_equal(value, 100);

    vector_destroy(pvec);
}

void test__vector_iterator_get_value__successfully_cstr(void** state)
{
    char* str = NULL;
    vector_t* pvec = create_vector(char*);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, "abcdefg");
    it_iter = vector_begin(pvec);

    _vector_iterator_get_value(it_iter, &str);
    assert_true(strcmp(str, "abcdefg") == 0);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_set_value
 */
void test__vector_iterator_set_value__invalid_iterator(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_set_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_set_value__vector_end(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    expect_assert_failure(_vector_iterator_set_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_set_value__invalid_value_buffer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_set_value(it_iter, NULL));

    vector_destroy(pvec);
}

void test__vector_iterator_set_value__successfully(void** state)
{
    int value = 0;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, 100);
    it_iter = vector_begin(pvec);

    _vector_iterator_set_value(it_iter, &value);
    assert_int_equal(*(int*)vector_at(pvec, 0), 0);

    vector_destroy(pvec);
}

void test__vector_iterator_set_value__successfully_cstr(void** state)
{
    const char* str = "AAAAAAAAAAA";
    vector_t* pvec = create_vector(char*);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, "abcdefg");
    it_iter = vector_begin(pvec);

    _vector_iterator_set_value(it_iter, str);
    assert_true(strcmp(str, (char*)vector_at(pvec, 0)) == 0);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_get_pointer
 */
void test__vector_iterator_get_pointer__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_get_pointer(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer__vector_end(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    expect_assert_failure(_vector_iterator_get_pointer(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, 100);
    it_iter = vector_begin(pvec);

    assert_int_equal(*(int*)_vector_iterator_get_pointer(it_iter), 100);

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer__successfully_cstr(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, "abcdefg");
    it_iter = vector_begin(pvec);

    assert_true(strcmp("abcdefg", (char*)_vector_iterator_get_pointer(it_iter)) == 0);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_next
 */
void test__vector_iterator_next__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_next(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_next__invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_next(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_next__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_next;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_next = _vector_iterator_next(it_iter);

    assert_true(it_iter._t_pos._pc_corepos + pvec->_t_typeinfo._pt_type->_t_typesize == it_next._t_pos._pc_corepos);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_prev
 */
void test__vector_iterator_prev__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_prev(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_prev__invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_prev(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_prev__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_prev;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_prev = _vector_iterator_prev(it_iter);

    assert_true(it_iter._t_pos._pc_corepos - pvec->_t_typeinfo._pt_type->_t_typesize == it_prev._t_pos._pc_corepos);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_next_n
 */
void test__vector_iterator_next_n__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    expect_assert_failure(_vector_iterator_next_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__move_to_end_invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_next_n(it_iter, 20));

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__move_to_begin_invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    expect_assert_failure(_vector_iterator_next_n(it_iter, -20));

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__move_to_end_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_next_n;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_next_n = _vector_iterator_next_n(it_iter, 10);

    assert_true(it_iter._t_pos._pc_corepos + 10 * pvec->_t_typeinfo._pt_type->_t_typesize == it_next_n._t_pos._pc_corepos);

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__move_to_front_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_next_n;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_next_n = _vector_iterator_next_n(it_iter, -10);

    assert_true(it_iter._t_pos._pc_corepos - 10 * pvec->_t_typeinfo._pt_type->_t_typesize == it_next_n._t_pos._pc_corepos);

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__does_not_move_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_next_n;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_next_n = _vector_iterator_next_n(it_iter, 0);

    assert_true(it_iter._t_pos._pc_corepos == it_next_n._t_pos._pc_corepos);

    vector_destroy(pvec);
}

