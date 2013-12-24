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
    fun_type_t ftype = 1000;

    deque_init(pdeq);
    expect_assert_failure(_fun_get_unary(deque_begin(pdeq), ftype));
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(char);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_char);
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed char);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_char);
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(char);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__char_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(char);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uchar_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(short);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_short);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed short);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_short);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(short int);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__short_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(signed short int);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned short int);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ushort_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(int);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_int);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed int);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_int);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(signed);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__int_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(signed int);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_uint);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__uint_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(long);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_long);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed long);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_long);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(signed long int);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(signed long);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned long int);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_float);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_float);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__float_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(float);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_double);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_double);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__double_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(double);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_double_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(long double);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__cstl_bool_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__cstl_bool_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__cstl_bool_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_logical_not_cstl_bool);
    deque_destroy(pdeq);
}

void test__fun_get_unary__cstl_bool_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(bool_t);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

#ifndef _MSC_VER
void test__fun_get_unary__bool_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(_Bool);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__bool_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(_Bool);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__bool_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(_Bool);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_logical_not_bool);
    deque_destroy(pdeq);
}

void test__fun_get_unary__bool_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(_Bool);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_long_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(long long);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_negate_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_long_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(signed long long);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_long_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(signed long long int);
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__long_long_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(signed long long);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_long_NEGATE(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);
    fun_type_t ftype = _NEGATE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_long_INCREASE(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long int);
    fun_type_t ftype = _INCREASE_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == _fun_increase_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_long_LOGICAL_NOT(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long );
    fun_type_t ftype = _LOGICAL_NOT_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}

void test__fun_get_unary__ulong_long_RANDOM_NUMBER(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);
    fun_type_t ftype = _RANDOM_NUMBER_FUN;

    deque_init(pdeq);
    assert_true(_fun_get_unary(deque_begin(pdeq), ftype) == fun_default_unary);
    deque_destroy(pdeq);
}
#endif

/*
 * test _fun_get_binary
 */
UT_CASE_DEFINATION(_fun_get_binary)
void test__fun_get_binary__invalid_iter(void** state)
{
    iterator_t it;

    it._t_iteratortype = 100;
    expect_assert_failure(_fun_get_binary(it, _PLUS_FUN));
}

void test__fun_get_binary__invalid_type(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(_fun_get_binary(deque_begin(pdeq), 100));
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_PLUS(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_MINUS(void** state)
{
    deque_t* pdeq = create_deque(signed char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_LESS(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_GREATER(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_char);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__char_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_PLUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_MINUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_LESS(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_GREATER(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_uchar);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uchar_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(unsigned char);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_PLUS(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_MINUS(void** state)
{
    deque_t* pdeq = create_deque(short int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(signed short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(signed short int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_LESS(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_GREATER(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_short);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__short_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_PLUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_MINUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned short int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(unsigned short int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_LESS(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_GREATER(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_ushort);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ushort_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(unsigned short);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_PLUS(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_MINUS(void** state)
{
    deque_t* pdeq = create_deque(signed int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(signed);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_LESS(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_GREATER(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_int);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__int_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_PLUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_MINUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(unsigned);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_LESS(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_GREATER(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_uint);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__uint_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(unsigned int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_PLUS(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_MINUS(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(signed long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(signed long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_LESS(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_GREATER(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_PLUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_MINUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(unsigned long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_LESS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_GREATER(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_ulong);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(unsigned long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_PLUS(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_MINUS(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_LESS(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_GREATER(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_float);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__float_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(float);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_PLUS(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_MINUS(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_LESS(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_GREATER(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__double_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_PLUS(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_MINUS(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_LESS(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_GREATER(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_long_double);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_double_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(long double);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_PLUS(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_MINUS(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_cstr);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_cstr);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_LESS(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_cstr);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_cstr);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_GREATER(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_cstr);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_cstr);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstr_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(char*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_PLUS(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_MINUS(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_LESS(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_GREATER(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_logical_and_cstl_bool);
    deque_destroy(pdeq);
}

void test__fun_get_binary__cstl_bool_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(bool_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_logical_or_cstl_bool);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_PLUS(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_MINUS(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_vector);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_vector);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_LESS(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_vector);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_vector);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_GREATER(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_vector);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_vector);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__vector_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_PLUS(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_MINUS(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_deque);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_deque);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_LESS(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_deque);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_deque);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_GREATER(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_deque);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_deque);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__deque_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(deque_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_PLUS(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_MINUS(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_list);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_list);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_LESS(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_list);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_list);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_GREATER(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_list);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_list);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__list_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_PLUS(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_MINUS(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_slist);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_slist);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_LESS(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_slist);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_slist);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_GREATER(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_slist);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_slist);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__slist_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(slist_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_PLUS(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_MINUS(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_queue);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_queue);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_LESS(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_queue);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_queue);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_GREATER(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_queue);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_queue);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__queue_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(queue_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_PLUS(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_MINUS(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_stack);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_stack);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_LESS(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_stack);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_stack);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_GREATER(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_stack);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_stack);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__stack_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(stack_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_PLUS(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_MINUS(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_pair);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_pair);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_LESS(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_pair);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_pair);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_GREATER(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_pair);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_pair);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pair_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(pair_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_PLUS(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_MINUS(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_LESS(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_GREATER(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__set_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_PLUS(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_MINUS(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_LESS(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_GREATER(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__map_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_PLUS(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_MINUS(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_LESS(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_GREATER(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multiset_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_PLUS(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_MINUS(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_LESS(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_GREATER(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__multimap_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_PLUS(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_MINUS(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_hash_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_hash_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_LESS(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_hash_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_hash_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_GREATER(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_hash_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_hash_set);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_set_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(hash_set_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_PLUS(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_MINUS(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_hash_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_hash_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_LESS(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_hash_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_hash_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_GREATER(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_hash_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_hash_map);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_map_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_PLUS(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_MINUS(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_hash_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_hash_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_LESS(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_hash_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_hash_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_GREATER(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_hash_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_hash_multiset);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multiset_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(hash_multiset_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_PLUS(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_MINUS(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_hash_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_hash_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_LESS(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_hash_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_hash_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_GREATER(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_hash_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_hash_multimap);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__hash_multimap_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(hash_multimap_t<int, int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_PLUS(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_MINUS(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_LESS(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_GREATER(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__string_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(string_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

typedef struct _tag_test__fun_get_binary__user_define {
    int a;
    int b;
} _test__fun_get_binary__user_define_t;
static void _test__fun_get_binary__user_define_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = true;
}
void test__fun_get_binary__user_define_PLUS(void** state)
{
    deque_t* pdeq = NULL;

    type_register(_test__fun_get_binary__user_define_t, NULL, NULL, _test__fun_get_binary__user_define_less, NULL);
    pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_MINUS(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_LESS(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == _test__fun_get_binary__user_define_less);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_GREATER(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__user_define_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(_test__fun_get_binary__user_define_t);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

/* pointer */
void test__fun_get_binary__pointer_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(void*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_pointer);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pointer_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(void*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_pointer);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pointer_GREATER(void** state)
{
    deque_t* pdeq = create_deque(void*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_pointer);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pointer_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(void*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_pointer);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pointer_LESS(void** state)
{
    deque_t* pdeq = create_deque(void*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_pointer);
    deque_destroy(pdeq);
}

void test__fun_get_binary__pointer_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(void*);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_pointer);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_PLUS(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_MINUS(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_basic_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_basic_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_LESS(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_basic_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_basic_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_GREATER(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_basic_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_basic_string);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__basic_string_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(basic_string_t<int>);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

#ifndef _MSC_VER
void test__fun_get_binary__bool_PLUS(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_MINUS(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_LESS(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_GREATER(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_logical_and_bool);
    deque_destroy(pdeq);
}

void test__fun_get_binary__bool_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(_Bool);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_logical_or_bool);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_PLUS(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_MINUS(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(long long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(signed long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(signed long long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_LESS(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_GREATER(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_long_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__long_long_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_PLUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _PLUS_FUN) == fun_plus_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_MINUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MINUS_FUN) == fun_minus_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_MULTIPLIES(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MULTIPLIES_FUN) == fun_multiplies_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_DIVIDES(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _DIVIDES_FUN) == fun_divides_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_MODULUS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long int);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _MODULUS_FUN) == fun_modulus_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _EQUAL_FUN) == fun_equal_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_NOT_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _NOT_EQUAL_FUN) == fun_not_equal_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_LESS(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_FUN) == fun_less_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_LESS_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LESS_EQUAL_FUN) == fun_less_equal_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_GREATER(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_FUN) == fun_greater_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_GREATER_EQUAL(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _GREATER_EQUAL_FUN) == fun_greater_equal_ulong_long);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_LOGICAL_AND(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_AND_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}

void test__fun_get_binary__ulong_long_LOGICAL_OR(void** state)
{
    deque_t* pdeq = create_deque(unsigned long long);

    deque_init(pdeq);
    assert_true(_fun_get_binary(deque_begin(pdeq), _LOGICAL_OR_FUN) == fun_default_binary);
    deque_destroy(pdeq);
}
#endif
