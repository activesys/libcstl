#ifndef _UT_CSTL_LIST_ITERATOR_H_
#define _UT_CSTL_LIST_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_list_iterator)

/*
 * test _create_list_iterator
 */
UT_CASE_DECLARATION(_create_list_iterator)
void test__create_list_iterator__successfully(void** state);
/*
 * test _list_iterator_get_value
 */
UT_CASE_DECLARATION(_list_iterator_get_value)
void test__list_iterator_get_value__invalid_iterator(void** state);
void test__list_iterator_get_value__invalid_iterator_container_type(void** state);
void test__list_iterator_get_value__invalid_iterator_iterator_type(void** state);
void test__list_iterator_get_value__invalid_iterator_end(void** state);
void test__list_iterator_get_value__invalid_data_buffer(void** state);
void test__list_iterator_get_value__successfully(void** state);
void test__list_iterator_get_value__successfully_cstr(void** state);
/*
 * test _list_iterator_set_value
 */
UT_CASE_DECLARATION(_list_iterator_set_value)
void test__list_iterator_set_value__invalid_iter(void** state);
void test__list_iterator_set_value__invalid_iter_container_type(void** state);
void test__list_iterator_set_value__invalid_iter_iterator_type(void** state);
void test__list_iterator_set_value__invalid_iter_end(void** state);
void test__list_iterator_set_value__successfully(void** state);
void test__list_iterator_set_value__successfully_cstr(void** state);
/*
 * test _list_iterator_get_pointer
 */
UT_CASE_DECLARATION(_list_iterator_get_pointer)
void test__list_iterator_get_pointer__invalid_iter(void** state);
void test__list_iterator_get_pointer__invalid_iter_container_type(void** state);
void test__list_iterator_get_pointer__invalid_iter_iterator_type(void** state);
void test__list_iterator_get_pointer__successfully(void** state);
void test__list_iterator_get_pointer__successfully_cstr(void** state);
/*
 * test _list_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DECLARATION(_list_iterator_get_pointer_ignore_cstr)
void test__list_iterator_get_pointer_ignore_cstr__invalid_iter(void** state);
void test__list_iterator_get_pointer_ignore_cstr__invalid_iter_container_type(void** state);
void test__list_iterator_get_pointer_ignore_cstr__invalid_iter_iterator_type(void** state);
void test__list_iterator_get_pointer_ignore_cstr__successfully(void** state);
void test__list_iterator_get_pointer_ignore_cstr__successfully_cstr(void** state);
/*
 * test _list_iterator_next
 */
UT_CASE_DECLARATION(_list_iterator_next)
void test__list_iterator_next__invalid_iter(void** state);
void test__list_iterator_next__invalid_iter_container_type(void** state);
void test__list_iterator_next__invalid_iter_iterator_type(void** state);
void test__list_iterator_next__invalid_iter_end(void** state);
void test__list_iterator_next__successfully_end(void** state);
void test__list_iterator_next__successfully(void** state);
/*
 * test _list_iterator_prev
 */
UT_CASE_DECLARATION(_list_iterator_prev)
void test__list_iterator_prev__invalid_iter(void** state);
void test__list_iterator_prev__invalid_iter_container_type(void** state);
void test__list_iterator_prev__invalid_iter_iterator_type(void** state);
void test__list_iterator_prev__invalid_iter_begin(void** state);
void test__list_iterator_prev__successfully_begin(void** state);
void test__list_iterator_prev__successfully(void** state);
/*
 * test _list_iterator_equal
 */
UT_CASE_DECLARATION(_list_iterator_equal)
void test__list_iterator_equal__first_invalid_container_type(void** state);
void test__list_iterator_equal__first_invalid_iterator_type(void** state);
void test__list_iterator_equal__second_invalid_container_type(void** state);
void test__list_iterator_equal__second_invalid_iterator_type(void** state);
void test__list_iterator_equal__not_same_container(void** state);
void test__list_iterator_equal__first_not_belong_to_list(void** state);
void test__list_iterator_equal__second_not_belong_to_list(void** state);
void test__list_iterator_equal__two_vector_iterator(void** state);
void test__list_iterator_equal__equal(void** state);
void test__list_iterator_equal__not_equal(void** state);
/*
 * test _list_iterator_distance
 */
UT_CASE_DECLARATION(_list_iterator_distance)
void test__list_iterator_distance__first_invalid_container_type(void** state);
void test__list_iterator_distance__first_invalid_iterator_type(void** state);
void test__list_iterator_distance__second_invalid_container_type(void** state);
void test__list_iterator_distance__second_invalid_iterator_type(void** state);
void test__list_iterator_distance__not_same_container(void** state);
void test__list_iterator_distance__first_not_belong_to_list(void** state);
void test__list_iterator_distance__second_not_belong_to_list(void** state);
void test__list_iterator_distance__two_vector_iterator(void** state);
void test__list_iterator_distance__greater_than_0(void** state);
void test__list_iterator_distance__empty(void** state);
void test__list_iterator_distance__non_empty_equal_to_0(void** state);
void test__list_iterator_distance__less_than_0(void** state);
/*
 * test _list_iterator_before
 */
UT_CASE_DECLARATION(_list_iterator_before)
void test__list_iterator_before__first_invalid_container_type(void** state);
void test__list_iterator_before__first_invalid_iterator_type(void** state);
void test__list_iterator_before__second_invalid_container_type(void** state);
void test__list_iterator_before__second_invalid_iterator_type(void** state);
void test__list_iterator_before__not_same_container(void** state);
void test__list_iterator_before__first_not_belong_to_list(void** state);
void test__list_iterator_before__second_not_belong_to_list(void** state);
void test__list_iterator_before__two_vector_iterator(void** state);
void test__list_iterator_before__before(void** state);
void test__list_iterator_before__empty(void** state);
void test__list_iterator_before__non_empty_equal(void** state);
void test__list_iterator_before__after(void** state);

#define UT_CSTL_LIST_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_list_iterator, test__create_list_iterator__successfully),\
    UT_CASE_BEGIN(_list_iterator_get_value, test__list_iterator_get_value__invalid_iterator),\
    UT_CASE(test__list_iterator_get_value__invalid_iterator_container_type),\
    UT_CASE(test__list_iterator_get_value__invalid_iterator_iterator_type),\
    UT_CASE(test__list_iterator_get_value__invalid_iterator_end),\
    UT_CASE(test__list_iterator_get_value__invalid_data_buffer),\
    UT_CASE(test__list_iterator_get_value__successfully),\
    UT_CASE(test__list_iterator_get_value__successfully_cstr),\
    UT_CASE_BEGIN(_list_iterator_set_value, test__list_iterator_set_value__invalid_iter),\
    UT_CASE(test__list_iterator_set_value__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_set_value__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_set_value__invalid_iter_end),\
    UT_CASE(test__list_iterator_set_value__successfully),\
    UT_CASE(test__list_iterator_set_value__successfully_cstr),\
    UT_CASE_BEGIN(_list_iterator_get_pointer, test__list_iterator_get_pointer__invalid_iter),\
    UT_CASE(test__list_iterator_get_pointer__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_get_pointer__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_get_pointer__successfully),\
    UT_CASE(test__list_iterator_get_pointer__successfully_cstr),\
    UT_CASE_BEGIN(_list_iterator_get_pointer_ignore_cstr, test__list_iterator_get_pointer_ignore_cstr__invalid_iter),\
    UT_CASE(test__list_iterator_get_pointer_ignore_cstr__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_get_pointer_ignore_cstr__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_get_pointer_ignore_cstr__successfully),\
    UT_CASE(test__list_iterator_get_pointer_ignore_cstr__successfully_cstr),\
    UT_CASE_BEGIN(_list_iterator_next, test__list_iterator_next__invalid_iter),\
    UT_CASE(test__list_iterator_next__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_next__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_next__invalid_iter_end),\
    UT_CASE(test__list_iterator_next__successfully_end),\
    UT_CASE(test__list_iterator_next__successfully),\
    UT_CASE_BEGIN(_list_iterator_prev, test__list_iterator_prev__invalid_iter),\
    UT_CASE(test__list_iterator_prev__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_prev__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_prev__invalid_iter_begin),\
    UT_CASE(test__list_iterator_prev__successfully_begin),\
    UT_CASE(test__list_iterator_prev__successfully),\
    UT_CASE_BEGIN(_list_iterator_equal, test__list_iterator_equal__first_invalid_container_type),\
    UT_CASE(test__list_iterator_equal__first_invalid_iterator_type),\
    UT_CASE(test__list_iterator_equal__second_invalid_container_type),\
    UT_CASE(test__list_iterator_equal__second_invalid_iterator_type),\
    UT_CASE(test__list_iterator_equal__not_same_container),\
    UT_CASE(test__list_iterator_equal__first_not_belong_to_list),\
    UT_CASE(test__list_iterator_equal__second_not_belong_to_list),\
    UT_CASE(test__list_iterator_equal__two_vector_iterator),\
    UT_CASE(test__list_iterator_equal__equal),\
    UT_CASE(test__list_iterator_equal__not_equal),\
    UT_CASE_BEGIN(_list_iterator_distance, test__list_iterator_distance__first_invalid_container_type),\
    UT_CASE(test__list_iterator_distance__first_invalid_iterator_type),\
    UT_CASE(test__list_iterator_distance__second_invalid_container_type),\
    UT_CASE(test__list_iterator_distance__second_invalid_iterator_type),\
    UT_CASE(test__list_iterator_distance__not_same_container),\
    UT_CASE(test__list_iterator_distance__first_not_belong_to_list),\
    UT_CASE(test__list_iterator_distance__second_not_belong_to_list),\
    UT_CASE(test__list_iterator_distance__two_vector_iterator),\
    UT_CASE(test__list_iterator_distance__greater_than_0),\
    UT_CASE(test__list_iterator_distance__empty),\
    UT_CASE(test__list_iterator_distance__non_empty_equal_to_0),\
    UT_CASE(test__list_iterator_distance__less_than_0),\
    UT_CASE_BEGIN(_list_iterator_before, test__list_iterator_before__first_invalid_container_type),\
    UT_CASE(test__list_iterator_before__first_invalid_iterator_type),\
    UT_CASE(test__list_iterator_before__second_invalid_container_type),\
    UT_CASE(test__list_iterator_before__second_invalid_iterator_type),\
    UT_CASE(test__list_iterator_before__not_same_container),\
    UT_CASE(test__list_iterator_before__first_not_belong_to_list),\
    UT_CASE(test__list_iterator_before__second_not_belong_to_list),\
    UT_CASE(test__list_iterator_before__two_vector_iterator),\
    UT_CASE(test__list_iterator_before__before),\
    UT_CASE(test__list_iterator_before__empty),\
    UT_CASE(test__list_iterator_before__non_empty_equal),\
    UT_CASE(test__list_iterator_before__after)

#endif /* _UT_CSTL_LIST_ITERATOR_H_ */

