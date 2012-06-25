#ifndef _UT_CSTL_HASHTABLE_H_
#define _UT_CSTL_HASHTABLE_H_

UT_SUIT_DECLARATION(cstl_hashtable)
/*
 * test _create_hashtable
 */
UT_CASE_DECLARATION(_create_hashtable)
void test__create_hashtable__null_typename(void** state);
void test__create_hashtable__c_builtin(void** state);
void test__create_hashtable__cstr(void** state);
void test__create_hashtable__libcstl_builtin(void** state);
void test__create_hashtable__user_define(void** state);
void test__create_hashtable__unregister(void** state);
/*
 * test _hashtable_init
 */
UT_CASE_DECLARATION(_hashtable_init)
void test__hashtable_init__null_hashtable(void** state);
void test__hashtable_init__non_created(void** state);
void test__hashtable_init__bucket_0(void** state);
void test__hashtable_init__bucket_not_0(void** state);
void test__hashtable_init__null_hash(void** state);
void test__hashtable_init__non_null_hash(void** state);
void test__hashtable_init__null_compare(void** state);
void test__hashtable_init__non_null_compare(void** state);
/*
 * test _hashtable_init_copy
 */
UT_CASE_DECLARATION(_hashtable_init_copy)
void test__hashtable_init_copy__null_dest(void** state);
void test__hashtable_init_copy__null_src(void** state);
void test__hashtable_init_copy__non_created_dest(void** state);
void test__hashtable_init_copy__non_inited_src(void** state);
void test__hashtable_init_copy__not_same_type(void** state);
void test__hashtable_init_copy__empty(void** state);
void test__hashtable_init_copy__non_empty(void** state);
void test__hashtable_init_copy__non_null_hash(void** state);
void test__hashtable_init_copy__non_null_compare(void** state);
/*
 * test _hashtable_init_copy_equal_range
 */
UT_CASE_DECLARATION(_hashtable_init_copy_equal_range)
void test__hashtable_init_copy_equal_range__null_hashtable(void** state);
void test__hashtable_init_copy_equal_range__non_created_hashtable(void** state);
void test__hashtable_init_copy_equal_range__invalid_begin(void** state);
void test__hashtable_init_copy_equal_range__invalid_end(void** state);
void test__hashtable_init_copy_equal_range__invalid_range(void** state);
void test__hashtable_init_copy_equal_range__invalid_range_not_same_type(void** state);
void test__hashtable_init_copy_equal_range__empty(void** state);
void test__hashtable_init_copy_equal_range__non_empty(void** state);
void test__hashtable_init_copy_equal_range__non_empty_dup(void** state);
void test__hashtable_init_copy_equal_range__bucketcount(void** state);
void test__hashtable_init_copy_equal_range__non_null_hash(void** state);
void test__hashtable_init_copy_equal_range__non_null_compare(void** state);
/*
 * test _hashtable_init_copy_equal_array
 */
UT_CASE_DECLARATION(_hashtable_init_copy_equal_array)
void test__hashtable_init_copy_equal_array__null_hashtable(void** state);
void test__hashtable_init_copy_equal_array__non_created_hashtable(void** state);
void test__hashtable_init_copy_equal_array__invalid_array(void** state);
void test__hashtable_init_copy_equal_array__empty(void** state);
void test__hashtable_init_copy_equal_array__non_empty(void** state);
void test__hashtable_init_copy_equal_array__non_empty_dup(void** state);
void test__hashtable_init_copy_equal_array__bucketcount(void** state);
void test__hashtable_init_copy_equal_array__non_null_hash(void** state);
void test__hashtable_init_copy_equal_array__non_null_compare(void** state);
/*
 * test _hashtable_init_copy_unique_range
 */
UT_CASE_DECLARATION(_hashtable_init_copy_unique_range)
void test__hashtable_init_copy_unique_range__null_hashtable(void** state);
void test__hashtable_init_copy_unique_range__non_created_hashtable(void** state);
void test__hashtable_init_copy_unique_range__invalid_begin(void** state);
void test__hashtable_init_copy_unique_range__invalid_end(void** state);
void test__hashtable_init_copy_unique_range__invalid_range(void** state);
void test__hashtable_init_copy_unique_range__invalid_range_not_same_type(void** state);
void test__hashtable_init_copy_unique_range__empty(void** state);
void test__hashtable_init_copy_unique_range__non_empty(void** state);
void test__hashtable_init_copy_unique_range__non_empty_dup(void** state);
void test__hashtable_init_copy_unique_range__bucketcount(void** state);
void test__hashtable_init_copy_unique_range__non_null_hash(void** state);
void test__hashtable_init_copy_unique_range__non_null_compare(void** state);
/*
 * test _hashtable_init_copy_unique_array
 */
UT_CASE_DECLARATION(_hashtable_init_copy_unique_array)
void test__hashtable_init_copy_unique_array__null_hashtable(void** state);
void test__hashtable_init_copy_unique_array__non_created_hashtable(void** state);
void test__hashtable_init_copy_unique_array__invalid_array(void** state);
void test__hashtable_init_copy_unique_array__empty(void** state);
void test__hashtable_init_copy_unique_array__non_empty(void** state);
void test__hashtable_init_copy_unique_array__non_empty_dup(void** state);
void test__hashtable_init_copy_unique_array__bucketcount(void** state);
void test__hashtable_init_copy_unique_array__non_null_hash(void** state);
void test__hashtable_init_copy_unique_array__non_null_compare(void** state);
/*
 * test _hashtable_destroy
 */
UT_CASE_DECLARATION(_hashtable_destroy)
void test__hashtable_destroy__null_hashtable(void** state);
void test__hashtable_destroy__non_created(void** state);
void test__hashtable_destroy__created(void** state);
void test__hashtable_destroy__inited(void** state);
/*
 * test _hashtable_assign
 */
UT_CASE_DECLARATION(_hashtable_assign)
void test__hashtable_assign__null_dest(void** state);
void test__hashtable_assign__null_src(void** state);
void test__hashtable_assign__non_created_dest(void** state);
void test__hashtable_assign__non_init_src(void** state);
void test__hashtable_assign__not_same_type(void** state);
void test__hashtable_assign__empty_empty(void** state);
void test__hashtable_assign__non_empty_empty(void** state);
void test__hashtable_assign__non_empty_non_empty_less(void** state);
void test__hashtable_assign__non_empty_non_empty_size_equal(void** state);
void test__hashtable_assign__non_empty_non_empty_equal(void** state);
void test__hashtable_assign__non_empty_non_empty_greater(void** state);
void test__hashtable_assign__empty_non_empty(void** state);
void test__hashtable_assign__not_same_bucketcount(void** state);
/*
 * test _hashtable_size
 */
UT_CASE_DECLARATION(_hashtable_size)
void test__hashtable_size__null_hashtable(void** state);
void test__hashtable_size__non_inited(void** state);
void test__hashtable_size__empty(void** state);
void test__hashtable_size__non_empty(void** state);
/*
 * test _hashtable_emtpy
 */
UT_CASE_DECLARATION(_hashtable_empty)
void test__hashtable_empty__null_hashtable(void** state);
void test__hashtable_empty__non_inited(void** state);
void test__hashtable_empty__empty(void** state);
void test__hashtable_empty__non_empty(void** state);
/*
 * test _hashtable_max_size
 */
UT_CASE_DECLARATION(_hashtable_max_size)
void test__hashtable_max_size__null_hashtable(void** state);
void test__hashtable_max_size__non_inited(void** state);
void test__hashtable_max_size__empty(void** state);
void test__hashtable_max_size__non_empty(void** state);
/*
 * test _hashtable_bucket_count
 */
UT_CASE_DECLARATION(_hashtable_bucket_count)
void test__hashtable_bucket_count__null_hashtable(void** state);
void test__hashtable_bucket_count__non_inited(void** state);
void test__hashtable_bucket_count__53(void** state);
void test__hashtable_bucket_count__193(void** state);
void test__hashtable_bucket_count__change(void** state);
/*
 * test _hashtable_begin
 */
UT_CASE_DECLARATION(_hashtable_begin)
void test__hashtable_begin__null_hashtable(void** state);
void test__hashtable_begin__non_inited(void** state);
void test__hashtable_begin__empty(void** state);
void test__hashtable_begin__non_empty(void** state);
/*
 * test _hashtable_end
 */
UT_CASE_DECLARATION(_hashtable_end)
void test__hashtable_end__null_hashtable(void** state);
void test__hashtable_end__non_inited(void** state);
void test__hashtable_end__empty(void** state);
void test__hashtable_end__non_empty(void** state);
/*
 * test _hashtable_key_comp
 */
UT_CASE_DECLARATION(_hashtable_key_comp)
void test__hashtable_key_comp__null_hashtable(void** state);
void test__hashtable_key_comp__non_inited(void** state);
void test__hashtable_key_comp__default_key_comp(void** state);
void test__hashtable_key_comp__user_define_key_comp(void** state);
/*
 * test _hashtable_hash
 */
UT_CASE_DECLARATION(_hashtable_hash)
void test__hashtable_hash__null_hashtable(void** state);
void test__hashtable_hash__non_inited(void** state);
void test__hashtable_hash__default_hash(void** state);
void test__hashtable_hash__user_define_hash(void** state);
/*
 * test _hashtable_find
 */
UT_CASE_DECLARATION(_hashtable_find)
void test__hashtable_find__null_hashtable(void** state);
void test__hashtable_find__null_value(void** state);
void test__hashtable_find__non_inited(void** state);
void test__hashtable_find__c_builtin_find(void** state);
void test__hashtable_find__c_builtin_not_find(void** state);
void test__hashtable_find__cstr_find(void** state);
void test__hashtable_find__cstr_not_find(void** state);
void test__hashtable_find__libcstl_builtin_find(void** state);
void test__hashtable_find__libcstl_builtin_not_find(void** state);
void test__hashtable_find__user_define_find(void** state);
void test__hashtable_find__user_define_not_find(void** state);
/*
 * test _hashtable_clear
 */
UT_CASE_DECLARATION(_hashtable_clear)
void test__hashtable_clear__null_hashtable(void** state);
void test__hashtable_clear__non_inited(void** state);
void test__hashtable_clear__empty(void** state);
void test__hashtable_clear__non_empty(void** state);
/*
 * test _hashtable_count
 */
UT_CASE_DECLARATION(_hashtable_count)
void test__hashtable_count__null_hashtable(void** state);
void test__hashtable_count__null_value(void** state);
void test__hashtable_count__non_inited(void** state);
void test__hashtable_count__c_builtin_0(void** state);
void test__hashtable_count__c_builtin_1(void** state);
void test__hashtable_count__c_builtin_n(void** state);
void test__hashtable_count__cstr_0(void** state);
void test__hashtable_count__cstr_1(void** state);
void test__hashtable_count__cstr_n(void** state);
void test__hashtable_count__libcstl_builtin_0(void** state);
void test__hashtable_count__libcstl_builtin_1(void** state);
void test__hashtable_count__libcstl_builtin_n(void** state);
void test__hashtable_count__user_define_0(void** state);
void test__hashtable_count__user_define_1(void** state);
void test__hashtable_count__user_define_n(void** state);
/*
 * test _hashtable_equal_range
 */
UT_CASE_DECLARATION(_hashtable_equal_range)
void test__hashtable_equal_range__null_hashtable(void** state);
void test__hashtable_equal_range__null_value(void** state);
void test__hashtable_equal_range__non_inited(void** state);
void test__hashtable_equal_range__end(void** state);
void test__hashtable_equal_range__c_builtin_equal(void** state);
void test__hashtable_equal_range__c_builtin_greater(void** state);
void test__hashtable_equal_range__cstr_upper_equal(void** state);
void test__hashtable_equal_range__cstr_greater(void** state);
void test__hashtable_equal_range__libcstl_builtin_equal(void** state);
void test__hashtable_equal_range__libcstl_builtin_greater(void** state);
void test__hashtable_equal_range__user_define_equal(void** state);
void test__hashtable_equal_range__user_define_greater(void** state);
/*
 * test _hashtable_equal
 */
UT_CASE_DECLARATION(_hashtable_equal)
void test__hashtable_equal__null_first(void** state);
void test__hashtable_equal__null_second(void** state);
void test__hashtable_equal__non_inited_first(void** state);
void test__hashtable_equal__non_inited_second(void** state);
void test__hashtable_equal__not_same_type(void** state);
void test__hashtable_equal__not_same_bucket(void** state);
void test__hashtable_equal__same_hashtable(void** state);
void test__hashtable_equal__size_first_less_than_second(void** state);
void test__hashtable_equal__size_first_greater_than_second(void** state);
void test__hashtable_equal__size_equal_0(void** state);
void test__hashtable_equal__size_equal_elem_first_less_than_second(void** state);
void test__hashtable_equal__size_equal_elem_first_greater_than_second(void** state);
void test__hashtable_equal__compare_not_equal(void** state);
void test__hashtable_equal__equal(void** state);
/*
 * test _hashtable_not_equal
 */
UT_CASE_DECLARATION(_hashtable_not_equal)
void test__hashtable_not_equal__null_first(void** state);
void test__hashtable_not_equal__null_second(void** state);
void test__hashtable_not_equal__non_inited_first(void** state);
void test__hashtable_not_equal__non_inited_second(void** state);
void test__hashtable_not_equal__not_same_type(void** state);
void test__hashtable_not_equal__not_same_bucket(void** state);
void test__hashtable_not_equal__same_hashtable(void** state);
void test__hashtable_not_equal__size_first_less_than_second(void** state);
void test__hashtable_not_equal__size_first_greater_than_second(void** state);
void test__hashtable_not_equal__size_equal_0(void** state);
void test__hashtable_not_equal__size_equal_elem_first_less_than_second(void** state);
void test__hashtable_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test__hashtable_not_equal__compare_not_equal(void** state);
void test__hashtable_not_equal__equal(void** state);
/*
 * test _hashtable_less
 */
UT_CASE_DECLARATION(_hashtable_less)
void test__hashtable_less__null_first(void** state);
void test__hashtable_less__null_second(void** state);
void test__hashtable_less__non_inited_first(void** state);
void test__hashtable_less__non_inited_second(void** state);
void test__hashtable_less__not_same_type(void** state);
void test__hashtable_less__same_hashtable(void** state);
void test__hashtable_less__size_first_less_than_second(void** state);
void test__hashtable_less__size_first_greater_than_second(void** state);
void test__hashtable_less__size_equal_0(void** state);
void test__hashtable_less__size_equal_elem_first_less_than_second(void** state);
void test__hashtable_less__size_equal_elem_first_greater_than_second(void** state);
void test__hashtable_less__compare_less(void** state);
void test__hashtable_less__equal(void** state);
/*
 * test _hashtable_less_equal
 */
UT_CASE_DECLARATION(_hashtable_less_equal)
void test__hashtable_less_equal__null_first(void** state);
void test__hashtable_less_equal__null_second(void** state);
void test__hashtable_less_equal__non_inited_first(void** state);
void test__hashtable_less_equal__non_inited_second(void** state);
void test__hashtable_less_equal__not_same_type(void** state);
void test__hashtable_less_equal__same_hashtable(void** state);
void test__hashtable_less_equal__size_first_less_than_second(void** state);
void test__hashtable_less_equal__size_first_greater_than_second(void** state);
void test__hashtable_less_equal__size_equal_0(void** state);
void test__hashtable_less_equal__size_equal_elem_first_less_than_second(void** state);
void test__hashtable_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test__hashtable_less_equal__compare_less(void** state);
void test__hashtable_less_equal__equal(void** state);
/*
 * test _hashtable_greater
 */
UT_CASE_DECLARATION(_hashtable_greater)
void test__hashtable_greater__null_first(void** state);
void test__hashtable_greater__null_second(void** state);
void test__hashtable_greater__non_inited_first(void** state);
void test__hashtable_greater__non_inited_second(void** state);
void test__hashtable_greater__not_same_type(void** state);
void test__hashtable_greater__same_hashtable(void** state);
void test__hashtable_greater__size_first_less_than_second(void** state);
void test__hashtable_greater__size_first_greater_than_second(void** state);
void test__hashtable_greater__size_equal_0(void** state);
void test__hashtable_greater__size_equal_elem_first_less_than_second(void** state);
void test__hashtable_greater__size_equal_elem_first_greater_than_second(void** state);
void test__hashtable_greater__compare_less(void** state);
void test__hashtable_greater__equal(void** state);
/*
 * test _hashtable_greater_equal
 */
UT_CASE_DECLARATION(_hashtable_greater_equal)
void test__hashtable_greater_equal__null_first(void** state);
void test__hashtable_greater_equal__null_second(void** state);
void test__hashtable_greater_equal__non_inited_first(void** state);
void test__hashtable_greater_equal__non_inited_second(void** state);
void test__hashtable_greater_equal__not_same_type(void** state);
void test__hashtable_greater_equal__same_hashtable(void** state);
void test__hashtable_greater_equal__size_first_less_than_second(void** state);
void test__hashtable_greater_equal__size_first_greater_than_second(void** state);
void test__hashtable_greater_equal__size_equal_0(void** state);
void test__hashtable_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test__hashtable_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test__hashtable_greater_equal__compare_less(void** state);
void test__hashtable_greater_equal__equal(void** state);
/*
 * test _hashtable_swap
 */
UT_CASE_DECLARATION(_hashtable_swap)
void test__hashtable_swap__null_first(void** state);
void test__hashtable_swap__null_second(void** state);
void test__hashtable_swap__non_inited_first(void** state);
void test__hashtable_swap__non_inited_second(void** state);
void test__hashtable_swap__not_same_type(void** state);
void test__hashtable_swap__not_same_hash(void** state);
void test__hashtable_swap__same_hashtable(void** state);
void test__hashtable_swap__0_swap_n(void** state);
void test__hashtable_swap__n_swap_0(void** state);
void test__hashtable_swap__n_swap_n(void** state);
void test__hashtable_swap__m_swap_n(void** state);
/*
 * test _hashtable_insert_unique
 */
UT_CASE_DECLARATION(_hashtable_insert_unique)
void test__hashtable_insert_unique__null_hashtable(void** state);
void test__hashtable_insert_unique__null_value(void** state);
void test__hashtable_insert_unique__non_inited(void** state);
void test__hashtable_insert_unique__c_builtin_equal(void** state);
void test__hashtable_insert_unique__c_builtin_not_equal(void** state);
void test__hashtable_insert_unique__cstr_equal(void** state);
void test__hashtable_insert_unique__cstr_not_equal(void** state);
void test__hashtable_insert_unique__libcstl_builtin_equal(void** state);
void test__hashtable_insert_unique__libcstl_builtin_not_equal(void** state);
void test__hashtable_insert_unique__user_define_equal(void** state);
void test__hashtable_insert_unique__user_define_not_equal(void** state);
/*
 * test _hashtable_insert_equal
 */
UT_CASE_DECLARATION(_hashtable_insert_equal)
void test__hashtable_insert_equal__null_hashtable(void** state);
void test__hashtable_insert_equal__null_value(void** state);
void test__hashtable_insert_equal__non_inited(void** state);
void test__hashtable_insert_equal__c_builtin_equal(void** state);
void test__hashtable_insert_equal__c_builtin_not_equal(void** state);
void test__hashtable_insert_equal__cstr_equal(void** state);
void test__hashtable_insert_equal__cstr_not_equal(void** state);
void test__hashtable_insert_equal__libcstl_builtin_equal(void** state);
void test__hashtable_insert_equal__libcstl_builtin_not_equal(void** state);
void test__hashtable_insert_equal__user_define_equal(void** state);
void test__hashtable_insert_equal__user_define_not_equal(void** state);
/*
 * test _hashtable_insert_unique_range
 */
UT_CASE_DECLARATION(_hashtable_insert_unique_range)
void test__hashtable_insert_unique_range__null_hashtable(void** state);
void test__hashtable_insert_unique_range__non_inited(void** state);
void test__hashtable_insert_unique_range__invalid_begin(void** state);
void test__hashtable_insert_unique_range__invalid_end(void** state);
void test__hashtable_insert_unique_range__invalid_range(void** state);
void test__hashtable_insert_unique_range__not_same_type(void** state);
void test__hashtable_insert_unique_range__empty(void** state);
void test__hashtable_insert_unique_range__non_empty_equal(void** state);
void test__hashtable_insert_unique_range__non_empty_dest_src_dup(void** state);
void test__hashtable_insert_unique_range__non_empty_src_dup(void** state);
void test__hashtable_insert_unique_range__compare(void** state);
/*
 * test _hashtable_insert_unique_array
 */
UT_CASE_DECLARATION(_hashtable_insert_unique_array)
void test__hashtable_insert_unique_array__null_hashtable(void** state);
void test__hashtable_insert_unique_array__non_inited(void** state);
void test__hashtable_insert_unique_array__invalid_array(void** state);
void test__hashtable_insert_unique_array__empty(void** state);
void test__hashtable_insert_unique_array__non_empty_equal(void** state);
void test__hashtable_insert_unique_array__non_empty_dest_src_dup(void** state);
void test__hashtable_insert_unique_array__non_empty_src_dup(void** state);
/*
 * test _hashtable_insert_equal_range
 */
UT_CASE_DECLARATION(_hashtable_insert_equal_range)
void test__hashtable_insert_equal_range__null_hashtable(void** state);
void test__hashtable_insert_equal_range__non_inited(void** state);
void test__hashtable_insert_equal_range__invalid_begin(void** state);
void test__hashtable_insert_equal_range__invalid_end(void** state);
void test__hashtable_insert_equal_range__invalid_range(void** state);
void test__hashtable_insert_equal_range__not_same_type(void** state);
void test__hashtable_insert_equal_range__empty(void** state);
void test__hashtable_insert_equal_range__non_empty_equal(void** state);
void test__hashtable_insert_equal_range__non_empty_dest_src_dup(void** state);
void test__hashtable_insert_equal_range__non_empty_src_dup(void** state);
void test__hashtable_insert_equal_range__compare(void** state);
/*
 * test _hashtable_insert_equal_array
 */
UT_CASE_DECLARATION(_hashtable_insert_equal_array)
void test__hashtable_insert_equal_array__null_hashtable(void** state);
void test__hashtable_insert_equal_array__non_inited(void** state);
void test__hashtable_insert_equal_array__invalid_array(void** state);
void test__hashtable_insert_equal_array__empty(void** state);
void test__hashtable_insert_equal_array__non_empty_equal(void** state);
void test__hashtable_insert_equal_array__non_empty_dest_src_dup(void** state);
void test__hashtable_insert_equal_array__non_empty_src_dup(void** state);
/*
 * test _hashtable_erase_pos
 */
UT_CASE_DECLARATION(_hashtable_erase_pos)
void test__hashtable_erase_pos__null_hashtable(void** state);
void test__hashtable_erase_pos__non_inited(void** state);
void test__hashtable_erase_pos__invalid_pos(void** state);
void test__hashtable_erase_pos__end(void** state);
void test__hashtable_erase_pos__begin(void** state);
void test__hashtable_erase_pos__middle(void** state);
void test__hashtable_erase_pos__last(void** state);
void test__hashtable_erase_pos__erase_empty(void** state);
/*
 * test _hashtable_erase_range
 */
UT_CASE_DECLARATION(_hashtable_erase_range)
void test__hashtable_erase_range__null_hashtable(void** state);
void test__hashtable_erase_range__non_inited(void** state);
void test__hashtable_erase_range__invalid_begin(void** state);
void test__hashtable_erase_range__invalid_end(void** state);
void test__hashtable_erase_range__invalid_range(void** state);
void test__hashtable_erase_range__empty(void** state);
void test__hashtable_erase_range__begin(void** state);
void test__hashtable_erase_range__middle(void** state);
void test__hashtable_erase_range__end(void** state);
void test__hashtable_erase_range__all(void** state);
/*
 * test _hashtable_erase
 */
UT_CASE_DECLARATION(_hashtable_erase)
void test__hashtable_erase__null_hashtable(void** state);
void test__hashtable_erase__null_value(void** state);
void test__hashtable_erase__non_inited(void** state);
void test__hashtable_erase__c_builtin_0(void** state);
void test__hashtable_erase__c_builtin_1(void** state);
void test__hashtable_erase__c_builtin_n(void** state);
void test__hashtable_erase__cstr_0(void** state);
void test__hashtable_erase__cstr_1(void** state);
void test__hashtable_erase__cstr_n(void** state);
void test__hashtable_erase__libcstl_builtin_0(void** state);
void test__hashtable_erase__libcstl_builtin_1(void** state);
void test__hashtable_erase__libcstl_builtin_n(void** state);
void test__hashtable_erase__user_define_0(void** state);
void test__hashtable_erase__user_define_1(void** state);
void test__hashtable_erase__user_define_n(void** state);
/*
 * test _hashtable_resize
 */
UT_CASE_DECLARATION(_hashtable_resize)
void test__hashtable_resize__null_hashtable(void** state);
void test__hashtable_resize__non_inited(void** state);
void test__hashtable_resize__less_bucketcount(void** state);
void test__hashtable_resize__equal_bucketcount(void** state);
void test__hashtable_resize__greater_bucketcount(void** state);

#define UT_CSTL_HASHTABLE_CASE\
    UT_SUIT_BEGIN(cstl_hashtable, test__create_hashtable__null_typename),\
    UT_CASE(test__create_hashtable__c_builtin),\
    UT_CASE(test__create_hashtable__cstr),\
    UT_CASE(test__create_hashtable__libcstl_builtin),\
    UT_CASE(test__create_hashtable__user_define),\
    UT_CASE(test__create_hashtable__unregister),\
    UT_CASE_BEGIN(_hashtable_init,  test__hashtable_init__null_hashtable),\
    UT_CASE(test__hashtable_init__non_created),\
    UT_CASE(test__hashtable_init__bucket_0),\
    UT_CASE(test__hashtable_init__bucket_not_0),\
    UT_CASE(test__hashtable_init__null_hash),\
    UT_CASE(test__hashtable_init__non_null_hash),\
    UT_CASE(test__hashtable_init__null_compare),\
    UT_CASE(test__hashtable_init__non_null_compare),\
    UT_CASE_BEGIN(_hashtable_init_copy, test__hashtable_init_copy__null_dest),\
    UT_CASE(test__hashtable_init_copy__null_src),\
    UT_CASE(test__hashtable_init_copy__non_created_dest),\
    UT_CASE(test__hashtable_init_copy__non_inited_src),\
    UT_CASE(test__hashtable_init_copy__not_same_type),\
    UT_CASE(test__hashtable_init_copy__empty),\
    UT_CASE(test__hashtable_init_copy__non_empty),\
    UT_CASE(test__hashtable_init_copy__non_null_hash),\
    UT_CASE(test__hashtable_init_copy__non_null_compare),\
    UT_CASE_BEGIN(_hashtable_init_copy_equal_range, test__hashtable_init_copy_equal_range__null_hashtable),\
    UT_CASE(test__hashtable_init_copy_equal_range__non_created_hashtable),\
    UT_CASE(test__hashtable_init_copy_equal_range__invalid_begin),\
    UT_CASE(test__hashtable_init_copy_equal_range__invalid_end),\
    UT_CASE(test__hashtable_init_copy_equal_range__invalid_range),\
    UT_CASE(test__hashtable_init_copy_equal_range__invalid_range_not_same_type),\
    UT_CASE(test__hashtable_init_copy_equal_range__empty),\
    UT_CASE(test__hashtable_init_copy_equal_range__non_empty),\
    UT_CASE(test__hashtable_init_copy_equal_range__non_empty_dup),\
    UT_CASE(test__hashtable_init_copy_equal_range__bucketcount),\
    UT_CASE(test__hashtable_init_copy_equal_range__non_null_hash),\
    UT_CASE(test__hashtable_init_copy_equal_range__non_null_compare),\
    UT_CASE_BEGIN(_hashtable_init_copy_equal_array, test__hashtable_init_copy_equal_array__null_hashtable),\
    UT_CASE(test__hashtable_init_copy_equal_array__non_created_hashtable),\
    UT_CASE(test__hashtable_init_copy_equal_array__invalid_array),\
    UT_CASE(test__hashtable_init_copy_equal_array__empty),\
    UT_CASE(test__hashtable_init_copy_equal_array__non_empty),\
    UT_CASE(test__hashtable_init_copy_equal_array__non_empty_dup),\
    UT_CASE(test__hashtable_init_copy_equal_array__bucketcount),\
    UT_CASE(test__hashtable_init_copy_equal_array__non_null_hash),\
    UT_CASE(test__hashtable_init_copy_equal_array__non_null_compare),\
    UT_CASE_BEGIN(_hashtable_init_copy_unique_range, test__hashtable_init_copy_unique_range__null_hashtable),\
    UT_CASE(test__hashtable_init_copy_unique_range__non_created_hashtable),\
    UT_CASE(test__hashtable_init_copy_unique_range__invalid_begin),\
    UT_CASE(test__hashtable_init_copy_unique_range__invalid_end),\
    UT_CASE(test__hashtable_init_copy_unique_range__invalid_range),\
    UT_CASE(test__hashtable_init_copy_unique_range__invalid_range_not_same_type),\
    UT_CASE(test__hashtable_init_copy_unique_range__empty),\
    UT_CASE(test__hashtable_init_copy_unique_range__non_empty),\
    UT_CASE(test__hashtable_init_copy_unique_range__non_empty_dup),\
    UT_CASE(test__hashtable_init_copy_unique_range__bucketcount),\
    UT_CASE(test__hashtable_init_copy_unique_range__non_null_hash),\
    UT_CASE(test__hashtable_init_copy_unique_range__non_null_compare),\
    UT_CASE_BEGIN(_hashtable_init_copy_unique_array, test__hashtable_init_copy_unique_array__null_hashtable),\
    UT_CASE(test__hashtable_init_copy_unique_array__non_created_hashtable),\
    UT_CASE(test__hashtable_init_copy_unique_array__invalid_array),\
    UT_CASE(test__hashtable_init_copy_unique_array__empty),\
    UT_CASE(test__hashtable_init_copy_unique_array__non_empty),\
    UT_CASE(test__hashtable_init_copy_unique_array__non_empty_dup),\
    UT_CASE(test__hashtable_init_copy_unique_array__bucketcount),\
    UT_CASE(test__hashtable_init_copy_unique_array__non_null_hash),\
    UT_CASE(test__hashtable_init_copy_unique_array__non_null_compare),\
    UT_CASE_BEGIN(_hashtable_destroy, test__hashtable_destroy__null_hashtable),\
    UT_CASE(test__hashtable_destroy__non_created),\
    UT_CASE(test__hashtable_destroy__created),\
    UT_CASE(test__hashtable_destroy__inited),\
    UT_CASE_BEGIN(_hashtable_assign, test__hashtable_assign__null_dest),\
    UT_CASE(test__hashtable_assign__null_src),\
    UT_CASE(test__hashtable_assign__non_created_dest),\
    UT_CASE(test__hashtable_assign__non_init_src),\
    UT_CASE(test__hashtable_assign__not_same_type),\
    UT_CASE(test__hashtable_assign__empty_empty),\
    UT_CASE(test__hashtable_assign__non_empty_empty),\
    UT_CASE(test__hashtable_assign__non_empty_non_empty_less),\
    UT_CASE(test__hashtable_assign__non_empty_non_empty_size_equal),\
    UT_CASE(test__hashtable_assign__non_empty_non_empty_equal),\
    UT_CASE(test__hashtable_assign__non_empty_non_empty_greater),\
    UT_CASE(test__hashtable_assign__empty_non_empty),\
    UT_CASE(test__hashtable_assign__not_same_bucketcount),\
    UT_CASE_BEGIN(_hashtable_size, test__hashtable_size__null_hashtable),\
    UT_CASE(test__hashtable_size__non_inited),\
    UT_CASE(test__hashtable_size__empty),\
    UT_CASE(test__hashtable_size__non_empty),\
    UT_CASE_BEGIN(_hashtable_empty, test__hashtable_empty__null_hashtable),\
    UT_CASE(test__hashtable_empty__non_inited),\
    UT_CASE(test__hashtable_empty__empty),\
    UT_CASE(test__hashtable_empty__non_empty),\
    UT_CASE_BEGIN(_hashtable_max_size, test__hashtable_max_size__null_hashtable),\
    UT_CASE(test__hashtable_max_size__non_inited),\
    UT_CASE(test__hashtable_max_size__empty),\
    UT_CASE(test__hashtable_max_size__non_empty),\
    UT_CASE_BEGIN(_hashtable_bucket_count, test__hashtable_bucket_count__null_hashtable),\
    UT_CASE(test__hashtable_bucket_count__non_inited),\
    UT_CASE(test__hashtable_bucket_count__53),\
    UT_CASE(test__hashtable_bucket_count__193),\
    UT_CASE(test__hashtable_bucket_count__change),\
    UT_CASE_BEGIN(_hashtable_begin, test__hashtable_begin__null_hashtable),\
    UT_CASE(test__hashtable_begin__non_inited),\
    UT_CASE(test__hashtable_begin__empty),\
    UT_CASE(test__hashtable_begin__non_empty),\
    UT_CASE_BEGIN(_hashtable_end, test__hashtable_end__null_hashtable),\
    UT_CASE(test__hashtable_end__non_inited),\
    UT_CASE(test__hashtable_end__empty),\
    UT_CASE(test__hashtable_end__non_empty),\
    UT_CASE_BEGIN(_hashtable_key_comp, test__hashtable_key_comp__null_hashtable),\
    UT_CASE(test__hashtable_key_comp__non_inited),\
    UT_CASE(test__hashtable_key_comp__default_key_comp),\
    UT_CASE(test__hashtable_key_comp__user_define_key_comp),\
    UT_CASE_BEGIN(_hashtable_hash, test__hashtable_hash__null_hashtable),\
    UT_CASE(test__hashtable_hash__non_inited),\
    UT_CASE(test__hashtable_hash__default_hash),\
    UT_CASE(test__hashtable_hash__user_define_hash),\
    UT_CASE_BEGIN(_hashtable_find, test__hashtable_find__null_hashtable),\
    UT_CASE(test__hashtable_find__null_value),\
    UT_CASE(test__hashtable_find__non_inited),\
    UT_CASE(test__hashtable_find__c_builtin_find),\
    UT_CASE(test__hashtable_find__c_builtin_not_find),\
    UT_CASE(test__hashtable_find__cstr_find),\
    UT_CASE(test__hashtable_find__cstr_not_find),\
    UT_CASE(test__hashtable_find__libcstl_builtin_find),\
    UT_CASE(test__hashtable_find__libcstl_builtin_not_find),\
    UT_CASE(test__hashtable_find__user_define_find),\
    UT_CASE(test__hashtable_find__user_define_not_find),\
    UT_CASE_BEGIN(_hashtable_clear, test__hashtable_clear__null_hashtable),\
    UT_CASE(test__hashtable_clear__non_inited),\
    UT_CASE(test__hashtable_clear__empty),\
    UT_CASE(test__hashtable_clear__non_empty),\
    UT_CASE_BEGIN(_hashtable_count, test__hashtable_count__null_hashtable),\
    UT_CASE(test__hashtable_count__null_value),\
    UT_CASE(test__hashtable_count__non_inited),\
    UT_CASE(test__hashtable_count__c_builtin_0),\
    UT_CASE(test__hashtable_count__c_builtin_1),\
    UT_CASE(test__hashtable_count__c_builtin_n),\
    UT_CASE(test__hashtable_count__cstr_0),\
    UT_CASE(test__hashtable_count__cstr_1),\
    UT_CASE(test__hashtable_count__cstr_n),\
    UT_CASE(test__hashtable_count__libcstl_builtin_0),\
    UT_CASE(test__hashtable_count__libcstl_builtin_1),\
    UT_CASE(test__hashtable_count__libcstl_builtin_n),\
    UT_CASE(test__hashtable_count__user_define_0),\
    UT_CASE(test__hashtable_count__user_define_1),\
    UT_CASE(test__hashtable_count__user_define_n),\
    UT_CASE_BEGIN(_hashtable_equal_range, test__hashtable_equal_range__null_hashtable),\
    UT_CASE(test__hashtable_equal_range__null_value),\
    UT_CASE(test__hashtable_equal_range__non_inited),\
    UT_CASE(test__hashtable_equal_range__end),\
    UT_CASE(test__hashtable_equal_range__c_builtin_equal),\
    UT_CASE(test__hashtable_equal_range__c_builtin_greater),\
    UT_CASE(test__hashtable_equal_range__cstr_upper_equal),\
    UT_CASE(test__hashtable_equal_range__cstr_greater),\
    UT_CASE(test__hashtable_equal_range__libcstl_builtin_equal),\
    UT_CASE(test__hashtable_equal_range__libcstl_builtin_greater),\
    UT_CASE(test__hashtable_equal_range__user_define_equal),\
    UT_CASE(test__hashtable_equal_range__user_define_greater),\
    UT_CASE_BEGIN(_hashtable_equal, test__hashtable_equal__null_first),\
    UT_CASE(test__hashtable_equal__null_second),\
    UT_CASE(test__hashtable_equal__non_inited_first),\
    UT_CASE(test__hashtable_equal__non_inited_second),\
    UT_CASE(test__hashtable_equal__not_same_type),\
    UT_CASE(test__hashtable_equal__not_same_bucket),\
    UT_CASE(test__hashtable_equal__same_hashtable),\
    UT_CASE(test__hashtable_equal__size_first_less_than_second),\
    UT_CASE(test__hashtable_equal__size_first_greater_than_second),\
    UT_CASE(test__hashtable_equal__size_equal_0),\
    UT_CASE(test__hashtable_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__hashtable_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__hashtable_equal__compare_not_equal),\
    UT_CASE(test__hashtable_equal__equal),\
    UT_CASE_BEGIN(_hashtable_not_equal, test__hashtable_not_equal__null_first),\
    UT_CASE(test__hashtable_not_equal__null_second),\
    UT_CASE(test__hashtable_not_equal__non_inited_first),\
    UT_CASE(test__hashtable_not_equal__non_inited_second),\
    UT_CASE(test__hashtable_not_equal__not_same_type),\
    UT_CASE(test__hashtable_not_equal__not_same_bucket),\
    UT_CASE(test__hashtable_not_equal__same_hashtable),\
    UT_CASE(test__hashtable_not_equal__size_first_less_than_second),\
    UT_CASE(test__hashtable_not_equal__size_first_greater_than_second),\
    UT_CASE(test__hashtable_not_equal__size_equal_0),\
    UT_CASE(test__hashtable_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__hashtable_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__hashtable_not_equal__compare_not_equal),\
    UT_CASE(test__hashtable_not_equal__equal),\
    UT_CASE_BEGIN(_hashtable_less, test__hashtable_less__null_first),\
    UT_CASE(test__hashtable_less__null_second),\
    UT_CASE(test__hashtable_less__non_inited_first),\
    UT_CASE(test__hashtable_less__non_inited_second),\
    UT_CASE(test__hashtable_less__not_same_type),\
    UT_CASE(test__hashtable_less__same_hashtable),\
    UT_CASE(test__hashtable_less__size_first_less_than_second),\
    UT_CASE(test__hashtable_less__size_first_greater_than_second),\
    UT_CASE(test__hashtable_less__size_equal_0),\
    UT_CASE(test__hashtable_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test__hashtable_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__hashtable_less__compare_less),\
    UT_CASE(test__hashtable_less__equal),\
    UT_CASE_BEGIN(_hashtable_less_equal, test__hashtable_less_equal__null_first),\
    UT_CASE(test__hashtable_less_equal__null_second),\
    UT_CASE(test__hashtable_less_equal__non_inited_first),\
    UT_CASE(test__hashtable_less_equal__non_inited_second),\
    UT_CASE(test__hashtable_less_equal__not_same_type),\
    UT_CASE(test__hashtable_less_equal__same_hashtable),\
    UT_CASE(test__hashtable_less_equal__size_first_less_than_second),\
    UT_CASE(test__hashtable_less_equal__size_first_greater_than_second),\
    UT_CASE(test__hashtable_less_equal__size_equal_0),\
    UT_CASE(test__hashtable_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__hashtable_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__hashtable_less_equal__compare_less),\
    UT_CASE(test__hashtable_less_equal__equal),\
    UT_CASE_BEGIN(_hashtable_greater, test__hashtable_greater__null_first),\
    UT_CASE(test__hashtable_greater__null_second),\
    UT_CASE(test__hashtable_greater__non_inited_first),\
    UT_CASE(test__hashtable_greater__non_inited_second),\
    UT_CASE(test__hashtable_greater__not_same_type),\
    UT_CASE(test__hashtable_greater__same_hashtable),\
    UT_CASE(test__hashtable_greater__size_first_less_than_second),\
    UT_CASE(test__hashtable_greater__size_first_greater_than_second),\
    UT_CASE(test__hashtable_greater__size_equal_0),\
    UT_CASE(test__hashtable_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test__hashtable_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__hashtable_greater__compare_less),\
    UT_CASE(test__hashtable_greater__equal),\
    UT_CASE_BEGIN(_hashtable_greater_equal, test__hashtable_greater_equal__null_first),\
    UT_CASE(test__hashtable_greater_equal__null_second),\
    UT_CASE(test__hashtable_greater_equal__non_inited_first),\
    UT_CASE(test__hashtable_greater_equal__non_inited_second),\
    UT_CASE(test__hashtable_greater_equal__not_same_type),\
    UT_CASE(test__hashtable_greater_equal__same_hashtable),\
    UT_CASE(test__hashtable_greater_equal__size_first_less_than_second),\
    UT_CASE(test__hashtable_greater_equal__size_first_greater_than_second),\
    UT_CASE(test__hashtable_greater_equal__size_equal_0),\
    UT_CASE(test__hashtable_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test__hashtable_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test__hashtable_greater_equal__compare_less),\
    UT_CASE(test__hashtable_greater_equal__equal),\
    UT_CASE_BEGIN(_hashtable_swap, test__hashtable_swap__null_first),\
    UT_CASE(test__hashtable_swap__null_second),\
    UT_CASE(test__hashtable_swap__non_inited_first),\
    UT_CASE(test__hashtable_swap__non_inited_second),\
    UT_CASE(test__hashtable_swap__not_same_type),\
    UT_CASE(test__hashtable_swap__not_same_hash),\
    UT_CASE(test__hashtable_swap__same_hashtable),\
    UT_CASE(test__hashtable_swap__0_swap_n),\
    UT_CASE(test__hashtable_swap__n_swap_0),\
    UT_CASE(test__hashtable_swap__n_swap_n),\
    UT_CASE(test__hashtable_swap__m_swap_n),\
    UT_CASE_BEGIN(_hashtable_insert_unique, test__hashtable_insert_unique__null_hashtable),\
    UT_CASE(test__hashtable_insert_unique__null_value),\
    UT_CASE(test__hashtable_insert_unique__non_inited),\
    UT_CASE(test__hashtable_insert_unique__c_builtin_equal),\
    UT_CASE(test__hashtable_insert_unique__c_builtin_not_equal),\
    UT_CASE(test__hashtable_insert_unique__cstr_equal),\
    UT_CASE(test__hashtable_insert_unique__cstr_not_equal),\
    UT_CASE(test__hashtable_insert_unique__libcstl_builtin_equal),\
    UT_CASE(test__hashtable_insert_unique__libcstl_builtin_not_equal),\
    UT_CASE(test__hashtable_insert_unique__user_define_equal),\
    UT_CASE(test__hashtable_insert_unique__user_define_not_equal),\
    UT_CASE_BEGIN(_hashtable_insert_equal, test__hashtable_insert_equal__null_hashtable),\
    UT_CASE(test__hashtable_insert_equal__null_value),\
    UT_CASE(test__hashtable_insert_equal__non_inited),\
    UT_CASE(test__hashtable_insert_equal__c_builtin_equal),\
    UT_CASE(test__hashtable_insert_equal__c_builtin_not_equal),\
    UT_CASE(test__hashtable_insert_equal__cstr_equal),\
    UT_CASE(test__hashtable_insert_equal__cstr_not_equal),\
    UT_CASE(test__hashtable_insert_equal__libcstl_builtin_equal),\
    UT_CASE(test__hashtable_insert_equal__libcstl_builtin_not_equal),\
    UT_CASE(test__hashtable_insert_equal__user_define_equal),\
    UT_CASE(test__hashtable_insert_equal__user_define_not_equal),\
    UT_CASE_BEGIN(_hashtable_insert_equal_array, test__hashtable_insert_equal_array__null_hashtable),\
    UT_CASE(test__hashtable_insert_equal_array__non_inited),\
    UT_CASE(test__hashtable_insert_equal_array__invalid_array),\
    UT_CASE(test__hashtable_insert_equal_array__empty),\
    UT_CASE(test__hashtable_insert_equal_array__non_empty_equal),\
    UT_CASE(test__hashtable_insert_equal_array__non_empty_dest_src_dup),\
    UT_CASE(test__hashtable_insert_equal_array__non_empty_src_dup),\
    UT_CASE_BEGIN(_hashtable_insert_unique_range, test__hashtable_insert_unique_range__null_hashtable),\
    UT_CASE(test__hashtable_insert_unique_range__non_inited),\
    UT_CASE(test__hashtable_insert_unique_range__invalid_begin),\
    UT_CASE(test__hashtable_insert_unique_range__invalid_end),\
    UT_CASE(test__hashtable_insert_unique_range__invalid_range),\
    UT_CASE(test__hashtable_insert_unique_range__not_same_type),\
    UT_CASE(test__hashtable_insert_unique_range__empty),\
    UT_CASE(test__hashtable_insert_unique_range__non_empty_equal),\
    UT_CASE(test__hashtable_insert_unique_range__non_empty_dest_src_dup),\
    UT_CASE(test__hashtable_insert_unique_range__non_empty_src_dup),\
    UT_CASE(test__hashtable_insert_unique_range__compare),\
    UT_CASE_BEGIN(_hashtable_insert_unique_array, test__hashtable_insert_unique_array__null_hashtable),\
    UT_CASE(test__hashtable_insert_unique_array__non_inited),\
    UT_CASE(test__hashtable_insert_unique_array__invalid_array),\
    UT_CASE(test__hashtable_insert_unique_array__empty),\
    UT_CASE(test__hashtable_insert_unique_array__non_empty_equal),\
    UT_CASE(test__hashtable_insert_unique_array__non_empty_dest_src_dup),\
    UT_CASE(test__hashtable_insert_unique_array__non_empty_src_dup),\
    UT_CASE_BEGIN(_hashtable_insert_equal_range, test__hashtable_insert_equal_range__null_hashtable),\
    UT_CASE(test__hashtable_insert_equal_range__non_inited),\
    UT_CASE(test__hashtable_insert_equal_range__invalid_begin),\
    UT_CASE(test__hashtable_insert_equal_range__invalid_end),\
    UT_CASE(test__hashtable_insert_equal_range__invalid_range),\
    UT_CASE(test__hashtable_insert_equal_range__not_same_type),\
    UT_CASE(test__hashtable_insert_equal_range__empty),\
    UT_CASE(test__hashtable_insert_equal_range__non_empty_equal),\
    UT_CASE(test__hashtable_insert_equal_range__non_empty_dest_src_dup),\
    UT_CASE(test__hashtable_insert_equal_range__non_empty_src_dup),\
    UT_CASE(test__hashtable_insert_equal_range__compare),\
    UT_CASE_BEGIN(_hashtable_erase_pos, test__hashtable_erase_pos__null_hashtable),\
    UT_CASE(test__hashtable_erase_pos__non_inited),\
    UT_CASE(test__hashtable_erase_pos__invalid_pos),\
    UT_CASE(test__hashtable_erase_pos__end),\
    UT_CASE(test__hashtable_erase_pos__begin),\
    UT_CASE(test__hashtable_erase_pos__middle),\
    UT_CASE(test__hashtable_erase_pos__last),\
    UT_CASE(test__hashtable_erase_pos__erase_empty),\
    UT_CASE_BEGIN(_hashtable_erase_range, test__hashtable_erase_range__null_hashtable),\
    UT_CASE(test__hashtable_erase_range__non_inited),\
    UT_CASE(test__hashtable_erase_range__invalid_begin),\
    UT_CASE(test__hashtable_erase_range__invalid_end),\
    UT_CASE(test__hashtable_erase_range__invalid_range),\
    UT_CASE(test__hashtable_erase_range__empty),\
    UT_CASE(test__hashtable_erase_range__begin),\
    UT_CASE(test__hashtable_erase_range__middle),\
    UT_CASE(test__hashtable_erase_range__end),\
    UT_CASE(test__hashtable_erase_range__all),\
    UT_CASE_BEGIN(_hashtable_erase, test__hashtable_erase__null_hashtable),\
    UT_CASE(test__hashtable_erase__null_value),\
    UT_CASE(test__hashtable_erase__non_inited),\
    UT_CASE(test__hashtable_erase__c_builtin_0),\
    UT_CASE(test__hashtable_erase__c_builtin_1),\
    UT_CASE(test__hashtable_erase__c_builtin_n),\
    UT_CASE(test__hashtable_erase__cstr_0),\
    UT_CASE(test__hashtable_erase__cstr_1),\
    UT_CASE(test__hashtable_erase__cstr_n),\
    UT_CASE(test__hashtable_erase__libcstl_builtin_0),\
    UT_CASE(test__hashtable_erase__libcstl_builtin_1),\
    UT_CASE(test__hashtable_erase__libcstl_builtin_n),\
    UT_CASE(test__hashtable_erase__user_define_0),\
    UT_CASE(test__hashtable_erase__user_define_1),\
    UT_CASE(test__hashtable_erase__user_define_n),\
    UT_CASE_BEGIN(_hashtable_resize, test__hashtable_resize__null_hashtable),\
    UT_CASE(test__hashtable_resize__non_inited),\
    UT_CASE(test__hashtable_resize__less_bucketcount),\
    UT_CASE(test__hashtable_resize__equal_bucketcount),\
    UT_CASE(test__hashtable_resize__greater_bucketcount)

#endif /* _UT_CSTL_HASHTABLE_H_ */

