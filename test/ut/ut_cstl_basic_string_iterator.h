#ifndef _UT_CSTL_BASIC_STRING_ITERATOR_H_
#define _UT_CSTL_BASIC_STRING_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_basic_string_iterator)

/*
 * test _create_basic_string_iterator
 */
UT_CASE_DECLARATION(_create_basic_string_iterator)
void test__create_basic_string_iterator__successfully(void** state);
/*
 * test _basic_string_iterator_equal
 */
UT_CASE_DECLARATION(_basic_string_iterator_equal)
void test__basic_string_iterator_equal__different_container_type(void** state);
void test__basic_string_iterator_equal__different_iterator_type(void** state);
void test__basic_string_iterator_equal__different_container_pointer(void** state);
void test__basic_string_iterator_equal__first_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_equal__second_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_equal__equal(void** state);
void test__basic_string_iterator_equal__not_equal(void** state);
/*
 * test _basic_string_iterator_less
 */
UT_CASE_DECLARATION(_basic_string_iterator_less)
void test__basic_string_iterator_less__different_container_type(void** state);
void test__basic_string_iterator_less__different_iterator_type(void** state);
void test__basic_string_iterator_less__different_container_pointer(void** state);
void test__basic_string_iterator_less__first_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_less__second_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_less__first_greater_than_second(void** state);
void test__basic_string_iterator_less__first_equal_to_second(void** state);
void test__basic_string_iterator_less__first_less_than_second(void** state);
/*
 * test _basic_string_iterator_before
 */
UT_CASE_DECLARATION(_basic_string_iterator_before)
void test__basic_string_iterator_before__different_container_type(void** state);
void test__basic_string_iterator_before__different_iterator_type(void** state);
void test__basic_string_iterator_before__different_container_pointer(void** state);
void test__basic_string_iterator_before__first_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_before__second_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_before__first_after_second(void** state);
void test__basic_string_iterator_before__first_equal_to_second(void** state);
void test__basic_string_iterator_before__first_before_second(void** state);
/*
 * test _basic_string_iterator_get_value
 */
UT_CASE_DECLARATION(_basic_string_iterator_get_value)
void test__basic_string_iterator_get_value__invalid_iterator(void** state);
void test__basic_string_iterator_get_value__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_get_value__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_get_value__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_get_value__basic_string_end(void** state);
void test__basic_string_iterator_get_value__invalid_value_buffer(void** state);
void test__basic_string_iterator_get_value__successfully(void** state);
void test__basic_string_iterator_get_value__successfully_cstr(void** state);
void test__basic_string_iterator_get_value__c_terminator(void** state);
void test__basic_string_iterator_get_value__cstr_terminator(void** state);
void test__basic_string_iterator_get_value__cstl_terminator(void** state);
void test__basic_string_iterator_get_value__user_define_terminator(void** state);
/*
 * test _basic_string_iterator_set_value
 */
UT_CASE_DECLARATION(_basic_string_iterator_set_value)
void test__basic_string_iterator_set_value__invalid_iterator(void** state);
void test__basic_string_iterator_set_value__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_set_value__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_set_value__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_set_value__basic_string_end(void** state);
void test__basic_string_iterator_set_value__invalid_value_buffer(void** state);
void test__basic_string_iterator_set_value__successfully(void** state);
void test__basic_string_iterator_set_value__successfully_cstr(void** state);
void test__basic_string_iterator_set_value__c_terminator(void** state);
void test__basic_string_iterator_set_value__cstr_terminator(void** state);
void test__basic_string_iterator_set_value__cstl_terminator(void** state);
void test__basic_string_iterator_set_value__user_define_terminator(void** state);
/*
 * test _basic_string_iterator_get_pointer
 */
UT_CASE_DECLARATION(_basic_string_iterator_get_pointer)
void test__basic_string_iterator_get_pointer__invalid_iterator(void** state);
void test__basic_string_iterator_get_pointer__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_get_pointer__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_get_pointer__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_get_pointer__basic_string_end(void** state);
void test__basic_string_iterator_get_pointer__successfully(void** state);
void test__basic_string_iterator_get_pointer__successfully_cstr(void** state);
void test__basic_string_iterator_get_pointer__terminator(void** state);
void test__basic_string_iterator_get_pointer__cstr_terminator(void** state);
/*
 * test _basic_string_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DECLARATION(_basic_string_iterator_get_pointer_ignore_cstr)
void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__basic_string_end(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__successfully(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__successfully_cstr(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__terminator(void** state);
void test__basic_string_iterator_get_pointer_ignore_cstr__cstr_terminator(void** state);
/*
 * test _basic_string_iterator_next
 */
UT_CASE_DECLARATION(_basic_string_iterator_next)
void test__basic_string_iterator_next__invalid_iterator(void** state);
void test__basic_string_iterator_next__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_next__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_next__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_next__invalid_returned_iterator(void** state);
void test__basic_string_iterator_next__successfully(void** state);
/*
 * test _basic_string_iterator_next
 */
UT_CASE_DECLARATION(_basic_string_iterator_next)
void test__basic_string_iterator_next__invalid_iterator(void** state);
void test__basic_string_iterator_next__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_next__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_next__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_next__invalid_returned_iterator(void** state);
void test__basic_string_iterator_next__successfully(void** state);
/*
 * test _basic_string_iterator_prev
 */
UT_CASE_DECLARATION(_basic_string_iterator_prev)
void test__basic_string_iterator_prev__invalid_iterator(void** state);
void test__basic_string_iterator_prev__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_prev__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_prev__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_prev__invalid_returned_iterator(void** state);
void test__basic_string_iterator_prev__successfully(void** state);
/*
 * test _basic_string_iterator_next_n
 */
UT_CASE_DECLARATION(_basic_string_iterator_next_n)
void test__basic_string_iterator_next_n__invalid_iterator(void** state);
void test__basic_string_iterator_next_n__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_next_n__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_next_n__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_next_n__move_to_end_invalid_returned_iterator(void** state);
void test__basic_string_iterator_next_n__move_to_begin_invalid_returned_iterator(void** state);
void test__basic_string_iterator_next_n__move_to_end_successfully(void** state);
void test__basic_string_iterator_next_n__move_to_front_successfully(void** state);
void test__basic_string_iterator_next_n__does_not_move_successfully(void** state);
/*
 * test _basic_string_iterator_prev_n
 */
UT_CASE_DECLARATION(_basic_string_iterator_prev_n)
void test__basic_string_iterator_prev_n__invalid_iterator(void** state);
void test__basic_string_iterator_prev_n__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_prev_n__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_prev_n__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_prev_n__move_to_end_invalid_returned_iterator(void** state);
void test__basic_string_iterator_prev_n__move_to_begin_invalid_returned_iterator(void** state);
void test__basic_string_iterator_prev_n__move_to_end_successfully(void** state);
void test__basic_string_iterator_prev_n__move_to_front_successfully(void** state);
void test__basic_string_iterator_prev_n__does_not_move_successfully(void** state);
/*
 * test _basic_string_iterator_at
 */
UT_CASE_DECLARATION(_basic_string_iterator_at)
void test__basic_string_iterator_at__invalid_iterator(void** state);
void test__basic_string_iterator_at__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_at__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_at__invalid_iterator_container_pointer(void** state);
void test__basic_string_iterator_at__move_to_end_invalid_returned_iterator(void** state);
void test__basic_string_iterator_at__move_to_begin_invalid_returned_iterator(void** state);
void test__basic_string_iterator_at__end_invalid_iterator(void** state);
void test__basic_string_iterator_at__move_to_end_successfully(void** state);
void test__basic_string_iterator_at__move_to_end_cstr_successfully(void** state);
void test__basic_string_iterator_at__move_to_front_successfully(void** state);
void test__basic_string_iterator_at__move_to_front_cstr_successfully(void** state);
void test__basic_string_iterator_at__does_not_move_successfully(void** state);
void test__basic_string_iterator_at__does_not_move_cstr_successfully(void** state);
/*
 * test _basic_string_iterator_minus
 */
UT_CASE_DECLARATION(_basic_string_iterator_minus)
void test__basic_string_iterator_minus__different_container_type(void** state);
void test__basic_string_iterator_minus__different_iterator_type(void** state);
void test__basic_string_iterator_minus__different_container_pointer(void** state);
void test__basic_string_iterator_minus__first_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_minus__second_is_not_belong_to_basic_string(void** state);
void test__basic_string_iterator_minus__first_less_then_second(void** state);
void test__basic_string_iterator_minus__first_greater_then_second(void** state);
void test__basic_string_iterator_minus__first_equal_to_second(void** state);

#define UT_CSTL_BASIC_STRING_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_basic_string_iterator, test__create_basic_string_iterator__successfully),\
    UT_CASE_BEGIN(_basic_string_iterator_equal, test__basic_string_iterator_equal__different_container_type),\
    UT_CASE(test__basic_string_iterator_equal__different_iterator_type),\
    UT_CASE(test__basic_string_iterator_equal__different_container_pointer),\
    UT_CASE(test__basic_string_iterator_equal__first_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_equal__second_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_equal__equal),\
    UT_CASE(test__basic_string_iterator_equal__not_equal),\
    UT_CASE_BEGIN(_basic_string_iterator_get_pointer, test__basic_string_iterator_get_pointer__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_get_pointer__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_get_pointer__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_get_pointer__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_get_pointer__basic_string_end),\
    UT_CASE(test__basic_string_iterator_get_pointer__successfully),\
    UT_CASE(test__basic_string_iterator_get_pointer__successfully_cstr),\
    UT_CASE(test__basic_string_iterator_get_pointer__terminator),\
    UT_CASE(test__basic_string_iterator_get_pointer__cstr_terminator),\
    UT_CASE_BEGIN(_basic_string_iterator_get_pointer_ignore_cstr, test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__basic_string_end),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__successfully),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__successfully_cstr),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__terminator),\
    UT_CASE(test__basic_string_iterator_get_pointer_ignore_cstr__cstr_terminator),\
    UT_CASE_BEGIN(_basic_string_iterator_get_value, test__basic_string_iterator_get_value__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_get_value__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_get_value__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_get_value__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_get_value__basic_string_end),\
    UT_CASE(test__basic_string_iterator_get_value__invalid_value_buffer),\
    UT_CASE(test__basic_string_iterator_get_value__successfully),\
    UT_CASE(test__basic_string_iterator_get_value__successfully_cstr),\
    UT_CASE(test__basic_string_iterator_get_value__c_terminator),\
    UT_CASE(test__basic_string_iterator_get_value__cstr_terminator),\
    UT_CASE(test__basic_string_iterator_get_value__cstl_terminator),\
    UT_CASE(test__basic_string_iterator_get_value__user_define_terminator),\
    UT_CASE_BEGIN(_basic_string_iterator_set_value, test__basic_string_iterator_set_value__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_set_value__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_set_value__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_set_value__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_set_value__basic_string_end),\
    UT_CASE(test__basic_string_iterator_set_value__invalid_value_buffer),\
    UT_CASE(test__basic_string_iterator_set_value__successfully),\
    UT_CASE(test__basic_string_iterator_set_value__successfully_cstr),\
    UT_CASE(test__basic_string_iterator_set_value__c_terminator),\
    UT_CASE(test__basic_string_iterator_set_value__cstr_terminator),\
    UT_CASE(test__basic_string_iterator_set_value__cstl_terminator),\
    UT_CASE(test__basic_string_iterator_set_value__user_define_terminator),\
    UT_CASE_BEGIN(_basic_string_iterator_less, test__basic_string_iterator_less__different_container_type),\
    UT_CASE(test__basic_string_iterator_less__different_iterator_type),\
    UT_CASE(test__basic_string_iterator_less__different_container_pointer),\
    UT_CASE(test__basic_string_iterator_less__first_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_less__second_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_less__first_greater_than_second),\
    UT_CASE(test__basic_string_iterator_less__first_equal_to_second),\
    UT_CASE(test__basic_string_iterator_less__first_less_than_second),\
    UT_CASE_BEGIN(_basic_string_iterator_before, test__basic_string_iterator_before__different_container_type),\
    UT_CASE(test__basic_string_iterator_before__different_iterator_type),\
    UT_CASE(test__basic_string_iterator_before__different_container_pointer),\
    UT_CASE(test__basic_string_iterator_before__first_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_before__second_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_before__first_after_second),\
    UT_CASE(test__basic_string_iterator_before__first_equal_to_second),\
    UT_CASE(test__basic_string_iterator_before__first_before_second),\
    UT_CASE_BEGIN(_basic_string_iterator_next, test__basic_string_iterator_next__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_next__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_next__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_next__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_next__invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_next__successfully),\
    UT_CASE_BEGIN(_basic_string_iterator_prev, test__basic_string_iterator_prev__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_prev__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_prev__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_prev__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_prev__invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_prev__successfully),\
    UT_CASE_BEGIN(_basic_string_iterator_next_n, test__basic_string_iterator_next_n__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_next_n__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_next_n__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_next_n__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_next_n__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_next_n__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_next_n__move_to_end_successfully),\
    UT_CASE(test__basic_string_iterator_next_n__move_to_front_successfully),\
    UT_CASE(test__basic_string_iterator_next_n__does_not_move_successfully),\
    UT_CASE_BEGIN(_basic_string_iterator_prev_n, test__basic_string_iterator_prev_n__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_prev_n__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_prev_n__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_prev_n__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_prev_n__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_prev_n__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_prev_n__move_to_end_successfully),\
    UT_CASE(test__basic_string_iterator_prev_n__move_to_front_successfully),\
    UT_CASE(test__basic_string_iterator_prev_n__does_not_move_successfully),\
    UT_CASE_BEGIN(_basic_string_iterator_at, test__basic_string_iterator_at__invalid_iterator),\
    UT_CASE(test__basic_string_iterator_at__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_at__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_at__invalid_iterator_container_pointer),\
    UT_CASE(test__basic_string_iterator_at__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_at__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__basic_string_iterator_at__end_invalid_iterator),\
    UT_CASE(test__basic_string_iterator_at__move_to_end_successfully),\
    UT_CASE(test__basic_string_iterator_at__move_to_end_cstr_successfully),\
    UT_CASE(test__basic_string_iterator_at__move_to_front_successfully),\
    UT_CASE(test__basic_string_iterator_at__move_to_front_cstr_successfully),\
    UT_CASE(test__basic_string_iterator_at__does_not_move_successfully),\
    UT_CASE(test__basic_string_iterator_at__does_not_move_cstr_successfully),\
    UT_CASE_BEGIN(_basic_string_iterator_minus, test__basic_string_iterator_minus__different_container_type),\
    UT_CASE(test__basic_string_iterator_minus__different_iterator_type),\
    UT_CASE(test__basic_string_iterator_minus__different_container_pointer),\
    UT_CASE(test__basic_string_iterator_minus__first_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_minus__second_is_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_iterator_minus__first_less_then_second),\
    UT_CASE(test__basic_string_iterator_minus__first_greater_then_second),\
    UT_CASE(test__basic_string_iterator_minus__first_equal_to_second)

#endif /* _UT_CSTL_BASIC_STRING_ITERATOR_H_ */

