#ifndef _UT_CSTL_STRING_H_
#define _UT_CSTL_STRING_H_

UT_SUIT_DECLARATION(cstl_string)

/*
 * test create_string
 */
UT_CASE_DECLARATION(create_string)
void test_create_string__successfully(void** state);
/*
 * test string_init
 */
UT_CASE_DECLARATION(string_init)
void test_string_init__null_string_container(void** state);
void test_string_init__non_created(void** state);
void test_string_init__successfully(void** state);
/*
 * test string_init_char
 */
UT_CASE_DECLARATION(string_init_char)
void test_string_init_char__null(void** state);
void test_string_init_char__non_created(void** state);
void test_string_init_char__empty(void** state);
void test_string_init_char__non_empty(void** state);
/*
 * test string_init_cstr
 */
UT_CASE_DECLARATION(string_init_cstr)
void test_string_init_cstr__null(void** state);
void test_string_init_cstr__non_created(void** state);
void test_string_init_cstr__null_cstr(void** state);
void test_string_init_cstr__empty(void** state);
void test_string_init_cstr__non_empty(void** state);
void test_string_init_cstr__truncate_empty(void** state);
void test_string_init_cstr__truncate_non_empty(void** state);
/*
 * test string_init_subcstr
 */
UT_CASE_DECLARATION(string_init_subcstr)
void test_string_init_subcstr__null_container(void** state);
void test_string_init_subcstr__non_created_container(void** state);
void test_string_init_subcstr__null_cstr(void** state);
void test_string_init_subcstr__cstr_empty(void** state);
void test_string_init_subcstr__length_empty(void** state);
void test_string_init_subcstr__non_empty(void** state);
void test_string_init_subcstr__all(void** state);
void test_string_init_subcstr__truncate_empty(void** state);
void test_string_init_subcstr__truncate_non_empty(void** state);
/*
 * test string_init_copy
 */
UT_CASE_DECLARATION(string_init_copy)
void test_string_init_copy__null_dest(void** state);
void test_string_init_copy__null_src(void** state);
void test_string_init_copy__non_create_dest(void** state);
void test_string_init_copy__non_inited_src(void** state);
void test_string_init_copy__empty(void** state);
void test_string_init_copy__non_empty(void** state);
/*
 * test string_init_copy_substring
 */
UT_CASE_DECLARATION(string_init_copy_substring)
void test_string_init_copy_substring__null_dest(void** state);
void test_string_init_copy_substring__null_src(void** state);
void test_string_init_copy_substring__non_create_dest(void** state);
void test_string_init_copy_substring__non_inited_src(void** state);
void test_string_init_copy_substring__src_non_empty_begin_empty(void** state);
void test_string_init_copy_substring__src_non_empty_begin_non_empty(void** state);
void test_string_init_copy_substring__src_non_empty_begin_length(void** state);
void test_string_init_copy_substring__src_non_empty_begin_npos(void** state);
void test_string_init_copy_substring__src_non_empty_middle_empty(void** state);
void test_string_init_copy_substring__src_non_empty_middle_non_empty(void** state);
void test_string_init_copy_substring__src_non_empty_middle_length(void** state);
void test_string_init_copy_substring__src_non_empty_middle_npos(void** state);
void test_string_init_copy_substring__src_non_empty_end(void** state);
void test_string_init_copy_substring__src_non_empty_npos(void** state);
/*
 * test string_init_copy_range
 */
UT_CASE_DECLARATION(string_init_copy_range)
void test_string_init_copy_range__null_dest(void** state);
void test_string_init_copy_range__invalid_begin_iterator(void** state);
void test_string_init_copy_range__invalid_end_iterator(void** state);
void test_string_init_copy_range__invalid_range(void** state);
void test_string_init_copy_range__empty_range(void** state);
void test_string_init_copy_range__not_empty_range(void** state);
/*
 * test string_destroy
 */
UT_CASE_DECLARATION(string_destroy)
void test_string_destroy__null_string_container(void** state);
void test_string_destroy__non_created(void** state);
void test_string_destroy__created_non_inited(void** state);
void test_string_destroy__inited_empty(void** state);
void test_string_destroy__inited_non_empty(void** state);
/*
 * test string_c_str
 */
UT_CASE_DECLARATION(string_c_str)
void test_string_c_str__null_container(void** state);
void test_string_c_str__non_inited_container(void** state);
void test_string_c_str__empty(void** state);
void test_string_c_str__non_empty(void** state);
/*
 * test string_data
 */
UT_CASE_DECLARATION(string_data)
void test_string_data__null_container(void** state);
void test_string_data__non_inited_container(void** state);
void test_string_data__empty(void** state);
void test_string_data__non_empty(void** state);
/*
 * test string_copy
 */
UT_CASE_DECLARATION(string_copy)
void test_string_copy__null_container(void** state);
void test_string_copy__non_inited_container(void** state);
void test_string_copy__null_buffer(void** state);
void test_string_copy__invalid_position(void** state);
void test_string_copy__begin_empty(void** state);
void test_string_copy__begin_non_empty(void** state);
void test_string_copy__begin_length(void** state);
void test_string_copy__begin_npos(void** state);
void test_string_copy__middle_empty(void** state);
void test_string_copy__middle_non_empty(void** state);
void test_string_copy__middle_length(void** state);
void test_string_copy__middle_npos(void** state);
void test_string_copy__end(void** state);
void test_string_copy__npos(void** state);
/*
 * test string_size
 */
UT_CASE_DECLARATION(string_size)
void test_string_size__null_string_container(void** state);
void test_string_size__non_inited(void** state);
void test_string_size__successfully_empty(void** state);
void test_string_size__successfully_non_empty(void** state);
/*
 * test string_length
 */
UT_CASE_DECLARATION(string_length)
void test_string_length__null_string_container(void** state);
void test_string_length__non_inited(void** state);
void test_string_length__successfully_empty(void** state);
void test_string_length__successfully_non_empty(void** state);
/*
 * test string_empty
 */
UT_CASE_DECLARATION(string_empty)
void test_string_empty__null_string_container(void** state);
void test_string_empty__non_inited(void** state);
void test_string_empty__successfully_empty(void** state);
void test_string_empty__successfully_non_empty(void** state);
/*
 * test string_max_size
 */
UT_CASE_DECLARATION(string_max_size)
void test_string_max_size__null_string_container(void** state);
void test_string_max_size__non_inited(void** state);
void test_string_max_size__successfully(void** state);
/*
 * test string_capacity
 */
UT_CASE_DECLARATION(string_capacity)
void test_string_capacity__null_string_container(void** state);
void test_string_capacity__non_inited(void** state);
void test_string_capacity__successfully_empty(void** state);
void test_string_capacity__successfully_little(void** state);
void test_string_capacity__successfully_huge(void** state);
/*
 * test string_at
 */
UT_CASE_DECLARATION(string_at)
void test_string_at__null_string_container(void** state);
void test_string_at__non_inited_string_container(void** state);
void test_string_at__invalid_subscript_empty(void** state);
void test_string_at__invalid_subscript_end(void** state);
void test_string_at__invalid_subscript(void** state);
void test_string_at__successfully(void** state);
/*
 * test string_equal
 */
UT_CASE_DECLARATION(string_equal)
void test_string_equal__null_first(void** state);
void test_string_equal__null_second(void** state);
void test_string_equal__non_inited_first(void** state);
void test_string_equal__non_inited_second(void** state);
void test_string_equal__same_string(void** state);
void test_string_equal__size_first_less_than_second(void** state);
void test_string_equal__size_first_greater_than_second(void** state);
void test_string_equal__size_equal_0(void** state);
void test_string_equal__size_equal_elem_first_less_than_second(void** state);
void test_string_equal__size_equal_elem_first_greater_than_second(void** state);
void test_string_equal__size_equal_elem_equal(void** state);
/*
 * test string_not_equal
 */
UT_CASE_DECLARATION(string_not_equal)
void test_string_not_equal__null_first(void** state);
void test_string_not_equal__null_second(void** state);
void test_string_not_equal__non_inited_first(void** state);
void test_string_not_equal__non_inited_second(void** state);
void test_string_not_equal__same_string(void** state);
void test_string_not_equal__size_first_less_than_second(void** state);
void test_string_not_equal__size_first_greater_than_second(void** state);
void test_string_not_equal__size_equal_0(void** state);
void test_string_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_string_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_string_not_equal__size_equal_elem_equal(void** state);
/*
 * test string_less
 */
UT_CASE_DECLARATION(string_less)
void test_string_less__null_first(void** state);
void test_string_less__null_second(void** state);
void test_string_less__non_inited_first(void** state);
void test_string_less__non_inited_second(void** state);
void test_string_less__same_string(void** state);
void test_string_less__size_first_less_than_second(void** state);
void test_string_less__size_first_greater_than_second(void** state);
void test_string_less__size_equal_0(void** state);
void test_string_less__size_equal_elem_first_less_than_second(void** state);
void test_string_less__size_equal_elem_first_greater_than_second(void** state);
void test_string_less__size_equal_elem_equal(void** state);
/*
 * test string_less_equal
 */
UT_CASE_DECLARATION(string_less_equal)
void test_string_less_equal__null_first(void** state);
void test_string_less_equal__null_second(void** state);
void test_string_less_equal__non_inited_first(void** state);
void test_string_less_equal__non_inited_second(void** state);
void test_string_less_equal__same_string(void** state);
void test_string_less_equal__size_first_less_than_second(void** state);
void test_string_less_equal__size_first_greater_than_second(void** state);
void test_string_less_equal__size_equal_0(void** state);
void test_string_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_string_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_string_less_equal__size_equal_elem_equal(void** state);
/*
 * test string_greater
 */
UT_CASE_DECLARATION(string_greater)
void test_string_greater__null_first(void** state);
void test_string_greater__null_second(void** state);
void test_string_greater__non_inited_first(void** state);
void test_string_greater__non_inited_second(void** state);
void test_string_greater__same_string(void** state);
void test_string_greater__size_first_less_than_second(void** state);
void test_string_greater__size_first_greater_than_second(void** state);
void test_string_greater__size_equal_0(void** state);
void test_string_greater__size_equal_elem_first_less_than_second(void** state);
void test_string_greater__size_equal_elem_first_greater_than_second(void** state);
void test_string_greater__size_equal_elem_equal(void** state);
/*
 * test string_greater_equal
 */
UT_CASE_DECLARATION(string_greater_equal)
void test_string_greater_equal__null_first(void** state);
void test_string_greater_equal__null_second(void** state);
void test_string_greater_equal__non_inited_first(void** state);
void test_string_greater_equal__non_inited_second(void** state);
void test_string_greater_equal__same_string(void** state);
void test_string_greater_equal__size_first_less_than_second(void** state);
void test_string_greater_equal__size_first_greater_than_second(void** state);
void test_string_greater_equal__size_equal_0(void** state);
void test_string_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_string_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_string_greater_equal__size_equal_elem_equal(void** state);
/*
 * test string_equal_cstr
 */
UT_CASE_DECLARATION(string_equal_cstr)
void test_string_equal_cstr__null_string(void** state);
void test_string_equal_cstr__null_value_string(void** state);
void test_string_equal_cstr__non_inited_string(void** state);
void test_string_equal_cstr__char_empty(void** state);
void test_string_equal_cstr__char_less(void** state);
void test_string_equal_cstr__char_equal(void** state);
void test_string_equal_cstr__char_greater(void** state);
void test_string_equal_cstr__char_size_equal_less(void** state);
void test_string_equal_cstr__char_size_equal_greater(void** state);
/*
 * test string_not_equal_cstr
 */
UT_CASE_DECLARATION(string_not_equal_cstr)
void test_string_not_equal_cstr__null_string(void** state);
void test_string_not_equal_cstr__null_value_string(void** state);
void test_string_not_equal_cstr__non_inited_string(void** state);
void test_string_not_equal_cstr__char_empty(void** state);
void test_string_not_equal_cstr__char_less(void** state);
void test_string_not_equal_cstr__char_equal(void** state);
void test_string_not_equal_cstr__char_greater(void** state);
void test_string_not_equal_cstr__char_size_equal_less(void** state);
void test_string_not_equal_cstr__char_size_equal_greater(void** state);
/*
 * test string_less_cstr
 */
UT_CASE_DECLARATION(string_less_cstr)
void test_string_less_cstr__null_string(void** state);
void test_string_less_cstr__null_value_string(void** state);
void test_string_less_cstr__non_inited_string(void** state);
void test_string_less_cstr__char_empty(void** state);
void test_string_less_cstr__char_less(void** state);
void test_string_less_cstr__char_equal(void** state);
void test_string_less_cstr__char_greater(void** state);
void test_string_less_cstr__char_size_equal_less(void** state);
void test_string_less_cstr__char_size_equal_greater(void** state);
/*
 * test string_less_equal_cstr
 */
UT_CASE_DECLARATION(string_less_equal_cstr)
void test_string_less_equal_cstr__null_string(void** state);
void test_string_less_equal_cstr__null_value_string(void** state);
void test_string_less_equal_cstr__non_inited_string(void** state);
void test_string_less_equal_cstr__char_empty(void** state);
void test_string_less_equal_cstr__char_less(void** state);
void test_string_less_equal_cstr__char_equal(void** state);
void test_string_less_equal_cstr__char_greater(void** state);
void test_string_less_equal_cstr__char_size_equal_less(void** state);
void test_string_less_equal_cstr__char_size_equal_greater(void** state);
/*
 * test string_greater_cstr
 */
UT_CASE_DECLARATION(string_greater_cstr)
void test_string_greater_cstr__null_string(void** state);
void test_string_greater_cstr__null_value_string(void** state);
void test_string_greater_cstr__non_inited_string(void** state);
void test_string_greater_cstr__char_empty(void** state);
void test_string_greater_cstr__char_less(void** state);
void test_string_greater_cstr__char_equal(void** state);
void test_string_greater_cstr__char_greater(void** state);
void test_string_greater_cstr__char_size_equal_less(void** state);
void test_string_greater_cstr__char_size_equal_greater(void** state);
/*
 * test string_greater_equal_cstr
 */
UT_CASE_DECLARATION(string_greater_equal_cstr)
void test_string_greater_equal_cstr__null_string(void** state);
void test_string_greater_equal_cstr__null_value_string(void** state);
void test_string_greater_equal_cstr__non_inited_string(void** state);
void test_string_greater_equal_cstr__char_empty(void** state);
void test_string_greater_equal_cstr__char_less(void** state);
void test_string_greater_equal_cstr__char_equal(void** state);
void test_string_greater_equal_cstr__char_greater(void** state);
void test_string_greater_equal_cstr__char_size_equal_less(void** state);
void test_string_greater_equal_cstr__char_size_equal_greater(void** state);
/*
 * test string_compare
 */
UT_CASE_DECLARATION(string_compare)
void test_string_compare__null_first(void** state);
void test_string_compare__null_second(void** state);
void test_string_compare__non_inited_first(void** state);
void test_string_compare__non_inited_second(void** state);
void test_string_compare__same_string(void** state);
void test_string_compare__char_size_first_less_than_second(void** state);
void test_string_compare__char_size_first_greater_than_second(void** state);
void test_string_compare__char_size_equal_0(void** state);
void test_string_compare__char_size_equal_elem_first_less_than_second(void** state);
void test_string_compare__char_size_equal_elem_first_greater_than_second(void** state);
void test_string_compare__char_size_equal_elem_equal(void** state);
/*
 * test string_compare_substring_string
 */
UT_CASE_DECLARATION(string_compare_substring_string)
void test_string_compare_substring_string__null_first(void** state);
void test_string_compare_substring_string__null_second(void** state);
void test_string_compare_substring_string__non_inited_first(void** state);
void test_string_compare_substring_string__non_inited_second(void** state);
void test_string_compare_substring_string__invalid_pos(void** state);
void test_string_compare_substring_string__char_sub_size_less(void** state);
void test_string_compare_substring_string__char_sub_content_less(void** state);
void test_string_compare_substring_string__char_sub_equal(void** state);
void test_string_compare_substring_string__char_sub_size_greater(void** state);
void test_string_compare_substring_string__char_sub_content_greater(void** state);
void test_string_compare_substring_string__char_all_size_less(void** state);
void test_string_compare_substring_string__char_all_content_less(void** state);
void test_string_compare_substring_string__char_all_equal(void** state);
void test_string_compare_substring_string__char_all_size_greater(void** state);
void test_string_compare_substring_string__char_all_content_greater(void** state);
void test_string_compare_substring_string__char_empty_non_empty(void** state);
void test_string_compare_substring_string__char_non_empty_empty(void** state);
void test_string_compare_substring_string__char_empty_empty(void** state);
/*
 * test string_compare_substring_substring
 */
UT_CASE_DECLARATION(string_compare_substring_substring)
void test_string_compare_substring_substring__null_first(void** state);
void test_string_compare_substring_substring__null_second(void** state);
void test_string_compare_substring_substring__non_inited_first(void** state);
void test_string_compare_substring_substring__non_inited_second(void** state);
void test_string_compare_substring_substring__invalid_first_pos(void** state);
void test_string_compare_substring_substring__invalid_second_pos(void** state);
void test_string_compare_substring_substring__char_sub_size_less(void** state);
void test_string_compare_substring_substring__char_sub_content_less(void** state);
void test_string_compare_substring_substring__char_sub_equal(void** state);
void test_string_compare_substring_substring__char_sub_size_greater(void** state);
void test_string_compare_substring_substring__char_sub_content_greater(void** state);
void test_string_compare_substring_substring__char_all_size_less(void** state);
void test_string_compare_substring_substring__char_all_content_less(void** state);
void test_string_compare_substring_substring__char_all_equal(void** state);
void test_string_compare_substring_substring__char_all_size_greater(void** state);
void test_string_compare_substring_substring__char_all_content_greater(void** state);
void test_string_compare_substring_substring__char_empty_non_empty(void** state);
void test_string_compare_substring_substring__char_non_empty_empty(void** state);
void test_string_compare_substring_substring__char_empty_empty(void** state);
/*
 * test string_compare_cstr
 */
UT_CASE_DECLARATION(string_compare_cstr)
void test_string_compare_cstr__null_string(void** state);
void test_string_compare_cstr__null_value_string(void** state);
void test_string_compare_cstr__non_inited_string(void** state);
void test_string_compare_cstr__char_empty(void** state);
void test_string_compare_cstr__char_less(void** state);
void test_string_compare_cstr__char_equal(void** state);
void test_string_compare_cstr__char_greater(void** state);
void test_string_compare_cstr__char_size_equal_less(void** state);
void test_string_compare_cstr__char_size_equal_greater(void** state);
/*
 * test string_compare_substring_cstr
 */
UT_CASE_DECLARATION(string_compare_substring_cstr)
void test_string_compare_substring_cstr__null_string(void** state);
void test_string_compare_substring_cstr__null_value_string(void** state);
void test_string_compare_substring_cstr__non_inited_string(void** state);
void test_string_compare_substring_cstr__invalid_pos(void** state);
void test_string_compare_substring_cstr__char_empty_empty(void** state);
void test_string_compare_substring_cstr__char_non_empty_empty(void** state);
void test_string_compare_substring_cstr__char_empty_non_empty(void** state);
void test_string_compare_substring_cstr__char_sub_size_less(void** state);
void test_string_compare_substring_cstr__char_sub_content_less(void** state);
void test_string_compare_substring_cstr__char_sub_equal(void** state);
void test_string_compare_substring_cstr__char_sub_size_greater(void** state);
void test_string_compare_substring_cstr__char_sub_content_greater(void** state);
void test_string_compare_substring_cstr__char_all_size_less(void** state);
void test_string_compare_substring_cstr__char_all_content_less(void** state);
void test_string_compare_substring_cstr__char_all_equal(void** state);
void test_string_compare_substring_cstr__char_all_size_greater(void** state);
void test_string_compare_substring_cstr__char_all_content_greater(void** state);
/*
 * test string_compare_substring_subcstr
 */
UT_CASE_DECLARATION(string_compare_substring_subcstr)
void test_string_compare_substring_subcstr__null_string(void** state);
void test_string_compare_substring_subcstr__null_value_string(void** state);
void test_string_compare_substring_subcstr__non_inited_string(void** state);
void test_string_compare_substring_subcstr__invalid_pos(void** state);
void test_string_compare_substring_subcstr__char_empty_empty(void** state);
void test_string_compare_substring_subcstr__char_non_empty_empty(void** state);
void test_string_compare_substring_subcstr__char_empty_non_empty(void** state);
void test_string_compare_substring_subcstr__char_sub_size_less(void** state);
void test_string_compare_substring_subcstr__char_sub_content_less(void** state);
void test_string_compare_substring_subcstr__char_sub_equal(void** state);
void test_string_compare_substring_subcstr__char_sub_size_greater(void** state);
void test_string_compare_substring_subcstr__char_sub_content_greater(void** state);
void test_string_compare_substring_subcstr__char_all_size_less(void** state);
void test_string_compare_substring_subcstr__char_all_content_less(void** state);
void test_string_compare_substring_subcstr__char_all_equal(void** state);
void test_string_compare_substring_subcstr__char_all_size_greater(void** state);
void test_string_compare_substring_subcstr__char_all_content_greater(void** state);
/*
 * test string_substr
 */
UT_CASE_DECLARATION(string_substr)
void test_string_substr__null_string(void** state);
void test_string_substr__non_inited_string(void** state);
void test_string_substr__invalid_pos(void** state);
void test_string_substr__empty_substr(void** state);
void test_string_substr__all(void** state);
void test_string_substr__begin(void** state);
void test_string_substr__middle(void** state);
void test_string_substr__end(void** state);
/*
 * test string_connect
 */
UT_CASE_DECLARATION(string_connect)
void test_string_connect__null_dest(void** state);
void test_string_connect__null_src(void** state);
void test_string_connect__non_inited_dest(void** state);
void test_string_connect__non_inited_src(void** state);
void test_string_connect__empty_empty(void** state);
void test_string_connect__non_empty_empty(void** state);
void test_string_connect__empty_non_empty(void** state);
void test_string_connect__same(void** state);
void test_string_connect__char(void** state);
/*
 * test string_connect_cstr
 */
UT_CASE_DECLARATION(string_connect_cstr)
void test_string_connect_cstr__null_string(void** state);
void test_string_connect_cstr__null_value_string(void** state);
void test_string_connect_cstr__non_inited_string(void** state);
void test_string_connect_cstr__empty_empty(void** state);
void test_string_connect_cstr__non_empty_empty(void** state);
void test_string_connect_cstr__empty_non_empty(void** state);
void test_string_connect_cstr__char(void** state);
/*
 * test string_connect_char
 */
UT_CASE_DECLARATION(string_connect_char)
void test_string_connect_char__null_string_container(void** state);
void test_string_connect_char__non_inited_string_container(void** state);
void test_string_connect_char__empty_container(void** state);
void test_string_connect_char__non_empty_container(void** state);
/*
 * test string_find
 */
UT_CASE_DECLARATION(string_find)
void test_string_find__null_string(void** state);
void test_string_find__null_find(void** state);
void test_string_find__non_inited_string(void** state);
void test_string_find__non_inited_find(void** state);
void test_string_find__invalid_pos(void** state);
void test_string_find__same_begin(void** state);
void test_string_find__same_middle(void** state);
void test_string_find__char_begin_empty(void** state);
void test_string_find__char_begin_find(void** state);
void test_string_find__char_begin_not_find(void** state);
void test_string_find__char_middle_empty(void** state);
void test_string_find__char_middle_find(void** state);
void test_string_find__char_middle_not_find(void** state);
void test_string_find__char_middle_not_find_pos(void** state);
/*
 * test string_find_cstr
 */
UT_CASE_DECLARATION(string_find_cstr)
void test_string_find_cstr__null_string(void** state);
void test_string_find_cstr__null_find(void** state);
void test_string_find_cstr__non_inited_string(void** state);
void test_string_find_cstr__invalid_pos(void** state);
void test_string_find_cstr__char_begin_empty(void** state);
void test_string_find_cstr__char_begin_find(void** state);
void test_string_find_cstr__char_begin_not_find(void** state);
void test_string_find_cstr__char_middle_empty(void** state);
void test_string_find_cstr__char_middle_find(void** state);
void test_string_find_cstr__char_middle_not_find(void** state);
void test_string_find_cstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_subcstr
 */
UT_CASE_DECLARATION(string_find_subcstr)
void test_string_find_subcstr__null_string(void** state);
void test_string_find_subcstr__null_find(void** state);
void test_string_find_subcstr__non_inited_string(void** state);
void test_string_find_subcstr__invalid_pos(void** state);
void test_string_find_subcstr__char_begin_empty(void** state);
void test_string_find_subcstr__char_begin_length_0(void** state);
void test_string_find_subcstr__char_begin_find(void** state);
void test_string_find_subcstr__char_begin_not_find(void** state);
void test_string_find_subcstr__char_middle_empty(void** state);
void test_string_find_subcstr__char_middle_length_0(void** state);
void test_string_find_subcstr__char_middle_find(void** state);
void test_string_find_subcstr__char_middle_not_find(void** state);
void test_string_find_subcstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_char
 */
UT_CASE_DECLARATION(string_find_char)
void test_string_find_char__null_string_container(void** state);
void test_string_find_char__non_init_string_container(void** state);
void test_string_find_char__invalid_position(void** state);
void test_string_find_char__invalid_position_end(void** state);
void test_string_find_char__invalid_position_NPOS(void** state);
void test_string_find_char__find_failure(void** state);
void test_string_find_char__find_failure_middle_pos(void** state);
void test_string_find_char__find_successful(void** state);
void test_string_find_char__find_successful_middle(void** state);
void test_string_find_char__find_successful_back(void** state);
void test_string_find_char__find_successful_middle_pos(void** state);
/*
 * test string_rfind
 */
UT_CASE_DECLARATION(string_rfind)
void test_string_rfind__null_string(void** state);
void test_string_rfind__null_find(void** state);
void test_string_rfind__non_inited_string(void** state);
void test_string_rfind__non_inited_find(void** state);
void test_string_rfind__same_npos(void** state);
void test_string_rfind__same_middle(void** state);
void test_string_rfind__char_empty_empty_0(void** state);
void test_string_rfind__char_empty_empty_npos(void** state);
void test_string_rfind__char_empty_non_empty_0(void** state);
void test_string_rfind__char_empty_non_empty_npos(void** state);
void test_string_rfind__char_empty_npos(void** state);
void test_string_rfind__char_find_npos(void** state);
void test_string_rfind__char_not_find_npos(void** state);
void test_string_rfind__char_middle_empty(void** state);
void test_string_rfind__char_middle_find(void** state);
void test_string_rfind__char_middle_not_find(void** state);
void test_string_rfind__char_middle_not_find_pos(void** state);
/*
 * test string_rfind_cstr
 */
UT_CASE_DECLARATION(string_rfind_cstr)
void test_string_rfind_cstr__null_string(void** state);
void test_string_rfind_cstr__null_find(void** state);
void test_string_rfind_cstr__non_inited_string(void** state);
void test_string_rfind_cstr__char_empty_empty_0(void** state);
void test_string_rfind_cstr__char_empty_empty_npos(void** state);
void test_string_rfind_cstr__char_empty_non_empty_0(void** state);
void test_string_rfind_cstr__char_empty_non_empty_npos(void** state);
void test_string_rfind_cstr__char_empty_npos(void** state);
void test_string_rfind_cstr__char_find_npos(void** state);
void test_string_rfind_cstr__char_not_find_npos(void** state);
void test_string_rfind_cstr__char_middle_empty(void** state);
void test_string_rfind_cstr__char_middle_find(void** state);
void test_string_rfind_cstr__char_middle_not_find(void** state);
void test_string_rfind_cstr__char_middle_not_find_pos(void** state);
/*
 * test string_rfind_subcstr
 */
UT_CASE_DECLARATION(string_rfind_subcstr)
void test_string_rfind_subcstr__null_string(void** state);
void test_string_rfind_subcstr__null_find(void** state);
void test_string_rfind_subcstr__non_inited_string(void** state);
void test_string_rfind_subcstr__char_empty_empty_0(void** state);
void test_string_rfind_subcstr__char_empty_empty_npos(void** state);
void test_string_rfind_subcstr__char_empty_non_empty_0_length_0(void** state);
void test_string_rfind_subcstr__char_empty_non_empty_npos_length_0(void** state);
void test_string_rfind_subcstr__char_empty_non_empty_0(void** state);
void test_string_rfind_subcstr__char_empty_non_empty_npos(void** state);
void test_string_rfind_subcstr__char_empty_npos(void** state);
void test_string_rfind_subcstr__char_non_empty_npos_length_0(void** state);
void test_string_rfind_subcstr__char_find_npos(void** state);
void test_string_rfind_subcstr__char_not_find_npos(void** state);
void test_string_rfind_subcstr__char_middle_empty(void** state);
void test_string_rfind_subcstr__char_middle_non_empty_length_0(void** state);
void test_string_rfind_subcstr__char_middle_find(void** state);
void test_string_rfind_subcstr__char_middle_not_find(void** state);
void test_string_rfind_subcstr__char_middle_not_find_pos(void** state);
/*
 * test string_rfind_char
 */
UT_CASE_DECLARATION(string_rfind_char)
void test_string_rfind_char__null_string_container(void** state);
void test_string_rfind_char__non_init_string_container(void** state);
void test_string_rfind_char__invalid_position(void** state);
void test_string_rfind_char__invalid_position_begin(void** state);
void test_string_rfind_char__invalid_position_NPOS(void** state);
void test_string_rfind_char__find_failure(void** state);
void test_string_rfind_char__find_failure_middle_pos(void** state);
void test_string_rfind_char__find_successful(void** state);
void test_string_rfind_char__find_successful_middle(void** state);
void test_string_rfind_char__find_successful_back(void** state);
void test_string_rfind_char__find_successful_middle_pos(void** state);
/*
 * test string_find_first_of
 */
UT_CASE_DECLARATION(string_find_first_of)
void test_string_find_first_of__null_string(void** state);
void test_string_find_first_of__null_find(void** state);
void test_string_find_first_of__non_inited_string(void** state);
void test_string_find_first_of__non_inited_find(void** state);
void test_string_find_first_of__invalid_pos(void** state);
void test_string_find_first_of__same_begin(void** state);
void test_string_find_first_of__same_middle(void** state);
void test_string_find_first_of__char_begin_empty(void** state);
void test_string_find_first_of__char_begin_find(void** state);
void test_string_find_first_of__char_begin_not_find(void** state);
void test_string_find_first_of__char_middle_empty(void** state);
void test_string_find_first_of__char_middle_find(void** state);
void test_string_find_first_of__char_middle_not_find(void** state);
void test_string_find_first_of__char_middle_not_find_pos(void** state);
/*
 * test string_find_first_of_cstr
 */
UT_CASE_DECLARATION(string_find_first_of_cstr)
void test_string_find_first_of_cstr__null_string(void** state);
void test_string_find_first_of_cstr__null_find(void** state);
void test_string_find_first_of_cstr__non_inited_string(void** state);
void test_string_find_first_of_cstr__invalid_pos(void** state);
void test_string_find_first_of_cstr__char_begin_empty(void** state);
void test_string_find_first_of_cstr__char_begin_find(void** state);
void test_string_find_first_of_cstr__char_begin_not_find(void** state);
void test_string_find_first_of_cstr__char_middle_empty(void** state);
void test_string_find_first_of_cstr__char_middle_find(void** state);
void test_string_find_first_of_cstr__char_middle_not_find(void** state);
void test_string_find_first_of_cstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_first_of_subcstr
 */
UT_CASE_DECLARATION(string_find_first_of_subcstr)
void test_string_find_first_of_subcstr__null_string(void** state);
void test_string_find_first_of_subcstr__null_find(void** state);
void test_string_find_first_of_subcstr__non_inited_string(void** state);
void test_string_find_first_of_subcstr__invalid_pos(void** state);
void test_string_find_first_of_subcstr__char_begin_empty(void** state);
void test_string_find_first_of_subcstr__char_begin_length_0(void** state);
void test_string_find_first_of_subcstr__char_begin_find(void** state);
void test_string_find_first_of_subcstr__char_begin_not_find(void** state);
void test_string_find_first_of_subcstr__char_middle_empty(void** state);
void test_string_find_first_of_subcstr__char_middle_length_0(void** state);
void test_string_find_first_of_subcstr__char_middle_find(void** state);
void test_string_find_first_of_subcstr__char_middle_not_find(void** state);
void test_string_find_first_of_subcstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_first_of_char
 */
UT_CASE_DECLARATION(string_find_first_of_char)
void test_string_find_first_of_char__null_string_container(void** state);
void test_string_find_first_of_char__non_init_string_container(void** state);
void test_string_find_first_of_char__invalid_position(void** state);
void test_string_find_first_of_char__invalid_position_end(void** state);
void test_string_find_first_of_char__invalid_position_NPOS(void** state);
void test_string_find_first_of_char__find_failure(void** state);
void test_string_find_first_of_char__find_failure_middle_pos(void** state);
void test_string_find_first_of_char__find_successful(void** state);
void test_string_find_first_of_char__find_successful_middle(void** state);
void test_string_find_first_of_char__find_successful_back(void** state);
void test_string_find_first_of_char__find_successful_middle_pos(void** state);
/*
 * test string_find_first_not_of
 */
UT_CASE_DECLARATION(string_find_first_not_of)
void test_string_find_first_not_of__null_string(void** state);
void test_string_find_first_not_of__null_find(void** state);
void test_string_find_first_not_of__non_inited_string(void** state);
void test_string_find_first_not_of__non_inited_find(void** state);
void test_string_find_first_not_of__invalid_pos(void** state);
void test_string_find_first_not_of__same_begin(void** state);
void test_string_find_first_not_of__same_middle(void** state);
void test_string_find_first_not_of__char_begin_empty(void** state);
void test_string_find_first_not_of__char_begin_find(void** state);
void test_string_find_first_not_of__char_begin_not_find(void** state);
void test_string_find_first_not_of__char_middle_empty(void** state);
void test_string_find_first_not_of__char_middle_find(void** state);
void test_string_find_first_not_of__char_middle_not_find(void** state);
void test_string_find_first_not_of__char_middle_not_find_pos(void** state);
/*
 * test string_find_first_not_of_cstr
 */
UT_CASE_DECLARATION(string_find_first_not_of_cstr)
void test_string_find_first_not_of_cstr__null_string(void** state);
void test_string_find_first_not_of_cstr__null_find(void** state);
void test_string_find_first_not_of_cstr__non_inited_string(void** state);
void test_string_find_first_not_of_cstr__invalid_pos(void** state);
void test_string_find_first_not_of_cstr__char_begin_empty(void** state);
void test_string_find_first_not_of_cstr__char_begin_find(void** state);
void test_string_find_first_not_of_cstr__char_begin_not_find(void** state);
void test_string_find_first_not_of_cstr__char_middle_empty(void** state);
void test_string_find_first_not_of_cstr__char_middle_find(void** state);
void test_string_find_first_not_of_cstr__char_middle_not_find(void** state);
void test_string_find_first_not_of_cstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_first_not_of_subcstr
 */
UT_CASE_DECLARATION(string_find_first_not_of_subcstr)
void test_string_find_first_not_of_subcstr__null_string(void** state);
void test_string_find_first_not_of_subcstr__null_find(void** state);
void test_string_find_first_not_of_subcstr__non_inited_string(void** state);
void test_string_find_first_not_of_subcstr__invalid_pos(void** state);
void test_string_find_first_not_of_subcstr__char_begin_empty(void** state);
void test_string_find_first_not_of_subcstr__char_begin_length_0(void** state);
void test_string_find_first_not_of_subcstr__char_begin_find(void** state);
void test_string_find_first_not_of_subcstr__char_begin_not_find(void** state);
void test_string_find_first_not_of_subcstr__char_middle_empty(void** state);
void test_string_find_first_not_of_subcstr__char_middle_length_0(void** state);
void test_string_find_first_not_of_subcstr__char_middle_find(void** state);
void test_string_find_first_not_of_subcstr__char_middle_not_find(void** state);
void test_string_find_first_not_of_subcstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_first_not_of_char
 */
UT_CASE_DECLARATION(string_find_first_not_of_char)
void test_string_find_first_not_of_char__null_string_container(void** state);
void test_string_find_first_not_of_char__non_init_string_container(void** state);
void test_string_find_first_not_of_char__invalid_position(void** state);
void test_string_find_first_not_of_char__invalid_position_end(void** state);
void test_string_find_first_not_of_char__invalid_position_NPOS(void** state);
void test_string_find_first_not_of_char__find_first_not_of_failure(void** state);
void test_string_find_first_not_of_char__find_first_not_of_failure_middle_pos(void** state);
void test_string_find_first_not_of_char__find_first_not_of_successful(void** state);
void test_string_find_first_not_of_char__find_first_not_of_successful_middle(void** state);
void test_string_find_first_not_of_char__find_first_not_of_successful_back(void** state);
void test_string_find_first_not_of_char__find_first_not_of_successful_middle_pos(void** state);
/*
 * test string_find_last_of
 */
UT_CASE_DECLARATION(string_find_last_of)
void test_string_find_last_of__null_string(void** state);
void test_string_find_last_of__null_find(void** state);
void test_string_find_last_of__non_inited_string(void** state);
void test_string_find_last_of__non_inited_find(void** state);
void test_string_find_last_of__same_npos(void** state);
void test_string_find_last_of__same_middle(void** state);
void test_string_find_last_of__char_empty_empty_0(void** state);
void test_string_find_last_of__char_empty_empty_npos(void** state);
void test_string_find_last_of__char_empty_non_empty_0(void** state);
void test_string_find_last_of__char_empty_non_empty_npos(void** state);
void test_string_find_last_of__char_empty_npos(void** state);
void test_string_find_last_of__char_find_npos(void** state);
void test_string_find_last_of__char_not_find_npos(void** state);
void test_string_find_last_of__char_middle_empty(void** state);
void test_string_find_last_of__char_middle_find(void** state);
void test_string_find_last_of__char_middle_not_find(void** state);
void test_string_find_last_of__char_middle_not_find_pos(void** state);
/*
 * test string_find_last_of_cstr
 */
UT_CASE_DECLARATION(string_find_last_of_cstr)
void test_string_find_last_of_cstr__null_string(void** state);
void test_string_find_last_of_cstr__null_find(void** state);
void test_string_find_last_of_cstr__non_inited_string(void** state);
void test_string_find_last_of_cstr__char_empty_empty_0(void** state);
void test_string_find_last_of_cstr__char_empty_empty_npos(void** state);
void test_string_find_last_of_cstr__char_empty_non_empty_0(void** state);
void test_string_find_last_of_cstr__char_empty_non_empty_npos(void** state);
void test_string_find_last_of_cstr__char_empty_npos(void** state);
void test_string_find_last_of_cstr__char_find_npos(void** state);
void test_string_find_last_of_cstr__char_not_find_npos(void** state);
void test_string_find_last_of_cstr__char_middle_empty(void** state);
void test_string_find_last_of_cstr__char_middle_find(void** state);
void test_string_find_last_of_cstr__char_middle_not_find(void** state);
void test_string_find_last_of_cstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_last_of_subcstr
 */
UT_CASE_DECLARATION(string_find_last_of_subcstr)
void test_string_find_last_of_subcstr__null_string(void** state);
void test_string_find_last_of_subcstr__null_find(void** state);
void test_string_find_last_of_subcstr__non_inited_string(void** state);
void test_string_find_last_of_subcstr__char_empty_empty_0(void** state);
void test_string_find_last_of_subcstr__char_empty_empty_npos(void** state);
void test_string_find_last_of_subcstr__char_empty_non_empty_0_length_0(void** state);
void test_string_find_last_of_subcstr__char_empty_non_empty_npos_length_0(void** state);
void test_string_find_last_of_subcstr__char_empty_non_empty_0(void** state);
void test_string_find_last_of_subcstr__char_empty_non_empty_npos(void** state);
void test_string_find_last_of_subcstr__char_empty_npos(void** state);
void test_string_find_last_of_subcstr__char_non_empty_npos_length_0(void** state);
void test_string_find_last_of_subcstr__char_find_npos(void** state);
void test_string_find_last_of_subcstr__char_not_find_npos(void** state);
void test_string_find_last_of_subcstr__char_middle_empty(void** state);
void test_string_find_last_of_subcstr__char_middle_non_empty_length_0(void** state);
void test_string_find_last_of_subcstr__char_middle_find(void** state);
void test_string_find_last_of_subcstr__char_middle_not_find(void** state);
void test_string_find_last_of_subcstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_last_of_char
 */
UT_CASE_DECLARATION(string_find_last_of_char)
void test_string_find_last_of_char__null_string_container(void** state);
void test_string_find_last_of_char__non_init_string_container(void** state);
void test_string_find_last_of_char__invalid_position(void** state);
void test_string_find_last_of_char__invalid_position_begin(void** state);
void test_string_find_last_of_char__invalid_position_NPOS(void** state);
void test_string_find_last_of_char__find_failure(void** state);
void test_string_find_last_of_char__find_failure_middle_pos(void** state);
void test_string_find_last_of_char__find_successful(void** state);
void test_string_find_last_of_char__find_successful_middle(void** state);
void test_string_find_last_of_char__find_successful_back(void** state);
void test_string_find_last_of_char__find_successful_middle_pos(void** state);
/*
 * test string_find_last_not_of
 */
UT_CASE_DECLARATION(string_find_last_not_of)
void test_string_find_last_not_of__null_string(void** state);
void test_string_find_last_not_of__null_find(void** state);
void test_string_find_last_not_of__non_inited_string(void** state);
void test_string_find_last_not_of__non_inited_find(void** state);
void test_string_find_last_not_of__same_npos(void** state);
void test_string_find_last_not_of__same_middle(void** state);
void test_string_find_last_not_of__char_empty_empty_0(void** state);
void test_string_find_last_not_of__char_empty_empty_npos(void** state);
void test_string_find_last_not_of__char_empty_non_empty_0(void** state);
void test_string_find_last_not_of__char_empty_non_empty_npos(void** state);
void test_string_find_last_not_of__char_empty_npos(void** state);
void test_string_find_last_not_of__char_find_npos(void** state);
void test_string_find_last_not_of__char_not_find_npos(void** state);
void test_string_find_last_not_of__char_middle_empty(void** state);
void test_string_find_last_not_of__char_middle_find(void** state);
void test_string_find_last_not_of__char_middle_not_find(void** state);
void test_string_find_last_not_of__char_middle_not_find_pos(void** state);
/*
 * test string_find_last_not_of_cstr
 */
UT_CASE_DECLARATION(string_find_last_not_of_cstr)
void test_string_find_last_not_of_cstr__null_string(void** state);
void test_string_find_last_not_of_cstr__null_find(void** state);
void test_string_find_last_not_of_cstr__non_inited_string(void** state);
void test_string_find_last_not_of_cstr__char_empty_empty_0(void** state);
void test_string_find_last_not_of_cstr__char_empty_empty_npos(void** state);
void test_string_find_last_not_of_cstr__char_empty_non_empty_0(void** state);
void test_string_find_last_not_of_cstr__char_empty_non_empty_npos(void** state);
void test_string_find_last_not_of_cstr__char_empty_npos(void** state);
void test_string_find_last_not_of_cstr__char_find_npos(void** state);
void test_string_find_last_not_of_cstr__char_not_find_npos(void** state);
void test_string_find_last_not_of_cstr__char_middle_empty(void** state);
void test_string_find_last_not_of_cstr__char_middle_find(void** state);
void test_string_find_last_not_of_cstr__char_middle_not_find(void** state);
void test_string_find_last_not_of_cstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_last_not_of_subcstr
 */
UT_CASE_DECLARATION(string_find_last_not_of_subcstr)
void test_string_find_last_not_of_subcstr__null_string(void** state);
void test_string_find_last_not_of_subcstr__null_find(void** state);
void test_string_find_last_not_of_subcstr__non_inited_string(void** state);
void test_string_find_last_not_of_subcstr__char_empty_empty_0(void** state);
void test_string_find_last_not_of_subcstr__char_empty_empty_npos(void** state);
void test_string_find_last_not_of_subcstr__char_empty_non_empty_0_length_0(void** state);
void test_string_find_last_not_of_subcstr__char_empty_non_empty_npos_length_0(void** state);
void test_string_find_last_not_of_subcstr__char_empty_non_empty_0(void** state);
void test_string_find_last_not_of_subcstr__char_empty_non_empty_npos(void** state);
void test_string_find_last_not_of_subcstr__char_empty_npos(void** state);
void test_string_find_last_not_of_subcstr__char_non_empty_npos_length_0(void** state);
void test_string_find_last_not_of_subcstr__char_find_npos(void** state);
void test_string_find_last_not_of_subcstr__char_not_find_npos(void** state);
void test_string_find_last_not_of_subcstr__char_middle_empty(void** state);
void test_string_find_last_not_of_subcstr__char_middle_non_empty_length_0(void** state);
void test_string_find_last_not_of_subcstr__char_middle_find(void** state);
void test_string_find_last_not_of_subcstr__char_middle_not_find(void** state);
void test_string_find_last_not_of_subcstr__char_middle_not_find_pos(void** state);
/*
 * test string_find_last_not_of_char
 */
UT_CASE_DECLARATION(string_find_last_not_of_char)
void test_string_find_last_not_of_char__null_string_container(void** state);
void test_string_find_last_not_of_char__non_init_string_container(void** state);
void test_string_find_last_not_of_char__invalid_position(void** state);
void test_string_find_last_not_of_char__invalid_position_begin(void** state);
void test_string_find_last_not_of_char__invalid_position_NPOS(void** state);
void test_string_find_last_not_of_char__find_failure(void** state);
void test_string_find_last_not_of_char__find_failure_middle_pos(void** state);
void test_string_find_last_not_of_char__find_successful(void** state);
void test_string_find_last_not_of_char__find_successful_middle(void** state);
void test_string_find_last_not_of_char__find_successful_back(void** state);
void test_string_find_last_not_of_char__find_successful_middle_pos(void** state);
/*
 * test string_begin
 */
UT_CASE_DECLARATION(string_begin)
void test_string_begin__null_string_container(void** state);
void test_string_begin__non_inited_string_container(void** state);
void test_string_begin__empty(void** state);
void test_string_begin__non_empty(void** state);
/*
 * test string_end
 */
UT_CASE_DECLARATION(string_end)
void test_string_end__null_string_container(void** state);
void test_string_end__non_inited_string_container(void** state);
void test_string_end__empty(void** state);
void test_string_end__non_empty(void** state);
/*
 * test string_clear
 */
UT_CASE_DECLARATION(string_clear)
void test_string_clear__null_string_container(void** state);
void test_string_clear__non_inited_string_container(void** state);
void test_string_clear__empty_string_container(void** state);
void test_string_clear__non_empty_string_container(void** state);
/*
 * test string_swap
 */
UT_CASE_DECLARATION(string_swap)
void test_string_swap__null_first(void** state);
void test_string_swap__null_second(void** state);
void test_string_swap__non_inited_first(void** state);
void test_string_swap__non_inited_second(void** state);
void test_string_swap__string_equal(void** state);
void test_string_swap__0_swap_10(void** state);
void test_string_swap__10_swap_0(void** state);
void test_string_swap__10_swap_10(void** state);
/*
 * test string_reserve
 */
UT_CASE_DECLARATION(string_reserve)
void test_string_reserve__null_string_container(void** state);
void test_string_reserve__non_inited(void** state);
void test_string_reserve__shrink(void** state);
void test_string_reserve__not_change(void** state);
void test_string_reserve__expand(void** state);
/*
 * test string_assign
 */
UT_CASE_DECLARATION(string_assign)
void test_string_assign__null_dest(void** state);
void test_string_assign__null_src(void** state);
void test_string_assign__non_inited_dest(void** state);
void test_string_assign__non_inited_src(void** state);
void test_string_assign__same_container(void** state);
void test_string_assign__0_assign_0(void** state);
void test_string_assign__0_assign_10(void** state);
void test_string_assign__0_assign_1000(void** state);
void test_string_assign__10_assign_0(void** state);
void test_string_assign__10_assign_10_string_equal(void** state);
void test_string_assign__10_assign_10_string_not_equal(void** state);
void test_string_assign__10_assign_1000(void** state);
void test_string_assign__1000_assign_0(void** state);
void test_string_assign__1000_assign_10(void** state);
void test_string_assign__1000_assign_1010(void** state);
void test_string_assign__1000_assign_1810(void** state);
/*
 * test string_assign_substring
 */
UT_CASE_DECLARATION(string_assign_substring)
void test_string_assign_substring__null_dest(void** state);
void test_string_assign_substring__null_src(void** state);
void test_string_assign_substring__non_inited_dest(void** state);
void test_string_assign_substring__non_inited_src(void** state);
void test_string_assign_substring__successfully_src_non_empty_begin_empty(void** state);
void test_string_assign_substring__successfully_src_non_empty_begin_non_empty(void** state);
void test_string_assign_substring__successfully_src_non_empty_begin_length(void** state);
void test_string_assign_substring__successfully_src_non_empty_begin_npos(void** state);
void test_string_assign_substring__successfully_src_non_empty_middle_empty(void** state);
void test_string_assign_substring__successfully_src_non_empty_middle_non_empty(void** state);
void test_string_assign_substring__successfully_src_non_empty_middle_length(void** state);
void test_string_assign_substring__successfully_src_non_empty_middle_npos(void** state);
void test_string_assign_substring__successfully_src_non_empty_end(void** state);
void test_string_assign_substring__successfully_src_non_empty_npos(void** state);
/*
 * test string_assign_range
 */
UT_CASE_DECLARATION(string_assign_range)
void test_string_assign_range__null_dest(void** state);
void test_string_assign_range__non_inited_dest(void** state);
void test_string_assign_range__invalid_begin_iterator(void** state);
void test_string_assign_range__invalid_end_iterator(void** state);
void test_string_assign_range__invalid_range(void** state);
void test_string_assign_range__successfully_empty_range(void** state);
void test_string_assign_range__successfully(void** state);
/*
 * test string_assign_cstr
 */
UT_CASE_DECLARATION(string_assign_cstr)
void test_string_assign_cstr__null_container(void** state);
void test_string_assign_cstr__non_inited(void** state);
void test_string_assign_cstr__null_valuestring(void** state);
void test_string_assign_cstr__empty(void** state);
void test_string_assign_cstr__non_empty(void** state);
/*
 * test string_assign_subcstr
 */
UT_CASE_DECLARATION(string_assign_subcstr)
void test_string_assign_subcstr__null_container(void** state);
void test_string_assign_subcstr__non_created_container(void** state);
void test_string_assign_subcstr__null_valuestring(void** state);
void test_string_assign_subcstr__empty(void** state);
void test_string_assign_subcstr__non_empty(void** state);
void test_string_assign_subcstr__total(void** state);
/*
 * test string_assign_char
 */
UT_CASE_DECLARATION(string_assign_char)
void test_string_assign_char__null_container(void** state);
void test_string_assign_char__non_inited_container(void** state);
void test_string_assign_char__empty_container_assign_empty(void** state);
void test_string_assign_char__empty_container_assign_non_empty(void** state);
void test_string_assign_char__non_empty_container_assign_empty(void** state);
void test_string_assign_char__non_empty_container_assign_less(void** state);
void test_string_assign_char__non_empty_container_assign_equal(void** state);
void test_string_assign_char__non_empty_container_assign_greater(void** state);
/*
 * test string_append
 */
UT_CASE_DECLARATION(string_append)
void test_string_append__null_dest(void** state);
void test_string_append__null_src(void** state);
void test_string_append__non_inited_dest(void** state);
void test_string_append__non_inited_src(void** state);
void test_string_append__same_container(void** state);
void test_string_append__0_assign_0(void** state);
void test_string_append__0_assign_10(void** state);
void test_string_append__10_assign_0(void** state);
void test_string_append__1000_assign_1810(void** state);
/*
 * test string_append_substring
 */
UT_CASE_DECLARATION(string_append_substring)
void test_string_append_substring__null_dest(void** state);
void test_string_append_substring__null_src(void** state);
void test_string_append_substring__non_inited_dest(void** state);
void test_string_append_substring__non_inited_src(void** state);
void test_string_append_substring__successfully_src_non_empty_begin_empty(void** state);
void test_string_append_substring__successfully_src_non_empty_begin_non_empty(void** state);
void test_string_append_substring__successfully_src_non_empty_begin_length(void** state);
void test_string_append_substring__successfully_src_non_empty_begin_npos(void** state);
void test_string_append_substring__successfully_src_non_empty_middle_empty(void** state);
void test_string_append_substring__successfully_src_non_empty_middle_non_empty(void** state);
void test_string_append_substring__successfully_src_non_empty_middle_length(void** state);
void test_string_append_substring__successfully_src_non_empty_middle_npos(void** state);
void test_string_append_substring__successfully_src_non_empty_end(void** state);
void test_string_append_substring__successfully_src_non_empty_npos(void** state);
/*
 * test string_append_range
 */
UT_CASE_DECLARATION(string_append_range)
void test_string_append_range__null_dest(void** state);
void test_string_append_range__non_inited_dest(void** state);
void test_string_append_range__invalid_begin_iterator(void** state);
void test_string_append_range__invalid_end_iterator(void** state);
void test_string_append_range__invalid_range(void** state);
void test_string_append_range__successfully_empty_range(void** state);
void test_string_append_range__successfully(void** state);
void test_string_append_range__same_container(void** state);
/*
 * test string_append_cstr
 */
UT_CASE_DECLARATION(string_append_cstr)
void test_string_append_cstr__null_container(void** state);
void test_string_append_cstr__non_inited(void** state);
void test_string_append_cstr__null_valuestring(void** state);
void test_string_append_cstr__empty(void** state);
void test_string_append_cstr__non_empty(void** state);
/*
 * test string_append_subcstr
 */
UT_CASE_DECLARATION(string_append_subcstr)
void test_string_append_subcstr__null_container(void** state);
void test_string_append_subcstr__non_created_container(void** state);
void test_string_append_subcstr__null_valuestring(void** state);
void test_string_append_subcstr__empty(void** state);
void test_string_append_subcstr__non_empty(void** state);
void test_string_append_subcstr__total(void** state);
/*
 * test string_append_char
 */
UT_CASE_DECLARATION(string_append_char)
void test_string_append_char__null_container(void** state);
void test_string_append_char__non_inited_container(void** state);
void test_string_append_char__empty_append_empty(void** state);
void test_string_append_char__empty_append_non_empty(void** state);
void test_string_append_char__non_empty_append_empty(void** state);
void test_string_append_char__non_empty_append_non_empty(void** state);
/*
 * test string_insert
 */
UT_CASE_DECLARATION(string_insert)
void test_string_insert__null_string_container(void** state);
void test_string_insert__non_inited(void** state);
void test_string_insert__invalid_position(void** state);
void test_string_insert__empty(void** state);
void test_string_insert__begin(void** state);
void test_string_insert__middle(void** state);
void test_string_insert__end(void** state);
/*
 * test string_insert_n
 */
UT_CASE_DECLARATION(string_insert_n)
void test_string_insert_n__null_string_container(void** state);
void test_string_insert_n__non_inited(void** state);
void test_string_insert_n__invalid_position(void** state);
void test_string_insert_n__empty_insert_0(void** state);
void test_string_insert_n__empty_insert_10(void** state);
void test_string_insert_n__empty_insert_1000(void** state);
void test_string_insert_n__begin_insert_0(void** state);
void test_string_insert_n__begin_insert_10(void** state);
void test_string_insert_n__begin_insert_1000(void** state);
void test_string_insert_n__middle_insert_0(void** state);
void test_string_insert_n__middle_insert_10(void** state);
void test_string_insert_n__middle_insert_1000(void** state);
void test_string_insert_n__end_insert_0(void** state);
void test_string_insert_n__end_insert_10(void** state);
void test_string_insert_n__end_insert_1000(void** state);
/*
 * test string_insert_string
 */
UT_CASE_DECLARATION(string_insert_string)
void test_string_insert_string__null_dest(void** state);
void test_string_insert_string__null_insert(void** state);
void test_string_insert_string__non_inited_dest(void** state);
void test_string_insert_string__non_inited_insert(void** state);
void test_string_insert_string__same_container(void** state);
void test_string_insert_string__invalid_pos(void** state);
void test_string_insert_string__char_middle_insert_empty(void** state);
void test_string_insert_string__char_begin_insert_non_empty(void** state);
/*
 * test string_insert_substring
 */
UT_CASE_DECLARATION(string_insert_substring)
void test_string_insert_substring__null_dest(void** state);
void test_string_insert_substring__null_insert(void** state);
void test_string_insert_substring__non_inited_dest(void** state);
void test_string_insert_substring__non_inited_insert(void** state);
void test_string_insert_substring__same_container(void** state);
void test_string_insert_substring__invalid_pos(void** state);
void test_string_insert_substring__invalid_startpos(void** state);
void test_string_insert_substring__char_middle_insert_empty(void** state);
void test_string_insert_substring__char_begin_insert_non_empty(void** state);
/*
 * test string_insert_cstr
 */
UT_CASE_DECLARATION(string_insert_cstr)
void test_string_insert_cstr__null_container(void** state);
void test_string_insert_cstr__non_inited(void** state);
void test_string_insert_cstr__null_valuestring(void** state);
void test_string_insert_cstr__invalid_pos(void** state);
void test_string_insert_cstr__char_empty(void** state);
void test_string_insert_cstr__char_non_empty(void** state);
/*
 * test string_insert_subcstr
 */
UT_CASE_DECLARATION(string_insert_subcstr)
void test_string_insert_subcstr__null_container(void** state);
void test_string_insert_subcstr__non_created_container(void** state);
void test_string_insert_subcstr__null_valuestring(void** state);
void test_string_insert_subcstr__invalid_pos(void** state);
void test_string_insert_subcstr__char_empty(void** state);
void test_string_insert_subcstr__char_non_empty(void** state);
void test_string_insert_subcstr__char_total(void** state);
/*
 * test string_insert_range
 */
UT_CASE_DECLARATION(string_insert_range)
void test_string_insert_range__null_string(void** state);
void test_string_insert_range__non_inited_string(void** state);
void test_string_insert_range__invalid_pos(void** state);
void test_string_insert_range__invalid_begin(void** state);
void test_string_insert_range__invalid_end(void** state);
void test_string_insert_range__invalid_range(void** state);
void test_string_insert_range__range_belong_to_dest(void** state);
void test_string_insert_range__empty_insert_empty(void** state);
void test_string_insert_range__empty_insert_non_empty(void** state);
void test_string_insert_range__non_empty_insert_begin_empty(void** state);
void test_string_insert_range__non_empty_insert_middle_empty(void** state);
void test_string_insert_range__non_empty_insert_end_empty(void** state);
void test_string_insert_range__non_empty_insert_begin_non_empty(void** state);
void test_string_insert_range__non_empty_insert_middle_non_empty(void** state);
void test_string_insert_range__non_empty_insert_end_non_empty(void** state);
/*
 * test string_insert_char
 */
UT_CASE_DECLARATION(string_insert_char)
void test_string_insert_char__null_string_container(void** state);
void test_string_insert_char__non_inited(void** state);
void test_string_insert_char__invalid_position(void** state);
void test_string_insert_char__empty_insert_0(void** state);
void test_string_insert_char__empty_insert_10(void** state);
void test_string_insert_char__empty_insert_1000(void** state);
void test_string_insert_char__begin_insert_0(void** state);
void test_string_insert_char__begin_insert_10(void** state);
void test_string_insert_char__begin_insert_1000(void** state);
void test_string_insert_char__middle_insert_0(void** state);
void test_string_insert_char__middle_insert_10(void** state);
void test_string_insert_char__middle_insert_1000(void** state);
void test_string_insert_char__end_insert_0(void** state);
void test_string_insert_char__end_insert_10(void** state);
void test_string_insert_char__end_insert_1000(void** state);
/*
 * test string_push_back
 */
UT_CASE_DECLARATION(string_push_back)
void test_string_push_back__null_container(void** state);
void test_string_push_back__non_inited_container(void** state);
void test_string_push_back__empty(void** state);
void test_string_push_back__non_empty(void** state);
/*
 * test string_resize_char
 */
UT_CASE_DECLARATION(string_resize_char)
void test_string_resize_char__null_string_container(void** state);
void test_string_resize_char__non_inited(void** state);
void test_string_resize_char__successfully_0_resize_0(void** state);
void test_string_resize_char__successfully_0_resize_10(void** state);
void test_string_resize_char__successfully_10_resize_0(void** state);
void test_string_resize_char__successfully_10_resize_10(void** state);
void test_string_resize_char__successfully_10_resize_1000(void** state);
void test_string_resize_char__successfully_1000_resize_10(void** state);
/*
 * test string_resize
 */
UT_CASE_DECLARATION(string_resize)
void test_string_resize__null_string_container(void** state);
void test_string_resize__non_inited(void** state);
void test_string_resize__successfully_0_resize_0(void** state);
void test_string_resize__successfully_0_resize_10(void** state);
void test_string_resize__successfully_10_resize_0(void** state);
void test_string_resize__successfully_10_resize_10(void** state);
void test_string_resize__successfully_10_resize_1000(void** state);
void test_string_resize__successfully_1000_resize_10(void** state);
/*
 * test string_erase
 */
UT_CASE_DECLARATION(string_erase)
void test_string_erase__null_string(void** state);
void test_string_erase__non_inited_string(void** state);
void test_string_erase__invalid_pos(void** state);
void test_string_erase__empty(void** state);
void test_string_erase__begin(void** state);
void test_string_erase__middle(void** state);
void test_string_erase__last(void** state);
/*
 * test string_erase_range
 */
UT_CASE_DECLARATION(string_erase_range)
void test_string_erase_range__null_string(void** state);
void test_string_erase_range__non_inited_string(void** state);
void test_string_erase_range__invalid_begin(void** state);
void test_string_erase_range__invalid_end(void** state);
void test_string_erase_range__invalid_range(void** state);
void test_string_erase_range__empty(void** state);
void test_string_erase_range__begin(void** state);
void test_string_erase_range__middle(void** state);
void test_string_erase_range__end(void** state);
void test_string_erase_range__all(void** state);
void test_string_erase_range__erase_empty(void** state);
/*
 * test string_erase_substring
 */
UT_CASE_DECLARATION(string_erase_substring)
void test_string_erase_substring__null_string(void** state);
void test_string_erase_substring__non_inited_string(void** state);
void test_string_erase_substring__invalid_pos(void** state);
void test_string_erase_substring__begin(void** state);
void test_string_erase_substring__middle(void** state);
void test_string_erase_substring__end(void** state);
void test_string_erase_substring__all(void** state);
void test_string_erase_substring__erase_empty(void** state);
/*
 * test string_replace
 */
UT_CASE_DECLARATION(string_replace)
void test_string_replace__null_dest(void** state);
void test_string_replace__null_replace(void** state);
void test_string_replace__non_inited_dest(void** state);
void test_string_replace__non_inited_replace(void** state);
void test_string_replace__same_container(void** state);
void test_string_replace__invalid_pos(void** state);
void test_string_replace__begin_empty_replace_empty(void** state);
void test_string_replace__begin_empty_replace_non_empty(void** state);
void test_string_replace__begin_non_empty_replace_empty(void** state);
void test_string_replace__begin_non_empty_replace_non_empty(void** state);
void test_string_replace__middle_empty_replace_empty(void** state);
void test_string_replace__middle_empty_replace_non_empty(void** state);
void test_string_replace__middle_non_empty_replace_empty(void** state);
void test_string_replace__middle_non_empty_replace_non_empty(void** state);
void test_string_replace__end_non_empty_replace_empty(void** state);
void test_string_replace__end_non_empty_replace_non_empty(void** state);
void test_string_replace__all_replace_empty(void** state);
void test_string_replace__all_replace_non_empty(void** state);
/*
 * test string_replace_substring
 */
UT_CASE_DECLARATION(string_replace_substring)
void test_string_replace_substring__null_dest(void** state);
void test_string_replace_substring__null_replace(void** state);
void test_string_replace_substring__non_inited_dest(void** state);
void test_string_replace_substring__non_inited_replace(void** state);
void test_string_replace_substring__same_container(void** state);
void test_string_replace_substring__invalid_pos(void** state);
void test_string_replace_substring__invalid_position(void** state);
void test_string_replace_substring__begin_empty_replace_empty(void** state);
void test_string_replace_substring__begin_empty_replace_non_empty(void** state);
void test_string_replace_substring__begin_non_empty_replace_empty(void** state);
void test_string_replace_substring__begin_non_empty_replace_non_empty(void** state);
void test_string_replace_substring__middle_empty_replace_empty(void** state);
void test_string_replace_substring__middle_empty_replace_non_empty(void** state);
void test_string_replace_substring__middle_non_empty_replace_empty(void** state);
void test_string_replace_substring__middle_non_empty_replace_non_empty(void** state);
void test_string_replace_substring__end_non_empty_replace_empty(void** state);
void test_string_replace_substring__end_non_empty_replace_non_empty(void** state);
void test_string_replace_substring__all_replace_empty(void** state);
void test_string_replace_substring__all_replace_non_empty(void** state);
/*
 * test string_replace_cstr
 */
UT_CASE_DECLARATION(string_replace_cstr)
void test_string_replace_cstr__null_dest(void** state);
void test_string_replace_cstr__null_replace(void** state);
void test_string_replace_cstr__non_inited_dest(void** state);
void test_string_replace_cstr__invalid_pos(void** state);
void test_string_replace_cstr__begin_empty_replace_empty(void** state);
void test_string_replace_cstr__begin_empty_replace_non_empty(void** state);
void test_string_replace_cstr__begin_non_empty_replace_empty(void** state);
void test_string_replace_cstr__begin_non_empty_replace_non_empty(void** state);
void test_string_replace_cstr__middle_empty_replace_empty(void** state);
void test_string_replace_cstr__middle_empty_replace_non_empty(void** state);
void test_string_replace_cstr__middle_non_empty_replace_empty(void** state);
void test_string_replace_cstr__middle_non_empty_replace_non_empty(void** state);
void test_string_replace_cstr__end_non_empty_replace_empty(void** state);
void test_string_replace_cstr__end_non_empty_replace_non_empty(void** state);
void test_string_replace_cstr__all_replace_empty(void** state);
void test_string_replace_cstr__all_replace_non_empty(void** state);
/*
 * test string_replace_subcstr
 */
UT_CASE_DECLARATION(string_replace_subcstr)
void test_string_replace_subcstr__null_dest(void** state);
void test_string_replace_subcstr__null_replace(void** state);
void test_string_replace_subcstr__non_inited_dest(void** state);
void test_string_replace_subcstr__invalid_pos(void** state);
void test_string_replace_subcstr__begin_empty_replace_empty(void** state);
void test_string_replace_subcstr__begin_empty_replace_non_empty(void** state);
void test_string_replace_subcstr__begin_non_empty_replace_empty(void** state);
void test_string_replace_subcstr__begin_non_empty_replace_non_empty(void** state);
void test_string_replace_subcstr__middle_empty_replace_empty(void** state);
void test_string_replace_subcstr__middle_empty_replace_non_empty(void** state);
void test_string_replace_subcstr__middle_non_empty_replace_empty(void** state);
void test_string_replace_subcstr__middle_non_empty_replace_non_empty(void** state);
void test_string_replace_subcstr__end_non_empty_replace_empty(void** state);
void test_string_replace_subcstr__end_non_empty_replace_non_empty(void** state);
void test_string_replace_subcstr__all_replace_empty(void** state);
void test_string_replace_subcstr__all_replace_non_empty(void** state);
/*
 * test string_replace_char
 */
UT_CASE_DECLARATION(string_replace_char)
void test_string_replace_char__null_container(void** state);
void test_string_replace_char__non_inited_container(void** state);
void test_string_replace_char__empty_replace_empty(void** state);
void test_string_replace_char__empty_replace_non_empty(void** state);
void test_string_replace_char__begin_replace_empty(void** state);
void test_string_replace_char__begin_replace_less(void** state);
void test_string_replace_char__begin_replace_equal(void** state);
void test_string_replace_char__begin_replace_greater(void** state);
void test_string_replace_char__middle_replace_empty(void** state);
void test_string_replace_char__middle_replace_less(void** state);
void test_string_replace_char__middle_replace_equal(void** state);
void test_string_replace_char__middle_replace_greater(void** state);
void test_string_replace_char__end_replace_empty(void** state);
void test_string_replace_char__end_replace_less(void** state);
void test_string_replace_char__end_replace_equal(void** state);
void test_string_replace_char__end_replace_greater(void** state);
void test_string_replace_char__replace_all(void** state);
/*
 * test string_range_replace
 */
UT_CASE_DECLARATION(string_range_replace)
void test_string_range_replace__null_dest(void** state);
void test_string_range_replace__null_replace(void** state);
void test_string_range_replace__non_inited_dest(void** state);
void test_string_range_replace__non_inited_replace(void** state);
void test_string_range_replace__same_container(void** state);
void test_string_range_replace__invalid_range(void** state);
void test_string_range_replace__begin_empty_replace_empty(void** state);
void test_string_range_replace__begin_empty_replace_non_empty(void** state);
void test_string_range_replace__begin_non_empty_replace_empty(void** state);
void test_string_range_replace__begin_non_empty_replace_non_empty(void** state);
void test_string_range_replace__middle_empty_replace_empty(void** state);
void test_string_range_replace__middle_empty_replace_non_empty(void** state);
void test_string_range_replace__middle_non_empty_replace_empty(void** state);
void test_string_range_replace__middle_non_empty_replace_non_empty(void** state);
void test_string_range_replace__end_non_empty_replace_empty(void** state);
void test_string_range_replace__end_non_empty_replace_non_empty(void** state);
void test_string_range_replace__all_replace_empty(void** state);
void test_string_range_replace__all_replace_non_empty(void** state);
/*
 * test string_range_replace_substring
 */
UT_CASE_DECLARATION(string_range_replace_substring)
void test_string_range_replace_substring__null_dest(void** state);
void test_string_range_replace_substring__null_replace(void** state);
void test_string_range_replace_substring__non_inited_dest(void** state);
void test_string_range_replace_substring__non_inited_replace(void** state);
void test_string_range_replace_substring__same_container(void** state);
void test_string_range_replace_substring__invalid_range(void** state);
void test_string_range_replace_substring__invalid_position(void** state);
void test_string_range_replace_substring__begin_empty_replace_empty(void** state);
void test_string_range_replace_substring__begin_empty_replace_non_empty(void** state);
void test_string_range_replace_substring__begin_non_empty_replace_empty(void** state);
void test_string_range_replace_substring__begin_non_empty_replace_non_empty(void** state);
void test_string_range_replace_substring__middle_empty_replace_empty(void** state);
void test_string_range_replace_substring__middle_empty_replace_non_empty(void** state);
void test_string_range_replace_substring__middle_non_empty_replace_empty(void** state);
void test_string_range_replace_substring__middle_non_empty_replace_non_empty(void** state);
void test_string_range_replace_substring__end_non_empty_replace_empty(void** state);
void test_string_range_replace_substring__end_non_empty_replace_non_empty(void** state);
void test_string_range_replace_substring__all_replace_empty(void** state);
void test_string_range_replace_substring__all_replace_non_empty(void** state);
/*
 * test string_range_replace_cstr
 */
UT_CASE_DECLARATION(string_range_replace_cstr)
void test_string_range_replace_cstr__null_dest(void** state);
void test_string_range_replace_cstr__null_replace(void** state);
void test_string_range_replace_cstr__non_inited_dest(void** state);
void test_string_range_replace_cstr__invalid_range(void** state);
void test_string_range_replace_cstr__begin_empty_replace_empty(void** state);
void test_string_range_replace_cstr__begin_empty_replace_non_empty(void** state);
void test_string_range_replace_cstr__begin_non_empty_replace_empty(void** state);
void test_string_range_replace_cstr__begin_non_empty_replace_non_empty(void** state);
void test_string_range_replace_cstr__middle_empty_replace_empty(void** state);
void test_string_range_replace_cstr__middle_empty_replace_non_empty(void** state);
void test_string_range_replace_cstr__middle_non_empty_replace_empty(void** state);
void test_string_range_replace_cstr__middle_non_empty_replace_non_empty(void** state);
void test_string_range_replace_cstr__end_non_empty_replace_empty(void** state);
void test_string_range_replace_cstr__end_non_empty_replace_non_empty(void** state);
void test_string_range_replace_cstr__all_replace_empty(void** state);
void test_string_range_replace_cstr__all_replace_non_empty(void** state);
/*
 * test string_range_replace_subcstr
 */
UT_CASE_DECLARATION(string_range_replace_subcstr)
void test_string_range_replace_subcstr__null_dest(void** state);
void test_string_range_replace_subcstr__null_replace(void** state);
void test_string_range_replace_subcstr__non_inited_dest(void** state);
void test_string_range_replace_subcstr__invalid_range(void** state);
void test_string_range_replace_subcstr__begin_empty_replace_empty(void** state);
void test_string_range_replace_subcstr__begin_empty_replace_non_empty(void** state);
void test_string_range_replace_subcstr__begin_non_empty_replace_empty(void** state);
void test_string_range_replace_subcstr__begin_non_empty_replace_non_empty(void** state);
void test_string_range_replace_subcstr__middle_empty_replace_empty(void** state);
void test_string_range_replace_subcstr__middle_empty_replace_non_empty(void** state);
void test_string_range_replace_subcstr__middle_non_empty_replace_empty(void** state);
void test_string_range_replace_subcstr__middle_non_empty_replace_non_empty(void** state);
void test_string_range_replace_subcstr__end_non_empty_replace_empty(void** state);
void test_string_range_replace_subcstr__end_non_empty_replace_non_empty(void** state);
void test_string_range_replace_subcstr__all_replace_empty(void** state);
void test_string_range_replace_subcstr__all_replace_non_empty(void** state);
/*
 * test string_range_replace_char
 */
UT_CASE_DECLARATION(string_range_replace_char)
void test_string_range_replace_char__null_container(void** state);
void test_string_range_replace_char__non_inited_container(void** state);
void test_string_range_replace_char__invalid_range(void** state);
void test_string_range_replace_char__empty_replace_empty(void** state);
void test_string_range_replace_char__empty_replace_non_empty(void** state);
void test_string_range_replace_char__begin_replace_empty(void** state);
void test_string_range_replace_char__begin_replace_less(void** state);
void test_string_range_replace_char__begin_replace_equal(void** state);
void test_string_range_replace_char__begin_replace_greater(void** state);
void test_string_range_replace_char__middle_replace_empty(void** state);
void test_string_range_replace_char__middle_replace_less(void** state);
void test_string_range_replace_char__middle_replace_equal(void** state);
void test_string_range_replace_char__middle_replace_greater(void** state);
void test_string_range_replace_char__end_replace_empty(void** state);
void test_string_range_replace_char__end_replace_less(void** state);
void test_string_range_replace_char__end_replace_equal(void** state);
void test_string_range_replace_char__end_replace_greater(void** state);
void test_string_range_replace_char__replace_all(void** state);
/*
 * test string_replace_range
 */
UT_CASE_DECLARATION(string_replace_range)
void test_string_replace_range__null_dest(void** state);
void test_string_replace_range__non_inited_dest(void** state);
void test_string_replace_range__same_container(void** state);
void test_string_replace_range__invalid_range(void** state);
void test_string_replace_range__invalid_replace_range(void** state);
void test_string_replace_range__begin_empty_replace_empty(void** state);
void test_string_replace_range__begin_empty_replace_non_empty(void** state);
void test_string_replace_range__begin_non_empty_replace_empty(void** state);
void test_string_replace_range__begin_non_empty_replace_non_empty(void** state);
void test_string_replace_range__middle_empty_replace_empty(void** state);
void test_string_replace_range__middle_empty_replace_non_empty(void** state);
void test_string_replace_range__middle_non_empty_replace_empty(void** state);
void test_string_replace_range__middle_non_empty_replace_non_empty(void** state);
void test_string_replace_range__end_non_empty_replace_empty(void** state);
void test_string_replace_range__end_non_empty_replace_non_empty(void** state);
void test_string_replace_range__all_replace_empty(void** state);
void test_string_replace_range__all_replace_non_empty(void** state);
/*
 * test string_output
 */
UT_CASE_DECLARATION(string_output)
void test_string_output__null_string(void** state);
void test_string_output__null_stream(void** state);
void test_string_output__non_inited_string(void** state);
void test_string_output__output_empty(void** state);
void test_string_output__output_non_empty(void** state);
/*
 * test string_input
 */
UT_CASE_DECLARATION(string_input)
void test_string_input__null_string(void** state);
void test_string_input__null_stream(void** state);
void test_string_input__non_inited_string(void** state);
void test_string_input__input_empty(void** state);
void test_string_input__input_non_empty(void** state);
/*
 * test string_getline
 */
UT_CASE_DECLARATION(string_getline)
void test_string_getline__null_string(void** state);
void test_string_getline__null_stream(void** state);
void test_string_getline__non_inited_string(void** state);
void test_string_getline__getline_empty(void** state);
void test_string_getline__getline_non_empty(void** state);
/*
 * test string_getline_delimiter
 */
UT_CASE_DECLARATION(string_getline_delimiter)
void test_string_getline_delimiter__null_string(void** state);
void test_string_getline_delimiter__null_stream(void** state);
void test_string_getline_delimiter__non_inited_string(void** state);
void test_string_getline_delimiter__getline_delimiter_empty(void** state);
void test_string_getline_delimiter__getline_delimiter_non_empty(void** state);

#define UT_CSTL_STRING_CASE\
    UT_SUIT_BEGIN(cstl_string, test_create_string__successfully),\
    UT_CASE_BEGIN(string_init, test_string_init__null_string_container),\
    UT_CASE(test_string_init__non_created),\
    UT_CASE(test_string_init__successfully),\
    UT_CASE_BEGIN(string_size, test_string_size__null_string_container),\
    UT_CASE(test_string_size__non_inited),\
    UT_CASE(test_string_size__successfully_empty),\
    UT_CASE(test_string_size__successfully_non_empty),\
    UT_CASE_BEGIN(string_init_cstr, test_string_init_cstr__null),\
    UT_CASE(test_string_init_cstr__non_created),\
    UT_CASE(test_string_init_cstr__null_cstr),\
    UT_CASE(test_string_init_cstr__empty),\
    UT_CASE(test_string_init_cstr__non_empty),\
    UT_CASE(test_string_init_cstr__truncate_empty),\
    UT_CASE(test_string_init_cstr__truncate_non_empty),\
    UT_CASE_BEGIN(string_c_str, test_string_c_str__null_container),\
    UT_CASE(test_string_c_str__non_inited_container),\
    UT_CASE(test_string_c_str__empty),\
    UT_CASE(test_string_c_str__non_empty),\
    UT_CASE_BEGIN(string_init, test_string_init_char__null),\
    UT_CASE(test_string_init_char__non_created),\
    UT_CASE(test_string_init_char__empty),\
    UT_CASE(test_string_init_char__non_empty),\
    UT_CASE_BEGIN(string_init_subcstr, test_string_init_subcstr__null_container),\
    UT_CASE(test_string_init_subcstr__non_created_container),\
    UT_CASE(test_string_init_subcstr__null_cstr),\
    UT_CASE(test_string_init_subcstr__cstr_empty),\
    UT_CASE(test_string_init_subcstr__length_empty),\
    UT_CASE(test_string_init_subcstr__non_empty),\
    UT_CASE(test_string_init_subcstr__all),\
    UT_CASE(test_string_init_subcstr__truncate_empty),\
    UT_CASE(test_string_init_subcstr__truncate_non_empty),\
    UT_CASE_BEGIN(string_init_copy, test_string_init_copy__null_dest),\
    UT_CASE(test_string_init_copy__null_src),\
    UT_CASE(test_string_init_copy__non_create_dest),\
    UT_CASE(test_string_init_copy__non_inited_src),\
    UT_CASE(test_string_init_copy__empty),\
    UT_CASE(test_string_init_copy__non_empty),\
    UT_CASE_BEGIN(string_init_copy_substring, test_string_init_copy_substring__null_dest),\
    UT_CASE(test_string_init_copy_substring__null_src),\
    UT_CASE(test_string_init_copy_substring__non_create_dest),\
    UT_CASE(test_string_init_copy_substring__non_inited_src),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_non_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_length),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_npos),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_non_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_length),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_npos),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_end),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_npos),\
    UT_CASE_BEGIN(string_length, test_string_length__null_string_container),\
    UT_CASE(test_string_length__non_inited),\
    UT_CASE(test_string_length__successfully_empty),\
    UT_CASE(test_string_length__successfully_non_empty),\
    UT_CASE_BEGIN(string_init_copy_range, test_string_init_copy_range__null_dest),\
    UT_CASE(test_string_init_copy_range__invalid_begin_iterator),\
    UT_CASE(test_string_init_copy_range__invalid_end_iterator),\
    UT_CASE(test_string_init_copy_range__invalid_range),\
    UT_CASE(test_string_init_copy_range__empty_range),\
    UT_CASE(test_string_init_copy_range__not_empty_range),\
    UT_CASE_BEGIN(string_begin, test_string_begin__null_string_container),\
    UT_CASE(test_string_begin__non_inited_string_container),\
    UT_CASE(test_string_begin__empty),\
    UT_CASE(test_string_begin__non_empty),\
    UT_CASE_BEGIN(string_end, test_string_end__null_string_container),\
    UT_CASE(test_string_end__non_inited_string_container),\
    UT_CASE(test_string_end__empty),\
    UT_CASE(test_string_end__non_empty),\
    UT_CASE_BEGIN(string_destroy, test_string_destroy__null_string_container),\
    UT_CASE(test_string_destroy__non_created),\
    UT_CASE(test_string_destroy__created_non_inited),\
    UT_CASE(test_string_destroy__inited_empty),\
    UT_CASE(test_string_destroy__inited_non_empty),\
    UT_CASE_BEGIN(string_data, test_string_data__null_container),\
    UT_CASE(test_string_data__non_inited_container),\
    UT_CASE(test_string_data__empty),\
    UT_CASE(test_string_data__non_empty),\
    UT_CASE_BEGIN(string_copy, test_string_copy__null_container),\
    UT_CASE(test_string_copy__non_inited_container),\
    UT_CASE(test_string_copy__null_buffer),\
    UT_CASE(test_string_copy__invalid_position),\
    UT_CASE(test_string_copy__begin_empty),\
    UT_CASE(test_string_copy__begin_non_empty),\
    UT_CASE(test_string_copy__begin_length),\
    UT_CASE(test_string_copy__begin_npos),\
    UT_CASE(test_string_copy__middle_empty),\
    UT_CASE(test_string_copy__middle_non_empty),\
    UT_CASE(test_string_copy__middle_length),\
    UT_CASE(test_string_copy__middle_npos),\
    UT_CASE(test_string_copy__end),\
    UT_CASE(test_string_copy__npos),\
    UT_CASE_BEGIN(string_empty, test_string_empty__null_string_container),\
    UT_CASE(test_string_empty__non_inited),\
    UT_CASE(test_string_empty__successfully_empty),\
    UT_CASE(test_string_empty__successfully_non_empty),\
    UT_CASE_BEGIN(string_empty, test_string_max_size__null_string_container),\
    UT_CASE(test_string_max_size__non_inited),\
    UT_CASE(test_string_max_size__successfully),\
    UT_CASE_BEGIN(string_capacity, test_string_capacity__null_string_container),\
    UT_CASE(test_string_capacity__non_inited),\
    UT_CASE(test_string_capacity__successfully_empty),\
    UT_CASE(test_string_capacity__successfully_little),\
    UT_CASE(test_string_capacity__successfully_huge),\
    UT_CASE_BEGIN(string_push_back, test_string_push_back__null_container),\
    UT_CASE(test_string_push_back__non_inited_container),\
    UT_CASE(test_string_push_back__empty),\
    UT_CASE(test_string_push_back__non_empty),\
    UT_CASE_BEGIN(string_at, test_string_at__null_string_container),\
    UT_CASE(test_string_at__non_inited_string_container),\
    UT_CASE(test_string_at__invalid_subscript_empty),\
    UT_CASE(test_string_at__invalid_subscript_end),\
    UT_CASE(test_string_at__invalid_subscript),\
    UT_CASE(test_string_at__successfully),\
    UT_CASE_BEGIN(string_equal, test_string_equal__null_first),\
    UT_CASE(test_string_equal__null_second),\
    UT_CASE(test_string_equal__non_inited_first),\
    UT_CASE(test_string_equal__non_inited_second),\
    UT_CASE(test_string_equal__same_string),\
    UT_CASE(test_string_equal__size_first_less_than_second),\
    UT_CASE(test_string_equal__size_first_greater_than_second),\
    UT_CASE(test_string_equal__size_equal_0),\
    UT_CASE(test_string_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_string_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_string_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(string_not_equal, test_string_not_equal__null_first),\
    UT_CASE(test_string_not_equal__null_second),\
    UT_CASE(test_string_not_equal__non_inited_first),\
    UT_CASE(test_string_not_equal__non_inited_second),\
    UT_CASE(test_string_not_equal__same_string),\
    UT_CASE(test_string_not_equal__size_first_less_than_second),\
    UT_CASE(test_string_not_equal__size_first_greater_than_second),\
    UT_CASE(test_string_not_equal__size_equal_0),\
    UT_CASE(test_string_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_string_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_string_not_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(string_less, test_string_less__null_first),\
    UT_CASE(test_string_less__null_second),\
    UT_CASE(test_string_less__non_inited_first),\
    UT_CASE(test_string_less__non_inited_second),\
    UT_CASE(test_string_less__same_string),\
    UT_CASE(test_string_less__size_first_less_than_second),\
    UT_CASE(test_string_less__size_first_greater_than_second),\
    UT_CASE(test_string_less__size_equal_0),\
    UT_CASE(test_string_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_string_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_string_less__size_equal_elem_equal),\
    UT_CASE_BEGIN(string_less_equal, test_string_less_equal__null_first),\
    UT_CASE(test_string_less_equal__null_second),\
    UT_CASE(test_string_less_equal__non_inited_first),\
    UT_CASE(test_string_less_equal__non_inited_second),\
    UT_CASE(test_string_less_equal__same_string),\
    UT_CASE(test_string_less_equal__size_first_less_than_second),\
    UT_CASE(test_string_less_equal__size_first_greater_than_second),\
    UT_CASE(test_string_less_equal__size_equal_0),\
    UT_CASE(test_string_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_string_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_string_less_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(string_greater, test_string_greater__null_first),\
    UT_CASE(test_string_greater__null_second),\
    UT_CASE(test_string_greater__non_inited_first),\
    UT_CASE(test_string_greater__non_inited_second),\
    UT_CASE(test_string_greater__same_string),\
    UT_CASE(test_string_greater__size_first_less_than_second),\
    UT_CASE(test_string_greater__size_first_greater_than_second),\
    UT_CASE(test_string_greater__size_equal_0),\
    UT_CASE(test_string_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_string_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_string_greater__size_equal_elem_equal),\
    UT_CASE_BEGIN(string_greater_equal, test_string_greater_equal__null_first),\
    UT_CASE(test_string_greater_equal__null_second),\
    UT_CASE(test_string_greater_equal__non_inited_first),\
    UT_CASE(test_string_greater_equal__non_inited_second),\
    UT_CASE(test_string_greater_equal__same_string),\
    UT_CASE(test_string_greater_equal__size_first_less_than_second),\
    UT_CASE(test_string_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_string_greater_equal__size_equal_0),\
    UT_CASE(test_string_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_string_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_string_greater_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(string_equal_cstr, test_string_equal_cstr__null_string),\
    UT_CASE(test_string_equal_cstr__null_value_string),\
    UT_CASE(test_string_equal_cstr__non_inited_string),\
    UT_CASE(test_string_equal_cstr__char_empty),\
    UT_CASE(test_string_equal_cstr__char_less),\
    UT_CASE(test_string_equal_cstr__char_equal),\
    UT_CASE(test_string_equal_cstr__char_greater),\
    UT_CASE(test_string_equal_cstr__char_size_equal_less),\
    UT_CASE(test_string_equal_cstr__char_size_equal_greater),\
    UT_CASE_BEGIN(string_not_equal_cstr, test_string_not_equal_cstr__null_string),\
    UT_CASE(test_string_not_equal_cstr__null_value_string),\
    UT_CASE(test_string_not_equal_cstr__non_inited_string),\
    UT_CASE(test_string_not_equal_cstr__char_empty),\
    UT_CASE(test_string_not_equal_cstr__char_less),\
    UT_CASE(test_string_not_equal_cstr__char_equal),\
    UT_CASE(test_string_not_equal_cstr__char_greater),\
    UT_CASE(test_string_not_equal_cstr__char_size_equal_less),\
    UT_CASE(test_string_not_equal_cstr__char_size_equal_greater),\
    UT_CASE_BEGIN(string_less_cstr, test_string_less_cstr__null_string),\
    UT_CASE(test_string_less_cstr__null_value_string),\
    UT_CASE(test_string_less_cstr__non_inited_string),\
    UT_CASE(test_string_less_cstr__char_empty),\
    UT_CASE(test_string_less_cstr__char_less),\
    UT_CASE(test_string_less_cstr__char_equal),\
    UT_CASE(test_string_less_cstr__char_greater),\
    UT_CASE(test_string_less_cstr__char_size_equal_less),\
    UT_CASE(test_string_less_cstr__char_size_equal_greater),\
    UT_CASE_BEGIN(string_less_equal_cstr, test_string_less_equal_cstr__null_string),\
    UT_CASE(test_string_less_equal_cstr__null_value_string),\
    UT_CASE(test_string_less_equal_cstr__non_inited_string),\
    UT_CASE(test_string_less_equal_cstr__char_empty),\
    UT_CASE(test_string_less_equal_cstr__char_less),\
    UT_CASE(test_string_less_equal_cstr__char_equal),\
    UT_CASE(test_string_less_equal_cstr__char_greater),\
    UT_CASE(test_string_less_equal_cstr__char_size_equal_less),\
    UT_CASE(test_string_less_equal_cstr__char_size_equal_greater),\
    UT_CASE_BEGIN(string_greater_cstr, test_string_greater_cstr__null_string),\
    UT_CASE(test_string_greater_cstr__null_value_string),\
    UT_CASE(test_string_greater_cstr__non_inited_string),\
    UT_CASE(test_string_greater_cstr__char_empty),\
    UT_CASE(test_string_greater_cstr__char_less),\
    UT_CASE(test_string_greater_cstr__char_equal),\
    UT_CASE(test_string_greater_cstr__char_greater),\
    UT_CASE(test_string_greater_cstr__char_size_equal_less),\
    UT_CASE(test_string_greater_cstr__char_size_equal_greater),\
    UT_CASE_BEGIN(string_greater_equal_cstr, test_string_greater_equal_cstr__null_string),\
    UT_CASE(test_string_greater_equal_cstr__null_value_string),\
    UT_CASE(test_string_greater_equal_cstr__non_inited_string),\
    UT_CASE(test_string_greater_equal_cstr__char_empty),\
    UT_CASE(test_string_greater_equal_cstr__char_less),\
    UT_CASE(test_string_greater_equal_cstr__char_equal),\
    UT_CASE(test_string_greater_equal_cstr__char_greater),\
    UT_CASE(test_string_greater_equal_cstr__char_size_equal_less),\
    UT_CASE(test_string_greater_equal_cstr__char_size_equal_greater),\
    UT_CASE_BEGIN(string_compare, test_string_compare__null_first),\
    UT_CASE(test_string_compare__null_second),\
    UT_CASE(test_string_compare__non_inited_first),\
    UT_CASE(test_string_compare__non_inited_second),\
    UT_CASE(test_string_compare__same_string),\
    UT_CASE(test_string_compare__char_size_first_less_than_second),\
    UT_CASE(test_string_compare__char_size_first_greater_than_second),\
    UT_CASE(test_string_compare__char_size_equal_0),\
    UT_CASE(test_string_compare__char_size_equal_elem_first_less_than_second),\
    UT_CASE(test_string_compare__char_size_equal_elem_first_greater_than_second),\
    UT_CASE(test_string_compare__char_size_equal_elem_equal),\
    UT_CASE_BEGIN(string_compare_substring_string, test_string_compare_substring_string__null_first),\
    UT_CASE(test_string_compare_substring_string__null_second),\
    UT_CASE(test_string_compare_substring_string__non_inited_first),\
    UT_CASE(test_string_compare_substring_string__non_inited_second),\
    UT_CASE(test_string_compare_substring_string__invalid_pos),\
    UT_CASE(test_string_compare_substring_string__char_sub_size_less),\
    UT_CASE(test_string_compare_substring_string__char_sub_content_less),\
    UT_CASE(test_string_compare_substring_string__char_sub_equal),\
    UT_CASE(test_string_compare_substring_string__char_sub_size_greater),\
    UT_CASE(test_string_compare_substring_string__char_sub_content_greater),\
    UT_CASE(test_string_compare_substring_string__char_all_size_less),\
    UT_CASE(test_string_compare_substring_string__char_all_content_less),\
    UT_CASE(test_string_compare_substring_string__char_all_equal),\
    UT_CASE(test_string_compare_substring_string__char_all_size_greater),\
    UT_CASE(test_string_compare_substring_string__char_all_content_greater),\
    UT_CASE(test_string_compare_substring_string__char_empty_non_empty),\
    UT_CASE(test_string_compare_substring_string__char_non_empty_empty),\
    UT_CASE(test_string_compare_substring_string__char_empty_empty),\
    UT_CASE_BEGIN(string_compare_substring_substring, test_string_compare_substring_substring__null_first),\
    UT_CASE(test_string_compare_substring_substring__null_second),\
    UT_CASE(test_string_compare_substring_substring__non_inited_first),\
    UT_CASE(test_string_compare_substring_substring__non_inited_second),\
    UT_CASE(test_string_compare_substring_substring__invalid_first_pos),\
    UT_CASE(test_string_compare_substring_substring__invalid_second_pos),\
    UT_CASE(test_string_compare_substring_substring__char_sub_size_less),\
    UT_CASE(test_string_compare_substring_substring__char_sub_content_less),\
    UT_CASE(test_string_compare_substring_substring__char_sub_equal),\
    UT_CASE(test_string_compare_substring_substring__char_sub_size_greater),\
    UT_CASE(test_string_compare_substring_substring__char_sub_content_greater),\
    UT_CASE(test_string_compare_substring_substring__char_all_size_less),\
    UT_CASE(test_string_compare_substring_substring__char_all_content_less),\
    UT_CASE(test_string_compare_substring_substring__char_all_equal),\
    UT_CASE(test_string_compare_substring_substring__char_all_size_greater),\
    UT_CASE(test_string_compare_substring_substring__char_all_content_greater),\
    UT_CASE(test_string_compare_substring_substring__char_empty_non_empty),\
    UT_CASE(test_string_compare_substring_substring__char_non_empty_empty),\
    UT_CASE(test_string_compare_substring_substring__char_empty_empty),\
    UT_CASE_BEGIN(string_compare_cstr, test_string_compare_cstr__null_string),\
    UT_CASE(test_string_compare_cstr__null_value_string),\
    UT_CASE(test_string_compare_cstr__non_inited_string),\
    UT_CASE(test_string_compare_cstr__char_empty),\
    UT_CASE(test_string_compare_cstr__char_less),\
    UT_CASE(test_string_compare_cstr__char_equal),\
    UT_CASE(test_string_compare_cstr__char_greater),\
    UT_CASE(test_string_compare_cstr__char_size_equal_less),\
    UT_CASE(test_string_compare_cstr__char_size_equal_greater),\
    UT_CASE_BEGIN(string_compare_substring_cstr, test_string_compare_substring_cstr__null_string),\
    UT_CASE(test_string_compare_substring_cstr__null_value_string),\
    UT_CASE(test_string_compare_substring_cstr__non_inited_string),\
    UT_CASE(test_string_compare_substring_cstr__invalid_pos),\
    UT_CASE(test_string_compare_substring_cstr__char_empty_empty),\
    UT_CASE(test_string_compare_substring_cstr__char_non_empty_empty),\
    UT_CASE(test_string_compare_substring_cstr__char_empty_non_empty),\
    UT_CASE(test_string_compare_substring_cstr__char_sub_size_less),\
    UT_CASE(test_string_compare_substring_cstr__char_sub_content_less),\
    UT_CASE(test_string_compare_substring_cstr__char_sub_equal),\
    UT_CASE(test_string_compare_substring_cstr__char_sub_size_greater),\
    UT_CASE(test_string_compare_substring_cstr__char_sub_content_greater),\
    UT_CASE(test_string_compare_substring_cstr__char_all_size_less),\
    UT_CASE(test_string_compare_substring_cstr__char_all_content_less),\
    UT_CASE(test_string_compare_substring_cstr__char_all_equal),\
    UT_CASE(test_string_compare_substring_cstr__char_all_size_greater),\
    UT_CASE(test_string_compare_substring_cstr__char_all_content_greater),\
    UT_CASE_BEGIN(string_compare_substring_subcstr, test_string_compare_substring_subcstr__null_string),\
    UT_CASE(test_string_compare_substring_subcstr__null_value_string),\
    UT_CASE(test_string_compare_substring_subcstr__non_inited_string),\
    UT_CASE(test_string_compare_substring_subcstr__invalid_pos),\
    UT_CASE(test_string_compare_substring_subcstr__char_empty_empty),\
    UT_CASE(test_string_compare_substring_subcstr__char_non_empty_empty),\
    UT_CASE(test_string_compare_substring_subcstr__char_empty_non_empty),\
    UT_CASE(test_string_compare_substring_subcstr__char_sub_size_less),\
    UT_CASE(test_string_compare_substring_subcstr__char_sub_content_less),\
    UT_CASE(test_string_compare_substring_subcstr__char_sub_equal),\
    UT_CASE(test_string_compare_substring_subcstr__char_sub_size_greater),\
    UT_CASE(test_string_compare_substring_subcstr__char_sub_content_greater),\
    UT_CASE(test_string_compare_substring_subcstr__char_all_size_less),\
    UT_CASE(test_string_compare_substring_subcstr__char_all_content_less),\
    UT_CASE(test_string_compare_substring_subcstr__char_all_equal),\
    UT_CASE(test_string_compare_substring_subcstr__char_all_size_greater),\
    UT_CASE(test_string_compare_substring_subcstr__char_all_content_greater),\
    UT_CASE_BEGIN(string_substr, test_string_substr__null_string),\
    UT_CASE(test_string_substr__non_inited_string),\
    UT_CASE(test_string_substr__invalid_pos),\
    UT_CASE(test_string_substr__empty_substr),\
    UT_CASE(test_string_substr__all),\
    UT_CASE(test_string_substr__begin),\
    UT_CASE(test_string_substr__middle),\
    UT_CASE(test_string_substr__end),\
    UT_CASE_BEGIN(string_connect, test_string_connect__null_dest),\
    UT_CASE(test_string_connect__null_src),\
    UT_CASE(test_string_connect__non_inited_dest),\
    UT_CASE(test_string_connect__non_inited_src),\
    UT_CASE(test_string_connect__empty_empty),\
    UT_CASE(test_string_connect__non_empty_empty),\
    UT_CASE(test_string_connect__empty_non_empty),\
    UT_CASE(test_string_connect__same),\
    UT_CASE(test_string_connect__char),\
    UT_CASE_BEGIN(string_connect_cstr, test_string_connect_cstr__null_string),\
    UT_CASE(test_string_connect_cstr__null_value_string),\
    UT_CASE(test_string_connect_cstr__non_inited_string),\
    UT_CASE(test_string_connect_cstr__empty_empty),\
    UT_CASE(test_string_connect_cstr__non_empty_empty),\
    UT_CASE(test_string_connect_cstr__empty_non_empty),\
    UT_CASE(test_string_connect_cstr__char),\
    UT_CASE_BEGIN(string_connect_char, test_string_connect_char__null_string_container),\
    UT_CASE(test_string_connect_char__non_inited_string_container),\
    UT_CASE(test_string_connect_char__empty_container),\
    UT_CASE(test_string_connect_char__non_empty_container),\
    UT_CASE_BEGIN(string_find, test_string_find__null_string),\
    UT_CASE(test_string_find__null_find),\
    UT_CASE(test_string_find__non_inited_string),\
    UT_CASE(test_string_find__non_inited_find),\
    UT_CASE(test_string_find__invalid_pos),\
    UT_CASE(test_string_find__same_begin),\
    UT_CASE(test_string_find__same_middle),\
    UT_CASE(test_string_find__char_begin_empty),\
    UT_CASE(test_string_find__char_begin_find),\
    UT_CASE(test_string_find__char_begin_not_find),\
    UT_CASE(test_string_find__char_middle_empty),\
    UT_CASE(test_string_find__char_middle_find),\
    UT_CASE(test_string_find__char_middle_not_find),\
    UT_CASE(test_string_find__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_cstr, test_string_find_cstr__null_string),\
    UT_CASE(test_string_find_cstr__null_find),\
    UT_CASE(test_string_find_cstr__non_inited_string),\
    UT_CASE(test_string_find_cstr__invalid_pos),\
    UT_CASE(test_string_find_cstr__char_begin_empty),\
    UT_CASE(test_string_find_cstr__char_begin_find),\
    UT_CASE(test_string_find_cstr__char_begin_not_find),\
    UT_CASE(test_string_find_cstr__char_middle_empty),\
    UT_CASE(test_string_find_cstr__char_middle_find),\
    UT_CASE(test_string_find_cstr__char_middle_not_find),\
    UT_CASE(test_string_find_cstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_subcstr, test_string_find_subcstr__null_string),\
    UT_CASE(test_string_find_subcstr__null_find),\
    UT_CASE(test_string_find_subcstr__non_inited_string),\
    UT_CASE(test_string_find_subcstr__invalid_pos),\
    UT_CASE(test_string_find_subcstr__char_begin_empty),\
    UT_CASE(test_string_find_subcstr__char_begin_length_0),\
    UT_CASE(test_string_find_subcstr__char_begin_find),\
    UT_CASE(test_string_find_subcstr__char_begin_not_find),\
    UT_CASE(test_string_find_subcstr__char_middle_empty),\
    UT_CASE(test_string_find_subcstr__char_middle_length_0),\
    UT_CASE(test_string_find_subcstr__char_middle_find),\
    UT_CASE(test_string_find_subcstr__char_middle_not_find),\
    UT_CASE(test_string_find_subcstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_char, test_string_find_char__null_string_container),\
    UT_CASE(test_string_find_char__non_init_string_container),\
    UT_CASE(test_string_find_char__invalid_position),\
    UT_CASE(test_string_find_char__invalid_position_end),\
    UT_CASE(test_string_find_char__invalid_position_NPOS),\
    UT_CASE(test_string_find_char__find_failure),\
    UT_CASE(test_string_find_char__find_failure_middle_pos),\
    UT_CASE(test_string_find_char__find_successful),\
    UT_CASE(test_string_find_char__find_successful_middle),\
    UT_CASE(test_string_find_char__find_successful_back),\
    UT_CASE(test_string_find_char__find_successful_middle_pos),\
    UT_CASE_BEGIN(string_rfind, test_string_rfind__null_string),\
    UT_CASE(test_string_rfind__null_find),\
    UT_CASE(test_string_rfind__non_inited_string),\
    UT_CASE(test_string_rfind__non_inited_find),\
    UT_CASE(test_string_rfind__same_npos),\
    UT_CASE(test_string_rfind__same_middle),\
    UT_CASE(test_string_rfind__char_empty_empty_0),\
    UT_CASE(test_string_rfind__char_empty_empty_npos),\
    UT_CASE(test_string_rfind__char_empty_non_empty_0),\
    UT_CASE(test_string_rfind__char_empty_non_empty_npos),\
    UT_CASE(test_string_rfind__char_empty_npos),\
    UT_CASE(test_string_rfind__char_find_npos),\
    UT_CASE(test_string_rfind__char_not_find_npos),\
    UT_CASE(test_string_rfind__char_middle_empty),\
    UT_CASE(test_string_rfind__char_middle_find),\
    UT_CASE(test_string_rfind__char_middle_not_find),\
    UT_CASE(test_string_rfind__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_rfind_cstr, test_string_rfind_cstr__null_string),\
    UT_CASE(test_string_rfind_cstr__null_find),\
    UT_CASE(test_string_rfind_cstr__non_inited_string),\
    UT_CASE(test_string_rfind_cstr__char_empty_empty_0),\
    UT_CASE(test_string_rfind_cstr__char_empty_empty_npos),\
    UT_CASE(test_string_rfind_cstr__char_empty_non_empty_0),\
    UT_CASE(test_string_rfind_cstr__char_empty_non_empty_npos),\
    UT_CASE(test_string_rfind_cstr__char_empty_npos),\
    UT_CASE(test_string_rfind_cstr__char_find_npos),\
    UT_CASE(test_string_rfind_cstr__char_not_find_npos),\
    UT_CASE(test_string_rfind_cstr__char_middle_empty),\
    UT_CASE(test_string_rfind_cstr__char_middle_find),\
    UT_CASE(test_string_rfind_cstr__char_middle_not_find),\
    UT_CASE(test_string_rfind_cstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_rfind_subcstr, test_string_rfind_subcstr__null_string),\
    UT_CASE(test_string_rfind_subcstr__null_find),\
    UT_CASE(test_string_rfind_subcstr__non_inited_string),\
    UT_CASE(test_string_rfind_subcstr__char_empty_empty_0),\
    UT_CASE(test_string_rfind_subcstr__char_empty_empty_npos),\
    UT_CASE(test_string_rfind_subcstr__char_empty_non_empty_0_length_0),\
    UT_CASE(test_string_rfind_subcstr__char_empty_non_empty_npos_length_0),\
    UT_CASE(test_string_rfind_subcstr__char_empty_non_empty_0),\
    UT_CASE(test_string_rfind_subcstr__char_empty_non_empty_npos),\
    UT_CASE(test_string_rfind_subcstr__char_empty_npos),\
    UT_CASE(test_string_rfind_subcstr__char_non_empty_npos_length_0),\
    UT_CASE(test_string_rfind_subcstr__char_find_npos),\
    UT_CASE(test_string_rfind_subcstr__char_not_find_npos),\
    UT_CASE(test_string_rfind_subcstr__char_middle_empty),\
    UT_CASE(test_string_rfind_subcstr__char_middle_non_empty_length_0),\
    UT_CASE(test_string_rfind_subcstr__char_middle_find),\
    UT_CASE(test_string_rfind_subcstr__char_middle_not_find),\
    UT_CASE(test_string_rfind_subcstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_rfind_char, test_string_rfind_char__null_string_container),\
    UT_CASE(test_string_rfind_char__non_init_string_container),\
    UT_CASE(test_string_rfind_char__invalid_position),\
    UT_CASE(test_string_rfind_char__invalid_position_begin),\
    UT_CASE(test_string_rfind_char__invalid_position_NPOS),\
    UT_CASE(test_string_rfind_char__find_failure),\
    UT_CASE(test_string_rfind_char__find_failure_middle_pos),\
    UT_CASE(test_string_rfind_char__find_successful),\
    UT_CASE(test_string_rfind_char__find_successful_middle),\
    UT_CASE(test_string_rfind_char__find_successful_back),\
    UT_CASE(test_string_rfind_char__find_successful_middle_pos),\
    UT_CASE_BEGIN(string_find_first_of, test_string_find_first_of__null_string),\
    UT_CASE(test_string_find_first_of__null_find),\
    UT_CASE(test_string_find_first_of__non_inited_string),\
    UT_CASE(test_string_find_first_of__non_inited_find),\
    UT_CASE(test_string_find_first_of__invalid_pos),\
    UT_CASE(test_string_find_first_of__same_begin),\
    UT_CASE(test_string_find_first_of__same_middle),\
    UT_CASE(test_string_find_first_of__char_begin_empty),\
    UT_CASE(test_string_find_first_of__char_begin_find),\
    UT_CASE(test_string_find_first_of__char_begin_not_find),\
    UT_CASE(test_string_find_first_of__char_middle_empty),\
    UT_CASE(test_string_find_first_of__char_middle_find),\
    UT_CASE(test_string_find_first_of__char_middle_not_find),\
    UT_CASE(test_string_find_first_of__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_first_of_cstr, test_string_find_first_of_cstr__null_string),\
    UT_CASE(test_string_find_first_of_cstr__null_find),\
    UT_CASE(test_string_find_first_of_cstr__non_inited_string),\
    UT_CASE(test_string_find_first_of_cstr__invalid_pos),\
    UT_CASE(test_string_find_first_of_cstr__char_begin_empty),\
    UT_CASE(test_string_find_first_of_cstr__char_begin_find),\
    UT_CASE(test_string_find_first_of_cstr__char_begin_not_find),\
    UT_CASE(test_string_find_first_of_cstr__char_middle_empty),\
    UT_CASE(test_string_find_first_of_cstr__char_middle_find),\
    UT_CASE(test_string_find_first_of_cstr__char_middle_not_find),\
    UT_CASE(test_string_find_first_of_cstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_first_of_subcstr, test_string_find_first_of_subcstr__null_string),\
    UT_CASE(test_string_find_first_of_subcstr__null_find),\
    UT_CASE(test_string_find_first_of_subcstr__non_inited_string),\
    UT_CASE(test_string_find_first_of_subcstr__invalid_pos),\
    UT_CASE(test_string_find_first_of_subcstr__char_begin_empty),\
    UT_CASE(test_string_find_first_of_subcstr__char_begin_length_0),\
    UT_CASE(test_string_find_first_of_subcstr__char_begin_find),\
    UT_CASE(test_string_find_first_of_subcstr__char_begin_not_find),\
    UT_CASE(test_string_find_first_of_subcstr__char_middle_empty),\
    UT_CASE(test_string_find_first_of_subcstr__char_middle_length_0),\
    UT_CASE(test_string_find_first_of_subcstr__char_middle_find),\
    UT_CASE(test_string_find_first_of_subcstr__char_middle_not_find),\
    UT_CASE(test_string_find_first_of_subcstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_first_of_char, test_string_find_first_of_char__null_string_container),\
    UT_CASE(test_string_find_first_of_char__non_init_string_container),\
    UT_CASE(test_string_find_first_of_char__invalid_position),\
    UT_CASE(test_string_find_first_of_char__invalid_position_end),\
    UT_CASE(test_string_find_first_of_char__invalid_position_NPOS),\
    UT_CASE(test_string_find_first_of_char__find_failure),\
    UT_CASE(test_string_find_first_of_char__find_failure_middle_pos),\
    UT_CASE(test_string_find_first_of_char__find_successful),\
    UT_CASE(test_string_find_first_of_char__find_successful_middle),\
    UT_CASE(test_string_find_first_of_char__find_successful_back),\
    UT_CASE(test_string_find_first_of_char__find_successful_middle_pos),\
    UT_CASE_BEGIN(string_find_first_not_of, test_string_find_first_not_of__null_string),\
    UT_CASE(test_string_find_first_not_of__null_find),\
    UT_CASE(test_string_find_first_not_of__non_inited_string),\
    UT_CASE(test_string_find_first_not_of__non_inited_find),\
    UT_CASE(test_string_find_first_not_of__invalid_pos),\
    UT_CASE(test_string_find_first_not_of__same_begin),\
    UT_CASE(test_string_find_first_not_of__same_middle),\
    UT_CASE(test_string_find_first_not_of__char_begin_empty),\
    UT_CASE(test_string_find_first_not_of__char_begin_find),\
    UT_CASE(test_string_find_first_not_of__char_begin_not_find),\
    UT_CASE(test_string_find_first_not_of__char_middle_empty),\
    UT_CASE(test_string_find_first_not_of__char_middle_find),\
    UT_CASE(test_string_find_first_not_of__char_middle_not_find),\
    UT_CASE(test_string_find_first_not_of__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_first_not_of_cstr, test_string_find_first_not_of_cstr__null_string),\
    UT_CASE(test_string_find_first_not_of_cstr__null_find),\
    UT_CASE(test_string_find_first_not_of_cstr__non_inited_string),\
    UT_CASE(test_string_find_first_not_of_cstr__invalid_pos),\
    UT_CASE(test_string_find_first_not_of_cstr__char_begin_empty),\
    UT_CASE(test_string_find_first_not_of_cstr__char_begin_find),\
    UT_CASE(test_string_find_first_not_of_cstr__char_begin_not_find),\
    UT_CASE(test_string_find_first_not_of_cstr__char_middle_empty),\
    UT_CASE(test_string_find_first_not_of_cstr__char_middle_find),\
    UT_CASE(test_string_find_first_not_of_cstr__char_middle_not_find),\
    UT_CASE(test_string_find_first_not_of_cstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_first_not_of_subcstr, test_string_find_first_not_of_subcstr__null_string),\
    UT_CASE(test_string_find_first_not_of_subcstr__null_find),\
    UT_CASE(test_string_find_first_not_of_subcstr__non_inited_string),\
    UT_CASE(test_string_find_first_not_of_subcstr__invalid_pos),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_begin_empty),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_begin_length_0),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_begin_find),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_begin_not_find),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_middle_empty),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_middle_length_0),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_middle_find),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_middle_not_find),\
    UT_CASE(test_string_find_first_not_of_subcstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_first_not_of_char, test_string_find_first_not_of_char__null_string_container),\
    UT_CASE(test_string_find_first_not_of_char__non_init_string_container),\
    UT_CASE(test_string_find_first_not_of_char__invalid_position),\
    UT_CASE(test_string_find_first_not_of_char__invalid_position_end),\
    UT_CASE(test_string_find_first_not_of_char__invalid_position_NPOS),\
    UT_CASE(test_string_find_first_not_of_char__find_first_not_of_failure),\
    UT_CASE(test_string_find_first_not_of_char__find_first_not_of_failure_middle_pos),\
    UT_CASE(test_string_find_first_not_of_char__find_first_not_of_successful),\
    UT_CASE(test_string_find_first_not_of_char__find_first_not_of_successful_middle),\
    UT_CASE(test_string_find_first_not_of_char__find_first_not_of_successful_back),\
    UT_CASE(test_string_find_first_not_of_char__find_first_not_of_successful_middle_pos),\
    UT_CASE_BEGIN(string_find_last_of, test_string_find_last_of__null_string),\
    UT_CASE(test_string_find_last_of__null_find),\
    UT_CASE(test_string_find_last_of__non_inited_string),\
    UT_CASE(test_string_find_last_of__non_inited_find),\
    UT_CASE(test_string_find_last_of__same_npos),\
    UT_CASE(test_string_find_last_of__same_middle),\
    UT_CASE(test_string_find_last_of__char_empty_empty_0),\
    UT_CASE(test_string_find_last_of__char_empty_empty_npos),\
    UT_CASE(test_string_find_last_of__char_empty_non_empty_0),\
    UT_CASE(test_string_find_last_of__char_empty_non_empty_npos),\
    UT_CASE(test_string_find_last_of__char_empty_npos),\
    UT_CASE(test_string_find_last_of__char_find_npos),\
    UT_CASE(test_string_find_last_of__char_not_find_npos),\
    UT_CASE(test_string_find_last_of__char_middle_empty),\
    UT_CASE(test_string_find_last_of__char_middle_find),\
    UT_CASE(test_string_find_last_of__char_middle_not_find),\
    UT_CASE(test_string_find_last_of__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_last_of_cstr, test_string_find_last_of_cstr__null_string),\
    UT_CASE(test_string_find_last_of_cstr__null_find),\
    UT_CASE(test_string_find_last_of_cstr__non_inited_string),\
    UT_CASE(test_string_find_last_of_cstr__char_empty_empty_0),\
    UT_CASE(test_string_find_last_of_cstr__char_empty_empty_npos),\
    UT_CASE(test_string_find_last_of_cstr__char_empty_non_empty_0),\
    UT_CASE(test_string_find_last_of_cstr__char_empty_non_empty_npos),\
    UT_CASE(test_string_find_last_of_cstr__char_empty_npos),\
    UT_CASE(test_string_find_last_of_cstr__char_find_npos),\
    UT_CASE(test_string_find_last_of_cstr__char_not_find_npos),\
    UT_CASE(test_string_find_last_of_cstr__char_middle_empty),\
    UT_CASE(test_string_find_last_of_cstr__char_middle_find),\
    UT_CASE(test_string_find_last_of_cstr__char_middle_not_find),\
    UT_CASE(test_string_find_last_of_cstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_last_of_subcstr, test_string_find_last_of_subcstr__null_string),\
    UT_CASE(test_string_find_last_of_subcstr__null_find),\
    UT_CASE(test_string_find_last_of_subcstr__non_inited_string),\
    UT_CASE(test_string_find_last_of_subcstr__char_empty_empty_0),\
    UT_CASE(test_string_find_last_of_subcstr__char_empty_empty_npos),\
    UT_CASE(test_string_find_last_of_subcstr__char_empty_non_empty_0_length_0),\
    UT_CASE(test_string_find_last_of_subcstr__char_empty_non_empty_npos_length_0),\
    UT_CASE(test_string_find_last_of_subcstr__char_empty_non_empty_0),\
    UT_CASE(test_string_find_last_of_subcstr__char_empty_non_empty_npos),\
    UT_CASE(test_string_find_last_of_subcstr__char_empty_npos),\
    UT_CASE(test_string_find_last_of_subcstr__char_non_empty_npos_length_0),\
    UT_CASE(test_string_find_last_of_subcstr__char_find_npos),\
    UT_CASE(test_string_find_last_of_subcstr__char_not_find_npos),\
    UT_CASE(test_string_find_last_of_subcstr__char_middle_empty),\
    UT_CASE(test_string_find_last_of_subcstr__char_middle_non_empty_length_0),\
    UT_CASE(test_string_find_last_of_subcstr__char_middle_find),\
    UT_CASE(test_string_find_last_of_subcstr__char_middle_not_find),\
    UT_CASE(test_string_find_last_of_subcstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_last_of_char, test_string_find_last_of_char__null_string_container),\
    UT_CASE(test_string_find_last_of_char__non_init_string_container),\
    UT_CASE(test_string_find_last_of_char__invalid_position),\
    UT_CASE(test_string_find_last_of_char__invalid_position_begin),\
    UT_CASE(test_string_find_last_of_char__invalid_position_NPOS),\
    UT_CASE(test_string_find_last_of_char__find_failure),\
    UT_CASE(test_string_find_last_of_char__find_failure_middle_pos),\
    UT_CASE(test_string_find_last_of_char__find_successful),\
    UT_CASE(test_string_find_last_of_char__find_successful_middle),\
    UT_CASE(test_string_find_last_of_char__find_successful_back),\
    UT_CASE(test_string_find_last_of_char__find_successful_middle_pos),\
    UT_CASE_BEGIN(string_find_last_not_of, test_string_find_last_not_of__null_string),\
    UT_CASE(test_string_find_last_not_of__null_find),\
    UT_CASE(test_string_find_last_not_of__non_inited_string),\
    UT_CASE(test_string_find_last_not_of__non_inited_find),\
    UT_CASE(test_string_find_last_not_of__same_npos),\
    UT_CASE(test_string_find_last_not_of__same_middle),\
    UT_CASE(test_string_find_last_not_of__char_empty_empty_0),\
    UT_CASE(test_string_find_last_not_of__char_empty_empty_npos),\
    UT_CASE(test_string_find_last_not_of__char_empty_non_empty_0),\
    UT_CASE(test_string_find_last_not_of__char_empty_non_empty_npos),\
    UT_CASE(test_string_find_last_not_of__char_empty_npos),\
    UT_CASE(test_string_find_last_not_of__char_find_npos),\
    UT_CASE(test_string_find_last_not_of__char_not_find_npos),\
    UT_CASE(test_string_find_last_not_of__char_middle_empty),\
    UT_CASE(test_string_find_last_not_of__char_middle_find),\
    UT_CASE(test_string_find_last_not_of__char_middle_not_find),\
    UT_CASE(test_string_find_last_not_of__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_last_not_of_cstr, test_string_find_last_not_of_cstr__null_string),\
    UT_CASE(test_string_find_last_not_of_cstr__null_find),\
    UT_CASE(test_string_find_last_not_of_cstr__non_inited_string),\
    UT_CASE(test_string_find_last_not_of_cstr__char_empty_empty_0),\
    UT_CASE(test_string_find_last_not_of_cstr__char_empty_empty_npos),\
    UT_CASE(test_string_find_last_not_of_cstr__char_empty_non_empty_0),\
    UT_CASE(test_string_find_last_not_of_cstr__char_empty_non_empty_npos),\
    UT_CASE(test_string_find_last_not_of_cstr__char_empty_npos),\
    UT_CASE(test_string_find_last_not_of_cstr__char_find_npos),\
    UT_CASE(test_string_find_last_not_of_cstr__char_not_find_npos),\
    UT_CASE(test_string_find_last_not_of_cstr__char_middle_empty),\
    UT_CASE(test_string_find_last_not_of_cstr__char_middle_find),\
    UT_CASE(test_string_find_last_not_of_cstr__char_middle_not_find),\
    UT_CASE(test_string_find_last_not_of_cstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_last_not_of_subcstr, test_string_find_last_not_of_subcstr__null_string),\
    UT_CASE(test_string_find_last_not_of_subcstr__null_find),\
    UT_CASE(test_string_find_last_not_of_subcstr__non_inited_string),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_empty_empty_0),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_empty_empty_npos),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_empty_non_empty_0_length_0),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_empty_non_empty_npos_length_0),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_empty_non_empty_0),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_empty_non_empty_npos),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_empty_npos),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_non_empty_npos_length_0),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_find_npos),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_not_find_npos),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_middle_empty),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_middle_non_empty_length_0),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_middle_find),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_middle_not_find),\
    UT_CASE(test_string_find_last_not_of_subcstr__char_middle_not_find_pos),\
    UT_CASE_BEGIN(string_find_last_not_of_char, test_string_find_last_not_of_char__null_string_container),\
    UT_CASE(test_string_find_last_not_of_char__non_init_string_container),\
    UT_CASE(test_string_find_last_not_of_char__invalid_position),\
    UT_CASE(test_string_find_last_not_of_char__invalid_position_begin),\
    UT_CASE(test_string_find_last_not_of_char__invalid_position_NPOS),\
    UT_CASE(test_string_find_last_not_of_char__find_failure),\
    UT_CASE(test_string_find_last_not_of_char__find_failure_middle_pos),\
    UT_CASE(test_string_find_last_not_of_char__find_successful),\
    UT_CASE(test_string_find_last_not_of_char__find_successful_middle),\
    UT_CASE(test_string_find_last_not_of_char__find_successful_back),\
    UT_CASE(test_string_find_last_not_of_char__find_successful_middle_pos),\
    UT_CASE_BEGIN(string_clear, test_string_clear__null_string_container),\
    UT_CASE(test_string_clear__non_inited_string_container),\
    UT_CASE(test_string_clear__empty_string_container),\
    UT_CASE(test_string_clear__non_empty_string_container),\
    UT_CASE_BEGIN(string_swap, test_string_swap__null_first),\
    UT_CASE(test_string_swap__null_second),\
    UT_CASE(test_string_swap__non_inited_first),\
    UT_CASE(test_string_swap__non_inited_second),\
    UT_CASE(test_string_swap__string_equal),\
    UT_CASE(test_string_swap__0_swap_10),\
    UT_CASE(test_string_swap__10_swap_0),\
    UT_CASE(test_string_swap__10_swap_10),\
    UT_CASE_BEGIN(string_reserve, test_string_reserve__null_string_container),\
    UT_CASE(test_string_reserve__non_inited),\
    UT_CASE(test_string_reserve__shrink),\
    UT_CASE(test_string_reserve__not_change),\
    UT_CASE(test_string_reserve__expand),\
    UT_CASE_BEGIN(string_assign, test_string_assign__null_dest),\
    UT_CASE(test_string_assign__null_src),\
    UT_CASE(test_string_assign__non_inited_dest),\
    UT_CASE(test_string_assign__non_inited_src),\
    UT_CASE(test_string_assign__same_container),\
    UT_CASE(test_string_assign__0_assign_0),\
    UT_CASE(test_string_assign__0_assign_10),\
    UT_CASE(test_string_assign__0_assign_1000),\
    UT_CASE(test_string_assign__10_assign_0),\
    UT_CASE(test_string_assign__10_assign_10_string_equal),\
    UT_CASE(test_string_assign__10_assign_10_string_not_equal),\
    UT_CASE(test_string_assign__10_assign_1000),\
    UT_CASE(test_string_assign__1000_assign_0),\
    UT_CASE(test_string_assign__1000_assign_10),\
    UT_CASE(test_string_assign__1000_assign_1010),\
    UT_CASE(test_string_assign__1000_assign_1810),\
    UT_CASE_BEGIN(string_assign_substring, test_string_assign_substring__null_dest),\
    UT_CASE(test_string_assign_substring__null_src),\
    UT_CASE(test_string_assign_substring__non_inited_dest),\
    UT_CASE(test_string_assign_substring__non_inited_src),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_begin_empty),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_begin_non_empty),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_begin_length),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_begin_npos),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_middle_empty),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_middle_non_empty),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_middle_length),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_middle_npos),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_end),\
    UT_CASE(test_string_assign_substring__successfully_src_non_empty_npos),\
    UT_CASE_BEGIN(string_assign_range, test_string_assign_range__null_dest),\
    UT_CASE(test_string_assign_range__non_inited_dest),\
    UT_CASE(test_string_assign_range__invalid_begin_iterator),\
    UT_CASE(test_string_assign_range__invalid_end_iterator),\
    UT_CASE(test_string_assign_range__invalid_range),\
    UT_CASE(test_string_assign_range__successfully_empty_range),\
    UT_CASE(test_string_assign_range__successfully),\
    UT_CASE_BEGIN(string_assign_cstr, test_string_assign_cstr__null_container),\
    UT_CASE(test_string_assign_cstr__non_inited),\
    UT_CASE(test_string_assign_cstr__null_valuestring),\
    UT_CASE(test_string_assign_cstr__empty),\
    UT_CASE(test_string_assign_cstr__non_empty),\
    UT_CASE_BEGIN(string_assign_subcstr, test_string_assign_subcstr__null_container),\
    UT_CASE(test_string_assign_subcstr__non_created_container),\
    UT_CASE(test_string_assign_subcstr__null_valuestring),\
    UT_CASE(test_string_assign_subcstr__empty),\
    UT_CASE(test_string_assign_subcstr__non_empty),\
    UT_CASE(test_string_assign_subcstr__total),\
    UT_CASE_BEGIN(string_assign_char, test_string_assign_char__null_container),\
    UT_CASE(test_string_assign_char__non_inited_container),\
    UT_CASE(test_string_assign_char__empty_container_assign_empty),\
    UT_CASE(test_string_assign_char__empty_container_assign_non_empty),\
    UT_CASE(test_string_assign_char__non_empty_container_assign_empty),\
    UT_CASE(test_string_assign_char__non_empty_container_assign_less),\
    UT_CASE(test_string_assign_char__non_empty_container_assign_equal),\
    UT_CASE(test_string_assign_char__non_empty_container_assign_greater),\
    UT_CASE_BEGIN(string_append, test_string_append__null_dest),\
    UT_CASE(test_string_append__null_src),\
    UT_CASE(test_string_append__non_inited_dest),\
    UT_CASE(test_string_append__non_inited_src),\
    UT_CASE(test_string_append__same_container),\
    UT_CASE(test_string_append__0_assign_0),\
    UT_CASE(test_string_append__0_assign_10),\
    UT_CASE(test_string_append__10_assign_0),\
    UT_CASE(test_string_append__1000_assign_1810),\
    UT_CASE_BEGIN(string_append_substring, test_string_append_substring__null_dest),\
    UT_CASE(test_string_append_substring__null_src),\
    UT_CASE(test_string_append_substring__non_inited_dest),\
    UT_CASE(test_string_append_substring__non_inited_src),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_begin_empty),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_begin_non_empty),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_begin_length),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_begin_npos),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_middle_empty),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_middle_non_empty),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_middle_length),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_middle_npos),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_end),\
    UT_CASE(test_string_append_substring__successfully_src_non_empty_npos),\
    UT_CASE_BEGIN(string_append_range, test_string_append_range__null_dest),\
    UT_CASE(test_string_append_range__non_inited_dest),\
    UT_CASE(test_string_append_range__invalid_begin_iterator),\
    UT_CASE(test_string_append_range__invalid_end_iterator),\
    UT_CASE(test_string_append_range__invalid_range),\
    UT_CASE(test_string_append_range__successfully_empty_range),\
    UT_CASE(test_string_append_range__same_container),\
    UT_CASE(test_string_append_range__successfully),\
    UT_CASE_BEGIN(string_append_cstr, test_string_append_cstr__null_container),\
    UT_CASE(test_string_append_cstr__non_inited),\
    UT_CASE(test_string_append_cstr__null_valuestring),\
    UT_CASE(test_string_append_cstr__empty),\
    UT_CASE(test_string_append_cstr__non_empty),\
    UT_CASE_BEGIN(string_append_subcstr, test_string_append_subcstr__null_container),\
    UT_CASE(test_string_append_subcstr__non_created_container),\
    UT_CASE(test_string_append_subcstr__null_valuestring),\
    UT_CASE(test_string_append_subcstr__empty),\
    UT_CASE(test_string_append_subcstr__non_empty),\
    UT_CASE(test_string_append_subcstr__total),\
    UT_CASE_BEGIN(string_append_char, test_string_append_char__null_container),\
    UT_CASE(test_string_append_char__non_inited_container),\
    UT_CASE(test_string_append_char__empty_append_empty),\
    UT_CASE(test_string_append_char__empty_append_non_empty),\
    UT_CASE(test_string_append_char__non_empty_append_empty),\
    UT_CASE(test_string_append_char__non_empty_append_non_empty),\
    UT_CASE_BEGIN(string_insert, test_string_insert__null_string_container),\
    UT_CASE(test_string_insert__non_inited),\
    UT_CASE(test_string_insert__invalid_position),\
    UT_CASE(test_string_insert__empty),\
    UT_CASE(test_string_insert__begin),\
    UT_CASE(test_string_insert__middle),\
    UT_CASE(test_string_insert__end),\
    UT_CASE_BEGIN(string_insert_n, test_string_insert_n__null_string_container),\
    UT_CASE(test_string_insert_n__non_inited),\
    UT_CASE(test_string_insert_n__invalid_position),\
    UT_CASE(test_string_insert_n__empty_insert_0),\
    UT_CASE(test_string_insert_n__empty_insert_10),\
    UT_CASE(test_string_insert_n__empty_insert_1000),\
    UT_CASE(test_string_insert_n__begin_insert_0),\
    UT_CASE(test_string_insert_n__begin_insert_10),\
    UT_CASE(test_string_insert_n__begin_insert_1000),\
    UT_CASE(test_string_insert_n__middle_insert_0),\
    UT_CASE(test_string_insert_n__middle_insert_10),\
    UT_CASE(test_string_insert_n__middle_insert_1000),\
    UT_CASE(test_string_insert_n__end_insert_0),\
    UT_CASE(test_string_insert_n__end_insert_10),\
    UT_CASE(test_string_insert_n__end_insert_1000),\
    UT_CASE_BEGIN(string_insert_string, test_string_insert_string__null_dest),\
    UT_CASE(test_string_insert_string__null_insert),\
    UT_CASE(test_string_insert_string__non_inited_dest),\
    UT_CASE(test_string_insert_string__non_inited_insert),\
    UT_CASE(test_string_insert_string__same_container),\
    UT_CASE(test_string_insert_string__invalid_pos),\
    UT_CASE(test_string_insert_string__char_middle_insert_empty),\
    UT_CASE(test_string_insert_string__char_begin_insert_non_empty),\
    UT_CASE_BEGIN(string_insert_substring, test_string_insert_substring__null_dest),\
    UT_CASE(test_string_insert_substring__null_insert),\
    UT_CASE(test_string_insert_substring__non_inited_dest),\
    UT_CASE(test_string_insert_substring__non_inited_insert),\
    UT_CASE(test_string_insert_substring__same_container),\
    UT_CASE(test_string_insert_substring__invalid_pos),\
    UT_CASE(test_string_insert_substring__invalid_startpos),\
    UT_CASE(test_string_insert_substring__char_middle_insert_empty),\
    UT_CASE(test_string_insert_substring__char_begin_insert_non_empty),\
    UT_CASE_BEGIN(string_insert_cstr, test_string_insert_cstr__null_container),\
    UT_CASE(test_string_insert_cstr__non_inited),\
    UT_CASE(test_string_insert_cstr__null_valuestring),\
    UT_CASE(test_string_insert_cstr__invalid_pos),\
    UT_CASE(test_string_insert_cstr__char_empty),\
    UT_CASE(test_string_insert_cstr__char_non_empty),\
    UT_CASE_BEGIN(string_insert_subcstr, test_string_insert_subcstr__null_container),\
    UT_CASE(test_string_insert_subcstr__non_created_container),\
    UT_CASE(test_string_insert_subcstr__null_valuestring),\
    UT_CASE(test_string_insert_subcstr__invalid_pos),\
    UT_CASE(test_string_insert_subcstr__char_empty),\
    UT_CASE(test_string_insert_subcstr__char_non_empty),\
    UT_CASE(test_string_insert_subcstr__char_total),\
    UT_CASE_BEGIN(string_insert_range, test_string_insert_range__null_string),\
    UT_CASE(test_string_insert_range__non_inited_string),\
    UT_CASE(test_string_insert_range__invalid_pos),\
    UT_CASE(test_string_insert_range__invalid_begin),\
    UT_CASE(test_string_insert_range__invalid_end),\
    UT_CASE(test_string_insert_range__invalid_range),\
    UT_CASE(test_string_insert_range__empty_insert_empty),\
    UT_CASE(test_string_insert_range__empty_insert_non_empty),\
    UT_CASE(test_string_insert_range__non_empty_insert_begin_empty),\
    UT_CASE(test_string_insert_range__non_empty_insert_middle_empty),\
    UT_CASE(test_string_insert_range__non_empty_insert_end_empty),\
    UT_CASE(test_string_insert_range__non_empty_insert_begin_non_empty),\
    UT_CASE(test_string_insert_range__non_empty_insert_middle_non_empty),\
    UT_CASE(test_string_insert_range__range_belong_to_dest),\
    UT_CASE(test_string_insert_range__non_empty_insert_end_non_empty),\
    UT_CASE_BEGIN(string_insert_char, test_string_insert_char__null_string_container),\
    UT_CASE(test_string_insert_char__non_inited),\
    UT_CASE(test_string_insert_char__invalid_position),\
    UT_CASE(test_string_insert_char__empty_insert_0),\
    UT_CASE(test_string_insert_char__empty_insert_10),\
    UT_CASE(test_string_insert_char__empty_insert_1000),\
    UT_CASE(test_string_insert_char__begin_insert_0),\
    UT_CASE(test_string_insert_char__begin_insert_10),\
    UT_CASE(test_string_insert_char__begin_insert_1000),\
    UT_CASE(test_string_insert_char__middle_insert_0),\
    UT_CASE(test_string_insert_char__middle_insert_10),\
    UT_CASE(test_string_insert_char__middle_insert_1000),\
    UT_CASE(test_string_insert_char__end_insert_0),\
    UT_CASE(test_string_insert_char__end_insert_10),\
    UT_CASE(test_string_insert_char__end_insert_1000),\
    UT_CASE_BEGIN(string_resize_char, test_string_resize_char__null_string_container),\
    UT_CASE(test_string_resize_char__non_inited),\
    UT_CASE(test_string_resize_char__successfully_0_resize_0),\
    UT_CASE(test_string_resize_char__successfully_0_resize_10),\
    UT_CASE(test_string_resize_char__successfully_10_resize_0),\
    UT_CASE(test_string_resize_char__successfully_10_resize_10),\
    UT_CASE(test_string_resize_char__successfully_10_resize_1000),\
    UT_CASE(test_string_resize_char__successfully_1000_resize_10),\
    UT_CASE_BEGIN(string_resize, test_string_resize__null_string_container),\
    UT_CASE(test_string_resize__non_inited),\
    UT_CASE(test_string_resize__successfully_0_resize_0),\
    UT_CASE(test_string_resize__successfully_0_resize_10),\
    UT_CASE(test_string_resize__successfully_10_resize_0),\
    UT_CASE(test_string_resize__successfully_10_resize_10),\
    UT_CASE(test_string_resize__successfully_10_resize_1000),\
    UT_CASE(test_string_resize__successfully_1000_resize_10),\
    UT_CASE_BEGIN(string_erase, test_string_erase__null_string),\
    UT_CASE(test_string_erase__non_inited_string),\
    UT_CASE(test_string_erase__invalid_pos),\
    UT_CASE(test_string_erase__empty),\
    UT_CASE(test_string_erase__begin),\
    UT_CASE(test_string_erase__middle),\
    UT_CASE(test_string_erase__last),\
    UT_CASE_BEGIN(string_erase_range, test_string_erase_range__null_string),\
    UT_CASE(test_string_erase_range__non_inited_string),\
    UT_CASE(test_string_erase_range__invalid_begin),\
    UT_CASE(test_string_erase_range__invalid_end),\
    UT_CASE(test_string_erase_range__invalid_range),\
    UT_CASE(test_string_erase_range__empty),\
    UT_CASE(test_string_erase_range__begin),\
    UT_CASE(test_string_erase_range__middle),\
    UT_CASE(test_string_erase_range__end),\
    UT_CASE(test_string_erase_range__all),\
    UT_CASE(test_string_erase_range__erase_empty),\
    UT_CASE_BEGIN(string_erase_substring, test_string_erase_substring__null_string),\
    UT_CASE(test_string_erase_substring__non_inited_string),\
    UT_CASE(test_string_erase_substring__invalid_pos),\
    UT_CASE(test_string_erase_substring__begin),\
    UT_CASE(test_string_erase_substring__middle),\
    UT_CASE(test_string_erase_substring__end),\
    UT_CASE(test_string_erase_substring__all),\
    UT_CASE(test_string_erase_substring__erase_empty),\
    UT_CASE_BEGIN(string_replace, test_string_replace__null_dest),\
    UT_CASE(test_string_replace__null_replace),\
    UT_CASE(test_string_replace__non_inited_dest),\
    UT_CASE(test_string_replace__non_inited_replace),\
    UT_CASE(test_string_replace__same_container),\
    UT_CASE(test_string_replace__invalid_pos),\
    UT_CASE(test_string_replace__begin_empty_replace_empty),\
    UT_CASE(test_string_replace__begin_empty_replace_non_empty),\
    UT_CASE(test_string_replace__begin_non_empty_replace_empty),\
    UT_CASE(test_string_replace__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace__middle_empty_replace_empty),\
    UT_CASE(test_string_replace__middle_empty_replace_non_empty),\
    UT_CASE(test_string_replace__middle_non_empty_replace_empty),\
    UT_CASE(test_string_replace__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace__end_non_empty_replace_empty),\
    UT_CASE(test_string_replace__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace__all_replace_empty),\
    UT_CASE(test_string_replace__all_replace_non_empty),\
    UT_CASE_BEGIN(string_replace_substring, test_string_replace_substring__null_dest),\
    UT_CASE(test_string_replace_substring__null_replace),\
    UT_CASE(test_string_replace_substring__non_inited_dest),\
    UT_CASE(test_string_replace_substring__non_inited_replace),\
    UT_CASE(test_string_replace_substring__same_container),\
    UT_CASE(test_string_replace_substring__invalid_pos),\
    UT_CASE(test_string_replace_substring__invalid_position),\
    UT_CASE(test_string_replace_substring__begin_empty_replace_empty),\
    UT_CASE(test_string_replace_substring__begin_empty_replace_non_empty),\
    UT_CASE(test_string_replace_substring__begin_non_empty_replace_empty),\
    UT_CASE(test_string_replace_substring__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_substring__middle_empty_replace_empty),\
    UT_CASE(test_string_replace_substring__middle_empty_replace_non_empty),\
    UT_CASE(test_string_replace_substring__middle_non_empty_replace_empty),\
    UT_CASE(test_string_replace_substring__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_substring__end_non_empty_replace_empty),\
    UT_CASE(test_string_replace_substring__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_substring__all_replace_empty),\
    UT_CASE(test_string_replace_substring__all_replace_non_empty),\
    UT_CASE_BEGIN(string_replace_cstr, test_string_replace_cstr__null_dest),\
    UT_CASE(test_string_replace_cstr__null_replace),\
    UT_CASE(test_string_replace_cstr__non_inited_dest),\
    UT_CASE(test_string_replace_cstr__invalid_pos),\
    UT_CASE(test_string_replace_cstr__begin_empty_replace_empty),\
    UT_CASE(test_string_replace_cstr__begin_empty_replace_non_empty),\
    UT_CASE(test_string_replace_cstr__begin_non_empty_replace_empty),\
    UT_CASE(test_string_replace_cstr__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_cstr__middle_empty_replace_empty),\
    UT_CASE(test_string_replace_cstr__middle_empty_replace_non_empty),\
    UT_CASE(test_string_replace_cstr__middle_non_empty_replace_empty),\
    UT_CASE(test_string_replace_cstr__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_cstr__end_non_empty_replace_empty),\
    UT_CASE(test_string_replace_cstr__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_cstr__all_replace_empty),\
    UT_CASE(test_string_replace_cstr__all_replace_non_empty),\
    UT_CASE_BEGIN(string_replace_subcstr, test_string_replace_subcstr__null_dest),\
    UT_CASE(test_string_replace_subcstr__null_replace),\
    UT_CASE(test_string_replace_subcstr__non_inited_dest),\
    UT_CASE(test_string_replace_subcstr__invalid_pos),\
    UT_CASE(test_string_replace_subcstr__begin_empty_replace_empty),\
    UT_CASE(test_string_replace_subcstr__begin_empty_replace_non_empty),\
    UT_CASE(test_string_replace_subcstr__begin_non_empty_replace_empty),\
    UT_CASE(test_string_replace_subcstr__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_subcstr__middle_empty_replace_empty),\
    UT_CASE(test_string_replace_subcstr__middle_empty_replace_non_empty),\
    UT_CASE(test_string_replace_subcstr__middle_non_empty_replace_empty),\
    UT_CASE(test_string_replace_subcstr__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_subcstr__end_non_empty_replace_empty),\
    UT_CASE(test_string_replace_subcstr__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_subcstr__all_replace_empty),\
    UT_CASE(test_string_replace_subcstr__all_replace_non_empty),\
    UT_CASE_BEGIN(string_replace_char, test_string_replace_char__null_container),\
    UT_CASE(test_string_replace_char__non_inited_container),\
    UT_CASE(test_string_replace_char__empty_replace_empty),\
    UT_CASE(test_string_replace_char__empty_replace_non_empty),\
    UT_CASE(test_string_replace_char__begin_replace_empty),\
    UT_CASE(test_string_replace_char__begin_replace_less),\
    UT_CASE(test_string_replace_char__begin_replace_equal),\
    UT_CASE(test_string_replace_char__begin_replace_greater),\
    UT_CASE(test_string_replace_char__middle_replace_empty),\
    UT_CASE(test_string_replace_char__middle_replace_less),\
    UT_CASE(test_string_replace_char__middle_replace_equal),\
    UT_CASE(test_string_replace_char__middle_replace_greater),\
    UT_CASE(test_string_replace_char__end_replace_empty),\
    UT_CASE(test_string_replace_char__end_replace_less),\
    UT_CASE(test_string_replace_char__end_replace_equal),\
    UT_CASE(test_string_replace_char__end_replace_greater),\
    UT_CASE(test_string_replace_char__replace_all),\
    UT_CASE_BEGIN(string_range_replace, test_string_range_replace__null_dest),\
    UT_CASE(test_string_range_replace__null_replace),\
    UT_CASE(test_string_range_replace__non_inited_dest),\
    UT_CASE(test_string_range_replace__non_inited_replace),\
    UT_CASE(test_string_range_replace__same_container),\
    UT_CASE(test_string_range_replace__invalid_range),\
    UT_CASE(test_string_range_replace__begin_empty_replace_empty),\
    UT_CASE(test_string_range_replace__begin_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace__begin_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace__middle_empty_replace_empty),\
    UT_CASE(test_string_range_replace__middle_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace__middle_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace__end_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace__all_replace_empty),\
    UT_CASE(test_string_range_replace__all_replace_non_empty),\
    UT_CASE_BEGIN(string_range_replace_substring, test_string_range_replace_substring__null_dest),\
    UT_CASE(test_string_range_replace_substring__null_replace),\
    UT_CASE(test_string_range_replace_substring__non_inited_dest),\
    UT_CASE(test_string_range_replace_substring__non_inited_replace),\
    UT_CASE(test_string_range_replace_substring__same_container),\
    UT_CASE(test_string_range_replace_substring__invalid_range),\
    UT_CASE(test_string_range_replace_substring__invalid_position),\
    UT_CASE(test_string_range_replace_substring__begin_empty_replace_empty),\
    UT_CASE(test_string_range_replace_substring__begin_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_substring__begin_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_substring__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_substring__middle_empty_replace_empty),\
    UT_CASE(test_string_range_replace_substring__middle_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_substring__middle_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_substring__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_substring__end_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_substring__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_substring__all_replace_empty),\
    UT_CASE(test_string_range_replace_substring__all_replace_non_empty),\
    UT_CASE_BEGIN(string_range_replace_cstr, test_string_range_replace_cstr__null_dest),\
    UT_CASE(test_string_range_replace_cstr__null_replace),\
    UT_CASE(test_string_range_replace_cstr__non_inited_dest),\
    UT_CASE(test_string_range_replace_cstr__invalid_range),\
    UT_CASE(test_string_range_replace_cstr__begin_empty_replace_empty),\
    UT_CASE(test_string_range_replace_cstr__begin_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_cstr__begin_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_cstr__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_cstr__middle_empty_replace_empty),\
    UT_CASE(test_string_range_replace_cstr__middle_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_cstr__middle_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_cstr__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_cstr__end_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_cstr__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_cstr__all_replace_empty),\
    UT_CASE(test_string_range_replace_cstr__all_replace_non_empty),\
    UT_CASE_BEGIN(string_range_replace_subcstr, test_string_range_replace_subcstr__null_dest),\
    UT_CASE(test_string_range_replace_subcstr__null_replace),\
    UT_CASE(test_string_range_replace_subcstr__non_inited_dest),\
    UT_CASE(test_string_range_replace_subcstr__invalid_range),\
    UT_CASE(test_string_range_replace_subcstr__begin_empty_replace_empty),\
    UT_CASE(test_string_range_replace_subcstr__begin_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_subcstr__begin_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_subcstr__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_subcstr__middle_empty_replace_empty),\
    UT_CASE(test_string_range_replace_subcstr__middle_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_subcstr__middle_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_subcstr__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_subcstr__end_non_empty_replace_empty),\
    UT_CASE(test_string_range_replace_subcstr__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_subcstr__all_replace_empty),\
    UT_CASE(test_string_range_replace_subcstr__all_replace_non_empty),\
    UT_CASE_BEGIN(string_range_replace_char, test_string_range_replace_char__null_container),\
    UT_CASE(test_string_range_replace_char__non_inited_container),\
    UT_CASE(test_string_range_replace_char__invalid_range),\
    UT_CASE(test_string_range_replace_char__empty_replace_empty),\
    UT_CASE(test_string_range_replace_char__empty_replace_non_empty),\
    UT_CASE(test_string_range_replace_char__begin_replace_empty),\
    UT_CASE(test_string_range_replace_char__begin_replace_less),\
    UT_CASE(test_string_range_replace_char__begin_replace_equal),\
    UT_CASE(test_string_range_replace_char__begin_replace_greater),\
    UT_CASE(test_string_range_replace_char__middle_replace_empty),\
    UT_CASE(test_string_range_replace_char__middle_replace_less),\
    UT_CASE(test_string_range_replace_char__middle_replace_equal),\
    UT_CASE(test_string_range_replace_char__middle_replace_greater),\
    UT_CASE(test_string_range_replace_char__end_replace_empty),\
    UT_CASE(test_string_range_replace_char__end_replace_less),\
    UT_CASE(test_string_range_replace_char__end_replace_equal),\
    UT_CASE(test_string_range_replace_char__end_replace_greater),\
    UT_CASE(test_string_range_replace_char__replace_all),\
    UT_CASE_BEGIN(string_replace_range, test_string_replace_range__null_dest),\
    UT_CASE(test_string_replace_range__non_inited_dest),\
    UT_CASE(test_string_replace_range__same_container),\
    UT_CASE(test_string_replace_range__invalid_range),\
    UT_CASE(test_string_replace_range__invalid_replace_range),\
    UT_CASE(test_string_replace_range__begin_empty_replace_empty),\
    UT_CASE(test_string_replace_range__begin_empty_replace_non_empty),\
    UT_CASE(test_string_replace_range__begin_non_empty_replace_empty),\
    UT_CASE(test_string_replace_range__begin_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_range__middle_empty_replace_empty),\
    UT_CASE(test_string_replace_range__middle_empty_replace_non_empty),\
    UT_CASE(test_string_replace_range__middle_non_empty_replace_empty),\
    UT_CASE(test_string_replace_range__middle_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_range__end_non_empty_replace_empty),\
    UT_CASE(test_string_replace_range__end_non_empty_replace_non_empty),\
    UT_CASE(test_string_replace_range__all_replace_empty),\
    UT_CASE(test_string_replace_range__all_replace_non_empty),\
    UT_CASE_BEGIN(string_output, test_string_output__null_string),\
    UT_CASE(test_string_output__null_stream),\
    UT_CASE(test_string_output__non_inited_string),\
    UT_CASE(test_string_output__output_empty),\
    UT_CASE(test_string_output__output_non_empty),\
    UT_CASE_BEGIN(string_input, test_string_input__null_string),\
    UT_CASE(test_string_input__null_stream),\
    UT_CASE(test_string_input__non_inited_string),\
    UT_CASE(test_string_input__input_empty),\
    UT_CASE(test_string_input__input_non_empty),\
    UT_CASE_BEGIN(string_getline, test_string_getline__null_string),\
    UT_CASE(test_string_getline__null_stream),\
    UT_CASE(test_string_getline__non_inited_string),\
    UT_CASE(test_string_getline__getline_empty),\
    UT_CASE(test_string_getline__getline_non_empty),\
    UT_CASE_BEGIN(string_getline_delimiter, test_string_getline_delimiter__null_string),\
    UT_CASE(test_string_getline_delimiter__null_stream),\
    UT_CASE(test_string_getline_delimiter__non_inited_string),\
    UT_CASE(test_string_getline_delimiter__getline_delimiter_empty),\
    UT_CASE(test_string_getline_delimiter__getline_delimiter_non_empty)

#endif /* _UT_CSTL_STRING_H_ */

