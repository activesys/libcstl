#ifndef _UT_CSTL_VECTOR_ITERATOR_H_
#define _UT_CSTL_VECTOR_ITERATOR_H_

UT_CASE_DECLARATION(cstl_vector_iterator)

/*
 * test _create_vector_iterator
 */
UT_ITEM_DECLARATION(_create_vector_iterator)
void test__create_vector_iterator__successfully(void** state);
/*
 * test _vector_iterator_equal
 */
UT_ITEM_DECLARATION(_vector_iterator_equal)
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
UT_ITEM_DECLARATION(_vector_iterator_less)
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
UT_ITEM_DECLARATION(_vector_iterator_before)
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
UT_ITEM_DECLARATION(_vector_iterator_get_value)
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
UT_ITEM_DECLARATION(_vector_iterator_set_value)
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
UT_ITEM_DECLARATION(_vector_iterator_get_pointer)
void test__vector_iterator_get_pointer__invalid_iterator(void** state);
void test__vector_iterator_get_pointer__invalid_iterator_container_type(void** state);
void test__vector_iterator_get_pointer__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_get_pointer__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_get_pointer__vector_end(void** state);
void test__vector_iterator_get_pointer__successfully(void** state);
void test__vector_iterator_get_pointer__successfully_cstr(void** state);
/*
 * test _vector_iterator_next
 */
UT_ITEM_DECLARATION(_vector_iterator_next)
void test__vector_iterator_next__invalid_iterator(void** state);
void test__vector_iterator_next__invalid_iterator_container_type(void** state);
void test__vector_iterator_next__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_next__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_next__invalid_returned_iterator(void** state);
void test__vector_iterator_next__successfully(void** state);
/*
 * test _vector_iterator_prev
 */
UT_ITEM_DECLARATION(_vector_iterator_prev)
void test__vector_iterator_prev__invalid_iterator(void** state);
void test__vector_iterator_prev__invalid_iterator_container_type(void** state);
void test__vector_iterator_prev__invalid_iterator_iterator_type(void** state);
void test__vector_iterator_prev__invalid_iterator_container_pointer(void** state);
void test__vector_iterator_prev__invalid_returned_iterator(void** state);
void test__vector_iterator_prev__successfully(void** state);
/*
 * test _vector_iterator_next_n
 */
UT_ITEM_DECLARATION(_vector_iterator_next_n)
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
UT_ITEM_DECLARATION(_vector_iterator_prev_n)
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
UT_ITEM_DECLARATION(_vector_iterator_at)
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
UT_ITEM_DECLARATION(_vector_iterator_minus)
void test__vector_iterator_minus__different_container_type(void** state);
void test__vector_iterator_minus__different_iterator_type(void** state);
void test__vector_iterator_minus__different_container_pointer(void** state);
void test__vector_iterator_minus__first_is_not_belong_to_vector(void** state);
void test__vector_iterator_minus__second_is_not_belong_to_vector(void** state);
void test__vector_iterator_minus__first_less_then_second(void** state);
void test__vector_iterator_minus__first_greater_then_second(void** state);
void test__vector_iterator_minus__first_equal_to_second(void** state);

#define UT_CSTL_VECTOR_ITERATOR_CASE \
    UT_CASE(cstl_vector_iterator),\
    UT_ITEM(_create_vector_iterator),\
    unit_test(test__create_vector_iterator__successfully),\
    UT_ITEM(_vector_iterator_equal),\
    unit_test(test__vector_iterator_equal__different_container_type),\
    unit_test(test__vector_iterator_equal__different_iterator_type),\
    unit_test(test__vector_iterator_equal__different_container_pointer),\
    unit_test(test__vector_iterator_equal__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_equal__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_equal__equal),\
    unit_test(test__vector_iterator_equal__not_equal),\
    UT_ITEM(_vector_iterator_less),\
    unit_test(test__vector_iterator_less__different_container_type),\
    unit_test(test__vector_iterator_less__different_iterator_type),\
    unit_test(test__vector_iterator_less__different_container_pointer),\
    unit_test(test__vector_iterator_less__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_less__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_less__first_greater_than_second),\
    unit_test(test__vector_iterator_less__first_equal_to_second),\
    unit_test(test__vector_iterator_less__first_less_than_second),\
    UT_ITEM(_vector_iterator_before),\
    unit_test(test__vector_iterator_before__different_container_type),\
    unit_test(test__vector_iterator_before__different_iterator_type),\
    unit_test(test__vector_iterator_before__different_container_pointer),\
    unit_test(test__vector_iterator_before__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_before__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_before__first_after_second),\
    unit_test(test__vector_iterator_before__first_equal_to_second),\
    unit_test(test__vector_iterator_before__first_before_second),\
    UT_ITEM(_vector_iterator_get_value),\
    unit_test(test__vector_iterator_get_value__invalid_iterator),\
    unit_test(test__vector_iterator_get_value__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_get_value__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_get_value__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_get_value__vector_end),\
    unit_test(test__vector_iterator_get_value__invalid_value_buffer),\
    unit_test(test__vector_iterator_get_value__successfully),\
    unit_test(test__vector_iterator_get_value__successfully_cstr),\
    UT_ITEM(_vector_iterator_set_value),\
    unit_test(test__vector_iterator_set_value__invalid_iterator),\
    unit_test(test__vector_iterator_set_value__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_set_value__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_set_value__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_set_value__vector_end),\
    unit_test(test__vector_iterator_set_value__invalid_value_buffer),\
    unit_test(test__vector_iterator_set_value__successfully),\
    unit_test(test__vector_iterator_set_value__successfully_cstr),\
    UT_ITEM(_vector_iterator_get_pointer),\
    unit_test(test__vector_iterator_get_pointer__invalid_iterator),\
    unit_test(test__vector_iterator_get_pointer__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_get_pointer__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_get_pointer__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_get_pointer__vector_end),\
    unit_test(test__vector_iterator_get_pointer__successfully),\
    unit_test(test__vector_iterator_get_pointer__successfully_cstr),\
    UT_ITEM(_vector_iterator_next),\
    unit_test(test__vector_iterator_next__invalid_iterator),\
    unit_test(test__vector_iterator_next__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_next__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_next__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_next__invalid_returned_iterator),\
    unit_test(test__vector_iterator_next__successfully),\
    UT_ITEM(_vector_iterator_prev),\
    unit_test(test__vector_iterator_prev__invalid_iterator),\
    unit_test(test__vector_iterator_prev__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_prev__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_prev__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_prev__invalid_returned_iterator),\
    unit_test(test__vector_iterator_prev__successfully),\
    UT_ITEM(_vector_iterator_next_n),\
    unit_test(test__vector_iterator_next_n__invalid_iterator),\
    unit_test(test__vector_iterator_next_n__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_next_n__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_next_n__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_next_n__move_to_end_invalid_returned_iterator),\
    unit_test(test__vector_iterator_next_n__move_to_begin_invalid_returned_iterator),\
    unit_test(test__vector_iterator_next_n__move_to_end_successfully),\
    unit_test(test__vector_iterator_next_n__move_to_front_successfully),\
    unit_test(test__vector_iterator_next_n__does_not_move_successfully),\
    UT_ITEM(_vector_iterator_prev_n),\
    unit_test(test__vector_iterator_prev_n__invalid_iterator),\
    unit_test(test__vector_iterator_prev_n__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_prev_n__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_prev_n__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_prev_n__move_to_end_invalid_returned_iterator),\
    unit_test(test__vector_iterator_prev_n__move_to_begin_invalid_returned_iterator),\
    unit_test(test__vector_iterator_prev_n__move_to_end_successfully),\
    unit_test(test__vector_iterator_prev_n__move_to_front_successfully),\
    unit_test(test__vector_iterator_prev_n__does_not_move_successfully),\
    UT_ITEM(_vector_iterator_at),\
    unit_test(test__vector_iterator_at__invalid_iterator),\
    unit_test(test__vector_iterator_at__invalid_iterator_container_type),\
    unit_test(test__vector_iterator_at__invalid_iterator_iterator_type),\
    unit_test(test__vector_iterator_at__invalid_iterator_container_pointer),\
    unit_test(test__vector_iterator_at__move_to_end_invalid_returned_iterator),\
    unit_test(test__vector_iterator_at__move_to_begin_invalid_returned_iterator),\
    unit_test(test__vector_iterator_at__end_invalid_iterator),\
    unit_test(test__vector_iterator_at__move_to_end_successfully),\
    unit_test(test__vector_iterator_at__move_to_end_cstr_successfully),\
    unit_test(test__vector_iterator_at__move_to_front_successfully),\
    unit_test(test__vector_iterator_at__move_to_front_cstr_successfully),\
    unit_test(test__vector_iterator_at__does_not_move_successfully),\
    unit_test(test__vector_iterator_at__does_not_move_cstr_successfully),\
    UT_ITEM(_vector_iterator_minus),\
    unit_test(test__vector_iterator_minus__different_container_type),\
    unit_test(test__vector_iterator_minus__different_iterator_type),\
    unit_test(test__vector_iterator_minus__different_container_pointer),\
    unit_test(test__vector_iterator_minus__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_minus__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_minus__first_less_then_second),\
    unit_test(test__vector_iterator_minus__first_greater_then_second),\
    unit_test(test__vector_iterator_minus__first_equal_to_second)

#endif /* _UT_CSTL_VECTOR_ITERATOR_H_ */

