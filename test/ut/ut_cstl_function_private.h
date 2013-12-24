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
void test__fun_get_unary__cstl_bool_NEGATE(void** state);
void test__fun_get_unary__cstl_bool_LOGICAL_NOT(void** state);
void test__fun_get_unary__cstl_bool_INCREASE(void** state);
void test__fun_get_unary__cstl_bool_RANDOM_NUMBER(void** state);
#ifndef _MSC_VER
void test__fun_get_unary__bool_NEGATE(void** state);
void test__fun_get_unary__bool_LOGICAL_NOT(void** state);
void test__fun_get_unary__bool_INCREASE(void** state);
void test__fun_get_unary__bool_RANDOM_NUMBER(void** state);
void test__fun_get_unary__long_long_NEGATE(void** state);
void test__fun_get_unary__long_long_INCREASE(void** state);
void test__fun_get_unary__long_long_LOGICAL_NOT(void** state);
void test__fun_get_unary__long_long_RANDOM_NUMBER(void** state);
void test__fun_get_unary__ulong_long_NEGATE(void** state);
void test__fun_get_unary__ulong_long_LOGICAL_NOT(void** state);
void test__fun_get_unary__ulong_long_INCREASE(void** state);
void test__fun_get_unary__ulong_long_RANDOM_NUMBER(void** state);
#endif
/*
 * test _fun_get_binary
 */
UT_CASE_DECLARATION(_fun_get_binary)
void test__fun_get_binary__invalid_iter(void** state);
void test__fun_get_binary__invalid_type(void** state);
void test__fun_get_binary__char_PLUS(void** state);
void test__fun_get_binary__char_MINUS(void** state);
void test__fun_get_binary__char_MULTIPLIES(void** state);
void test__fun_get_binary__char_DIVIDES(void** state);
void test__fun_get_binary__char_MODULUS(void** state);
void test__fun_get_binary__char_EQUAL(void** state);
void test__fun_get_binary__char_NOT_EQUAL(void** state);
void test__fun_get_binary__char_LESS(void** state);
void test__fun_get_binary__char_LESS_EQUAL(void** state);
void test__fun_get_binary__char_GREATER(void** state);
void test__fun_get_binary__char_GREATER_EQUAL(void** state);
void test__fun_get_binary__char_LOGICAL_AND(void** state);
void test__fun_get_binary__char_LOGICAL_OR(void** state);
void test__fun_get_binary__uchar_PLUS(void** state);
void test__fun_get_binary__uchar_MINUS(void** state);
void test__fun_get_binary__uchar_MULTIPLIES(void** state);
void test__fun_get_binary__uchar_DIVIDES(void** state);
void test__fun_get_binary__uchar_MODULUS(void** state);
void test__fun_get_binary__uchar_EQUAL(void** state);
void test__fun_get_binary__uchar_NOT_EQUAL(void** state);
void test__fun_get_binary__uchar_LESS(void** state);
void test__fun_get_binary__uchar_LESS_EQUAL(void** state);
void test__fun_get_binary__uchar_GREATER(void** state);
void test__fun_get_binary__uchar_GREATER_EQUAL(void** state);
void test__fun_get_binary__uchar_LOGICAL_AND(void** state);
void test__fun_get_binary__uchar_LOGICAL_OR(void** state);
void test__fun_get_binary__short_PLUS(void** state);
void test__fun_get_binary__short_MINUS(void** state);
void test__fun_get_binary__short_MULTIPLIES(void** state);
void test__fun_get_binary__short_DIVIDES(void** state);
void test__fun_get_binary__short_MODULUS(void** state);
void test__fun_get_binary__short_EQUAL(void** state);
void test__fun_get_binary__short_NOT_EQUAL(void** state);
void test__fun_get_binary__short_LESS(void** state);
void test__fun_get_binary__short_LESS_EQUAL(void** state);
void test__fun_get_binary__short_GREATER(void** state);
void test__fun_get_binary__short_GREATER_EQUAL(void** state);
void test__fun_get_binary__short_LOGICAL_AND(void** state);
void test__fun_get_binary__short_LOGICAL_OR(void** state);
void test__fun_get_binary__ushort_PLUS(void** state);
void test__fun_get_binary__ushort_MINUS(void** state);
void test__fun_get_binary__ushort_MULTIPLIES(void** state);
void test__fun_get_binary__ushort_DIVIDES(void** state);
void test__fun_get_binary__ushort_MODULUS(void** state);
void test__fun_get_binary__ushort_EQUAL(void** state);
void test__fun_get_binary__ushort_NOT_EQUAL(void** state);
void test__fun_get_binary__ushort_LESS(void** state);
void test__fun_get_binary__ushort_LESS_EQUAL(void** state);
void test__fun_get_binary__ushort_GREATER(void** state);
void test__fun_get_binary__ushort_GREATER_EQUAL(void** state);
void test__fun_get_binary__ushort_LOGICAL_AND(void** state);
void test__fun_get_binary__ushort_LOGICAL_OR(void** state);
void test__fun_get_binary__int_PLUS(void** state);
void test__fun_get_binary__int_MINUS(void** state);
void test__fun_get_binary__int_MULTIPLIES(void** state);
void test__fun_get_binary__int_DIVIDES(void** state);
void test__fun_get_binary__int_MODULUS(void** state);
void test__fun_get_binary__int_EQUAL(void** state);
void test__fun_get_binary__int_NOT_EQUAL(void** state);
void test__fun_get_binary__int_LESS(void** state);
void test__fun_get_binary__int_LESS_EQUAL(void** state);
void test__fun_get_binary__int_GREATER(void** state);
void test__fun_get_binary__int_GREATER_EQUAL(void** state);
void test__fun_get_binary__int_LOGICAL_AND(void** state);
void test__fun_get_binary__int_LOGICAL_OR(void** state);
void test__fun_get_binary__uint_PLUS(void** state);
void test__fun_get_binary__uint_MINUS(void** state);
void test__fun_get_binary__uint_MULTIPLIES(void** state);
void test__fun_get_binary__uint_DIVIDES(void** state);
void test__fun_get_binary__uint_MODULUS(void** state);
void test__fun_get_binary__uint_EQUAL(void** state);
void test__fun_get_binary__uint_NOT_EQUAL(void** state);
void test__fun_get_binary__uint_LESS(void** state);
void test__fun_get_binary__uint_LESS_EQUAL(void** state);
void test__fun_get_binary__uint_GREATER(void** state);
void test__fun_get_binary__uint_GREATER_EQUAL(void** state);
void test__fun_get_binary__uint_LOGICAL_AND(void** state);
void test__fun_get_binary__uint_LOGICAL_OR(void** state);
void test__fun_get_binary__long_PLUS(void** state);
void test__fun_get_binary__long_MINUS(void** state);
void test__fun_get_binary__long_MULTIPLIES(void** state);
void test__fun_get_binary__long_DIVIDES(void** state);
void test__fun_get_binary__long_MODULUS(void** state);
void test__fun_get_binary__long_EQUAL(void** state);
void test__fun_get_binary__long_NOT_EQUAL(void** state);
void test__fun_get_binary__long_LESS(void** state);
void test__fun_get_binary__long_LESS_EQUAL(void** state);
void test__fun_get_binary__long_GREATER(void** state);
void test__fun_get_binary__long_GREATER_EQUAL(void** state);
void test__fun_get_binary__long_LOGICAL_AND(void** state);
void test__fun_get_binary__long_LOGICAL_OR(void** state);
void test__fun_get_binary__ulong_PLUS(void** state);
void test__fun_get_binary__ulong_MINUS(void** state);
void test__fun_get_binary__ulong_MULTIPLIES(void** state);
void test__fun_get_binary__ulong_DIVIDES(void** state);
void test__fun_get_binary__ulong_MODULUS(void** state);
void test__fun_get_binary__ulong_EQUAL(void** state);
void test__fun_get_binary__ulong_NOT_EQUAL(void** state);
void test__fun_get_binary__ulong_LESS(void** state);
void test__fun_get_binary__ulong_LESS_EQUAL(void** state);
void test__fun_get_binary__ulong_GREATER(void** state);
void test__fun_get_binary__ulong_GREATER_EQUAL(void** state);
void test__fun_get_binary__ulong_LOGICAL_AND(void** state);
void test__fun_get_binary__ulong_LOGICAL_OR(void** state);
void test__fun_get_binary__float_PLUS(void** state);
void test__fun_get_binary__float_MINUS(void** state);
void test__fun_get_binary__float_MULTIPLIES(void** state);
void test__fun_get_binary__float_DIVIDES(void** state);
void test__fun_get_binary__float_MODULUS(void** state);
void test__fun_get_binary__float_EQUAL(void** state);
void test__fun_get_binary__float_NOT_EQUAL(void** state);
void test__fun_get_binary__float_LESS(void** state);
void test__fun_get_binary__float_LESS_EQUAL(void** state);
void test__fun_get_binary__float_GREATER(void** state);
void test__fun_get_binary__float_GREATER_EQUAL(void** state);
void test__fun_get_binary__float_LOGICAL_AND(void** state);
void test__fun_get_binary__float_LOGICAL_OR(void** state);
void test__fun_get_binary__double_PLUS(void** state);
void test__fun_get_binary__double_MINUS(void** state);
void test__fun_get_binary__double_MULTIPLIES(void** state);
void test__fun_get_binary__double_DIVIDES(void** state);
void test__fun_get_binary__double_MODULUS(void** state);
void test__fun_get_binary__double_EQUAL(void** state);
void test__fun_get_binary__double_NOT_EQUAL(void** state);
void test__fun_get_binary__double_LESS(void** state);
void test__fun_get_binary__double_LESS_EQUAL(void** state);
void test__fun_get_binary__double_GREATER(void** state);
void test__fun_get_binary__double_GREATER_EQUAL(void** state);
void test__fun_get_binary__double_LOGICAL_AND(void** state);
void test__fun_get_binary__double_LOGICAL_OR(void** state);
void test__fun_get_binary__long_double_PLUS(void** state);
void test__fun_get_binary__long_double_MINUS(void** state);
void test__fun_get_binary__long_double_MULTIPLIES(void** state);
void test__fun_get_binary__long_double_DIVIDES(void** state);
void test__fun_get_binary__long_double_MODULUS(void** state);
void test__fun_get_binary__long_double_EQUAL(void** state);
void test__fun_get_binary__long_double_NOT_EQUAL(void** state);
void test__fun_get_binary__long_double_LESS(void** state);
void test__fun_get_binary__long_double_LESS_EQUAL(void** state);
void test__fun_get_binary__long_double_GREATER(void** state);
void test__fun_get_binary__long_double_GREATER_EQUAL(void** state);
void test__fun_get_binary__long_double_LOGICAL_AND(void** state);
void test__fun_get_binary__long_double_LOGICAL_OR(void** state);
void test__fun_get_binary__cstr_PLUS(void** state);
void test__fun_get_binary__cstr_MINUS(void** state);
void test__fun_get_binary__cstr_MULTIPLIES(void** state);
void test__fun_get_binary__cstr_DIVIDES(void** state);
void test__fun_get_binary__cstr_MODULUS(void** state);
void test__fun_get_binary__cstr_EQUAL(void** state);
void test__fun_get_binary__cstr_NOT_EQUAL(void** state);
void test__fun_get_binary__cstr_LESS(void** state);
void test__fun_get_binary__cstr_LESS_EQUAL(void** state);
void test__fun_get_binary__cstr_GREATER(void** state);
void test__fun_get_binary__cstr_GREATER_EQUAL(void** state);
void test__fun_get_binary__cstr_LOGICAL_AND(void** state);
void test__fun_get_binary__cstr_LOGICAL_OR(void** state);
void test__fun_get_binary__cstl_bool_PLUS(void** state);
void test__fun_get_binary__cstl_bool_MINUS(void** state);
void test__fun_get_binary__cstl_bool_MULTIPLIES(void** state);
void test__fun_get_binary__cstl_bool_DIVIDES(void** state);
void test__fun_get_binary__cstl_bool_MODULUS(void** state);
void test__fun_get_binary__cstl_bool_EQUAL(void** state);
void test__fun_get_binary__cstl_bool_NOT_EQUAL(void** state);
void test__fun_get_binary__cstl_bool_LESS(void** state);
void test__fun_get_binary__cstl_bool_LESS_EQUAL(void** state);
void test__fun_get_binary__cstl_bool_GREATER(void** state);
void test__fun_get_binary__cstl_bool_GREATER_EQUAL(void** state);
void test__fun_get_binary__cstl_bool_LOGICAL_AND(void** state);
void test__fun_get_binary__cstl_bool_LOGICAL_OR(void** state);
void test__fun_get_binary__vector_PLUS(void** state);
void test__fun_get_binary__vector_MINUS(void** state);
void test__fun_get_binary__vector_MULTIPLIES(void** state);
void test__fun_get_binary__vector_DIVIDES(void** state);
void test__fun_get_binary__vector_MODULUS(void** state);
void test__fun_get_binary__vector_EQUAL(void** state);
void test__fun_get_binary__vector_NOT_EQUAL(void** state);
void test__fun_get_binary__vector_LESS(void** state);
void test__fun_get_binary__vector_LESS_EQUAL(void** state);
void test__fun_get_binary__vector_GREATER(void** state);
void test__fun_get_binary__vector_GREATER_EQUAL(void** state);
void test__fun_get_binary__vector_LOGICAL_AND(void** state);
void test__fun_get_binary__vector_LOGICAL_OR(void** state);
void test__fun_get_binary__deque_PLUS(void** state);
void test__fun_get_binary__deque_MINUS(void** state);
void test__fun_get_binary__deque_MULTIPLIES(void** state);
void test__fun_get_binary__deque_DIVIDES(void** state);
void test__fun_get_binary__deque_MODULUS(void** state);
void test__fun_get_binary__deque_EQUAL(void** state);
void test__fun_get_binary__deque_NOT_EQUAL(void** state);
void test__fun_get_binary__deque_LESS(void** state);
void test__fun_get_binary__deque_LESS_EQUAL(void** state);
void test__fun_get_binary__deque_GREATER(void** state);
void test__fun_get_binary__deque_GREATER_EQUAL(void** state);
void test__fun_get_binary__deque_LOGICAL_AND(void** state);
void test__fun_get_binary__deque_LOGICAL_OR(void** state);
void test__fun_get_binary__list_PLUS(void** state);
void test__fun_get_binary__list_MINUS(void** state);
void test__fun_get_binary__list_MULTIPLIES(void** state);
void test__fun_get_binary__list_DIVIDES(void** state);
void test__fun_get_binary__list_MODULUS(void** state);
void test__fun_get_binary__list_EQUAL(void** state);
void test__fun_get_binary__list_NOT_EQUAL(void** state);
void test__fun_get_binary__list_LESS(void** state);
void test__fun_get_binary__list_LESS_EQUAL(void** state);
void test__fun_get_binary__list_GREATER(void** state);
void test__fun_get_binary__list_GREATER_EQUAL(void** state);
void test__fun_get_binary__list_LOGICAL_AND(void** state);
void test__fun_get_binary__list_LOGICAL_OR(void** state);
void test__fun_get_binary__slist_PLUS(void** state);
void test__fun_get_binary__slist_MINUS(void** state);
void test__fun_get_binary__slist_MULTIPLIES(void** state);
void test__fun_get_binary__slist_DIVIDES(void** state);
void test__fun_get_binary__slist_MODULUS(void** state);
void test__fun_get_binary__slist_EQUAL(void** state);
void test__fun_get_binary__slist_NOT_EQUAL(void** state);
void test__fun_get_binary__slist_LESS(void** state);
void test__fun_get_binary__slist_LESS_EQUAL(void** state);
void test__fun_get_binary__slist_GREATER(void** state);
void test__fun_get_binary__slist_GREATER_EQUAL(void** state);
void test__fun_get_binary__slist_LOGICAL_AND(void** state);
void test__fun_get_binary__slist_LOGICAL_OR(void** state);
void test__fun_get_binary__queue_PLUS(void** state);
void test__fun_get_binary__queue_MINUS(void** state);
void test__fun_get_binary__queue_MULTIPLIES(void** state);
void test__fun_get_binary__queue_DIVIDES(void** state);
void test__fun_get_binary__queue_MODULUS(void** state);
void test__fun_get_binary__queue_EQUAL(void** state);
void test__fun_get_binary__queue_NOT_EQUAL(void** state);
void test__fun_get_binary__queue_LESS(void** state);
void test__fun_get_binary__queue_LESS_EQUAL(void** state);
void test__fun_get_binary__queue_GREATER(void** state);
void test__fun_get_binary__queue_GREATER_EQUAL(void** state);
void test__fun_get_binary__queue_LOGICAL_AND(void** state);
void test__fun_get_binary__queue_LOGICAL_OR(void** state);
void test__fun_get_binary__stack_PLUS(void** state);
void test__fun_get_binary__stack_MINUS(void** state);
void test__fun_get_binary__stack_MULTIPLIES(void** state);
void test__fun_get_binary__stack_DIVIDES(void** state);
void test__fun_get_binary__stack_MODULUS(void** state);
void test__fun_get_binary__stack_EQUAL(void** state);
void test__fun_get_binary__stack_NOT_EQUAL(void** state);
void test__fun_get_binary__stack_LESS(void** state);
void test__fun_get_binary__stack_LESS_EQUAL(void** state);
void test__fun_get_binary__stack_GREATER(void** state);
void test__fun_get_binary__stack_GREATER_EQUAL(void** state);
void test__fun_get_binary__stack_LOGICAL_AND(void** state);
void test__fun_get_binary__stack_LOGICAL_OR(void** state);
void test__fun_get_binary__pair_PLUS(void** state);
void test__fun_get_binary__pair_MINUS(void** state);
void test__fun_get_binary__pair_MULTIPLIES(void** state);
void test__fun_get_binary__pair_DIVIDES(void** state);
void test__fun_get_binary__pair_MODULUS(void** state);
void test__fun_get_binary__pair_EQUAL(void** state);
void test__fun_get_binary__pair_NOT_EQUAL(void** state);
void test__fun_get_binary__pair_LESS(void** state);
void test__fun_get_binary__pair_LESS_EQUAL(void** state);
void test__fun_get_binary__pair_GREATER(void** state);
void test__fun_get_binary__pair_GREATER_EQUAL(void** state);
void test__fun_get_binary__pair_LOGICAL_AND(void** state);
void test__fun_get_binary__pair_LOGICAL_OR(void** state);
void test__fun_get_binary__set_PLUS(void** state);
void test__fun_get_binary__set_MINUS(void** state);
void test__fun_get_binary__set_MULTIPLIES(void** state);
void test__fun_get_binary__set_DIVIDES(void** state);
void test__fun_get_binary__set_MODULUS(void** state);
void test__fun_get_binary__set_EQUAL(void** state);
void test__fun_get_binary__set_NOT_EQUAL(void** state);
void test__fun_get_binary__set_LESS(void** state);
void test__fun_get_binary__set_LESS_EQUAL(void** state);
void test__fun_get_binary__set_GREATER(void** state);
void test__fun_get_binary__set_GREATER_EQUAL(void** state);
void test__fun_get_binary__set_LOGICAL_AND(void** state);
void test__fun_get_binary__set_LOGICAL_OR(void** state);
void test__fun_get_binary__map_PLUS(void** state);
void test__fun_get_binary__map_MINUS(void** state);
void test__fun_get_binary__map_MULTIPLIES(void** state);
void test__fun_get_binary__map_DIVIDES(void** state);
void test__fun_get_binary__map_MODULUS(void** state);
void test__fun_get_binary__map_EQUAL(void** state);
void test__fun_get_binary__map_NOT_EQUAL(void** state);
void test__fun_get_binary__map_LESS(void** state);
void test__fun_get_binary__map_LESS_EQUAL(void** state);
void test__fun_get_binary__map_GREATER(void** state);
void test__fun_get_binary__map_GREATER_EQUAL(void** state);
void test__fun_get_binary__map_LOGICAL_AND(void** state);
void test__fun_get_binary__map_LOGICAL_OR(void** state);
void test__fun_get_binary__multiset_PLUS(void** state);
void test__fun_get_binary__multiset_MINUS(void** state);
void test__fun_get_binary__multiset_MULTIPLIES(void** state);
void test__fun_get_binary__multiset_DIVIDES(void** state);
void test__fun_get_binary__multiset_MODULUS(void** state);
void test__fun_get_binary__multiset_EQUAL(void** state);
void test__fun_get_binary__multiset_NOT_EQUAL(void** state);
void test__fun_get_binary__multiset_LESS(void** state);
void test__fun_get_binary__multiset_LESS_EQUAL(void** state);
void test__fun_get_binary__multiset_GREATER(void** state);
void test__fun_get_binary__multiset_GREATER_EQUAL(void** state);
void test__fun_get_binary__multiset_LOGICAL_AND(void** state);
void test__fun_get_binary__multiset_LOGICAL_OR(void** state);
void test__fun_get_binary__multimap_PLUS(void** state);
void test__fun_get_binary__multimap_MINUS(void** state);
void test__fun_get_binary__multimap_MULTIPLIES(void** state);
void test__fun_get_binary__multimap_DIVIDES(void** state);
void test__fun_get_binary__multimap_MODULUS(void** state);
void test__fun_get_binary__multimap_EQUAL(void** state);
void test__fun_get_binary__multimap_NOT_EQUAL(void** state);
void test__fun_get_binary__multimap_LESS(void** state);
void test__fun_get_binary__multimap_LESS_EQUAL(void** state);
void test__fun_get_binary__multimap_GREATER(void** state);
void test__fun_get_binary__multimap_GREATER_EQUAL(void** state);
void test__fun_get_binary__multimap_LOGICAL_AND(void** state);
void test__fun_get_binary__multimap_LOGICAL_OR(void** state);
void test__fun_get_binary__hash_set_PLUS(void** state);
void test__fun_get_binary__hash_set_MINUS(void** state);
void test__fun_get_binary__hash_set_MULTIPLIES(void** state);
void test__fun_get_binary__hash_set_DIVIDES(void** state);
void test__fun_get_binary__hash_set_MODULUS(void** state);
void test__fun_get_binary__hash_set_EQUAL(void** state);
void test__fun_get_binary__hash_set_NOT_EQUAL(void** state);
void test__fun_get_binary__hash_set_LESS(void** state);
void test__fun_get_binary__hash_set_LESS_EQUAL(void** state);
void test__fun_get_binary__hash_set_GREATER(void** state);
void test__fun_get_binary__hash_set_GREATER_EQUAL(void** state);
void test__fun_get_binary__hash_set_LOGICAL_AND(void** state);
void test__fun_get_binary__hash_set_LOGICAL_OR(void** state);
void test__fun_get_binary__hash_map_PLUS(void** state);
void test__fun_get_binary__hash_map_MINUS(void** state);
void test__fun_get_binary__hash_map_MULTIPLIES(void** state);
void test__fun_get_binary__hash_map_DIVIDES(void** state);
void test__fun_get_binary__hash_map_MODULUS(void** state);
void test__fun_get_binary__hash_map_EQUAL(void** state);
void test__fun_get_binary__hash_map_NOT_EQUAL(void** state);
void test__fun_get_binary__hash_map_LESS(void** state);
void test__fun_get_binary__hash_map_LESS_EQUAL(void** state);
void test__fun_get_binary__hash_map_GREATER(void** state);
void test__fun_get_binary__hash_map_GREATER_EQUAL(void** state);
void test__fun_get_binary__hash_map_LOGICAL_AND(void** state);
void test__fun_get_binary__hash_map_LOGICAL_OR(void** state);
void test__fun_get_binary__hash_multiset_PLUS(void** state);
void test__fun_get_binary__hash_multiset_MINUS(void** state);
void test__fun_get_binary__hash_multiset_MULTIPLIES(void** state);
void test__fun_get_binary__hash_multiset_DIVIDES(void** state);
void test__fun_get_binary__hash_multiset_MODULUS(void** state);
void test__fun_get_binary__hash_multiset_EQUAL(void** state);
void test__fun_get_binary__hash_multiset_NOT_EQUAL(void** state);
void test__fun_get_binary__hash_multiset_LESS(void** state);
void test__fun_get_binary__hash_multiset_LESS_EQUAL(void** state);
void test__fun_get_binary__hash_multiset_GREATER(void** state);
void test__fun_get_binary__hash_multiset_GREATER_EQUAL(void** state);
void test__fun_get_binary__hash_multiset_LOGICAL_AND(void** state);
void test__fun_get_binary__hash_multiset_LOGICAL_OR(void** state);
void test__fun_get_binary__hash_multimap_PLUS(void** state);
void test__fun_get_binary__hash_multimap_MINUS(void** state);
void test__fun_get_binary__hash_multimap_MULTIPLIES(void** state);
void test__fun_get_binary__hash_multimap_DIVIDES(void** state);
void test__fun_get_binary__hash_multimap_MODULUS(void** state);
void test__fun_get_binary__hash_multimap_EQUAL(void** state);
void test__fun_get_binary__hash_multimap_NOT_EQUAL(void** state);
void test__fun_get_binary__hash_multimap_LESS(void** state);
void test__fun_get_binary__hash_multimap_LESS_EQUAL(void** state);
void test__fun_get_binary__hash_multimap_GREATER(void** state);
void test__fun_get_binary__hash_multimap_GREATER_EQUAL(void** state);
void test__fun_get_binary__hash_multimap_LOGICAL_AND(void** state);
void test__fun_get_binary__hash_multimap_LOGICAL_OR(void** state);
void test__fun_get_binary__string_PLUS(void** state);
void test__fun_get_binary__string_MINUS(void** state);
void test__fun_get_binary__string_MULTIPLIES(void** state);
void test__fun_get_binary__string_DIVIDES(void** state);
void test__fun_get_binary__string_MODULUS(void** state);
void test__fun_get_binary__string_EQUAL(void** state);
void test__fun_get_binary__string_NOT_EQUAL(void** state);
void test__fun_get_binary__string_LESS(void** state);
void test__fun_get_binary__string_LESS_EQUAL(void** state);
void test__fun_get_binary__string_GREATER(void** state);
void test__fun_get_binary__string_GREATER_EQUAL(void** state);
void test__fun_get_binary__string_LOGICAL_AND(void** state);
void test__fun_get_binary__string_LOGICAL_OR(void** state);
void test__fun_get_binary__user_define_PLUS(void** state);
void test__fun_get_binary__user_define_MINUS(void** state);
void test__fun_get_binary__user_define_MULTIPLIES(void** state);
void test__fun_get_binary__user_define_DIVIDES(void** state);
void test__fun_get_binary__user_define_MODULUS(void** state);
void test__fun_get_binary__user_define_EQUAL(void** state);
void test__fun_get_binary__user_define_NOT_EQUAL(void** state);
void test__fun_get_binary__user_define_LESS(void** state);
void test__fun_get_binary__user_define_LESS_EQUAL(void** state);
void test__fun_get_binary__user_define_GREATER(void** state);
void test__fun_get_binary__user_define_GREATER_EQUAL(void** state);
void test__fun_get_binary__user_define_LOGICAL_AND(void** state);
void test__fun_get_binary__user_define_LOGICAL_OR(void** state);
void test__fun_get_binary__pointer_EQUAL(void** state);
void test__fun_get_binary__pointer_NOT_EQUAL(void** state);
void test__fun_get_binary__pointer_GREATER(void** state);
void test__fun_get_binary__pointer_GREATER_EQUAL(void** state);
void test__fun_get_binary__pointer_LESS(void** state);
void test__fun_get_binary__pointer_LESS_EQUAL(void** state);
void test__fun_get_binary__basic_string_PLUS(void** state);
void test__fun_get_binary__basic_string_MINUS(void** state);
void test__fun_get_binary__basic_string_MULTIPLIES(void** state);
void test__fun_get_binary__basic_string_DIVIDES(void** state);
void test__fun_get_binary__basic_string_MODULUS(void** state);
void test__fun_get_binary__basic_string_EQUAL(void** state);
void test__fun_get_binary__basic_string_NOT_EQUAL(void** state);
void test__fun_get_binary__basic_string_LESS(void** state);
void test__fun_get_binary__basic_string_LESS_EQUAL(void** state);
void test__fun_get_binary__basic_string_GREATER(void** state);
void test__fun_get_binary__basic_string_GREATER_EQUAL(void** state);
void test__fun_get_binary__basic_string_LOGICAL_AND(void** state);
void test__fun_get_binary__basic_string_LOGICAL_OR(void** state);
#ifndef _MSC_VER
void test__fun_get_binary__bool_PLUS(void** state);
void test__fun_get_binary__bool_MINUS(void** state);
void test__fun_get_binary__bool_MULTIPLIES(void** state);
void test__fun_get_binary__bool_DIVIDES(void** state);
void test__fun_get_binary__bool_MODULUS(void** state);
void test__fun_get_binary__bool_EQUAL(void** state);
void test__fun_get_binary__bool_NOT_EQUAL(void** state);
void test__fun_get_binary__bool_LESS(void** state);
void test__fun_get_binary__bool_LESS_EQUAL(void** state);
void test__fun_get_binary__bool_GREATER(void** state);
void test__fun_get_binary__bool_GREATER_EQUAL(void** state);
void test__fun_get_binary__bool_LOGICAL_AND(void** state);
void test__fun_get_binary__bool_LOGICAL_OR(void** state);
void test__fun_get_binary__long_long_PLUS(void** state);
void test__fun_get_binary__long_long_MINUS(void** state);
void test__fun_get_binary__long_long_MULTIPLIES(void** state);
void test__fun_get_binary__long_long_DIVIDES(void** state);
void test__fun_get_binary__long_long_MODULUS(void** state);
void test__fun_get_binary__long_long_EQUAL(void** state);
void test__fun_get_binary__long_long_NOT_EQUAL(void** state);
void test__fun_get_binary__long_long_LESS(void** state);
void test__fun_get_binary__long_long_LESS_EQUAL(void** state);
void test__fun_get_binary__long_long_GREATER(void** state);
void test__fun_get_binary__long_long_GREATER_EQUAL(void** state);
void test__fun_get_binary__long_long_LOGICAL_AND(void** state);
void test__fun_get_binary__long_long_LOGICAL_OR(void** state);
void test__fun_get_binary__ulong_long_PLUS(void** state);
void test__fun_get_binary__ulong_long_MINUS(void** state);
void test__fun_get_binary__ulong_long_MULTIPLIES(void** state);
void test__fun_get_binary__ulong_long_DIVIDES(void** state);
void test__fun_get_binary__ulong_long_MODULUS(void** state);
void test__fun_get_binary__ulong_long_EQUAL(void** state);
void test__fun_get_binary__ulong_long_NOT_EQUAL(void** state);
void test__fun_get_binary__ulong_long_LESS(void** state);
void test__fun_get_binary__ulong_long_LESS_EQUAL(void** state);
void test__fun_get_binary__ulong_long_GREATER(void** state);
void test__fun_get_binary__ulong_long_GREATER_EQUAL(void** state);
void test__fun_get_binary__ulong_long_LOGICAL_AND(void** state);
void test__fun_get_binary__ulong_long_LOGICAL_OR(void** state);
#endif

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
    UT_CASE(test__fun_get_unary__cstl_bool_NEGATE),\
    UT_CASE(test__fun_get_unary__cstl_bool_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__cstl_bool_INCREASE),\
    UT_CASE(test__fun_get_unary__cstl_bool_RANDOM_NUMBER),\
    UT_CASE_BEGIN(_fun_get_binary, test__fun_get_binary__invalid_iter),\
    UT_CASE(test__fun_get_binary__invalid_type),\
    UT_CASE(test__fun_get_binary__char_PLUS),\
    UT_CASE(test__fun_get_binary__char_MINUS),\
    UT_CASE(test__fun_get_binary__char_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__char_DIVIDES),\
    UT_CASE(test__fun_get_binary__char_MODULUS),\
    UT_CASE(test__fun_get_binary__char_EQUAL),\
    UT_CASE(test__fun_get_binary__char_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__char_LESS),\
    UT_CASE(test__fun_get_binary__char_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__char_GREATER),\
    UT_CASE(test__fun_get_binary__char_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__char_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__char_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__uchar_PLUS),\
    UT_CASE(test__fun_get_binary__uchar_MINUS),\
    UT_CASE(test__fun_get_binary__uchar_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__uchar_DIVIDES),\
    UT_CASE(test__fun_get_binary__uchar_MODULUS),\
    UT_CASE(test__fun_get_binary__uchar_EQUAL),\
    UT_CASE(test__fun_get_binary__uchar_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__uchar_LESS),\
    UT_CASE(test__fun_get_binary__uchar_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__uchar_GREATER),\
    UT_CASE(test__fun_get_binary__uchar_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__uchar_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__uchar_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__short_PLUS),\
    UT_CASE(test__fun_get_binary__short_MINUS),\
    UT_CASE(test__fun_get_binary__short_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__short_DIVIDES),\
    UT_CASE(test__fun_get_binary__short_MODULUS),\
    UT_CASE(test__fun_get_binary__short_EQUAL),\
    UT_CASE(test__fun_get_binary__short_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__short_LESS),\
    UT_CASE(test__fun_get_binary__short_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__short_GREATER),\
    UT_CASE(test__fun_get_binary__short_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__short_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__short_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__ushort_PLUS),\
    UT_CASE(test__fun_get_binary__ushort_MINUS),\
    UT_CASE(test__fun_get_binary__ushort_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__ushort_DIVIDES),\
    UT_CASE(test__fun_get_binary__ushort_MODULUS),\
    UT_CASE(test__fun_get_binary__ushort_EQUAL),\
    UT_CASE(test__fun_get_binary__ushort_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__ushort_LESS),\
    UT_CASE(test__fun_get_binary__ushort_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__ushort_GREATER),\
    UT_CASE(test__fun_get_binary__ushort_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__ushort_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__ushort_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__int_PLUS),\
    UT_CASE(test__fun_get_binary__int_MINUS),\
    UT_CASE(test__fun_get_binary__int_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__int_DIVIDES),\
    UT_CASE(test__fun_get_binary__int_MODULUS),\
    UT_CASE(test__fun_get_binary__int_EQUAL),\
    UT_CASE(test__fun_get_binary__int_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__int_LESS),\
    UT_CASE(test__fun_get_binary__int_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__int_GREATER),\
    UT_CASE(test__fun_get_binary__int_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__int_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__int_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__uint_PLUS),\
    UT_CASE(test__fun_get_binary__uint_MINUS),\
    UT_CASE(test__fun_get_binary__uint_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__uint_DIVIDES),\
    UT_CASE(test__fun_get_binary__uint_MODULUS),\
    UT_CASE(test__fun_get_binary__uint_EQUAL),\
    UT_CASE(test__fun_get_binary__uint_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__uint_LESS),\
    UT_CASE(test__fun_get_binary__uint_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__uint_GREATER),\
    UT_CASE(test__fun_get_binary__uint_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__uint_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__uint_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__long_PLUS),\
    UT_CASE(test__fun_get_binary__long_MINUS),\
    UT_CASE(test__fun_get_binary__long_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__long_DIVIDES),\
    UT_CASE(test__fun_get_binary__long_MODULUS),\
    UT_CASE(test__fun_get_binary__long_EQUAL),\
    UT_CASE(test__fun_get_binary__long_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__long_LESS),\
    UT_CASE(test__fun_get_binary__long_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__long_GREATER),\
    UT_CASE(test__fun_get_binary__long_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__long_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__long_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__ulong_PLUS),\
    UT_CASE(test__fun_get_binary__ulong_MINUS),\
    UT_CASE(test__fun_get_binary__ulong_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__ulong_DIVIDES),\
    UT_CASE(test__fun_get_binary__ulong_MODULUS),\
    UT_CASE(test__fun_get_binary__ulong_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_LESS),\
    UT_CASE(test__fun_get_binary__ulong_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_GREATER),\
    UT_CASE(test__fun_get_binary__ulong_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__ulong_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__float_PLUS),\
    UT_CASE(test__fun_get_binary__float_MINUS),\
    UT_CASE(test__fun_get_binary__float_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__float_DIVIDES),\
    UT_CASE(test__fun_get_binary__float_MODULUS),\
    UT_CASE(test__fun_get_binary__float_EQUAL),\
    UT_CASE(test__fun_get_binary__float_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__float_LESS),\
    UT_CASE(test__fun_get_binary__float_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__float_GREATER),\
    UT_CASE(test__fun_get_binary__float_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__float_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__float_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__double_PLUS),\
    UT_CASE(test__fun_get_binary__double_MINUS),\
    UT_CASE(test__fun_get_binary__double_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__double_DIVIDES),\
    UT_CASE(test__fun_get_binary__double_MODULUS),\
    UT_CASE(test__fun_get_binary__double_EQUAL),\
    UT_CASE(test__fun_get_binary__double_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__double_LESS),\
    UT_CASE(test__fun_get_binary__double_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__double_GREATER),\
    UT_CASE(test__fun_get_binary__double_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__double_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__double_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__long_double_PLUS),\
    UT_CASE(test__fun_get_binary__long_double_MINUS),\
    UT_CASE(test__fun_get_binary__long_double_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__long_double_DIVIDES),\
    UT_CASE(test__fun_get_binary__long_double_MODULUS),\
    UT_CASE(test__fun_get_binary__long_double_EQUAL),\
    UT_CASE(test__fun_get_binary__long_double_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__long_double_LESS),\
    UT_CASE(test__fun_get_binary__long_double_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__long_double_GREATER),\
    UT_CASE(test__fun_get_binary__long_double_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__long_double_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__long_double_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__cstr_PLUS),\
    UT_CASE(test__fun_get_binary__cstr_MINUS),\
    UT_CASE(test__fun_get_binary__cstr_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__cstr_DIVIDES),\
    UT_CASE(test__fun_get_binary__cstr_MODULUS),\
    UT_CASE(test__fun_get_binary__cstr_EQUAL),\
    UT_CASE(test__fun_get_binary__cstr_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__cstr_LESS),\
    UT_CASE(test__fun_get_binary__cstr_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__cstr_GREATER),\
    UT_CASE(test__fun_get_binary__cstr_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__cstr_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__cstr_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__cstl_bool_PLUS),\
    UT_CASE(test__fun_get_binary__cstl_bool_MINUS),\
    UT_CASE(test__fun_get_binary__cstl_bool_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__cstl_bool_DIVIDES),\
    UT_CASE(test__fun_get_binary__cstl_bool_MODULUS),\
    UT_CASE(test__fun_get_binary__cstl_bool_EQUAL),\
    UT_CASE(test__fun_get_binary__cstl_bool_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__cstl_bool_LESS),\
    UT_CASE(test__fun_get_binary__cstl_bool_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__cstl_bool_GREATER),\
    UT_CASE(test__fun_get_binary__cstl_bool_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__cstl_bool_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__cstl_bool_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__vector_PLUS),\
    UT_CASE(test__fun_get_binary__vector_MINUS),\
    UT_CASE(test__fun_get_binary__vector_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__vector_DIVIDES),\
    UT_CASE(test__fun_get_binary__vector_MODULUS),\
    UT_CASE(test__fun_get_binary__vector_EQUAL),\
    UT_CASE(test__fun_get_binary__vector_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__vector_LESS),\
    UT_CASE(test__fun_get_binary__vector_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__vector_GREATER),\
    UT_CASE(test__fun_get_binary__vector_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__vector_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__vector_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__deque_PLUS),\
    UT_CASE(test__fun_get_binary__deque_MINUS),\
    UT_CASE(test__fun_get_binary__deque_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__deque_DIVIDES),\
    UT_CASE(test__fun_get_binary__deque_MODULUS),\
    UT_CASE(test__fun_get_binary__deque_EQUAL),\
    UT_CASE(test__fun_get_binary__deque_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__deque_LESS),\
    UT_CASE(test__fun_get_binary__deque_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__deque_GREATER),\
    UT_CASE(test__fun_get_binary__deque_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__deque_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__deque_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__list_PLUS),\
    UT_CASE(test__fun_get_binary__list_MINUS),\
    UT_CASE(test__fun_get_binary__list_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__list_DIVIDES),\
    UT_CASE(test__fun_get_binary__list_MODULUS),\
    UT_CASE(test__fun_get_binary__list_EQUAL),\
    UT_CASE(test__fun_get_binary__list_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__list_LESS),\
    UT_CASE(test__fun_get_binary__list_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__list_GREATER),\
    UT_CASE(test__fun_get_binary__list_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__list_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__list_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__slist_PLUS),\
    UT_CASE(test__fun_get_binary__slist_MINUS),\
    UT_CASE(test__fun_get_binary__slist_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__slist_DIVIDES),\
    UT_CASE(test__fun_get_binary__slist_MODULUS),\
    UT_CASE(test__fun_get_binary__slist_EQUAL),\
    UT_CASE(test__fun_get_binary__slist_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__slist_LESS),\
    UT_CASE(test__fun_get_binary__slist_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__slist_GREATER),\
    UT_CASE(test__fun_get_binary__slist_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__slist_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__slist_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__queue_PLUS),\
    UT_CASE(test__fun_get_binary__queue_MINUS),\
    UT_CASE(test__fun_get_binary__queue_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__queue_DIVIDES),\
    UT_CASE(test__fun_get_binary__queue_MODULUS),\
    UT_CASE(test__fun_get_binary__queue_EQUAL),\
    UT_CASE(test__fun_get_binary__queue_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__queue_LESS),\
    UT_CASE(test__fun_get_binary__queue_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__queue_GREATER),\
    UT_CASE(test__fun_get_binary__queue_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__queue_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__queue_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__stack_PLUS),\
    UT_CASE(test__fun_get_binary__stack_MINUS),\
    UT_CASE(test__fun_get_binary__stack_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__stack_DIVIDES),\
    UT_CASE(test__fun_get_binary__stack_MODULUS),\
    UT_CASE(test__fun_get_binary__stack_EQUAL),\
    UT_CASE(test__fun_get_binary__stack_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__stack_LESS),\
    UT_CASE(test__fun_get_binary__stack_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__stack_GREATER),\
    UT_CASE(test__fun_get_binary__stack_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__stack_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__stack_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__pair_PLUS),\
    UT_CASE(test__fun_get_binary__pair_MINUS),\
    UT_CASE(test__fun_get_binary__pair_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__pair_DIVIDES),\
    UT_CASE(test__fun_get_binary__pair_MODULUS),\
    UT_CASE(test__fun_get_binary__pair_EQUAL),\
    UT_CASE(test__fun_get_binary__pair_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__pair_LESS),\
    UT_CASE(test__fun_get_binary__pair_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__pair_GREATER),\
    UT_CASE(test__fun_get_binary__pair_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__pair_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__pair_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__set_PLUS),\
    UT_CASE(test__fun_get_binary__set_MINUS),\
    UT_CASE(test__fun_get_binary__set_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__set_DIVIDES),\
    UT_CASE(test__fun_get_binary__set_MODULUS),\
    UT_CASE(test__fun_get_binary__set_EQUAL),\
    UT_CASE(test__fun_get_binary__set_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__set_LESS),\
    UT_CASE(test__fun_get_binary__set_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__set_GREATER),\
    UT_CASE(test__fun_get_binary__set_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__set_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__set_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__map_PLUS),\
    UT_CASE(test__fun_get_binary__map_MINUS),\
    UT_CASE(test__fun_get_binary__map_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__map_DIVIDES),\
    UT_CASE(test__fun_get_binary__map_MODULUS),\
    UT_CASE(test__fun_get_binary__map_EQUAL),\
    UT_CASE(test__fun_get_binary__map_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__map_LESS),\
    UT_CASE(test__fun_get_binary__map_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__map_GREATER),\
    UT_CASE(test__fun_get_binary__map_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__map_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__map_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__multiset_PLUS),\
    UT_CASE(test__fun_get_binary__multiset_MINUS),\
    UT_CASE(test__fun_get_binary__multiset_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__multiset_DIVIDES),\
    UT_CASE(test__fun_get_binary__multiset_MODULUS),\
    UT_CASE(test__fun_get_binary__multiset_EQUAL),\
    UT_CASE(test__fun_get_binary__multiset_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__multiset_LESS),\
    UT_CASE(test__fun_get_binary__multiset_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__multiset_GREATER),\
    UT_CASE(test__fun_get_binary__multiset_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__multiset_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__multiset_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__multimap_PLUS),\
    UT_CASE(test__fun_get_binary__multimap_MINUS),\
    UT_CASE(test__fun_get_binary__multimap_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__multimap_DIVIDES),\
    UT_CASE(test__fun_get_binary__multimap_MODULUS),\
    UT_CASE(test__fun_get_binary__multimap_EQUAL),\
    UT_CASE(test__fun_get_binary__multimap_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__multimap_LESS),\
    UT_CASE(test__fun_get_binary__multimap_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__multimap_GREATER),\
    UT_CASE(test__fun_get_binary__multimap_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__multimap_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__multimap_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__hash_set_PLUS),\
    UT_CASE(test__fun_get_binary__hash_set_MINUS),\
    UT_CASE(test__fun_get_binary__hash_set_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__hash_set_DIVIDES),\
    UT_CASE(test__fun_get_binary__hash_set_MODULUS),\
    UT_CASE(test__fun_get_binary__hash_set_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_set_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_set_LESS),\
    UT_CASE(test__fun_get_binary__hash_set_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_set_GREATER),\
    UT_CASE(test__fun_get_binary__hash_set_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_set_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__hash_set_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__hash_map_PLUS),\
    UT_CASE(test__fun_get_binary__hash_map_MINUS),\
    UT_CASE(test__fun_get_binary__hash_map_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__hash_map_DIVIDES),\
    UT_CASE(test__fun_get_binary__hash_map_MODULUS),\
    UT_CASE(test__fun_get_binary__hash_map_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_map_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_map_LESS),\
    UT_CASE(test__fun_get_binary__hash_map_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_map_GREATER),\
    UT_CASE(test__fun_get_binary__hash_map_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_map_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__hash_map_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__hash_multiset_PLUS),\
    UT_CASE(test__fun_get_binary__hash_multiset_MINUS),\
    UT_CASE(test__fun_get_binary__hash_multiset_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__hash_multiset_DIVIDES),\
    UT_CASE(test__fun_get_binary__hash_multiset_MODULUS),\
    UT_CASE(test__fun_get_binary__hash_multiset_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multiset_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multiset_LESS),\
    UT_CASE(test__fun_get_binary__hash_multiset_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multiset_GREATER),\
    UT_CASE(test__fun_get_binary__hash_multiset_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multiset_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__hash_multiset_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__hash_multimap_PLUS),\
    UT_CASE(test__fun_get_binary__hash_multimap_MINUS),\
    UT_CASE(test__fun_get_binary__hash_multimap_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__hash_multimap_DIVIDES),\
    UT_CASE(test__fun_get_binary__hash_multimap_MODULUS),\
    UT_CASE(test__fun_get_binary__hash_multimap_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multimap_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multimap_LESS),\
    UT_CASE(test__fun_get_binary__hash_multimap_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multimap_GREATER),\
    UT_CASE(test__fun_get_binary__hash_multimap_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__hash_multimap_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__hash_multimap_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__string_PLUS),\
    UT_CASE(test__fun_get_binary__string_MINUS),\
    UT_CASE(test__fun_get_binary__string_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__string_DIVIDES),\
    UT_CASE(test__fun_get_binary__string_MODULUS),\
    UT_CASE(test__fun_get_binary__string_EQUAL),\
    UT_CASE(test__fun_get_binary__string_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__string_LESS),\
    UT_CASE(test__fun_get_binary__string_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__string_GREATER),\
    UT_CASE(test__fun_get_binary__string_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__string_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__string_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__user_define_PLUS),\
    UT_CASE(test__fun_get_binary__user_define_MINUS),\
    UT_CASE(test__fun_get_binary__user_define_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__user_define_DIVIDES),\
    UT_CASE(test__fun_get_binary__user_define_MODULUS),\
    UT_CASE(test__fun_get_binary__user_define_EQUAL),\
    UT_CASE(test__fun_get_binary__user_define_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__user_define_LESS),\
    UT_CASE(test__fun_get_binary__user_define_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__user_define_GREATER),\
    UT_CASE(test__fun_get_binary__user_define_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__user_define_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__user_define_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__pointer_EQUAL),\
    UT_CASE(test__fun_get_binary__pointer_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__pointer_GREATER),\
    UT_CASE(test__fun_get_binary__pointer_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__pointer_LESS),\
    UT_CASE(test__fun_get_binary__pointer_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__basic_string_PLUS),\
    UT_CASE(test__fun_get_binary__basic_string_MINUS),\
    UT_CASE(test__fun_get_binary__basic_string_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__basic_string_DIVIDES),\
    UT_CASE(test__fun_get_binary__basic_string_MODULUS),\
    UT_CASE(test__fun_get_binary__basic_string_EQUAL),\
    UT_CASE(test__fun_get_binary__basic_string_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__basic_string_LESS),\
    UT_CASE(test__fun_get_binary__basic_string_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__basic_string_GREATER),\
    UT_CASE(test__fun_get_binary__basic_string_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__basic_string_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__basic_string_LOGICAL_OR)

#ifndef _MSC_VER
#define UT_CSTL_FUNCTION_PRIVATE_CASE_C99\
    UT_SUIT_BEGIN(cstl_function_private, test__fun_get_unary__bool_NEGATE),\
    UT_CASE(test__fun_get_unary__bool_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__bool_INCREASE),\
    UT_CASE(test__fun_get_unary__bool_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__long_long_NEGATE),\
    UT_CASE(test__fun_get_unary__long_long_INCREASE),\
    UT_CASE(test__fun_get_unary__long_long_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__long_long_RANDOM_NUMBER),\
    UT_CASE(test__fun_get_unary__ulong_long_NEGATE),\
    UT_CASE(test__fun_get_unary__ulong_long_LOGICAL_NOT),\
    UT_CASE(test__fun_get_unary__ulong_long_INCREASE),\
    UT_CASE(test__fun_get_unary__ulong_long_RANDOM_NUMBER),\
    UT_CASE_BEGIN(_fun_get_binary, test__fun_get_binary__bool_PLUS),\
    UT_CASE(test__fun_get_binary__bool_MINUS),\
    UT_CASE(test__fun_get_binary__bool_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__bool_DIVIDES),\
    UT_CASE(test__fun_get_binary__bool_MODULUS),\
    UT_CASE(test__fun_get_binary__bool_EQUAL),\
    UT_CASE(test__fun_get_binary__bool_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__bool_LESS),\
    UT_CASE(test__fun_get_binary__bool_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__bool_GREATER),\
    UT_CASE(test__fun_get_binary__bool_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__bool_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__bool_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__long_long_PLUS),\
    UT_CASE(test__fun_get_binary__long_long_MINUS),\
    UT_CASE(test__fun_get_binary__long_long_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__long_long_DIVIDES),\
    UT_CASE(test__fun_get_binary__long_long_MODULUS),\
    UT_CASE(test__fun_get_binary__long_long_EQUAL),\
    UT_CASE(test__fun_get_binary__long_long_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__long_long_LESS),\
    UT_CASE(test__fun_get_binary__long_long_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__long_long_GREATER),\
    UT_CASE(test__fun_get_binary__long_long_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__long_long_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__long_long_LOGICAL_OR),\
    UT_CASE(test__fun_get_binary__ulong_long_PLUS),\
    UT_CASE(test__fun_get_binary__ulong_long_MINUS),\
    UT_CASE(test__fun_get_binary__ulong_long_MULTIPLIES),\
    UT_CASE(test__fun_get_binary__ulong_long_DIVIDES),\
    UT_CASE(test__fun_get_binary__ulong_long_MODULUS),\
    UT_CASE(test__fun_get_binary__ulong_long_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_long_NOT_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_long_LESS),\
    UT_CASE(test__fun_get_binary__ulong_long_LESS_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_long_GREATER),\
    UT_CASE(test__fun_get_binary__ulong_long_GREATER_EQUAL),\
    UT_CASE(test__fun_get_binary__ulong_long_LOGICAL_AND),\
    UT_CASE(test__fun_get_binary__ulong_long_LOGICAL_OR)
#endif

#endif /* _UT_CSTL_FUNCTION_PRIVATE_H_ */

