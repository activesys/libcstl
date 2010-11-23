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

