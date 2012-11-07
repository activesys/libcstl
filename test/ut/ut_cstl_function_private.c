#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/chash_map.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/clist.h"
#include "cstl/cdeque.h"
#include "cstl/cslist.h"
#include "cstl/cmap.h"
#include "cstl/cset.h"
#include "cstl/chash_set.h"
#include "cstl/calgorithm.h"
#include "cstl/cfunctional.h"

#include "ut_def.h"
#include "ut_cstl_function_private.h"

UT_SUIT_DEFINATION(cstl_function_private, _fun_get_unary)

/*
 * test _fun_get_unary
 */
UT_CASE_DEFINATION(_fun_get_unary)
void test__fun_get_unary__invalid_iter(void** state)
{
    iterator_t it;

    it._t_iteratortype = 100;
    expect_assert_failure(_fun_get_unary(it, _LESS_FUN));
}

void test__fun_get_unary__invalid_type(void** state)
{
    deque_t* pdeq = create_deque(int);
    fun_unary_type_t uftype = 1000;

    deque_init(pdeq);
    expect_assert_failure(_fun_get_unary(deque_begin(pdeq), uftype));
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(char);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_negate_char);
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed char);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_char);
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(char);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(char);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(short);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_negate_short);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed short);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_short);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(short int);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(signed short int);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned short int);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(int);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_negate_int);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed int);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_int);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(signed);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(signed int);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_uint);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(long);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_negate_long);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed long);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_long);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(signed long int);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(signed long);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned long int);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_negate_float);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_float);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_negate_double);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == _fun_increase_double);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_negate_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__bool_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_unary_type_t uftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__bool_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_unary_type_t uftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__bool_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_unary_type_t uftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_logical_not_bool);
    deque_destroy(pdeq);
}

void test__fun_get_unary__bool_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_unary_type_t uftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), uftype) == fun_default_unary);
    deque_destroy(pdeq);
}

