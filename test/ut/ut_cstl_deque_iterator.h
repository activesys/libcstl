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
/*
 * test _deque_iterator_get_pointer
 */
UT_CASE_DECLARATION(_deque_iterator_get_pointer)
void test__deque_iterator_get_pointer__invalid_iterator(void** state);
void test__deque_iterator_get_pointer__invalid_iterator_container_type(void** state);
void test__deque_iterator_get_pointer__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_get_pointer__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_get_pointer__deque_end(void** state);
void test__deque_iterator_get_pointer__successfully_not_border(void** state);
void test__deque_iterator_get_pointer__successfully_border(void** state);
void test__deque_iterator_get_pointer__successfully_cstr_not_border(void** state);
void test__deque_iterator_get_pointer__successfully_cstr_border(void** state);
/*
 * test _deque_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DECLARATION(_deque_iterator_get_pointer_ignore_cstr)
void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__deque_end(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__successfully_not_border(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__successfully_border(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__successfully_cstr_not_border(void** state);
void test__deque_iterator_get_pointer_ignore_cstr__successfully_cstr_border(void** state);
/*
 * test _deque_iterator_next
 */
UT_CASE_DECLARATION(_deque_iterator_next)
void test__deque_iterator_next__invalid_iterator(void** state);
void test__deque_iterator_next__invalid_iterator_container_type(void** state);
void test__deque_iterator_next__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_next__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_next__invalid_returned_iterator(void** state);
void test__deque_iterator_next__successfully_not_border(void** state);
void test__deque_iterator_next__successfully_border(void** state);
/*
 * test _deque_iterator_prev
 */
UT_CASE_DECLARATION(_deque_iterator_prev)
void test__deque_iterator_prev__invalid_iterator(void** state);
void test__deque_iterator_prev__invalid_iterator_container_type(void** state);
void test__deque_iterator_prev__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_prev__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_prev__invalid_returned_iterator(void** state);
void test__deque_iterator_prev__successfully_not_border(void** state);
void test__deque_iterator_prev__successfully_border(void** state);
/*
 * test _deque_iterator_next_n
 */
UT_CASE_DECLARATION(_deque_iterator_next_n)
void test__deque_iterator_next_n__invalid_iterator(void** state);
void test__deque_iterator_next_n__invalid_iterator_container_type(void** state);
void test__deque_iterator_next_n__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_next_n__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_next_n__move_to_end_invalid_returned_iterator(void** state);
void test__deque_iterator_next_n__move_to_begin_invalid_returned_iterator(void** state);
void test__deque_iterator_next_n__move_to_end_successfully_not_border(void** state);
void test__deque_iterator_next_n__move_to_not_end_successfully_not_border(void** state);
void test__deque_iterator_next_n__move_to_end_successfully_border(void** state);
void test__deque_iterator_next_n__move_to_end_successfully_border_end(void** state);
void test__deque_iterator_next_n__move_to_not_end_successfully_border(void** state);
void test__deque_iterator_next_n__move_to_front_successfully_not_border(void** state);
void test__deque_iterator_next_n__move_to_not_front_successfully_not_border(void** state);
void test__deque_iterator_next_n__move_to_front_successfully_border(void** state);
void test__deque_iterator_next_n__move_to_not_front_successfully_border(void** state);
void test__deque_iterator_next_n__does_not_move_successfully(void** state);
void test__deque_iterator_next_n__move_to_end_span(void** state);
void test__deque_iterator_next_n__move_to_not_end_span(void** state);
void test__deque_iterator_next_n__move_to_not_end_span_middle_border(void** state);
void test__deque_iterator_next_n__move_to_end_span_border_end(void** state);
void test__deque_iterator_next_n__move_to_end_span_border_begin_end(void** state);
void test__deque_iterator_next_n__move_to_front_span(void** state);
void test__deque_iterator_next_n__move_to_not_front_span(void** state);
void test__deque_iterator_next_n__move_to_front_span_border_begin_end(void** state);
/*
 * test _deque_iterator_prev_n
 */
UT_CASE_DECLARATION(_deque_iterator_prev_n)
void test__deque_iterator_prev_n__invalid_iterator(void** state);
void test__deque_iterator_prev_n__invalid_iterator_container_type(void** state);
void test__deque_iterator_prev_n__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_prev_n__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_prev_n__move_to_end_invalid_returned_iterator(void** state);
void test__deque_iterator_prev_n__move_to_begin_invalid_returned_iterator(void** state);
void test__deque_iterator_prev_n__move_to_end_successfully_not_border(void** state);
void test__deque_iterator_prev_n__move_to_not_end_successfully_not_border(void** state);
void test__deque_iterator_prev_n__move_to_end_successfully_border(void** state);
void test__deque_iterator_prev_n__move_to_end_successfully_border_end(void** state);
void test__deque_iterator_prev_n__move_to_not_end_successfully_border(void** state);
void test__deque_iterator_prev_n__move_to_front_successfully_not_border(void** state);
void test__deque_iterator_prev_n__move_to_not_front_successfully_not_border(void** state);
void test__deque_iterator_prev_n__move_to_front_successfully_border(void** state);
void test__deque_iterator_prev_n__move_to_not_front_successfully_border(void** state);
void test__deque_iterator_prev_n__does_not_move_successfully(void** state);
void test__deque_iterator_prev_n__move_to_end_span(void** state);
void test__deque_iterator_prev_n__move_to_not_end_span(void** state);
void test__deque_iterator_prev_n__move_to_not_end_span_middle_border(void** state);
void test__deque_iterator_prev_n__move_to_end_span_border_end(void** state);
void test__deque_iterator_prev_n__move_to_end_span_border_begin_end(void** state);
void test__deque_iterator_prev_n__move_to_front_span(void** state);
void test__deque_iterator_prev_n__move_to_not_front_span(void** state);
void test__deque_iterator_prev_n__move_to_front_span_border_begin_end(void** state);
/*
 * test _deque_iterator_at
 */
UT_CASE_DECLARATION(_deque_iterator_at)
void test__deque_iterator_at__invalid_iterator(void** state);
void test__deque_iterator_at__invalid_iterator_container_type(void** state);
void test__deque_iterator_at__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_at__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_at__move_to_end_invalid_returned_iterator(void** state);
void test__deque_iterator_at__move_to_begin_invalid_returned_iterator(void** state);
void test__deque_iterator_at__end_invalid_iterator(void** state);
void test__deque_iterator_at__move_to_end_successfully(void** state);
void test__deque_iterator_at__move_to_end_cstr_successfully(void** state);
void test__deque_iterator_at__move_to_front_successfully(void** state);
void test__deque_iterator_at__move_to_front_cstr_successfully(void** state);
void test__deque_iterator_at__does_not_move_successfully(void** state);
void test__deque_iterator_at__does_not_move_cstr_successfully(void** state);
/*
 * test _deque_iterator_minus
 */
UT_CASE_DECLARATION(_deque_iterator_minus)
void test__deque_iterator_minus__different_container_type(void** state);
void test__deque_iterator_minus__different_iterator_type(void** state);
void test__deque_iterator_minus__different_container_pointer(void** state);
void test__deque_iterator_minus__first_is_not_belong_to_deque(void** state);
void test__deque_iterator_minus__second_is_not_belong_to_deque(void** state);
void test__deque_iterator_minus__first_less_then_second(void** state);
void test__deque_iterator_minus__first_less_then_second_same_chunk(void** state);
void test__deque_iterator_minus__first_less_then_second_border(void** state);
void test__deque_iterator_minus__first_less_then_second_border_end(void** state);
void test__deque_iterator_minus__first_less_then_second_border_begin(void** state);
void test__deque_iterator_minus__first_less_then_second_span(void** state);
void test__deque_iterator_minus__first_greater_then_second(void** state);
void test__deque_iterator_minus__first_greater_then_second_same_chunk(void** state);
void test__deque_iterator_minus__first_greater_then_second_border(void** state);
void test__deque_iterator_minus__first_greater_then_second_border_end(void** state);
void test__deque_iterator_minus__first_greater_then_second_border_begin(void** state);
void test__deque_iterator_minus__first_greater_then_second_span(void** state);
void test__deque_iterator_minus__first_equal_to_second(void** state);
void test__deque_iterator_minus__first_equal_to_second_border(void** state);

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
    UT_CASE(test__deque_iterator_set_value__successfully_cstr_border),\
    UT_CASE_BEGIN(_deque_iterator_get_pointer, test__deque_iterator_get_pointer__invalid_iterator),\
    UT_CASE(test__deque_iterator_get_pointer__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_get_pointer__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_get_pointer__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_get_pointer__deque_end),\
    UT_CASE(test__deque_iterator_get_pointer__successfully_not_border),\
    UT_CASE(test__deque_iterator_get_pointer__successfully_border),\
    UT_CASE(test__deque_iterator_get_pointer__successfully_cstr_not_border),\
    UT_CASE(test__deque_iterator_get_pointer__successfully_cstr_border),\
    UT_CASE_BEGIN(_deque_iterator_get_pointer_ignore_cstr, test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__deque_end),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__successfully_not_border),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__successfully_border),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__successfully_cstr_not_border),\
    UT_CASE(test__deque_iterator_get_pointer_ignore_cstr__successfully_cstr_border),\
    UT_CASE_BEGIN(_deque_iterator_next, test__deque_iterator_next__invalid_iterator),\
    UT_CASE(test__deque_iterator_next__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_next__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_next__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_next__invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_next__successfully_not_border),\
    UT_CASE(test__deque_iterator_next__successfully_border),\
    UT_CASE_BEGIN(_deque_iterator_prev, test__deque_iterator_prev__invalid_iterator),\
    UT_CASE(test__deque_iterator_prev__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_prev__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_prev__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_prev__invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_prev__successfully_not_border),\
    UT_CASE(test__deque_iterator_prev__successfully_border),\
    UT_CASE_BEGIN(_deque_iterator_next_n, test__deque_iterator_next_n__invalid_iterator),\
    UT_CASE(test__deque_iterator_next_n__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_next_n__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_next_n__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_next_n__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_next_n__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_next_n__move_to_end_successfully_not_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_not_end_successfully_not_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_end_successfully_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_end_successfully_border_end),\
    UT_CASE(test__deque_iterator_next_n__move_to_not_end_successfully_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_front_successfully_not_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_not_front_successfully_not_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_front_successfully_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_not_front_successfully_border),\
    UT_CASE(test__deque_iterator_next_n__does_not_move_successfully),\
    UT_CASE(test__deque_iterator_next_n__move_to_end_span),\
    UT_CASE(test__deque_iterator_next_n__move_to_not_end_span),\
    UT_CASE(test__deque_iterator_next_n__move_to_not_end_span_middle_border),\
    UT_CASE(test__deque_iterator_next_n__move_to_end_span_border_end),\
    UT_CASE(test__deque_iterator_next_n__move_to_end_span_border_begin_end),\
    UT_CASE(test__deque_iterator_next_n__move_to_front_span),\
    UT_CASE(test__deque_iterator_next_n__move_to_not_front_span),\
    UT_CASE(test__deque_iterator_next_n__move_to_front_span_border_begin_end),\
    UT_CASE_BEGIN(_deque_iterator_prev_n, test__deque_iterator_prev_n__invalid_iterator),\
    UT_CASE(test__deque_iterator_prev_n__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_prev_n__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_prev_n__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_prev_n__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_prev_n__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_prev_n__move_to_end_successfully_not_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_not_end_successfully_not_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_end_successfully_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_end_successfully_border_end),\
    UT_CASE(test__deque_iterator_prev_n__move_to_not_end_successfully_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_front_successfully_not_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_not_front_successfully_not_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_front_successfully_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_not_front_successfully_border),\
    UT_CASE(test__deque_iterator_prev_n__does_not_move_successfully),\
    UT_CASE(test__deque_iterator_prev_n__move_to_end_span),\
    UT_CASE(test__deque_iterator_prev_n__move_to_not_end_span),\
    UT_CASE(test__deque_iterator_prev_n__move_to_not_end_span_middle_border),\
    UT_CASE(test__deque_iterator_prev_n__move_to_end_span_border_end),\
    UT_CASE(test__deque_iterator_prev_n__move_to_end_span_border_begin_end),\
    UT_CASE(test__deque_iterator_prev_n__move_to_front_span),\
    UT_CASE(test__deque_iterator_prev_n__move_to_not_front_span),\
    UT_CASE(test__deque_iterator_prev_n__move_to_front_span_border_begin_end),\
    UT_CASE_BEGIN(_deque_iterator_at, test__deque_iterator_at__invalid_iterator),\
    UT_CASE(test__deque_iterator_at__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_at__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_at__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_at__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_at__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__deque_iterator_at__end_invalid_iterator),\
    UT_CASE(test__deque_iterator_at__move_to_end_successfully),\
    UT_CASE(test__deque_iterator_at__move_to_end_cstr_successfully),\
    UT_CASE(test__deque_iterator_at__move_to_front_successfully),\
    UT_CASE(test__deque_iterator_at__move_to_front_cstr_successfully),\
    UT_CASE(test__deque_iterator_at__does_not_move_successfully),\
    UT_CASE(test__deque_iterator_at__does_not_move_cstr_successfully),\
    UT_CASE_BEGIN(_deque_iterator_minus, test__deque_iterator_minus__different_container_type),\
    UT_CASE(test__deque_iterator_minus__different_iterator_type),\
    UT_CASE(test__deque_iterator_minus__different_container_pointer),\
    UT_CASE(test__deque_iterator_minus__first_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_minus__second_is_not_belong_to_deque),\
    UT_CASE(test__deque_iterator_minus__first_less_then_second),\
    UT_CASE(test__deque_iterator_minus__first_less_then_second_same_chunk),\
    UT_CASE(test__deque_iterator_minus__first_less_then_second_border),\
    UT_CASE(test__deque_iterator_minus__first_less_then_second_border_end),\
    UT_CASE(test__deque_iterator_minus__first_less_then_second_border_begin),\
    UT_CASE(test__deque_iterator_minus__first_less_then_second_span),\
    UT_CASE(test__deque_iterator_minus__first_greater_then_second),\
    UT_CASE(test__deque_iterator_minus__first_greater_then_second_same_chunk),\
    UT_CASE(test__deque_iterator_minus__first_greater_then_second_border),\
    UT_CASE(test__deque_iterator_minus__first_greater_then_second_border_end),\
    UT_CASE(test__deque_iterator_minus__first_greater_then_second_border_begin),\
    UT_CASE(test__deque_iterator_minus__first_greater_then_second_span),\
    UT_CASE(test__deque_iterator_minus__first_equal_to_second),\
    UT_CASE(test__deque_iterator_minus__first_equal_to_second_border)

#endif /* _UT_CSTL_DEQUE_ITERATOR_H_ */

