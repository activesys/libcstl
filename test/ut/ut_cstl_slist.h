#ifndef _UT_CSTL_SLIST_H_
#define _UT_CSTL_SLIST_H_

UT_SUIT_DECLARATION(cstl_slist)

/*
 * test slist_init
 */
UT_CASE_DECLARATION(slist_init)
void test_slist_init__null_slist_container(void** state);
void test_slist_init__non_created_slist_container(void** state);
void test_slist_init__successfully(void** state);
/*
 * test slist_init_n
 */
UT_CASE_DECLARATION(slist_init_n)
void test_slist_init_n__null_slist_container(void** state);
void test_slist_init_n__non_created_slist_container(void** state);
void test_slist_init_n__empty(void** state);
void test_slist_init_n__c_builtin(void** state);
void test_slist_init_n__cstr(void** stat);
void test_slist_init_n__libcstl_builtin(void** state);
void test_slist_init_n__user_define(void** state);
/*
 * test slist_init_copy
 */
UT_CASE_DECLARATION(slist_init_copy)
void test_slist_init_copy__null_dest_slist_container(void** state);
void test_slist_init_copy__null_src_slist_container(void** state);
void test_slist_init_copy__non_created_dest_slist_container(void** state);
void test_slist_init_copy__non_inited_src_slist_container(void** state);
void test_slist_init_copy__not_same_type(void** state);
void test_slist_init_copy__init_copy_empty(void** state);
void test_slist_init_copy__c_builtin(void** state);
void test_slist_init_copy__cstr(void** state);
void test_slist_init_copy__libcstl_builtin(void** state);
void test_slist_init_copy__user_define(void** state);
/*
 * test slist_init_copy_range
 */
UT_CASE_DECLARATION(slist_init_copy_range)
void test_slist_init_copy_range__null_slist_container(void** state);
void test_slist_init_copy_range__non_created_slist_container(void** state);
void test_slist_init_copy_range__invalid_range(void** state);
void test_slist_init_copy_range__not_same(void** state);
void test_slist_init_copy_range__init_copy_range_empty(void** state);
void test_slist_init_copy_range__c_builtin(void** state);
void test_slist_init_copy_range__cstr(void** state);
void test_slist_init_copy_range__libcstl_builtin(void** state);
void test_slist_init_copy_range__user_define(void** state);
void test_slist_init_copy_range__other_container_range(void** state);
/*
 * test slist_init_copy_array
 */
UT_CASE_DECLARATION(slist_init_copy_array)
void test_slist_init_copy_array__null_slist_container(void** state);
void test_slist_init_copy_array__non_created_slist_container(void** state);
void test_slist_init_copy_array__invalid_array(void** state);
void test_slist_init_copy_array__init_copy_array_empty(void** state);
void test_slist_init_copy_array__c_builtin(void** state);
void test_slist_init_copy_array__cstr(void** state);
void test_slist_init_copy_array__libcstl_builtin(void** state);
void test_slist_init_copy_array__user_define(void** state);
/*
 * test slist_destroy
 */
UT_CASE_DECLARATION(slist_destroy)
void test_slist_destroy__null_slist_container(void** state);
void test_slist_destroy__non_created_slist_container(void** state);
void test_slist_destroy__created_non_inited(void** state);
void test_slist_destroy__empty(void** state);
void test_slist_destroy__non_empty(void** state);
/*
 * test slist_size
 */
UT_CASE_DECLARATION(slist_size)
void test_slist_size__null_slist_container(void** state);
void test_slist_size__non_inited_slist_container(void** state);
void test_slist_size__empty(void** state);
void test_slist_size__non_empty(void** state);
/*
 * test slist_empty
 */
UT_CASE_DECLARATION(slist_empty)
void test_slist_empty__null_slist_container(void** state);
void test_slist_empty__non_inited_slist_container(void** state);
void test_slist_empty__empty(void** state);
void test_slist_empty__non_empty(void** state);
/*
 * test slist_max_size
 */
UT_CASE_DECLARATION(slist_max_size)
void test_slist_max_size__null_slist_container(void** state);
void test_slist_max_size__non_inited_slist_container(void** state);
void test_slist_max_size__empty(void** state);
void test_slist_max_size__non_empty(void** state);
/*
 * test slist_equal
 */
UT_CASE_DECLARATION(slist_equal)
void test_slist_equal__null_first(void** state);
void test_slist_equal__null_second(void** state);
void test_slist_equal__non_inited_first(void** state);
void test_slist_equal__non_inited_second(void** state);
void test_slist_equal__not_same_type(void** state);
void test_slist_equal__same_slist(void** state);
void test_slist_equal__size_first_less_than_second(void** state);
void test_slist_equal__size_first_greater_than_second(void** state);
void test_slist_equal__size_equal_0(void** state);
void test_slist_equal__size_equal_elem_first_less_than_second(void** state);
void test_slist_equal__size_equal_elem_first_greater_than_second(void** state);
void test_slist_equal__size_equal_elem_equal(void** state);
/*
 * test slist_not_equal
 */
UT_CASE_DECLARATION(slist_not_equal)
void test_slist_not_equal__null_first(void** state);
void test_slist_not_equal__null_second(void** state);
void test_slist_not_equal__non_inited_first(void** state);
void test_slist_not_equal__non_inited_second(void** state);
void test_slist_not_equal__not_same_type(void** state);
void test_slist_not_equal__same_slist(void** state);
void test_slist_not_equal__size_first_less_than_second(void** state);
void test_slist_not_equal__size_first_greater_than_second(void** state);
void test_slist_not_equal__size_equal_0(void** state);
void test_slist_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_slist_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_slist_not_equal__size_equal_elem_equal(void** state);
/*
 * test slist_less
 */
UT_CASE_DECLARATION(slist_less)
void test_slist_less__null_first(void** state);
void test_slist_less__null_second(void** state);
void test_slist_less__non_inited_first(void** state);
void test_slist_less__non_inited_second(void** state);
void test_slist_less__not_same_type(void** state);
void test_slist_less__same_slist(void** state);
void test_slist_less__size_first_less_than_second(void** state);
void test_slist_less__size_first_greater_than_second(void** state);
void test_slist_less__size_equal_0(void** state);
void test_slist_less__size_equal_elem_first_less_than_second(void** state);
void test_slist_less__size_equal_elem_first_greater_than_second(void** state);
void test_slist_less__size_equal_elem_equal(void** state);
/*
 * test slist_less_equal
 */
UT_CASE_DECLARATION(slist_less_equal)
void test_slist_less_equal__null_first(void** state);
void test_slist_less_equal__null_second(void** state);
void test_slist_less_equal__non_inited_first(void** state);
void test_slist_less_equal__non_inited_second(void** state);
void test_slist_less_equal__not_same_type(void** state);
void test_slist_less_equal__same_slist(void** state);
void test_slist_less_equal__size_first_less_than_second(void** state);
void test_slist_less_equal__size_first_greater_than_second(void** state);
void test_slist_less_equal__size_equal_0(void** state);
void test_slist_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_slist_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_slist_less_equal__size_equal_elem_equal(void** state);
/*
 * test slist_greater
 */
UT_CASE_DECLARATION(slist_greater)
void test_slist_greater__null_first(void** state);
void test_slist_greater__null_second(void** state);
void test_slist_greater__non_inited_first(void** state);
void test_slist_greater__non_inited_second(void** state);
void test_slist_greater__not_same_type(void** state);
void test_slist_greater__same_slist(void** state);
void test_slist_greater__size_first_less_than_second(void** state);
void test_slist_greater__size_first_greater_than_second(void** state);
void test_slist_greater__size_equal_0(void** state);
void test_slist_greater__size_equal_elem_first_less_than_second(void** state);
void test_slist_greater__size_equal_elem_first_greater_than_second(void** state);
void test_slist_greater__size_equal_elem_equal(void** state);
/*
 * test slist_greater_equal
 */
UT_CASE_DECLARATION(slist_greater_equal)
void test_slist_greater_equal__null_first(void** state);
void test_slist_greater_equal__null_second(void** state);
void test_slist_greater_equal__non_inited_first(void** state);
void test_slist_greater_equal__non_inited_second(void** state);
void test_slist_greater_equal__not_same_type(void** state);
void test_slist_greater_equal__same_slist(void** state);
void test_slist_greater_equal__size_first_less_than_second(void** state);
void test_slist_greater_equal__size_first_greater_than_second(void** state);
void test_slist_greater_equal__size_equal_0(void** state);
void test_slist_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_slist_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_slist_greater_equal__size_equal_elem_equal(void** state);
/*
 * test slist_assign
 */
UT_CASE_DECLARATION(slist_assign)
void test_slist_assign__null_dest(void** state);
void test_slist_assign__null_src(void** state);
void test_slist_assign__non_inited_dest(void** state);
void test_slist_assign__non_inited_src(void** state);
void test_slist_assign__not_same_type(void** state);
void test_slist_assign__same_container(void** state);
void test_slist_assign__0_assign_0(void** state);
void test_slist_assign__0_assign_10(void** state);
void test_slist_assign__10_assign_0(void** state);
void test_slist_assign__10_assign_10_slist_equal(void** state);
void test_slist_assign__10_assign_10_slist_not_equal(void** state);
void test_slist_assign__10_assign_1000(void** state);
/*
 * test slist_assign_range
 */
UT_CASE_DECLARATION(slist_assign_range)
void test_slist_assign_range__null_slist_container(void** state);
void test_slist_assign_range__non_inited(void** state);
void test_slist_assign_range__invalid_it_begin(void** state);
void test_slist_assign_range__invalid_it_end(void** state);
void test_slist_assign_range__invalid_range(void** state);
void test_slist_assign_range__invalid_range_not_same_type(void** state);
void test_slist_assign_range__range_belong_to_slist(void** state);
void test_slist_assign_range__0_assign_range_0(void** state);
void test_slist_assign_range__0_assign_range_10(void** state);
void test_slist_assign_range__10_assign_range_0(void** state);
void test_slist_assign_range__10_assign_range_10_same_elem(void** state);
void test_slist_assign_range__10_assign_range_10_not_same_elem(void** state);
void test_slist_assign_range__10_assign_range_1000(void** state);
void test_slist_assign_range__other_container_range(void** state);
/*
 * test slist_assign_array
 */
UT_CASE_DECLARATION(slist_assign_array)
void test_slist_assign_array__null_slist_container(void** state);
void test_slist_assign_array__non_inited(void** state);
void test_slist_assign_array__invalid_array(void** state);
void test_slist_assign_array__0_assign_array_0(void** state);
void test_slist_assign_array__0_assign_array_10(void** state);
void test_slist_assign_array__10_assign_array_0(void** state);
void test_slist_assign_array__10_assign_array_10_same_elem(void** state);
void test_slist_assign_array__10_assign_array_10_not_same_elem(void** state);
void test_slist_assign_array__10_assign_array_1000(void** state);
void test_slist_assign_array__cstr(void** state);
void test_slist_assign_array__user_define(void** state);
/*
 * test slist_swap
 */
UT_CASE_DECLARATION(slist_swap)
void test_slist_swap__null_first(void** state);
void test_slist_swap__null_second(void** state);
void test_slist_swap__non_inited_first(void** state);
void test_slist_swap__non_inited_second(void** state);
void test_slist_swap__not_same_type(void** state);
void test_slist_swap__slist_equal(void** state);
void test_slist_swap__0_swap_10(void** state);
void test_slist_swap__10_swap_0(void** state);
void test_slist_swap__10_swap_10(void** state);
void test_slist_swap__10_swap_1000(void** state);
/*
 * test slist_front
 */
UT_CASE_DECLARATION(slist_front)
void test_slist_front__null_slist_container(void** state);
void test_slist_front__non_inited_slist_container(void** state);
void test_slist_front__empty(void** state);
void test_slist_front__successfully(void** state);
void test_slist_front__successfully_cstr(void** state);
/*
 * test slist_begin
 */
UT_CASE_DECLARATION(slist_begin)
void test_slist_begin__null_slist_container(void** state);
void test_slist_begin__non_inited_slist_container(void** state);
void test_slist_begin__empty(void** state);
void test_slist_begin__non_empty(void** state);
/*
 * test slist_end
 */
UT_CASE_DECLARATION(slist_end)
void test_slist_end__null_slist_container(void** state);
void test_slist_end__non_inited_slist_container(void** state);
void test_slist_end__empty(void** state);
void test_slist_end__non_empty(void** state);
/*
 * test slist_previous
 */
UT_CASE_DECLARATION(slist_previous)
void test_slist_previous__null_slist_container(void** state);
void test_slist_previous__non_inited_slist_container(void** state);
void test_slist_previous__empty(void** state);
void test_slist_previous__non_empty_begin(void** state);
void test_slist_previous__non_empty_non_begin(void** state);
void test_slist_previous__non_empty_end(void** state);
/*
 * test slist_insert_range
 */
UT_CASE_DECLARATION(slist_insert_range)
void test_slist_insert_range__null_slist_container(void** state);
void test_slist_insert_range__non_inited(void** state);
void test_slist_insert_range__invalid_position(void** state);
void test_slist_insert_range__invalid_range(void** state);
void test_slist_insert_range__invalid_range_not_same_type(void** state);
void test_slist_insert_range__invalid_range_belong_to_slist(void** state);
void test_slist_insert_range__empty_insert_0(void** state);
void test_slist_insert_range__empty_insert_10(void** state);
void test_slist_insert_range__begin_insert_0(void** state);
void test_slist_insert_range__begin_insert_10(void** state);
void test_slist_insert_range__middle_insert_0(void** state);
void test_slist_insert_range__middle_insert_10(void** state);
void test_slist_insert_range__end_insert_0(void** state);
void test_slist_insert_range__end_insert_10(void** state);
void test_slist_insert_range__other_container_range(void** state);
/*
 * test slist_insert_array
 */
UT_CASE_DECLARATION(slist_insert_array)
void test_slist_insert_array__null_slist_container(void** state);
void test_slist_insert_array__non_inited(void** state);
void test_slist_insert_array__invalid_position(void** state);
void test_slist_insert_array__invalid_array(void** state);
void test_slist_insert_array__empty_insert_0(void** state);
void test_slist_insert_array__empty_insert_10(void** state);
void test_slist_insert_array__begin_insert_0(void** state);
void test_slist_insert_array__begin_insert_10(void** state);
void test_slist_insert_array__middle_insert_0(void** state);
void test_slist_insert_array__middle_insert_10(void** state);
void test_slist_insert_array__end_insert_0(void** state);
void test_slist_insert_array__end_insert_10(void** state);
void test_slist_insert_array__cstr(void** state);
void test_slist_insert_array__cstl(void** state);
void test_slist_insert_array__user_define(void** state);
/*
 * test slist_insert_after_range
 */
UT_CASE_DECLARATION(slist_insert_after_range)
void test_slist_insert_after_range__null_slist_container(void** state);
void test_slist_insert_after_range__non_inited(void** state);
void test_slist_insert_after_range__invalid_position(void** state);
void test_slist_insert_after_range__invalid_position_end(void** state);
void test_slist_insert_after_range__invalid_range(void** state);
void test_slist_insert_after_range__invalid_range_not_same_type(void** state);
void test_slist_insert_after_range__invalid_range_belong_to_slist(void** state);
void test_slist_insert_after_range__begin_insert_0(void** state);
void test_slist_insert_after_range__begin_insert_10(void** state);
void test_slist_insert_after_range__middle_insert_0(void** state);
void test_slist_insert_after_range__middle_insert_10(void** state);
void test_slist_insert_after_range__end_insert_0(void** state);
void test_slist_insert_after_range__end_insert_10(void** state);
void test_slist_insert_after_range__other_container_range(void** state);
/*
 * test slist_insert_after_array
 */
UT_CASE_DECLARATION(slist_insert_after_array)
void test_slist_insert_after_array__null_slist_container(void** state);
void test_slist_insert_after_array__non_inited(void** state);
void test_slist_insert_after_array__invalid_position(void** state);
void test_slist_insert_after_array__invalid_array(void** state);
void test_slist_insert_after_array__begin_insert_0(void** state);
void test_slist_insert_after_array__begin_insert_10(void** state);
void test_slist_insert_after_array__middle_insert_0(void** state);
void test_slist_insert_after_array__middle_insert_10(void** state);
void test_slist_insert_after_array__end_insert_0(void** state);
void test_slist_insert_after_array__end_insert_10(void** state);
void test_slist_insert_after_array__cstr(void** state);
void test_slist_insert_after_array__cstl(void** state);
void test_slist_insert_after_array__user_define(void** state);
/*
 * test slist_pop_front
 */
UT_CASE_DECLARATION(slist_pop_front)
void test_slist_pop_front__null_slist_container(void** state);
void test_slist_pop_front__non_inited_slist_container(void** state);
void test_slist_pop_front__empty(void** state);
void test_slist_pop_front__successfully(void** state);
/*
 * test slist_erase
 */
UT_CASE_DECLARATION(slist_erase)
void test_slist_erase__null_slist_container(void** state);
void test_slist_erase__non_inited_slist_container(void** state);
void test_slist_erase__invalid_pos_end(void** state);
void test_slist_erase__invalid_pos(void** state);
void test_slist_erase__successfully_begin(void** state);
void test_slist_erase__successfully_middle(void** state);
void test_slist_erase__successfully_back(void** state);
/*
 * test slist_erase_range
 */
UT_CASE_DECLARATION(slist_erase_range)
void test_slist_erase_range__null_slist_container(void** state);
void test_slist_erase_range__non_inited_slist_container(void** state);
void test_slist_erase_range__invalid_range_not_belong_to_slist(void** state);
void test_slist_erase_range__invalid_range(void** state);
void test_slist_erase_range__successfully_empty(void** state);
void test_slist_erase_range__successfully_begin(void** state);
void test_slist_erase_range__successfully_middle(void** state);
void test_slist_erase_range__successfully_end(void** state);
void test_slist_erase_range__successfully_all(void** state);
/*
 * test slist_erase_after
 */
UT_CASE_DECLARATION(slist_erase_after)
void test_slist_erase_after__null_slist_container(void** state);
void test_slist_erase_after__non_inited_slist_container(void** state);
void test_slist_erase_after__invalid_pos_end(void** state);
void test_slist_erase_after__invalid_pos(void** state);
void test_slist_erase_after__successfully_begin(void** state);
void test_slist_erase_after__successfully_middle(void** state);
void test_slist_erase_after__successfully_back(void** state);
void test_slist_erase_after__successfully_last(void** state);
/*
 * test slist_erase_after_range
 */
UT_CASE_DECLARATION(slist_erase_after_range)
void test_slist_erase_after_range__null_slist_container(void** state);
void test_slist_erase_after_range__non_inited_slist_container(void** state);
void test_slist_erase_after_range__invalid_range_not_belong_to_slist(void** state);
void test_slist_erase_after_range__invalid_range_begin_is_slist_end(void** state);
void test_slist_erase_after_range__invalid_range(void** state);
void test_slist_erase_after_range__successfully_empty(void** state);
void test_slist_erase_after_range__successfully_empty_next(void** state);
void test_slist_erase_after_range__successfully_begin(void** state);
void test_slist_erase_after_range__successfully_middle(void** state);
void test_slist_erase_after_range__successfully_end(void** state);
void test_slist_erase_after_range__successfully_all(void** state);
/*
 * test slist_remove_if
 */
UT_CASE_DECLARATION(slist_remove_if)
void test_slist_remove_if__null_slist_container(void** state);
void test_slist_remove_if__non_inited_slist_container(void** state);
void test_slist_remove_if__empty(void** state);
void test_slist_remove_if__non_empty_no_removed(void** state);
void test_slist_remove_if__non_empty_remove(void** state);
void test_slist_remove_if__non_empty_remove_more(void** state);
void test_slist_remove_if__non_empty_remove_all(void** state);
void test_slist_remove_if__empty_default_ufun_op(void** state);
void test_slist_remove_if__non_empty_default_ufun_op(void** state);
void test_slist_remove_if__cstr_empty(void** state);
void test_slist_remove_if__cstr_non_empty_no_removed(void** state);
void test_slist_remove_if__cstr_non_empty_remove(void** state);
void test_slist_remove_if__cstr_non_empty_remove_more(void** state);
void test_slist_remove_if__cstr_non_empty_remove_all(void** state);
/*
 * test slist_resize
 */
UT_CASE_DECLARATION(slist_resize)
void test_slist_resize__null_slist_container(void** state);
void test_slist_resize__non_inited(void** state);
void test_slist_resize__successfully_0_resize_0(void** state);
void test_slist_resize__successfully_0_resize_10(void** state);
void test_slist_resize__successfully_10_resize_0(void** state);
void test_slist_resize__successfully_10_resize_10(void** state);
void test_slist_resize__successfully_10_resize_1000(void** state);
/*
 * test slist_clear
 */
UT_CASE_DECLARATION(slist_clear)
void test_slist_clear__null_slist_container(void** state);
void test_slist_clear__non_inited_slist_container(void** state);
void test_slist_clear__empty_slist_container(void** state);
void test_slist_clear__non_empty_slist_container(void** state);
/*
 * test slist_unique
 */
UT_CASE_DECLARATION(slist_unique)
void test_slist_unique__null_slist_container(void** state);
void test_slist_unique__non_inited_slist_container(void** state);
void test_slist_unique__empty(void** state);
void test_slist_unique__non_empty_no_duplicate(void** state);
void test_slist_unique__non_empty_adjacent_duplicate(void** state);
void test_slist_unique__non_empty_not_adjacent_duplicate(void** state);
void test_slist_unique__non_empty_all_duplicate(void** state);
void test_slist_unique__cstr_non_empty_no_duplicate(void** state);
void test_slist_unique__cstr_non_empty_adjacent_duplicate(void** state);
void test_slist_unique__cstr_non_empty_not_adjacent_duplicate(void** state);
void test_slist_unique__cstr_non_empty_all_duplicate(void** state);
/*
 * test slist_unique_if
 */
UT_CASE_DECLARATION(slist_unique_if)
void test_slist_unique_if__null_slist_container(void** state);
void test_slist_unique_if__non_inited_slist_container(void** state);
void test_slist_unique_if__empty(void** state);
void test_slist_unique_if__non_empty_non_duplicate(void** state);
void test_slist_unique_if__non_empty_duplicate(void** state);
void test_slist_unique_if__non_empty_more_duplicate(void** state);
void test_slist_unique_if__non_empty_duplicate_not_adjacent(void** state);
void test_slist_unique_if__non_empty_duplicate_all(void** state);
void test_slist_unique_if__cstr_non_empty_no_duplicate(void** state);
void test_slist_unique_if__cstr_non_empty_adjacent_duplicate(void** state);
void test_slist_unique_if__cstr_non_empty_not_adjacent_duplicate(void** state);
void test_slist_unique_if__cstr_non_empty_all_duplicate(void** state);
void test_slist_unique_if__default_predicate(void** state);
/*
 * test slist_splice
 */
UT_CASE_DECLARATION(slist_splice)
void test_slist_splice__null_target_slist_container(void** state);
void test_slist_splice__null_source_slist_container(void** state);
void test_slist_splice__non_inited_target_slist_container(void** state);
void test_slist_splice__non_inited_source_slist_container(void** state);
void test_slist_splice__not_same_type(void** state);
void test_slist_splice__invalid_target_position(void** state);
void test_slist_splice__same_slist(void** state);
void test_slist_splice__target_empty_source_empty(void** state);
void test_slist_splice__target_empty_source_non_empty(void** state);
void test_slist_splice__target_begin_source_empty(void** state);
void test_slist_splice__target_begin_source_non_empty(void** state);
void test_slist_splice__target_middle_source_non_empty(void** state);
void test_slist_splice__target_end_source_non_empty(void** state);
/*
 * test slist_splice_pos
 */
UT_CASE_DECLARATION(slist_splice_pos)
void test_slist_splice_pos__null_target_slist_container(void** state);
void test_slist_splice_pos__null_source_slist_container(void** state);
void test_slist_splice_pos__non_inited_target_slist_container(void** state);
void test_slist_splice_pos__non_inited_source_slist_container(void** state);
void test_slist_splice_pos__not_same(void** state);
void test_slist_splice_pos__invalid_tearget_position(void** state);
void test_slist_splice_pos__invalid_source_position(void** state);
void test_slist_splice_pos__invalid_source_position_end(void** state);
void test_slist_splice_pos__same_slist_container_same_position(void** state);
void test_slist_splice_pos__same_slist_container_next_position(void** state);
void test_slist_splice_pos__same_slist_container_not_same_not_next_position(void** state);
void test_slist_splice_pos__target_empty(void** state);
void test_slist_splice_pos__target_begin_source_begin(void** state);
void test_slist_splice_pos__target_middle_source_middle(void** state);
void test_slist_splice_pos__target_end_source_begin(void** state);
/*
 * test slist_splice_range
 */
UT_CASE_DECLARATION(slist_splice_range)
void test_slist_splice_range__null_target_slist_container(void** state);
void test_slist_splice_range__null_source_slist_container(void** state);
void test_slist_splice_range__non_inited_target_slist_container(void** state);
void test_slist_splice_range__non_inited_source_slist_container(void** state);
void test_slist_splice_range__not_same(void** state);
void test_slist_splice_range__invalid_tearget_position(void** state);
void test_slist_splice_range__invalid_source_range(void** state);
void test_slist_splice_range__invalid_target_position_in_range(void** state);
void test_slist_splice_range__same_slist_container_pos_equal_begin(void** state);
void test_slist_splice_range__same_slist_container_pos_equal_end(void** state);
void test_slist_splice_range__same_slist_container_pos_not_in_range(void** state);
void test_slist_splice_range__target_empty_range_empty(void** state);
void test_slist_splice_range__target_empty_range_not_empty(void** state);
void test_slist_splice_range__target_begin_source_begin(void** state);
void test_slist_splice_range__target_middle_source_middle(void** state);
void test_slist_splice_range__target_end_source_all(void** state);
/*
 * test slist_splice_after_pos
 */
UT_CASE_DECLARATION(slist_splice_after_pos)
void test_slist_splice_after_pos__null_target_slist_container(void** state);
void test_slist_splice_after_pos__null_source_slist_container(void** state);
void test_slist_splice_after_pos__non_inited_target_slist_container(void** state);
void test_slist_splice_after_pos__non_inited_source_slist_container(void** state);
void test_slist_splice_after_pos__not_same(void** state);
void test_slist_splice_after_pos__invalid_tearget_position(void** state);
void test_slist_splice_after_pos__invalid_source_position(void** state);
void test_slist_splice_after_pos__invalid_target_position_end(void** state);
void test_slist_splice_after_pos__invalid_source_position_end(void** state);
void test_slist_splice_after_pos__same_slist_container_same_position(void** state);
void test_slist_splice_after_pos__same_slist_container_next_position(void** state);
void test_slist_splice_after_pos__same_slist_container_last_source_position(void** state);
void test_slist_splice_after_pos__same_slist_container_not_same_not_next_position(void** state);
void test_slist_splice_after_pos__target_begin_source_begin(void** state);
void test_slist_splice_after_pos__target_middle_source_middle(void** state);
void test_slist_splice_after_pos__target_last_source_begin(void** state);
void test_slist_splice_after_pos__target_last_source_last(void** state);
/*
 * test slist_splice_after_range
 */
UT_CASE_DECLARATION(slist_splice_after_range)
void test_slist_splice_after_range__null_target_slist_container(void** state);
void test_slist_splice_after_range__null_source_slist_container(void** state);
void test_slist_splice_after_range__non_inited_target_slist_container(void** state);
void test_slist_splice_after_range__non_inited_source_slist_container(void** state);
void test_slist_splice_after_range__not_same(void** state);
void test_slist_splice_after_range__invalid_tearget_position(void** state);
void test_slist_splice_after_range__invalid_source_range(void** state);
void test_slist_splice_after_range__invalid_target_position_end(void** state);
void test_slist_splice_after_range__invalid_source_range_end(void** state);
void test_slist_splice_after_range__invalid_target_position_in_range(void** state);
void test_slist_splice_after_range__same_slist_container_pos_equal_begin(void** state);
void test_slist_splice_after_range__same_slist_container_pos_equal_end(void** state);
void test_slist_splice_after_range__same_slist_container_pos_not_in_range(void** state);
void test_slist_splice_after_range__target_begin_source_begin(void** state);
void test_slist_splice_after_range__target_middle_source_middle(void** state);
void test_slist_splice_after_range__target_last_source_all(void** state);
void test_slist_splice_after_range__target_last_source_empty(void** state);
/*
 * test slist_sort
 */
UT_CASE_DECLARATION(slist_sort)
void test_slist_sort__null_slist_container(void** state);
void test_slist_sort__non_inited_slist_container(void** state);
void test_slist_sort__empty_less(void** state);
void test_slist_sort__1_less(void** state);
void test_slist_sort__2_equal_less(void** state);
void test_slist_sort__2_less_less(void** state);
void test_slist_sort__2_greater_less(void** state);
void test_slist_sort__random_equal_less(void** state);
void test_slist_sort__random_less_less(void** state);
void test_slist_sort__random_greater_less(void** state);
void test_slist_sort__random_random_less(void** state);
void test_slist_sort__random_random_dup_less(void** state);
/*
 * test slist_sort_if
 */
UT_CASE_DECLARATION(slist_sort_if)
void test_slist_sort_if__null_slist_container(void** state);
void test_slist_sort_if__non_inited_slist_container(void** state);
void test_slist_sort_if__empty_less(void** state);
void test_slist_sort_if__empty_greater(void** state);
void test_slist_sort_if__1_less(void** state);
void test_slist_sort_if__1_greater(void** state);
void test_slist_sort_if__2_equal_less(void** state);
void test_slist_sort_if__2_equal_greater(void** state);
void test_slist_sort_if__2_less_less(void** state);
void test_slist_sort_if__2_less_greater(void** state);
void test_slist_sort_if__2_greater_less(void** state);
void test_slist_sort_if__2_greater_greater(void** state);
void test_slist_sort_if__random_equal_less(void** state);
void test_slist_sort_if__random_equal_greater(void** state);
void test_slist_sort_if__random_less_less(void** state);
void test_slist_sort_if__random_less_greater(void** state);
void test_slist_sort_if__random_greater_less(void** state);
void test_slist_sort_if__random_greater_greater(void** state);
void test_slist_sort_if__random_random_less(void** state);
void test_slist_sort_if__random_random_greater(void** state);
void test_slist_sort_if__random_random_dup_less(void** state);
void test_slist_sort_if__random_random_dup_greater(void** state);
void test_slist_sort_if__cstr_1_less(void** state);
void test_slist_sort_if__cstr_1_greater(void** state);
void test_slist_sort_if__cstr_2_equal_less(void** state);
void test_slist_sort_if__cstr_2_equal_greater(void** state);
void test_slist_sort_if__cstr_2_less_less(void** state);
void test_slist_sort_if__cstr_2_less_greater(void** state);
void test_slist_sort_if__cstr_2_greater_less(void** state);
void test_slist_sort_if__cstr_2_greater_greater(void** state);
void test_slist_sort_if__cstr_random_equal_less(void** state);
void test_slist_sort_if__cstr_random_equal_greater(void** state);
void test_slist_sort_if__cstr_random_less_less(void** state);
void test_slist_sort_if__cstr_random_less_greater(void** state);
void test_slist_sort_if__cstr_random_greater_less(void** state);
void test_slist_sort_if__cstr_random_greater_greater(void** state);
void test_slist_sort_if__cstr_random_random_less(void** state);
void test_slist_sort_if__cstr_random_random_greater(void** state);
void test_slist_sort_if__cstr_random_random_dup_less(void** state);
void test_slist_sort_if__cstr_random_random_dup_greater(void** state);
/*
 * test slist_merge
 */
UT_CASE_DECLARATION(slist_merge)
void test_slist_merge__null_dest_slist_container(void** state);
void test_slist_merge__null_src_slist_container(void** state);
void test_slist_merge__non_inited_dest_slist_container(void** state);
void test_slist_merge__non_inited_src_slist_container(void** state);
void test_slist_merge__not_same(void** state);
void test_slist_merge__same_slist_container(void** state);
void test_slist_merge__dest_empty_src_empty(void** state);
void test_slist_merge__dest_non_empty_src_empty(void** state);
void test_slist_merge__dest_empty_src_non_empty(void** state);
void test_slist_merge__dest_tailing(void** state);
void test_slist_merge__src_tailing(void** state);
void test_slist_merge__random(void** state);
void test_slist_merge__cstr_dest_tailing(void** state);
void test_slist_merge__cstr_src_tailing(void** state);
void test_slist_merge__cstr_random(void** state);
/*
 * test slist_merge_if
 */
UT_CASE_DECLARATION(slist_merge_if)
void test_slist_merge_if__null_dest_slist_container(void** state);
void test_slist_merge_if__null_src_slist_container(void** state);
void test_slist_merge_if__non_inited_dest_slist_container(void** state);
void test_slist_merge_if__non_inited_src_slist_container(void** state);
void test_slist_merge_if__not_same(void** state);
void test_slist_merge_if__same_slist_container(void** state);
void test_slist_merge_if__dest_empty_src_empty(void** state);
void test_slist_merge_if__dest_non_empty_src_empty(void** state);
void test_slist_merge_if__dest_empty_src_non_empty(void** state);
void test_slist_merge_if__ascending_dest_tailing(void** state);
void test_slist_merge_if__ascending_src_tailing(void** state);
void test_slist_merge_if__descending_dest_tailing(void** state);
void test_slist_merge_if__descending_src_tailing(void** state);
void test_slist_merge_if__random(void** state);
void test_slist_merge_if__cstr_ascending_dest_tailing(void** state);
void test_slist_merge_if__cstr_ascending_src_tailing(void** state);
void test_slist_merge_if__cstr_descending_dest_tailing(void** state);
void test_slist_merge_if__cstr_descending_src_tailing(void** state);
void test_slist_merge_if__cstr_random(void** state);
/*
 * test slist_reverse
 */
UT_CASE_DECLARATION(slist_reverse)
void test_slist_reverse__null_slist_container(void** state);
void test_slist_reverse__non_inited_slist_container(void** state);
void test_slist_reverse__empty(void** state);
void test_slist_reverse__same(void** state);
void test_slist_reverse__not_same(void** state);

#define UT_CSTL_SLIST_CASE\
    UT_SUIT_BEGIN(cstl_slist, test_slist_init__null_slist_container),\
    UT_CASE(test_slist_init__non_created_slist_container),\
    UT_CASE(test_slist_init__successfully),\
    UT_CASE_BEGIN(slist_init_n, test_slist_init_n__null_slist_container),\
    UT_CASE(test_slist_init_n__non_created_slist_container),\
    UT_CASE(test_slist_init_n__empty),\
    UT_CASE(test_slist_init_n__c_builtin),\
    UT_CASE(test_slist_init_n__cstr),\
    UT_CASE(test_slist_init_n__libcstl_builtin),\
    UT_CASE(test_slist_init_n__user_define),\
    UT_CASE_BEGIN(slist_init_copy, test_slist_init_copy__null_dest_slist_container),\
    UT_CASE(test_slist_init_copy__null_src_slist_container),\
    UT_CASE(test_slist_init_copy__non_created_dest_slist_container),\
    UT_CASE(test_slist_init_copy__non_inited_src_slist_container),\
    UT_CASE(test_slist_init_copy__not_same_type),\
    UT_CASE(test_slist_init_copy__init_copy_empty),\
    UT_CASE(test_slist_init_copy__c_builtin),\
    UT_CASE(test_slist_init_copy__cstr),\
    UT_CASE(test_slist_init_copy__libcstl_builtin),\
    UT_CASE(test_slist_init_copy__user_define),\
    UT_CASE_BEGIN(slist_init_copy_range, test_slist_init_copy_range__null_slist_container),\
    UT_CASE(test_slist_init_copy_range__non_created_slist_container),\
    UT_CASE(test_slist_init_copy_range__invalid_range),\
    UT_CASE(test_slist_init_copy_range__not_same),\
    UT_CASE(test_slist_init_copy_range__init_copy_range_empty),\
    UT_CASE(test_slist_init_copy_range__c_builtin),\
    UT_CASE(test_slist_init_copy_range__cstr),\
    UT_CASE(test_slist_init_copy_range__libcstl_builtin),\
    UT_CASE(test_slist_init_copy_range__user_define),\
    UT_CASE(test_slist_init_copy_range__other_container_range),\
    UT_CASE_BEGIN(slist_init_copy_array, test_slist_init_copy_array__null_slist_container),\
    UT_CASE(test_slist_init_copy_array__non_created_slist_container),\
    UT_CASE(test_slist_init_copy_array__invalid_array),\
    UT_CASE(test_slist_init_copy_array__init_copy_array_empty),\
    UT_CASE(test_slist_init_copy_array__c_builtin),\
    UT_CASE(test_slist_init_copy_array__cstr),\
    UT_CASE(test_slist_init_copy_array__libcstl_builtin),\
    UT_CASE(test_slist_init_copy_array__user_define),\
    UT_CASE_BEGIN(slist_destroy, test_slist_destroy__null_slist_container),\
    UT_CASE(test_slist_destroy__non_created_slist_container),\
    UT_CASE(test_slist_destroy__created_non_inited),\
    UT_CASE(test_slist_destroy__empty),\
    UT_CASE(test_slist_destroy__non_empty),\
    UT_CASE_BEGIN(slist_size, test_slist_size__null_slist_container),\
    UT_CASE(test_slist_size__non_inited_slist_container),\
    UT_CASE(test_slist_size__empty),\
    UT_CASE(test_slist_size__non_empty),\
    UT_CASE_BEGIN(slist_empty, test_slist_empty__null_slist_container),\
    UT_CASE(test_slist_empty__non_inited_slist_container),\
    UT_CASE(test_slist_empty__empty),\
    UT_CASE(test_slist_empty__non_empty),\
    UT_CASE_BEGIN(slist_max_size, test_slist_max_size__null_slist_container),\
    UT_CASE(test_slist_max_size__non_inited_slist_container),\
    UT_CASE(test_slist_max_size__empty),\
    UT_CASE(test_slist_max_size__non_empty),\
    UT_CASE_BEGIN(slist_equal, test_slist_equal__null_first),\
    UT_CASE(test_slist_equal__null_second),\
    UT_CASE(test_slist_equal__non_inited_first),\
    UT_CASE(test_slist_equal__non_inited_second),\
    UT_CASE(test_slist_equal__not_same_type),\
    UT_CASE(test_slist_equal__same_slist),\
    UT_CASE(test_slist_equal__size_first_less_than_second),\
    UT_CASE(test_slist_equal__size_first_greater_than_second),\
    UT_CASE(test_slist_equal__size_equal_0),\
    UT_CASE(test_slist_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_slist_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_slist_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(slist_not_equal, test_slist_not_equal__null_first),\
    UT_CASE(test_slist_not_equal__null_second),\
    UT_CASE(test_slist_not_equal__non_inited_first),\
    UT_CASE(test_slist_not_equal__non_inited_second),\
    UT_CASE(test_slist_not_equal__not_same_type),\
    UT_CASE(test_slist_not_equal__same_slist),\
    UT_CASE(test_slist_not_equal__size_first_less_than_second),\
    UT_CASE(test_slist_not_equal__size_first_greater_than_second),\
    UT_CASE(test_slist_not_equal__size_equal_0),\
    UT_CASE(test_slist_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_slist_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_slist_not_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(slist_less, test_slist_less__null_first),\
    UT_CASE(test_slist_less__null_second),\
    UT_CASE(test_slist_less__non_inited_first),\
    UT_CASE(test_slist_less__non_inited_second),\
    UT_CASE(test_slist_less__not_same_type),\
    UT_CASE(test_slist_less__same_slist),\
    UT_CASE(test_slist_less__size_first_less_than_second),\
    UT_CASE(test_slist_less__size_first_greater_than_second),\
    UT_CASE(test_slist_less__size_equal_0),\
    UT_CASE(test_slist_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_slist_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_slist_less__size_equal_elem_equal),\
    UT_CASE_BEGIN(slist_less_equal, test_slist_less_equal__null_first),\
    UT_CASE(test_slist_less_equal__null_second),\
    UT_CASE(test_slist_less_equal__non_inited_first),\
    UT_CASE(test_slist_less_equal__non_inited_second),\
    UT_CASE(test_slist_less_equal__not_same_type),\
    UT_CASE(test_slist_less_equal__same_slist),\
    UT_CASE(test_slist_less_equal__size_first_less_than_second),\
    UT_CASE(test_slist_less_equal__size_first_greater_than_second),\
    UT_CASE(test_slist_less_equal__size_equal_0),\
    UT_CASE(test_slist_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_slist_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_slist_less_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(slist_greater, test_slist_greater__null_first),\
    UT_CASE(test_slist_greater__null_second),\
    UT_CASE(test_slist_greater__non_inited_first),\
    UT_CASE(test_slist_greater__non_inited_second),\
    UT_CASE(test_slist_greater__not_same_type),\
    UT_CASE(test_slist_greater__same_slist),\
    UT_CASE(test_slist_greater__size_first_less_than_second),\
    UT_CASE(test_slist_greater__size_first_greater_than_second),\
    UT_CASE(test_slist_greater__size_equal_0),\
    UT_CASE(test_slist_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_slist_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_slist_greater__size_equal_elem_equal),\
    UT_CASE_BEGIN(slist_greater_equal, test_slist_greater_equal__null_first),\
    UT_CASE(test_slist_greater_equal__null_second),\
    UT_CASE(test_slist_greater_equal__non_inited_first),\
    UT_CASE(test_slist_greater_equal__non_inited_second),\
    UT_CASE(test_slist_greater_equal__not_same_type),\
    UT_CASE(test_slist_greater_equal__same_slist),\
    UT_CASE(test_slist_greater_equal__size_first_less_than_second),\
    UT_CASE(test_slist_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_slist_greater_equal__size_equal_0),\
    UT_CASE(test_slist_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_slist_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_slist_greater_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(slist_assign, test_slist_assign__null_dest),\
    UT_CASE(test_slist_assign__null_src),\
    UT_CASE(test_slist_assign__non_inited_dest),\
    UT_CASE(test_slist_assign__non_inited_src),\
    UT_CASE(test_slist_assign__not_same_type),\
    UT_CASE(test_slist_assign__same_container),\
    UT_CASE(test_slist_assign__0_assign_0),\
    UT_CASE(test_slist_assign__0_assign_10),\
    UT_CASE(test_slist_assign__10_assign_0),\
    UT_CASE(test_slist_assign__10_assign_10_slist_equal),\
    UT_CASE(test_slist_assign__10_assign_10_slist_not_equal),\
    UT_CASE(test_slist_assign__10_assign_1000),\
    UT_CASE_BEGIN(slist_assign_range, test_slist_assign_range__null_slist_container),\
    UT_CASE(test_slist_assign_range__non_inited),\
    UT_CASE(test_slist_assign_range__invalid_it_begin),\
    UT_CASE(test_slist_assign_range__invalid_it_end),\
    UT_CASE(test_slist_assign_range__invalid_range),\
    UT_CASE(test_slist_assign_range__invalid_range_not_same_type),\
    UT_CASE(test_slist_assign_range__range_belong_to_slist),\
    UT_CASE(test_slist_assign_range__0_assign_range_0),\
    UT_CASE(test_slist_assign_range__0_assign_range_10),\
    UT_CASE(test_slist_assign_range__10_assign_range_0),\
    UT_CASE(test_slist_assign_range__10_assign_range_10_same_elem),\
    UT_CASE(test_slist_assign_range__10_assign_range_10_not_same_elem),\
    UT_CASE(test_slist_assign_range__10_assign_range_1000),\
    UT_CASE(test_slist_assign_range__other_container_range),\
    UT_CASE_BEGIN(slist_assign_array, test_slist_assign_array__null_slist_container),\
    UT_CASE(test_slist_assign_array__non_inited),\
    UT_CASE(test_slist_assign_array__invalid_array),\
    UT_CASE(test_slist_assign_array__0_assign_array_0),\
    UT_CASE(test_slist_assign_array__0_assign_array_10),\
    UT_CASE(test_slist_assign_array__10_assign_array_0),\
    UT_CASE(test_slist_assign_array__10_assign_array_10_same_elem),\
    UT_CASE(test_slist_assign_array__10_assign_array_10_not_same_elem),\
    UT_CASE(test_slist_assign_array__10_assign_array_1000),\
    UT_CASE(test_slist_assign_array__cstr),\
    UT_CASE(test_slist_assign_array__user_define),\
    UT_CASE_BEGIN(slist_swap, test_slist_swap__null_first),\
    UT_CASE(test_slist_swap__null_second),\
    UT_CASE(test_slist_swap__non_inited_first),\
    UT_CASE(test_slist_swap__non_inited_second),\
    UT_CASE(test_slist_swap__not_same_type),\
    UT_CASE(test_slist_swap__slist_equal),\
    UT_CASE(test_slist_swap__0_swap_10),\
    UT_CASE(test_slist_swap__10_swap_0),\
    UT_CASE(test_slist_swap__10_swap_10),\
    UT_CASE(test_slist_swap__10_swap_1000),\
    UT_CASE_BEGIN(slist_front, test_slist_front__null_slist_container),\
    UT_CASE(test_slist_front__non_inited_slist_container),\
    UT_CASE(test_slist_front__empty),\
    UT_CASE(test_slist_front__successfully),\
    UT_CASE(test_slist_front__successfully_cstr),\
    UT_CASE_BEGIN(slist_begin, test_slist_begin__null_slist_container),\
    UT_CASE(test_slist_begin__non_inited_slist_container),\
    UT_CASE(test_slist_begin__empty),\
    UT_CASE(test_slist_begin__non_empty),\
    UT_CASE_BEGIN(slist_end, test_slist_end__null_slist_container),\
    UT_CASE(test_slist_end__non_inited_slist_container),\
    UT_CASE(test_slist_end__empty),\
    UT_CASE(test_slist_end__non_empty),\
    UT_CASE_BEGIN(slist_previous, test_slist_previous__null_slist_container),\
    UT_CASE(test_slist_previous__non_inited_slist_container),\
    UT_CASE(test_slist_previous__empty),\
    UT_CASE(test_slist_previous__non_empty_begin),\
    UT_CASE(test_slist_previous__non_empty_non_begin),\
    UT_CASE(test_slist_previous__non_empty_end),\
    UT_CASE_BEGIN(slist_insert_range, test_slist_insert_range__null_slist_container),\
    UT_CASE(test_slist_insert_range__non_inited),\
    UT_CASE(test_slist_insert_range__invalid_position),\
    UT_CASE(test_slist_insert_range__invalid_range),\
    UT_CASE(test_slist_insert_range__invalid_range_not_same_type),\
    UT_CASE(test_slist_insert_range__invalid_range_belong_to_slist),\
    UT_CASE(test_slist_insert_range__empty_insert_0),\
    UT_CASE(test_slist_insert_range__empty_insert_10),\
    UT_CASE(test_slist_insert_range__begin_insert_0),\
    UT_CASE(test_slist_insert_range__begin_insert_10),\
    UT_CASE(test_slist_insert_range__middle_insert_0),\
    UT_CASE(test_slist_insert_range__middle_insert_10),\
    UT_CASE(test_slist_insert_range__end_insert_0),\
    UT_CASE(test_slist_insert_range__end_insert_10),\
    UT_CASE(test_slist_insert_range__other_container_range),\
    UT_CASE_BEGIN(slist_insert_array, test_slist_insert_array__null_slist_container),\
    UT_CASE(test_slist_insert_array__non_inited),\
    UT_CASE(test_slist_insert_array__invalid_position),\
    UT_CASE(test_slist_insert_array__invalid_array),\
    UT_CASE(test_slist_insert_array__empty_insert_0),\
    UT_CASE(test_slist_insert_array__empty_insert_10),\
    UT_CASE(test_slist_insert_array__begin_insert_0),\
    UT_CASE(test_slist_insert_array__begin_insert_10),\
    UT_CASE(test_slist_insert_array__middle_insert_0),\
    UT_CASE(test_slist_insert_array__middle_insert_10),\
    UT_CASE(test_slist_insert_array__end_insert_0),\
    UT_CASE(test_slist_insert_array__end_insert_10),\
    UT_CASE(test_slist_insert_array__cstr),\
    UT_CASE(test_slist_insert_array__cstl),\
    UT_CASE(test_slist_insert_array__user_define),\
    UT_CASE_BEGIN(slist_insert_after_range, test_slist_insert_after_range__null_slist_container),\
    UT_CASE(test_slist_insert_after_range__non_inited),\
    UT_CASE(test_slist_insert_after_range__invalid_position),\
    UT_CASE(test_slist_insert_after_range__invalid_position_end),\
    UT_CASE(test_slist_insert_after_range__invalid_range),\
    UT_CASE(test_slist_insert_after_range__invalid_range_not_same_type),\
    UT_CASE(test_slist_insert_after_range__invalid_range_belong_to_slist),\
    UT_CASE(test_slist_insert_after_range__begin_insert_0),\
    UT_CASE(test_slist_insert_after_range__begin_insert_10),\
    UT_CASE(test_slist_insert_after_range__middle_insert_0),\
    UT_CASE(test_slist_insert_after_range__middle_insert_10),\
    UT_CASE(test_slist_insert_after_range__end_insert_0),\
    UT_CASE(test_slist_insert_after_range__end_insert_10),\
    UT_CASE(test_slist_insert_after_range__other_container_range),\
    UT_CASE_BEGIN(slist_insert_after_array, test_slist_insert_after_array__null_slist_container),\
    UT_CASE(test_slist_insert_after_array__non_inited),\
    UT_CASE(test_slist_insert_after_array__invalid_position),\
    UT_CASE(test_slist_insert_after_array__invalid_array),\
    UT_CASE(test_slist_insert_after_array__begin_insert_0),\
    UT_CASE(test_slist_insert_after_array__begin_insert_10),\
    UT_CASE(test_slist_insert_after_array__middle_insert_0),\
    UT_CASE(test_slist_insert_after_array__middle_insert_10),\
    UT_CASE(test_slist_insert_after_array__end_insert_0),\
    UT_CASE(test_slist_insert_after_array__end_insert_10),\
    UT_CASE(test_slist_insert_after_array__cstr),\
    UT_CASE(test_slist_insert_after_array__cstl),\
    UT_CASE(test_slist_insert_after_array__user_define),\
    UT_CASE_BEGIN(slist_pop_front, test_slist_pop_front__null_slist_container),\
    UT_CASE(test_slist_pop_front__non_inited_slist_container),\
    UT_CASE(test_slist_pop_front__empty),\
    UT_CASE(test_slist_pop_front__successfully),\
    UT_CASE_BEGIN(slist_erase, test_slist_erase__null_slist_container),\
    UT_CASE(test_slist_erase__non_inited_slist_container),\
    UT_CASE(test_slist_erase__invalid_pos_end),\
    UT_CASE(test_slist_erase__invalid_pos),\
    UT_CASE(test_slist_erase__successfully_begin),\
    UT_CASE(test_slist_erase__successfully_middle),\
    UT_CASE(test_slist_erase__successfully_back),\
    UT_CASE_BEGIN(slist_erase_range, test_slist_erase_range__null_slist_container),\
    UT_CASE(test_slist_erase_range__non_inited_slist_container),\
    UT_CASE(test_slist_erase_range__invalid_range_not_belong_to_slist),\
    UT_CASE(test_slist_erase_range__invalid_range),\
    UT_CASE(test_slist_erase_range__successfully_empty),\
    UT_CASE(test_slist_erase_range__successfully_begin),\
    UT_CASE(test_slist_erase_range__successfully_middle),\
    UT_CASE(test_slist_erase_range__successfully_end),\
    UT_CASE(test_slist_erase_range__successfully_all),\
    UT_CASE_BEGIN(slist_erase_after, test_slist_erase_after__null_slist_container),\
    UT_CASE(test_slist_erase_after__non_inited_slist_container),\
    UT_CASE(test_slist_erase_after__invalid_pos_end),\
    UT_CASE(test_slist_erase_after__invalid_pos),\
    UT_CASE(test_slist_erase_after__successfully_begin),\
    UT_CASE(test_slist_erase_after__successfully_middle),\
    UT_CASE(test_slist_erase_after__successfully_back),\
    UT_CASE(test_slist_erase_after__successfully_last),\
    UT_CASE_BEGIN(slist_erase_after_range, test_slist_erase_after_range__null_slist_container),\
    UT_CASE(test_slist_erase_after_range__non_inited_slist_container),\
    UT_CASE(test_slist_erase_after_range__invalid_range_not_belong_to_slist),\
    UT_CASE(test_slist_erase_after_range__invalid_range_begin_is_slist_end),\
    UT_CASE(test_slist_erase_after_range__invalid_range),\
    UT_CASE(test_slist_erase_after_range__successfully_empty),\
    UT_CASE(test_slist_erase_after_range__successfully_empty_next),\
    UT_CASE(test_slist_erase_after_range__successfully_begin),\
    UT_CASE(test_slist_erase_after_range__successfully_middle),\
    UT_CASE(test_slist_erase_after_range__successfully_end),\
    UT_CASE(test_slist_erase_after_range__successfully_all),\
    UT_CASE_BEGIN(slist_remove_if, test_slist_remove_if__null_slist_container),\
    UT_CASE(test_slist_remove_if__non_inited_slist_container),\
    UT_CASE(test_slist_remove_if__empty),\
    UT_CASE(test_slist_remove_if__non_empty_no_removed),\
    UT_CASE(test_slist_remove_if__non_empty_remove),\
    UT_CASE(test_slist_remove_if__non_empty_remove_more),\
    UT_CASE(test_slist_remove_if__non_empty_remove_all),\
    UT_CASE(test_slist_remove_if__empty_default_ufun_op),\
    UT_CASE(test_slist_remove_if__non_empty_default_ufun_op),\
    UT_CASE(test_slist_remove_if__cstr_empty),\
    UT_CASE(test_slist_remove_if__cstr_non_empty_no_removed),\
    UT_CASE(test_slist_remove_if__cstr_non_empty_remove),\
    UT_CASE(test_slist_remove_if__cstr_non_empty_remove_more),\
    UT_CASE(test_slist_remove_if__cstr_non_empty_remove_all),\
    UT_CASE_BEGIN(slist_resize, test_slist_resize__null_slist_container),\
    UT_CASE(test_slist_resize__non_inited),\
    UT_CASE(test_slist_resize__successfully_0_resize_0),\
    UT_CASE(test_slist_resize__successfully_0_resize_10),\
    UT_CASE(test_slist_resize__successfully_10_resize_0),\
    UT_CASE(test_slist_resize__successfully_10_resize_10),\
    UT_CASE(test_slist_resize__successfully_10_resize_1000),\
    UT_CASE_BEGIN(slist_clear, test_slist_clear__null_slist_container),\
    UT_CASE(test_slist_clear__non_inited_slist_container),\
    UT_CASE(test_slist_clear__empty_slist_container),\
    UT_CASE(test_slist_clear__non_empty_slist_container),\
    UT_CASE_BEGIN(slist_unique, test_slist_unique__null_slist_container),\
    UT_CASE(test_slist_unique__non_inited_slist_container),\
    UT_CASE(test_slist_unique__empty),\
    UT_CASE(test_slist_unique__non_empty_no_duplicate),\
    UT_CASE(test_slist_unique__non_empty_adjacent_duplicate),\
    UT_CASE(test_slist_unique__non_empty_not_adjacent_duplicate),\
    UT_CASE(test_slist_unique__non_empty_all_duplicate),\
    UT_CASE(test_slist_unique__cstr_non_empty_no_duplicate),\
    UT_CASE(test_slist_unique__cstr_non_empty_adjacent_duplicate),\
    UT_CASE(test_slist_unique__cstr_non_empty_not_adjacent_duplicate),\
    UT_CASE(test_slist_unique__cstr_non_empty_all_duplicate),\
    UT_CASE_BEGIN(slist_unique_if, test_slist_unique_if__null_slist_container),\
    UT_CASE(test_slist_unique_if__non_inited_slist_container),\
    UT_CASE(test_slist_unique_if__empty),\
    UT_CASE(test_slist_unique_if__non_empty_non_duplicate),\
    UT_CASE(test_slist_unique_if__non_empty_duplicate),\
    UT_CASE(test_slist_unique_if__non_empty_more_duplicate),\
    UT_CASE(test_slist_unique_if__non_empty_duplicate_not_adjacent),\
    UT_CASE(test_slist_unique_if__non_empty_duplicate_all),\
    UT_CASE(test_slist_unique_if__cstr_non_empty_no_duplicate),\
    UT_CASE(test_slist_unique_if__cstr_non_empty_adjacent_duplicate),\
    UT_CASE(test_slist_unique_if__cstr_non_empty_not_adjacent_duplicate),\
    UT_CASE(test_slist_unique_if__cstr_non_empty_all_duplicate),\
    UT_CASE(test_slist_unique_if__default_predicate),\
    UT_CASE_BEGIN(slist_splice, test_slist_splice__null_target_slist_container),\
    UT_CASE(test_slist_splice__null_source_slist_container),\
    UT_CASE(test_slist_splice__non_inited_target_slist_container),\
    UT_CASE(test_slist_splice__non_inited_source_slist_container),\
    UT_CASE(test_slist_splice__not_same_type),\
    UT_CASE(test_slist_splice__invalid_target_position),\
    UT_CASE(test_slist_splice__same_slist),\
    UT_CASE(test_slist_splice__target_empty_source_empty),\
    UT_CASE(test_slist_splice__target_empty_source_non_empty),\
    UT_CASE(test_slist_splice__target_begin_source_empty),\
    UT_CASE(test_slist_splice__target_begin_source_non_empty),\
    UT_CASE(test_slist_splice__target_middle_source_non_empty),\
    UT_CASE(test_slist_splice__target_end_source_non_empty),\
    UT_CASE_BEGIN(slist_splice_pos, test_slist_splice_pos__null_target_slist_container),\
    UT_CASE(test_slist_splice_pos__null_source_slist_container),\
    UT_CASE(test_slist_splice_pos__non_inited_target_slist_container),\
    UT_CASE(test_slist_splice_pos__non_inited_source_slist_container),\
    UT_CASE(test_slist_splice_pos__not_same),\
    UT_CASE(test_slist_splice_pos__invalid_tearget_position),\
    UT_CASE(test_slist_splice_pos__invalid_source_position),\
    UT_CASE(test_slist_splice_pos__invalid_source_position_end),\
    UT_CASE(test_slist_splice_pos__same_slist_container_same_position),\
    UT_CASE(test_slist_splice_pos__same_slist_container_next_position),\
    UT_CASE(test_slist_splice_pos__same_slist_container_not_same_not_next_position),\
    UT_CASE(test_slist_splice_pos__target_empty),\
    UT_CASE(test_slist_splice_pos__target_begin_source_begin),\
    UT_CASE(test_slist_splice_pos__target_middle_source_middle),\
    UT_CASE(test_slist_splice_pos__target_end_source_begin),\
    UT_CASE_BEGIN(slist_splice_range, test_slist_splice_range__null_target_slist_container),\
    UT_CASE(test_slist_splice_range__null_source_slist_container),\
    UT_CASE(test_slist_splice_range__non_inited_target_slist_container),\
    UT_CASE(test_slist_splice_range__non_inited_source_slist_container),\
    UT_CASE(test_slist_splice_range__not_same),\
    UT_CASE(test_slist_splice_range__invalid_tearget_position),\
    UT_CASE(test_slist_splice_range__invalid_source_range),\
    UT_CASE(test_slist_splice_range__invalid_target_position_in_range),\
    UT_CASE(test_slist_splice_range__same_slist_container_pos_equal_begin),\
    UT_CASE(test_slist_splice_range__same_slist_container_pos_equal_end),\
    UT_CASE(test_slist_splice_range__same_slist_container_pos_not_in_range),\
    UT_CASE(test_slist_splice_range__target_empty_range_empty),\
    UT_CASE(test_slist_splice_range__target_empty_range_not_empty),\
    UT_CASE(test_slist_splice_range__target_begin_source_begin),\
    UT_CASE(test_slist_splice_range__target_middle_source_middle),\
    UT_CASE(test_slist_splice_range__target_end_source_all),\
    UT_CASE_BEGIN(slist_splice_after_pos, test_slist_splice_after_pos__null_target_slist_container),\
    UT_CASE(test_slist_splice_after_pos__null_source_slist_container),\
    UT_CASE(test_slist_splice_after_pos__non_inited_target_slist_container),\
    UT_CASE(test_slist_splice_after_pos__non_inited_source_slist_container),\
    UT_CASE(test_slist_splice_after_pos__not_same),\
    UT_CASE(test_slist_splice_after_pos__invalid_tearget_position),\
    UT_CASE(test_slist_splice_after_pos__invalid_source_position),\
    UT_CASE(test_slist_splice_after_pos__invalid_target_position_end),\
    UT_CASE(test_slist_splice_after_pos__invalid_source_position_end),\
    UT_CASE(test_slist_splice_after_pos__same_slist_container_same_position),\
    UT_CASE(test_slist_splice_after_pos__same_slist_container_next_position),\
    UT_CASE(test_slist_splice_after_pos__same_slist_container_last_source_position),\
    UT_CASE(test_slist_splice_after_pos__same_slist_container_not_same_not_next_position),\
    UT_CASE(test_slist_splice_after_pos__target_begin_source_begin),\
    UT_CASE(test_slist_splice_after_pos__target_middle_source_middle),\
    UT_CASE(test_slist_splice_after_pos__target_last_source_begin),\
    UT_CASE(test_slist_splice_after_pos__target_last_source_last),\
    UT_CASE_BEGIN(slist_splice_after_range, test_slist_splice_after_range__null_target_slist_container),\
    UT_CASE(test_slist_splice_after_range__null_source_slist_container),\
    UT_CASE(test_slist_splice_after_range__non_inited_target_slist_container),\
    UT_CASE(test_slist_splice_after_range__non_inited_source_slist_container),\
    UT_CASE(test_slist_splice_after_range__not_same),\
    UT_CASE(test_slist_splice_after_range__invalid_tearget_position),\
    UT_CASE(test_slist_splice_after_range__invalid_source_range),\
    UT_CASE(test_slist_splice_after_range__invalid_target_position_end),\
    UT_CASE(test_slist_splice_after_range__invalid_source_range_end),\
    UT_CASE(test_slist_splice_after_range__invalid_target_position_in_range),\
    UT_CASE(test_slist_splice_after_range__same_slist_container_pos_equal_begin),\
    UT_CASE(test_slist_splice_after_range__same_slist_container_pos_equal_end),\
    UT_CASE(test_slist_splice_after_range__same_slist_container_pos_not_in_range),\
    UT_CASE(test_slist_splice_after_range__target_begin_source_begin),\
    UT_CASE(test_slist_splice_after_range__target_middle_source_middle),\
    UT_CASE(test_slist_splice_after_range__target_last_source_all),\
    UT_CASE(test_slist_splice_after_range__target_last_source_empty),\
    UT_CASE_BEGIN(slist_sort, test_slist_sort__null_slist_container),\
    UT_CASE(test_slist_sort__non_inited_slist_container),\
    UT_CASE(test_slist_sort__empty_less),\
    UT_CASE(test_slist_sort__1_less),\
    UT_CASE(test_slist_sort__2_equal_less),\
    UT_CASE(test_slist_sort__2_less_less),\
    UT_CASE(test_slist_sort__2_greater_less),\
    UT_CASE(test_slist_sort__random_equal_less),\
    UT_CASE(test_slist_sort__random_less_less),\
    UT_CASE(test_slist_sort__random_greater_less),\
    UT_CASE(test_slist_sort__random_random_less),\
    UT_CASE(test_slist_sort__random_random_dup_less),\
    UT_CASE_BEGIN(slist_sort_if, test_slist_sort_if__null_slist_container),\
    UT_CASE(test_slist_sort_if__non_inited_slist_container),\
    UT_CASE(test_slist_sort_if__empty_less),\
    UT_CASE(test_slist_sort_if__empty_greater),\
    UT_CASE(test_slist_sort_if__1_less),\
    UT_CASE(test_slist_sort_if__1_greater),\
    UT_CASE(test_slist_sort_if__2_equal_less),\
    UT_CASE(test_slist_sort_if__2_equal_greater),\
    UT_CASE(test_slist_sort_if__2_less_less),\
    UT_CASE(test_slist_sort_if__2_less_greater),\
    UT_CASE(test_slist_sort_if__2_greater_less),\
    UT_CASE(test_slist_sort_if__2_greater_greater),\
    UT_CASE(test_slist_sort_if__random_equal_less),\
    UT_CASE(test_slist_sort_if__random_equal_greater),\
    UT_CASE(test_slist_sort_if__random_less_less),\
    UT_CASE(test_slist_sort_if__random_less_greater),\
    UT_CASE(test_slist_sort_if__random_greater_less),\
    UT_CASE(test_slist_sort_if__random_greater_greater),\
    UT_CASE(test_slist_sort_if__random_random_less),\
    UT_CASE(test_slist_sort_if__random_random_greater),\
    UT_CASE(test_slist_sort_if__random_random_dup_less),\
    UT_CASE(test_slist_sort_if__random_random_dup_greater),\
    UT_CASE(test_slist_sort_if__cstr_1_less),\
    UT_CASE(test_slist_sort_if__cstr_1_greater),\
    UT_CASE(test_slist_sort_if__cstr_2_equal_less),\
    UT_CASE(test_slist_sort_if__cstr_2_equal_greater),\
    UT_CASE(test_slist_sort_if__cstr_2_less_less),\
    UT_CASE(test_slist_sort_if__cstr_2_less_greater),\
    UT_CASE(test_slist_sort_if__cstr_2_greater_less),\
    UT_CASE(test_slist_sort_if__cstr_2_greater_greater),\
    UT_CASE(test_slist_sort_if__cstr_random_equal_less),\
    UT_CASE(test_slist_sort_if__cstr_random_equal_greater),\
    UT_CASE(test_slist_sort_if__cstr_random_less_less),\
    UT_CASE(test_slist_sort_if__cstr_random_less_greater),\
    UT_CASE(test_slist_sort_if__cstr_random_greater_less),\
    UT_CASE(test_slist_sort_if__cstr_random_greater_greater),\
    UT_CASE(test_slist_sort_if__cstr_random_random_less),\
    UT_CASE(test_slist_sort_if__cstr_random_random_greater),\
    UT_CASE(test_slist_sort_if__cstr_random_random_dup_less),\
    UT_CASE(test_slist_sort_if__cstr_random_random_dup_greater),\
    UT_CASE_BEGIN(slist_merge, test_slist_merge__null_dest_slist_container),\
    UT_CASE(test_slist_merge__null_src_slist_container),\
    UT_CASE(test_slist_merge__non_inited_dest_slist_container),\
    UT_CASE(test_slist_merge__non_inited_src_slist_container),\
    UT_CASE(test_slist_merge__not_same),\
    UT_CASE(test_slist_merge__same_slist_container),\
    UT_CASE(test_slist_merge__dest_empty_src_empty),\
    UT_CASE(test_slist_merge__dest_non_empty_src_empty),\
    UT_CASE(test_slist_merge__dest_empty_src_non_empty),\
    UT_CASE(test_slist_merge__dest_tailing),\
    UT_CASE(test_slist_merge__src_tailing),\
    UT_CASE(test_slist_merge__random),\
    UT_CASE(test_slist_merge__cstr_dest_tailing),\
    UT_CASE(test_slist_merge__cstr_src_tailing),\
    UT_CASE(test_slist_merge__cstr_random),\
    UT_CASE_BEGIN(slist_merge_if, test_slist_merge_if__null_dest_slist_container),\
    UT_CASE(test_slist_merge_if__null_src_slist_container),\
    UT_CASE(test_slist_merge_if__non_inited_dest_slist_container),\
    UT_CASE(test_slist_merge_if__non_inited_src_slist_container),\
    UT_CASE(test_slist_merge_if__not_same),\
    UT_CASE(test_slist_merge_if__same_slist_container),\
    UT_CASE(test_slist_merge_if__dest_empty_src_empty),\
    UT_CASE(test_slist_merge_if__dest_non_empty_src_empty),\
    UT_CASE(test_slist_merge_if__dest_empty_src_non_empty),\
    UT_CASE(test_slist_merge_if__ascending_dest_tailing),\
    UT_CASE(test_slist_merge_if__ascending_src_tailing),\
    UT_CASE(test_slist_merge_if__descending_dest_tailing),\
    UT_CASE(test_slist_merge_if__descending_src_tailing),\
    UT_CASE(test_slist_merge_if__random),\
    UT_CASE(test_slist_merge_if__cstr_ascending_dest_tailing),\
    UT_CASE(test_slist_merge_if__cstr_ascending_src_tailing),\
    UT_CASE(test_slist_merge_if__cstr_descending_dest_tailing),\
    UT_CASE(test_slist_merge_if__cstr_descending_src_tailing),\
    UT_CASE(test_slist_merge_if__cstr_random),\
    UT_CASE_BEGIN(slist_reverse, test_slist_reverse__null_slist_container),\
    UT_CASE(test_slist_reverse__non_inited_slist_container),\
    UT_CASE(test_slist_reverse__empty),\
    UT_CASE(test_slist_reverse__same),\
    UT_CASE(test_slist_reverse__not_same)

#endif /* _UT_CSTL_SLIST_H_ */

