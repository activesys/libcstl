#ifndef _UT_CSTL_FUNCTION_PRIVATE_H_
#define _UT_CSTL_FUNCTION_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_function_private)

/*
 * test _fun_get_unary
 */
UT_CASE_DECLARATION(_fun_get_unary)
void test__fun_get_unary__invalid_iter(void** state);
void test__fun_get_unary__invalid_type(void** state);
void test__fun_get_unary__char_NEGATE(void** state);
void test__fun_get_unary__char_INCREASE(void** state);
void test__fun_get_unary__char_LOGICAL_NOT(void** state);
void test__fun_get_unary__char_RANDOM_NUMBER(void** state);
void test__fun_get_unary__uchar_NEGATE(void** state);
void test__fun_get_unary__uchar_LOGICAL_NOT(void** state);
void test__fun_get_unary__uchar_INCREASE(void** state);
void test__fun_get_unary__uchar_RANDOM_NUMBER(void** state);
void test__fun_get_unary__short_NEGATE(void** state);
void test__fun_get_unary__short_INCREASE(void** state);
void test__fun_get_unary__short_LOGICAL_NOT(void** state);
void test__fun_get_unary__short_RANDOM_NUMBER(void** state);
void test__fun_get_unary__ushort_NEGATE(void** state);
void test__fun_get_unary__ushort_LOGICAL_NOT(void** state);
void test__fun_get_unary__ushort_INCREASE(void** state);
void test__fun_get_unary__ushort_RANDOM_NUMBER(void** state);
void test__fun_get_unary__int_NEGATE(void** state);
void test__fun_get_unary__int_INCREASE(void** state);
void test__fun_get_unary__int_LOGICAL_NOT(void** state);
void test__fun_get_unary__int_RANDOM_NUMBER(void** state);
void test__fun_get_unary__uint_NEGATE(void** state);
void test__fun_get_unary__uint_LOGICAL_NOT(void** state);
void test__fun_get_unary__uint_INCREASE(void** state);
void test__fun_get_unary__uint_RANDOM_NUMBER(void** state);
void test__fun_get_unary__long_NEGATE(void** state);
void test__fun_get_unary__long_INCREASE(void** state);
void test__fun_get_unary__long_LOGICAL_NOT(void** state);
void test__fun_get_unary__long_RANDOM_NUMBER(void** state);
void test__fun_get_unary__ulong_NEGATE(void** state);
void test__fun_get_unary__ulong_LOGICAL_NOT(void** state);
void test__fun_get_unary__ulong_INCREASE(void** state);
void test__fun_get_unary__ulong_RANDOM_NUMBER(void** state);
void test__fun_get_unary__float_NEGATE(void** state);
void test__fun_get_unary__float_LOGICAL_NOT(void** state);
void test__fun_get_unary__float_INCREASE(void** state);
void test__fun_get_unary__float_RANDOM_NUMBER(void** state);
void test__fun_get_unary__double_NEGATE(void** state);
void test__fun_get_unary__double_LOGICAL_NOT(void** state);
void test__fun_get_unary__double_INCREASE(void** state);
void test__fun_get_unary__double_RANDOM_NUMBER(void** state);
void test__fun_get_unary__long_double_NEGATE(void** state);
void test__fun_get_unary__long_double_LOGICAL_NOT(void** state);
void test__fun_get_unary__long_double_INCREASE(void** state);
void test__fun_get_unary__long_double_RANDOM_NUMBER(void** state);
void test__fun_get_unary__bool_NEGATE(void** state);
void test__fun_get_unary__bool_LOGICAL_NOT(void** state);
void test__fun_get_unary__bool_INCREASE(void** state);
void test__fun_get_unary__bool_RANDOM_NUMBER(void** state);

#define UT_CSTL_FUNCTION_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_function_private, test__fun_get_unary__invalid_iter),\
    UT_CASE(test__fun_get_unary__invalid_type),\
    UT_CASE(test__fun_get_unary__char_NEGATE),\
    UT_CASE(test__fun_get_unary__char_INCREASE),\
    UT_CASE(test__fun_get_unary__char_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__char_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__uchar_NEGATE),\
    UT_CASE(test__fun_get_unary__uchar_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__uchar_INCREASE),\
    UT_CASE(test__fun_get_unary__uchar_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__short_NEGATE),\
    UT_CASE(test__fun_get_unary__short_INCREASE),\
    UT_CASE(test__fun_get_unary__short_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__short_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__ushort_NEGATE),\
    UT_CASE(test__fun_get_unary__ushort_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__ushort_INCREASE),\
    UT_CASE(test__fun_get_unary__ushort_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__int_NEGATE),\
    UT_CASE(test__fun_get_unary__int_INCREASE),\
    UT_CASE(test__fun_get_unary__int_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__int_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__uint_NEGATE),\
    UT_CASE(test__fun_get_unary__uint_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__uint_INCREASE),\
    UT_CASE(test__fun_get_unary__uint_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__long_NEGATE),\
    UT_CASE(test__fun_get_unary__long_INCREASE),\
    UT_CASE(test__fun_get_unary__long_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__long_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__ulong_NEGATE),\
    UT_CASE(test__fun_get_unary__ulong_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__ulong_INCREASE),\
    UT_CASE(test__fun_get_unary__ulong_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__float_NEGATE),\
    UT_CASE(test__fun_get_unary__float_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__float_INCREASE),\
    UT_CASE(test__fun_get_unary__float_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__double_NEGATE),\
    UT_CASE(test__fun_get_unary__double_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__double_INCREASE),\
    UT_CASE(test__fun_get_unary__double_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__long_double_NEGATE),\
    UT_CASE(test__fun_get_unary__long_double_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__long_double_INCREASE),\
    UT_CASE(test__fun_get_unary__long_double_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__bool_NEGATE),\
    UT_CASE(test__fun_get_unary__bool_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__bool_INCREASE),\
    UT_CASE(test__fun_get_unary__bool_RANDOM_NUMBER)

#endif /* _UT_CSTL_FUNCTION_PRIVATE_H_ */

