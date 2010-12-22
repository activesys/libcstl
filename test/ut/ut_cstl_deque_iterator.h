#ifndef _UT_CSTL_DEQUE_ITERATOR_H_
#define _UT_CSTL_DEQUE_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_deque_iterator)

/*
 * test _create_deque_iterator
 */
UT_CASE_DECLARATION(_create_deque_iterator)
void test__create_deque_iterator__successfully(void** state);
/*
 * test _deque_iterator_equal
 */
UT_CASE_DECLARATION(_deque_iterator_equal)
void test__deque_iterator_equal__different_container_type(void** state);
void test__deque_iterator_equal__different_iterator_type(void** state);
void test__deque_iterator_equal__different_container_pointer(void** state);
void test__deque_iterator_equal__first_is_not_belong_to_deque(void** state);
void test__deque_iterator_equal__second_is_not_belong_to_deque(void** state);
void test__deque_iterator_equal__equal_not_border(void** state);
void test__deque_iterator_equal__equal_border(void** state);
void test__deque_iterator_equal__not_equal_same_chunk(void** state);
void test__deque_iterator_equal__not_equal_not_same_chunk(void** state);
/*
 * test _deque_iterator_less
 */
UT_CASE_DECLARATION(_deque_iterator_less)
void test__deque_iterator_less__different_container_type(void** state);
void test__deque_iterator_less__different_iterator_type(void** state);
void test__deque_iterator_less__different_container_pointer(void** state);
void test__deque_iterator_less__first_is_not_belong_to_deque(void** state);
void test__deque_iterator_less__second_is_not_belong_to_deque(void** state);
void test__deque_iterator_less__first_greater_than_second_same_chunk(void** state);
void test__deque_iterator_less__first_equal_to_second_same_chunk(void** state);
void test__deque_iterator_less__first_less_than_second_same_chunk(void** state);
void test__deque_iterator_less__first_greater_than_second_not_same_chunk(void** state);
void test__deque_iterator_less__first_equal_to_second_not_same_chunk(void** state);
void test__deque_iterator_less__first_less_than_second_not_same_chunk(void** state);
/*
 * test _deque_iterator_before
 */
UT_CASE_DECLARATION(_deque_iterator_before)
void test__deque_iterator_before__different_container_type(void** state);
void test__deque_iterator_before__different_iterator_type(void** state);
void test__deque_iterator_before__different_container_pointer(void** state);
void test__deque_iterator_before__first_is_not_belong_to_deque(void** state);
void test__deque_iterator_before__second_is_not_belong_to_deque(void** state);
void test__deque_iterator_before__first_greater_than_second_same_chunk(void** state);
void test__deque_iterator_before__first_equal_to_second_same_chunk(void** state);
void test__deque_iterator_before__first_less_than_second_same_chunk(void** state);
void test__deque_iterator_before__first_greater_than_second_not_same_chunk(void** state);
void test__deque_iterator_before__first_equal_to_second_not_same_chunk(void** state);
void test__deque_iterator_before__first_less_than_second_not_same_chunk(void** state);
/*
 * test _deque_iterator_get_value
 */
UT_CASE_DECLARATION(_deque_iterator_get_value)
void test__deque_iterator_get_value__invalid_iterator(void** state);
void test__deque_iterator_get_value__invalid_iterator_container_type(void** state);
void test__deque_iterator_get_value__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_get_value__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_get_value__deque_end(void** state);
void test__deque_iterator_get_value__invalid_value_buffer(void** state);
void test__deque_iterator_get_value__successfully_not_border(void** state);
void test__deque_iterator_get_value__successfully_border(void** state);
void test__deque_iterator_get_value__successfully_cstr_not_border(void** state);
void test__deque_iterator_get_value__successfully_cstr_border(void** state);
/*
 * test _deque_iterator_set_value
 */
UT_CASE_DECLARATION(_deque_iterator_set_value)
void test__deque_iterator_set_value__invalid_iterator(void** state);
void test__deque_iterator_set_value__invalid_iterator_container_type(void** state);
void test__deque_iterator_set_value__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_set_value__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_set_value__deque_end(void** state);
void test__deque_iterator_set_value__invalid_value_buffer(void** state);
void test__deque_iterator_set_value__successfully_not_border(void** state);
void test__deque_iterator_set_value__successfully_border(void** state);
void test__deque_iterator_set_value__successfully_cstr_not_border(void** state);
void test__deque_iterator_set_value__successfully_cstr_border(void** state);

#define UT_CSTL_DEQUE_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_deque_iterator, test__create_deque_iterator__successfully),\
    UT_CASE_BEGIN(_deque_iterator_equal, test__deque_iterator_equal__different_container_type),\
    UT_CASE(test__deque_iterator_equal__different_iterator_type),\
    UT_CASE(test__deque_iterator_equal__different_container_pointer),\
    UT_CASE(test__deque_iterator_equal__first_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_equal__second_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_equal__equal_not_border),\
    UT_CASE(test__deque_iterator_equal__equal_border),\
    UT_CASE(test__deque_iterator_equal__not_equal_same_chunk),\
    UT_CASE(test__deque_iterator_equal__not_equal_not_same_chunk),\
    UT_CASE_BEGIN(_deque_iterator_less, test__deque_iterator_less__different_container_type),\
    UT_CASE(test__deque_iterator_less__different_iterator_type),\
    UT_CASE(test__deque_iterator_less__different_container_pointer),\
    UT_CASE(test__deque_iterator_less__first_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_less__second_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_less__first_greater_than_second_same_chunk),\
    UT_CASE(test__deque_iterator_less__first_equal_to_second_same_chunk),\
    UT_CASE(test__deque_iterator_less__first_less_than_second_same_chunk),\
    UT_CASE(test__deque_iterator_less__first_greater_than_second_not_same_chunk),\
    UT_CASE(test__deque_iterator_less__first_equal_to_second_not_same_chunk),\
    UT_CASE(test__deque_iterator_less__first_less_than_second_not_same_chunk),\
    UT_CASE_BEGIN(_deque_iterator_before, test__deque_iterator_before__different_container_type),\
    UT_CASE(test__deque_iterator_before__different_iterator_type),\
    UT_CASE(test__deque_iterator_before__different_container_pointer),\
    UT_CASE(test__deque_iterator_before__first_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_before__second_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_before__first_greater_than_second_same_chunk),\
    UT_CASE(test__deque_iterator_before__first_equal_to_second_same_chunk),\
    UT_CASE(test__deque_iterator_before__first_less_than_second_same_chunk),\
    UT_CASE(test__deque_iterator_before__first_greater_than_second_not_same_chunk),\
    UT_CASE(test__deque_iterator_before__first_equal_to_second_not_same_chunk),\
    UT_CASE(test__deque_iterator_before__first_less_than_second_not_same_chunk),\
    UT_CASE_BEGIN(_deque_iterator_get_value, test__deque_iterator_get_value__invalid_iterator),\
    UT_CASE(test__deque_iterator_get_value__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_get_value__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_get_value__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_get_value__deque_end),\
    UT_CASE(test__deque_iterator_get_value__invalid_value_buffer),\
    UT_CASE(test__deque_iterator_get_value__successfully_not_border),\
    UT_CASE(test__deque_iterator_get_value__successfully_border),\
    UT_CASE(test__deque_iterator_get_value__successfully_cstr_not_border),\
    UT_CASE(test__deque_iterator_get_value__successfully_cstr_border),\
    UT_CASE_BEGIN(_deque_iterator_set_value, test__deque_iterator_set_value__invalid_iterator),\
    UT_CASE(test__deque_iterator_set_value__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_set_value__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_set_value__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_set_value__deque_end),\
    UT_CASE(test__deque_iterator_set_value__invalid_value_buffer),\
    UT_CASE(test__deque_iterator_set_value__successfully_not_border),\
    UT_CASE(test__deque_iterator_set_value__successfully_border),\
    UT_CASE(test__deque_iterator_set_value__successfully_cstr_not_border),\
    UT_CASE(test__deque_iterator_set_value__successfully_cstr_border)

#endif /* _UT_CSTL_DEQUE_ITERATOR_H_ */

