#ifndef _UT_CSTL_VECTOR_ITERATOR_H_
#define _UT_CSTL_VECTOR_ITERATOR_H_

/*
 * test _create_vector_iterator
 */
void test__create_vector_iterator__successfully(void** state);
/*
 * test _vector_iterator_equal
 */
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
void test__vector_iterator_get_value__invalid_iterator(void** state);
void test__vector_iterator_get_value__vector_end(void** state);
void test__vector_iterator_get_value__invalid_value_buffer(void** state);
void test__vector_iterator_get_value__successfully(void** state);
void test__vector_iterator_get_value__successfully_cstr(void** state);
/*
 * test _vector_iterator_set_value
 */
void test__vector_iterator_set_value__invalid_iterator(void** state);
void test__vector_iterator_set_value__vector_end(void** state);
void test__vector_iterator_set_value__invalid_value_buffer(void** state);
void test__vector_iterator_set_value__successfully(void** state);
void test__vector_iterator_set_value__successfully_cstr(void** state);

#define UT_CSTL_VECTOR_ITERATOR_CASE \
    unit_test(test__create_vector_iterator__successfully),\
    unit_test(test__vector_iterator_equal__different_container_type),\
    unit_test(test__vector_iterator_equal__different_iterator_type),\
    unit_test(test__vector_iterator_equal__different_container_pointer),\
    unit_test(test__vector_iterator_equal__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_equal__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_equal__equal),\
    unit_test(test__vector_iterator_equal__not_equal),\
    unit_test(test__vector_iterator_less__different_container_type),\
    unit_test(test__vector_iterator_less__different_iterator_type),\
    unit_test(test__vector_iterator_less__different_container_pointer),\
    unit_test(test__vector_iterator_less__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_less__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_less__first_greater_than_second),\
    unit_test(test__vector_iterator_less__first_equal_to_second),\
    unit_test(test__vector_iterator_less__first_less_than_second),\
    unit_test(test__vector_iterator_before__different_container_type),\
    unit_test(test__vector_iterator_before__different_iterator_type),\
    unit_test(test__vector_iterator_before__different_container_pointer),\
    unit_test(test__vector_iterator_before__first_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_before__second_is_not_belong_to_vector),\
    unit_test(test__vector_iterator_before__first_after_second),\
    unit_test(test__vector_iterator_before__first_equal_to_second),\
    unit_test(test__vector_iterator_before__first_before_second),\
    unit_test(test__vector_iterator_get_value__invalid_iterator),\
    unit_test(test__vector_iterator_get_value__vector_end),\
    unit_test(test__vector_iterator_get_value__invalid_value_buffer),\
    unit_test(test__vector_iterator_get_value__successfully),\
    unit_test(test__vector_iterator_get_value__successfully_cstr),\
    unit_test(test__vector_iterator_set_value__invalid_iterator),\
    unit_test(test__vector_iterator_set_value__vector_end),\
    unit_test(test__vector_iterator_set_value__invalid_value_buffer),\
    unit_test(test__vector_iterator_set_value__successfully),\
    unit_test(test__vector_iterator_set_value__successfully_cstr),

#endif /* _UT_CSTL_VECTOR_ITERATOR_H_ */

