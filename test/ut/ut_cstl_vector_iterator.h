#ifndef _UT_CSTL_VECTOR_ITERATOR_H_
#define _UT_CSTL_VECTOR_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_vector_iterator)

/*
 * test _create_vector_iterator
 */
UT_CASE_DECLARATION(_create_vector_iterator)
void test__create_vector_iterator__successfully(void** state);
/*
 * test _vector_iterator_equal
 */
UT_CASE_DECLARATION(_vector_iterator_equal)
void test__vector_iterator_equal__different_container_type(void** state);
void test__vector_iterator_equal__different_iterator_type(void** state);
void test__vector_iterator_equal__different_container_pointer(void** state);
void test__vector_iterator_equal__first_is_not_belong_to_vector(void** state);
void test__vector_iterator_equal__second_is_not_belong_to_vector(void** state);
void test__vector_iterator_equal__equal(void** state);
void test__vector_iterator_equal__not_equal(void** state);
/*
 * test _vector_iterator_less
 */
UT_CASE_DECLARATION(_vector_iterator_less)
void test__vector_iterator_less__different_container_type(void** state);
void test__vector_iterator_less__different_iterator_type(void** state);
void test__vector_iterator_less__different_container_pointer(void** state);
void test__vector_iterator_less__first_is_not_belong_to_vector(void** state);
void test__vector_iterator_less__second_is_not_belong_to_vector(void** state);
void test__vector_iterator_less__first_greater_than_second(void** state);
void test__vector_iterator_less__first_equal_to_second(void** state);
void test__vector_iterator_less__first_less_than_second(void** state);
/*
 * test _vector_iterator_before
 */
UT_CASE_DECLARATION(_vector_iterator_before)
void test__vector_iterator_before__different_container_type(void** state);
void test__vector_iterator_before__different_iterator_type(void** state);
void test__vector_iterator_before__different_container_pointer(void** state);
void test__vector_iterator_before__first_is_not_belong_to_vector(void** state);
void test__vector_iterator_before__second_is_not_belong_to_vector(void** state);
void test__vector_iterator_before__first_after_second(void** state);
void test__vector_iterator_before__first_equal_to_second(void** state);
void test__vector_iterator_before__first_before_second(void** state);
/*
 * test _vector_iterator_get_value
 */
UT_CASE_DECLARATION(_vector_iterator_get_value)
void test__vector_iterator_get_value__invalid_iterator(void** state);
void test__vector_iterator_get_value__invalid_iterator_container_type(void** state);
void test__vector_iterator_get_value__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_get_value__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_get_value__vector_end(void** state);
void test__vector_iterator_get_value__invalid_value_buffer(void** state);
void test__vector_iterator_get_value__successfully(void** state);
void test__vector_iterator_get_value__successfully_cstr(void** state);
/*
 * test _vector_iterator_set_value
 */
UT_CASE_DECLARATION(_vector_iterator_set_value)
void test__vector_iterator_set_value__invalid_iterator(void** state);
void test__vector_iterator_set_value__invalid_iterator_container_type(void** state);
void test__vector_iterator_set_value__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_set_value__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_set_value__vector_end(void** state);
void test__vector_iterator_set_value__invalid_value_buffer(void** state);
void test__vector_iterator_set_value__successfully(void** state);
void test__vector_iterator_set_value__successfully_cstr(void** state);
/*
 * test _vector_iterator_get_pointer
 */
UT_CASE_DECLARATION(_vector_iterator_get_pointer)
void test__vector_iterator_get_pointer__invalid_iterator(void** state);
void test__vector_iterator_get_pointer__invalid_iterator_container_type(void** state);
void test__vector_iterator_get_pointer__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_get_pointer__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_get_pointer__vector_end(void** state);
void test__vector_iterator_get_pointer__successfully(void** state);
void test__vector_iterator_get_pointer__successfully_cstr(void** state);
/*
 * test _vector_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DECLARATION(_vector_iterator_get_pointer_ignore_cstr)
void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator(void** state);
void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type(void** state);
void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_get_pointer_ignore_cstr__vector_end(void** state);
void test__vector_iterator_get_pointer_ignore_cstr__successfully(void** state);
void test__vector_iterator_get_pointer_ignore_cstr__successfully_cstr(void** state);
/*
 * test _vector_iterator_next
 */
UT_CASE_DECLARATION(_vector_iterator_next)
void test__vector_iterator_next__invalid_iterator(void** state);
void test__vector_iterator_next__invalid_iterator_container_type(void** state);
void test__vector_iterator_next__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_next__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_next__invalid_returned_iterator(void** state);
void test__vector_iterator_next__successfully(void** state);
/*
 * test _vector_iterator_prev
 */
UT_CASE_DECLARATION(_vector_iterator_prev)
void test__vector_iterator_prev__invalid_iterator(void** state);
void test__vector_iterator_prev__invalid_iterator_container_type(void** state);
void test__vector_iterator_prev__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_prev__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_prev__invalid_returned_iterator(void** state);
void test__vector_iterator_prev__successfully(void** state);
/*
 * test _vector_iterator_next_n
 */
UT_CASE_DECLARATION(_vector_iterator_next_n)
void test__vector_iterator_next_n__invalid_iterator(void** state);
void test__vector_iterator_next_n__invalid_iterator_container_type(void** state);
void test__vector_iterator_next_n__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_next_n__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_next_n__move_to_end_invalid_returned_iterator(void** state);
void test__vector_iterator_next_n__move_to_begin_invalid_returned_iterator(void** state);
void test__vector_iterator_next_n__move_to_end_successfully(void** state);
void test__vector_iterator_next_n__move_to_front_successfully(void** state);
void test__vector_iterator_next_n__does_not_move_successfully(void** state);
/*
 * test _vector_iterator_prev_n
 */
UT_CASE_DECLARATION(_vector_iterator_prev_n)
void test__vector_iterator_prev_n__invalid_iterator(void** state);
void test__vector_iterator_prev_n__invalid_iterator_container_type(void** state);
void test__vector_iterator_prev_n__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_prev_n__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_prev_n__move_to_end_invalid_returned_iterator(void** state);
void test__vector_iterator_prev_n__move_to_begin_invalid_returned_iterator(void** state);
void test__vector_iterator_prev_n__move_to_end_successfully(void** state);
void test__vector_iterator_prev_n__move_to_front_successfully(void** state);
void test__vector_iterator_prev_n__does_not_move_successfully(void** state);
/*
 * test _vector_iterator_at
 */
UT_CASE_DECLARATION(_vector_iterator_at)
void test__vector_iterator_at__invalid_iterator(void** state);
void test__vector_iterator_at__invalid_iterator_container_type(void** state);
void test__vector_iterator_at__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_at__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_at__move_to_end_invalid_returned_iterator(void** state);
void test__vector_iterator_at__move_to_begin_invalid_returned_iterator(void** state);
void test__vector_iterator_at__end_invalid_iterator(void** state);
void test__vector_iterator_at__move_to_end_successfully(void** state);
void test__vector_iterator_at__move_to_end_cstr_successfully(void** state);
void test__vector_iterator_at__move_to_front_successfully(void** state);
void test__vector_iterator_at__move_to_front_cstr_successfully(void** state);
void test__vector_iterator_at__does_not_move_successfully(void** state);
void test__vector_iterator_at__does_not_move_cstr_successfully(void** state);
/*
 * test _vector_iterator_minus
 */
UT_CASE_DECLARATION(_vector_iterator_minus)
void test__vector_iterator_minus__different_container_type(void** state);
void test__vector_iterator_minus__different_iterator_type(void** state);
void test__vector_iterator_minus__different_container_pointer(void** state);
void test__vector_iterator_minus__first_is_not_belong_to_vector(void** state);
void test__vector_iterator_minus__second_is_not_belong_to_vector(void** state);
void test__vector_iterator_minus__first_less_then_second(void** state);
void test__vector_iterator_minus__first_greater_then_second(void** state);
void test__vector_iterator_minus__first_equal_to_second(void** state);

#define UT_CSTL_VECTOR_ITERATOR_CASE \
    UT_SUIT_BEGIN(cstl_vector_iterator, test__create_vector_iterator__successfully),\
    UT_CASE_BEGIN(_vector_iterator_equal, test__vector_iterator_equal__different_container_type),\
    UT_CASE(test__vector_iterator_equal__different_iterator_type),\
    UT_CASE(test__vector_iterator_equal__different_container_pointer),\
    UT_CASE(test__vector_iterator_equal__first_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_equal__second_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_equal__equal),\
    UT_CASE(test__vector_iterator_equal__not_equal),\
    UT_CASE_BEGIN(_vector_iterator_less, test__vector_iterator_less__different_container_type),\
    UT_CASE(test__vector_iterator_less__different_iterator_type),\
    UT_CASE(test__vector_iterator_less__different_container_pointer),\
    UT_CASE(test__vector_iterator_less__first_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_less__second_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_less__first_greater_than_second),\
    UT_CASE(test__vector_iterator_less__first_equal_to_second),\
    UT_CASE(test__vector_iterator_less__first_less_than_second),\
    UT_CASE_BEGIN(_vector_iterator_before, test__vector_iterator_before__different_container_type),\
    UT_CASE(test__vector_iterator_before__different_iterator_type),\
    UT_CASE(test__vector_iterator_before__different_container_pointer),\
    UT_CASE(test__vector_iterator_before__first_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_before__second_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_before__first_after_second),\
    UT_CASE(test__vector_iterator_before__first_equal_to_second),\
    UT_CASE(test__vector_iterator_before__first_before_second),\
    UT_CASE_BEGIN(_vector_iterator_get_value, test__vector_iterator_get_value__invalid_iterator),\
    UT_CASE(test__vector_iterator_get_value__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_get_value__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_get_value__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_get_value__vector_end),\
    UT_CASE(test__vector_iterator_get_value__invalid_value_buffer),\
    UT_CASE(test__vector_iterator_get_value__successfully),\
    UT_CASE(test__vector_iterator_get_value__successfully_cstr),\
    UT_CASE_BEGIN(_vector_iterator_set_value, test__vector_iterator_set_value__invalid_iterator),\
    UT_CASE(test__vector_iterator_set_value__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_set_value__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_set_value__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_set_value__vector_end),\
    UT_CASE(test__vector_iterator_set_value__invalid_value_buffer),\
    UT_CASE(test__vector_iterator_set_value__successfully),\
    UT_CASE(test__vector_iterator_set_value__successfully_cstr),\
    UT_CASE_BEGIN(_vector_iterator_get_pointer, test__vector_iterator_get_pointer__invalid_iterator),\
    UT_CASE(test__vector_iterator_get_pointer__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_get_pointer__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_get_pointer__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_get_pointer__vector_end),\
    UT_CASE(test__vector_iterator_get_pointer__successfully),\
    UT_CASE(test__vector_iterator_get_pointer__successfully_cstr),\
    UT_CASE_BEGIN(_vector_iterator_get_pointer_ignore_cstr, test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator),\
    UT_CASE(test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_get_pointer_ignore_cstr__vector_end),\
    UT_CASE(test__vector_iterator_get_pointer_ignore_cstr__successfully),\
    UT_CASE(test__vector_iterator_get_pointer_ignore_cstr__successfully_cstr),\
    UT_CASE_BEGIN(_vector_iterator_next, test__vector_iterator_next__invalid_iterator),\
    UT_CASE(test__vector_iterator_next__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_next__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_next__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_next__invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_next__successfully),\
    UT_CASE_BEGIN(_vector_iterator_prev, test__vector_iterator_prev__invalid_iterator),\
    UT_CASE(test__vector_iterator_prev__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_prev__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_prev__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_prev__invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_prev__successfully),\
    UT_CASE_BEGIN(_vector_iterator_next_n, test__vector_iterator_next_n__invalid_iterator),\
    UT_CASE(test__vector_iterator_next_n__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_next_n__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_next_n__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_next_n__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_next_n__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_next_n__move_to_end_successfully),\
    UT_CASE(test__vector_iterator_next_n__move_to_front_successfully),\
    UT_CASE(test__vector_iterator_next_n__does_not_move_successfully),\
    UT_CASE_BEGIN(_vector_iterator_prev_n, test__vector_iterator_prev_n__invalid_iterator),\
    UT_CASE(test__vector_iterator_prev_n__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_prev_n__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_prev_n__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_prev_n__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_prev_n__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_prev_n__move_to_end_successfully),\
    UT_CASE(test__vector_iterator_prev_n__move_to_front_successfully),\
    UT_CASE(test__vector_iterator_prev_n__does_not_move_successfully),\
    UT_CASE_BEGIN(_vector_iterator_at, test__vector_iterator_at__invalid_iterator),\
    UT_CASE(test__vector_iterator_at__invalid_iterator_container_type),\
    UT_CASE(test__vector_iterator_at__invalid_iterator_iterator_type),\
    UT_CASE(test__vector_iterator_at__invalid_iterator_container_pointer),\
    UT_CASE(test__vector_iterator_at__move_to_end_invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_at__move_to_begin_invalid_returned_iterator),\
    UT_CASE(test__vector_iterator_at__end_invalid_iterator),\
    UT_CASE(test__vector_iterator_at__move_to_end_successfully),\
    UT_CASE(test__vector_iterator_at__move_to_end_cstr_successfully),\
    UT_CASE(test__vector_iterator_at__move_to_front_successfully),\
    UT_CASE(test__vector_iterator_at__move_to_front_cstr_successfully),\
    UT_CASE(test__vector_iterator_at__does_not_move_successfully),\
    UT_CASE(test__vector_iterator_at__does_not_move_cstr_successfully),\
    UT_CASE_BEGIN(_vector_iterator_minus, test__vector_iterator_minus__different_container_type),\
    UT_CASE(test__vector_iterator_minus__different_iterator_type),\
    UT_CASE(test__vector_iterator_minus__different_container_pointer),\
    UT_CASE(test__vector_iterator_minus__first_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_minus__second_is_not_belong_to_vector),\
    UT_CASE(test__vector_iterator_minus__first_less_then_second),\
    UT_CASE(test__vector_iterator_minus__first_greater_then_second),\
    UT_CASE(test__vector_iterator_minus__first_equal_to_second)

#endif /* _UT_CSTL_VECTOR_ITERATOR_H_ */

