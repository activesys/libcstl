#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_vector_aux.h"

UT_SUIT_DEFINATION(cstl_vector_aux, _vector_iterator_belong_to_vector)

/*
 * test _vector_iterator_belong_to_vector
 */
UT_CASE_DEFINATION(_vector_iterator_belong_to_vector)
void test__vector_iterator_belong_to_vector__null_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_belong_to_vector(NULL, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_different_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__less_than_begin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    assert_false(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__within_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    assert_true(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__end_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    assert_true(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__greater_than_end(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._t_pos._pc_corepos += pvec->_t_typeinfo._pt_type->_t_typesize;

    assert_false(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

/*
 * test _vector_same_type
 */
UT_CASE_DEFINATION(_vector_same_type)
void test__vector_same_type__null_first(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_vector_same_type(NULL, pvec));

    vector_destroy(pvec);
}

void test__vector_same_type__null_second(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_vector_same_type(pvec, NULL));

    vector_destroy(pvec);
}

void test__vector_same_type__not_same_type_name(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__not_same_type_pointer(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_init(pvec_first);
    vector_init(pvec_second);

    pvec_second->_t_typeinfo._pt_type = NULL;
    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__not_same_type_style(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_init(pvec_first);
    vector_init(pvec_second);

    pvec_second->_t_typeinfo._t_style = _TYPE_CSTL_BUILTIN;
    assert_false(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__same_type(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(int);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_true(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_type__same_type_duplicate_name(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(signed);
    vector_init(pvec_first);
    vector_init(pvec_second);

    assert_true(_vector_same_type(pvec_first, pvec_second));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

/*
 * test _vector_same_vector_iterator_type
 */
UT_CASE_DEFINATION(_vector_same_vector_iterator_type)
void test__vector_same_vector_iterator_type__null_vector(void** state)
{
    vector_iterator_t it_iter;

    expect_assert_failure(_vector_same_vector_iterator_type(NULL, it_iter));
}

void test__vector_same_vector_iterator_type__iterator_null_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter = _create_vector_iterator();

    vector_init(pvec);

    expect_assert_failure(_vector_same_vector_iterator_type(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_same_vector_iterator_type__iterator_not_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_same_vector_iterator_type(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_same_vector_iterator_type__iterator_not_random_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init(pvec);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_same_vector_iterator_type(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_same_vector_iterator_type__same(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(signed);
    vector_iterator_t it_iter;

    vector_init(pvec_first);
    vector_init(pvec_second);
    it_iter = vector_begin(pvec_second);

    assert_true(_vector_same_vector_iterator_type(pvec_first, it_iter));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

void test__vector_same_vector_iterator_type__not_same(void** state)
{
    vector_t* pvec_first = create_vector(int);
    vector_t* pvec_second = create_vector(double);
    vector_iterator_t it_iter;

    vector_init(pvec_first);
    vector_init(pvec_second);
    it_iter = vector_begin(pvec_second);

    assert_false(_vector_same_vector_iterator_type(pvec_first, it_iter));

    vector_destroy(pvec_first);
    vector_destroy(pvec_second);
}

