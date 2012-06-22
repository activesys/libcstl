#ifndef _UT_CSTL_AVL_TREE_H_
#define _UT_CSTL_AVL_TREE_H_

UT_SUIT_DECLARATION(cstl_avl_tree)
/*
 * test _create_avl_tree
 */
UT_CASE_DECLARATION(_create_avl_tree)
void test__create_avl_tree__null_typename(void** state);
void test__create_avl_tree__c_builtin(void** state);
void test__create_avl_tree__cstr(void** state);
void test__create_avl_tree__libcstl_builtin(void** state);
void test__create_avl_tree__user_define(void** state);
void test__create_avl_tree__unregister(void** state);
/*
 * test _avl_tree_init
 */
UT_CASE_DECLARATION(_avl_tree_init)
void test__avl_tree_init__null_avl_tree(void** state);
void test__avl_tree_init__non_created(void** state);
void test__avl_tree_init__null_compare(void** state);
void test__avl_tree_init__non_null_compare(void** state);
/*
 * test _avl_tree_init_copy
 */
UT_CASE_DECLARATION(_avl_tree_init_copy)
void test__avl_tree_init_copy__null_dest(void** state);
void test__avl_tree_init_copy__null_src(void** state);
void test__avl_tree_init_copy__non_created_dest(void** state);
void test__avl_tree_init_copy__non_inited_src(void** state);
void test__avl_tree_init_copy__not_same_type(void** state);
void test__avl_tree_init_copy__empty(void** state);
void test__avl_tree_init_copy__non_empty(void** state);
void test__avl_tree_init_copy__non_null_compare(void** state);
/*
 * test _avl_tree_init_copy_equal_range
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_equal_range)
void test__avl_tree_init_copy_equal_range__null_avl_tree(void** state);
void test__avl_tree_init_copy_equal_range__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_equal_range__invalid_begin(void** state);
void test__avl_tree_init_copy_equal_range__invalid_end(void** state);
void test__avl_tree_init_copy_equal_range__invalid_range(void** state);
void test__avl_tree_init_copy_equal_range__invalid_range_not_same_type(void** state);
void test__avl_tree_init_copy_equal_range__empty(void** state);
void test__avl_tree_init_copy_equal_range__non_empty(void** state);
void test__avl_tree_init_copy_equal_range__non_empty_dup(void** state);
/*
 * test _avl_tree_init_copy_equal_array
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_equal_array)
void test__avl_tree_init_copy_equal_array__null_avl_tree(void** state);
void test__avl_tree_init_copy_equal_array__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_equal_array__invalid_array(void** state);
void test__avl_tree_init_copy_equal_array__empty(void** state);
void test__avl_tree_init_copy_equal_array__non_empty(void** state);
void test__avl_tree_init_copy_equal_array__non_empty_dup(void** state);
/*
 * test _avl_tree_init_copy_unique_range
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_unique_range)
void test__avl_tree_init_copy_unique_range__null_avl_tree(void** state);
void test__avl_tree_init_copy_unique_range__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_unique_range__invalid_begin(void** state);
void test__avl_tree_init_copy_unique_range__invalid_end(void** state);
void test__avl_tree_init_copy_unique_range__invalid_range(void** state);
void test__avl_tree_init_copy_unique_range__invalid_range_not_same_type(void** state);
void test__avl_tree_init_copy_unique_range__empty(void** state);
void test__avl_tree_init_copy_unique_range__non_empty(void** state);
void test__avl_tree_init_copy_unique_range__non_empty_dup(void** state);
/*
 * test _avl_tree_init_copy_unique_array
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_unique_array)
void test__avl_tree_init_copy_unique_array__null_avl_tree(void** state);
void test__avl_tree_init_copy_unique_array__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_unique_array__invalid_array(void** state);
void test__avl_tree_init_copy_unique_array__empty(void** state);
void test__avl_tree_init_copy_unique_array__non_empty(void** state);
void test__avl_tree_init_copy_unique_array__non_empty_dup(void** state);
/*
 * test _avl_tree_init_copy_equal_range_ex
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_equal_range_ex)
void test__avl_tree_init_copy_equal_range_ex__null_avl_tree(void** state);
void test__avl_tree_init_copy_equal_range_ex__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_equal_range_ex__invalid_begin(void** state);
void test__avl_tree_init_copy_equal_range_ex__invalid_end(void** state);
void test__avl_tree_init_copy_equal_range_ex__invalid_range(void** state);
void test__avl_tree_init_copy_equal_range_ex__invalid_range_not_same_type(void** state);
void test__avl_tree_init_copy_equal_range_ex__empty(void** state);
void test__avl_tree_init_copy_equal_range_ex__non_empty(void** state);
void test__avl_tree_init_copy_equal_range_ex__non_empty_dup(void** state);
void test__avl_tree_init_copy_equal_range_ex__compare(void** state);
/*
 * test _avl_tree_init_copy_equal_array_ex
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_equal_array_ex)
void test__avl_tree_init_copy_equal_array_ex__null_avl_tree(void** state);
void test__avl_tree_init_copy_equal_array_ex__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_equal_array_ex__invalid_array(void** state);
void test__avl_tree_init_copy_equal_array_ex__empty(void** state);
void test__avl_tree_init_copy_equal_array_ex__non_empty(void** state);
void test__avl_tree_init_copy_equal_array_ex__non_empty_dup(void** state);
void test__avl_tree_init_copy_equal_array_ex__compare(void** state);
/*
 * test _avl_tree_init_copy_unique_range_ex
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_unique_range_ex)
void test__avl_tree_init_copy_unique_range_ex__null_avl_tree(void** state);
void test__avl_tree_init_copy_unique_range_ex__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_unique_range_ex__invalid_begin(void** state);
void test__avl_tree_init_copy_unique_range_ex__invalid_end(void** state);
void test__avl_tree_init_copy_unique_range_ex__invalid_range(void** state);
void test__avl_tree_init_copy_unique_range_ex__invalid_range_not_same_type(void** state);
void test__avl_tree_init_copy_unique_range_ex__empty(void** state);
void test__avl_tree_init_copy_unique_range_ex__non_empty(void** state);
void test__avl_tree_init_copy_unique_range_ex__non_empty_dup(void** state);
void test__avl_tree_init_copy_unique_range_ex__compare(void** state);
/*
 * test _avl_tree_init_copy_unique_array_ex
 */
UT_CASE_DECLARATION(_avl_tree_init_copy_unique_array_ex)
void test__avl_tree_init_copy_unique_array_ex__null_avl_tree(void** state);
void test__avl_tree_init_copy_unique_array_ex__non_created_avl_tree(void** state);
void test__avl_tree_init_copy_unique_array_ex__invalid_array(void** state);
void test__avl_tree_init_copy_unique_array_ex__empty(void** state);
void test__avl_tree_init_copy_unique_array_ex__non_empty(void** state);
void test__avl_tree_init_copy_unique_array_ex__non_empty_dup(void** state);
void test__avl_tree_init_copy_unique_array_ex__compare(void** state);
/*
 * test _avl_tree_destroy
 */
UT_CASE_DECLARATION(_avl_tree_destroy)
void test__avl_tree_destroy__null_avl_tree(void** state);
void test__avl_tree_destroy__non_created(void** state);
void test__avl_tree_destroy__created(void** state);
void test__avl_tree_destroy__inited(void** state);
/*
 * test _avl_tree_assign
 */
UT_CASE_DECLARATION(_avl_tree_assign)
void test__avl_tree_assign__null_dest(void** state);
void test__avl_tree_assign__null_src(void** state);
void test__avl_tree_assign__non_created_dest(void** state);
void test__avl_tree_assign__non_init_src(void** state);
void test__avl_tree_assign__not_same_type(void** state);
void test__avl_tree_assign__empty_empty(void** state);
void test__avl_tree_assign__non_empty_empty(void** state);
void test__avl_tree_assign__non_empty_non_empty_less(void** state);
void test__avl_tree_assign__non_empty_non_empty_size_equal(void** state);
void test__avl_tree_assign__non_empty_non_empty_equal(void** state);
void test__avl_tree_assign__non_empty_non_empty_greater(void** state);
void test__avl_tree_assign__empty_non_empty(void** state);
/*
 * test _avl_tree_size
 */
UT_CASE_DECLARATION(_avl_tree_size)
void test__avl_tree_size__null_avl_tree(void** state);
void test__avl_tree_size__non_inited(void** state);
void test__avl_tree_size__empty(void** state);
void test__avl_tree_size__non_empty(void** state);
/*
 * test _avl_tree_emtpy
 */
UT_CASE_DECLARATION(_avl_tree_empty)
void test__avl_tree_empty__null_avl_tree(void** state);
void test__avl_tree_empty__non_inited(void** state);
void test__avl_tree_empty__empty(void** state);
void test__avl_tree_empty__non_empty(void** state);
/*
 * test _avl_tree_max_size
 */
UT_CASE_DECLARATION(_avl_tree_max_size)
void test__avl_tree_max_size__null_avl_tree(void** state);
void test__avl_tree_max_size__non_inited(void** state);
void test__avl_tree_max_size__empty(void** state);
void test__avl_tree_max_size__non_empty(void** state);
/*
 * test _avl_tree_begin
 */
UT_CASE_DECLARATION(_avl_tree_begin)
void test__avl_tree_begin__null_avl_tree(void** state);
void test__avl_tree_begin__non_inited(void** state);
void test__avl_tree_begin__empty(void** state);
void test__avl_tree_begin__non_empty(void** state);
/*
 * test _avl_tree_end
 */
UT_CASE_DECLARATION(_avl_tree_end)
void test__avl_tree_end__null_avl_tree(void** state);
void test__avl_tree_end__non_inited(void** state);
void test__avl_tree_end__empty(void** state);
void test__avl_tree_end__non_empty(void** state);
/*
 * test _avl_tree_key_comp
 */
UT_CASE_DECLARATION(_avl_tree_key_comp)
void test__avl_tree_key_comp__null_avl_tree(void** state);
void test__avl_tree_key_comp__non_inited(void** state);
void test__avl_tree_key_comp__default_key_comp(void** state);
void test__avl_tree_key_comp__user_define_key_comp(void** state);
/*
 * test _avl_tree_find
 */
UT_CASE_DECLARATION(_avl_tree_find)
void test__avl_tree_find__null_avl_tree(void** state);
void test__avl_tree_find__null_value(void** state);
void test__avl_tree_find__non_inited(void** state);
void test__avl_tree_find__c_builtin_find(void** state);
void test__avl_tree_find__c_builtin_not_find(void** state);
void test__avl_tree_find__cstr_find(void** state);
void test__avl_tree_find__cstr_not_find(void** state);
void test__avl_tree_find__libcstl_builtin_find(void** state);
void test__avl_tree_find__libcstl_builtin_not_find(void** state);
void test__avl_tree_find__user_define_find(void** state);
void test__avl_tree_find__user_define_not_find(void** state);
/*
 * test _avl_tree_clear
 */
UT_CASE_DECLARATION(_avl_tree_clear)
void test__avl_tree_clear__null_avl_tree(void** state);
void test__avl_tree_clear__non_inited(void** state);
void test__avl_tree_clear__empty(void** state);
void test__avl_tree_clear__non_empty(void** state);
/*
 * test _avl_tree_count
 */
UT_CASE_DECLARATION(_avl_tree_count)
void test__avl_tree_count__null_avl_tree(void** state);
void test__avl_tree_count__null_value(void** state);
void test__avl_tree_count__non_inited(void** state);
void test__avl_tree_count__c_builtin_0(void** state);
void test__avl_tree_count__c_builtin_1(void** state);
void test__avl_tree_count__c_builtin_n(void** state);
void test__avl_tree_count__cstr_0(void** state);
void test__avl_tree_count__cstr_1(void** state);
void test__avl_tree_count__cstr_n(void** state);
void test__avl_tree_count__libcstl_builtin_0(void** state);
void test__avl_tree_count__libcstl_builtin_1(void** state);
void test__avl_tree_count__libcstl_builtin_n(void** state);
void test__avl_tree_count__user_define_0(void** state);
void test__avl_tree_count__user_define_1(void** state);
void test__avl_tree_count__user_define_n(void** state);
/*
 * test _avl_tree_lower_bound
 */
UT_CASE_DECLARATION(_avl_tree_lower_bound)
void test__avl_tree_lower_bound__null_avl_tree(void** state);
void test__avl_tree_lower_bound__null_value(void** state);
void test__avl_tree_lower_bound__non_inited(void** state);
void test__avl_tree_lower_bound__c_builtin_equal(void** state);
void test__avl_tree_lower_bound__c_builtin_greater(void** state);
void test__avl_tree_lower_bound__cstr_lower_equal(void** state);
void test__avl_tree_lower_bound__cstr_greater(void** state);
void test__avl_tree_lower_bound__libcstl_builtin_equal(void** state);
void test__avl_tree_lower_bound__libcstl_builtin_greater(void** state);
void test__avl_tree_lower_bound__user_define_equal(void** state);
void test__avl_tree_lower_bound__user_define_greater(void** state);
/*
 * test _avl_tree_upper_bound
 */
UT_CASE_DECLARATION(_avl_tree_upper_bound)
void test__avl_tree_upper_bound__null_avl_tree(void** state);
void test__avl_tree_upper_bound__null_value(void** state);
void test__avl_tree_upper_bound__non_inited(void** state);
void test__avl_tree_upper_bound__c_builtin_equal(void** state);
void test__avl_tree_upper_bound__c_builtin_greater(void** state);
void test__avl_tree_upper_bound__cstr_upper_equal(void** state);
void test__avl_tree_upper_bound__cstr_greater(void** state);
void test__avl_tree_upper_bound__libcstl_builtin_equal(void** state);
void test__avl_tree_upper_bound__libcstl_builtin_greater(void** state);
void test__avl_tree_upper_bound__user_define_equal(void** state);
void test__avl_tree_upper_bound__user_define_greater(void** state);
/*
 * test _avl_tree_equal_range
 */
UT_CASE_DECLARATION(_avl_tree_equal_range)
void test__avl_tree_equal_range__null_avl_tree(void** state);
void test__avl_tree_equal_range__null_value(void** state);
void test__avl_tree_equal_range__non_inited(void** state);
void test__avl_tree_equal_range__c_builtin_equal(void** state);
void test__avl_tree_equal_range__c_builtin_greater(void** state);
void test__avl_tree_equal_range__cstr_upper_equal(void** state);
void test__avl_tree_equal_range__cstr_greater(void** state);
void test__avl_tree_equal_range__libcstl_builtin_equal(void** state);
void test__avl_tree_equal_range__libcstl_builtin_greater(void** state);
void test__avl_tree_equal_range__user_define_equal(void** state);
void test__avl_tree_equal_range__user_define_greater(void** state);
/*
 * test _avl_tree_equal
 */
UT_CASE_DECLARATION(_avl_tree_equal)
void test__avl_tree_equal__null_first(void** state);
void test__avl_tree_equal__null_second(void** state);
void test__avl_tree_equal__non_inited_first(void** state);
void test__avl_tree_equal__non_inited_second(void** state);
void test__avl_tree_equal__not_same_type(void** state);
void test__avl_tree_equal__same_avl_tree(void** state);
void test__avl_tree_equal__size_first_less_than_second(void** state);
void test__avl_tree_equal__size_first_greater_than_second(void** state);
void test__avl_tree_equal__size_equal_0(void** state);
void test__avl_tree_equal__size_equal_elem_first_less_than_second(void** state);
void test__avl_tree_equal__size_equal_elem_first_greater_than_second(void** state);
void test__avl_tree_equal__compare_not_equal(void** state);
void test__avl_tree_equal__equal(void** state);
/*
 * test _avl_tree_not_equal
 */
UT_CASE_DECLARATION(_avl_tree_not_equal)
void test__avl_tree_not_equal__null_first(void** state);
void test__avl_tree_not_equal__null_second(void** state);
void test__avl_tree_not_equal__non_inited_first(void** state);
void test__avl_tree_not_equal__non_inited_second(void** state);
void test__avl_tree_not_equal__not_same_type(void** state);
void test__avl_tree_not_equal__same_avl_tree(void** state);
void test__avl_tree_not_equal__size_first_less_than_second(void** state);
void test__avl_tree_not_equal__size_first_greater_than_second(void** state);
void test__avl_tree_not_equal__size_equal_0(void** state);
void test__avl_tree_not_equal__size_equal_elem_first_less_than_second(void** state);
void test__avl_tree_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test__avl_tree_not_equal__compare_not_equal(void** state);
void test__avl_tree_not_equal__equal(void** state);
/*
 * test _avl_tree_less
 */
UT_CASE_DECLARATION(_avl_tree_less)
void test__avl_tree_less__null_first(void** state);
void test__avl_tree_less__null_second(void** state);
void test__avl_tree_less__non_inited_first(void** state);
void test__avl_tree_less__non_inited_second(void** state);
void test__avl_tree_less__not_same_type(void** state);
void test__avl_tree_less__same_avl_tree(void** state);
void test__avl_tree_less__size_first_less_than_second(void** state);
void test__avl_tree_less__size_first_greater_than_second(void** state);
void test__avl_tree_less__size_equal_0(void** state);
void test__avl_tree_less__size_equal_elem_first_less_than_second(void** state);
void test__avl_tree_less__size_equal_elem_first_greater_than_second(void** state);
void test__avl_tree_less__compare_less(void** state);
void test__avl_tree_less__equal(void** state);
/*
 * test _avl_tree_less_equal
 */
UT_CASE_DECLARATION(_avl_tree_less_equal)
void test__avl_tree_less_equal__null_first(void** state);
void test__avl_tree_less_equal__null_second(void** state);
void test__avl_tree_less_equal__non_inited_first(void** state);
void test__avl_tree_less_equal__non_inited_second(void** state);
void test__avl_tree_less_equal__not_same_type(void** state);
void test__avl_tree_less_equal__same_avl_tree(void** state);
void test__avl_tree_less_equal__size_first_less_than_second(void** state);
void test__avl_tree_less_equal__size_first_greater_than_second(void** state);
void test__avl_tree_less_equal__size_equal_0(void** state);
void test__avl_tree_less_equal__size_equal_elem_first_less_than_second(void** state);
void test__avl_tree_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test__avl_tree_less_equal__compare_less(void** state);
void test__avl_tree_less_equal__equal(void** state);
/*
 * test _avl_tree_greater
 */
UT_CASE_DECLARATION(_avl_tree_greater)
void test__avl_tree_greater__null_first(void** state);
void test__avl_tree_greater__null_second(void** state);
void test__avl_tree_greater__non_inited_first(void** state);
void test__avl_tree_greater__non_inited_second(void** state);
void test__avl_tree_greater__not_same_type(void** state);
void test__avl_tree_greater__same_avl_tree(void** state);
void test__avl_tree_greater__size_first_less_than_second(void** state);
void test__avl_tree_greater__size_first_greater_than_second(void** state);
void test__avl_tree_greater__size_equal_0(void** state);
void test__avl_tree_greater__size_equal_elem_first_less_than_second(void** state);
void test__avl_tree_greater__size_equal_elem_first_greater_than_second(void** state);
void test__avl_tree_greater__compare_less(void** state);
void test__avl_tree_greater__equal(void** state);
/*
 * test _avl_tree_greater_equal
 */
UT_CASE_DECLARATION(_avl_tree_greater_equal)
void test__avl_tree_greater_equal__null_first(void** state);
void test__avl_tree_greater_equal__null_second(void** state);
void test__avl_tree_greater_equal__non_inited_first(void** state);
void test__avl_tree_greater_equal__non_inited_second(void** state);
void test__avl_tree_greater_equal__not_same_type(void** state);
void test__avl_tree_greater_equal__same_avl_tree(void** state);
void test__avl_tree_greater_equal__size_first_less_than_second(void** state);
void test__avl_tree_greater_equal__size_first_greater_than_second(void** state);
void test__avl_tree_greater_equal__size_equal_0(void** state);
void test__avl_tree_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test__avl_tree_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test__avl_tree_greater_equal__compare_less(void** state);
void test__avl_tree_greater_equal__equal(void** state);
/*
 * test _avl_tree_swap
 */
UT_CASE_DECLARATION(_avl_tree_swap)
void test__avl_tree_swap__null_first(void** state);
void test__avl_tree_swap__null_second(void** state);
void test__avl_tree_swap__non_inited_first(void** state);
void test__avl_tree_swap__non_inited_second(void** state);
void test__avl_tree_swap__not_same_type(void** state);
void test__avl_tree_swap__same_avl_tree(void** state);
void test__avl_tree_swap__0_swap_n(void** state);
void test__avl_tree_swap__n_swap_0(void** state);
void test__avl_tree_swap__n_swap_n(void** state);
void test__avl_tree_swap__m_swap_n(void** state);
/*
 * test _avl_tree_insert_unique
 */
UT_CASE_DECLARATION(_avl_tree_insert_unique)
void test__avl_tree_insert_unique__null_avl_tree(void** state);
void test__avl_tree_insert_unique__null_value(void** state);
void test__avl_tree_insert_unique__non_inited(void** state);
void test__avl_tree_insert_unique__c_builtin_equal(void** state);
void test__avl_tree_insert_unique__c_builtin_not_equal(void** state);
void test__avl_tree_insert_unique__cstr_equal(void** state);
void test__avl_tree_insert_unique__cstr_not_equal(void** state);
void test__avl_tree_insert_unique__libcstl_builtin_equal(void** state);
void test__avl_tree_insert_unique__libcstl_builtin_not_equal(void** state);
void test__avl_tree_insert_unique__user_define_equal(void** state);
void test__avl_tree_insert_unique__user_define_not_equal(void** state);
/*
 * test _avl_tree_insert_equal
 */
UT_CASE_DECLARATION(_avl_tree_insert_equal)
void test__avl_tree_insert_equal__null_avl_tree(void** state);
void test__avl_tree_insert_equal__null_value(void** state);
void test__avl_tree_insert_equal__non_inited(void** state);
void test__avl_tree_insert_equal__c_builtin_equal(void** state);
void test__avl_tree_insert_equal__c_builtin_not_equal(void** state);
void test__avl_tree_insert_equal__cstr_equal(void** state);
void test__avl_tree_insert_equal__cstr_not_equal(void** state);
void test__avl_tree_insert_equal__libcstl_builtin_equal(void** state);
void test__avl_tree_insert_equal__libcstl_builtin_not_equal(void** state);
void test__avl_tree_insert_equal__user_define_equal(void** state);
void test__avl_tree_insert_equal__user_define_not_equal(void** state);
/*
 * test _avl_tree_insert_unique_range
 */
UT_CASE_DECLARATION(_avl_tree_insert_unique_range)
void test__avl_tree_insert_unique_range__null_avl_tree(void** state);
void test__avl_tree_insert_unique_range__non_inited(void** state);
void test__avl_tree_insert_unique_range__invalid_begin(void** state);
void test__avl_tree_insert_unique_range__invalid_end(void** state);
void test__avl_tree_insert_unique_range__invalid_range(void** state);
void test__avl_tree_insert_unique_range__not_same_type(void** state);
void test__avl_tree_insert_unique_range__empty(void** state);
void test__avl_tree_insert_unique_range__non_empty_equal(void** state);
void test__avl_tree_insert_unique_range__non_empty_dest_src_dup(void** state);
void test__avl_tree_insert_unique_range__non_empty_src_dup(void** state);
void test__avl_tree_insert_unique_range__other_container_range(void** state);
/*
 * test _avl_tree_insert_unique_array
 */
UT_CASE_DECLARATION(_avl_tree_insert_unique_array)
void test__avl_tree_insert_unique_array__null_avl_tree(void** state);
void test__avl_tree_insert_unique_array__non_inited(void** state);
void test__avl_tree_insert_unique_array__invalid_array(void** state);
void test__avl_tree_insert_unique_array__empty(void** state);
void test__avl_tree_insert_unique_array__non_empty_equal(void** state);
void test__avl_tree_insert_unique_array__non_empty_dest_src_dup(void** state);
void test__avl_tree_insert_unique_array__non_empty_src_dup(void** state);
/*
 * test _avl_tree_insert_equal_range
 */
UT_CASE_DECLARATION(_avl_tree_insert_equal_range)
void test__avl_tree_insert_equal_range__null_avl_tree(void** state);
void test__avl_tree_insert_equal_range__non_inited(void** state);
void test__avl_tree_insert_equal_range__invalid_begin(void** state);
void test__avl_tree_insert_equal_range__invalid_end(void** state);
void test__avl_tree_insert_equal_range__invalid_range(void** state);
void test__avl_tree_insert_equal_range__not_same_type(void** state);
void test__avl_tree_insert_equal_range__empty(void** state);
void test__avl_tree_insert_equal_range__non_empty_equal(void** state);
void test__avl_tree_insert_equal_range__non_empty_dest_src_dup(void** state);
void test__avl_tree_insert_equal_range__non_empty_src_dup(void** state);
/*
 * test _avl_tree_insert_equal_array
 */
UT_CASE_DECLARATION(_avl_tree_insert_equal_array)
void test__avl_tree_insert_equal_array__null_avl_tree(void** state);
void test__avl_tree_insert_equal_array__non_inited(void** state);
void test__avl_tree_insert_equal_array__invalid_array(void** state);
void test__avl_tree_insert_equal_array__empty(void** state);
void test__avl_tree_insert_equal_array__non_empty_equal(void** state);
void test__avl_tree_insert_equal_array__non_empty_dest_src_dup(void** state);
void test__avl_tree_insert_equal_array__non_empty_src_dup(void** state);
/*
 * test _avl_tree_erase_pos
 */
UT_CASE_DECLARATION(_avl_tree_erase_pos)
void test__avl_tree_erase_pos__null_avl_tree(void** state);
void test__avl_tree_erase_pos__non_inited(void** state);
void test__avl_tree_erase_pos__invalid_pos(void** state);
void test__avl_tree_erase_pos__end(void** state);
void test__avl_tree_erase_pos__begin(void** state);
void test__avl_tree_erase_pos__middle(void** state);
void test__avl_tree_erase_pos__last(void** state);
void test__avl_tree_erase_pos__erase_empty(void** state);
/*
 * test _avl_tree_erase_range
 */
UT_CASE_DECLARATION(_avl_tree_erase_range)
void test__avl_tree_erase_range__null_avl_tree(void** state);
void test__avl_tree_erase_range__non_inited(void** state);
void test__avl_tree_erase_range__invalid_begin(void** state);
void test__avl_tree_erase_range__invalid_end(void** state);
void test__avl_tree_erase_range__invalid_range(void** state);
void test__avl_tree_erase_range__empty(void** state);
void test__avl_tree_erase_range__begin(void** state);
void test__avl_tree_erase_range__middle(void** state);
void test__avl_tree_erase_range__end(void** state);
void test__avl_tree_erase_range__all(void** state);
/*
 * test _avl_tree_erase
 */
UT_CASE_DECLARATION(_avl_tree_erase)
void test__avl_tree_erase__null_avl_tree(void** state);
void test__avl_tree_erase__null_value(void** state);
void test__avl_tree_erase__non_inited(void** state);
void test__avl_tree_erase__c_builtin_0(void** state);
void test__avl_tree_erase__c_builtin_1(void** state);
void test__avl_tree_erase__c_builtin_n(void** state);
void test__avl_tree_erase__cstr_0(void** state);
void test__avl_tree_erase__cstr_1(void** state);
void test__avl_tree_erase__cstr_n(void** state);
void test__avl_tree_erase__libcstl_builtin_0(void** state);
void test__avl_tree_erase__libcstl_builtin_1(void** state);
void test__avl_tree_erase__libcstl_builtin_n(void** state);
void test__avl_tree_erase__user_define_0(void** state);
void test__avl_tree_insert_equal__user_define_1(void** state);
void test__avl_tree_insert_equal__user_define_n(void** state);

#define UT_CSTL_AVL_TREE_CASE\
    UT_SUIT_BEGIN(cstl_avl_tree, test__create_avl_tree__null_typename),\
    UT_CASE(test__create_avl_tree__c_builtin),\
    UT_CASE(test__create_avl_tree__cstr),\
    UT_CASE(test__create_avl_tree__libcstl_builtin),\
    UT_CASE(test__create_avl_tree__user_define),\
    UT_CASE(test__create_avl_tree__unregister),\
    UT_CASE_BEGIN(_avl_tree_init,  test__avl_tree_init__null_avl_tree),\
    UT_CASE(test__avl_tree_init__non_created),\
    UT_CASE(test__avl_tree_init__null_compare),\
    UT_CASE(test__avl_tree_init__non_null_compare),\
    UT_CASE_BEGIN(_avl_tree_init_copy, test__avl_tree_init_copy__null_dest),\
    UT_CASE(test__avl_tree_init_copy__null_src),\
    UT_CASE(test__avl_tree_init_copy__non_created_dest),\
    UT_CASE(test__avl_tree_init_copy__non_inited_src),\
    UT_CASE(test__avl_tree_init_copy__not_same_type),\
    UT_CASE(test__avl_tree_init_copy__empty),\
    UT_CASE(test__avl_tree_init_copy__non_empty),\
    UT_CASE(test__avl_tree_init_copy__non_null_compare),\
    UT_CASE_BEGIN(_avl_tree_init_copy_equal_range, test__avl_tree_init_copy_equal_range__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_range__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_range__invalid_begin),\
    UT_CASE(test__avl_tree_init_copy_equal_range__invalid_end),\
    UT_CASE(test__avl_tree_init_copy_equal_range__invalid_range),\
    UT_CASE(test__avl_tree_init_copy_equal_range__invalid_range_not_same_type),\
    UT_CASE(test__avl_tree_init_copy_equal_range__empty),\
    UT_CASE(test__avl_tree_init_copy_equal_range__non_empty),\
    UT_CASE(test__avl_tree_init_copy_equal_range__non_empty_dup),\
    UT_CASE_BEGIN(_avl_tree_init_copy_equal_array, test__avl_tree_init_copy_equal_array__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_array__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_array__invalid_array),\
    UT_CASE(test__avl_tree_init_copy_equal_array__empty),\
    UT_CASE(test__avl_tree_init_copy_equal_array__non_empty),\
    UT_CASE(test__avl_tree_init_copy_equal_array__non_empty_dup),\
    UT_CASE_BEGIN(_avl_tree_init_copy_unique_range, test__avl_tree_init_copy_unique_range__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_range__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_range__invalid_begin),\
    UT_CASE(test__avl_tree_init_copy_unique_range__invalid_end),\
    UT_CASE(test__avl_tree_init_copy_unique_range__invalid_range),\
    UT_CASE(test__avl_tree_init_copy_unique_range__invalid_range_not_same_type),\
    UT_CASE(test__avl_tree_init_copy_unique_range__empty),\
    UT_CASE(test__avl_tree_init_copy_unique_range__non_empty),\
    UT_CASE(test__avl_tree_init_copy_unique_range__non_empty_dup),\
    UT_CASE_BEGIN(_avl_tree_init_copy_unique_array, test__avl_tree_init_copy_unique_array__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_array__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_array__invalid_array),\
    UT_CASE(test__avl_tree_init_copy_unique_array__empty),\
    UT_CASE(test__avl_tree_init_copy_unique_array__non_empty),\
    UT_CASE(test__avl_tree_init_copy_unique_array__non_empty_dup),\
    UT_CASE_BEGIN(_avl_tree_init_copy_equal_range_ex, test__avl_tree_init_copy_equal_range_ex__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__invalid_begin),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__invalid_end),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__invalid_range),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__invalid_range_not_same_type),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__empty),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__non_empty),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__non_empty_dup),\
    UT_CASE(test__avl_tree_init_copy_equal_range_ex__compare),\
    UT_CASE_BEGIN(_avl_tree_init_copy_equal_array_ex, test__avl_tree_init_copy_equal_array_ex__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_array_ex__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_equal_array_ex__invalid_array),\
    UT_CASE(test__avl_tree_init_copy_equal_array_ex__empty),\
    UT_CASE(test__avl_tree_init_copy_equal_array_ex__non_empty),\
    UT_CASE(test__avl_tree_init_copy_equal_array_ex__non_empty_dup),\
    UT_CASE(test__avl_tree_init_copy_equal_array_ex__compare),\
    UT_CASE_BEGIN(_avl_tree_init_copy_unique_range_ex, test__avl_tree_init_copy_unique_range_ex__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__invalid_begin),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__invalid_end),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__invalid_range),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__invalid_range_not_same_type),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__empty),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__non_empty),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__non_empty_dup),\
    UT_CASE(test__avl_tree_init_copy_unique_range_ex__compare),\
    UT_CASE_BEGIN(_avl_tree_init_copy_unique_array_ex, test__avl_tree_init_copy_unique_array_ex__null_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_array_ex__non_created_avl_tree),\
    UT_CASE(test__avl_tree_init_copy_unique_array_ex__invalid_array),\
    UT_CASE(test__avl_tree_init_copy_unique_array_ex__empty),\
    UT_CASE(test__avl_tree_init_copy_unique_array_ex__non_empty),\
    UT_CASE(test__avl_tree_init_copy_unique_array_ex__non_empty_dup),\
    UT_CASE(test__avl_tree_init_copy_unique_array_ex__compare),\
    UT_CASE_BEGIN(_avl_tree_destroy, test__avl_tree_destroy__null_avl_tree),\
    UT_CASE(test__avl_tree_destroy__non_created),\
    UT_CASE(test__avl_tree_destroy__created),\
    UT_CASE(test__avl_tree_destroy__inited),\
    UT_CASE_BEGIN(_avl_tree_assign, test__avl_tree_assign__null_dest),\
    UT_CASE(test__avl_tree_assign__null_src),\
    UT_CASE(test__avl_tree_assign__non_created_dest),\
    UT_CASE(test__avl_tree_assign__non_init_src),\
    UT_CASE(test__avl_tree_assign__not_same_type),\
    UT_CASE(test__avl_tree_assign__empty_empty),\
    UT_CASE(test__avl_tree_assign__non_empty_empty),\
    UT_CASE(test__avl_tree_assign__non_empty_non_empty_less),\
    UT_CASE(test__avl_tree_assign__non_empty_non_empty_size_equal),\
    UT_CASE(test__avl_tree_assign__non_empty_non_empty_equal),\
    UT_CASE(test__avl_tree_assign__non_empty_non_empty_greater),\
    UT_CASE(test__avl_tree_assign__empty_non_empty),\
    UT_CASE_BEGIN(_avl_tree_size, test__avl_tree_size__null_avl_tree),\
    UT_CASE(test__avl_tree_size__non_inited),\
    UT_CASE(test__avl_tree_size__empty),\
    UT_CASE(test__avl_tree_size__non_empty),\
    UT_CASE_BEGIN(_avl_tree_empty, test__avl_tree_empty__null_avl_tree),\
    UT_CASE(test__avl_tree_empty__non_inited),\
    UT_CASE(test__avl_tree_empty__empty),\
    UT_CASE(test__avl_tree_empty__non_empty),\
    UT_CASE_BEGIN(_avl_tree_max_size, test__avl_tree_max_size__null_avl_tree),\
    UT_CASE(test__avl_tree_max_size__non_inited),\
    UT_CASE(test__avl_tree_max_size__empty),\
    UT_CASE(test__avl_tree_max_size__non_empty),\
    UT_CASE_BEGIN(_avl_tree_begin, test__avl_tree_begin__null_avl_tree),\
    UT_CASE(test__avl_tree_begin__non_inited),\
    UT_CASE(test__avl_tree_begin__empty),\
    UT_CASE(test__avl_tree_begin__non_empty),\
    UT_CASE_BEGIN(_avl_tree_end, test__avl_tree_end__null_avl_tree),\
    UT_CASE(test__avl_tree_end__non_inited),\
    UT_CASE(test__avl_tree_end__empty),\
    UT_CASE(test__avl_tree_end__non_empty),\
    UT_CASE_BEGIN(_avl_tree_key_comp, test__avl_tree_key_comp__null_avl_tree),\
    UT_CASE(test__avl_tree_key_comp__non_inited),\
    UT_CASE(test__avl_tree_key_comp__default_key_comp),\
    UT_CASE(test__avl_tree_key_comp__user_define_key_comp),\
    UT_CASE_BEGIN(_avl_tree_find, test__avl_tree_find__null_avl_tree),\
    UT_CASE(test__avl_tree_find__null_value),\
    UT_CASE(test__avl_tree_find__non_inited),\
    UT_CASE(test__avl_tree_find__c_builtin_find),\
    UT_CASE(test__avl_tree_find__c_builtin_not_find),\
    UT_CASE(test__avl_tree_find__cstr_find),\
    UT_CASE(test__avl_tree_find__cstr_not_find),\
    UT_CASE(test__avl_tree_find__libcstl_builtin_find),\
    UT_CASE(test__avl_tree_find__libcstl_builtin_not_find),\
    UT_CASE(test__avl_tree_find__user_define_find),\
    UT_CASE(test__avl_tree_find__user_define_not_find),\
    UT_CASE_BEGIN(_avl_tree_clear, test__avl_tree_clear__null_avl_tree),\
    UT_CASE(test__avl_tree_clear__non_inited),\
    UT_CASE(test__avl_tree_clear__empty),\
    UT_CASE(test__avl_tree_clear__non_empty),\
    UT_CASE_BEGIN(_avl_tree_count, test__avl_tree_count__null_avl_tree),\
    UT_CASE(test__avl_tree_count__null_value),\
    UT_CASE(test__avl_tree_count__non_inited),\
    UT_CASE(test__avl_tree_count__c_builtin_0),\
    UT_CASE(test__avl_tree_count__c_builtin_1),\
    UT_CASE(test__avl_tree_count__c_builtin_n),\
    UT_CASE(test__avl_tree_count__cstr_0),\
    UT_CASE(test__avl_tree_count__cstr_1),\
    UT_CASE(test__avl_tree_count__cstr_n),\
    UT_CASE(test__avl_tree_count__libcstl_builtin_0),\
    UT_CASE(test__avl_tree_count__libcstl_builtin_1),\
    UT_CASE(test__avl_tree_count__libcstl_builtin_n),\
    UT_CASE(test__avl_tree_count__user_define_0),\
    UT_CASE(test__avl_tree_count__user_define_1),\
    UT_CASE(test__avl_tree_count__user_define_n),\
    UT_CASE_BEGIN(_avl_tree_lower_bound, test__avl_tree_lower_bound__null_avl_tree),\
    UT_CASE(test__avl_tree_lower_bound__null_value),\
    UT_CASE(test__avl_tree_lower_bound__non_inited),\
    UT_CASE(test__avl_tree_lower_bound__c_builtin_equal),\
    UT_CASE(test__avl_tree_lower_bound__c_builtin_greater),\
    UT_CASE(test__avl_tree_lower_bound__cstr_lower_equal),\
    UT_CASE(test__avl_tree_lower_bound__cstr_greater),\
    UT_CASE(test__avl_tree_lower_bound__libcstl_builtin_equal),\
    UT_CASE(test__avl_tree_lower_bound__libcstl_builtin_greater),\
    UT_CASE(test__avl_tree_lower_bound__user_define_equal),\
    UT_CASE(test__avl_tree_lower_bound__user_define_greater),\
    UT_CASE_BEGIN(_avl_tree_upper_bound, test__avl_tree_upper_bound__null_avl_tree),\
    UT_CASE(test__avl_tree_upper_bound__null_value),\
    UT_CASE(test__avl_tree_upper_bound__non_inited),\
    UT_CASE(test__avl_tree_upper_bound__c_builtin_equal),\
    UT_CASE(test__avl_tree_upper_bound__c_builtin_greater),\
    UT_CASE(test__avl_tree_upper_bound__cstr_upper_equal),\
    UT_CASE(test__avl_tree_upper_bound__cstr_greater),\
    UT_CASE(test__avl_tree_upper_bound__libcstl_builtin_equal),\
    UT_CASE(test__avl_tree_upper_bound__libcstl_builtin_greater),\
    UT_CASE(test__avl_tree_upper_bound__user_define_equal),\
    UT_CASE(test__avl_tree_upper_bound__user_define_greater),\
    UT_CASE_BEGIN(_avl_tree_equal_range, test__avl_tree_equal_range__null_avl_tree),\
    UT_CASE(test__avl_tree_equal_range__null_value),\
    UT_CASE(test__avl_tree_equal_range__non_inited),\
    UT_CASE(test__avl_tree_equal_range__c_builtin_equal),\
    UT_CASE(test__avl_tree_equal_range__c_builtin_greater),\
    UT_CASE(test__avl_tree_equal_range__cstr_upper_equal),\
    UT_CASE(test__avl_tree_equal_range__cstr_greater),\
    UT_CASE(test__avl_tree_equal_range__libcstl_builtin_equal),\
    UT_CASE(test__avl_tree_equal_range__libcstl_builtin_greater),\
    UT_CASE(test__avl_tree_equal_range__user_define_equal),\
    UT_CASE(test__avl_tree_equal_range__user_define_greater),\
    UT_CASE_BEGIN(_avl_tree_equal, test__avl_tree_equal__null_first),\
    UT_CASE(test__avl_tree_equal__null_second),\
    UT_CASE(test__avl_tree_equal__non_inited_first),\
    UT_CASE(test__avl_tree_equal__non_inited_second),\
    UT_CASE(test__avl_tree_equal__not_same_type),\
    UT_CASE(test__avl_tree_equal__same_avl_tree),\
    UT_CASE(test__avl_tree_equal__size_first_less_than_second),\
    UT_CASE(test__avl_tree_equal__size_first_greater_than_second),\
    UT_CASE(test__avl_tree_equal__size_equal_0),\
    UT_CASE(test__avl_tree_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__avl_tree_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__avl_tree_equal__compare_not_equal),\
    UT_CASE(test__avl_tree_equal__equal),\
    UT_CASE_BEGIN(_avl_tree_not_equal, test__avl_tree_not_equal__null_first),\
    UT_CASE(test__avl_tree_not_equal__null_second),\
    UT_CASE(test__avl_tree_not_equal__non_inited_first),\
    UT_CASE(test__avl_tree_not_equal__non_inited_second),\
    UT_CASE(test__avl_tree_not_equal__not_same_type),\
    UT_CASE(test__avl_tree_not_equal__same_avl_tree),\
    UT_CASE(test__avl_tree_not_equal__size_first_less_than_second),\
    UT_CASE(test__avl_tree_not_equal__size_first_greater_than_second),\
    UT_CASE(test__avl_tree_not_equal__size_equal_0),\
    UT_CASE(test__avl_tree_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__avl_tree_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__avl_tree_not_equal__compare_not_equal),\
    UT_CASE(test__avl_tree_not_equal__equal),\
    UT_CASE_BEGIN(_avl_tree_less, test__avl_tree_less__null_first),\
    UT_CASE(test__avl_tree_less__null_second),\
    UT_CASE(test__avl_tree_less__non_inited_first),\
    UT_CASE(test__avl_tree_less__non_inited_second),\
    UT_CASE(test__avl_tree_less__not_same_type),\
    UT_CASE(test__avl_tree_less__same_avl_tree),\
    UT_CASE(test__avl_tree_less__size_first_less_than_second),\
    UT_CASE(test__avl_tree_less__size_first_greater_than_second),\
    UT_CASE(test__avl_tree_less__size_equal_0),\
    UT_CASE(test__avl_tree_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test__avl_tree_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__avl_tree_less__compare_less),\
    UT_CASE(test__avl_tree_less__equal),\
    UT_CASE_BEGIN(_avl_tree_less_equal, test__avl_tree_less_equal__null_first),\
    UT_CASE(test__avl_tree_less_equal__null_second),\
    UT_CASE(test__avl_tree_less_equal__non_inited_first),\
    UT_CASE(test__avl_tree_less_equal__non_inited_second),\
    UT_CASE(test__avl_tree_less_equal__not_same_type),\
    UT_CASE(test__avl_tree_less_equal__same_avl_tree),\
    UT_CASE(test__avl_tree_less_equal__size_first_less_than_second),\
    UT_CASE(test__avl_tree_less_equal__size_first_greater_than_second),\
    UT_CASE(test__avl_tree_less_equal__size_equal_0),\
    UT_CASE(test__avl_tree_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__avl_tree_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__avl_tree_less_equal__compare_less),\
    UT_CASE(test__avl_tree_less_equal__equal),\
    UT_CASE_BEGIN(_avl_tree_greater, test__avl_tree_greater__null_first),\
    UT_CASE(test__avl_tree_greater__null_second),\
    UT_CASE(test__avl_tree_greater__non_inited_first),\
    UT_CASE(test__avl_tree_greater__non_inited_second),\
    UT_CASE(test__avl_tree_greater__not_same_type),\
    UT_CASE(test__avl_tree_greater__same_avl_tree),\
    UT_CASE(test__avl_tree_greater__size_first_less_than_second),\
    UT_CASE(test__avl_tree_greater__size_first_greater_than_second),\
    UT_CASE(test__avl_tree_greater__size_equal_0),\
    UT_CASE(test__avl_tree_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test__avl_tree_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__avl_tree_greater__compare_less),\
    UT_CASE(test__avl_tree_greater__equal),\
    UT_CASE_BEGIN(_avl_tree_greater_equal, test__avl_tree_greater_equal__null_first),\
    UT_CASE(test__avl_tree_greater_equal__null_second),\
    UT_CASE(test__avl_tree_greater_equal__non_inited_first),\
    UT_CASE(test__avl_tree_greater_equal__non_inited_second),\
    UT_CASE(test__avl_tree_greater_equal__not_same_type),\
    UT_CASE(test__avl_tree_greater_equal__same_avl_tree),\
    UT_CASE(test__avl_tree_greater_equal__size_first_less_than_second),\
    UT_CASE(test__avl_tree_greater_equal__size_first_greater_than_second),\
    UT_CASE(test__avl_tree_greater_equal__size_equal_0),\
    UT_CASE(test__avl_tree_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__avl_tree_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__avl_tree_greater_equal__compare_less),\
    UT_CASE(test__avl_tree_greater_equal__equal),\
    UT_CASE_BEGIN(_avl_tree_swap, test__avl_tree_swap__null_first),\
    UT_CASE(test__avl_tree_swap__null_second),\
    UT_CASE(test__avl_tree_swap__non_inited_first),\
    UT_CASE(test__avl_tree_swap__non_inited_second),\
    UT_CASE(test__avl_tree_swap__not_same_type),\
    UT_CASE(test__avl_tree_swap__same_avl_tree),\
    UT_CASE(test__avl_tree_swap__0_swap_n),\
    UT_CASE(test__avl_tree_swap__n_swap_0),\
    UT_CASE(test__avl_tree_swap__n_swap_n),\
    UT_CASE(test__avl_tree_swap__m_swap_n),\
    UT_CASE_BEGIN(_avl_tree_insert_unique, test__avl_tree_insert_unique__null_avl_tree),\
    UT_CASE(test__avl_tree_insert_unique__null_value),\
    UT_CASE(test__avl_tree_insert_unique__non_inited),\
    UT_CASE(test__avl_tree_insert_unique__c_builtin_equal),\
    UT_CASE(test__avl_tree_insert_unique__c_builtin_not_equal),\
    UT_CASE(test__avl_tree_insert_unique__cstr_equal),\
    UT_CASE(test__avl_tree_insert_unique__cstr_not_equal),\
    UT_CASE(test__avl_tree_insert_unique__libcstl_builtin_equal),\
    UT_CASE(test__avl_tree_insert_unique__libcstl_builtin_not_equal),\
    UT_CASE(test__avl_tree_insert_unique__user_define_equal),\
    UT_CASE(test__avl_tree_insert_unique__user_define_not_equal),\
    UT_CASE_BEGIN(_avl_tree_insert_equal, test__avl_tree_insert_equal__null_avl_tree),\
    UT_CASE(test__avl_tree_insert_equal__null_value),\
    UT_CASE(test__avl_tree_insert_equal__non_inited),\
    UT_CASE(test__avl_tree_insert_equal__c_builtin_equal),\
    UT_CASE(test__avl_tree_insert_equal__c_builtin_not_equal),\
    UT_CASE(test__avl_tree_insert_equal__cstr_equal),\
    UT_CASE(test__avl_tree_insert_equal__cstr_not_equal),\
    UT_CASE(test__avl_tree_insert_equal__libcstl_builtin_equal),\
    UT_CASE(test__avl_tree_insert_equal__libcstl_builtin_not_equal),\
    UT_CASE(test__avl_tree_insert_equal__user_define_equal),\
    UT_CASE(test__avl_tree_insert_equal__user_define_not_equal),\
    UT_CASE_BEGIN(_avl_tree_insert_unique_range, test__avl_tree_insert_unique_range__null_avl_tree),\
    UT_CASE(test__avl_tree_insert_unique_range__non_inited),\
    UT_CASE(test__avl_tree_insert_unique_range__invalid_begin),\
    UT_CASE(test__avl_tree_insert_unique_range__invalid_end),\
    UT_CASE(test__avl_tree_insert_unique_range__invalid_range),\
    UT_CASE(test__avl_tree_insert_unique_range__not_same_type),\
    UT_CASE(test__avl_tree_insert_unique_range__empty),\
    UT_CASE(test__avl_tree_insert_unique_range__non_empty_equal),\
    UT_CASE(test__avl_tree_insert_unique_range__non_empty_dest_src_dup),\
    UT_CASE(test__avl_tree_insert_unique_range__non_empty_src_dup),\
    UT_CASE(test__avl_tree_insert_unique_range__other_container_range),\
    UT_CASE_BEGIN(_avl_tree_insert_unique_array, test__avl_tree_insert_unique_array__null_avl_tree),\
    UT_CASE(test__avl_tree_insert_unique_array__non_inited),\
    UT_CASE(test__avl_tree_insert_unique_array__invalid_array),\
    UT_CASE(test__avl_tree_insert_unique_array__empty),\
    UT_CASE(test__avl_tree_insert_unique_array__non_empty_equal),\
    UT_CASE(test__avl_tree_insert_unique_array__non_empty_dest_src_dup),\
    UT_CASE(test__avl_tree_insert_unique_array__non_empty_src_dup),\
    UT_CASE_BEGIN(_avl_tree_insert_equal_range, test__avl_tree_insert_equal_range__null_avl_tree),\
    UT_CASE(test__avl_tree_insert_equal_range__non_inited),\
    UT_CASE(test__avl_tree_insert_equal_range__invalid_begin),\
    UT_CASE(test__avl_tree_insert_equal_range__invalid_end),\
    UT_CASE(test__avl_tree_insert_equal_range__invalid_range),\
    UT_CASE(test__avl_tree_insert_equal_range__not_same_type),\
    UT_CASE(test__avl_tree_insert_equal_range__empty),\
    UT_CASE(test__avl_tree_insert_equal_range__non_empty_equal),\
    UT_CASE(test__avl_tree_insert_equal_range__non_empty_dest_src_dup),\
    UT_CASE(test__avl_tree_insert_equal_range__non_empty_src_dup),\
    UT_CASE_BEGIN(_avl_tree_insert_equal_array, test__avl_tree_insert_equal_array__null_avl_tree),\
    UT_CASE(test__avl_tree_insert_equal_array__non_inited),\
    UT_CASE(test__avl_tree_insert_equal_array__invalid_array),\
    UT_CASE(test__avl_tree_insert_equal_array__empty),\
    UT_CASE(test__avl_tree_insert_equal_array__non_empty_equal),\
    UT_CASE(test__avl_tree_insert_equal_array__non_empty_dest_src_dup),\
    UT_CASE(test__avl_tree_insert_equal_array__non_empty_src_dup),\
    UT_CASE_BEGIN(_avl_tree_erase_pos, test__avl_tree_erase_pos__null_avl_tree),\
    UT_CASE(test__avl_tree_erase_pos__non_inited),\
    UT_CASE(test__avl_tree_erase_pos__invalid_pos),\
    UT_CASE(test__avl_tree_erase_pos__end),\
    UT_CASE(test__avl_tree_erase_pos__begin),\
    UT_CASE(test__avl_tree_erase_pos__middle),\
    UT_CASE(test__avl_tree_erase_pos__last),\
    UT_CASE(test__avl_tree_erase_pos__erase_empty),\
    UT_CASE_BEGIN(_avl_tree_erase_range, test__avl_tree_erase_range__null_avl_tree),\
    UT_CASE(test__avl_tree_erase_range__non_inited),\
    UT_CASE(test__avl_tree_erase_range__invalid_begin),\
    UT_CASE(test__avl_tree_erase_range__invalid_end),\
    UT_CASE(test__avl_tree_erase_range__invalid_range),\
    UT_CASE(test__avl_tree_erase_range__empty),\
    UT_CASE(test__avl_tree_erase_range__begin),\
    UT_CASE(test__avl_tree_erase_range__middle),\
    UT_CASE(test__avl_tree_erase_range__end),\
    UT_CASE(test__avl_tree_erase_range__all),\
    UT_CASE_BEGIN(_avl_tree_erase, test__avl_tree_erase__null_avl_tree),\
    UT_CASE(test__avl_tree_erase__null_value),\
    UT_CASE(test__avl_tree_erase__non_inited),\
    UT_CASE(test__avl_tree_erase__c_builtin_0),\
    UT_CASE(test__avl_tree_erase__c_builtin_1),\
    UT_CASE(test__avl_tree_erase__c_builtin_n),\
    UT_CASE(test__avl_tree_erase__cstr_0),\
    UT_CASE(test__avl_tree_erase__cstr_1),\
    UT_CASE(test__avl_tree_erase__cstr_n),\
    UT_CASE(test__avl_tree_erase__libcstl_builtin_0),\
    UT_CASE(test__avl_tree_erase__libcstl_builtin_1),\
    UT_CASE(test__avl_tree_erase__libcstl_builtin_n),\
    UT_CASE(test__avl_tree_erase__user_define_0),\
    UT_CASE(test__avl_tree_insert_equal__user_define_1),\
    UT_CASE(test__avl_tree_insert_equal__user_define_n)

#endif /* _UT_CSTL_AVL_TREE_H_ */

