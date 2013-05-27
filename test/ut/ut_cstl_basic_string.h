#ifndef _UT_CSTL_BASIC_STRING_H_
#define _UT_CSTL_BASIC_STRING_H_

UT_SUIT_DECLARATION(cstl_basic_string)

/*
 * test basic_string_init
 */
UT_CASE_DECLARATION(basic_string_init)
void test_basic_string_init__null_basic_string_container(void** state);
void test_basic_string_init__non_created(void** state);
void test_basic_string_init__successfully_c_builtin(void** state);
void test_basic_string_init__successfully_cstl_builtin(void** state);
void test_basic_string_init__successfully_cstr(void** state);
void test_basic_string_init__successfully_user_defined(void** state);
/*
 * test basic_string_init_cstr
 */
UT_CASE_DECLARATION(basic_string_init_cstr)
void test_basic_string_init_cstr__null_container(void** state);
void test_basic_string_init_cstr__non_created_container(void** state);
void test_basic_string_init_cstr__null_valuestring(void** state);
void test_basic_string_init_cstr__c_builtin_init_empty(void** state);
void test_basic_string_init_cstr__c_builtin_init_non_empty(void** state);
void test_basic_string_init_cstr__char_init_empty(void** state);
void test_basic_string_init_cstr__char_init_non_empty(void** state);
void test_basic_string_init_cstr__cstr_init_empty(void** state);
void test_basic_string_init_cstr__cstr_init_non_empty(void** state);
void test_basic_string_init_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_init_cstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_init_cstr__user_define_empty(void** state);
void test_basic_string_init_cstr__user_define_non_empty(void** state);
/*
 * test basic_string_init_subcstr
 */
UT_CASE_DECLARATION(basic_string_init_subcstr)
void test_basic_string_init_subcstr__null_container(void** state);
void test_basic_string_init_subcstr__non_created_container(void** state);
void test_basic_string_init_subcstr__null_valuestring(void** state);
void test_basic_string_init_subcstr__length_ge_max_size(void** state);
void test_basic_string_init_subcstr__c_builtin_init_empty(void** state);
void test_basic_string_init_subcstr__c_builtin_init_non_empty(void** state);
void test_basic_string_init_subcstr__c_builtin_init_total(void** state);
void test_basic_string_init_subcstr__char_init_empty(void** state);
void test_basic_string_init_subcstr__char_init_non_empty(void** state);
void test_basic_string_init_subcstr__char_init_total(void** state);
void test_basic_string_init_subcstr__cstr_init_empty(void** state);
void test_basic_string_init_subcstr__cstr_init_non_empty(void** state);
void test_basic_string_init_subcstr__cstr_init_total(void** state);
void test_basic_string_init_subcstr__libcstl_builtin_empty(void** state);
void test_basic_string_init_subcstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_init_subcstr__libcstl_builtin_total(void** state);
void test_basic_string_init_subcstr__user_define_empty(void** state);
void test_basic_string_init_subcstr__user_define_non_empty(void** state);
void test_basic_string_init_subcstr__user_define_total(void** state);
void test_basic_string_init_subcstr__terminator_c(void** state);
void test_basic_string_init_subcstr__terminator_cstr(void** state);
void test_basic_string_init_subcstr__terminator_libcstl(void** state);
void test_basic_string_init_subcstr__terminator_user_define(void** state);
void test_basic_string_init_subcstr__memleak(void** state);
/*
 * test basic_string_init_copy
 */
UT_CASE_DECLARATION(basic_string_init_copy)
void test_basic_string_init_copy__null_dest(void** state);
void test_basic_string_init_copy__null_src(void** state);
void test_basic_string_init_copy__non_create_dest(void** state);
void test_basic_string_init_copy__non_inited_src(void** state);
void test_basic_string_init_copy__not_same_type(void** state);
void test_basic_string_init_copy__successfully_c_builtin_empty(void** state);
void test_basic_string_init_copy__successfully_c_builtin_little(void** state);
void test_basic_string_init_copy__successfully_c_builtin_huge(void** state);
void test_basic_string_init_copy__successfully_cstr_empty(void** state);
void test_basic_string_init_copy__successfully_cstr_little(void** state);
void test_basic_string_init_copy__successfully_cstr_huge(void** state);
void test_basic_string_init_copy__successfully_cstl_builtin_empty(void** state);
void test_basic_string_init_copy__successfully_cstl_builtin_little(void** state);
void test_basic_string_init_copy__successfully_cstl_builtin_huge(void** state);
void test_basic_string_init_copy__successfully_user_define_empty(void** state);
void test_basic_string_init_copy__successfully_user_define_little(void** state);
void test_basic_string_init_copy__successfully_user_define_huge(void** state);
void test_basic_string_init_copy__multi_shared(void** state);
/*
 * test basic_string_init_copy_substring
 */
UT_CASE_DECLARATION(basic_string_init_copy_substring)
void test_basic_string_init_copy_substring__null_dest(void** state);
void test_basic_string_init_copy_substring__null_src(void** state);
void test_basic_string_init_copy_substring__non_create_dest(void** state);
void test_basic_string_init_copy_substring__non_inited_src(void** state);
void test_basic_string_init_copy_substring__not_same_type(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_end(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_end(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_end(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_npos(void** state);
void test_basic_string_init_copy_substring__check(void** state);
void test_basic_string_init_copy_substring__terminator_c(void** state);
void test_basic_string_init_copy_substring__terminator_cstr(void** state);
void test_basic_string_init_copy_substring__terminator_libcstl(void** state);
void test_basic_string_init_copy_substring__terminator_user_define(void** state);
/*
 * test basic_string_init_copy_range
 */
UT_CASE_DECLARATION(basic_string_init_copy_range)
void test_basic_string_init_copy_range__null_dest(void** state);
void test_basic_string_init_copy_range__invalid_begin_iterator(void** state);
void test_basic_string_init_copy_range__invalid_end_iterator(void** state);
void test_basic_string_init_copy_range__invalid_range(void** state);
void test_basic_string_init_copy_range__not_same_type(void** state);
void test_basic_string_init_copy_range__successfully_empty_range(void** state);
void test_basic_string_init_copy_range__successfully_c_builtin(void** state);
void test_basic_string_init_copy_range__successfully_cstr(void** state);
void test_basic_string_init_copy_range__successfully_cstl_builtin(void** state);
void test_basic_string_init_copy_range__successfully_user_define(void** state);
void test_basic_string_init_copy_range__terminator_c(void** state);
void test_basic_string_init_copy_range__terminator_cstr(void** state);
void test_basic_string_init_copy_range__terminator_libcstl(void** state);
void test_basic_string_init_copy_range__terminator_user_define(void** state);
/*
 * test basic_string_destroy
 */
UT_CASE_DECLARATION(basic_string_destroy)
void test_basic_string_destroy__null_basic_string_container(void** state);
void test_basic_string_destroy__non_created(void** state);
void test_basic_string_destroy__created_non_inited(void** state);
void test_basic_string_destroy__inited_empty(void** state);
void test_basic_string_destroy__inited_non_empty(void** state);
void test_basic_string_destroy__shared(void** state);
/*
 * test basic_string_c_str
 */
UT_CASE_DECLARATION(basic_string_c_str)
void test_basic_string_c_str__null_container(void** state);
void test_basic_string_c_str__non_inited_container(void** state);
void test_basic_string_c_str__empty(void** state);
void test_basic_string_c_str__non_empty(void** state);
/*
 * test basic_string_data
 */
UT_CASE_DECLARATION(basic_string_data)
void test_basic_string_data__null_container(void** state);
void test_basic_string_data__non_inited_container(void** state);
void test_basic_string_data__empty(void** state);
void test_basic_string_data__non_empty(void** state);
void test_basic_string_data__shared(void** state);
/*
 * test basic_string_copy
 */
UT_CASE_DECLARATION(basic_string_copy)
void test_basic_string_copy__null_container(void** state);
void test_basic_string_copy__non_inited_container(void** state);
void test_basic_string_copy__null_buffer(void** state);
void test_basic_string_copy__invalid_position(void** state);
void test_basic_string_copy__begin_empty(void** state);
void test_basic_string_copy__begin_non_empty(void** state);
void test_basic_string_copy__begin_length(void** state);
void test_basic_string_copy__begin_npos(void** state);
void test_basic_string_copy__middle_empty(void** state);
void test_basic_string_copy__middle_non_empty(void** state);
void test_basic_string_copy__middle_length(void** state);
void test_basic_string_copy__middle_npos(void** state);
void test_basic_string_copy__end(void** state);
void test_basic_string_copy__npos(void** state);
void test_basic_string_copy__shared(void** state);
void test_basic_string_copy__terminator_c(void** state);
void test_basic_string_copy__terminator_cstr(void** state);
void test_basic_string_copy__terminator_cstl(void** state);
void test_basic_string_copy__terminator_cstl_2(void** state);
void test_basic_string_copy__terminator_user_define(void** state);
/*
 * test basic_string_size
 */
UT_CASE_DECLARATION(basic_string_size)
void test_basic_string_size__null_basic_string_container(void** state);
void test_basic_string_size__non_inited(void** state);
void test_basic_string_size__successfully_empty(void** state);
void test_basic_string_size__successfully_non_empty(void** state);
/*
 * test basic_string_length
 */
UT_CASE_DECLARATION(basic_string_length)
void test_basic_string_length__null_basic_string_container(void** state);
void test_basic_string_length__non_inited(void** state);
void test_basic_string_length__successfully_empty(void** state);
void test_basic_string_length__successfully_non_empty(void** state);
/*
 * test basic_string_empty
 */
UT_CASE_DECLARATION(basic_string_empty)
void test_basic_string_empty__null_basic_string_container(void** state);
void test_basic_string_empty__non_inited(void** state);
void test_basic_string_empty__successfully_empty(void** state);
void test_basic_string_empty__successfully_non_empty(void** state);
/*
 * test basic_string_max_size
 */
UT_CASE_DECLARATION(basic_string_max_size)
void test_basic_string_max_size__null_basic_string_container(void** state);
void test_basic_string_max_size__non_created(void** state);
void test_basic_string_max_size__successfully(void** state);
/*
 * test basic_string_capacity
 */
UT_CASE_DECLARATION(basic_string_capacity)
void test_basic_string_capacity__null_basic_string_container(void** state);
void test_basic_string_capacity__non_inited(void** state);
void test_basic_string_capacity__successfully_empty(void** state);
void test_basic_string_capacity__successfully_little(void** state);
void test_basic_string_capacity__successfully_huge(void** state);
/*
 * test basic_string_at
 */
UT_CASE_DECLARATION(basic_string_at)
void test_basic_string_at__null_basic_string_container(void** state);
void test_basic_string_at__non_inited_basic_string_container(void** state);
void test_basic_string_at__invalid_subscript_empty(void** state);
void test_basic_string_at__invalid_subscript_end(void** state);
void test_basic_string_at__invalid_subscript(void** state);
void test_basic_string_at__c_builtin(void** state);
void test_basic_string_at__cstl(void** state);
void test_basic_string_at__user_define(void** state);
void test_basic_string_at__successfully(void** state);
void test_basic_string_at__successfully_cstr(void** state);
void test_basic_string_at__sharable(void** state);
/*
 * test basic_string_equal
 */
UT_CASE_DECLARATION(basic_string_equal)
void test_basic_string_equal__null_first(void** state);
void test_basic_string_equal__null_second(void** state);
void test_basic_string_equal__non_inited_first(void** state);
void test_basic_string_equal__non_inited_second(void** state);
void test_basic_string_equal__not_same_type(void** state);
void test_basic_string_equal__same_basic_string(void** state);
void test_basic_string_equal__size_first_less_than_second(void** state);
void test_basic_string_equal__size_first_greater_than_second(void** state);
void test_basic_string_equal__size_equal_0(void** state);
void test_basic_string_equal__size_equal_elem_first_less_than_second(void** state);
void test_basic_string_equal__size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_equal__size_equal_elem_equal(void** state);
void test_basic_string_equal__shared(void** state);
/*
 * test basic_string_not_equal
 */
UT_CASE_DECLARATION(basic_string_not_equal)
void test_basic_string_not_equal__null_first(void** state);
void test_basic_string_not_equal__null_second(void** state);
void test_basic_string_not_equal__non_inited_first(void** state);
void test_basic_string_not_equal__non_inited_second(void** state);
void test_basic_string_not_equal__not_same_type(void** state);
void test_basic_string_not_equal__same_basic_string(void** state);
void test_basic_string_not_equal__size_first_less_than_second(void** state);
void test_basic_string_not_equal__size_first_greater_than_second(void** state);
void test_basic_string_not_equal__size_equal_0(void** state);
void test_basic_string_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_basic_string_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_not_equal__size_equal_elem_equal(void** state);
void test_basic_string_not_equal__shared(void** state);
/*
 * test basic_string_less
 */
UT_CASE_DECLARATION(basic_string_less)
void test_basic_string_less__null_first(void** state);
void test_basic_string_less__null_second(void** state);
void test_basic_string_less__non_inited_first(void** state);
void test_basic_string_less__non_inited_second(void** state);
void test_basic_string_less__not_same_type(void** state);
void test_basic_string_less__same_basic_string(void** state);
void test_basic_string_less__size_first_less_than_second(void** state);
void test_basic_string_less__size_first_greater_than_second(void** state);
void test_basic_string_less__size_equal_0(void** state);
void test_basic_string_less__size_equal_elem_first_less_than_second(void** state);
void test_basic_string_less__size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_less__size_equal_elem_equal(void** state);
void test_basic_string_less__shared(void** state);
/*
 * test basic_string_less_equal
 */
UT_CASE_DECLARATION(basic_string_less_equal)
void test_basic_string_less_equal__null_first(void** state);
void test_basic_string_less_equal__null_second(void** state);
void test_basic_string_less_equal__non_inited_first(void** state);
void test_basic_string_less_equal__non_inited_second(void** state);
void test_basic_string_less_equal__not_same_type(void** state);
void test_basic_string_less_equal__same_basic_string(void** state);
void test_basic_string_less_equal__size_first_less_than_second(void** state);
void test_basic_string_less_equal__size_first_greater_than_second(void** state);
void test_basic_string_less_equal__size_equal_0(void** state);
void test_basic_string_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_basic_string_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_less_equal__size_equal_elem_equal(void** state);
void test_basic_string_less_equal__shared(void** state);
/*
 * test basic_string_greater
 */
UT_CASE_DECLARATION(basic_string_greater)
void test_basic_string_greater__null_first(void** state);
void test_basic_string_greater__null_second(void** state);
void test_basic_string_greater__non_inited_first(void** state);
void test_basic_string_greater__non_inited_second(void** state);
void test_basic_string_greater__not_same_type(void** state);
void test_basic_string_greater__same_basic_string(void** state);
void test_basic_string_greater__size_first_less_than_second(void** state);
void test_basic_string_greater__size_first_greater_than_second(void** state);
void test_basic_string_greater__size_equal_0(void** state);
void test_basic_string_greater__size_equal_elem_first_less_than_second(void** state);
void test_basic_string_greater__size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_greater__size_equal_elem_equal(void** state);
void test_basic_string_greater__shared(void** state);
/*
 * test basic_string_greater_equal
 */
UT_CASE_DECLARATION(basic_string_greater_equal)
void test_basic_string_greater_equal__null_first(void** state);
void test_basic_string_greater_equal__null_second(void** state);
void test_basic_string_greater_equal__non_inited_first(void** state);
void test_basic_string_greater_equal__non_inited_second(void** state);
void test_basic_string_greater_equal__not_same_type(void** state);
void test_basic_string_greater_equal__same_basic_string(void** state);
void test_basic_string_greater_equal__size_first_less_than_second(void** state);
void test_basic_string_greater_equal__size_first_greater_than_second(void** state);
void test_basic_string_greater_equal__size_equal_0(void** state);
void test_basic_string_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_basic_string_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_greater_equal__size_equal_elem_equal(void** state);
void test_basic_string_greater_equal__shared(void** state);
/*
 * test basic_string_equal_cstr
 */
UT_CASE_DECLARATION(basic_string_equal_cstr)
void test_basic_string_equal_cstr__null_basic_string(void** state);
void test_basic_string_equal_cstr__null_value_string(void** state);
void test_basic_string_equal_cstr__non_inited_basic_string(void** state);
void test_basic_string_equal_cstr__c_builtin_empty(void** state);
void test_basic_string_equal_cstr__c_builtin_less(void** state);
void test_basic_string_equal_cstr__c_builtin_equal(void** state);
void test_basic_string_equal_cstr__c_builtin_greater(void** state);
void test_basic_string_equal_cstr__c_builtin_size_equal_less(void** state);
void test_basic_string_equal_cstr__c_builtin_size_equal_greater(void** state);
void test_basic_string_equal_cstr__char_empty(void** state);
void test_basic_string_equal_cstr__char_less(void** state);
void test_basic_string_equal_cstr__char_equal(void** state);
void test_basic_string_equal_cstr__char_greater(void** state);
void test_basic_string_equal_cstr__char_size_equal_less(void** state);
void test_basic_string_equal_cstr__char_size_equal_greater(void** state);
void test_basic_string_equal_cstr__cstr_empty(void** state);
void test_basic_string_equal_cstr__cstr_less(void** state);
void test_basic_string_equal_cstr__cstr_equal(void** state);
void test_basic_string_equal_cstr__cstr_greater(void** state);
void test_basic_string_equal_cstr__cstr_size_equal_less(void** state);
void test_basic_string_equal_cstr__cstr_size_equal_greater(void** state);
void test_basic_string_equal_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_equal_cstr__libcstl_builtin_less(void** state);
void test_basic_string_equal_cstr__libcstl_builtin_equal(void** state);
void test_basic_string_equal_cstr__libcstl_builtin_greater(void** state);
void test_basic_string_equal_cstr__libcstl_builtin_size_equal_less(void** state);
void test_basic_string_equal_cstr__libcstl_builtin_size_equal_greater(void** state);
void test_basic_string_equal_cstr__user_defined_empty(void** state);
void test_basic_string_equal_cstr__user_defined_less(void** state);
void test_basic_string_equal_cstr__user_defined_equal(void** state);
void test_basic_string_equal_cstr__user_defined_greater(void** state);
void test_basic_string_equal_cstr__user_defined_size_equal_less(void** state);
void test_basic_string_equal_cstr__user_defined_size_equal_greater(void** state);
/*
 * test basic_string_not_equal_cstr
 */
UT_CASE_DECLARATION(basic_string_not_equal_cstr)
void test_basic_string_not_equal_cstr__null_basic_string(void** state);
void test_basic_string_not_equal_cstr__null_value_string(void** state);
void test_basic_string_not_equal_cstr__non_inited_basic_string(void** state);
void test_basic_string_not_equal_cstr__c_builtin_empty(void** state);
void test_basic_string_not_equal_cstr__c_builtin_less(void** state);
void test_basic_string_not_equal_cstr__c_builtin_equal(void** state);
void test_basic_string_not_equal_cstr__c_builtin_greater(void** state);
void test_basic_string_not_equal_cstr__c_builtin_size_equal_less(void** state);
void test_basic_string_not_equal_cstr__c_builtin_size_equal_greater(void** state);
void test_basic_string_not_equal_cstr__char_empty(void** state);
void test_basic_string_not_equal_cstr__char_less(void** state);
void test_basic_string_not_equal_cstr__char_equal(void** state);
void test_basic_string_not_equal_cstr__char_greater(void** state);
void test_basic_string_not_equal_cstr__char_size_equal_less(void** state);
void test_basic_string_not_equal_cstr__char_size_equal_greater(void** state);
void test_basic_string_not_equal_cstr__cstr_empty(void** state);
void test_basic_string_not_equal_cstr__cstr_less(void** state);
void test_basic_string_not_equal_cstr__cstr_equal(void** state);
void test_basic_string_not_equal_cstr__cstr_greater(void** state);
void test_basic_string_not_equal_cstr__cstr_size_equal_less(void** state);
void test_basic_string_not_equal_cstr__cstr_size_equal_greater(void** state);
void test_basic_string_not_equal_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_not_equal_cstr__libcstl_builtin_less(void** state);
void test_basic_string_not_equal_cstr__libcstl_builtin_equal(void** state);
void test_basic_string_not_equal_cstr__libcstl_builtin_greater(void** state);
void test_basic_string_not_equal_cstr__libcstl_builtin_size_equal_less(void** state);
void test_basic_string_not_equal_cstr__libcstl_builtin_size_equal_greater(void** state);
void test_basic_string_not_equal_cstr__user_defined_empty(void** state);
void test_basic_string_not_equal_cstr__user_defined_less(void** state);
void test_basic_string_not_equal_cstr__user_defined_equal(void** state);
void test_basic_string_not_equal_cstr__user_defined_greater(void** state);
void test_basic_string_not_equal_cstr__user_defined_size_equal_less(void** state);
void test_basic_string_not_equal_cstr__user_defined_size_equal_greater(void** state);
/*
 * test basic_string_less_cstr
 */
UT_CASE_DECLARATION(basic_string_less_cstr)
void test_basic_string_less_cstr__null_basic_string(void** state);
void test_basic_string_less_cstr__null_value_string(void** state);
void test_basic_string_less_cstr__non_inited_basic_string(void** state);
void test_basic_string_less_cstr__c_builtin_empty(void** state);
void test_basic_string_less_cstr__c_builtin_less(void** state);
void test_basic_string_less_cstr__c_builtin_equal(void** state);
void test_basic_string_less_cstr__c_builtin_greater(void** state);
void test_basic_string_less_cstr__c_builtin_size_equal_less(void** state);
void test_basic_string_less_cstr__c_builtin_size_equal_greater(void** state);
void test_basic_string_less_cstr__char_empty(void** state);
void test_basic_string_less_cstr__char_less(void** state);
void test_basic_string_less_cstr__char_equal(void** state);
void test_basic_string_less_cstr__char_greater(void** state);
void test_basic_string_less_cstr__char_size_equal_less(void** state);
void test_basic_string_less_cstr__char_size_equal_greater(void** state);
void test_basic_string_less_cstr__cstr_empty(void** state);
void test_basic_string_less_cstr__cstr_less(void** state);
void test_basic_string_less_cstr__cstr_equal(void** state);
void test_basic_string_less_cstr__cstr_greater(void** state);
void test_basic_string_less_cstr__cstr_size_equal_less(void** state);
void test_basic_string_less_cstr__cstr_size_equal_greater(void** state);
void test_basic_string_less_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_less_cstr__libcstl_builtin_less(void** state);
void test_basic_string_less_cstr__libcstl_builtin_equal(void** state);
void test_basic_string_less_cstr__libcstl_builtin_greater(void** state);
void test_basic_string_less_cstr__libcstl_builtin_size_equal_less(void** state);
void test_basic_string_less_cstr__libcstl_builtin_size_equal_greater(void** state);
void test_basic_string_less_cstr__user_defined_empty(void** state);
void test_basic_string_less_cstr__user_defined_less(void** state);
void test_basic_string_less_cstr__user_defined_equal(void** state);
void test_basic_string_less_cstr__user_defined_greater(void** state);
void test_basic_string_less_cstr__user_defined_size_equal_less(void** state);
void test_basic_string_less_cstr__user_defined_size_equal_greater(void** state);
/*
 * test basic_string_less_equal_cstr
 */
UT_CASE_DECLARATION(basic_string_less_equal_cstr)
void test_basic_string_less_equal_cstr__null_basic_string(void** state);
void test_basic_string_less_equal_cstr__null_value_string(void** state);
void test_basic_string_less_equal_cstr__non_inited_basic_string(void** state);
void test_basic_string_less_equal_cstr__c_builtin_empty(void** state);
void test_basic_string_less_equal_cstr__c_builtin_less(void** state);
void test_basic_string_less_equal_cstr__c_builtin_equal(void** state);
void test_basic_string_less_equal_cstr__c_builtin_greater(void** state);
void test_basic_string_less_equal_cstr__c_builtin_size_equal_less(void** state);
void test_basic_string_less_equal_cstr__c_builtin_size_equal_greater(void** state);
void test_basic_string_less_equal_cstr__char_empty(void** state);
void test_basic_string_less_equal_cstr__char_less(void** state);
void test_basic_string_less_equal_cstr__char_equal(void** state);
void test_basic_string_less_equal_cstr__char_greater(void** state);
void test_basic_string_less_equal_cstr__char_size_equal_less(void** state);
void test_basic_string_less_equal_cstr__char_size_equal_greater(void** state);
void test_basic_string_less_equal_cstr__cstr_empty(void** state);
void test_basic_string_less_equal_cstr__cstr_less(void** state);
void test_basic_string_less_equal_cstr__cstr_equal(void** state);
void test_basic_string_less_equal_cstr__cstr_greater(void** state);
void test_basic_string_less_equal_cstr__cstr_size_equal_less(void** state);
void test_basic_string_less_equal_cstr__cstr_size_equal_greater(void** state);
void test_basic_string_less_equal_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_less_equal_cstr__libcstl_builtin_less(void** state);
void test_basic_string_less_equal_cstr__libcstl_builtin_equal(void** state);
void test_basic_string_less_equal_cstr__libcstl_builtin_greater(void** state);
void test_basic_string_less_equal_cstr__libcstl_builtin_size_equal_less(void** state);
void test_basic_string_less_equal_cstr__libcstl_builtin_size_equal_greater(void** state);
void test_basic_string_less_equal_cstr__user_defined_empty(void** state);
void test_basic_string_less_equal_cstr__user_defined_less(void** state);
void test_basic_string_less_equal_cstr__user_defined_equal(void** state);
void test_basic_string_less_equal_cstr__user_defined_greater(void** state);
void test_basic_string_less_equal_cstr__user_defined_size_equal_less(void** state);
void test_basic_string_less_equal_cstr__user_defined_size_equal_greater(void** state);
/*
 * test basic_string_greater_cstr
 */
UT_CASE_DECLARATION(basic_string_greater_cstr)
void test_basic_string_greater_cstr__null_basic_string(void** state);
void test_basic_string_greater_cstr__null_value_string(void** state);
void test_basic_string_greater_cstr__non_inited_basic_string(void** state);
void test_basic_string_greater_cstr__c_builtin_empty(void** state);
void test_basic_string_greater_cstr__c_builtin_less(void** state);
void test_basic_string_greater_cstr__c_builtin_equal(void** state);
void test_basic_string_greater_cstr__c_builtin_greater(void** state);
void test_basic_string_greater_cstr__c_builtin_size_equal_less(void** state);
void test_basic_string_greater_cstr__c_builtin_size_equal_greater(void** state);
void test_basic_string_greater_cstr__char_empty(void** state);
void test_basic_string_greater_cstr__char_less(void** state);
void test_basic_string_greater_cstr__char_equal(void** state);
void test_basic_string_greater_cstr__char_greater(void** state);
void test_basic_string_greater_cstr__char_size_equal_less(void** state);
void test_basic_string_greater_cstr__char_size_equal_greater(void** state);
void test_basic_string_greater_cstr__cstr_empty(void** state);
void test_basic_string_greater_cstr__cstr_less(void** state);
void test_basic_string_greater_cstr__cstr_equal(void** state);
void test_basic_string_greater_cstr__cstr_greater(void** state);
void test_basic_string_greater_cstr__cstr_size_equal_less(void** state);
void test_basic_string_greater_cstr__cstr_size_equal_greater(void** state);
void test_basic_string_greater_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_greater_cstr__libcstl_builtin_less(void** state);
void test_basic_string_greater_cstr__libcstl_builtin_equal(void** state);
void test_basic_string_greater_cstr__libcstl_builtin_greater(void** state);
void test_basic_string_greater_cstr__libcstl_builtin_size_equal_less(void** state);
void test_basic_string_greater_cstr__libcstl_builtin_size_equal_greater(void** state);
void test_basic_string_greater_cstr__user_defined_empty(void** state);
void test_basic_string_greater_cstr__user_defined_less(void** state);
void test_basic_string_greater_cstr__user_defined_equal(void** state);
void test_basic_string_greater_cstr__user_defined_greater(void** state);
void test_basic_string_greater_cstr__user_defined_size_equal_less(void** state);
void test_basic_string_greater_cstr__user_defined_size_equal_greater(void** state);
/*
 * test basic_string_greater_equal_cstr
 */
UT_CASE_DECLARATION(basic_string_greater_equal_cstr)
void test_basic_string_greater_equal_cstr__null_basic_string(void** state);
void test_basic_string_greater_equal_cstr__null_value_string(void** state);
void test_basic_string_greater_equal_cstr__non_inited_basic_string(void** state);
void test_basic_string_greater_equal_cstr__c_builtin_empty(void** state);
void test_basic_string_greater_equal_cstr__c_builtin_less(void** state);
void test_basic_string_greater_equal_cstr__c_builtin_equal(void** state);
void test_basic_string_greater_equal_cstr__c_builtin_greater(void** state);
void test_basic_string_greater_equal_cstr__c_builtin_size_equal_less(void** state);
void test_basic_string_greater_equal_cstr__c_builtin_size_equal_greater(void** state);
void test_basic_string_greater_equal_cstr__char_empty(void** state);
void test_basic_string_greater_equal_cstr__char_less(void** state);
void test_basic_string_greater_equal_cstr__char_equal(void** state);
void test_basic_string_greater_equal_cstr__char_greater(void** state);
void test_basic_string_greater_equal_cstr__char_size_equal_less(void** state);
void test_basic_string_greater_equal_cstr__char_size_equal_greater(void** state);
void test_basic_string_greater_equal_cstr__cstr_empty(void** state);
void test_basic_string_greater_equal_cstr__cstr_less(void** state);
void test_basic_string_greater_equal_cstr__cstr_equal(void** state);
void test_basic_string_greater_equal_cstr__cstr_greater(void** state);
void test_basic_string_greater_equal_cstr__cstr_size_equal_less(void** state);
void test_basic_string_greater_equal_cstr__cstr_size_equal_greater(void** state);
void test_basic_string_greater_equal_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_greater_equal_cstr__libcstl_builtin_less(void** state);
void test_basic_string_greater_equal_cstr__libcstl_builtin_equal(void** state);
void test_basic_string_greater_equal_cstr__libcstl_builtin_greater(void** state);
void test_basic_string_greater_equal_cstr__libcstl_builtin_size_equal_less(void** state);
void test_basic_string_greater_equal_cstr__libcstl_builtin_size_equal_greater(void** state);
void test_basic_string_greater_equal_cstr__user_defined_empty(void** state);
void test_basic_string_greater_equal_cstr__user_defined_less(void** state);
void test_basic_string_greater_equal_cstr__user_defined_equal(void** state);
void test_basic_string_greater_equal_cstr__user_defined_greater(void** state);
void test_basic_string_greater_equal_cstr__user_defined_size_equal_less(void** state);
void test_basic_string_greater_equal_cstr__user_defined_size_equal_greater(void** state);
/*
 * test basic_string_compare
 */
UT_CASE_DECLARATION(basic_string_compare)
void test_basic_string_compare__null_first(void** state);
void test_basic_string_compare__null_second(void** state);
void test_basic_string_compare__non_inited_first(void** state);
void test_basic_string_compare__non_inited_second(void** state);
void test_basic_string_compare__not_same_type(void** state);
void test_basic_string_compare__same_basic_string(void** state);
void test_basic_string_compare__c_builtin_size_first_less_than_second(void** state);
void test_basic_string_compare__c_builtin_size_first_greater_than_second(void** state);
void test_basic_string_compare__c_builtin_size_equal_0(void** state);
void test_basic_string_compare__c_builtin_size_equal_elem_first_less_than_second(void** state);
void test_basic_string_compare__c_builtin_size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_compare__c_builtin_size_equal_elem_equal(void** state);
void test_basic_string_compare__char_size_first_less_than_second(void** state);
void test_basic_string_compare__char_size_first_greater_than_second(void** state);
void test_basic_string_compare__char_size_equal_0(void** state);
void test_basic_string_compare__char_size_equal_elem_first_less_than_second(void** state);
void test_basic_string_compare__char_size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_compare__char_size_equal_elem_equal(void** state);
void test_basic_string_compare__cstr_size_first_less_than_second(void** state);
void test_basic_string_compare__cstr_size_first_greater_than_second(void** state);
void test_basic_string_compare__cstr_size_equal_0(void** state);
void test_basic_string_compare__cstr_size_equal_elem_first_less_than_second(void** state);
void test_basic_string_compare__cstr_size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_compare__cstr_size_equal_elem_equal(void** state);
void test_basic_string_compare__libcstl_builtin_size_first_less_than_second(void** state);
void test_basic_string_compare__libcstl_builtin_size_first_greater_than_second(void** state);
void test_basic_string_compare__libcstl_builtin_size_equal_0(void** state);
void test_basic_string_compare__libcstl_builtin_size_equal_elem_first_less_than_second(void** state);
void test_basic_string_compare__libcstl_builtin_size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_compare__libcstl_builtin_size_equal_elem_equal(void** state);
void test_basic_string_compare__user_define_size_first_less_than_second(void** state);
void test_basic_string_compare__user_define_size_first_greater_than_second(void** state);
void test_basic_string_compare__user_define_size_equal_0(void** state);
void test_basic_string_compare__user_define_size_equal_elem_first_less_than_second(void** state);
void test_basic_string_compare__user_define_size_equal_elem_first_greater_than_second(void** state);
void test_basic_string_compare__user_define_size_equal_elem_equal(void** state);
void test_basic_string_compare__shared(void** state);
/*
 * test basic_string_compare_substring_string
 */
UT_CASE_DECLARATION(basic_string_compare_substring_string)
void test_basic_string_compare_substring_string__null_first(void** state);
void test_basic_string_compare_substring_string__null_second(void** state);
void test_basic_string_compare_substring_string__non_inited_first(void** state);
void test_basic_string_compare_substring_string__non_inited_second(void** state);
void test_basic_string_compare_substring_string__invalid_pos(void** state);
void test_basic_string_compare_substring_string__not_same_type(void** state);
void test_basic_string_compare_substring_string__c_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_string__c_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_string__c_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_string__c_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_string__c_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_string__c_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_string__c_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_string__c_builtin_all_equal(void** state);
void test_basic_string_compare_substring_string__c_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_string__c_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_string__c_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_string__c_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_string__c_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_string__char_sub_size_less(void** state);
void test_basic_string_compare_substring_string__char_sub_content_less(void** state);
void test_basic_string_compare_substring_string__char_sub_equal(void** state);
void test_basic_string_compare_substring_string__char_sub_size_greater(void** state);
void test_basic_string_compare_substring_string__char_sub_content_greater(void** state);
void test_basic_string_compare_substring_string__char_all_size_less(void** state);
void test_basic_string_compare_substring_string__char_all_content_less(void** state);
void test_basic_string_compare_substring_string__char_all_equal(void** state);
void test_basic_string_compare_substring_string__char_all_size_greater(void** state);
void test_basic_string_compare_substring_string__char_all_content_greater(void** state);
void test_basic_string_compare_substring_string__char_empty_non_empty(void** state);
void test_basic_string_compare_substring_string__char_non_empty_empty(void** state);
void test_basic_string_compare_substring_string__char_empty_empty(void** state);
void test_basic_string_compare_substring_string__cstr_sub_size_less(void** state);
void test_basic_string_compare_substring_string__cstr_sub_content_less(void** state);
void test_basic_string_compare_substring_string__cstr_sub_equal(void** state);
void test_basic_string_compare_substring_string__cstr_sub_size_greater(void** state);
void test_basic_string_compare_substring_string__cstr_sub_content_greater(void** state);
void test_basic_string_compare_substring_string__cstr_all_size_less(void** state);
void test_basic_string_compare_substring_string__cstr_all_content_less(void** state);
void test_basic_string_compare_substring_string__cstr_all_equal(void** state);
void test_basic_string_compare_substring_string__cstr_all_size_greater(void** state);
void test_basic_string_compare_substring_string__cstr_all_content_greater(void** state);
void test_basic_string_compare_substring_string__cstr_empty_non_empty(void** state);
void test_basic_string_compare_substring_string__cstr_non_empty_empty(void** state);
void test_basic_string_compare_substring_string__cstr_empty_empty(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_all_equal(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_string__libcstl_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_string__user_define_sub_size_less(void** state);
void test_basic_string_compare_substring_string__user_define_sub_content_less(void** state);
void test_basic_string_compare_substring_string__user_define_sub_equal(void** state);
void test_basic_string_compare_substring_string__user_define_sub_size_greater(void** state);
void test_basic_string_compare_substring_string__user_define_sub_content_greater(void** state);
void test_basic_string_compare_substring_string__user_define_all_size_less(void** state);
void test_basic_string_compare_substring_string__user_define_all_content_less(void** state);
void test_basic_string_compare_substring_string__user_define_all_equal(void** state);
void test_basic_string_compare_substring_string__user_define_all_size_greater(void** state);
void test_basic_string_compare_substring_string__user_define_all_content_greater(void** state);
void test_basic_string_compare_substring_string__user_define_empty_non_empty(void** state);
void test_basic_string_compare_substring_string__user_define_non_empty_empty(void** state);
void test_basic_string_compare_substring_string__user_define_empty_empty(void** state);
void test_basic_string_compare_substring_string__shared(void** state);
/*
 * test basic_string_compare_substring_substring
 */
UT_CASE_DECLARATION(basic_string_compare_substring_substring)
void test_basic_string_compare_substring_substring__null_first(void** state);
void test_basic_string_compare_substring_substring__null_second(void** state);
void test_basic_string_compare_substring_substring__non_inited_first(void** state);
void test_basic_string_compare_substring_substring__non_inited_second(void** state);
void test_basic_string_compare_substring_substring__invalid_first_pos(void** state);
void test_basic_string_compare_substring_substring__invalid_second_pos(void** state);
void test_basic_string_compare_substring_substring__not_same_type(void** state);
void test_basic_string_compare_substring_substring__c_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_substring__c_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_substring__c_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_substring__c_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_substring__c_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_substring__c_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_substring__c_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_substring__c_builtin_all_equal(void** state);
void test_basic_string_compare_substring_substring__c_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_substring__c_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_substring__c_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_substring__c_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_substring__c_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_substring__char_sub_size_less(void** state);
void test_basic_string_compare_substring_substring__char_sub_content_less(void** state);
void test_basic_string_compare_substring_substring__char_sub_equal(void** state);
void test_basic_string_compare_substring_substring__char_sub_size_greater(void** state);
void test_basic_string_compare_substring_substring__char_sub_content_greater(void** state);
void test_basic_string_compare_substring_substring__char_all_size_less(void** state);
void test_basic_string_compare_substring_substring__char_all_content_less(void** state);
void test_basic_string_compare_substring_substring__char_all_equal(void** state);
void test_basic_string_compare_substring_substring__char_all_size_greater(void** state);
void test_basic_string_compare_substring_substring__char_all_content_greater(void** state);
void test_basic_string_compare_substring_substring__char_empty_non_empty(void** state);
void test_basic_string_compare_substring_substring__char_non_empty_empty(void** state);
void test_basic_string_compare_substring_substring__char_empty_empty(void** state);
void test_basic_string_compare_substring_substring__cstr_sub_size_less(void** state);
void test_basic_string_compare_substring_substring__cstr_sub_content_less(void** state);
void test_basic_string_compare_substring_substring__cstr_sub_equal(void** state);
void test_basic_string_compare_substring_substring__cstr_sub_size_greater(void** state);
void test_basic_string_compare_substring_substring__cstr_sub_content_greater(void** state);
void test_basic_string_compare_substring_substring__cstr_all_size_less(void** state);
void test_basic_string_compare_substring_substring__cstr_all_content_less(void** state);
void test_basic_string_compare_substring_substring__cstr_all_equal(void** state);
void test_basic_string_compare_substring_substring__cstr_all_size_greater(void** state);
void test_basic_string_compare_substring_substring__cstr_all_content_greater(void** state);
void test_basic_string_compare_substring_substring__cstr_empty_non_empty(void** state);
void test_basic_string_compare_substring_substring__cstr_non_empty_empty(void** state);
void test_basic_string_compare_substring_substring__cstr_empty_empty(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_all_equal(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_substring__libcstl_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_substring__user_define_sub_size_less(void** state);
void test_basic_string_compare_substring_substring__user_define_sub_content_less(void** state);
void test_basic_string_compare_substring_substring__user_define_sub_equal(void** state);
void test_basic_string_compare_substring_substring__user_define_sub_size_greater(void** state);
void test_basic_string_compare_substring_substring__user_define_sub_content_greater(void** state);
void test_basic_string_compare_substring_substring__user_define_all_size_less(void** state);
void test_basic_string_compare_substring_substring__user_define_all_content_less(void** state);
void test_basic_string_compare_substring_substring__user_define_all_equal(void** state);
void test_basic_string_compare_substring_substring__user_define_all_size_greater(void** state);
void test_basic_string_compare_substring_substring__user_define_all_content_greater(void** state);
void test_basic_string_compare_substring_substring__user_define_empty_non_empty(void** state);
void test_basic_string_compare_substring_substring__user_define_non_empty_empty(void** state);
void test_basic_string_compare_substring_substring__user_define_empty_empty(void** state);
void test_basic_string_compare_substring_substring__shared(void** state);
void test_basic_string_compare_substring_substring__size1(void** state);
void test_basic_string_compare_substring_substring__size2(void** state);
void test_basic_string_compare_substring_substring__size(void** state);
void test_basic_string_compare_substring_substring__terminator_c(void** state);
void test_basic_string_compare_substring_substring__terminator_cstr(void** state);
void test_basic_string_compare_substring_substring__terminator_cstl(void** state);
void test_basic_string_compare_substring_substring__terminator_user_define(void** state);
/*
 * test basic_string_compare_cstr
 */
UT_CASE_DECLARATION(basic_string_compare_cstr)
void test_basic_string_compare_cstr__null_basic_string(void** state);
void test_basic_string_compare_cstr__null_value_string(void** state);
void test_basic_string_compare_cstr__non_inited_basic_string(void** state);
void test_basic_string_compare_cstr__c_builtin_empty(void** state);
void test_basic_string_compare_cstr__c_builtin_less(void** state);
void test_basic_string_compare_cstr__c_builtin_equal(void** state);
void test_basic_string_compare_cstr__c_builtin_greater(void** state);
void test_basic_string_compare_cstr__c_builtin_size_equal_less(void** state);
void test_basic_string_compare_cstr__c_builtin_size_equal_greater(void** state);
void test_basic_string_compare_cstr__char_empty(void** state);
void test_basic_string_compare_cstr__char_less(void** state);
void test_basic_string_compare_cstr__char_equal(void** state);
void test_basic_string_compare_cstr__char_greater(void** state);
void test_basic_string_compare_cstr__char_size_equal_less(void** state);
void test_basic_string_compare_cstr__char_size_equal_greater(void** state);
void test_basic_string_compare_cstr__cstr_empty(void** state);
void test_basic_string_compare_cstr__cstr_less(void** state);
void test_basic_string_compare_cstr__cstr_equal(void** state);
void test_basic_string_compare_cstr__cstr_greater(void** state);
void test_basic_string_compare_cstr__cstr_size_equal_less(void** state);
void test_basic_string_compare_cstr__cstr_size_equal_greater(void** state);
void test_basic_string_compare_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_compare_cstr__libcstl_builtin_less(void** state);
void test_basic_string_compare_cstr__libcstl_builtin_equal(void** state);
void test_basic_string_compare_cstr__libcstl_builtin_greater(void** state);
void test_basic_string_compare_cstr__libcstl_builtin_size_equal_less(void** state);
void test_basic_string_compare_cstr__libcstl_builtin_size_equal_greater(void** state);
void test_basic_string_compare_cstr__user_defined_empty(void** state);
void test_basic_string_compare_cstr__user_defined_less(void** state);
void test_basic_string_compare_cstr__user_defined_equal(void** state);
void test_basic_string_compare_cstr__user_defined_greater(void** state);
void test_basic_string_compare_cstr__user_defined_size_equal_less(void** state);
void test_basic_string_compare_cstr__user_defined_size_equal_greater(void** state);
/*
 * test basic_string_compare_substring_cstr
 */
UT_CASE_DECLARATION(basic_string_compare_substring_cstr)
void test_basic_string_compare_substring_cstr__null_basic_string(void** state);
void test_basic_string_compare_substring_cstr__null_value_string(void** state);
void test_basic_string_compare_substring_cstr__non_inited_basic_string(void** state);
void test_basic_string_compare_substring_cstr__invalid_pos(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_all_equal(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_cstr__c_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_cstr__char_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__char_non_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__char_empty_non_empty(void** state);
void test_basic_string_compare_substring_cstr__char_sub_size_less(void** state);
void test_basic_string_compare_substring_cstr__char_sub_content_less(void** state);
void test_basic_string_compare_substring_cstr__char_sub_equal(void** state);
void test_basic_string_compare_substring_cstr__char_sub_size_greater(void** state);
void test_basic_string_compare_substring_cstr__char_sub_content_greater(void** state);
void test_basic_string_compare_substring_cstr__char_all_size_less(void** state);
void test_basic_string_compare_substring_cstr__char_all_content_less(void** state);
void test_basic_string_compare_substring_cstr__char_all_equal(void** state);
void test_basic_string_compare_substring_cstr__char_all_size_greater(void** state);
void test_basic_string_compare_substring_cstr__char_all_content_greater(void** state);
void test_basic_string_compare_substring_cstr__cstr_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__cstr_non_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__cstr_empty_non_empty(void** state);
void test_basic_string_compare_substring_cstr__cstr_sub_size_less(void** state);
void test_basic_string_compare_substring_cstr__cstr_sub_content_less(void** state);
void test_basic_string_compare_substring_cstr__cstr_sub_equal(void** state);
void test_basic_string_compare_substring_cstr__cstr_sub_size_greater(void** state);
void test_basic_string_compare_substring_cstr__cstr_sub_content_greater(void** state);
void test_basic_string_compare_substring_cstr__cstr_all_size_less(void** state);
void test_basic_string_compare_substring_cstr__cstr_all_content_less(void** state);
void test_basic_string_compare_substring_cstr__cstr_all_equal(void** state);
void test_basic_string_compare_substring_cstr__cstr_all_size_greater(void** state);
void test_basic_string_compare_substring_cstr__cstr_all_content_greater(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_all_equal(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_cstr__libcstl_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_cstr__user_defined_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__user_defined_non_empty_empty(void** state);
void test_basic_string_compare_substring_cstr__user_defined_empty_non_empty(void** state);
void test_basic_string_compare_substring_cstr__user_defined_sub_size_less(void** state);
void test_basic_string_compare_substring_cstr__user_defined_sub_content_less(void** state);
void test_basic_string_compare_substring_cstr__user_defined_sub_equal(void** state);
void test_basic_string_compare_substring_cstr__user_defined_sub_size_greater(void** state);
void test_basic_string_compare_substring_cstr__user_defined_sub_content_greater(void** state);
void test_basic_string_compare_substring_cstr__user_defined_all_size_less(void** state);
void test_basic_string_compare_substring_cstr__user_defined_all_content_less(void** state);
void test_basic_string_compare_substring_cstr__user_defined_all_equal(void** state);
void test_basic_string_compare_substring_cstr__user_defined_all_size_greater(void** state);
void test_basic_string_compare_substring_cstr__user_defined_all_content_greater(void** state);
/*
 * test basic_string_compare_substring_subcstr
 */
UT_CASE_DECLARATION(basic_string_compare_substring_subcstr)
void test_basic_string_compare_substring_subcstr__null_basic_string(void** state);
void test_basic_string_compare_substring_subcstr__null_value_string(void** state);
void test_basic_string_compare_substring_subcstr__non_inited_basic_string(void** state);
void test_basic_string_compare_substring_subcstr__invalid_pos(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_all_equal(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__c_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__char_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__char_non_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__char_empty_non_empty(void** state);
void test_basic_string_compare_substring_subcstr__char_sub_size_less(void** state);
void test_basic_string_compare_substring_subcstr__char_sub_content_less(void** state);
void test_basic_string_compare_substring_subcstr__char_sub_equal(void** state);
void test_basic_string_compare_substring_subcstr__char_sub_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__char_sub_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__char_all_size_less(void** state);
void test_basic_string_compare_substring_subcstr__char_all_content_less(void** state);
void test_basic_string_compare_substring_subcstr__char_all_equal(void** state);
void test_basic_string_compare_substring_subcstr__char_all_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__char_all_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__cstr_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__cstr_non_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__cstr_empty_non_empty(void** state);
void test_basic_string_compare_substring_subcstr__cstr_sub_size_less(void** state);
void test_basic_string_compare_substring_subcstr__cstr_sub_content_less(void** state);
void test_basic_string_compare_substring_subcstr__cstr_sub_equal(void** state);
void test_basic_string_compare_substring_subcstr__cstr_sub_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__cstr_sub_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__cstr_all_size_less(void** state);
void test_basic_string_compare_substring_subcstr__cstr_all_content_less(void** state);
void test_basic_string_compare_substring_subcstr__cstr_all_equal(void** state);
void test_basic_string_compare_substring_subcstr__cstr_all_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__cstr_all_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_non_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_empty_non_empty(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_size_less(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_content_less(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_equal(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_all_size_less(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_all_content_less(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_all_equal(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_all_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__libcstl_builtin_all_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_non_empty_empty(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_empty_non_empty(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_sub_size_less(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_sub_content_less(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_sub_equal(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_sub_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_sub_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_all_size_less(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_all_content_less(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_all_equal(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_all_size_greater(void** state);
void test_basic_string_compare_substring_subcstr__user_defined_all_content_greater(void** state);
void test_basic_string_compare_substring_subcstr__shared(void** state);
void test_basic_string_compare_substring_subcstr__include_terminator(void** state);
void test_basic_string_compare_substring_subcstr__size(void** state);
void test_basic_string_compare_substring_subcstr__terminator_c(void** state);
void test_basic_string_compare_substring_subcstr__terminator_cstr(void** state);
void test_basic_string_compare_substring_subcstr__terminator_cstl(void** state);
void test_basic_string_compare_substring_subcstr__terminator_user_define(void** state);
/*
 * test basic_string_substr
 */
UT_CASE_DECLARATION(basic_string_substr)
void test_basic_string_substr__null_basic_string(void** state);
void test_basic_string_substr__non_inited_basic_string(void** state);
void test_basic_string_substr__invalid_pos(void** state);
void test_basic_string_substr__empty_substr(void** state);
void test_basic_string_substr__all(void** state);
void test_basic_string_substr__c_builtin(void** state);
void test_basic_string_substr__char(void** state);
void test_basic_string_substr__cstr(void** state);
void test_basic_string_substr__libcstl(void** state);
void test_basic_string_substr__user_define(void** state);
void test_basic_string_substr__check(void** state);
/*
 * test basic_string_connect
 */
UT_CASE_DECLARATION(basic_string_connect)
void test_basic_string_connect__null_dest(void** state);
void test_basic_string_connect__null_src(void** state);
void test_basic_string_connect__non_inited_dest(void** state);
void test_basic_string_connect__non_inited_src(void** state);
void test_basic_string_connect__not_same_type(void** state);
void test_basic_string_connect__empty_empty(void** state);
void test_basic_string_connect__non_empty_empty(void** state);
void test_basic_string_connect__empty_non_empty(void** state);
void test_basic_string_connect__same(void** state);
void test_basic_string_connect__c_builtin(void** state);
void test_basic_string_connect__char(void** state);
void test_basic_string_connect__cstr(void** state);
void test_basic_string_connect__libcstl(void** state);
void test_basic_string_connect__user_define(void** state);
/*
 * test basic_string_connect_cstr
 */
UT_CASE_DECLARATION(basic_string_connect_cstr)
void test_basic_string_connect_cstr__null_basic_string(void** state);
void test_basic_string_connect_cstr__null_value_string(void** state);
void test_basic_string_connect_cstr__non_inited_basic_string(void** state);
void test_basic_string_connect_cstr__empty_empty(void** state);
void test_basic_string_connect_cstr__non_empty_empty(void** state);
void test_basic_string_connect_cstr__empty_non_empty(void** state);
void test_basic_string_connect_cstr__c_builtin(void** state);
void test_basic_string_connect_cstr__char(void** state);
void test_basic_string_connect_cstr__cstr(void** state);
void test_basic_string_connect_cstr__libcstl(void** state);
void test_basic_string_connect_cstr__user_define(void** state);
/*
 * test basic_string_find
 */
UT_CASE_DECLARATION(basic_string_find)
void test_basic_string_find__null_basic_string(void** state);
void test_basic_string_find__null_find(void** state);
void test_basic_string_find__non_inited_basic_string(void** state);
void test_basic_string_find__non_inited_find(void** state);
void test_basic_string_find__not_same_type(void** state);
void test_basic_string_find__invalid_pos(void** state);
void test_basic_string_find__same_begin(void** state);
void test_basic_string_find__same_middle(void** state);
void test_basic_string_find__c_builtin_begin_empty(void** state);
void test_basic_string_find__c_builtin_begin_find(void** state);
void test_basic_string_find__c_builtin_begin_not_find(void** state);
void test_basic_string_find__c_builtin_middle_empty(void** state);
void test_basic_string_find__c_builtin_middle_find(void** state);
void test_basic_string_find__c_builtin_middle_not_find(void** state);
void test_basic_string_find__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find__c_builtin_pos_eq_size_n_eq_0(void** state);
void test_basic_string_find__c_builtin_pos_eq_size_n_ne_0(void** state);
void test_basic_string_find__c_builtin_pos_gt_size_n_eq_0(void** state);
void test_basic_string_find__c_builtin_pos_gt_size_n_ne_0(void** state);
void test_basic_string_find__char_begin_empty(void** state);
void test_basic_string_find__char_begin_find(void** state);
void test_basic_string_find__char_begin_not_find(void** state);
void test_basic_string_find__char_middle_empty(void** state);
void test_basic_string_find__char_middle_find(void** state);
void test_basic_string_find__char_middle_not_find(void** state);
void test_basic_string_find__char_middle_not_find_pos(void** state);
void test_basic_string_find__cstr_begin_empty(void** state);
void test_basic_string_find__cstr_begin_find(void** state);
void test_basic_string_find__cstr_begin_not_find(void** state);
void test_basic_string_find__cstr_middle_empty(void** state);
void test_basic_string_find__cstr_middle_find(void** state);
void test_basic_string_find__cstr_middle_not_find(void** state);
void test_basic_string_find__cstr_middle_not_find_pos(void** state);
void test_basic_string_find__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find__libcstl_builtin_begin_find(void** state);
void test_basic_string_find__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find__libcstl_builtin_middle_find(void** state);
void test_basic_string_find__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find__user_define_begin_empty(void** state);
void test_basic_string_find__user_define_begin_find(void** state);
void test_basic_string_find__user_define_begin_not_find(void** state);
void test_basic_string_find__user_define_middle_empty(void** state);
void test_basic_string_find__user_define_middle_find(void** state);
void test_basic_string_find__user_define_middle_not_find(void** state);
void test_basic_string_find__user_define_middle_not_find_pos(void** state);
/*
 * test basic_string_find_cstr
 */
UT_CASE_DECLARATION(basic_string_find_cstr)
void test_basic_string_find_cstr__null_basic_string(void** state);
void test_basic_string_find_cstr__null_find(void** state);
void test_basic_string_find_cstr__non_inited_basic_string(void** state);
void test_basic_string_find_cstr__invalid_pos(void** state);
void test_basic_string_find_cstr__c_builtin_begin_empty(void** state);
void test_basic_string_find_cstr__c_builtin_begin_find(void** state);
void test_basic_string_find_cstr__c_builtin_begin_not_find(void** state);
void test_basic_string_find_cstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_cstr__c_builtin_middle_find(void** state);
void test_basic_string_find_cstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_cstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_cstr__c_builtin_pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_cstr__c_builtin_pos_eq_size_n_ne_0(void** state);
void test_basic_string_find_cstr__c_builtin_pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_cstr__c_builtin_pos_gt_size_n_ne_0(void** state);
void test_basic_string_find_cstr__char_begin_empty(void** state);
void test_basic_string_find_cstr__char_begin_find(void** state);
void test_basic_string_find_cstr__char_begin_not_find(void** state);
void test_basic_string_find_cstr__char_middle_empty(void** state);
void test_basic_string_find_cstr__char_middle_find(void** state);
void test_basic_string_find_cstr__char_middle_not_find(void** state);
void test_basic_string_find_cstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_cstr__cstr_begin_empty(void** state);
void test_basic_string_find_cstr__cstr_begin_find(void** state);
void test_basic_string_find_cstr__cstr_begin_not_find(void** state);
void test_basic_string_find_cstr__cstr_middle_empty(void** state);
void test_basic_string_find_cstr__cstr_middle_find(void** state);
void test_basic_string_find_cstr__cstr_middle_not_find(void** state);
void test_basic_string_find_cstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_cstr__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_cstr__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_cstr__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_cstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_cstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_cstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_cstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_cstr__user_define_begin_empty(void** state);
void test_basic_string_find_cstr__user_define_begin_find(void** state);
void test_basic_string_find_cstr__user_define_begin_not_find(void** state);
void test_basic_string_find_cstr__user_define_middle_empty(void** state);
void test_basic_string_find_cstr__user_define_middle_find(void** state);
void test_basic_string_find_cstr__user_define_middle_not_find(void** state);
void test_basic_string_find_cstr__user_define_middle_not_find_pos(void** state);
/*
 * test basic_string_find_subcstr
 */
UT_CASE_DECLARATION(basic_string_find_subcstr)
void test_basic_string_find_subcstr__null_basic_string(void** state);
void test_basic_string_find_subcstr__null_find(void** state);
void test_basic_string_find_subcstr__non_inited_basic_string(void** state);
void test_basic_string_find_subcstr__invalid_pos(void** state);
void test_basic_string_find_subcstr__c_builtin_begin_empty(void** state);
void test_basic_string_find_subcstr__c_builtin_begin_length_0(void** state);
void test_basic_string_find_subcstr__c_builtin_begin_find(void** state);
void test_basic_string_find_subcstr__c_builtin_begin_not_find(void** state);
void test_basic_string_find_subcstr__c_builtin_begin_equal_size(void** state);
void test_basic_string_find_subcstr__c_builtin_begin_greater_size(void** state);
void test_basic_string_find_subcstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_subcstr__c_builtin_middle_length_0(void** state);
void test_basic_string_find_subcstr__c_builtin_middle_find(void** state);
void test_basic_string_find_subcstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_subcstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_subcstr__c_builtin_middle_equal_size(void** state);
void test_basic_string_find_subcstr__c_builtin_middle_great_size(void** state);
void test_basic_string_find_subcstr__c_builtin_end_empty(void** state);
void test_basic_string_find_subcstr__c_builtin_end_non_empty(void** state);
void test_basic_string_find_subcstr__char_begin_empty(void** state);
void test_basic_string_find_subcstr__char_begin_length_0(void** state);
void test_basic_string_find_subcstr__char_begin_find(void** state);
void test_basic_string_find_subcstr__char_begin_not_find(void** state);
void test_basic_string_find_subcstr__char_middle_empty(void** state);
void test_basic_string_find_subcstr__char_middle_length_0(void** state);
void test_basic_string_find_subcstr__char_middle_find(void** state);
void test_basic_string_find_subcstr__char_middle_not_find(void** state);
void test_basic_string_find_subcstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_subcstr__cstr_begin_empty(void** state);
void test_basic_string_find_subcstr__cstr_begin_length_0(void** state);
void test_basic_string_find_subcstr__cstr_begin_find(void** state);
void test_basic_string_find_subcstr__cstr_begin_not_find(void** state);
void test_basic_string_find_subcstr__cstr_middle_empty(void** state);
void test_basic_string_find_subcstr__cstr_middle_length_0(void** state);
void test_basic_string_find_subcstr__cstr_middle_find(void** state);
void test_basic_string_find_subcstr__cstr_middle_not_find(void** state);
void test_basic_string_find_subcstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_begin_length_0(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_middle_length_0(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_subcstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_subcstr__user_define_begin_empty(void** state);
void test_basic_string_find_subcstr__user_define_begin_length_0(void** state);
void test_basic_string_find_subcstr__user_define_begin_find(void** state);
void test_basic_string_find_subcstr__user_define_begin_not_find(void** state);
void test_basic_string_find_subcstr__user_define_middle_empty(void** state);
void test_basic_string_find_subcstr__user_define_middle_length_0(void** state);
void test_basic_string_find_subcstr__user_define_middle_find(void** state);
void test_basic_string_find_subcstr__user_define_middle_not_find(void** state);
void test_basic_string_find_subcstr__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_subcstr__shared(void** state);
/*
 * test basic_string_rfind
 */
UT_CASE_DECLARATION(basic_string_rfind)
void test_basic_string_rfind__null_basic_string(void** state);
void test_basic_string_rfind__null_find(void** state);
void test_basic_string_rfind__non_inited_basic_string(void** state);
void test_basic_string_rfind__non_inited_find(void** state);
void test_basic_string_rfind__not_same_type(void** state);
void test_basic_string_rfind__same_npos(void** state);
void test_basic_string_rfind__same_middle(void** state);
void test_basic_string_rfind__c_builtin_empty_empty_0(void** state);
void test_basic_string_rfind__c_builtin_empty_empty_npos(void** state);
void test_basic_string_rfind__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_rfind__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_rfind__c_builtin_empty_npos(void** state);
void test_basic_string_rfind__c_builtin_find_npos(void** state);
void test_basic_string_rfind__c_builtin_not_find_npos(void** state);
void test_basic_string_rfind__c_builtin_middle_empty(void** state);
void test_basic_string_rfind__c_builtin_middle_find(void** state);
void test_basic_string_rfind__c_builtin_middle_not_find(void** state);
void test_basic_string_rfind__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_rfind__char_empty_empty_0(void** state);
void test_basic_string_rfind__char_empty_empty_npos(void** state);
void test_basic_string_rfind__char_empty_non_empty_0(void** state);
void test_basic_string_rfind__char_empty_non_empty_npos(void** state);
void test_basic_string_rfind__char_empty_npos(void** state);
void test_basic_string_rfind__char_find_npos(void** state);
void test_basic_string_rfind__char_not_find_npos(void** state);
void test_basic_string_rfind__char_middle_empty(void** state);
void test_basic_string_rfind__char_middle_find(void** state);
void test_basic_string_rfind__char_middle_not_find(void** state);
void test_basic_string_rfind__char_middle_not_find_pos(void** state);
void test_basic_string_rfind__cstr_empty_empty_0(void** state);
void test_basic_string_rfind__cstr_empty_empty_npos(void** state);
void test_basic_string_rfind__cstr_empty_non_empty_0(void** state);
void test_basic_string_rfind__cstr_empty_non_empty_npos(void** state);
void test_basic_string_rfind__cstr_empty_npos(void** state);
void test_basic_string_rfind__cstr_find_npos(void** state);
void test_basic_string_rfind__cstr_not_find_npos(void** state);
void test_basic_string_rfind__cstr_middle_empty(void** state);
void test_basic_string_rfind__cstr_middle_find(void** state);
void test_basic_string_rfind__cstr_middle_not_find(void** state);
void test_basic_string_rfind__cstr_middle_not_find_pos(void** state);
void test_basic_string_rfind__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_rfind__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_rfind__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_rfind__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_rfind__libcstl_builtin_empty_npos(void** state);
void test_basic_string_rfind__libcstl_builtin_find_npos(void** state);
void test_basic_string_rfind__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_rfind__libcstl_builtin_middle_empty(void** state);
void test_basic_string_rfind__libcstl_builtin_middle_find(void** state);
void test_basic_string_rfind__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_rfind__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_rfind__user_define_empty_empty_0(void** state);
void test_basic_string_rfind__user_define_empty_empty_npos(void** state);
void test_basic_string_rfind__user_define_empty_non_empty_0(void** state);
void test_basic_string_rfind__user_define_empty_non_empty_npos(void** state);
void test_basic_string_rfind__user_define_empty_npos(void** state);
void test_basic_string_rfind__user_define_find_npos(void** state);
void test_basic_string_rfind__user_define_not_find_npos(void** state);
void test_basic_string_rfind__user_define_middle_empty(void** state);
void test_basic_string_rfind__user_define_middle_find(void** state);
void test_basic_string_rfind__user_define_middle_not_find(void** state);
void test_basic_string_rfind__user_define_middle_not_find_pos(void** state);
void test_basic_string_rfind__pos_eq_0_n_eq_0(void** state);
void test_basic_string_rfind__pos_lt_size_n_eq_0(void** state);
void test_basic_string_rfind__pos_eq_size_n_eq_0(void** state);
void test_basic_string_rfind__pos_gt_size_n_eq_0(void** state);
void test_basic_string_rfind__pos_eq_0_n_lt_size(void** state);
void test_basic_string_rfind__pos_lt_size_n_lt_size(void** state);
void test_basic_string_rfind__pos_eq_size_n_lt_size(void** state);
void test_basic_string_rfind__pos_gt_size_n_lt_size(void** state);
void test_basic_string_rfind__pos_eq_0_n_eq_size(void** state);
void test_basic_string_rfind__pos_lt_size_n_eq_size(void** state);
void test_basic_string_rfind__pos_eq_size_n_eq_size(void** state);
void test_basic_string_rfind__pos_gt_size_n_eq_size(void** state);
void test_basic_string_rfind__pos_eq_0_n_gt_size(void** state);
void test_basic_string_rfind__pos_lt_size_n_gt_size(void** state);
void test_basic_string_rfind__pos_eq_size_n_gt_size(void** state);
void test_basic_string_rfind__pos_gt_size_n_gt_size(void** state);
/*
 * test basic_string_rfind_cstr
 */
UT_CASE_DECLARATION(basic_string_rfind_cstr)
void test_basic_string_rfind_cstr__null_basic_string(void** state);
void test_basic_string_rfind_cstr__null_find(void** state);
void test_basic_string_rfind_cstr__non_inited_basic_string(void** state);
void test_basic_string_rfind_cstr__c_builtin_empty_empty_0(void** state);
void test_basic_string_rfind_cstr__c_builtin_empty_empty_npos(void** state);
void test_basic_string_rfind_cstr__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_rfind_cstr__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_rfind_cstr__c_builtin_empty_npos(void** state);
void test_basic_string_rfind_cstr__c_builtin_find_npos(void** state);
void test_basic_string_rfind_cstr__c_builtin_not_find_npos(void** state);
void test_basic_string_rfind_cstr__c_builtin_middle_empty(void** state);
void test_basic_string_rfind_cstr__c_builtin_middle_find(void** state);
void test_basic_string_rfind_cstr__c_builtin_middle_not_find(void** state);
void test_basic_string_rfind_cstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_rfind_cstr__char_empty_empty_0(void** state);
void test_basic_string_rfind_cstr__char_empty_empty_npos(void** state);
void test_basic_string_rfind_cstr__char_empty_non_empty_0(void** state);
void test_basic_string_rfind_cstr__char_empty_non_empty_npos(void** state);
void test_basic_string_rfind_cstr__char_empty_npos(void** state);
void test_basic_string_rfind_cstr__char_find_npos(void** state);
void test_basic_string_rfind_cstr__char_not_find_npos(void** state);
void test_basic_string_rfind_cstr__char_middle_empty(void** state);
void test_basic_string_rfind_cstr__char_middle_find(void** state);
void test_basic_string_rfind_cstr__char_middle_not_find(void** state);
void test_basic_string_rfind_cstr__char_middle_not_find_pos(void** state);
void test_basic_string_rfind_cstr__cstr_empty_empty_0(void** state);
void test_basic_string_rfind_cstr__cstr_empty_empty_npos(void** state);
void test_basic_string_rfind_cstr__cstr_empty_non_empty_0(void** state);
void test_basic_string_rfind_cstr__cstr_empty_non_empty_npos(void** state);
void test_basic_string_rfind_cstr__cstr_empty_npos(void** state);
void test_basic_string_rfind_cstr__cstr_find_npos(void** state);
void test_basic_string_rfind_cstr__cstr_not_find_npos(void** state);
void test_basic_string_rfind_cstr__cstr_middle_empty(void** state);
void test_basic_string_rfind_cstr__cstr_middle_find(void** state);
void test_basic_string_rfind_cstr__cstr_middle_not_find(void** state);
void test_basic_string_rfind_cstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_empty_npos(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_find_npos(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_rfind_cstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_rfind_cstr__user_define_empty_empty_0(void** state);
void test_basic_string_rfind_cstr__user_define_empty_empty_npos(void** state);
void test_basic_string_rfind_cstr__user_define_empty_non_empty_0(void** state);
void test_basic_string_rfind_cstr__user_define_empty_non_empty_npos(void** state);
void test_basic_string_rfind_cstr__user_define_empty_npos(void** state);
void test_basic_string_rfind_cstr__user_define_find_npos(void** state);
void test_basic_string_rfind_cstr__user_define_not_find_npos(void** state);
void test_basic_string_rfind_cstr__user_define_middle_empty(void** state);
void test_basic_string_rfind_cstr__user_define_middle_find(void** state);
void test_basic_string_rfind_cstr__user_define_middle_not_find(void** state);
void test_basic_string_rfind_cstr__user_define_middle_not_find_pos(void** state);
void test_basic_string_rfind_cstr__pos_eq_0_n_eq_0(void** state);
void test_basic_string_rfind_cstr__pos_lt_size_n_eq_0(void** state);
void test_basic_string_rfind_cstr__pos_eq_size_n_eq_0(void** state);
void test_basic_string_rfind_cstr__pos_gt_size_n_eq_0(void** state);
void test_basic_string_rfind_cstr__pos_eq_0_n_lt_size(void** state);
void test_basic_string_rfind_cstr__pos_lt_size_n_lt_size(void** state);
void test_basic_string_rfind_cstr__pos_eq_size_n_lt_size(void** state);
void test_basic_string_rfind_cstr__pos_gt_size_n_lt_size(void** state);
void test_basic_string_rfind_cstr__pos_lt_size_n_eq_size(void** state);
void test_basic_string_rfind_cstr__pos_eq_size_n_eq_size(void** state);
void test_basic_string_rfind_cstr__pos_gt_size_n_eq_size(void** state);
void test_basic_string_rfind_cstr__pos_eq_0_n_eq_size(void** state);
void test_basic_string_rfind_cstr__pos_eq_0_n_gt_size(void** state);
void test_basic_string_rfind_cstr__pos_lt_size_n_gt_size(void** state);
void test_basic_string_rfind_cstr__pos_eq_size_n_gt_size(void** state);
void test_basic_string_rfind_cstr__pos_gt_size_n_gt_size(void** state);
/*
 * test basic_string_rfind_subcstr
 */
UT_CASE_DECLARATION(basic_string_rfind_subcstr)
void test_basic_string_rfind_subcstr__null_basic_string(void** state);
void test_basic_string_rfind_subcstr__null_find(void** state);
void test_basic_string_rfind_subcstr__non_inited_basic_string(void** state);
void test_basic_string_rfind_subcstr__c_builtin_empty_empty_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_empty_empty_npos(void** state);
void test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_0_length_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_rfind_subcstr__c_builtin_empty_npos(void** state);
void test_basic_string_rfind_subcstr__c_builtin_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_find_npos(void** state);
void test_basic_string_rfind_subcstr__c_builtin_not_find_npos(void** state);
void test_basic_string_rfind_subcstr__c_builtin_middle_empty(void** state);
void test_basic_string_rfind_subcstr__c_builtin_middle_empty_length_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_middle_find(void** state);
void test_basic_string_rfind_subcstr__c_builtin_middle_not_find(void** state);
void test_basic_string_rfind_subcstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_rfind_subcstr__char_empty_empty_0(void** state);
void test_basic_string_rfind_subcstr__char_empty_empty_npos(void** state);
void test_basic_string_rfind_subcstr__char_empty_non_empty_0_length_0(void** state);
void test_basic_string_rfind_subcstr__char_empty_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__char_empty_non_empty_0(void** state);
void test_basic_string_rfind_subcstr__char_empty_non_empty_npos(void** state);
void test_basic_string_rfind_subcstr__char_empty_npos(void** state);
void test_basic_string_rfind_subcstr__char_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__char_find_npos(void** state);
void test_basic_string_rfind_subcstr__char_not_find_npos(void** state);
void test_basic_string_rfind_subcstr__char_middle_empty(void** state);
void test_basic_string_rfind_subcstr__char_middle_non_empty_length_0(void** state);
void test_basic_string_rfind_subcstr__char_middle_find(void** state);
void test_basic_string_rfind_subcstr__char_middle_not_find(void** state);
void test_basic_string_rfind_subcstr__char_middle_not_find_pos(void** state);
void test_basic_string_rfind_subcstr__cstr_empty_empty_0(void** state);
void test_basic_string_rfind_subcstr__cstr_empty_empty_npos(void** state);
void test_basic_string_rfind_subcstr__cstr_empty_non_empty_0_length_0(void** state);
void test_basic_string_rfind_subcstr__cstr_empty_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__cstr_empty_non_empty_0(void** state);
void test_basic_string_rfind_subcstr__cstr_empty_non_empty_npos(void** state);
void test_basic_string_rfind_subcstr__cstr_empty_npos(void** state);
void test_basic_string_rfind_subcstr__cstr_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__cstr_find_npos(void** state);
void test_basic_string_rfind_subcstr__cstr_not_find_npos(void** state);
void test_basic_string_rfind_subcstr__cstr_middle_empty(void** state);
void test_basic_string_rfind_subcstr__cstr_middle_non_empty_length_0(void** state);
void test_basic_string_rfind_subcstr__cstr_middle_find(void** state);
void test_basic_string_rfind_subcstr__cstr_middle_not_find(void** state);
void test_basic_string_rfind_subcstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_0_length_0(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_empty_npos(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_find_npos(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_middle_non_empty_length_0(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_rfind_subcstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_rfind_subcstr__user_define_empty_empty_0(void** state);
void test_basic_string_rfind_subcstr__user_define_empty_empty_npos(void** state);
void test_basic_string_rfind_subcstr__user_define_empty_non_empty_0_length_0(void** state);
void test_basic_string_rfind_subcstr__user_define_empty_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__user_define_empty_non_empty_0(void** state);
void test_basic_string_rfind_subcstr__user_define_empty_non_empty_npos(void** state);
void test_basic_string_rfind_subcstr__user_define_empty_npos(void** state);
void test_basic_string_rfind_subcstr__user_define_non_empty_npos_length_0(void** state);
void test_basic_string_rfind_subcstr__user_define_find_npos(void** state);
void test_basic_string_rfind_subcstr__user_define_not_find_npos(void** state);
void test_basic_string_rfind_subcstr__user_define_middle_empty(void** state);
void test_basic_string_rfind_subcstr__user_define_middle_non_empty_length_0(void** state);
void test_basic_string_rfind_subcstr__user_define_middle_find(void** state);
void test_basic_string_rfind_subcstr__user_define_middle_not_find(void** state);
void test_basic_string_rfind_subcstr__user_define_middle_not_find_pos(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_eq_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_eq_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_eq_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_eq_0(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_lt_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_lt_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_lt_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_lt_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_eq_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_eq_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_eq_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_eq_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_gt_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_gt_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_gt_size(void** state);
void test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_gt_size(void** state);
/*
 * test basic_string_find_first_of
 */
UT_CASE_DECLARATION(basic_string_find_first_of)
void test_basic_string_find_first_of__null_basic_string(void** state);
void test_basic_string_find_first_of__null_find(void** state);
void test_basic_string_find_first_of__non_inited_basic_string(void** state);
void test_basic_string_find_first_of__non_inited_find(void** state);
void test_basic_string_find_first_of__not_same_type(void** state);
void test_basic_string_find_first_of__invalid_pos(void** state);
void test_basic_string_find_first_of__same_begin(void** state);
void test_basic_string_find_first_of__same_middle(void** state);
void test_basic_string_find_first_of__c_builtin_begin_empty(void** state);
void test_basic_string_find_first_of__c_builtin_begin_find(void** state);
void test_basic_string_find_first_of__c_builtin_begin_not_find(void** state);
void test_basic_string_find_first_of__c_builtin_middle_empty(void** state);
void test_basic_string_find_first_of__c_builtin_middle_find(void** state);
void test_basic_string_find_first_of__c_builtin_middle_not_find(void** state);
void test_basic_string_find_first_of__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_of__char_begin_empty(void** state);
void test_basic_string_find_first_of__char_begin_find(void** state);
void test_basic_string_find_first_of__char_begin_not_find(void** state);
void test_basic_string_find_first_of__char_middle_empty(void** state);
void test_basic_string_find_first_of__char_middle_find(void** state);
void test_basic_string_find_first_of__char_middle_not_find(void** state);
void test_basic_string_find_first_of__char_middle_not_find_pos(void** state);
void test_basic_string_find_first_of__cstr_begin_empty(void** state);
void test_basic_string_find_first_of__cstr_begin_find(void** state);
void test_basic_string_find_first_of__cstr_begin_not_find(void** state);
void test_basic_string_find_first_of__cstr_middle_empty(void** state);
void test_basic_string_find_first_of__cstr_middle_find(void** state);
void test_basic_string_find_first_of__cstr_middle_not_find(void** state);
void test_basic_string_find_first_of__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_first_of__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_first_of__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_first_of__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_first_of__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_first_of__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_first_of__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_first_of__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_of__user_define_begin_empty(void** state);
void test_basic_string_find_first_of__user_define_begin_find(void** state);
void test_basic_string_find_first_of__user_define_begin_not_find(void** state);
void test_basic_string_find_first_of__user_define_middle_empty(void** state);
void test_basic_string_find_first_of__user_define_middle_find(void** state);
void test_basic_string_find_first_of__user_define_middle_not_find(void** state);
void test_basic_string_find_first_of__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_first_of__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_first_of__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_first_of__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_first_of__pos_eq_0_n_gt_size(void** state);
void test_basic_string_find_first_of__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_first_of__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_first_of__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_first_of__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_first_of__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_first_of__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_first_of__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_first_of__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_first_of__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_first_of__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_first_of__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_first_of__pos_eq_0_n_eq_0(void** state);
void test_basic_string_find_first_of__terminator_c(void** state);
void test_basic_string_find_first_of__terminator_cstr(void** state);
void test_basic_string_find_first_of__terminator_cstl(void** state);
void test_basic_string_find_first_of__terminator_user_define(void** state);
/*
 * test basic_string_find_first_of_cstr
 */
UT_CASE_DECLARATION(basic_string_find_first_of_cstr)
void test_basic_string_find_first_of_cstr__null_basic_string(void** state);
void test_basic_string_find_first_of_cstr__null_find(void** state);
void test_basic_string_find_first_of_cstr__non_inited_basic_string(void** state);
void test_basic_string_find_first_of_cstr__invalid_pos(void** state);
void test_basic_string_find_first_of_cstr__c_builtin_begin_empty(void** state);
void test_basic_string_find_first_of_cstr__c_builtin_begin_find(void** state);
void test_basic_string_find_first_of_cstr__c_builtin_begin_not_find(void** state);
void test_basic_string_find_first_of_cstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_first_of_cstr__c_builtin_middle_find(void** state);
void test_basic_string_find_first_of_cstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_first_of_cstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_cstr__char_begin_empty(void** state);
void test_basic_string_find_first_of_cstr__char_begin_find(void** state);
void test_basic_string_find_first_of_cstr__char_begin_not_find(void** state);
void test_basic_string_find_first_of_cstr__char_middle_empty(void** state);
void test_basic_string_find_first_of_cstr__char_middle_find(void** state);
void test_basic_string_find_first_of_cstr__char_middle_not_find(void** state);
void test_basic_string_find_first_of_cstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_cstr__cstr_begin_empty(void** state);
void test_basic_string_find_first_of_cstr__cstr_begin_find(void** state);
void test_basic_string_find_first_of_cstr__cstr_begin_not_find(void** state);
void test_basic_string_find_first_of_cstr__cstr_middle_empty(void** state);
void test_basic_string_find_first_of_cstr__cstr_middle_find(void** state);
void test_basic_string_find_first_of_cstr__cstr_middle_not_find(void** state);
void test_basic_string_find_first_of_cstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_cstr__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_first_of_cstr__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_first_of_cstr__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_first_of_cstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_first_of_cstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_first_of_cstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_first_of_cstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_cstr__user_define_begin_empty(void** state);
void test_basic_string_find_first_of_cstr__user_define_begin_find(void** state);
void test_basic_string_find_first_of_cstr__user_define_begin_not_find(void** state);
void test_basic_string_find_first_of_cstr__user_define_middle_empty(void** state);
void test_basic_string_find_first_of_cstr__user_define_middle_find(void** state);
void test_basic_string_find_first_of_cstr__user_define_middle_not_find(void** state);
void test_basic_string_find_first_of_cstr__user_define_middle_not_find_pos(void** state);
/*
 * test basic_string_find_first_of_subcstr
 */
UT_CASE_DECLARATION(basic_string_find_first_of_subcstr)
void test_basic_string_find_first_of_subcstr__null_basic_string(void** state);
void test_basic_string_find_first_of_subcstr__null_find(void** state);
void test_basic_string_find_first_of_subcstr__non_inited_basic_string(void** state);
void test_basic_string_find_first_of_subcstr__invalid_pos(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_begin_empty(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_begin_length_0(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_begin_find(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_begin_not_find(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_middle_length_0(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_middle_find(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_first_of_subcstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_subcstr__char_begin_empty(void** state);
void test_basic_string_find_first_of_subcstr__char_begin_length_0(void** state);
void test_basic_string_find_first_of_subcstr__char_begin_find(void** state);
void test_basic_string_find_first_of_subcstr__char_begin_not_find(void** state);
void test_basic_string_find_first_of_subcstr__char_middle_empty(void** state);
void test_basic_string_find_first_of_subcstr__char_middle_length_0(void** state);
void test_basic_string_find_first_of_subcstr__char_middle_find(void** state);
void test_basic_string_find_first_of_subcstr__char_middle_not_find(void** state);
void test_basic_string_find_first_of_subcstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_subcstr__cstr_begin_empty(void** state);
void test_basic_string_find_first_of_subcstr__cstr_begin_length_0(void** state);
void test_basic_string_find_first_of_subcstr__cstr_begin_find(void** state);
void test_basic_string_find_first_of_subcstr__cstr_begin_not_find(void** state);
void test_basic_string_find_first_of_subcstr__cstr_middle_empty(void** state);
void test_basic_string_find_first_of_subcstr__cstr_middle_length_0(void** state);
void test_basic_string_find_first_of_subcstr__cstr_middle_find(void** state);
void test_basic_string_find_first_of_subcstr__cstr_middle_not_find(void** state);
void test_basic_string_find_first_of_subcstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_length_0(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_length_0(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_subcstr__user_define_begin_empty(void** state);
void test_basic_string_find_first_of_subcstr__user_define_begin_length_0(void** state);
void test_basic_string_find_first_of_subcstr__user_define_begin_find(void** state);
void test_basic_string_find_first_of_subcstr__user_define_begin_not_find(void** state);
void test_basic_string_find_first_of_subcstr__user_define_middle_empty(void** state);
void test_basic_string_find_first_of_subcstr__user_define_middle_length_0(void** state);
void test_basic_string_find_first_of_subcstr__user_define_middle_find(void** state);
void test_basic_string_find_first_of_subcstr__user_define_middle_not_find(void** state);
void test_basic_string_find_first_of_subcstr__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_0_n_eq_0(void** state);
void test_basic_string_find_first_of_subcstr__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_first_of_subcstr__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_0_n_gt_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_first_of_subcstr__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_first_of_subcstr__terminator_c(void** state);
void test_basic_string_find_first_of_subcstr__terminator_cstr(void** state);
void test_basic_string_find_first_of_subcstr__terminator_cstl(void** state);
void test_basic_string_find_first_of_subcstr__terminator_user_define(void** state);
/*
 * test basic_string_find_first_not_of
 */
UT_CASE_DECLARATION(basic_string_find_first_not_of)
void test_basic_string_find_first_not_of__null_basic_string(void** state);
void test_basic_string_find_first_not_of__null_find(void** state);
void test_basic_string_find_first_not_of__non_inited_basic_string(void** state);
void test_basic_string_find_first_not_of__non_inited_find(void** state);
void test_basic_string_find_first_not_of__not_same_type(void** state);
void test_basic_string_find_first_not_of__invalid_pos(void** state);
void test_basic_string_find_first_not_of__same_begin(void** state);
void test_basic_string_find_first_not_of__same_middle(void** state);
void test_basic_string_find_first_not_of__c_builtin_begin_empty(void** state);
void test_basic_string_find_first_not_of__c_builtin_begin_find(void** state);
void test_basic_string_find_first_not_of__c_builtin_begin_not_find(void** state);
void test_basic_string_find_first_not_of__c_builtin_middle_empty(void** state);
void test_basic_string_find_first_not_of__c_builtin_middle_find(void** state);
void test_basic_string_find_first_not_of__c_builtin_middle_not_find(void** state);
void test_basic_string_find_first_not_of__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of__char_begin_empty(void** state);
void test_basic_string_find_first_not_of__char_begin_find(void** state);
void test_basic_string_find_first_not_of__char_begin_not_find(void** state);
void test_basic_string_find_first_not_of__char_middle_empty(void** state);
void test_basic_string_find_first_not_of__char_middle_find(void** state);
void test_basic_string_find_first_not_of__char_middle_not_find(void** state);
void test_basic_string_find_first_not_of__char_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of__cstr_begin_empty(void** state);
void test_basic_string_find_first_not_of__cstr_begin_find(void** state);
void test_basic_string_find_first_not_of__cstr_begin_not_find(void** state);
void test_basic_string_find_first_not_of__cstr_middle_empty(void** state);
void test_basic_string_find_first_not_of__cstr_middle_find(void** state);
void test_basic_string_find_first_not_of__cstr_middle_not_find(void** state);
void test_basic_string_find_first_not_of__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_first_not_of__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_first_not_of__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_first_not_of__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_first_not_of__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_first_not_of__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_first_not_of__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of__user_define_begin_empty(void** state);
void test_basic_string_find_first_not_of__user_define_begin_find(void** state);
void test_basic_string_find_first_not_of__user_define_begin_not_find(void** state);
void test_basic_string_find_first_not_of__user_define_middle_empty(void** state);
void test_basic_string_find_first_not_of__user_define_middle_find(void** state);
void test_basic_string_find_first_not_of__user_define_middle_not_find(void** state);
void test_basic_string_find_first_not_of__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_first_not_of__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_first_not_of__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_first_not_of__pos_eq_0_n_gt_size(void** state);
void test_basic_string_find_first_not_of__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_first_not_of__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_first_not_of__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_first_not_of__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_first_not_of__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_first_not_of__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_first_not_of__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_first_not_of__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_first_not_of__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_first_not_of__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_first_not_of__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_first_not_of__pos_eq_0_n_eq_0(void** state);
/*
 * test basic_string_find_first_not_of_cstr
 */
UT_CASE_DECLARATION(basic_string_find_first_not_of_cstr)
void test_basic_string_find_first_not_of_cstr__null_basic_string(void** state);
void test_basic_string_find_first_not_of_cstr__null_find(void** state);
void test_basic_string_find_first_not_of_cstr__non_inited_basic_string(void** state);
void test_basic_string_find_first_not_of_cstr__invalid_pos(void** state);
void test_basic_string_find_first_not_of_cstr__c_builtin_begin_empty(void** state);
void test_basic_string_find_first_not_of_cstr__c_builtin_begin_find(void** state);
void test_basic_string_find_first_not_of_cstr__c_builtin_begin_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_first_not_of_cstr__c_builtin_middle_find(void** state);
void test_basic_string_find_first_not_of_cstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_cstr__char_begin_empty(void** state);
void test_basic_string_find_first_not_of_cstr__char_begin_find(void** state);
void test_basic_string_find_first_not_of_cstr__char_begin_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__char_middle_empty(void** state);
void test_basic_string_find_first_not_of_cstr__char_middle_find(void** state);
void test_basic_string_find_first_not_of_cstr__char_middle_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_cstr__cstr_begin_empty(void** state);
void test_basic_string_find_first_not_of_cstr__cstr_begin_find(void** state);
void test_basic_string_find_first_not_of_cstr__cstr_begin_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__cstr_middle_empty(void** state);
void test_basic_string_find_first_not_of_cstr__cstr_middle_find(void** state);
void test_basic_string_find_first_not_of_cstr__cstr_middle_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_cstr__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_first_not_of_cstr__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_first_not_of_cstr__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_cstr__user_define_begin_empty(void** state);
void test_basic_string_find_first_not_of_cstr__user_define_begin_find(void** state);
void test_basic_string_find_first_not_of_cstr__user_define_begin_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__user_define_middle_empty(void** state);
void test_basic_string_find_first_not_of_cstr__user_define_middle_find(void** state);
void test_basic_string_find_first_not_of_cstr__user_define_middle_not_find(void** state);
void test_basic_string_find_first_not_of_cstr__user_define_middle_not_find_pos(void** state);
/*
 * test basic_string_find_first_not_of_subcstr
 */
UT_CASE_DECLARATION(basic_string_find_first_not_of_subcstr)
void test_basic_string_find_first_not_of_subcstr__null_basic_string(void** state);
void test_basic_string_find_first_not_of_subcstr__null_find(void** state);
void test_basic_string_find_first_not_of_subcstr__non_inited_basic_string(void** state);
void test_basic_string_find_first_not_of_subcstr__invalid_pos(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_begin_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_begin_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_begin_find(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_begin_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_middle_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_middle_find(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_subcstr__char_begin_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__char_begin_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__char_begin_find(void** state);
void test_basic_string_find_first_not_of_subcstr__char_begin_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__char_middle_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__char_middle_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__char_middle_find(void** state);
void test_basic_string_find_first_not_of_subcstr__char_middle_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_begin_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_begin_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_begin_find(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_begin_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_middle_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_middle_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_middle_find(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_middle_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_find(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_begin_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_begin_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_begin_find(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_begin_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_middle_empty(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_middle_length_0(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_middle_find(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_middle_not_find(void** state);
void test_basic_string_find_first_not_of_subcstr__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_eq_0(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_gt_size(void** state);
/*
 * test basic_string_find_last_of
 */
UT_CASE_DECLARATION(basic_string_find_last_of)
void test_basic_string_find_last_of__null_basic_string(void** state);
void test_basic_string_find_last_of__null_find(void** state);
void test_basic_string_find_last_of__non_inited_basic_string(void** state);
void test_basic_string_find_last_of__non_inited_find(void** state);
void test_basic_string_find_last_of__not_same_type(void** state);
void test_basic_string_find_last_of__same_npos(void** state);
void test_basic_string_find_last_of__same_middle(void** state);
void test_basic_string_find_last_of__c_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_of__c_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_of__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_of__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of__c_builtin_empty_npos(void** state);
void test_basic_string_find_last_of__c_builtin_find_npos(void** state);
void test_basic_string_find_last_of__c_builtin_not_find_npos(void** state);
void test_basic_string_find_last_of__c_builtin_middle_empty(void** state);
void test_basic_string_find_last_of__c_builtin_middle_find(void** state);
void test_basic_string_find_last_of__c_builtin_middle_not_find(void** state);
void test_basic_string_find_last_of__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_of__char_empty_empty_0(void** state);
void test_basic_string_find_last_of__char_empty_empty_npos(void** state);
void test_basic_string_find_last_of__char_empty_non_empty_0(void** state);
void test_basic_string_find_last_of__char_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of__char_empty_npos(void** state);
void test_basic_string_find_last_of__char_find_npos(void** state);
void test_basic_string_find_last_of__char_not_find_npos(void** state);
void test_basic_string_find_last_of__char_middle_empty(void** state);
void test_basic_string_find_last_of__char_middle_find(void** state);
void test_basic_string_find_last_of__char_middle_not_find(void** state);
void test_basic_string_find_last_of__char_middle_not_find_pos(void** state);
void test_basic_string_find_last_of__cstr_empty_empty_0(void** state);
void test_basic_string_find_last_of__cstr_empty_empty_npos(void** state);
void test_basic_string_find_last_of__cstr_empty_non_empty_0(void** state);
void test_basic_string_find_last_of__cstr_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of__cstr_empty_npos(void** state);
void test_basic_string_find_last_of__cstr_find_npos(void** state);
void test_basic_string_find_last_of__cstr_not_find_npos(void** state);
void test_basic_string_find_last_of__cstr_middle_empty(void** state);
void test_basic_string_find_last_of__cstr_middle_find(void** state);
void test_basic_string_find_last_of__cstr_middle_not_find(void** state);
void test_basic_string_find_last_of__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_last_of__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_of__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_of__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_of__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of__libcstl_builtin_empty_npos(void** state);
void test_basic_string_find_last_of__libcstl_builtin_find_npos(void** state);
void test_basic_string_find_last_of__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_find_last_of__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_last_of__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_last_of__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_last_of__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_of__user_define_empty_empty_0(void** state);
void test_basic_string_find_last_of__user_define_empty_empty_npos(void** state);
void test_basic_string_find_last_of__user_define_empty_non_empty_0(void** state);
void test_basic_string_find_last_of__user_define_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of__user_define_empty_npos(void** state);
void test_basic_string_find_last_of__user_define_find_npos(void** state);
void test_basic_string_find_last_of__user_define_not_find_npos(void** state);
void test_basic_string_find_last_of__user_define_middle_empty(void** state);
void test_basic_string_find_last_of__user_define_middle_find(void** state);
void test_basic_string_find_last_of__user_define_middle_not_find(void** state);
void test_basic_string_find_last_of__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_last_of__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_last_of__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_last_of__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_last_of__pos_eq_0_n_gt_size(void** state);
void test_basic_string_find_last_of__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_last_of__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_last_of__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_last_of__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_last_of__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_last_of__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_last_of__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_last_of__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_last_of__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_last_of__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_last_of__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_last_of__pos_eq_0_n_eq_0(void** state);
/*
 * test basic_string_find_last_of_cstr
 */
UT_CASE_DECLARATION(basic_string_find_last_of_cstr)
void test_basic_string_find_last_of_cstr__null_basic_string(void** state);
void test_basic_string_find_last_of_cstr__null_find(void** state);
void test_basic_string_find_last_of_cstr__non_inited_basic_string(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_find_npos(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_not_find_npos(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_middle_find(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_last_of_cstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_cstr__char_empty_empty_0(void** state);
void test_basic_string_find_last_of_cstr__char_empty_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__char_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_cstr__char_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__char_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__char_find_npos(void** state);
void test_basic_string_find_last_of_cstr__char_not_find_npos(void** state);
void test_basic_string_find_last_of_cstr__char_middle_empty(void** state);
void test_basic_string_find_last_of_cstr__char_middle_find(void** state);
void test_basic_string_find_last_of_cstr__char_middle_not_find(void** state);
void test_basic_string_find_last_of_cstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_cstr__cstr_empty_empty_0(void** state);
void test_basic_string_find_last_of_cstr__cstr_empty_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__cstr_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_cstr__cstr_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__cstr_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__cstr_find_npos(void** state);
void test_basic_string_find_last_of_cstr__cstr_not_find_npos(void** state);
void test_basic_string_find_last_of_cstr__cstr_middle_empty(void** state);
void test_basic_string_find_last_of_cstr__cstr_middle_find(void** state);
void test_basic_string_find_last_of_cstr__cstr_middle_not_find(void** state);
void test_basic_string_find_last_of_cstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_find_npos(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_last_of_cstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_cstr__user_define_empty_empty_0(void** state);
void test_basic_string_find_last_of_cstr__user_define_empty_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__user_define_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_cstr__user_define_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__user_define_empty_npos(void** state);
void test_basic_string_find_last_of_cstr__user_define_find_npos(void** state);
void test_basic_string_find_last_of_cstr__user_define_not_find_npos(void** state);
void test_basic_string_find_last_of_cstr__user_define_middle_empty(void** state);
void test_basic_string_find_last_of_cstr__user_define_middle_find(void** state);
void test_basic_string_find_last_of_cstr__user_define_middle_not_find(void** state);
void test_basic_string_find_last_of_cstr__user_define_middle_not_find_pos(void** state);
/*
 * test basic_string_find_last_of_subcstr
 */
UT_CASE_DECLARATION(basic_string_find_last_of_subcstr)
void test_basic_string_find_last_of_subcstr__null_basic_string(void** state);
void test_basic_string_find_last_of_subcstr__null_find(void** state);
void test_basic_string_find_last_of_subcstr__non_inited_basic_string(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_not_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_middle_empty_length_0(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_middle_find(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_last_of_subcstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_subcstr__char_empty_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__char_empty_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__char_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_of_subcstr__char_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__char_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__char_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__char_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__char_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__char_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__char_not_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__char_middle_empty(void** state);
void test_basic_string_find_last_of_subcstr__char_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_of_subcstr__char_middle_find(void** state);
void test_basic_string_find_last_of_subcstr__char_middle_not_find(void** state);
void test_basic_string_find_last_of_subcstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_subcstr__cstr_empty_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__cstr_empty_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__cstr_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__cstr_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__cstr_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__cstr_not_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__cstr_middle_empty(void** state);
void test_basic_string_find_last_of_subcstr__cstr_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_of_subcstr__cstr_middle_find(void** state);
void test_basic_string_find_last_of_subcstr__cstr_middle_not_find(void** state);
void test_basic_string_find_last_of_subcstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_subcstr__user_define_empty_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__user_define_empty_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_0(void** state);
void test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__user_define_empty_npos(void** state);
void test_basic_string_find_last_of_subcstr__user_define_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_of_subcstr__user_define_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__user_define_not_find_npos(void** state);
void test_basic_string_find_last_of_subcstr__user_define_middle_empty(void** state);
void test_basic_string_find_last_of_subcstr__user_define_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_of_subcstr__user_define_middle_find(void** state);
void test_basic_string_find_last_of_subcstr__user_define_middle_not_find(void** state);
void test_basic_string_find_last_of_subcstr__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_last_of_subcstr__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_0_n_gt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_last_of_subcstr__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_last_of_subcstr__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_last_of_subcstr__pos_eq_0_n_eq_0(void** state);
/*
 * test basic_string_find_last_not_of
 */
UT_CASE_DECLARATION(basic_string_find_last_not_of)
void test_basic_string_find_last_not_of__null_basic_string(void** state);
void test_basic_string_find_last_not_of__null_find(void** state);
void test_basic_string_find_last_not_of__non_inited_basic_string(void** state);
void test_basic_string_find_last_not_of__non_inited_find(void** state);
void test_basic_string_find_last_not_of__not_same_type(void** state);
void test_basic_string_find_last_not_of__same_npos(void** state);
void test_basic_string_find_last_not_of__same_middle(void** state);
void test_basic_string_find_last_not_of__c_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_not_of__c_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of__c_builtin_empty_npos(void** state);
void test_basic_string_find_last_not_of__c_builtin_find_npos(void** state);
void test_basic_string_find_last_not_of__c_builtin_not_find_npos(void** state);
void test_basic_string_find_last_not_of__c_builtin_middle_empty(void** state);
void test_basic_string_find_last_not_of__c_builtin_middle_find(void** state);
void test_basic_string_find_last_not_of__c_builtin_middle_not_find(void** state);
void test_basic_string_find_last_not_of__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of__char_empty_empty_0(void** state);
void test_basic_string_find_last_not_of__char_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of__char_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of__char_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of__char_empty_npos(void** state);
void test_basic_string_find_last_not_of__char_find_npos(void** state);
void test_basic_string_find_last_not_of__char_not_find_npos(void** state);
void test_basic_string_find_last_not_of__char_middle_empty(void** state);
void test_basic_string_find_last_not_of__char_middle_find(void** state);
void test_basic_string_find_last_not_of__char_middle_not_find(void** state);
void test_basic_string_find_last_not_of__char_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of__cstr_empty_empty_0(void** state);
void test_basic_string_find_last_not_of__cstr_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of__cstr_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of__cstr_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of__cstr_empty_npos(void** state);
void test_basic_string_find_last_not_of__cstr_find_npos(void** state);
void test_basic_string_find_last_not_of__cstr_not_find_npos(void** state);
void test_basic_string_find_last_not_of__cstr_middle_empty(void** state);
void test_basic_string_find_last_not_of__cstr_middle_find(void** state);
void test_basic_string_find_last_not_of__cstr_middle_not_find(void** state);
void test_basic_string_find_last_not_of__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_empty_npos(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_find_npos(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_last_not_of__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of__user_define_empty_empty_0(void** state);
void test_basic_string_find_last_not_of__user_define_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of__user_define_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of__user_define_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of__user_define_empty_npos(void** state);
void test_basic_string_find_last_not_of__user_define_find_npos(void** state);
void test_basic_string_find_last_not_of__user_define_not_find_npos(void** state);
void test_basic_string_find_last_not_of__user_define_middle_empty(void** state);
void test_basic_string_find_last_not_of__user_define_middle_find(void** state);
void test_basic_string_find_last_not_of__user_define_middle_not_find(void** state);
void test_basic_string_find_last_not_of__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_last_not_of__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_last_not_of__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_last_not_of__pos_eq_0_n_gt_size(void** state);
void test_basic_string_find_last_not_of__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_last_not_of__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_last_not_of__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_last_not_of__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_last_not_of__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_last_not_of__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_last_not_of__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_last_not_of__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_last_not_of__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_last_not_of__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_last_not_of__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_last_not_of__pos_eq_0_n_eq_0(void** state);
/*
 * test basic_string_find_last_not_of_cstr
 */
UT_CASE_DECLARATION(basic_string_find_last_not_of_cstr)
void test_basic_string_find_last_not_of_cstr__null_basic_string(void** state);
void test_basic_string_find_last_not_of_cstr__null_find(void** state);
void test_basic_string_find_last_not_of_cstr__non_inited_basic_string(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_not_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_middle_find(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_last_not_of_cstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_cstr__char_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__char_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__char_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__char_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__char_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__char_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__char_not_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__char_middle_empty(void** state);
void test_basic_string_find_last_not_of_cstr__char_middle_find(void** state);
void test_basic_string_find_last_not_of_cstr__char_middle_not_find(void** state);
void test_basic_string_find_last_not_of_cstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_not_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_middle_empty(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_middle_find(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_middle_not_find(void** state);
void test_basic_string_find_last_not_of_cstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_empty_npos(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_not_find_npos(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_middle_empty(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_middle_find(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_middle_not_find(void** state);
void test_basic_string_find_last_not_of_cstr__user_define_middle_not_find_pos(void** state);
/*
 * test basic_string_find_last_not_of_subcstr
 */
UT_CASE_DECLARATION(basic_string_find_last_not_of_subcstr)
void test_basic_string_find_last_not_of_subcstr__null_basic_string(void** state);
void test_basic_string_find_last_not_of_subcstr__null_find(void** state);
void test_basic_string_find_last_not_of_subcstr__non_inited_basic_string(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_not_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_middle_empty(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_middle_empty_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_middle_find(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_middle_not_find(void** state);
void test_basic_string_find_last_not_of_subcstr__c_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_subcstr__char_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__char_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__char_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__char_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__char_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__char_not_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__char_middle_empty(void** state);
void test_basic_string_find_last_not_of_subcstr__char_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__char_middle_find(void** state);
void test_basic_string_find_last_not_of_subcstr__char_middle_not_find(void** state);
void test_basic_string_find_last_not_of_subcstr__char_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_not_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_middle_empty(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_middle_find(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_middle_not_find(void** state);
void test_basic_string_find_last_not_of_subcstr__cstr_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_not_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_empty(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_find(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_not_find(void** state);
void test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_empty_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_empty_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_0_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_0(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_empty_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_non_empty_npos_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_not_find_npos(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_middle_empty(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_middle_non_empty_length_0(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_middle_find(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_middle_not_find(void** state);
void test_basic_string_find_last_not_of_subcstr__user_define_middle_not_find_pos(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_gt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_gt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_gt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_gt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_eq_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_eq_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_eq_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_eq_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_lt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_lt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_lt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_lt_size(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_eq_0(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_eq_0(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_eq_0(void** state);
void test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_eq_0(void** state);
/*
 * test basic_string_begin
 */
UT_CASE_DECLARATION(basic_string_begin)
void test_basic_string_begin__null_basic_string_container(void** state);
void test_basic_string_begin__non_inited_basic_string_container(void** state);
void test_basic_string_begin__empty(void** state);
void test_basic_string_begin__non_empty(void** state);
void test_basic_string_begin__shared(void** state);
/*
 * test basic_string_end
 */
UT_CASE_DECLARATION(basic_string_end)
void test_basic_string_end__null_basic_string_container(void** state);
void test_basic_string_end__non_inited_basic_string_container(void** state);
void test_basic_string_end__empty(void** state);
void test_basic_string_end__non_empty(void** state);
void test_basic_string_end__shared(void** state);
/*
 * test basic_string_clear
 */
UT_CASE_DECLARATION(basic_string_clear)
void test_basic_string_clear__null_basic_string_container(void** state);
void test_basic_string_clear__non_inited_basic_string_container(void** state);
void test_basic_string_clear__empty_basic_string_container(void** state);
void test_basic_string_clear__non_empty_basic_string_container(void** state);
void test_basic_string_clear__shared(void** state);
void test_basic_string_clear__terminator_c(void** state);
void test_basic_string_clear__terminator_cstr(void** state);
void test_basic_string_clear__terminator_cstl(void** state);
void test_basic_string_clear__terminator_user_define(void** state);
/*
 * test basic_string_swap
 */
UT_CASE_DECLARATION(basic_string_swap)
void test_basic_string_swap__null_first(void** state);
void test_basic_string_swap__null_second(void** state);
void test_basic_string_swap__non_inited_first(void** state);
void test_basic_string_swap__non_inited_second(void** state);
void test_basic_string_swap__not_same_type(void** state);
void test_basic_string_swap__basic_string_equal(void** state);
void test_basic_string_swap__0_swap_10(void** state);
void test_basic_string_swap__0_swap_1000(void** state);
void test_basic_string_swap__10_swap_0(void** state);
void test_basic_string_swap__10_swap_10(void** state);
void test_basic_string_swap__10_swap_1000(void** state);
void test_basic_string_swap__1000_swap_0(void** state);
void test_basic_string_swap__1000_swap_10(void** state);
void test_basic_string_swap__1000_swap_1010(void** state);
void test_basic_string_swap__shared(void** state);
/*
 * test basic_string_reserve
 */
UT_CASE_DECLARATION(basic_string_reserve)
void test_basic_string_reserve__null_basic_string_container(void** state);
void test_basic_string_reserve__non_inited(void** state);
void test_basic_string_reserve__max_size(void** state);
void test_basic_string_reserve__shrink(void** state);
void test_basic_string_reserve__not_change(void** state);
void test_basic_string_reserve__expand(void** state);
void test_basic_string_reserve__shared(void** state);
/*
 * test basic_string_assign
 */
UT_CASE_DECLARATION(basic_string_assign)
void test_basic_string_assign__null_dest(void** state);
void test_basic_string_assign__null_src(void** state);
void test_basic_string_assign__non_inited_dest(void** state);
void test_basic_string_assign__non_inited_src(void** state);
void test_basic_string_assign__not_same_type(void** state);
void test_basic_string_assign__same_container(void** state);
void test_basic_string_assign__0_assign_0(void** state);
void test_basic_string_assign__0_assign_10(void** state);
void test_basic_string_assign__0_assign_1000(void** state);
void test_basic_string_assign__10_assign_0(void** state);
void test_basic_string_assign__10_assign_10_basic_string_equal(void** state);
void test_basic_string_assign__10_assign_10_basic_string_not_equal(void** state);
void test_basic_string_assign__10_assign_1000(void** state);
void test_basic_string_assign__1000_assign_0(void** state);
void test_basic_string_assign__1000_assign_10(void** state);
void test_basic_string_assign__1000_assign_1010(void** state);
void test_basic_string_assign__1000_assign_1810(void** state);
void test_basic_string_assign__char(void** state);
void test_basic_string_assign__cstr(void** state);
void test_basic_string_assign__libcstl(void** state);
void test_basic_string_assign__user_define(void** state);
void test_basic_string_assign__same_rep(void** state);
void test_basic_string_assign__shared(void** state);
/*
 * test basic_string_assign_substring
 */
UT_CASE_DECLARATION(basic_string_assign_substring)
void test_basic_string_assign_substring__null_dest(void** state);
void test_basic_string_assign_substring__null_src(void** state);
void test_basic_string_assign_substring__non_inited_dest(void** state);
void test_basic_string_assign_substring__non_inited_src(void** state);
void test_basic_string_assign_substring__not_same_type(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_non_empty(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_length(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_npos(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_empty(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_non_empty(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_length(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_npos(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_end(void** state);
void test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_npos(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_empty(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_non_empty(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_length(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_npos(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_empty(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_non_empty(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_length(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_npos(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_end(void** state);
void test_basic_string_assign_substring__successfully_cstr_src_non_empty_npos(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_begin_non_empty(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_begin_length(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_begin_npos(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_empty(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_non_empty(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_length(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_npos(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_length(void** state);
void test_basic_string_assign_substring__successfully_cstl_builtin_npos(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_begin_empty(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_begin_non_empty(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_begin_length(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_begin_npos(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_middle_empty(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_middle_non_empty(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_middle_length(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_middle_npos(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_end(void** state);
void test_basic_string_assign_substring__successfully_user_define_non_empty_npos(void** state);
void test_basic_string_assign_substring__shared(void** state);
void test_basic_string_assign_substring__same_pbstr(void** state);
void test_basic_string_assign_substring__shared_assign(void** state);
void test_basic_string_assign_substring__less_size(void** state);
void test_basic_string_assign_substring__greater_size(void** state);
void test_basic_string_assign_substring__about_size(void** state);
/*
 * test basic_string_assign_range
 */
UT_CASE_DECLARATION(basic_string_assign_range)
void test_basic_string_assign_range__null_dest(void** state);
void test_basic_string_assign_range__non_inited_dest(void** state);
void test_basic_string_assign_range__invalid_begin_iterator(void** state);
void test_basic_string_assign_range__invalid_end_iterator(void** state);
void test_basic_string_assign_range__invalid_range(void** state);
void test_basic_string_assign_range__not_same_type(void** state);
void test_basic_string_assign_range__successfully_empty_range(void** state);
void test_basic_string_assign_range__successfully_c_builtin(void** state);
void test_basic_string_assign_range__successfully_cstr(void** state);
void test_basic_string_assign_range__successfully_cstl_builtin(void** state);
void test_basic_string_assign_range__successfully_user_define(void** state);
void test_basic_string_assign_range__shared(void** state);
void test_basic_string_assign_range__same_pbstr(void** state);
void test_basic_string_assign_range__other_container(void** state);
/*
 * test basic_string_assign_cstr
 */
UT_CASE_DECLARATION(basic_string_assign_cstr)
void test_basic_string_assign_cstr__null_container(void** state);
void test_basic_string_assign_cstr__non_inited(void** state);
void test_basic_string_assign_cstr__null_valuestring(void** state);
void test_basic_string_assign_cstr__c_builtin_empty(void** state);
void test_basic_string_assign_cstr__c_builtin_non_empty(void** state);
void test_basic_string_assign_cstr__char_empty(void** state);
void test_basic_string_assign_cstr__char_non_empty(void** state);
void test_basic_string_assign_cstr__cstr_empty(void** state);
void test_basic_string_assign_cstr__cstr_init_non_empty(void** state);
void test_basic_string_assign_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_assign_cstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_assign_cstr__user_define_empty(void** state);
void test_basic_string_assign_cstr__user_define_non_empty(void** state);
void test_basic_string_assign_cstr__shared(void** state);
/*
 * test basic_string_assign_subcstr
 */
UT_CASE_DECLARATION(basic_string_assign_subcstr)
void test_basic_string_assign_subcstr__null_container(void** state);
void test_basic_string_assign_subcstr__non_created_container(void** state);
void test_basic_string_assign_subcstr__null_valuestring(void** state);
void test_basic_string_assign_subcstr__c_builtin_empty(void** state);
void test_basic_string_assign_subcstr__c_builtin_non_empty(void** state);
void test_basic_string_assign_subcstr__c_builtin_total(void** state);
void test_basic_string_assign_subcstr__char_empty(void** state);
void test_basic_string_assign_subcstr__char_non_empty(void** state);
void test_basic_string_assign_subcstr__char_total(void** state);
void test_basic_string_assign_subcstr__cstr_empty(void** state);
void test_basic_string_assign_subcstr__cstr_non_empty(void** state);
void test_basic_string_assign_subcstr__cstr_total(void** state);
void test_basic_string_assign_subcstr__libcstl_builtin_empty(void** state);
void test_basic_string_assign_subcstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_assign_subcstr__libcstl_builtin_total(void** state);
void test_basic_string_assign_subcstr__user_define_empty(void** state);
void test_basic_string_assign_subcstr__user_define_non_empty(void** state);
void test_basic_string_assign_subcstr__user_define_total(void** state);
void test_basic_string_assign_subcstr__shared(void** state);
void test_basic_string_assign_subcstr__include_terminator(void** state);
/*
 * test basic_string_append
 */
UT_CASE_DECLARATION(basic_string_append)
void test_basic_string_append__null_dest(void** state);
void test_basic_string_append__null_src(void** state);
void test_basic_string_append__non_inited_dest(void** state);
void test_basic_string_append__non_inited_src(void** state);
void test_basic_string_append__not_same_type(void** state);
void test_basic_string_append__same_container(void** state);
void test_basic_string_append__0_assign_0(void** state);
void test_basic_string_append__0_assign_10(void** state);
void test_basic_string_append__10_assign_0(void** state);
void test_basic_string_append__1000_assign_1810(void** state);
void test_basic_string_append__char(void** state);
void test_basic_string_append__cstr(void** state);
void test_basic_string_append__libcstl(void** state);
void test_basic_string_append__user_define(void** state);
void test_basic_string_append__shared(void** state);
/*
 * test basic_string_append_substring
 */
UT_CASE_DECLARATION(basic_string_append_substring)
void test_basic_string_append_substring__null_dest(void** state);
void test_basic_string_append_substring__null_src(void** state);
void test_basic_string_append_substring__non_inited_dest(void** state);
void test_basic_string_append_substring__non_inited_src(void** state);
void test_basic_string_append_substring__not_same_type(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_non_empty(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_length(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_npos(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_empty(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_non_empty(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_length(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_npos(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_end(void** state);
void test_basic_string_append_substring__successfully_c_builtin_src_non_empty_npos(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_empty(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_non_empty(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_length(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_npos(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_empty(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_non_empty(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_length(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_npos(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_end(void** state);
void test_basic_string_append_substring__successfully_cstr_src_non_empty_npos(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_non_empty_begin_non_empty(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_non_empty_begin_length(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_non_empty_begin_npos(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_empty(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_non_empty(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_length(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_npos(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_length(void** state);
void test_basic_string_append_substring__successfully_cstl_builtin_npos(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_begin_empty(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_begin_non_empty(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_begin_length(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_begin_npos(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_middle_empty(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_middle_non_empty(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_middle_length(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_middle_npos(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_end(void** state);
void test_basic_string_append_substring__successfully_user_define_non_empty_npos(void** state);
void test_basic_string_append_substring__shared(void** state);
void test_basic_string_append_substring__gt_size(void** state);
void test_basic_string_append_substring__eq_size(void** state);
void test_basic_string_append_substring__lt_size(void** state);
/*
 * test basic_string_append_range
 */
UT_CASE_DECLARATION(basic_string_append_range)
void test_basic_string_append_range__null_dest(void** state);
void test_basic_string_append_range__non_inited_dest(void** state);
void test_basic_string_append_range__invalid_begin_iterator(void** state);
void test_basic_string_append_range__invalid_end_iterator(void** state);
void test_basic_string_append_range__invalid_range(void** state);
void test_basic_string_append_range__not_same_type(void** state);
void test_basic_string_append_range__successfully_empty_range(void** state);
void test_basic_string_append_range__successfully_c_builtin(void** state);
void test_basic_string_append_range__successfully_cstr(void** state);
void test_basic_string_append_range__successfully_cstl_builtin(void** state);
void test_basic_string_append_range__successfully_user_define(void** state);
/*void test_basic_string_append_range__same_container(void** state);*/
void test_basic_string_append_range__shared(void** state);
/*
 * test basic_string_append_cstr
 */
UT_CASE_DECLARATION(basic_string_append_cstr)
void test_basic_string_append_cstr__null_container(void** state);
void test_basic_string_append_cstr__non_inited(void** state);
void test_basic_string_append_cstr__null_valuestring(void** state);
void test_basic_string_append_cstr__c_builtin_empty(void** state);
void test_basic_string_append_cstr__c_builtin_non_empty(void** state);
void test_basic_string_append_cstr__char_empty(void** state);
void test_basic_string_append_cstr__char_non_empty(void** state);
void test_basic_string_append_cstr__cstr_empty(void** state);
void test_basic_string_append_cstr__cstr_init_non_empty(void** state);
void test_basic_string_append_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_append_cstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_append_cstr__user_define_empty(void** state);
void test_basic_string_append_cstr__user_define_non_empty(void** state);
void test_basic_string_append_cstr__shared(void** state);
/*
 * test basic_string_append_subcstr
 */
UT_CASE_DECLARATION(basic_string_append_subcstr)
void test_basic_string_append_subcstr__null_container(void** state);
void test_basic_string_append_subcstr__non_created_container(void** state);
void test_basic_string_append_subcstr__null_valuestring(void** state);
void test_basic_string_append_subcstr__c_builtin_empty(void** state);
void test_basic_string_append_subcstr__c_builtin_non_empty(void** state);
void test_basic_string_append_subcstr__c_builtin_total(void** state);
void test_basic_string_append_subcstr__char_empty(void** state);
void test_basic_string_append_subcstr__char_non_empty(void** state);
void test_basic_string_append_subcstr__char_total(void** state);
void test_basic_string_append_subcstr__cstr_empty(void** state);
void test_basic_string_append_subcstr__cstr_non_empty(void** state);
void test_basic_string_append_subcstr__cstr_total(void** state);
void test_basic_string_append_subcstr__libcstl_builtin_empty(void** state);
void test_basic_string_append_subcstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_append_subcstr__libcstl_builtin_total(void** state);
void test_basic_string_append_subcstr__user_define_empty(void** state);
void test_basic_string_append_subcstr__user_define_non_empty(void** state);
void test_basic_string_append_subcstr__user_define_total(void** state);
void test_basic_string_append_subcstr__shared(void** state);
/*
 * test basic_string_insert_string
 */
UT_CASE_DECLARATION(basic_string_insert_string)
void test_basic_string_insert_string__null_dest(void** state);
void test_basic_string_insert_string__null_insert(void** state);
void test_basic_string_insert_string__non_inited_dest(void** state);
void test_basic_string_insert_string__non_inited_insert(void** state);
void test_basic_string_insert_string__not_same_type(void** state);
void test_basic_string_insert_string__same_container(void** state);
void test_basic_string_insert_string__invalid_pos(void** state);
void test_basic_string_insert_string__c_builtin_begin_insert_empty(void** state);
void test_basic_string_insert_string__c_builtin_middle_insert_non_empty(void** state);
void test_basic_string_insert_string__char_middle_insert_empty(void** state);
void test_basic_string_insert_string__char_begin_insert_non_empty(void** state);
void test_basic_string_insert_string__cstr_middle_insert_empty(void** state);
void test_basic_string_insert_string__cstr_begin_insert_non_empty(void** state);
void test_basic_string_insert_string__libcstl_builtin_middle_insert_empty(void** state);
void test_basic_string_insert_string__libcstl_builtin_begin_insert_non_empty(void** state);
void test_basic_string_insert_string__user_define_middle_insert_empty(void** state);
void test_basic_string_insert_string__user_define_begin_insert_non_empty(void** state);
/*
 * test basic_string_insert_substring
 */
UT_CASE_DECLARATION(basic_string_insert_substring)
void test_basic_string_insert_substring__null_dest(void** state);
void test_basic_string_insert_substring__null_insert(void** state);
void test_basic_string_insert_substring__non_inited_dest(void** state);
void test_basic_string_insert_substring__non_inited_insert(void** state);
void test_basic_string_insert_substring__not_same_type(void** state);
void test_basic_string_insert_substring__same_container(void** state);
void test_basic_string_insert_substring__invalid_pos(void** state);
void test_basic_string_insert_substring__invalid_startpos(void** state);
void test_basic_string_insert_substring__c_builtin_begin_insert_empty(void** state);
void test_basic_string_insert_substring__c_builtin_middle_insert_non_empty(void** state);
void test_basic_string_insert_substring__char_middle_insert_empty(void** state);
void test_basic_string_insert_substring__char_begin_insert_non_empty(void** state);
void test_basic_string_insert_substring__cstr_middle_insert_empty(void** state);
void test_basic_string_insert_substring__cstr_begin_insert_non_empty(void** state);
void test_basic_string_insert_substring__libcstl_builtin_middle_insert_empty(void** state);
void test_basic_string_insert_substring__libcstl_builtin_begin_insert_non_empty(void** state);
void test_basic_string_insert_substring__user_define_middle_insert_empty(void** state);
void test_basic_string_insert_substring__user_define_begin_insert_non_empty(void** state);
void test_basic_string_insert_substring__end(void** state);
/*
 * test basic_string_insert_range
 */
UT_CASE_DECLARATION(basic_string_insert_range)
void test_basic_string_insert_range__null_basic_string(void** state);
void test_basic_string_insert_range__non_inited_basic_string(void** state);
void test_basic_string_insert_range__invalid_pos(void** state);
void test_basic_string_insert_range__invalid_begin(void** state);
void test_basic_string_insert_range__invalid_end(void** state);
void test_basic_string_insert_range__invalid_range(void** state);
void test_basic_string_insert_range__not_same_type(void** state);
/*void test_basic_string_insert_range__range_belong_to_dest(void** state);*/
void test_basic_string_insert_range__c_builtin_empty_insert_empty(void** state);
void test_basic_string_insert_range__c_builtin_empty_insert_non_empty(void** state);
void test_basic_string_insert_range__c_builtin_non_empty_insert_begin_empty(void** state);
void test_basic_string_insert_range__c_builtin_non_empty_insert_middle_empty(void** state);
void test_basic_string_insert_range__c_builtin_non_empty_insert_end_empty(void** state);
void test_basic_string_insert_range__c_builtin_non_empty_insert_begin_non_empty(void** state);
void test_basic_string_insert_range__c_builtin_non_empty_insert_middle_non_empty(void** state);
void test_basic_string_insert_range__c_builtin_non_empty_insert_end_non_empty(void** state);
void test_basic_string_insert_range__char(void** state);
void test_basic_string_insert_range__cstr(void** state);
void test_basic_string_insert_range__libcstl_builtin(void** state);
void test_basic_string_insert_range__user_define(void** state);
/*
 * test basic_string_insert_cstr
 */
UT_CASE_DECLARATION(basic_string_insert_cstr)
void test_basic_string_insert_cstr__null_container(void** state);
void test_basic_string_insert_cstr__non_inited(void** state);
void test_basic_string_insert_cstr__null_valuestring(void** state);
void test_basic_string_insert_cstr__invalid_pos(void** state);
void test_basic_string_insert_cstr__c_builtin_empty(void** state);
void test_basic_string_insert_cstr__c_builtin_non_empty(void** state);
void test_basic_string_insert_cstr__char_empty(void** state);
void test_basic_string_insert_cstr__char_non_empty(void** state);
void test_basic_string_insert_cstr__cstr_empty(void** state);
void test_basic_string_insert_cstr__cstr_init_non_empty(void** state);
void test_basic_string_insert_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_insert_cstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_insert_cstr__user_define_empty(void** state);
void test_basic_string_insert_cstr__user_define_non_empty(void** state);
/*
 * test basic_string_insert_subcstr
 */
UT_CASE_DECLARATION(basic_string_insert_subcstr)
void test_basic_string_insert_subcstr__null_container(void** state);
void test_basic_string_insert_subcstr__non_created_container(void** state);
void test_basic_string_insert_subcstr__null_valuestring(void** state);
void test_basic_string_insert_subcstr__invalid_pos(void** state);
void test_basic_string_insert_subcstr__c_builtin_empty(void** state);
void test_basic_string_insert_subcstr__c_builtin_non_empty(void** state);
void test_basic_string_insert_subcstr__c_builtin_total(void** state);
void test_basic_string_insert_subcstr__char_empty(void** state);
void test_basic_string_insert_subcstr__char_non_empty(void** state);
void test_basic_string_insert_subcstr__char_total(void** state);
void test_basic_string_insert_subcstr__cstr_empty(void** state);
void test_basic_string_insert_subcstr__cstr_non_empty(void** state);
void test_basic_string_insert_subcstr__cstr_total(void** state);
void test_basic_string_insert_subcstr__libcstl_builtin_empty(void** state);
void test_basic_string_insert_subcstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_insert_subcstr__libcstl_builtin_total(void** state);
void test_basic_string_insert_subcstr__user_define_empty(void** state);
void test_basic_string_insert_subcstr__user_define_non_empty(void** state);
void test_basic_string_insert_subcstr__user_define_total(void** state);
/*
 * test basic_string_erase
 */
UT_CASE_DECLARATION(basic_string_erase)
void test_basic_string_erase__null_basic_string(void** state);
void test_basic_string_erase__non_inited_basic_string(void** state);
void test_basic_string_erase__invalid_pos(void** state);
void test_basic_string_erase__empty(void** state);
void test_basic_string_erase__c_builtin_begin(void** state);
void test_basic_string_erase__c_builtin_middle(void** state);
void test_basic_string_erase__c_builtin_last(void** state);
void test_basic_string_erase__char(void** state);
void test_basic_string_erase__cstr(void** state);
void test_basic_string_erase__libcstl_builtin(void** state);
void test_basic_string_erase__user_define(void** state);
/*
 * test basic_string_erase_range
 */
UT_CASE_DECLARATION(basic_string_erase_range)
void test_basic_string_erase_range__null_basic_string(void** state);
void test_basic_string_erase_range__non_inited_basic_string(void** state);
void test_basic_string_erase_range__invalid_begin(void** state);
void test_basic_string_erase_range__invalid_end(void** state);
void test_basic_string_erase_range__invalid_range(void** state);
void test_basic_string_erase_range__empty(void** state);
void test_basic_string_erase_range__c_builtin_begin(void** state);
void test_basic_string_erase_range__c_builtin_middle(void** state);
void test_basic_string_erase_range__c_builtin_end(void** state);
void test_basic_string_erase_range__c_builtin_all(void** state);
void test_basic_string_erase_range__c_builtin_erase_empty(void** state);
void test_basic_string_erase_range__char(void** state);
void test_basic_string_erase_range__cstr(void** state);
void test_basic_string_erase_range__libcstl_builtin(void** state);
void test_basic_string_erase_range__user_define(void** state);
/*
 * test basic_string_erase_substring
 */
UT_CASE_DECLARATION(basic_string_erase_substring)
void test_basic_string_erase_substring__null_basic_string(void** state);
void test_basic_string_erase_substring__non_inited_basic_string(void** state);
void test_basic_string_erase_substring__invalid_pos(void** state);
void test_basic_string_erase_substring__c_builtin_begin(void** state);
void test_basic_string_erase_substring__c_builtin_middle(void** state);
void test_basic_string_erase_substring__c_builtin_end(void** state);
void test_basic_string_erase_substring__c_builtin_all(void** state);
void test_basic_string_erase_substring__c_builtin_erase_empty(void** state);
void test_basic_string_erase_substring__char(void** state);
void test_basic_string_erase_substring__cstr(void** state);
void test_basic_string_erase_substring__libcstr_builtin(void** state);
void test_basic_string_erase_substring__user_define(void** state);
void test_basic_string_erase_substring__shared(void** state);
void test_basic_string_erase_substring__end(void** state);
/*
 * test basic_string_replace
 */
UT_CASE_DECLARATION(basic_string_replace)
void test_basic_string_replace__null_dest(void** state);
void test_basic_string_replace__null_replace(void** state);
void test_basic_string_replace__non_inited_dest(void** state);
void test_basic_string_replace__non_inited_replace(void** state);
void test_basic_string_replace__not_same_type(void** state);
void test_basic_string_replace__same_container(void** state);
void test_basic_string_replace__invalid_pos(void** state);
void test_basic_string_replace__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_replace__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_replace__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_replace__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_replace__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_replace__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_replace__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_replace__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_replace__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_replace__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_replace__c_builtin_all_replace_empty(void** state);
void test_basic_string_replace__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_replace__char(void** state);
void test_basic_string_replace__cstr(void** state);
void test_basic_string_replace__libcstl_builtin(void** state);
void test_basic_string_replace__user_define(void** state);
void test_basic_string_replace__shared(void** state);
/*
 * test basic_string_replace_substring
 */
UT_CASE_DECLARATION(basic_string_replace_substring)
void test_basic_string_replace_substring__null_dest(void** state);
void test_basic_string_replace_substring__null_replace(void** state);
void test_basic_string_replace_substring__non_inited_dest(void** state);
void test_basic_string_replace_substring__non_inited_replace(void** state);
void test_basic_string_replace_substring__not_same_type(void** state);
void test_basic_string_replace_substring__invalid_pos(void** state);
void test_basic_string_replace_substring__invalid_position(void** state);
void test_basic_string_replace_substring__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_replace_substring__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_replace_substring__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_replace_substring__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_substring__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_replace_substring__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_replace_substring__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_replace_substring__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_substring__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_replace_substring__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_substring__c_builtin_all_replace_empty(void** state);
void test_basic_string_replace_substring__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_replace_substring__char(void** state);
void test_basic_string_replace_substring__cstr(void** state);
void test_basic_string_replace_substring__libcstl_builtin(void** state);
void test_basic_string_replace_substring__user_define(void** state);
void test_basic_string_replace_substring__shared(void** state);
void test_basic_string_replace_substring__check(void** state);
void test_basic_string_replace_substring__terminator_c(void** state);
void test_basic_string_replace_substring__terminator_cstr(void** state);
void test_basic_string_replace_substring__terminator_cstl(void** state);
void test_basic_string_replace_substring__terminator_user_define(void** state);
void test_basic_string_replace_substring__same_container(void** state);
void test_basic_string_replace_substring__same_container_1(void** state);
void test_basic_string_replace_substring__same_container_2(void** state);
void test_basic_string_replace_substring__same_container_3(void** state);
void test_basic_string_replace_substring__same_container_4(void** state);
void test_basic_string_replace_substring__same_container_5(void** state);
void test_basic_string_replace_substring__same_container_6(void** state);
void test_basic_string_replace_substring__same_container_7(void** state);
void test_basic_string_replace_substring__same_container_8(void** state);
void test_basic_string_replace_substring__same_container_9(void** state);
void test_basic_string_replace_substring__same_container_10(void** state);
void test_basic_string_replace_substring__same_container_11(void** state);
void test_basic_string_replace_substring__same_container_12(void** state);
void test_basic_string_replace_substring__same_container_13(void** state);
void test_basic_string_replace_substring__same_container_14(void** state);
void test_basic_string_replace_substring__same_container_15(void** state);
void test_basic_string_replace_substring__same_container_16(void** state);
/*
 * test basic_string_replace_cstr
 */
UT_CASE_DECLARATION(basic_string_replace_cstr)
void test_basic_string_replace_cstr__null_dest(void** state);
void test_basic_string_replace_cstr__null_replace(void** state);
void test_basic_string_replace_cstr__non_inited_dest(void** state);
void test_basic_string_replace_cstr__invalid_pos(void** state);
void test_basic_string_replace_cstr__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_all_replace_empty(void** state);
void test_basic_string_replace_cstr__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_replace_cstr__char(void** state);
void test_basic_string_replace_cstr__cstr(void** state);
void test_basic_string_replace_cstr__libcstl_builtin(void** state);
void test_basic_string_replace_cstr__user_define(void** state);
/*
 * test basic_string_replace_subcstr
 */
UT_CASE_DECLARATION(basic_string_replace_subcstr)
void test_basic_string_replace_subcstr__null_dest(void** state);
void test_basic_string_replace_subcstr__null_replace(void** state);
void test_basic_string_replace_subcstr__non_inited_dest(void** state);
void test_basic_string_replace_subcstr__invalid_pos(void** state);
void test_basic_string_replace_subcstr__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_all_replace_empty(void** state);
void test_basic_string_replace_subcstr__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_replace_subcstr__char(void** state);
void test_basic_string_replace_subcstr__cstr(void** state);
void test_basic_string_replace_subcstr__libcstl_builtin(void** state);
void test_basic_string_replace_subcstr__user_define(void** state);
/*
 * test basic_string_range_replace
 */
UT_CASE_DECLARATION(basic_string_range_replace)
void test_basic_string_range_replace__null_dest(void** state);
void test_basic_string_range_replace__null_replace(void** state);
void test_basic_string_range_replace__non_inited_dest(void** state);
void test_basic_string_range_replace__non_inited_replace(void** state);
void test_basic_string_range_replace__not_same_type(void** state);
void test_basic_string_range_replace__same_container(void** state);
void test_basic_string_range_replace__invalid_range(void** state);
void test_basic_string_range_replace__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_range_replace__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_range_replace__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_range_replace__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_range_replace__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_range_replace__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_range_replace__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_range_replace__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace__c_builtin_all_replace_empty(void** state);
void test_basic_string_range_replace__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_range_replace__char(void** state);
void test_basic_string_range_replace__cstr(void** state);
void test_basic_string_range_replace__libcstl_builtin(void** state);
void test_basic_string_range_replace__user_define(void** state);
/*
 * test basic_string_range_replace_substring
 */
UT_CASE_DECLARATION(basic_string_range_replace_substring)
void test_basic_string_range_replace_substring__null_dest(void** state);
void test_basic_string_range_replace_substring__null_replace(void** state);
void test_basic_string_range_replace_substring__non_inited_dest(void** state);
void test_basic_string_range_replace_substring__non_inited_replace(void** state);
void test_basic_string_range_replace_substring__not_same_type(void** state);
void test_basic_string_range_replace_substring__same_container(void** state);
void test_basic_string_range_replace_substring__invalid_range(void** state);
void test_basic_string_range_replace_substring__invalid_position(void** state);
void test_basic_string_range_replace_substring__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_all_replace_empty(void** state);
void test_basic_string_range_replace_substring__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_range_replace_substring__char(void** state);
void test_basic_string_range_replace_substring__cstr(void** state);
void test_basic_string_range_replace_substring__libcstl_builtin(void** state);
void test_basic_string_range_replace_substring__user_define(void** state);
/*
 * test basic_string_range_replace_cstr
 */
UT_CASE_DECLARATION(basic_string_range_replace_cstr)
void test_basic_string_range_replace_cstr__null_dest(void** state);
void test_basic_string_range_replace_cstr__null_replace(void** state);
void test_basic_string_range_replace_cstr__non_inited_dest(void** state);
void test_basic_string_range_replace_cstr__invalid_range(void** state);
void test_basic_string_range_replace_cstr__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_all_replace_empty(void** state);
void test_basic_string_range_replace_cstr__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_range_replace_cstr__char(void** state);
void test_basic_string_range_replace_cstr__cstr(void** state);
void test_basic_string_range_replace_cstr__libcstl_builtin(void** state);
void test_basic_string_range_replace_cstr__user_define(void** state);
/*
 * test basic_string_range_replace_subcstr
 */
UT_CASE_DECLARATION(basic_string_range_replace_subcstr)
void test_basic_string_range_replace_subcstr__null_dest(void** state);
void test_basic_string_range_replace_subcstr__null_replace(void** state);
void test_basic_string_range_replace_subcstr__non_inited_dest(void** state);
void test_basic_string_range_replace_subcstr__invalid_range(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_all_replace_empty(void** state);
void test_basic_string_range_replace_subcstr__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_range_replace_subcstr__char(void** state);
void test_basic_string_range_replace_subcstr__cstr(void** state);
void test_basic_string_range_replace_subcstr__libcstl_builtin(void** state);
void test_basic_string_range_replace_subcstr__user_define(void** state);
/*
 * test basic_string_replace_range
 */
UT_CASE_DECLARATION(basic_string_replace_range)
void test_basic_string_replace_range__null_dest(void** state);
void test_basic_string_replace_range__non_inited_dest(void** state);
void test_basic_string_replace_range__not_same_type(void** state);
void test_basic_string_replace_range__same_container(void** state);
void test_basic_string_replace_range__invalid_range(void** state);
void test_basic_string_replace_range__invalid_replace_range(void** state);
void test_basic_string_replace_range__c_builtin_begin_empty_replace_empty(void** state);
void test_basic_string_replace_range__c_builtin_begin_empty_replace_non_empty(void** state);
void test_basic_string_replace_range__c_builtin_begin_non_empty_replace_empty(void** state);
void test_basic_string_replace_range__c_builtin_begin_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_range__c_builtin_middle_empty_replace_empty(void** state);
void test_basic_string_replace_range__c_builtin_middle_empty_replace_non_empty(void** state);
void test_basic_string_replace_range__c_builtin_middle_non_empty_replace_empty(void** state);
void test_basic_string_replace_range__c_builtin_middle_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_range__c_builtin_end_non_empty_replace_empty(void** state);
void test_basic_string_replace_range__c_builtin_end_non_empty_replace_non_empty(void** state);
void test_basic_string_replace_range__c_builtin_all_replace_empty(void** state);
void test_basic_string_replace_range__c_builtin_all_replace_non_empty(void** state);
void test_basic_string_replace_range__char(void** state);
void test_basic_string_replace_range__cstr(void** state);
void test_basic_string_replace_range__libcstl_builtin(void** state);
void test_basic_string_replace_range__user_define(void** state);
/*
 * test basic_string_resize
 */
UT_CASE_DECLARATION(basic_string_resize)
void test_basic_string_resize__null(void** state);
void test_basic_string_resize__non_inited(void** state);
void test_basic_string_resize__greater_max_size(void** state);
void test_basic_string_resize__0_resize_0(void** state);
void test_basic_string_resize__0_resize_5(void** state);
void test_basic_string_resize__10_resize_0(void** state);
void test_basic_string_resize__10_resize_5(void** state);
void test_basic_string_resize__10_resize_10(void** state);
void test_basic_string_resize__10_resize_110(void** state);
void test_basic_string_resize__cstr(void** state);
void test_basic_string_resize__libcstl(void** state);
void test_basic_string_resize__user_define(void** state);
void test_basic_string_resize__shared(void** state);

#define UT_CSTL_BASIC_STRING_CASE\
    UT_SUIT_BEGIN(cstl_basic_string, test_basic_string_init__null_basic_string_container),\
    UT_CASE(test_basic_string_init__non_created),\
    UT_CASE(test_basic_string_init__successfully_c_builtin),\
    UT_CASE(test_basic_string_init__successfully_cstl_builtin),\
    UT_CASE(test_basic_string_init__successfully_cstr),\
    UT_CASE(test_basic_string_init__successfully_user_defined),\
    UT_CASE_BEGIN(basic_string_size, test_basic_string_size__null_basic_string_container),\
    UT_CASE(test_basic_string_size__non_inited),\
    UT_CASE(test_basic_string_size__successfully_empty),\
    UT_CASE(test_basic_string_size__successfully_non_empty),\
    UT_CASE_BEGIN(basic_string_length, test_basic_string_length__null_basic_string_container),\
    UT_CASE(test_basic_string_length__non_inited),\
    UT_CASE(test_basic_string_length__successfully_empty),\
    UT_CASE(test_basic_string_length__successfully_non_empty),\
    UT_CASE_BEGIN(basic_string_capacity, test_basic_string_capacity__null_basic_string_container),\
    UT_CASE(test_basic_string_capacity__non_inited),\
    UT_CASE(test_basic_string_capacity__successfully_empty),\
    UT_CASE(test_basic_string_capacity__successfully_little),\
    UT_CASE(test_basic_string_capacity__successfully_huge),\
    UT_CASE_BEGIN(basic_string_at, test_basic_string_at__null_basic_string_container),\
    UT_CASE(test_basic_string_at__non_inited_basic_string_container),\
    UT_CASE(test_basic_string_at__invalid_subscript_empty),\
    UT_CASE(test_basic_string_at__invalid_subscript_end),\
    UT_CASE(test_basic_string_at__invalid_subscript),\
    UT_CASE(test_basic_string_at__c_builtin),\
    UT_CASE(test_basic_string_at__cstl),\
    UT_CASE(test_basic_string_at__user_define),\
    UT_CASE(test_basic_string_at__successfully),\
    UT_CASE(test_basic_string_at__successfully_cstr),\
    UT_CASE(test_basic_string_at__sharable),\
    UT_CASE_BEGIN(basic_string_init_copy, test_basic_string_init_copy__null_dest),\
    UT_CASE(test_basic_string_init_copy__null_src),\
    UT_CASE(test_basic_string_init_copy__non_create_dest),\
    UT_CASE(test_basic_string_init_copy__non_inited_src),\
    UT_CASE(test_basic_string_init_copy__not_same_type),\
    UT_CASE(test_basic_string_init_copy__successfully_c_builtin_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_c_builtin_little),\
    UT_CASE(test_basic_string_init_copy__successfully_c_builtin_huge),\
    UT_CASE(test_basic_string_init_copy__successfully_cstr_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_cstr_little),\
    UT_CASE(test_basic_string_init_copy__successfully_cstr_huge),\
    UT_CASE(test_basic_string_init_copy__successfully_cstl_builtin_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_cstl_builtin_little),\
    UT_CASE(test_basic_string_init_copy__successfully_cstl_builtin_huge),\
    UT_CASE(test_basic_string_init_copy__successfully_user_define_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_user_define_little),\
    UT_CASE(test_basic_string_init_copy__successfully_user_define_huge),\
    UT_CASE(test_basic_string_init_copy__multi_shared),\
    UT_CASE_BEGIN(basic_string_max_size, test_basic_string_max_size__null_basic_string_container),\
    UT_CASE(test_basic_string_max_size__non_created),\
    UT_CASE(test_basic_string_max_size__successfully),\
    UT_CASE_BEGIN(basic_string_init_subcstr, test_basic_string_init_subcstr__null_container),\
    UT_CASE(test_basic_string_init_subcstr__non_created_container),\
    UT_CASE(test_basic_string_init_subcstr__null_valuestring),\
    UT_CASE(test_basic_string_init_subcstr__length_ge_max_size),\
    UT_CASE(test_basic_string_init_subcstr__c_builtin_init_empty),\
    UT_CASE(test_basic_string_init_subcstr__c_builtin_init_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__c_builtin_init_total),\
    UT_CASE(test_basic_string_init_subcstr__char_init_empty),\
    UT_CASE(test_basic_string_init_subcstr__char_init_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__char_init_total),\
    UT_CASE(test_basic_string_init_subcstr__cstr_init_empty),\
    UT_CASE(test_basic_string_init_subcstr__cstr_init_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__cstr_init_total),\
    UT_CASE(test_basic_string_init_subcstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_init_subcstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__libcstl_builtin_total),\
    UT_CASE(test_basic_string_init_subcstr__user_define_empty),\
    UT_CASE(test_basic_string_init_subcstr__user_define_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__user_define_total),\
    UT_CASE(test_basic_string_init_subcstr__terminator_c),\
    UT_CASE(test_basic_string_init_subcstr__terminator_cstr),\
    UT_CASE(test_basic_string_init_subcstr__terminator_libcstl),\
    UT_CASE(test_basic_string_init_subcstr__terminator_user_define),\
    UT_CASE(test_basic_string_init_subcstr__memleak),\
    UT_CASE_BEGIN(basic_string_init_cstr, test_basic_string_init_cstr__null_container),\
    UT_CASE(test_basic_string_init_cstr__non_created_container),\
    UT_CASE(test_basic_string_init_cstr__null_valuestring),\
    UT_CASE(test_basic_string_init_cstr__c_builtin_init_empty),\
    UT_CASE(test_basic_string_init_cstr__c_builtin_init_non_empty),\
    UT_CASE(test_basic_string_init_cstr__char_init_empty),\
    UT_CASE(test_basic_string_init_cstr__char_init_non_empty),\
    UT_CASE(test_basic_string_init_cstr__cstr_init_empty),\
    UT_CASE(test_basic_string_init_cstr__cstr_init_non_empty),\
    UT_CASE(test_basic_string_init_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_init_cstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_init_cstr__user_define_empty),\
    UT_CASE(test_basic_string_init_cstr__user_define_non_empty),\
    UT_CASE_BEGIN(basic_string_reserve, test_basic_string_reserve__null_basic_string_container),\
    UT_CASE(test_basic_string_reserve__non_inited),\
    UT_CASE(test_basic_string_reserve__max_size),\
    UT_CASE(test_basic_string_reserve__shrink),\
    UT_CASE(test_basic_string_reserve__not_change),\
    UT_CASE(test_basic_string_reserve__expand),\
    UT_CASE(test_basic_string_reserve__shared),\
    UT_CASE_BEGIN(basic_string_init_copy_substring, test_basic_string_init_copy_substring__null_dest),\
    UT_CASE(test_basic_string_init_copy_substring__null_src),\
    UT_CASE(test_basic_string_init_copy_substring__non_create_dest),\
    UT_CASE(test_basic_string_init_copy_substring__non_inited_src),\
    UT_CASE(test_basic_string_init_copy_substring__not_same_type),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_end),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_end),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_end),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_npos),\
    UT_CASE(test_basic_string_init_copy_substring__check),\
    UT_CASE(test_basic_string_init_copy_substring__terminator_c),\
    UT_CASE(test_basic_string_init_copy_substring__terminator_cstr),\
    UT_CASE(test_basic_string_init_copy_substring__terminator_libcstl),\
    UT_CASE(test_basic_string_init_copy_substring__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_begin, test_basic_string_begin__null_basic_string_container),\
    UT_CASE(test_basic_string_begin__non_inited_basic_string_container),\
    UT_CASE(test_basic_string_begin__empty),\
    UT_CASE(test_basic_string_begin__non_empty),\
    UT_CASE(test_basic_string_begin__shared),\
    UT_CASE_BEGIN(basic_string_end, test_basic_string_end__null_basic_string_container),\
    UT_CASE(test_basic_string_end__non_inited_basic_string_container),\
    UT_CASE(test_basic_string_end__empty),\
    UT_CASE(test_basic_string_end__non_empty),\
    UT_CASE(test_basic_string_end__shared),\
    UT_CASE_BEGIN(basic_string_init_copy_range, test_basic_string_init_copy_range__null_dest),\
    UT_CASE(test_basic_string_init_copy_range__invalid_begin_iterator),\
    UT_CASE(test_basic_string_init_copy_range__invalid_end_iterator),\
    UT_CASE(test_basic_string_init_copy_range__invalid_range),\
    UT_CASE(test_basic_string_init_copy_range__not_same_type),\
    UT_CASE(test_basic_string_init_copy_range__successfully_empty_range),\
    UT_CASE(test_basic_string_init_copy_range__successfully_c_builtin),\
    UT_CASE(test_basic_string_init_copy_range__successfully_cstr),\
    UT_CASE(test_basic_string_init_copy_range__successfully_cstl_builtin),\
    UT_CASE(test_basic_string_init_copy_range__successfully_user_define),\
    UT_CASE(test_basic_string_init_copy_range__terminator_c),\
    UT_CASE(test_basic_string_init_copy_range__terminator_cstr),\
    UT_CASE(test_basic_string_init_copy_range__terminator_libcstl),\
    UT_CASE(test_basic_string_init_copy_range__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_destroy, test_basic_string_destroy__null_basic_string_container),\
    UT_CASE(test_basic_string_destroy__non_created),\
    UT_CASE(test_basic_string_destroy__created_non_inited),\
    UT_CASE(test_basic_string_destroy__inited_empty),\
    UT_CASE(test_basic_string_destroy__inited_non_empty),\
    UT_CASE(test_basic_string_destroy__shared),\
    UT_CASE_BEGIN(basic_string_c_str, test_basic_string_c_str__null_container),\
    UT_CASE(test_basic_string_c_str__non_inited_container),\
    UT_CASE(test_basic_string_c_str__empty),\
    UT_CASE(test_basic_string_c_str__non_empty),\
    UT_CASE_BEGIN(basic_string_data, test_basic_string_data__null_container),\
    UT_CASE(test_basic_string_data__non_inited_container),\
    UT_CASE(test_basic_string_data__empty),\
    UT_CASE(test_basic_string_data__non_empty),\
    UT_CASE(test_basic_string_data__shared),\
    UT_CASE_BEGIN(basic_string_empty, test_basic_string_empty__null_basic_string_container),\
    UT_CASE(test_basic_string_empty__non_inited),\
    UT_CASE(test_basic_string_empty__successfully_empty),\
    UT_CASE(test_basic_string_empty__successfully_non_empty),\
    UT_CASE_BEGIN(basic_string_copy, test_basic_string_copy__null_container),\
    UT_CASE(test_basic_string_copy__non_inited_container),\
    UT_CASE(test_basic_string_copy__null_buffer),\
    UT_CASE(test_basic_string_copy__invalid_position),\
    UT_CASE(test_basic_string_copy__begin_empty),\
    UT_CASE(test_basic_string_copy__begin_non_empty),\
    UT_CASE(test_basic_string_copy__begin_length),\
    UT_CASE(test_basic_string_copy__begin_npos),\
    UT_CASE(test_basic_string_copy__middle_empty),\
    UT_CASE(test_basic_string_copy__middle_non_empty),\
    UT_CASE(test_basic_string_copy__middle_length),\
    UT_CASE(test_basic_string_copy__middle_npos),\
    UT_CASE(test_basic_string_copy__end),\
    UT_CASE(test_basic_string_copy__npos),\
    UT_CASE(test_basic_string_copy__shared),\
    UT_CASE(test_basic_string_copy__terminator_c),\
    UT_CASE(test_basic_string_copy__terminator_cstr),\
    UT_CASE(test_basic_string_copy__terminator_cstl),\
    UT_CASE(test_basic_string_copy__terminator_cstl_2),\
    UT_CASE(test_basic_string_copy__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_compare_substring_substring, test_basic_string_compare_substring_substring__null_first),\
    UT_CASE(test_basic_string_compare_substring_substring__null_second),\
    UT_CASE(test_basic_string_compare_substring_substring__non_inited_first),\
    UT_CASE(test_basic_string_compare_substring_substring__non_inited_second),\
    UT_CASE(test_basic_string_compare_substring_substring__invalid_first_pos),\
    UT_CASE(test_basic_string_compare_substring_substring__invalid_second_pos),\
    UT_CASE(test_basic_string_compare_substring_substring__not_same_type),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__c_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__char_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__char_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__char_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__char_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__char_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__char_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__char_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__char_all_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__char_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__char_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__char_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__char_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__char_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_all_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__cstr_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__libcstl_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_all_equal),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__user_define_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_substring__shared),\
    UT_CASE(test_basic_string_compare_substring_substring__size1),\
    UT_CASE(test_basic_string_compare_substring_substring__size2),\
    UT_CASE(test_basic_string_compare_substring_substring__size),\
    UT_CASE(test_basic_string_compare_substring_substring__terminator_c),\
    UT_CASE(test_basic_string_compare_substring_substring__terminator_cstr),\
    UT_CASE(test_basic_string_compare_substring_substring__terminator_cstl),\
    UT_CASE(test_basic_string_compare_substring_substring__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_compare_substring_string, test_basic_string_compare_substring_string__null_first),\
    UT_CASE(test_basic_string_compare_substring_string__null_second),\
    UT_CASE(test_basic_string_compare_substring_string__non_inited_first),\
    UT_CASE(test_basic_string_compare_substring_string__non_inited_second),\
    UT_CASE(test_basic_string_compare_substring_string__invalid_pos),\
    UT_CASE(test_basic_string_compare_substring_string__not_same_type),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__c_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__char_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__char_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__char_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_string__char_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__char_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__char_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__char_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__char_all_equal),\
    UT_CASE(test_basic_string_compare_substring_string__char_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__char_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__char_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_string__char_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__char_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_all_equal),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__cstr_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__libcstl_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_all_equal),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__user_define_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_string__shared),\
    UT_CASE_BEGIN(basic_string_compare, test_basic_string_compare__null_first),\
    UT_CASE(test_basic_string_compare__null_second),\
    UT_CASE(test_basic_string_compare__non_inited_first),\
    UT_CASE(test_basic_string_compare__non_inited_second),\
    UT_CASE(test_basic_string_compare__not_same_type),\
    UT_CASE(test_basic_string_compare__same_basic_string),\
    UT_CASE(test_basic_string_compare__c_builtin_size_first_less_than_second),\
    UT_CASE(test_basic_string_compare__c_builtin_size_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__c_builtin_size_equal_0),\
    UT_CASE(test_basic_string_compare__c_builtin_size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_compare__c_builtin_size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__c_builtin_size_equal_elem_equal),\
    UT_CASE(test_basic_string_compare__char_size_first_less_than_second),\
    UT_CASE(test_basic_string_compare__char_size_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__char_size_equal_0),\
    UT_CASE(test_basic_string_compare__char_size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_compare__char_size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__char_size_equal_elem_equal),\
    UT_CASE(test_basic_string_compare__cstr_size_first_less_than_second),\
    UT_CASE(test_basic_string_compare__cstr_size_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__cstr_size_equal_0),\
    UT_CASE(test_basic_string_compare__cstr_size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_compare__cstr_size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__cstr_size_equal_elem_equal),\
    UT_CASE(test_basic_string_compare__libcstl_builtin_size_first_less_than_second),\
    UT_CASE(test_basic_string_compare__libcstl_builtin_size_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__libcstl_builtin_size_equal_0),\
    UT_CASE(test_basic_string_compare__libcstl_builtin_size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_compare__libcstl_builtin_size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__libcstl_builtin_size_equal_elem_equal),\
    UT_CASE(test_basic_string_compare__user_define_size_first_less_than_second),\
    UT_CASE(test_basic_string_compare__user_define_size_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__user_define_size_equal_0),\
    UT_CASE(test_basic_string_compare__user_define_size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_compare__user_define_size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_compare__user_define_size_equal_elem_equal),\
    UT_CASE(test_basic_string_compare__shared),\
    UT_CASE_BEGIN(basic_string_equal, test_basic_string_equal__null_first),\
    UT_CASE(test_basic_string_equal__null_second),\
    UT_CASE(test_basic_string_equal__non_inited_first),\
    UT_CASE(test_basic_string_equal__non_inited_second),\
    UT_CASE(test_basic_string_equal__not_same_type),\
    UT_CASE(test_basic_string_equal__same_basic_string),\
    UT_CASE(test_basic_string_equal__size_first_less_than_second),\
    UT_CASE(test_basic_string_equal__size_first_greater_than_second),\
    UT_CASE(test_basic_string_equal__size_equal_0),\
    UT_CASE(test_basic_string_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_equal__size_equal_elem_equal),\
    UT_CASE(test_basic_string_equal__shared),\
    UT_CASE_BEGIN(basic_string_not_equal, test_basic_string_not_equal__null_first),\
    UT_CASE(test_basic_string_not_equal__null_second),\
    UT_CASE(test_basic_string_not_equal__non_inited_first),\
    UT_CASE(test_basic_string_not_equal__non_inited_second),\
    UT_CASE(test_basic_string_not_equal__not_same_type),\
    UT_CASE(test_basic_string_not_equal__same_basic_string),\
    UT_CASE(test_basic_string_not_equal__size_first_less_than_second),\
    UT_CASE(test_basic_string_not_equal__size_first_greater_than_second),\
    UT_CASE(test_basic_string_not_equal__size_equal_0),\
    UT_CASE(test_basic_string_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_not_equal__size_equal_elem_equal),\
    UT_CASE(test_basic_string_not_equal__shared),\
    UT_CASE_BEGIN(basic_string_less, test_basic_string_less__null_first),\
    UT_CASE(test_basic_string_less__null_second),\
    UT_CASE(test_basic_string_less__non_inited_first),\
    UT_CASE(test_basic_string_less__non_inited_second),\
    UT_CASE(test_basic_string_less__not_same_type),\
    UT_CASE(test_basic_string_less__same_basic_string),\
    UT_CASE(test_basic_string_less__size_first_less_than_second),\
    UT_CASE(test_basic_string_less__size_first_greater_than_second),\
    UT_CASE(test_basic_string_less__size_equal_0),\
    UT_CASE(test_basic_string_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_less__size_equal_elem_equal),\
    UT_CASE(test_basic_string_less__shared),\
    UT_CASE_BEGIN(basic_string_less_equal, test_basic_string_less_equal__null_first),\
    UT_CASE(test_basic_string_less_equal__null_second),\
    UT_CASE(test_basic_string_less_equal__non_inited_first),\
    UT_CASE(test_basic_string_less_equal__non_inited_second),\
    UT_CASE(test_basic_string_less_equal__not_same_type),\
    UT_CASE(test_basic_string_less_equal__same_basic_string),\
    UT_CASE(test_basic_string_less_equal__size_first_less_than_second),\
    UT_CASE(test_basic_string_less_equal__size_first_greater_than_second),\
    UT_CASE(test_basic_string_less_equal__size_equal_0),\
    UT_CASE(test_basic_string_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_less_equal__size_equal_elem_equal),\
    UT_CASE(test_basic_string_less_equal__shared),\
    UT_CASE_BEGIN(basic_string_greater, test_basic_string_greater__null_first),\
    UT_CASE(test_basic_string_greater__null_second),\
    UT_CASE(test_basic_string_greater__non_inited_first),\
    UT_CASE(test_basic_string_greater__non_inited_second),\
    UT_CASE(test_basic_string_greater__not_same_type),\
    UT_CASE(test_basic_string_greater__same_basic_string),\
    UT_CASE(test_basic_string_greater__size_first_less_than_second),\
    UT_CASE(test_basic_string_greater__size_first_greater_than_second),\
    UT_CASE(test_basic_string_greater__size_equal_0),\
    UT_CASE(test_basic_string_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_greater__size_equal_elem_equal),\
    UT_CASE(test_basic_string_greater__shared),\
    UT_CASE_BEGIN(basic_string_greater_equal, test_basic_string_greater_equal__null_first),\
    UT_CASE(test_basic_string_greater_equal__null_second),\
    UT_CASE(test_basic_string_greater_equal__non_inited_first),\
    UT_CASE(test_basic_string_greater_equal__non_inited_second),\
    UT_CASE(test_basic_string_greater_equal__not_same_type),\
    UT_CASE(test_basic_string_greater_equal__same_basic_string),\
    UT_CASE(test_basic_string_greater_equal__size_first_less_than_second),\
    UT_CASE(test_basic_string_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_basic_string_greater_equal__size_equal_0),\
    UT_CASE(test_basic_string_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_basic_string_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_basic_string_greater_equal__size_equal_elem_equal),\
    UT_CASE(test_basic_string_greater_equal__shared),\
    UT_CASE_BEGIN(basic_string_compare_substring_subcstr, test_basic_string_compare_substring_subcstr__null_basic_string),\
    UT_CASE(test_basic_string_compare_substring_subcstr__null_value_string),\
    UT_CASE(test_basic_string_compare_substring_subcstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_compare_substring_subcstr__invalid_pos),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__c_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_all_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__char_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_all_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__cstr_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__libcstl_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_all_equal),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__user_defined_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_subcstr__shared),\
    UT_CASE(test_basic_string_compare_substring_subcstr__include_terminator),\
    UT_CASE(test_basic_string_compare_substring_subcstr__size),\
    UT_CASE(test_basic_string_compare_substring_subcstr__terminator_c),\
    UT_CASE(test_basic_string_compare_substring_subcstr__terminator_cstr),\
    UT_CASE(test_basic_string_compare_substring_subcstr__terminator_cstl),\
    UT_CASE(test_basic_string_compare_substring_subcstr__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_compare_substring_cstr, test_basic_string_compare_substring_cstr__null_basic_string),\
    UT_CASE(test_basic_string_compare_substring_cstr__null_value_string),\
    UT_CASE(test_basic_string_compare_substring_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_compare_substring_cstr__invalid_pos),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__c_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_all_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__char_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_all_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__cstr_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_all_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__libcstl_builtin_all_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_non_empty_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_empty_non_empty),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_sub_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_sub_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_sub_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_sub_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_sub_content_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_all_size_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_all_content_less),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_all_equal),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_all_size_greater),\
    UT_CASE(test_basic_string_compare_substring_cstr__user_defined_all_content_greater),\
    UT_CASE_BEGIN(basic_string_compare_cstr, test_basic_string_compare_cstr__null_basic_string),\
    UT_CASE(test_basic_string_compare_cstr__null_value_string),\
    UT_CASE(test_basic_string_compare_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_compare_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_compare_cstr__c_builtin_less),\
    UT_CASE(test_basic_string_compare_cstr__c_builtin_equal),\
    UT_CASE(test_basic_string_compare_cstr__c_builtin_greater),\
    UT_CASE(test_basic_string_compare_cstr__c_builtin_size_equal_less),\
    UT_CASE(test_basic_string_compare_cstr__c_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_compare_cstr__char_empty),\
    UT_CASE(test_basic_string_compare_cstr__char_less),\
    UT_CASE(test_basic_string_compare_cstr__char_equal),\
    UT_CASE(test_basic_string_compare_cstr__char_greater),\
    UT_CASE(test_basic_string_compare_cstr__char_size_equal_less),\
    UT_CASE(test_basic_string_compare_cstr__char_size_equal_greater),\
    UT_CASE(test_basic_string_compare_cstr__cstr_empty),\
    UT_CASE(test_basic_string_compare_cstr__cstr_less),\
    UT_CASE(test_basic_string_compare_cstr__cstr_equal),\
    UT_CASE(test_basic_string_compare_cstr__cstr_greater),\
    UT_CASE(test_basic_string_compare_cstr__cstr_size_equal_less),\
    UT_CASE(test_basic_string_compare_cstr__cstr_size_equal_greater),\
    UT_CASE(test_basic_string_compare_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_compare_cstr__libcstl_builtin_less),\
    UT_CASE(test_basic_string_compare_cstr__libcstl_builtin_equal),\
    UT_CASE(test_basic_string_compare_cstr__libcstl_builtin_greater),\
    UT_CASE(test_basic_string_compare_cstr__libcstl_builtin_size_equal_less),\
    UT_CASE(test_basic_string_compare_cstr__libcstl_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_compare_cstr__user_defined_empty),\
    UT_CASE(test_basic_string_compare_cstr__user_defined_less),\
    UT_CASE(test_basic_string_compare_cstr__user_defined_equal),\
    UT_CASE(test_basic_string_compare_cstr__user_defined_greater),\
    UT_CASE(test_basic_string_compare_cstr__user_defined_size_equal_less),\
    UT_CASE(test_basic_string_compare_cstr__user_defined_size_equal_greater),\
    UT_CASE_BEGIN(basic_string_equal_cstr, test_basic_string_equal_cstr__null_basic_string),\
    UT_CASE(test_basic_string_equal_cstr__null_value_string),\
    UT_CASE(test_basic_string_equal_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_equal_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_equal_cstr__c_builtin_less),\
    UT_CASE(test_basic_string_equal_cstr__c_builtin_equal),\
    UT_CASE(test_basic_string_equal_cstr__c_builtin_greater),\
    UT_CASE(test_basic_string_equal_cstr__c_builtin_size_equal_less),\
    UT_CASE(test_basic_string_equal_cstr__c_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_equal_cstr__char_empty),\
    UT_CASE(test_basic_string_equal_cstr__char_less),\
    UT_CASE(test_basic_string_equal_cstr__char_equal),\
    UT_CASE(test_basic_string_equal_cstr__char_greater),\
    UT_CASE(test_basic_string_equal_cstr__char_size_equal_less),\
    UT_CASE(test_basic_string_equal_cstr__char_size_equal_greater),\
    UT_CASE(test_basic_string_equal_cstr__cstr_empty),\
    UT_CASE(test_basic_string_equal_cstr__cstr_less),\
    UT_CASE(test_basic_string_equal_cstr__cstr_equal),\
    UT_CASE(test_basic_string_equal_cstr__cstr_greater),\
    UT_CASE(test_basic_string_equal_cstr__cstr_size_equal_less),\
    UT_CASE(test_basic_string_equal_cstr__cstr_size_equal_greater),\
    UT_CASE(test_basic_string_equal_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_equal_cstr__libcstl_builtin_less),\
    UT_CASE(test_basic_string_equal_cstr__libcstl_builtin_equal),\
    UT_CASE(test_basic_string_equal_cstr__libcstl_builtin_greater),\
    UT_CASE(test_basic_string_equal_cstr__libcstl_builtin_size_equal_less),\
    UT_CASE(test_basic_string_equal_cstr__libcstl_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_equal_cstr__user_defined_empty),\
    UT_CASE(test_basic_string_equal_cstr__user_defined_less),\
    UT_CASE(test_basic_string_equal_cstr__user_defined_equal),\
    UT_CASE(test_basic_string_equal_cstr__user_defined_greater),\
    UT_CASE(test_basic_string_equal_cstr__user_defined_size_equal_less),\
    UT_CASE(test_basic_string_equal_cstr__user_defined_size_equal_greater),\
    UT_CASE_BEGIN(basic_string_not_equal_cstr, test_basic_string_not_equal_cstr__null_basic_string),\
    UT_CASE(test_basic_string_not_equal_cstr__null_value_string),\
    UT_CASE(test_basic_string_not_equal_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_not_equal_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_not_equal_cstr__c_builtin_less),\
    UT_CASE(test_basic_string_not_equal_cstr__c_builtin_equal),\
    UT_CASE(test_basic_string_not_equal_cstr__c_builtin_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__c_builtin_size_equal_less),\
    UT_CASE(test_basic_string_not_equal_cstr__c_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__char_empty),\
    UT_CASE(test_basic_string_not_equal_cstr__char_less),\
    UT_CASE(test_basic_string_not_equal_cstr__char_equal),\
    UT_CASE(test_basic_string_not_equal_cstr__char_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__char_size_equal_less),\
    UT_CASE(test_basic_string_not_equal_cstr__char_size_equal_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__cstr_empty),\
    UT_CASE(test_basic_string_not_equal_cstr__cstr_less),\
    UT_CASE(test_basic_string_not_equal_cstr__cstr_equal),\
    UT_CASE(test_basic_string_not_equal_cstr__cstr_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__cstr_size_equal_less),\
    UT_CASE(test_basic_string_not_equal_cstr__cstr_size_equal_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_not_equal_cstr__libcstl_builtin_less),\
    UT_CASE(test_basic_string_not_equal_cstr__libcstl_builtin_equal),\
    UT_CASE(test_basic_string_not_equal_cstr__libcstl_builtin_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__libcstl_builtin_size_equal_less),\
    UT_CASE(test_basic_string_not_equal_cstr__libcstl_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__user_defined_empty),\
    UT_CASE(test_basic_string_not_equal_cstr__user_defined_less),\
    UT_CASE(test_basic_string_not_equal_cstr__user_defined_equal),\
    UT_CASE(test_basic_string_not_equal_cstr__user_defined_greater),\
    UT_CASE(test_basic_string_not_equal_cstr__user_defined_size_equal_less),\
    UT_CASE(test_basic_string_not_equal_cstr__user_defined_size_equal_greater),\
    UT_CASE_BEGIN(basic_string_less_cstr, test_basic_string_less_cstr__null_basic_string),\
    UT_CASE(test_basic_string_less_cstr__null_value_string),\
    UT_CASE(test_basic_string_less_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_less_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_less_cstr__c_builtin_less),\
    UT_CASE(test_basic_string_less_cstr__c_builtin_equal),\
    UT_CASE(test_basic_string_less_cstr__c_builtin_greater),\
    UT_CASE(test_basic_string_less_cstr__c_builtin_size_equal_less),\
    UT_CASE(test_basic_string_less_cstr__c_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_less_cstr__char_empty),\
    UT_CASE(test_basic_string_less_cstr__char_less),\
    UT_CASE(test_basic_string_less_cstr__char_equal),\
    UT_CASE(test_basic_string_less_cstr__char_greater),\
    UT_CASE(test_basic_string_less_cstr__char_size_equal_less),\
    UT_CASE(test_basic_string_less_cstr__char_size_equal_greater),\
    UT_CASE(test_basic_string_less_cstr__cstr_empty),\
    UT_CASE(test_basic_string_less_cstr__cstr_less),\
    UT_CASE(test_basic_string_less_cstr__cstr_equal),\
    UT_CASE(test_basic_string_less_cstr__cstr_greater),\
    UT_CASE(test_basic_string_less_cstr__cstr_size_equal_less),\
    UT_CASE(test_basic_string_less_cstr__cstr_size_equal_greater),\
    UT_CASE(test_basic_string_less_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_less_cstr__libcstl_builtin_less),\
    UT_CASE(test_basic_string_less_cstr__libcstl_builtin_equal),\
    UT_CASE(test_basic_string_less_cstr__libcstl_builtin_greater),\
    UT_CASE(test_basic_string_less_cstr__libcstl_builtin_size_equal_less),\
    UT_CASE(test_basic_string_less_cstr__libcstl_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_less_cstr__user_defined_empty),\
    UT_CASE(test_basic_string_less_cstr__user_defined_less),\
    UT_CASE(test_basic_string_less_cstr__user_defined_equal),\
    UT_CASE(test_basic_string_less_cstr__user_defined_greater),\
    UT_CASE(test_basic_string_less_cstr__user_defined_size_equal_less),\
    UT_CASE(test_basic_string_less_cstr__user_defined_size_equal_greater),\
    UT_CASE_BEGIN(basic_string_less_equal_cstr, test_basic_string_less_equal_cstr__null_basic_string),\
    UT_CASE(test_basic_string_less_equal_cstr__null_value_string),\
    UT_CASE(test_basic_string_less_equal_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_less_equal_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_less_equal_cstr__c_builtin_less),\
    UT_CASE(test_basic_string_less_equal_cstr__c_builtin_equal),\
    UT_CASE(test_basic_string_less_equal_cstr__c_builtin_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__c_builtin_size_equal_less),\
    UT_CASE(test_basic_string_less_equal_cstr__c_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__char_empty),\
    UT_CASE(test_basic_string_less_equal_cstr__char_less),\
    UT_CASE(test_basic_string_less_equal_cstr__char_equal),\
    UT_CASE(test_basic_string_less_equal_cstr__char_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__char_size_equal_less),\
    UT_CASE(test_basic_string_less_equal_cstr__char_size_equal_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__cstr_empty),\
    UT_CASE(test_basic_string_less_equal_cstr__cstr_less),\
    UT_CASE(test_basic_string_less_equal_cstr__cstr_equal),\
    UT_CASE(test_basic_string_less_equal_cstr__cstr_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__cstr_size_equal_less),\
    UT_CASE(test_basic_string_less_equal_cstr__cstr_size_equal_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_less_equal_cstr__libcstl_builtin_less),\
    UT_CASE(test_basic_string_less_equal_cstr__libcstl_builtin_equal),\
    UT_CASE(test_basic_string_less_equal_cstr__libcstl_builtin_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__libcstl_builtin_size_equal_less),\
    UT_CASE(test_basic_string_less_equal_cstr__libcstl_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__user_defined_empty),\
    UT_CASE(test_basic_string_less_equal_cstr__user_defined_less),\
    UT_CASE(test_basic_string_less_equal_cstr__user_defined_equal),\
    UT_CASE(test_basic_string_less_equal_cstr__user_defined_greater),\
    UT_CASE(test_basic_string_less_equal_cstr__user_defined_size_equal_less),\
    UT_CASE(test_basic_string_less_equal_cstr__user_defined_size_equal_greater),\
    UT_CASE_BEGIN(basic_string_greater_cstr, test_basic_string_greater_cstr__null_basic_string),\
    UT_CASE(test_basic_string_greater_cstr__null_value_string),\
    UT_CASE(test_basic_string_greater_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_greater_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_greater_cstr__c_builtin_less),\
    UT_CASE(test_basic_string_greater_cstr__c_builtin_equal),\
    UT_CASE(test_basic_string_greater_cstr__c_builtin_greater),\
    UT_CASE(test_basic_string_greater_cstr__c_builtin_size_equal_less),\
    UT_CASE(test_basic_string_greater_cstr__c_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_greater_cstr__char_empty),\
    UT_CASE(test_basic_string_greater_cstr__char_less),\
    UT_CASE(test_basic_string_greater_cstr__char_equal),\
    UT_CASE(test_basic_string_greater_cstr__char_greater),\
    UT_CASE(test_basic_string_greater_cstr__char_size_equal_less),\
    UT_CASE(test_basic_string_greater_cstr__char_size_equal_greater),\
    UT_CASE(test_basic_string_greater_cstr__cstr_empty),\
    UT_CASE(test_basic_string_greater_cstr__cstr_less),\
    UT_CASE(test_basic_string_greater_cstr__cstr_equal),\
    UT_CASE(test_basic_string_greater_cstr__cstr_greater),\
    UT_CASE(test_basic_string_greater_cstr__cstr_size_equal_less),\
    UT_CASE(test_basic_string_greater_cstr__cstr_size_equal_greater),\
    UT_CASE(test_basic_string_greater_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_greater_cstr__libcstl_builtin_less),\
    UT_CASE(test_basic_string_greater_cstr__libcstl_builtin_equal),\
    UT_CASE(test_basic_string_greater_cstr__libcstl_builtin_greater),\
    UT_CASE(test_basic_string_greater_cstr__libcstl_builtin_size_equal_less),\
    UT_CASE(test_basic_string_greater_cstr__libcstl_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_greater_cstr__user_defined_empty),\
    UT_CASE(test_basic_string_greater_cstr__user_defined_less),\
    UT_CASE(test_basic_string_greater_cstr__user_defined_equal),\
    UT_CASE(test_basic_string_greater_cstr__user_defined_greater),\
    UT_CASE(test_basic_string_greater_cstr__user_defined_size_equal_less),\
    UT_CASE(test_basic_string_greater_cstr__user_defined_size_equal_greater),\
    UT_CASE_BEGIN(basic_string_greater_equal_cstr, test_basic_string_greater_equal_cstr__null_basic_string),\
    UT_CASE(test_basic_string_greater_equal_cstr__null_value_string),\
    UT_CASE(test_basic_string_greater_equal_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_greater_equal_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_greater_equal_cstr__c_builtin_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__c_builtin_equal),\
    UT_CASE(test_basic_string_greater_equal_cstr__c_builtin_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__c_builtin_size_equal_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__c_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__char_empty),\
    UT_CASE(test_basic_string_greater_equal_cstr__char_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__char_equal),\
    UT_CASE(test_basic_string_greater_equal_cstr__char_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__char_size_equal_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__char_size_equal_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__cstr_empty),\
    UT_CASE(test_basic_string_greater_equal_cstr__cstr_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__cstr_equal),\
    UT_CASE(test_basic_string_greater_equal_cstr__cstr_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__cstr_size_equal_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__cstr_size_equal_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_greater_equal_cstr__libcstl_builtin_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__libcstl_builtin_equal),\
    UT_CASE(test_basic_string_greater_equal_cstr__libcstl_builtin_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__libcstl_builtin_size_equal_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__libcstl_builtin_size_equal_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__user_defined_empty),\
    UT_CASE(test_basic_string_greater_equal_cstr__user_defined_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__user_defined_equal),\
    UT_CASE(test_basic_string_greater_equal_cstr__user_defined_greater),\
    UT_CASE(test_basic_string_greater_equal_cstr__user_defined_size_equal_less),\
    UT_CASE(test_basic_string_greater_equal_cstr__user_defined_size_equal_greater),\
    UT_CASE_BEGIN(basic_string_substr, test_basic_string_substr__null_basic_string),\
    UT_CASE(test_basic_string_substr__non_inited_basic_string),\
    UT_CASE(test_basic_string_substr__invalid_pos),\
    UT_CASE(test_basic_string_substr__empty_substr),\
    UT_CASE(test_basic_string_substr__all),\
    UT_CASE(test_basic_string_substr__c_builtin),\
    UT_CASE(test_basic_string_substr__char),\
    UT_CASE(test_basic_string_substr__cstr),\
    UT_CASE(test_basic_string_substr__libcstl),\
    UT_CASE(test_basic_string_substr__user_define),\
    UT_CASE(test_basic_string_substr__check),\
    UT_CASE_BEGIN(basic_string_swap, test_basic_string_swap__null_first),\
    UT_CASE(test_basic_string_swap__null_second),\
    UT_CASE(test_basic_string_swap__non_inited_first),\
    UT_CASE(test_basic_string_swap__non_inited_second),\
    UT_CASE(test_basic_string_swap__not_same_type),\
    UT_CASE(test_basic_string_swap__basic_string_equal),\
    UT_CASE(test_basic_string_swap__0_swap_10),\
    UT_CASE(test_basic_string_swap__0_swap_1000),\
    UT_CASE(test_basic_string_swap__10_swap_0),\
    UT_CASE(test_basic_string_swap__10_swap_10),\
    UT_CASE(test_basic_string_swap__10_swap_1000),\
    UT_CASE(test_basic_string_swap__1000_swap_0),\
    UT_CASE(test_basic_string_swap__1000_swap_10),\
    UT_CASE(test_basic_string_swap__1000_swap_1010),\
    UT_CASE(test_basic_string_swap__shared),\
    UT_CASE_BEGIN(basic_string_clear, test_basic_string_clear__null_basic_string_container),\
    UT_CASE(test_basic_string_clear__non_inited_basic_string_container),\
    UT_CASE(test_basic_string_clear__empty_basic_string_container),\
    UT_CASE(test_basic_string_clear__non_empty_basic_string_container),\
    UT_CASE(test_basic_string_clear__shared),\
    UT_CASE(test_basic_string_clear__terminator_c),\
    UT_CASE(test_basic_string_clear__terminator_cstr),\
    UT_CASE(test_basic_string_clear__terminator_cstl),\
    UT_CASE(test_basic_string_clear__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_assign, test_basic_string_assign__null_dest),\
    UT_CASE(test_basic_string_assign__null_src),\
    UT_CASE(test_basic_string_assign__non_inited_dest),\
    UT_CASE(test_basic_string_assign__non_inited_src),\
    UT_CASE(test_basic_string_assign__not_same_type),\
    UT_CASE(test_basic_string_assign__same_container),\
    UT_CASE(test_basic_string_assign__0_assign_0),\
    UT_CASE(test_basic_string_assign__0_assign_10),\
    UT_CASE(test_basic_string_assign__0_assign_1000),\
    UT_CASE(test_basic_string_assign__10_assign_0),\
    UT_CASE(test_basic_string_assign__10_assign_10_basic_string_equal),\
    UT_CASE(test_basic_string_assign__10_assign_10_basic_string_not_equal),\
    UT_CASE(test_basic_string_assign__10_assign_1000),\
    UT_CASE(test_basic_string_assign__1000_assign_0),\
    UT_CASE(test_basic_string_assign__1000_assign_10),\
    UT_CASE(test_basic_string_assign__1000_assign_1010),\
    UT_CASE(test_basic_string_assign__1000_assign_1810),\
    UT_CASE(test_basic_string_assign__char),\
    UT_CASE(test_basic_string_assign__cstr),\
    UT_CASE(test_basic_string_assign__libcstl),\
    UT_CASE(test_basic_string_assign__user_define),\
    UT_CASE(test_basic_string_assign__same_rep),\
    UT_CASE(test_basic_string_assign__shared),\
    UT_CASE_BEGIN(basic_string_assign_substring, test_basic_string_assign_substring__null_dest),\
    UT_CASE(test_basic_string_assign_substring__null_src),\
    UT_CASE(test_basic_string_assign_substring__non_inited_dest),\
    UT_CASE(test_basic_string_assign_substring__non_inited_src),\
    UT_CASE(test_basic_string_assign_substring__not_same_type),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_end),\
    UT_CASE(test_basic_string_assign_substring__successfully_c_builtin_src_non_empty_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_end),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstr_src_non_empty_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_begin_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_begin_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_non_empty_middle_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_cstl_builtin_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_begin_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_begin_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_begin_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_middle_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_middle_length),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_middle_npos),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_end),\
    UT_CASE(test_basic_string_assign_substring__successfully_user_define_non_empty_npos),\
    UT_CASE(test_basic_string_assign_substring__shared),\
    UT_CASE(test_basic_string_assign_substring__same_pbstr),\
    UT_CASE(test_basic_string_assign_substring__shared_assign),\
    UT_CASE(test_basic_string_assign_substring__less_size),\
    UT_CASE(test_basic_string_assign_substring__greater_size),\
    UT_CASE(test_basic_string_assign_substring__about_size),\
    UT_CASE_BEGIN(basic_string_assign_subcstr, test_basic_string_assign_subcstr__null_container),\
    UT_CASE(test_basic_string_assign_subcstr__non_created_container),\
    UT_CASE(test_basic_string_assign_subcstr__null_valuestring),\
    UT_CASE(test_basic_string_assign_subcstr__c_builtin_empty),\
    UT_CASE(test_basic_string_assign_subcstr__c_builtin_non_empty),\
    UT_CASE(test_basic_string_assign_subcstr__c_builtin_total),\
    UT_CASE(test_basic_string_assign_subcstr__char_empty),\
    UT_CASE(test_basic_string_assign_subcstr__char_non_empty),\
    UT_CASE(test_basic_string_assign_subcstr__char_total),\
    UT_CASE(test_basic_string_assign_subcstr__cstr_empty),\
    UT_CASE(test_basic_string_assign_subcstr__cstr_non_empty),\
    UT_CASE(test_basic_string_assign_subcstr__cstr_total),\
    UT_CASE(test_basic_string_assign_subcstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_assign_subcstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_assign_subcstr__libcstl_builtin_total),\
    UT_CASE(test_basic_string_assign_subcstr__user_define_empty),\
    UT_CASE(test_basic_string_assign_subcstr__user_define_non_empty),\
    UT_CASE(test_basic_string_assign_subcstr__user_define_total),\
    UT_CASE(test_basic_string_assign_subcstr__shared),\
    UT_CASE(test_basic_string_assign_subcstr__include_terminator),\
    UT_CASE_BEGIN(basic_string_assign_cstr, test_basic_string_assign_cstr__null_container),\
    UT_CASE(test_basic_string_assign_cstr__non_inited),\
    UT_CASE(test_basic_string_assign_cstr__null_valuestring),\
    UT_CASE(test_basic_string_assign_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_assign_cstr__c_builtin_non_empty),\
    UT_CASE(test_basic_string_assign_cstr__char_empty),\
    UT_CASE(test_basic_string_assign_cstr__char_non_empty),\
    UT_CASE(test_basic_string_assign_cstr__cstr_empty),\
    UT_CASE(test_basic_string_assign_cstr__cstr_init_non_empty),\
    UT_CASE(test_basic_string_assign_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_assign_cstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_assign_cstr__user_define_empty),\
    UT_CASE(test_basic_string_assign_cstr__user_define_non_empty),\
    UT_CASE(test_basic_string_assign_cstr__shared),\
    UT_CASE_BEGIN(basic_string_assign_range, test_basic_string_assign_range__null_dest),\
    UT_CASE(test_basic_string_assign_range__non_inited_dest),\
    UT_CASE(test_basic_string_assign_range__invalid_begin_iterator),\
    UT_CASE(test_basic_string_assign_range__invalid_end_iterator),\
    UT_CASE(test_basic_string_assign_range__invalid_range),\
    UT_CASE(test_basic_string_assign_range__not_same_type),\
    UT_CASE(test_basic_string_assign_range__successfully_empty_range),\
    UT_CASE(test_basic_string_assign_range__successfully_c_builtin),\
    UT_CASE(test_basic_string_assign_range__successfully_cstr),\
    UT_CASE(test_basic_string_assign_range__successfully_cstl_builtin),\
    UT_CASE(test_basic_string_assign_range__successfully_user_define),\
    UT_CASE(test_basic_string_assign_range__shared),\
    UT_CASE(test_basic_string_assign_range__same_pbstr),\
    UT_CASE(test_basic_string_assign_range__other_container),\
    UT_CASE_BEGIN(basic_string_resize, test_basic_string_resize__null),\
    UT_CASE(test_basic_string_resize__non_inited),\
    UT_CASE(test_basic_string_resize__greater_max_size),\
    UT_CASE(test_basic_string_resize__0_resize_0),\
    UT_CASE(test_basic_string_resize__0_resize_5),\
    UT_CASE(test_basic_string_resize__10_resize_0),\
    UT_CASE(test_basic_string_resize__10_resize_5),\
    UT_CASE(test_basic_string_resize__10_resize_10),\
    UT_CASE(test_basic_string_resize__10_resize_110),\
    UT_CASE(test_basic_string_resize__cstr),\
    UT_CASE(test_basic_string_resize__libcstl),\
    UT_CASE(test_basic_string_resize__user_define),\
    UT_CASE(test_basic_string_resize__shared),\
    UT_CASE_BEGIN(basic_string_append_subcstr, test_basic_string_append_subcstr__null_container),\
    UT_CASE(test_basic_string_append_subcstr__non_created_container),\
    UT_CASE(test_basic_string_append_subcstr__null_valuestring),\
    UT_CASE(test_basic_string_append_subcstr__c_builtin_empty),\
    UT_CASE(test_basic_string_append_subcstr__c_builtin_non_empty),\
    UT_CASE(test_basic_string_append_subcstr__c_builtin_total),\
    UT_CASE(test_basic_string_append_subcstr__char_empty),\
    UT_CASE(test_basic_string_append_subcstr__char_non_empty),\
    UT_CASE(test_basic_string_append_subcstr__char_total),\
    UT_CASE(test_basic_string_append_subcstr__cstr_empty),\
    UT_CASE(test_basic_string_append_subcstr__cstr_non_empty),\
    UT_CASE(test_basic_string_append_subcstr__cstr_total),\
    UT_CASE(test_basic_string_append_subcstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_append_subcstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_append_subcstr__libcstl_builtin_total),\
    UT_CASE(test_basic_string_append_subcstr__user_define_empty),\
    UT_CASE(test_basic_string_append_subcstr__user_define_non_empty),\
    UT_CASE(test_basic_string_append_subcstr__user_define_total),\
    UT_CASE(test_basic_string_append_subcstr__shared),\
    UT_CASE_BEGIN(basic_string_append_cstr, test_basic_string_append_cstr__null_container),\
    UT_CASE(test_basic_string_append_cstr__non_inited),\
    UT_CASE(test_basic_string_append_cstr__null_valuestring),\
    UT_CASE(test_basic_string_append_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_append_cstr__c_builtin_non_empty),\
    UT_CASE(test_basic_string_append_cstr__char_empty),\
    UT_CASE(test_basic_string_append_cstr__char_non_empty),\
    UT_CASE(test_basic_string_append_cstr__cstr_empty),\
    UT_CASE(test_basic_string_append_cstr__cstr_init_non_empty),\
    UT_CASE(test_basic_string_append_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_append_cstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_append_cstr__user_define_empty),\
    UT_CASE(test_basic_string_append_cstr__user_define_non_empty),\
    UT_CASE(test_basic_string_append_cstr__shared),\
    UT_CASE_BEGIN(basic_string_append_range, test_basic_string_append_range__null_dest),\
    UT_CASE(test_basic_string_append_range__non_inited_dest),\
    UT_CASE(test_basic_string_append_range__invalid_begin_iterator),\
    UT_CASE(test_basic_string_append_range__invalid_end_iterator),\
    UT_CASE(test_basic_string_append_range__invalid_range),\
    UT_CASE(test_basic_string_append_range__not_same_type),\
    UT_CASE(test_basic_string_append_range__successfully_empty_range),\
    UT_CASE(test_basic_string_append_range__successfully_c_builtin),\
    UT_CASE(test_basic_string_append_range__successfully_cstr),\
    UT_CASE(test_basic_string_append_range__successfully_cstl_builtin),\
    UT_CASE(test_basic_string_append_range__successfully_user_define),\
    UT_CASE(test_basic_string_append_range__shared),\
    UT_CASE_BEGIN(basic_string_append_substring, test_basic_string_append_substring__null_dest),\
    UT_CASE(test_basic_string_append_substring__null_src),\
    UT_CASE(test_basic_string_append_substring__non_inited_dest),\
    UT_CASE(test_basic_string_append_substring__non_inited_src),\
    UT_CASE(test_basic_string_append_substring__not_same_type),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_end),\
    UT_CASE(test_basic_string_append_substring__successfully_c_builtin_src_non_empty_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_end),\
    UT_CASE(test_basic_string_append_substring__successfully_cstr_src_non_empty_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_non_empty_begin_length),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_non_empty_begin_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_length),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_non_empty_middle_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_length),\
    UT_CASE(test_basic_string_append_substring__successfully_cstl_builtin_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_begin_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_begin_length),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_begin_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_middle_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_middle_length),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_middle_npos),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_end),\
    UT_CASE(test_basic_string_append_substring__successfully_user_define_non_empty_npos),\
    UT_CASE(test_basic_string_append_substring__shared),\
    UT_CASE(test_basic_string_append_substring__gt_size),\
    UT_CASE(test_basic_string_append_substring__eq_size),\
    UT_CASE(test_basic_string_append_substring__lt_size),\
    UT_CASE_BEGIN(basic_string_append, test_basic_string_append__null_dest),\
    UT_CASE(test_basic_string_append__null_src),\
    UT_CASE(test_basic_string_append__non_inited_dest),\
    UT_CASE(test_basic_string_append__non_inited_src),\
    UT_CASE(test_basic_string_append__not_same_type),\
    UT_CASE(test_basic_string_append__same_container),\
    UT_CASE(test_basic_string_append__0_assign_0),\
    UT_CASE(test_basic_string_append__0_assign_10),\
    UT_CASE(test_basic_string_append__10_assign_0),\
    UT_CASE(test_basic_string_append__1000_assign_1810),\
    UT_CASE(test_basic_string_append__char),\
    UT_CASE(test_basic_string_append__cstr),\
    UT_CASE(test_basic_string_append__libcstl),\
    UT_CASE(test_basic_string_append__user_define),\
    UT_CASE(test_basic_string_append__shared),\
    UT_CASE_BEGIN(basic_string_connect, test_basic_string_connect__null_dest),\
    UT_CASE(test_basic_string_connect__null_src),\
    UT_CASE(test_basic_string_connect__non_inited_dest),\
    UT_CASE(test_basic_string_connect__non_inited_src),\
    UT_CASE(test_basic_string_connect__not_same_type),\
    UT_CASE(test_basic_string_connect__empty_empty),\
    UT_CASE(test_basic_string_connect__non_empty_empty),\
    UT_CASE(test_basic_string_connect__empty_non_empty),\
    UT_CASE(test_basic_string_connect__same),\
    UT_CASE(test_basic_string_connect__c_builtin),\
    UT_CASE(test_basic_string_connect__char),\
    UT_CASE(test_basic_string_connect__cstr),\
    UT_CASE(test_basic_string_connect__libcstl),\
    UT_CASE(test_basic_string_connect__user_define),\
    UT_CASE_BEGIN(basic_string_connect_cstr, test_basic_string_connect_cstr__null_basic_string),\
    UT_CASE(test_basic_string_connect_cstr__null_value_string),\
    UT_CASE(test_basic_string_connect_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_connect_cstr__empty_empty),\
    UT_CASE(test_basic_string_connect_cstr__non_empty_empty),\
    UT_CASE(test_basic_string_connect_cstr__empty_non_empty),\
    UT_CASE(test_basic_string_connect_cstr__c_builtin),\
    UT_CASE(test_basic_string_connect_cstr__char),\
    UT_CASE(test_basic_string_connect_cstr__cstr),\
    UT_CASE(test_basic_string_connect_cstr__libcstl),\
    UT_CASE(test_basic_string_connect_cstr__user_define),\
    UT_CASE_BEGIN(basic_string_erase_substring, test_basic_string_erase_substring__null_basic_string),\
    UT_CASE(test_basic_string_erase_substring__non_inited_basic_string),\
    UT_CASE(test_basic_string_erase_substring__invalid_pos),\
    UT_CASE(test_basic_string_erase_substring__c_builtin_begin),\
    UT_CASE(test_basic_string_erase_substring__c_builtin_middle),\
    UT_CASE(test_basic_string_erase_substring__c_builtin_end),\
    UT_CASE(test_basic_string_erase_substring__c_builtin_all),\
    UT_CASE(test_basic_string_erase_substring__c_builtin_erase_empty),\
    UT_CASE(test_basic_string_erase_substring__char),\
    UT_CASE(test_basic_string_erase_substring__cstr),\
    UT_CASE(test_basic_string_erase_substring__libcstr_builtin),\
    UT_CASE(test_basic_string_erase_substring__user_define),\
    UT_CASE(test_basic_string_erase_substring__shared),\
    UT_CASE(test_basic_string_erase_substring__end),\
    UT_CASE_BEGIN(basic_string_erase, test_basic_string_erase__null_basic_string),\
    UT_CASE(test_basic_string_erase__non_inited_basic_string),\
    UT_CASE(test_basic_string_erase__invalid_pos),\
    UT_CASE(test_basic_string_erase__empty),\
    UT_CASE(test_basic_string_erase__c_builtin_begin),\
    UT_CASE(test_basic_string_erase__c_builtin_middle),\
    UT_CASE(test_basic_string_erase__c_builtin_last),\
    UT_CASE(test_basic_string_erase__char),\
    UT_CASE(test_basic_string_erase__cstr),\
    UT_CASE(test_basic_string_erase__libcstl_builtin),\
    UT_CASE(test_basic_string_erase__user_define),\
    UT_CASE_BEGIN(basic_string_erase_range, test_basic_string_erase_range__null_basic_string),\
    UT_CASE(test_basic_string_erase_range__non_inited_basic_string),\
    UT_CASE(test_basic_string_erase_range__invalid_begin),\
    UT_CASE(test_basic_string_erase_range__invalid_end),\
    UT_CASE(test_basic_string_erase_range__invalid_range),\
    UT_CASE(test_basic_string_erase_range__empty),\
    UT_CASE(test_basic_string_erase_range__c_builtin_begin),\
    UT_CASE(test_basic_string_erase_range__c_builtin_middle),\
    UT_CASE(test_basic_string_erase_range__c_builtin_end),\
    UT_CASE(test_basic_string_erase_range__c_builtin_all),\
    UT_CASE(test_basic_string_erase_range__c_builtin_erase_empty),\
    UT_CASE(test_basic_string_erase_range__char),\
    UT_CASE(test_basic_string_erase_range__cstr),\
    UT_CASE(test_basic_string_erase_range__libcstl_builtin),\
    UT_CASE(test_basic_string_erase_range__user_define),\
    UT_CASE_BEGIN(basic_string_replace_substring, test_basic_string_replace_substring__null_dest),\
    UT_CASE(test_basic_string_replace_substring__null_replace),\
    UT_CASE(test_basic_string_replace_substring__non_inited_dest),\
    UT_CASE(test_basic_string_replace_substring__non_inited_replace),\
    UT_CASE(test_basic_string_replace_substring__not_same_type),\
    UT_CASE(test_basic_string_replace_substring__invalid_pos),\
    UT_CASE(test_basic_string_replace_substring__invalid_position),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_replace_substring__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_replace_substring__char),\
    UT_CASE(test_basic_string_replace_substring__cstr),\
    UT_CASE(test_basic_string_replace_substring__libcstl_builtin),\
    UT_CASE(test_basic_string_replace_substring__user_define),\
    UT_CASE(test_basic_string_replace_substring__shared),\
    UT_CASE(test_basic_string_replace_substring__check),\
    UT_CASE(test_basic_string_replace_substring__terminator_c),\
    UT_CASE(test_basic_string_replace_substring__terminator_cstr),\
    UT_CASE(test_basic_string_replace_substring__terminator_cstl),\
    UT_CASE(test_basic_string_replace_substring__terminator_user_define),\
    UT_CASE(test_basic_string_replace_substring__same_container),\
    UT_CASE(test_basic_string_replace_substring__same_container_1),\
    UT_CASE(test_basic_string_replace_substring__same_container_2),\
    UT_CASE(test_basic_string_replace_substring__same_container_3),\
    UT_CASE(test_basic_string_replace_substring__same_container_4),\
    UT_CASE(test_basic_string_replace_substring__same_container_5),\
    UT_CASE(test_basic_string_replace_substring__same_container_6),\
    UT_CASE(test_basic_string_replace_substring__same_container_7),\
    UT_CASE(test_basic_string_replace_substring__same_container_8),\
    UT_CASE(test_basic_string_replace_substring__same_container_9),\
    UT_CASE(test_basic_string_replace_substring__same_container_10),\
    UT_CASE(test_basic_string_replace_substring__same_container_11),\
    UT_CASE(test_basic_string_replace_substring__same_container_12),\
    UT_CASE(test_basic_string_replace_substring__same_container_13),\
    UT_CASE(test_basic_string_replace_substring__same_container_14),\
    UT_CASE(test_basic_string_replace_substring__same_container_15),\
    UT_CASE(test_basic_string_replace_substring__same_container_16),\
    UT_CASE_BEGIN(basic_string_replace, test_basic_string_replace__null_dest),\
    UT_CASE(test_basic_string_replace__null_replace),\
    UT_CASE(test_basic_string_replace__non_inited_dest),\
    UT_CASE(test_basic_string_replace__non_inited_replace),\
    UT_CASE(test_basic_string_replace__not_same_type),\
    UT_CASE(test_basic_string_replace__same_container),\
    UT_CASE(test_basic_string_replace__invalid_pos),\
    UT_CASE(test_basic_string_replace__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_replace__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_replace__char),\
    UT_CASE(test_basic_string_replace__cstr),\
    UT_CASE(test_basic_string_replace__libcstl_builtin),\
    UT_CASE(test_basic_string_replace__user_define),\
    UT_CASE(test_basic_string_replace__shared),\
    UT_CASE_BEGIN(basic_string_range_replace_substring, test_basic_string_range_replace_substring__null_dest),\
    UT_CASE(test_basic_string_range_replace_substring__null_replace),\
    UT_CASE(test_basic_string_range_replace_substring__non_inited_dest),\
    UT_CASE(test_basic_string_range_replace_substring__non_inited_replace),\
    UT_CASE(test_basic_string_range_replace_substring__not_same_type),\
    UT_CASE(test_basic_string_range_replace_substring__same_container),\
    UT_CASE(test_basic_string_range_replace_substring__invalid_range),\
    UT_CASE(test_basic_string_range_replace_substring__invalid_position),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_range_replace_substring__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_substring__char),\
    UT_CASE(test_basic_string_range_replace_substring__cstr),\
    UT_CASE(test_basic_string_range_replace_substring__libcstl_builtin),\
    UT_CASE(test_basic_string_range_replace_substring__user_define),\
    UT_CASE_BEGIN(basic_string_range_replace, test_basic_string_range_replace__null_dest),\
    UT_CASE(test_basic_string_range_replace__null_replace),\
    UT_CASE(test_basic_string_range_replace__non_inited_dest),\
    UT_CASE(test_basic_string_range_replace__non_inited_replace),\
    UT_CASE(test_basic_string_range_replace__not_same_type),\
    UT_CASE(test_basic_string_range_replace__same_container),\
    UT_CASE(test_basic_string_range_replace__invalid_range),\
    UT_CASE(test_basic_string_range_replace__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_range_replace__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace__char),\
    UT_CASE(test_basic_string_range_replace__cstr),\
    UT_CASE(test_basic_string_range_replace__libcstl_builtin),\
    UT_CASE(test_basic_string_range_replace__user_define),\
    UT_CASE_BEGIN(basic_string_replace_subcstr, test_basic_string_replace_subcstr__null_dest),\
    UT_CASE(test_basic_string_replace_subcstr__null_replace),\
    UT_CASE(test_basic_string_replace_subcstr__non_inited_dest),\
    UT_CASE(test_basic_string_replace_subcstr__invalid_pos),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_replace_subcstr__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_replace_subcstr__char),\
    UT_CASE(test_basic_string_replace_subcstr__cstr),\
    UT_CASE(test_basic_string_replace_subcstr__libcstl_builtin),\
    UT_CASE(test_basic_string_replace_subcstr__user_define),\
    UT_CASE_BEGIN(basic_string_replace_cstr, test_basic_string_replace_cstr__null_dest),\
    UT_CASE(test_basic_string_replace_cstr__null_replace),\
    UT_CASE(test_basic_string_replace_cstr__non_inited_dest),\
    UT_CASE(test_basic_string_replace_cstr__invalid_pos),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_replace_cstr__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_replace_cstr__char),\
    UT_CASE(test_basic_string_replace_cstr__cstr),\
    UT_CASE(test_basic_string_replace_cstr__libcstl_builtin),\
    UT_CASE(test_basic_string_replace_cstr__user_define),\
    UT_CASE_BEGIN(basic_string_range_replace_subcstr, test_basic_string_range_replace_subcstr__null_dest),\
    UT_CASE(test_basic_string_range_replace_subcstr__null_replace),\
    UT_CASE(test_basic_string_range_replace_subcstr__non_inited_dest),\
    UT_CASE(test_basic_string_range_replace_subcstr__invalid_range),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_subcstr__char),\
    UT_CASE(test_basic_string_range_replace_subcstr__cstr),\
    UT_CASE(test_basic_string_range_replace_subcstr__libcstl_builtin),\
    UT_CASE(test_basic_string_range_replace_subcstr__user_define),\
    UT_CASE_BEGIN(basic_string_range_replace_cstr, test_basic_string_range_replace_cstr__null_dest),\
    UT_CASE(test_basic_string_range_replace_cstr__null_replace),\
    UT_CASE(test_basic_string_range_replace_cstr__non_inited_dest),\
    UT_CASE(test_basic_string_range_replace_cstr__invalid_range),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_range_replace_cstr__char),\
    UT_CASE(test_basic_string_range_replace_cstr__cstr),\
    UT_CASE(test_basic_string_range_replace_cstr__libcstl_builtin),\
    UT_CASE(test_basic_string_range_replace_cstr__user_define),\
    UT_CASE_BEGIN(basic_string_replace_range, test_basic_string_replace_range__null_dest),\
    UT_CASE(test_basic_string_replace_range__non_inited_dest),\
    UT_CASE(test_basic_string_replace_range__not_same_type),\
    UT_CASE(test_basic_string_replace_range__same_container),\
    UT_CASE(test_basic_string_replace_range__invalid_range),\
    UT_CASE(test_basic_string_replace_range__invalid_replace_range),\
    UT_CASE(test_basic_string_replace_range__c_builtin_begin_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_begin_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_begin_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_begin_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_middle_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_middle_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_middle_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_middle_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_end_non_empty_replace_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_end_non_empty_replace_non_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_all_replace_empty),\
    UT_CASE(test_basic_string_replace_range__c_builtin_all_replace_non_empty),\
    UT_CASE(test_basic_string_replace_range__char),\
    UT_CASE(test_basic_string_replace_range__cstr),\
    UT_CASE(test_basic_string_replace_range__libcstl_builtin),\
    UT_CASE(test_basic_string_replace_range__user_define),\
    UT_CASE_BEGIN(basic_string_insert_substring, test_basic_string_insert_substring__null_dest),\
    UT_CASE(test_basic_string_insert_substring__null_insert),\
    UT_CASE(test_basic_string_insert_substring__non_inited_dest),\
    UT_CASE(test_basic_string_insert_substring__non_inited_insert),\
    UT_CASE(test_basic_string_insert_substring__not_same_type),\
    UT_CASE(test_basic_string_insert_substring__same_container),\
    UT_CASE(test_basic_string_insert_substring__invalid_pos),\
    UT_CASE(test_basic_string_insert_substring__invalid_startpos),\
    UT_CASE(test_basic_string_insert_substring__c_builtin_begin_insert_empty),\
    UT_CASE(test_basic_string_insert_substring__c_builtin_middle_insert_non_empty),\
    UT_CASE(test_basic_string_insert_substring__char_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_substring__char_begin_insert_non_empty),\
    UT_CASE(test_basic_string_insert_substring__cstr_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_substring__cstr_begin_insert_non_empty),\
    UT_CASE(test_basic_string_insert_substring__libcstl_builtin_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_substring__libcstl_builtin_begin_insert_non_empty),\
    UT_CASE(test_basic_string_insert_substring__user_define_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_substring__user_define_begin_insert_non_empty),\
    UT_CASE(test_basic_string_insert_substring__end),\
    UT_CASE_BEGIN(basic_string_insert_string, test_basic_string_insert_string__null_dest),\
    UT_CASE(test_basic_string_insert_string__null_insert),\
    UT_CASE(test_basic_string_insert_string__non_inited_dest),\
    UT_CASE(test_basic_string_insert_string__non_inited_insert),\
    UT_CASE(test_basic_string_insert_string__not_same_type),\
    UT_CASE(test_basic_string_insert_string__same_container),\
    UT_CASE(test_basic_string_insert_string__invalid_pos),\
    UT_CASE(test_basic_string_insert_string__c_builtin_begin_insert_empty),\
    UT_CASE(test_basic_string_insert_string__c_builtin_middle_insert_non_empty),\
    UT_CASE(test_basic_string_insert_string__char_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_string__char_begin_insert_non_empty),\
    UT_CASE(test_basic_string_insert_string__cstr_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_string__cstr_begin_insert_non_empty),\
    UT_CASE(test_basic_string_insert_string__libcstl_builtin_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_string__libcstl_builtin_begin_insert_non_empty),\
    UT_CASE(test_basic_string_insert_string__user_define_middle_insert_empty),\
    UT_CASE(test_basic_string_insert_string__user_define_begin_insert_non_empty),\
    UT_CASE_BEGIN(basic_string_insert_subcstr, test_basic_string_insert_subcstr__null_container),\
    UT_CASE(test_basic_string_insert_subcstr__non_created_container),\
    UT_CASE(test_basic_string_insert_subcstr__null_valuestring),\
    UT_CASE(test_basic_string_insert_subcstr__invalid_pos),\
    UT_CASE(test_basic_string_insert_subcstr__c_builtin_empty),\
    UT_CASE(test_basic_string_insert_subcstr__c_builtin_non_empty),\
    UT_CASE(test_basic_string_insert_subcstr__c_builtin_total),\
    UT_CASE(test_basic_string_insert_subcstr__char_empty),\
    UT_CASE(test_basic_string_insert_subcstr__char_non_empty),\
    UT_CASE(test_basic_string_insert_subcstr__char_total),\
    UT_CASE(test_basic_string_insert_subcstr__cstr_empty),\
    UT_CASE(test_basic_string_insert_subcstr__cstr_non_empty),\
    UT_CASE(test_basic_string_insert_subcstr__cstr_total),\
    UT_CASE(test_basic_string_insert_subcstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_insert_subcstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_insert_subcstr__libcstl_builtin_total),\
    UT_CASE(test_basic_string_insert_subcstr__user_define_empty),\
    UT_CASE(test_basic_string_insert_subcstr__user_define_non_empty),\
    UT_CASE(test_basic_string_insert_subcstr__user_define_total),\
    UT_CASE_BEGIN(basic_string_insert_cstr, test_basic_string_insert_cstr__null_container),\
    UT_CASE(test_basic_string_insert_cstr__non_inited),\
    UT_CASE(test_basic_string_insert_cstr__null_valuestring),\
    UT_CASE(test_basic_string_insert_cstr__invalid_pos),\
    UT_CASE(test_basic_string_insert_cstr__c_builtin_empty),\
    UT_CASE(test_basic_string_insert_cstr__c_builtin_non_empty),\
    UT_CASE(test_basic_string_insert_cstr__char_empty),\
    UT_CASE(test_basic_string_insert_cstr__char_non_empty),\
    UT_CASE(test_basic_string_insert_cstr__cstr_empty),\
    UT_CASE(test_basic_string_insert_cstr__cstr_init_non_empty),\
    UT_CASE(test_basic_string_insert_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_insert_cstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_insert_cstr__user_define_empty),\
    UT_CASE(test_basic_string_insert_cstr__user_define_non_empty),\
    UT_CASE_BEGIN(basic_string_insert_range, test_basic_string_insert_range__null_basic_string),\
    UT_CASE(test_basic_string_insert_range__non_inited_basic_string),\
    UT_CASE(test_basic_string_insert_range__invalid_pos),\
    UT_CASE(test_basic_string_insert_range__invalid_begin),\
    UT_CASE(test_basic_string_insert_range__invalid_end),\
    UT_CASE(test_basic_string_insert_range__invalid_range),\
    UT_CASE(test_basic_string_insert_range__not_same_type),\
    UT_CASE(test_basic_string_insert_range__c_builtin_empty_insert_empty),\
    UT_CASE(test_basic_string_insert_range__c_builtin_empty_insert_non_empty),\
    UT_CASE(test_basic_string_insert_range__c_builtin_non_empty_insert_begin_empty),\
    UT_CASE(test_basic_string_insert_range__c_builtin_non_empty_insert_middle_empty),\
    UT_CASE(test_basic_string_insert_range__c_builtin_non_empty_insert_end_empty),\
    UT_CASE(test_basic_string_insert_range__c_builtin_non_empty_insert_begin_non_empty),\
    UT_CASE(test_basic_string_insert_range__c_builtin_non_empty_insert_middle_non_empty),\
    UT_CASE(test_basic_string_insert_range__c_builtin_non_empty_insert_end_non_empty),\
    UT_CASE(test_basic_string_insert_range__char),\
    UT_CASE(test_basic_string_insert_range__cstr),\
    UT_CASE(test_basic_string_insert_range__libcstl_builtin),\
    UT_CASE(test_basic_string_insert_range__user_define),\
    UT_CASE_BEGIN(basic_string_find_subcstr, test_basic_string_find_subcstr__null_basic_string),\
    UT_CASE(test_basic_string_find_subcstr__null_find),\
    UT_CASE(test_basic_string_find_subcstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_subcstr__invalid_pos),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_begin_length_0),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_begin_equal_size),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_begin_greater_size),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_middle_length_0),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_middle_equal_size),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_middle_great_size),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_end_empty),\
    UT_CASE(test_basic_string_find_subcstr__c_builtin_end_non_empty),\
    UT_CASE(test_basic_string_find_subcstr__char_begin_empty),\
    UT_CASE(test_basic_string_find_subcstr__char_begin_length_0),\
    UT_CASE(test_basic_string_find_subcstr__char_begin_find),\
    UT_CASE(test_basic_string_find_subcstr__char_begin_not_find),\
    UT_CASE(test_basic_string_find_subcstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_subcstr__char_middle_length_0),\
    UT_CASE(test_basic_string_find_subcstr__char_middle_find),\
    UT_CASE(test_basic_string_find_subcstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_subcstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_subcstr__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_subcstr__cstr_begin_length_0),\
    UT_CASE(test_basic_string_find_subcstr__cstr_begin_find),\
    UT_CASE(test_basic_string_find_subcstr__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_subcstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_subcstr__cstr_middle_length_0),\
    UT_CASE(test_basic_string_find_subcstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_subcstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_subcstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_begin_length_0),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_middle_length_0),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_subcstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_subcstr__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_subcstr__user_define_begin_length_0),\
    UT_CASE(test_basic_string_find_subcstr__user_define_begin_find),\
    UT_CASE(test_basic_string_find_subcstr__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_subcstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_subcstr__user_define_middle_length_0),\
    UT_CASE(test_basic_string_find_subcstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_subcstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_subcstr__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_subcstr__shared),\
    UT_CASE_BEGIN(basic_string_find_cstr, test_basic_string_find_cstr__null_basic_string),\
    UT_CASE(test_basic_string_find_cstr__null_find),\
    UT_CASE(test_basic_string_find_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_cstr__invalid_pos),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_pos_eq_size_n_ne_0),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_cstr__c_builtin_pos_gt_size_n_ne_0),\
    UT_CASE(test_basic_string_find_cstr__char_begin_empty),\
    UT_CASE(test_basic_string_find_cstr__char_begin_find),\
    UT_CASE(test_basic_string_find_cstr__char_begin_not_find),\
    UT_CASE(test_basic_string_find_cstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_cstr__char_middle_find),\
    UT_CASE(test_basic_string_find_cstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_cstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_cstr__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_cstr__cstr_begin_find),\
    UT_CASE(test_basic_string_find_cstr__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_cstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_cstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_cstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_cstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_cstr__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_cstr__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_cstr__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_cstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_cstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_cstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_cstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_cstr__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_cstr__user_define_begin_find),\
    UT_CASE(test_basic_string_find_cstr__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_cstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_cstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_cstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_cstr__user_define_middle_not_find_pos),\
    UT_CASE_BEGIN(basic_string_find, test_basic_string_find__null_basic_string),\
    UT_CASE(test_basic_string_find__null_find),\
    UT_CASE(test_basic_string_find__non_inited_basic_string),\
    UT_CASE(test_basic_string_find__non_inited_find),\
    UT_CASE(test_basic_string_find__not_same_type),\
    UT_CASE(test_basic_string_find__invalid_pos),\
    UT_CASE(test_basic_string_find__same_begin),\
    UT_CASE(test_basic_string_find__same_middle),\
    UT_CASE(test_basic_string_find__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find__c_builtin_pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find__c_builtin_pos_eq_size_n_ne_0),\
    UT_CASE(test_basic_string_find__c_builtin_pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find__c_builtin_pos_gt_size_n_ne_0),\
    UT_CASE(test_basic_string_find__char_begin_empty),\
    UT_CASE(test_basic_string_find__char_begin_find),\
    UT_CASE(test_basic_string_find__char_begin_not_find),\
    UT_CASE(test_basic_string_find__char_middle_empty),\
    UT_CASE(test_basic_string_find__char_middle_find),\
    UT_CASE(test_basic_string_find__char_middle_not_find),\
    UT_CASE(test_basic_string_find__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find__cstr_begin_empty),\
    UT_CASE(test_basic_string_find__cstr_begin_find),\
    UT_CASE(test_basic_string_find__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find__cstr_middle_empty),\
    UT_CASE(test_basic_string_find__cstr_middle_find),\
    UT_CASE(test_basic_string_find__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find__user_define_begin_empty),\
    UT_CASE(test_basic_string_find__user_define_begin_find),\
    UT_CASE(test_basic_string_find__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find__user_define_middle_empty),\
    UT_CASE(test_basic_string_find__user_define_middle_find),\
    UT_CASE(test_basic_string_find__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find__user_define_middle_not_find_pos),\
    UT_CASE_BEGIN(basic_string_rfind_subcstr, test_basic_string_rfind_subcstr__null_basic_string),\
    UT_CASE(test_basic_string_rfind_subcstr__null_find),\
    UT_CASE(test_basic_string_rfind_subcstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_middle_empty_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_subcstr__char_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__char_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__char_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__char_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__char_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__char_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__char_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__char_not_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__char_middle_empty),\
    UT_CASE(test_basic_string_rfind_subcstr__char_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__char_middle_find),\
    UT_CASE(test_basic_string_rfind_subcstr__char_middle_not_find),\
    UT_CASE(test_basic_string_rfind_subcstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_not_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_middle_find),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_rfind_subcstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_rfind_subcstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_empty_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_not_find_npos),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_middle_find),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_rfind_subcstr__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_eq_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_rfind_subcstr__c_builtin_pos_gt_size_n_gt_size),\
    UT_CASE_BEGIN(basic_string_rfind_cstr, test_basic_string_rfind_cstr__null_basic_string),\
    UT_CASE(test_basic_string_rfind_cstr__null_find),\
    UT_CASE(test_basic_string_rfind_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_rfind_cstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_cstr__char_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__char_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__char_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__char_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__char_not_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__char_middle_empty),\
    UT_CASE(test_basic_string_rfind_cstr__char_middle_find),\
    UT_CASE(test_basic_string_rfind_cstr__char_middle_not_find),\
    UT_CASE(test_basic_string_rfind_cstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_not_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_middle_find),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_rfind_cstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_rfind_cstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_empty_npos),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_not_find_npos),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_middle_find),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_rfind_cstr__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_0_n_eq_0),\
    UT_CASE(test_basic_string_rfind_cstr__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind_cstr__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_rfind_cstr__pos_gt_size_n_gt_size),\
    UT_CASE_BEGIN(basic_string_rfind, test_basic_string_rfind__null_basic_string),\
    UT_CASE(test_basic_string_rfind__null_find),\
    UT_CASE(test_basic_string_rfind__non_inited_basic_string),\
    UT_CASE(test_basic_string_rfind__non_inited_find),\
    UT_CASE(test_basic_string_rfind__not_same_type),\
    UT_CASE(test_basic_string_rfind__same_npos),\
    UT_CASE(test_basic_string_rfind__same_middle),\
    UT_CASE(test_basic_string_rfind__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_rfind__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_rfind__c_builtin_find_npos),\
    UT_CASE(test_basic_string_rfind__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_rfind__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_rfind__c_builtin_middle_find),\
    UT_CASE(test_basic_string_rfind__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_rfind__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind__char_empty_empty_0),\
    UT_CASE(test_basic_string_rfind__char_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind__char_empty_npos),\
    UT_CASE(test_basic_string_rfind__char_find_npos),\
    UT_CASE(test_basic_string_rfind__char_not_find_npos),\
    UT_CASE(test_basic_string_rfind__char_middle_empty),\
    UT_CASE(test_basic_string_rfind__char_middle_find),\
    UT_CASE(test_basic_string_rfind__char_middle_not_find),\
    UT_CASE(test_basic_string_rfind__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_rfind__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind__cstr_empty_npos),\
    UT_CASE(test_basic_string_rfind__cstr_find_npos),\
    UT_CASE(test_basic_string_rfind__cstr_not_find_npos),\
    UT_CASE(test_basic_string_rfind__cstr_middle_empty),\
    UT_CASE(test_basic_string_rfind__cstr_middle_find),\
    UT_CASE(test_basic_string_rfind__cstr_middle_not_find),\
    UT_CASE(test_basic_string_rfind__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_rfind__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_rfind__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_rfind__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_rfind__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_rfind__user_define_empty_npos),\
    UT_CASE(test_basic_string_rfind__user_define_find_npos),\
    UT_CASE(test_basic_string_rfind__user_define_not_find_npos),\
    UT_CASE(test_basic_string_rfind__user_define_middle_empty),\
    UT_CASE(test_basic_string_rfind__user_define_middle_find),\
    UT_CASE(test_basic_string_rfind__user_define_middle_not_find),\
    UT_CASE(test_basic_string_rfind__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_rfind__pos_eq_0_n_eq_0),\
    UT_CASE(test_basic_string_rfind__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_rfind__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_rfind__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_rfind__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_rfind__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_rfind__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_rfind__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_rfind__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_rfind__pos_gt_size_n_gt_size),\
    UT_CASE_BEGIN(basic_string_find_first_of_subcstr, test_basic_string_find_first_of_subcstr__null_basic_string),\
    UT_CASE(test_basic_string_find_first_of_subcstr__null_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_first_of_subcstr__invalid_pos),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_begin_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_middle_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_begin_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_begin_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_middle_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_middle_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_begin_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_begin_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_middle_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_begin_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_begin_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_middle_length_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_subcstr__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_0_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of_subcstr__terminator_c),\
    UT_CASE(test_basic_string_find_first_of_subcstr__terminator_cstr),\
    UT_CASE(test_basic_string_find_first_of_subcstr__terminator_cstl),\
    UT_CASE(test_basic_string_find_first_of_subcstr__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_find_first_of_cstr, test_basic_string_find_first_of_cstr__null_basic_string),\
    UT_CASE(test_basic_string_find_first_of_cstr__null_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_first_of_cstr__invalid_pos),\
    UT_CASE(test_basic_string_find_first_of_cstr__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_cstr__char_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__char_begin_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__char_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__char_middle_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_cstr__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__cstr_begin_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_cstr__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of_cstr__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__user_define_begin_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_first_of_cstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of_cstr__user_define_middle_not_find_pos),\
    UT_CASE_BEGIN(basic_string_find_first_of, test_basic_string_find_first_of__null_basic_string),\
    UT_CASE(test_basic_string_find_first_of__null_find),\
    UT_CASE(test_basic_string_find_first_of__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_first_of__non_inited_find),\
    UT_CASE(test_basic_string_find_first_of__not_same_type),\
    UT_CASE(test_basic_string_find_first_of__invalid_pos),\
    UT_CASE(test_basic_string_find_first_of__same_begin),\
    UT_CASE(test_basic_string_find_first_of__same_middle),\
    UT_CASE(test_basic_string_find_first_of__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_of__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_of__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_of__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_of__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of__char_begin_empty),\
    UT_CASE(test_basic_string_find_first_of__char_begin_find),\
    UT_CASE(test_basic_string_find_first_of__char_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of__char_middle_empty),\
    UT_CASE(test_basic_string_find_first_of__char_middle_find),\
    UT_CASE(test_basic_string_find_first_of__char_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_first_of__cstr_begin_find),\
    UT_CASE(test_basic_string_find_first_of__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_first_of__cstr_middle_find),\
    UT_CASE(test_basic_string_find_first_of__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_of__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_of__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_of__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_of__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_first_of__user_define_begin_find),\
    UT_CASE(test_basic_string_find_first_of__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_first_of__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_first_of__user_define_middle_find),\
    UT_CASE(test_basic_string_find_first_of__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_first_of__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_of__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_first_of__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_first_of__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of__pos_eq_0_n_eq_0),\
    UT_CASE(test_basic_string_find_first_of__terminator_c),\
    UT_CASE(test_basic_string_find_first_of__terminator_cstr),\
    UT_CASE(test_basic_string_find_first_of__terminator_cstl),\
    UT_CASE(test_basic_string_find_first_of__terminator_user_define),\
    UT_CASE_BEGIN(basic_string_find_first_not_of_subcstr, test_basic_string_find_first_not_of_subcstr__null_basic_string),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__null_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__invalid_pos),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_begin_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_middle_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_begin_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_middle_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_begin_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_middle_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_begin_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_middle_length_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_eq_0),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_not_of_subcstr__pos_eq_0_n_gt_size),\
    UT_CASE_BEGIN(basic_string_find_first_not_of_cstr, test_basic_string_find_first_not_of_cstr__null_basic_string),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__null_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__invalid_pos),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__char_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__char_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__char_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__char_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__cstr_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__user_define_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of_cstr__user_define_middle_not_find_pos),\
    UT_CASE_BEGIN(basic_string_find_first_not_of, test_basic_string_find_first_not_of__null_basic_string),\
    UT_CASE(test_basic_string_find_first_not_of__null_find),\
    UT_CASE(test_basic_string_find_first_not_of__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_first_not_of__non_inited_find),\
    UT_CASE(test_basic_string_find_first_not_of__not_same_type),\
    UT_CASE(test_basic_string_find_first_not_of__invalid_pos),\
    UT_CASE(test_basic_string_find_first_not_of__same_begin),\
    UT_CASE(test_basic_string_find_first_not_of__same_middle),\
    UT_CASE(test_basic_string_find_first_not_of__c_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of__c_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of__c_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of__char_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of__char_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of__char_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__char_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of__char_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of__char_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of__cstr_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of__cstr_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of__cstr_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of__cstr_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of__libcstl_builtin_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of__libcstl_builtin_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of__libcstl_builtin_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of__user_define_begin_empty),\
    UT_CASE(test_basic_string_find_first_not_of__user_define_begin_find),\
    UT_CASE(test_basic_string_find_first_not_of__user_define_begin_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_first_not_of__user_define_middle_find),\
    UT_CASE(test_basic_string_find_first_not_of__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_first_not_of__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_first_not_of__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_first_not_of__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_not_of__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_first_not_of__pos_eq_0_n_eq_0),\
    UT_CASE_BEGIN(basic_string_find_last_of_subcstr, test_basic_string_find_last_of_subcstr__null_basic_string),\
    UT_CASE(test_basic_string_find_last_of_subcstr__null_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_middle_empty_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_middle_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_subcstr__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_of_subcstr__pos_eq_0_n_eq_0),\
    UT_CASE_BEGIN(basic_string_find_last_of_cstr, test_basic_string_find_last_of_cstr__null_basic_string),\
    UT_CASE(test_basic_string_find_last_of_cstr__null_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_middle_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_empty_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of_cstr__user_define_middle_not_find_pos),\
    UT_CASE_BEGIN(basic_string_find_last_of, test_basic_string_find_last_of__null_basic_string),\
    UT_CASE(test_basic_string_find_last_of__null_find),\
    UT_CASE(test_basic_string_find_last_of__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_last_of__non_inited_find),\
    UT_CASE(test_basic_string_find_last_of__not_same_type),\
    UT_CASE(test_basic_string_find_last_of__same_npos),\
    UT_CASE(test_basic_string_find_last_of__same_middle),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of__char_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of__char_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__char_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__char_find_npos),\
    UT_CASE(test_basic_string_find_last_of__char_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of__char_middle_empty),\
    UT_CASE(test_basic_string_find_last_of__char_middle_find),\
    UT_CASE(test_basic_string_find_last_of__char_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__cstr_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__cstr_find_npos),\
    UT_CASE(test_basic_string_find_last_of__cstr_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_last_of__cstr_middle_find),\
    UT_CASE(test_basic_string_find_last_of__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_of__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_of__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__user_define_empty_npos),\
    UT_CASE(test_basic_string_find_last_of__user_define_find_npos),\
    UT_CASE(test_basic_string_find_last_of__user_define_not_find_npos),\
    UT_CASE(test_basic_string_find_last_of__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_last_of__user_define_middle_find),\
    UT_CASE(test_basic_string_find_last_of__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_last_of__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_of__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_last_of__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_last_of__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_of__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_of__pos_eq_0_n_eq_0),\
    UT_CASE_BEGIN(basic_string_find_last_not_of_subcstr, test_basic_string_find_last_not_of_subcstr__null_basic_string),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__null_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_middle_empty_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_0_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_non_empty_npos_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_middle_non_empty_length_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_not_of_subcstr__pos_eq_0_n_eq_0),\
    UT_CASE_BEGIN(basic_string_find_last_not_of_cstr, test_basic_string_find_last_not_of_cstr__null_basic_string),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__null_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of_cstr__user_define_middle_not_find_pos),\
    UT_CASE_BEGIN(basic_string_find_last_not_of, test_basic_string_find_last_not_of__null_basic_string),\
    UT_CASE(test_basic_string_find_last_not_of__null_find),\
    UT_CASE(test_basic_string_find_last_not_of__non_inited_basic_string),\
    UT_CASE(test_basic_string_find_last_not_of__non_inited_find),\
    UT_CASE(test_basic_string_find_last_not_of__not_same_type),\
    UT_CASE(test_basic_string_find_last_not_of__same_npos),\
    UT_CASE(test_basic_string_find_last_not_of__same_middle),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of__c_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of__char_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__char_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__char_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__char_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__char_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__char_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__char_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__char_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of__char_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of__char_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of__char_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of__cstr_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of__libcstl_builtin_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_empty_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_empty_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_empty_non_empty_0),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_empty_non_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_empty_npos),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_not_find_npos),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_middle_empty),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_middle_find),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_middle_not_find),\
    UT_CASE(test_basic_string_find_last_not_of__user_define_middle_not_find_pos),\
    UT_CASE(test_basic_string_find_last_not_of__pos_gt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_lt_size_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_0_n_gt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_gt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_lt_size_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_0_n_eq_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_gt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_lt_size_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_0_n_lt_size),\
    UT_CASE(test_basic_string_find_last_not_of__pos_gt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_not_of__pos_lt_size_n_eq_0),\
    UT_CASE(test_basic_string_find_last_not_of__pos_eq_0_n_eq_0)

#endif /* _UT_CSTL_BASIC_STRING_H_ */

