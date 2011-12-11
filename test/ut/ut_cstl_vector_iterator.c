#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_vector_iterator.h"

UT_SUIT_DEFINATION(cstl_vector_iterator, _create_vector_iterator)

/*
 * test _create_vector_iterator
 */
UT_CASE_DEFINATION(_create_vector_iterator)
void test__create_vector_iterator__successfully(void** state)
{
    vector_iterator_t it_iter = _create_vector_iterator();
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _VECTOR_CONTAINER);
    assert_true(it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR);
    assert_true(it_iter._t_pos._pby_corepos == NULL);
}

/*
 * test _vector_iterator_equal
 */
UT_CASE_DEFINATION(_vector_iterator_equal)
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

    it_first._t_iteratortype = _INPUT_ITERATOR;

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
    it_first._t_pos._pby_corepos = NULL;

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
    it_second._t_pos._pby_corepos = NULL;

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
UT_CASE_DEFINATION(_vector_iterator_less)
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

    it_first._t_iteratortype = _INPUT_ITERATOR;

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
    it_first._t_pos._pby_corepos = NULL;

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
    it_second._t_pos._pby_corepos = NULL;

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
UT_CASE_DEFINATION(_vector_iterator_before)
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

    it_first._t_iteratortype = _INPUT_ITERATOR;

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
    it_first._t_pos._pby_corepos = NULL;

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
    it_second._t_pos._pby_corepos = NULL;

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
UT_CASE_DEFINATION(_vector_iterator_get_value)
void test__vector_iterator_get_value__invalid_iterator(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_get_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_get_value__invalid_iterator_container_type(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_get_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_get_value__invalid_iterator_iterator_type(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_get_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_get_value__invalid_iterator_container_pointer(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

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
UT_CASE_DEFINATION(_vector_iterator_set_value)
void test__vector_iterator_set_value__invalid_iterator(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_set_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_set_value__invalid_iterator_container_type(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_set_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_set_value__invalid_iterator_iterator_type(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_set_value(it_iter, &value));

    vector_destroy(pvec);
}

void test__vector_iterator_set_value__invalid_iterator_container_pointer(void** state)
{
    int value;
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

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
UT_CASE_DEFINATION(_vector_iterator_get_pointer)
void test__vector_iterator_get_pointer__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_get_pointer(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_get_pointer(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_get_pointer(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer__invalid_iterator_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

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
 * test _vector_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_vector_iterator_get_pointer_ignore_cstr)
void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_get_pointer_ignore_cstr(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_get_pointer_ignore_cstr(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_get_pointer_ignore_cstr(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

    expect_assert_failure(_vector_iterator_get_pointer_ignore_cstr(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer_ignore_cstr__vector_end(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    expect_assert_failure(_vector_iterator_get_pointer_ignore_cstr(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer_ignore_cstr__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, 100);
    it_iter = vector_begin(pvec);

    assert_int_equal(*(int*)_vector_iterator_get_pointer_ignore_cstr(it_iter), 100);

    vector_destroy(pvec);
}

void test__vector_iterator_get_pointer_ignore_cstr__successfully_cstr(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, "abcdefg");
    it_iter = vector_begin(pvec);

    assert_true(strcmp("abcdefg", string_c_str(_vector_iterator_get_pointer_ignore_cstr(it_iter))) == 0);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_next
 */
UT_CASE_DEFINATION(_vector_iterator_next)
void test__vector_iterator_next__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_next(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_next__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_next(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_next__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_next(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_next__invalid_iterator_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

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

    assert_true(it_iter._t_pos._pby_corepos + pvec->_t_typeinfo._pt_type->_t_typesize == it_next._t_pos._pby_corepos);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_prev
 */
UT_CASE_DEFINATION(_vector_iterator_prev)
void test__vector_iterator_prev__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_prev(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_prev__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_prev(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_prev__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_prev(it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_prev__invalid_iterator_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._pt_container = NULL;

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

    assert_true(it_iter._t_pos._pby_corepos - pvec->_t_typeinfo._pt_type->_t_typesize == it_prev._t_pos._pby_corepos);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_next_n
 */
UT_CASE_DEFINATION(_vector_iterator_next_n)
void test__vector_iterator_next_n__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_next_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_next_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_next_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_next_n__invalid_iterator_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

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

    assert_true(it_iter._t_pos._pby_corepos + 10 * pvec->_t_typeinfo._pt_type->_t_typesize == it_next_n._t_pos._pby_corepos);

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

    assert_true(it_iter._t_pos._pby_corepos - 10 * pvec->_t_typeinfo._pt_type->_t_typesize == it_next_n._t_pos._pby_corepos);

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

    assert_true(it_iter._t_pos._pby_corepos == it_next_n._t_pos._pby_corepos);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_prev_n
 */
UT_CASE_DEFINATION(_vector_iterator_prev_n)
void test__vector_iterator_prev_n__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_prev_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_prev_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_prev_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__invalid_iterator_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._pt_container = NULL;

    expect_assert_failure(_vector_iterator_prev_n(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__move_to_end_invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_prev_n(it_iter, -20));

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__move_to_begin_invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    expect_assert_failure(_vector_iterator_prev_n(it_iter, 20));

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__move_to_end_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_prev_n;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_prev_n = _vector_iterator_prev_n(it_iter, -10);

    assert_true(it_iter._t_pos._pby_corepos + 10 * pvec->_t_typeinfo._pt_type->_t_typesize == it_prev_n._t_pos._pby_corepos);

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__move_to_front_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_prev_n;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_prev_n = _vector_iterator_prev_n(it_iter, 10);

    assert_true(it_iter._t_pos._pby_corepos - 10 * pvec->_t_typeinfo._pt_type->_t_typesize == it_prev_n._t_pos._pby_corepos);

    vector_destroy(pvec);
}

void test__vector_iterator_prev_n__does_not_move_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    vector_iterator_t it_prev_n;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_prev_n = _vector_iterator_prev_n(it_iter, 0);

    assert_true(it_iter._t_pos._pby_corepos == it_prev_n._t_pos._pby_corepos);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_at
 */
UT_CASE_DEFINATION(_vector_iterator_at)
void test__vector_iterator_at__invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_at(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_at__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_at(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_at__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_at(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_at__invalid_iterator_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

    expect_assert_failure(_vector_iterator_at(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_at__move_to_end_invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_at(it_iter, 20));

    vector_destroy(pvec);
}

void test__vector_iterator_at__move_to_begin_invalid_returned_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    expect_assert_failure(_vector_iterator_at(it_iter, -20));

    vector_destroy(pvec);
}

void test__vector_iterator_at__end_invalid_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_elem(pvec, 10, 100);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_at(it_iter, 10));

    vector_destroy(pvec);
}

void test__vector_iterator_at__move_to_end_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    it_iter = vector_begin(pvec);

    assert_int_equal(*(int*)_vector_iterator_at(it_iter, 5), 5);

    vector_destroy(pvec);
}

void test__vector_iterator_at__move_to_end_cstr_successfully(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_iterator_t it_iter;
    char* s_at = NULL;

    vector_init(pvec);
    vector_push_back(pvec, "abc");
    vector_push_back(pvec, "def");
    vector_push_back(pvec, "hij");
    vector_push_back(pvec, "klm");
    vector_push_back(pvec, "nop");
    it_iter = vector_begin(pvec);
    s_at = (char*)_vector_iterator_at(it_iter, 3);

    assert_true(strcmp(s_at, "klm") == 0);

    vector_destroy(pvec);
}

void test__vector_iterator_at__move_to_front_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0;i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    it_iter = vector_end(pvec);

    assert_int_equal(*(int*)_vector_iterator_at(it_iter, -2), 8);

    vector_destroy(pvec);
}

void test__vector_iterator_at__move_to_front_cstr_successfully(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_iterator_t it_iter;
    char* s_at = NULL;

    vector_init(pvec);
    vector_push_back(pvec, "abc");
    vector_push_back(pvec, "def");
    vector_push_back(pvec, "hij");
    vector_push_back(pvec, "klm");
    vector_push_back(pvec, "nop");
    it_iter = vector_end(pvec);
    s_at = (char*)_vector_iterator_at(it_iter, -3);

    assert_true(strcmp(s_at, "hij") == 0);

    vector_destroy(pvec);
}

void test__vector_iterator_at__does_not_move_successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;
    int i = 0;

    vector_init(pvec);
    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec, i);
    }
    it_iter = _vector_iterator_next_n(vector_begin(pvec), 4);

    assert_int_equal(*(int*)_vector_iterator_at(it_iter, 0), 4);

    vector_destroy(pvec);
}

void test__vector_iterator_at__does_not_move_cstr_successfully(void** state)
{
    vector_t* pvec = create_vector(char*);
    vector_iterator_t it_iter;
    char* s_at = NULL;

    vector_init(pvec);
    vector_push_back(pvec, "abc");
    vector_push_back(pvec, "def");
    vector_push_back(pvec, "hij");
    vector_push_back(pvec, "klm");
    vector_push_back(pvec, "nop");
    it_iter = vector_begin(pvec);
    s_at = (char*)_vector_iterator_at(it_iter, 0);

    assert_true(strcmp(s_at, "abc") == 0);

    vector_destroy(pvec);
}

/*
 * test _vector_iterator_minus
 */
UT_CASE_DEFINATION(_vector_iterator_minus)
void test__vector_iterator_minus__different_container_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_minus(it_first, it_second));
}

void test__vector_iterator_minus__different_iterator_type(void** state)
{
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_minus(it_first, it_second));
}

void test__vector_iterator_minus__different_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init(pvec);

    it_first = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_minus(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_minus__first_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_first._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_minus(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_minus__second_is_not_belong_to_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = it_second = vector_begin(pvec);
    it_second._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_iterator_minus(it_first, it_second));

    vector_destroy(pvec);
}

void test__vector_iterator_minus__first_less_then_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_second = vector_end(pvec);

    assert_int_equal(_vector_iterator_minus(it_first, it_second), -10);

    vector_destroy(pvec);
}

void test__vector_iterator_minus__first_greater_then_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_end(pvec);
    it_second = vector_begin(pvec);

    assert_int_equal(_vector_iterator_minus(it_first, it_second), 10);

    vector_destroy(pvec);
}

void test__vector_iterator_minus__first_equal_to_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_first = _create_vector_iterator();
    vector_iterator_t it_second = _create_vector_iterator();

    vector_init_n(pvec, 10);

    it_first = vector_begin(pvec);
    it_second = vector_begin(pvec);

    assert_int_equal(_vector_iterator_minus(it_first, it_second), 0);

    vector_destroy(pvec);
}

